// dfs_block.c
#include "dfs_block.h"
#include "dfs_config.h"
#include "dfs_utils.h"
#include <string.h>

#define DFS_MAGIC_HEADER "DFS1"
#define DFS_BLOCK_VERSION 1

int dfs_block_write_header(uint8_t* buffer, size_t buffer_size) {
    if (buffer_size < DFS_HEADER_SIZE) return DFS_ERR_BUFFER_TOO_SMALL;

    memcpy(buffer, DFS_MAGIC_HEADER, 4);
    buffer[4] = DFS_BLOCK_VERSION;
    return DFS_OK;
}

int dfs_block_validate_header(const uint8_t* buffer, size_t buffer_size) {
    if (buffer_size < DFS_HEADER_SIZE) return DFS_ERR_INVALID_INPUT;
    if (memcmp(buffer, DFS_MAGIC_HEADER, 4) != 0) return DFS_ERR_INVALID_INPUT;
    if (buffer[4] != DFS_BLOCK_VERSION) return DFS_ERR_INVALID_INPUT;

    return DFS_OK;
}
