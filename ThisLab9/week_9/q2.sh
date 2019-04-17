for i in $(seq 0.5 0.25 2.5);
do
  ns q2.tcl "$i"
  echo "$i"
  awk -f "test.awk" "out_$i.tr"
done
