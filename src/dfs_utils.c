// dfs_utils.c
#include "dfs_utils.h"
#include <stdint.h>

uint32_t dfs_crc32(const uint8_t* data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; ++i) {
        crc ^= data[i];
        for (int j = 0; j < 8; ++j)
            crc = (crc >> 1) ^ (0xEDB88320 & (-(crc & 1)));
    }
    return ~crc;
}

uint8_t dfs_bit_count(uint32_t x) {
    uint8_t count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}
