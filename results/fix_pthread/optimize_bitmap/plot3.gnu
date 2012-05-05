set terminal png size 1000, 600 font "/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman.ttf" 14

set output "big2.png"
set boxwidth 0.75 absolute

set style fill solid 1.00 border -1

set style data histogram

set style histogram cluster gap 1 title  offset character 0, -0.5, 0


set grid y

set ylabel "Elapsed Time (s)"
set style data histograms
set title "The Result of Optimizations (RGL10, IRGL10, USA, SW10)" 

set key outside center bottom horizontal Left reverse




plot newhistogram "RGL10",  '1' using 2 t  "Baseline", '' using 6:xtic(1) t "With Channel",\
newhistogram "IRGL10", '2' using 2 t "Baseline", '' using 6:xtic(1) t "With Channel",\
 newhistogram "USA", '3' using 2 t "Baseline", '' using 6:xtic(1) t "With Channel",\
 newhistogram "SW10", '4' using 2 t "Baseline", '' using 6:xtic(1) t "With Channel"

