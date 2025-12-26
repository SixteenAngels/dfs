// dfs_decompress.h
#ifndef DFS_DECOMPRESS_H
#define DFS_DECOMPRESS_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "dfs.h"
#include "dfs_types.h"
#include "dfs_config.h"
#include "dfs_error.h"
#include "dfs_utils.h"
#include "dfs_dict.h"
#include "dfs_stream.h"
#include "dfs_block.h"
#include "dfs_cache.h"
#include "dfs_logger.h"

/**
 * Core in-memory decompression routine
 *
 * @param input         Pointer to compressed data
 * @param input_size    Size of compressed data in bytes
 * @param output        Pointer to output buffer
 * @param output_size   Pointer to size of output buffer; updated with actual size
 * @return dfs_status_t Result of the operation
 */
dfs_status_t dfs_decompress_buffer(const uint8_t* input, size_t input_size,
                                   uint8_t* output, size_t* output_size);


/**
 * Decompress a DFS file (.wsm format) from disk
 *
 * @param input_path    Path to the compressed input file
 * @param output_path   Path to the decompressed output file
 * @return dfs_status_t Result of the operation
 */
dfs_status_t dfs_decompress_file(const char* input_path, const char* output_path);


/**
 * Initialize internal state for streamed or multiblock decompression.
 * This allows decompression of very large files block-by-block.
 *
 * @return dfs_status_t Initialization status
 */
dfs_status_t dfs_decompress_init(void);


/**
 * Clean up internal memory/state used during decompression
 */
void dfs_decompress_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif // DFS_DECOMPRESS_H
