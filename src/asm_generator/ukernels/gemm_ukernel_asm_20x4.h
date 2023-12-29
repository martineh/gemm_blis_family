  .text
  .align      5
  .global     gemm_ukernel_asm_20x4
  .global     gemm_ukernel_asm_edge_20x4

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

  #define C00q       q0
  #define C00v       v0.4s
  #define C01q       q1
  #define C01v       v1.4s
  #define C02q       q2
  #define C02v       v2.4s
  #define C03q       q3
  #define C03v       v3.4s
  #define C10q       q4
  #define C10v       v4.4s
  #define C11q       q5
  #define C11v       v5.4s
  #define C12q       q6
  #define C12v       v6.4s
  #define C13q       q7
  #define C13v       v7.4s
  #define C20q       q8
  #define C20v       v8.4s
  #define C21q       q9
  #define C21v       v9.4s
  #define C22q       q10
  #define C22v       v10.4s
  #define C23q       q11
  #define C23v       v11.4s
  #define C30q       q12
  #define C30v       v12.4s
  #define C31q       q13
  #define C31v       v13.4s
  #define C32q       q14
  #define C32v       v14.4s
  #define C33q       q15
  #define C33v       v15.4s
  #define C40q       q16
  #define C40v       v16.4s
  #define C41q       q17
  #define C41v       v17.4s
  #define C42q       q18
  #define C42v       v18.4s
  #define C43q       q19
  #define C43v       v19.4s

  #define A0q        q20
  #define A0v        v20.4s
  #define A1q        q21
  #define A1v        v21.4s
  #define A2q        q22
  #define A2v        v22.4s
  #define A3q        q23
  #define A3v        v23.4s
  #define A4q        q24
  #define A4v        v24.4s

  #define B0q        q25
  #define B0v        v25.s

  #define TMP        s26
  #define BETA       s27

  .macro KERNEL_20x4
    ldr A0q, [A_ptr]
    add A_ptr, A_ptr, #16
    ldr A1q, [A_ptr]
    add A_ptr, A_ptr, #16
    ldr A2q, [A_ptr]
    add A_ptr, A_ptr, #16
    ldr A3q, [A_ptr]
    add A_ptr, A_ptr, #16
    ldr A4q, [A_ptr]
    add A_ptr, A_ptr, #16

    ldr B0q, [B_ptr]
    add B_ptr, B_ptr, #16

    fmla C00v, A0v, B0v[0]
    fmla C01v, A0v, B0v[1]
    fmla C02v, A0v, B0v[2]
    fmla C03v, A0v, B0v[3]
    fmla C10v, A1v, B0v[0]
    fmla C11v, A1v, B0v[1]
    fmla C12v, A1v, B0v[2]
    fmla C13v, A1v, B0v[3]
    fmla C20v, A2v, B0v[0]
    fmla C21v, A2v, B0v[1]
    fmla C22v, A2v, B0v[2]
    fmla C23v, A2v, B0v[3]
    fmla C30v, A3v, B0v[0]
    fmla C31v, A3v, B0v[1]
    fmla C32v, A3v, B0v[2]
    fmla C33v, A3v, B0v[3]
    fmla C40v, A4v, B0v[0]
    fmla C41v, A4v, B0v[1]
    fmla C42v, A4v, B0v[2]
    fmla C43v, A4v, B0v[3]
  .endm

  gemm_ukernel_asm_20x4:
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

    ldr BETA, [beta_ptr]
    fmov TMP, 1.0e+0 
    fcmp BETA, TMP 
    b.eq .LOAD_20x4
    movi C00v, 0
    movi C10v, 0
    movi C20v, 0
    movi C30v, 0
    movi C40v, 0
    movi C01v, 0
    movi C11v, 0
    movi C21v, 0
    movi C31v, 0
    movi C41v, 0
    movi C02v, 0
    movi C12v, 0
    movi C22v, 0
    movi C32v, 0
    movi C42v, 0
    movi C03v, 0
    movi C13v, 0
    movi C23v, 0
    movi C33v, 0
    movi C43v, 0

    b .S_LOOP_20x4

  .LOAD_20x4:
    ldr C00q, [C00_ptr]
    ldr C10q, [C00_ptr, #16]
    ldr C20q, [C00_ptr, #32]
    ldr C30q, [C00_ptr, #48]
    ldr C40q, [C00_ptr, #64]

    ldr C01q, [C01_ptr]
    ldr C11q, [C01_ptr, #16]
    ldr C21q, [C01_ptr, #32]
    ldr C31q, [C01_ptr, #48]
    ldr C41q, [C01_ptr, #64]

    ldr C02q, [C02_ptr]
    ldr C12q, [C02_ptr, #16]
    ldr C22q, [C02_ptr, #32]
    ldr C32q, [C02_ptr, #48]
    ldr C42q, [C02_ptr, #64]

    ldr C03q, [C03_ptr]
    ldr C13q, [C03_ptr, #16]
    ldr C23q, [C03_ptr, #32]
    ldr C33q, [C03_ptr, #48]
    ldr C43q, [C03_ptr, #64]


  .S_LOOP_20x4:
  .LOOP_20x4:
    KERNEL_20x4
    sub kc, kc, 1
    cmp kc, 0
    b.ne .LOOP_20x4

  .STORE_20x4:
    str C00q, [C00_ptr]
    str C10q, [C00_ptr, #16]
    str C20q, [C00_ptr, #32]
    str C30q, [C00_ptr, #48]
    str C40q, [C00_ptr, #64]

    str C01q, [C01_ptr]
    str C11q, [C01_ptr, #16]
    str C21q, [C01_ptr, #32]
    str C31q, [C01_ptr, #48]
    str C41q, [C01_ptr, #64]

    str C02q, [C02_ptr]
    str C12q, [C02_ptr, #16]
    str C22q, [C02_ptr, #32]
    str C32q, [C02_ptr, #48]
    str C42q, [C02_ptr, #64]

    str C03q, [C03_ptr]
    str C13q, [C03_ptr, #16]
    str C23q, [C03_ptr, #32]
    str C33q, [C03_ptr, #48]
    str C43q, [C03_ptr, #64]


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

  .macro KERNEL_20x4_edge
    ldr A0q, [A_ptr, #0]
    ldr A1q, [A_ptr, #16]
    ldr A2q, [A_ptr, #32]
    ldr A3q, [A_ptr, #48]
    ldr A4q, [A_ptr, #64]

    ldr B0q, [B_ptr, #0]

    fmla C00v, A0v, B0v[0]
    fmla C01v, A0v, B0v[1]
    fmla C02v, A0v, B0v[2]
    fmla C03v, A0v, B0v[3]
    fmla C10v, A1v, B0v[0]
    fmla C11v, A1v, B0v[1]
    fmla C12v, A1v, B0v[2]
    fmla C13v, A1v, B0v[3]
    fmla C20v, A2v, B0v[0]
    fmla C21v, A2v, B0v[1]
    fmla C22v, A2v, B0v[2]
    fmla C23v, A2v, B0v[3]
    fmla C30v, A3v, B0v[0]
    fmla C31v, A3v, B0v[1]
    fmla C32v, A3v, B0v[2]
    fmla C33v, A3v, B0v[3]
    fmla C40v, A4v, B0v[0]
    fmla C41v, A4v, B0v[1]
    fmla C42v, A4v, B0v[2]
    fmla C43v, A4v, B0v[3]
    add A_ptr, A_ptr, A_desp
    add B_ptr, B_ptr, B_desp
  .endm

  gemm_ukernel_asm_edge_20x4:
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

    movi C00v, 0
    movi C10v, 0
    movi C20v, 0
    movi C30v, 0
    movi C40v, 0
    movi C01v, 0
    movi C11v, 0
    movi C21v, 0
    movi C31v, 0
    movi C41v, 0
    movi C02v, 0
    movi C12v, 0
    movi C22v, 0
    movi C32v, 0
    movi C42v, 0
    movi C03v, 0
    movi C13v, 0
    movi C23v, 0
    movi C33v, 0
    movi C43v, 0

  .S_LOOP_20x4_edge:
  .LOOP_20x4_edge:
    KERNEL_20x4_edge
    sub kc, kc, 1
    cmp kc, 0
    b.ne .LOOP_20x4_edge

  .STORE_20x4_edge:
    str C00q, [C00_ptr]
    str C10q, [C00_ptr, #16]
    str C20q, [C00_ptr, #32]
    str C30q, [C00_ptr, #48]
    str C40q, [C00_ptr, #64]

    str C01q, [C01_ptr]
    str C11q, [C01_ptr, #16]
    str C21q, [C01_ptr, #32]
    str C31q, [C01_ptr, #48]
    str C41q, [C01_ptr, #64]

    str C02q, [C02_ptr]
    str C12q, [C02_ptr, #16]
    str C22q, [C02_ptr, #32]
    str C32q, [C02_ptr, #48]
    str C42q, [C02_ptr, #64]

    str C03q, [C03_ptr]
    str C13q, [C03_ptr, #16]
    str C23q, [C03_ptr, #32]
    str C33q, [C03_ptr, #48]
    str C43q, [C03_ptr, #64]


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

