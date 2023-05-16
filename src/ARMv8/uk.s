	.arch armv8-a
	.file	"uk.c"
// GNU C17 (Ubuntu 10.3.0-1ubuntu1~18.04~1) version 10.3.0 (aarch64-linux-gnu)
//	compiled by GNU C version 10.3.0, GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0, isl version isl-0.19-GMP

// GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
// options passed:  -imultiarch aarch64-linux-gnu uk.c
// -march=armv8-a+simd+fp -mlittle-endian -mabi=lp64 -O3 -O3 -fverbose-asm
// -fasynchronous-unwind-tables -fstack-protector-strong -Wformat
// -Wformat-security
// options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
// -falign-functions -falign-jumps -falign-labels -falign-loops
// -fallocation-dce -fasynchronous-unwind-tables -fauto-inc-dec
// -fbranch-count-reg -fcaller-saves -fcode-hoisting
// -fcombine-stack-adjustments -fcommon -fcompare-elim -fcprop-registers
// -fcrossjumping -fcse-follow-jumps -fdefer-pop
// -fdelete-null-pointer-checks -fdevirtualize -fdevirtualize-speculatively
// -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-symbols
// -feliminate-unused-debug-types -fexpensive-optimizations
// -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse
// -fgcse-after-reload -fgcse-lm -fgnu-unique -fguess-branch-probability
// -fhoist-adjacent-loads -fident -fif-conversion -fif-conversion2
// -findirect-inlining -finline -finline-atomics -finline-functions
// -finline-functions-called-once -finline-small-functions -fipa-bit-cp
// -fipa-cp -fipa-cp-clone -fipa-icf -fipa-icf-functions
// -fipa-icf-variables -fipa-profile -fipa-pure-const -fipa-ra
// -fipa-reference -fipa-reference-addressable -fipa-sra
// -fipa-stack-alignment -fipa-vrp -fira-hoist-pressure
// -fira-share-save-slots -fira-share-spill-slots
// -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
// -fleading-underscore -flifetime-dse -floop-interchange
// -floop-unroll-and-jam -flra-remat -fmath-errno -fmerge-constants
// -fmerge-debug-strings -fmove-loop-invariants -fomit-frame-pointer
// -foptimize-sibling-calls -foptimize-strlen -fpartial-inlining
// -fpeel-loops -fpeephole -fpeephole2 -fplt -fpredictive-commoning
// -fprefetch-loop-arrays -free -freg-struct-return -freorder-blocks
// -freorder-functions -frerun-cse-after-loop
// -fsched-critical-path-heuristic -fsched-dep-count-heuristic
// -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
// -fsched-pressure -fsched-rank-heuristic -fsched-spec
// -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
// -fschedule-insns -fschedule-insns2 -fsection-anchors
// -fsemantic-interposition -fshow-column -fshrink-wrap
// -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
// -fsplit-loops -fsplit-paths -fsplit-wide-types -fssa-backprop
// -fssa-phiopt -fstack-protector-strong -fstdarg-opt -fstore-merging
// -fstrict-aliasing -fstrict-volatile-bitfields -fsync-libcalls
// -fthread-jumps -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp
// -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
// -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
// -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-distribute-patterns
// -ftree-loop-distribution -ftree-loop-if-convert -ftree-loop-im
// -ftree-loop-ivcanon -ftree-loop-optimize -ftree-loop-vectorize
// -ftree-parallelize-loops= -ftree-partial-pre -ftree-phiprop -ftree-pre
// -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink
// -ftree-slp-vectorize -ftree-slsr -ftree-sra -ftree-switch-conversion
// -ftree-tail-merge -ftree-ter -ftree-vrp -funit-at-a-time
// -funswitch-loops -funwind-tables -fverbose-asm
// -fversion-loops-for-strides -fzero-initialized-in-bss
// -mfix-cortex-a53-835769 -mfix-cortex-a53-843419 -mglibc -mlittle-endian
// -momit-leaf-frame-pointer -moutline-atomics -mpc-relative-literal-loads

	.text
	.align	2
	.p2align 4,,11
	.global	uk_1xX_a1True_b1False
	.type	uk_1xX_a1True_b1False, %function
uk_1xX_a1True_b1False:
.LFB4307:
	.cfi_startproc
// uk.c:19: inline void uk_1xX_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x0, x4	// B, tmp307
	mov	x7, x6	// C, tmp308
// uk.c:20: for (int k = 0; k < KC; k++) {
	cmp	x1, 0	// KC,
	ble	.L1		//,
	mov	x4, x3	// ivtmp.198, A
	mov	x6, x0	// ivtmp.200, B
	add	x8, x3, x1, lsl 5	// _212, ivtmp.198, KC,
	add	x5, x7, 384	// _36, C,
.L7:
	mov	x2, x6	// ivtmp.169, ivtmp.200
	add	x6, x6, 48	// ivtmp.200, ivtmp.200,
	cmp	x5, x2	// _36, ivtmp.169
	mov	x1, x4	// ivtmp.198, ivtmp.198
	ccmp	x7, x6, 2, hi	// C, ivtmp.200,,
	add	x4, x4, 32	// ivtmp.198, ivtmp.198,
	cset	w3, cs	// tmp240,
	cmp	x5, x1	// _36, ivtmp.198
	ccmp	x7, x4, 2, hi	// C, ivtmp.198,,
	cset	w0, cs	// tmp242,
	tst	w3, w0	// tmp240, tmp242
	beq	.L3		//,
	ldp	s20, s19, [x1, 4]	// _365, _375, MEM[base: _200, offset: 4B]
	mov	x0, x7	// ivtmp.173, C
	ldp	s18, s17, [x1, 12]	// _385, _395, MEM[base: _200, offset: 12B]
// uk.c:19: inline void uk_1xX_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x3, 0	// ivtmp.177,
	ldp	s16, s7, [x1, 20]	// _405, _415, MEM[base: _200, offset: 20B]
	dup	v20.4s, v20.s[0]	// vect_cst__366, _365
	ldr	s6, [x1, 28]	// _425, MEM[base: _200, offset: 28B]
	dup	v19.4s, v19.s[0]	// vect_cst__376, _375
	ld1r	{v21.4s}, [x1]	// vect_cst__356, MEM[base: _200, offset: 0B]
	dup	v18.4s, v18.s[0]	// vect_cst__386, _385
	dup	v17.4s, v17.s[0]	// vect_cst__396, _395
	dup	v16.4s, v16.s[0]	// vect_cst__406, _405
	dup	v7.4s, v7.s[0]	// vect_cst__416, _415
	dup	v6.4s, v6.s[0]	// vect_cst__426, _425
.L4:
// uk.c:23:       C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
	ldp	q2, q0, [x0]	// MEM[base: _50, offset: 0B], MEM[base: _50, offset: 16B], MEM[base: _50, offset: 0B]
	ldp	q23, q3, [x0, 32]	// MEM[base: _50, offset: 32B], MEM[base: _50, offset: 48B], MEM[base: _50, offset: 32B]
	ldp	q5, q24, [x0, 64]	// MEM[base: _50, offset: 64B], MEM[base: _50, offset: 80B], MEM[base: _50, offset: 64B]
	ldp	q22, q1, [x0, 96]	// MEM[base: _50, offset: 96B], MEM[base: _50, offset: 112B], MEM[base: _50, offset: 96B]
	uzp1	v4.4s, v2.4s, v0.4s	// vect_perm_even_331, MEM[base: _50, offset: 0B], MEM[base: _50, offset: 16B]
	uzp2	v2.4s, v2.4s, v0.4s	// vect_perm_odd_332, MEM[base: _50, offset: 0B], MEM[base: _50, offset: 16B]
	uzp1	v0.4s, v23.4s, v3.4s	// vect_perm_even_333, MEM[base: _50, offset: 32B], MEM[base: _50, offset: 48B]
	uzp2	v23.4s, v23.4s, v3.4s	// vect_perm_odd_334, MEM[base: _50, offset: 32B], MEM[base: _50, offset: 48B]
	uzp1	v3.4s, v5.4s, v24.4s	// vect_perm_even_335, MEM[base: _50, offset: 64B], MEM[base: _50, offset: 80B]
	uzp2	v5.4s, v5.4s, v24.4s	// vect_perm_odd_336, MEM[base: _50, offset: 64B], MEM[base: _50, offset: 80B]
	uzp1	v24.4s, v22.4s, v1.4s	// vect_perm_even_337, MEM[base: _50, offset: 96B], MEM[base: _50, offset: 112B]
	uzp2	v22.4s, v22.4s, v1.4s	// vect_perm_odd_338, MEM[base: _50, offset: 96B], MEM[base: _50, offset: 112B]
	uzp1	v1.4s, v4.4s, v0.4s	// vect_perm_even_339, vect_perm_even_331, vect_perm_even_333
	uzp2	v4.4s, v4.4s, v0.4s	// vect_perm_odd_340, vect_perm_even_331, vect_perm_even_333
	uzp1	v0.4s, v3.4s, v24.4s	// vect_perm_even_341, vect_perm_even_335, vect_perm_even_337
	uzp1	v26.4s, v5.4s, v22.4s	// vect_perm_even_345, vect_perm_odd_336, vect_perm_odd_338
	uzp2	v3.4s, v3.4s, v24.4s	// vect_perm_odd_342, vect_perm_even_335, vect_perm_even_337
	uzp2	v5.4s, v5.4s, v22.4s	// vect_perm_odd_346, vect_perm_odd_336, vect_perm_odd_338
	uzp1	v24.4s, v2.4s, v23.4s	// vect_perm_even_343, vect_perm_odd_332, vect_perm_odd_334
	uzp2	v2.4s, v2.4s, v23.4s	// vect_perm_odd_344, vect_perm_odd_332, vect_perm_odd_334
	uzp2	v25.4s, v1.4s, v0.4s	// vect_perm_odd_348, vect_perm_even_339, vect_perm_even_341
	uzp1	v0.4s, v1.4s, v0.4s	// tmp271, vect_perm_even_339, vect_perm_even_341
	uzp1	v23.4s, v4.4s, v3.4s	// vect_perm_even_351, vect_perm_odd_340, vect_perm_odd_342
	uzp1	v22.4s, v2.4s, v5.4s	// vect_perm_even_353, vect_perm_odd_344, vect_perm_odd_346
	uzp2	v2.4s, v2.4s, v5.4s	// vect_perm_odd_354, vect_perm_odd_344, vect_perm_odd_346
// uk.c:23:       C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
	ldr	q5, [x2, x3]	// MEM[base: _208, index: ivtmp.177_53, offset: 0B], MEM[base: _208, index: ivtmp.177_53, offset: 0B]
	add	x3, x3, 16	// ivtmp.177, ivtmp.177,
// uk.c:23:       C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
	uzp2	v4.4s, v4.4s, v3.4s	// vect_perm_odd_352, vect_perm_odd_340, vect_perm_odd_342
	uzp1	v3.4s, v24.4s, v26.4s	// vect_perm_even_349, vect_perm_even_343, vect_perm_even_345
	fmla	v0.4s, v21.4s, v5.4s	// tmp271, vect_cst__356, MEM[base: _208, index: ivtmp.177_53, offset: 0B]
	uzp2	v24.4s, v24.4s, v26.4s	// vect_perm_odd_350, vect_perm_even_343, vect_perm_even_345
	fmla	v23.4s, v5.4s, v19.4s	// vect__106.134, MEM[base: _208, index: ivtmp.177_53, offset: 0B], vect_cst__376
	fmla	v3.4s, v5.4s, v20.4s	// vect__82.129, MEM[base: _208, index: ivtmp.177_53, offset: 0B], vect_cst__366
	mov	v1.16b, v0.16b	// vect__58.124, tmp271
	mov	v0.16b, v25.16b	// vect_perm_odd_348, vect_perm_odd_348
	fmla	v24.4s, v5.4s, v16.4s	// vect__178.149, MEM[base: _208, index: ivtmp.177_53, offset: 0B], vect_cst__406
	fmla	v22.4s, v5.4s, v18.4s	// vect__130.139, MEM[base: _208, index: ivtmp.177_53, offset: 0B], vect_cst__386
	fmla	v4.4s, v5.4s, v7.4s	// vect__202.154, MEM[base: _208, index: ivtmp.177_53, offset: 0B], vect_cst__416
	fmla	v2.4s, v5.4s, v6.4s	// vect__226.159, MEM[base: _208, index: ivtmp.177_53, offset: 0B], vect_cst__426
	fmla	v0.4s, v5.4s, v17.4s	// vect_perm_odd_348, MEM[base: _208, index: ivtmp.177_53, offset: 0B], vect_cst__396
	zip1	v25.4s, v23.4s, v4.4s	// vect_inter_high_441, vect__106.134, vect__202.154
	zip1	v26.4s, v22.4s, v2.4s	// vect_inter_high_443, vect__130.139, vect__226.159
	zip1	v5.4s, v1.4s, v0.4s	// vect_inter_high_437, vect__58.124, vect__154.144
	zip2	v4.4s, v23.4s, v4.4s	// vect_inter_low_442, vect__106.134, vect__202.154
	zip1	v23.4s, v3.4s, v24.4s	// vect_inter_high_439, vect__82.129, vect__178.149
	zip2	v0.4s, v1.4s, v0.4s	// vect_inter_low_438, vect__58.124, vect__154.144
	zip2	v2.4s, v22.4s, v2.4s	// vect_inter_low_444, vect__130.139, vect__226.159
	zip2	v1.4s, v3.4s, v24.4s	// vect_inter_low_440, vect__82.129, vect__178.149
	zip1	v24.4s, v5.4s, v25.4s	// vect_inter_high_445, vect_inter_high_437, vect_inter_high_441
	zip2	v3.4s, v5.4s, v25.4s	// vect_inter_low_446, vect_inter_high_437, vect_inter_high_441
	zip1	v25.4s, v23.4s, v26.4s	// vect_inter_high_449, vect_inter_high_439, vect_inter_high_443
	zip1	v22.4s, v0.4s, v4.4s	// vect_inter_high_447, vect_inter_low_438, vect_inter_low_442
	zip2	v5.4s, v23.4s, v26.4s	// vect_inter_low_450, vect_inter_high_439, vect_inter_high_443
	zip2	v0.4s, v0.4s, v4.4s	// vect_inter_low_448, vect_inter_low_438, vect_inter_low_442
	zip1	v4.4s, v1.4s, v2.4s	// vect_inter_high_451, vect_inter_low_440, vect_inter_low_444
	zip2	v2.4s, v1.4s, v2.4s	// vect_inter_low_452, vect_inter_low_440, vect_inter_low_444
	zip1	v1.4s, v24.4s, v25.4s	// tmp272, vect_inter_high_445, vect_inter_high_449
	zip2	v24.4s, v24.4s, v25.4s	// tmp273, vect_inter_high_445, vect_inter_high_449
	zip1	v23.4s, v3.4s, v5.4s	// tmp274, vect_inter_low_446, vect_inter_low_450
	zip2	v3.4s, v3.4s, v5.4s	// tmp275, vect_inter_low_446, vect_inter_low_450
	zip1	v5.4s, v22.4s, v4.4s	// tmp276, vect_inter_high_447, vect_inter_high_451
	zip2	v22.4s, v22.4s, v4.4s	// tmp277, vect_inter_high_447, vect_inter_high_451
	stp	q1, q24, [x0]	// tmp272, tmp273, MEM[base: _50, offset: 0B]
	zip1	v1.4s, v0.4s, v2.4s	// tmp278, vect_inter_low_448, vect_inter_low_452
	stp	q23, q3, [x0, 32]	// tmp274, tmp275, MEM[base: _50, offset: 32B]
	zip2	v0.4s, v0.4s, v2.4s	// tmp279, vect_inter_low_448, vect_inter_low_452
	stp	q5, q22, [x0, 64]	// tmp276, tmp277, MEM[base: _50, offset: 64B]
	stp	q1, q0, [x0, 96]	// tmp278, tmp279, MEM[base: _50, offset: 96B]
	add	x0, x0, 128	// ivtmp.173, ivtmp.173,
	cmp	x3, 48	// ivtmp.177,
	bne	.L4		//,
