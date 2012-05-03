

set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 

set output "regular.png"

set datafile missing '-'
set style data linespoints
set title "Optimization of the Exploration on Regular Graph(RGL1) on Many-core Processors"


set yrange[0.95:1.35]
set key outside center bottom vertical Left reverse 
set xlabel "Block Number"
set ylabel "Speedup"




set grid

plot 'rgl1.out' using 2 t "Baseline", '' using 3 t "With Two Level Queue", ''  using 4:xtic(1) t "With Two Level Queue, Read Check"


