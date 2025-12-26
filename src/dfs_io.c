#include "dfs_io.h"
#include "dfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dfs_file_t* dfs_io_open(const char* path, const char* mode) {
    if (!path || !mode) return NULL;

    FILE* fp = fopen(path, mode);
    if (!fp) return NULL;

    dfs_file_t* file = (dfs_file_t*)malloc(sizeof(dfs_file_t));
    if (!file) {
        fclose(fp);
        return NULL;
    }

    file->fp = fp;
    return file;
}

void dfs_io_close(dfs_file_t* file) {
    if (file) {
        if (file->fp) fclose(file->fp);
        free(file);
    }
}

size_t dfs_io_read(void* buffer, size_t size, size_t count, dfs_file_t* file) {
    if (!file || !buffer) return 0;
    return fread(buffer, size, count, file->fp);
}

size_t dfs_io_write(const void* buffer, size_t size, size_t count, dfs_file_t* file) {
    if (!file || !buffer) return 0;
    return fwrite(buffer, size, count, file->fp);
}

long dfs_io_seek(dfs_file_t* file, long offset, int origin) {
    if (!file) return -1;
    return fseek(file->fp, offset, origin);
}

long dfs_io_tell(dfs_file_t* file) {
    if (!file) return -1;
    return ftell(file->fp);
}

int dfs_io_compress_file(const char* input_path, const char* output_path) {
    if (!input_path || !output_path) {
        return DFS_ERR_INVALID_INPUT;
    }

    FILE* in_file = fopen(input_path, "rb");
    if (!in_file) {
        return DFS_ERR_FILE_IO;
    }

    // Get file size
    fseek(in_file, 0, SEEK_END);
    long file_size = ftell(in_file);
    fseek(in_file, 0, SEEK_SET);

    if (file_size < 0) {
        fclose(in_file);
        return DFS_ERR_FILE_IO;
    }

    // Read input file
    uint8_t* input_data = (uint8_t*)malloc(file_size);
    if (!input_data) {
        fclose(in_file);
        return DFS_ERR_FILE_IO;
    }

    size_t read_size = fread(input_data, 1, file_size, in_file);
    fclose(in_file);

    if (read_size != (size_t)file_size) {
        free(input_data);
        return DFS_ERR_FILE_IO;
    }

    // Compress
    uint8_t* compressed = (uint8_t*)malloc(file_size * 2); // Allocate enough space
    if (!compressed) {
        free(input_data);
        return DFS_ERR_FILE_IO;
    }

    size_t compressed_size = file_size * 2;
    int status = dfs_compress(input_data, file_size, compressed, &compressed_size);
    free(input_data);

    if (status != DFS_OK) {
        free(compressed);
        return status;
    }

    // Write output file
    FILE* out_file = fopen(output_path, "wb");
    if (!out_file) {
        free(compressed);
        return DFS_ERR_FILE_IO;
    }

    size_t written = fwrite(compressed, 1, compressed_size, out_file);
    fclose(out_file);
    free(compressed);

    if (written != compressed_size) {
        return DFS_ERR_FILE_IO;
    }

    return DFS_OK;
}

int dfs_io_decompress_file(const char* input_path, const char* output_path) {
    if (!input_path || !output_path) {
        return DFS_ERR_INVALID_INPUT;
    }

    FILE* in_file = fopen(input_path, "rb");
    if (!in_file) {
        return DFS_ERR_FILE_IO;
    }

    // Get file size
    fseek(in_file, 0, SEEK_END);
    long file_size = ftell(in_file);
    fseek(in_file, 0, SEEK_SET);

    if (file_size < 0) {
        fclose(in_file);
        return DFS_ERR_FILE_IO;
    }

    // Read input file
    uint8_t* compressed = (uint8_t*)malloc(file_size);
    if (!compressed) {
        fclose(in_file);
        return DFS_ERR_FILE_IO;
    }

    size_t read_size = fread(compressed, 1, file_size, in_file);
    fclose(in_file);

    if (read_size != (size_t)file_size) {
        free(compressed);
        return DFS_ERR_FILE_IO;
    }

    // Decompress (allocate enough space, typically compressed is smaller)
    uint8_t* decompressed = (uint8_t*)malloc(file_size * 4); // Allocate enough space
    if (!decompressed) {
        free(compressed);
        return DFS_ERR_FILE_IO;
    }

    size_t decompressed_size = file_size * 4;
    int status = dfs_decompress(compressed, file_size, decompressed, &decompressed_size);
    free(compressed);

    if (status != DFS_OK) {
        free(decompressed);
        return status;
    }

    // Write output file
    FILE* out_file = fopen(output_path, "wb");
    if (!out_file) {
        free(decompressed);
        return DFS_ERR_FILE_IO;
    }

    size_t written = fwrite(decompressed, 1, decompressed_size, out_file);
    fclose(out_file);
    free(decompressed);

    if (written != decompressed_size) {
        return DFS_ERR_FILE_IO;
    }

    return DFS_OK;
}
