set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set key off

set xlabel "Temperature"

set output "RelaxationTime-Temperature.eps"
set title "Relaxation Time - Temperature"
set ylabel "Relaxation Time"
plot "Data" using 3:4

set output "RelaxationTime-Temperature-Line.eps"
set title "Relaxation Time - Temperature"
set ylabel "Relaxation Time"
plot "Data" using 3:4 with lines

set output "Energy-Temperature.eps"
set title "Energy - Temperature"
set ylabel "Energy"
plot "Data" using 3:5
