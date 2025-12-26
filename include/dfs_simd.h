// dfs_simd.h
#ifndef DFS_SIMD_H
#define DFS_SIMD_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// SIMD accelerated functions
int dfs_simd_compare(const void* a, const void* b, size_t len);
void dfs_simd_memcpy(void* dst, const void* src, size_t len);
int dfs_memcmp_simd(const void* a, const void* b, size_t len); // legacy or alias if needed

#ifdef __cplusplus
}
#endif

#endif // DFS_SIMD_H
