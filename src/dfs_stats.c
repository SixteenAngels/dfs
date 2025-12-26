#include "dfs_stats.h"
#include <string.h>  // for memset

static dfs_stats_t g_stats = {0};

void dfs_stats_reset(void) {
    memset(&g_stats, 0, sizeof(g_stats));
}

void dfs_stats_update_input(size_t bytes) {
    g_stats.total_input_bytes += bytes;
}

void dfs_stats_update_output(size_t bytes) {
    g_stats.total_output_bytes += bytes;
}

void dfs_stats_record_compression(double ratio) {
    g_stats.compression_ratio = ratio;
}

void dfs_stats_get(dfs_stats_t* out) {
    if (out) {
        *out = g_stats;
    }
}
