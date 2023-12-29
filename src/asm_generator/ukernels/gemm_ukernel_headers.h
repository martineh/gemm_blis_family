typedef void (*ukernel_asm)(size_t , float *, float *, float *, float *, float *, size_t );

typedef void (*ukernel_edge)(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void ukernels_selector(int _MR, int _NR, ukernel_asm *ukr, ukernel_edge *ukr_edge);

void gemm_ukernel_asm_4x4(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_4x4(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_4x4(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_4x8(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_4x8(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_4x8(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_4x12(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_4x12(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_4x12(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_4x16(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_4x16(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_4x16(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_4x20(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_4x20(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_4x20(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_8x4(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_8x4(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_8x4(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_8x8(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_8x8(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_8x8(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_8x12(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_8x12(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_8x12(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_12x4(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_12x4(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_12x4(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_12x8(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_12x8(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_12x8(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_16x4(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_16x4(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_16x4(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

void gemm_ukernel_asm_20x4(size_t , float *, float *, float *, float *, float *, size_t );

void gemm_ukernel_asm_edge_20x4(size_t , float *, float *, float *, size_t, float *, size_t );

void gemm_ukernel_edge_20x4(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, 
                            float *a, float *b, float *beta, float *ctmp, 
                            float *C, size_t ldC);

