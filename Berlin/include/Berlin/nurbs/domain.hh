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
#ifndef _Berlin_nurbs_domain_hh
#define _Berlin_nurbs_domain_hh

#include <ostream>
#include <algorithm>
#include <cstdarg>

namespace Berlin
{
namespace nurbs
{

//. a multidimensional index
template <size_t D>
struct index
{
  index() {}
  index(const size_t *i) { std::copy(i, i + D, values);}
  index(index<D-1> rhs, size_t lhs)
  {
    std::copy(rhs.values, rhs.values + D - 1, values);
    values[D-1] = lhs;
  }
  index(const index<D> &idx) { std::copy(idx.values, idx.values + D, values);}
  index<D+1> operator[](size_t i) const { return index<D+1>(*this, i);}
  size_t values[D+1];
};

//. a domain defines a D-dimensional container of Ts
template <typename T, size_t D> 
class domain
{
public:
  typedef size_t vector_index;
  //. Helper object for indexing:
  //. Example: domain(index[1][2])
  static const nurbs::index<0> index;
  static const size_t dimensions = D;

  domain(const nurbs::index<D> &);
  domain(const size_t *);
  domain(const domain<T, D> &);
  domain<T,D> &operator=(const domain<T, D> &);
  ~domain();

  size_t size(size_t i) const { return my_sizes.values[i];}
  const size_t *sizes() const { return my_sizes.values;}
  const T *data() const { return my_data;}
  size_t length() const { return my_length;}

  const T &operator() (nurbs::index<D>) const;
  T &operator() (nurbs::index<D>);

  const T &operator[](vector_index i) const { return my_data[i];}
  T &operator[](vector_index i) { return my_data[i];}
private:
  nurbs::index<D> my_sizes;
  size_t          my_length;
  T              *my_data;
};

template <typename T, size_t D>
const nurbs::index<0> domain<T, D>::index;

template <typename T, size_t D>
domain<T, D>::domain(const nurbs::index<D> &idx)
  : my_sizes(idx)
{
  my_length = 1;
  for(size_t i = 0; i < D; ++i) my_length *= idx.values[i];
  my_data = new T[my_length];
}

template <typename T, size_t D>
domain<T, D>::domain(const size_t *idx)
  : my_sizes(idx)
{
  my_length = 1;
  for(size_t i = 0; i < D; ++i) my_length *= idx[i];
  my_data = new T[my_length];
}

template <typename T, size_t D>
domain<T, D>::domain(const domain<T, D> &m)
  : my_sizes(m.my_sizes),
    my_length(m.my_length),
    my_data(new T[my_length])
{
  std::copy(m.my_data, m.my_data + my_length, my_data);
}

template <typename T, size_t D>
domain<T, D>::~domain()
{
  delete [] my_data;
}

template <typename T, unsigned int D>
domain<T, D> &domain<T, D>::operator=(const domain<T, D> &m)
{
  my_length = m.my_length;
  my_data = m.my_data;
  my_sizes = m.my_sizes;
  return *this;
}

template<typename T, size_t D>
const T &domain<T,D>::operator()(nurbs::index<D> idx) const
{
  size_t sum = 0;
  for(size_t j = 0; j < D; ++j)
  {
    size_t prod = 1;
    for(size_t k = 0; k < j; ++k) prod *= my_sizes.values[k];
    sum += idx.values[j] * prod;  
    prod = 1;
  }
  return my_data[sum];
}

template<typename T, size_t D>
T &domain<T,D>::operator()(nurbs::index<D> idx)
{
  size_t sum = 0;
  for(size_t j = 0; j < D; ++j)
  {
    size_t prod = 1;
    for(size_t k = 0; k < j; ++k) prod *= my_sizes.values[k];
    sum += idx.values[j] * prod;  
    prod = 1;
  }
  return my_data[sum];
}

}
}

#endif
