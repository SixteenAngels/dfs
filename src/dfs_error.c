// dfs_error.c
#include "dfs_error.h"
#include "dfs.h"
#include <stdio.h>

const char* dfs_strerror(dfs_status_t code) {
    switch (code) {
        case DFS_OK: return "No error (DFS_OK)";
        case DFS_ERR_INVALID_INPUT: return "Invalid input provided";
        case DFS_ERR_BUFFER_TOO_SMALL: return "Output buffer too small";
        case DFS_ERR_COMPRESSION_FAILED: return "Compression failed";
        case DFS_ERR_DECOMPRESSION_FAILED: return "Decompression failed";
        case DFS_ERR_FILE_IO: return "File I/O error";
        case DFS_ERR_MEM_ALLOC: return "Memory allocation failed";
        case DFS_ERR_THREAD_FAIL: return "Threading error";
        case DFS_ERR_UNKNOWN: return "Unknown error";
        default: return "Unrecognized error code";
    }
}

void dfs_perror(const char* prefix, dfs_status_t code) {
    if (prefix)
        fprintf(stderr, "%s: %s\n", prefix, dfs_strerror(code));
    else
        fprintf(stderr, "%s\n", dfs_strerror(code));
}
