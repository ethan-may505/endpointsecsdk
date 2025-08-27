#!/bin/bash

set -e

PROJECT_NAME="go-sample"
GO_FILE="./src/main.go"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Detect platform
detect_platform() {
    case "$(uname -s)" in
        Linux*)     PLATFORM=linux;;
        Darwin*)    PLATFORM=darwin;;
        CYGWIN*|MINGW*|MSYS*) PLATFORM=windows;;
        *)          PLATFORM=unknown;;
    esac
    
    case "$(uname -m)" in
        x86_64|amd64) ARCH=amd64;;
        i386|i686)    
            print_error "i386/i686 (32-bit) architecture is not supported. Only x64 and ARM64 are supported."
            exit 1
            ;;
        arm64|aarch64) ARCH=arm64;;
        armv7l)       
            print_error "ARMv7 (32-bit ARM) architecture is not supported. Only x64 and ARM64 are supported."
            exit 1
            ;;
        *)            ARCH=amd64;;  # Default to amd64
    esac
}

# Check if Go is installed
check_go() {
    if ! command -v go &> /dev/null; then
        print_error "Go is not installed or not in PATH"
        print_status "Please install Go from https://golang.org/dl/"
        exit 1
    fi
    
    GO_VERSION=$(go version | awk '{print $3}')
    print_status "Found Go version: $GO_VERSION"
}

# Download SDK files using the Python SDK downloader
download_sdk() {
    print_status "Checking if SDK files need to be downloaded..."
    
    # Check if inc and libs directories exist
    if [ ! -d "inc" ] || [ ! -d "libs" ] || [ ! -f "inc/wa_api.h" ]; then
        print_status "SDK files not found. Downloading using Python SDK downloader..."
        
        # Check if Python SDK downloader exists
        PYTHON_SDK_DOWNLOADER_DIR="../OPSWAT-SDK-Downloader/PythonSDKDownloader"
        PYTHON_SDK_DOWNLOADER_MAIN="$PYTHON_SDK_DOWNLOADER_DIR/main.py"
        
        if [ ! -d "$PYTHON_SDK_DOWNLOADER_DIR" ]; then
            print_error "Python SDK downloader not found at $PYTHON_SDK_DOWNLOADER_DIR"
            print_status "Please ensure OPSWAT-SDK-Downloader is available in the root directory"
            exit 1
        fi
        
        if [ ! -f "$PYTHON_SDK_DOWNLOADER_MAIN" ]; then
            print_error "Python SDK downloader main.py not found at $PYTHON_SDK_DOWNLOADER_MAIN"
            exit 1
        fi
        
        # Check for Python
        PYTHON_CMD=""
        if command -v py &> /dev/null; then
            PYTHON_CMD="py"
        elif command -v python3 &> /dev/null; then
            PYTHON_CMD="python3"
        elif command -v python &> /dev/null; then
            PYTHON_CMD="python"
        else
            print_error "Python is not installed or not in PATH"
            print_status "Please install Python from https://python.org/"
            exit 1
        fi
        
        # Run the Python SDK downloader
        print_status "Running Python SDK downloader with $PYTHON_CMD..."
        cd "$PYTHON_SDK_DOWNLOADER_DIR"
        if ! $PYTHON_CMD main.py "$(pwd)/../.." "go-sample"; then
            print_error "Python SDK downloader failed"
            exit 1
        fi
        cd - > /dev/null
        
        print_success "SDK files downloaded successfully"
        
        # Setup SDK file structure for Go build
        print_status "Setting up SDK file structure for Go build..."
        if [ -f "setup-sdk-files.sh" ]; then
            if ! ./setup-sdk-files.sh; then
                print_error "SDK file structure setup failed"
                exit 1
            fi
        else
            print_error "setup-sdk-files.sh not found"
            exit 1
        fi
    else
        print_status "SDK files already present"
    fi
}

