/*
 * Manual compilation test script
 * This file can be used to verify the code compiles correctly
 * 
 * Compile with:
 *   gcc -I./include test_manual.c src/dfs.c src/dfs_compress.c src/dfs_decompress.c src/dfs_dict.c src/dfs_error.c src/dfs_logger.c src/dfs_utils.c src/dfs_io.c src/dfs_mem.c -o test_manual
 * 
 * Or use the build scripts provided (build_test.bat or build_test.sh)
 */

#include <stdio.h>
#include <string.h>
#include "dfs.h"

int main() {
    printf("=== DFS Compression Library Manual Test ===\n\n");
    
    const char* test_strings[] = {
        "Hello, World!",
        "This is a test of the DFS compression system. It must be reversible!",
        "The quick brown fox jumps over the lazy dog.",
        "A"  // Single character test
    };
    
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    int passed = 0;
    
    for (int i = 0; i < num_tests; i++) {
        const char* msg = test_strings[i];
        size_t msg_len = strlen(msg);
        
        printf("Test %d/%d: \"%s\"\n", i + 1, num_tests, msg);
        
        // Compress
        uint8_t compressed[1024];
        size_t compressed_size = sizeof(compressed);
        
        int result = dfs_compress((const uint8_t*)msg, msg_len, compressed, &compressed_size);
        if (result != DFS_OK) {
            printf("  FAILED: Compression error %d\n\n", result);
            continue;
        }
        
        // Decompress
        uint8_t decompressed[1024];
        size_t decompressed_size = sizeof(decompressed);
        
        result = dfs_decompress(compressed, compressed_size, decompressed, &decompressed_size);
        if (result != DFS_OK) {
            printf("  FAILED: Decompression error %d\n\n", result);
            continue;
        }
        
        // Verify
        if (decompressed_size != msg_len || memcmp(msg, decompressed, msg_len) != 0) {
            printf("  FAILED: Data mismatch\n\n");
            continue;
        }
        
        printf("  PASSED: %zu bytes -> %zu bytes (%.1f%%)\n\n", 
               msg_len, compressed_size, (double)compressed_size / msg_len * 100.0);
        passed++;
    }
    
    printf("Results: %d/%d tests passed\n", passed, num_tests);
    
    if (passed == num_tests) {
        printf("\nSUCCESS: All tests passed!\n");
        return 0;
    } else {
        printf("\nFAILURE: Some tests failed.\n");
        return 1;
    }
}

