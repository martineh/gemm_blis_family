#include "uk.h"



#include <stdio.h>
#include <stdlib.h>

#include <arm_neon.h>


// example_sgemm_a1True_b1False(
//     KC : size,
//     alpha : f32[1] @DRAM,
//     A : f32[KC, 8] @DRAM,
//     B : f32[KC, 12] @DRAM,
//     beta : f32[1] @DRAM,
//     C : f32[12, 8] @DRAM
// )
inline void uk_1xX_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
for (int k = 0; k < KC; k++) {
  for (int j = 0; j < 12; j++) {
    for (int i = 0; i < 8; i++) {
      C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
    }
  }
}
}
inline void uk_wind_8x12_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, struct exo_win_2f32 C ) {
	float *Cb = malloc(12 * 8 * sizeof(*Cb));
	float32x4_t Cb_reg[12][2];
	float32x4_t beta_reg;
	beta_reg = vld1q_dup_f32(&beta[(0) * (1)]);
	float32x4_t C_reg[2];
	for (int cj = 0; cj < 12; cj++) {
		  for (int cit = 0; cit < 2; cit++) {
			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
			        }
		    for (int cit = 0; cit < 2; cit++) {
			        Cb_reg[cj][cit] = vmulq_f32(C_reg[cit], beta_reg);
				  }
	}
	for (int cj = 0; cj < 12; cj++) {
		  for (int cit = 0; cit < 2; cit++) {
			      vst1q_f32(&Cb[(cj) * (8) + (4 * cit) * (1)], Cb_reg[cj][cit]);
			        }
	}
	Cb_reg[0][0] = vld1q_f32(&Cb[(0) * (8) + (0) * (1)]);
	Cb_reg[0][1] = vld1q_f32(&Cb[(0) * (8) + (4) * (1)]);
	Cb_reg[1][0] = vld1q_f32(&Cb[(1) * (8) + (0) * (1)]);
	Cb_reg[1][1] = vld1q_f32(&Cb[(1) * (8) + (4) * (1)]);
	Cb_reg[2][0] = vld1q_f32(&Cb[(2) * (8) + (0) * (1)]);
	Cb_reg[2][1] = vld1q_f32(&Cb[(2) * (8) + (4) * (1)]);
	Cb_reg[3][0] = vld1q_f32(&Cb[(3) * (8) + (0) * (1)]);
	Cb_reg[3][1] = vld1q_f32(&Cb[(3) * (8) + (4) * (1)]);
	Cb_reg[4][0] = vld1q_f32(&Cb[(4) * (8) + (0) * (1)]);
	Cb_reg[4][1] = vld1q_f32(&Cb[(4) * (8) + (4) * (1)]);
	Cb_reg[5][0] = vld1q_f32(&Cb[(5) * (8) + (0) * (1)]);
	Cb_reg[5][1] = vld1q_f32(&Cb[(5) * (8) + (4) * (1)]);
	Cb_reg[6][0] = vld1q_f32(&Cb[(6) * (8) + (0) * (1)]);
	Cb_reg[6][1] = vld1q_f32(&Cb[(6) * (8) + (4) * (1)]);
	Cb_reg[7][0] = vld1q_f32(&Cb[(7) * (8) + (0) * (1)]);
	Cb_reg[7][1] = vld1q_f32(&Cb[(7) * (8) + (4) * (1)]);
	Cb_reg[8][0] = vld1q_f32(&Cb[(8) * (8) + (0) * (1)]);
	Cb_reg[8][1] = vld1q_f32(&Cb[(8) * (8) + (4) * (1)]);
	Cb_reg[9][0] = vld1q_f32(&Cb[(9) * (8) + (0) * (1)]);
	Cb_reg[9][1] = vld1q_f32(&Cb[(9) * (8) + (4) * (1)]);
	Cb_reg[10][0] = vld1q_f32(&Cb[(10) * (8) + (0) * (1)]);
	Cb_reg[10][1] = vld1q_f32(&Cb[(10) * (8) + (4) * (1)]);
	Cb_reg[11][0] = vld1q_f32(&Cb[(11) * (8) + (0) * (1)]);
	Cb_reg[11][1] = vld1q_f32(&Cb[(11) * (8) + (4) * (1)]);
	float32x4_t A_reg[2];
	float32x4_t B_reg[3];
	for (int k = 0; k < KC; k++) {
	  A_reg[0] = vld1q_f32(&A[(k) * (8) + (4 * 0) * (1)]);
	    A_reg[1] = vld1q_f32(&A[(k) * (8) + (4 * 1) * (1)]);
	      B_reg[0] = vld1q_f32(&B[(k) * (12) + (4 * 0) * (1)]);
	        B_reg[1] = vld1q_f32(&B[(k) * (12) + (4 * 1) * (1)]);
		  B_reg[2] = vld1q_f32(&B[(k) * (12) + (4 * 2) * (1)]);
	  Cb_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
	    Cb_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (1));
	      Cb_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (2));
	        Cb_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (3));
		  Cb_reg[0 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][1], A_reg[1], B_reg[0], (0));
		    Cb_reg[1 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][1], A_reg[1], B_reg[0], (1));
		      Cb_reg[2 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][1], A_reg[1], B_reg[0], (2));
		        Cb_reg[3 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][1], A_reg[1], B_reg[0], (3));
			  Cb_reg[0 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 1][0], A_reg[0], B_reg[1], (0));
			    Cb_reg[1 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 1][0], A_reg[0], B_reg[1], (1));
			      Cb_reg[2 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 1][0], A_reg[0], B_reg[1], (2));
			        Cb_reg[3 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 1][0], A_reg[0], B_reg[1], (3));
				  Cb_reg[0 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 1][1], A_reg[1], B_reg[1], (0));
				    Cb_reg[1 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 1][1], A_reg[1], B_reg[1], (1));
				      Cb_reg[2 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 1][1], A_reg[1], B_reg[1], (2));
				        Cb_reg[3 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 1][1], A_reg[1], B_reg[1], (3));
					  Cb_reg[0 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 2][0], A_reg[0], B_reg[2], (0));
					    Cb_reg[1 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 2][0], A_reg[0], B_reg[2], (1));
					      Cb_reg[2 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 2][0], A_reg[0], B_reg[2], (2));
					        Cb_reg[3 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 2][0], A_reg[0], B_reg[2], (3));
						  Cb_reg[0 + 4 * 2][1] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 2][1], A_reg[1], B_reg[2], (0));
						    Cb_reg[1 + 4 * 2][1] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 2][1], A_reg[1], B_reg[2], (1));
						      Cb_reg[2 + 4 * 2][1] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 2][1], A_reg[1], B_reg[2], (2));
						        Cb_reg[3 + 4 * 2][1] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 2][1], A_reg[1], B_reg[2], (3));
	}
	vst1q_f32(&Cb[(0 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[0 + 4 * 0][0]);
	vst1q_f32(&Cb[(0 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[0 + 4 * 0][1]);
	vst1q_f32(&Cb[(1 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[1 + 4 * 0][0]);
	vst1q_f32(&Cb[(1 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[1 + 4 * 0][1]);
	vst1q_f32(&Cb[(2 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[2 + 4 * 0][0]);
	vst1q_f32(&Cb[(2 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[2 + 4 * 0][1]);
	vst1q_f32(&Cb[(3 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[3 + 4 * 0][0]);
	vst1q_f32(&Cb[(3 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[3 + 4 * 0][1]);
	vst1q_f32(&Cb[(0 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[0 + 4 * 1][0]);
	vst1q_f32(&Cb[(0 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[0 + 4 * 1][1]);
	vst1q_f32(&Cb[(1 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[1 + 4 * 1][0]);
	vst1q_f32(&Cb[(1 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[1 + 4 * 1][1]);
	vst1q_f32(&Cb[(2 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[2 + 4 * 1][0]);
	vst1q_f32(&Cb[(2 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[2 + 4 * 1][1]);
	vst1q_f32(&Cb[(3 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[3 + 4 * 1][0]);
	vst1q_f32(&Cb[(3 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[3 + 4 * 1][1]);
	vst1q_f32(&Cb[(0 + 4 * 2) * (8) + (4 * 0) * (1)], Cb_reg[0 + 4 * 2][0]);
	vst1q_f32(&Cb[(0 + 4 * 2) * (8) + (4 * 1) * (1)], Cb_reg[0 + 4 * 2][1]);
	vst1q_f32(&Cb[(1 + 4 * 2) * (8) + (4 * 0) * (1)], Cb_reg[1 + 4 * 2][0]);
	vst1q_f32(&Cb[(1 + 4 * 2) * (8) + (4 * 1) * (1)], Cb_reg[1 + 4 * 2][1]);
	vst1q_f32(&Cb[(2 + 4 * 2) * (8) + (4 * 0) * (1)], Cb_reg[2 + 4 * 2][0]);
	vst1q_f32(&Cb[(2 + 4 * 2) * (8) + (4 * 1) * (1)], Cb_reg[2 + 4 * 2][1]);
	vst1q_f32(&Cb[(3 + 4 * 2) * (8) + (4 * 0) * (1)], Cb_reg[3 + 4 * 2][0]);
	vst1q_f32(&Cb[(3 + 4 * 2) * (8) + (4 * 1) * (1)], Cb_reg[3 + 4 * 2][1]);
	for (int cj = 0; cj < 12; cj++) {
		  for (int ci = 0; ci < 8; ci++) {
			      C.data[(cj) * (C.strides[0]) + (ci) * (C.strides[1])] = Cb[(cj) * (8) + (ci) * (1)];
			        }
	}
	free(Cb);
}



// example_sgemm_a1True_b1True(
//     KC : size,
//     alpha : f32[1] @DRAM,
//     A : f32[KC, 8] @DRAM,
//     B : f32[KC, 12] @DRAM,
//     beta : f32[1] @DRAM,
//     C : f32[12, 8] @DRAM
// )
inline void example_sgemm_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
float *Cb = malloc(12 * 8 * sizeof(*Cb));
free(Cb);
for (int k = 0; k < KC; k++) {
  for (int j = 0; j < 12; j++) {
    for (int i = 0; i < 8; i++) {
      C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
    }
  }
}
}


/* relying on the following instruction..."
neon_broadcast_4xf32(dst,src)
{dst_data} = vld1q_dup_f32(&{src_data});
*/

/* relying on the following instruction..."
neon_vfmla_4xf32_4xf32(dst,lhs,rhs,lane)
{dst_data} = vfmaq_laneq_f32({dst_data}, {lhs_data}, {rhs_data}, {lane});
*/

/* relying on the following instruction..."
neon_vld_4xf32(dst,src)
{dst_data} = vld1q_f32(&{src_data});
*/

/* relying on the following instruction..."
neon_vmul_4xf32(dst,lhs,rhs)
{dst_data} = vmulq_f32({lhs_data}, {rhs_data});
*/

/* relying on the following instruction..."
neon_vst_4xf32(dst,src)
vst1q_f32(&{dst_data}, {src_data});
*/
// uk_8x12_a1True_b1False(
//     KC : size,
//     alpha : f32[1] @DRAM,
//     A : f32[KC, 8] @DRAM,
//     B : f32[KC, 12] @DRAM,
//     beta : f32[1] @DRAM,
//     C : f32[12, 8] @DRAM
// )
inline void uk_8x12_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
float *Cb = malloc(12 * 8 * sizeof(*Cb));
float32x4_t Cb_reg[12][2];
float32x4_t beta_reg;
beta_reg = vld1q_dup_f32(&beta[(0) * (1)]);
float32x4_t C_reg[2];
for (int cj = 0; cj < 12; cj++) {
  for (int cit = 0; cit < 2; cit++) {
    C_reg[cit] = vld1q_f32(&C[(cj) * (8) + (4 * cit) * (1)]);
  }
  for (int cit = 0; cit < 2; cit++) {
    Cb_reg[cj][cit] = vmulq_f32(C_reg[cit], beta_reg);
  }
}
for (int cj = 0; cj < 12; cj++) {
  for (int cit = 0; cit < 2; cit++) {
    vst1q_f32(&Cb[(cj) * (8) + (4 * cit) * (1)], Cb_reg[cj][cit]);
  }
}
Cb_reg[0][0] = vld1q_f32(&Cb[(0) * (8) + (0) * (1)]);
Cb_reg[0][1] = vld1q_f32(&Cb[(0) * (8) + (4) * (1)]);
Cb_reg[1][0] = vld1q_f32(&Cb[(1) * (8) + (0) * (1)]);
Cb_reg[1][1] = vld1q_f32(&Cb[(1) * (8) + (4) * (1)]);
Cb_reg[2][0] = vld1q_f32(&Cb[(2) * (8) + (0) * (1)]);
Cb_reg[2][1] = vld1q_f32(&Cb[(2) * (8) + (4) * (1)]);
Cb_reg[3][0] = vld1q_f32(&Cb[(3) * (8) + (0) * (1)]);
Cb_reg[3][1] = vld1q_f32(&Cb[(3) * (8) + (4) * (1)]);
Cb_reg[4][0] = vld1q_f32(&Cb[(4) * (8) + (0) * (1)]);
Cb_reg[4][1] = vld1q_f32(&Cb[(4) * (8) + (4) * (1)]);
Cb_reg[5][0] = vld1q_f32(&Cb[(5) * (8) + (0) * (1)]);
Cb_reg[5][1] = vld1q_f32(&Cb[(5) * (8) + (4) * (1)]);
Cb_reg[6][0] = vld1q_f32(&Cb[(6) * (8) + (0) * (1)]);
Cb_reg[6][1] = vld1q_f32(&Cb[(6) * (8) + (4) * (1)]);
Cb_reg[7][0] = vld1q_f32(&Cb[(7) * (8) + (0) * (1)]);
Cb_reg[7][1] = vld1q_f32(&Cb[(7) * (8) + (4) * (1)]);
Cb_reg[8][0] = vld1q_f32(&Cb[(8) * (8) + (0) * (1)]);
Cb_reg[8][1] = vld1q_f32(&Cb[(8) * (8) + (4) * (1)]);
Cb_reg[9][0] = vld1q_f32(&Cb[(9) * (8) + (0) * (1)]);
Cb_reg[9][1] = vld1q_f32(&Cb[(9) * (8) + (4) * (1)]);
Cb_reg[10][0] = vld1q_f32(&Cb[(10) * (8) + (0) * (1)]);
Cb_reg[10][1] = vld1q_f32(&Cb[(10) * (8) + (4) * (1)]);
Cb_reg[11][0] = vld1q_f32(&Cb[(11) * (8) + (0) * (1)]);
Cb_reg[11][1] = vld1q_f32(&Cb[(11) * (8) + (4) * (1)]);
float32x4_t A_reg[2];
float32x4_t B_reg[3];
for (int k = 0; k < KC; k++) {
  A_reg[0] = vld1q_f32(&A[(k) * (8) + (4 * 0) * (1)]);
  A_reg[1] = vld1q_f32(&A[(k) * (8) + (4 * 1) * (1)]);
  B_reg[0] = vld1q_f32(&B[(k) * (12) + (4 * 0) * (1)]);
  B_reg[1] = vld1q_f32(&B[(k) * (12) + (4 * 1) * (1)]);
  B_reg[2] = vld1q_f32(&B[(k) * (12) + (4 * 2) * (1)]);
  Cb_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
  Cb_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (1));
  Cb_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (2));
  Cb_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (3));
  Cb_reg[0 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][1], A_reg[1], B_reg[0], (0));
  Cb_reg[1 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][1], A_reg[1], B_reg[0], (1));
  Cb_reg[2 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][1], A_reg[1], B_reg[0], (2));
  Cb_reg[3 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][1], A_reg[1], B_reg[0], (3));
  Cb_reg[0 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 1][0], A_reg[0], B_reg[1], (0));
  Cb_reg[1 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 1][0], A_reg[0], B_reg[1], (1));
  Cb_reg[2 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 1][0], A_reg[0], B_reg[1], (2));
  Cb_reg[3 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 1][0], A_reg[0], B_reg[1], (3));
  Cb_reg[0 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 1][1], A_reg[1], B_reg[1], (0));
  Cb_reg[1 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 1][1], A_reg[1], B_reg[1], (1));
  Cb_reg[2 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 1][1], A_reg[1], B_reg[1], (2));
  Cb_reg[3 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 1][1], A_reg[1], B_reg[1], (3));
  Cb_reg[0 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 2][0], A_reg[0], B_reg[2], (0));
  Cb_reg[1 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 2][0], A_reg[0], B_reg[2], (1));
  Cb_reg[2 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 2][0], A_reg[0], B_reg[2], (2));
  Cb_reg[3 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 2][0], A_reg[0], B_reg[2], (3));
  Cb_reg[0 + 4 * 2][1] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 2][1], A_reg[1], B_reg[2], (0));
  Cb_reg[1 + 4 * 2][1] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 2][1], A_reg[1], B_reg[2], (1));
  Cb_reg[2 + 4 * 2][1] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 2][1], A_reg[1], B_reg[2], (2));
  Cb_reg[3 + 4 * 2][1] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 2][1], A_reg[1], B_reg[2], (3));
}
vst1q_f32(&Cb[(0 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[0 + 4 * 0][0]);
vst1q_f32(&Cb[(0 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[0 + 4 * 0][1]);
vst1q_f32(&Cb[(1 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[1 + 4 * 0][0]);
vst1q_f32(&Cb[(1 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[1 + 4 * 0][1]);
vst1q_f32(&Cb[(2 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[2 + 4 * 0][0]);
vst1q_f32(&Cb[(2 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[2 + 4 * 0][1]);
vst1q_f32(&Cb[(3 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[3 + 4 * 0][0]);
vst1q_f32(&Cb[(3 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[3 + 4 * 0][1]);
vst1q_f32(&Cb[(0 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[0 + 4 * 1][0]);
vst1q_f32(&Cb[(0 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[0 + 4 * 1][1]);
vst1q_f32(&Cb[(1 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[1 + 4 * 1][0]);
vst1q_f32(&Cb[(1 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[1 + 4 * 1][1]);
vst1q_f32(&Cb[(2 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[2 + 4 * 1][0]);
vst1q_f32(&Cb[(2 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[2 + 4 * 1][1]);
vst1q_f32(&Cb[(3 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[3 + 4 * 1][0]);
vst1q_f32(&Cb[(3 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[3 + 4 * 1][1]);
vst1q_f32(&Cb[(0 + 4 * 2) * (8) + (4 * 0) * (1)], Cb_reg[0 + 4 * 2][0]);
vst1q_f32(&Cb[(0 + 4 * 2) * (8) + (4 * 1) * (1)], Cb_reg[0 + 4 * 2][1]);
vst1q_f32(&Cb[(1 + 4 * 2) * (8) + (4 * 0) * (1)], Cb_reg[1 + 4 * 2][0]);
vst1q_f32(&Cb[(1 + 4 * 2) * (8) + (4 * 1) * (1)], Cb_reg[1 + 4 * 2][1]);
vst1q_f32(&Cb[(2 + 4 * 2) * (8) + (4 * 0) * (1)], Cb_reg[2 + 4 * 2][0]);
vst1q_f32(&Cb[(2 + 4 * 2) * (8) + (4 * 1) * (1)], Cb_reg[2 + 4 * 2][1]);
vst1q_f32(&Cb[(3 + 4 * 2) * (8) + (4 * 0) * (1)], Cb_reg[3 + 4 * 2][0]);
vst1q_f32(&Cb[(3 + 4 * 2) * (8) + (4 * 1) * (1)], Cb_reg[3 + 4 * 2][1]);
for (int cj = 0; cj < 12; cj++) {
  for (int ci = 0; ci < 8; ci++) {
    C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
  }
}
free(Cb);
}

// uk_8x12_a1True_b1True(
//     KC : size,
//     alpha : f32[1] @DRAM,
//     A : f32[KC, 8] @DRAM,
//     B : f32[KC, 12] @DRAM,
//     beta : f32[1] @DRAM,
//     C : f32[12, 8] @DRAM
// )
inline void uk_8x12_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
float *Cb = malloc(12 * 8 * sizeof(*Cb));
free(Cb);
float32x4_t C_reg[12][2];
C_reg[0][0] = vld1q_f32(&C[(0) * (8) + (0) * (1)]);
C_reg[0][1] = vld1q_f32(&C[(0) * (8) + (4) * (1)]);
C_reg[1][0] = vld1q_f32(&C[(1) * (8) + (0) * (1)]);
C_reg[1][1] = vld1q_f32(&C[(1) * (8) + (4) * (1)]);
C_reg[2][0] = vld1q_f32(&C[(2) * (8) + (0) * (1)]);
C_reg[2][1] = vld1q_f32(&C[(2) * (8) + (4) * (1)]);
C_reg[3][0] = vld1q_f32(&C[(3) * (8) + (0) * (1)]);
C_reg[3][1] = vld1q_f32(&C[(3) * (8) + (4) * (1)]);
C_reg[4][0] = vld1q_f32(&C[(4) * (8) + (0) * (1)]);
C_reg[4][1] = vld1q_f32(&C[(4) * (8) + (4) * (1)]);
C_reg[5][0] = vld1q_f32(&C[(5) * (8) + (0) * (1)]);
C_reg[5][1] = vld1q_f32(&C[(5) * (8) + (4) * (1)]);
C_reg[6][0] = vld1q_f32(&C[(6) * (8) + (0) * (1)]);
C_reg[6][1] = vld1q_f32(&C[(6) * (8) + (4) * (1)]);
C_reg[7][0] = vld1q_f32(&C[(7) * (8) + (0) * (1)]);
C_reg[7][1] = vld1q_f32(&C[(7) * (8) + (4) * (1)]);
C_reg[8][0] = vld1q_f32(&C[(8) * (8) + (0) * (1)]);
C_reg[8][1] = vld1q_f32(&C[(8) * (8) + (4) * (1)]);
C_reg[9][0] = vld1q_f32(&C[(9) * (8) + (0) * (1)]);
C_reg[9][1] = vld1q_f32(&C[(9) * (8) + (4) * (1)]);
C_reg[10][0] = vld1q_f32(&C[(10) * (8) + (0) * (1)]);
C_reg[10][1] = vld1q_f32(&C[(10) * (8) + (4) * (1)]);
C_reg[11][0] = vld1q_f32(&C[(11) * (8) + (0) * (1)]);
C_reg[11][1] = vld1q_f32(&C[(11) * (8) + (4) * (1)]);
float32x4_t A_reg[2];
float32x4_t B_reg[3];
for (int k = 0; k < KC; k++) {
  A_reg[0] = vld1q_f32(&A[(k) * (8) + (4 * 0) * (1)]);
  A_reg[1] = vld1q_f32(&A[(k) * (8) + (4 * 1) * (1)]);
  B_reg[0] = vld1q_f32(&B[(k) * (12) + (4 * 0) * (1)]);
  B_reg[1] = vld1q_f32(&B[(k) * (12) + (4 * 1) * (1)]);
  B_reg[2] = vld1q_f32(&B[(k) * (12) + (4 * 2) * (1)]);
  C_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
  C_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (1));
  C_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (2));
  C_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (3));
  C_reg[0 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][1], A_reg[1], B_reg[0], (0));
  C_reg[1 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][1], A_reg[1], B_reg[0], (1));
  C_reg[2 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][1], A_reg[1], B_reg[0], (2));
  C_reg[3 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][1], A_reg[1], B_reg[0], (3));
  C_reg[0 + 4 * 1][0] = vfmaq_laneq_f32(C_reg[0 + 4 * 1][0], A_reg[0], B_reg[1], (0));
  C_reg[1 + 4 * 1][0] = vfmaq_laneq_f32(C_reg[1 + 4 * 1][0], A_reg[0], B_reg[1], (1));
  C_reg[2 + 4 * 1][0] = vfmaq_laneq_f32(C_reg[2 + 4 * 1][0], A_reg[0], B_reg[1], (2));
  C_reg[3 + 4 * 1][0] = vfmaq_laneq_f32(C_reg[3 + 4 * 1][0], A_reg[0], B_reg[1], (3));
  C_reg[0 + 4 * 1][1] = vfmaq_laneq_f32(C_reg[0 + 4 * 1][1], A_reg[1], B_reg[1], (0));
  C_reg[1 + 4 * 1][1] = vfmaq_laneq_f32(C_reg[1 + 4 * 1][1], A_reg[1], B_reg[1], (1));
  C_reg[2 + 4 * 1][1] = vfmaq_laneq_f32(C_reg[2 + 4 * 1][1], A_reg[1], B_reg[1], (2));
  C_reg[3 + 4 * 1][1] = vfmaq_laneq_f32(C_reg[3 + 4 * 1][1], A_reg[1], B_reg[1], (3));
  C_reg[0 + 4 * 2][0] = vfmaq_laneq_f32(C_reg[0 + 4 * 2][0], A_reg[0], B_reg[2], (0));
  C_reg[1 + 4 * 2][0] = vfmaq_laneq_f32(C_reg[1 + 4 * 2][0], A_reg[0], B_reg[2], (1));
  C_reg[2 + 4 * 2][0] = vfmaq_laneq_f32(C_reg[2 + 4 * 2][0], A_reg[0], B_reg[2], (2));
  C_reg[3 + 4 * 2][0] = vfmaq_laneq_f32(C_reg[3 + 4 * 2][0], A_reg[0], B_reg[2], (3));
  C_reg[0 + 4 * 2][1] = vfmaq_laneq_f32(C_reg[0 + 4 * 2][1], A_reg[1], B_reg[2], (0));
  C_reg[1 + 4 * 2][1] = vfmaq_laneq_f32(C_reg[1 + 4 * 2][1], A_reg[1], B_reg[2], (1));
  C_reg[2 + 4 * 2][1] = vfmaq_laneq_f32(C_reg[2 + 4 * 2][1], A_reg[1], B_reg[2], (2));
  C_reg[3 + 4 * 2][1] = vfmaq_laneq_f32(C_reg[3 + 4 * 2][1], A_reg[1], B_reg[2], (3));
}
vst1q_f32(&C[(0 + 4 * 0) * (8) + (4 * 0) * (1)], C_reg[0 + 4 * 0][0]);
vst1q_f32(&C[(0 + 4 * 0) * (8) + (4 * 1) * (1)], C_reg[0 + 4 * 0][1]);
vst1q_f32(&C[(1 + 4 * 0) * (8) + (4 * 0) * (1)], C_reg[1 + 4 * 0][0]);
vst1q_f32(&C[(1 + 4 * 0) * (8) + (4 * 1) * (1)], C_reg[1 + 4 * 0][1]);
vst1q_f32(&C[(2 + 4 * 0) * (8) + (4 * 0) * (1)], C_reg[2 + 4 * 0][0]);
vst1q_f32(&C[(2 + 4 * 0) * (8) + (4 * 1) * (1)], C_reg[2 + 4 * 0][1]);
vst1q_f32(&C[(3 + 4 * 0) * (8) + (4 * 0) * (1)], C_reg[3 + 4 * 0][0]);
vst1q_f32(&C[(3 + 4 * 0) * (8) + (4 * 1) * (1)], C_reg[3 + 4 * 0][1]);
vst1q_f32(&C[(0 + 4 * 1) * (8) + (4 * 0) * (1)], C_reg[0 + 4 * 1][0]);
vst1q_f32(&C[(0 + 4 * 1) * (8) + (4 * 1) * (1)], C_reg[0 + 4 * 1][1]);
vst1q_f32(&C[(1 + 4 * 1) * (8) + (4 * 0) * (1)], C_reg[1 + 4 * 1][0]);
vst1q_f32(&C[(1 + 4 * 1) * (8) + (4 * 1) * (1)], C_reg[1 + 4 * 1][1]);
vst1q_f32(&C[(2 + 4 * 1) * (8) + (4 * 0) * (1)], C_reg[2 + 4 * 1][0]);
vst1q_f32(&C[(2 + 4 * 1) * (8) + (4 * 1) * (1)], C_reg[2 + 4 * 1][1]);
vst1q_f32(&C[(3 + 4 * 1) * (8) + (4 * 0) * (1)], C_reg[3 + 4 * 1][0]);
vst1q_f32(&C[(3 + 4 * 1) * (8) + (4 * 1) * (1)], C_reg[3 + 4 * 1][1]);
vst1q_f32(&C[(0 + 4 * 2) * (8) + (4 * 0) * (1)], C_reg[0 + 4 * 2][0]);
vst1q_f32(&C[(0 + 4 * 2) * (8) + (4 * 1) * (1)], C_reg[0 + 4 * 2][1]);
vst1q_f32(&C[(1 + 4 * 2) * (8) + (4 * 0) * (1)], C_reg[1 + 4 * 2][0]);
vst1q_f32(&C[(1 + 4 * 2) * (8) + (4 * 1) * (1)], C_reg[1 + 4 * 2][1]);
vst1q_f32(&C[(2 + 4 * 2) * (8) + (4 * 0) * (1)], C_reg[2 + 4 * 2][0]);
vst1q_f32(&C[(2 + 4 * 2) * (8) + (4 * 1) * (1)], C_reg[2 + 4 * 2][1]);
vst1q_f32(&C[(3 + 4 * 2) * (8) + (4 * 0) * (1)], C_reg[3 + 4 * 2][0]);
vst1q_f32(&C[(3 + 4 * 2) * (8) + (4 * 1) * (1)], C_reg[3 + 4 * 2][1]);
}

inline void uk_8x4_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	float *Cb = malloc(4 * 8 * sizeof(*Cb));
	float32x4_t Cb_reg[4][2];
	float32x4_t beta_reg;
	beta_reg = vld1q_dup_f32(&beta[(0) * (1)]);
	float32x4_t C_reg[2];
	for (int cj = 0; cj < 4; cj++) {
		  for (int cit = 0; cit < 2; cit++) {
			      C_reg[cit] = vld1q_f32(&C[(cj) * (8) + (4 * cit) * (1)]);
			        }
		    for (int cit = 0; cit < 2; cit++) {
			        Cb_reg[cj][cit] = vmulq_f32(C_reg[cit], beta_reg);
				  }
	}
	for (int cj = 0; cj < 4; cj++) {
		  for (int cit = 0; cit < 2; cit++) {
			      vst1q_f32(&Cb[(cj) * (8) + (4 * cit) * (1)], Cb_reg[cj][cit]);
			        }
	}
	Cb_reg[0][0] = vld1q_f32(&Cb[(0) * (8) + (0) * (1)]);
	Cb_reg[0][1] = vld1q_f32(&Cb[(0) * (8) + (4) * (1)]);
	Cb_reg[1][0] = vld1q_f32(&Cb[(1) * (8) + (0) * (1)]);
	Cb_reg[1][1] = vld1q_f32(&Cb[(1) * (8) + (4) * (1)]);
	Cb_reg[2][0] = vld1q_f32(&Cb[(2) * (8) + (0) * (1)]);
	Cb_reg[2][1] = vld1q_f32(&Cb[(2) * (8) + (4) * (1)]);
	Cb_reg[3][0] = vld1q_f32(&Cb[(3) * (8) + (0) * (1)]);
	Cb_reg[3][1] = vld1q_f32(&Cb[(3) * (8) + (4) * (1)]);
	float32x4_t A_reg[2];
	float32x4_t B_reg[1];
	for (int k = 0; k < KC; k++) {
		  A_reg[0] = vld1q_f32(&A[(k) * (8) + (4 * 0) * (1)]);
		    A_reg[1] = vld1q_f32(&A[(k) * (8) + (4 * 1) * (1)]);
		      B_reg[0] = vld1q_f32(&B[(k) * (4) + (4 * 0) * (1)]);
		        Cb_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
			  Cb_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (1));
			    Cb_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (2));
			      Cb_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (3));
			        Cb_reg[0 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][1], A_reg[1], B_reg[0], (0));
				  Cb_reg[1 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][1], A_reg[1], B_reg[0], (1));
				    Cb_reg[2 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][1], A_reg[1], B_reg[0], (2));
				      Cb_reg[3 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][1], A_reg[1], B_reg[0], (3));
	}
	vst1q_f32(&Cb[(0 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[0 + 4 * 0][0]);
	vst1q_f32(&Cb[(0 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[0 + 4 * 0][1]);
	vst1q_f32(&Cb[(1 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[1 + 4 * 0][0]);
	vst1q_f32(&Cb[(1 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[1 + 4 * 0][1]);
	vst1q_f32(&Cb[(2 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[2 + 4 * 0][0]);
	vst1q_f32(&Cb[(2 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[2 + 4 * 0][1]);
	vst1q_f32(&Cb[(3 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[3 + 4 * 0][0]);
	vst1q_f32(&Cb[(3 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[3 + 4 * 0][1]);
	for (int cj = 0; cj < 4; cj++) {
		  for (int ci = 0; ci < 8; ci++) {
			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
			        }
	}
	free(Cb);
}

inline void uk_8x8_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	float *Cb = malloc(8 * 8 * sizeof(*Cb));
	float32x4_t Cb_reg[8][2];
	float32x4_t beta_reg;
	beta_reg = vld1q_dup_f32(&beta[(0) * (1)]);
	float32x4_t C_reg[2];
	for (int cj = 0; cj < 8; cj++) {
		  for (int cit = 0; cit < 2; cit++) {
			      C_reg[cit] = vld1q_f32(&C[(cj) * (8) + (4 * cit) * (1)]);
			        }
		    for (int cit = 0; cit < 2; cit++) {
			        Cb_reg[cj][cit] = vmulq_f32(C_reg[cit], beta_reg);
				  }
	}
	for (int cj = 0; cj < 8; cj++) {
		  for (int cit = 0; cit < 2; cit++) {
			      vst1q_f32(&Cb[(cj) * (8) + (4 * cit) * (1)], Cb_reg[cj][cit]);
			        }
	}
	Cb_reg[0][0] = vld1q_f32(&Cb[(0) * (8) + (0) * (1)]);
	Cb_reg[0][1] = vld1q_f32(&Cb[(0) * (8) + (4) * (1)]);
	Cb_reg[1][0] = vld1q_f32(&Cb[(1) * (8) + (0) * (1)]);
	Cb_reg[1][1] = vld1q_f32(&Cb[(1) * (8) + (4) * (1)]);
	Cb_reg[2][0] = vld1q_f32(&Cb[(2) * (8) + (0) * (1)]);
	Cb_reg[2][1] = vld1q_f32(&Cb[(2) * (8) + (4) * (1)]);
	Cb_reg[3][0] = vld1q_f32(&Cb[(3) * (8) + (0) * (1)]);
	Cb_reg[3][1] = vld1q_f32(&Cb[(3) * (8) + (4) * (1)]);
	Cb_reg[4][0] = vld1q_f32(&Cb[(4) * (8) + (0) * (1)]);
	Cb_reg[4][1] = vld1q_f32(&Cb[(4) * (8) + (4) * (1)]);
	Cb_reg[5][0] = vld1q_f32(&Cb[(5) * (8) + (0) * (1)]);
	Cb_reg[5][1] = vld1q_f32(&Cb[(5) * (8) + (4) * (1)]);
	Cb_reg[6][0] = vld1q_f32(&Cb[(6) * (8) + (0) * (1)]);
	Cb_reg[6][1] = vld1q_f32(&Cb[(6) * (8) + (4) * (1)]);
	Cb_reg[7][0] = vld1q_f32(&Cb[(7) * (8) + (0) * (1)]);
	Cb_reg[7][1] = vld1q_f32(&Cb[(7) * (8) + (4) * (1)]);
	float32x4_t A_reg[2];
	float32x4_t B_reg[2];
	for (int k = 0; k < KC; k++) {
		  A_reg[0] = vld1q_f32(&A[(k) * (8) + (4 * 0) * (1)]);
		    A_reg[1] = vld1q_f32(&A[(k) * (8) + (4 * 1) * (1)]);
		      B_reg[0] = vld1q_f32(&B[(k) * (8) + (4 * 0) * (1)]);
		        B_reg[1] = vld1q_f32(&B[(k) * (8) + (4 * 1) * (1)]);
			  Cb_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
			    Cb_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (0));
			      Cb_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (0));
			        Cb_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (0));
				  Cb_reg[0 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][1], A_reg[1], B_reg[0], (0));
				    Cb_reg[1 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][1], A_reg[1], B_reg[0], (0));
				      Cb_reg[2 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][1], A_reg[1], B_reg[0], (0));
				        Cb_reg[3 + 4 * 0][1] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][1], A_reg[1], B_reg[0], (0));
					  Cb_reg[0 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 1][0], A_reg[0], B_reg[0], (1));
					    Cb_reg[1 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 1][0], A_reg[0], B_reg[0], (1));
					      Cb_reg[2 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 1][0], A_reg[0], B_reg[0], (1));
					        Cb_reg[3 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 1][0], A_reg[0], B_reg[0], (1));
						  Cb_reg[0 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 1][1], A_reg[1], B_reg[0], (1));
						    Cb_reg[1 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 1][1], A_reg[1], B_reg[0], (1));
						      Cb_reg[2 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 1][1], A_reg[1], B_reg[0], (1));
						        Cb_reg[3 + 4 * 1][1] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 1][1], A_reg[1], B_reg[0], (1));
	}
	vst1q_f32(&Cb[(0 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[0 + 4 * 0][0]);
	vst1q_f32(&Cb[(0 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[0 + 4 * 0][1]);
	vst1q_f32(&Cb[(1 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[1 + 4 * 0][0]);
	vst1q_f32(&Cb[(1 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[1 + 4 * 0][1]);
	vst1q_f32(&Cb[(2 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[2 + 4 * 0][0]);
	vst1q_f32(&Cb[(2 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[2 + 4 * 0][1]);
	vst1q_f32(&Cb[(3 + 4 * 0) * (8) + (4 * 0) * (1)], Cb_reg[3 + 4 * 0][0]);
	vst1q_f32(&Cb[(3 + 4 * 0) * (8) + (4 * 1) * (1)], Cb_reg[3 + 4 * 0][1]);
	vst1q_f32(&Cb[(0 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[0 + 4 * 1][0]);
	vst1q_f32(&Cb[(0 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[0 + 4 * 1][1]);
	vst1q_f32(&Cb[(1 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[1 + 4 * 1][0]);
	vst1q_f32(&Cb[(1 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[1 + 4 * 1][1]);
	vst1q_f32(&Cb[(2 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[2 + 4 * 1][0]);
	vst1q_f32(&Cb[(2 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[2 + 4 * 1][1]);
	vst1q_f32(&Cb[(3 + 4 * 1) * (8) + (4 * 0) * (1)], Cb_reg[3 + 4 * 1][0]);
	vst1q_f32(&Cb[(3 + 4 * 1) * (8) + (4 * 1) * (1)], Cb_reg[3 + 4 * 1][1]);
	for (int cj = 0; cj < 8; cj++) {
		  for (int ci = 0; ci < 8; ci++) {
			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
			        }
	}
	free(Cb);
}

inline void uk_4x8_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	float *Cb = malloc(8 * 4 * sizeof(*Cb));
	float32x4_t Cb_reg[8][1];
	float32x4_t beta_reg;
	beta_reg = vld1q_dup_f32(&beta[(0) * (1)]);
	float32x4_t C_reg[1];
	for (int cj = 0; cj < 8; cj++) {
		  for (int cit = 0; cit < 1; cit++) {
			      C_reg[cit] = vld1q_f32(&C[(cj) * (4) + (4 * cit) * (1)]);
			        }
		    for (int cit = 0; cit < 1; cit++) {
			        Cb_reg[cj][cit] = vmulq_f32(C_reg[cit], beta_reg);
				  }
	}
	for (int cj = 0; cj < 8; cj++) {
		  for (int cit = 0; cit < 1; cit++) {
			      vst1q_f32(&Cb[(cj) * (4) + (4 * cit) * (1)], Cb_reg[cj][cit]);
			        }
	}
	Cb_reg[0][0] = vld1q_f32(&Cb[(0) * (4) + (0) * (1)]);
	Cb_reg[1][0] = vld1q_f32(&Cb[(1) * (4) + (0) * (1)]);
	Cb_reg[2][0] = vld1q_f32(&Cb[(2) * (4) + (0) * (1)]);
	Cb_reg[3][0] = vld1q_f32(&Cb[(3) * (4) + (0) * (1)]);
	Cb_reg[4][0] = vld1q_f32(&Cb[(4) * (4) + (0) * (1)]);
	Cb_reg[5][0] = vld1q_f32(&Cb[(5) * (4) + (0) * (1)]);
	Cb_reg[6][0] = vld1q_f32(&Cb[(6) * (4) + (0) * (1)]);
	Cb_reg[7][0] = vld1q_f32(&Cb[(7) * (4) + (0) * (1)]);
	float32x4_t A_reg[1];
	float32x4_t B_reg[2];
	for (int k = 0; k < KC; k++) {
		  A_reg[0] = vld1q_f32(&A[(k) * (4) + (4 * 0) * (1)]);
		    B_reg[0] = vld1q_f32(&B[(k) * (8) + (4 * 0) * (1)]);
		      B_reg[1] = vld1q_f32(&B[(k) * (8) + (4 * 1) * (1)]);
		        Cb_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
			  Cb_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (1));
			    Cb_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (2));
			      Cb_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (3));
			        Cb_reg[0 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 1][0], A_reg[0], B_reg[1], (0));
				  Cb_reg[1 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 1][0], A_reg[0], B_reg[1], (1));
				    Cb_reg[2 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 1][0], A_reg[0], B_reg[1], (2));
				      Cb_reg[3 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 1][0], A_reg[0], B_reg[1], (3));
	}
	vst1q_f32(&Cb[(0 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[0 + 4 * 0][0]);
	vst1q_f32(&Cb[(1 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[1 + 4 * 0][0]);
	vst1q_f32(&Cb[(2 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[2 + 4 * 0][0]);
	vst1q_f32(&Cb[(3 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[3 + 4 * 0][0]);
	vst1q_f32(&Cb[(0 + 4 * 1) * (4) + (4 * 0) * (1)], Cb_reg[0 + 4 * 1][0]);
	vst1q_f32(&Cb[(1 + 4 * 1) * (4) + (4 * 0) * (1)], Cb_reg[1 + 4 * 1][0]);
	vst1q_f32(&Cb[(2 + 4 * 1) * (4) + (4 * 0) * (1)], Cb_reg[2 + 4 * 1][0]);
	vst1q_f32(&Cb[(3 + 4 * 1) * (4) + (4 * 0) * (1)], Cb_reg[3 + 4 * 1][0]);
	for (int cj = 0; cj < 8; cj++) {
		  for (int ci = 0; ci < 4; ci++) {
			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
			        }
	}
	free(Cb);
}

inline void uk_4x4_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	float *Cb = malloc(4 * 4 * sizeof(*Cb));
	float32x4_t Cb_reg[4][1];
	float32x4_t beta_reg;
	beta_reg = vld1q_dup_f32(&beta[(0) * (1)]);
	float32x4_t C_reg[1];
	for (int cj = 0; cj < 4; cj++) {
		  for (int cit = 0; cit < 1; cit++) {
			      C_reg[cit] = vld1q_f32(&C[(cj) * (4) + (4 * cit) * (1)]);
			        }
		    for (int cit = 0; cit < 1; cit++) {
			        Cb_reg[cj][cit] = vmulq_f32(C_reg[cit], beta_reg);
				  }
	}
	for (int cj = 0; cj < 4; cj++) {
		  for (int cit = 0; cit < 1; cit++) {
			      vst1q_f32(&Cb[(cj) * (4) + (4 * cit) * (1)], Cb_reg[cj][cit]);
			        }
	}
	Cb_reg[0][0] = vld1q_f32(&Cb[(0) * (4) + (0) * (1)]);
	Cb_reg[1][0] = vld1q_f32(&Cb[(1) * (4) + (0) * (1)]);
	Cb_reg[2][0] = vld1q_f32(&Cb[(2) * (4) + (0) * (1)]);
	Cb_reg[3][0] = vld1q_f32(&Cb[(3) * (4) + (0) * (1)]);
	float32x4_t A_reg[1];
	float32x4_t B_reg[1];
	for (int k = 0; k < KC; k++) {
		  A_reg[0] = vld1q_f32(&A[(k) * (4) + (4 * 0) * (1)]);
		    B_reg[0] = vld1q_f32(&B[(k) * (4) + (4 * 0) * (1)]);
		      Cb_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
		        Cb_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (1));
			  Cb_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (2));
			    Cb_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (3));
	}
	vst1q_f32(&Cb[(0 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[0 + 4 * 0][0]);
	vst1q_f32(&Cb[(1 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[1 + 4 * 0][0]);
	vst1q_f32(&Cb[(2 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[2 + 4 * 0][0]);
	vst1q_f32(&Cb[(3 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[3 + 4 * 0][0]);
	for (int cj = 0; cj < 4; cj++) {
		  for (int ci = 0; ci < 4; ci++) {
			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
			        }
	}
	free(Cb);
}

inline void uk_4x12_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	float *Cb = malloc(12 * 4 * sizeof(*Cb));
	float32x4_t Cb_reg[12][1];
	float32x4_t beta_reg;
	beta_reg = vld1q_dup_f32(&beta[(0) * (1)]);
	float32x4_t C_reg[1];
	for (int cj = 0; cj < 12; cj++) {
		  for (int cit = 0; cit < 1; cit++) {
			      C_reg[cit] = vld1q_f32(&C[(cj) * (4) + (4 * cit) * (1)]);
			        }
		    for (int cit = 0; cit < 1; cit++) {
			        Cb_reg[cj][cit] = vmulq_f32(C_reg[cit], beta_reg);
				  }
	}
	for (int cj = 0; cj < 12; cj++) {
		  for (int cit = 0; cit < 1; cit++) {
			      vst1q_f32(&Cb[(cj) * (4) + (4 * cit) * (1)], Cb_reg[cj][cit]);
			        }
	}
	Cb_reg[0][0] = vld1q_f32(&Cb[(0) * (4) + (0) * (1)]);
	Cb_reg[1][0] = vld1q_f32(&Cb[(1) * (4) + (0) * (1)]);
	Cb_reg[2][0] = vld1q_f32(&Cb[(2) * (4) + (0) * (1)]);
	Cb_reg[3][0] = vld1q_f32(&Cb[(3) * (4) + (0) * (1)]);
	Cb_reg[4][0] = vld1q_f32(&Cb[(4) * (4) + (0) * (1)]);
	Cb_reg[5][0] = vld1q_f32(&Cb[(5) * (4) + (0) * (1)]);
	Cb_reg[6][0] = vld1q_f32(&Cb[(6) * (4) + (0) * (1)]);
	Cb_reg[7][0] = vld1q_f32(&Cb[(7) * (4) + (0) * (1)]);
	Cb_reg[8][0] = vld1q_f32(&Cb[(8) * (4) + (0) * (1)]);
	Cb_reg[9][0] = vld1q_f32(&Cb[(9) * (4) + (0) * (1)]);
	Cb_reg[10][0] = vld1q_f32(&Cb[(10) * (4) + (0) * (1)]);
	Cb_reg[11][0] = vld1q_f32(&Cb[(11) * (4) + (0) * (1)]);
	float32x4_t A_reg[1];
	float32x4_t B_reg[3];
	for (int k = 0; k < KC; k++) {
		  A_reg[0] = vld1q_f32(&A[(k) * (4) + (4 * 0) * (1)]);
		    B_reg[0] = vld1q_f32(&B[(k) * (12) + (4 * 0) * (1)]);
		      B_reg[1] = vld1q_f32(&B[(k) * (12) + (4 * 1) * (1)]);
		        B_reg[2] = vld1q_f32(&B[(k) * (12) + (4 * 2) * (1)]);
			  Cb_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
			    Cb_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (0));
			      Cb_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (0));
			        Cb_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (0));
				  Cb_reg[0 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 1][0], A_reg[0], B_reg[0], (1));
				    Cb_reg[1 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 1][0], A_reg[0], B_reg[0], (1));
				      Cb_reg[2 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 1][0], A_reg[0], B_reg[0], (1));
				        Cb_reg[3 + 4 * 1][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 1][0], A_reg[0], B_reg[0], (1));
					  Cb_reg[0 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[0 + 4 * 2][0], A_reg[0], B_reg[0], (2));
					    Cb_reg[1 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[1 + 4 * 2][0], A_reg[0], B_reg[0], (2));
					      Cb_reg[2 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[2 + 4 * 2][0], A_reg[0], B_reg[0], (2));
					        Cb_reg[3 + 4 * 2][0] = vfmaq_laneq_f32(Cb_reg[3 + 4 * 2][0], A_reg[0], B_reg[0], (2));
	}
	vst1q_f32(&Cb[(0 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[0 + 4 * 0][0]);
	vst1q_f32(&Cb[(1 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[1 + 4 * 0][0]);
	vst1q_f32(&Cb[(2 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[2 + 4 * 0][0]);
	vst1q_f32(&Cb[(3 + 4 * 0) * (4) + (4 * 0) * (1)], Cb_reg[3 + 4 * 0][0]);
	vst1q_f32(&Cb[(0 + 4 * 1) * (4) + (4 * 0) * (1)], Cb_reg[0 + 4 * 1][0]);
	vst1q_f32(&Cb[(1 + 4 * 1) * (4) + (4 * 0) * (1)], Cb_reg[1 + 4 * 1][0]);
	vst1q_f32(&Cb[(2 + 4 * 1) * (4) + (4 * 0) * (1)], Cb_reg[2 + 4 * 1][0]);
	vst1q_f32(&Cb[(3 + 4 * 1) * (4) + (4 * 0) * (1)], Cb_reg[3 + 4 * 1][0]);
	vst1q_f32(&Cb[(0 + 4 * 2) * (4) + (4 * 0) * (1)], Cb_reg[0 + 4 * 2][0]);
	vst1q_f32(&Cb[(1 + 4 * 2) * (4) + (4 * 0) * (1)], Cb_reg[1 + 4 * 2][0]);
	vst1q_f32(&Cb[(2 + 4 * 2) * (4) + (4 * 0) * (1)], Cb_reg[2 + 4 * 2][0]);
	vst1q_f32(&Cb[(3 + 4 * 2) * (4) + (4 * 0) * (1)], Cb_reg[3 + 4 * 2][0]);
	for (int cj = 0; cj < 12; cj++) {
		  for (int ci = 0; ci < 4; ci++) {
			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
			        }
	}
	free(Cb);
}


inline void uk_16x4_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	float32x4_t C_reg[4][4];
	C_reg[0][0] = vld1q_f32(&C[(0) * (16) + (0) * (1)]);
	C_reg[0][1] = vld1q_f32(&C[(0) * (16) + (4) * (1)]);
	C_reg[0][2] = vld1q_f32(&C[(0) * (16) + (8) * (1)]);
	C_reg[0][3] = vld1q_f32(&C[(0) * (16) + (12) * (1)]);
	C_reg[1][0] = vld1q_f32(&C[(1) * (16) + (0) * (1)]);
	C_reg[1][1] = vld1q_f32(&C[(1) * (16) + (4) * (1)]);
	C_reg[1][2] = vld1q_f32(&C[(1) * (16) + (8) * (1)]);
	C_reg[1][3] = vld1q_f32(&C[(1) * (16) + (12) * (1)]);
	C_reg[2][0] = vld1q_f32(&C[(2) * (16) + (0) * (1)]);
	C_reg[2][1] = vld1q_f32(&C[(2) * (16) + (4) * (1)]);
	C_reg[2][2] = vld1q_f32(&C[(2) * (16) + (8) * (1)]);
	C_reg[2][3] = vld1q_f32(&C[(2) * (16) + (12) * (1)]);
	C_reg[3][0] = vld1q_f32(&C[(3) * (16) + (0) * (1)]);
	C_reg[3][1] = vld1q_f32(&C[(3) * (16) + (4) * (1)]);
	C_reg[3][2] = vld1q_f32(&C[(3) * (16) + (8) * (1)]);
	C_reg[3][3] = vld1q_f32(&C[(3) * (16) + (12) * (1)]);
	float32x4_t A_reg[4];
	float32x4_t B_reg[1];
	for (int k = 0; k < KC; k++) {
		  A_reg[0] = vld1q_f32(&A[(k) * (16) + (4 * 0) * (1)]);
		    A_reg[1] = vld1q_f32(&A[(k) * (16) + (4 * 1) * (1)]);
		      A_reg[2] = vld1q_f32(&A[(k) * (16) + (4 * 2) * (1)]);
		        A_reg[3] = vld1q_f32(&A[(k) * (16) + (4 * 3) * (1)]);
			  B_reg[0] = vld1q_f32(&B[(k) * (4) + (4 * 0) * (1)]);
			    C_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
			      C_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (1));
			        C_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (2));
				  C_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (3));
				    C_reg[0 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][1], A_reg[1], B_reg[0], (0));
				      C_reg[1 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][1], A_reg[1], B_reg[0], (1));
				        C_reg[2 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][1], A_reg[1], B_reg[0], (2));
					  C_reg[3 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][1], A_reg[1], B_reg[0], (3));
					    C_reg[0 + 4 * 0][2] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][2], A_reg[2], B_reg[0], (0));
					      C_reg[1 + 4 * 0][2] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][2], A_reg[2], B_reg[0], (1));
					        C_reg[2 + 4 * 0][2] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][2], A_reg[2], B_reg[0], (2));
						  C_reg[3 + 4 * 0][2] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][2], A_reg[2], B_reg[0], (3));
						    C_reg[0 + 4 * 0][3] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][3], A_reg[3], B_reg[0], (0));
						      C_reg[1 + 4 * 0][3] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][3], A_reg[3], B_reg[0], (1));
						        C_reg[2 + 4 * 0][3] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][3], A_reg[3], B_reg[0], (2));
							  C_reg[3 + 4 * 0][3] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][3], A_reg[3], B_reg[0], (3));
	}
	vst1q_f32(&C[(0 + 4 * 0) * (16) + (4 * 0) * (1)], C_reg[0 + 4 * 0][0]);
	vst1q_f32(&C[(0 + 4 * 0) * (16) + (4 * 1) * (1)], C_reg[0 + 4 * 0][1]);
	vst1q_f32(&C[(0 + 4 * 0) * (16) + (4 * 2) * (1)], C_reg[0 + 4 * 0][2]);
	vst1q_f32(&C[(0 + 4 * 0) * (16) + (4 * 3) * (1)], C_reg[0 + 4 * 0][3]);
	vst1q_f32(&C[(1 + 4 * 0) * (16) + (4 * 0) * (1)], C_reg[1 + 4 * 0][0]);
	vst1q_f32(&C[(1 + 4 * 0) * (16) + (4 * 1) * (1)], C_reg[1 + 4 * 0][1]);
	vst1q_f32(&C[(1 + 4 * 0) * (16) + (4 * 2) * (1)], C_reg[1 + 4 * 0][2]);
	vst1q_f32(&C[(1 + 4 * 0) * (16) + (4 * 3) * (1)], C_reg[1 + 4 * 0][3]);
	vst1q_f32(&C[(2 + 4 * 0) * (16) + (4 * 0) * (1)], C_reg[2 + 4 * 0][0]);
	vst1q_f32(&C[(2 + 4 * 0) * (16) + (4 * 1) * (1)], C_reg[2 + 4 * 0][1]);
	vst1q_f32(&C[(2 + 4 * 0) * (16) + (4 * 2) * (1)], C_reg[2 + 4 * 0][2]);
	vst1q_f32(&C[(2 + 4 * 0) * (16) + (4 * 3) * (1)], C_reg[2 + 4 * 0][3]);
	vst1q_f32(&C[(3 + 4 * 0) * (16) + (4 * 0) * (1)], C_reg[3 + 4 * 0][0]);
	vst1q_f32(&C[(3 + 4 * 0) * (16) + (4 * 1) * (1)], C_reg[3 + 4 * 0][1]);
	vst1q_f32(&C[(3 + 4 * 0) * (16) + (4 * 2) * (1)], C_reg[3 + 4 * 0][2]);
	vst1q_f32(&C[(3 + 4 * 0) * (16) + (4 * 3) * (1)], C_reg[3 + 4 * 0][3]);
}

inline void uk_8x4_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	float32x4_t C_reg[4][2];
	C_reg[0][0] = vld1q_f32(&C[(0) * (8) + (0) * (1)]);
	C_reg[0][1] = vld1q_f32(&C[(0) * (8) + (4) * (1)]);
	C_reg[1][0] = vld1q_f32(&C[(1) * (8) + (0) * (1)]);
	C_reg[1][1] = vld1q_f32(&C[(1) * (8) + (4) * (1)]);
	C_reg[2][0] = vld1q_f32(&C[(2) * (8) + (0) * (1)]);
	C_reg[2][1] = vld1q_f32(&C[(2) * (8) + (4) * (1)]);
	C_reg[3][0] = vld1q_f32(&C[(3) * (8) + (0) * (1)]);
	C_reg[3][1] = vld1q_f32(&C[(3) * (8) + (4) * (1)]);
	float32x4_t A_reg[2];
	float32x4_t B_reg[1];
	for (int k = 0; k < KC; k++) {
		  A_reg[0] = vld1q_f32(&A[(k) * (8) + (4 * 0) * (1)]);
		    A_reg[1] = vld1q_f32(&A[(k) * (8) + (4 * 1) * (1)]);
		      B_reg[0] = vld1q_f32(&B[(k) * (4) + (4 * 0) * (1)]);
		        C_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
			  C_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (1));
			    C_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (2));
			      C_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (3));
			        C_reg[0 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][1], A_reg[1], B_reg[0], (0));
				  C_reg[1 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][1], A_reg[1], B_reg[0], (1));
				    C_reg[2 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][1], A_reg[1], B_reg[0], (2));
				      C_reg[3 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][1], A_reg[1], B_reg[0], (3));
	}
	vst1q_f32(&C[(0 + 4 * 0) * (8) + (4 * 0) * (1)], C_reg[0 + 4 * 0][0]);
	vst1q_f32(&C[(0 + 4 * 0) * (8) + (4 * 1) * (1)], C_reg[0 + 4 * 0][1]);
	vst1q_f32(&C[(1 + 4 * 0) * (8) + (4 * 0) * (1)], C_reg[1 + 4 * 0][0]);
	vst1q_f32(&C[(1 + 4 * 0) * (8) + (4 * 1) * (1)], C_reg[1 + 4 * 0][1]);
	vst1q_f32(&C[(2 + 4 * 0) * (8) + (4 * 0) * (1)], C_reg[2 + 4 * 0][0]);
	vst1q_f32(&C[(2 + 4 * 0) * (8) + (4 * 1) * (1)], C_reg[2 + 4 * 0][1]);
	vst1q_f32(&C[(3 + 4 * 0) * (8) + (4 * 0) * (1)], C_reg[3 + 4 * 0][0]);
	vst1q_f32(&C[(3 + 4 * 0) * (8) + (4 * 1) * (1)], C_reg[3 + 4 * 0][1]);
}

inline void uk_24x4_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	float32x4_t C_reg[4][6];
	C_reg[0][0] = vld1q_f32(&C[(0) * (24) + (0) * (1)]);
	C_reg[0][1] = vld1q_f32(&C[(0) * (24) + (4) * (1)]);
	C_reg[0][2] = vld1q_f32(&C[(0) * (24) + (8) * (1)]);
	C_reg[0][3] = vld1q_f32(&C[(0) * (24) + (12) * (1)]);
	C_reg[0][4] = vld1q_f32(&C[(0) * (24) + (16) * (1)]);
	C_reg[0][5] = vld1q_f32(&C[(0) * (24) + (20) * (1)]);
	C_reg[1][0] = vld1q_f32(&C[(1) * (24) + (0) * (1)]);
	C_reg[1][1] = vld1q_f32(&C[(1) * (24) + (4) * (1)]);
	C_reg[1][2] = vld1q_f32(&C[(1) * (24) + (8) * (1)]);
	C_reg[1][3] = vld1q_f32(&C[(1) * (24) + (12) * (1)]);
	C_reg[1][4] = vld1q_f32(&C[(1) * (24) + (16) * (1)]);
	C_reg[1][5] = vld1q_f32(&C[(1) * (24) + (20) * (1)]);
	C_reg[2][0] = vld1q_f32(&C[(2) * (24) + (0) * (1)]);
	C_reg[2][1] = vld1q_f32(&C[(2) * (24) + (4) * (1)]);
	C_reg[2][2] = vld1q_f32(&C[(2) * (24) + (8) * (1)]);
	C_reg[2][3] = vld1q_f32(&C[(2) * (24) + (12) * (1)]);
	C_reg[2][4] = vld1q_f32(&C[(2) * (24) + (16) * (1)]);
	C_reg[2][5] = vld1q_f32(&C[(2) * (24) + (20) * (1)]);
	C_reg[3][0] = vld1q_f32(&C[(3) * (24) + (0) * (1)]);
	C_reg[3][1] = vld1q_f32(&C[(3) * (24) + (4) * (1)]);
	C_reg[3][2] = vld1q_f32(&C[(3) * (24) + (8) * (1)]);
	C_reg[3][3] = vld1q_f32(&C[(3) * (24) + (12) * (1)]);
	C_reg[3][4] = vld1q_f32(&C[(3) * (24) + (16) * (1)]);
	C_reg[3][5] = vld1q_f32(&C[(3) * (24) + (20) * (1)]);
	float32x4_t A_reg[6];
	float32x4_t B_reg[1];
	for (int k = 0; k < KC; k++) {
		  A_reg[0] = vld1q_f32(&A[(k) * (24) + (4 * 0) * (1)]);
		    A_reg[1] = vld1q_f32(&A[(k) * (24) + (4 * 1) * (1)]);
		      A_reg[2] = vld1q_f32(&A[(k) * (24) + (4 * 2) * (1)]);
		        A_reg[3] = vld1q_f32(&A[(k) * (24) + (4 * 3) * (1)]);
			  A_reg[4] = vld1q_f32(&A[(k) * (24) + (4 * 4) * (1)]);
			    A_reg[5] = vld1q_f32(&A[(k) * (24) + (4 * 5) * (1)]);
			      B_reg[0] = vld1q_f32(&B[(k) * (4) + (4 * 0) * (1)]);
			        C_reg[0 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][0], A_reg[0], B_reg[0], (0));
				  C_reg[1 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][0], A_reg[0], B_reg[0], (1));
				    C_reg[2 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][0], A_reg[0], B_reg[0], (2));
				      C_reg[3 + 4 * 0][0] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][0], A_reg[0], B_reg[0], (3));
				        C_reg[0 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][1], A_reg[1], B_reg[0], (0));
					  C_reg[1 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][1], A_reg[1], B_reg[0], (1));
					    C_reg[2 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][1], A_reg[1], B_reg[0], (2));
					      C_reg[3 + 4 * 0][1] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][1], A_reg[1], B_reg[0], (3));
					        C_reg[0 + 4 * 0][2] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][2], A_reg[2], B_reg[0], (0));
						  C_reg[1 + 4 * 0][2] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][2], A_reg[2], B_reg[0], (1));
						    C_reg[2 + 4 * 0][2] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][2], A_reg[2], B_reg[0], (2));
						      C_reg[3 + 4 * 0][2] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][2], A_reg[2], B_reg[0], (3));
						        C_reg[0 + 4 * 0][3] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][3], A_reg[3], B_reg[0], (0));
							  C_reg[1 + 4 * 0][3] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][3], A_reg[3], B_reg[0], (1));
							    C_reg[2 + 4 * 0][3] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][3], A_reg[3], B_reg[0], (2));
							      C_reg[3 + 4 * 0][3] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][3], A_reg[3], B_reg[0], (3));
							        C_reg[0 + 4 * 0][4] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][4], A_reg[4], B_reg[0], (0));
								  C_reg[1 + 4 * 0][4] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][4], A_reg[4], B_reg[0], (1));
								    C_reg[2 + 4 * 0][4] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][4], A_reg[4], B_reg[0], (2));
								      C_reg[3 + 4 * 0][4] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][4], A_reg[4], B_reg[0], (3));
								        C_reg[0 + 4 * 0][5] = vfmaq_laneq_f32(C_reg[0 + 4 * 0][5], A_reg[5], B_reg[0], (0));
									  C_reg[1 + 4 * 0][5] = vfmaq_laneq_f32(C_reg[1 + 4 * 0][5], A_reg[5], B_reg[0], (1));
									    C_reg[2 + 4 * 0][5] = vfmaq_laneq_f32(C_reg[2 + 4 * 0][5], A_reg[5], B_reg[0], (2));
									      C_reg[3 + 4 * 0][5] = vfmaq_laneq_f32(C_reg[3 + 4 * 0][5], A_reg[5], B_reg[0], (3));
	}
	vst1q_f32(&C[(0 + 4 * 0) * (24) + (4 * 0) * (1)], C_reg[0 + 4 * 0][0]);
	vst1q_f32(&C[(0 + 4 * 0) * (24) + (4 * 1) * (1)], C_reg[0 + 4 * 0][1]);
	vst1q_f32(&C[(0 + 4 * 0) * (24) + (4 * 2) * (1)], C_reg[0 + 4 * 0][2]);
	vst1q_f32(&C[(0 + 4 * 0) * (24) + (4 * 3) * (1)], C_reg[0 + 4 * 0][3]);
	vst1q_f32(&C[(0 + 4 * 0) * (24) + (4 * 4) * (1)], C_reg[0 + 4 * 0][4]);
	vst1q_f32(&C[(0 + 4 * 0) * (24) + (4 * 5) * (1)], C_reg[0 + 4 * 0][5]);
	vst1q_f32(&C[(1 + 4 * 0) * (24) + (4 * 0) * (1)], C_reg[1 + 4 * 0][0]);
	vst1q_f32(&C[(1 + 4 * 0) * (24) + (4 * 1) * (1)], C_reg[1 + 4 * 0][1]);
	vst1q_f32(&C[(1 + 4 * 0) * (24) + (4 * 2) * (1)], C_reg[1 + 4 * 0][2]);
	vst1q_f32(&C[(1 + 4 * 0) * (24) + (4 * 3) * (1)], C_reg[1 + 4 * 0][3]);
	vst1q_f32(&C[(1 + 4 * 0) * (24) + (4 * 4) * (1)], C_reg[1 + 4 * 0][4]);
	vst1q_f32(&C[(1 + 4 * 0) * (24) + (4 * 5) * (1)], C_reg[1 + 4 * 0][5]);
	vst1q_f32(&C[(2 + 4 * 0) * (24) + (4 * 0) * (1)], C_reg[2 + 4 * 0][0]);
	vst1q_f32(&C[(2 + 4 * 0) * (24) + (4 * 1) * (1)], C_reg[2 + 4 * 0][1]);
	vst1q_f32(&C[(2 + 4 * 0) * (24) + (4 * 2) * (1)], C_reg[2 + 4 * 0][2]);
	vst1q_f32(&C[(2 + 4 * 0) * (24) + (4 * 3) * (1)], C_reg[2 + 4 * 0][3]);
	vst1q_f32(&C[(2 + 4 * 0) * (24) + (4 * 4) * (1)], C_reg[2 + 4 * 0][4]);
	vst1q_f32(&C[(2 + 4 * 0) * (24) + (4 * 5) * (1)], C_reg[2 + 4 * 0][5]);
	vst1q_f32(&C[(3 + 4 * 0) * (24) + (4 * 0) * (1)], C_reg[3 + 4 * 0][0]);
	vst1q_f32(&C[(3 + 4 * 0) * (24) + (4 * 1) * (1)], C_reg[3 + 4 * 0][1]);
	vst1q_f32(&C[(3 + 4 * 0) * (24) + (4 * 2) * (1)], C_reg[3 + 4 * 0][2]);
	vst1q_f32(&C[(3 + 4 * 0) * (24) + (4 * 3) * (1)], C_reg[3 + 4 * 0][3]);
	vst1q_f32(&C[(3 + 4 * 0) * (24) + (4 * 4) * (1)], C_reg[3 + 4 * 0][4]);
	vst1q_f32(&C[(3 + 4 * 0) * (24) + (4 * 5) * (1)], C_reg[3 + 4 * 0][5]);
}

