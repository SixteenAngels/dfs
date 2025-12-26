// dfs_dict.h
#ifndef DFS_DICT_H
#define DFS_DICT_H

#include "dfs_types.h"
#include "dfs_config.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DFS_DICT_TOKEN_LEN 4  // adjustable minimum token length

// Token structure
typedef struct {
    uint8_t data[DFS_TOKEN_MAX_LENGTH];
    size_t length;
} dfs_token_t;

// Dictionary structure
typedef struct {
    dfs_token_t* entries;
    size_t size;
    size_t capacity;
} dfs_dict_t;

// Create a new dictionary
dfs_dict_t* dfs_dict_create(void);

// Free a dictionary
void dfs_dict_free(dfs_dict_t* dict);

// Insert a token into the dictionary
int dfs_dict_insert(dfs_dict_t* dict, const uint8_t* data, size_t length, uint16_t* out_index);

// Initialize the dictionary
void dfs_dict_init();

// Add a token to the dictionary
bool dfs_dict_add(const byte* token, size_t length);

// Find a token in the dictionary and get its index
int dfs_dict_find(const byte* token, size_t length);

// Reset/clear the dictionary
void dfs_dict_reset();

#ifdef __cplusplus
}
#endif

#endif // DFS_DICT_H
