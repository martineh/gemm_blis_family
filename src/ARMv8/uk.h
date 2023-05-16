
#pragma once
#ifndef UK_H
#define UK_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>

// Compiler feature macros adapted from Hedley (public domain)
// https://github.com/nemequ/hedley

#if defined(__has_builtin)
#  define EXO_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#  define EXO_HAS_BUILTIN(builtin) (0)
#endif

#if EXO_HAS_BUILTIN(__builtin_assume)
#  define EXO_ASSUME(expr) __builtin_assume(expr)
#elif EXO_HAS_BUILTIN(__builtin_unreachable)
#  define EXO_ASSUME(expr) \
      ((void)((expr) ? 1 : (__builtin_unreachable(), 1)))
#else
#  define EXO_ASSUME(expr) ((void)(expr))
#endif


struct exo_win_1f32{
    float * const data;
    const int_fast32_t strides[1];
};
struct exo_win_1f32c{
    const float * const data;
    const int_fast32_t strides[1];
};

struct exo_win_2f32{
    float * const data;
    const int_fast32_t strides[2];
};
/*
struct exo_win_1f16{
	    __fp16 * const data;
	        const int_fast32_t strides[1];
};
struct exo_win_1f16c{
	    const __fp16 * const data;
	        const int_fast32_t strides[1];
};
struct exo_win_2f16{
	    __fp16 * const data;
	        const int_fast32_t strides[2];
};

void uk_wind_16x24_a1True_b1True( void *ctxt, int_fast32_t KC, const __fp16* alpha, const __fp16* A, const __fp16* B, const __fp16* beta, struct exo_win_2f16 C );
*/

// example_sgemm_a1True_b1False(
//     KC : size,
//     alpha : f32[1] @DRAM,
//     A : f32[KC, 8] @DRAM,
//     B : f32[KC, 12] @DRAM,
//     beta : f32[1] @DRAM,
//     C : f32[12, 8] @DRAM
// )
void example_sgemm_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );

// example_sgemm_a1True_b1True(
//     KC : size,
//     alpha : f32[1] @DRAM,
//     A : f32[KC, 8] @DRAM,
//     B : f32[KC, 12] @DRAM,
//     beta : f32[1] @DRAM,
//     C : f32[12, 8] @DRAM
// )
void example_sgemm_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );

// uk_8x12_a1True_b1False(
//     KC : size,
//     alpha : f32[1] @DRAM,
//     A : f32[KC, 8] @DRAM,
//     B : f32[KC, 12] @DRAM,
//     beta : f32[1] @DRAM,
//     C : f32[12, 8] @DRAM
// )
void uk_8x12_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );
void uk_24x4_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );
void uk_16x4_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );
void uk_wind_8x12_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta,  struct exo_win_2f32 C );
void uk_8x8_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );
void uk_8x4_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );
void uk_8x4_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );
void uk_4x12_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );
void uk_4x8_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );
void uk_4x4_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );
void uk_1xX_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );

// uk_8x12_a1True_b1True(
//     KC : size,
//     alpha : f32[1] @DRAM,
//     A : f32[KC, 8] @DRAM,
//     B : f32[KC, 12] @DRAM,
//     beta : f32[1] @DRAM,
//     C : f32[12, 8] @DRAM
// )
void uk_8x12_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C );



#ifdef __cplusplus
}
#endif
#endif  // UK_H
