#include "fft.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>

namespace cpl {

  FFT::FFT() {
    N = 0;
    f = 0;
    inverse = false;
  }

  void FFT::transform(
    std::vector< std::complex<double> > &data
  ) {
    N = data.size();
    f = &data;
    bit_reverse();
    for (int n = 1; n < N; n *= 2)
      Danielson_Lanczos(n);
    for (int i = 0; i < N; ++i)
      (*f)[i] /= std::sqrt(double(N));
  }

  void FFT::inverse_transform(
    std::vector< std::complex<double> > &data
  ) {
    inverse = true;
    transform(data);
    inverse = false;
  }

  std::vector<double> FFT::power(
    const std::vector< std::complex<double> > &data
  ) {
    std::vector<double> P(1 + N / 2);
    P[0] = std::norm(data[0]) / double(N);
    for (int i = 1; i < N / 2; i++)
      P[i] = (std::norm(data[i]) + std::norm(data[N-i])) / double(N);
    P[N/2] = std::norm(data[N/2]) / double(N);
    return P;
  }

  void FFT::bit_reverse() {
    int j = 1;
    for (int i = 1; i < N; ++i) {
      if (i < j) {
        std::complex<double> temp = (*f)[i-1];
        (*f)[i-1] = (*f)[j-1];
        (*f)[j-1] = temp;
      }
      int k = N / 2;
      while ( k < j ) {
        j -= k;
        k /= 2;
      }
      j += k;
    }
  }

  void FFT::Danielson_Lanczos(int n) {
    const double pi = 4 * atan(1.0);
    std::complex<double> W(0, pi / n);
    W = inverse ? std::exp(W) : std::exp(-W);
    std::complex<double> W_j(1, 0);
    for (int j = 0; j < n; ++j) {
      for (int i = j; i < N; i += 2 * n) {
        std::complex<double> temp = W_j * (*f)[n+i];
        (*f)[n+i] = (*f)[i] - temp;
        (*f)[i] += temp;
      }
      W_j *= W;
    }
  }

} /* end namespace cpl */

typedef std::vector<double> Vector;

inline void swap(double& a, double& b) {
  double temp = a;
  a = b;
  b = temp;
}

