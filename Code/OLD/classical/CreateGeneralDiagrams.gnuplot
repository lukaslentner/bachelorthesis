set terminal postscript eps enhanced color solid rounded
set datafile separator "|"
set autoscale

set xlabel "Temperature"


# Aufgabe 3:
set output "03_01_Energy-Temperature.eps"
set title "Energy - Temperature"
set ylabel "Energy"
set key right bottom
set nolog
plot "../10/Data" using 2:4 with lines title "Modul=10", \
     "../16/Data" using 2:4 with lines title "Modul=16", \
     "../24/Data" using 2:4 with lines title "Modul=24", \
     "../36/Data" using 2:4 with lines title "Modul=36"

set output "03_02_Energy_Size-Temperature.eps"
set title "Energy/Size - Temperature"
set ylabel "Energy/Size"
set key right bottom
set nolog
plot "../10/Data" using 2:($4/10**2) with lines title "Modul=10", \
     "../16/Data" using 2:($4/16**2) with lines title "Modul=16", \
     "../24/Data" using 2:($4/24**2) with lines title "Modul=24", \
     "../36/Data" using 2:($4/36**2) with lines title "Modul=36"


# Aufgabe 4:
set output "04_01_Susceptibility-Temperature.eps"
set title "Susceptibility - Temperature"
set ylabel "Susceptibility"
set key right top
set nolog
plot "../10/Data" using 2:9 with lines title "Modul=10", \
     "../16/Data" using 2:9 with lines title "Modul=16", \
     "../24/Data" using 2:9 with lines title "Modul=24", \
     "../36/Data" using 2:9 with lines title "Modul=36"

set output "04_02_TemperatureMaxSusceptibility-ModulInverse.eps"
set title "Temperature of Max Susceptibility - Modul Inverse"
set xlabel "Modul Inverse"
set ylabel "Temperature of Max Susceptibility"
set key right top
set nolog
# Equation: 7.88
# (ny=1)
# m=x0*Tc
# t=Tc
fit m*x+t "Data_MaxSusceptibility" using ($1**-1):2 via m,t
plot "Data_MaxSusceptibility" using ($1**-1):2 title "Measurements", m*x+t title "Linear Fit"


# Aufgabe 5:
set output "05_01_MaxSusceptibility-Modul.eps"
set title "Max Susceptibility - Modul"
set xlabel "Modul"
set ylabel "Max Susceptibility"
set key right top
set log
# Equation: 7.90
# (gamma=roh)
# r=gamma/ny
# a=f(0)*prop
fit a*x**r "Data_MaxSusceptibility" using 1:3 via a,r
plot "Data_MaxSusceptibility" using 1:3 title "Measurements", a*x**r title "Power Fit"

set output "05_02_L()*Susceptibility-L*().eps"
set title "L**(-gamma/etha)*Susceptibility - L*(T-Tc(L))"
set xlabel "L*(T-Tc(L))"
set ylabel "L**(-gamma/etha)*Susceptibility"
set key right top
set nolog
# Wert muss eingetragen werden: Tc pro Modul
plot "../10/Data" using (10*($2-2.49 )):(10**-r*$9) with lines title "Modul=10", \
     "../16/Data" using (16*($2-2.415 )):(16**-r*$9) with lines title "Modul=16", \
     "../24/Data" using (24*($2-2.355 )):(24**-r*$9) with lines title "Modul=24", \
     "../36/Data" using (36*($2-2.325)):(36**-r*$9) with lines title "Modul=36"


# Aufgabe 6:
set output "06_01_Magnetization-Temperature.eps"
set title "Magnetization - Temperature."
set xlabel "Temperature"
set ylabel "Magnetization"
set key right top
set nolog
plot "../10/Data" using 2:7 with lines title "Modul=10", \
     "../16/Data" using 2:7 with lines title "Modul=16", \
     "../24/Data" using 2:7 with lines title "Modul=24", \
     "../36/Data" using 2:7 with lines title "Modul=36"

set output "06_02_L.M-Temperature.eps"
set title "L**(beta/ny)*Magnetization - Temperature."
set xlabel "Temperature"
set ylabel "L**(beta/ny)*Magnetization"
set key right top
set nolog
# Equation: 7.90
# (beta=roh)
# q=beta/ny
# Wert muss eingetragen werden: beta/ny sodass sich die Graphen treffen
q=0.125
plot "../10/Data" using 2:($7*$1**q) with lines title "Modul=10", \
     "../16/Data" using 2:($7*$1**q) with lines title "Modul=16", \
     "../24/Data" using 2:($7*$1**q) with lines title "Modul=24", \
     "../36/Data" using 2:($7*$1**q) with lines title "Modul=36"


# Aufgabe 7:
set output "07_01_SHeat-Temperature.eps"
set title "Specific Heat - Temperature."
set xlabel "Temperature"
set ylabel "Specific Heat"
set key right top
set nolog
plot "../10/Data" using 2:6 with lines title "Modul=10", \
     "../16/Data" using 2:6 with lines title "Modul=16", \
     "../24/Data" using 2:6 with lines title "Modul=24", \
     "../36/Data" using 2:6 with lines title "Modul=36"
