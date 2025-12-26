#ifndef DFS_STREAM_H
#define DFS_STREAM_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "dfs_status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t* buffer;
    size_t size;
    size_t position;
    FILE* file;
    int is_memory;
    size_t pos;
} dfs_stream_t;

dfs_stream_t* dfs_stream_open(const char* path, const char* mode);
dfs_stream_t* dfs_stream_open_memory(uint8_t* buffer, size_t size);
size_t dfs_stream_read(dfs_stream_t* s, void* dest, size_t bytes);
size_t dfs_stream_write(dfs_stream_t* s, const void* src, size_t bytes);
void dfs_stream_close(dfs_stream_t* s);

// Helper functions for reading/writing specific types
uint8_t dfs_stream_read_u8(dfs_stream_t* stream);
uint16_t dfs_stream_read_u16(dfs_stream_t* stream);
void dfs_stream_write_u8(dfs_stream_t* stream, uint8_t value);
void dfs_stream_write_u16(dfs_stream_t* stream, uint16_t value);

#ifdef __cplusplus
}
#endif

#endif // DFS_STREAM_H
