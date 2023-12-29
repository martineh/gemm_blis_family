/* 
   GEMM FLAVOURS

   -----

   GEMM FLAVOURS is a family of algorithms for matrix multiplication based
   on the BLIS approach for this operation: https://github.com/flame/blis

   -----

   This program is free software: you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free Software
   Foundation, either version 3 of the License, or (at your option) any later
   version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
   You should have received a copy of the GNU General Public License along with
   this program. If not, see <http://www.gnu.org/licenses/>.

   -----

   author    = "Enrique S. Quintana-Orti"
   contact   = "quintana@disca.upv.es"
   copyright = "Copyright 2021, Universitat Politecnica de Valencia"
   license   = "GPLv3"
   status    = "Production"
   version   = "1.1"
*/

#include "gemm_blis.h"

#include <iostream>
#include <cassert>
#include <arm_neon.h>

#define vl_fp32 4
#define vregister float32x4_t 
#define vinit(vreg)                     vreg = vmovq_n_f32(0)
#define vload(vreg, mem)                vreg = vld1q_f32(mem) 
#define vstore(mem, vreg)               vst1q_f32(mem, vreg) 
#define vupdate(vreg1, vreg2, vreg3, j) vreg1 = vfmaq_laneq_f32(vreg1, vreg2, vreg3, j) 

// vloadC templates to unroll mr/nr loops to load of micro-tile of C
template<int i, int j, int k, int l, typename T>
void vloadC_nr(vregister *Cr, T *C, T beta) {
  if constexpr (j == 0) return;
  else { 
    vloadC_nr<i, j-1, k, l>(Cr, C, beta);
    if (beta == 1.0)
      vload(*(Cr + (j - 1) * k + i), C + (j - 1) * vl_fp32);
    else
      vinit(*(Cr + (j - 1) * k + i));
  }
}
         
template<int i, int j, int k, int l, typename T>
void vloadC_mv_nr(vregister *Cr, T *C, int ldC, T beta) {
  if constexpr (i == 0) return;
  else { vloadC_mv_nr<i-1, j, k, l>(Cr, C, ldC, beta);
         vloadC_nr<i-1, j, k, l>(Cr, &C[(i - 1) * ldC], beta); }}
         
// vload template to unroll mv/nv loops to load of Ar/Br into vregs
template<int i, int j, typename T>
void vload_(vregister *ar, T *Ar) {
  if constexpr (i == 0) return;
  else { vload_<i-1, j>(ar, Ar);
         vload(*(ar + i - 1), Ar + (i - 1) * j); }}
         
// vupdate templates to unroll mv/nv/vl loops to load Ar/Br into vregs
template<int i>
void vupdate_vl(vregister *Cr, vregister ar, vregister br) {
  if constexpr (i == 0) return;
  else { vupdate_vl<i-1>(Cr, ar, br);
         vupdate(*(Cr + i - 1), ar, br, i - 1); }}
         
template<int i, int j>
void vupdate_vl_nv(vregister *Cr, vregister ar, vregister *br) {
  if constexpr (i == 0) return;
  else { vupdate_vl_nv<i-1, j>(Cr, ar, br);
         vupdate_vl<j>((Cr + (i - 1) * j), ar, *(br + i - 1)); }}
         
template<int i, int j, int k, int nr>
void vupdate_vl_nv_mv(vregister*Cr, vregister*ar, vregister*br){
  if constexpr (i == 0) return;
  else { vupdate_vl_nv_mv<i-1, j, k, nr>(Cr, ar, br);
         vupdate_vl_nv<j, k>((Cr + (i - 1) * nr), *(ar + i - 1), br);}}

// vstoreC templates to unroll mr/nr loops to store of micro-tile of C
template<int i, int j, int k, int l, typename T>
void vstoreC_mv(T *C, vregister *Cr) {
  if constexpr (j == 0) return;
  else { vstoreC_mv<i, j-1, k, l>(C, Cr);
         vstore(C + (j - 1) * vl_fp32, *(Cr + (j - 1) * k + i)); }}
         
