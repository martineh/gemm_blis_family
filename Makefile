include Makefile.inc

#------------------------------------------
#| COMPILERS                              |
#------------------------------------------
CC       =  gcc
CLINKER  =  gcc
#------------------------------------------

#------------------------------------------
#| PATHS CONFIGURE                        |
#------------------------------------------
vpath %.c ./src
vpath %.h ./src

vpath %.c ./modelLevel
vpath %.h ./modelLevel

vpath %.c ./src/AMD
vpath %.h ./src/AMD
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
  SIMD = -DAVX2
  FLAGS = -fopenmp -fomit-frame-pointer -O3 -mavx2 -mfma -mfpmath=sse -march=znver1 -mno-avx256-split-unaligned-store -Wall -Wno-unused-function -Wfatal-errors -fPIC -std=c99 -D_POSIX_C_SOURCE=200112L
else
  FLAGS = -O3 
endif

ifeq ($(RUN_MODE), FAMILY_BLIS)
  # FIX for all BLIS MR,NR Values!
  ifeq ($(SIMD_MODE), AVX2)
    MR=6
    NR=16
  else
  endif	
endif

OPTFLAGS = $(FLAGS) -DCHECK -DMR=$(MR) -DNR=$(NR) -DKR=1 $(MODE) $(SIMD) $(DTYPE)
#------------------------------------------


OBJDIR = build
BIN    = test_gemm.x
_OBJ   = gemm_blis.o inutils.o sutils.o test_gemm.o model_level.o gemm_blis_amd_avx256_fp32.o  


OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))
default: $(OBJDIR)/$(BIN)

$(OBJDIR)/%.o:%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c -o $@ $< $(INCLUDE) $(LIBS)

$(OBJDIR)/$(BIN): $(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o $@ $^ $(LIBS)

clean:
	rm $(OBJDIR)/* 
