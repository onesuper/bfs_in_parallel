

set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 

set output "smallworld-speedup.png"

set datafile missing '-'
set style data linespoints
set title "Results of Optimizations on Small-world Graph(SW10) on Many-core Processors"


set yrange[0.8:2.4]
set key outside center bottom vertical Left reverse 
set xlabel "Thread Number"
set ylabel "Speedup"




set grid

plot '4.1' using 2 t "Baseline", '' using 3 t "With Bitmap", ''  using 4:xtic(1) t "With Bitmap, Batch", '' using 5 t "With Bitmap, Batch, Readcheck"


