#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main (){
  double first,mid,last;
  double fact,integral;
  double mp,fp;
  double ep=0.0;
  double bin=pow(2,8);
  ofstream myfile;
  
  cout<<"pick a number:";
  cin>>fact;
  cout<<"thanks"<<endl;
   
  for (int i=1; ep<1; i++){
    fp=i/bin;
    ep=(i+1)/bin;
    mp=(fp+ep)/2;
    first=pow(fp, fact-1.0)*exp((-1.0)*fp);
    mid=pow(mp, fact-1.0)*exp((-1.0)*mp);
    last=pow(ep,fact-1.0)*exp((-1.0)*ep);
    integral+=((ep-fp)/6.0)*(first+4.0*mid+last);

    first=pow(1/fp, fact-1.0)*exp((-1.0)*(1/fp));
    mid=pow(1/mp, fact-1.0)*exp((-1.0)*(1/mp));
    last=pow(1/ep,fact-1.0)*exp((-1.0)*(1/ep));
    integral+=((fp-ep)/6.0)*(first+4.0*mid+last);
  }
  cout <<"done looping"<<endl;
  myfile.open("SolvedInt.txt");
  myfile << "Gamma(" << fact << ")=" << integral << endl;
  myfile.close();
  cout<<"file written"<<endl;
  return 0;
}