// uk.c:20: for (int k = 0; k < KC; k++) {
	cmp	x4, x8	// ivtmp.198, _212
	bne	.L7		//,
.L1:
// uk.c:27: }
	ret	
.L3:
	mov	x0, x7	// ivtmp.168, C
	.p2align 3,,7
.L6:
// uk.c:23:       C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
	ldp	s7, s6, [x0]	// MEM[base: _122, offset: 0B], MEM[base: _122, offset: 4B], MEM[base: _122, offset: 0B]
	ldr	s1, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s0, [x1]	// MEM[base: _200, offset: 0B], MEM[base: _200, offset: 0B]
	ldp	s5, s4, [x0, 8]	// MEM[base: _122, offset: 8B], MEM[base: _122, offset: 12B], MEM[base: _122, offset: 8B]
	fmadd	s7, s1, s0, s7	// _255, MEM[base: _81, offset: 0B], MEM[base: _200, offset: 0B], MEM[base: _122, offset: 0B]
	ldp	s3, s2, [x0, 16]	// MEM[base: _122, offset: 16B], MEM[base: _122, offset: 20B], MEM[base: _122, offset: 16B]
	ldp	s1, s0, [x0, 24]	// MEM[base: _122, offset: 24B], MEM[base: _122, offset: 28B], MEM[base: _122, offset: 24B]
// uk.c:21:   for (int j = 0; j < 12; j++) {
	add	x0, x0, 32	// ivtmp.168, ivtmp.168,
// uk.c:23:       C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
	str	s7, [x0, -32]	// _255, MEM[base: _122, offset: 0B]
	ldr	s7, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s16, [x1, 4]	// MEM[base: _200, offset: 4B], MEM[base: _200, offset: 4B]
	fmadd	s6, s16, s7, s6	// _247, MEM[base: _200, offset: 4B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 4B]
	str	s6, [x0, -28]	// _247, MEM[base: _122, offset: 4B]
	ldr	s6, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s7, [x1, 8]	// MEM[base: _200, offset: 8B], MEM[base: _200, offset: 8B]
	fmadd	s5, s7, s6, s5	// _239, MEM[base: _200, offset: 8B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 8B]
	str	s5, [x0, -24]	// _239, MEM[base: _122, offset: 8B]
	ldr	s6, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s5, [x1, 12]	// MEM[base: _200, offset: 12B], MEM[base: _200, offset: 12B]
	fmadd	s4, s6, s5, s4	// _230, MEM[base: _81, offset: 0B], MEM[base: _200, offset: 12B], MEM[base: _122, offset: 12B]
	str	s4, [x0, -20]	// _230, MEM[base: _122, offset: 12B]
	ldr	s4, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s5, [x1, 16]	// MEM[base: _200, offset: 16B], MEM[base: _200, offset: 16B]
	fmadd	s3, s5, s4, s3	// _197, MEM[base: _200, offset: 16B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 16B]
	str	s3, [x0, -16]	// _197, MEM[base: _122, offset: 16B]
	ldr	s3, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s4, [x1, 20]	// MEM[base: _200, offset: 20B], MEM[base: _200, offset: 20B]
	fmadd	s2, s4, s3, s2	// _289, MEM[base: _200, offset: 20B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 20B]
	str	s2, [x0, -12]	// _289, MEM[base: _122, offset: 20B]
	ldr	s2, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s3, [x1, 24]	// MEM[base: _200, offset: 24B], MEM[base: _200, offset: 24B]
	fmadd	s1, s3, s2, s1	// _299, MEM[base: _200, offset: 24B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 24B]
	str	s1, [x0, -8]	// _299, MEM[base: _122, offset: 24B]
	ldr	s1, [x2], 4	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s2, [x1, 28]	// MEM[base: _200, offset: 28B], MEM[base: _200, offset: 28B]
	fmadd	s0, s2, s1, s0	// _309, MEM[base: _200, offset: 28B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 28B]
	str	s0, [x0, -4]	// _309, MEM[base: _122, offset: 28B]
// uk.c:21:   for (int j = 0; j < 12; j++) {
	cmp	x5, x0	// _36, ivtmp.168
	bne	.L6		//,
// uk.c:20: for (int k = 0; k < KC; k++) {
	cmp	x4, x8	// ivtmp.198, _212
	bne	.L7		//,
	b	.L1		//
	.cfi_endproc
.LFE4307:
	.size	uk_1xX_a1True_b1False, .-uk_1xX_a1True_b1False
	.align	2
	.p2align 4,,11
	.global	uk_wind_8x12_a1True_b1False
	.type	uk_wind_8x12_a1True_b1False, %function
uk_wind_8x12_a1True_b1False:
.LFB4308:
	.cfi_startproc
	stp	x29, x30, [sp, -112]!	//,,,
	.cfi_def_cfa_offset 112
	.cfi_offset 29, -112
	.cfi_offset 30, -104
// uk.c:29: 	float *Cb = malloc(12 * 8 * sizeof(*Cb));
	mov	x0, 384	//,
// uk.c:28: void uk_wind_8x12_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, struct exo_win_2f32 C ) {
	mov	x29, sp	//,
	stp	x19, x20, [sp, 16]	//,,
	.cfi_offset 19, -96
	.cfi_offset 20, -88
	mov	x20, x4	// B, tmp481
	stp	x23, x24, [sp, 48]	//,,
	.cfi_offset 23, -64
	.cfi_offset 24, -56
	mov	x24, x1	// KC, tmp479
	ldp	x19, x23, [x6]	// C$data, C$strides$0, C.data
	stp	x21, x22, [sp, 32]	//,,
	.cfi_offset 21, -80
	.cfi_offset 22, -72
	mov	x21, x3	// A, tmp480
	stp	d8, d9, [sp, 80]	//,,
	stp	d10, d11, [sp, 96]	//,,
	ldr	x22, [x6, 16]	// C$strides$1, C.strides[1]
	str	x25, [sp, 64]	//,
	.cfi_offset 72, -32
	.cfi_offset 73, -24
	.cfi_offset 74, -16
	.cfi_offset 75, -8
	.cfi_offset 25, -48
	mov	x25, x5	// beta, tmp482
	str	d12, [sp, 72]	//,
	.cfi_offset 76, -40
// uk.c:29: 	float *Cb = malloc(12 * 8 * sizeof(*Cb));
	bl	malloc		//
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	lsl	x1, x23, 1	// _776, C$strides$0,
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	lsl	x5, x22, 2	// tmp478, C$strides$1,
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x10, x23, x1	// _798, C$strides$0, _776
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x1, x5, x1	// tmp374, tmp478, _776
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x9, x23, x10	// _820, C$strides$0, _798
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x12, x23, x5	// tmp369, C$strides$0, tmp478
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x8, x23, x9	// _842, C$strides$0, _820
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	lsl	x3, x1, 2	// tmp375, tmp374,
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x7, x23, x8	// _864, C$strides$0, _842
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	lsl	x12, x12, 2	// tmp370, tmp369,
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x6, x23, x7	// _886, C$strides$0, _864
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x18, x5, x10	// tmp379, tmp478, _798
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x2, x23, x6	// _908, C$strides$0, _886
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	lsl	x10, x10, 2	// tmp377, _798,
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x4, x23, x2	// _930, C$strides$0, _908
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x17, x5, x9	// tmp384, tmp478, _820
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x1, x23, x4	// _952, C$strides$0, _930
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x16, x5, x8	// tmp389, tmp478, _842
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x11, x23, x1	// _562, C$strides$0, _952
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x15, x5, x7	// tmp394, tmp478, _864
	add	x30, x11, x5	// tmp419, _562, tmp478
	add	x14, x5, x6	// tmp399, tmp478, _886
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	lsl	x11, x11, 2	// tmp417, _562,
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x13, x5, x2	// tmp404, tmp478, _908
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q31, [x19, x3]	// _787,
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x3, x5, x1	// tmp414, tmp478, _952
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q9, [x19, x12]	// _765,
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	add	x12, x5, x4	// tmp409, tmp478, _930
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:15603:   return (float32x4_t) {__a, __a, __a, __a};
	ld1r	{v0.4s}, [x25]	// tmp364, MEM[(const float32_t *)beta_144(D)]
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	lsl	x25, x22, 4	// tmp366, C$strides$1,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q30, [x19, x10]	// _803,
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	lsl	x10, x23, 2	// _756, C$strides$0,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q7, [x19, x11]	// _571,
// uk.c:36: 			      C_reg[cit] = vld1q_f32(&C.data[(cj) * (C.strides[0]) + (4 * cit) * (C.strides[1])]);
	lsl	x11, x23, 3	// tmp372, C$strides$0,
	lsl	x18, x18, 2	// tmp380, tmp379,
	lsl	x30, x30, 2	// tmp420, tmp419,
	lsl	x9, x9, 2	// tmp382, _820,
	lsl	x17, x17, 2	// tmp385, tmp384,
	lsl	x8, x8, 2	// tmp387, _842,
	lsl	x16, x16, 2	// tmp390, tmp389,
	lsl	x7, x7, 2	// tmp392, _864,
	lsl	x15, x15, 2	// tmp395, tmp394,
	lsl	x6, x6, 2	// tmp397, _886,
	lsl	x14, x14, 2	// tmp400, tmp399,
	lsl	x2, x2, 2	// tmp402, _908,
	lsl	x13, x13, 2	// tmp405, tmp404,
	lsl	x4, x4, 2	// tmp407, _930,
	lsl	x12, x12, 2	// tmp410, tmp409,
	lsl	x1, x1, 2	// tmp412, _952,
	lsl	x3, x3, 2	// tmp415, tmp414,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q11, [x19, x25]	// _743,
	ldr	q10, [x19, x10]	// _759,* _756
	ldr	q8, [x19, x11]	// _781,
	ldr	q12, [x19]	// _106,* C$data
	ldr	q6, [x19, x30]	// _586,
	ldr	q29, [x19, x18]	// _809,
	ldr	q28, [x19, x9]	// _825,
	ldr	q27, [x19, x17]	// _831,
	ldr	q26, [x19, x8]	// _847,
	ldr	q25, [x19, x16]	// _853,
	ldr	q24, [x19, x7]	// _869,
	ldr	q23, [x19, x15]	// _875,
	ldr	q22, [x19, x6]	// _891,
	ldr	q21, [x19, x14]	// _897,
	ldr	q20, [x19, x2]	// _913,
	ldr	q19, [x19, x13]	// _919,
	ldr	q18, [x19, x4]	// _935,
	ldr	q17, [x19, x12]	// _941,
	ldr	q16, [x19, x1]	// _957,
	ldr	q1, [x19, x3]	// _963,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v31.4s, v0.4s, v31.4s	// tmp427, tmp364, _787
	fmul	v11.4s, v0.4s, v11.4s	// tmp423, tmp364, _743
	fmul	v10.4s, v0.4s, v10.4s	// tmp424, tmp364, _759
	fmul	v9.4s, v0.4s, v9.4s	// tmp425, tmp364, _765
	fmul	v8.4s, v0.4s, v8.4s	// tmp426, tmp364, _781
	fmul	v12.4s, v12.4s, v0.4s	// tmp422, _106, tmp364
	fmul	v30.4s, v0.4s, v30.4s	// tmp428, tmp364, _803
	fmul	v6.4s, v0.4s, v6.4s	// tmp445, tmp364, _586
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q10, q9, [x0, 32]	// tmp424, tmp425,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v7.4s, v0.4s, v7.4s	// tmp444, tmp364, _571
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q12, q11, [x0]	// tmp422, tmp423,* Cb
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v29.4s, v0.4s, v29.4s	// tmp429, tmp364, _809
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q8, q31, [x0, 64]	// tmp426, tmp427,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v28.4s, v0.4s, v28.4s	// tmp430, tmp364, _825
	fmul	v27.4s, v0.4s, v27.4s	// tmp431, tmp364, _831
	fmul	v26.4s, v0.4s, v26.4s	// tmp432, tmp364, _847
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q30, q29, [x0, 96]	// tmp428, tmp429,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v25.4s, v0.4s, v25.4s	// tmp433, tmp364, _853
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q7, q6, [x0, 352]	// tmp444, tmp445,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v24.4s, v0.4s, v24.4s	// tmp434, tmp364, _869
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q28, q27, [x0, 128]	// tmp430, tmp431,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v23.4s, v0.4s, v23.4s	// tmp435, tmp364, _875
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q26, q25, [x0, 160]	// tmp432, tmp433,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v22.4s, v0.4s, v22.4s	// tmp436, tmp364, _891
	fmul	v21.4s, v0.4s, v21.4s	// tmp437, tmp364, _897
	fmul	v20.4s, v0.4s, v20.4s	// tmp438, tmp364, _913
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q24, q23, [x0, 192]	// tmp434, tmp435,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v19.4s, v0.4s, v19.4s	// tmp439, tmp364, _919
	fmul	v18.4s, v0.4s, v18.4s	// tmp440, tmp364, _935
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q22, q21, [x0, 224]	// tmp436, tmp437,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v17.4s, v0.4s, v17.4s	// tmp441, tmp364, _941
	fmul	v16.4s, v0.4s, v16.4s	// tmp442, tmp364, _957
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q20, q19, [x0, 256]	// tmp438, tmp439,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v0.4s, v0.4s, v1.4s	// tmp443, tmp364, _963
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q18, q17, [x0, 288]	// tmp440, tmp441,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	mov	v5.16b, v0.16b	// _242, tmp443
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q16, q0, [x0, 320]	// tmp442, tmp443,
// uk.c:73: 	for (int k = 0; k < KC; k++) {
	cmp	x24, 0	// KC,
	ble	.L13		//,
	mov	x3, x21	// ivtmp.246, A
	mov	x2, x20	// ivtmp.248, B
	mov	x4, 0	// ivtmp.244,
	.p2align 3,,7
