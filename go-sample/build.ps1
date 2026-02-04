# build.ps1 - Windows PowerShell build script for MetaDefender SDK Go project

param(
    [string]$Action = "build",
    [switch]$Help
)

# Enable strict mode for better error handling
Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

# Project configuration
$PROJECT_NAME = "go-sample"
$GO_FILE = ".\src\main.go"

# Console colors
$Colors = @{
    Red    = "Red"
    Green  = "Green"
    Yellow = "Yellow"
    Blue   = "Blue"
    White  = "White"
}

# Function to print colored output
function Write-Status {
    param([string]$Message)
    Write-Host "[INFO] $Message" -ForegroundColor $Colors.Blue
}

function Write-Success {
    param([string]$Message)
    Write-Host "[SUCCESS] $Message" -ForegroundColor $Colors.Green
}

function Write-Warning {
    param([string]$Message)
    Write-Host "[WARNING] $Message" -ForegroundColor $Colors.Yellow
}

function Write-Error {
    param([string]$Message)
    Write-Host "[ERROR] $Message" -ForegroundColor $Colors.Red
}

# Detect Windows architecture
function Get-WindowsArchitecture {
    $arch = $env:PROCESSOR_ARCHITECTURE
    $wow64Arch = $env:PROCESSOR_ARCHITEW6432
    
    # Check if running under WOW64 (32-bit process on 64-bit system)
    if ($wow64Arch) {
        $arch = $wow64Arch
    }
    
    switch ($arch) {
        "AMD64" { return "amd64" }
        "ARM64" { return "arm64" }
        "x86"   { 
            Write-Error "x86 (32-bit) architecture is not supported. Only x64 and ARM64 are supported."
            exit 1
        }
        default { 
            Write-Warning "Unknown architecture: $arch, defaulting to amd64"
            return "amd64" 
        }
    }
}

# Check if Go is installed
function Test-GoInstallation {
    Write-Status "Checking Go installation..."
    
    try {
        $goVersion = go version
        if ($LASTEXITCODE -ne 0) {
            throw "Go command failed"
        }
        Write-Status "Found Go version: $goVersion"
        return $true
    }
    catch {
        Write-Error "Go is not installed or not in PATH"
        Write-Status "Please install Go from https://golang.org/dl/"
        return $false
    }
}

