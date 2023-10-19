include Makefile.inc

#------------------------------------------
#| COMPILERS                              |
#------------------------------------------
CC       =  gcc
CLINKER  =  gcc
#------------------------------------------

OBJDIR = build
BIN    = test_gemm.x
_OBJ   = gemm_blis.o inutils.o sutils.o test_gemm.o model_level.o microkernel.o

#------------------------------------------
#| PATHS CONFIGURE                        |
#------------------------------------------
vpath %.c ./src
vpath %.h ./src

vpath %.c ./modelLevel
vpath %.h ./modelLevel

vpath %.c ./src/AVX2
vpath %.h ./src/AVX2

vpath %.c ./src/ARMv8
vpath %.h ./src/ARMv8
#------------------------------------------

#------------------------------------------
#| COMPILER FLAGS                         |
#------------------------------------------

ifeq ($(RUN_MODE), FAMILY)
  MODE=-DFAMILY
else ifeq ($(RUN_MODE), FAMILY_BLIS)
  MODE=-DFAMILY_BLIS
else ifeq ($(RUN_MODE), FAMILY_EXO)
  MODE=-DFAMILY_EXO
else ifeq ($(RUN_MODE), FAMILY_AUTOGEN)
  MODE=-DFAMILY_AUTOGEN
else ifeq ($(RUN_MODE), BLIS)
  MODE=-DBLIS
endif

#Dependes Arquitecture Mode
ifeq ($(SIMD_MODE), AVX2)
  SIMD  = -DAVX2
  FLAGS = -S -fopenmp -fomit-frame-pointer -O3 -mavx2 -mfma -mfpmath=sse -march=znver1 -mno-avx256-split-unaligned-store -Wall -Wno-unused-function -Wfatal-errors -fPIC -std=c99 -D_POSIX_C_SOURCE=200112L
  _OBJ += gemm_blis_amd_avx256_fp32.o
else ifeq ($(SIMD_MODE), ARMv8)
  SIMD  = -DARMv8
  FLAGS = -O3 -march=armv8-a+simd+fp -fopenmp -Wall -Wunused-function
  _OBJ += gemm_blis_neon_fp32.o 
else ifeq ($(SIMD_MODE), ARMv8_EXO)
  SIMD  = -DARMv8_EXO
  FLAGS = -O3 -march=armv8-a+simd+fp -Wall -Wunused-function
  _OBJ += uk.o 
else
  FLAGS = -O3 
endif

ifeq ($(RUN_MODE), FAMILY_BLIS)
  # FIX for all BLIS MR,NR Values!
  ifeq ($(SIMD_MODE), AVX2)
    MR=6
    NR=16
  else ifeq ($(SIMD_MODE), ARMv8)
    MR=8
    NR=12
  else ifeq ($(SIMD_MODE), ARMv8_EXO)
    MR=8
    NR=12
  else
  endif	
endif

OPTFLAGS = $(FLAGS) -DCHECK -DMR=$(MR) -DNR=$(NR) -DKR=1 $(MODE) $(SIMD) $(DTYPE)
#------------------------------------------




OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))
default: $(OBJDIR)/$(BIN)

$(OBJDIR)/%.o:%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c -o $@ $< $(INCLUDE) $(LIBS)

$(OBJDIR)/$(BIN): $(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o $@ $^ $(LIBS)

clean:
	rm $(OBJDIR)/* 

