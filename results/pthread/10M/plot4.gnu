set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 

set output "smallworld.png"
set boxwidth 0.7 absolute
set style fill solid 1.00 border -1
set style data histogram
set style histogram cluster gap 3
set xtics 1 nomirror
set ytics 1 nomirror
set mxtics 2
set mytics 2
set ytics 200
set yrange [0:1200]
set ylabel "Elapsed Time (ms)"
set xlabel "Number of Threads"
set title "Exploration on Small-world Graph(1M, 6) on Multi-core Proccessors"


plot '4.indoor' using 2 t "Serial BFS", '' using 3 t "Rodinia", '' using 4 t "Baseline", '' using 5 t "With Bitmap", '' using 6 t "With Bitmap, Batch", '' using 7 t "With Bitmap, Batch, Read Check", '' using 8:xtic(1) t "With Bitmap, Batch, Read Check, Channel"


