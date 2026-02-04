#!/bin/bash

# Setup SDK files script - creates the expected inc and libs structure from downloaded SDK

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[SETUP]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

setup_sdk_structure() {
    print_status "Setting up SDK file structure for Go build..."
    
    # Check if extract directory exists
    if [ ! -d "extract" ]; then
        print_error "Extract directory not found. Please run the SDK downloader first."
        return 1
    fi
    
    # Create inc directory and copy headers
    print_status "Creating inc directory and copying headers..."
    mkdir -p inc
    
    # Copy headers from extracted Windows SDK (they should be the same across platforms)
    if [ -d "extract/windows/inc" ]; then
        cp -r extract/windows/inc/* inc/
        print_status "Copied headers from Windows SDK"
    elif [ -d "extract/linux/inc" ]; then
        cp -r extract/linux/inc/* inc/
        print_status "Copied headers from Linux SDK"
    elif [ -d "extract/mac/inc" ]; then
        cp -r extract/mac/inc/* inc/
        print_status "Copied headers from Mac SDK"
    else
        print_error "No SDK headers found in extract directory"
        return 1
    fi
    
    # Create libs directory structure
    print_status "Creating libs directory and copying libraries..."
    mkdir -p libs
    
    # Copy Windows libraries
    if [ -d "client/windows" ]; then
        mkdir -p libs/win
        print_status "Setting up Windows libraries..."
        
        # Copy libraries and rename them for Go build
        if [ -d "client/windows/x64" ]; then
            cp client/windows/x64/libwaapi.dll libs/win/x64_libwaapi.dll
            cp client/windows/x64/*.dll libs/win/ 2>/dev/null || true
            cp client/windows/x64/*.exe libs/win/ 2>/dev/null || true
        fi
        
        
        if [ -d "client/windows/arm64" ]; then
            cp client/windows/arm64/libwaapi.dll libs/win/arm64_libwaapi.dll
            # Copy other arm64 files
            for file in client/windows/arm64/*.dll; do
                if [ -f "$file" ]; then
                    filename=$(basename "$file")
                    if [ "$filename" != "libwaapi.dll" ]; then
                        cp "$file" libs/win/
                    fi
                fi
            done
            cp client/windows/arm64/*.exe libs/win/ 2>/dev/null || true
        fi
        
        print_status "Windows libraries set up"
    fi
    
    # Copy Linux libraries
    if [ -d "client/linux" ]; then
        mkdir -p libs/linux
        print_status "Setting up Linux libraries..."
        
        if [ -d "client/linux/x64" ]; then
            cp client/linux/x64/libwaapi.so* libs/linux/ 2>/dev/null || true
            cp client/linux/x64/*.so* libs/linux/ 2>/dev/null || true
            cp client/linux/x64/*.dat libs/linux/ 2>/dev/null || true
        fi
        
        
        if [ -d "client/linux/arm64" ]; then
            # Copy arm64 libraries with prefix
            for file in client/linux/arm64/libwaapi.so*; do
                if [ -f "$file" ]; then
                    filename=$(basename "$file")
                    cp "$file" "libs/linux/arm64_$filename"
                fi
            done
        fi
        
        print_status "Linux libraries set up"
    fi
    
    # Copy Mac libraries
    if [ -d "client/mac" ]; then
        mkdir -p libs/mac
        print_status "Setting up Mac libraries..."
        
        cp client/mac/*.dylib libs/mac/ 2>/dev/null || true
        cp client/mac/*.dat libs/mac/ 2>/dev/null || true
        
        print_status "Mac libraries set up"
    fi
    
    print_success "SDK file structure setup complete"
    
    # Show summary
    print_status "Summary:"
    if [ -d "inc" ]; then
        header_count=$(find inc -name "*.h" | wc -l)
        print_status "  Headers: $header_count files in inc/"
    fi
    
    if [ -d "libs" ]; then
        lib_count=$(find libs -name "*.*" | wc -l)
        print_status "  Libraries: $lib_count files in libs/"
        
        if [ -d "libs/win" ]; then
            win_count=$(find libs/win -name "*.dll" -o -name "*.exe" | wc -l)
            print_status "    Windows: $win_count files"
        fi
        
        if [ -d "libs/linux" ]; then
            linux_count=$(find libs/linux -name "*.so*" -o -name "*.dat" | wc -l)
            print_status "    Linux: $linux_count files"
        fi
        
        if [ -d "libs/mac" ]; then
            mac_count=$(find libs/mac -name "*.dylib" -o -name "*.dat" | wc -l)
            print_status "    Mac: $mac_count files"
        fi
    fi
    
    return 0
}

# Main execution
main() {
    print_status "Setting up SDK files for Go build..."
    
    if setup_sdk_structure; then
        print_success "SDK setup completed successfully!"
        print_status "You can now run the Go build process."
    else
        print_error "SDK setup failed!"
        exit 1
    fi
}

# Run main function
main "$@"