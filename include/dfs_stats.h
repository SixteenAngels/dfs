// dfs_stats.h
#ifndef DFS_STATS_H
#define DFS_STATS_H

#include "dfs_types.h"
#include <time.h>

typedef struct {
    size_t total_input_bytes;
    size_t total_output_bytes;
    double compression_ratio;
    float compression_time_ms;
} dfs_stats_t;

void dfs_stats_reset(void);
void dfs_stats_update_input(size_t bytes);
void dfs_stats_update_output(size_t bytes);
void dfs_stats_record_compression(double ratio);
void dfs_stats_get(dfs_stats_t* out);

#endif // DFS_STATS_H
