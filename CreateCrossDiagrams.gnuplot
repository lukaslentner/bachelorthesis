set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale

set xlabel "Temperature"

set output "Energy-Temperature.eps"
set title "Energy - Temperature"
set ylabel "Energy"
plot "../SSE/Open-1D/10/Data" using 4:5 with lines title "SSE", "../ED/Open-1D/10/Data" using 4:5 with lines title "ED"

set output "SpecHeat-Temperature.eps"
set title "Specific Heat - Temperature"
set ylabel "Specific Heat"
plot "../SSE/Open-1D/10/Data" using 4:7 with lines title "SSE", "../ED/Open-1D/10/Data" using 4:7 with lines title "ED"
