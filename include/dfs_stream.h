#ifndef DFS_STREAM_H
#define DFS_STREAM_H

#include <stddef.h>
#include <stdint.h>
#include "dfs_status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t* buffer;
    size_t size;
    size_t position;
} dfs_stream_t;

dfs_status_t dfs_stream_read(dfs_stream_t* stream, void* out, size_t len);
dfs_status_t dfs_stream_write(dfs_stream_t* stream, const void* in, size_t len);

#ifdef __cplusplus
}
#endif

#endif // DFS_STREAM_H
