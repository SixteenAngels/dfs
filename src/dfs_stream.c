// dfs_stream.c
#include "dfs_stream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dfs_stream_t* dfs_stream_open(const char* path, const char* mode) {
    dfs_stream_t* s = (dfs_stream_t*)malloc(sizeof(dfs_stream_t));
    if (!s) return NULL;

    s->file = fopen(path, mode);
    s->is_memory = 0;
    s->buffer = NULL;
    s->size = 0;
    s->pos = 0;

    if (!s->file) {
        free(s);
        return NULL;
    }

    return s;
}

dfs_stream_t* dfs_stream_open_memory(uint8_t* buffer, size_t size) {
    dfs_stream_t* s = (dfs_stream_t*)malloc(sizeof(dfs_stream_t));
    if (!s) return NULL;

    s->is_memory = 1;
    s->buffer = buffer;
    s->size = size;
    s->pos = 0;
    s->file = NULL;

    return s;
}

size_t dfs_stream_read(dfs_stream_t* s, void* dest, size_t bytes) {
    if (!s) return 0;
    if (s->is_memory) {
        size_t available = s->size - s->pos;
        size_t to_read = bytes < available ? bytes : available;
        memcpy(dest, s->buffer + s->pos, to_read);
        s->pos += to_read;
        return to_read;
    } else {
        return fread(dest, 1, bytes, s->file);
    }
}

size_t dfs_stream_write(dfs_stream_t* s, const void* src, size_t bytes) {
    if (!s) return 0;
    if (s->is_memory) {
        size_t available = s->size - s->pos;
        size_t to_write = bytes < available ? bytes : available;
        memcpy(s->buffer + s->pos, src, to_write);
        s->pos += to_write;
        return to_write;
    } else {
        return fwrite(src, 1, bytes, s->file);
    }
}

void dfs_stream_close(dfs_stream_t* s) {
    if (!s) return;
    if (s->file) fclose(s->file);
    free(s);
}
