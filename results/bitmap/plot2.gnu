

set terminal png nocrop enhanced font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 size 620,420 
set output 'bitmap_2.png'

set datafile missing '-'
set style data linespoints
set title "CPU Optimized by bitmap with Changing Thread Number"

set xrange [0:10]
set yrange [0:10000]

set xlabel "Thread Number"
set ylabel "Elapsed Time (ms)"

set xtics auto 1 nomirror
set ytics auto 2000 nomirror

set mxtics 1
set mytics 2


plot 'bitmap_2.dat' using 1:2 t "RGL10", '' using 1:3 t "IRGL10", '' using 1:4 t "USA", '' using 1:5 t "SW10" 


