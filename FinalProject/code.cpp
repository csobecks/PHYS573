#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "rpois.h"

using namespace std;

class runi{
    public:
        double riskpopu[150];
        double dailynew[150];
        double total;
}

/*
days: observation period
nd: simulation period
Rt: infection rate pattern
muT: mean time an infrected person will transmit the virus to another person; mean infection time. 
     assume independence among those ones begin infected. The default value is set to muT=4 days
sizeV: the dispersion parameter so that the variance=mu+mu^2/size.
       the default value is 1
limit: the target population size
pp: the proportion of people with immunity in the population
n0: the initial number of infectious persons
    the default setting is n0=1, just one infected person
*/
int TransSimu(int nd, double muT, double sizeV, int n0, runi &a){
    double kk=rep(0.0,days); //daily new cases: kk
    double atrisk=rep(0.0,days); //atrisk: number of active cases each day
    int nn=length(kk); //simulation period of nn days

    int tt=0; // the cumulative total number of confirmed cases

    if(nd>length(Rt)){
        println("Error: the length of Rt should not be smaller than nd.");
        return -1;
        //break somehow
    }
    double stoplimit=limit*(1-pp);

    int nk=n0; // initial number of existing infectious persons; need at least one person

    for(int k; k<nk; k++){
        if(tt>stoplimit){Rt[1]=0.001;}

        ni=poisson_distribution<int> dist(Rt[1]);
        imuind=;

        if(imuind==1){ni=0;}
        tt=tt+ni;

        if(ni>0){
            double tk[ni];
            for(int j=0;j<ni;j++){
                tk[j]=rnbinom(1,size=sizeV,mu=muT)+1;
                kk[tk[j]]=kk[tk[j]]+1;
            }    
        }

    }
    

    return 0;
}



void main(){

    int iter=2;
    int out;
    runi a;
    int nd=100;
    double muT=3.8;
    double sizeV=1.1;
    int n0=9;
    int outMA[iter][150];
    int newMA[iter][150];
    int gtotalA;

    for(int i=0; i<iter; i++){
        out=TransSimu(nd,muT,sizeV,n0,a);
        if(out==-1){
            cout<<"Error"<<endl;
            break;}


        for(int j=0;j<150;j++){
            outMA[i][j]=a.riskpopu[j];
            newMA[i][j]=a.dailynew[j];
            gtotalA=a.total;
        }
    }
    
    if(out==-1){return;}

    Ofstream file("output.txt");
    file<<outMA<<" "<<newMA<<" "<<gtotalA<<"\n";
    file.close();
    return;
}