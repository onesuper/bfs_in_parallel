set terminal png large font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 11 

set output "regular.png"
set boxwidth 0.8 absolute
set style fill solid 1.00 border -1
set style data histogram
set style histogram cluster gap 3
set xtics 1 nomirror rotate by -45
set ytics 2 nomirror
set mxtics 2
set mytics 2
set ytics 1000
set yrange [0:3500]
set ylabel "Elapsed Time (ms)"
set title "Exploration on Regular Graph on Many-core Proccessors"

#set key inside left top vertical Left reverse noenhanced autotitles columnhead nobox
set key inside left top vertical Left reverse


plot '1.dat' using 2 t "1 X 128 Threads", '' using 3 t "2 X 128 Threads",'' using 4 t "4 X 128 Threads", '' using 5 t "8 X 128 Threads", '' using 6 t "16 X 128 Threads", '' using 7 t "32 X 128 Threads", '' using 8 t "64 X 128 Threads",'' using 9 t "128 X 128 Threads",'' using 10 t "256 X 128 Threads",'' using 11 t "512 X 128 Threads", '' using 12:xtic(1) t "1024 X 128 Threads"


