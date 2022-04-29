
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
double TransSimu(int days, int nd, float rr, float muT, float sizeV, float limit, double pp, int n0){
    kk=atrisk=rep(0.0,days); //daily new cases: kk
                             //atrisk: number of active cases each day
    nn=length(kk); //simulation period of nn days

    tt=0; // the cumulative total number of confirmed cases

    if(nd>length(Tr)){
        println("Error: the length of Rt should not be smaller than nd.")
        breaker=1;
    }

    
}