// dfs_thread.h
#ifndef DFS_THREAD_H
#define DFS_THREAD_H

#include "dfs_types.h"

#ifdef _WIN32
#include <windows.h>
typedef HANDLE dfs_thread_t;
#else
#include <pthread.h>
typedef pthread_t dfs_thread_t;
#endif

typedef void* (*dfs_thread_func)(void* arg);

#ifdef __cplusplus
extern "C" {
#endif

int dfs_thread_create(dfs_thread_t* thread, dfs_thread_func func, void* arg);
int dfs_thread_join(dfs_thread_t thread);

#ifdef DFS_ENABLE_MULTITHREADING

int dfs_parallel_compress(const dfs_buffer_t* input, dfs_buffer_t* output);
int dfs_parallel_decompress(const dfs_buffer_t* input, dfs_buffer_t* output);

#endif

#ifdef __cplusplus
}
#endif

#endif // DFS_THREAD_H
