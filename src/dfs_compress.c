// dfs_compress.c
#include "dfs_compress.h"
#include "dfs_dict.h"
#include "dfs_block.h"
#include "dfs_utils.h"
#include "dfs_mem.h"
#include "dfs_config.h"
#include "dfs_error.h"
#include "dfs.h"
#include <string.h>

dfs_status_t dfs_compress_buffer(const uint8_t* input, size_t input_size, uint8_t* output, size_t* output_size) {
    if (!input || !output || !output_size || input_size == 0) return DFS_ERR_INVALID_INPUT;

    dfs_dict_t* dict = dfs_dict_create();
    if (!dict) return DFS_ERR_COMPRESSION_FAILED;

    uint8_t* out_ptr = output;
    size_t out_capacity = *output_size;
    size_t out_used = 0;

    size_t i = 0;
    while (i < input_size) {
        size_t max_len = DFS_TOKEN_MAX_LENGTH;
        if (i + max_len > input_size) max_len = input_size - i;

        uint16_t index;
        int status = dfs_dict_insert(dict, &input[i], max_len, &index);

        if (status < 0) {
            dfs_dict_free(dict);
            return DFS_ERR_COMPRESSION_FAILED;
        }

        // Encode: [2 bytes: index][1 byte: actual length][data]
        if (out_used + 3 + max_len > out_capacity) {
            dfs_dict_free(dict);
            return DFS_ERR_BUFFER_TOO_SMALL;
        }

        out_ptr[out_used++] = (index >> 8) & 0xFF;
        out_ptr[out_used++] = index & 0xFF;
        out_ptr[out_used++] = (uint8_t)max_len;
        memcpy(&out_ptr[out_used], &input[i], max_len);
        out_used += max_len;

        i += max_len;
    }

    dfs_dict_free(dict);
    *output_size = out_used;
    return DFS_OK;
}