.L14:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q1, q0, [x3]	// _272, _271,* ivtmp.246
// uk.c:73: 	for (int k = 0; k < KC; k++) {
	add	x4, x4, 1	// ivtmp.244, ivtmp.244,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q4, q3, [x2]	// _270, _269,* ivtmp.248
// uk.c:73: 	for (int k = 0; k < KC; k++) {
	add	x3, x3, 32	// ivtmp.246, ivtmp.246,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q2, [x2, 32]	// _268,
// uk.c:73: 	for (int k = 0; k < KC; k++) {
	add	x2, x2, 48	// ivtmp.248, ivtmp.248,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:16810:   return __builtin_aarch64_fmav4sf (__b,
	fmla	v12.4s, v1.4s, v4.s[0]	// _267, _272, _270,
	fmla	v10.4s, v1.4s, v4.s[1]	// _265, _272, _270,
	fmla	v8.4s, v1.4s, v4.s[2]	// _263, _272, _270,
	fmla	v30.4s, v1.4s, v4.s[3]	// _261, _272, _270,
	fmla	v11.4s, v0.4s, v4.s[0]	// _260, _271, _270,
	fmla	v9.4s, v0.4s, v4.s[1]	// _259, _271, _270,
	fmla	v31.4s, v0.4s, v4.s[2]	// _258, _271, _270,
	fmla	v29.4s, v0.4s, v4.s[3]	// _257, _271, _270,
	fmla	v28.4s, v1.4s, v3.s[0]	// _256, _272, _269,
	fmla	v26.4s, v1.4s, v3.s[1]	// _255, _272, _269,
	fmla	v24.4s, v1.4s, v3.s[2]	// _254, _272, _269,
	fmla	v22.4s, v1.4s, v3.s[3]	// _253, _272, _269,
	fmla	v27.4s, v0.4s, v3.s[0]	// _252, _271, _269,
	fmla	v25.4s, v0.4s, v3.s[1]	// _251, _271, _269,
	fmla	v23.4s, v0.4s, v3.s[2]	// _250, _271, _269,
	fmla	v21.4s, v0.4s, v3.s[3]	// _249, _271, _269,
	fmla	v20.4s, v1.4s, v2.s[0]	// _248, _272, _268,
	fmla	v18.4s, v1.4s, v2.s[1]	// _247, _272, _268,
	fmla	v16.4s, v1.4s, v2.s[2]	// _246, _272, _268,
	fmla	v7.4s, v1.4s, v2.s[3]	// _245, _272, _268,
	fmla	v19.4s, v0.4s, v2.s[0]	// _244, _271, _268,
	fmla	v17.4s, v0.4s, v2.s[1]	// _243, _271, _268,
	fmla	v5.4s, v0.4s, v2.s[2]	// _242, _271, _268,
	fmla	v6.4s, v0.4s, v2.s[3]	// _241, _271, _268,
// uk.c:73: 	for (int k = 0; k < KC; k++) {
	cmp	x4, x24	// ivtmp.244, KC
	bne	.L14		//,
.L13:
// uk.c:130: 			      C.data[(cj) * (C.strides[0]) + (ci) * (C.strides[1])] = Cb[(cj) * (8) + (ci) * (1)];
	lsl	x4, x22, 1	// _427, C$strides$1,
	lsl	x3, x22, 3	// tmp460, C$strides$1,
	add	x6, x4, x22	// _445, _427, C$strides$1
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q12, q11, [x0]	// _267, _260,* Cb
// uk.c:130: 			      C.data[(cj) * (C.strides[0]) + (ci) * (C.strides[1])] = Cb[(cj) * (8) + (ci) * (1)];
	sub	x3, x3, x22	// _517, tmp460, C$strides$1
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q10, q9, [x0, 32]	// _265, _259,
// uk.c:130: 			      C.data[(cj) * (C.strides[0]) + (ci) * (C.strides[1])] = Cb[(cj) * (8) + (ci) * (1)];
	lsl	x8, x6, 1	// tmp458, _445,
	add	x7, x5, x22	// _481, tmp478, C$strides$1
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q8, q31, [x0, 64]	// _263, _258,
	mov	x1, x19	// ivtmp.218, C$data
	mov	x2, x0	// ivtmp.217, Cb
	stp	q30, q29, [x0, 96]	// _261, _257,
	add	x9, x0, 384	// _1, Cb,
	stp	q28, q27, [x0, 128]	// _256, _252,
	stp	q26, q25, [x0, 160]	// _255, _251,
	stp	q24, q23, [x0, 192]	// _254, _250,
	stp	q22, q21, [x0, 224]	// _253, _249,
	stp	q20, q19, [x0, 256]	// _248, _244,
	stp	q18, q17, [x0, 288]	// _247, _243,
	stp	q16, q5, [x0, 320]	// _246, _242,
	stp	q7, q6, [x0, 352]	// _245, _241,
	cmp	x23, 1	// C$strides$0,
	bne	.L16		//,
	.p2align 3,,7
.L18:
// uk.c:130: 			      C.data[(cj) * (C.strides[0]) + (ci) * (C.strides[1])] = Cb[(cj) * (8) + (ci) * (1)];
	ldp	s1, s0, [x2]	// MEM[base: _515, offset: 0B], MEM[base: _515, offset: 4B], MEM[base: _515, offset: 0B]
	ldr	s2, [x2, 8]	// MEM[base: _515, offset: 8B], MEM[base: _515, offset: 8B]
	str	s1, [x1]	// MEM[base: _515, offset: 0B], MEM[base: _672, offset: 0B]
	str	s0, [x1, x22, lsl 2]	// MEM[base: _515, offset: 4B], MEM[base: _672, index: _480, step: 4, offset: 0B]
	ldp	s1, s0, [x2, 12]	// MEM[base: _515, offset: 12B], MEM[base: _515, offset: 16B], MEM[base: _515, offset: 12B]
	str	s2, [x1, x4, lsl 2]	// MEM[base: _515, offset: 8B], MEM[base: _672, index: _436, step: 4, offset: 0B]
	ldr	s2, [x2, 20]	// MEM[base: _515, offset: 20B], MEM[base: _515, offset: 20B]
	str	s1, [x1, x6, lsl 2]	// MEM[base: _515, offset: 12B], MEM[base: _672, index: _434, step: 4, offset: 0B]
	str	s0, [x1, x5, lsl 2]	// MEM[base: _515, offset: 16B], MEM[base: _672, index: _108, step: 4, offset: 0B]
	ldp	s1, s0, [x2, 24]	// MEM[base: _515, offset: 24B], MEM[base: _515, offset: 28B], MEM[base: _515, offset: 24B]
	str	s2, [x1, x7, lsl 2]	// MEM[base: _515, offset: 20B], MEM[base: _672, index: _133, step: 4, offset: 0B]
// uk.c:128: 	for (int cj = 0; cj < 12; cj++) {
	add	x2, x2, 32	// ivtmp.217, ivtmp.217,
// uk.c:130: 			      C.data[(cj) * (C.strides[0]) + (ci) * (C.strides[1])] = Cb[(cj) * (8) + (ci) * (1)];
	str	s1, [x1, x8, lsl 2]	// MEM[base: _515, offset: 24B], MEM[base: _672, index: _131, step: 4, offset: 0B]
	str	s0, [x1, x3, lsl 2]	// MEM[base: _515, offset: 28B], MEM[base: _672, index: _112, step: 4, offset: 0B]
// uk.c:128: 	for (int cj = 0; cj < 12; cj++) {
	add	x1, x1, 4	// ivtmp.218, ivtmp.218,
	cmp	x9, x2	// _1, ivtmp.217
	bne	.L18		//,
.L17:
// uk.c:134: }
	ldp	x19, x20, [sp, 16]	//,,
	ldp	x21, x22, [sp, 32]	//,,
	ldp	x23, x24, [sp, 48]	//,,
	ldr	x25, [sp, 64]	//,
	ldr	d12, [sp, 72]	//,
	ldp	d8, d9, [sp, 80]	//,,
	ldp	d10, d11, [sp, 96]	//,,
	ldp	x29, x30, [sp], 112	//,,,
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 25
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 76
	.cfi_restore 74
	.cfi_restore 75
	.cfi_restore 72
	.cfi_restore 73
	.cfi_def_cfa_offset 0
// uk.c:133: 	free(Cb);
	b	free		//
	.p2align 2,,3
.L16:
	.cfi_restore_state
// uk.c:130: 			      C.data[(cj) * (C.strides[0]) + (ci) * (C.strides[1])] = Cb[(cj) * (8) + (ci) * (1)];
	ldp	s1, s0, [x2]	// MEM[base: _950, offset: 0B], MEM[base: _950, offset: 4B], MEM[base: _950, offset: 0B]
	ldr	s2, [x2, 8]	// MEM[base: _950, offset: 8B], MEM[base: _950, offset: 8B]
	str	s1, [x1]	// MEM[base: _950, offset: 0B], MEM[base: _904, offset: 0B]
	str	s0, [x1, x22, lsl 2]	// MEM[base: _950, offset: 4B], MEM[base: _904, index: _883, step: 4, offset: 0B]
	ldp	s1, s0, [x2, 12]	// MEM[base: _950, offset: 12B], MEM[base: _950, offset: 16B], MEM[base: _950, offset: 12B]
	str	s2, [x1, x4, lsl 2]	// MEM[base: _950, offset: 8B], MEM[base: _904, index: _862, step: 4, offset: 0B]
	ldr	s2, [x2, 20]	// MEM[base: _950, offset: 20B], MEM[base: _950, offset: 20B]
	str	s1, [x1, x6, lsl 2]	// MEM[base: _950, offset: 12B], MEM[base: _904, index: _860, step: 4, offset: 0B]
	str	s0, [x1, x5, lsl 2]	// MEM[base: _950, offset: 16B], MEM[base: _904, index: _108, step: 4, offset: 0B]
	ldp	s1, s0, [x2, 24]	// MEM[base: _950, offset: 24B], MEM[base: _950, offset: 28B], MEM[base: _950, offset: 24B]
	str	s2, [x1, x7, lsl 2]	// MEM[base: _950, offset: 20B], MEM[base: _904, index: _818, step: 4, offset: 0B]
// uk.c:128: 	for (int cj = 0; cj < 12; cj++) {
	add	x2, x2, 32	// ivtmp.233, ivtmp.233,
// uk.c:130: 			      C.data[(cj) * (C.strides[0]) + (ci) * (C.strides[1])] = Cb[(cj) * (8) + (ci) * (1)];
	str	s1, [x1, x8, lsl 2]	// MEM[base: _950, offset: 24B], MEM[base: _904, index: _816, step: 4, offset: 0B]
	str	s0, [x1, x3, lsl 2]	// MEM[base: _950, offset: 28B], MEM[base: _904, index: _795, step: 4, offset: 0B]
// uk.c:128: 	for (int cj = 0; cj < 12; cj++) {
	add	x1, x1, x10	// ivtmp.234, ivtmp.234, _756
	cmp	x2, x9	// ivtmp.233, _774
	bne	.L16		//,
	b	.L17		//
	.cfi_endproc
.LFE4308:
	.size	uk_wind_8x12_a1True_b1False, .-uk_wind_8x12_a1True_b1False
	.align	2
	.p2align 4,,11
	.global	example_sgemm_a1True_b1True
	.type	example_sgemm_a1True_b1True, %function
example_sgemm_a1True_b1True:
.LFB4309:
	.cfi_startproc
// uk.c:146: void example_sgemm_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x0, x4	// B, tmp307
	mov	x7, x6	// C, tmp308
// uk.c:149: for (int k = 0; k < KC; k++) {
	cmp	x1, 0	// KC,
	ble	.L23		//,
	mov	x4, x3	// ivtmp.346, A
	mov	x6, x0	// ivtmp.348, B
	add	x8, x3, x1, lsl 5	// _212, ivtmp.346, KC,
	add	x5, x7, 384	// _36, C,
.L29:
	mov	x2, x6	// ivtmp.318, ivtmp.348
	add	x6, x6, 48	// ivtmp.348, ivtmp.348,
	cmp	x5, x2	// _36, ivtmp.318
	mov	x1, x4	// ivtmp.346, ivtmp.346
	ccmp	x7, x6, 2, hi	// C, ivtmp.348,,
	add	x4, x4, 32	// ivtmp.346, ivtmp.346,
	cset	w3, cs	// tmp240,
	cmp	x5, x1	// _36, ivtmp.346
	ccmp	x7, x4, 2, hi	// C, ivtmp.346,,
	cset	w0, cs	// tmp242,
	tst	w3, w0	// tmp240, tmp242
	beq	.L25		//,
	ldp	s20, s19, [x1, 4]	// _365, _375, MEM[base: _200, offset: 4B]
	mov	x0, x7	// ivtmp.321, C
	ldp	s18, s17, [x1, 12]	// _385, _395, MEM[base: _200, offset: 12B]
// uk.c:146: void example_sgemm_a1True_b1True( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x3, 0	// ivtmp.325,
	ldp	s16, s7, [x1, 20]	// _405, _415, MEM[base: _200, offset: 20B]
	dup	v20.4s, v20.s[0]	// vect_cst__366, _365
	ldr	s6, [x1, 28]	// _425, MEM[base: _200, offset: 28B]
	dup	v19.4s, v19.s[0]	// vect_cst__376, _375
	ld1r	{v21.4s}, [x1]	// vect_cst__356, MEM[base: _200, offset: 0B]
	dup	v18.4s, v18.s[0]	// vect_cst__386, _385
	dup	v17.4s, v17.s[0]	// vect_cst__396, _395
	dup	v16.4s, v16.s[0]	// vect_cst__406, _405
	dup	v7.4s, v7.s[0]	// vect_cst__416, _415
	dup	v6.4s, v6.s[0]	// vect_cst__426, _425
