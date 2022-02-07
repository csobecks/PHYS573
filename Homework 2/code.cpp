#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main (){
  double first,mid,last,fact;
  double integral=0;
  double mp,fp;
  double ep=0.0;
  unsigned double bin=1<<32;
  ofstream myfile;
  
  cout<<"pick a number:";
  cin>>fact;
  cout<<"thanks"<<endl;
   
  for (int i=1; ep<=2; i++){
    fp=i/bin;
    ep=(i+1)/bin;
    mp=(fp+ep)/2;
    first=pow(fp, fact-1.0)*exp((-1.0)*fp);
    mid=pow(mp, fact-1.0)*exp((-1.0)*mp);
    last=pow(ep,fact-1.0)*exp((-1.0)*ep);
    integral+=((ep-fp)/6.0)*(first+(4.0*mid)+last);
  }
  for (int i=2*bin-1; fp>0; i--){
    fp=i/bin;
    if(fp==0){break;}
    ep=(i+1)/bin;
    mp=(fp+ep)/2;
    first=pow(fp, 1.0-fact)*exp((-1.0)*(1/fp));
    mid=pow(mp, 1.0-fact)*exp((-1.0)*(1/mp));
    last=pow(ep, 1.0-fact)*exp((-1.0)*(1/ep));
    integral+=((ep-fp)/6.0)*(first+(4.0*mid)+last);
    cout<<"integral value is"<<integral<<endl;
  }
  cout <<"done looping"<<endl;
  myfile.open("SolvedInt.txt");
  myfile << "Gamma(" << fact << ")= " << integral << endl;
  myfile.close();
  cout<<"file written"<<endl;
  return 0;
}
