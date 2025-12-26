# DFS Compression Library

A high-performance data compression library written in C, designed for efficient compression and decompression of data with a dictionary-based compression algorithm.

## Overview

DFS (Dictionary-based File System) is a compression library that uses a dictionary-based approach to compress and decompress data. The library provides both in-memory and file-based compression APIs, making it suitable for various use cases from embedded systems to desktop applications.

## Features

- **Dictionary-based Compression**: Efficient compression using a dynamic dictionary
- **In-Memory API**: Compress/decompress data directly from memory buffers
- **File-based API**: Compress/decompress files directly
- **Error Handling**: Comprehensive error codes and error reporting
- **Logging System**: Built-in logging for debugging and monitoring
- **Modular Design**: Well-organized codebase with separate modules for different functionalities
- **Cross-platform**: Written in standard C99 for maximum portability

## Project Structure

```
dfs/
├── include/          # Header files
│   ├── dfs.h         # Main public API
│   ├── dfs_compress.h
│   ├── dfs_decompress.h
│   ├── dfs_dict.h    # Dictionary implementation
│   ├── dfs_io.h      # File I/O operations
│   ├── dfs_error.h   # Error handling
│   ├── dfs_logger.h  # Logging system
│   └── ...
├── src/              # Source files
│   ├── dfs.c         # Main API implementation
│   ├── dfs_compress.c
│   ├── dfs_decompress.c
│   ├── dfs_dict.c
│   ├── dfs_io.c
│   └── ...
├── test/             # Test files
│   └── test_dfs.c    # Basic compression/decompression test
├── CMakeLists.txt    # CMake build configuration
└── README.md         # This file
```

## Recent Fixes and Improvements

This project has been recently refactored and fixed to resolve compilation errors and improve code quality:

### 1. **Fixed Duplicate Function Definitions**
   - Resolved duplicate definitions of `dfs_compress` and `dfs_decompress`
   - Renamed internal implementations to `dfs_compress_buffer` and `dfs_decompress_buffer`
   - Properly separated public API from internal implementations

### 2. **Added Missing Function Declarations**
   - Added `dfs_compress_buffer` and `dfs_decompress_buffer` declarations to headers
   - Ensured all functions are properly declared before use

### 3. **Fixed Missing Definitions**
   - Added `DFS_TOKEN_MAX_LENGTH` definition (255 bytes) to `dfs_config.h`
   - Added missing type definitions (`dfs_dict_t`, `dfs_token_t`, `dfs_file_t`)

### 4. **Improved Error Handling**
   - Standardized error code usage throughout the codebase
   - Added proper error code includes where needed
   - Improved error reporting consistency

### 5. **Fixed Logging System**
   - Updated logging calls to use proper macros (`DFS_LOG_ERROR`, `DFS_LOG_INFO`, etc.)
   - Fixed incorrect logging API usage

### 6. **Implemented File I/O Functions**
   - Implemented `dfs_io_compress_file` and `dfs_io_decompress_file`
   - Added proper file reading/writing with error handling

### 7. **Type Consistency**
   - Standardized return types to use `dfs_status_t` where appropriate
   - Improved type safety and consistency across the codebase

### 8. **Header Organization**
   - Added proper includes to prevent compilation errors
   - Organized header dependencies correctly
   - Added C++ compatibility guards

## Building the Project

### Prerequisites
- CMake 3.10 or higher
- A C99-compatible compiler (GCC, Clang, MSVC, etc.)

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build .

# On Unix-like systems, you can also use:
# make
```

### Building on Windows

```powershell
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build using Visual Studio
cmake --build . --config Release
```

## Usage

### Basic In-Memory Compression

```c
#include "dfs.h"
#include <stdio.h>
#include <string.h>

int main() {
    const char* data = "Hello, World!";
    size_t data_len = strlen(data);
    
    // Compress
    uint8_t compressed[1024];
    size_t compressed_size = sizeof(compressed);
    
    if (dfs_compress((const uint8_t*)data, data_len, 
                      compressed, &compressed_size) != DFS_OK) {
        printf("Compression failed\n");
        return 1;
    }
    
    printf("Compressed %zu bytes to %zu bytes\n", data_len, compressed_size);
    
    // Decompress
    uint8_t decompressed[1024];
    size_t decompressed_size = sizeof(decompressed);
    
    if (dfs_decompress(compressed, compressed_size,
                       decompressed, &decompressed_size) != DFS_OK) {
        printf("Decompression failed\n");
        return 1;
    }
    
    printf("Decompressed: %.*s\n", (int)decompressed_size, decompressed);
    
    return 0;
}
```

### File-based Compression

```c
#include "dfs.h"

