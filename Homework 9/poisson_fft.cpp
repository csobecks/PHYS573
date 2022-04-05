#include <cmath>
#include <complex>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

#include "fft.hpp"
using namespace cpl;

int main() {

    cout << " FFT solution of Poisson's equation\n"
         << " ----------------------------------\n";
    cout << " Enter number points in x or y: ";
    int N;
    cin >> N;
    int n = 1;
    while (n < N)
        n *= 2;
    if (n != N)
        cout << " must be a power of 2, using " << (N=n) << endl;

    double h = 1 / double(N - 1);        // assume physical size in x and y = 1

    clock_t t0 = clock();

    double q = 10;                       // point charge
    vector<vector<complex<double> > > rho =
        vector<vector<complex<double> > >(N, vector<complex<double> >(N));
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            if (j == N/2 && k == N/2)    // at center of lattice
                rho[j][k] = q / (h * h);
            else
                rho[j][k] = 0.0;
        }
    }

    vector<complex<double> > f(N);       // to store rows and columns
    FFT fft;                             // FFT object for 1-D transforms

    // FFT rows of rho
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++)
            f[k] = rho[j][k];
        fft.transform(f);
        for (int k = 0; k < N; k++)
            rho[j][k] = f[k];
    }
    // FFT columns of rho
    for (int k = 0; k < N; k++) {
        for (int j = 0; j < N; j++)
            f[j] = rho[j][k];
        fft.transform(f);
        for (int j = 0; j < N; j++)
            rho[j][k] = f[j];
    }

    // solve equation in Fourier space
    complex<double> i(0.0, 1.0);
    double pi = 4 * atan(1.0);
    complex<double> W = exp(2.0 * pi * i / double(N));
    complex<double> Wm = 1.0, Wn = 1.0;
    for (int m = 0; m < N; m++) {
        for (int n = 0; n < N; n++) {
            complex<double> denom = 4.0;
            denom -= Wm + 1.0 / Wm + Wn + 1.0 / Wn;
            if (denom != 0.0)
                rho[m][n] *= h * h / denom;
            Wn *= W;
        }
        Wm *= W;
    }

    // inverse FFT rows of rho
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++)
            f[k] = rho[j][k];
        fft.inverse_transform(f);
        for (int k = 0; k < N; k++)
            rho[j][k] = f[k];
    }
    // inverse FFT columns of rho
    for (int k = 0; k < N; k++) {
        for (int j = 0; j < N; j++)
            f[j] = rho[j][k];
        fft.inverse_transform(f);
        for (int j = 0; j < N; j++)
            rho[j][k] = f[j];
    }

    clock_t t1 = clock();
    cout << " CPU time = " << double(t1 - t0) / CLOCKS_PER_SEC
         << " sec" << endl;

    // write potential to file
    cout << " Potential in file poisson_fft.data" << endl;
    ofstream dataFile("poisson_fft.data");
    for (int j = 0; j < N; j++) {
        double x = j * h;
        for (int k = 0; k < N; k++) {
            double y = k * h;
            dataFile << x << '\t' << y << '\t' << real(rho[j][k]) << '\n';
        }
        dataFile << '\n';
    }
    dataFile.close();
}
