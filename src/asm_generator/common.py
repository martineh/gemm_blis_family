import os

u_folder      = "ukernels"
c_name        = "gemm_ukernel.c"
selector_name = "selector_ukernel.c"
h_name        = "gemm_ukernel_headers.h"


def generate_edge_function(asm):
    MR = asm.orig_mr
    NR = asm.orig_nr

    #Micro-Kernel Output Files
    name_path = os.path.dirname(__file__) + "/" + u_folder 

    file_name = name_path + "/" + c_name

    foutS = None
    if not os.path.exists(file_name):
        foutS = open(file_name, "w")
        foutS.write("\n#include <stdio.h>\n")
        foutS.write("#include <stdlib.h>\n")
        foutS.write("\n#include \"" + h_name + "\"\n\n")
    else:
        foutS = open(file_name, "a")
   
    foutS.write("void gemm_ukernel_edge_%dx%d(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, \
                 \n                           float *a, float *b, float *beta, float *ctmp, \
                 \n                           float *C, size_t ldC) {\n" % (MR, NR))
    foutS.write("    int i, j;\n")
    MR_target = MR
    NR_target = NR
    min_NR_loop = asm.vl
    if asm.vl != MR or asm.vl != NR:
        if asm.vl == MR:
            MR_target = MR + 1 
        else:
            NR_target = NR + 1

    if asm.arch == "riscv" and (NR < asm.vl):
        min_NR_loop = NR
        NR_target = min_NR_loop + 1

    first = True
    for mr in range (asm.vl, MR_target, asm.vl):
        for nr in range (min_NR_loop, NR_target, asm.vl):
            #asm.set_edge(mr, nr)
            if first:
                foutS.write(f"    if ((mr <= %d) && (nr <= %d))\n" % (mr, nr))
                first = False
            else:
                foutS.write(f"    else if ((mr <= %d) && (nr <= %d))\n" % (mr, nr))
            foutS.write("      gemm_ukernel_asm_edge_%dx%d(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));\n" % (mr, nr))
    if not first:
        foutS.write("    else\n")
    foutS.write("      gemm_ukernel_asm_edge_%dx%d(kc, alpha, a, b, _MR * sizeof(float), ctmp, _NR * sizeof(float));\n\n" % (MR, NR))

    foutS.write("    for (j = 0; j < nr; j++)\n")
    foutS.write("      for (i = 0; i < mr; i++)\n")
    foutS.write("        C[j*ldC + i] = (*beta) * C[j*ldC + i] + ctmp[j * _MR + i];\n")
    foutS.write("}\n")
    foutS.close()

    add_header(MR, NR, edge=True)



def new_micro_file(MR, NR):
    #Micro-Kernel Output Files
    name_path = os.path.dirname(__file__) + "/" + u_folder
   
    #Include .S
    Cname = "gemm_ukernel_asm_%dx%d.S" % (MR, NR)
    file_name = name_path + "/" + Cname
    foutS = open(file_name, "w")
    foutS.write("\n#include \"gemm_ukernel_asm_%dx%d.h\"\n" % (MR, NR))
    foutS.close()

    #ASM Implementation
    Cname = "gemm_ukernel_asm_%dx%d.h" % (MR, NR)
    file_name = name_path + "/" + Cname

    return open(file_name, "w")


def add_header(MR, NR, edge=False):
    #Micro-Kernel Output Files
    name_path = os.path.dirname(__file__) + "/" + u_folder
    file_name = name_path + "/" + h_name
   
    add_header = True
    fdout = None

    if os.path.exists(file_name):
        fdout = open(file_name, "r")
       
        if edge:
            tag="edge" 
        else:
            tag="asm"

        #check if header exists
        header_check = "gemm_ukernel_%s_%dx%d" % (tag, MR, NR)
        for line in fdout:
            if header_check in line:
                add_header = False
                break

        if add_header:
            fdout.close()
            fdout = open(file_name, "a")
    else:
        fdout = open(file_name, "w")
        fdout.write(f"typedef void (*ukernel_asm)(size_t , float *, float *, float *, float *, float *, size_t );\n\n")
        fdout.write(f"typedef void (*ukernel_edge)(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, \n\
                            float *a, float *b, float *beta, float *ctmp, \n\
                            float *C, size_t ldC);\n\n")
        fdout.write(f"void ukernels_selector(int _MR, int _NR, ukernel_asm *ukr, ukernel_edge *ukr_edge);\n\n")

    if add_header:
        if not edge:
            fdout.write(f"void gemm_ukernel_asm_{MR}x{NR}(size_t , float *, float *, float *, float *, float *, size_t );\n\n")
            fdout.write(f"void gemm_ukernel_asm_edge_{MR}x{NR}(size_t , float *, float *, float *, size_t, float *, size_t );\n\n")
        else:
            fdout.write(f"void gemm_ukernel_edge_{MR}x{NR}(size_t mr, size_t nr, size_t _MR, size_t _NR, size_t kc, float *alpha, \n\
                            float *a, float *b, float *beta, float *ctmp, \n\
                            float *C, size_t ldC);\n\n")

    fdout.close()

