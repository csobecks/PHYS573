//
// Find zero root of functor within interval (a,b)
//
//
#include "nr3.h"
#include "roots.h"
#include <cmath>
#include <iostream>


//
// Functor with zero root to find
//
struct Ftor {
  Doub alpha; // the parameter
  
  // Function with zero root
  Doub operator () (const Doub & x) const
  {
    // return alpha * x * x - 3.;
    return tgamma(x);
  }
  
  //
  // The constructor takes an argument that lets the user
  // set the value of alpha.
  //
  Ftor(Doub a):alpha(a) { }
};

int main()
{
  Doub a, b, alpha;
  Doub root;
  Doub err = 1.e-14;

  cout << "Enter values for a, b, alpha: " << endl;
  cin >> a >> b >> alpha;
  cout << endl;
  
  if (!cin) {
    cout << "Invalid input." << endl;
    return 0;
  }
  
  cout << "Will find zero root of function between "
       << a << " and " << b << " with alpha = " << alpha << endl;
  
  // Create the functor object with user's value of alpha
  Ftor f(alpha);
  
  cout << scientific << setprecision(14);
  
  root = rtbis(f,a,b,err);
  cout << "Zero root of function found at " << root << endl;
  
  return 0;
}
