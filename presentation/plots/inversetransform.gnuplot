#set terminal wxt size 1024,768 enhanced font 'Verdana,10' persist
set term png transparent size 1500,800 enhanced truecolor font 'Verdana,16'

# change a color of border.
set border lw 2 lc rgb "white"

# change text colors of  tics
set xtics textcolor rgb "white"
set ytics textcolor rgb "white"

# change text colors of labels
set xlabel "x" textcolor rgb "white"
set ylabel "r" textcolor rgb "white"

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
set xrange [ 0.00000 : 9.00000 ] noreverse nowriteback
set yrange [ 0.00000 : 1.00000 ] noreverse nowriteback
unset colorbox
save_encoding = "utf8"

f(x) = x*exp(-x)
F(x) = 1 - (x+1)*exp(-x)

#r=0.53
v=1.77605
v=1.77605
r=(F(v))
#set label 1 sprintf("r = %.2f",r) at +0.03,r+0.02 textcolor rgb "white"
#set label 2 sprintf("F^{-1}(%.2f) = %.2f",r,v) at v+0.06,r-0.02 textcolor rgb "white"
#unset arrow 1
#unset arrow 2


#set style fill transparent pattern 4 bo
#
i=0
set output sprintf('animated/inversetransform-%d.png', i)
i=i+1
plot f(x) with filledcurves y1=0 fs transparent pattern 5 lc rgb "white" title "f(x) = x e^{-x}",\
     F(x) lc rgb "light-grey" lw 3 title "F(x) = 1 - (x+1)e^{-x}"

set output sprintf('animated/inversetransform-%d.png', i)
i=i+1
set label 1 sprintf("r = %.2f",r) at +0.03,r+0.02 textcolor rgb "white"
replot

set output sprintf('animated/inversetransform-%d.png', i)
i=i+1
set arrow 1 from 0,r to v,r lw 3 lc "blue"
replot

set output sprintf('animated/inversetransform-%d.png', i)
i=i+1
set label 2 sprintf("F^{-1}(%.2f) = ?",r) at v+0.06,r-0.02 textcolor rgb "white"
replot

set output sprintf('animated/inversetransform-%d.png', i)
i=i+1
unset label 2
set label 2 sprintf("F^{-1}(%.2f) = %.2f",r,v) at v+0.06,r-0.02 textcolor rgb "white"
replot

set output sprintf('animated/inversetransform-%d.png', i)
i=i+1
set arrow 2 from v,r to v,0 lw 3 lc "blue"
replot
