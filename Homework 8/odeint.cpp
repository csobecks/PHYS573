#include "odeint.hpp"
#include "linalg.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>

namespace cpl {

  RK4::RK4() {
    h = 0.01;
    acc = 1e-6;
  }

  void RK4::integrate(
    std::vector<double> (*flow)(     // name of flow vector function
      const std::vector<double>& y,  // dependent variable vector - input
      const double x                 // independent variable - input
    ),
    std::vector<double>& y,          // dependent variable vector - in&out
    const double x0,                 // integrate from x0
    const double x1                  // to x1
  ) {
    // adjust step direction and size
    if ((x1 - x0) * h < 0)
      h = -h;
    if ((x1 - x0) / h < 2)
      h = (x1 - x0) / 2;

    // adaptive step from x0 to x1
    int steps = 0;
    double x = x0;
    while (x < x1) {
      adaptive_step(flow, y, x);
      ++steps;
    }

    // final fixed size step
    double save = h;
    h = x1 - x;
    step(flow, y, x);
    h = save;
  }

  void RK4::integrate(
    std::vector<double> (*flow)(     // name of flow vector function
      const std::vector<double>& xy  // extended vector x & y
    ),
    std::vector<double>& xy,         // extended vector x & y - in&out
    const double Delta_x             // desired change x_final - x_initial
  ) {
    // adjust step direction and size
    if (Delta_x * h < 0)
      h = -h;
    if (Delta_x / h < 2)
      h = Delta_x / 2;

    // adaptive step from x0 to x1
    int steps = 0;
    double h_sum = 0;
    while (std::abs(h_sum) < std::abs(Delta_x)) {
      adaptive_step(flow, xy);
      h_sum += h_last;
      ++steps;
    }

    // final fixed size step
    double save = h;
    h = Delta_x - h_sum;
    step(flow, xy);
    h = save;
  }

  void RK4::step(
    std::vector<double> (*flow)(     // name of flow vector function
      const std::vector<double>& y,  // dependent variable vector - input
      const double x                 // independent variable - input
    ),
    std::vector<double>& y,          // dependent variable vector - in&out
    double& x                        // independent variable - in&out
  ) {
    std::vector<double> k1 = h * flow(y, x);
    std::vector<double> k2 = h * flow(y + 0.5 * k1, x + 0.5 * h);
    std::vector<double> k3 = h * flow(y + 0.5 * k2, x + 0.5 * h);
    std::vector<double> k4 = h * flow(y + k3, x + h);
    y += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
    x += h;
  }

  void RK4::step(
    std::vector<double> (*flow)(     // name of flow vector function
      const std::vector<double>& xy  // extended vector x & y
    ),
    std::vector<double>& xy          // extended vector x & y - in&out
  ) {
    std::vector<double> k1 = h * flow(xy);
    std::vector<double> k2 = h * flow(xy + 0.5 * k1);
    std::vector<double> k3 = h * flow(xy + 0.5 * k2);
    std::vector<double> k4 = h * flow(xy + k3);
    xy += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
  }

  void RK4::adaptive_step(
    std::vector<double> (*flow)(     // name of flow vector function
      const std::vector<double>& y,  // dependent variable vector - input
      const double x                 // independent variable - input
    ),
    std::vector<double>& y,          // dependent variable vector - in&out
    double& x                        // independent variable - in&out
  ) {
    const double SAFETY = 0.9, PGROW = -0.2, PSHRINK = -0.25,
                 ERRCON = 1.89E-4, TINY = 1.0e-30;
    int n = y.size();
    std::vector<double> y_half(n), y_full(n), Delta(n);
    std::vector<double> scale = flow(y, x);
    for (int i = 0; i < n; i++)
      scale[i] = std::abs(y[i]) + std::abs(scale[i] * h) + TINY;
    double err_max;
    while (true) {
      // take two half steps
      h /= 2;
      double x_half = x;
      y_half = y;
      step(flow, y_half, x_half);
      step(flow, y_half, x_half);
      // take full step
      h *= 2;
      double x_full = x;
      y_full = y;
      step(flow, y_full, x_full);
      // estimate error
      Delta = y_half - y_full;
      err_max = 0;
      for (int i = 0; i < n; i++)
        err_max = std::max(err_max, std::abs(Delta[i]) / scale[i]);
      err_max /= acc;
      if (err_max <= 1.0)
        break;
      double h_temp = SAFETY * h * pow(err_max, PSHRINK);
      if (h >= 0.0)
        h = std::max(h_temp, 0.1 * h);
      else
        h = std::min(h_temp, 0.1 * h);
      if (std::abs(h) == 0.0) {
        std::cerr << "RK4::adaptive_step: step size underflow\naborting ..."
                  << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    x += h;
    h_last = h;
    h *= (err_max > ERRCON ? SAFETY * pow(err_max, PGROW) : 5.0);
    y = y_half + Delta / 15.0;
  }

  void RK4::adaptive_step(
    std::vector<double> (*flow)(     // name of flow vector function
      const std::vector<double>& xy  // extended vector x & y - input
    ),
    std::vector<double>& xy          // extended vector x & y - in&out
  ) {
    const double SAFETY = 0.9, PGROW = -0.2, PSHRINK = -0.25,
                 ERRCON = 1.89E-4, TINY = 1.0e-30;
    int n = xy.size();
    std::vector<double> xy_half(n), xy_full(n), Delta(n);
    std::vector<double> scale = flow(xy);
    for (int i = 0; i < n; i++)
      scale[i] = std::abs(xy[i]) + std::abs(scale[i] * h) + TINY;
    double err_max;
    while (true) {
      // take two half steps
      h /= 2;
      xy_half = xy;
      step(flow, xy_half);
      step(flow, xy_half);
      // take full step
      h *= 2;
      xy_full = xy;
      step(flow, xy_full);
      // estimate error
      Delta = xy_half - xy_full;
      err_max = 0;
      for (int i = 0; i < n; i++)
        err_max = std::max(err_max, std::abs(Delta[i]) / scale[i]);
      err_max /= acc;
      if (err_max <= 1.0)
        break;
      double h_temp = SAFETY * h * pow(err_max, PSHRINK);
      if (h >= 0.0)
        h = std::max(h_temp, 0.1 * h);
      else
        h = std::min(h_temp, 0.1 * h);
      if (std::abs(h) == 0.0) {
        std::cerr << "RK4::adaptive_step: step size underflow\naborting ..."
                  << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    h_last = h;
    h *= (err_max > ERRCON ? SAFETY * pow(err_max, PGROW) : 5.0);
    xy = xy_half + Delta / 15.0;
  }

  void RK4::set_step_size(double h) {
    this->h = h;
  }

  double RK4::get_step_size() {
    return h;
  }

  void RK4::set_accuracy(double acc) {
    this->acc = acc;
  }

  double RK4::get_accuracy() {
    return acc;
  }

}  /* end namespace cpl */
