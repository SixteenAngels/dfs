// dfs_utils.h
#ifndef DFS_UTILS_H
#define DFS_UTILS_H

#include "dfs_types.h"
#include <stdio.h>

void dfs_log(const char* fmt, ...);
u32 dfs_hash_token(const byte* data, size_t len);
void* dfs_alloc(size_t size);
void  dfs_free(void* ptr);

#endif // DFS_UTILS_H
