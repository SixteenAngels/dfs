// dfs_cli.c - Command-line interface for DFS compression
#include "dfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char* prog_name) {
    printf("DFS Compression Library - Command Line Tool\n");
    printf("Usage: %s <operation> <input_file> <output_file>\n", prog_name);
    printf("\n");
    printf("Operations:\n");
    printf("  compress    - Compress input file to output file\n");
    printf("  decompress  - Decompress input file to output file\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s compress input.txt output.dfs\n", prog_name);
    printf("  %s decompress output.dfs input_restored.txt\n", prog_name);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }
    
    const char* operation = argv[1];
    const char* input_path = argv[2];
    const char* output_path = argv[3];
    
    dfs_status_t result;
    
    if (strcmp(operation, "compress") == 0) {
        printf("Compressing %s -> %s\n", input_path, output_path);
        result = dfs_compress_file(input_path, output_path);
        if (result == DFS_OK) {
            printf("Compression successful!\n");
            return 0;
        } else {
            printf("Compression failed with error code: %d\n", result);
            return 1;
        }
    } else if (strcmp(operation, "decompress") == 0) {
        printf("Decompressing %s -> %s\n", input_path, output_path);
        result = dfs_decompress_file(input_path, output_path);
        if (result == DFS_OK) {
            printf("Decompression successful!\n");
            return 0;
        } else {
            printf("Decompression failed with error code: %d\n", result);
            return 1;
        }
    } else {
        printf("Error: Unknown operation '%s'\n", operation);
        print_usage(argv[0]);
        return 1;
    }
}

