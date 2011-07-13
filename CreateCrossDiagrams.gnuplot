set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale

set xlabel "Temperature"

set output "Energy-Temperature.eps"
set title "Energy - Temperature"
set ylabel "Energy"
plot "Analysis/SSE/Open-1D/8/Data" using 4:5 with lines title "SSE", "Analysis/ED/Open-1D/8/Data" using 4:5 with lines title "ED"

set output "SpecHeat-Temperature.eps"
set title "Specific Heat - Temperature"
set ylabel "Specific Heat"
plot "Analysis/SSE/Open-1D/8/Data" using 4:7 with lines title "SSE", "Analysis/ED/Open-1D/8/Data" using 4:7 with lines title "ED"
