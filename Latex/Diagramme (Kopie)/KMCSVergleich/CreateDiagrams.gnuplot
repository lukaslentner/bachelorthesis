set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set encoding iso_8859_15

set xlabel "Temperatur"

set key right bottom
set output "Energie-Temperatur.eps"
set title "Energie pro Spin - Temperatur"
set ylabel "Energie pro Spin"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:($6/100) lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:($6/256) lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($6/576) lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:($6/1296) lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:($6/4096) lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf Energie-Temperatur.eps && rm Energie-Temperatur.eps

set key right top
set output "AutokorrelationszeitEnergie-Temperatur.eps"
set title "Autokorrelationszeit der Energie - Temperatur"
set ylabel "Autokorrelationszeit der Energie"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:8 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:8 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:8 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:8 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:8 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf AutokorrelationszeitEnergie-Temperatur.eps && rm AutokorrelationszeitEnergie-Temperatur.eps

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
