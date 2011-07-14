set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale

set xlabel "Temperature"

set key right bottom
set output "Energy-Temperature.eps"
set title "Energy - Temperature"
set ylabel "Energy"
plot "Data" using 4:($5+$6) lt rgb "#FFAAAA" with lines title "Energy + StdDev", \
"Data" using 4:($5-$6) lt rgb "#FFAAAA" with lines title "Energy - StdDev", \
"Data" using 4:5 lt rgb "#FF0000" with lines title "Energy"

set key off
set output "SpecHeat-Temperature.eps"
set title "Specific Heat - Temperature"
set ylabel "Specific Heat"
plot "Data" using 4:7 lt rgb "#FF0000" with lines
