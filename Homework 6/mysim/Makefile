CCC         = mpic++
OPT         =

all: mysim

mysim: mysim.cpp
	module load openmpi/2.1.1; \
	$(CCC) $(OPT) -o mysim mysim.cpp

submit: mysim
	qsub mysim.pbs

interactive:
	qsub -I -A ACF-UTK0182 -l nodes=1:ppn=16,walltime=0:05:00 -q debug

clean:
	rm -f *~ mysim Mysim.o* Mysim.e*
