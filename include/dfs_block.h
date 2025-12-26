#ifndef DFS_BLOCK_H
#define DFS_BLOCK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DFS_MAGIC_HEADER "DFS1"
#define DFS_BLOCK_SIZE 4096

typedef struct {
    uint32_t magic;
    uint16_t version;
    uint16_t flags;
    uint32_t original_size;
    uint32_t compressed_size;
} dfs_block_header_t;

#ifdef __cplusplus
}
#endif

#endif // DFS_BLOCK_H
