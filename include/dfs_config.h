// dfs_config.h
#ifndef DFS_CONFIG_H
#define DFS_CONFIG_H

#define DFS_VERSION "1.0.0"

// Enable debugging logs
#define DFS_ENABLE_LOGGING 1

// Max dictionary size (can be adjusted for performance/memory)
#define DFS_MAX_DICT_SIZE 65536

// Optional multithreading toggle (used later)
#define DFS_ENABLE_MULTITHREADING 1

// Maximum token length for compression
#define DFS_TOKEN_MAX_LENGTH 255

#endif // DFS_CONFIG_H
