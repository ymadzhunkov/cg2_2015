set terminal wxt size 1024,768 enhanced font 'Verdana,10' persist

#set term png transparent size 1024,768 enhanced truecolor font 'Verdana,16'

#Change colors of elements in Gnuplot

# change a color of border.
set border lw 5

# change text colors of  tics
#set xtics textcolor rgb "white"
#set ytics textcolor rgb "white"

# change text colors of labels
#set xlabel "x" textcolor rgb "white"
#set ylabel "9x-6y+z" textcolor rgb "white"

#change the display format axis tick labels
#set format x "10^{%L}"
#set format y "10^{%L}"

# change a text color of key
set key textcolor rgb "white"

# Line width of the axes
set border linewidth 1.5

# Line styles
#set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2
#set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2
#set style line 3 linecolor rgb '#ffff00' linetype 1 linewidth 2

#set xrange [1:1e9]
#set yrange [-1.5:1.5]
#set logscale xy

#tr8d(x) = x ** (-2.0/8.0);
#tr1d(x) = x ** (-2.0/1.0);
#tr2d(x) = x ** (-2.0/2.0);

#mc(x) = x ** (-1.0/2.0)
# Plot
#plot tr2d(x) title 'Трапеците 2D' with lines linestyle 1, \
#     tr8d(x) title 'Трапеците 8D' with lines linestyle 3, \
#     mc(x)   title 'Монте Карло'  with lines linestyle 2
set output 'randu-9.png'
plot "../randu/randu.dat" using 1:4 every ::::10000 with points notitle pointtype 1
