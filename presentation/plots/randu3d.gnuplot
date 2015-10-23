#set terminal wxt size 1024,768 enhanced font 'Verdana,10' persist

set term png transparent size 1024,768 enhanced truecolor font 'Verdana,16'

#Change colors of elements in Gnuplot

# change a color of border.
set border lw 5 lc rgb "white"

# change text colors of  tics
set xtics textcolor rgb "white"
set ytics textcolor rgb "white"
set ztics textcolor rgb "white"

# change text colors of labels
set xlabel "x" textcolor rgb "white"
set ylabel "y" textcolor rgb "white"
set zlabel "z" textcolor rgb "white"

set xrange [0:1]
set yrange [0:1]
set zrange [0:1]

set border 4095

# Line width of the axes
set border linewidth 1.5

do for [i=0:9] { 
   set output sprintf('animated/randu3d-%d.png', i)
   set view 60, 62 + i*10, 1, 1
   splot "randu/randu.dat" using 1:2:3 with points notitle pointtype 1 lc 'white'
}
