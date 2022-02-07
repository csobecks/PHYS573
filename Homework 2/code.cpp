#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main (){
  double first,mid,last,fact;
  double integral=0.0;
  double mp,fp;
  double ep=0.0;
  double bin;
  ofstream myfile;
  myfile.open("SolvedInt.txt");
  
  cout<<"pick a number:";
  cin>>fact;
  cout<<"thanks"<<endl;

  for (int j=1; j<12; j++){
    bin=1<<j;
    integral=0;
    ep=0;
    cout<<"bin size is "<<bin<<endl;
    for (int i=1; ep<=1; i++){
      fp=i/bin;
      ep=(i+1)/bin;
      mp=(fp+ep)/2;
      first=pow(fp, fact-1.0)*exp((-1.0)*fp);
      mid=pow(mp, fact-1.0)*exp((-1.0)*mp);
      last=pow(ep,fact-1.0)*exp((-1.0)*ep);
      integral+=((ep-fp)/6.0)*(first+(4.0*mid)+last);
    
      first=pow(fp, -1.0-fact)*exp((-1.0)*(1/fp));
      mid=pow(mp, -1.0-fact)*exp((-1.0)*(1/mp));
      last=pow(ep, -1.0-fact)*exp((-1.0)*(1/ep));
      integral+=((ep-fp)/6.0)*(first+(4.0*mid)+last);
    }
    myfile << "Bin size "<< bin <<": Gamma(" << fact << ")= " << integral << endl;
  }

  myfile.close();
  cout<<"file written"<<endl;
  return 0;
}
