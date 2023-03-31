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

#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

//#include <arm_neon.h>
//#include <arm_sve.h>
//#include <riscv_vector.h>

#include "qblis.h"
#include "dtypes.h"
#include "gemm_blis.h"
#include "AMD/gemm_blis_amd_avx256_fp32.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define Acol(a1,a2)  A[ (a2)*(ldA)+(a1) ]
#define Bcol(a1,a2)  B[ (a2)*(ldB)+(a1) ]
#define Ccol(a1,a2)  C[ (a2)*(ldC)+(a1) ]
#define Mcol(a1,a2)  M[ (a2)*(ldM)+(a1) ]

#define Arow(a1,a2)  A[ (a1)*(ldA)+(a2) ]
#define Brow(a1,a2)  B[ (a1)*(ldB)+(a2) ]
#define Crow(a1,a2)  C[ (a1)*(ldC)+(a2) ]
#define Mrow(a1,a2)  M[ (a1)*(ldM)+(a2) ]

int print_matrix(char *, char, size_t, int, DTYPE *, size_t);


#if defined(MK_BLIS)
void gemm_blis_B3A2C0( char orderA, char orderB, char orderC,
                       char transA, char transB, 
                       size_t m, size_t n, size_t k, 
                       DTYPE alpha, DTYPE *A, size_t ldA, 
		                    DTYPE *B, size_t ldB, 
		       DTYPE beta,  DTYPE *C, size_t ldC, 
		       DTYPE *Ac, DTYPE *Bc, 
                       size_t MC, size_t NC, size_t KC,
		       cntx_t * cntx, auxinfo_t * aux, sgemm_ukr_ft gemm_kernel) {
#else
void gemm_blis_B3A2C0( char orderA, char orderB, char orderC,
                       char transA, char transB, 
                       size_t m, size_t n, size_t k, 
                       DTYPE alpha, DTYPE *A, size_t ldA, 
		                    DTYPE *B, size_t ldB, 
		       DTYPE beta,  DTYPE *C, size_t ldC, 
		       DTYPE *Ac, DTYPE *Bc, 
                       size_t MC, size_t NC, size_t KC ) {
#endif
  size_t    ic, jc, pc, mc, nc, kc, ir, jr, mr, nr; 
  DTYPE  zero = 0.0, one = 1.0, betaI; 
  DTYPE  *Aptr, *Bptr, *Cptr;

  #if defined(CHECK)
  #include "check_params.h"
  #endif
  
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
      //pack_CB_v( orderB, transB, kc, nc, Bptr, ldB, Bc, NR);
      
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
        //pack_RB_v( orderA, transA, mc, kc, Aptr, ldA, Ac, MR);
	
	//#pragma omp  parallel for private(nr, ir, mr, Cptr) firstprivate (Ac, Bc)   
        for ( jr=0; jr<nc; jr+=NR ) {
          nr = min(nc-jr, NR); 
	  
          for ( ir=0; ir<mc; ir+=MR ) {
            mr = min(mc-ir, MR); 
	    
            if ( orderC=='C' ) {
              Cptr = &Ccol(ic+ir,jc+jr);
              //uKernels Stored By [Columns]
	      gemm_microkernel_Cresident_AMD_avx256_2vx6_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC ); 
	      //gemm_microkernel_Cresident_AMD_avx256_3vx4_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC );
	      //bli_sgemm_haswell_asm_6x16(mr, nr, kc, &alpha, &Ac[ir*kc], &Bc[jr*kc], &betaI,  Cptr, 1, ldC, aux, cntx);
	    } else {
              Cptr = &Crow(ic+ir,jc+jr);
	      //uKernels Stored By [Rows]
	      //--------------+--------------------------------------------------------------------------------------------------------
	      //No packing A  |
	      //--------------+--------------------------------------------------------------------------------------------------------
	      //gemm_microkernel_Cresident_AMD_avx256_6x2v_nopack_unroll_fp32( orderC, mr, nr, kc, alpha, &Arow(ic + ir, pc), ldA, &Bc[jr*kc], betaI, Cptr, ldC ); 
	      //gemm_microkernel_Cresident_AMD_avx256_6x2v_nopack_fp32( orderC, mr, nr, kc, alpha, &Arow(ic + ir, pc), ldA, &Bc[jr*kc], betaI, Cptr, ldC ); 
	      //gemm_microkernel_Cresident_AMD_avx256_4x3v_nopack_fp32( orderC, mr, nr, kc, alpha, &Arow(ic + ir, pc), ldA, &Bc[jr*kc], betaI, Cptr, ldC ); 
              
	      //--------------+--------------------------------------------------------------------------------------------------------
	      //Packing A     |
              //--------------+--------------------------------------------------------------------------------------------------------
	      //gemm_microkernel_Cresident_AMD_avx256_6x2v_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC ); 
	      //gemm_microkernel_Cresident_AMD_avx256_4x3v_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC ); 
	      //gemm_kernel(mr, nr, kc, &alpha, &Ac[ir*kc], &Bc[jr*kc], &betaI,  Cptr, 1, ldC, aux, cntx);
	    }

            //#if defined(BASE)
	       //gemm_base_Cresident( orderC, mr, nr, kc, alpha, &Ac[ir*kc], MR, &Bc[jr*kc], NR, betaI, Cptr, ldC );
           //#elif defined(MK_BLIS)
               //gemm_kernel(mr, nr, kc, &alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, 1, ldC, aux, cntx);
            //#else
              //if(MR==mr && NR==nr ) {
                //gemm_microkernel_Cresident_AMD_avx256_mrxnr_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC );
              //} else {
		//--------------+--------------------------------------------------------------------------------------------------------
                //MR=8 x NR=n   |
		//--------------+
	        //gemm_microkernel_Cresident_AMD_avx256_8x8_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC );
	        //gemm_microkernel_Cresident_AMD_avx256_8x14_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC ); 
		//-----------------------------------------------------------------------------------------------------------------------
		
		//--------------+--------------------------------------------------------------------------------------------------------
                //MR=16 x NR=n  |
		//--------------+
	        //gemm_microkernel_Cresident_AMD_avx256_16x6_optimum_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC ); 
	        //gemm_microkernel_Cresident_AMD_avx256_16x6_BLIS_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC ); 
	        //gemm_microkernel_Cresident_AMD_avx256_6x16_BLIS_ROW_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC ); 
		//-----------------------------------------------------------------------------------------------------------------------
		
		//--------------+--------------------------------------------------------------------------------------------------------
                //MR=24 x NR=n  |
		//--------------+
	       // gemm_microkernel_Cresident_AMD_avx256_24x4_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC );
		//-----------------------------------------------------------------------------------------------------------------------
		
		//--------------+--------------------------------------------------------------------------------------------------------
                // MR=32 x NR=n |
		//--------------+--------------------------------------------------------------------------------------------------------
	        //gemm_microkernel_Cresident_AMD_avx256_32x2_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC );
		//-----------------------------------------------------------------------------------------------------------------------
		
		//--------------+--------------------------------------------------------------------------------------------------------
                // MR=40 x NR=n |
		//--------------+--------------------------------------------------------------------------------------------------------
	        //gemm_microkernel_Cresident_AMD_avx256_40x2_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC );
		//-----------------------------------------------------------------------------------------------------------------------
              //}
            //#endif
          }
	  
        }
      }
    }
  }
}


