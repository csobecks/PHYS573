#ifndef ODEINT_HPP_INCLUDED
#define ODEINT_HPP_INCLUDED

#include <iostream>
#include <vector>

namespace cpl {

  // This class implements the fourth order Runge Kutta algorithm with
  // adaptive step size control from Numerical Recipes 2nd edition

  class RK4 {
  public:

    RK4();    // constructor

    /*
      The following two member functions solve a system of first
      order differential equations, described by the vector function
      "flow", from "start" to "end" values of the independent
      variable, given the initial "solution" vector. The first form
      assumes "flow" depends on the solution vector, and the second
      form assumes that "flow" depends also on the independent
      variable. An adaptive algorithm is used in which the step size
      is adjusted at each step to maintain the desired accuracy.
    */

    void integrate(
      std::vector<double> (*flow)(     // name of flow vector function
        const std::vector<double>& y,  // dependent variable vector - input
        const double x                 // independent variable - input
      ),
      std::vector<double>& y,          // dependent variable vector - in&out
      const double x0,                 // integrate from x0
      const double x1                  // to x1
    );

    void integrate(
      std::vector<double> (*flow)(     // name of flow vector function
        const std::vector<double>& xy  // extended vector x & y
      ),
      std::vector<double>& xy,         // extended vector x & y - in&out
      const double Delta_x             // desired change x_final - x_initial
    );

    // The following functions take a single RK4 step of fixed step size

    void step(
      std::vector<double> (*flow)(     // name of flow vector function
        const std::vector<double>& y,  // dependent variable vector - input
        const double x                 // independent variable - input
      ),
      std::vector<double>& y,          // dependent variable vector - in&out
      double& x                        // independent variable - in&out
    );

    void step(
      std::vector<double> (*flow)(     // name of flow vector function
        const std::vector<double>& xy  // extended vector x & y
      ),
      std::vector<double>& xy          // extended vector x & y - in&out
    );

    // The following functions take a single RK4 step of fixed step size

    void adaptive_step(
      std::vector<double> (*flow)(     // name of flow vector function
        const std::vector<double>& y,  // dependent variable vector - input
        const double x                 // independent variable - input
      ),
      std::vector<double>& y,          // dependent variable vector - in&out
      double& x                        // independent variable - in&out
    );

    void adaptive_step(
      std::vector<double> (*flow)(     // name of flow vector function
        const std::vector<double>& xy  // extended vector x & y - input
      ),
      std::vector<double>& xy          // extended vector x & y - in&out
    );

    // The following functions set/get integration parameter

    void set_step_size(double);        // suggested size of next step

    double get_step_size();

    void set_accuracy(double);         // accuracy for adaptive step

    double get_accuracy();

  private:

    double h;            // step size
    double acc;          // desired accuracy
    double h_last;       // size of most recent adaptive step

  };

}  /* end namespace cpl */

#endif /* ODEINT_HPP_INCLUDED */
