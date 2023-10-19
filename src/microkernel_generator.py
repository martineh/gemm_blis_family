#!/usr/bin/python

import math


class GEMM:
    def __init__(self, assembly, orderA, orderB, orderC, mr, nr, register_size, mv, nv, vl, arch, unroll, dtype, packA, packB, broadcast):
        self.assembly = assembly
        self.orderA = orderA
        self.orderB = orderB
        self.orderC = orderC
        self.mr = mr
        self.nr = nr
        self.register_size = register_size
        self.mv = mv
        self.nv = nv
        self.vl = vl
        self.arch = arch
        self.unroll = unroll
        self.dtype = dtype
        self.packA = packA
        self.packB = packB
        self.broadcast = broadcast



##------------------------##
## MACROS WITH INTRINSICS ##
##------------------------##


def define_macro_risc_v(gemm):  # TODO revisar tipos de datos
    mac  = "#ifdef RVV4\n"
    mac += "// Macros for RISC-V V\n"
    mac += "    #define vl_fp32 4 \n"
    mac += "    #define vregister vfloat32m1_t \n" 
    mac += "    #define vinit(vl) \\\n" 
    mac += "        float init[vl]; \\\n"
    mac += "        memset(&init, 0.0, vl); \\\n"
    mac += "         vle32_v_f32m1(&init, vl))\\\n"
    mac += "\n"
    mac += "    #define vload(vreg, mem)                vreg = vle32_v_f32m1(mem, vl_fp32)\n"
    mac += "    #define vstore(mem, vreg)               vse32_v_f32m1(mem, vreg, vl_fp32)\n"
    mac += "    #define vupdate(vreg1, vreg2, vreg3, j) vreg1 = vfmacc_vf_f32m1(vreg1, vreg3[j], vreg2, vl_fp32)\n"
    mac += "#endif \n"
    return mac


def define_macro_avx(gemm):  
    # Register size = 256 bits in AVX2, 512 in AVX-512
    # DOCS https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=avx2&ig_expand=31
    bitsize = int(gemm.dtype[-2:])
    data = gemm.dtype[:-2]
    dtype_one_letter = {"float32": "s",
                        "float64": "d",
                        "float16": "h"}
    mac = ""
    #mac += "#ifdef AVX2\n"
    if gemm.register_size == 256:
        mac  += "// Macros for AVX2\n"
    elif gemm.register_size == 512:
        mac  += "// Macros for AVX_512\n"
    #mac += "    #define vl_fp32 16 \n"
    mac += "    #define vregister __m{}{} \n".format(gemm.register_size, "" if gemm.dtype == "float32" else dtype_one_letter[gemm.dtype])
    mac += "    #define vinit(vreg) vreg = _mm{}_set1_p{}(0); \n".format(gemm.register_size, dtype_one_letter.get(gemm.dtype))
    mac += "    #define vload(vreg, mem)  vreg = _mm{}_loadu_p{}(mem) \n".format(gemm.register_size, dtype_one_letter.get(gemm.dtype))
    mac += "    #define vstore(mem, vreg) _mm{}_storeu_p{}(mem, vreg) \n".format(gemm.register_size, dtype_one_letter.get(gemm.dtype))
    mac += "    #define vupdate(vreg1, vreg2, vreg3, j) {} vreg1 = _mm{}_fmadd_p{}(vreg2, _mm{}_set1_p{}(vreg3[j]), vreg1); {} \n".format("{", gemm.register_size, dtype_one_letter.get(gemm.dtype), 
                                                                                                                                          gemm.register_size, dtype_one_letter.get(gemm.dtype), "}")
    #mac += "#endif"
    return mac


