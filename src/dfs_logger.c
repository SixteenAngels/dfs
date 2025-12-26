#include "dfs_logger.h"
#include <stdarg.h>
#include <time.h>

static dfs_log_level_t current_level = DFS_LOG_LEVEL_INFO;
static FILE* log_output = NULL;

void dfs_set_log_level(dfs_log_level_t level) {
    current_level = level;
}

void dfs_set_log_file(FILE* file) {
    log_output = file;
}

static const char* level_to_string(dfs_log_level_t level) {
    switch (level) {
        case DFS_LOG_LEVEL_DEBUG: return "DEBUG";
        case DFS_LOG_LEVEL_INFO:  return "INFO";
        case DFS_LOG_LEVEL_WARN:  return "WARN";
        case DFS_LOG_LEVEL_ERROR: return "ERROR";
        default: return "LOG";
    }
}

static void timestamp(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

void dfs_log_internal(dfs_log_level_t level, const char* fmt, ...) {
    if (level < current_level || level == DFS_LOG_LEVEL_NONE)
        return;

    FILE* out = log_output ? log_output : stderr;

    char timebuf[20];
    timestamp(timebuf, sizeof(timebuf));

    fprintf(out, "[%s] [%s] ", timebuf, level_to_string(level));

    va_list args;
    va_start(args, fmt);
    vfprintf(out, fmt, args);
    va_end(args);

    fprintf(out, "\n");
    fflush(out);
}
