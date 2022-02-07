#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main (){
  double first,mid,last,fact;
  double integral=0.0;
  double mp,fp;
  double ep=0.0;
  double bin=1<<1;
  double elapsed;
  ofstream myfile;
  myfile.open("SolvedInt.txt");
  
  cout<<"pick a number:";
  cin>>fact;
  cout<<"thanks"<<endl;

  //bin size 1
  cout<<"bin size"<<bin<<endl;
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

  //bin size 2
  integral=0;
  bin=1<<3;
  ep=0;
  cout<<"bin size"<<bin<<endl;
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
  myfile << "Bin size "<< bin <<": Gamma(" << fact << ")= " << integral <<endl;

  //bin size 3
  integral=0;
  bin=1<<5;
  ep=0;
  cout<<"bin size"<<bin<<endl;
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

  //bin size 4
  integral=0;
  bin=1<<6;
  ep=0;
  cout<<"bin size"<<bin<<endl;
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

  //bin size 5
  integral=0;
  bin=1<<10;
  ep=0;
  cout<<"bin size"<<bin<<endl;
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

  myfile.close();
  cout<<"file written"<<endl;
  return 0;
}
