// dfs_analyze.h
#ifndef DFS_ANALYZE_H
#define DFS_ANALYZE_H

#include "dfs_types.h"
#include <stdint.h>
#include <stddef.h>

typedef struct {
    size_t frequency[256];
} dfs_histogram_t;

typedef struct {
    size_t file_size;
    size_t unique_bytes;
    float entropy;
} dfs_file_info_t;

void dfs_analyze_frequency(const uint8_t* data, size_t size, dfs_histogram_t* hist);
void dfs_analyze_print_histogram(const dfs_histogram_t* hist);
int dfs_analyze_file(const char* path, dfs_file_info_t* info);

#endif // DFS_ANALYZE_H