def generate_selector_function(asm, close=False):
    #Micro-Kernel Output Files
    name_path = os.path.dirname(__file__) + "/" + u_folder
    file_name = name_path + "/" + selector_name
   
    MR = asm.orig_mr
    NR = asm.orig_nr

    add_header = True
    fdout = None

    if close:
        fdout = open(file_name, "a")
        fdout.write("  } else {\n")
        fdout.write("    (*ukr)      = NULL;\n")
        fdout.write("    (*ukr_edge) = NULL;\n")
        fdout.write("  }\n")
        fdout.write("}\n")
        fdout.close()
        return

    if os.path.exists(file_name):
        fdout = open(file_name, "r")
       
        #check if header exists
        header_check = "gemm_ukernel_asm_%dx%d" % (MR, NR)
        for line in fdout:
            if header_check in line:
                add_header = False
                break

        if add_header:
            fdout.close()
            fdout = open(file_name, "a")
    else:
        fdout = open(file_name, "w")
        fdout.write("\n#include <stdio.h>\n")
        fdout.write("#include <stdlib.h>\n")
        fdout.write("\n#include \"" + h_name + "\"\n\n")
        fdout.write("void ukernels_selector(int _MR, int _NR, ukernel_asm *ukr, ukernel_edge *ukr_edge) {\n\n")

        fdout.write("  if (_MR == %d && _NR == %d) {\n" % (MR, NR))
        fdout.write("    (*ukr)      = &gemm_ukernel_asm_%dx%d;\n" % (MR, NR))
        fdout.write("    (*ukr_edge) = &gemm_ukernel_edge_%dx%d;\n" % (MR, NR))
        add_header=False

    if add_header:
        fdout.write("  } else if (_MR == %d && _NR == %d) {\n" % (MR, NR))
        fdout.write("    (*ukr)      = &gemm_ukernel_asm_%dx%d;\n" % (MR, NR))
        fdout.write("    (*ukr_edge) = &gemm_ukernel_edge_%dx%d;\n" % (MR, NR))

    fdout.close()


def clear_path():
    name_path = os.path.dirname(__file__) + "/" + u_folder + "/"

    if os.path.exists(name_path):
        for f in os.listdir(name_path):
            file_name = name_path + f
            os.remove(file_name)
    else:
        os.makedirs(name_path)

#TODO: I don't know... is 'generate_packA' a member function from the class ARMV8 or RISCV??
def generate_packA(asm):
    MR = asm.orig_mr
    NR = asm.orig_nr

    #Micro-Kernel Output Files
    name_path = os.path.dirname(__file__) + "/" + u_folder

    file_name = name_path + "/" + c_name
    foutS = open(file_name, "a")
  
    if asm.arch == "riscv":
        print("Waring: Pack vectorization not implemented for RISCV\n")
    else:
        MR = asm.orig_mr
        MR_row = MR // asm.vl

        foutS.write("\n")
        foutS.write("void pack_A( int _MR, int mc, int kc, float *A, int ldA, float *Ac) {\n")
        foutS.write("  int i, j, ii, k, rr;\n");

        Aregs = "A0"
        for i in range(1, MR_row):
            Aregs += ", A%d" % (i)

        foutS.write("  float32x4_t %s;\n" %(Aregs))
        foutS.write("  for ( i=0; i<mc; i+=_MR ) {\n")
        foutS.write("    k = i * kc;\n")
        foutS.write("    rr = mc-i < _MR ? mc-i : _MR;\n") #(((a)<(b))?(a):(b))
        foutS.write("    if (rr == _MR) {\n")
        foutS.write("      for ( j=0; j<kc; j++ ) {\n")

        dsp=0
        for i in range(0, MR_row):
            foutS.write("        A%d = vld1q_f32(&A[j * ldA + (i + %d)]);\n" %(i, dsp))
            dsp += asm.vl

        dsp=0
        for i in range(0, MR_row):
            foutS.write("        vst1q_f32(&Ac[k], A%d); k += 4;\n" % (i))
            dsp += asm.vl

        foutS.write("      }\n")
        foutS.write("    } else {\n")
        foutS.write("      for ( j=0; j<kc; j++ ) {\n")
        foutS.write("        for ( ii=0; ii < rr; ii++ ) {\n")
        foutS.write("          Ac[k] = A[j * ldA + (i + ii)];\n")
        foutS.write("          k++;\n")
        foutS.write("        }\n")
        foutS.write("        k += (_MR - rr);\n")
        foutS.write("      }\n")
        foutS.write("    }\n")
        foutS.write("  }\n")
        foutS.write("}\n")

    foutS.close()
