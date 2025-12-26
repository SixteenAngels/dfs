#ifndef DFS_PERF_H
#define DFS_PERF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void dfs_perf_start(void);
void dfs_perf_end(void);
double dfs_perf_get_seconds(void);

#ifdef __cplusplus
}
#endif

#endif // DFS_PERF_H
