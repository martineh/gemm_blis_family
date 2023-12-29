
#include <stdio.h>
#include <stdlib.h>

#include "gemm_ukernel_headers.h"

void gemm_ukernel_edge_4x4(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_4x8(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_4x8(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_4x12(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 4) && (nr <= 8))
      gemm_ukernel_asm_edge_4x8(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_4x12(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_4x16(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 4) && (nr <= 8))
      gemm_ukernel_asm_edge_4x8(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 4) && (nr <= 12))
      gemm_ukernel_asm_edge_4x12(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_4x16(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_4x20(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 4) && (nr <= 8))
      gemm_ukernel_asm_edge_4x8(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 4) && (nr <= 12))
      gemm_ukernel_asm_edge_4x12(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 4) && (nr <= 16))
      gemm_ukernel_asm_edge_4x16(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_4x20(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_8x4(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_8x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_8x8(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 4) && (nr <= 8))
      gemm_ukernel_asm_edge_4x8(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_8x8(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_8x12(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 4) && (nr <= 8))
      gemm_ukernel_asm_edge_4x8(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 4) && (nr <= 12))
      gemm_ukernel_asm_edge_4x12(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_8x12(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_12x4(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 8) && (nr <= 4))
      gemm_ukernel_asm_edge_8x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_12x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_12x8(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 4) && (nr <= 8))
      gemm_ukernel_asm_edge_4x8(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 8) && (nr <= 4))
      gemm_ukernel_asm_edge_8x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 8) && (nr <= 8))
      gemm_ukernel_asm_edge_8x8(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_12x8(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_16x4(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 8) && (nr <= 4))
      gemm_ukernel_asm_edge_8x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 12) && (nr <= 4))
      gemm_ukernel_asm_edge_12x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_16x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
void gemm_ukernel_edge_20x4(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha,                  
                           float *a, float *b, float *beta, float *ctmp,                  
                           float *C, size_t ldC) {
    int i, j;
    if ((mr <= 4) && (nr <= 4))
      gemm_ukernel_asm_edge_4x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 8) && (nr <= 4))
      gemm_ukernel_asm_edge_8x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 12) && (nr <= 4))
      gemm_ukernel_asm_edge_12x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else if ((mr <= 16) && (nr <= 4))
      gemm_ukernel_asm_edge_16x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));
    else
      gemm_ukernel_asm_edge_20x4(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));

    for (j = 0; j < nr; j++)
      for (i = 0; i < mr; i++)
        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];
}