template<int i, int j, int k, int l, typename T>
void vstoreC_mv_nr(T *C, vregister *Cr, int ldC) {
  if constexpr (i == 0) return;
  else { vstoreC_mv_nr<i-1, j, k, l>(C, Cr, ldC);
         vstoreC_mv<i-1, j, k, l>(&C[(i - 1) * ldC], Cr); }}


template<int mr, int nr, typename T>
void gemm_ukernel_generic_intrinsics_mrxnr(int kc, T beta, T *Ar, T *Br, T *C, int ldC) {
  // mr x nr micro-kernel with C resident in regs.

  constexpr int mv = mr / vl_fp32, nv = nr / vl_fp32;
  int iv, j, jv, pr, baseA = 0, baseB = 0;
  vregister Cr[mv * nr],    // Macro-tile of C
            ar[mv], br[nv]; // Single column/row of Ar/Br

  // Load the micro-tile of C if beta==1.0 into vector registers
  vloadC_mv_nr<nr, mv, nr, vl_fp32>(Cr, C, ldC, beta);

  for (pr=0; pr<kc; pr++) {
     // Load the pr-th column/row of Ar/Br into vector registers
     vload_<mv, vl_fp32>(ar, &Ar[baseA]); baseA += mr; 
     vload_<nv, vl_fp32>(br, &Br[baseB]); baseB += nr;

     // Update micro-tile with AXPYs
     vupdate_vl_nv_mv<mv, nv, vl_fp32, nr>(Cr, ar, br); 
  }
  
  // Store the micro-tile in memory
  vstoreC_mv_nr<nr, mv, nr, vl_fp32>(C, Cr, ldC);
}

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

void gemm_blis_B3A2C0( char orderA, char orderB, char orderC,
                       char transA, char transB, 
                       size_t m, size_t n, size_t k, 
                       DTYPE alpha, DTYPE *A, size_t ldA, 
		                    DTYPE *B, size_t ldB, 
		       DTYPE beta,  DTYPE *C, size_t ldC, 
		       DTYPE *Ac, DTYPE *Bc, 
                       size_t MC, size_t NC, size_t KC, float * Ctmp, 
		       ukernel_asm ukr, ukernel_edge ukr_edge) {
  size_t    ic, jc, pc, mc, nc, kc, ir, jr, mr, nr, j, i; 
  DTYPE  zero = 0.0, one = 1.0, betaI; 
  DTYPE  *Aptr, *Bptr, *Cptr;


  // Quick return if possible
  if ( (m==0)||(n==0)||(((alpha==zero)||(k==0))&&(beta==one)) )
    return;
  
  #include "quick_gemm.h"
  
  for ( jc=0; jc<n; jc+=NC ) {
    nc = min(n-jc, NC); 

    for ( pc=0; pc<k; pc+=KC ) {
      kc = min(k-pc, KC); 
      
      if ( (transB=='N')&&(orderB=='C') )
        Bptr = &Bcol(pc,jc);
      else if ( (transB=='N')&&(orderB=='R') )
        Bptr = &Brow(pc,jc);
      else if ( (transB=='T')&&(orderB=='C') )
        Bptr = &Bcol(jc,pc);
      else
        Bptr = &Brow(jc,pc);
      
      pack_CB( orderB, transB, kc, nc, Bptr, ldB, Bc, NR);
      
      if ( pc==0 )
        betaI = beta;
      else
        betaI = one;
      
      for ( ic=0; ic<m; ic+=MC ) {
        mc = min(m-ic, MC); 
	
        if ( (transA=='N')&&(orderA=='C') ){
          Aptr = &Acol(ic, pc);
	}else if ( (transA=='N')&&(orderA=='R') ){
          Aptr = &Arow(ic, pc);
	}else if ( (transA=='T')&&(orderA=='C') ){
          Aptr = &Acol(pc, ic);
	}else{
          Aptr = &Arow(pc, ic);
	}
	
	//Comment or uncomment for packing or not
        pack_RB( orderA, transA, mc, kc, Aptr, ldA, Ac, MR);
	
        for ( jr=0; jr<nc; jr+=NR ) {
          nr = min(nc-jr, NR); 
	  
          for ( ir=0; ir<mc; ir+=MR ) {
            mr = min(mc-ir, MR); 
	    
            if ( orderC=='C' )
              Cptr = &Ccol(ic+ir,jc+jr);
	    else
              Cptr = &Crow(ic+ir,jc+jr);

	    if (mr == MR && nr == NR) {
	      //gemm_ukernel_generic_intrinsics_mrxnr<MR, NR, float>(kc, betaI, &Ac[ir*kc], &Bc[jr*kc], Cptr, ldC);
	      ukr(kc, &alpha, &Ac[ir*kc], &Bc[jr*kc], &betaI, Cptr, ldC * sizeof(float));
	    } else {
	      //gemm_ukernel_generic_intrinsics_mrxnr<MR, NR, float>(kc, 0.0, &Ac[ir*kc], &Bc[jr*kc], Ctmp, MR);
              //for (j = 0; j < nr; j++)
                //for (i = 0; i < mr; i++)
                  //Cptr[j*ldC + i] = (betaI) * Cptr[j*ldC + i] + Ctmp[j * MR + i];
	      ukr_edge(mr, nr, MR, NR, kc, &alpha, &Ac[ir*kc], &Bc[jr*kc], &betaI, Ctmp, Cptr, ldC);
	    }

          }
        }
      }
    }
  }

 // free(Ctmp);

}


