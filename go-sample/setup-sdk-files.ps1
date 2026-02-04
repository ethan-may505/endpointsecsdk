# Setup SDK files PowerShell script - creates the expected inc and libs structure from downloaded SDK

param(
    [switch]$Help
)

# Console colors
$Colors = @{
    Red    = "Red"
    Green  = "Green"
    Yellow = "Yellow"
    Blue   = "Blue"
    White  = "White"
}

# Function to print colored output
function Write-Setup {
    param([string]$Message)
    Write-Host "[SETUP] $Message" -ForegroundColor $Colors.Blue
}

function Write-Success {
    param([string]$Message)
    Write-Host "[SUCCESS] $Message" -ForegroundColor $Colors.Green
}

function Write-Error {
    param([string]$Message)
    Write-Host "[ERROR] $Message" -ForegroundColor $Colors.Red
}

function Set-SdkStructure {
    Write-Setup "Setting up SDK file structure for Go build..."
    
    # Check if extract directory exists
    if (-not (Test-Path "extract" -PathType Container)) {
        Write-Error "Extract directory not found. Please run the SDK downloader first."
        return $false
    }
    
    # Create inc directory and copy headers
    Write-Setup "Creating inc directory and copying headers..."
    if (-not (Test-Path "inc" -PathType Container)) {
        New-Item -ItemType Directory -Path "inc" | Out-Null
    }
    
    # Copy headers from extracted Windows SDK (they should be the same across platforms)
    $headerSource = $null
    if (Test-Path "extract\windows\inc" -PathType Container) {
        $headerSource = "extract\windows\inc"
        Write-Setup "Using headers from Windows SDK"
    } elseif (Test-Path "extract\linux\inc" -PathType Container) {
        $headerSource = "extract\linux\inc"
        Write-Setup "Using headers from Linux SDK"
    } elseif (Test-Path "extract\mac\inc" -PathType Container) {
        $headerSource = "extract\mac\inc"
        Write-Setup "Using headers from Mac SDK"
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
    
    # Create libs directory structure
    Write-Setup "Creating libs directory and copying libraries..."
    if (-not (Test-Path "libs" -PathType Container)) {
        New-Item -ItemType Directory -Path "libs" | Out-Null
    }
    
    # Copy Windows libraries
    if (Test-Path "client\windows" -PathType Container) {
        if (-not (Test-Path "libs\win" -PathType Container)) {
            New-Item -ItemType Directory -Path "libs\win" | Out-Null
        }
        Write-Setup "Setting up Windows libraries..."
        
        # Copy libraries and rename them for Go build
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
        
        Write-Setup "Windows libraries set up"
    }
    
    # Copy Linux libraries
    if (Test-Path "client\linux" -PathType Container) {
        if (-not (Test-Path "libs\linux" -PathType Container)) {
            New-Item -ItemType Directory -Path "libs\linux" | Out-Null
        }
        Write-Setup "Setting up Linux libraries..."
        
        if (Test-Path "client\linux\x64" -PathType Container) {
            Get-ChildItem "client\linux\x64\libwaapi.so*" | ForEach-Object {
                Copy-Item $_.FullName "libs\linux\$($_.Name)" -Force
            }
            Get-ChildItem "client\linux\x64\*.so*" | ForEach-Object {
                Copy-Item $_.FullName "libs\linux\$($_.Name)" -Force
            }
            Get-ChildItem "client\linux\x64\*.dat" | ForEach-Object {
                Copy-Item $_.FullName "libs\linux\$($_.Name)" -Force
            }
        }
        
        
        if (Test-Path "client\linux\arm64" -PathType Container) {
            Get-ChildItem "client\linux\arm64\libwaapi.so*" | ForEach-Object {
                Copy-Item $_.FullName "libs\linux\arm64_$($_.Name)" -Force
            }
        }
        
        Write-Setup "Linux libraries set up"
    }
    
    # Copy Mac libraries
    if (Test-Path "client\mac" -PathType Container) {
        if (-not (Test-Path "libs\mac" -PathType Container)) {
            New-Item -ItemType Directory -Path "libs\mac" | Out-Null
        }
        Write-Setup "Setting up Mac libraries..."
        
        Get-ChildItem "client\mac\*.dylib" | ForEach-Object {
            Copy-Item $_.FullName "libs\mac\$($_.Name)" -Force
        }
        Get-ChildItem "client\mac\*.dat" | ForEach-Object {
            Copy-Item $_.FullName "libs\mac\$($_.Name)" -Force
        }
        
        Write-Setup "Mac libraries set up"
    }
    
    Write-Success "SDK file structure setup complete"
    
    # Show summary
    Write-Setup "Summary:"
    if (Test-Path "inc" -PathType Container) {
        $headerCount = (Get-ChildItem "inc" -Recurse -Filter "*.h").Count
        Write-Setup "  Headers: $headerCount files in inc/"
    }
    
    if (Test-Path "libs" -PathType Container) {
        $libCount = (Get-ChildItem "libs" -Recurse -File).Count
        Write-Setup "  Libraries: $libCount files in libs/"
        
        if (Test-Path "libs\win" -PathType Container) {
            $winCount = (Get-ChildItem "libs\win" -Filter "*.dll").Count + (Get-ChildItem "libs\win" -Filter "*.exe").Count
            Write-Setup "    Windows: $winCount files"
        }
        
        if (Test-Path "libs\linux" -PathType Container) {
            $linuxCount = (Get-ChildItem "libs\linux" -Filter "*.so*").Count + (Get-ChildItem "libs\linux" -Filter "*.dat").Count
            Write-Setup "    Linux: $linuxCount files"
        }
        
        if (Test-Path "libs\mac" -PathType Container) {
            $macCount = (Get-ChildItem "libs\mac" -Filter "*.dylib").Count + (Get-ChildItem "libs\mac" -Filter "*.dat").Count
            Write-Setup "    Mac: $macCount files"
        }
    }
    
    return $true
}

function Show-Help {
    Write-Host ""
    Write-Host "SDK Setup Script for Go Build" -ForegroundColor $Colors.Blue
    Write-Host "==============================" -ForegroundColor $Colors.Blue
    Write-Host ""
    Write-Host "This script sets up the SDK file structure required for Go build from downloaded SDK files." -ForegroundColor $Colors.White
    Write-Host ""
    Write-Host "Usage: .\setup-sdk-files.ps1 [Options]" -ForegroundColor $Colors.White
    Write-Host ""
    Write-Host "Options:" -ForegroundColor $Colors.Yellow
    Write-Host "  -Help    Show this help message" -ForegroundColor $Colors.White
    Write-Host ""
}

# Main execution
try {
    if ($Help) {
        Show-Help
        exit 0
    }
    
    Write-Setup "Setting up SDK files for Go build..."
    
    if (Set-SdkStructure) {
        Write-Success "SDK setup completed successfully!"
        Write-Setup "You can now run the Go build process."
        exit 0
    } else {
        Write-Error "SDK setup failed!"
        exit 1
    }
}
catch {
    Write-Error "Script execution failed: $($_.Exception.Message)"
    exit 1
}