.L26:
// uk.c:152:       C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
	ldp	q2, q0, [x0]	// MEM[base: _50, offset: 0B], MEM[base: _50, offset: 16B], MEM[base: _50, offset: 0B]
	ldp	q23, q3, [x0, 32]	// MEM[base: _50, offset: 32B], MEM[base: _50, offset: 48B], MEM[base: _50, offset: 32B]
	ldp	q5, q24, [x0, 64]	// MEM[base: _50, offset: 64B], MEM[base: _50, offset: 80B], MEM[base: _50, offset: 64B]
	ldp	q22, q1, [x0, 96]	// MEM[base: _50, offset: 96B], MEM[base: _50, offset: 112B], MEM[base: _50, offset: 96B]
	uzp1	v4.4s, v2.4s, v0.4s	// vect_perm_even_331, MEM[base: _50, offset: 0B], MEM[base: _50, offset: 16B]
	uzp2	v2.4s, v2.4s, v0.4s	// vect_perm_odd_332, MEM[base: _50, offset: 0B], MEM[base: _50, offset: 16B]
	uzp1	v0.4s, v23.4s, v3.4s	// vect_perm_even_333, MEM[base: _50, offset: 32B], MEM[base: _50, offset: 48B]
	uzp2	v23.4s, v23.4s, v3.4s	// vect_perm_odd_334, MEM[base: _50, offset: 32B], MEM[base: _50, offset: 48B]
	uzp1	v3.4s, v5.4s, v24.4s	// vect_perm_even_335, MEM[base: _50, offset: 64B], MEM[base: _50, offset: 80B]
	uzp2	v5.4s, v5.4s, v24.4s	// vect_perm_odd_336, MEM[base: _50, offset: 64B], MEM[base: _50, offset: 80B]
	uzp1	v24.4s, v22.4s, v1.4s	// vect_perm_even_337, MEM[base: _50, offset: 96B], MEM[base: _50, offset: 112B]
	uzp2	v22.4s, v22.4s, v1.4s	// vect_perm_odd_338, MEM[base: _50, offset: 96B], MEM[base: _50, offset: 112B]
	uzp1	v1.4s, v4.4s, v0.4s	// vect_perm_even_339, vect_perm_even_331, vect_perm_even_333
	uzp2	v4.4s, v4.4s, v0.4s	// vect_perm_odd_340, vect_perm_even_331, vect_perm_even_333
	uzp1	v0.4s, v3.4s, v24.4s	// vect_perm_even_341, vect_perm_even_335, vect_perm_even_337
	uzp1	v26.4s, v5.4s, v22.4s	// vect_perm_even_345, vect_perm_odd_336, vect_perm_odd_338
	uzp2	v3.4s, v3.4s, v24.4s	// vect_perm_odd_342, vect_perm_even_335, vect_perm_even_337
	uzp2	v5.4s, v5.4s, v22.4s	// vect_perm_odd_346, vect_perm_odd_336, vect_perm_odd_338
	uzp1	v24.4s, v2.4s, v23.4s	// vect_perm_even_343, vect_perm_odd_332, vect_perm_odd_334
	uzp2	v2.4s, v2.4s, v23.4s	// vect_perm_odd_344, vect_perm_odd_332, vect_perm_odd_334
	uzp2	v25.4s, v1.4s, v0.4s	// vect_perm_odd_348, vect_perm_even_339, vect_perm_even_341
	uzp1	v0.4s, v1.4s, v0.4s	// tmp271, vect_perm_even_339, vect_perm_even_341
	uzp1	v23.4s, v4.4s, v3.4s	// vect_perm_even_351, vect_perm_odd_340, vect_perm_odd_342
	uzp1	v22.4s, v2.4s, v5.4s	// vect_perm_even_353, vect_perm_odd_344, vect_perm_odd_346
	uzp2	v2.4s, v2.4s, v5.4s	// vect_perm_odd_354, vect_perm_odd_344, vect_perm_odd_346
// uk.c:152:       C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
	ldr	q5, [x2, x3]	// MEM[base: _208, index: ivtmp.325_53, offset: 0B], MEM[base: _208, index: ivtmp.325_53, offset: 0B]
	add	x3, x3, 16	// ivtmp.325, ivtmp.325,
// uk.c:152:       C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
	uzp2	v4.4s, v4.4s, v3.4s	// vect_perm_odd_352, vect_perm_odd_340, vect_perm_odd_342
	uzp1	v3.4s, v24.4s, v26.4s	// vect_perm_even_349, vect_perm_even_343, vect_perm_even_345
	fmla	v0.4s, v21.4s, v5.4s	// tmp271, vect_cst__356, MEM[base: _208, index: ivtmp.325_53, offset: 0B]
	uzp2	v24.4s, v24.4s, v26.4s	// vect_perm_odd_350, vect_perm_even_343, vect_perm_even_345
	fmla	v23.4s, v5.4s, v19.4s	// vect__106.283, MEM[base: _208, index: ivtmp.325_53, offset: 0B], vect_cst__376
	fmla	v3.4s, v5.4s, v20.4s	// vect__82.278, MEM[base: _208, index: ivtmp.325_53, offset: 0B], vect_cst__366
	mov	v1.16b, v0.16b	// vect__58.273, tmp271
	mov	v0.16b, v25.16b	// vect_perm_odd_348, vect_perm_odd_348
	fmla	v24.4s, v5.4s, v16.4s	// vect__178.298, MEM[base: _208, index: ivtmp.325_53, offset: 0B], vect_cst__406
	fmla	v22.4s, v5.4s, v18.4s	// vect__130.288, MEM[base: _208, index: ivtmp.325_53, offset: 0B], vect_cst__386
	fmla	v4.4s, v5.4s, v7.4s	// vect__202.303, MEM[base: _208, index: ivtmp.325_53, offset: 0B], vect_cst__416
	fmla	v2.4s, v5.4s, v6.4s	// vect__226.308, MEM[base: _208, index: ivtmp.325_53, offset: 0B], vect_cst__426
	fmla	v0.4s, v5.4s, v17.4s	// vect_perm_odd_348, MEM[base: _208, index: ivtmp.325_53, offset: 0B], vect_cst__396
	zip1	v25.4s, v23.4s, v4.4s	// vect_inter_high_441, vect__106.283, vect__202.303
	zip1	v26.4s, v22.4s, v2.4s	// vect_inter_high_443, vect__130.288, vect__226.308
	zip1	v5.4s, v1.4s, v0.4s	// vect_inter_high_437, vect__58.273, vect__154.293
	zip2	v4.4s, v23.4s, v4.4s	// vect_inter_low_442, vect__106.283, vect__202.303
	zip1	v23.4s, v3.4s, v24.4s	// vect_inter_high_439, vect__82.278, vect__178.298
	zip2	v0.4s, v1.4s, v0.4s	// vect_inter_low_438, vect__58.273, vect__154.293
	zip2	v2.4s, v22.4s, v2.4s	// vect_inter_low_444, vect__130.288, vect__226.308
	zip2	v1.4s, v3.4s, v24.4s	// vect_inter_low_440, vect__82.278, vect__178.298
	zip1	v24.4s, v5.4s, v25.4s	// vect_inter_high_445, vect_inter_high_437, vect_inter_high_441
	zip2	v3.4s, v5.4s, v25.4s	// vect_inter_low_446, vect_inter_high_437, vect_inter_high_441
	zip1	v25.4s, v23.4s, v26.4s	// vect_inter_high_449, vect_inter_high_439, vect_inter_high_443
	zip1	v22.4s, v0.4s, v4.4s	// vect_inter_high_447, vect_inter_low_438, vect_inter_low_442
	zip2	v5.4s, v23.4s, v26.4s	// vect_inter_low_450, vect_inter_high_439, vect_inter_high_443
	zip2	v0.4s, v0.4s, v4.4s	// vect_inter_low_448, vect_inter_low_438, vect_inter_low_442
	zip1	v4.4s, v1.4s, v2.4s	// vect_inter_high_451, vect_inter_low_440, vect_inter_low_444
	zip2	v2.4s, v1.4s, v2.4s	// vect_inter_low_452, vect_inter_low_440, vect_inter_low_444
	zip1	v1.4s, v24.4s, v25.4s	// tmp272, vect_inter_high_445, vect_inter_high_449
	zip2	v24.4s, v24.4s, v25.4s	// tmp273, vect_inter_high_445, vect_inter_high_449
	zip1	v23.4s, v3.4s, v5.4s	// tmp274, vect_inter_low_446, vect_inter_low_450
	zip2	v3.4s, v3.4s, v5.4s	// tmp275, vect_inter_low_446, vect_inter_low_450
	zip1	v5.4s, v22.4s, v4.4s	// tmp276, vect_inter_high_447, vect_inter_high_451
	zip2	v22.4s, v22.4s, v4.4s	// tmp277, vect_inter_high_447, vect_inter_high_451
	stp	q1, q24, [x0]	// tmp272, tmp273, MEM[base: _50, offset: 0B]
	zip1	v1.4s, v0.4s, v2.4s	// tmp278, vect_inter_low_448, vect_inter_low_452
	stp	q23, q3, [x0, 32]	// tmp274, tmp275, MEM[base: _50, offset: 32B]
	zip2	v0.4s, v0.4s, v2.4s	// tmp279, vect_inter_low_448, vect_inter_low_452
	stp	q5, q22, [x0, 64]	// tmp276, tmp277, MEM[base: _50, offset: 64B]
	stp	q1, q0, [x0, 96]	// tmp278, tmp279, MEM[base: _50, offset: 96B]
	add	x0, x0, 128	// ivtmp.321, ivtmp.321,
	cmp	x3, 48	// ivtmp.325,
	bne	.L26		//,
// uk.c:149: for (int k = 0; k < KC; k++) {
	cmp	x4, x8	// ivtmp.346, _212
	bne	.L29		//,
.L23:
// uk.c:156: }
	ret	
.L25:
	mov	x0, x7	// ivtmp.317, C
	.p2align 3,,7
.L28:
// uk.c:152:       C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
	ldp	s7, s6, [x0]	// MEM[base: _122, offset: 0B], MEM[base: _122, offset: 4B], MEM[base: _122, offset: 0B]
	ldr	s1, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s0, [x1]	// MEM[base: _200, offset: 0B], MEM[base: _200, offset: 0B]
	ldp	s5, s4, [x0, 8]	// MEM[base: _122, offset: 8B], MEM[base: _122, offset: 12B], MEM[base: _122, offset: 8B]
	fmadd	s7, s1, s0, s7	// _255, MEM[base: _81, offset: 0B], MEM[base: _200, offset: 0B], MEM[base: _122, offset: 0B]
	ldp	s3, s2, [x0, 16]	// MEM[base: _122, offset: 16B], MEM[base: _122, offset: 20B], MEM[base: _122, offset: 16B]
	ldp	s1, s0, [x0, 24]	// MEM[base: _122, offset: 24B], MEM[base: _122, offset: 28B], MEM[base: _122, offset: 24B]
// uk.c:150:   for (int j = 0; j < 12; j++) {
	add	x0, x0, 32	// ivtmp.317, ivtmp.317,
// uk.c:152:       C[(j) * (8) + (i) * (1)] += A[(k) * (8) + (i) * (1)] * B[(k) * (12) + (j) * (1)];
	str	s7, [x0, -32]	// _255, MEM[base: _122, offset: 0B]
	ldr	s7, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s16, [x1, 4]	// MEM[base: _200, offset: 4B], MEM[base: _200, offset: 4B]
	fmadd	s6, s16, s7, s6	// _247, MEM[base: _200, offset: 4B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 4B]
	str	s6, [x0, -28]	// _247, MEM[base: _122, offset: 4B]
	ldr	s6, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s7, [x1, 8]	// MEM[base: _200, offset: 8B], MEM[base: _200, offset: 8B]
	fmadd	s5, s7, s6, s5	// _239, MEM[base: _200, offset: 8B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 8B]
	str	s5, [x0, -24]	// _239, MEM[base: _122, offset: 8B]
	ldr	s6, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s5, [x1, 12]	// MEM[base: _200, offset: 12B], MEM[base: _200, offset: 12B]
	fmadd	s4, s6, s5, s4	// _230, MEM[base: _81, offset: 0B], MEM[base: _200, offset: 12B], MEM[base: _122, offset: 12B]
	str	s4, [x0, -20]	// _230, MEM[base: _122, offset: 12B]
	ldr	s4, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s5, [x1, 16]	// MEM[base: _200, offset: 16B], MEM[base: _200, offset: 16B]
	fmadd	s3, s5, s4, s3	// _197, MEM[base: _200, offset: 16B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 16B]
	str	s3, [x0, -16]	// _197, MEM[base: _122, offset: 16B]
	ldr	s3, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s4, [x1, 20]	// MEM[base: _200, offset: 20B], MEM[base: _200, offset: 20B]
	fmadd	s2, s4, s3, s2	// _289, MEM[base: _200, offset: 20B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 20B]
	str	s2, [x0, -12]	// _289, MEM[base: _122, offset: 20B]
	ldr	s2, [x2]	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s3, [x1, 24]	// MEM[base: _200, offset: 24B], MEM[base: _200, offset: 24B]
	fmadd	s1, s3, s2, s1	// _299, MEM[base: _200, offset: 24B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 24B]
	str	s1, [x0, -8]	// _299, MEM[base: _122, offset: 24B]
	ldr	s1, [x2], 4	// MEM[base: _81, offset: 0B], MEM[base: _81, offset: 0B]
	ldr	s2, [x1, 28]	// MEM[base: _200, offset: 28B], MEM[base: _200, offset: 28B]
	fmadd	s0, s2, s1, s0	// _309, MEM[base: _200, offset: 28B], MEM[base: _81, offset: 0B], MEM[base: _122, offset: 28B]
	str	s0, [x0, -4]	// _309, MEM[base: _122, offset: 28B]
// uk.c:150:   for (int j = 0; j < 12; j++) {
	cmp	x5, x0	// _36, ivtmp.317
	bne	.L28		//,
// uk.c:149: for (int k = 0; k < KC; k++) {
	cmp	x4, x8	// ivtmp.346, _212
	bne	.L29		//,
	b	.L23		//
	.cfi_endproc
.LFE4309:
	.size	example_sgemm_a1True_b1True, .-example_sgemm_a1True_b1True
	.align	2
	.p2align 4,,11
	.global	uk_8x12_a1True_b1False
	.type	uk_8x12_a1True_b1False, %function
uk_8x12_a1True_b1False:
.LFB4310:
	.cfi_startproc
	stp	x29, x30, [sp, -96]!	//,,,
	.cfi_def_cfa_offset 96
	.cfi_offset 29, -96
	.cfi_offset 30, -88
// uk.c:192: float *Cb = malloc(12 * 8 * sizeof(*Cb));
	mov	x0, 384	//,
