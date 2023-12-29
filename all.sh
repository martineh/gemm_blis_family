
model="cnn_models/resnet50.blis.dat"
#model="cnn_models/googlenet.blis.dat"

for micro in 4x4 4x8 4x12 4x16 4x20 8x4 8x8 8x12 12x4 12x8 16x4 20x4
do
  echo $micro
  mr=$(echo $micro | cut -f1 -d"x")
  nr=$(echo $micro | cut -f2 -d"x")
  sed -i 's/^MR.*/MR='$mr'/' Makefile.inc
  sed -i 's/^NR.*/NR='$nr'/' Makefile.inc
  make clean; make
  ./run_gemm.sh $model output/"eval_"$mr"x"$nr".csv"
done

#for mr in {4..24..4}
#  do
#  sed -i 's/^MR.*/MR='$mr'/' Makefile.inc
#    for nr in {4..24..4}
#      do
#        sed -i 's/^NR.*/NR='$nr'/' Makefile.inc
#	make clean; make
#	./run_gemm.sh $model output/"eval_"$mr"x"$nr".csv"
#  done
#done

