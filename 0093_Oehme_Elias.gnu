set term pngcairo size 800,600

# Plot 1

set output "T_r.png"
set title 'Temperatur ueber Radius'
set xlabel 'Radius (mm)'
set ylabel 'Temperatur (°C)'
set xrange [0:20]
set key outside
plot 'T_t.dat' using 1:2 with lines linewidth 2 title '0 seconds', \
     'T_t.dat' using 1:3 with lines linewidth 2 title '10 seconds', \
     'T_t.dat' using 1:4 with lines linewidth 2 title '60 seconds', \
     'T_t.dat' using 1:5 with lines linewidth 2 title '600 seconds', \
     'T_t.dat' using 1:6 with lines linewidth 2 title '3600 seconds'

# Plot 2

reset
set output "T_t.png"
set title 'Temperatur ueber Zeit'
set xlabel 'Zeit (s)'
set ylabel 'Temperature (°C)'
set xrange [0:3600]
set key outside
plot 'T_r.dat' using 1:2 with lines linewidth 2 title '0 mm', \
     'T_r.dat' using 1:3 with lines linewidth 2 title '2 mm', \
     'T_r.dat' using 1:4 with lines linewidth 2 title '10 mm', \
     'T_r.dat' using 1:5 with lines linewidth 2 title '18 mm', \
     'T_r.dat' using 1:6 with lines linewidth 2 title '20 mm'

# Plot 3

reset
set output "T_M.png"
set title 'Mittlere Temperatur'
set xlabel 'Zeit (s)'
set ylabel 'Mittlere Temperatur (°C)'
plot 'T_M.dat' using 1:2 with lines linewidth 2 title 'mittlere Temperatur'

# Plot 4

reset
set output 'T_q1.png'
set title 'Waermestrom ueber den Ort'
set xlabel 'Ort in mm'
set ylabel 'Waermestrom in W/m²'
plot 'T_q1.dat' using 1:2 with lines linewidth 2 title '0 s', \
     'T_q1.dat' using 1:3 with lines linewidth 2 title '10 s', \
     'T_q1.dat' using 1:4 with lines linewidth 2 title '60 s', \
     'T_q1.dat' using 1:5 with lines linewidth 2 title '600 s', \
     'T_q1.dat' using 1:6 with lines linewidth 2 title '3600 s'

#PLot 5

set output 'T_q2.png'

set title 'Waermestrom ueber die Zeit'
set xlabel 'Zeit in s'
set ylabel 'Waermestrom in W/m²'
set xrange [0:3600]
set key outside

plot 'T_q2.dat' using 1:2 with lines linewidth 1.5 title 'r = 0 mm', \
     'T_q2.dat' using 1:3 with lines linewidth 1.5 title 'r = 2 mm', \
     'T_q2.dat' using 1:4 with lines linewidth 1.5 title 'r = 10 mm', \
     'T_q2.dat' using 1:5 with lines linewidth 1.5 title 'r = 18 mm', \
     'T_q2.dat' using 1:6 with lines linewidth 1.5 title 'r = 20 mm'

reset

#Plot 6

set output 'T_Q.png'

set title 'pro LE zugefuehrte Wärmemenge'
set xlabel 'Zeit in s'
set ylabel 'Waermestrom in MJ/m'
set yrange [0:60]
set xrange [0:3600]

plot 'T_Q.dat' using 1:2 with linespoints linewidth 2 pointtype 13 pointsize 1.5 title 'zugeführte Wärmemenge'
reset session



