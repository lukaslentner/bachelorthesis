set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set encoding iso_8859_15

set xlabel "Temperatur [J]"

set key right bottom
set output "Energie-Temperatur.eps"
set title "Energie pro Spin - Temperatur"
set ylabel "Energie pro Spin [J]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:6 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:6 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:6 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:6 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:6 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf Energie-Temperatur.eps && rm Energie-Temperatur.eps

set key right top
set output "AutokorrelationszeitEnergie-Temperatur.eps"
set title "Autokorrelationszeit der Energie - Temperatur"
set ylabel "Autokorrelationszeit der Energie [MC-Schritte]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:8 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:8 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:8 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:8 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:8 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf AutokorrelationszeitEnergie-Temperatur.eps && rm AutokorrelationszeitEnergie-Temperatur.eps

set key right top
set output "SpezifischeWaerme-Temperatur.eps"
set title "Spezifische Wärme pro Spin - Temperatur"
set ylabel "Spezifische Wärme pro Spin [1]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:9 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:9 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:9 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:9 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:9 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf SpezifischeWaerme-Temperatur.eps && rm SpezifischeWaerme-Temperatur.eps

set key right top
set output "Magnetisierung-Temperatur.eps"
set title "Magnetisierung pro Spin - Temperatur"
set ylabel "Magnetisierung pro Spin [A/m^2]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:12 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:12 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:12 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:12 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:12 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf Magnetisierung-Temperatur.eps && rm Magnetisierung-Temperatur.eps

set key right top
set output "MagnetischeSuszeptibilitaet-Temperatur.eps"
set title "Magnetische Suszeptibilität pro Spin - Temperatur"
set ylabel "Magnetische Suszeptibilität pro Spin [A^2/m^4/J]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:15 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:15 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:15 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:15 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:15 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf MagnetischeSuszeptibilitaet-Temperatur.eps && rm MagnetischeSuszeptibilitaet-Temperatur.eps

set key right top
set output "AbsoluteMagnetisierung-Temperatur.eps"
set title "Absolute Magnetisierung pro Spin - Temperatur"
set ylabel "Absolute Magnetisierung pro Spin [A/m^2]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:18 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:18 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:18 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:18 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:18 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf AbsoluteMagnetisierung-Temperatur.eps && rm AbsoluteMagnetisierung-Temperatur.eps

set key right top
set output "AbsoluteMagnetischeSuszeptibilitaet-Temperatur.eps"
set title "Absolute, Magnetische Suszeptibilität pro Spin - Temperatur"
set ylabel "Absolute, Magnetische Suszeptibilität pro Spin [A^2/m^4/J]"
plot "../../../Code/Analysis/ISING/100-Periodic2D/Data" using 5:21 lt rgb "#FF0000" with lines title "10x10 Gitter", \
"../../../Code/Analysis/ISING/256-Periodic2D/Data" using 5:21 lt rgb "#00FF00" with lines title "16x16 Gitter", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:21 lt rgb "#0000FF" with lines title "24x24 Gitter", \
"../../../Code/Analysis/ISING/1296-Periodic2D/Data" using 5:21 lt rgb "#FF00FF" with lines title "36x36 Gitter", \
"../../../Code/Analysis/ISING/4096-Periodic2D/Data" using 5:21 lt rgb "#00FFFF" with lines title "64x64 Gitter"
!epstopdf AbsoluteMagnetischeSuszeptibilitaet-Temperatur.eps && rm AbsoluteMagnetischeSuszeptibilitaet-Temperatur.eps
