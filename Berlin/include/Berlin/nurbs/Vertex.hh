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
#ifndef _Berlin_nurbs_Vertex_hh
#define _Berlin_nurbs_Vertex_hh

#include <Fresco/Types.hh>

namespace Berlin
{
namespace nurbs
{

inline Fresco::Vertex make_vertex(Fresco::Coord x,
                                  Fresco::Coord y,
                                  Fresco::Coord z)
{
  Fresco::Vertex v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

inline Fresco::Vertex &assign(Fresco::Vertex &v, Fresco::Coord s)
{
  v.x = v.y = v.z = s;
  return v;
}

inline Fresco::Vertex &operator+=(Fresco::Vertex &p, const Fresco::Vertex &q)
{
  p.x += q.x;
  p.y += q.y;
  p.z += q.z;
  return p;
}

inline Fresco::Vertex &operator-=(Fresco::Vertex &p, const Fresco::Vertex &q)
{
  p.x -= q.x;
  p.y -= q.y;
  p.z -= q.z;
  return p;
}

inline Fresco::Vertex &operator*=(Fresco::Vertex &v, Fresco::Coord s)
{
  v.x *= s;
  v.y *= s;
  v.z *= s;
  return v;
}

inline Fresco::Vertex &operator/=(Fresco::Vertex &v, Fresco::Coord s)
{
  v.x /= s;
  v.y /= s;
  v.z /= s;
  return v;
}

inline Fresco::Vertex operator+(const Fresco::Vertex &p,
                                const Fresco::Vertex &q)
{
  Fresco::Vertex result(p);
  return result += q;
}

inline Fresco::Vertex operator-(const Fresco::Vertex &p,
                                const Fresco::Vertex &q)
{
  Fresco::Vertex result(p);
  return result -= q;
}

inline Fresco::Vertex operator*(const Fresco::Vertex &p,
                                Fresco::Coord scalar)
{
  Fresco::Vertex result(p);
  return result *= scalar;
}

inline Fresco::Vertex operator/(const Fresco::Vertex &p,
                                Fresco::Coord scalar)
{
  Fresco::Vertex result(p);
  return result /= scalar;
}

inline Fresco::Coord scalar(const Fresco::Vertex &p,
                            const Fresco::Vertex &q)
{
  return p.x * q.x + p.y * q.y + p.z * q.z;
}

inline Fresco::Coord norm(const Fresco::Vertex &p)
{
  return std::sqrt(scalar(p, p));
}

}
}

#endif
