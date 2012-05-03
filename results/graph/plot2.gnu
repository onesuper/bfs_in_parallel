

set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 

set output "small-world.png"

set datafile missing '-'
set style data linespoints
set title "Graph Features(Small-world graph)"


#set yrange [0:4]

set key outside right top vertical Left reverse 
set xlabel "Exploration Level"
set ylabel "Frontier Size"

#set xtics auto 5 nomirror
#set ytics auto 200 nomirror

#set mxtics 5
#set mytics 2

#set grid


plot 'SW1.log' using 1 t "SW1"
