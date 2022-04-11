#include <complex>
#include <vector>

namespace cpl {

  // This class implements the FFT on a vector of N data points

  class FFT {
  public:

    FFT();                          // constructor

    void transform(                 // replaces data by its transform
      std::vector< std::complex<double> > &data
    );

    void inverse_transform(         // replaces data by its inverse transform
      std::vector< std::complex<double> > &data
    );

    std::vector<double> power(      // returns power spectrum of data
      const std::vector< std::complex<double> > &data
    );

  private:
    int N;
    std::vector< std::complex<double> > *f;
    bool inverse;

    void bit_reverse();
    void Danielson_Lanczos(int n);
  };

} /* end namespace cpl */
