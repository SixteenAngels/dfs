#ifndef DFS_LOGGER_H
#define DFS_LOGGER_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DFS_LOG_LEVEL_DEBUG = 0,
    DFS_LOG_LEVEL_INFO,
    DFS_LOG_LEVEL_WARN,
    DFS_LOG_LEVEL_ERROR,
    DFS_LOG_LEVEL_NONE
} dfs_log_level_t;

// Set log level (e.g., DFS_LOG_LEVEL_INFO)
void dfs_set_log_level(dfs_log_level_t level);

// Redirect logs to a file (or NULL for stderr)
void dfs_set_log_file(FILE* file);

// Internal logging function (not for direct use)
void dfs_log_internal(dfs_log_level_t level, const char* fmt, ...);

// Logging macros
#define DFS_LOG_DEBUG(fmt, ...)  dfs_log_internal(DFS_LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define DFS_LOG_INFO(fmt, ...)   dfs_log_internal(DFS_LOG_LEVEL_INFO,  fmt, ##__VA_ARGS__)
#define DFS_LOG_WARN(fmt, ...)   dfs_log_internal(DFS_LOG_LEVEL_WARN,  fmt, ##__VA_ARGS__)
#define DFS_LOG_ERROR(fmt, ...)  dfs_log_internal(DFS_LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // DFS_LOGGER_H
