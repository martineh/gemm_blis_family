#if defined(MK_BLIS)
    #include "blis/blis.h"
    void gemm_blis_B3A2C0( char, char, char, char, char, size_t, size_t, size_t, DTYPE, DTYPE *, size_t, DTYPE *, size_t, DTYPE, DTYPE *, size_t, 
			   DTYPE *, DTYPE *, size_t, size_t, size_t, cntx_t *, auxinfo_t *, sgemm_ukr_ft);

    void gemm_blis_A3B2C0( char, char, char, char, char, size_t, size_t, size_t, DTYPE, DTYPE *, int, DTYPE *, size_t, DTYPE, DTYPE *, size_t, 
			   DTYPE *, DTYPE *, size_t, size_t, size_t, cntx_t *, auxinfo_t *, sgemm_ukr_ft); 
#else

    void gemm_blis_B3A2C0( char, char, char, char, char, size_t, size_t, size_t, DTYPE, DTYPE *, size_t, DTYPE *, size_t, DTYPE, DTYPE *, size_t,
			   DTYPE *, DTYPE *, size_t, size_t, size_t);
    void gemm_blis_A3B2C0( char, char, char, char, char, size_t, size_t, size_t, DTYPE, DTYPE *, size_t, DTYPE *, size_t, DTYPE, DTYPE *, size_t,
			   DTYPE *, DTYPE *, size_t, size_t, size_t);
#endif

void gemm_blis_B3C2A0( char, char, char, char, char, size_t, size_t, size_t, DTYPE, DTYPE *, int, DTYPE *, int, DTYPE, DTYPE *, int, 
                       DTYPE *, DTYPE *, int, int, int);
void gemm_blis_C3B2A0( char, char, char, char, char, size_t, size_t, size_t, DTYPE, DTYPE *, int, DTYPE *, int, DTYPE, DTYPE *, int, 
                       DTYPE *, DTYPE *, int, int, int);
void gemm_blis_A3C2B0( char, char, char, char, char, int, int, int, DTYPE, DTYPE *, int, DTYPE *, int, DTYPE, DTYPE *, int, 
                       DTYPE *, DTYPE *, int, int, int);
void gemm_blis_C3A2B0( char, char, char, char, char, int, int, int, DTYPE, DTYPE *, int, DTYPE *, int, DTYPE, DTYPE *, int, 
                       DTYPE *, DTYPE *, int, int, int);
void gemm_base_Cresident( char, int, int, int, DTYPE, DTYPE *, int, DTYPE *, int, DTYPE, DTYPE *, int );
void gemm_base_ABresident( char, char, int, int, int, DTYPE, DTYPE *, int, DTYPE *, int, DTYPE, DTYPE *, int );

void pack_RB( char, char, int, int, DTYPE *, int, DTYPE *, int );
void pack_CB( char, char, int, int, DTYPE *, int, DTYPE *, int );
void unpack_RB( char, char, int, int, DTYPE *, int, DTYPE *, int );
void unpack_CB( char, char, int, int, DTYPE *, int, DTYPE *, int );

//-----------------------------------------------------------------------------------
void pack_RB_v( char, char, int, int, DTYPE *, int, DTYPE *, int );
void pack_CB_v( char, char, int, int, DTYPE *, int, DTYPE *, int );
//-----------------------------------------------------------------------------------

