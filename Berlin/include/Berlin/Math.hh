/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Berlin_Math_hh
#define _Berlin_Math_hh

#include <Fresco/config.hh>
#include <Fresco/Transform.hh>
#include <algorithm>
#include <cstdlib>
#include <cmath>

namespace Math
{

  const double pi = M_PI;
  template <class T> inline T min(T a, T b) { return a < b ? a : b; }
  template <class T> inline T max(T a, T b) { return a < b ? b : a; }

  template <class T> inline T min(T a, T b, const T &c, const T &d)
  { return min(min(a, b), min(c, d)); }
  template <class T> inline T max(T a, T b, const T &c, const T &d)
  { return max(max(a, b), max(c, d)); }

  inline float abs(float a) { return fabs(a); }
  inline double abs(double a) { return fabs(a); }
  inline int abs(int a) { return abs(a); }
  inline long abs(long a) { return labs(a); }

  template <class T> inline int round(T a)
  {
      return a > 0 ? static_cast<int>(a + 0.5) :
                     - static_cast<int>(-a + 0.5);
  }
  template <class T> inline bool equal(T a, T b, T e)
  { return a - b < e && b - a < e; }

  //. general orthogonal matrix transformation
  //. needs to be refined for perspective trafos
  inline Fresco::Vertex &operator *= (Fresco::Vertex &v,
				      const Fresco::Transform::Matrix &m)
  {
      Fresco::Coord tx = v.x;
      Fresco::Coord ty = v.y;
      v.x = m[0][0] * tx + m[0][1] * ty + m[0][2] * v.z + m[0][3];
      v.y = m[1][0] * tx + m[1][1] * ty + m[1][2] * v.z + m[1][3];
      v.z = m[2][0] * tx + m[2][1] * ty + m[2][2] * v.z + m[2][3];
      return v;
  }

} // namespace

#endif
