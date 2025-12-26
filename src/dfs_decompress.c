// dfs_decompress.c
#include "dfs_decompress.h"
#include "dfs_utils.h"
#include "dfs_mem.h"
#include "dfs_error.h"
#include "dfs.h"
#include <string.h>

dfs_status_t dfs_decompress_buffer(const uint8_t* input, size_t input_size, uint8_t* output, size_t* output_size) {
    if (!input || !output || !output_size || input_size == 0) return DFS_ERR_INVALID_INPUT;

    size_t in_offset = 0;
    size_t out_offset = 0;
    size_t out_capacity = *output_size;

    while (in_offset + 3 <= input_size) {
        uint16_t index = (input[in_offset] << 8) | input[in_offset + 1];
        uint8_t length = input[in_offset + 2];
        in_offset += 3;

        if (in_offset + length > input_size || out_offset + length > out_capacity)
            return DFS_ERR_BUFFER_TOO_SMALL;

        memcpy(&output[out_offset], &input[in_offset], length);
        in_offset += length;
        out_offset += length;
    }

    *output_size = out_offset;
    return DFS_OK;
}