void pack_RB( char orderM, char transM, int mc, int nc, DTYPE *M, int ldM, DTYPE *Mc, int RR ){
/*
  BLIS pack for M-->Mc
*/
  int    i, j, ii, k, rr;

  if ( ((transM=='N')&&( orderM=='C'))||
       ((transM=='T')&&( orderM=='R')) ) {
    for ( i=0; i<mc; i+=RR ) { 
      k = i*nc;
      rr = min( mc-i, RR );
      
      for ( j=0; j<nc; j++ ) {
        for ( ii=0; ii<rr; ii++ ) {
	  Mc[k] = Mcol(i+ii, j);
          k++;
        } 
        k += (RR-rr);
      }
    }
  } else {
    for ( i=0; i<mc; i+=RR ) { 
      k = i*nc;
      rr = min( mc-i, RR );
      for ( j=0; j<nc; j++ ) {
        for ( ii=0; ii<rr; ii++ ) {
           Mc[k] = Mcol(j,i+ii);
          k++;
        }
        k += (RR-rr);
      }
    }
  }
}

void pack_CB( char orderM, char transM, int mc, int nc, DTYPE *M, int ldM, DTYPE *Mc, int RR ){
/*
  BLIS pack for M-->Mc
*/
  int    i, j, jj, k, nr;

  k = 0;
  if ( ((transM=='N')&&( orderM=='C'))||
       ((transM=='T')&&( orderM=='R')) )
    for ( j=0; j<nc; j+=RR ) { 
      k = j*mc;
      nr = min( nc-j, RR );
      for ( i=0; i<mc; i++ ) {
        for ( jj=0; jj<nr; jj++ ) {
          Mc[k] = Mcol(i,j+jj);
          k++;
        }
        k += (RR-nr);
      }
    }
  else
    for ( j=0; j<nc; j+=RR ) { 
      k = j*mc;
      nr = min( nc-j, RR );
      for ( i=0; i<mc; i++ ) {
        for ( jj=0; jj<nr; jj++ ) {
          Mc[k] = Mcol(j+jj,i);
          k++;
        }
        k += (RR-nr);
      }
    }
}

void unpack_RB( char orderM, char transM, int mc, int nc, DTYPE *M, int ldM, DTYPE *Mc, int RR ){
/*
  BLIS unpack for M-->Mc
*/
  int    i, j, ii, k, rr;

  if ( ((transM=='N')&&( orderM=='C'))||
       ((transM=='T')&&( orderM=='R')) ) {
    for ( i=0; i<mc; i+=RR ) { 
      k = i*nc;
      rr = min( mc-i, RR );
      for ( j=0; j<nc; j++ ) {
        for ( ii=0; ii<rr; ii++ ) {
          Mcol(i+ii,j) = Mc[k];
          k++;
        }
        k += (RR-rr);
      }
    }
  } else {
    for ( i=0; i<mc; i+=RR ) { 
      k = i*nc;
      rr = min( mc-i, RR );
      for ( j=0; j<nc; j++ ) {
        for ( ii=0; ii<rr; ii++ ) {
          Mcol(j,i+ii) = Mc[k];
          k++;
        }
        k += (RR-rr);
      }
    }
  }
}

