// dfs.h
#ifndef DFS_H
#define DFS_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// =======================
// DFS Version
// =======================
#define DFS_VERSION "1.0.0"

// =======================
// Status Codes
// =======================
typedef enum {
    DFS_OK = 0,
    DFS_ERR_INVALID_INPUT,
    DFS_ERR_BUFFER_TOO_SMALL,
    DFS_ERR_COMPRESSION_FAILED,
    DFS_ERR_DECOMPRESSION_FAILED,
    DFS_ERR_FILE_IO,
    DFS_ERR_MEM_ALLOC,
    DFS_ERR_THREAD_FAIL,
    DFS_ERR_INVALID_FORMAT,
    DFS_ERR_UNKNOWN
} dfs_status_t;

// =======================
// Main API Functions
// =======================

/**
 * Compress data from memory buffer
 *
 * @param input          Pointer to input buffer
 * @param input_size     Size of input buffer in bytes
 * @param output         Pointer to output buffer
 * @param output_size    Pointer to output buffer size; updated with actual size
 *
 * @return DFS_OK or an error code
 */
dfs_status_t dfs_compress(const uint8_t* input, size_t input_size, uint8_t* output, size_t* output_size);

/**
 * Decompress data from memory buffer
 *
 * @param input          Pointer to compressed input
 * @param input_size     Size of compressed input
 * @param output         Pointer to output buffer
 * @param output_size    Pointer to output buffer size; updated with actual size
 *
 * @return DFS_OK or an error code
 */
dfs_status_t dfs_decompress(const uint8_t* input, size_t input_size, uint8_t* output, size_t* output_size);

// =======================
// Optional File-based APIs
// =======================

/**
 * Compress an input file and write to output file
 *
 * @param input_path     Path to input file
 * @param output_path    Path to write compressed output
 *
 * @return DFS_OK or an error code
 */
dfs_status_t dfs_compress_file(const char* input_path, const char* output_path);

/**
 * Decompress an input file and write to output file
 *
 * @param input_path     Path to compressed input file
 * @param output_path    Path to write decompressed output
 *
 * @return DFS_OK or an error code
 */
dfs_status_t dfs_decompress_file(const char* input_path, const char* output_path);

#ifdef __cplusplus
}
#endif

#endif // DFS_H
