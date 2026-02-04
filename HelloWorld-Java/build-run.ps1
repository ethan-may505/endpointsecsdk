# OESIS Java Simple Demo - Build and Run Script
$ErrorActionPreference = "Stop"

# Get script directory
$SCRIPT_DIR = $PSScriptRoot
Set-Location $SCRIPT_DIR

Write-Host "=================================================" -ForegroundColor Cyan
Write-Host "   OESIS Java Simple Demo - Build & Run" -ForegroundColor Cyan
Write-Host "=================================================" -ForegroundColor Cyan
Write-Host ""

# Create directories
$LIB_DIR = Join-Path $SCRIPT_DIR "lib"
$BUILD_DIR = Join-Path $SCRIPT_DIR "build"
$DLL_DIR = Join-Path $SCRIPT_DIR "dll"
$SOURCE_DIR = Join-Path $SCRIPT_DIR "sample-code-java"

if (-not (Test-Path $LIB_DIR)) {
    New-Item -ItemType Directory -Path $LIB_DIR | Out-Null
}

if (-not (Test-Path $BUILD_DIR)) {
    New-Item -ItemType Directory -Path $BUILD_DIR | Out-Null
}

# Download dependencies
Write-Host "[1/4] Checking dependencies..." -ForegroundColor Yellow

$JNA_JAR = Join-Path $LIB_DIR "jna-5.12.1.jar"
$JSON_JAR = Join-Path $LIB_DIR "json-20230227.jar"

if (-not (Test-Path $JNA_JAR)) {
    Write-Host "  Downloading jna-5.12.1.jar..." -ForegroundColor Gray
    $JNA_URL = "https://repo1.maven.org/maven2/net/java/dev/jna/jna/5.12.1/jna-5.12.1.jar"
    Invoke-WebRequest -Uri $JNA_URL -OutFile $JNA_JAR
    Write-Host "  Downloaded jna-5.12.1.jar" -ForegroundColor Green
} else {
    Write-Host "  jna-5.12.1.jar exists" -ForegroundColor Green
}

if (-not (Test-Path $JSON_JAR)) {
    Write-Host "  Downloading json-20230227.jar..." -ForegroundColor Gray
    $JSON_URL = "https://repo1.maven.org/maven2/org/json/json/20230227/json-20230227.jar"
    Invoke-WebRequest -Uri $JSON_URL -OutFile $JSON_JAR
    Write-Host "  Downloaded json-20230227.jar" -ForegroundColor Green
} else {
    Write-Host "  json-20230227.jar exists" -ForegroundColor Green
}

Write-Host ""

# Compile
Write-Host "[2/4] Compiling SimpleMain.java..." -ForegroundColor Yellow

$CLASSPATH = "$JNA_JAR;$JSON_JAR"
$SOURCE_FILE = Join-Path $SOURCE_DIR "SimpleMain.java"

javac -cp $CLASSPATH -d $BUILD_DIR $SOURCE_FILE

if ($LASTEXITCODE -ne 0) {
    Write-Host "  Compilation failed!" -ForegroundColor Red
    exit 1
}

Write-Host "  Compilation successful" -ForegroundColor Green
Write-Host ""

# Run
Write-Host "[3/4] Running SimpleMain..." -ForegroundColor Yellow
Write-Host ""

$RUN_CLASSPATH = "$BUILD_DIR;$JNA_JAR;$JSON_JAR"
$env:PATH = "$DLL_DIR;$env:PATH"

& java -cp $RUN_CLASSPATH "-Djna.library.path=$DLL_DIR" sample_code_java.SimpleMain

Write-Host ""
Write-Host "[4/4] Done!" -ForegroundColor Yellow
Write-Host ""
Write-Host "=================================================" -ForegroundColor Cyan
