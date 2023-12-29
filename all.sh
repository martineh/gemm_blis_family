
model="cnn_models/resnet50.blis.dat"

sed -i 's/^MR.*/MR='4'/' Makefile.inc

for mr in {4..24..4}
  do
  sed -i 's/^MR.*/MR='$mr'/' Makefile.inc
    for nr in {4..24..4}
      do
        sed -i 's/^NR.*/NR='$nr'/' Makefile.inc
	make clean; make
	./run_gemm.sh $model output/"eval_"$mr"x"$nr".csv"
  done
done

