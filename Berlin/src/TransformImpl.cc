/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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
#include "Berlin/TransformImpl.hh"
#include "Berlin/Math.hh"

static const double radians_per_degree = Math::pi / 180;
static const double tolerance = 1e-4;

TransformImpl::TransformImpl() { init(); }

TransformImpl::TransformImpl(Transform::Matrix m)
{
  loadMatrix(m);
  identity = false;
  translate_only = false;
  xy = true;
  valid = false;
}

TransformImpl::~TransformImpl() { }

// void TransformImpl::externalize_to_stream(CosStream::StreamIO_ptr targetStreamIO, _Ix_Env& _env) {
//     bool identical = Identity();

//     targetStreamIO->write_boolean(identical);
//     if (!identical) {
// 	for (CORBA::ULong i = 0; i < 4; i++) {
// 	    for (CORBA::ULong j = 0; j < 4; j++) {
// 		targetStreamIO->write_float(mat_[i][j]);
// 	    }
// 	}
//     }
// }

// void TransformImpl::internalize_from_stream(CosStream::StreamIO_ptr sourceStreamIO, CosLifeCycle::FactoryFinder_ptr there, _Ix_Env& _env) {
//     bool identical = sourceStreamIO->read_boolean();

//     if (!identical) {
// 	for (CORBA::ULong i = 0; i < 4; i++) {
// 	    for (CORBA::ULong j = 0; j < 4; j++) {
// 		mat_[i][j] = sourceStreamIO->read_float();
// 	    }
// 	}
// 	modified();
//     } else {
// 	load_Identity();
//     }
// }

void TransformImpl::init()
{
  mat[0][0] = mat[1][1] = Coord(1);
  mat[0][1] = Coord(0);mat[1][0] = Coord(0);
  mat[0][2] = Coord(0);mat[1][2] = Coord(0);
  mat[0][3] = Coord(0);mat[1][3] = Coord(0);
  mat[2][0] = Coord(0);mat[2][1] = Coord(0);
  mat[2][2] = Coord(0);mat[2][3] = Coord(0);
  mat[3][0] = Coord(0);mat[3][1] = Coord(0);
  mat[3][2] = Coord(0);mat[3][3] = Coord(0);
  identity     = true;
  translate_only = true;
  xy = true;
  valid = true;
}

void TransformImpl::recompute()
{
  Coord m00 = mat[0][0];
  Coord m01 = mat[0][1];
  Coord m10 = mat[1][0];
  Coord m11 = mat[1][1];
  Coord m20 = mat[2][0];
  Coord m21 = mat[2][1];
  Coord one_plus = 1 + tolerance, one_minus = 1 - tolerance;
  Coord zero_plus = 0 + tolerance, zero_minus = 0 - tolerance;
  
  translate_only = (m00 > one_minus && m00 < one_plus &&
		    m11 > one_minus && m11 < one_plus &&
		    m01 > zero_minus && m01 < zero_plus &&
		    m10 > zero_minus && m10 < zero_plus);

  identity = (translate_only &&
	   m20 > zero_minus && m20 < zero_plus &&
	   m21 > zero_minus && m21 < zero_plus);
  valid = true;
}

