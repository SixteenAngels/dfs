// dfs_thread.h
#ifndef DFS_THREAD_H
#define DFS_THREAD_H

#include "dfs_types.h"

#ifdef DFS_ENABLE_MULTITHREADING

int dfs_parallel_compress(const dfs_buffer_t* input, dfs_buffer_t* output);
int dfs_parallel_decompress(const dfs_buffer_t* input, dfs_buffer_t* output);

#endif

#endif // DFS_THREAD_H
