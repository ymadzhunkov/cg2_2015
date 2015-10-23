#set terminal wxt size 1024,768 enhanced font 'Verdana,10' persist
set term png transparent size 1500,800 enhanced truecolor font 'Verdana,16'

# change a color of border.
set border lw 2 lc rgb "white"

# change text colors of  tics
set xtics textcolor rgb "white"
set ytics textcolor rgb "white"

# change text colors of labels
set xlabel "x" textcolor rgb "white"
set ylabel "f(x)" textcolor rgb "white"

# change a text color of key
set key textcolor rgb "white"

#set clip two
#set key title "Gaussian Distribution"
set key inside right top vertical Left reverse enhanced autotitle nobox
set key noinvert samplen 1 spacing 1 width 0 height 0 
#set style fill   solid 1.00 noborder
set style data lines
#set style function filledcurves y1=0
ymax = exp(-1.0)
set xrange [ 0.00000 : 9.00000 ] noreverse nowriteback
set yrange [ 0.00000 : ymax ] noreverse nowriteback
unset colorbox
save_encoding = "utf8"

f(x) = x*exp(-x)

i=0
set output sprintf('animated/rejection_one-%d.png', i)
i=i + 1
plot f(x) with filledcurves y1=0 fs transparent pattern 5 lc rgb "white" title "f(x) = x e^{-x}"


set output sprintf('animated/rejection_one-%d.png', i)
i = i + 1
r1 = 2.54
set label 1 sprintf("r_1 = %.2f",r1) at r1 + 0.03, -0.03 textcolor rgb "white"
replot

set output sprintf('animated/rejection_one-%d.png', i)
i = i + 1
set arrow 1 from r1,0 to r1, ymax nohead lc rgb "white"
replot


set output sprintf('animated/rejection_one-%d.png', i)
i = i + 1
set label 2 sprintf("f(%.2f) = %.2f",r1, f(r1)) at r1 + 0.03, f(r1) textcolor rgb "white"
replot

set output sprintf('animated/rejection_one-%d.png', i)
i = i + 1
unset arrow 1
set arrow 1 from r1,0 to r1, f(r1) nohead lc rgb "green"
set arrow 2 from r1,f(r1) to r1, ymax nohead lc rgb "red"
replot

set output sprintf('animated/rejection_one-%d.png', i)
i = i + 1
r2 = 0.28
set label 3 sprintf("r_2 = %.2f",r2) at r1 + 0.5, r2 textcolor rgb "white"
set arrow 3 from r1,r2 to r1+0.4, r2 lc rgb "white"
replot
unset arrow 1
unset arrow 2
unset arrow 3

unset label 2
unset label 1
unset label 3
set pointsize 2
set palette model RGB defined ( 0 'red', 1 'green' )
i = 0
set output sprintf('animated/rejection-%d.png', i)
i = i + 1
N=10
plot f(x) with filledcurves y1=0 fs transparent pattern 5 lc rgb "white" title "f(x) = x e^{-x}",\
   'randu/randu.dat' every ::::N using ($1 * 10):($2 * ymax):( f(10*$1) < $2 * ymax ? 0 : 1 )  with points palette z pt 3 notitle

set output sprintf('animated/rejection-%d.png', i)
i = i + 1
N=100
replot
set output sprintf('animated/rejection-%d.png', i)
i = i + 1
N=300
replot
set output sprintf('animated/rejection-%d.png', i)
i = i + 1
N=500
replot
set output sprintf('animated/rejection-%d.png', i)
i = i + 1
N=1000
replot
set output sprintf('animated/rejection-%d.png', i)
i = i + 1
N=2000
replot
set output sprintf('animated/rejection-%d.png', i)
i = i + 1
N=3000
replot
set output sprintf('animated/rejection-%d.png', i)
i = i + 1
N=5000
replot
set output sprintf('animated/rejection-%d.png', i)
i = i + 1
N=7000
replot
set output sprintf('animated/rejection-%d.png', i)
i = i + 1
N=10000
replot
