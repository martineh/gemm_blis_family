#include <stdio.h>
#include <stdlib.h>

#include "dtypes.h"

#ifdef AVX2
  #include <immintrin.h>
  #include "AVX2/gemm_blis_amd_avx256_fp32.h"
#elif ARMv8
  #include <arm_neon.h>
  #include "ARMv8/gemm_blis_neon_fp32.h"
#endif

extern "C"      // Import C style functions
{
#include "asm_generator/ukernels/gemm_ukernel_headers.h"
}

#define Acol(a1,a2)  A[ (a2)*(ldA)+(a1) ]
#define Bcol(a1,a2)  B[ (a2)*(ldB)+(a1) ]
#define Ccol(a1,a2)  C[ (a2)*(ldC)+(a1) ]
#define Mcol(a1,a2)  M[ (a2)*(ldM)+(a1) ]

#define Arow(a1,a2)  A[ (a1)*(ldA)+(a2) ]
#define Brow(a1,a2)  B[ (a1)*(ldB)+(a2) ]
#define Crow(a1,a2)  C[ (a1)*(ldC)+(a2) ]
#define Mrow(a1,a2)  M[ (a1)*(ldM)+(a2) ]

void gemm_blis_B3A2C0( char, char, char, char, char, size_t, size_t, size_t, DTYPE, DTYPE *, size_t, DTYPE *, size_t, DTYPE, DTYPE *, size_t, 
		       DTYPE *, DTYPE *, size_t, size_t, size_t, float *, ukernel_asm, ukernel_edge);

void gemm_base_Cresident( char, int, int, int, DTYPE, DTYPE *, int, DTYPE *, int, DTYPE, DTYPE *, int );
void gemm_base_ABresident( char, char, int, int, int, DTYPE, DTYPE *, int, DTYPE *, int, DTYPE, DTYPE *, int );

void pack_RB( char, char, int, int, DTYPE *, int, DTYPE *, int );
void pack_CB( char, char, int, int, DTYPE *, int, DTYPE *, int );
void unpack_RB( char, char, int, int, DTYPE *, int, DTYPE *, int );
void unpack_CB( char, char, int, int, DTYPE *, int, DTYPE *, int );

//-----------------------------------------------------------------------------------
void pack_RB_v( char, char, int, int, DTYPE *, int, DTYPE *, int );
void pack_CB_v( char, char, int, int, DTYPE *, int, DTYPE *, int );
//-----------------------------------------------------------------------------------

