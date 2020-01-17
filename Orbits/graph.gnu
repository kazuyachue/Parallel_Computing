set terminal png
#
set output "orbit.png"
set size square
plot "earth.txt" with circles, "orbit.txt" u 3:4 w l notitle, "orbit.txt" u 5:6 w l notitle
#
set output "speed.png"
set size nosquare
plot "orbit.txt" u 2:7 w l title "vx","orbit.txt" u 2:8 w l title "vy","orbit.txt" u 2:9 w l title "vmag",0 w l ls 0 notitle
#
set output "distance.png"
set size nosquare
plot "orbit.txt" u 2:10 w l title "r", 6.371e+6 w l ls 0 title "R"