# Setup SDK file structure from extracted files
function Invoke-SdkSetup {
    Write-Status "Setting up SDK file structure for Go build..."
    
    # Check if extract directory exists
    if (-not (Test-Path "extract" -PathType Container)) {
        Write-Error "Extract directory not found. Please run the SDK downloader first."
        return $false
    }
    
    # Create inc directory and copy headers
    Write-Status "Creating inc directory and copying headers..."
    if (-not (Test-Path "inc" -PathType Container)) {
        New-Item -ItemType Directory -Path "inc" | Out-Null
    }
    
    # Copy headers from extracted Windows SDK (they should be the same across platforms)
    $headerSource = $null
    if (Test-Path "extract\windows\inc" -PathType Container) {
        $headerSource = "extract\windows\inc"
        Write-Status "Using headers from Windows SDK"
    } elseif (Test-Path "extract\linux\inc" -PathType Container) {
        $headerSource = "extract\linux\inc"
        Write-Status "Using headers from Linux SDK"
    } elseif (Test-Path "extract\mac\inc" -PathType Container) {
        $headerSource = "extract\mac\inc"
        Write-Status "Using headers from Mac SDK"
    } else {
        Write-Error "No SDK headers found in extract directory"
        return $false
    }
    
    # Copy all header files
    Get-ChildItem -Path $headerSource -Recurse | ForEach-Object {
        $destinationPath = $_.FullName.Replace($headerSource, "inc")
        $destinationDir = Split-Path $destinationPath -Parent
        
        if (-not (Test-Path $destinationDir -PathType Container)) {
            New-Item -ItemType Directory -Path $destinationDir -Force | Out-Null
        }
        
        Copy-Item $_.FullName $destinationPath -Force
    }
    
    # Create libs directory structure for runtime DLLs
    Write-Status "Creating libs directory and copying runtime libraries..."
    if (-not (Test-Path "libs" -PathType Container)) {
        New-Item -ItemType Directory -Path "libs" | Out-Null
    }
    
    # Copy Windows libraries
    if (Test-Path "client\windows" -PathType Container) {
        if (-not (Test-Path "libs\win" -PathType Container)) {
            New-Item -ItemType Directory -Path "libs\win" | Out-Null
        }
        Write-Status "Setting up Windows runtime libraries..."
        
        # Copy libraries and rename them for Go runtime
        if (Test-Path "client\windows\x64" -PathType Container) {
            Copy-Item "client\windows\x64\libwaapi.dll" "libs\win\x64_libwaapi.dll" -Force
            Get-ChildItem "client\windows\x64\*.dll" | Where-Object { $_.Name -ne "libwaapi.dll" } | ForEach-Object {
                Copy-Item $_.FullName "libs\win\$($_.Name)" -Force
            }
            Get-ChildItem "client\windows\x64\*.exe" | ForEach-Object {
                Copy-Item $_.FullName "libs\win\$($_.Name)" -Force
            }
        }
        
        if (Test-Path "client\windows\arm64" -PathType Container) {
            Copy-Item "client\windows\arm64\libwaapi.dll" "libs\win\arm64_libwaapi.dll" -Force
            Get-ChildItem "client\windows\arm64\*.dll" | Where-Object { $_.Name -ne "libwaapi.dll" } | ForEach-Object {
                Copy-Item $_.FullName "libs\win\$($_.Name)" -Force
            }
            Get-ChildItem "client\windows\arm64\*.exe" | ForEach-Object {
                Copy-Item $_.FullName "libs\win\$($_.Name)" -Force
            }
        }
        
        Write-Status "Windows runtime libraries set up"
    }
    
    Write-Status "SDK file structure setup complete"
    return $true
}

# Download SDK files using the Python SDK downloader
function Invoke-SdkDownload {
    Write-Status "Checking if SDK files need to be downloaded..."
    
    # Check if inc and libs directories exist
    if (-not (Test-Path "inc" -PathType Container) -or 
        -not (Test-Path "libs" -PathType Container) -or 
        -not (Test-Path "inc\wa_api.h")) {
        
        Write-Status "SDK files not found. Downloading using Python SDK downloader..."
        
        # Check if Python SDK downloader exists
        $pythonSdkDownloaderDir = "..\OPSWAT-SDK-Downloader\PythonSDKDownloader"
        $pythonSdkDownloaderMain = "$pythonSdkDownloaderDir\main.py"
        
        if (-not (Test-Path $pythonSdkDownloaderDir -PathType Container)) {
            Write-Error "Python SDK downloader not found at $pythonSdkDownloaderDir"
            Write-Status "Please ensure OPSWAT-SDK-Downloader is available in the root directory"
            return $false
        }
        
        if (-not (Test-Path $pythonSdkDownloaderMain)) {
            Write-Error "Python SDK downloader main.py not found at $pythonSdkDownloaderMain"
            return $false
        }
        
        # Check for Python
        $pythonCmd = $null
        $pythonCommands = @("py", "python3", "python")
        
        foreach ($cmd in $pythonCommands) {
            try {
                & $cmd --version | Out-Null
                if ($LASTEXITCODE -eq 0) {
                    $pythonCmd = $cmd
                    break
                }
            }
            catch {
                # Command not found, continue to next
            }
        }
        
        if (-not $pythonCmd) {
            Write-Error "Python is not installed or not in PATH"
            Write-Status "Please install Python from https://python.org/"
            return $false
        }
        
        # Run the Python SDK downloader
        Write-Status "Running Python SDK downloader with $pythonCmd..."
        $currentDir = Get-Location
        Set-Location $pythonSdkDownloaderDir
        $parentDir = (Get-Location).Parent.Parent.FullName
        
        try {
            & $pythonCmd main.py $parentDir "go-sample"
            if ($LASTEXITCODE -ne 0) {
                throw "Python SDK downloader failed with exit code $LASTEXITCODE"
            }
            Write-Success "SDK files downloaded successfully"
        }
        catch {
            Write-Error "Python SDK download failed: $($_.Exception.Message)"
            return $false
        }
        finally {
            Set-Location $currentDir
        }
        
        # Setup SDK file structure for Go build
        Write-Status "Setting up SDK file structure for Go build..."
        try {
            if (-not (Invoke-SdkSetup)) {
                throw "SDK file structure setup failed"
            }
        }
        catch {
            Write-Error "SDK file structure setup failed: $($_.Exception.Message)"
            return $false
        }
    }
    else {
        Write-Status "SDK files already present"
    }
    
    return $true
}

