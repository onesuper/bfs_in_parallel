set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman.ttf" 13

set output "regular.png"
set boxwidth 0.75 absolute
set style fill solid 1.00 border -1
set style data histogram
set style histogram cluster gap 3 

#set style data histograms
set xtics nomirror
set grid y

set ylabel "Elapsed Time (ms)"

set title "Cache-Coherence" 

set key outside center bottom horizontal Left reverse 




plot newhistogram "",  '2thread' using 2 t  "2 Threads in 2 Sockets", '' using 3:xtic(1) t "2 Threads in 1 Socket", newhistogram "", '2thread' using 4 t "4 Threads in 4 Sockets", '' using 5:xtic(1) t "4 Threads in 1 Sockets"

