#
# Torbert, 29 September 2017
#
set terminal png
set output "plot.png"
set key autotitle columnheader
set grid ytics lt 0
set xtics nomirror
plot "out.txt" u 1:2 w l , \
     "out.txt" u 1:3 w l , \
     "out.txt" u 1:4 w l
#
# end of file
#