# Check for required files
check_files() {
    print_status "Checking for required files..."
    
    if [ ! -f "$GO_FILE" ]; then
        print_error "Go source file '$GO_FILE' not found"
        exit 1
    fi
    
    # Download SDK files if needed
    download_sdk
    
    if [ ! -d "inc" ]; then
        print_error "Include directory 'inc' not found even after SDK download"
        exit 1
    fi
    
    if [ ! -f "inc/wa_api.h" ]; then
        print_error "MDES SDK header 'inc/wa_api.h' not found even after SDK download"
        exit 1
    fi
    
    # Check for platform-specific library directory
    LIBS_DIR="libs"
    if [ ! -d "$LIBS_DIR" ]; then
        print_error "Libraries directory '$LIBS_DIR' not found even after SDK download"
        exit 1
    fi
    
    # Check for platform-specific library in extract directory
    EXTRACT_LIBS_DIR=""
    LIB_FILE=""
    case $PLATFORM in
        linux)
            EXTRACT_LIBS_DIR="extract/linux/bin/detection"
            case $ARCH in
                amd64) EXTRACT_LIBS_DIR="$EXTRACT_LIBS_DIR/x64/release";;
                arm64) EXTRACT_LIBS_DIR="$EXTRACT_LIBS_DIR/arm64/release";;
                *)     EXTRACT_LIBS_DIR="$EXTRACT_LIBS_DIR/x64/release";;  # Default to x64
            esac
            LIB_FILE="libwaapi.so"
            ;;
        darwin)
            EXTRACT_LIBS_DIR="extract/mac/bin/detection/release"
            LIB_FILE="libwaapi.dylib"
            ;;
        windows)
            EXTRACT_LIBS_DIR="extract/windows/lib"
            case $ARCH in
                amd64) EXTRACT_LIBS_DIR="$EXTRACT_LIBS_DIR/x64/release";;
                arm64) EXTRACT_LIBS_DIR="$EXTRACT_LIBS_DIR/arm64/release";;
                *)     EXTRACT_LIBS_DIR="$EXTRACT_LIBS_DIR/x64/release";;  # Default to x64
            esac
            LIB_FILE="libwaapi.lib"
            ;;
    esac
    
    if [ ! -d "$EXTRACT_LIBS_DIR" ]; then
        print_error "Extract libraries directory '$EXTRACT_LIBS_DIR' not found"
        exit 1
    fi
    
    if [ ! -f "$EXTRACT_LIBS_DIR/$LIB_FILE" ]; then
        print_error "MDES SDK library '$EXTRACT_LIBS_DIR/$LIB_FILE' not found"
        print_status "Available libraries in $EXTRACT_LIBS_DIR:"
        ls -la "$EXTRACT_LIBS_DIR" | head -10
        exit 1
    fi
    
    print_success "Found MDES SDK library: $EXTRACT_LIBS_DIR/$LIB_FILE"
}

# Set up environment variables for CGO
setup_cgo() {
    print_status "Setting up CGO environment for $PLATFORM/$ARCH..."
    
    export CGO_ENABLED=1
    export GOOS=$PLATFORM
    export GOARCH=$ARCH
    
    # Set platform-specific CGO flags with correct library path
    case $PLATFORM in
        linux)
            case $ARCH in
                amd64) export CGO_LDFLAGS="-L./extract/linux/bin/detection/x64/release -lwaapi";;
                arm64) export CGO_LDFLAGS="-L./extract/linux/bin/detection/arm64/release -lwaapi";;
                *)     export CGO_LDFLAGS="-L./extract/linux/bin/detection/x64/release -lwaapi";;
            esac
            ;;
        darwin)
            export CGO_LDFLAGS="-L./extract/mac/bin/detection/release -lwaapi"
            ;;
        windows)
            case $ARCH in
                amd64) export CGO_LDFLAGS="-L./extract/windows/lib/x64/release -lwaapi";;
                arm64) export CGO_LDFLAGS="-L./extract/windows/lib/arm64/release -lwaapi";;
                *)     export CGO_LDFLAGS="-L./extract/windows/lib/x64/release -lwaapi";;
            esac
            ;;
    esac
    
    export CGO_CFLAGS="-I./inc"
}

