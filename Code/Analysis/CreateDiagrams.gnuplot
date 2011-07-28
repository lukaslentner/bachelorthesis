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
set output "EnergyAutoCorrelationTime-Temperature.eps"
set title "Energy AutoCorrelation Time - Temperature"
set ylabel "Energy AutoCorrelation Time"
plot "Data" using 5:8 lt rgb "#FF0000" with lines

set key right bottom
set output "SHeat-Temperature.eps"
set title "Specific Heat - Temperature"
set ylabel "Specific Heat"
plot "Data" using 5:($9+$10) lt rgb "#FFAAAA" with lines title "Specific Heat + StdDev", \
"Data" using 5:($9-$10) lt rgb "#FFAAAA" with lines title "Specific Heat - StdDev", \
"Data" using 5:9 lt rgb "#FF0000" with lines title "Specific Heat"

set key off
set output "SHeatAutoCorrelationTime-Temperature.eps"
set title "Specific Heat AutoCorrelation Time - Temperature"
set ylabel "Specific Heat AutoCorrelation Time"
plot "Data" using 5:11 lt rgb "#FF0000" with lines

set key right bottom
set output "Magnetisation-Temperature.eps"
set title "Magnetisation - Temperature"
set ylabel "Magnetisation"
plot "Data" using 5:($12+$13) lt rgb "#FFAAAA" with lines title "Magnetisation + StdDev", \
"Data" using 5:($12-$13) lt rgb "#FFAAAA" with lines title "Magnetisation - StdDev", \
"Data" using 5:12 lt rgb "#FF0000" with lines title "Magnetisation"

set key off
set output "MagnetisationAutoCorrelationTime-Temperature.eps"
set title "Magnetisation AutoCorrelation Time - Temperature"
set ylabel "Magnetisation AutoCorrelation Time"
plot "Data" using 5:14 lt rgb "#FF0000" with lines

set key right bottom
set output "Susceptibility-Temperature.eps"
set title "Susceptibility - Temperature"
set ylabel "Susceptibility"
plot "Data" using 5:($15+$16) lt rgb "#FFAAAA" with lines title "Susceptibility + StdDev", \
"Data" using 5:($15-$16) lt rgb "#FFAAAA" with lines title "Susceptibility - StdDev", \
"Data" using 5:15 lt rgb "#FF0000" with lines title "Susceptibility"

set key off
set output "SusceptibilityAutoCorrelationTime-Temperature.eps"
set title "Susceptibility AutoCorrelation Time - Temperature"
set ylabel "Susceptibility AutoCorrelation Time"
plot "Data" using 5:17 lt rgb "#FF0000" with lines

set key right bottom
set output "AbsoluteMagnetisation-Temperature.eps"
set title "Absolute Magnetisation - Temperature"
set ylabel "Absolute Magnetisation"
plot "Data" using 5:($18+$19) lt rgb "#FFAAAA" with lines title "Absolute Magnetisation + StdDev", \
"Data" using 5:($18-$19) lt rgb "#FFAAAA" with lines title "Absolute Magnetisation - StdDev", \
"Data" using 5:18 lt rgb "#FF0000" with lines title "Absolute Magnetisation"

set key off
set output "AbsoluteMagnetisationAutoCorrelationTime-Temperature.eps"
set title "Absolute Magnetisation AutoCorrelation Time - Temperature"
set ylabel "Absolute Magnetisation AutoCorrelation Time"
plot "Data" using 5:20 lt rgb "#FF0000" with lines

set key right bottom
set output "AbsoluteSusceptibility-Temperature.eps"
set title "Absolute Susceptibility - Temperature"
set ylabel "AbsoluteSusceptibility"
plot "Data" using 5:($21+$22) lt rgb "#FFAAAA" with lines title "Absolute Susceptibility + StdDev", \
"Data" using 5:($21-$22) lt rgb "#FFAAAA" with lines title "Absolute Susceptibility - StdDev", \
"Data" using 5:21 lt rgb "#FF0000" with lines title "Absolute Susceptibility"

set key off
set output "AbsoluteSusceptibilityAutoCorrelationTime-Temperature.eps"
set title "Absolute Susceptibility AutoCorrelation Time - Temperature"
set ylabel "Absolute Susceptibility AutoCorrelation Time"
plot "Data" using 5:23 lt rgb "#FF0000" with lines
