// dfs_simd.c
#include "dfs_simd.h"

#if defined(DFS_USE_SIMD)

#if defined(__SSE2__) || defined(_M_X64) || defined(_M_IX86)
    #include <emmintrin.h>  // SSE2
#elif defined(__ARM_NEON)
    #include <arm_neon.h>   // ARM NEON
#endif

#endif // DFS_USE_SIMD

#include <string.h>

int dfs_memcmp_simd(const void* a, const void* b, size_t len) {
#if defined(DFS_USE_SIMD)

    size_t i = 0;
#if defined(__SSE2__)
    const __m128i* pa = (const __m128i*)a;
    const __m128i* pb = (const __m128i*)b;

    while (i + 16 <= len) {
        __m128i va = _mm_loadu_si128(&pa[i / 16]);
        __m128i vb = _mm_loadu_si128(&pb[i / 16]);

        __m128i cmp = _mm_cmpeq_epi8(va, vb);
        int mask = _mm_movemask_epi8(cmp);
        if (mask != 0xFFFF) return 1;

        i += 16;
    }

#elif defined(__ARM_NEON)
    const uint8x16_t* pa = (const uint8x16_t*)a;
    const uint8x16_t* pb = (const uint8x16_t*)b;

    while (i + 16 <= len) {
        uint8x16_t va = vld1q_u8((const uint8_t*)pa + i);
        uint8x16_t vb = vld1q_u8((const uint8_t*)pb + i);
        uint8x16_t veq = vceqq_u8(va, vb);

        uint64x2_t p64 = vreinterpretq_u64_u8(veq);
        if (vgetq_lane_u64(p64, 0) != ~0ULL || vgetq_lane_u64(p64, 1) != ~0ULL)
            return 1;

        i += 16;
    }
#endif

    // Fallback to byte-wise comparison for remaining bytes
    const uint8_t* ba = (const uint8_t*)a;
    const uint8_t* bb = (const uint8_t*)b;
    for (; i < len; ++i) {
        if (ba[i] != bb[i]) return 1;
    }
    return 0;

#else
    // No SIMD: fallback to standard memcmp
    return memcmp(a, b, len);
#endif
}
