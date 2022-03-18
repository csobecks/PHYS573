CCC         = g++
OPT         = \
-I/sw/cs400_centos7.3_acfsoftware/gsl/2.3/centos7.3_gnu6.3.0/include \
-L/sw/cs400_centos7.3_acfsoftware/gsl/2.3/centos7.3_gnu6.3.0/lib \
-lgsl -lgslcblas -lm

all: runge

runge: runge.cpp
	$(CCC) -o runge runge.cpp $(OPT)

run: runge
	module load gsl; \
	./runge

plot:
	module load gnuplot; \
	gnuplot 'runge-noninteractive.plt'; \
	display -flatten runge.pdf

clean:
	rm -f *~ runge
