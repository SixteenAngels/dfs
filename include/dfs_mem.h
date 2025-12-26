#ifndef DFS_MEM_H
#define DFS_MEM_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* dfs_alloc(size_t size);
void  dfs_free(void* ptr);
void  dfs_mem_init(void);
void  dfs_mem_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif // DFS_MEM_H
