## Homework 8

To begin this assignment, I created a few cases to just test the code to see how the output would change with each variable. 

To check the dependence of the three body calculations on the numerical method used, I have created eight trials for varying step size and accuracy. For all the trials, I have set the accuracy to 1e-6 and the step size to 30. From here, I set the trials in the following way 
0: μ=0.5 x=0.3 v_y=1.0
1: μ=0.5 x=1.0 v_y=1.0
2: μ=0.9 x=0.3 v_y=1.0
3: μ=0.9 x=1.0 v_y=1.0
4: μ=0.5 x=0.3 v_y=0.5
5: μ=0.5 x=1.0 v_y=0.5
6: μ=0.9 x=0.3 v_y=0.5
7: μ=0.9 x=1.0 v_y=0.5

The plots are then labelled trajectory_trial#.pdf.

The initial value was chosen because it is similar to a stable method that we have looked at in class. By changing these values, I can see how each parameter effects the path of the orbit. For the case of the μ term, this seems to widen each loop in the orbit as seen between plots 0 & 2 and plots 4&6. The x term seems to be able to pull apart the orbit. This is seen between plots 0 & 1. plot 0 is stable, but once the initial point is pulled to x=1.0, the orbit falls apart. The loops in the oscillation are there, but they don't line up anymore so the motion is a bit more chaotic. This is also seen between plots 4&5. The v_y term looks like it can flip the direction of the orbit as seen in plots 3&7. Here the parameters are such that the system will escape the orbit. When the v_y term is below 1, it deviates to the negative x axis while v_y=1 deviates to the right. We can also see this flip or pull in plots 0&4. 

To test step size, I have set the following parameters (μ=0.5,x=1.0,v_y=1.0,accuracy=1e-6) From here, I've set the step sizes to (0=10,1=20,2=50,3=100) in the corresponding files trajectory_step#.pdf. As we can see in plot 0, we have a general idea of how the system will evolve in the short term after starting. Here we have no idea if the system will diverge or hit escape velocity. To see this, we need to move to a higher step size like that in plot 3 where the step size is 100. Here we have a good idea that the motion will be quite chaotic. This may be helpful for trying to find some sort of steady state solution, but it offers us no help in determining the final state of of the system. It's also very difficult to even follow the path of the system. Therefore, it's preferable to use a smaller step size to get an exact path of a system in a short time period. On the other hand it's more beneficial to have a large step size when trying to see if the system achieves any sort of steady state orbit. 

Turning to the accuracy parameter of the measurements. For this system, I have the parameters set to (μ=0.4,x=0.4,v_y=1.0,step=20). These parameters were chosen because this is a system that we know is stable and has a step size that gives at least one full orbit. The accuracy parameter was set to (0=1e-3,1=1e-6,2=1e-9,3=1e-12). From here, observing plot 0, we have a decent idea of the path in the loops, but the transition between loops only has about three points defining the steps between. This calculation is quite fast because of this low accuracy. Turning to plot 3, there is a very clearly defined path of the system as it moves through orbit. The steps that were initially missing in between are very clearly definied. The issue with this one is that the calculation time is noticeably slower. Where plot 0 took milliseconds, plot 3 took around 1 second. This may not be so bad now, but moving to higher systems this can become a very large number. So a lower accuracy should be used when running trials or very large systems in a short timeframe. Otherwise, if a higher accuracy can be afforded, it should be employed. Realistically, you probably only need 1e-6 like in plot 2. 
