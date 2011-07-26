set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set key off

set xlabel "Temperature"

set output "RelaxationTime-Temperature.eps"
set title "Relaxation Time - Temperature"
set ylabel "Relaxation Time"
plot "Data" using 2:3

set output "RelaxationTime-Temperature-Line.eps"
set title "Relaxation Time - Temperature"
set ylabel "Relaxation Time"
plot "Data" using 2:3 with lines

set output "Energy-Temperature.eps"
set title "Energy - Temperature"
set ylabel "Energy"
plot "Data" using 2:4

set output "Energy-Temperature_Error.eps"
set title "Energy - Temperature with errorbars"
set ylabel "Energy"
plot "Data" using 2:4:5 with errorbars

set output "SHeat-Temperature.eps"
set title "Specific Heat - Temperature"
set ylabel "Specific Heat"
plot "" using 2:6

set output "Magnetization-Temperature.eps"
set title "Magnetization - Temperature"
set ylabel "Magnetization"
plot "" using 2:7

set output "Magnetization-Temperature_Error_Error.eps"
set title "Magnetization - Temperature with errorbars"
set ylabel "Magnetization"
plot "" using 2:7:8 with errorbars

set output "Susceptibility-Temperature.eps"
set title "Susceptibility - Temperature"
set ylabel "Susceptibility"
plot "" using 2:9
