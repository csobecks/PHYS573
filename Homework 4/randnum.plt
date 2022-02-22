# myplot
# load "randtest.plt"

plot "randnum.dat"
set terminal pdf
set output "randnum.pdf"
replot
set terminal png size 800,500
set output "randnum.png"
replot