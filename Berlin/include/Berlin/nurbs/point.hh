/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2003 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 */
#ifndef _Berlin_nurbs_point_hh
#define _Berlin_nurbs_point_hh

namespace Berlin
{
namespace nurbs
{

template <typename T, size_t D>
class point
{
public:
  static const size_t dimensions = D;
  point() { for(size_t i = 0; i < D; ++i) my_coords[i] = 0;}

  T &operator[](size_t i) { return my_coords[i];}
  const T &operator[](size_t i) const { return my_coords[i];}

  point<T,D> &operator+=(const point<T,D> &);
  point<T,D> &operator-=(const point<T,D> &);
  point<T,D> &operator*=(T);
  point<T,D> &operator/=(T);
private:
  T my_coords[D];
};

template <typename T, size_t D>
point<T, D> &assign(point<T, D> &p, T s) { p[0] = p[1] = p[2] = s; return p;}

template <typename T, size_t D>
point<T, D> &point<T, D>::operator+=(const point<T,D> &p)
{
  T *tmp1 = my_coords;
  const T *tmp2 = p.my_coords;
  for(size_t i = 0; i < D; ++i) *tmp1++ += *tmp2++;
  return *this;
}

template <typename T, size_t D>
point <T, D> &point<T, D>::operator-=(const point<T,D> &p)
{
  T *tmp1 = my_coords;
  const T *tmp2 = p.my_coords;
  for(size_t i = 0; i < D; ++i) *tmp1++ -= *tmp2++;
  return *this;
}

template <typename T, size_t D>
point <T, D> &point<T, D>::operator*=(T s)
{
  T *tmp1 = my_coords;
  for(size_t i = 0; i < D; ++i) *tmp1++ *= s;
  return *this;
}

template <typename T, size_t D>
point <T, D> &point<T, D>::operator/=(T s)
{
  T *tmp1 = my_coords;
  for(size_t i = 0; i < D; ++i) *tmp1++ /= s;
  return *this;
}

template <typename T, size_t D>
point<T, D> operator+(const point<T, D> &p, const point<T, D> &q)
{
  point<T, D> result(p);
  return result += q;
}

template <typename T, size_t D>
point<T, D> operator-(const point<T, D> &p, const point<T, D> &q)
{
  point<T, D> result(p);
  return result -= q;
}

template <typename T, size_t D>
point<T, D> operator*(const point<T, D> &p, T scalar)
{
  point<T, D> result(p);
  return result *= scalar;
}

template <typename T, size_t D>
point <T, D> operator/(const point<T, D> &p, T scalar)
{
  point<T, D> result(p);
  return result /= scalar;
}

template <typename T, size_t D>
T scalar(const point<T, D> &p, const point<T, D> &q)
{
  T sum = 0.;
  for(size_t i = 0; i < D; ++i) sum += p[i] * q[i];
  return sum;
}

template <typename T, size_t D>
T norm(const point<T, D> &p)
{
  return std::sqrt(scalar(p, p));
}

}
}

#endif
