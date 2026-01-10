# PacManX WebAssembly Version

This document describes how to build and run the WebAssembly version of PacManX, allowing the game to run directly in web browsers.

## Overview

The WebAssembly (WASM) version of PacManX has been created using Emscripten, which compiles the C++ code to WebAssembly. This allows the game to run in any modern web browser without requiring native compilation.

## Prerequisites

### Installing Emscripten SDK

1. Clone the Emscripten SDK repository:
```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
```

2. Install and activate the latest version:
```bash
./emsdk install latest
./emsdk activate latest
```

3. Set up environment variables (you'll need to do this each time you open a new terminal):
```bash
source ./emsdk_env.sh
```

### System Requirements

- CMake 3.10 or higher
- Python 3 (for running local web server)
- Modern web browser with WebGL support (Chrome, Firefox, Safari, Edge)

## Building the WebAssembly Version

### Quick Build (Recommended)

Use the provided build script:

```bash
./build_wasm.sh
```

This script will:
- Check for Emscripten installation
- Create a `build_wasm` directory
- Configure the project with CMake
- Compile the C++ code to WebAssembly
- Generate all necessary files

### Manual Build

If you prefer to build manually:

```bash
# Create and enter build directory
mkdir build_wasm
cd build_wasm

# Configure with Emscripten
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
emmake make -j4
```

## Running the Game

After building, you'll have these files in the `build_wasm` directory:
- `pacmanx.html` - Main HTML file
- `pacmanx.js` - JavaScript loader
- `pacmanx.wasm` - WebAssembly binary
- `pacmanx.data` - Preloaded game assets (textures)

### Option 1: Using Python's Built-in Server

```bash
cd build_wasm
python3 -m http.server 8000
```

Then open your browser and navigate to:
```
http://localhost:8000/pacmanx.html
```

### Option 2: Using Node.js http-server

```bash
npm install -g http-server
cd build_wasm
http-server -p 8000
```

### Option 3: Deploy to Web Server

Copy all files from `build_wasm` directory to your web server and access the `pacmanx.html` file.

## Game Controls

- **Arrow Keys (↑ ↓ ← →)** - Move Pac-Man
- **W A S D** - Alternative movement controls
- **P** - Pause/Resume game
- **ESC** or **Q** - Quit game

## Technical Details

### Key Differences from Native Version

1. **Main Loop**: Uses `emscripten_set_main_loop` instead of `glutMainLoop`
2. **Threading**: Pthread includes are conditionally compiled out for WASM
3. **Sleep Function**: Disabled in paused state for WASM compatibility
4. **OpenGL**: Uses Emscripten's GLUT emulation and legacy GL emulation

### Build Configuration

The CMakeLists.txt includes specific Emscripten flags:
- `USE_GLUT=1` - Enable GLUT emulation
- `LEGACY_GL_EMULATION=1` - Enable fixed-function pipeline emulation
- `ALLOW_MEMORY_GROWTH=1` - Allow dynamic memory allocation
- `--preload-file` - Bundle texture assets with the WASM file

### File Size Optimization

The current build uses `-O3` optimization. To further reduce file size:

1. Edit `CMakeLists.txt` and modify the LINK_FLAGS section:
```cmake
-O3 -s WASM=1 --closure 1
```

2. Rebuild the project

## Troubleshooting

### Build Errors

**Error: "emcc not found"**
- Solution: Make sure you've activated the Emscripten environment: `source /path/to/emsdk/emsdk_env.sh`

**Error: "CMake version too old"**
- Solution: Update CMake to version 3.10 or higher

### Runtime Errors

**Error: "Failed to load .data file"**
- Solution: Make sure all files (HTML, JS, WASM, and DATA) are in the same directory and served from a web server

**Error: "WebGL context lost"**
- Solution: Your browser may have run out of GPU memory. Try closing other tabs or restarting the browser

**Game runs slowly**
- Check browser console for errors
- Try a different browser (Chrome/Firefox typically have better WebGL performance)
- Reduce browser window size

## Browser Compatibility

Tested and working on:
- Google Chrome 90+
- Mozilla Firefox 88+
- Safari 14+
- Microsoft Edge 90+

## Development

### Project Structure

```
PacManX/
├── CMakeLists.txt       # Build configuration (supports both native and WASM)
├── build_wasm.sh        # WASM build script
├── index.html           # Standalone HTML wrapper (optional)
├── README_WASM.md       # This file
├── include/             # C++ header files
├── src/                 # C++ source files
│   ├── main.cpp        # Modified with Emscripten support
│   └── Processador.cpp # Modified for WASM compatibility
└── texture/            # Game assets
```

### Building Native Version

The CMakeLists.txt also supports building the native version:

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
./pacmanx
```

## Credits

Original game by Fabrício Soares, Yooh, and Wesnydy.
WebAssembly port created using Emscripten.

## License

See LICENSE.md file for details.
