set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale
set encoding iso_8859_15

set xlabel "Temperatur T [J]"

set key right top
set output "AutokorrelationszeitEnergie-Temperatur.eps"
set ylabel "Autokorrelationszeit der Energie {/Symbol t}_E [MC-Schritt]"
plot "../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:8 lt rgb "#0000FF" with lines title "{/Symbol t}_E"
!epstopdf AutokorrelationszeitEnergie-Temperatur.eps && rm AutokorrelationszeitEnergie-Temperatur.eps

set key right bottom
set output "Energie-Temperatur.eps"
set ylabel "Energie pro Spin E/N [J]"
plot "../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($6+$7) lt rgb "#AAAAFF" with lines title "E/N + {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($6-$7) lt rgb "#AAAAFF" with lines title "E/N - {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:6 lt rgb "#0000FF" with lines title "E/N"
!epstopdf Energie-Temperatur.eps && rm Energie-Temperatur.eps

set key right top
set output "WaermeKapazitaet-Temperatur.eps"
set ylabel "Wärme Kapazität pro Spin C/N [1]"
plot "../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($9+$10) lt rgb "#AAAAFF" with lines title "C/N + {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($9-$10) lt rgb "#AAAAFF" with lines title "C/N - {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:9 lt rgb "#0000FF" with lines title "C/N"
!epstopdf WaermeKapazitaet-Temperatur.eps && rm WaermeKapazitaet-Temperatur.eps

set key right top
set output "Magnetisierung-Temperatur.eps"
set ylabel "Magnetisierung pro Spin M/N [A/m^2]"
plot "../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($12+$13) lt rgb "#AAAAFF" with lines title "M/N + {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($12-$13) lt rgb "#AAAAFF" with lines title "M/N + {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:12 lt rgb "#0000FF" with lines title "M/N"
!epstopdf Magnetisierung-Temperatur.eps && rm Magnetisierung-Temperatur.eps

set key right top
set output "Suszeptibilitaet-Temperatur.eps"
set ylabel "Magnetische Suszeptibilität {/Symbol c}/N [A^2/m^4/J]"
plot "../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($15+$16) lt rgb "#AAAAFF" with lines title "{/Symbol c}/N + {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($15-$16) lt rgb "#AAAAFF" with lines title "{/Symbol c}/N - {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:15 lt rgb "#0000FF" with lines title "{/Symbol c}/N"
!epstopdf Suszeptibilitaet-Temperatur.eps && rm Suszeptibilitaet-Temperatur.eps

set key right top
set output "AbsoluteMagnetisierung-Temperatur.eps"
set ylabel "Absolute Magnetisierung pro Spin M'/N [A/m^2]"
plot "../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($18+$19) lt rgb "#AAAAFF" with lines title "M'/N + {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($18-$19) lt rgb "#AAAAFF" with lines title "M'/N - {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:18 lt rgb "#0000FF" with lines title "M'/N"
!epstopdf AbsoluteMagnetisierung-Temperatur.eps && rm AbsoluteMagnetisierung-Temperatur.eps

set key right top
set output "AbsoluteSuszeptibilitaet-Temperatur.eps"
set ylabel "Absolute, Magnetische Suszeptibilität {/Symbol c}' [A^2/m^4/J]"
plot "../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($21+$22) lt rgb "#AAAAFF" with lines title "{/Symbol c}'/N + {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:($21-$22) lt rgb "#AAAAFF" with lines title "{/Symbol c}'/N - {/Symbol s}", \
"../../../Code/Analysis/ISING/576-Periodic2D/Data" using 5:21 lt rgb "#0000FF" with lines title "{/Symbol c}'/N"
!epstopdf AbsoluteSuszeptibilitaet-Temperatur.eps && rm AbsoluteSuszeptibilitaet-Temperatur.eps