#if defined(MK_BLIS)
    void gemm_blis_A3B2C0( char orderA, char orderB, char orderC,
			   char transA, char transB, 
			   size_t m, size_t n, size_t k, 
			   DTYPE alpha, DTYPE *A, int ldA, 
			   DTYPE *B, size_t ldB, 
			   DTYPE beta,  DTYPE *C, size_t ldC, 
			   DTYPE *Ac, DTYPE *Bc, 
			   size_t MC, size_t NC, size_t KC,
			   cntx_t * cntx, auxinfo_t * aux, sgemm_ukr_ft gemm_kernel) {
#else
   void gemm_blis_A3B2C0( char orderA, char orderB, char orderC,
			  char transA, char transB, 
			  size_t m, size_t n, size_t k, 
			  DTYPE alpha, DTYPE *A, size_t ldA, 
			  DTYPE *B, size_t ldB, 
			  DTYPE beta,  DTYPE *C, size_t ldC, 
			  DTYPE *Ac, DTYPE *Bc, 
			  size_t MC, size_t NC, size_t KC ){
#endif
  /*size_t ic, jc, pc, mc, nc, kc, ir, jr, mr, nr; 
  DTYPE  betaI, zero = 0.0, one = 1.0; 
  DTYPE  *Aptr, *Bptr, *Cptr;
  #if defined(CHECK)
  #include "check_params.h"
  #endif

  // Quick return if possible
  if ( (m==0)||(n==0)||(((alpha==zero)||(k==0))&&(beta==one)) )
    return;

  #include "quick_gemm.h"

  for ( ic=0; ic<m; ic+=MC ) {
    mc = min(m-ic, MC); 

    for ( pc=0; pc<k; pc+=KC ) {
      kc = min(k-pc, KC); 

      if ( (transA=='N')&&(orderA=='C') )
        Aptr = &Acol(ic,pc);
      else if ( (transA=='N')&&(orderA=='R') )
        Aptr = &Arow(ic,pc);
      else if ( (transA=='T')&&(orderA=='C') )
        Aptr = &Acol(pc,ic);
      else
        Aptr = &Arow(pc,ic);
      pack_RB( orderA, transA, mc, kc, Aptr, ldA, Ac, MR);

      if ( pc==0 )
        betaI = beta;
      else
        betaI = one;

      for ( jc=0; jc<n; jc+=NC ) {
        nc = min(n-jc, NC); 

        if ( (transB=='N')&&(orderB=='C') )
          Bptr = &Bcol(pc,jc);
        else if ( (transB=='N')&&(orderB=='R') )
          Bptr = &Brow(pc,jc);
        else if ( (transB=='T')&&(orderB=='C') )
          Bptr = &Bcol(jc,pc);
        else
          Bptr = &Brow(jc,pc);
        pack_CB( orderB, transB, kc, nc, Bptr, ldB, Bc, NR);

        for ( ir=0; ir<mc; ir+=MR ) {
          mr = min(mc-ir, MR); 

          for ( jr=0; jr<nc; jr+=NR ) {
            nr = min(nc-jr, NR); 

            if ( orderC=='C' )
              Cptr = &Ccol(ic+ir,jc+jr);
            else
              Cptr = &Crow(ic+ir,jc+jr);

            #if defined(BASE)
	        gemm_base_Cresident( orderC, mr, nr, kc, alpha, &Ac[ir*kc], MR, &Bc[jr*kc], NR, betaI, Cptr, ldC );
            #elif defined(MK_BLIS)
		gemm_kernel(mr, nr, kc, &alpha, &Ac[ir*kc], &Bc[jr*kc], &betaI,  Cptr, 1, ldC, aux, cntx);
            #elif defined(MK_8x12)
		gemm_microkernel_Cresident_sve_8x12_fp32 (orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC);
            #elif defined(MK_16x12)
		gemm_microkernel_Cresident_sve_16x12_fp32(orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC);
            #elif defined(MK_32x10)
		//gemm_microkernel_Cresident_sve_32x10_v2_fp32(orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC);
		gemm_microkernel_Cresident_sve_32x10_fp32(orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC);
            #elif defined(MK_32x12)
		gemm_microkernel_Cresident_sve_32x12_fp32(orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC);
            #elif defined(MK_32x14)
		gemm_microkernel_Cresident_sve_32x14_fp32(orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC);
            #elif defined(MK_48x8)
		gemm_microkernel_Cresident_sve_48x8_fp32 (orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC);
            #elif defined(MK_64x8)
		gemm_microkernel_Cresident_sve_64x8_fp32 (orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC);
            #elif defined(MK_64x6)
		gemm_microkernel_Cresident_sve_64x6_fp32 (orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC);
            #elif defined(MK_80x4)
		gemm_microkernel_Cresident_sve_80x4_fp32 (orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC);
	    #else
		printf("Micro-kernel not implemented.\n");
		exit(-1);
            #endif
          }
        }
      }
    }
  }*/
}

void gemm_blis_B3C2A0( char orderA, char orderB, char orderC,
                       char transA, char transB, 
                       size_t m, size_t n, size_t k, 
                       DTYPE alpha, DTYPE *A, int ldA, 
		                    DTYPE *B, int ldB, 
		       DTYPE beta,  DTYPE *C, int ldC, 
		       DTYPE *Bc, DTYPE *Cc, 
                       int MC, int NC, int KC ){
  /*int    ic, jc, pc, mc, nc, kc, ir, pr, mr, kr; 
  DTYPE  zero = 0.0, one = 1.0, betaI, betaII; 
  DTYPE  *Aptr, *Bptr, *Cptr;
  #if defined(CHECK)
  #include "check_params.h"
  #endif

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
      pack_RB( orderB, transB, kc, nc, Bptr, ldB, Bc, NR);

      if ( pc==0 )
        betaI = beta;
      else
        betaI = one;

      for ( ic=0; ic<m; ic+=MC ) {
        mc = min(m-ic, MC); 

        if ( orderC=='C' )
          Cptr = &Ccol(ic,jc);
        else
          Cptr = &Crow(ic,jc);
        pack_RB( orderC, 'N', mc, nc, Cptr, ldC, Cc, MR);

        for ( pr=0; pr<kc; pr+=KR ) {
          kr = min(kc-pr, KR); 

          if ( pr==0 )
            betaII = betaI;
          else
            betaII = one;

          for ( ir=0; ir<mc; ir+=MR ) {
            mr = min(mc-ir, MR); 

            if ( (transA=='N')&&(orderA=='C') )
              Aptr = &Acol(ic+ir,pc+pr);
            else if ( (transA=='N')&&(orderA=='R') )
              Aptr = &Arow(ic+ir,pc+pr);
            else if ( (transA=='T')&&(orderA=='C') )
              Aptr = &Acol(pc+pr,ic+ir);
            else
              Aptr = &Arow(pc+pr,ic+ir);

            #if defined(MK_32x12) 
	        gemm_microkernel_ABresident_sve_32x12_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #elif defined(MK_48x8)
	        gemm_microkernel_ABresident_sve_48x8_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
	    #elif defined(MK_64x6)
	        gemm_microkernel_ABresident_sve_64x6_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #elif defined(MK_80x4)
	        gemm_microkernel_ABresident_sve_80x4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
	    #elif defined(MK_4x4)
	        gemm_microkernel_ABresident_sve_4x4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #elif defined(MK_16x4)
	        //gemm_microkernel_ABresident_sve_16x4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
	        //gemm_microkernel_ABresident_sve_16x4_unrollx2_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
	        gemm_microkernel_ABresident_sve_16x4_unrollx4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
	    #elif defined(MK_16x12)
	        gemm_microkernel_ABresident_sve_16x12_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #elif defined(MK_32x4)
	        gemm_microkernel_ABresident_sve_32x4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #elif defined(MK_48x4)
	        gemm_microkernel_ABresident_sve_48x4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #endif
          }
        }
        unpack_RB( orderC, 'N', mc, nc, Cptr, ldC, Cc, MR);
      }
    }
  }*/
}

void gemm_blis_C3B2A0( char orderA, char orderB, char orderC,
                       char transA, char transB, 
                       size_t m, size_t n, size_t k, 
                       DTYPE alpha, DTYPE *A, int ldA, 
		                    DTYPE *B, int ldB, 
		       DTYPE beta,  DTYPE *C, int ldC, 
		       DTYPE *Bc, DTYPE *Cc, 
                       int MC, int NC, int KC ){
  /*size_t    ic, jc, pc, mc, nc, kc, ir, pr, mr, kr; 
  DTYPE  zero = 0.0, one = 1.0, betaI, betaII; 
  DTYPE  *Aptr, *Bptr, *Cptr;
  #if defined(CHECK)
  #include "check_params.h"
  #endif

  // Quick return if possible
  if ( (m==0)||(n==0)||(((alpha==zero)||(k==0))&&(beta==one)) )
    return;

  #include "quick_gemm.h"

  for ( jc=0; jc<n; jc+=NC ) {
    nc = min(n-jc, NC); 

    for ( ic=0; ic<m; ic+=MC ) {
      mc = min(m-ic, MC); 

      if ( orderC=='C' )
        Cptr = &Ccol(ic,jc);
      else
        Cptr = &Crow(ic,jc);
      pack_RB( orderC, 'N', mc, nc, Cptr, ldC, Cc, MR);

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
        pack_RB( orderB, transB, kc, nc, Bptr, ldB, Bc, NR);

        if ( pc==0 )
          betaI = beta;
        else
          betaI = one;

        for ( ir=0; ir<mc; ir+=MR ) {
          mr = min(mc-ir, MR); 

          for ( pr=0; pr<kc; pr+=KR ) {
            kr = min(kc-pr, KR); 

            if ( pr==0 )
              betaII = betaI;
            else
              betaII = one;

            if ( (transA=='N')&&(orderA=='C') )
              Aptr = &Acol(ic+ir,pc+pr);
            else if ( (transA=='N')&&(orderA=='R') )
              Aptr = &Arow(ic+ir,pc+pr);
            else if ( (transA=='T')&&(orderA=='C') )
              Aptr = &Acol(pc+pr,ic+ir);
            else
              Aptr = &Arow(pc+pr,ic+ir);

            #if defined(MK_32x12)
	        gemm_microkernel_ABresident_sve_32x12_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #elif defined(MK_48x8)
	        gemm_microkernel_ABresident_sve_48x8_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
	    #elif defined(MK_64x6)
	        gemm_microkernel_ABresident_sve_64x6_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #elif defined(MK_80x4)
	        gemm_microkernel_ABresident_sve_80x4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
	    #elif defined(MK_4x4)
	        gemm_microkernel_ABresident_sve_4x4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #elif defined(MK_16x4)
	        //gemm_microkernel_ABresident_sve_16x4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
	        //gemm_microkernel_ABresident_sve_16x4_unrollx2_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
	        gemm_microkernel_ABresident_sve_16x4_unrollx4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
	    #elif defined(MK_16x12)
	        gemm_microkernel_ABresident_sve_16x12_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #elif defined(MK_32x4)
	        gemm_microkernel_ABresident_sve_32x4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #elif defined(MK_48x4)
	        gemm_microkernel_ABresident_sve_48x4_fp32( orderA, transA, mr, nc, kr, alpha, Aptr, ldA, &Bc[pr*nc], betaII, &Cc[ir*nc] );
            #endif

          }
        }
      }
      unpack_RB( orderC, 'N', mc, nc, Cptr, ldC, Cc, MR);
    }
  }*/
}

void gemm_blis_A3C2B0( char orderA, char orderB, char orderC,
                       char transA, char transB, 
                       int m, int n, int k, 
                       DTYPE alpha, DTYPE *A, int ldA, 
		                    DTYPE *B, int ldB, 
		       DTYPE beta,  DTYPE *C, int ldC, 
		       DTYPE *Ac, DTYPE *Cc, 
                       int MC, int NC, int KC ){
  /*int    ic, jc, pc, mc, nc, kc, jr, pr, nr, kr; 
  DTYPE  zero = 0.0, one = 1.0, betaI, betaII; 
  DTYPE  *Aptr, *Bptr, *Cptr;
  char   ttransB; 
  #if defined(CHECK)
  #include "check_params.h"
  #endif

  // Quick return if possible
  if ( (m==0)||(n==0)||(((alpha==zero)||(k==0))&&(beta==one)) )
    return;

  #include "quick_gemm.h"

  if ( transB=='N' )
    ttransB = 'T';
  else
    ttransB = 'N';

  for ( ic=0; ic<m; ic+=MC ) {
    mc = min(m-ic, MC); 

    for ( pc=0; pc<k; pc+=KC ) {
      kc = min(k-pc, KC); 

      if ( (transA=='N')&&(orderA=='C') )
        Aptr = &Acol(ic,pc);
      else if ( (transA=='N')&&(orderA=='R') )
        Aptr = &Arow(ic,pc);
      else if ( (transA=='T')&&(orderA=='C') )
        Aptr = &Acol(pc,ic);
      else
        Aptr = &Arow(pc,ic);
      pack_CB( orderA, transA, mc, kc, Aptr, ldA, Ac, KR);

      if ( pc==0 )
        betaI = beta;
      else
        betaI = one;

      for ( jc=0; jc<n; jc+=NC ) {
        nc = min(n-jc, NC); 

        if ( orderC=='C')
          Cptr = &Ccol(ic,jc);
        else 
          Cptr = &Crow(ic,jc);
        pack_CB( orderC, 'N', mc, nc, Cptr, ldC, Cc, NR);

        for ( pr=0; pr<kc; pr+=KR ) {
          kr = min(kc-pr, KR); 

          if ( pr==0 )
            betaII = betaI;
          else
            betaII = one;

          for ( jr=0; jr<nc; jr+=NR ) {
            nr = min(nc-jr, NR); 

            if ( (transB=='N')&&(orderB=='C') )
              Bptr = &Bcol(pc+pr,jc+jr);
            else if ( (transB=='N')&&(orderB=='R') )
              Bptr = &Brow(pc+pr,jc+jr);
            else if ( (transB=='T')&&(orderB=='C') )
              Bptr = &Bcol(jc+jr,pc+pr);
            else
              Bptr = &Brow(jc+jr,pc+pr);

	    //gemm_base_ABresident( orderB, ttransB, nr, mc, kr, alpha, Bptr, ldB, &Ac[pr*mc], KR, betaII, &Cc[jr*mc], NR );
	    //gemm_microkernel_ABresident_sve_4x4_fp32 ( orderB, ttransB, nr, mc, kr, alpha, Bptr, ldB, &Ac[pr*mc], betaII, &Cc[jr*mc] );
	    //gemm_microkernel_ABresident_sve_16x4_fp32( orderB, ttransB, nr, mc, kr, alpha, Bptr, ldB, &Ac[pr*mc], betaII, &Cc[jr*mc] );
	    //gemm_microkernel_ABresident_sve_64x6_fp32( orderB, ttransB, nr, mc, kr, alpha, Bptr, ldB, &Ac[pr*mc], betaII, &Cc[jr*mc] );
	    
          }
        }
        unpack_CB( orderC, 'N', mc, nc, Cptr, ldC, Cc, NR);
      }
    }
  }*/
}

void gemm_blis_C3A2B0( char orderA, char orderB, char orderC,
                       char transA, char transB, 
                       int m, int n, int k, 
                       DTYPE alpha, DTYPE *A, int ldA, 
		                    DTYPE *B, int ldB, 
		       DTYPE beta,  DTYPE *C, int ldC, 
		       DTYPE *Ac, DTYPE *Cc, 
                       int MC, int NC, int KC ){
  /*size_t    ic, jc, pc, mc, nc, kc, jr, pr, nr, kr; 
  DTYPE  zero = 0.0, one = 1.0, betaI, betaII; 
  DTYPE  *Aptr, *Bptr, *Cptr;
  char   ttransB;
  #if defined(CHECK)
  #include "check_params.h"
  #endif

  // Quick return if possible
  if ( (m==0)||(n==0)||(((alpha==zero)||(k==0))&&(beta==one)) )
    return;

  #include "quick_gemm.h"

  if ( transB=='N' )
    ttransB = 'T';
  else
    ttransB = 'N';

  for ( ic=0; ic<m; ic+=MC ) {
    mc = min(m-ic, MC); 

    for ( jc=0; jc<n; jc+=NC ) {
      nc = min(n-jc, NC); 

      if ( orderC=='C')
        Cptr = &Ccol(ic,jc);
      else 
        Cptr = &Crow(ic,jc);
      pack_CB( orderC, 'N', mc, nc, Cptr, ldC, Cc, NR);

      for ( pc=0; pc<k; pc+=KC ) {
        kc = min(k-pc, KC); 

        if ( (transA=='N')&&(orderA=='C') )
          Aptr = &Acol(ic,pc);
        else if ( (transA=='N')&&(orderA=='R') )
          Aptr = &Arow(ic,pc);
        else if ( (transA=='T')&&(orderA=='C') )
          Aptr = &Acol(pc,ic);
        else
          Aptr = &Arow(pc,ic);
        pack_CB( orderA, transA, mc, kc, Aptr, ldA, Ac, KR);

        if ( pc==0 )
          betaI = beta;
        else
          betaI = one;

        for ( jr=0; jr<nc; jr+=NR ) {
          nr = min(nc-jr, NR); 

          for ( pr=0; pr<kc; pr+=KR ) {
            kr = min(kc-pr, KR); 

            if ( pr==0 )
              betaII = betaI;
            else
              betaII = one;

            if ( (transB=='N')&&(orderB=='C') )
              Bptr = &Bcol(pc+pr,jc+jr);
            else if ( (transB=='N')&&(orderB=='R') )
              Bptr = &Brow(pc+pr,jc+jr);
            else if ( (transB=='T')&&(orderB=='C') )
              Bptr = &Bcol(jc+jr,pc+pr);
            else
              Bptr = &Brow(jc+jr,pc+pr);

	    //gemm_microkernel_Cresident_sve_64x6_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC );
	    //gemm_microkernel_Cresident_sve_48x8_fp32( orderC, mr, nr, kc, alpha, &Ac[ir*kc], &Bc[jr*kc], betaI, Cptr, ldC );
          }
        }
      }
      unpack_CB( orderC, 'N', mc, nc, Cptr, ldC, Cc, NR);
    }
  }*/
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

//------------------------------------------------------------------------------------
// Packings AVX2 Vectorized (AMD EPYC)
//------------------------------------------------------------------------------------
void pack_CB_v( char orderM, char transM, int mc, int nc, DTYPE *M, int ldM, DTYPE *Mc, int RR ){
  //AMD __mm256: Packing for NR=2v=16. Matrix Stored by Rows.
  __m256 M00, M01, M02;

  int    i, j, jj, k, nr;
  k = 0;
  for ( j = 0; j < nc; j += RR ) { 
    k = j*mc;
    nr = min( nc-j, RR );
    if (nr == 24) {// nr == 24
      for ( i=0; i < mc; i++ ) {
        M00 = _mm256_loadu_ps(&Mcol(j + 0, i));
        M01 = _mm256_loadu_ps(&Mcol(j + 8, i));
        M02 = _mm256_loadu_ps(&Mcol(j + 16,i));

        _mm256_storeu_ps(&Mc[k], M00); k += 8;
        _mm256_storeu_ps(&Mc[k], M01); k += 8;
        _mm256_storeu_ps(&Mc[k], M02); k += 8;
        //k += (RR - nr);
      }
    } else if (nr == 16) {// nr == 16
      for ( i=0; i < mc; i++ ) {
        M00 = _mm256_loadu_ps(&Mcol(j, i));
        M01 = _mm256_loadu_ps(&Mcol(j + 8, i));

        _mm256_storeu_ps(&Mc[k], M00); k += 8;
        _mm256_storeu_ps(&Mc[k], M01); k += 8;
        k += (RR - nr);
      }
    } else {
      for ( i=0; i<mc; i++ ) {
        for ( jj=0; jj<nr; jj++ ) {
          Mc[k] = Mcol(j+jj,i);
          k++;
        }
        k += (RR-nr);
      }
    }

  }

}

void pack_RB_v( char orderM, char transM, int mc, int nc, DTYPE *M, int ldM, DTYPE *Mc, int RR ){
      
}



