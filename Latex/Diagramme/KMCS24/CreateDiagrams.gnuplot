set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set encoding iso_8859_15

set xlabel "Temperatur"

set key right top
set output "AutokorrelationszeitEnergie-Temperatur.eps"
set title "Autokorrelationszeit der Energie - Temperatur"
set ylabel "Autokorrelationszeit der Energie"
plot "../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($6+$7) lt rgb "#FFAAAA" with lines title "Energie + Standardabweichung"
!epstopdf AutokorrelationszeitEnergie-Temperatur.eps && rm AutokorrelationszeitEnergie-Temperatur.eps

set key right bottom
set output "Energie-Temperatur.eps"
set title "Energie - Temperatur Diagramm eines 24x24 Spin Gitters mit periodischen Randbedingungen"
set ylabel "Energie"
plot "../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($6+$7) lt rgb "#FFAAAA" with lines title "Energie + Standardabweichung", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($6-$7) lt rgb "#FFAAAA" with lines title "Energie - Standardabweichung", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:6 lt rgb "#FF0000" with lines title "Energie"
!epstopdf Energie-Temperatur.eps && rm Energie-Temperatur.eps

set key right top
set output "SpezifischeWaerme-Temperatur.eps"
set title "Spezifische Wärme - Temperatur"
set ylabel "Spezifische Wärme"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:9 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:9 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:9 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:9 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:9 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf SpezifischeWaerme-Temperatur.eps && rm SpezifischeWaerme-Temperatur.eps

set key right top
set output "Magnetisierung-Temperatur.eps"
set title "Magnetisierung pro Spin - Temperatur"
set ylabel "Magnetisierung pro Spin"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:12 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:12 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:12 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:12 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:12 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf Magnetisierung-Temperatur.eps && rm Magnetisierung-Temperatur.eps

set key right top
set output "Suszeptibilitaet-Temperatur.eps"
set title "Magnetische Suszeptibilität - Temperatur"
set ylabel "Magnetische Suszeptibilität"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:15 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:15 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:15 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:15 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:15 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf Suszeptibilitaet-Temperatur.eps && rm Suszeptibilitaet-Temperatur.eps









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