// uk.c:191: inline void uk_8x12_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x29, sp	//,
	stp	x19, x20, [sp, 16]	//,,
	.cfi_offset 19, -80
	.cfi_offset 20, -72
	mov	x19, x6	// C, tmp342
	mov	x20, x4	// B, tmp340
	str	x23, [sp, 48]	//,
	.cfi_offset 23, -48
	mov	x23, x5	// beta, tmp341
	stp	x21, x22, [sp, 32]	//,,
	.cfi_offset 21, -64
	.cfi_offset 22, -56
	mov	x22, x1	// KC, tmp338
	mov	x21, x3	// A, tmp339
	str	d12, [sp, 56]	//,
	stp	d8, d9, [sp, 64]	//,,
	stp	d10, d11, [sp, 80]	//,,
	.cfi_offset 76, -40
	.cfi_offset 72, -32
	.cfi_offset 73, -24
	.cfi_offset 74, -16
	.cfi_offset 75, -8
// uk.c:192: float *Cb = malloc(12 * 8 * sizeof(*Cb));
	bl	malloc		//
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:15603:   return (float32x4_t) {__a, __a, __a, __a};
	ld1r	{v0.4s}, [x23]	// tmp274, MEM[(const float32_t *)beta_134(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q12, q11, [x19]	// _714, _721,* C
	ldp	q10, q9, [x19, 32]	// _737, _744,
	ldp	q8, q31, [x19, 64]	// _760, _767,
	ldp	q30, q29, [x19, 96]	// _783, _790,
	ldp	q28, q27, [x19, 128]	// _806, _813,
	ldp	q26, q25, [x19, 160]	// _829, _836,
	ldp	q24, q23, [x19, 192]	// _852, _859,
	ldp	q22, q21, [x19, 224]	// _875, _882,
	ldp	q20, q19, [x19, 256]	// _898, _905,
	ldp	q18, q17, [x19, 288]	// _921, _928,
	ldp	q16, q7, [x19, 320]	// _944, _951,
	ldp	q6, q5, [x19, 352]	// _500, _512,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v12.4s, v0.4s, v12.4s	// tmp299, tmp274, _714
	fmul	v11.4s, v0.4s, v11.4s	// tmp300, tmp274, _721
	fmul	v10.4s, v0.4s, v10.4s	// tmp301, tmp274, _737
	fmul	v9.4s, v0.4s, v9.4s	// tmp302, tmp274, _744
	fmul	v8.4s, v0.4s, v8.4s	// tmp303, tmp274, _760
	fmul	v31.4s, v0.4s, v31.4s	// tmp304, tmp274, _767
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q12, q11, [x0]	// tmp299, tmp300,* Cb
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v30.4s, v0.4s, v30.4s	// tmp305, tmp274, _783
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q10, q9, [x0, 32]	// tmp301, tmp302,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v29.4s, v0.4s, v29.4s	// tmp306, tmp274, _790
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q8, q31, [x0, 64]	// tmp303, tmp304,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v28.4s, v0.4s, v28.4s	// tmp307, tmp274, _806
	fmul	v27.4s, v0.4s, v27.4s	// tmp308, tmp274, _813
	fmul	v26.4s, v0.4s, v26.4s	// tmp309, tmp274, _829
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q30, q29, [x0, 96]	// tmp305, tmp306,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v25.4s, v0.4s, v25.4s	// tmp310, tmp274, _836
	fmul	v24.4s, v0.4s, v24.4s	// tmp311, tmp274, _852
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q28, q27, [x0, 128]	// tmp307, tmp308,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v23.4s, v0.4s, v23.4s	// tmp312, tmp274, _859
	fmul	v22.4s, v0.4s, v22.4s	// tmp313, tmp274, _875
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q26, q25, [x0, 160]	// tmp309, tmp310,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v21.4s, v0.4s, v21.4s	// tmp314, tmp274, _882
	fmul	v20.4s, v0.4s, v20.4s	// tmp315, tmp274, _898
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q24, q23, [x0, 192]	// tmp311, tmp312,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v19.4s, v0.4s, v19.4s	// tmp316, tmp274, _905
	fmul	v18.4s, v0.4s, v18.4s	// tmp317, tmp274, _921
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q22, q21, [x0, 224]	// tmp313, tmp314,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v17.4s, v0.4s, v17.4s	// tmp318, tmp274, _928
	fmul	v16.4s, v0.4s, v16.4s	// tmp319, tmp274, _944
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q20, q19, [x0, 256]	// tmp315, tmp316,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v7.4s, v0.4s, v7.4s	// tmp320, tmp274, _951
	fmul	v6.4s, v0.4s, v6.4s	// tmp321, tmp274, _500
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q18, q17, [x0, 288]	// tmp317, tmp318,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v5.4s, v0.4s, v5.4s	// tmp322, tmp274, _512
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q16, q7, [x0, 320]	// tmp319, tmp320,
	stp	q6, q5, [x0, 352]	// tmp321, tmp322,
// uk.c:236: for (int k = 0; k < KC; k++) {
	cmp	x22, 0	// KC,
	ble	.L34		//,
	mov	x3, x21	// ivtmp.368, A
	mov	x2, x20	// ivtmp.370, B
	mov	x4, 0	// ivtmp.366,
	.p2align 3,,7
.L35:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q1, q0, [x3]	// _260, _259,* ivtmp.368
// uk.c:236: for (int k = 0; k < KC; k++) {
	add	x4, x4, 1	// ivtmp.366, ivtmp.366,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q4, q3, [x2]	// _258, _257,* ivtmp.370
// uk.c:236: for (int k = 0; k < KC; k++) {
	add	x3, x3, 32	// ivtmp.368, ivtmp.368,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q2, [x2, 32]	// _256,
// uk.c:236: for (int k = 0; k < KC; k++) {
	add	x2, x2, 48	// ivtmp.370, ivtmp.370,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:16810:   return __builtin_aarch64_fmav4sf (__b,
	fmla	v12.4s, v1.4s, v4.s[0]	// _255, _260, _258,
	fmla	v10.4s, v1.4s, v4.s[1]	// _254, _260, _258,
	fmla	v8.4s, v1.4s, v4.s[2]	// _253, _260, _258,
	fmla	v30.4s, v1.4s, v4.s[3]	// _252, _260, _258,
	fmla	v11.4s, v0.4s, v4.s[0]	// _251, _259, _258,
	fmla	v9.4s, v0.4s, v4.s[1]	// _250, _259, _258,
	fmla	v31.4s, v0.4s, v4.s[2]	// _249, _259, _258,
	fmla	v29.4s, v0.4s, v4.s[3]	// _248, _259, _258,
	fmla	v28.4s, v1.4s, v3.s[0]	// _247, _260, _257,
	fmla	v26.4s, v1.4s, v3.s[1]	// _246, _260, _257,
	fmla	v24.4s, v1.4s, v3.s[2]	// _245, _260, _257,
	fmla	v22.4s, v1.4s, v3.s[3]	// _244, _260, _257,
	fmla	v27.4s, v0.4s, v3.s[0]	// _243, _259, _257,
	fmla	v25.4s, v0.4s, v3.s[1]	// _242, _259, _257,
	fmla	v23.4s, v0.4s, v3.s[2]	// _241, _259, _257,
	fmla	v21.4s, v0.4s, v3.s[3]	// _240, _259, _257,
	fmla	v20.4s, v1.4s, v2.s[0]	// _239, _260, _256,
	fmla	v18.4s, v1.4s, v2.s[1]	// _238, _260, _256,
	fmla	v16.4s, v1.4s, v2.s[2]	// _237, _260, _256,
	fmla	v6.4s, v1.4s, v2.s[3]	// _236, _260, _256,
	fmla	v19.4s, v0.4s, v2.s[0]	// _235, _259, _256,
	fmla	v17.4s, v0.4s, v2.s[1]	// _234, _259, _256,
	fmla	v7.4s, v0.4s, v2.s[2]	// _233, _259, _256,
	fmla	v5.4s, v0.4s, v2.s[3]	// _232, _259, _256,
// uk.c:236: for (int k = 0; k < KC; k++) {
	cmp	x22, x4	// KC, ivtmp.366
	bne	.L35		//,
.L34:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q12, [x0]	// _255,* Cb
// uk.c:293:     C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q12, [x19]	// _255, MEM <vector(4) float> [(float *)C_168(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q11, [x0, 16]	// _251,
// uk.c:293:     C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q11, [x19, 16]	// _251, MEM <vector(4) float> [(float *)C_168(D) + 16B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q10, [x0, 32]	// _254,
// uk.c:293:     C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q10, [x19, 32]	// _254, MEM <vector(4) float> [(float *)C_168(D) + 32B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q9, [x0, 48]	// _250,
// uk.c:293:     C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q9, [x19, 48]	// _250, MEM <vector(4) float> [(float *)C_168(D) + 48B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q8, [x0, 64]	// _253,
// uk.c:293:     C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q8, [x19, 64]	// _253, MEM <vector(4) float> [(float *)C_168(D) + 64B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q31, [x0, 80]	// _249,
// uk.c:293:     C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q31, [x19, 80]	// _249, MEM <vector(4) float> [(float *)C_168(D) + 80B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q30, [x0, 96]	// _252,
// uk.c:293:     C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q30, [x19, 96]	// _252, MEM <vector(4) float> [(float *)C_168(D) + 96B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q29, [x0, 112]	// _248,
// uk.c:293:     C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q29, [x19, 112]	// _248, MEM <vector(4) float> [(float *)C_168(D) + 112B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q28, q27, [x0, 128]	// _247, _243,
	stp	q26, q25, [x0, 160]	// _246, _242,
	stp	q24, q23, [x0, 192]	// _245, _241,
	stp	q22, q21, [x0, 224]	// _244, _240,
	stp	q20, q19, [x0, 256]	// _239, _235,
	stp	q18, q17, [x0, 288]	// _238, _234,
	stp	q16, q7, [x0, 320]	// _237, _233,
	stp	q6, q5, [x0, 352]	// _236, _232,
// uk.c:293:     C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	stp	q28, q27, [x19, 128]	// _247, _243, MEM <vector(4) float> [(float *)C_168(D) + 128B]
// uk.c:297: }
	ldr	d12, [sp, 56]	//,
// uk.c:293:     C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	stp	q26, q25, [x19, 160]	// _246, _242, MEM <vector(4) float> [(float *)C_168(D) + 160B]
	stp	q24, q23, [x19, 192]	// _245, _241, MEM <vector(4) float> [(float *)C_168(D) + 192B]
	stp	q22, q21, [x19, 224]	// _244, _240, MEM <vector(4) float> [(float *)C_168(D) + 224B]
	stp	q20, q19, [x19, 256]	// _239, _235, MEM <vector(4) float> [(float *)C_168(D) + 256B]
	stp	q18, q17, [x19, 288]	// _238, _234, MEM <vector(4) float> [(float *)C_168(D) + 288B]
	stp	q16, q7, [x19, 320]	// _237, _233, MEM <vector(4) float> [(float *)C_168(D) + 320B]
	stp	q6, q5, [x19, 352]	// _236, _232, MEM <vector(4) float> [(float *)C_168(D) + 352B]
// uk.c:297: }
	ldp	x19, x20, [sp, 16]	//,,
	ldp	x21, x22, [sp, 32]	//,,
	ldr	x23, [sp, 48]	//,
	ldp	d8, d9, [sp, 64]	//,,
	ldp	d10, d11, [sp, 80]	//,,
	ldp	x29, x30, [sp], 96	//,,,
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 23
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 76
	.cfi_restore 74
	.cfi_restore 75
	.cfi_restore 72
	.cfi_restore 73
	.cfi_def_cfa_offset 0
// uk.c:296: free(Cb);
	b	free		//
	.cfi_endproc
.LFE4310:
	.size	uk_8x12_a1True_b1False, .-uk_8x12_a1True_b1False
	.align	2
	.p2align 4,,11
	.global	uk_8x12_a1True_b1True
	.type	uk_8x12_a1True_b1True, %function
uk_8x12_a1True_b1True:
.LFB4311:
	.cfi_startproc
	stp	d8, d9, [sp, -48]!	//,,,
	.cfi_def_cfa_offset 48
	.cfi_offset 72, -48
	.cfi_offset 73, -40
	stp	d10, d11, [sp, 16]	//,,
	str	d12, [sp, 32]	//,
	.cfi_offset 74, -32
	.cfi_offset 75, -24
	.cfi_offset 76, -16
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q12, [x6]	// C_reg$0$0,* C
	ldp	q11, q10, [x6, 16]	// C_reg$0$1, C_reg$1$0,
	ldp	q9, q8, [x6, 48]	// C_reg$1$1, C_reg$2$0,
	ldp	q31, q30, [x6, 80]	// C_reg$2$1, C_reg$3$0,
	ldp	q29, q28, [x6, 112]	// C_reg$3$1, C_reg$4$0,
	ldp	q27, q26, [x6, 144]	// C_reg$4$1, C_reg$5$0,
	ldp	q25, q24, [x6, 176]	// C_reg$5$1, C_reg$6$0,
	ldp	q23, q22, [x6, 208]	// C_reg$6$1, C_reg$7$0,
	ldp	q21, q20, [x6, 240]	// C_reg$7$1, C_reg$8$0,
	ldp	q19, q18, [x6, 272]	// C_reg$8$1, C_reg$9$0,
	ldp	q17, q16, [x6, 304]	// C_reg$9$1, C_reg$10$0,
	ldp	q7, q6, [x6, 336]	// C_reg$10$1, C_reg$11$0,
	ldr	q5, [x6, 368]	// C_reg$11$1,
// uk.c:337: for (int k = 0; k < KC; k++) {
	cmp	x1, 0	// KC,
	ble	.L39		//,
	mov	x0, 0	// ivtmp.381,
	.p2align 3,,7
.L40:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q1, q0, [x3]	// _144, _143,* ivtmp.383
// uk.c:337: for (int k = 0; k < KC; k++) {
	add	x0, x0, 1	// ivtmp.381, ivtmp.381,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q4, q3, [x4]	// _142, _141,* ivtmp.385
// uk.c:337: for (int k = 0; k < KC; k++) {
	add	x3, x3, 32	// ivtmp.383, ivtmp.383,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q2, [x4, 32]	// _140,
