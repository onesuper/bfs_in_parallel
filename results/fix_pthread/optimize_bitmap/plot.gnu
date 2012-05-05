set terminal png size 1600, 600 font "/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman.ttf" 14

set output "big.png"
set boxwidth 0.75 absolute

set style fill solid 1.00 border -1

set style data histogram

set style histogram cluster gap 1 title  offset character 0, -0.5, 0


set grid y

set ylabel "Elapsed Time (s)"
set style data histograms
set title "The Result of Optimizations (RGL10, IRGL10, USA, SW10)" 

set key outside center bottom horizontal Left reverse




plot newhistogram "RGL10",  '1' using 2 t  "Baseline", '' using 3:xtic(1) t "With Bitmap",'' using 4 t "With Bitmap, Batch",'' using 5 t "With Bitmap, Batch, Read Check",\
newhistogram "IRGL10", '2' using 2 t "Baseline", '' using 3:xtic(1) t "With Bitmap",'' using 4 t "With Bitmap, Batch", '' using 5 t "With Bitmap, Batch, Read Check",\
 newhistogram "USA", '3' using 2 t "Baseline", '' using 3:xtic(1) t "With Bitmap",'' using 4 t "With Bitmap, Batch", '' using 5 t "With Bitmap, Batch, Read Check", \
 newhistogram "SW10", '4' using 2 t "Baseline", '' using 3:xtic(1) t "With Bitmap", '' using 4 t "With Bitmap, Batch", '' using 5 t "With Bitmap, Batch, Read Check"

