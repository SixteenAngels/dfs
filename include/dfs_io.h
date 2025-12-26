// dfs_io.h
#ifndef DFS_IO_H
#define DFS_IO_H

#include "dfs_types.h"
#include "dfs_error.h"

#ifdef __cplusplus
extern "C" {
#endif

// Load file into memory buffer
int dfs_load_file(const char* path, dfs_buffer_t* buffer);

// Save buffer to file
int dfs_save_file(const char* path, const dfs_buffer_t* buffer);

// Release file buffer
void dfs_free_buffer(dfs_buffer_t* buffer);

// Compress a file
int dfs_io_compress_file(const char* input_path, const char* output_path);

// Decompress a file
int dfs_io_decompress_file(const char* input_path, const char* output_path);

#ifdef __cplusplus
}
#endif

#endif // DFS_IO_H