void nr_four1(Vector& data, const int isign) {
  int n,mmax,m,j,istep,i;
  double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;

  int nn=data.size()/2;
  n=nn << 1;
  j=1;
  for (i=1;i<n;i+=2) {
    if (j > i) {
      swap(data[j-1],data[i-1]);
      swap(data[j],data[i]);
    }
    m=nn;
    while (m >= 2 && j > m) {
      j -= m;
      m >>= 1;
    }
    j += m;
  }
  mmax=2;
  while (n > mmax) {
    istep=mmax << 1;
    theta=isign*(6.28318530717959/mmax);
    wtemp=std::sin(0.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi=std::sin(theta);
    wr=1.0;
    wi=0.0;
    for (m=1;m<mmax;m+=2) {
      for (i=m;i<=n;i+=istep) {
        j=i+mmax;
        tempr=wr*data[j-1]-wi*data[j];
        tempi=wr*data[j]+wi*data[j-1];
        data[j-1]=data[i-1]-tempr;
        data[j]=data[i]-tempi;
        data[i-1] += tempr;
        data[i] += tempi;
      }
      wr=(wtemp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtemp*wpi+wi;
    }
    mmax=istep;
  }
}

void nr_realft(Vector& data, const int isign) {
  int i,i1,i2,i3,i4;
  double c1=0.5,c2,h1r,h1i,h2r,h2i,wr,wi,wpr,wpi,wtemp,theta;

  int n=data.size();
  theta=3.141592653589793238/double(n>>1);
  if (isign == 1) {
    c2 = -0.5;
    nr_four1(data,1);
  } else {
    c2=0.5;
    theta = -theta;
  }
  wtemp=sin(0.5*theta);
  wpr = -2.0*wtemp*wtemp;
  wpi=std::sin(theta);
  wr=1.0+wpr;
  wi=wpi;
  for (i=1;i<(n>>2);i++) {
    i2=1+(i1=i+i);
    i4=1+(i3=n-i1);
    h1r=c1*(data[i1]+data[i3]);
    h1i=c1*(data[i2]-data[i4]);
    h2r= -c2*(data[i2]+data[i4]);
    h2i=c2*(data[i1]-data[i3]);
    data[i1]=h1r+wr*h2r-wi*h2i;
    data[i2]=h1i+wr*h2i+wi*h2r;
    data[i3]=h1r-wr*h2r+wi*h2i;
    data[i4]= -h1i+wr*h2i+wi*h2r;
    wr=(wtemp=wr)*wpr-wi*wpi+wr;
    wi=wi*wpr+wtemp*wpi+wi;
  }
  if (isign == 1) {
    data[0] = (h1r=data[0])+data[1];
    data[1] = h1r-data[1];
  } else {
    data[0]=c1*((h1r=data[0])+data[1]);
    data[1]=c1*(h1r-data[1]);
    nr_four1(data,-1);
  }
}

void nr_sinft(Vector& y) {
  int j;
  double sum,y1,y2,theta,wi=0.0,wr=1.0,wpi,wpr,wtemp;

  int n=y.size();
  theta=3.141592653589793238/double(n);
  wtemp=sin(0.5*theta);
  wpr= -2.0*wtemp*wtemp;
  wpi=sin(theta);
  y[0]=0.0;
  for (j=1;j<(n>>1)+1;j++) {
    wr=(wtemp=wr)*wpr-wi*wpi+wr;
    wi=wi*wpr+wtemp*wpi+wi;
    y1=wi*(y[j]+y[n-j]);
    y2=0.5*(y[j]-y[n-j]);
    y[j]=y1+y2;
    y[n-j]=y1-y2;
  }
  nr_realft(y,1);
  y[0]*=0.5;
  sum=y[1]=0.0;
  for (j=0;j<n-1;j+=2) {
    sum += y[j];
    y[j]=y[j+1];
    y[j+1]=sum;
  }
}

void nr_cosft1(Vector& y) {
  const double PI=3.141592653589793238;
  int j;
  double sum,y1,y2,theta,wi=0.0,wpi,wpr,wr=1.0,wtemp;

  int n=y.size()-1;
  Vector yy(n);
  theta=PI/n;
  wtemp=std::sin(0.5*theta);
  wpr = -2.0*wtemp*wtemp;
  wpi=std::sin(theta);
  sum=0.5*(y[0]-y[n]);
  yy[0]=0.5*(y[0]+y[n]);
  for (j=1;j<n/2;j++) {
    wr=(wtemp=wr)*wpr-wi*wpi+wr;
    wi=wi*wpr+wtemp*wpi+wi;
    y1=0.5*(y[j]+y[n-j]);
    y2=(y[j]-y[n-j]);
    yy[j]=y1-wi*y2;
    yy[n-j]=y1+wi*y2;
    sum += wr*y2;
  }
  yy[n/2]=y[n/2];
  nr_realft(yy,1);
  for (j=0;j<n;j++) y[j]=yy[j];
  y[n]=y[1];
  y[1]=sum;
  for (j=3;j<n;j+=2) {
    sum += y[j];
    y[j]=sum;
  }
}

void nr_cosft2(Vector& y, const int isign) {
  const double PI=3.141592653589793238;
  int i;
  double sum,sum1,y1,y2,ytemp,theta,wi=0.0,wi1,wpi,wpr,wr=1.0,wr1,wtemp;

  int n=y.size();
  theta=0.5*PI/n;
  wr1=std::cos(theta);
  wi1=std::sin(theta);
  wpr = -2.0*wi1*wi1;
  wpi=std::sin(2.0*theta);
  if (isign == 1) {
    for (i=0;i<n/2;i++) {
      y1=0.5*(y[i]+y[n-1-i]);
      y2=wi1*(y[i]-y[n-1-i]);
      y[i]=y1+y2;
      y[n-1-i]=y1-y2;
      wr1=(wtemp=wr1)*wpr-wi1*wpi+wr1;
      wi1=wi1*wpr+wtemp*wpi+wi1;
    }
    nr_realft(y,1);
    for (i=2;i<n;i+=2) {
      wr=(wtemp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtemp*wpi+wi;
      y1=y[i]*wr-y[i+1]*wi;
      y2=y[i+1]*wr+y[i]*wi;
      y[i]=y1;
      y[i+1]=y2;
    }
    sum=0.5*y[1];
    for (i=n-1;i>0;i-=2) {
      sum1=sum;
      sum += y[i];
      y[i]=sum1;
    }
  } else if (isign == -1) {
    ytemp=y[n-1];
    for (i=n-1;i>2;i-=2)
      y[i]=y[i-2]-y[i];
    y[1]=2.0*ytemp;
    for (i=2;i<n;i+=2) {
      wr=(wtemp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtemp*wpi+wi;
      y1=y[i]*wr+y[i+1]*wi;
      y2=y[i+1]*wr-y[i]*wi;
      y[i]=y1;
      y[i+1]=y2;
    }
    nr_realft(y,-1);
    for (i=0;i<n/2;i++) {
      y1=y[i]+y[n-1-i];
      y2=(0.5/wi1)*(y[i]-y[n-1-i]);
      y[i]=0.5*(y1+y2);
      y[n-1-i]=0.5*(y1-y2);
      wr1=(wtemp=wr1)*wpr-wi1*wpi+wr1;
      wi1=wi1*wpr+wtemp*wpi+wi1;
    }
  }
}
