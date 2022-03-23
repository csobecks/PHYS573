CCC         = g++
OPT         =

all: threebody

odeint.o: odeint.cpp
	$(CCC) $(OPT) -c odeint.cpp
linalg.o: linalg.cpp
	$(CCC) $(OPT) -c linalg.cpp
threebody: prc3body.cpp odeint.o linalg.o
	$(CCC) $(OPT) -o threebody prc3body.cpp odeint.o linalg.o
clean:
	-rm -f *.o *.data threebody
