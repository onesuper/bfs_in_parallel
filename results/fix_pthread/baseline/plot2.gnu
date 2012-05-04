set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 

set output "irregular.png"
set boxwidth 0.7 absolute
set style fill solid 1.00 border -1
set style data histogram
set style histogram cluster gap 3
#set xtics 1 nomirror
#set ytics 1 nomirror
#set mxtics 2
#set mytics 2
#set ytics 1000
#set yrange [0:4500]
set grid
set ylabel "Elapsed Time (ms)"
set xlabel "Thread Number"
set title "Exploration on Iregular Graph(IRGL1) on Multi-core Proccessors"

plot 'irgl1' using 2 t "Serial BFS", '' using 3 t "Rodinia BFS", '' using 4:xtic(1) t "My Parallel BFS"


