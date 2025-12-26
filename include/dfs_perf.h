#ifndef DFS_PERF_H
#define DFS_PERF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double start;
    double end;
    double elapsed;
} dfs_timer_t;

void dfs_timer_start(dfs_timer_t* timer);
void dfs_timer_stop(dfs_timer_t* timer);
double dfs_timer_elapsed(const dfs_timer_t* timer);

#ifdef __cplusplus
}
#endif

#endif // DFS_PERF_H
