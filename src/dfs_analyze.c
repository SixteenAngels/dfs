#include "dfs_analyze.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Simple histogram-based byte frequency analysis
void dfs_analyze_frequency(const uint8_t* data, size_t size, dfs_histogram_t* hist) {
    if (!data || !hist) return;

    memset(hist->frequency, 0, sizeof(hist->frequency));

    for (size_t i = 0; i < size; ++i) {
        hist->frequency[data[i]]++;
    }
}

// Print byte frequency distribution
void dfs_analyze_print_histogram(const dfs_histogram_t* hist) {
    if (!hist) return;

    printf("Byte Frequency Histogram:\n");
    for (int i = 0; i < 256; ++i) {
        if (hist->frequency[i] > 0) {
            printf("0x%02X: %zu\n", i, hist->frequency[i]);
        }
    }
}
