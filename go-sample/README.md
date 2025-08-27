# OPSWAT SDK Go Sample

This sample demonstrates how to use the OPSWAT MetaDefender Endpoint Security SDK with Go.

**Supported Architectures**: x64 (AMD64) and ARM64 only. 32-bit architectures (x86/win32/ARMv7) are not supported.

## Prerequisites

### For All Platforms
1. **Install Go**
   - Navigate to https://go.dev/doc/install
   - Install the correct version of Go for your architecture (x64 or ARM64 only)

2. **Install Python** (for SDK downloader)
   - Navigate to https://python.org/downloads/
   - Install Python 3.x for your platform
   - The build scripts will automatically use the Python SDK downloader (no manual build required!)

### For Windows
1. **Install GCC**
   - Navigate to https://github.com/niXman/mingw-builds-binaries/releases/tag/15.1.0-rt_v12-rev0
   - Download the correct version:
     - For x64: `x86_64-15.1.0-release-posix-seh-ucrt-rt_v12-rev0.7z`
     - For ARM64: Use MSYS2 CLANG ARM64 toolchain (`pacman -S mingw-w64-clang-aarch64-toolchain`)
   - Extract files to a system path, e.g., `c:\gcc`
   - Add the GCC bin directory to your PATH environment variable: `C:\gcc\mingw64\bin`

### For Linux/Mac
1. **Install build tools**
   - Ubuntu/Debian: `sudo apt-get install build-essential`
   - CentOS/RHEL: `sudo yum groupinstall "Development Tools"`
   - Mac: Install Xcode command line tools: `xcode-select --install`

## SDK Files Auto-Download

The build scripts will automatically download and set up the required SDK files (headers and libraries) using the Python SDK downloader. You no longer need to manually copy `inc` and `libs` directories or build the C# SDK downloader - everything is handled automatically when you run the build script.

**Important**: The build script looks for the OPSWAT-SDK-Downloader in the parent directory (`../OPSWAT-SDK-Downloader/PythonSDKDownloader/`). Ensure this directory structure is maintained.

### What happens during build:
1. Checks if SDK files (`inc/` and `libs/`) are already present
2. If not, automatically runs the Python SDK downloader
3. Sets up the proper file structure for Go builds
4. Proceeds with the Go compilation

## Building

### Windows (PowerShell)
```powershell
# Navigate to the go-sample directory
cd go-sample

# Run the build script
.\build.ps1

# Or clean previous builds
.\build.ps1 clean
```

### Linux/Mac (Bash)
```bash
# Navigate to the go-sample directory
cd go-sample

# Make the build script executable (first time only)
chmod +x build.sh

# Run the build script
./build.sh

# Or clean previous builds
./build.sh clean
```

### Cross-Platform (Makefile)
```bash
# Navigate to the go-sample directory
cd go-sample

# Build the project
make

# Or use specific targets
make clean      # Clean build artifacts
make build      # Build the project
make run        # Build and run
make dev        # Clean, build, and run
make help       # Show available targets
```

## License Files

Before running the sample, copy your license files to the build directory:
- `license.cfg`
- `pass_key.txt`

These files should be placed in `go-sample/build/` after building.

## Running

After building, navigate to the build directory and run the executable:

### Windows
```cmd
cd build
go-sample.exe
```

### Linux/Mac
```bash
cd build
./go-sample
```

## File Structure

- `src/main.go` - Main Go source code
- `build.sh` - Linux/Mac build script
- `build.ps1` - Windows PowerShell build script
- `build/` - Output directory (created during build)
- `inc/` - SDK headers (downloaded automatically)
- `libs/` - SDK libraries (downloaded automatically)

## Notes

- The `inc/` and `libs/` directories are automatically downloaded and should not be committed to version control
- The build scripts handle cross-platform compilation and library linking
- Sample code demonstrates product detection functionality using the OPSWAT SDK