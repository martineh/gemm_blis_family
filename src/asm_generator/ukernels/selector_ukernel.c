
#include <stdio.h>
#include <stdlib.h>

#include "gemm_ukernel_headers.h"

void ukernels_selector(int MR, int NR, ukernel_asm *ukr, ukernel_edge *ukr_edge) {

  if (MR == 4 && NR == 4) {
    (*ukr)      = &gemm_ukernel_asm_4x4;
    (*ukr_edge) = &gemm_ukernel_edge_4x4;
  } else if (MR == 4 && NR == 8) {
    (*ukr)      = &gemm_ukernel_asm_4x8;
    (*ukr_edge) = &gemm_ukernel_edge_4x8;
  } else if (MR == 4 && NR == 12) {
    (*ukr)      = &gemm_ukernel_asm_4x12;
    (*ukr_edge) = &gemm_ukernel_edge_4x12;
  } else if (MR == 4 && NR == 16) {
    (*ukr)      = &gemm_ukernel_asm_4x16;
    (*ukr_edge) = &gemm_ukernel_edge_4x16;
  } else if (MR == 4 && NR == 20) {
    (*ukr)      = &gemm_ukernel_asm_4x20;
    (*ukr_edge) = &gemm_ukernel_edge_4x20;
  } else if (MR == 8 && NR == 4) {
    (*ukr)      = &gemm_ukernel_asm_8x4;
    (*ukr_edge) = &gemm_ukernel_edge_8x4;
  } else if (MR == 8 && NR == 8) {
    (*ukr)      = &gemm_ukernel_asm_8x8;
    (*ukr_edge) = &gemm_ukernel_edge_8x8;
  } else if (MR == 8 && NR == 12) {
    (*ukr)      = &gemm_ukernel_asm_8x12;
    (*ukr_edge) = &gemm_ukernel_edge_8x12;
  } else if (MR == 12 && NR == 4) {
    (*ukr)      = &gemm_ukernel_asm_12x4;
    (*ukr_edge) = &gemm_ukernel_edge_12x4;
  } else if (MR == 12 && NR == 8) {
    (*ukr)      = &gemm_ukernel_asm_12x8;
    (*ukr_edge) = &gemm_ukernel_edge_12x8;
  } else if (MR == 16 && NR == 4) {
    (*ukr)      = &gemm_ukernel_asm_16x4;
    (*ukr_edge) = &gemm_ukernel_edge_16x4;
  } else if (MR == 20 && NR == 4) {
    (*ukr)      = &gemm_ukernel_asm_20x4;
    (*ukr_edge) = &gemm_ukernel_edge_20x4;
  } else {
    (*ukr)      = NULL;
    (*ukr_edge) = NULL;
  }
}
