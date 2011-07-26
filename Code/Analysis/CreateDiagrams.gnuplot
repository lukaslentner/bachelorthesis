set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale

set xlabel "Temperature"

set key right bottom
set output "Energy-Temperature.eps"
set title "Energy - Temperature"
set ylabel "Energy"
plot "Data" using 5:($6+$7) lt rgb "#FFAAAA" with lines title "Energy + StdDev", \
"Data" using 5:($6-$7) lt rgb "#FFAAAA" with lines title "Energy - StdDev", \
"Data" using 5:6 lt rgb "#FF0000" with lines title "Energy"

set key off
set output "EnergyRelaxationTime-Temperature.eps"
set title "Energy Relaxation Time - Temperature"
set ylabel "Energy Relaxation Time"
plot "Data" using 5:8 lt rgb "#FF0000" with lines

set key right bottom
set output "SHeat-Temperature.eps"
set title "Specific Heat - Temperature"
set ylabel "Specific Heat"
plot "Data" using 5:($9+$10) lt rgb "#FFAAAA" with lines title "Specific Heat + StdDev", \
"Data" using 5:($9-$10) lt rgb "#FFAAAA" with lines title "Specific Heat - StdDev", \
"Data" using 5:9 lt rgb "#FF0000" with lines title "Specific Heat"

set key off
set output "SHeatRelaxationTime-Temperature.eps"
set title "Specific Heat Relaxation Time - Temperature"
set ylabel "Specific Heat Relaxation Time"
plot "Data" using 5:11 lt rgb "#FF0000" with lines

set key right bottom
set output "Magnetization-Temperature.eps"
set title "Magnetization - Temperature"
set ylabel "Magnetization"
plot "Data" using 5:($12+$13) lt rgb "#FFAAAA" with lines title "Magnetization + StdDev", \
"Data" using 5:($12-$13) lt rgb "#FFAAAA" with lines title "Magnetization - StdDev", \
"Data" using 5:12 lt rgb "#FF0000" with lines title "Magnetization"

set key off
set output "MagnetizationRelaxationTime-Temperature.eps"
set title "Magnetization Relaxation Time - Temperature"
set ylabel "Magnetization Relaxation Time"
plot "Data" using 5:14 lt rgb "#FF0000" with lines

set key right bottom
set output "Susceptibility-Temperature.eps"
set title "Susceptibility - Temperature"
set ylabel "Susceptibility"
plot "Data" using 5:($15+$16) lt rgb "#FFAAAA" with lines title "Susceptibility + StdDev", \
"Data" using 5:($15-$16) lt rgb "#FFAAAA" with lines title "Susceptibility - StdDev", \
"Data" using 5:15 lt rgb "#FF0000" with lines title "Susceptibility"

set key off
set output "SusceptibilityRelaxationTime-Temperature.eps"
set title "Susceptibility Relaxation Time - Temperature"
set ylabel "Susceptibility Relaxation Time"
plot "Data" using 5:17 lt rgb "#FF0000" with lines
