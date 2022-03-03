## Homework 6

For this assignment, I've completed the example farm.cpp. That code is in the farm folder. The commands that I used are the following
>make clean
>make
>make submit

The physics calculation is located in the mysim folder. The calculation that I am performing is the canonical ensemble partition function. This function is an sum of boltzmann factors. We're lucky because these factors go to zero as the energy levels get higher. For my calculation, I'm splitting up this sum up by the number of nodes and then calculating each part. The accuracy of my calculation is double precision, but this can be increased by changing the data type. The energy spectrum that I'm using is the 1D harmonic oscillator. Manually checking the solution for the first few terms, the solution is accurate, so I am happy. The commands are the following.
>make clean
>make
>make submit