set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale

set xlabel "Temperature"

set key right bottom
set output "Energy-Temperature.eps"
set title "Energy - Temperature"
set ylabel "Energy"
plot "../../SSE/DATAFOLDER/Data" using 4:5 lt rgb "#FF0000" with lines title "SSE", \
"../../SSE/DATAFOLDER/Data" using 4:($5+$6) lt rgb "#FFAAAA" with lines title "SSE + StdDev", \
"../../SSE/DATAFOLDER/Data" using 4:($5-$6) lt rgb "#FFAAAA" with lines title "SSE - StdDev", \
"../../ED/DATAFOLDER/Data" using 4:5 lt rgb "#000000" with lines title "ED"

set key right top
set output "SpecHeat-Temperature.eps"
set title "Specific Heat - Temperature"
set ylabel "Specific Heat"
plot "../../SSE/DATAFOLDER/Data" using 4:8 lt rgb "#FF0000" with lines title "SSE", \
"../../SSE/DATAFOLDER/Data" using 4:($8+$9) lt rgb "#FFAAAA" with lines title "SSE + StdDev", \
"../../SSE/DATAFOLDER/Data" using 4:($8-$9) lt rgb "#FFAAAA" with lines title "SSE - StdDev", \
"../../ED/DATAFOLDER/Data" using 4:8 lt rgb "#000000" with lines title "ED"

set key right top
set output "Suscept-Temperature.eps"
set title "Susceptibility - Temperature"
set ylabel "Susceptibility"
plot "../../SSE/DATAFOLDER/Data" using 4:11 lt rgb "#FF0000" with lines title "SSE", \
"../../SSE/DATAFOLDER/Data" using 4:($11+$12) lt rgb "#FFAAAA" with lines title "SSE + StdDev", \
"../../SSE/DATAFOLDER/Data" using 4:($11-$12) lt rgb "#FFAAAA" with lines title "SSE - StdDev", \
"../../ED/DATAFOLDER/Data" using 4:11 lt rgb "#000000" with lines title "ED"
