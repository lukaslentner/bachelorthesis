set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set encoding iso_8859_15
set size 0.7,0.7

set xlabel "Temperatur T [J]"

set key right top
set output "AutocorrelationtimeEnergy-Temperature.eps"
set ylabel "Autokorrelationszeit der Energie {/Symbol t}_E [MC-Schritte]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:8 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:8 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:8 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:8 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:8 lt rgb "#00AAAA" with lines title "64x64 Gitter"
!epstopdf AutocorrelationtimeEnergy-Temperature.eps && rm AutocorrelationtimeEnergy-Temperature.eps

set key right bottom
set output "Energy-Temperature.eps"
set ylabel "Energie pro Spin E/N [J]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:6 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:6 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:6 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:6 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:6 lt rgb "#00AAAA" with lines title "64x64 Gitter"
!epstopdf Energy-Temperature.eps && rm Energy-Temperature.eps

set key right top
set output "SpecificHeat-Temperature.eps"
set ylabel "Wärmekapazität pro Spin C/N [1]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:9 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:9 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:9 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:9 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:9 lt rgb "#00AAAA" with lines title "64x64 Gitter"
!epstopdf SpecificHeat-Temperature.eps && rm SpecificHeat-Temperature.eps

set key right top
set output "Magnetization-Temperature.eps"
set ylabel "Magnetisierung pro Spin M/N [A/m^2]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:12 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:12 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:12 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:12 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:12 lt rgb "#00AAAA" with lines title "64x64 Gitter"
!epstopdf Magnetization-Temperature.eps && rm Magnetization-Temperature.eps

set key right top
set output "MagneticSusceptibility-Temperature.eps"
set ylabel "Magnetische Suszeptibilität pro Spin {/Symbol c}/N [A^2/m^4/J]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:15 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:15 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:15 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:15 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:15 lt rgb "#00AAAA" with lines title "64x64 Gitter"
!epstopdf MagneticSusceptibility-Temperature.eps && rm MagneticSusceptibility-Temperature.eps

set key right top
set output "AbsoluteMagnetization-Temperature.eps"
set ylabel "Absolute Magnetisierung pro Spin M'/N [A/m^2]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:18 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:18 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:18 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:18 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:18 lt rgb "#00AAAA" with lines title "64x64 Gitter"
!epstopdf AbsoluteMagnetization-Temperature.eps && rm AbsoluteMagnetization-Temperature.eps

set key right top
set output "MagneticSusceptibility-Temperature.eps"
set ylabel "Absolute, Magnetische Suszeptibilität pro Spin {/Symbol c}'/N [A^2/m^4/J]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:21 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:21 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:21 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:21 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:21 lt rgb "#00AAAA" with lines title "64x64 Gitter"
!epstopdf AbsoluteMagneticSusceptibility-Temperature.eps && rm AbsoluteMagneticSusceptibility-Temperature.eps
