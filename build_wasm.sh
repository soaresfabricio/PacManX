#!/bin/bash

# Build script for PacManX WebAssembly version
# Requires Emscripten SDK to be installed and activated

set -e  # Exit on error

echo "======================================"
echo "PacManX WebAssembly Build Script"
echo "======================================"
echo ""

# Check if emcc is available
if ! command -v emcc &> /dev/null; then
    echo "Error: Emscripten compiler (emcc) not found!"
    echo ""
    echo "Please install Emscripten SDK:"
    echo "  1. git clone https://github.com/emscripten-core/emsdk.git"
    echo "  2. cd emsdk"
    echo "  3. ./emsdk install latest"
    echo "  4. ./emsdk activate latest"
    echo "  5. source ./emsdk_env.sh"
    echo ""
    exit 1
fi

echo "Emscripten version:"
emcc --version
echo ""

# Create build directory
BUILD_DIR="build_wasm"
if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning previous build..."
    rm -rf "$BUILD_DIR"
fi

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Configuring with CMake..."
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release

echo ""
echo "Building WebAssembly..."
emmake make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo ""
echo "======================================"
echo "Build completed successfully!"
echo "======================================"
echo ""
echo "Output files generated in: $BUILD_DIR/"
echo "  - pacmanx.html  (Main HTML file)"
echo "  - pacmanx.js    (JavaScript loader)"
echo "  - pacmanx.wasm  (WebAssembly binary)"
echo "  - pacmanx.data  (Preloaded assets)"
echo ""
echo "To test the game:"
echo "  1. Copy the generated files to a web server"
echo "  2. Or use Python's built-in server:"
echo "     cd $BUILD_DIR && python3 -m http.server 8000"
echo "  3. Open http://localhost:8000/pacmanx.html in your browser"
echo ""
