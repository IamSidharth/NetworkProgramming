rm -f "*.dat"
for i in $(seq 40 10 160);
do
  ns q2.tcl "$i"
  awk -v rate="$i" -f "q2.awk" "out_$i.tr"
done
