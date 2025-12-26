// dfs_cache.c
#include "dfs_cache.h"
#include <stdlib.h>
#include <string.h>

#define CACHE_MAGIC 0xCAFEBABE

int dfs_cache_init(dfs_cache_t* cache, size_t size) {
    if (!cache || size == 0) return DFS_ERR_INVALID_INPUT;

    cache->size = size;
    cache->entries = (dfs_cache_entry_t*)malloc(size * sizeof(dfs_cache_entry_t));
    if (!cache->entries) return DFS_ERR_MEM_ALLOC;

    memset(cache->entries, 0, size * sizeof(dfs_cache_entry_t));
    cache->magic = CACHE_MAGIC;
    return DFS_OK;
}

int dfs_cache_put(dfs_cache_t* cache, uint32_t key, uint32_t value) {
    if (!cache || cache->magic != CACHE_MAGIC) return DFS_ERR_INVALID_INPUT;
    size_t index = key % cache->size;
    cache->entries[index].key = key;
    cache->entries[index].value = value;
    return DFS_OK;
}

int dfs_cache_get(dfs_cache_t* cache, uint32_t key, uint32_t* value_out) {
    if (!cache || !value_out || cache->magic != CACHE_MAGIC) return DFS_ERR_INVALID_INPUT;
    size_t index = key % cache->size;
    if (cache->entries[index].key == key) {
        *value_out = cache->entries[index].value;
        return DFS_OK;
    }
    return DFS_ERR_UNKNOWN;
}

void dfs_cache_free(dfs_cache_t* cache) {
    if (cache && cache->magic == CACHE_MAGIC) {
        free(cache->entries);
        cache->entries = NULL;
        cache->magic = 0;
    }
}
