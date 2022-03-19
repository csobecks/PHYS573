#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#define PI 3.141592

int
func (double t, const double y[], double f[],
      void *params)
{
  double c = *(double *)params;
  f[0] = y[1];
  f[1] = y[0]-3*y[0]*y[0];
  return GSL_SUCCESS;
}

int
jac (double t, const double y[], double *dfdy, 
     double dfdt[], void *params)
{
  double c = *(double *)params;
  gsl_matrix_view dfdy_mat 
    = gsl_matrix_view_array (dfdy, 2, 2);
  gsl_matrix * m = &dfdy_mat.matrix; 
  gsl_matrix_set (m, 0, 0, 0.0);
  gsl_matrix_set (m, 0, 1, 1.0);
  gsl_matrix_set (m, 1, 0, 1.0-6.0*y[0]);
  gsl_matrix_set (m, 1, 1, 0.0);
  dfdt[0] = 0.0;
  dfdt[1] = 0.0;
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
  
  double c = 0.022;
  gsl_odeiv_system sys = {func, jac, 2, &c};
  
  double t = 0.0, t1 = 4.0;
  double h = 1e-2;
  double y[2] = { sin(y[0]), cos(y[0]) }, y_err[2];
  double dydt_in[2], dydt_out[2];
  
  /* initialise dydt_in from system parameters */
  GSL_ODEIV_FN_EVAL(&sys, t, y, dydt_in);
  
  while (t < t1)
    {
      int status = gsl_odeiv_step_apply (s, t, h, 
					 y, y_err, 
					 dydt_in, 
					 dydt_out, 
					 &sys);
      
      if (status != GSL_SUCCESS)
	break;
      
      dydt_in[0] = dydt_out[0];
      dydt_in[1] = dydt_out[1];
      
      t += h;
      
      printf ("%.5e %.5e %.5e\n", t, y[0], y[1]);
      myfile << t << " " << y[0] << " " << y[1] << endl;
    }
  
  gsl_odeiv_step_free (s);

  myfile.close();
  return 0;
}