// uk.c:337: for (int k = 0; k < KC; k++) {
	add	x4, x4, 48	// ivtmp.385, ivtmp.385,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:16810:   return __builtin_aarch64_fmav4sf (__b,
	fmla	v12.4s, v1.4s, v4.s[0]	// C_reg$0$0, _144, _142,
	fmla	v10.4s, v1.4s, v4.s[1]	// C_reg$1$0, _144, _142,
	fmla	v8.4s, v1.4s, v4.s[2]	// C_reg$2$0, _144, _142,
	fmla	v30.4s, v1.4s, v4.s[3]	// C_reg$3$0, _144, _142,
	fmla	v11.4s, v0.4s, v4.s[0]	// C_reg$0$1, _143, _142,
	fmla	v9.4s, v0.4s, v4.s[1]	// C_reg$1$1, _143, _142,
	fmla	v31.4s, v0.4s, v4.s[2]	// C_reg$2$1, _143, _142,
	fmla	v29.4s, v0.4s, v4.s[3]	// C_reg$3$1, _143, _142,
	fmla	v28.4s, v1.4s, v3.s[0]	// C_reg$4$0, _144, _141,
	fmla	v26.4s, v1.4s, v3.s[1]	// C_reg$5$0, _144, _141,
	fmla	v24.4s, v1.4s, v3.s[2]	// C_reg$6$0, _144, _141,
	fmla	v22.4s, v1.4s, v3.s[3]	// C_reg$7$0, _144, _141,
	fmla	v27.4s, v0.4s, v3.s[0]	// C_reg$4$1, _143, _141,
	fmla	v25.4s, v0.4s, v3.s[1]	// C_reg$5$1, _143, _141,
	fmla	v23.4s, v0.4s, v3.s[2]	// C_reg$6$1, _143, _141,
	fmla	v21.4s, v0.4s, v3.s[3]	// C_reg$7$1, _143, _141,
	fmla	v20.4s, v1.4s, v2.s[0]	// C_reg$8$0, _144, _140,
	fmla	v18.4s, v1.4s, v2.s[1]	// C_reg$9$0, _144, _140,
	fmla	v16.4s, v1.4s, v2.s[2]	// C_reg$10$0, _144, _140,
	fmla	v6.4s, v1.4s, v2.s[3]	// C_reg$11$0, _144, _140,
	fmla	v19.4s, v0.4s, v2.s[0]	// C_reg$8$1, _143, _140,
	fmla	v17.4s, v0.4s, v2.s[1]	// C_reg$9$1, _143, _140,
	fmla	v7.4s, v0.4s, v2.s[2]	// C_reg$10$1, _143, _140,
	fmla	v5.4s, v0.4s, v2.s[3]	// C_reg$11$1, _143, _140,
// uk.c:337: for (int k = 0; k < KC; k++) {
	cmp	x1, x0	// KC, ivtmp.381
	bne	.L40		//,
.L39:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q12, q11, [x6]	// C_reg$0$0, C_reg$0$1,* C
// uk.c:392: }
	ldr	d12, [sp, 32]	//,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q10, q9, [x6, 32]	// C_reg$1$0, C_reg$1$1,
	stp	q8, q31, [x6, 64]	// C_reg$2$0, C_reg$2$1,
	stp	q30, q29, [x6, 96]	// C_reg$3$0, C_reg$3$1,
	stp	q28, q27, [x6, 128]	// C_reg$4$0, C_reg$4$1,
	stp	q26, q25, [x6, 160]	// C_reg$5$0, C_reg$5$1,
	stp	q24, q23, [x6, 192]	// C_reg$6$0, C_reg$6$1,
	stp	q22, q21, [x6, 224]	// C_reg$7$0, C_reg$7$1,
	stp	q20, q19, [x6, 256]	// C_reg$8$0, C_reg$8$1,
	stp	q18, q17, [x6, 288]	// C_reg$9$0, C_reg$9$1,
	stp	q16, q7, [x6, 320]	// C_reg$10$0, C_reg$10$1,
	stp	q6, q5, [x6, 352]	// C_reg$11$0, C_reg$11$1,
// uk.c:392: }
	ldp	d10, d11, [sp, 16]	//,,
	ldp	d8, d9, [sp], 48	//,,,
	.cfi_restore 73
	.cfi_restore 72
	.cfi_restore 76
	.cfi_restore 74
	.cfi_restore 75
	.cfi_def_cfa_offset 0
	ret	
	.cfi_endproc
.LFE4311:
	.size	uk_8x12_a1True_b1True, .-uk_8x12_a1True_b1True
	.align	2
	.p2align 4,,11
	.global	uk_8x4_a1True_b1False
	.type	uk_8x4_a1True_b1False, %function
uk_8x4_a1True_b1False:
.LFB4312:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!	//,,,
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
// uk.c:395: 	float *Cb = malloc(4 * 8 * sizeof(*Cb));
	mov	x0, 128	//,
// uk.c:394: inline void uk_8x4_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x29, sp	//,
	stp	x21, x22, [sp, 32]	//,,
	.cfi_offset 21, -32
	.cfi_offset 22, -24
	mov	x21, x6	// C, tmp190
	mov	x22, x1	// KC, tmp186
	str	x23, [sp, 48]	//,
	.cfi_offset 23, -16
	mov	x23, x5	// beta, tmp189
	stp	x19, x20, [sp, 16]	//,,
	.cfi_offset 19, -48
	.cfi_offset 20, -40
// uk.c:394: inline void uk_8x4_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x19, x3	// A, tmp187
	mov	x20, x4	// B, tmp188
// uk.c:395: 	float *Cb = malloc(4 * 8 * sizeof(*Cb));
	bl	malloc		//
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q18, q17, [x21]	// _187, _173,* C
	ldp	q16, q7, [x21, 32]	// _63, _55,
	ldp	q6, q5, [x21, 64]	// _4, _380,
	ldp	q4, q0, [x21, 96]	// _306, _318,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:15603:   return (float32x4_t) {__a, __a, __a, __a};
	ld1r	{v3.4s}, [x23]	// tmp164, MEM[(const float32_t *)beta_76(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v18.4s, v3.4s, v18.4s	// tmp173, tmp164, _187
	fmul	v17.4s, v3.4s, v17.4s	// tmp174, tmp164, _173
	fmul	v16.4s, v16.4s, v3.4s	// tmp175, _63, tmp164
	fmul	v7.4s, v7.4s, v3.4s	// tmp176, _55, tmp164
	fmul	v6.4s, v6.4s, v3.4s	// tmp177, _4, tmp164
	fmul	v5.4s, v3.4s, v5.4s	// tmp178, tmp164, _380
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q18, q17, [x0]	// tmp173, tmp174,* Cb
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v4.4s, v3.4s, v4.4s	// tmp179, tmp164, _306
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q16, q7, [x0, 32]	// tmp175, tmp176,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v3.4s, v3.4s, v0.4s	// tmp180, tmp164, _318
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q6, q5, [x0, 64]	// tmp177, tmp178,
	stp	q4, q3, [x0, 96]	// tmp179, tmp180,
// uk.c:423: 	for (int k = 0; k < KC; k++) {
	cmp	x22, 0	// KC,
	ble	.L44		//,
	mov	x3, x19	// ivtmp.407, A
	mov	x4, x20	// ivtmp.409, B
	mov	x2, 0	// ivtmp.405,
	.p2align 3,,7
.L45:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q2, q1, [x3]	// _136, _135,* ivtmp.407
// uk.c:423: 	for (int k = 0; k < KC; k++) {
	add	x2, x2, 1	// ivtmp.405, ivtmp.405,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q0, [x4], 16	// _134,
// uk.c:423: 	for (int k = 0; k < KC; k++) {
	add	x3, x3, 32	// ivtmp.407, ivtmp.407,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:16810:   return __builtin_aarch64_fmav4sf (__b,
	fmla	v18.4s, v2.4s, v0.s[0]	// _133, _136, _134,
	fmla	v16.4s, v2.4s, v0.s[1]	// _132, _136, _134,
	fmla	v6.4s, v2.4s, v0.s[2]	// _131, _136, _134,
	fmla	v4.4s, v2.4s, v0.s[3]	// _130, _136, _134,
	fmla	v17.4s, v1.4s, v0.s[0]	// _129, _135, _134,
	fmla	v7.4s, v1.4s, v0.s[1]	// _128, _135, _134,
	fmla	v5.4s, v1.4s, v0.s[2]	// _127, _135, _134,
	fmla	v3.4s, v1.4s, v0.s[3]	// _126, _135, _134,
// uk.c:423: 	for (int k = 0; k < KC; k++) {
	cmp	x22, x2	// KC, ivtmp.405
	bne	.L45		//,
.L44:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q18, [x0]	// _133,* Cb
// uk.c:446: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q18, [x21]	// _133, MEM <vector(4) float> [(float *)C_94(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q17, [x0, 16]	// _129,
// uk.c:446: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q17, [x21, 16]	// _129, MEM <vector(4) float> [(float *)C_94(D) + 16B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q16, [x0, 32]	// _132,
// uk.c:446: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q16, [x21, 32]	// _132, MEM <vector(4) float> [(float *)C_94(D) + 32B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q7, [x0, 48]	// _128,
// uk.c:446: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q7, [x21, 48]	// _128, MEM <vector(4) float> [(float *)C_94(D) + 48B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q6, [x0, 64]	// _131,
// uk.c:446: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q6, [x21, 64]	// _131, MEM <vector(4) float> [(float *)C_94(D) + 64B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q5, [x0, 80]	// _127,
// uk.c:446: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q5, [x21, 80]	// _127, MEM <vector(4) float> [(float *)C_94(D) + 80B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q4, [x0, 96]	// _130,
// uk.c:446: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q4, [x21, 96]	// _130, MEM <vector(4) float> [(float *)C_94(D) + 96B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q3, [x0, 112]	// _126,
// uk.c:450: }
	ldp	x19, x20, [sp, 16]	//,,
	ldr	x23, [sp, 48]	//,
// uk.c:446: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q3, [x21, 112]	// _126, MEM <vector(4) float> [(float *)C_94(D) + 112B]
// uk.c:450: }
	ldp	x21, x22, [sp, 32]	//,,
	ldp	x29, x30, [sp], 64	//,,,
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 23
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
// uk.c:449: 	free(Cb);
	b	free		//
	.cfi_endproc
.LFE4312:
	.size	uk_8x4_a1True_b1False, .-uk_8x4_a1True_b1False
	.align	2
	.p2align 4,,11
	.global	uk_8x8_a1True_b1False
	.type	uk_8x8_a1True_b1False, %function
uk_8x8_a1True_b1False:
.LFB4313:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!	//,,,
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
// uk.c:453: 	float *Cb = malloc(8 * 8 * sizeof(*Cb));
	mov	x0, 256	//,
// uk.c:452: inline void uk_8x8_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x29, sp	//,
	stp	x19, x20, [sp, 16]	//,,
	.cfi_offset 19, -48
	.cfi_offset 20, -40
	mov	x19, x6	// C, tmp262
	mov	x20, x4	// B, tmp260
	str	x23, [sp, 48]	//,
	.cfi_offset 23, -16
	mov	x23, x5	// beta, tmp261
	stp	x21, x22, [sp, 32]	//,,
	.cfi_offset 21, -32
	.cfi_offset 22, -24
// uk.c:452: inline void uk_8x8_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x22, x1	// KC, tmp258
	mov	x21, x3	// A, tmp259
// uk.c:453: 	float *Cb = malloc(8 * 8 * sizeof(*Cb));
	bl	malloc		//
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q26, q25, [x19]	// _58, _65,* C
	ldp	q24, q23, [x19, 32]	// _507, _514,
	ldp	q22, q21, [x19, 64]	// _530, _537,
	ldp	q20, q19, [x19, 96]	// _553, _560,
	ldp	q18, q17, [x19, 128]	// _576, _583,
	ldp	q16, q7, [x19, 160]	// _599, _606,
	ldp	q6, q5, [x19, 192]	// _622, _629,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:15603:   return (float32x4_t) {__a, __a, __a, __a};
	ld1r	{v0.4s}, [x23]	// tmp214, MEM[(const float32_t *)beta_98(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q4, q3, [x19, 224]	// _391, _403,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v26.4s, v26.4s, v0.4s	// tmp231, _58, tmp214
	fmul	v25.4s, v25.4s, v0.4s	// tmp232, _65, tmp214
	fmul	v24.4s, v0.4s, v24.4s	// tmp233, tmp214, _507
	fmul	v23.4s, v0.4s, v23.4s	// tmp234, tmp214, _514
	fmul	v22.4s, v0.4s, v22.4s	// tmp235, tmp214, _530
	fmul	v21.4s, v0.4s, v21.4s	// tmp236, tmp214, _537
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q26, q25, [x0]	// tmp231, tmp232,* Cb
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v20.4s, v0.4s, v20.4s	// tmp237, tmp214, _553
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q24, q23, [x0, 32]	// tmp233, tmp234,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v19.4s, v0.4s, v19.4s	// tmp238, tmp214, _560
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q22, q21, [x0, 64]	// tmp235, tmp236,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v18.4s, v0.4s, v18.4s	// tmp239, tmp214, _576
	fmul	v17.4s, v0.4s, v17.4s	// tmp240, tmp214, _583
	fmul	v16.4s, v0.4s, v16.4s	// tmp241, tmp214, _599
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q20, q19, [x0, 96]	// tmp237, tmp238,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v7.4s, v0.4s, v7.4s	// tmp242, tmp214, _606
	fmul	v6.4s, v0.4s, v6.4s	// tmp243, tmp214, _622
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q18, q17, [x0, 128]	// tmp239, tmp240,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v5.4s, v0.4s, v5.4s	// tmp244, tmp214, _629
	fmul	v4.4s, v0.4s, v4.4s	// tmp245, tmp214, _391
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q16, q7, [x0, 160]	// tmp241, tmp242,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v3.4s, v0.4s, v3.4s	// tmp246, tmp214, _403
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q6, q5, [x0, 192]	// tmp243, tmp244,
	stp	q4, q3, [x0, 224]	// tmp245, tmp246,
// uk.c:489: 	for (int k = 0; k < KC; k++) {
	cmp	x22, 0	// KC,
	ble	.L49		//,
	add	x3, x21, 16	// ivtmp.429, A,
	add	x2, x20, 16	// ivtmp.431, B,
	mov	x4, 0	// ivtmp.426,
	.p2align 3,,7
.L50:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q0, [x2, -16]	// _185,
// uk.c:489: 	for (int k = 0; k < KC; k++) {
	add	x4, x4, 1	// ivtmp.426, ivtmp.426,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q2, [x3, -16]	// _187,