def define_macro_sve(gemm):
    bitsize = int(gemm.dtype[-2:])
    data = gemm.dtype[:-2]
    mac = "// Macros for ARM SVE\n"
    mac += "    #define vl_fp{} {} \n".format(bitsize, gemm.register_size // bitsize)
    mac += "    #define vregister sv{}{}_t\n".format(data, bitsize)
    mac += "    #define vpred(mr) svbool_t pred = svwhilelt_b32_u32(0, min(vl_fp32, mr))\n"
    mac += "    #define vinit(vreg) vreg = svdup_{}{}(0)\n".format(data[:1], bitsize)
    mac += "    #define vbroadcast(vreg, value) vreg = svdup_{}{}(value)\n".format(data[:1], bitsize)
    mac += "    #define vload(vreg, mem)  vreg = svld1_{}{}(pred, mem)\n".format(data[:1], bitsize)
    mac += "    #define vstore(mem, vreg) svst1_{}{}(pred, mem, vreg)\n".format(data[:1], bitsize)
    #mac += "    #define vupdate(vreg1, vreg2, mem, j) vreg1 = svmla_n_{}{}_z(pred, vreg1, vreg2, mem)\n".format(data[:1], bitsize)  # With lane
    mac += "    #define vupdate(vreg1, vreg2, mem) vreg1 = svmla_{}{}_z(pred, vreg1, vreg2, mem)\n".format(data[:1], bitsize)   # With broadcast        C00 = svmla_f32_z(pred8, C00, A0, B0);
    return mac


def define_macro_neon(gemm):
    bitsize = int(gemm.dtype[-2:])
    data = gemm.dtype[:-2]
    mac  = "// Macros for ARM NEON \n"
    mac += "    #define vl_fp{} {} \n".format(bitsize, gemm.register_size // bitsize)
    mac += "    #define vregister {}{}x{}_t \n".format(data, bitsize, gemm.register_size // bitsize)
    mac += "    #define vload(vreg, mem)                vreg = vld1q_f{}(mem) \n".format(bitsize)
    mac += "    #define vstore(mem, vreg)               vst1q_f{}(mem, vreg) \n".format(bitsize)
    mac += "    #define vupdate(vreg1, vreg2, vreg3, j) vreg1 = vfmaq_laneq_f{}(vreg1, vreg2, vreg3, j) \n".format(bitsize)
    mac += "    #define vinit(vreg)                     vreg = vmovq_n_f{}(0) \n".format(bitsize)
    mac += "    #define vbroadcast(a1,a2)               a1 = vdupq_n_f{}(a2) \n".format(bitsize)
    return mac  


##----------------------##
## MACROS WITH ASSEMBLY ##
##----------------------##


def define_macro_neon_assembly(gemm):
    bitsize = int(gemm.dtype[-2:])
    data = gemm.dtype[:-2]
    mac  = "// Macros for ARM NEON using assembly\n"
    #dtype_one_letter = {"float32": "s",
                        #"float64": "d",
                        #"float16": "h"}
                                                                ##asm("vmovsldup (%1), %0": "=v"(zmm): "r"(addr))
    #mac += "    #define vload_asm(vreg, reg, offset)            (__asm__ __volatile__(\"ldr vreg, [reg, #offset] \");) \n"
    #mac += "    #define vupdate_asm(vreg1, vreg2, vreg3, j)     (__asm__ __volatile__(\"fmla vreg1, vreg2, vreg3[j] \");) \n"
    #mac += "    #define add_asm(dest, src, value)               ({ __asm__ __volatile__(\"flds %1\n\t\" \
                                                                    #\"fadds %2\n\t\" \
                                                                    #\"fsts %0\n\t\" \
                                                                    #: \"=m\" (result) \
                                                                    #: \"m\" (src), \"m\" (val)); \
                                                                    #result;\
                                                                #})

    #\"add dest, src, #value \");) \n"
    #mac += "    #define sub_asm(dest, src, value)               (__asm__ __volatile__(\"sub dest, src, #value \");) \n"
    #mac += "    #define cmp_asm(value1, value2)                 (__asm__ __volatile__(\"cmp value1, value2 \");) \n"
    
    return mac

#/*#define ADD(a, b) ({ \
    #int result; \
    #__asm__ ("add %1, %0;" : "=r" (result) : "r" (a), "0" (b)); \
    #result; \
#})*/

#// #define ADD_FLOAT32(dest, src, val) ({ \
#//     float result; \
#//     __asm__ ("flds %1\n\t" \
#//              "fadds %2\n\t" \
#//              "fsts %0\n\t" \
#//              : "=m" (result) \
#//              : "m" (src), "m" (val)); \
#//     result; \
#// })
#// In this macro, we define an ADD_FLOAT32 macro that takes three arguments: dest (the destination float), src (the source float), and val (the value to add to the source float). 
#// The assembly code for adding a 32-bit float value to another 32-bit float value using inline assembly is:
#// 
#//     flds %1: Load the source float value onto the floating-point stack.
#//     fadds %2: Add the value to add to the source float value.
#//     fsts %0: Store the result into the destination float.
#// 
 #We use the "=m" constraint to indicate that the output operand should be stored in memory, and the "m" constraint to indicate that all input operands can be stored in memory. 
 #Note that this macro assumes that all arguments are 32-bit float values. If you need to add other data types, you will need to use the appropriate assembly instructions and data types.


def define_macro_avx_assembly(gemm):
    pass


def define_macro_risc_v_assembly(gemm):
    pass


def define_macro_sve_assembly(gemm):
    pass


##--------------------------##
## END MACROS WITH ASSEMBLY ##
##--------------------------##



def define_macros(gemm):
    gemm.arch.lower(); gemm.dtype.lower()
    mac  = "#include \"microkernel.h\"\n"

    if gemm.assembly:
        macros = {"riscv": define_macro_risc_v_assembly, 
                "avx512": define_macro_avx_assembly,
                "avx2": define_macro_avx_assembly,
                "neon": define_macro_neon_assembly,
                "sve": define_macro_sve_assembly}
        f_mac = macros.get(gemm.arch)
        mac += f_mac(gemm)
        
    macros = {"riscv": define_macro_risc_v, 
            "avx512": define_macro_avx,
            "avx2": define_macro_avx,
            "neon": define_macro_neon,
            "sve": define_macro_sve}
        
    f_mac = macros.get(gemm.arch)
    mac += f_mac(gemm)
    
    # Common macros
    #mac += "    #define min(a,b) (((a)<(b))?(a):(b)) \n"
    mac += "    #define Ccol(a1,a2)  C[(a2) * (ldC) + (a1)] \n"
    mac += "    #define Crow(a1,a2)  C[(a1) * (ldC) + (a2)] \n"
    mac += "    #define Ctcol(a1,a2) Ctmp[(a2) * (ldCt) + (a1)] \n"
    mac += "    #define Ctrow(a1,a2) Ctmp[(a1) * (ldCt) + (a2)] \n"
    mac += "    #define Ctref(a1,a2) Ctmp[(a2) * (ldCt) + (a1)] \n"
    if gemm.packA == "N":
        mac += "    #define Acol(a1,a2)  A[(a2) * (ldA) + (a1)] \n"
        mac += "    #define Arow(a1,a2)  A[(a1) * (ldA) + (a2)] \n"
    if gemm.packB == "N":
        mac += "    #define Bcol(a1,a2)  B[(a2) * (ldB) + (a1)] \n"
        mac += "    #define Brow(a1,a2)  B[(a1) * (ldB) + (a2)] \n"
    mac += "    #define FUNROLL {}\n".format(gemm.unroll)
    
    if gemm.assembly:
        if gemm.packA == "N" and gemm.packB == "N":
            pass
        if gemm.packA == "N":
            pass
        if gemm.packB == "N":
            pass
        mac += define_loop_body_asm(gemm) 
    else:
        # Macros in case matrix A and B are not packed
        if gemm.broadcast == "L":  # Multiply accesing lane in vector register
            if gemm.packA == "N" and gemm.packB == "N":
                mac += define_loop_body_ab(gemm)
            if gemm.packA == "N":
                mac += define_loop_body_1_register_A(gemm)
            if gemm.packB == "N":
                mac += define_loop_body_b(gemm)
            mac += define_loop_body(gemm)
        else:  # Multiply using broadcast
            if gemm.packA == "N" and gemm.packB == "N":
                for i in range(1, gemm.nr):
                    macro = "LOOP_BODY_AB_NR{}".format(i)
                    mac += define_loop_body_broadcast(gemm, macro, gemm.mv, i)
            if gemm.packA == "N":
                macro = "LOOP_BODY_A"
                mac += define_loop_body_broadcast(gemm, macro, 1, gemm.nr)
            if gemm.packB == "N":
                for i in range(1, gemm.nr):
                    macro = "LOOP_BODY_B_NR{}".format(i)
                    mac += define_loop_body_broadcast(gemm, macro, gemm.mv, i)
            macro = "LOOP_BODY"
            mac += define_loop_body_broadcast(gemm, macro, gemm.mv, gemm.nr)
        
    return mac


def add_header(gemm):
    header  = ""
    header += "inline void gemm_ukernel_Cresident_SIMD(int mr, int nr, int kc, {}, int ldA, {}, int ldB, DTYPE *C, int ldC, char orderC, DTYPE beta) {}\n".format("DTYPE *Ar" if gemm.packA == "Y" else "DTYPE *A", 
                                                                                                                                                                  "DTYPE *Br" if gemm.packB == "Y" else "DTYPE *B", "{")
    header += "// mr x nr = {} x {} micro-kernel and C resident in regs.\n".format(gemm.mr if gemm.orderC == "C" else gemm.nr, 
                                                                                   gemm.nr if gemm.orderC == "C" else gemm.mr)
    header += "// Inputs:\n"
    header += "//   - C stored in {}-major order, with leading dimension ldC\n".format("column" if gemm.orderC == "C" else "row")
    header += "//   - {}, with leading dimension {}\n".format("Ar packed by columns" if gemm.packA == "Y" else "A stored in {}-major order".format("column" if gemm.orderC == "C" else "row"), 
                                                              "mr = " + str(gemm.mr) if gemm.packA == "Y" else "ldA")
    header += "//   - {}, with leading dimension {}\n".format("Br packed by rows" if gemm.packB == "Y" else "B stored in {}-major order".format("column" if gemm.orderC == "C" else "row"),
                                                              "nr = " + str(gemm.nr) if gemm.packB == "Y" else "ldB")
    return header


def quick_return():
    return "  if (kc == 0) return;\n"


def declare_variables(gemm):
    """
    int       pr, baseA = 0, baseB = 0; 
    vregister Cr[mv][nr]      // Micro-tile of C
              ar[mv], br[nv]; // Single column/row of Ar/Br
    """
    variables  = "  int       i, j, pr, baseA = 0, baseB = 0, ldCt = {}, Amr, Bnr;\n".format("MR" if gemm.orderC == "C" else "NR")    
    variables += "  vregister "
    
    for j in range(gemm.nr):
        variables += "Cr0_{}, ".format(j)
    for i in range(gemm.mv - 1):
        variables += "\n            "
        for j in range(gemm.nr):
            variables += "Cr{}_{}, ".format(i + 1, j)
        variables += '\n            '
    
    for j in range(gemm.nr):
        variables += "A0_{}, ".format(j)
    for i in range(gemm.mv - 1):
        variables += "\n            "
        for j in range(gemm.nr):
            variables += "A{}_{}, ".format(i + 1, j)
        variables += '\n'
    variables = variables[:-2]  # Para 4x4 es 2
    if variables[-1] == ",":  # Hace falta para mr = 8
        variables = variables[:-1]  
    variables += ";\n"
    # Para orderA = R --> Cr es hasta Cr2_8 (uk 8x12)
    variables += "  vregister "
    for i in range(gemm.mv):
        variables += "ar{}, ".format(i)
    
    for i in range(gemm.nv):
        variables += "br{}, ".format(i)
    variables = variables[:-2]
    variables += "; \n"      
    
    # For SVE is needed a extra register to multiply Beta using broadcast
    if gemm.broadcast == "B":
        variables += "  vregister RBeta; \n"
        
    variables += "  DTYPE zero = 0.0, one = 1.0, Ctmp[MR * NR], *Aptr, *Bptr; \n"
    
    # To multiply without packing, you need a temporal buffer to load elements in vregisters
    if gemm.packA == "N":
        variables += "  DTYPE Atmp[MR];"
    if gemm.packB == "N":
        variables += "  DTYPE Btmp[NR];"
    variables += "\n"
    
    # Declaring registers to the microkernel with assembly
    #if gemm.assembly:
        #variables += "  register DTYPE *baseA_reg asm (\"x24\") = {};".format("Ar" if gemm.packA == "Y" else "A")
        #variables += "  register DTYPE *baseB_reg asm (\"x26\") = {};".format("Br" if gemm.packB == "Y" else "B")
        
        
    return variables


def init(gemm):
    start = "  "
    
    # For SVE only
    if gemm.broadcast == "B":
        start += "vpred(mr); \n  "
        start += "vbroadcast(RBeta, beta); \n  "
    
    # Initialize vregister to 0 for matrix C
    for j in range(gemm.nr):
        start += "vinit(Cr{}_{}); ".format(0, j)
    start += "\n  "
    for i in range(gemm.mv-1):
        for j in range(gemm.nr):
            start += "vinit(Cr{}_{}); ".format(i + 1, j)
        start += "\n  "
        
    # Initialize vregister to 0 for matrix A (B is C if row-major)
    for i in range(gemm.mv):
        start += "vinit({}{}); ".format("ar" if gemm.orderC == "C" else "br", i)
    start += "\n  "
    
    # Initialize vregister to 0 for matrix B (A is C if row-major)
    for i in range(gemm.nv):
        start += "vinit({}{}); ".format("br" if gemm.orderC == "C" else "ar", i)
    return start


def check_orderC(gemm):  # TODO habrá que cambiarlo cuando orderA y orderB sean R
    order  = ""
    order += "  if (orderC == \'C\') { \n"
    order += " " * 4 + "Aptr = {}; \n".format("&Ar[0]" if gemm.packA == "Y" else "&A[0]")
    order += " " * 4 + "Bptr = {}; \n".format("&Br[0]" if gemm.packB == "Y" else "&B[0]")
    order += " " * 4 + "Amr  = {}; \n".format("MR" if gemm.packA == "Y" else "ldA")
    order += " " * 4 + "Bnr  = {}; \n".format("NR" if gemm.packB == "Y" else "1" if gemm.orderB == "C" else "ldB")
    order += "  } else { \n"
    order += " " * 4 + "Aptr = {}; \n".format("&Br[0]" if gemm.packB == "Y" else "&B[0]")
    order += " " * 4 + "Bptr = {}; \n".format("&Ar[0]" if gemm.packA == "Y" else "&A[0]")
    order += " " * 4 + "Amr  = {}; \n".format("NR" if gemm.packB == "Y" else "1" if gemm.orderB == "C" else "ldB")
    order += " " * 4 + "Bnr  = {}; \n".format("MR" if gemm.packA == "Y" else "ldA")
    order += "  } \n"
    return order


def define_loop_body(gemm):
    text  = "    #define LOOP_BODY \\\n"
    text += "{\\\n"
    # Load matrix A
    if gemm.packA == "Y":
        text += load_A_register(gemm)
    else:
        text += load_A_manually(gemm)
    
    # Load matrix B
    if gemm.packB == "Y":
        text += load_B_register(gemm)
    else:
        text += load_B_manually(gemm)
    
    text += update_micro_tile(gemm, gemm.mv, gemm.nv)
    return text


def define_loop_body_broadcast(gemm, name_macro, mv, nv):
    text  = "    #define {} \\\n".format(name_macro)
    text += "{\\\n"
    
    # Load matrix A
    if gemm.packA == "Y" and gemm.orderC == "C":
        text += load_A_register(gemm)
    else:
        text += load_A_manually_broadcast(gemm)
    
    # Update microtile
    text += update_micro_tile_broadcast(gemm, mv, nv)
    return text


def define_loop_body_asm(gemm):
    size_of_byte = 8
    bitsize = int(gemm.dtype[-2:])
    data = gemm.dtype[:-2]
    
    loop  = "    #define LOOP_BODY \\\n"
    loop += "{ \\\n"    
    loop += update_micro_tile_asm(gemm)
    loop += "    asm add_asm(x24, x24, {}); \\\n".format(bitsize * gemm.mr // size_of_byte)  # baseA += Amr (asumiendo Amr == MR)
    loop += "    asm add_asm(x26, x26, {}); \\\n".format(bitsize * gemm.nr // size_of_byte)  # baseB += Bnr (asumiendo Bnr == NR)
    loop += "} \n"
    return loop
    

def update_micro_tile_asm(gemm):
    # Constants to implement the code
    size_of_byte = 8
    bitsize = int(gemm.dtype[-2:])
    data = gemm.dtype[:-2]
    dtype_one_letter = {"float32": "s",
                        "float64": "d",
                        "float16": "h"}
    
    registers_arch = {"neon":   32,
                      "avx512": 32
                      }
    
    num_registers_arch = registers_arch.get(gemm.arch)
    num_registers_c = gemm.nr * gemm.mv
    
    # Code
    upd = ""
    
    # Load A
    for vregister_a in range(gemm.mv):
        upd += "    vload_asm(q{}, x24, {}); \\\n".format(
            num_registers_c + vregister_a,                                  # Starting to the next available register. First go C, then A and then B
            vregister_a * bitsize * size_of_byte // gemm.register_size)     # Offset to load
    
    # Load B
    for vregister_b in range(gemm.nv):
        upd += "    vload_asm(q{}, x26, {}); \\\n".format(
            num_registers_c + gemm.mv + vregister_b,                        # Starting to the next available register. First go C, then A and then B
            vregister_b * bitsize * size_of_byte // gemm.register_size)     # Offset to load
    
    #" ldr q20, [x24]                   \n\t"  // Load A
    #"                                  \n\t"
    #" ldr q22, [x26]                   \n\t"  // Load B

    #" ldr q26, [x26,#64]               \n\t" 
    
    
    #mac += "    #define vload_asm(vreg, reg, offset)            asm(\"ldr vreg, [reg, #offset] \") \n"
    #mac += "    #define vupdate_asm(vreg1, vreg2, vreg3, j)     asm(\"fmla vreg1, vreg2, vreg3[j] \") \n"
    #mac += "    #define add_asm(reg_dest, reg_ori, value)       asm(\"add reg_dest, reg_ori, #value \") \n"
    #mac += "    #define sub_asm(reg_dest, reg_ori, value)       asm(\"sub reg_dest, reg_ori, #value \") \n"
    #mac += "    #define cmp_asm(value1, value2)                 asm(\"cmp value1, value2 \") \n"
    for column in range(gemm.mv):
        for row in range(gemm.nv):
            for lane in range(gemm.vl):
                upd += "    vupdate_asm(\"v{}.2{}\", \"v{}.2{}\", \"v{}.{}\", {}); \\\n".format(
                    column * gemm.mv,                               #
                    dtype_one_letter.get(gemm.dtype),               # DTYPE for the register
                    num_registers_arch - gemm.nv - gemm.mv + row,   #
                    dtype_one_letter.get(gemm.dtype),               # DTYPE for the register
                    num_registers_arch - gemm.nv + row,             #
                    dtype_one_letter.get(gemm.dtype),               # DTYPE for the register
                    lane)                                           # Lane to operate in the vector register
                    #column, row)                                    # For comments
    
    return upd
        
        
def update_micro_tile(gemm, mv, nr):
    upd = ""
    
    if gemm.orderC == "C":
        for iv in range(mv):
            for jv in range(nr):
                for j in range(min(gemm.vl, gemm.nr)):
                    Cr = "Cr{}_{}".format(iv, jv * gemm.vl + j)
                    upd += "    vupdate({}, ar{}, br{}, {});\\\n".format(Cr, iv, jv, j)

    else:
        for iv in range(nr):
            for jv in range(mv):
                for j in range(min(gemm.vl, gemm.mr)):
                    Cr = "Cr{}_{}".format(jv, iv * gemm.vl + j)
                    upd += "    vupdate({}, ar{}, br{}, {});\\\n".format(Cr, jv, iv, j)
    
    
    upd += "    baseA += Amr; baseB += Bnr;\\\n"
    upd += "} \n"
    
    return upd



def update_micro_tile_broadcast(gemm, mv, nr):
    upd = ""
    
    if gemm.orderC == "C":
        for iv in range(mv):
                jv = 0
                for j in range(min(gemm.vl, nr)):
                    #mac += "    #define vbroadcast(vreg, value) vreg = svdup_{}{}(value)\n".format(data[:1], bitsize)
                    #B0  = svdup_n_f32(Bptr[baseB + 0]);
                    upd += "    vbroadcast(br{}, Bptr[baseB + {}]);\\\n".format(j % 2, j if gemm.orderB == "R" else str(j)+"*ldB")
                    Cr = "Cr{}_{}".format(iv, jv * gemm.vl + j)
                    upd += "    vupdate({}, ar{}, br{});\\\n".format(Cr, iv, j % 2)

    else:
        for iv in range(nr):
            for jv in range(mv):
                for j in range(min(gemm.vl, gemm.mr)):
                    upd += "    vbroadcast(ar{}, Bptr[baseB + {}]);\\\n".format(j % 2, j)
                    Cr = "Cr{}_{}".format(jv, iv * gemm.vl + j)
                    upd += "    vupdate({}, ar{}, br{}, {});\\\n".format(Cr, jv, iv, j)
    
    
    upd += "    baseA += Amr; baseB += Bnr;\\\n"
    upd += "} \n"
    
    return upd



# Loads directly into the register, used when matrix A is packed
def load_A_register(gemm):
    load = ""
    for iv in range(gemm.mv if gemm.orderC == "C" else gemm.nv):
        load += "    vload({}{}, {} + {} + {});\\\n".format("ar" if gemm.orderC == "C" else "br", iv, "Aptr" if gemm.orderC == "C" else "Bptr","baseA" if gemm.orderC == "C" else "baseB", iv * gemm.vl)
    return load


# Loads directly into the register, used when matrix B is packed        
def load_B_register(gemm):
    load = ""
    for iv in range(gemm.nv if gemm.orderC == "C" else gemm.mv):
        load += "    vload({}{}, {} + {} + {});\\\n".format("br" if gemm.orderC == "C" else "ar", iv, "Bptr" if gemm.orderC == "C" else "Aptr","baseB" if gemm.orderC == "C" else "baseA", iv * gemm.vl)
    return load



##-----------------##
## LOADS WITH LANE ##
##-----------------##

# Used only when matrix A or B are not packed

# Load only 1 register with VL elements
def load_one_register(gemm, vregister, matrix):
    load = ""
    if gemm.orderC == "C":
        load += "    for (i = 0; i < {}; i++) {} \\\n".format("mr" if matrix == "A" else "nr", "{")
        load += "        {}0[i] = {}ptr[base{} + i{}];\\\n".format(vregister, matrix, matrix, "" if matrix_aligned(gemm, matrix) else "*ld{}".format(matrix))
        load += "    }\\\n"
    else:
        load += "    for (i = 0; i < {}; i++) {} \\\n".format("mr" if matrix == "A" else "nr", "{")
        load += "        {}0[i] = {}ptr[base{} + i{}];\\\n".format("br" if vregister == "ar" else "ar", "B" if matrix == "A" else "A", "B" if matrix == "A" else "A",
                                                                   "" if matrix_aligned(gemm, matrix) else "*ld{}".format(matrix))
        load += "    }\\\n"
    return load


# Load MR elements into vregister A when matrix A is not packed
def load_A_manually(gemm):
    load = ""
    if gemm.orderC == "C":
        for i in range(gemm.mr - gemm.vl):
            load += " " * 4 + "ar{}[{}] = Aptr[baseA + {}{}];\\\n".format(i // gemm.vl, i % gemm.vl, i, "" if gemm.orderA == "C" else "*ldA")
        # Load last register
        load += "    for (i = {}, j = 0; i < mr; i++, j++) {} \\\n".format(gemm.mr - gemm.vl, "{")
        load += "        ar{}[j] = Aptr[baseA + i{}];\\\n".format(gemm.mv - 1, "" if gemm.orderA == "C" else "*ldA")
        load += "    }\\\n"
    else:  # gemm.orderC == R --> Load matrix B because it will be B x A
        for i in range(gemm.nr - gemm.vl):
            load += " " * 4 + "br{}[{}] = Bptr[baseB + {}{}];\\\n".format(i // gemm.vl, i % gemm.vl, i, "" if gemm.orderA == "C" else "*ldA")
        # Load last register
        load += "    for (i = {}, j = 0; i < mr; i++, j++) {} \\\n".format(gemm.nr - gemm.vl, "{")  # Quizá es i < nr en lugar de i < mr
        load += "        br{}[j] = Bptr[baseB + i{}];\\\n".format(gemm.nv - 1, "" if gemm.orderA == "C" else "*ldA")
        load += "    }\\\n"
    return load 


# Load NR elements into vregister B when matrix B is not packed
def load_B_manually(gemm):
    load = ""
    if gemm.orderC == "C":
        # Load last register
        load += "    for (i = 0; i < nr; i++) { \\\n"
        load += "        Btmp[i] = Bptr[baseB + i{}]; \\\n".format("" if gemm.orderB == "R" else "*ldB")
        load += "    } \\\n"
        load += "    for (i = nr; i < NR; i++) { \\\n"
        load += "        Btmp[i] = 0; \\\n"
        load += "    } \\\n"
        for i in range(gemm.nv):
            load += "    vload(br{}, &Btmp[{}]); \\\n" .format(i, i * gemm.vl)
    else:  # gemm.orderC == R --> Load matrix A because it will be B x A
        for i in range(gemm.mr - gemm.vl):
            load += " " * 4 + "ar{}[{}] = Aptr[baseA + {}{}];\\\n".format(i // gemm.vl, i % gemm.vl, i, "" if gemm.orderB == "R" else "*ldB")
        # Load last register
        load += "    for (i = {}, j = 0; i < nr; i++, j++) {} \\\n".format(gemm.mr - gemm.vl, "{")
        load += "        ar{}[j] = Aptr[baseA + i{}];\\\n".format(gemm.mv - 1, "" if gemm.orderB == "R" else "*ldB")
        load += "    }\\\n"
    return load



##---------------------##
## LOADS WITH ASSEMBLY ##
##---------------------##

  
def load_A_register_assembly(gemm):
    load  = "    __asm__ volatile \\\n"
    load += "    ( \\\n"
    load += "    LABEL(LOOP_ITER_{}vx{} \\\n".format(gemm.mv, gemm.nr)
    load += "    \" ldr q{}, [x{}]  \\n\\t \" // Load A \\\n".format(29, 24)
    #load += "    ldr q{}, [x{}]  // Load A \\\n".format(num_registers_arch - gemm.nv, register_A)
    for i in range(29 - 1, 29 - gemm.mv, -1):
        load += "    \" ldr q{}, [x{}, #{}] \\n\\t \" \\\n".format(29, 24, gemm.vl * (29 - i))
    
    load += "\n"
    return load


  #" ldr q30, [x26]                   \n\t"  // Load B
  #" ldr q31, [x26,#16]               \n\t"  

def load_B_register_assembly(gemm):
    load  = ""
    load += "    ldr q{}, [x{}]  // Load B \\\n".format(31, 26)
    #load += "    ldr q{}, [x{}]  // Load B \\\n".format(num_registers_arch, register_B)
    for i in range(31 - 1, 31 - gemm.nv, -1):
        load += "    \" ldr q{}, [x{}, #{}] \\n\\t \" \\\n".format(31, 26, gemm.vl * (29 - i))

    load += "\n"
    return load




##----------------------##
## LOADS WITH BROADCAST ##
##----------------------##

# Used only when matrix A or B are not packed

# Load only 1 register with VL elements
# Multiplication will be with broadcast, so vregister B must contain the same value in all lanes
def load_one_register_broadcast(gemm, vregister, matrix):
    load = ""
    if gemm.orderC == "C":
        if matrix == "A":
            if not matrix_aligned(gemm, matrix):
                load += "    for (i = 0; i < {}; i++) {} \\\n".format(gemm.vl, "{")
                load += "        Atmp[i] = Aptr[baseA + i*ldA]; \\\n"
                load += "    } \\\n"
                load += "    vload(ar0, Atmp); \\\n"
            else:
                load += "    vload(ar0, A); \\\n"
    else:
        if matrix == "A":
            load += "    for (i = 0; i < {}; i++) {} \\\n".format(gemm.vl, "{")
            load += "        Atmp[i] = Aptr[baseB]; \\\n"
            load += "    } \\\n"
            load += "    vload(ar0, Atmp); \\\n"

    return load


# Load MR elements into vregister A when matrix A is not packed
def load_A_manually_broadcast(gemm):
    load = ""
    if gemm.orderC == "C":
        # Load last register
        if gemm.orderA == "R":
            load += "    for (i = 0; i < mr; i++) { \\\n"
            load += "        Atmp[i] = Aptr[baseA + i*ldA]; \\\n"
            load += "    } \\\n"
        for i in range(gemm.mv):
            load += "    vload(ar{}, {}); \\\n" .format(i, "&Aptr[baseA + {}]".format(i * gemm.vl) if gemm.orderA == "C" else "&Atmp[{}]".format(i * gemm.vl))
        
    else:  # gemm.orderC == R --> Load matrix B because it will be B x A
            
        for i in range(gemm.nr - gemm.vl):
            load += " " * 4 + "br{}[{}] = Bptr[baseB + {}{}];\\\n".format(i // gemm.vl, i % gemm.vl, i, "" if gemm.orderA == "C" else "*ldA")
        # Load last register
        load += "    for (i = {}, j = 0; i < mr; i++, j++) {} \\\n".format(gemm.nr - gemm.vl, "{")  # Quizá es i < nr en lugar de i < mr
        load += "        br{}[j] = Bptr[baseB + i{}];\\\n".format(gemm.nv - 1, "" if gemm.orderA == "C" else "*ldA")
        load += "    }\\\n"
    return load



def matrix_aligned(gemm, matrix): return matrix == "A" and gemm.orderA == "C" or matrix == "B" and gemm.orderB == "R"



def define_loop_body_1_register_A(gemm):
    text = "    #define LOOP_BODY_A \\\n"
    text += "{\\\n"
    
    # Load matrix A
    if gemm.broadcast == "B":
        text += load_one_register_broadcast(gemm, "ar", "A")
    else:
        text += load_one_register(gemm, "ar", "A")
        
    # Load matrix B
    if gemm.broadcast == "L":
        if gemm.packB == "Y":
            text += load_B_register(gemm)
        else:
            text += load_B_manually(gemm)
            
    # Update microtile
    if gemm.broadcast == "B":
        text += update_micro_tile_broadcast(gemm, 1 if gemm.orderC == "C" else gemm.nr, gemm.nr if gemm.orderC == "C" else 1)
    else:
        text += update_micro_tile(gemm, 1 if gemm.orderC == "C" else gemm.nv, gemm.nv if gemm.orderC == "C" else 1)
    return text


def define_loop_body_b(gemm):
    text = "    #define LOOP_BODY_B \\\n"
    text += "{\\\n"
    
    # Load matrix A
    if gemm.packA == "Y":
        text += load_A_register(gemm)
    else:
        if gemm.broadcast == "B":
            text += load_A_manually_broadcast(gemm)
        else:
            text += load_A_manually(gemm)
        
    # Load matrix B
    if gemm.broadcast == "B":
        text += load_one_register_broadcast(gemm, "br", "B")
    else:
        text += load_one_register(gemm, "br", "B")
    
    # Update microtile
    if gemm.broadcast == "B":
        text += update_micro_tile_broadcast(gemm, 1 if gemm.orderC == "C" else gemm.nv, gemm.nv if gemm.orderC == "C" else 1)
    else:
        text += update_micro_tile(gemm, 1 if gemm.orderC == "C" else gemm.nv, gemm.nv if gemm.orderC == "C" else 1)    
    return text


def define_loop_body_ab(gemm):  
    text = "    #define LOOP_BODY_AB \\\n"
    text += "{\\\n"
    
    # Load matrix A and B
    if gemm.broadcast == "B":
        text += load_one_register_broadcast(gemm, "ar", "A")
        text += load_one_register_broadcast(gemm, "br", "B")
    else:
        text += load_one_register(gemm, "ar", "A")
        text += load_one_register(gemm, "br", "B")
    
    # Update microtile
    if gemm.broadcast == "B":
        text += update_micro_tile_broadcast(gemm, 1 if gemm.orderC == "C" else gemm.nv, gemm.nv if gemm.orderC == "C" else 1)
    else:
        text += update_micro_tile(gemm, 1 if gemm.orderC == "C" else gemm.nv, gemm.nv if gemm.orderC == "C" else 1)    
    return text



def vload(dest, iv, j, gemm):
    return "    vload({}{}_{}, &Ccol({}, {}));\n".format(dest, iv, j, iv * gemm.vl, j)


def load_micro_tile_C(mv, nr, vl):
    loads  = "  // Load the micro-tile of C into vector registers,\n"
    loads += "  // each with vl_fp32 = {} FP32 elements\n".format(vl)
    for iv in range(mv):
      for j in range(nr):
          loads += vload("Cr",iv,j, gemm)  # vreg = vle32_v_f32m4 ( mem , vl_fp32 )
    return loads


def vloadAB(dest, iv,vl):
    if dest == "ar":
        return "    vload({}{}, &Ar[baseA+{}]);\n".format(dest,iv,iv*vl)
    else:
        return "    vload({}{}, &Br[baseB+{}]);\n".format(dest,iv,iv*vl)


def load_A_and_B(mv,nv,vl):
#Sin packing vload de 1 en 1 A en broadcast y B de 1 en 1

#Si la A no se sale de la matriz se puede hacer el load de microkernel
#La B habrá que acceder a elementos de B, cargarlos sobre un vector temporal y luego cargarlos. 
#No puede haber ifs dentro del for. En la cabecera de se recibe float*A y int ldA.
#Atmp[0] = Acol(0,0), Atmp[1] = Acol(1,0)... hasta 4 (o los que hagan falta). 
#A0 = vload(&Atmp. Esto dentro de if mr==MR && nr==NR

  """
  for ( pr=0; pr<kc; pr++ ) {
    // Load the pr-th column/row of Ar/Br into vector registers
    for ( iv=0; iv<mv; iv++ )
      vload(ar[iv], &Ar[baseA+iv*vl_fp32]); 
    for ( jv=0; jv<nv; jv++ )
      vload(br[jv], &Br[baseB+jv*vl_fp32]);
  """
  #loads = "  for ( pr=0; pr<kc; pr++ ) {}\n".format("{")
  loads = "    // Load the pr-th column/row of Ar/Br into vector registers\n"
  for iv in range(mv):
      loads += vloadAB("ar",iv,vl)
  for jv in range(nv):
      loads += vloadAB("br",jv,vl)
  return loads


def vupdate(iv,jv,vl,j):
    #vreg3 = v f ma cc _v f _f 32 m4 ( vreg3 , vreg2 , vreg1 , vl_fp32 )
    Cr = "Cr{}_{}".format(iv,jv*vl+j)
    #upd="        {} = vfmacc_vf_f32{}({},br{}[{}],ar{},{});\n".format(Cr,riscv_size,Cr,jv,j,iv,vl)
    upd = "    vupdate({}, ar{}, br{}, {});\n".format(Cr,iv,jv,j)
    return upd


def loop(gemm):  
    it = "  int it = kc % FUNROLL;\n"
    tabs = 2
    
    # Case when matrix A and B are not packed
    if gemm.packA == "N" and gemm.packB == "N":
        it += "  if (mr < {} && nr < {}) {} \n".format(gemm.vl, gemm.vl if gemm.broadcast == "L" else gemm.nr, "{")
        tabs = 4
        if gemm.broadcast == "L":
            # If can access any lane in the vector register, just generate one macro
            macro = "LOOP_BODY_AB"
            it += loopbody(gemm, macro, tabs)
            it += "  }\n"
        else:
            # If access to any lane is forbiden
            # Multiply will ve doing using broadcast of one element of matrix B in a vector register
            # We must generate as many macros as NR size (only in case matrix B is not packed)
            # TODO check orderC == R
            it += "    if (nr == 1) { \n"
            macro = "LOOP_BODY_AB_NR1"
            tabs = 6
            it += loopbody(gemm, macro, tabs)
            it += "    }\n"
            for i in range(2, gemm.nr):
                it += "    else if (nr == {}) {} \n".format(i, "{")
                macro = "LOOP_BODY_AB_NR{}".format(i)
                tabs = 6
                it += loopbody(gemm, macro, tabs)
                it += "    }\n"
            it += "  }\n"
            
    # Case matrix A is not packed
    # TODO check orderC == R when broadcasting
    if gemm.packA == "N":
        if gemm.packB == "N": it += "  else { \n"
        it += "  if (mr < {}) {} \n".format(gemm.vl, "{")
        macro = "LOOP_BODY_A"
        tabs = 4
        it += loopbody(gemm, macro, tabs)
        it += "  } \n"
        
    # Case matrix B is not packed
    if gemm.packB == "N":
        if gemm.packA == "N": it += "  else { \n" 
        it += "  if (nr < {}) {} \n".format(gemm.vl if gemm.broadcast == "L" else gemm.nr, "{")
        tabs = 4
        if gemm.broadcast == "L":
            # If can access any lane in the vector register, just generate one macro
            macro = "LOOP_BODY_B"
            it += loopbody(gemm, macro, tabs)
            it += "  }\n"
        else:
            # If access to any lane is forbiden
            # Multiply will ve doing using broadcast of one element of matrix B in a vector register
            # We must generate as many macros as NR size (only in case matrix B is not packed)
            # TODO check orderC == R
            it += "    if (nr == 1) { \n"
            macro = "LOOP_BODY_B_NR1"
            tabs = 6
            it += loopbody(gemm, macro, tabs)
            it += "    }\n"
            for i in range(2, gemm.nr):
                it += "    else if (nr == {}) {} \n".format(i, "{")
                macro = "LOOP_BODY_B_NR{}".format(i)
                tabs = 6
                it += loopbody(gemm, macro, tabs)
                it += "    }\n"
            it += "  }\n"

    # Extra bracket for base case
    if gemm.packA == "N" or gemm.packB == "N":
        tabs = 4
        it += "  else {\n"
    
    # Base case
    macro = "LOOP_BODY"
    it += loopbody(gemm, macro, tabs)
    
    # Close brackets
    if gemm.packA == "N" and gemm.packB == "N": it += "  }\n"
    if gemm.packA == "N":                       it += "  }\n"
    if gemm.packB == "N":                       it += "  }\n"
    
    # Return code
    return it


def loopbody(gemm, macro, tabs):
    it  = " " * tabs + "if (alpha != zero) { \n"
    it  = ""
    it += " " * (tabs + 2) + "for (pr = 0; pr < it; pr++) { \n"
    it += " " * (tabs + 4) + macro + "; \n"
    it += " " * (tabs + 2) + "} \n"
    it += " " * (tabs + 2) + "for (pr = it; pr < kc; pr += FUNROLL) { \n"
    for i in range(gemm.unroll):
        it += " " * (tabs + 2) + macro + ";\n"
    it += "    } \n"
    #it += " " * (tabs + 2) + "if (alpha == -one) {\n"
    #for i in range(gemm.nr):
        #it += " " + (tabs + 2) + "Cr{} = -Cr{};"
    #if ( alpha==-one ) {
		    #C00 = -C00; C01 = -C01; C02 = -C02; C03 = -C03; 
	    #}
	    #else if ( alpha!=one ) {
		    #C00 = alpha*C00; C01 = alpha*C01; C02 = alpha*C02; C03 = alpha*C03; 
	    #}
    #it += "    } \n"
    return it
    

def check_mr(gemm):
    text  = " " * 2 + "if ((mr < MR) || (nr < NR)) {\n"
    text += store_micro_tile(gemm, "tref")  # To store in Ctref
    text += "\n" 
    text += " " * 4 + "if (beta != zero) { \n"      
    text += " " * 6 + "for (j = 0; j < nr; j++) \n" 
    text += " " * 8 + "for (i = 0; i < mr; i++) \n" 
    # TODO cambiar para que sirva para ambas versiones
    if gemm.orderC == "C":
        text += " " * 10 + "Ccol(i,j) = beta * Ccol(i,j) + Ctcol(i,j); \n"
    else:
        text += " " * 10 + "Crow(i,j) = beta * Crow(i,j) + Ctrow(i,j); \n"
    
    text += " " * 4 + "} else { \n"
    text += " " * 6 + "for (j = 0; j < nr; j++) \n" 
    text += " " * 8 + "for (i = 0; i < mr; i++) \n"
    
    if gemm.orderC == "C":
        text += " " * 10 + "Ccol(i,j) = Ctcol(i,j); \n"
    else:
        text += " " * 10 + "Crow(i,j) = Ctrow(i,j); \n"
    
    text += " " * 4 + "} \n"
    text += " " * 2 + "} else if ((mr == MR) && (nr == NR)) { \n"
    text += check_beta(gemm)
    return text

    
def check_beta(gemm):
    check = " " * 2 + "if ( beta != zero ) {\n"
    # Load A
    for iv in range(gemm.mv):
        for j in range(gemm.nr):
            check += vload("A", iv, j, gemm)
    for i in range(gemm.mv):
        for j in range(gemm.nr):
            if gemm.broadcast == "B":
                check += "    vupdate(Cr{}_{}, RBeta, A{}_{});\n".format(i,j, i,j, i,j)
            else:
                check += "    Cr{}_{} += beta * A{}_{}; \n".format(i,j, i,j)
        check += '\n'
    check += "  }\n"
    return check


def vstore(dest, j, iv, gemm):
    if dest == "tref":
        return "  vstore(&C{}({}, {}), Cr{}_{}); \n".format(dest, iv * gemm.vl, j, iv, j)
    #Ctref(a1, a2) Ctmp[(a2) * (ldCt) + (a1)]
    return "  vstore(&Ccol({},{}), Cr{}_{});\n".format(iv * gemm.vl, j, iv, j)


def store_micro_tile(gemm, dest=""):
    """
  // Store the micro-tile in memory
  for ( j=0; j<nr; j++ )
    for ( iv=0; iv<mv; iv++ )
      vstore(&C[j*ldC+iv*vl_fp32], Cr[iv][j]);
}
    """
    #print(nr, mv, vl)
    store = ""
    for iv in range(gemm.mv):
        for j in range(gemm.nr):
            store += vstore(dest, j, iv, gemm)
    return store




def main(assembly, orderA, orderB, orderC, og_mr, og_nr, register_size, arch, unroll, dtype, packA, packB, name, broadcast):
    
    if orderC == "R": mr = og_nr; nr = og_mr            # If matrix C is row-major, change mr and nr because it's B * A, no A * B
    else: mr = og_mr; nr = og_nr
    
    if arch == "neon":   register_size = 128            # Check if register_size is correct according to arch (Only for ARM NEON)
    if arch == "avx2":   register_size = 256            # Check if register_size is correct according to arch (Only for AVX2 and AVX_512)
    if arch == "avx512": register_size = 512            # Check if register_size is correct according to arch (Only for AVX2 and AVX_512)
    if arch == "sve":    broadcast = "B"                # SVE only allows broadcasting, not lane
    if dtype == "double": dtype = "float64"             # Change name of double to float64
    if unroll < 1: unroll = 1                           # Check if unroll is less than 1. unroll cannot be less than 1, so assume a 0 or negative value as 1
    if mr < 1: mr = 1                                   # Check if mr is less than 1. mr cannot be less than 1, so assume a 0 or negative value as 1
    if nr < 1: nr = 1                                   # Check if nr is less than 1. nr cannot be less than 1, so assume a 0 or negative value as 1
    
        
    vl = int(register_size) // int(dtype[-2:])          # Vector lane, number of elements in a single register
    mv = int(math.ceil(mr/vl))                          # Number of register used to store matrix A
    nv = int(math.ceil(nr/vl))                          # Number of register used to store matrix B
    if arch == "sve":                                   # In SVE will be doing broadcasting and each register will store one value repeated in all lanes
        nv = 2                                          # So use 2 registers to alternate them in the loop as a kind of prefetching
    max_l = int(vl/4)                                   # Used with RISC-V
    riscv_size = "m{}".format(max_l)                    # Used with RISC-V

    gemm = GEMM(assembly=assembly, orderA=orderA, orderB=orderB, orderC=orderC, mr=mr, nr=nr, register_size=register_size, arch=arch, unroll=unroll, dtype=dtype, packA=packA, packB=packB, mv=mv, nv=nv, vl=vl, broadcast=broadcast)
    # Store in "text" the C code for the microkernel
    text  = ""
    text += define_macros(gemm)
    text += "\n"
    text += add_header(gemm)
    text += "\n"
    text += quick_return()
    text += declare_variables(gemm)
    text += "\n"
    text += init(gemm)
    text += "\n"
    text += check_orderC(gemm)
    text += loop(gemm)
    text += check_mr(gemm)
    text += "  // Store the micro-tile in memory\n"
    text += store_micro_tile(gemm)
    text += "    } \n}"
    
    # Create file .c
    with open(name, "w") as f:
        f.write(text)

    # Crear el .h
    includes = {"riscv": "", 
                "avx512": "#include <immintrin.h>\n",
                "avx2": "#include <immintrin.h>\n",
                "neon": "#include <arm_neon.h>\n",
                "sve": "#include <arm_sve.h>\n"}
    include = includes.get(gemm.arch)
    
    with open("microkernel.h".format(arch), "w") as f:
        text_h  = include
        text_h += "#include \"dtypes.h\" \n"
        text_h += "void gemm_ukernel_Cresident_SIMD(int, int, int, DTYPE *, int, DTYPE *, int, DTYPE *, int, char, DTYPE); \n"
        f.write(text_h)
    
        
    #print(text)


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description='MR and NR values')
    parser.add_argument("--assembly", "-S", action="store_true", required=False, 
                        help="Generate microkernel with assembly instead of intrinsics")
    parser.add_argument("--orderA", required=False, default="C",
                        help="Order for the matrix A (Column | Row) (default %(default)s)",
                        choices=["C", "R"])
    parser.add_argument("--orderB", required=False, default="C",
                        help="Order for the matrix B (Column | Row) (default %(default)s)",
                        choices=["C", "R"])
    parser.add_argument("--orderC", required=False, default="C",
                        help="Order for the matrix C (Column | Row) (default %(default)s)",
                        choices=["C", "R"])
    parser.add_argument('--mr', required=False, default=4, type=int,
                        help='MR size of the microkernel (default: %(default)s)')
    parser.add_argument('--nr', required=False, default=4, type=int,
                        help='NR size of the microkernel (default: %(default)s)')
    parser.add_argument('--register_size', required=False, default=128, type=int,
                        help='Register size (in bits) (default: %(default)s)')
    parser.add_argument("--arch", required=False, default="neon",
                        help="Arch (default: %(default)s)", choices=["neon", "avx2", "avx512", "sve", "riscv"])
    parser.add_argument("--unroll", required=False, default=1, type=int,
                        help="Factor unroll (default: %(default)s) Factor lower than 1 will be processed as 1")
    parser.add_argument("--dtype", required=False, default="float32", 
                        help="Data type (default: %(default)s)", 
                        choices=["float16", "float32", "float64", "double"])    # TODO int16, int32, ¿int64?
    parser.add_argument("--packA", required=False, default="Y",
                        help="Packing on matrix A (Y|N) (default: %(default)s)")
    parser.add_argument("--packB", required=False, default="Y",
                        help="Packing on matrix B (Y|N) (default: %(default)s)")
    parser.add_argument("--name", required=False, default="microkernel.c",
                        help="Name for the microkernel generated (default: %(default)s)")
    parser.add_argument("--broadcast", required=False, default="L",
                        help="Multiply with broadcasting (B) or lane (L) (default %(default)s)", choices=["L", "B"])
    args = parser.parse_args()
    
    main(assembly=args.assembly, orderA=args.orderA, orderB=args.orderB, orderC=args.orderC, og_mr=args.mr, og_nr=args.nr, register_size=args.register_size, arch=args.arch, unroll=args.unroll, 
         dtype=args.dtype, packA=args.packA, packB=args.packB, name=args.name, broadcast=args.broadcast)