void unpack_CB( char orderM, char transM, int mc, int nc, DTYPE *M, int ldM, DTYPE *Mc, int RR ){
/*
  BLIS unpack for M-->Mc
*/
  int    i, j, jj, k, nr;

  k = 0;
  if ( ((transM=='N')&&( orderM=='C'))||
       ((transM=='T')&&( orderM=='R')) )
    for ( j=0; j<nc; j+=RR ) { 
      k = j*mc;
      nr = min( nc-j, RR );
      for ( i=0; i<mc; i++ ) {
        for ( jj=0; jj<nr; jj++ ) {
          Mcol(i,j+jj) = Mc[k];
          k++;
        }
        k += (RR-nr);
      }
    }
  else
    for ( j=0; j<nc; j+=RR ) { 
      k = j*mc;
      nr = min( nc-j, RR );
      for ( i=0; i<mc; i++ ) {
        for ( jj=0; jj<nr; jj++ ) {
          Mcol(j+jj,i) = Mc[k];
          k++;
        }
        k += (RR-nr);
      }
    }
}

void gemm_base_Cresident( char orderC, int m, int n, int k, 
                          DTYPE alpha, DTYPE *A, int ldA, 
                                       DTYPE *B, int ldB, 
                          DTYPE beta,  DTYPE *C, int ldC ){
/*
  Baseline micro-kernel 
  Replace with specialized micro-kernel where C-->m x n is resident in registers
*/
  int    i, j, p;
  DTYPE  zero = 0.0, tmp;

  for ( j=0; j<n; j++ )
    for ( i=0; i<m; i++ ) {
      tmp = 0.0; 
      for ( p=0; p<k; p++ ) 
        tmp += Acol(i,p) * Brow(p,j);

      if ( beta==zero ) {
        if ( orderC=='C' )
          Ccol(i,j) = alpha*tmp;
        else
          Crow(i,j) = alpha*tmp;
      }
      else {
        if ( orderC=='C' )
          Ccol(i,j) = alpha*tmp + beta*Ccol(i,j);
        else
          Crow(i,j) = alpha*tmp + beta*Crow(i,j);
      }
    }
}

void gemm_base_ABresident( char orderA, char transM, 
                           int m, int n, int k, 
                           DTYPE alpha, DTYPE *A, int ldA, 
                                        DTYPE *B, int ldB, 
                           DTYPE beta,  DTYPE *C, int ldC ){
/*
  Baseline micro-kernel 
  Replace with specialized micro-kernel where A-->m x k is resident in registers
*/
  int    i, j, p;
  DTYPE  zero = 0.0, tmp;

  if ( transM=='N' ) {
    for ( j=0; j<n; j++ )
      for ( i=0; i<m; i++ ) {
        tmp = 0.0; 
        if ( orderA=='C' )
          for ( p=0; p<k; p++ ) 
            tmp += Acol(i,p) * Bcol(p,j);
        else
          for ( p=0; p<k; p++ ) 
            tmp += Arow(i,p) * Bcol(p,j);
  
        if (beta==zero)
          Ccol(i,j) = alpha*tmp;
        else
          Ccol(i,j) = alpha*tmp + beta*Ccol(i,j);
      }
  }
  else {
    for ( j=0; j<n; j++ )
      for ( i=0; i<m; i++ ) {
        tmp = 0.0; 
        if ( orderA=='C' )
          for ( p=0; p<k; p++ ) 
            tmp += Acol(p,i) * Bcol(p,j);
        else
          for ( p=0; p<k; p++ ) 
            tmp += Arow(p,i) * Bcol(p,j);
  
        if (beta==zero)
          Ccol(i,j) = alpha*tmp;
        else
          Ccol(i,j) = alpha*tmp + beta*Ccol(i,j);
      }
  }
}

