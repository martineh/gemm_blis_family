#!/bin/bash

#-------------------------------------------------------------
# Variants : example : B3A2C0(B3-->L3, A-->L2, C--> v-register)
# ORDER    : C = column major, R = row major
# TRANS    : T = transpose   , N = !T
#-------------------------------------------------------------
ORDERA=C  #R
ORDERB=C  #R
ORDERC=C  #R
TRANSA=N  #T
TRANSB=N  #T
#-------------------------------------------------------------


#-------------------------------------------------------------
# ALPHA - BETA Fixed Values
#-------------------------------------------------------------
ALPHA=1.0   
BETA=0.0   
#-------------------------------------------------------------


#-------------------------------------------------------------
# Execution Minimum Time
#-------------------------------------------------------------
TIMIN=2.0 
#-------------------------------------------------------------


#-------------------------------------------------------------
# Enable (T) | Disable (F) Testing Mode
#-------------------------------------------------------------
TEST=F
#-------------------------------------------------------------


#-------------------------------------------------------------
# Enable (0) | Disable (1) Visual Mode
#-------------------------------------------------------------
VISUAL=0
#-------------------------------------------------------------


if $(echo $1 | grep -q "batch"); then 
	source $1
else
	source batch/null.sh
fi

export OMP_PLACES="{0,1,2,3,4,5,6,7}"
export OMP_PROC_BIND=TRUE

export OMP_NUM_THREADS=8
export BLIS_JC_NT=1
export BLIS_IC_NT=1
export BLIS_JR_NT=8
export BLIS_IR_NT=1


taskset -c 0 ./build/test_gemm.x "" $ORDERA $ORDERB $ORDERC $TRANSA $TRANSB $ALPHA $BETA $MMIN $MMAX $MSTEP $NMIN $NMAX $NSTEP $KMIN $KMAX $KSTEP $VISUAL $TIMIN $TEST $1 $2

