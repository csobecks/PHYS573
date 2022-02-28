## Homework 5

For this homework we are using ROOT. I am a condensed matter student, so I don't really care for ROOT. I find that python is better at plotting for me and it is prettier/faster than ROOT. Regardless, I am doing a project on root. The plotting feature of ROOT seems to draw me the most so I'm going to plot the value of the complimentary error function over a 2D plane. The error function, erf(x), shows up in many places of physics. It is used to find the error in a measurement at a point. It can also be used to describe diffusion in thermodynamics. I chose to use the complimentary error function because it's changing values shows up better on a plot from 0 to 0.5 than the error function from 0 to 1. 

My commands were the following
>module load root
>root
>.x code.C