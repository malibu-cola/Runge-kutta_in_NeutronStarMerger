set term postscript
set output 'sample.eps'
set xrange [0.0:1.0]
set yrange [1:100]
set xlabel 'time[s]'
set ylabel 'R[km]'
set title 'initial R_0=2'
plot "./sample.txt" with line
set out