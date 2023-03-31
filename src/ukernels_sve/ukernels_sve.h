#include <stdio.h>
#include <stdlib.h>
#include <arm_sve.h>
#include "../qblis.h"

#define  Acol(a1, a2)    A[ (a2) * (ldA)  + (a1) ]
#define  Bcol(a1, a2)    B[ (a2) * (ldB)  + (a1) ]
#define  Ccol(a1, a2)    C[ (a2) * (ldC)  + (a1) ]
#define Ctcol(a1, a2) Ctmp[ (a2) * (ldCt) + (a1) ]

#define  Arow(a1, a2)    A[ (a1) * (ldA)  + (a2) ]
#define  Brow(a1, a2)    B[ (a1) * (ldB)  + (a2) ]
#define  Crow(a1, a2)    C[ (a1) * (ldC)  + (a2) ]
#define Ctrow(a1, a2) Ctmp[ (a1) * (ldCt) + (a2) ]

#define Ctref(a1, a2) Ctmp[ (a2) * (ldCt) + (a1) ]
#define Atref(a1, a2) Atmp[ (a2) * (Atlda)+ (a1) ]

void ukernel_sve_32x10_fp32(char, int, int, int, float, float *, float *, float, float *, int);
void ukernel_sve_32x8_fp32 (char, int, int, int, float, float *, float *, float, float *, int);
