CCC         = mpic++
OPT         =

all: farm

farm: farm.cpp
	module load openmpi/2.1.1; \
	$(CCC) $(OPT) -o farm farm.cpp

submit: farm
	qsub farm.pbs

interactive:
	qsub -I -A ACF-UTK0182 -l nodes=1:ppn=16,walltime=0:05:00 -q debug

clean:
	rm -f *~ farm Farm.o* Farm.e*
