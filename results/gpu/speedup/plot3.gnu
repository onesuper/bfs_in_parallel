

set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 

set output "realworld.png"

set datafile missing '-'
set style data linespoints
set title "Speedup of the Exploration on Real-world Graph"


#set yrange [0:1]
set key outside right top vertical Left reverse 
set xlabel "Block Number"
set ylabel "Speedup"

#set xtics auto 5 nomirror
#set ytics auto 200 nomirror

#set mxtics 5
#set mytics 2

set grid


plot '3.dat' using 2 t "BAY", '' using 3 t "NY", '' using 4 t "COL", '' using 5 t "FLA", '' using 6 t "CAL", '' using 7 t "NE", '' using 8 t "NW", '' using 9 t "LKS", '' using 10 t "E", '' using 11 t "W", '' using 12 t "CTR", '' using 13:xtic(1) t "USA"
