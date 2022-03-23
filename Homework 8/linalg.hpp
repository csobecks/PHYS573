#ifndef LINALG_HPP_INCLUDED
#define LINALG_HPP_INCLUDED

#include <cassert>
#include <vector>

namespace cpl {

  // -- addition or subtraction of vectors ------------------------------------

  template< typename T >               // unary +
  std::vector<T> operator+(
    const std::vector<T>& v
  ) {
    return v;
  }

  template< typename T >               // unary -
  std::vector<T> operator-(
    const std::vector<T>& v
  ) {
    std::vector<T> neg;
    for (int i = 0; i < v.size(); i++)
      neg[i] = -v[i];
    return neg;
  }

  template< typename T >               // binary + like vectors
  std::vector<T> operator+(
    const std::vector<T>& v1,
    const std::vector<T>& v2
  ) {
    assert(v1.size() == v2.size() && "v1 + v2: size() not equal");
    std::vector<T> sum;
    for (int i = 0; i < v1.size(); i++)
      sum.push_back(v1[i] + v2[i]);
    return sum;
  }

  template< typename T >               // binary - like vectors
  std::vector<T> operator-(
    const std::vector<T>& v1,
    const std::vector<T>& v2
  ) {
    assert(v1.size() == v2.size() && "v1 - v2: size() not equal");
    std::vector<T> sum;
    for (int i = 0; i < v1.size(); i++)
      sum.push_back(v1[i] - v2[i]);
    return sum;
  }

  template< typename T >               // += like vectors
  std::vector<T>& operator+=(
    std::vector<T>& v1,
    const std::vector<T>& v2
  ) {
    assert(v1.size() == v2.size() && "v1 += v2: size() not equal");
    for (int i = 0; i < v1.size(); i++)
      v1[i] += v2[i];
    return v1;
  }

  template< typename T >               // -= like vectors
  std::vector<T>& operator-=(
    std::vector<T>& v1,
    const std::vector<T>& v2
  ) {
    assert(v1.size() == v2.size() && "v1 -= v2: size() not equal");
    for (int i = 0; i < v1.size(); i++)
      v1[i] -= v2[i];
    return v1;
  }

  // -- multiply or divide a vector by a scalar -------------------------------

  template< typename S, typename T >
  std::vector<T> operator*(
    const S s,
    const std::vector<T>& v
  ) {
    std::vector<T> sv;
    for (int i = 0; i < v.size(); i++)
      sv.push_back(s * v[i]);
    return sv;
  }

  template< typename S, typename T >
  std::vector<T> operator*(
    const std::vector<T>& v,
    const S s
  ) {
    std::vector<T> vs;
    for (int i = 0; i < v.size(); i++)
      vs.push_back(v[i] * s);
    return vs;
  }

  template< typename S, typename T >
  std::vector<T> operator/(
    const std::vector<T>& v,
    const S s
  ) {
    std::vector<T> vds;
    for (int i = 0; i < v.size(); i++)
      vds.push_back(v[i] / s);
    return vds;
  }

  template< typename S, typename T >
  std::vector<T>& operator*=(
    std::vector<T>& v,
    const S s
  ) {
    for (int i = 0; i < v.size(); i++)
      v[i] *= s;
    return v;
  }

  template< typename S, typename T >
  std::vector<T>& operator/=(
    std::vector<T>& v,
    const S s
  ) {
    for (int i = 0; i < v.size(); i++)
      v[i] /= s;
    return v;
  }

} /* end namespace cpl */

#endif /* LINALG_HPP_INCLUDED */
