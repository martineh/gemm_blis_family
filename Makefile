include Makefile.inc

#------------------------------------------
#| COMPILERS                              |
#------------------------------------------
CC       =  g++
CLINKER  =  g++
#------------------------------------------

OBJDIR = build
BIN    = test_gemm.x
_OBJ   = gemm_blis.o inutils.o sutils.o test_gemm.o model_level.o 

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
else ifeq ($(RUN_MODE), BLIS)
  MODE=-DBLIS
endif

#Dependes Arquitecture Mode
ifeq ($(SIMD_MODE), AVX2)
  SIMD  = -DAVX2
  FLAGS = -fopenmp -fomit-frame-pointer -O3 -mavx2 -mfma -mfpmath=sse -march=znver1 -mno-avx256-split-unaligned-store -Wall -Wno-unused-function -Wfatal-errors -fPIC -std=c99 -D_POSIX_C_SOURCE=200112L
else ifeq ($(SIMD_MODE), ARMv8)
  SIMD  = -DARMv8
  FLAGS = -O3 -march=armv8-a -fopenmp -Wall -Wunused-function -std=gnu++17
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
  else
  endif	
endif

OPTFLAGS = $(FLAGS) -DCHECK -DMR=$(MR) -DNR=$(NR) -DKR=1 $(MODE) $(SIMD) $(DTYPE)
#------------------------------------------

OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

SRC_ASM_FILES = $(wildcard ./src/asm_generator/ukernels/*.S)
OBJ_ASM_FILES = $(patsubst ./src/asm_generator/ukernels/%.S, $(OBJDIR)/%.o, $(SRC_ASM_FILES))
OBJ += $(OBJ_ASM_FILES)

OBJ += $(OBJDIR)/gemm_ukernel.o  $(OBJDIR)/selector_ukernel.o

default: $(OBJDIR)/$(BIN)

$(OBJDIR)/%.o:%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c -o $@ $< $(INCLUDE) $(LIBS)

$(OBJDIR)/%.o: ./src/asm_generator/ukernels/%.S
	gcc $(CFLAGS) $(OPTFLAGS) -c -o $@ $< $(INCLUDE) $(LIBS)

$(OBJDIR)/gemm_ukernel.o: ./src/asm_generator/ukernels/gemm_ukernel.c
	$(CC) $(CFLAGS) $(OPTFLAGS) -c -o $@ $< $(INCLUDE) $(LIBS)

$(OBJDIR)/selector_ukernel.o: ./src/asm_generator/ukernels/selector_ukernel.c
	$(CC) $(CFLAGS) $(OPTFLAGS) -c -o $@ $< $(INCLUDE) $(LIBS)


$(OBJDIR)/$(BIN): $(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o $@ $^ $(LIBS)

clean:
	rm $(OBJDIR)/* 