int main() {
    // Compress a file
    if (dfs_compress_file("input.txt", "output.dfs") != DFS_OK) {
        printf("File compression failed\n");
        return 1;
    }
    
    // Decompress a file
    if (dfs_decompress_file("output.dfs", "output.txt") != DFS_OK) {
        printf("File decompression failed\n");
        return 1;
    }
    
    return 0;
}
```

## API Reference

### Main Functions

#### `dfs_compress`
Compress data from a memory buffer.

```c
int dfs_compress(const uint8_t* input, size_t input_size, 
                 uint8_t* output, size_t* output_size);
```

**Parameters:**
- `input`: Pointer to input data buffer
- `input_size`: Size of input data in bytes
- `output`: Pointer to output buffer
- `output_size`: Pointer to output buffer size (updated with actual compressed size)

**Returns:** `DFS_OK` on success, error code on failure

#### `dfs_decompress`
Decompress data from a memory buffer.

```c
int dfs_decompress(const uint8_t* input, size_t input_size,
                   uint8_t* output, size_t* output_size);
```

**Parameters:**
- `input`: Pointer to compressed data buffer
- `input_size`: Size of compressed data in bytes
- `output`: Pointer to output buffer
- `output_size`: Pointer to output buffer size (updated with actual decompressed size)

**Returns:** `DFS_OK` on success, error code on failure

#### `dfs_compress_file`
Compress a file.

```c
int dfs_compress_file(const char* input_path, const char* output_path);
```

**Parameters:**
- `input_path`: Path to input file
- `output_path`: Path to output compressed file

**Returns:** `DFS_OK` on success, error code on failure

#### `dfs_decompress_file`
Decompress a file.

```c
int dfs_decompress_file(const char* input_path, const char* output_path);
```

**Parameters:**
- `input_path`: Path to compressed input file
- `output_path`: Path to decompressed output file

**Returns:** `DFS_OK` on success, error code on failure

### Error Codes

```c
typedef enum {
    DFS_OK = 0,
    DFS_ERR_INVALID_INPUT,
    DFS_ERR_BUFFER_TOO_SMALL,
    DFS_ERR_COMPRESSION_FAILED,
    DFS_ERR_DECOMPRESSION_FAILED,
    DFS_ERR_FILE_IO,
    DFS_ERR_UNKNOWN
} dfs_status_t;
```

## Running Tests

The project includes a basic test program to verify compression and decompression:

```bash
# Build the test executable
cd build
cmake --build . --target test_dfs

# Run the test
./test_dfs  # On Unix
# or
.\test_dfs.exe  # On Windows
```

The test program:
1. Compresses a test string
2. Decompresses the compressed data
3. Verifies that the decompressed data matches the original
4. Prints the results

## Configuration

Configuration options can be found in `include/dfs_config.h`:

- `DFS_VERSION`: Library version string
- `DFS_ENABLE_LOGGING`: Enable/disable logging
- `DFS_MAX_DICT_SIZE`: Maximum dictionary size (default: 65536)
- `DFS_ENABLE_MULTITHREADING`: Enable multithreading support
- `DFS_TOKEN_MAX_LENGTH`: Maximum token length (default: 255)

## Architecture

The DFS compression library uses a dictionary-based compression algorithm:

1. **Dictionary Creation**: A dynamic dictionary is created to store frequently occurring patterns
2. **Token Matching**: Input data is divided into tokens and matched against the dictionary
3. **Encoding**: Tokens are encoded using dictionary indices
4. **Output Generation**: Compressed data includes dictionary indices and literal data

The decompression process reverses this:
1. **Index Reading**: Dictionary indices are read from compressed data
2. **Token Lookup**: Tokens are retrieved from the dictionary using indices
3. **Reconstruction**: Original data is reconstructed from tokens

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.

## License

[Specify your license here]

## Author

[Your name/Organization]

## Acknowledgments

- Built with standard C99 for maximum portability
- Uses CMake for cross-platform builds
- Designed with modularity and extensibility in mind

