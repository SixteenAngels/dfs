// dfs_plugin.h
#ifndef DFS_PLUGIN_H
#define DFS_PLUGIN_H

#include "dfs_types.h"

typedef int (*dfs_plugin_compress_fn)(const byte*, size_t, byte*, size_t*);
typedef int (*dfs_plugin_decompress_fn)(const byte*, size_t, byte*, size_t*);

typedef struct {
    const char* name;
    dfs_plugin_compress_fn compress;
    dfs_plugin_decompress_fn decompress;
} dfs_plugin_t;

int dfs_register_plugin(dfs_plugin_t* plugin);
int dfs_unregister_plugin(const char* name);

#endif // DFS_PLUGIN_H
