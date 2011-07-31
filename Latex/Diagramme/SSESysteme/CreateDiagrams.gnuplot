set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set encoding iso_8859_15
set size 0.7,0.7

set xlabel "Temperatur T [J]"

set key right bottom
set output "Energie-Temperatur.eps"
set ylabel "Energie pro Spin E/N [J]"
plot "../../../Code/Analysis/SSE/4-Open1D/Data" using 5:6 lt rgb "#FF0000" with lines title "SSE 4er Kette offen", \
"../../../Code/Analysis/ED/4-Open1D/Data" using 5:6 lt rgb "#660000" with lines title "ED 4er Kette offen", \
"../../../Code/Analysis/SSE/4-Periodic1D/Data" using 5:6 lt rgb "#00FF00" with lines title "SSE 4er Kette periodisch", \
"../../../Code/Analysis/ED/4-Periodic1D/Data" using 5:6 lt rgb "#003300" with lines title "ED 4er Kette periodisch", \
"../../../Code/Analysis/SSE/4-Periodic2D/Data" using 5:6 lt rgb "#AAAAFF" with lines title "SSE 2x2 Gitter periodisch", \
"../../../Code/Analysis/ED/4-Periodic2D/Data" using 5:6 lt rgb "#000099" with lines title "ED 2x2 Gitter periodisch"
!epstopdf Energie-Temperatur.eps && rm Energie-Temperatur.eps

set key right top
set output "Waermekapazitaet-Temperatur.eps"
set ylabel "Wärmekapazität pro Spin C/N [1]"
plot "../../../Code/Analysis/SSE/4-Open1D/Data" using 5:9 lt rgb "#FF0000" with lines title "SSE 4er Kette offen", \
"../../../Code/Analysis/ED/4-Open1D/Data" using 5:9 lt rgb "#660000" with lines title "ED 4er Kette offen", \
"../../../Code/Analysis/SSE/4-Periodic1D/Data" using 5:9 lt rgb "#00FF00" with lines title "SSE 4er Kette periodisch", \
"../../../Code/Analysis/ED/4-Periodic1D/Data" using 5:9 lt rgb "#003300" with lines title "ED 4er Kette periodisch", \
"../../../Code/Analysis/SSE/4-Periodic2D/Data" using 5:9 lt rgb "#AAAAFF" with lines title "SSE 2x2 Gitter periodisch", \
"../../../Code/Analysis/ED/4-Periodic2D/Data" using 5:9 lt rgb "#000099" with lines title "ED 2x2 Gitter periodisch"
!epstopdf Waermekapazitaet-Temperatur.eps && rm Waermekapazitaet-Temperatur.eps
