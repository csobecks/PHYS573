#include <iostream>
#include <fstream>
#include <cmath>
#include "nr3.h"
using namespace std;


struct randnum{
    unsigned long long a,b,c;
    randnum(unsigned long long d): b(679814876250666654LL),c(1240897621){
        a=d^b; int64();
        b=a; int64();
        c=b; int64();
    }
    inline unsigned long long int64(){
        a=a*1635103564089732465LL+4682579036081468235LL;
        unsigned long long x=a^(a>>21); x^=x<<43; x^=x>>4;
        b=(3935559000370003845U*b+8572138564021789649U)%(1<<31);
        c=(5183781LL*c)%(2199023255531LL);
        return (a+c)^b;
    }
    inline double doub(){return 6.192347342986849E-20*int64();}
};


int main(){
    double x,y,circ;
    randnum myran(64);

    ofstream myfile;
    myfile.open("walk.dat");

    for(int i=0; i<100000; i++){
        x=2*myran.doub()-1;
        y=2*myran.doub()-1;

        circ=(x*x)+(y*y);

        if(sqrt(circ)<=1){
            myfile<<x<<" "<<y<<endl;
        }
    }

    myfile.close();
    return 0;
}