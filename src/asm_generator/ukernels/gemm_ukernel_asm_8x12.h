  .text
  .align      5
  .global     gemm_ukernel_asm_8x12
  .global     gemm_ukernel_asm_edge_8x12

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
  #define C10q       q12
  #define C10v       v12.4s
  #define C11q       q13
  #define C11v       v13.4s
  #define C12q       q14
  #define C12v       v14.4s
  #define C13q       q15
  #define C13v       v15.4s
  #define C14q       q16
  #define C14v       v16.4s
  #define C15q       q17
  #define C15v       v17.4s
  #define C16q       q18
  #define C16v       v18.4s
  #define C17q       q19
  #define C17v       v19.4s
  #define C18q       q20
  #define C18v       v20.4s
  #define C19q       q21
  #define C19v       v21.4s
  #define C110q       q22
  #define C110v       v22.4s
  #define C111q       q23
  #define C111v       v23.4s

  #define A0q        q24
  #define A0v        v24.4s
  #define A1q        q25
  #define A1v        v25.4s

  #define B0q        q26
  #define B0v        v26.s
  #define B1q        q27
  #define B1v        v27.s
  #define B2q        q28
  #define B2v        v28.s

  #define TMP        s29
  #define BETA       s30

  .macro KERNEL_8x12
    ldr A0q, [A_ptr]
    add A_ptr, A_ptr, #16
    ldr A1q, [A_ptr]
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
    fmla C10v, A1v, B0v[0]
    fmla C11v, A1v, B0v[1]
    fmla C12v, A1v, B0v[2]
    fmla C13v, A1v, B0v[3]
    fmla C14v, A1v, B1v[0]
    fmla C15v, A1v, B1v[1]
    fmla C16v, A1v, B1v[2]
    fmla C17v, A1v, B1v[3]
    fmla C18v, A1v, B2v[0]
    fmla C19v, A1v, B2v[1]
    fmla C110v, A1v, B2v[2]
    fmla C111v, A1v, B2v[3]
  .endm

  gemm_ukernel_asm_8x12:
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
    b.eq .LOAD_8x12
    movi C00v, 0
    movi C10v, 0
    movi C01v, 0
    movi C11v, 0
    movi C02v, 0
    movi C12v, 0
    movi C03v, 0
    movi C13v, 0
    movi C04v, 0
    movi C14v, 0
    movi C05v, 0
    movi C15v, 0
    movi C06v, 0
    movi C16v, 0
    movi C07v, 0
    movi C17v, 0
    movi C08v, 0
    movi C18v, 0
    movi C09v, 0
    movi C19v, 0
    movi C010v, 0
    movi C110v, 0
    movi C011v, 0
    movi C111v, 0

    b .S_LOOP_8x12

  .LOAD_8x12:
    ldr C00q, [C00_ptr]
    ldr C10q, [C00_ptr, #16]

    ldr C01q, [C01_ptr]
    ldr C11q, [C01_ptr, #16]

    ldr C02q, [C02_ptr]
    ldr C12q, [C02_ptr, #16]

    ldr C03q, [C03_ptr]
    ldr C13q, [C03_ptr, #16]

    ldr C04q, [C04_ptr]
    ldr C14q, [C04_ptr, #16]

    ldr C05q, [C05_ptr]
    ldr C15q, [C05_ptr, #16]

    ldr C06q, [C06_ptr]
    ldr C16q, [C06_ptr, #16]

    ldr C07q, [C07_ptr]
    ldr C17q, [C07_ptr, #16]

    ldr C08q, [C08_ptr]
    ldr C18q, [C08_ptr, #16]

    ldr C09q, [C09_ptr]
    ldr C19q, [C09_ptr, #16]

    ldr C010q, [C010_ptr]
    ldr C110q, [C010_ptr, #16]

    ldr C011q, [C011_ptr]
    ldr C111q, [C011_ptr, #16]


  .S_LOOP_8x12:
  .LOOP_8x12:
    KERNEL_8x12
    sub kc, kc, 1
    cmp kc, 0
    b.ne .LOOP_8x12

  .STORE_8x12:
    str C00q, [C00_ptr]
    str C10q, [C00_ptr, #16]

    str C01q, [C01_ptr]
    str C11q, [C01_ptr, #16]

    str C02q, [C02_ptr]
    str C12q, [C02_ptr, #16]

    str C03q, [C03_ptr]
    str C13q, [C03_ptr, #16]

    str C04q, [C04_ptr]
    str C14q, [C04_ptr, #16]

    str C05q, [C05_ptr]
    str C15q, [C05_ptr, #16]

    str C06q, [C06_ptr]
    str C16q, [C06_ptr, #16]

    str C07q, [C07_ptr]
    str C17q, [C07_ptr, #16]

    str C08q, [C08_ptr]
    str C18q, [C08_ptr, #16]

    str C09q, [C09_ptr]
    str C19q, [C09_ptr, #16]

    str C010q, [C010_ptr]
    str C110q, [C010_ptr, #16]

    str C011q, [C011_ptr]
    str C111q, [C011_ptr, #16]


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

  .macro KERNEL_8x12_edge
    ldr A0q, [A_ptr, #0]
    ldr A1q, [A_ptr, #16]

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
    fmla C10v, A1v, B0v[0]
    fmla C11v, A1v, B0v[1]
    fmla C12v, A1v, B0v[2]
    fmla C13v, A1v, B0v[3]
    fmla C14v, A1v, B1v[0]
    fmla C15v, A1v, B1v[1]
    fmla C16v, A1v, B1v[2]
    fmla C17v, A1v, B1v[3]
    fmla C18v, A1v, B2v[0]
    fmla C19v, A1v, B2v[1]
    fmla C110v, A1v, B2v[2]
    fmla C111v, A1v, B2v[3]
    add A_ptr, A_ptr, A_desp
    add B_ptr, B_ptr, B_desp
  .endm

  gemm_ukernel_asm_edge_8x12:
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
    movi C10v, 0
    movi C01v, 0
    movi C11v, 0
    movi C02v, 0
    movi C12v, 0
    movi C03v, 0
    movi C13v, 0
    movi C04v, 0
    movi C14v, 0
    movi C05v, 0
    movi C15v, 0
    movi C06v, 0
    movi C16v, 0
    movi C07v, 0
    movi C17v, 0
    movi C08v, 0
    movi C18v, 0
    movi C09v, 0
    movi C19v, 0
    movi C010v, 0
    movi C110v, 0
    movi C011v, 0
    movi C111v, 0

  .S_LOOP_8x12_edge:
  .LOOP_8x12_edge:
    KERNEL_8x12_edge
    sub kc, kc, 1
    cmp kc, 0
    b.ne .LOOP_8x12_edge

  .STORE_8x12_edge:
    str C00q, [C00_ptr]
    str C10q, [C00_ptr, #16]

    str C01q, [C01_ptr]
    str C11q, [C01_ptr, #16]

    str C02q, [C02_ptr]
    str C12q, [C02_ptr, #16]

    str C03q, [C03_ptr]
    str C13q, [C03_ptr, #16]

    str C04q, [C04_ptr]
    str C14q, [C04_ptr, #16]

    str C05q, [C05_ptr]
    str C15q, [C05_ptr, #16]

    str C06q, [C06_ptr]
    str C16q, [C06_ptr, #16]

    str C07q, [C07_ptr]
    str C17q, [C07_ptr, #16]

    str C08q, [C08_ptr]
    str C18q, [C08_ptr, #16]

    str C09q, [C09_ptr]
    str C19q, [C09_ptr, #16]

    str C010q, [C010_ptr]
    str C110q, [C010_ptr, #16]

    str C011q, [C011_ptr]
    str C111q, [C011_ptr, #16]


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