// uk.c:489: 	for (int k = 0; k < KC; k++) {
	add	x2, x2, 32	// ivtmp.431, ivtmp.431,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q1, [x3], 32	// _186,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:16810:   return __builtin_aarch64_fmav4sf (__b,
	fmla	v26.4s, v2.4s, v0.s[0]	// _184, _187, _185,
	fmla	v24.4s, v2.4s, v0.s[0]	// _183, _187, _185,
	fmla	v22.4s, v2.4s, v0.s[0]	// _182, _187, _185,
	fmla	v20.4s, v2.4s, v0.s[0]	// _181, _187, _185,
	fmla	v18.4s, v2.4s, v0.s[1]	// _176, _187, _185,
	fmla	v16.4s, v2.4s, v0.s[1]	// _175, _187, _185,
	fmla	v6.4s, v2.4s, v0.s[1]	// _174, _187, _185,
	fmla	v4.4s, v2.4s, v0.s[1]	// _173, _187, _185,
	fmla	v25.4s, v1.4s, v0.s[0]	// _180, _186, _185,
	fmla	v23.4s, v1.4s, v0.s[0]	// _179, _186, _185,
	fmla	v21.4s, v1.4s, v0.s[0]	// _178, _186, _185,
	fmla	v19.4s, v1.4s, v0.s[0]	// _177, _186, _185,
	fmla	v17.4s, v1.4s, v0.s[1]	// _172, _186, _185,
	fmla	v7.4s, v1.4s, v0.s[1]	// _171, _186, _185,
	fmla	v5.4s, v1.4s, v0.s[1]	// _170, _186, _185,
	fmla	v3.4s, v1.4s, v0.s[1]	// _169, _186, _185,
// uk.c:489: 	for (int k = 0; k < KC; k++) {
	cmp	x4, x22	// ivtmp.426, KC
	bne	.L50		//,
.L49:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q26, [x0]	// _184,* Cb
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q26, [x19]	// _184, MEM <vector(4) float> [(float *)C_121(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q25, [x0, 16]	// _180,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q25, [x19, 16]	// _180, MEM <vector(4) float> [(float *)C_121(D) + 16B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q24, [x0, 32]	// _183,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q24, [x19, 32]	// _183, MEM <vector(4) float> [(float *)C_121(D) + 32B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q23, [x0, 48]	// _179,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q23, [x19, 48]	// _179, MEM <vector(4) float> [(float *)C_121(D) + 48B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q22, [x0, 64]	// _182,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q22, [x19, 64]	// _182, MEM <vector(4) float> [(float *)C_121(D) + 64B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q21, [x0, 80]	// _178,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q21, [x19, 80]	// _178, MEM <vector(4) float> [(float *)C_121(D) + 80B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q20, [x0, 96]	// _181,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q20, [x19, 96]	// _181, MEM <vector(4) float> [(float *)C_121(D) + 96B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q19, [x0, 112]	// _177,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q19, [x19, 112]	// _177, MEM <vector(4) float> [(float *)C_121(D) + 112B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q18, [x0, 128]	// _176,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q18, [x19, 128]	// _176, MEM <vector(4) float> [(float *)C_121(D) + 128B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q17, [x0, 144]	// _172,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q17, [x19, 144]	// _172, MEM <vector(4) float> [(float *)C_121(D) + 144B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q16, [x0, 160]	// _175,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q16, [x19, 160]	// _175, MEM <vector(4) float> [(float *)C_121(D) + 160B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q7, [x0, 176]	// _171,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q7, [x19, 176]	// _171, MEM <vector(4) float> [(float *)C_121(D) + 176B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q6, [x0, 192]	// _174,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q6, [x19, 192]	// _174, MEM <vector(4) float> [(float *)C_121(D) + 192B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q5, [x0, 208]	// _170,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q5, [x19, 208]	// _170, MEM <vector(4) float> [(float *)C_121(D) + 208B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q4, [x0, 224]	// _173,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q4, [x19, 224]	// _173, MEM <vector(4) float> [(float *)C_121(D) + 224B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q3, [x0, 240]	// _169,
// uk.c:529: 			      C[(cj) * (8) + (ci) * (1)] = Cb[(cj) * (8) + (ci) * (1)];
	str	q3, [x19, 240]	// _169, MEM <vector(4) float> [(float *)C_121(D) + 240B]
// uk.c:533: }
	ldp	x19, x20, [sp, 16]	//,,
	ldp	x21, x22, [sp, 32]	//,,
	ldr	x23, [sp, 48]	//,
	ldp	x29, x30, [sp], 64	//,,,
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 23
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
// uk.c:532: 	free(Cb);
	b	free		//
	.cfi_endproc
.LFE4313:
	.size	uk_8x8_a1True_b1False, .-uk_8x8_a1True_b1False
	.align	2
	.p2align 4,,11
	.global	uk_4x8_a1True_b1False
	.type	uk_4x8_a1True_b1False, %function
uk_4x8_a1True_b1False:
.LFB4314:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!	//,,,
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
// uk.c:536: 	float *Cb = malloc(8 * 4 * sizeof(*Cb));
	mov	x0, 128	//,
// uk.c:535: inline void uk_4x8_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x29, sp	//,
	stp	x21, x22, [sp, 32]	//,,
	.cfi_offset 21, -32
	.cfi_offset 22, -24
	mov	x21, x6	// C, tmp206
	mov	x22, x1	// KC, tmp202
	str	x23, [sp, 48]	//,
	.cfi_offset 23, -16
	mov	x23, x5	// beta, tmp205
	stp	x19, x20, [sp, 16]	//,,
	.cfi_offset 19, -48
	.cfi_offset 20, -40
// uk.c:535: inline void uk_4x8_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x20, x3	// A, tmp203
	mov	x19, x4	// B, tmp204
// uk.c:536: 	float *Cb = malloc(8 * 4 * sizeof(*Cb));
	bl	malloc		//
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q18, q17, [x21]	// _304, _317,* C
	ldp	q16, q7, [x21, 32]	// _330, _343,
	ldp	q6, q5, [x21, 64]	// _356, _369,
	ldp	q4, q0, [x21, 96]	// _382, _111,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:15603:   return (float32x4_t) {__a, __a, __a, __a};
	ld1r	{v3.4s}, [x23]	// tmp168, MEM[(const float32_t *)beta_76(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v18.4s, v3.4s, v18.4s	// tmp177, tmp168, _304
	fmul	v17.4s, v3.4s, v17.4s	// tmp178, tmp168, _317
	fmul	v16.4s, v3.4s, v16.4s	// tmp179, tmp168, _330
	fmul	v7.4s, v3.4s, v7.4s	// tmp180, tmp168, _343
	fmul	v6.4s, v3.4s, v6.4s	// tmp181, tmp168, _356
	fmul	v5.4s, v3.4s, v5.4s	// tmp182, tmp168, _369
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q18, q17, [x0]	// tmp177, tmp178,* Cb
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v4.4s, v3.4s, v4.4s	// tmp183, tmp168, _382
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q16, q7, [x0, 32]	// tmp179, tmp180,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v3.4s, v3.4s, v0.4s	// tmp184, tmp168, _111
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q6, q5, [x0, 64]	// tmp181, tmp182,
	stp	q4, q3, [x0, 96]	// tmp183, tmp184,
// uk.c:564: 	for (int k = 0; k < KC; k++) {
	cmp	x22, 0	// KC,
	ble	.L54		//,
	mov	x3, x20	// ivtmp.448, A
	mov	x4, x19	// ivtmp.449, B
	mov	x2, 0	// ivtmp.446,
	.p2align 3,,7
.L55:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q2, q1, [x4]	// _133, _132,* ivtmp.449
// uk.c:564: 	for (int k = 0; k < KC; k++) {
	add	x2, x2, 1	// ivtmp.446, ivtmp.446,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q0, [x3], 16	// _134,
// uk.c:564: 	for (int k = 0; k < KC; k++) {
	add	x4, x4, 32	// ivtmp.449, ivtmp.449,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:16810:   return __builtin_aarch64_fmav4sf (__b,
	fmla	v18.4s, v0.4s, v2.s[0]	// _131, _134, _133,
	fmla	v17.4s, v0.4s, v2.s[1]	// _129, _134, _133,
	fmla	v16.4s, v0.4s, v2.s[2]	// _127, _134, _133,
	fmla	v7.4s, v0.4s, v2.s[3]	// _125, _134, _133,
	fmla	v6.4s, v0.4s, v1.s[0]	// _124, _134, _132,
	fmla	v5.4s, v0.4s, v1.s[1]	// _123, _134, _132,
	fmla	v4.4s, v0.4s, v1.s[2]	// _122, _134, _132,
	fmla	v3.4s, v0.4s, v1.s[3]	// _121, _134, _132,
// uk.c:564: 	for (int k = 0; k < KC; k++) {
	cmp	x22, x2	// KC, ivtmp.446
	bne	.L55		//,
.L54:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q18, [x0]	// _131,* Cb
// uk.c:587: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q18, [x21]	// _131, MEM <vector(4) float> [(float *)C_93(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q17, [x0, 16]	// _129,
// uk.c:587: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q17, [x21, 16]	// _129, MEM <vector(4) float> [(float *)C_93(D) + 16B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q16, [x0, 32]	// _127,
// uk.c:587: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q16, [x21, 32]	// _127, MEM <vector(4) float> [(float *)C_93(D) + 32B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q7, [x0, 48]	// _125,
// uk.c:587: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q7, [x21, 48]	// _125, MEM <vector(4) float> [(float *)C_93(D) + 48B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q6, [x0, 64]	// _124,
// uk.c:587: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q6, [x21, 64]	// _124, MEM <vector(4) float> [(float *)C_93(D) + 64B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q5, [x0, 80]	// _123,
// uk.c:587: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q5, [x21, 80]	// _123, MEM <vector(4) float> [(float *)C_93(D) + 80B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q4, [x0, 96]	// _122,
// uk.c:587: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q4, [x21, 96]	// _122, MEM <vector(4) float> [(float *)C_93(D) + 96B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q3, [x0, 112]	// _121,
// uk.c:591: }
	ldp	x19, x20, [sp, 16]	//,,
	ldr	x23, [sp, 48]	//,
// uk.c:587: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q3, [x21, 112]	// _121, MEM <vector(4) float> [(float *)C_93(D) + 112B]
// uk.c:591: }
	ldp	x21, x22, [sp, 32]	//,,
	ldp	x29, x30, [sp], 64	//,,,
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 23
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
// uk.c:590: 	free(Cb);
	b	free		//
	.cfi_endproc
.LFE4314:
	.size	uk_4x8_a1True_b1False, .-uk_4x8_a1True_b1False
	.align	2
	.p2align 4,,11
	.global	uk_4x4_a1True_b1False
	.type	uk_4x4_a1True_b1False, %function
uk_4x4_a1True_b1False:
.LFB4315:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!	//,,,
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
// uk.c:594: 	float *Cb = malloc(4 * 4 * sizeof(*Cb));
	mov	x0, 64	//,
// uk.c:593: inline void uk_4x4_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x29, sp	//,
	stp	x21, x22, [sp, 32]	//,,
	.cfi_offset 21, -32
	.cfi_offset 22, -24
	mov	x22, x6	// C, tmp158
	mov	x21, x1	// KC, tmp154
	str	x23, [sp, 48]	//,
	.cfi_offset 23, -16
	mov	x23, x5	// beta, tmp157
	stp	x19, x20, [sp, 16]	//,,
	.cfi_offset 19, -48
	.cfi_offset 20, -40
// uk.c:593: inline void uk_4x4_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x20, x3	// A, tmp155
	mov	x19, x4	// B, tmp156
// uk.c:594: 	float *Cb = malloc(4 * 4 * sizeof(*Cb));
	bl	malloc		//
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q5, q4, [x22]	// _6, _190,* C
	ldp	q3, q0, [x22, 32]	// _163, _83,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:15603:   return (float32x4_t) {__a, __a, __a, __a};
	ld1r	{v2.4s}, [x23]	// tmp137, MEM[(const float32_t *)beta_56(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v5.4s, v5.4s, v2.4s	// tmp142, _6, tmp137
	fmul	v4.4s, v2.4s, v4.4s	// tmp143, tmp137, _190
	fmul	v3.4s, v2.4s, v3.4s	// tmp144, tmp137, _163
	fmul	v2.4s, v2.4s, v0.4s	// tmp145, tmp137, _83
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q5, q4, [x0]	// tmp142, tmp143,* Cb
	stp	q3, q2, [x0, 32]	// tmp144, tmp145,
// uk.c:618: 	for (int k = 0; k < KC; k++) {
	cmp	x21, 0	// KC,
	ble	.L59		//,
	mov	x3, x20	// ivtmp.466, A
	mov	x4, x19	// ivtmp.467, B
	mov	x2, 0	// ivtmp.464,
	.p2align 3,,7
.L60:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q0, [x3], 16	// _97,
// uk.c:618: 	for (int k = 0; k < KC; k++) {
	add	x2, x2, 1	// ivtmp.464, ivtmp.464,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q1, [x4], 16	// _96,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:16810:   return __builtin_aarch64_fmav4sf (__b,
	fmla	v5.4s, v0.4s, v1.s[0]	// _95, _97, _96,
	fmla	v4.4s, v0.4s, v1.s[1]	// _93, _97, _96,
	fmla	v3.4s, v0.4s, v1.s[2]	// _91, _97, _96,
	fmla	v2.4s, v0.4s, v1.s[3]	// _89, _97, _96,
// uk.c:618: 	for (int k = 0; k < KC; k++) {
	cmp	x21, x2	// KC, ivtmp.464
	bne	.L60		//,
.L59:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q5, [x0]	// _95,* Cb
// uk.c:632: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q5, [x22]	// _95, MEM <vector(4) float> [(float *)C_69(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q4, [x0, 16]	// _93,
// uk.c:632: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q4, [x22, 16]	// _93, MEM <vector(4) float> [(float *)C_69(D) + 16B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q3, [x0, 32]	// _91,
// uk.c:632: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q3, [x22, 32]	// _91, MEM <vector(4) float> [(float *)C_69(D) + 32B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q2, [x0, 48]	// _89,
// uk.c:636: }
	ldp	x19, x20, [sp, 16]	//,,
	ldr	x23, [sp, 48]	//,
// uk.c:632: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q2, [x22, 48]	// _89, MEM <vector(4) float> [(float *)C_69(D) + 48B]
// uk.c:636: }
	ldp	x21, x22, [sp, 32]	//,,
	ldp	x29, x30, [sp], 64	//,,,
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 23
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
// uk.c:635: 	free(Cb);
	b	free		//
	.cfi_endproc
.LFE4315:
	.size	uk_4x4_a1True_b1False, .-uk_4x4_a1True_b1False
	.align	2
	.p2align 4,,11
	.global	uk_4x12_a1True_b1False
	.type	uk_4x12_a1True_b1False, %function
uk_4x12_a1True_b1False:
.LFB4316:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!	//,,,
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
// uk.c:639: 	float *Cb = malloc(12 * 4 * sizeof(*Cb));
	mov	x0, 192	//,
