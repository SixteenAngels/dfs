// dfs_types.h
#ifndef DFS_TYPES_H
#define DFS_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef uint8_t  byte;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct {
    byte* data;
    size_t size;
} dfs_buffer_t;

typedef struct {
    FILE* fp;
} dfs_file_t;

#endif // DFS_TYPES_H
