set terminal png size 800,600
set output "scaling.png"

set title "Execution Time vs Dataset Size"
set xlabel "Dataset Size"
set ylabel "Time (seconds)"
set grid
set key left top

plot \
"t1.dat" using 1:2 with linespoints title "1 Thread", \
"t2.dat" using 1:2 with linespoints title "2 Threads", \
"t4.dat" using 1:2 with linespoints title "4 Threads", \
"t8.dat" using 1:2 with linespoints title "8 Threads"