set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set key off

set xlabel "Temperature"

set output "Energy-Temperature.eps"
set title "Energy - Temperature"
set ylabel "Energy"
plot "Data" using 4:5

set output "SpecHeat-Temperature.eps"
set title "Specific Heat - Temperature"
set ylabel "Specific Heat"
plot "Data" using 4:7
