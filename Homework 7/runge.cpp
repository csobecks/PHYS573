#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

#define PI 3.14159

int
func (double t, const double y[], double f[],
      void *params)
{
  double c = *(double *)params;
  f[0] = y[2];
  f[1] = y[1];
  f[2] = -6*y[0]*y[1];
  return GSL_SUCCESS;
}

int
jac (double t, const double y[], double *dfdy, 
     double dfdt[], void *params)
{
  double c = *(double *)params;
  gsl_matrix_view dfdy_mat 
    = gsl_matrix_view_array (dfdy, 3, 3);
  gsl_matrix * m = &dfdy_mat.matrix; 
  gsl_matrix_set (m, 0, 0, 0.0);
  gsl_matrix_set (m, 0, 1, 0.0);
  gsl_matrix_set (m, 0, 2, 1.0);
  gsl_matrix_set (m, 1, 0, 0.0);
  gsl_matrix_set (m, 1, 1, 1.0);
  gsl_matrix_set (m, 1, 2, 0.0);
  gsl_matrix_set (m, 2, 0, -6*y[1]);
  gsl_matrix_set (m, 2, 1, -6*y[0]);
  gsl_matrix_set (m, 2, 2, 0.0);
  dfdt[0] = 0.0;
  dfdt[1] = 0.0;
  dfdt[2] = 0.0;
  return GSL_SUCCESS;
}
     
int
main (void)
{

  ofstream myfile;
  myfile.open("home7.dat");

  const gsl_odeiv_step_type * T 
    = gsl_odeiv_step_rk4;
  
  gsl_odeiv_step * s 
    = gsl_odeiv_step_alloc (T, 2);
  
  double c = 1.0;
  gsl_odeiv_system sys = {func, jac, 3, &c};
  
  double t = 0, t1 = 2*c;
  double h = 1e-2;
  double y[3] = { sin(y[0]), cos(y[0]), -sin(y[1])}, y_err[3];
  double dydt_in[3], dydt_out[3];
  
  /* initialise dydt_in from system parameters */
  GSL_ODEIV_FN_EVAL(&sys, t, y, dydt_in);
  
  while (t < t1)
    {
      int status = gsl_odeiv_step_apply (s, t, h, 
					 y, y_err, 
					 dydt_in, 
					 dydt_out, 
					 &sys);
      
      if (status != GSL_SUCCESS){break;}
      
      dydt_in[0] = dydt_out[0];
      dydt_in[1] = dydt_out[1];
      dydt_in[2] = dydt_out[2];
      
      t += h;
      
      printf ("%.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2]);
      myfile << t << " " << y[0] << " " << y[1] << " " << y[2] << endl;
    }
  
  gsl_odeiv_step_free (s);

  myfile.close();
  return 0;
}
