#!/bin/bash

cnn_model_path=$1
cnn_model=$2
dtype="float32"
packA="Y"
packB="Y"
arch="avx2"
# cnn_model="resnet"
# cnn_model="vgg"
path=""

if [ "$packA" = "Y" ] && [ "$packB" = "Y" ]; then
    path=${cnn_model}
elif [ "$packA" = "Y" ] && [ "$packB" = "N" ]; then
    path="${cnn_model}_nopackB"
elif [ "$packA" = "N" ] && [ "$packB" = "Y" ]; then
    path="${cnn_model}_nopackA" 
elif [ "$packA" = "N" ] && [ "$packB" = "N" ]; then
    path="${cnn_model}_nopackAB"
fi
    
if [ "$arch" = "neon" ]; then
    uk1=( 4 4  4  4  4  4 8 8 8 12 12 16 20 24 )
    uk2=( 4 8 12 16 20 24 4 8 12 4  8  4  4  4 )
    total=${#uk1[*]}
elif [ "$arch" = "avx2" ]; then
    uk1=( 8  8  8  8  8  8 16 16 16 24 24 32 40 48 )
    uk2=( 8 16 24 32 40 48  8 16 24 8  16  8  8  8 )
    total=${#uk1[*]}
else
    uk1=( 4 4  4  4  4  4 8 8 8 12 12 16 20 24 )
    uk2=( 4 8 12 16 20 24 4 8 12 4  8  4  4  4 )
    total=${#uk1[*]}
fi


for (( i=0; i<$total; i++ )); do
    if [ "$dtype" = "float16" ]; then
        mr=$((uk1[i] * 2))
        nr=$((uk2[i] * 2))
    elif [ "$dtype" = "float64" ]; then
        mr=$((uk1[i] / 2))
        nr=$((uk2[i] / 2))
    else
        mr=${uk1[i]}
        nr=${uk2[i]}
    fi
    sed -i "/MR=/c\MR=$mr" Makefile.inc
    sed -i "/NR=/c\NR=$nr" Makefile.inc
    cd src; python3 microkernel_generator.py --mr $mr --nr $nr --packA $packA --packB $packB --dtype $dtype --arch $arch; cd ..
    make clean; make
     ./run_gemm.sh $cnn_model_path out/$dtype/$cnn_model/${path}_${mr}x${nr}.csv

done
