set terminal png size 800,600
set output "speedup.png"

set title "Speedup vs Threads (1M Dataset)"
set xlabel "Threads"
set ylabel "Speedup"
set grid

T1 = 42.825589

plot \
"results.dat" using ($1==1000000 ? $3 : 1/0):(T1/$4) \
with linespoints title "Speedup"