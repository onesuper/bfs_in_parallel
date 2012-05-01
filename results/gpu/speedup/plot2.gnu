

set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 

set output "irregular.png"

set datafile missing '-'
set style data linespoints
set title "Speedup of the Exploration on Irregular Graph"


#set yrange [0:1]
set key outside right top vertical Left reverse 
set xlabel "Block Number"
set ylabel "Speedup"

#set xtics auto 5 nomirror
#set ytics auto 200 nomirror

#set mxtics 5
#set mytics 2

set grid


plot '2.dat' using 2 t "IRGL1", '' using 3 t "IRGL2", '' using 4 t "IRGL3", '' using 5 t "IRGL4", '' using 6 t "IRGL5", '' using 7 t "IRGL6", '' using 8 t "IRGL7", '' using 9 t "IRGL8", '' using 10 t "IRGL9", '' using 11:xtic(1) t "IRGL10"


