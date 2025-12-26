# Quick Start Guide

## Prerequisites

Before building the DFS Compression Library, you need:

1. **A C Compiler** (one of the following):
   - **GCC** (MinGW on Windows, or native on Linux/Mac)
   - **Clang** (available on all platforms)
   - **MSVC** (Visual Studio on Windows)

2. **CMake** (optional, but recommended):
   - Download from: https://cmake.org/download/
   - Or use package managers:
     - Windows: `choco install cmake` or `winget install cmake`
     - Linux: `sudo apt-get install cmake` (Ubuntu/Debian) or `sudo yum install cmake` (RHEL/CentOS)
     - Mac: `brew install cmake`

## Building Without CMake

If CMake is not available, you can compile manually:

### On Windows (using GCC/MinGW):
```bash
gcc -I./include -c src/*.c
gcc -o test_dfs test/test_dfs.c *.o -I./include
```

### On Linux/Mac:
```bash
gcc -I./include -c src/*.c
gcc -o test_dfs test/test_dfs.c *.o -I./include
./test_dfs
```

## Building With CMake (Recommended)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Running the Test

After building:
```bash
# Windows
.\test_dfs.exe

# Linux/Mac
./test_dfs
```

## Expected Test Output

When the test runs successfully, you should see:

```
=== DFS Compression Library Test ===

Original message length: 68 bytes
Original: This is a test of the DFS compression system. It must be reversible!

Compressing...
Compressed size: XXX bytes
Compression ratio: XX.XX%

Decompressing...
Decompressed size: 68 bytes

Decompressed: This is a test of the DFS compression system. It must be reversible!

SUCCESS: Compression and decompression verified!
Original and decompressed data match perfectly.
```

## Troubleshooting

### "CMake not found"
- Install CMake from https://cmake.org/download/
- Or compile manually using the instructions above

### "Compiler not found"
- Install a C compiler:
  - Windows: Install MinGW-w64 or Visual Studio
  - Linux: `sudo apt-get install build-essential`
  - Mac: Install Xcode Command Line Tools: `xcode-select --install`

### Compilation Errors
- Ensure all header files are in the `include/` directory
- Ensure all source files are in the `src/` directory
- Check that you're including the `include/` directory in your compiler flags (`-I./include`)

## Next Steps

1. Review the [README.md](README.md) for detailed API documentation
2. Explore the example code in `test/test_dfs.c`
3. Integrate the library into your own projects

