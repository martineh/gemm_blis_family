#include "microkernel.h"
// Macros for AVX2
    #define vregister __m256 
    #define vinit(vreg) vreg = _mm256_set1_ps(0); 
    #define vload(vreg, mem)  vreg = _mm256_loadu_ps(mem) 
    #define vstore(mem, vreg) _mm256_storeu_ps(mem, vreg) 
    #define vupdate(vreg1, vreg2, vreg3, j) { vreg1 = _mm256_fmadd_ps(vreg2, _mm256_set1_ps(vreg3[j]), vreg1); } 
    #define Ccol(a1,a2)  C[(a2) * (ldC) + (a1)] 
    #define Crow(a1,a2)  C[(a1) * (ldC) + (a2)] 
    #define Ctcol(a1,a2) Ctmp[(a2) * (ldCt) + (a1)] 
    #define Ctrow(a1,a2) Ctmp[(a1) * (ldCt) + (a2)] 
    #define Ctref(a1,a2) Ctmp[(a2) * (ldCt) + (a1)] 
    #define FUNROLL 1
    #define LOOP_BODY \
{\
    vload(ar0, Aptr + baseA + 0);\
    vload(ar1, Aptr + baseA + 8);\
    vload(br0, Bptr + baseB + 0);\
    vupdate(Cr0_0, ar0, br0, 0);\
    vupdate(Cr0_1, ar0, br0, 1);\
    vupdate(Cr0_2, ar0, br0, 2);\
    vupdate(Cr0_3, ar0, br0, 3);\
    vupdate(Cr0_4, ar0, br0, 4);\
    vupdate(Cr1_0, ar1, br0, 0);\
    vupdate(Cr1_1, ar1, br0, 1);\
    vupdate(Cr1_2, ar1, br0, 2);\
    vupdate(Cr1_3, ar1, br0, 3);\
    vupdate(Cr1_4, ar1, br0, 4);\
    baseA += Amr; baseB += Bnr;\
} 

inline void gemm_ukernel_Cresident_SIMD(int mr, int nr, int kc, DTYPE *Ar, int ldA, DTYPE *Br, int ldB, DTYPE *C, int ldC, char orderC, DTYPE beta) {
// mr x nr = 16 x 5 micro-kernel and C resident in regs.
// Inputs:
//   - C stored in column-major order, with leading dimension ldC
//   - Ar packed by columns, with leading dimension mr = 16
//   - Br packed by rows, with leading dimension nr = 5

  if (kc == 0) return;
  int       i, j, pr, baseA = 0, baseB = 0, ldCt = MR, Amr, Bnr;
  vregister Cr0_0, Cr0_1, Cr0_2, Cr0_3, Cr0_4, 
            Cr1_0, Cr1_1, Cr1_2, Cr1_3, Cr1_4, 
            A0_0, A0_1, A0_2, A0_3, A0_4, 
            A1_0, A1_1, A1_2, A1_3, A1_4;
  vregister ar0, ar1, br0; 
  DTYPE zero = 0.0, one = 1.0, Ctmp[MR * NR], *Aptr, *Bptr; 


  vinit(Cr0_0); vinit(Cr0_1); vinit(Cr0_2); vinit(Cr0_3); vinit(Cr0_4); 
  vinit(Cr1_0); vinit(Cr1_1); vinit(Cr1_2); vinit(Cr1_3); vinit(Cr1_4); 
  vinit(ar0); vinit(ar1); 
  vinit(br0); 
  if (orderC == 'C') { 
    Aptr = &Ar[0]; 
    Bptr = &Br[0]; 
    Amr  = MR; 
    Bnr  = NR; 
  } else { 
    Aptr = &Br[0]; 
    Bptr = &Ar[0]; 
    Amr  = NR; 
    Bnr  = MR; 
  } 
  int it = kc % FUNROLL;
    for (pr = 0; pr < it; pr++) { 
      LOOP_BODY; 
    } 
    for (pr = it; pr < kc; pr += FUNROLL) { 
    LOOP_BODY;
    } 
  if ((mr < MR) || (nr < NR)) {
  vstore(&Ctref(0, 0), Cr0_0); 
  vstore(&Ctref(0, 1), Cr0_1); 
  vstore(&Ctref(0, 2), Cr0_2); 
  vstore(&Ctref(0, 3), Cr0_3); 
  vstore(&Ctref(0, 4), Cr0_4); 
  vstore(&Ctref(8, 0), Cr1_0); 
  vstore(&Ctref(8, 1), Cr1_1); 
  vstore(&Ctref(8, 2), Cr1_2); 
  vstore(&Ctref(8, 3), Cr1_3); 
  vstore(&Ctref(8, 4), Cr1_4); 

    if (beta != zero) { 
      for (j = 0; j < nr; j++) 
        for (i = 0; i < mr; i++) 
          Ccol(i,j) = beta * Ccol(i,j) + Ctcol(i,j); 
    } else { 
      for (j = 0; j < nr; j++) 
        for (i = 0; i < mr; i++) 
          Ccol(i,j) = Ctcol(i,j); 
    } 
  } else if ((mr == MR) && (nr == NR)) { 
  if ( beta != zero ) {
    vload(A0_0, &Ccol(0, 0));
    vload(A0_1, &Ccol(0, 1));
    vload(A0_2, &Ccol(0, 2));
    vload(A0_3, &Ccol(0, 3));
    vload(A0_4, &Ccol(0, 4));
    vload(A1_0, &Ccol(8, 0));
    vload(A1_1, &Ccol(8, 1));
    vload(A1_2, &Ccol(8, 2));
    vload(A1_3, &Ccol(8, 3));
    vload(A1_4, &Ccol(8, 4));
    Cr0_0 += beta * A0_0; 
    Cr0_1 += beta * A0_1; 
    Cr0_2 += beta * A0_2; 
    Cr0_3 += beta * A0_3; 
    Cr0_4 += beta * A0_4; 

    Cr1_0 += beta * A1_0; 
    Cr1_1 += beta * A1_1; 
    Cr1_2 += beta * A1_2; 
    Cr1_3 += beta * A1_3; 
    Cr1_4 += beta * A1_4; 

  }
  // Store the micro-tile in memory
  vstore(&Ccol(0,0), Cr0_0);
  vstore(&Ccol(0,1), Cr0_1);
  vstore(&Ccol(0,2), Cr0_2);
  vstore(&Ccol(0,3), Cr0_3);
  vstore(&Ccol(0,4), Cr0_4);
  vstore(&Ccol(8,0), Cr1_0);
  vstore(&Ccol(8,1), Cr1_1);
  vstore(&Ccol(8,2), Cr1_2);
  vstore(&Ccol(8,3), Cr1_3);
  vstore(&Ccol(8,4), Cr1_4);
    } 
}