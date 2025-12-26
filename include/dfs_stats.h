// dfs_stats.h
#ifndef DFS_STATS_H
#define DFS_STATS_H

#include "dfs_types.h"
#include <time.h>

typedef struct {
    size_t original_size;
    size_t compressed_size;
    float ratio;
    float compression_time_ms;
} dfs_stats_t;

void dfs_init_stats(dfs_stats_t* stats);
void dfs_calculate_stats(dfs_stats_t* stats, size_t original, size_t compressed, clock_t start, clock_t end);

#endif // DFS_STATS_H
