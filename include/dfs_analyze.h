// dfs_analyze.h
#ifndef DFS_ANALYZE_H
#define DFS_ANALYZE_H

#include "dfs_types.h"

typedef struct {
    size_t file_size;
    size_t unique_bytes;
    float entropy;
} dfs_file_info_t;

int dfs_analyze_file(const char* path, dfs_file_info_t* info);

#endif // DFS_ANALYZE_H
