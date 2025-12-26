// dfs_thread.c
#include "dfs_thread.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

int dfs_thread_create(dfs_thread_t* thread, dfs_thread_func func, void* arg) {
#ifdef _WIN32
    *thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, arg, 0, NULL);
    return (*thread != NULL) ? 0 : -1;
#else
    return pthread_create(thread, NULL, func, arg);
#endif
}

int dfs_thread_join(dfs_thread_t thread) {
#ifdef _WIN32
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    return 0;
#else
    return pthread_join(thread, NULL);
#endif
}