// uk.c:638: inline void uk_4x12_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x29, sp	//,
	stp	x19, x20, [sp, 16]	//,,
	.cfi_offset 19, -48
	.cfi_offset 20, -40
	mov	x19, x6	// C, tmp233
	mov	x20, x4	// B, tmp231
	str	x23, [sp, 48]	//,
	.cfi_offset 23, -16
	mov	x23, x5	// beta, tmp232
	stp	x21, x22, [sp, 32]	//,,
	.cfi_offset 21, -32
	.cfi_offset 22, -24
// uk.c:638: inline void uk_4x12_a1True_b1False( void *ctxt, int_fast32_t KC, const float* alpha, const float* A, const float* B, const float* beta, float* C ) {
	mov	x22, x1	// KC, tmp229
	mov	x21, x3	// A, tmp230
// uk.c:639: 	float *Cb = malloc(12 * 4 * sizeof(*Cb));
	bl	malloc		//
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q21, q20, [x19]	// _422, _435,* C
	ldp	q19, q18, [x19, 32]	// _448, _461,
	ldp	q17, q16, [x19, 64]	// _474, _487,
	ldp	q7, q6, [x19, 96]	// _500, _513,
	ldp	q5, q4, [x19, 128]	// _526, _539,
	ldp	q3, q0, [x19, 160]	// _552, _129,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:15603:   return (float32x4_t) {__a, __a, __a, __a};
	ld1r	{v2.4s}, [x23]	// tmp188, MEM[(const float32_t *)beta_89(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v21.4s, v2.4s, v21.4s	// tmp201, tmp188, _422
	fmul	v20.4s, v2.4s, v20.4s	// tmp202, tmp188, _435
	fmul	v19.4s, v2.4s, v19.4s	// tmp203, tmp188, _448
	fmul	v18.4s, v2.4s, v18.4s	// tmp204, tmp188, _461
	fmul	v17.4s, v2.4s, v17.4s	// tmp205, tmp188, _474
	fmul	v16.4s, v2.4s, v16.4s	// tmp206, tmp188, _487
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q21, q20, [x0]	// tmp201, tmp202,* Cb
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v7.4s, v2.4s, v7.4s	// tmp207, tmp188, _500
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q19, q18, [x0, 32]	// tmp203, tmp204,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v6.4s, v2.4s, v6.4s	// tmp208, tmp188, _513
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q17, q16, [x0, 64]	// tmp205, tmp206,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v5.4s, v2.4s, v5.4s	// tmp209, tmp188, _526
	fmul	v4.4s, v2.4s, v4.4s	// tmp210, tmp188, _539
	fmul	v3.4s, v2.4s, v3.4s	// tmp211, tmp188, _552
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q7, q6, [x0, 96]	// tmp207, tmp208,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:1487:   return __a * __b;
	fmul	v2.4s, v2.4s, v0.4s	// tmp212, tmp188, _129
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q5, q4, [x0, 128]	// tmp209, tmp210,
	stp	q3, q2, [x0, 160]	// tmp211, tmp212,
// uk.c:671: 	for (int k = 0; k < KC; k++) {
	cmp	x22, 0	// KC,
	ble	.L64		//,
	mov	x4, x21	// ivtmp.483, A
	mov	x3, x20	// ivtmp.484, B
	mov	x2, 0	// ivtmp.481,
	.p2align 3,,7
.L65:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q0, [x4], 16	// _159,
// uk.c:671: 	for (int k = 0; k < KC; k++) {
	add	x2, x2, 1	// ivtmp.481, ivtmp.481,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q1, [x3], 48	// _158,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:16810:   return __builtin_aarch64_fmav4sf (__b,
	fmla	v21.4s, v0.4s, v1.s[0]	// _157, _159, _158,
	fmla	v20.4s, v0.4s, v1.s[0]	// _155, _159, _158,
	fmla	v19.4s, v0.4s, v1.s[0]	// _153, _159, _158,
	fmla	v18.4s, v0.4s, v1.s[0]	// _151, _159, _158,
	fmla	v17.4s, v0.4s, v1.s[1]	// _150, _159, _158,
	fmla	v16.4s, v0.4s, v1.s[1]	// _149, _159, _158,
	fmla	v7.4s, v0.4s, v1.s[1]	// _148, _159, _158,
	fmla	v6.4s, v0.4s, v1.s[1]	// _147, _159, _158,
	fmla	v5.4s, v0.4s, v1.s[2]	// _146, _159, _158,
	fmla	v4.4s, v0.4s, v1.s[2]	// _145, _159, _158,
	fmla	v3.4s, v0.4s, v1.s[2]	// _144, _159, _158,
	fmla	v2.4s, v0.4s, v1.s[2]	// _143, _159, _158,
// uk.c:671: 	for (int k = 0; k < KC; k++) {
	cmp	x22, x2	// KC, ivtmp.481
	bne	.L65		//,
.L64:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q21, [x0]	// _157,* Cb
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q21, [x19]	// _157, MEM <vector(4) float> [(float *)C_107(D)]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q20, [x0, 16]	// _155,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q20, [x19, 16]	// _155, MEM <vector(4) float> [(float *)C_107(D) + 16B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q19, [x0, 32]	// _153,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q19, [x19, 32]	// _153, MEM <vector(4) float> [(float *)C_107(D) + 32B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q18, [x0, 48]	// _151,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q18, [x19, 48]	// _151, MEM <vector(4) float> [(float *)C_107(D) + 48B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q17, [x0, 64]	// _150,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q17, [x19, 64]	// _150, MEM <vector(4) float> [(float *)C_107(D) + 64B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q16, [x0, 80]	// _149,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q16, [x19, 80]	// _149, MEM <vector(4) float> [(float *)C_107(D) + 80B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q7, [x0, 96]	// _148,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q7, [x19, 96]	// _148, MEM <vector(4) float> [(float *)C_107(D) + 96B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q6, [x0, 112]	// _147,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q6, [x19, 112]	// _147, MEM <vector(4) float> [(float *)C_107(D) + 112B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q5, [x0, 128]	// _146,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q5, [x19, 128]	// _146, MEM <vector(4) float> [(float *)C_107(D) + 128B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q4, [x0, 144]	// _145,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q4, [x19, 144]	// _145, MEM <vector(4) float> [(float *)C_107(D) + 144B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q3, [x0, 160]	// _144,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q3, [x19, 160]	// _144, MEM <vector(4) float> [(float *)C_107(D) + 160B]
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	str	q2, [x0, 176]	// _143,
// uk.c:707: }
	ldp	x21, x22, [sp, 32]	//,,
	ldr	x23, [sp, 48]	//,
// uk.c:703: 			      C[(cj) * (4) + (ci) * (1)] = Cb[(cj) * (4) + (ci) * (1)];
	str	q2, [x19, 176]	// _143, MEM <vector(4) float> [(float *)C_107(D) + 176B]
// uk.c:707: }
	ldp	x19, x20, [sp, 16]	//,,
	ldp	x29, x30, [sp], 64	//,,,
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 23
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
// uk.c:706: 	free(Cb);
	b	free		//
	.cfi_endproc
.LFE4316:
	.size	uk_4x12_a1True_b1False, .-uk_4x12_a1True_b1False
	.align	2
	.p2align 4,,11
	.global	uk_24x4_a1True_b1True
	.type	uk_24x4_a1True_b1True, %function
uk_24x4_a1True_b1True:
.LFB4317:
	.cfi_startproc
	stp	d8, d9, [sp, -64]!	//,,,
	.cfi_def_cfa_offset 64
	.cfi_offset 72, -64
	.cfi_offset 73, -56
	stp	d10, d11, [sp, 16]	//,,
	stp	d12, d13, [sp, 32]	//,,
	str	d14, [sp, 48]	//,
	.cfi_offset 74, -48
	.cfi_offset 75, -40
	.cfi_offset 76, -32
	.cfi_offset 77, -24
	.cfi_offset 78, -16
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q14, [x6]	// C_reg$0$0,* C
	ldp	q13, q12, [x6, 16]	// C_reg$0$1, C_reg$0$2,
	ldp	q11, q10, [x6, 48]	// C_reg$0$3, C_reg$0$4,
	ldp	q9, q8, [x6, 80]	// C_reg$0$5, C_reg$1$0,
	ldp	q31, q30, [x6, 112]	// C_reg$1$1, C_reg$1$2,
	ldp	q29, q28, [x6, 144]	// C_reg$1$3, C_reg$1$4,
	ldp	q27, q26, [x6, 176]	// C_reg$1$5, C_reg$2$0,
	ldp	q25, q24, [x6, 208]	// C_reg$2$1, C_reg$2$2,
	ldp	q23, q22, [x6, 240]	// C_reg$2$3, C_reg$2$4,
	ldp	q21, q20, [x6, 272]	// C_reg$2$5, C_reg$3$0,
	ldp	q19, q18, [x6, 304]	// C_reg$3$1, C_reg$3$2,
	ldp	q17, q16, [x6, 336]	// C_reg$3$3, C_reg$3$4,
	ldr	q7, [x6, 368]	// C_reg$3$5,
// uk.c:737: 	for (int k = 0; k < KC; k++) {
	cmp	x1, 0	// KC,
	ble	.L69		//,
	mov	x0, 0	// ivtmp.494,
	.p2align 3,,7
.L70:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldr	q0, [x4], 16	// _142,
// uk.c:737: 	for (int k = 0; k < KC; k++) {
	add	x0, x0, 1	// ivtmp.494, ivtmp.494,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:17484:   return __builtin_aarch64_ld1v4sf ((const __builtin_aarch64_simd_sf *) __a);
	ldp	q6, q5, [x3]	// _148, _147,* ivtmp.496
	ldp	q4, q3, [x3, 32]	// _146, _145,
	ldp	q2, q1, [x3, 64]	// _144, _143,
// uk.c:737: 	for (int k = 0; k < KC; k++) {
	add	x3, x3, 96	// ivtmp.496, ivtmp.496,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:16810:   return __builtin_aarch64_fmav4sf (__b,
	fmla	v14.4s, v6.4s, v0.s[0]	// C_reg$0$0, _148, _142,
	fmla	v8.4s, v6.4s, v0.s[1]	// C_reg$1$0, _148, _142,
	fmla	v26.4s, v6.4s, v0.s[2]	// C_reg$2$0, _148, _142,
	fmla	v20.4s, v6.4s, v0.s[3]	// C_reg$3$0, _148, _142,
	fmla	v13.4s, v5.4s, v0.s[0]	// C_reg$0$1, _147, _142,
	fmla	v31.4s, v5.4s, v0.s[1]	// C_reg$1$1, _147, _142,
	fmla	v25.4s, v5.4s, v0.s[2]	// C_reg$2$1, _147, _142,
	fmla	v19.4s, v5.4s, v0.s[3]	// C_reg$3$1, _147, _142,
	fmla	v12.4s, v4.4s, v0.s[0]	// C_reg$0$2, _146, _142,
	fmla	v30.4s, v4.4s, v0.s[1]	// C_reg$1$2, _146, _142,
	fmla	v24.4s, v4.4s, v0.s[2]	// C_reg$2$2, _146, _142,
	fmla	v18.4s, v4.4s, v0.s[3]	// C_reg$3$2, _146, _142,
	fmla	v11.4s, v3.4s, v0.s[0]	// C_reg$0$3, _145, _142,
	fmla	v29.4s, v3.4s, v0.s[1]	// C_reg$1$3, _145, _142,
	fmla	v23.4s, v3.4s, v0.s[2]	// C_reg$2$3, _145, _142,
	fmla	v17.4s, v3.4s, v0.s[3]	// C_reg$3$3, _145, _142,
	fmla	v10.4s, v2.4s, v0.s[0]	// C_reg$0$4, _144, _142,
	fmla	v28.4s, v2.4s, v0.s[1]	// C_reg$1$4, _144, _142,
	fmla	v22.4s, v2.4s, v0.s[2]	// C_reg$2$4, _144, _142,
	fmla	v16.4s, v2.4s, v0.s[3]	// C_reg$3$4, _144, _142,
	fmla	v9.4s, v1.4s, v0.s[0]	// C_reg$0$5, _143, _142,
	fmla	v27.4s, v1.4s, v0.s[1]	// C_reg$1$5, _143, _142,
	fmla	v21.4s, v1.4s, v0.s[2]	// C_reg$2$5, _143, _142,
	fmla	v7.4s, v1.4s, v0.s[3]	// C_reg$3$5, _143, _142,
// uk.c:737: 	for (int k = 0; k < KC; k++) {
	cmp	x0, x1	// ivtmp.494, KC
	bne	.L70		//,
.L69:
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q14, q13, [x6]	// C_reg$0$0, C_reg$0$1,* C
// uk.c:794: }
	ldr	d14, [sp, 48]	//,
// /usr/lib/gcc/aarch64-linux-gnu/10/include/arm_neon.h:27835:   __builtin_aarch64_st1v4sf ((__builtin_aarch64_simd_sf *) __a, __b);
	stp	q12, q11, [x6, 32]	// C_reg$0$2, C_reg$0$3,
	stp	q10, q9, [x6, 64]	// C_reg$0$4, C_reg$0$5,
	stp	q8, q31, [x6, 96]	// C_reg$1$0, C_reg$1$1,
	stp	q30, q29, [x6, 128]	// C_reg$1$2, C_reg$1$3,
	stp	q28, q27, [x6, 160]	// C_reg$1$4, C_reg$1$5,
	stp	q26, q25, [x6, 192]	// C_reg$2$0, C_reg$2$1,
	stp	q24, q23, [x6, 224]	// C_reg$2$2, C_reg$2$3,
	stp	q22, q21, [x6, 256]	// C_reg$2$4, C_reg$2$5,
	stp	q20, q19, [x6, 288]	// C_reg$3$0, C_reg$3$1,
	stp	q18, q17, [x6, 320]	// C_reg$3$2, C_reg$3$3,
	stp	q16, q7, [x6, 352]	// C_reg$3$4, C_reg$3$5,
// uk.c:794: }
	ldp	d10, d11, [sp, 16]	//,,
	ldp	d12, d13, [sp, 32]	//,,
	ldp	d8, d9, [sp], 64	//,,,
	.cfi_restore 73
	.cfi_restore 72
	.cfi_restore 78
	.cfi_restore 76
	.cfi_restore 77
	.cfi_restore 74
	.cfi_restore 75
	.cfi_def_cfa_offset 0
	ret	
	.cfi_endproc
.LFE4317:
	.size	uk_24x4_a1True_b1True, .-uk_24x4_a1True_b1True
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1~18.04~1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