# Check for required files and directories
function Test-RequiredFiles {
    param([string]$Architecture)
    
    Write-Status "Checking for required files..."
    
    # Check Go source file
    if (-not (Test-Path $GO_FILE)) {
        Write-Error "Go source file '$GO_FILE' not found"
        return $false
    }
    
    # Download SDK files if needed
    if (-not (Invoke-SdkDownload)) {
        return $false
    }
    
    # Check include directory
    if (-not (Test-Path "inc" -PathType Container)) {
        Write-Error "Include directory 'inc' not found even after SDK download"
        return $false
    }
    
    # Check MDES SDK header
    if (-not (Test-Path "inc\wa_api.h")) {
        Write-Error "MDES SDK header 'inc\wa_api.h' not found even after SDK download"
        return $false
    }
    
    # Check libraries directory
    $libsDir = "libs"
    if (-not (Test-Path $libsDir -PathType Container)) {
        Write-Error "Libraries directory '$libsDir' not found even after SDK download"
        return $false
    }
    
    # Check Windows-specific library directory
    $windowsLibsDir = "$libsDir\win"
    if (-not (Test-Path $windowsLibsDir -PathType Container)) {
        Write-Error "Windows libraries directory '$windowsLibsDir' not found"
        return $false
    }
    
    # Check for .lib files in extract directory structure
    $extractLibsDir = "extract\windows\lib"
    $libArchDir = switch ($Architecture) {
        "amd64" { "x64" }
        "arm64" { "arm64" }
        default { "x64" }
    }
    
    $libPath = "$extractLibsDir\$libArchDir\release\libwaapi.lib"
    if (-not (Test-Path $libPath)) {
        Write-Error "MDES SDK static library '$libPath' not found"
        Write-Status "Available lib directories in ${extractLibsDir}:"
        if (Test-Path $extractLibsDir) {
            Get-ChildItem $extractLibsDir | Select-Object Name | Format-Table
        }
        return $false
    }
    
    Write-Success "Found MDES SDK static library: $libPath"
    return $true
}

# Set up CGO environment variables
function Set-CgoEnvironment {
    param([string]$Architecture)
    
    Write-Status "Setting up CGO environment for Windows/$Architecture..."
    
    # Set Go environment variables
    $env:CGO_ENABLED = "1"
    $env:GOOS = "windows"
    $env:GOARCH = $Architecture
    
    # Set CGO flags for Windows based on architecture to use .lib files
    $currentDir = (Get-Location).Path
    $libArchDir = switch ($Architecture) {
        "amd64" { "x64" }
        "arm64" { "arm64" }
        default { "x64" }
    }
    $libDir = "$currentDir\extract\windows\lib\$libArchDir\release"
    
    # Use forward slashes and escape spaces properly for CGO
    $libDirUnix = $libDir -replace '\\', '/' -replace ' ', '\ '
    $incDirUnix = "$currentDir\inc" -replace '\\', '/' -replace ' ', '\ '
    
    $env:CGO_LDFLAGS = "-L$libDirUnix -lwaapi"
    $env:CGO_CFLAGS = "-I$incDirUnix"
    
    # For ARM64, we need to specify the cross-compiler
    if ($Architecture -eq "arm64") {
        # Check if MSYS2 CLANG ARM64 toolchain is available
        $clangPath = "C:\msys64\clangarm64\bin"
        if (Test-Path $clangPath) {
            Write-Status "Using MSYS2 CLANG ARM64 toolchain"
            $env:CC = "$clangPath\aarch64-w64-mingw32-clang.exe"
            $env:CXX = "$clangPath\aarch64-w64-mingw32-clang++.exe"
            $env:PATH = "$clangPath;$env:PATH"
        } else {
            Write-Warning "MSYS2 CLANG ARM64 toolchain not found at $clangPath"
            Write-Status "Make sure you have installed: pacman -S mingw-w64-clang-aarch64-toolchain"
        }
    }
    
    Write-Status "CGO environment configured:"
    Write-Status "  CGO_ENABLED: $env:CGO_ENABLED"
    Write-Status "  GOOS: $env:GOOS"
    Write-Status "  GOARCH: $env:GOARCH"
    Write-Status "  CGO_LDFLAGS: $env:CGO_LDFLAGS"
    Write-Status "  CGO_CFLAGS: $env:CGO_CFLAGS"
    if ($env:CC) { Write-Status "  CC: $env:CC" }
    if ($env:CXX) { Write-Status "  CXX: $env:CXX" }
}

