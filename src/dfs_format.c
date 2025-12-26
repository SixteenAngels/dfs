#include "dfs_format.h"
#include <string.h>

int dfs_format_header_write(dfs_stream_t* stream, const dfs_header_t* header) {
    if (!stream || !header) return DFS_ERR_INVALID_INPUT;

    // Write the file signature
    dfs_stream_write(stream, (const uint8_t*)DFS_MAGIC_BYTES, strlen(DFS_MAGIC_BYTES));

    // Write version info
    dfs_stream_write_u8(stream, header->version_major);
    dfs_stream_write_u8(stream, header->version_minor);

    // Write flags
    dfs_stream_write_u16(stream, header->flags);

    return DFS_OK;
}

int dfs_format_header_read(dfs_stream_t* stream, dfs_header_t* header) {
    if (!stream || !header) return DFS_ERR_INVALID_INPUT;

    // Read and validate magic bytes
    char magic[DFS_MAGIC_LEN + 1] = {0};
    dfs_stream_read(stream, (uint8_t*)magic, DFS_MAGIC_LEN);

    if (strncmp(magic, DFS_MAGIC_BYTES, DFS_MAGIC_LEN) != 0) {
        return DFS_ERR_INVALID_FORMAT;
    }

    // Read version info
    header->version_major = dfs_stream_read_u8(stream);
    header->version_minor = dfs_stream_read_u8(stream);

    // Read flags
    header->flags = dfs_stream_read_u16(stream);

    return DFS_OK;
}
