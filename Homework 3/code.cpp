#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double Pleg(int,int,double);
double xval(double,int);
double factorial(int);
double doubfact(int);
double Leg(int,int,double,double);
double Yreal(int,double,double);
double Yimag(int,double,double);


double Leg(int l, int m, double x,double val){
    double PI=3.141592653589793;
    return sqrt(((4*PI)*factorial(l+m))/(((l<<1)+1)*factorial(l-m)))*val;
}

double Pleg(int l, int m, double x){
    double front=1;
    double val;
    double PI=3.141592653589793;

    if (abs(x)>1 || m>l || m<0){
        cout<<"that's not going to work."<<endl;
        return -1;
    }
    else{
        if(m&1!=0){
            front=-1;
        }
        else{
            front=1;
        }

        val=front*sqrt(((m<<1)+1)/((PI*4)*factorial(m<<1)))*doubfact((m<<1)-1)*xval(1-x*x,m);

        for(int i=0;m+i<l;i++){
            val*=x*sqrt((m<<1)+3);
        }

        return val;
    }
}

double Yreal(int m, double phi, double val){
    double PI=3.141592653589793;
    double twoPI=2*PI;
    int forward=0;

    while(forward==0){
        if(phi>twoPI){
            phi-=twoPI;
        }
        else{forward=1;}
    }
    return val*cos(m*phi);
}

double Yimag(int m, double phi, double val){
    double PI=3.141592653589793;
    double twoPI=2*PI;
    int forward=0;

    while(forward==0){
        if(phi>twoPI){
            phi-=twoPI;
        }
        else{forward=1;}
    }
    return val*sin(m*phi);
}

double xval(double val, int m){
    double num=1;
    int hold=m>>1;
    
    for(int i=0;i<hold;i++){
            num*=val;
    }
    
    if(m&1){
        num*=sqrt(val);
    }else{}

    return num;
}


double factorial(int val){
    double num=1;
    for(int i=0;val-i>0;i++){
        num*=val-i;
    }
    return num;
}

double doubfact(int val){
    int loop=val;
    double num=1;
    for(int i=0;(loop-(i<<1))>0;i++){
        num*=val-(i<<1);
    }
    return num;
}

int main(){
    int l,m;
    double phi;
    double x=0;
    int bin1=1<<3;
    double bin=1<<3;
    double aR[bin1][2];
    ofstream myfile;
    myfile.open("LegPlot.dat");

    cout<<"What is your l value?"<<endl;
    cin>>l;
    cout<<"what about m value?(shouldn't be bigger than l)"<<endl;
    cin>>m;
    cout<<"what value for phi?"<<endl;
    cin>>phi;
    cout<<"nice, calculating...."<<endl;

    for(int i=0;x<=1;i++){
        aR[i][0] = Pleg(l,m,x);
        aR[i][1] = Leg(l,m,x,aR[i][0]);
        aR[i][2] = Yreal(m,phi,aR[i][0]);
        aR[i][3] = Yimag(m,phi,aR[i][0]);
        myfile<<x<<" "<<aR[i][0]<<" "<<aR[i][1]<<" "<<aR[i][2]<<" "<<aR[i][3]<<endl;
        x=(i+1)/bin;
    }
    myfile.close();
    cout<<"done"<<endl;
    return 0;
}