/*
inline void uk_wind_16x24_a1True_b1True( void *ctxt, int_fast32_t KC, const __fp16* alpha, const __fp16* A, const __fp16* B, const __fp16* beta, struct exo_win_2f16 C ) {
	float *Cb = malloc(24 * 16 * sizeof(*Cb));
	free(Cb);
	float16x8_t C_reg[24][2];
	C_reg[0][0] = vld1q_f16(&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[0][1] = vld1q_f16(&C.data[(0) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[1][0] = vld1q_f16(&C.data[(1) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[1][1] = vld1q_f16(&C.data[(1) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[2][0] = vld1q_f16(&C.data[(2) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[2][1] = vld1q_f16(&C.data[(2) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[3][0] = vld1q_f16(&C.data[(3) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[3][1] = vld1q_f16(&C.data[(3) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[4][0] = vld1q_f16(&C.data[(4) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[4][1] = vld1q_f16(&C.data[(4) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[5][0] = vld1q_f16(&C.data[(5) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[5][1] = vld1q_f16(&C.data[(5) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[6][0] = vld1q_f16(&C.data[(6) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[6][1] = vld1q_f16(&C.data[(6) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[7][0] = vld1q_f16(&C.data[(7) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[7][1] = vld1q_f16(&C.data[(7) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[8][0] = vld1q_f16(&C.data[(8) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[8][1] = vld1q_f16(&C.data[(8) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[9][0] = vld1q_f16(&C.data[(9) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[9][1] = vld1q_f16(&C.data[(9) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[10][0] = vld1q_f16(&C.data[(10) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[10][1] = vld1q_f16(&C.data[(10) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[11][0] = vld1q_f16(&C.data[(11) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[11][0] = vld1q_f16(&C.data[(11) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[11][1] = vld1q_f16(&C.data[(11) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[12][0] = vld1q_f16(&C.data[(12) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[12][1] = vld1q_f16(&C.data[(12) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[13][0] = vld1q_f16(&C.data[(13) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[13][1] = vld1q_f16(&C.data[(13) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[14][0] = vld1q_f16(&C.data[(14) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[14][1] = vld1q_f16(&C.data[(14) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[15][0] = vld1q_f16(&C.data[(15) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[15][1] = vld1q_f16(&C.data[(15) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[16][0] = vld1q_f16(&C.data[(16) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[16][1] = vld1q_f16(&C.data[(16) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[17][0] = vld1q_f16(&C.data[(17) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[17][1] = vld1q_f16(&C.data[(17) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[18][0] = vld1q_f16(&C.data[(18) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[18][1] = vld1q_f16(&C.data[(18) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[19][0] = vld1q_f16(&C.data[(19) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[19][1] = vld1q_f16(&C.data[(19) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[20][0] = vld1q_f16(&C.data[(20) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[20][1] = vld1q_f16(&C.data[(20) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[21][0] = vld1q_f16(&C.data[(21) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[21][1] = vld1q_f16(&C.data[(21) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[22][0] = vld1q_f16(&C.data[(22) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[22][1] = vld1q_f16(&C.data[(22) * (C.strides[0]) + (8) * (C.strides[1])]);
	C_reg[23][0] = vld1q_f16(&C.data[(23) * (C.strides[0]) + (0) * (C.strides[1])]);
	C_reg[23][1] = vld1q_f16(&C.data[(23) * (C.strides[0]) + (8) * (C.strides[1])]);
	float16x8_t A_reg[2];
	float16x8_t B_reg[3];
	for (int k = 0; k < KC; k++) {
		  A_reg[0] = vld1q_f16(&A[(k) * (16) + (8 * 0) * (1)]);
		    A_reg[1] = vld1q_f16(&A[(k) * (16) + (8 * 1) * (1)]);
		      B_reg[0] = vld1q_f16(&B[(k) * (24) + (8 * 0) * (1)]);
		        B_reg[1] = vld1q_f16(&B[(k) * (24) + (8 * 1) * (1)]);
			  B_reg[2] = vld1q_f16(&B[(k) * (24) + (8 * 2) * (1)]);
			    C_reg[0 + 8 * 0][0] = vfmaq_laneq_f16(C_reg[0 + 8 * 0][0], A_reg[0], B_reg[0], (0));
			      C_reg[1 + 8 * 0][0] = vfmaq_laneq_f16(C_reg[1 + 8 * 0][0], A_reg[0], B_reg[0], (1));
			        C_reg[2 + 8 * 0][0] = vfmaq_laneq_f16(C_reg[2 + 8 * 0][0], A_reg[0], B_reg[0], (2));
				  C_reg[3 + 8 * 0][0] = vfmaq_laneq_f16(C_reg[3 + 8 * 0][0], A_reg[0], B_reg[0], (3));
				    C_reg[4 + 8 * 0][0] = vfmaq_laneq_f16(C_reg[4 + 8 * 0][0], A_reg[0], B_reg[0], (4));
				      C_reg[5 + 8 * 0][0] = vfmaq_laneq_f16(C_reg[5 + 8 * 0][0], A_reg[0], B_reg[0], (5));
				        C_reg[6 + 8 * 0][0] = vfmaq_laneq_f16(C_reg[6 + 8 * 0][0], A_reg[0], B_reg[0], (6));
					  C_reg[7 + 8 * 0][0] = vfmaq_laneq_f16(C_reg[7 + 8 * 0][0], A_reg[0], B_reg[0], (7));
					    C_reg[0 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[0 + 8 * 0][1], A_reg[1], B_reg[0], (0));
					      C_reg[1 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[1 + 8 * 0][1], A_reg[1], B_reg[0], (1));
					        C_reg[2 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[2 + 8 * 0][1], A_reg[1], B_reg[0], (2));
						  C_reg[3 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[3 + 8 * 0][1], A_reg[1], B_reg[0], (3));
						    C_reg[4 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[4 + 8 * 0][1], A_reg[1], B_reg[0], (4));
						      C_reg[5 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[5 + 8 * 0][1], A_reg[1], B_reg[0], (5));
						        C_reg[6 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[6 + 8 * 0][1], A_reg[1], B_reg[0], (6));
							  C_reg[7 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[7 + 8 * 0][1], A_reg[1], B_reg[0], (7));
							    C_reg[0 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[0 + 8 * 1][0], A_reg[0], B_reg[1], (0));
							      C_reg[1 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[1 + 8 * 1][0], A_reg[0], B_reg[1], (1));
							        C_reg[2 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[2 + 8 * 1][0], A_reg[0], B_reg[1], (2));
								  C_reg[3 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[3 + 8 * 1][0], A_reg[0], B_reg[1], (3));
								    C_reg[4 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[4 + 8 * 1][0], A_reg[0], B_reg[1], (4));
								      C_reg[5 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[5 + 8 * 0][1], A_reg[1], B_reg[0], (5));
								        C_reg[6 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[6 + 8 * 0][1], A_reg[1], B_reg[0], (6));
									  C_reg[7 + 8 * 0][1] = vfmaq_laneq_f16(C_reg[7 + 8 * 0][1], A_reg[1], B_reg[0], (7));
									    C_reg[0 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[0 + 8 * 1][0], A_reg[0], B_reg[1], (0));
									      C_reg[1 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[1 + 8 * 1][0], A_reg[0], B_reg[1], (1));
									        C_reg[2 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[2 + 8 * 1][0], A_reg[0], B_reg[1], (2));
										  C_reg[3 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[3 + 8 * 1][0], A_reg[0], B_reg[1], (3));
										    C_reg[4 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[4 + 8 * 1][0], A_reg[0], B_reg[1], (4));
										      C_reg[5 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[5 + 8 * 1][0], A_reg[0], B_reg[1], (5));
										        C_reg[6 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[6 + 8 * 1][0], A_reg[0], B_reg[1], (6));
											  C_reg[7 + 8 * 1][0] = vfmaq_laneq_f16(C_reg[7 + 8 * 1][0], A_reg[0], B_reg[1], (7));
											    C_reg[0 + 8 * 1][1] = vfmaq_laneq_f16(C_reg[0 + 8 * 1][1], A_reg[1], B_reg[1], (0));
											      C_reg[1 + 8 * 1][1] = vfmaq_laneq_f16(C_reg[1 + 8 * 1][1], A_reg[1], B_reg[1], (1));
											        C_reg[2 + 8 * 1][1] = vfmaq_laneq_f16(C_reg[2 + 8 * 1][1], A_reg[1], B_reg[1], (2));
												  C_reg[3 + 8 * 1][1] = vfmaq_laneq_f16(C_reg[3 + 8 * 1][1], A_reg[1], B_reg[1], (3));
												    C_reg[4 + 8 * 1][1] = vfmaq_laneq_f16(C_reg[4 + 8 * 1][1], A_reg[1], B_reg[1], (4));
												      C_reg[5 + 8 * 1][1] = vfmaq_laneq_f16(C_reg[5 + 8 * 1][1], A_reg[1], B_reg[1], (5));
												        C_reg[6 + 8 * 1][1] = vfmaq_laneq_f16(C_reg[6 + 8 * 1][1], A_reg[1], B_reg[1], (6));
													  C_reg[7 + 8 * 1][1] = vfmaq_laneq_f16(C_reg[7 + 8 * 1][1], A_reg[1], B_reg[1], (7));
													    C_reg[0 + 8 * 2][0] = vfmaq_laneq_f16(C_reg[0 + 8 * 2][0], A_reg[0], B_reg[2], (0));
													      C_reg[1 + 8 * 2][0] = vfmaq_laneq_f16(C_reg[1 + 8 * 2][0], A_reg[0], B_reg[2], (1));
													        C_reg[2 + 8 * 2][0] = vfmaq_laneq_f16(C_reg[2 + 8 * 2][0], A_reg[0], B_reg[2], (2));
														  C_reg[3 + 8 * 2][0] = vfmaq_laneq_f16(C_reg[3 + 8 * 2][0], A_reg[0], B_reg[2], (3));
														    C_reg[4 + 8 * 2][0] = vfmaq_laneq_f16(C_reg[4 + 8 * 2][0], A_reg[0], B_reg[2], (4));
														      C_reg[5 + 8 * 2][0] = vfmaq_laneq_f16(C_reg[5 + 8 * 2][0], A_reg[0], B_reg[2], (5));
														        C_reg[6 + 8 * 2][0] = vfmaq_laneq_f16(C_reg[6 + 8 * 2][0], A_reg[0], B_reg[2], (6));
															  C_reg[7 + 8 * 2][0] = vfmaq_laneq_f16(C_reg[7 + 8 * 2][0], A_reg[0], B_reg[2], (7));
															   C_reg[0 + 8 * 2][1] = vfmaq_laneq_f16(C_reg[0 + 8 * 2][1], A_reg[1], B_reg[2], (0));
															     C_reg[1 + 8 * 2][1] = vfmaq_laneq_f16(C_reg[1 + 8 * 2][1], A_reg[1], B_reg[2], (1));
															       C_reg[2 + 8 * 2][1] = vfmaq_laneq_f16(C_reg[2 + 8 * 2][1], A_reg[1], B_reg[2], (2));
															         C_reg[3 + 8 * 2][1] = vfmaq_laneq_f16(C_reg[3 + 8 * 2][1], A_reg[1], B_reg[2], (3));
																   C_reg[4 + 8 * 2][1] = vfmaq_laneq_f16(C_reg[4 + 8 * 2][1], A_reg[1], B_reg[2], (4));
																     C_reg[5 + 8 * 2][1] = vfmaq_laneq_f16(C_reg[5 + 8 * 2][1], A_reg[1], B_reg[2], (5));
																       C_reg[6 + 8 * 2][1] = vfmaq_laneq_f16(C_reg[6 + 8 * 2][1], A_reg[1], B_reg[2], (6));
																         C_reg[7 + 8 * 2][1] = vfmaq_laneq_f16(C_reg[7 + 8 * 2][1], A_reg[1], B_reg[2], (7));
	}
	vst1q_f16(&C.data[(0 + 8 * 0) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[0 + 8 * 0][0]);
	vst1q_f16(&C.data[(0 + 8 * 0) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[0 + 8 * 0][1]);
	vst1q_f16(&C.data[(1 + 8 * 0) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[1 + 8 * 0][0]);
	vst1q_f16(&C.data[(1 + 8 * 0) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[1 + 8 * 0][1]);
	vst1q_f16(&C.data[(2 + 8 * 0) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[2 + 8 * 0][0]);
	vst1q_f16(&C.data[(2 + 8 * 0) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[2 + 8 * 0][1]);
	vst1q_f16(&C.data[(3 + 8 * 0) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[3 + 8 * 0][0]);
	vst1q_f16(&C.data[(3 + 8 * 0) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[3 + 8 * 0][1]);
	vst1q_f16(&C.data[(4 + 8 * 0) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[4 + 8 * 0][0]);
	vst1q_f16(&C.data[(4 + 8 * 0) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[4 + 8 * 0][1]);
	vst1q_f16(&C.data[(5 + 8 * 0) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[5 + 8 * 0][0]);
	vst1q_f16(&C.data[(5 + 8 * 0) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[5 + 8 * 0][1]);
	vst1q_f16(&C.data[(6 + 8 * 0) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[6 + 8 * 0][0]);
	vst1q_f16(&C.data[(6 + 8 * 0) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[6 + 8 * 0][1]);
	vst1q_f16(&C.data[(7 + 8 * 0) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[7 + 8 * 0][0]);
	vst1q_f16(&C.data[(7 + 8 * 0) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[7 + 8 * 0][1]);
	vst1q_f16(&C.data[(0 + 8 * 1) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[0 + 8 * 1][0]);
	vst1q_f16(&C.data[(0 + 8 * 1) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[0 + 8 * 1][1]);
	vst1q_f16(&C.data[(1 + 8 * 1) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[1 + 8 * 1][0]);
	vst1q_f16(&C.data[(1 + 8 * 1) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[1 + 8 * 1][1]);
	vst1q_f16(&C.data[(2 + 8 * 1) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[2 + 8 * 1][0]);
	vst1q_f16(&C.data[(2 + 8 * 1) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[2 + 8 * 1][1]);
	vst1q_f16(&C.data[(3 + 8 * 1) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[3 + 8 * 1][0]);
	vst1q_f16(&C.data[(3 + 8 * 1) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[3 + 8 * 1][1]);
	vst1q_f16(&C.data[(4 + 8 * 1) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[4 + 8 * 1][0]);
	vst1q_f16(&C.data[(4 + 8 * 1) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[4 + 8 * 1][1]);
	vst1q_f16(&C.data[(5 + 8 * 1) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[5 + 8 * 1][0]);
	vst1q_f16(&C.data[(5 + 8 * 1) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[5 + 8 * 1][1]);
	vst1q_f16(&C.data[(6 + 8 * 1) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[6 + 8 * 1][0]);
	vst1q_f16(&C.data[(6 + 8 * 1) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[6 + 8 * 1][1]);
	vst1q_f16(&C.data[(7 + 8 * 1) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[7 + 8 * 1][0]);
	vst1q_f16(&C.data[(7 + 8 * 1) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[7 + 8 * 1][1]);
	vst1q_f16(&C.data[(0 + 8 * 2) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[0 + 8 * 2][0]);
	vst1q_f16(&C.data[(0 + 8 * 2) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[0 + 8 * 2][1]);
	vst1q_f16(&C.data[(1 + 8 * 2) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[1 + 8 * 2][0]);
	vst1q_f16(&C.data[(1 + 8 * 2) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[1 + 8 * 2][1]);
	vst1q_f16(&C.data[(2 + 8 * 2) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[2 + 8 * 2][0]);
	vst1q_f16(&C.data[(2 + 8 * 2) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[2 + 8 * 2][1]);
	vst1q_f16(&C.data[(3 + 8 * 2) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[3 + 8 * 2][0]);
	vst1q_f16(&C.data[(3 + 8 * 2) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[3 + 8 * 2][1]);
	vst1q_f16(&C.data[(4 + 8 * 2) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[4 + 8 * 2][0]);
	vst1q_f16(&C.data[(4 + 8 * 2) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[4 + 8 * 2][1]);
	vst1q_f16(&C.data[(5 + 8 * 2) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[5 + 8 * 2][0]);
	vst1q_f16(&C.data[(5 + 8 * 2) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[5 + 8 * 2][1]);
	vst1q_f16(&C.data[(6 + 8 * 2) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[6 + 8 * 2][0]);
	vst1q_f16(&C.data[(6 + 8 * 2) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[6 + 8 * 2][1]);
	vst1q_f16(&C.data[(7 + 8 * 2) * (C.strides[0]) + (8 * 0) * (C.strides[1])], C_reg[7 + 8 * 2][0]);
	vst1q_f16(&C.data[(7 + 8 * 2) * (C.strides[0]) + (8 * 1) * (C.strides[1])], C_reg[7 + 8 * 2][1]);
}
*/
