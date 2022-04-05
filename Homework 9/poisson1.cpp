#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int L;                        // number of interior points in x and y
vector<vector<double> > V;    // potential to be found
vector<vector<double> > rho;  // given charge density

double h;                     // lattice spacing
vector<vector<double> > VNew; // new potential after each step
int steps;                    // number of iteration steps
double accuracy;              // desired accuracy in solution
double omega;                 // overrelaxation parameter

void initialize() {
    int N = L + 2;
    V = rho = VNew = vector<vector<double> >(N, vector<double>(N));

    h = 1 / double(L + 1);    // assume physical size in x and y = 1
    double q = 10;            // point charge
    int i = N / 2;            // center of lattice
    //V[i][i] = (1/(2*3.14159))*exp(-1.0*(i-L)*(i-L)/(2*1));
    for(int k=0;k<=L;k++){
    for(int m=0;m<=L;m++)
    {
        rho[m][k]=(1/2.23903)*(exp(-1.0*(m-(L/2))*(m-(L/2))/(2*4))
                                +exp(-1.0*(k-(L/2))*(k-(L/2))/(2*4)));
    }}
    // rho[i+(L/3)][i-(L/3)]=(1/2.23903)*(exp(-1.0*(i+(L/3)-L)*(i+(L/3)-L)/(2*1))+exp(-1.0*(i-(L/3)-L)*(i-(L/3)-L)/(2*1)));  // charge density
    // rho[i][i+(L/4)]=(1/2.23903)*(1+exp(-1.0*(i+(L/4)-L)*(i+(L/4)-L)/(2*1)));
    // rho[i][i]=(1/2.23903);
    steps = 0;
}

void Jacobi() {

    // Jacobi algorithm for a single iterative step
    for (int i = 1; i <= L; i++)
    for (int j = 1; j <= L; j++)
        VNew[i][j] = 0.25 * (V[i - 1][j] + V[i + 1][j] +
                             V[i][j - 1] + V[i][j + 1] +
                             h * h * rho[i][j]);
}

double relativeError() {

    double error = 0;         // average relative error per lattice point
    int n = 0;                // number of non-zero differences

    for (int i = 1; i <= L; i++)
    for (int j = 1; j <= L; j++) {
        if (VNew[i][j] != 0)
        if (VNew[i][j] != V[i][j]) {
            error += abs(1 - V[i][j] / VNew[i][j]);
            ++n;
        }
    }
    if (n != 0)
        error /= n;

    return error;
}

void GaussSeidel() {

    // copy V to VNew
    for (int i = 1; i <= L; i++)
    for (int j = 1; j <= L; j++)
        VNew[i][j] = V[i][j];

    // Gauss-Seidel update
    for (int i = 1; i <= L; i++)
    for (int j = 1; j <= L; j++)
        VNew[i][j] = 0.25 * (VNew[i - 1][j] + VNew[i + 1][j] +
                             VNew[i][j - 1] + VNew[i][j + 1] +
                             h * h * rho[i][j]);
}

void SuccessiveOverRelaxation() {

    // update even sites
    for (int i = 1; i <= L; i++)
    for (int j = 1; j <= L; j++)
    if ((i + j) % 2 == 0)
        VNew[i][j] = (1 - omega) * V[i][j] + omega / 4 *
                       (V[i - 1][j] + V[i + 1][j] +
                        V[i][j - 1] + V[i][j + 1] +
                        h * h * rho[i][j]);

    // update odd sites
    for (int i = 1; i <= L; i++)
    for (int j = 1; j <= L; j++)
    if ((i + j) % 2 != 0)
        VNew[i][j] = (1 - omega) * V[i][j] + omega / 4 *
                       (VNew[i - 1][j] + VNew[i + 1][j] +
                        VNew[i][j - 1] + VNew[i][j + 1] +
                        h * h * rho[i][j]);
}

void iterate(void (*method)()) {

    clock_t t0 = clock();

    while (true) {
        method();
        ++steps;
        double error = relativeError();
        if (error < accuracy)
            break;
        vector<vector<double> > swap = V;
        V = VNew;
        VNew = swap;
    }
    cout << " Number of steps = " << steps << endl;

    clock_t t1 = clock();
    cout << " CPU time = " << double(t1 - t0) / CLOCKS_PER_SEC
         << " sec" << endl;
}

int main() {

    cout << " Iterative solution of Poisson's equation\n"
         << " ----------------------------------------\n";
    cout << " Enter number of interior points in x or y: ";
    cin >> L;

    initialize();

    cout << " Enter desired accuracy in solution: ";
    cin >> accuracy;
    cout << " Enter 1 for Jacobi, 2 for Gauss Seidel, 3 for SOR: ";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        iterate(Jacobi);
        break;
    case 2:
        iterate(GaussSeidel);
        break;
    case 3:
        cout << " Enter overrelaxation parameter omega: ";
        cin >> omega;
        iterate(SuccessiveOverRelaxation);
        break;
    default:
        cout << " Jacobi: " << endl;
        iterate(Jacobi);
        cout << " Gauss-Seidel: " << endl;
        initialize();
        iterate(GaussSeidel);
        omega = 2 / (1 + 4 * atan(1.0) / double(L));
        cout << " Successive Over Relaxation with theoretical optimum omega = "
             << omega << endl;
        initialize();
        iterate(SuccessiveOverRelaxation);
        break;
    }

    // write potential to file
    cout << " Potential in file poisson.data" << endl;
    ofstream dataFile("poisson.data");
    for (int i = 0; i < L + 2; i++) {
        double x = i * h;
        for (int j = 0; j < L + 2; j++) {
            double y = j * h;
            dataFile << x << '\t' << y << '\t' << V[i][j] << '\n';
        }
        dataFile << '\n';
    }
    dataFile.close();
}
