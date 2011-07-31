set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set encoding iso_8859_15
set size 0.7,0.7

set xlabel "Temperatur T [J]"

set key right bottom
set output "FehlerEnergie-Temperatur.eps"
set ylabel "Fehler der Energie {/Symbol s}_E [J]"
plot "../../../Code/Analysis/SSE/24-Periodic1D/Data" using 5:($7*24) lt rgb "#FF0000" with lines title "SSE 24er Kette", \
"../../../Code/Analysis/SSE/36-Periodic1D/Data" using 5:($7*36) lt rgb "#00FF00" with lines title "SSE 36er Kette", \
"../../../Code/Analysis/SSE/64-Periodic1D/Data" using 5:($7*64) lt rgb "#AAAAFF" with lines title "SSE 64er Kette"
!epstopdf FehlerEnergie-Temperatur.eps && rm FehlerEnergie-Temperatur.eps

set key right bottom
set output "Energie-Temperatur.eps"
set ylabel "Energie pro Spin E/N [J]"
plot "../../../Code/Analysis/SSE/24-Periodic1D/Data" using 5:6 lt rgb "#FF0000" with lines title "SSE 24er Kette", \
"../../../Code/Analysis/SSE/36-Periodic1D/Data" using 5:6 lt rgb "#00FF00" with lines title "SSE 36er Kette", \
"../../../Code/Analysis/SSE/64-Periodic1D/Data" using 5:6 lt rgb "#AAAAFF" with lines title "SSE 64er Kette"
!epstopdf Energie-Temperatur.eps && rm Energie-Temperatur.eps

set key right top
set output "Waermekapazitaet-Temperatur.eps"
set ylabel "Wärmekapazität pro Spin C/N [1]"
plot "../../../Code/Analysis/SSE/24-Periodic1D/Data" using 5:9 lt rgb "#FF0000" with lines title "SSE 24er Kette", \
"../../../Code/Analysis/SSE/36-Periodic1D/Data" using 5:9 lt rgb "#00FF00" with lines title "SSE 36er Kette", \
"../../../Code/Analysis/SSE/64-Periodic1D/Data" using 5:9 lt rgb "#AAAAFF" with lines title "SSE 64er Kette"
!epstopdf Waermekapazitaet-Temperatur.eps && rm Waermekapazitaet-Temperatur.eps
