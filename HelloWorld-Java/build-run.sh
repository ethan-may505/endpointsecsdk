#!/bin/bash
# OESIS Java Simple Demo - Build and Run Script for Linux
set -e

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "================================================="
echo "   OESIS Java Simple Demo - Build & Run"
echo "================================================="
echo ""

# Create directories
LIB_DIR="$SCRIPT_DIR/lib"
BUILD_DIR="$SCRIPT_DIR/build"
SO_DIR="$SCRIPT_DIR/so"
SOURCE_DIR="$SCRIPT_DIR/sample-code-java"

mkdir -p "$LIB_DIR"
mkdir -p "$BUILD_DIR"

# Download dependencies
echo "[1/4] Checking dependencies..."

JNA_JAR="$LIB_DIR/jna-5.12.1.jar"
JSON_JAR="$LIB_DIR/json-20230227.jar"

if [ ! -f "$JNA_JAR" ]; then
    echo "  Downloading jna-5.12.1.jar..."
    JNA_URL="https://repo1.maven.org/maven2/net/java/dev/jna/jna/5.12.1/jna-5.12.1.jar"
    curl -L -o "$JNA_JAR" "$JNA_URL" || wget -O "$JNA_JAR" "$JNA_URL"
    echo "  Downloaded jna-5.12.1.jar"
else
    echo "  jna-5.12.1.jar exists"
fi

if [ ! -f "$JSON_JAR" ]; then
    echo "  Downloading json-20230227.jar..."
    JSON_URL="https://repo1.maven.org/maven2/org/json/json/20230227/json-20230227.jar"
    curl -L -o "$JSON_JAR" "$JSON_URL" || wget -O "$JSON_JAR" "$JSON_URL"
    echo "  Downloaded json-20230227.jar"
else
    echo "  json-20230227.jar exists"
fi

echo ""

# Compile
echo "[2/4] Compiling SimpleMain.java..."

CLASSPATH="$JNA_JAR:$JSON_JAR"
SOURCE_FILE="$SOURCE_DIR/SimpleMain.java"

javac -cp "$CLASSPATH" -d "$BUILD_DIR" "$SOURCE_FILE"

if [ $? -ne 0 ]; then
    echo "  Compilation failed!"
    exit 1
fi

echo "  Compilation successful"
echo ""

# Run
echo "[3/4] Running SimpleMain..."
echo ""

RUN_CLASSPATH="$BUILD_DIR:$JNA_JAR:$JSON_JAR"
export LD_LIBRARY_PATH="$SO_DIR:$LD_LIBRARY_PATH"

java -cp "$RUN_CLASSPATH" -Djna.library.path="$SO_DIR" sample_code_java.SimpleMain

echo ""
echo "[4/4] Done!"
echo ""
echo "================================================="
