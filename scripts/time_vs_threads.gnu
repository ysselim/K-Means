set terminal png size 800,600
set output "time_vs_threads.png"

set title "Execution Time vs Threads"
set xlabel "Threads"
set ylabel "Time (seconds)"
set grid
set key left top

plot \
"results.dat" using ($1==10000 ? $3 : 1/0):4 with linespoints title "10K", \
"results.dat" using ($1==50000 ? $3 : 1/0):4 with linespoints title "50K", \
"results.dat" using ($1==100000 ? $3 : 1/0):4 with linespoints title "100K", \
"results.dat" using ($1==500000 ? $3 : 1/0):4 with linespoints title "500K", \
"results.dat" using ($1==1000000 ? $3 : 1/0):4 with linespoints title "1M"