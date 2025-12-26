// dfs_error.h
#ifndef DFS_ERROR_H
#define DFS_ERROR_H

#include "dfs_types.h"
#include "dfs.h"

#ifdef __cplusplus
extern "C" {
#endif

const char* dfs_strerror(dfs_status_t code);
void dfs_perror(const char* prefix, dfs_status_t code);

#ifdef __cplusplus
}
#endif

#endif // DFS_ERROR_H