# Build the project
build_project() {
    print_status "Building $PROJECT_NAME for $PLATFORM/$ARCH..."

    # Create build directory
    BUILD_DIR="build"
    mkdir -p "$BUILD_DIR"

    # Set output binary name based on platform
    OUTPUT_NAME="$PROJECT_NAME"
    if [ "$PLATFORM" = "windows" ]; then
        OUTPUT_NAME="$PROJECT_NAME.exe"
    fi
    OUTPUT_PATH="$BUILD_DIR/$OUTPUT_NAME"

    # Build command
    BUILD_CMD="go build -o $OUTPUT_PATH $GO_FILE"

    print_status "Running: $BUILD_CMD"

    if $BUILD_CMD; then
        print_success "Build completed successfully!"
        print_success "Binary created: $OUTPUT_PATH"

        # Make executable on Unix-like systems
        if [ "$PLATFORM" != "windows" ]; then
            chmod +x "$OUTPUT_PATH"
        fi

        # Show file info
        if command -v file &> /dev/null && [ "$PLATFORM" != "windows" ]; then
            print_status "Binary info: $(file $OUTPUT_PATH)"
        fi

        # Show file size
        if [ -f "$OUTPUT_PATH" ]; then
            SIZE=$(du -h "$OUTPUT_PATH" | cut -f1)
            print_status "Binary size: $SIZE"
        fi

        # Copy platform-specific libraries to build directory
        print_status "Copying platform libraries to $BUILD_DIR..."
        case $PLATFORM in
            linux)
                # Copy main libraries (unversioned)
                cp libs/linux/libwaapi.so "$BUILD_DIR/" 2>/dev/null || true
                cp libs/linux/libwautils.so "$BUILD_DIR/" 2>/dev/null || true
                cp libs/linux/libwaheap.so "$BUILD_DIR/" 2>/dev/null || true
                # Copy architecture-specific libraries if they exist
                case $ARCH in
                    amd64) 
                        # Standard x64 libraries are the default libwaapi.so
                        ;;
                    arm64)
                        cp libs/linux/arm64_libwaapi.so "$BUILD_DIR/libwaapi.so" 2>/dev/null || true
                        ;;
                esac
                print_status "Copied Linux libraries: libwaapi.so, libwautils.so, libwaheap.so"
                ;;
            darwin)
                # Copy required dylibs for Mac
                cp libs/mac/libwaapi.dylib "$BUILD_DIR/" 2>/dev/null || true
                cp libs/mac/libwautils.dylib "$BUILD_DIR/" 2>/dev/null || true
                # Note: libwaheap.dylib doesn't exist on Mac platform
                print_status "Copied Mac libraries: libwaapi.dylib, libwautils.dylib"
                ;;
            windows)
                # Copy Windows DLLs directly
                rm -f "$BUILD_DIR/"*.dll 2>/dev/null || true
                
                # Determine architecture-specific library prefix
                ARCH_PREFIX=""
                case $ARCH in
                    amd64) ARCH_PREFIX="x64_" ;;
                    arm64) ARCH_PREFIX="arm64_" ;;
                    *)     ARCH_PREFIX="x64_" ;;  # Default to x64
                esac
                
                # Copy architecture-specific libwaapi.dll and rename it
                if [ -f "libs/win/${ARCH_PREFIX}libwaapi.dll" ]; then
                    cp "libs/win/${ARCH_PREFIX}libwaapi.dll" "$BUILD_DIR/libwaapi.dll"
                    print_status "Copied and renamed: libwaapi.dll"
                fi
                
                # Copy additional required DLLs (not architecture-specific)
                for dll in libwautils.dll libwaheap.dll; do
                    if [ -f "libs/win/$dll" ]; then
                        cp "libs/win/$dll" "$BUILD_DIR/"
                        print_status "Copied additional DLL: $dll"
                    else
                        print_warning "Additional DLL not found: $dll"
                    fi
                done
                
                # Copy executables
                for exe in wa_3rd_party_host_*.exe; do
                    if [ -f "libs/win/$exe" ]; then
                        cp "libs/win/$exe" "$BUILD_DIR/"
                        print_status "Copied executable: $exe"
                    fi
                done
                
                print_status "Copied Windows libraries: libwaapi.dll, libwautils.dll, libwaheap.dll"
                ;;
        esac
        print_success "Copied platform libraries to $BUILD_DIR."
    else
        print_error "Build failed!"
        exit 1
    fi
}

# Clean previous builds
clean_build() {
    print_status "Cleaning previous builds..."
    rm -rf build/
}

# Main execution
main() {
    print_status "Starting build process..."
    
    detect_platform
    print_status "Detected platform: $PLATFORM/$ARCH"
    
    check_go
    check_files
    
    if [ "$1" = "clean" ]; then
        clean_build
        print_success "Clean completed"
        exit 0
    fi
    
    setup_cgo
    build_project
    
    print_success "Build process completed successfully!"
    print_status "To run the program:"
    if [ "$PLATFORM" = "windows" ]; then
        print_status "  cd build && .\\$PROJECT_NAME.exe"
    else
        print_status "  cd build && ./go-sample"
    fi
}

# Show help
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo "Usage: $0 [clean]"
    echo ""
    echo "Options:"
    echo "  clean    Clean previous builds"
    echo "  -h, --help    Show this help message"
    echo ""
    exit 0
fi

# Run main function
main "$@"