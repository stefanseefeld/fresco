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
#ifndef _Berlin_nurbs_array_hh
#define _Berlin_nurbs_array_hh

namespace Berlin
{
namespace nurbs
{

//. an STL compliant container wrapper for arrays of constant size
template<class T, std::size_t N>
class array 
{
public:
  typedef T              value_type;
  typedef T             *iterator;
  typedef const T       *const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef T             &reference;
  typedef const T       &const_reference;
  typedef std::size_t    size_type;
  typedef std::ptrdiff_t difference_type;
    
  array() {}
  array(const array<T, N> &other) { std::copy(other.begin(), other.end(), begin());}
  array(T value) { std::fill_n(begin(), N, value);}
  template <typename T2>
  array<T,N> &operator= (const array<T2,N> &rhs) 
  {
    std::copy(rhs.begin(),rhs.end(), begin());
    return *this;
  }
  void assign(const T &value) { std::fill_n(begin(), N, value);}

  iterator begin() { return my_data;}
  const_iterator begin() const { return my_data;}
  iterator end() { return my_data+N;}
  const_iterator end() const { return my_data+N;}
  
  reverse_iterator rbegin() { return reverse_iterator(end());}
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end());}
  reverse_iterator rend() { return reverse_iterator(begin());}
  const_reverse_iterator rend() const { return const_reverse_iterator(begin());}

  reference operator[](size_type i) { return my_data[i];}
  const_reference operator[](size_type i) const { return my_data[i];}

  reference front() { return my_data[0];}
  const_reference front() const { return my_data[0];}
  reference back() { return my_data[N-1];}
  const_reference back() const { return my_data[N-1];}
  
  void swap (array<T,N> &y) { std::swap_ranges(begin(),end(),y.begin());}
  const T *data() const { return my_data;}
private:
  T my_data[N];
};

template<class T, std::size_t N>
bool operator== (const array<T,N> &x, const array<T,N> &y) 
{
  return std::equal(x.begin(), x.end(), y.begin());
}

template<class T, std::size_t N>
bool operator< (const array<T,N> &x, const array<T,N> &y) 
{
  return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

template<class T, std::size_t N>
bool operator!= (const array<T,N> &x, const array<T,N> &y)
{
  return !(x==y);
}

template<class T, std::size_t N>
bool operator> (const array<T,N> &x, const array<T,N> &y)
{
  return y<x;
}

template<class T, std::size_t N>
bool operator<= (const array<T,N> &x, const array<T,N> &y)
{
  return !(y<x);
}

template<class T, std::size_t N>
bool operator>= (const array<T,N> &x, const array<T,N> &y)
{
  return !(x<y);
}

template<class T, std::size_t N>
inline void swap (array<T,N> &x, array<T,N> &y)
{
  x.swap(y);
}

}
}

#endif
