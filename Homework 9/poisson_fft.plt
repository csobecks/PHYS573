set xlabel "x"
set ylabel "y"
set zlabel "z"
set surface
set contour both
set cntrparam levels auto 8
splot "poisson_fft.data" with lines
set terminal pdf
set output "poisson_fft.pdf"
replot
