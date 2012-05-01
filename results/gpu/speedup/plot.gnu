

set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 

set output "regular.png"

set datafile missing '-'
set style data linespoints
set title "Speedup of the Exploration on Regular Graph"


#set yrange [0:4]
set key outside right top vertical Left reverse 
set xlabel "Block Number"
set ylabel "Speedup"

#set xtics auto 5 nomirror
#set ytics auto 200 nomirror

#set mxtics 5
#set mytics 2

set grid


plot '1.dat' using 2 t "RGL1", '' using 3 t "RGL2", '' using 4 t "RGL3", '' using 5 t "RGL4", '' using 6 t "RGL5", '' using 7 t "RGL6", '' using 8 t "RGL7", '' using 9 t "RGL8", '' using 10 t "RGL9", '' using 11:xtic(1) t "RGL10"


