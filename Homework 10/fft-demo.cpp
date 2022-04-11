// #include <cmath>
// #include <iostream>
// #include <fstream>
// #include <vector>
// using namespace std;

// #include "fft.hpp"
// using namespace cpl;

// const double pi = 4*atan(1.0);

// int N;

// int main(){
//     double q;

//     cout<<"FFT for coulomb potential"<<endl;
//     cout<<"choose a value for the charge, q"<<endl;
//     cin>>q;
//     cout << "Enter number of data points N: ";
//     cin >> N;

//     int n = 1;
//     while (n < N)
// 	n *= 2;
//     if (n != N)
// 	cout << "Setting N = " << (N = n) << " (must be a power of 2)" << endl;
//     double dt=1<<10;

//     vector<complex<double> > data(N);
//     ofstream file("f.data");
//     for(int n=0;n<=N;n++){
//         complex<double> t=(n+1)*dt;
//         complex<double> val;
//         val=q/t;
//         data[n]=val.real();
//         file<<t<<'\t'<<val.real()<<'\n';
//     }
//     file.close();
//     cout<<"function output to f.data"<<endl;

//     FFT fft;
//     fft.transform(data);
//     file.open("fHat.data");
//     for(int n=0;n<N;n++){
//         double omega = n*2*pi/(N*dt);
// 	    file<<omega<<'\t'<<real(data[n])<<'\n';
//     }
//     file.close();
//     cout<<"tranform output to fHat.data"<<endl;

// }





// fft_demo.cpp
// demonstrate use of FFT on damped oscillator

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "fft.hpp"
using namespace cpl;

const double pi = 3.1415926;

int N;				// number of transform points

int main ( ) {
    cout << "FFT of coulomb potential\n";
    cout << "Enter number of data points N: ";
    cin >> N;
    int n = 1;
    while (n < N)
	n *= 2;
    if (n != N)
	cout << "Setting N = " << (N = n) << " (must be a power of 2)" << endl;
    double dt = 255;

    vector< complex<double> > data(N);
    ofstream file("f.data");
    double q=2.0;
    for (int n = 0; n < N; n++) {
	    double t = (n+1)*dt;
	    complex<double> x = q/t;
	    data[n] = x.real();
	file << t << '\t' << x.real() << '\n';
    }
    file.close();
    cout << "Function output to f.data" << endl;

    FFT fft;
    fft.transform(data);
    file.open("fHat.data");
    for (int n = 0; n < N; n++) {
	    double t = (n+1)*dt;
	    file << t << '\t' << real(data[n])<< '\n';
    }
    file.close();
    cout << "Transform output to fHat.data" << endl;
}
