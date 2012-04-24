

set terminal png nocrop enhanced font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 size 620,420 
set output 'conflict.png'

set datafile missing '-'
set style data linespoints
set title "CPU Lockless with Changing Thread Number"

set xrange [0:30]
set yrange [0:600]

set xlabel "Thread Number"
set ylabel "Elapsed Time (ms)"

set xtics auto 5 nomirror
set ytics auto 100 nomirror

set mxtics 5
set mytics 2


plot 'conflict.dat' using 1:2 t "RGL1", '' using 1:3 t "IRGL1", '' using 1:4 t "BAY", '' using 1:5 t "SW1" 


