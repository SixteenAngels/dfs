#ifndef DFS_CACHE_H
#define DFS_CACHE_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void dfs_cache_init(size_t size);
void dfs_cache_store(uint32_t hash, uint32_t offset);
int  dfs_cache_lookup(uint32_t hash, uint32_t* offset);
void dfs_cache_clear(void);

#ifdef __cplusplus
}
#endif

#endif // DFS_CACHE_H
