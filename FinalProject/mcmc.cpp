#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(){
    static int first_time=1;
    static ofstream f_data, f_site, f_a_rate;

    if(first_time){
        // f_data.open("corr.txt");
        // if(f_data.bad()){
        //     cout<<"Failed to open correlator file\n"<<flush;
        // }

        // f_a_rate.open("acceptance.txt");
        // if (f_a_rate.bad()){
        //     cout<<"Failed to open acceptance rate file\n"<<flush;
        // }

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

    //observables

    double corr[T]; //to store correlator data
    double corr_sq[T], std_err[T];
    double xsq=0.0, xsq_sq=0.0;
    double x_val=0.0, x_val_sq=0.0;
    double std_err_x_val, std_err_xsq;

    int tau; //to choose a random site

    //write out initially 
    cout<<"MCMC for double well potential"<<endl;
    cout<<"a="<< a<<" b="<<b<<" f="<<f<< endl;
    cout<<"mass is "<<m<<endl;

    //initilize observables etc
    for(int t=0; t<T;t++){
        // site[t]=exp(-(t*t)/2.0)
        site[t]=(drand48()-0.5);
        old_site[t]=0.0;
        new_site[t]=0.0;
        corr[t]=0.0;
        std_err[t]=0.0;
        corr_sq[t]=0.00;
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

            //compute correlator, etc.
            for(int t=0;t<T;t++){
                corr[t]=corr[t]+site[t]*site[0]/(2.0*m*omega);
                corr_sq[t]=corr_sq[t]+pow(site[t]*site[0]/(2.0*m*omega),2.0);

                x_val=x_val+site[t];
                x_val_sq = x_val_sq+site[t]*site[t];

                xsq=xsq+site[t]*site[t]/(2.0*m*omega);
                xsq_sq=xsq_sq+pow(site[t],4.0)/(pow(2.0*m*omega,2.0));
            }
        }
    }// end generation MC steps

    //evaluate error in observables
    // for(int t=0;t<T;t++){
    //     corr[t]=corr[t]/tot;
    //     corr_sq[t]=corr_sq[t]/tot;
    //     std_err[t]=sqrt((corr_sq[t]-corr[t]*corr[t])/tot);
    // }

    // xsq=xsq/(tot*T);
    // xsq_sq=xsq_sq/(tot*T);
    // x_val=x_val/(tot*T);
    // x_val_sq=x_val_sq/(tot*T);
    // std_err_xsq=sqrt((xsq_sq-xsq*xsq)/(tot*T));
    // std_err_x_val=sqrt((x_val_sq-x_val*x_val)/(tot*T));

    // cout<<"\n<x^2>= "<<xsq<<"\t"<<std_err_xsq<<"\n"<<endl;
    // cout<<"\n<x>= "<<x_val<<"\t"<<std_err_x_val<<"\n"<<endl;

    // cout<<"\nE_0=m*omega^2*<x^2>= "<<m*omega*omega*xsq<<"\t"<<m*omega*omega*std_err_xsq<<"\n"<<endl;

    // //write out correlator to a file
    // for(int t=0;t<T;t++){
    //     f_data<<t<<"\t"<<corr[t]<<"\t"<<std_err[t]<<endl;
    // }
    // f_data<<T<<"\t"<<corr[0]<<"\t"<<std_err[0]<<endl;

    return 0;
}
