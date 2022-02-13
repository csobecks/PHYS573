#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


double Pleg(int l, int m, double x){
    double front=1;
    double val;
    double PI=3.1415926;

    if (abs(x)>1||m>l||m<0){
        cout<<"that's not going to work."<<endl;
        return 0;
    }

    for(int i=0;i<m;i++){
        front*=-1;
    }

    val=front*sqrt((2*m+1)/(4*PI*factorial(2*m))*doubfact(2*m-1)*xval(1-x*x,m);

    for(int i=0;m+i<l;i++){
        val*=x*sqrt(2*m+3)
    }

    return val;
}

double xval(double val, int m){
    double num=1;
    if m%2==0{
        int hold=floor(m/2);
        for(int i=0;i<hold;i++){
            num*=val;
        }
    }
    else{
        int hold=floor(m/2);
        for(int i=0;i<hold;i++){
            num*=val;
        } 
        num*=sqrt(val);
    }
}


double factorial(int val){
    double num=1;
    for(int i=0;val-i>0;i++){
        num*=val-i;
    }
    return num;
}

double doubfact(int val){
    double num=1;
    for(int i=0,val-2*i>0;i++){
        num*=val-2*i;
    }
    return num;
}


int main(){
    int l,m;
    double bin=1<<10;

    cout<<"What is your l value?"<<endl;
    cim>>l;
    cout<<"what about m value?(shouldn't be bigger than l)"<<endl;
    cin>>m;
    cout<<"nice, calculating...."<<endl;

    for(int i=0;i/bin<1;i++){
        
    }


    return 0;
}