# Build the project
function Invoke-ProjectBuild {
    param([string]$Architecture)
    
    Write-Status "Building $PROJECT_NAME for Windows/$Architecture..."
    
    # Create build directory
    $buildDir = "build"
    if (-not (Test-Path $buildDir)) {
        New-Item -ItemType Directory -Path $buildDir | Out-Null
    }
    
    # Set output binary name
    $outputName = "$PROJECT_NAME.exe"
    $outputPath = "$buildDir\$outputName"
    
    # Build command
    $buildCmd = "go build -o `"$outputPath`" `"$GO_FILE`""
    
    Write-Status "Running: $buildCmd"
    
    try {
        # Execute the build command
        Invoke-Expression $buildCmd
        
        if ($LASTEXITCODE -ne 0) {
            throw "Build command failed with exit code $LASTEXITCODE"
        }
        
        Write-Success "Build completed successfully!"
        Write-Success "Binary created: $outputPath"
        
        # Show file info
        if (Test-Path $outputPath) {
            $fileInfo = Get-Item $outputPath
            $sizeKB = [math]::Round($fileInfo.Length / 1KB, 2)
            Write-Status "Binary size: $sizeKB KB"
            Write-Status "Binary created: $($fileInfo.CreationTime)"
        }
        
        # Copy Windows runtime DLLs for the specific architecture to build directory
        Write-Status "Copying Windows runtime DLLs for $Architecture to $buildDir..."
        $windowsLibsDir = "libs\win"
        
        # Define architecture-specific library prefixes for runtime DLLs
        $archPrefix = switch ($Architecture) {
            "amd64" { "x64_" }
            "arm64" { "arm64_" }
            default { "x64_" }
        }
        
        # Copy only the runtime DLLs for the current architecture
        $archLibraries = @(Get-ChildItem "$windowsLibsDir\$archPrefix*.dll")
        if ($archLibraries.Count -eq 0) {
            Write-Warning "No runtime DLLs found for architecture $Architecture with prefix '$archPrefix'"
        } else {

            # Remove existing DLLs from build directory
            Remove-Item -Path (Join-Path $buildDir '*.dll') -Force -ErrorAction SilentlyContinue
            
            foreach ($lib in $archLibraries) {
                $copiedPath = Join-Path $buildDir $lib.Name
                Copy-Item $lib.FullName $copiedPath -Force

                $newName = $lib.Name -replace $archPrefix, ''
    
                if ($newName -ne $lib.Name) {
                    Rename-Item -Path $copiedPath -NewName $newName
                    Write-Status "Copied and renamed runtime DLL: $newName"
                } else {
                    Write-Status "Copied runtime DLL (no rename needed): $($lib.Name)"
                }
            }

            # Copy additional required runtime DLLs from the correct client directory based on architecture
            $clientArchDir = switch ($Architecture) {
                "amd64" { "client\windows\x64" }
                "arm64" { "client\windows\arm64" }
                default { "client\windows\x64" }
            }
            
            $additionalDlls = @('libwautils.dll', 'libwaheap.dll', 'libwalocal.dll', 'libwadeviceinfo.dll', 'libwaresource.dll', 'libwaaddon.dll', 'libwavmodapi.dll')
            foreach ($dll in $additionalDlls) {
                $sourcePath = Join-Path $clientArchDir $dll
                if (Test-Path $sourcePath) {
                    Copy-Item -Path $sourcePath -Destination $buildDir -Force
                    Write-Status "Copied additional runtime DLL: $dll from $clientArchDir"
                } else {
                    Write-Warning "Additional runtime DLL not found: $dll at $sourcePath"
                }
            }

            # Copy architecture-specific .exe files from the source directory
            $archSpecificExecutables = switch ($Architecture) {
                "amd64" { @('wa_3rd_party_host_64.exe') }
                "arm64" { @('wa_3rd_party_host_ARM64.exe') }
                default { @('wa_3rd_party_host_64.exe') }
            }
            
            foreach ($exeName in $archSpecificExecutables) {
                $exePath = Join-Path $windowsLibsDir $exeName
                if (Test-Path $exePath) {
                    Copy-Item -Path $exePath -Destination $buildDir -Force
                    Write-Status "Copied architecture-specific executable: $exeName"
                } else {
                    Write-Warning "Architecture-specific executable not found: $exeName at $exePath"
                }
            }

            # Copy licensed component DLLs from extract directory based on architecture
            $extractArchDir = switch ($Architecture) {
                "amd64" { "x64" }
                "arm64" { "arm64" }
                default { "x64" }
            }
            
            $licensedComponents = @(
                @{Name = "libwainfection.dll"; Path = "extract\windows\bin\infection\$extractArchDir\release"},
                @{Name = "libwaremoval.dll"; Path = "extract\windows\bin\removal\$extractArchDir\release"},
                @{Name = "libwadriver.dll"; Path = "extract\windows\bin\wadriver\$extractArchDir\release"},
                @{Name = "libwacollector.dll"; Path = "extract\windows\bin\diagnostics\$extractArchDir\release"},
                @{Name = "libwaadbrowser.dll"; Path = "extract\windows\bin\advancedbrowser\$extractArchDir\release"},
                @{Name = "libwanetscan.dll"; Path = "extract\windows\bin\netscan\$extractArchDir\release"},
                @{Name = "libwadlp.dll"; Path = "extract\windows\bin\dlp\$extractArchDir\release"}
            )
            
            foreach ($component in $licensedComponents) {
                $sourcePath = Join-Path $component.Path $component.Name
                if (Test-Path $sourcePath) {
                    Copy-Item -Path $sourcePath -Destination $buildDir -Force
                    Write-Status "Copied licensed component DLL: $($component.Name)"
                } else {
                    Write-Warning "Licensed component DLL not found: $($component.Name) at $sourcePath"
                }
            }

            Write-Success "Copied $($archLibraries.Count) architecture-specific runtime DLLs to $buildDir."


            # Copy license files from license directory to build directory
            Write-Status "Copying license files to build directory..."
            $sourceLicenseFile = "license\license.cfg"
            $sourcePassKeyFile = "license\pass_key.txt"
            
            if (Test-Path $sourceLicenseFile) {
                Copy-Item -Path $sourceLicenseFile -Destination $buildDir -Force
                Write-Status "Copied license.cfg to build directory"
            } else {
                Write-Warning "License file not found at: $sourceLicenseFile"
            }
            
            if (Test-Path $sourcePassKeyFile) {
                Copy-Item -Path $sourcePassKeyFile -Destination $buildDir -Force
                Write-Status "Copied pass_key.txt to build directory"
            } else {
                Write-Warning "Pass key file not found at: $sourcePassKeyFile"
            }

            # Check if required license files are present in build directory
            $licenseFile = Join-Path $buildDir 'license.cfg'
            $passKeyFile = Join-Path $buildDir 'pass_key.txt'

            if (-Not (Test-Path $licenseFile) -or -Not (Test-Path $passKeyFile)) {
                Write-Host "`nERROR: Missing required files!" -ForegroundColor Red -BackgroundColor Black
                Write-Host "Make sure both 'license.cfg' and 'pass_key.txt' are present in the license directory:" -ForegroundColor Red
                Write-Host "  license\" -ForegroundColor Red
                Write-Status "The build script will copy these files automatically to the build directory."
                return $false
            }

        }
        
        return $true
    }
    catch {
        Write-Error "Build failed: $($_.Exception.Message)"
        return $false
    }
}

