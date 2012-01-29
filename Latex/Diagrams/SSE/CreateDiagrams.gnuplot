set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set encoding iso_8859_15
set size 0.7,0.7

set xlabel "Temperatur T [J]"

set key right bottom
set output "Chain_ErrorEnergy-Temperature.eps"
set ylabel "Fehler der Energie {/Symbol s}_E [J]"
plot "../../../Code/Analysis/SSE/24-Periodic1D/Data" using 5:($7*24) lt rgb "#FF0000" with lines title "24er Kette", \
"../../../Code/Analysis/SSE/36-Periodic1D/Data" using 5:($7*36) lt rgb "#00FF00" with lines title "36er Kette", \
"../../../Code/Analysis/SSE/64-Periodic1D/Data" using 5:($7*64) lt rgb "#0000FF" with lines title "64er Kette"
!epstopdf Chain_ErrorEnergy-Temperature.eps && rm Chain_ErrorEnergy-Temperature.eps

set key right bottom
set output "Chain_Energy-Temperature.eps"
set ylabel "Energie pro Spin E/N [J]"
plot "../../../Code/Analysis/SSE/24-Periodic1D/Data" using 5:6 lt rgb "#FF0000" with lines title "24er Kette", \
"../../../Code/Analysis/SSE/36-Periodic1D/Data" using 5:6 lt rgb "#00FF00" with lines title "36er Kette", \
"../../../Code/Analysis/SSE/64-Periodic1D/Data" using 5:6 lt rgb "#0000FF" with lines title "64er Kette"
!epstopdf Chain_Energy-Temperature.eps && rm Chain_Energy-Temperature.eps

set key right top
set output "Chain_SpecificHeat-Temperature.eps"
set ylabel "Wärmekapazität pro Spin C/N [1]"
plot "../../../Code/Analysis/SSE/24-Periodic1D/Data" using 5:9 lt rgb "#FF0000" with lines title "SSE 24er Kette", \
"../../../Code/Analysis/SSE/36-Periodic1D/Data" using 5:9 lt rgb "#00FF00" with lines title "SSE 36er Kette", \
"../../../Code/Analysis/SSE/64-Periodic1D/Data" using 5:9 lt rgb "#0000FF" with lines title "SSE 64er Kette"
!epstopdf Chain_SpecificHeat-Temperature.eps && rm Chain_SpecificHeat-Temperature.eps

set key right bottom
set output "Lattice_Energy-Temperature.eps"
set ylabel "Energie pro Spin E/N [J]"
plot "../../../Code/Analysis/SSE/16-Periodic2D/Data" using 5:6 lt rgb "#FF0000" with lines title "4x4 Gitter", \
"../../../Code/Analysis/SSE/36-Periodic2D/Data" using 5:6 lt rgb "#0000FF" with lines title "6x6 Gitter"
!epstopdf Lattice_Energy-Temperature.eps && rm Lattice_Energy-Temperature.eps

set key right top
set output "Lattice_SpecificHeat-Temperature.eps"
set ylabel "Wärmekapazität pro Spin C/N [1]"
plot "../../../Code/Analysis/SSE/24-Periodic1D/Data" using 5:9 lt rgb "#FF0000" with lines title "4x4 Gitter", \
"../../../Code/Analysis/SSE/36-Periodic1D/Data" using 5:9 lt rgb "#0000FF" with lines title "6x6 Gitter"
!epstopdf Lattice_SpecificHeat-Temperature.eps && rm Lattice_SpecificHeat-Temperature.eps

set key right bottom
set output "All_Energy-Temperature.eps"
set ylabel "Energie pro Spin E/N [J]"
plot "../../../Code/Analysis/SSE/4-Open1D/Data" using 5:6 lt rgb "#FF0000" with lines title "SSE 4er Kette offen", \
"../../../Code/Analysis/ED/4-Open1D/Data" using 5:6 lt rgb "#990000" with lines title "ED 4er Kette offen", \
"../../../Code/Analysis/SSE/4-Periodic1D/Data" using 5:6 lt rgb "#00FF00" with lines title "SSE 4er Kette periodisch", \
"../../../Code/Analysis/ED/4-Periodic1D/Data" using 5:6 lt rgb "#006600" with lines title "ED 4er Kette periodisch", \
"../../../Code/Analysis/SSE/4-Periodic2D/Data" using 5:6 lt rgb "#AAAAFF" with lines title "SSE 2x2 Gitter periodisch", \
"../../../Code/Analysis/ED/4-Periodic2D/Data" using 5:6 lt rgb "#0000FF" with lines title "ED 2x2 Gitter periodisch"
!epstopdf All_Energy-Temperature.eps && rm All_Energy-Temperature.eps

set key right top
set output "All_SpecificHeat-Temperature.eps"
set ylabel "Wärmekapazität pro Spin C/N [1]"
plot "../../../Code/Analysis/SSE/4-Open1D/Data" using 5:9 lt rgb "#FF0000" with lines title "SSE 4er Kette offen", \
"../../../Code/Analysis/ED/4-Open1D/Data" using 5:9 lt rgb "#990000" with lines title "ED 4er Kette offen", \
"../../../Code/Analysis/SSE/4-Periodic1D/Data" using 5:9 lt rgb "#00FF00" with lines title "SSE 4er Kette periodisch", \
"../../../Code/Analysis/ED/4-Periodic1D/Data" using 5:9 lt rgb "#006600" with lines title "ED 4er Kette periodisch", \
"../../../Code/Analysis/SSE/4-Periodic2D/Data" using 5:9 lt rgb "#AAAAFF" with lines title "SSE 2x2 Gitter periodisch", \
"../../../Code/Analysis/ED/4-Periodic2D/Data" using 5:9 lt rgb "#0000FF" with lines title "ED 2x2 Gitter periodisch"
!epstopdf All_SpecificHeat-Temperature.eps && rm All_SpecificHeat-Temperature.eps