Coord TransformImpl::det()
{
  return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

void TransformImpl::copy(Transform_ptr t)
{
  if (CORBA::is_nil(t)) init();
  else
    {
      Transform::Matrix m;
      t->storeMatrix(m);
      loadMatrix(m);
    }
}

void TransformImpl::loadMatrix(Matrix m)
{
  mat[0][0] = m[0][0]; mat[0][1] = m[0][1];
  mat[0][2] = m[0][2]; mat[0][3] = m[0][3];
  mat[1][0] = m[1][0]; mat[1][1] = m[1][1];
  mat[1][2] = m[1][2]; mat[1][3] = m[1][3];
  mat[2][0] = m[2][0]; mat[2][1] = m[2][1];
  mat[2][2] = m[2][2]; mat[2][3] = m[2][3];
  mat[3][0] = m[3][0]; mat[3][1] = m[3][1];
  mat[3][2] = m[3][2]; mat[3][3] = m[3][3];
  modified();
}

void TransformImpl::loadIdentity() { init();}

void TransformImpl::storeMatrix(Matrix m)
{
  m[0][0] = mat[0][0]; m[0][1] = mat[0][1];
  m[0][2] = mat[0][2]; m[0][3] = mat[0][3];
  m[1][0] = mat[1][0]; m[1][1] = mat[1][1];
  m[1][2] = mat[1][2]; m[1][3] = mat[1][3];
  m[2][0] = mat[2][0]; m[2][1] = mat[2][1];
  m[2][2] = mat[2][2]; m[2][3] = mat[2][3];
  m[3][0] = mat[3][0]; m[3][1] = mat[3][1];
  m[3][2] = mat[3][2]; m[3][3] = mat[3][3];
}

CORBA::Boolean TransformImpl::equal(Transform_ptr t)
{
  if (!valid) recompute();
  if (identity) return CORBA::is_nil(t) || t->Identity();
  if (CORBA::is_nil(t) || t->Identity()) return false;
  Transform::Matrix m;
  t->storeMatrix(m);
  Coord m00 = mat[0][0];
  Coord m01 = mat[0][1];
  Coord m10 = mat[1][0];
  Coord m11 = mat[1][1];
  Coord m20 = mat[2][0];
  Coord m21 = mat[2][1];
  return (xy &&
	  m00 < m[0][0] + tolerance && m00 > m[0][0] - tolerance &&
	  m01 < m[0][1] + tolerance && m01 > m[0][1] - tolerance &&
	  m10 < m[1][0] + tolerance && m10 > m[1][0] - tolerance &&
	  m11 < m[1][1] + tolerance && m11 > m[1][1] - tolerance &&
	  m20 < m[2][0] + tolerance && m20 > m[2][0] - tolerance &&
	  m21 < m[2][1] + tolerance && m21 > m[2][1] - tolerance);
}

CORBA::Boolean TransformImpl::Identity()
{
  if (!valid) recompute();
  return identity;
}

CORBA::Boolean TransformImpl::Translation()
{
  if (!valid) recompute();
  return translate_only;
}

CORBA::Boolean TransformImpl::detIsZero()
{
  Coord d = det();
  return d < tolerance && d > -tolerance;
}

void TransformImpl::scale(const Vertex &v)
{
  mat[0][0] *= v.x;
  mat[0][1] *= v.y;
  
  mat[1][0] *= v.x;
  mat[1][1] *= v.y;
  mat[2][0] *= v.x;
  mat[2][1] *= v.y;
  modified();
}

void TransformImpl::rotate(double angle, Axis a)
{
  if (a != zaxis) return;
  Transform::Matrix m;
  Coord r_angle = Coord(angle * radians_per_degree);
  Coord tmp1 = Coord(cos(r_angle));
  Coord tmp2 = Coord(sin(r_angle));
    
  m[0][0] = tmp1 * mat[0][0];
  m[0][1] = tmp2 * mat[0][1];
  m[1][0] = tmp1 * mat[1][0];
  m[1][1] = tmp2 * mat[1][1];
  m[2][0] = tmp1 * mat[2][0];
  m[2][1] = tmp2 * mat[2][1];

  mat[0][1] = mat[0][0] * tmp2 + mat[0][1] * tmp1;
  mat[1][1] = mat[1][0] * tmp2 + mat[1][1] * tmp1;
  mat[2][1] = mat[2][0] * tmp2 + mat[2][1] * tmp1;
  mat[0][0] = m[0][0] - m[0][1];
  mat[1][0] = m[1][0] - m[1][1];
  mat[2][0] = m[2][0] - m[2][1];
  modified();
}

void TransformImpl::translate(const Vertex &v)
{
  mat[2][0] += v.x;
  mat[2][1] += v.y;
  modified();
}

void TransformImpl::premultiply(Transform_ptr t)
{
  if (!CORBA::is_nil(t) && !t->Identity())
    {
      Transform::Matrix m;
      t->storeMatrix(m);

      Coord tmp1 = mat[0][0];
      Coord tmp2 = mat[1][0];
      mat[0][0]  = m[0][0] * tmp1 + m[0][1] * tmp2;
      mat[1][0]  = m[1][0] * tmp1 + m[1][1] * tmp2;
      mat[2][0] += m[2][0] * tmp1 + m[2][1] * tmp2;
      
      tmp1 = mat[0][1];
      tmp2 = mat[1][1];
      
      mat[0][1]  = m[0][0] * tmp1 + m[0][1] * tmp2;
      mat[1][1]  = m[1][0] * tmp1 + m[1][1] * tmp2;
      mat[2][1] += m[2][0] * tmp1 + m[2][1] * tmp2;
      modified();
    }
}    

void TransformImpl::postmultiply(Transform_ptr t)
{
  if (!CORBA::is_nil(t) && !t->Identity())
    {
      Transform::Matrix m;
      t->storeMatrix(m);

      Coord tmp = mat[0][0] * m[0][1] + mat[0][1] * m[1][1];
      mat[0][0] = mat[0][0] * m[0][0] + mat[0][1] * m[1][0];
      mat[0][1] = tmp;

      tmp = mat[1][0] * m[0][1] + mat[1][1] * m[1][1];
      mat[1][0] = mat[1][0] * m[0][0] + mat[1][1] * m[1][0];
      mat[1][1] = tmp;

      tmp = mat[2][0] * m[0][1] + mat[2][1] * m[1][1];
      mat[2][0] = mat[2][0] * m[0][0] + mat[2][1] * m[1][0];
      mat[2][1] = tmp;

      mat[2][0] += m[2][0];
      mat[2][1] += m[2][1];
      modified();
    }
}

void TransformImpl::invert()
{
  if (!valid) recompute();
  if (translate_only)
    {
      mat[2][0] = -mat[2][0];
      mat[2][1] = -mat[2][1];
      modified();
    }
  else
    {
      Coord d = det();
      if (Math::equal(d, Coord(0), tolerance)) return;
      Coord t00 = mat[0][0];
      Coord t20 = mat[2][0];

      mat[2][0] = (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]) / d;
      mat[2][1] = (mat[0][1] * t20 - mat[0][0] * mat[2][1]) / d;
      mat[0][0] = mat[1][1]/d;
      mat[1][1] = t00/d;
      mat[1][0] = -mat[1][0]/d;
      mat[0][1] = -mat[0][1]/d;
      modified();
    }
}

void TransformImpl::transformVertex(Vertex &v)
{
  Coord tx = v.x;
  v.x = tx * mat[0][0] + v.y * mat[1][0] + mat[2][0];
  v.y = tx * mat[0][1] + v.y * mat[1][1] + mat[2][1];
}

void TransformImpl::inverseTransformVertex(Vertex &v)
{
  Coord d = det();
  Coord a = (v.x - mat[2][0]) / d;
  Coord b = (v.y - mat[2][1]) / d;
  v.x = a * mat[1][1] - b * mat[1][0];
  v.y = b * mat[0][0] - a * mat[0][1];
}

