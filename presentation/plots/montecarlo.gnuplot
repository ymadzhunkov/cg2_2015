#set terminal wxt size 1024,768 enhanced font 'Verdana,10' persist
set term png transparent size 2048,768 enhanced truecolor font 'Verdana,16'

# change a color of border.
set border lw 2 lc rgb "white"

# change text colors of  tics
set xtics textcolor rgb "white"
set ytics textcolor rgb "white"

# change text colors of labels
set xlabel "x" textcolor rgb "white"
#set ylabel "r" textcolor rgb "white"

# change a text color of key
set key textcolor rgb "white"

set clip two
#set key title "Gaussian Distribution"
set key inside left top vertical Left reverse enhanced autotitle nobox
set key noinvert samplen 1 spacing 1 width 0 height 0 
#set title "Transparent pattern-filled curves"
#set style fill   solid 1.00 noborder
set style data lines
#set style function filledcurves y1=0
set xrange [-pi : pi ] noreverse nowriteback
set yrange [0.00000 : 1.00000 ] noreverse nowriteback
unset colorbox
save_encoding = "utf8"
f(x) = sin(x*4)*sin(x*4)*exp(-x*x/2)
set xtics ('-π' -pi, '-π/2' -pi/2, 0, 'π/2' pi/2, 'π' pi)

outfile = sprintf('animated/montecarlo_dummy-0.png')
set output outfile
set samples 2000 #  no of sampling points
plot f(x) with filledcurves y1=0 fs transparent pattern 5 lc rgb "white" notitle


do for [i=0:12] { 
   N = 5 + (i+1)*(i+1)
   set samples N
   datfilename = sprintf('animated/tmp-%d.dat',i)
   set label 1 at -1.3, 0.8 sprintf('N = %d',N) font "Times New Roman,40" textcolor rgb "white"

   set table datfilename
   plot f(x)
   unset table
   outfile = sprintf('animated/trapez-%d.png',i)
   set output outfile
   set samples 2000 #  no of sampling points
   plot \
   datfilename with filledcurves y1=0 fs transparent solid 0.50 lc rgb "orange" lw 2 notitle, \
   datfilename with points ps 1 pt 6 lt -1 lw 4 lc rgb 'white' notitle, \
   datfilename with impulses lt -1 lw 2 lc rgb 'blue' notitle, \
   f(x) with filledcurves y1=0 fs transparent pattern 5 lc rgb "white" notitle
}


do for [i=0:12] { 
   N = 5 + (i+1)*(i+1)
   set label 1 at -1.3, 0.8 sprintf('N = %d',N) font "Times New Roman,40" textcolor rgb "white"
   datfilename = 'randu/randu.dat'
   outfile = sprintf('animated/montecarlo-%d.png',i)
   set output outfile
   set samples 2000 #  no of sampling points
   plot \
   datfilename using ($1*2*pi - pi):(f($1*2*pi - pi)) every ::::N with points ps 1 pt 6 lt -1 lw 4 lc rgb 'white' notitle, \
   datfilename using ($1*2*pi - pi):(f($1*2*pi - pi)) every ::::N with impulses lt -1 lw 2 lc rgb 'blue' notitle, \
   f(x) with filledcurves y1=0 fs transparent pattern 5 lc rgb "white" notitle
}
