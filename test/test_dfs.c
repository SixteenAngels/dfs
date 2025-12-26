#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dfs.h"

int main() {
    printf("=== DFS Compression Library Test ===\n\n");
    
    const char* msg = "This is a test of the DFS compression system. It must be reversible!";
    size_t msg_len = strlen(msg);

    printf("Original message length: %zu bytes\n", msg_len);
    printf("Original: %s\n\n", msg);

    // Compress
    uint8_t compressed[1024];
    size_t compressed_size = sizeof(compressed);

    printf("Compressing...\n");
    if (dfs_compress((const uint8_t*)msg, msg_len, compressed, &compressed_size) != DFS_OK) {
        printf("ERROR: Compression failed\n");
        return 1;
    }

    printf("Compressed size: %zu bytes\n", compressed_size);
    printf("Compression ratio: %.2f%%\n\n", (double)compressed_size / msg_len * 100.0);

    // Decompress
    uint8_t decompressed[1024];
    size_t decompressed_size = sizeof(decompressed);

    printf("Decompressing...\n");
    if (dfs_decompress(compressed, compressed_size, decompressed, &decompressed_size) != DFS_OK) {
        printf("ERROR: Decompression failed\n");
        return 1;
    }

    printf("Decompressed size: %zu bytes\n\n", decompressed_size);
    printf("Decompressed: %.*s\n\n", (int)decompressed_size, decompressed);

    // Verify correctness
    if (decompressed_size != msg_len) {
        printf("ERROR: Size mismatch! Original: %zu, Decompressed: %zu\n", msg_len, decompressed_size);
        return 1;
    }

    if (memcmp(msg, decompressed, msg_len) != 0) {
        printf("ERROR: Data mismatch! Decompressed data does not match original.\n");
        return 1;
    }

    printf("SUCCESS: Compression and decompression verified!\n");
    printf("Original and decompressed data match perfectly.\n");
    
    return 0;
}
