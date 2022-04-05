CCC         = g++
OPT         =

all: poisson poisson_fft

fft.o: fft.cpp fft.hpp
	$(CCC) $(OPT) -c fft.cpp

poisson: poisson.cpp
	$(CCC) $(OPT) -o poisson poisson.cpp

poisson_fft: poisson_fft.cpp fft.o
	$(CCC) $(OPT) -o poisson_fft poisson_fft.cpp fft.o

clean:
	rm -f *.data *.o *.pdf *~ poisson poisson_fft
