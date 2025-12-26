// dfs_perf.c
#include "dfs_perf.h"

#if defined(_WIN32)
#include <windows.h>
double dfs_now() {
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / freq.QuadPart;
}
#else
#include <time.h>
double dfs_now() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}
#endif

void dfs_timer_start(dfs_timer_t* timer) {
    if (timer) {
        timer->start = dfs_now();
    }
}

void dfs_timer_stop(dfs_timer_t* timer) {
    if (timer) {
        timer->end = dfs_now();
        timer->elapsed = timer->end - timer->start;
    }
}

double dfs_timer_elapsed(const dfs_timer_t* timer) {
    return timer ? timer->elapsed : 0.0;
}
