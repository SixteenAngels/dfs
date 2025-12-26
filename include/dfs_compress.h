// dfs_compress.h
#ifndef DFS_COMPRESS_H
#define DFS_COMPRESS_H

#include "dfs_types.h"
#include "dfs_error.h"
#include "dfs.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Core compression engine (internal use)
int dfs_internal_compress(const dfs_buffer_t* input, dfs_buffer_t* output);

// Core decompression engine (internal use)
int dfs_internal_decompress(const dfs_buffer_t* input, dfs_buffer_t* output);

// Buffer-based compression (used by main API)
dfs_status_t dfs_compress_buffer(const uint8_t* input, size_t input_size, uint8_t* output, size_t* output_size);

#ifdef __cplusplus
}
#endif

#endif // DFS_COMPRESS_H
