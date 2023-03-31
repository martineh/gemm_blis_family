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

vpath %.c ./src/modelLevel
vpath %.h ./src/modelLevel

vpath %.c ./src/AMD
vpath %.h ./src/AMD
#------------------------------------------


#------------------------------------------
#| COMPILER FLAGS                         |
#------------------------------------------
CHECK_PARAMS = -DCHECK
#Dependes Arquitecture Mode
ifeq ($(MODE), AVX2)
	FLAGS = -fopenmp -fomit-frame-pointer -O3 -mavx2 -mfma -mfpmath=sse -march=znver1 -mno-avx256-split-unaligned-store -Wall -Wno-unused-function -Wfatal-errors -fPIC -std=c99 -D_POSIX_C_SOURCE=200112L
else
	FLAGS = -O3 
endif
OPTFLAGS = $(FLAGS) -DMR=$(MR) -DNR=$(NR) -DKR=$(KR)
#------------------------------------------


OBJDIR = build
BIN    = test_gemm.x
_OBJ   = gemm_blis.o inutils.o sutils.o test_gemm.o model_level.o gemm_blis_amd_avx256_fp32.o  


OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))
default: $(OBJDIR)/$(BIN)

$(OBJDIR)/%.o:%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(OPTFLAGS) $(CHECK_PARAMS) $(DTYPE) -c -o $@ $< $(INCLUDE) $(LIBS)

$(OBJDIR)/$(BIN): $(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o $@ $^ $(LIBS)

clean:
	rm $(OBJDIR)/* 

