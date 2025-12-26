#include "dfs.h"
#include "dfs_compress.h"
#include "dfs_decompress.h"
#include "dfs_logger.h"
#include "dfs_utils.h"
#include "dfs_stream.h"
#include "dfs_error.h"
#include "dfs_io.h"

#include <stdio.h>
#include <stdlib.h>

// ========================
// In-memory Compression
// ========================
int dfs_compress(const uint8_t* input, size_t input_size, uint8_t* output, size_t* output_size) {
    if (!input || !output || !output_size || input_size == 0) {
        DFS_LOG_ERROR("Invalid parameters to dfs_compress");
        return DFS_ERR_INVALID_INPUT;
    }

    int status = dfs_compress_buffer(input, input_size, output, output_size);
    if (status != DFS_OK) {
        DFS_LOG_ERROR("Compression failed with status: %d", status);
        return status;
    }

    DFS_LOG_INFO("Compressed %zu bytes -> %zu bytes", input_size, *output_size);
    return DFS_OK;
}

// ========================
// In-memory Decompression
// ========================
int dfs_decompress(const uint8_t* input, size_t input_size, uint8_t* output, size_t* output_size) {
    if (!input || !output || !output_size || input_size == 0) {
        DFS_LOG_ERROR("Invalid parameters to dfs_decompress");
        return DFS_ERR_INVALID_INPUT;
    }

    int status = dfs_decompress_buffer(input, input_size, output, output_size);
    if (status != DFS_OK) {
        DFS_LOG_ERROR("Decompression failed with status: %d", status);
        return status;
    }

    DFS_LOG_INFO("Decompressed %zu bytes -> %zu bytes", input_size, *output_size);
    return DFS_OK;
}

// ========================
// File-based Compression
// ========================
int dfs_compress_file(const char* input_path, const char* output_path) {
    if (!input_path || !output_path) {
        DFS_LOG_ERROR("Invalid file paths for compression");
        return DFS_ERR_INVALID_INPUT;
    }

    return dfs_io_compress_file(input_path, output_path);
}

// ========================
// File-based Decompression
// ========================
int dfs_decompress_file(const char* input_path, const char* output_path) {
    if (!input_path || !output_path) {
        DFS_LOG_ERROR("Invalid file paths for decompression");
        return DFS_ERR_INVALID_INPUT;
    }

    return dfs_io_decompress_file(input_path, output_path);
}
