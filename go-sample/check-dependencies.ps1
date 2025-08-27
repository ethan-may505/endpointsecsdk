# Script to check DLL dependencies
Write-Host "Checking DLL dependencies for go-sample.exe..." -ForegroundColor Yellow

if (Test-Path "build\go-sample.exe") {
    Write-Host "Found go-sample.exe, listing dependencies..." -ForegroundColor Green
    
    # List all DLL files in build directory
    Write-Host "`nDLLs currently in build directory:" -ForegroundColor Cyan
    Get-ChildItem "build\*.dll" | ForEach-Object {
        Write-Host "  $($_.Name)" -ForegroundColor White
    }
    
    # Check for common missing dependencies
    Write-Host "`nChecking for common Visual C++ runtime DLLs on system:" -ForegroundColor Cyan
    $commonDlls = @(
        "msvcp140.dll", "vcruntime140.dll", "vcruntime140_1.dll",
        "msvcp120.dll", "msvcr120.dll",
        "msvcp110.dll", "msvcr110.dll"
    )
    
    foreach ($dll in $commonDlls) {
        $found = Get-Command $dll -ErrorAction SilentlyContinue
        if ($found) {
            Write-Host "  Found: $dll" -ForegroundColor Green
        } else {
            Write-Host "  Missing: $dll" -ForegroundColor Red
        }
    }
} else {
    Write-Host "go-sample.exe not found in build directory. Run build.ps1 first." -ForegroundColor Red
}

Write-Host "`nIf you are still getting 0xc0000135 errors, try:" -ForegroundColor Yellow
Write-Host "1. Install Microsoft Visual C++ Redistributable (latest x64 version)" -ForegroundColor White  
Write-Host "2. Run sfc /scannow as administrator to check system files" -ForegroundColor White
Write-Host "3. Use Dependency Walker or Dependencies.exe to analyze missing DLLs" -ForegroundColor White