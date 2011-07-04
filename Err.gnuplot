set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set key off

set xlabel "Sweep"

set output "Err-Sweep.eps"
set title "ERR - Sweep"
set ylabel "ERR"
plot "Err" using 1:2, "Err" using 1:3
