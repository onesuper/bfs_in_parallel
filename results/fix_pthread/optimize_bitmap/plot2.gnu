set terminal png size 1600, 600 font "/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman.ttf" 14

set output "small.png"
set boxwidth 0.75 absolute

set style fill solid 1.00 border -1

set style data histogram

set style histogram cluster gap 1 title  offset character 0, -0.5, 0


set grid y

set ylabel "Elapsed Time (s)"
set style data histograms
set title "The Result of Optimizations (RGL1, IRGL1, BAY, SW1)" 

set key outside center bottom horizontal Left reverse




plot newhistogram "RGL1",  '5' using 2 t  "Baseline", '' using 3 t "With Bitmap", '' using 4:xtic(1) t "With Bitmap, Batch", '' using 5 t "With Bitmap, Batch, Read Check",\
newhistogram "IRGL1", '6' using 2 t "Baseline", '' using 3 t "With Bitmap", '' using 4:xtic(1) t "With Bitmap, Batch", '' using 5 t "With Bitmap, Batch, Read Check", \
newhistogram "BAY", '7' using 2 t "Baseline", '' using 3 t "With Bitmap", '' using 4:xtic(1) t "With Bitmap, Batch", '' using 5 t "With Bitmap, Batch, Read Check", \
newhistogram "SW1", '8' using 2 t "Baseline", '' using 3 t "With Bitmap", '' using 4:xtic(1) t "With Bitmap, Batch",'' using 5 t "With Bitmap, Batch, Read Check"

