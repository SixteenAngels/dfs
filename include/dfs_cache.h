#ifndef DFS_CACHE_H
#define DFS_CACHE_H

#include <stdint.h>
#include <stddef.h>
#include "dfs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t key;
    uint32_t value;
} dfs_cache_entry_t;

typedef struct {
    uint32_t magic;
    size_t size;
    dfs_cache_entry_t* entries;
} dfs_cache_t;

int dfs_cache_init(dfs_cache_t* cache, size_t size);
int dfs_cache_put(dfs_cache_t* cache, uint32_t key, uint32_t value);
int dfs_cache_get(dfs_cache_t* cache, uint32_t key, uint32_t* value_out);
void dfs_cache_free(dfs_cache_t* cache);

#ifdef __cplusplus
}
#endif

#endif // DFS_CACHE_H
