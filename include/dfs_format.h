// dfs_format.h
#ifndef DFS_FORMAT_H
#define DFS_FORMAT_H

#include <stdint.h>

#define DFS_MAGIC_NUMBER 0x44534621  // "DFS!" in hex
#define DFS_HEADER_SIZE 16

typedef struct {
    uint32_t magic;
    uint16_t version_major;
    uint16_t version_minor;
    uint64_t original_size;
} dfs_file_header_t;

int dfs_write_header(FILE* fp, dfs_file_header_t* header);
int dfs_read_header(FILE* fp, dfs_file_header_t* header);

#endif // DFS_FORMAT_H
