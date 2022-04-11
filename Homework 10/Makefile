CCC         = g++
OPT         =

all: fft-demo

fft.o: fft.cpp fft.hpp
	$(CCC) $(OPT) -c fft.cpp

fft-demo: fft-demo.cpp fft.o
	$(CCC) $(OPT) -o fft-demo fft-demo.cpp fft.o

plot:	
	module load gnuplot; \
	gnuplot 'fft-demo.plt'

clean:
	rm -f *.data *.o *~ fft-demo
