/*
    The Restricted Planar Circular Massless Three-Body Problem
    Choose units:  G = 1,  M_Sun + M_Jupiter = 1,  |r_Jupiter - r_Sun| = 1
    In the co-rotating frame r_Sun = (-mu, 0), r_Jupiter = (1 - mu, 0)
    In these units mu = 0.00095 and
    the physical initial conditions for Earth are
    x = 1/5.203 = 0.192,  v_y = 1/sqrt(x) = 2.28
 */

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "linalg.hpp"              //  linear algebra for vector<double>
#include "odeint.hpp"              //  to use adaptive Runge-Kutta
using namespace cpl;

double mu;                         //  mass of Jupiter

double Jacobi(
  const vector<double>& trv
) {
  double t = trv[0], x = trv[1], y = trv[2], vx = trv[3], vy = trv[4],
    r1 = sqrt((x + mu) * (x + mu) + y * y),
    r2 = sqrt((x - 1 + mu) * (x - 1 + mu) + y * y);
  return x * x + y * y + 2 * (1 - mu) / r1 + 2 * mu / r2 - vx * vx - vy * vy;
}

bool switch_t_and_y = false;       //  to zero in on section point

//  derivative vector in co-rotating frame
vector<double> f(
  const vector<double>& trv
) {
  double t = trv[0], x = trv[1], y = trv[2], vx = trv[3], vy = trv[4],
    r1 = sqrt((x + mu) * (x + mu) + y * y),
    r2 = sqrt((x - 1 + mu) * (x - 1 + mu) + y * y);
  vector<double> f(5);
  f[0] = 1;
  f[1] = vx;
  f[2] = vy;
  f[3] = 2 * vy + x - (1 - mu) * (x + mu) / (r1 * r1 * r1)
       - mu * (x - 1 + mu) / (r2 * r2 * r2);
  f[4] = - 2 * vx + y - (1 - mu) * y / (r1 * r1 * r1)
       - mu * y / (r2 * r2 * r2);

  if (switch_t_and_y)
    f /= vy;

  return f;
}

// compute v_y given mu, C, x, and assuming y = 0 and vx = 0
double v_y(
  const double C,           // Jacobi integral
  const double x            // x-coordinate in co-rotating frame
) {

  double y = 0, vx = 0,
    r1 = sqrt((x + mu) * (x + mu) + y * y),
    r2 = sqrt((x - 1 + mu) * (x - 1 + mu) + y * y);

  double vy_sqd =
     - C + x * x + y * y + 2 * (1 - mu) / r1 + 2 * mu / r2 - vx * vx;

  if (vy_sqd < 0) {
    cerr << " Sorry, C = " << C << " too large, cannot solve for v_y"
         << endl;
    exit(EXIT_FAILURE);
  }

  return sqrt(vy_sqd);
}

int main() {
  cout << " Jupiter! The Three-Body Problem\n"
       << " -------------------------------\n"
       << " Enter mu in range [0,1]: ";
  cin >> mu;
  double t = 0, C, x, y = 0, vx = 0, vy;
  cout << " Enter x: ";
  cin >> x;
  cout << " Do you wish to specify C? Enter 1 for yes, 0 for no: ";
  bool yes;
  cin >> yes;
  if (yes) {
    cout << " Enter Jacobi Integral C: ";
    cin >> C;
    vy = v_y(C, x);
  } else {
    cout << " Enter v_y: ";
    cin >> vy;
    vy -= x;                // transform to co-rotating frame
  }

  vector<double> trv(5);    // (t, x, y, vx, vy) in co-rotating frame
  trv[0] = t;
  trv[1] = x;
  trv[2] = y;
  trv[3] = vx;
  trv[4] = vy;
  cout << " Jacobi Integral C = " << Jacobi(trv) << '\n'
       << " v_y in co-rotating frame = " << vy << endl;

  cout << " Enter number of section points: ";
  int section_points;
  cin >> section_points;
  ofstream trajectory_file("trajectory.data");
  ofstream section_file("section.data");

  RK4 rk4;
  double dt = 0.001;
  double accuracy = 1e-6;
  rk4.set_step_size(dt);
  rk4.set_accuracy(accuracy);

  int crossing = 0;
  while (true) {

    t = trv[0];
    x = trv[1] * cos(t) - trv[2] * sin(t);
    y = trv[1] * sin(t) + trv[2] * cos(t);
    trajectory_file << t << '\t' << x << '\t' << y << '\n';
    double y_old = trv[2];

    rk4.adaptive_step(f, trv);

    if (y_old < 0.0 && trv[2] >= 0.0 && trv[4] >= 0.0) {

      ++crossing;
      switch_t_and_y = true;
      double dt_save = rk4.get_step_size();

      vector<double> trv_map = trv;
      double dy = -trv_map[2];
      rk4.set_step_size(dy);
      rk4.step(f, trv_map);

      switch_t_and_y = false;
      rk4.set_step_size(dt_save);
      cout << "Crossing " << crossing << " x = " << trv_map[1]
           << " v_x = " << trv_map[3] << " Jacobi = "
           << Jacobi(trv_map) << endl;
      section_file << trv_map[1] << '\t' << trv_map[3] << '\n';
    }

    if (crossing >= section_points)
      break;

    double r = sqrt(trv[1]*trv[1] + trv[2]*trv[2]);
    if (r > 100) {
      cout << "Earth at " << r << " escaping Solar System ..." << endl;
      break;
    }
  }

  trajectory_file.close();
  section_file.close();
}
