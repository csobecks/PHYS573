#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(){
    static int first_time=1;
    static ofstream f_data, f_site, f_a_rate;

    if(first_time){
        f_site.open("site.txt");
        if(f_site.bad()){
            cout<<"Failed to open sites data file\n"<<flush;
        }

        first_time=0;
    }

    // simulation parameters
    int THERM = 1000000; // number of thermalization steps
    int SWEEPS = 1000000; // number of generation steps
    int GAP = 100; // interval between measurements
    double DELTA = 1.0 ; // random shift range
    //−DELTA <= delta <= DELTA
    double shift , u ; // random shift , random number value
    double tot = 0.0 ;
    int accept = 0 , no_calls = 0 ; // for acceptance rate
    double a=1.0;
    double b=8.0;
    double f=2.0;
    //physics parameters
    int T=64; //number of time slices
    double omega=1.0; //frequency omega
    double m=1.0; //mass m

    double dS; //change in action
    double site[T], old_site[T], new_site[T];

    int tau; //to choose a random site

    //write out initially 
    cout<<"MCMC for double well potential"<<endl;
    cout<<"a="<< a<<" b="<<b<<" f="<<f<< endl;
    cout<<"mass is "<<m<<endl;

    //initilize
    for(int t=0; t<T;t++){
        // site[t]=exp(-(t*t)/2.0)
        site[t]=(drand48()-0.5);
    }

    //begin thermalization MC sweeps
    for(int i=1; i<=THERM; i++){
        //loop over time slices
        for(int t=0;t<T;t++){
            tau=int(T*drand48());

            //store the current position at tau
            old_site[tau]=site[tau];

            //amount of random shift for position at tau
            shift=2.0*DELTA*(drand48()-0.5);

            //propose a small change in position at tau
            new_site[tau]=site[tau]+shift;

            //compute change in action
            if(tau!=(T-1)){
                // dS=((m/2.0)*((pow((site[tau+1]-new_site[tau]),2.0))
                //            -(pow((site[tau+1]-old_site[tau]),2.0))))
                   dS=(1/2)*(-a*(pow((site[tau+1]+new_site[tau]),4.0))
                         +b*((pow((site[tau+1]+new_site[tau]),2.0)))
                         +f*(site[tau+1]+new_site[tau])
                         -a*(pow((site[tau+1]+old_site[tau]),4.0))
                         +b*((pow((site[tau+1]+old_site[tau]),2.0)))
                         +f*(site[tau+1]+old_site[tau]));
            }
            else if(tau==(T-1)){
                // dS=((m/2.0)*((pow((site[0]-new_site[tau]),2.0))
                //            -(pow((site[0]-old_site[tau]),2.0))))
                   dS=(1/2)*(-a*(pow((site[tau+1]+new_site[tau]),4.0))
                         +b*((pow((site[tau+1]+new_site[tau]),2.0)))
                         +f*(site[tau+1]+new_site[tau])
                         -a*(pow((site[tau+1]+old_site[tau]),4.0))
                         +b*((pow((site[tau+1]+old_site[tau]),2.0)))
                         +f*(site[tau+1]+old_site[tau]));
            }

            //Metropolis update
            u=drand48();
            if(u<exp(-dS)){
                site[tau]=new_site[tau];
                accept++;
                // cout<<"ACCEPTED with dS of "<<dS<<endl;
            }
            else{
                site[tau]=old_site[tau];
                // cout<<"REJECTED with dS of "<<dS<<endl;
            }
        }//end of loop over time slices
    }//end of thermalization MC steps

    //begin generation MC steps
    for(int i=1;i<=SWEEPS; i++){
        //loop over time slices
        for(int t=0;t<T;t++){
            no_calls++;
            if((no_calls%100==0)&&(!first_time)){
                // cout<<"Acceptance rate "<<(double)accept/(double)no_calls<<"\n"<<flush;

                //write out accpatance rate to a file
                f_a_rate<<(double)accept/(double)no_calls<<endl;

                no_calls=0;
                accept=0;
            }

            //randomly choose a site
            tau=int(T*drand48());

            //store current position at tau
            old_site[tau]=site[tau];

            //amount of shift for position at tau
            shift=2.0*DELTA*(drand48()-0.5);

            //propose a small change to position at tau
            new_site[tau]=site[tau]+shift;

            //compute change in action
            if(tau!=(T-1)){
                // dS=((m/2.0)*((pow((site[tau+1]-new_site[tau]),2.0))
                //            -(pow((site[tau+1]-old_site[tau]),2.0))))
                   dS=(1/2)*(-a*(pow((site[tau+1]+new_site[tau]),4.0))
                         +b*((pow((site[tau+1]+new_site[tau]),2.0)))
                         +f*(site[tau+1]+new_site[tau])
                         -a*(pow((site[tau+1]+old_site[tau]),4.0))
                         +b*((pow((site[tau+1]+old_site[tau]),2.0)))
                         +f*(site[tau+1]+old_site[tau]));
            }
            else if(tau==(T-1)){
                // dS=((m/2.0)*((pow((site[0]-new_site[tau]),2.0))
                //            -(pow((site[0]-old_site[tau]),2.0))))
                   dS=(1/2)*(-a*(pow((site[tau+1]+new_site[tau]),4.0))
                         +b*((pow((site[tau+1]+new_site[tau]),2.0)))
                         +f*(site[tau+1]+new_site[tau])
                         -a*(pow((site[tau+1]+old_site[tau]),4.0))
                         +b*((pow((site[tau+1]+old_site[tau]),2.0)))
                         +f*(site[tau+1]+old_site[tau]));
            }

            //Metropolis update
            u=drand48();
            if(u<exp(-dS)){
                site[tau]=new_site[tau];
                accept++;
                // cout<<"ACCEPTED with dS of "<<dS<<endl;
            }
            else{
                site[tau]=old_site[tau];
                // cout<<"REJECTED with dS of "<<dS<<endl;
            }
        }//end loop over time slices

        if(i%GAP==0){
            tot++;
            //write out x[0] to a file
            f_site<<tot<<"\t"<<site[0]<<endl;
        }
    }// end generation MC steps


    return 0;
}