# Clean previous builds
function Clear-BuildDirectory {
    Write-Status "Cleaning previous builds..."
    
    if (Test-Path "build") {
        Remove-Item "build" -Recurse -Force
        Write-Success "Build directory cleaned"
    } else {
        Write-Status "No build directory to clean"
    }
}

# Show help information
function Show-Help {
    Write-Host ""
    Write-Host "MetaDefender SDK Go Build Script for Windows" -ForegroundColor $Colors.Blue
    Write-Host "=============================================" -ForegroundColor $Colors.Blue
    Write-Host ""
    Write-Host "Usage: .\build.ps1 [Action] [Options]" -ForegroundColor $Colors.White
    Write-Host ""
    Write-Host "Actions:" -ForegroundColor $Colors.Yellow
    Write-Host "  build    Build the project (default)" -ForegroundColor $Colors.White
    Write-Host "  clean    Clean previous builds" -ForegroundColor $Colors.White
    Write-Host ""
    Write-Host "Options:" -ForegroundColor $Colors.Yellow
    Write-Host "  -Help    Show this help message" -ForegroundColor $Colors.White
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor $Colors.Yellow
    Write-Host "  .\build.ps1              # Build the project" -ForegroundColor $Colors.White
    Write-Host "  .\build.ps1 build        # Build the project" -ForegroundColor $Colors.White
    Write-Host "  .\build.ps1 clean        # Clean build directory" -ForegroundColor $Colors.White
    Write-Host "  .\build.ps1 -Help        # Show help" -ForegroundColor $Colors.White
    Write-Host ""
    Write-Host "This script will:" -ForegroundColor $Colors.Green
    Write-Host "  1. Detect your Windows architecture (x64/ARM64 only)" -ForegroundColor $Colors.White
    Write-Host "  2. Check for required Go installation and MDES SDK files" -ForegroundColor $Colors.White
    Write-Host "  3. Set up CGO environment variables" -ForegroundColor $Colors.White
    Write-Host "  4. Build the MetaDefender SDK Go project" -ForegroundColor $Colors.White
    Write-Host "  5. Copy required DLLs to build directory" -ForegroundColor $Colors.White
    Write-Host ""
}

