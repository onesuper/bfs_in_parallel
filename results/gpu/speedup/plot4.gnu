

set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 

set output "smallworld.png"

set datafile missing '-'
set style data linespoints
set title "Speedup of the Exploration on Small-world Graph"


#set yrange [0:1]
set key outside right top vertical Left reverse 
set xlabel "Block Number"
set ylabel "Speedup"

#set xtics auto 5 nomirror
#set ytics auto 200 nomirror

#set mxtics 5
#set mytics 2

set grid


plot '4.dat' using 2 t "SW1", '' using 3 t "SW2", '' using 4 t "SW3", '' using 5 t "SW4", '' using 6 t "SW5", '' using 7 t "SW6", '' using 8 t "SW7", '' using 9 t "SW8", '' using 10 t "SW9", '' using 11:xtic(1) t "SW10"


