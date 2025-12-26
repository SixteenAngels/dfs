// dfs_dict.c
#include "dfs_dict.h"
#include <string.h>
#include <stdlib.h>

#define DFS_DICT_INIT_SIZE 4096
#define DFS_DICT_MAX_SIZE 65536

dfs_dict_t* dfs_dict_create(void) {
    dfs_dict_t* dict = (dfs_dict_t*)malloc(sizeof(dfs_dict_t));
    if (!dict) return NULL;

    dict->capacity = DFS_DICT_INIT_SIZE;
    dict->size = 0;
    dict->entries = (dfs_token_t*)calloc(dict->capacity, sizeof(dfs_token_t));

    return dict;
}

void dfs_dict_free(dfs_dict_t* dict) {
    if (dict) {
        free(dict->entries);
        free(dict);
    }
}

int dfs_dict_insert(dfs_dict_t* dict, const uint8_t* data, size_t length, uint16_t* out_index) {
    if (!dict || !data || length == 0 || dict->size >= DFS_DICT_MAX_SIZE) return -1;

    for (uint16_t i = 0; i < dict->size; ++i) {
        if (dict->entries[i].length == length &&
            memcmp(dict->entries[i].data, data, length) == 0) {
            if (out_index) *out_index = i;
            return 0; // already exists
        }
    }

    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        dfs_token_t* new_entries = (dfs_token_t*)realloc(dict->entries, new_capacity * sizeof(dfs_token_t));
        if (!new_entries) return -1;

        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    dfs_token_t* entry = &dict->entries[dict->size];
    entry->length = length > DFS_TOKEN_MAX_LENGTH ? DFS_TOKEN_MAX_LENGTH : length;
    memcpy(entry->data, data, entry->length);

    if (out_index) *out_index = dict->size;
    dict->size++;

    return 1; // new entry inserted
}