# Main execution function
function Invoke-Main {
    param([string]$Action)
    
    Write-Status "Starting build process..."
    
    # Detect architecture
    $architecture = Get-WindowsArchitecture
    Write-Status "Detected Windows architecture: $architecture"
    
    # Handle different actions
    switch ($Action.ToLower()) {
        "clean" {
            Clear-BuildDirectory
            Write-Success "Clean completed"
            return
        }
        "build" {
            # Continue with build process
        }
        default {
            Write-Error "Unknown action: $Action"
            Show-Help
            exit 1
        }
    }
    
    # Check Go installation
    if (-not (Test-GoInstallation)) {
        exit 1
    }
    
    # Check required files
    if (-not (Test-RequiredFiles -Architecture $architecture)) {
        exit 1
    }
    
    # Set up CGO environment
    Set-CgoEnvironment -Architecture $architecture
    
    # Build the project
    if (-not (Invoke-ProjectBuild -Architecture $architecture)) {
        exit 1
    }
    
    Write-Success "Build process completed successfully!"
    Write-Status "To run the program:"
    Write-Status "  cd build"
    Write-Status "  .\$PROJECT_NAME.exe"
    Write-Host ""
    Write-Status "Required DLLs have been copied to the build directory."

    
}

# Script entry point
try {
    if ($Help) {
        Show-Help
        exit 0
    }
    
    Invoke-Main -Action $Action
}
catch {
    Write-Error "Script execution failed: $($_.Exception.Message)"
    Write-Status "Use -Help for usage information"
    exit 1
}