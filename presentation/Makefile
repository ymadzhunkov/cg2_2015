presentation.pdf: presentation.tex beamerthemechaosgroup.sty Makefile convergence.png animated/randu-0.png animated/randu3d-0.png animated/inversetransform-0.png animated/rejection-0.png animated/montecarlo-0.png conclusion.tex mandelbrod.tex montecarlo_integration.tex variancereduction.tex generators.tex montecarlo_convergence.tex montecarlo_trapec.tex montecarlo_pi.tex probability.tex introduction.tex  montecarlo_definition.tex sampling.tex
	pdflatex presentation.tex

convergence.png: plots/convergence.gnuplot
	gnuplot plots/convergence.gnuplot 

animated/randu-0.png: plots/randu.gnuplot
	gnuplot plots/randu.gnuplot 

animated/randu3d-0.png: plots/randu3d.gnuplot
	gnuplot plots/randu3d.gnuplot 

animated/inversetransform-0.png: plots/inversetransform.gnuplot
	gnuplot plots/inversetransform.gnuplot

animated/rejection-0.png: plots/rejection.gnuplot
	gnuplot plots/rejection.gnuplot

animated/montecarlo-0.png: plots/montecarlo.gnuplot
	gnuplot plots/montecarlo.gnuplot

