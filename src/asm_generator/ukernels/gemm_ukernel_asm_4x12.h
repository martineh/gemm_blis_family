  .text
  .align      5
  .global     gemm_ukernel_asm_4x12
  .global     gemm_ukernel_asm_edge_4x12

  #define kc         x0
  #define alpha_ptr  x1
  #define A_ptr      x2
  #define B_ptr      x3
  #define beta_ptr   x4
  #define C00_ptr    x5
  #define ldC        x6
  #define unroll     x7
  #define kc_iter    x8
  #define kc_left    x9

  #define A_desp     x4
  #define B_desp     x6
  #define buf_desp   x4

  #define C01_ptr    x10
  #define C02_ptr    x11
  #define C03_ptr    x12
  #define C04_ptr    x13
  #define C05_ptr    x14
  #define C06_ptr    x15
  #define C07_ptr    x16
  #define C08_ptr    x17
  #define C09_ptr    x18
  #define C010_ptr    x19
  #define C011_ptr    x20

  #define C00q       q0
  #define C00v       v0.4s
  #define C01q       q1
  #define C01v       v1.4s
  #define C02q       q2
  #define C02v       v2.4s
  #define C03q       q3
  #define C03v       v3.4s
  #define C04q       q4
  #define C04v       v4.4s
  #define C05q       q5
  #define C05v       v5.4s
  #define C06q       q6
  #define C06v       v6.4s
  #define C07q       q7
  #define C07v       v7.4s
  #define C08q       q8
  #define C08v       v8.4s
  #define C09q       q9
  #define C09v       v9.4s
  #define C010q       q10
  #define C010v       v10.4s
  #define C011q       q11
  #define C011v       v11.4s

  #define A0q        q12
  #define A0v        v12.4s

  #define B0q        q13
  #define B0v        v13.s
  #define B1q        q14
  #define B1v        v14.s
  #define B2q        q15
  #define B2v        v15.s

  #define TMP        s16
  #define BETA       s17

  .macro KERNEL_4x12
    ldr A0q, [A_ptr]
    add A_ptr, A_ptr, #16

    ldr B0q, [B_ptr]
    add B_ptr, B_ptr, #16
    ldr B1q, [B_ptr]
    add B_ptr, B_ptr, #16
    ldr B2q, [B_ptr]
    add B_ptr, B_ptr, #16

    fmla C00v, A0v, B0v[0]
    fmla C01v, A0v, B0v[1]
    fmla C02v, A0v, B0v[2]
    fmla C03v, A0v, B0v[3]
    fmla C04v, A0v, B1v[0]
    fmla C05v, A0v, B1v[1]
    fmla C06v, A0v, B1v[2]
    fmla C07v, A0v, B1v[3]
    fmla C08v, A0v, B2v[0]
    fmla C09v, A0v, B2v[1]
    fmla C010v, A0v, B2v[2]
    fmla C011v, A0v, B2v[3]
  .endm

  gemm_ukernel_asm_4x12:
    add	sp, sp, #-(11 * 16)
    stp	d8, d9,   [sp, #(0 * 16)]
    stp	d10, d11, [sp, #(1 * 16)]
    stp	d12, d13, [sp, #(2 * 16)]
    stp	d14, d15, [sp, #(3 * 16)]
    stp	d16, d17, [sp, #(4 * 16)]
    stp	x18, x19, [sp, #(5 * 16)]
    stp	x20, x21, [sp, #(6 * 16)]
    stp	x22, x23, [sp, #(7 * 16)]
    stp	x24, x25, [sp, #(8 * 16)]
    stp	x26, x27, [sp, #(9 * 16)]
    str	x28,      [sp, #(10 * 16)]

    add C01_ptr, C00_ptr, ldC
    add C02_ptr, C01_ptr, ldC
    add C03_ptr, C02_ptr, ldC
    add C04_ptr, C03_ptr, ldC
    add C05_ptr, C04_ptr, ldC
    add C06_ptr, C05_ptr, ldC
    add C07_ptr, C06_ptr, ldC
    add C08_ptr, C07_ptr, ldC
    add C09_ptr, C08_ptr, ldC
    add C010_ptr, C09_ptr, ldC
    add C011_ptr, C010_ptr, ldC

    ldr BETA, [beta_ptr]
    fmov TMP, 1.0e+0 
    fcmp BETA, TMP 
    b.eq .LOAD_4x12
    movi C00v, 0
    movi C01v, 0
    movi C02v, 0
    movi C03v, 0
    movi C04v, 0
    movi C05v, 0
    movi C06v, 0
    movi C07v, 0
    movi C08v, 0
    movi C09v, 0
    movi C010v, 0
    movi C011v, 0

    b .S_LOOP_4x12

  .LOAD_4x12:
    ldr C00q, [C00_ptr]

    ldr C01q, [C01_ptr]

    ldr C02q, [C02_ptr]

    ldr C03q, [C03_ptr]

    ldr C04q, [C04_ptr]

    ldr C05q, [C05_ptr]

    ldr C06q, [C06_ptr]

    ldr C07q, [C07_ptr]

    ldr C08q, [C08_ptr]

    ldr C09q, [C09_ptr]

    ldr C010q, [C010_ptr]

    ldr C011q, [C011_ptr]


  .S_LOOP_4x12:
  .LOOP_4x12:
    KERNEL_4x12
    sub kc, kc, 1
    cmp kc, 0
    b.ne .LOOP_4x12

  .STORE_4x12:
    str C00q, [C00_ptr]

    str C01q, [C01_ptr]

    str C02q, [C02_ptr]

    str C03q, [C03_ptr]

    str C04q, [C04_ptr]

    str C05q, [C05_ptr]

    str C06q, [C06_ptr]

    str C07q, [C07_ptr]

    str C08q, [C08_ptr]

    str C09q, [C09_ptr]

    str C010q, [C010_ptr]

    str C011q, [C011_ptr]


  END:
    mov	x0, #0
    ldp	d8, d9, [sp, #(0 * 16)]
    ldp	d10, d11, [sp, #(1 * 16)]
    ldp	d12, d13, [sp, #(2 * 16)]
    ldp	d14, d15, [sp, #(3 * 16)]
    ldp	d16, d17, [sp, #(4 * 16)]
    ldp	x18, x19, [sp, #(5 * 16)]
    ldp	x20, x21, [sp, #(6 * 16)]
    ldp	x22, x23, [sp, #(7 * 16)]
    ldp	x24, x25, [sp, #(8 * 16)]
    ldp	x26, x27, [sp, #(9 * 16)]
    ldr	x28,      [sp, #(10 * 16)]
    add	sp, sp, #(11*16)
    ret

  .macro KERNEL_4x12_edge
    ldr A0q, [A_ptr, #0]

    ldr B0q, [B_ptr, #0]
    ldr B1q, [B_ptr, #16]
    ldr B2q, [B_ptr, #32]

    fmla C00v, A0v, B0v[0]
    fmla C01v, A0v, B0v[1]
    fmla C02v, A0v, B0v[2]
    fmla C03v, A0v, B0v[3]
    fmla C04v, A0v, B1v[0]
    fmla C05v, A0v, B1v[1]
    fmla C06v, A0v, B1v[2]
    fmla C07v, A0v, B1v[3]
    fmla C08v, A0v, B2v[0]
    fmla C09v, A0v, B2v[1]
    fmla C010v, A0v, B2v[2]
    fmla C011v, A0v, B2v[3]
    add A_ptr, A_ptr, A_desp
    add B_ptr, B_ptr, B_desp
  .endm

  gemm_ukernel_asm_edge_4x12:
    add	sp, sp, #-(11 * 16)
    stp	d8, d9,   [sp, #(0 * 16)]
    stp	d10, d11, [sp, #(1 * 16)]
    stp	d12, d13, [sp, #(2 * 16)]
    stp	d14, d15, [sp, #(3 * 16)]
    stp	d16, d17, [sp, #(4 * 16)]
    stp	x18, x19, [sp, #(5 * 16)]
    stp	x20, x21, [sp, #(6 * 16)]
    stp	x22, x23, [sp, #(7 * 16)]
    stp	x24, x25, [sp, #(8 * 16)]
    stp	x26, x27, [sp, #(9 * 16)]
    str	x28,      [sp, #(10 * 16)]

    add C01_ptr, C00_ptr, buf_desp
    add C02_ptr, C01_ptr, buf_desp
    add C03_ptr, C02_ptr, buf_desp
    add C04_ptr, C03_ptr, buf_desp
    add C05_ptr, C04_ptr, buf_desp
    add C06_ptr, C05_ptr, buf_desp
    add C07_ptr, C06_ptr, buf_desp
    add C08_ptr, C07_ptr, buf_desp
    add C09_ptr, C08_ptr, buf_desp
    add C010_ptr, C09_ptr, buf_desp
    add C011_ptr, C010_ptr, buf_desp

    movi C00v, 0
    movi C01v, 0
    movi C02v, 0
    movi C03v, 0
    movi C04v, 0
    movi C05v, 0
    movi C06v, 0
    movi C07v, 0
    movi C08v, 0
    movi C09v, 0
    movi C010v, 0
    movi C011v, 0

  .S_LOOP_4x12_edge:
  .LOOP_4x12_edge:
    KERNEL_4x12_edge
    sub kc, kc, 1
    cmp kc, 0
    b.ne .LOOP_4x12_edge

  .STORE_4x12_edge:
    str C00q, [C00_ptr]

    str C01q, [C01_ptr]

    str C02q, [C02_ptr]

    str C03q, [C03_ptr]

    str C04q, [C04_ptr]

    str C05q, [C05_ptr]

    str C06q, [C06_ptr]

    str C07q, [C07_ptr]

    str C08q, [C08_ptr]

    str C09q, [C09_ptr]

    str C010q, [C010_ptr]

    str C011q, [C011_ptr]


  END_edge:
    mov	x0, #0
    ldp	d8, d9, [sp, #(0 * 16)]
    ldp	d10, d11, [sp, #(1 * 16)]
    ldp	d12, d13, [sp, #(2 * 16)]
    ldp	d14, d15, [sp, #(3 * 16)]
    ldp	d16, d17, [sp, #(4 * 16)]
    ldp	x18, x19, [sp, #(5 * 16)]
    ldp	x20, x21, [sp, #(6 * 16)]
    ldp	x22, x23, [sp, #(7 * 16)]
    ldp	x24, x25, [sp, #(8 * 16)]
    ldp	x26, x27, [sp, #(9 * 16)]
    ldr	x28,      [sp, #(10 * 16)]
    add	sp, sp, #(11*16)
    ret

