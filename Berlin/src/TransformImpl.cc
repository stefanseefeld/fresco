/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
 * http://www.berlin-consortium.org
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
#include "Berlin/Logger.hh"
#include <Prague/Sys/Tracer.hh>

static const double radians_per_degree = Math::pi / 180;
static const double tolerance = 1e-4;

using namespace Prague;
using namespace Warsaw;

/*
 * transformation matrices are of the form:
 *
 *        [ r00 r01 r02 tx]
 *    M = [ r10 r11 r12 ty]
 *        [ r20 r21 r22 tz]
 *        [ 0   0   0   1 ]
 */
template <size_t N>
bool LUfactor(Coord matrix[N][N], size_t pivot[N])
{
  for (size_t j = 0; j < N; j++)
    {
      size_t jp = j;
      Coord t = Math::abs(matrix[j][j]);
      for (size_t i = j + 1; i < N; i++)
	if (Math::abs(matrix[i][j]) > t)
	  {
	    jp = i;
	    t = Math::abs(matrix[i][j]);
	  }
      pivot[j] = jp;
      if (Math::equal(matrix[jp][j], 0., 1e-10)) return false;
      if (jp != j) for (size_t k = 0; k < N; k++) swap(matrix[j][k], matrix[jp][k]);
      if (j < N - 1)
        {
	  Coord scale =  1. / matrix[j][j];
	  for (size_t k = j + 1; k < N; k++)
	    matrix[k][j] *= scale;
	  for (size_t ii = j + 1; ii < N; ii++)
	    for (size_t jj = j + 1; jj < N; jj++)
	      matrix[ii][jj] -= matrix[ii][j] * matrix[j][jj];
        }
    }
  return true;
}

template <size_t N>
void LUsolve(const Coord matrix[N][N], const size_t pivot[N], Coord v[N])
{
  short ii = -1;
  Coord sum = 0.0;

  for (size_t i = 0; i < N; i++) 
    {
      sum = v[pivot[i]];
      v[pivot[i]] = v[i];
      if (ii != -1)
	for (size_t j = ii; j <= i - 1; j++) 
	  sum -= matrix[i][j] * v[j];
      else if (sum) ii = i;
      v[i] = sum;
    }
  for (short i = static_cast<short>(N) - 1; i >= 0; i--) 
    {
      sum = v[i];
      for (size_t j = i + 1; j < N; j++) 
	sum -= matrix[i][j] * v[j];
      v[i] = sum / matrix[i][i];
    }
}

TransformImpl::TransformImpl() { init();}

TransformImpl::TransformImpl(Warsaw::Transform::Matrix m)
{
  Trace trace("TransformImpl::TransformImpl(Warsaw::Transform::Matrix)");
  load_matrix(m);
  ident = false;
  translate_only = false;
  xy = true;
  valid = false;
}

TransformImpl::~TransformImpl() { }

void TransformImpl::init()
{
  mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1.;
  mat[0][1] = mat[0][2] = mat[0][3] = 0.;
  mat[1][0] = mat[1][2] = mat[1][3] = 0.;
  mat[2][0] = mat[2][1] = mat[2][3] = 0.;
  mat[3][0] = mat[3][1] = mat[3][2] = 0.;
  ident     = true;
  translate_only = true;
  xy = true;
  valid = true;
}

void TransformImpl::recompute()
{
  translate_only = (Math::equal(mat[0][0], 1., tolerance) &&
		    Math::equal(mat[1][1], 1., tolerance) &&
		    Math::equal(mat[2][2], 1., tolerance) &&
		    Math::equal(mat[0][1], 0., tolerance) &&
		    Math::equal(mat[1][0], 0., tolerance) &&
		    Math::equal(mat[0][2], 0., tolerance) &&
		    Math::equal(mat[2][0], 0., tolerance) &&
		    Math::equal(mat[1][2], 0., tolerance) &&
		    Math::equal(mat[2][1], 0., tolerance));
  ident = (translate_only &&
	   Math::equal(mat[0][3], 0., tolerance) &&
	   Math::equal(mat[1][3], 0., tolerance) &&
	   Math::equal(mat[2][3], 0., tolerance));
  valid = true;
}

Coord TransformImpl::det()
{
  double pos = 0., neg = 0., t;
  t =  mat[0][0] * mat[1][1] * mat[2][2];
  if (t >= 0.) pos += t; else neg += t;
  t =  mat[0][1] * mat[1][2] * mat[2][0];
  if (t >= 0.) pos += t; else neg += t;
  t =  mat[0][2] * mat[1][0] * mat[2][1];
  if (t >= 0.) pos += t; else neg += t;
  t = -mat[0][2] * mat[1][1] * mat[2][0];
  if (t >= 0.) pos += t; else neg += t;
  t = -mat[0][1] * mat[1][0] * mat[2][2];
  if (t >= 0.) pos += t; else neg += t;
  t = -mat[0][0] * mat[1][2] * mat[2][1];
  if (t >= 0.) pos += t; else neg += t;
  return pos + neg;
}

void TransformImpl::copy(Transform_ptr transform)
{
  Trace trace("TransformImpl::copy");
  if (CORBA::is_nil(transform)) init();
  else
    {
      Warsaw::Transform::Matrix m;
      transform->store_matrix(m);
      load_matrix(m);
    }
}

void TransformImpl::load_matrix(const Warsaw::Transform::Matrix m)
{
  Trace trace("TransformImpl::load_matrix");
  for (short i = 0; i != 3; i++)
    for (short j = 0; j != 4; j++)
      mat[i][j] = m[i][j];
  mat[3][0] = mat[3][1] = mat[3][2] = 0., mat[3][3] = 1.;
  modified();
}

void TransformImpl::load_identity() { init();}

void TransformImpl::store_matrix(Warsaw::Transform::Matrix m)
{
  Trace trace("TransformImpl::store_matrix");
  for (short i = 0; i != 3; i++)
    for (short j = 0; j != 4; j++)
      m[i][j] = mat[i][j];
  m[3][0] = m[3][1] = m[3][2] = 0., m[3][3] = 1.;
}

CORBA::Boolean TransformImpl::equal(Transform_ptr transform)
{
  Trace trace("TransformImpl::equal");
  if (!valid) recompute();
  if (ident) return CORBA::is_nil(transform) || transform->identity();
  if (CORBA::is_nil(transform) || transform->identity()) return false;
  Warsaw::Transform::Matrix m;
  transform->store_matrix(m);
  return
    Math::equal(mat[0][0], m[0][0], tolerance) &&
    Math::equal(mat[0][1], m[0][1], tolerance) &&
    Math::equal(mat[0][2], m[0][2], tolerance) &&
    Math::equal(mat[0][3], m[0][3], tolerance) &&
    Math::equal(mat[1][0], m[1][0], tolerance) &&
    Math::equal(mat[1][1], m[1][1], tolerance) &&
    Math::equal(mat[1][2], m[1][2], tolerance) &&
    Math::equal(mat[1][3], m[1][3], tolerance) &&
    Math::equal(mat[2][0], m[2][0], tolerance) &&
    Math::equal(mat[2][1], m[2][1], tolerance) &&
    Math::equal(mat[2][2], m[2][2], tolerance) &&
    Math::equal(mat[2][3], m[2][3], tolerance);
}

CORBA::Boolean TransformImpl::identity()
{
  if (!valid) recompute();
  return ident;
}

CORBA::Boolean TransformImpl::translation()
{
  if (!valid) recompute();
  return translate_only;
}

CORBA::Boolean TransformImpl::det_is_zero()
{
  Coord d = det();
  return d < tolerance && d > -tolerance;
}

void TransformImpl::scale(const Vertex &v)
{
  mat[0][0] *= v.x;
  mat[0][1] *= v.x;
  mat[0][2] *= v.x;
  
  mat[1][0] *= v.y;
  mat[1][1] *= v.y;
  mat[1][2] *= v.y;

  mat[2][0] *= v.z;
  mat[2][1] *= v.z;
  mat[2][2] *= v.z;
  modified();
}

void TransformImpl::rotate(double angle, Axis a)
{
  Coord r_angle = angle * radians_per_degree;
  Coord c = cos(r_angle);
  Coord s = sin(r_angle);
  Warsaw::Transform::Matrix m;
  short i = 0, j = 1;
  if (a == xaxis) i = 2;
  else if (a == yaxis) j = 2;

  m[i][0] = mat[i][0], m[i][1] = mat[i][1], m[i][2] = mat[i][2], m[i][3] = mat[i][3];
  m[j][0] = mat[j][0], m[j][1] = mat[j][1], m[j][2] = mat[j][2], m[j][3] = mat[j][3];

  mat[i][0] = c * m[i][0] - s * m[j][0];
  mat[i][1] = c * m[i][1] - s * m[j][1];
  mat[i][2] = c * m[i][2] - s * m[j][2];
  mat[i][3] = c * m[i][3] - s * m[j][3];

  mat[j][0] = s * m[i][0] + c * m[j][0];
  mat[j][1] = s * m[i][1] + c * m[j][1];
  mat[j][2] = s * m[i][2] + c * m[j][2];
  mat[j][3] = s * m[i][3] + c * m[j][3];

  modified();
}

void TransformImpl::translate(const Vertex &v)
{
  mat[0][3] += v.x;
  mat[1][3] += v.y;
  mat[2][3] += v.z;
  modified();
}

void TransformImpl::premultiply(Transform_ptr transform)
{
  if (!CORBA::is_nil(transform) && !transform->identity())
    {
      Warsaw::Transform::Matrix m;
      transform->store_matrix(m);
      for (unsigned short i = 0; i != 3; i++)
	{
	  Coord mi0 = mat[i][0], mi1 = mat[i][1], mi2 = mat[i][2], mi3 = mat[i][3];
	  mat[i][0] = mi0 * m[0][0] + mi1 * m[1][0] + mi2 * m[2][0] + mi3 * m[3][0];
	  mat[i][1] = mi0 * m[0][1] + mi1 * m[1][1] + mi2 * m[2][1] + mi3 * m[3][1];
	  mat[i][2] = mi0 * m[0][2] + mi1 * m[1][2] + mi2 * m[2][2] + mi3 * m[3][2];
	  mat[i][3] = mi0 * m[0][3] + mi1 * m[1][3] + mi2 * m[2][3] + mi3 * m[3][3];
	}
      modified();
    }
}    

void TransformImpl::postmultiply(Transform_ptr transform)
{
  if (!CORBA::is_nil(transform) && !transform->identity())
    {
      Warsaw::Transform::Matrix m;
      transform->store_matrix(m);
      for (unsigned short i = 0; i != 4; i++)
	{
	  Coord m0i = mat[0][i], m1i = mat[1][i], m2i = mat[2][i];
	  mat[0][i] = m[0][0] * m0i + m[0][1] * m1i + m[0][2] * m2i;
	  mat[1][i] = m[1][0] * m0i + m[1][1] * m1i + m[2][1] * m2i;
	  mat[2][i] = m[2][0] * m0i + m[2][1] * m1i + m[2][2] * m2i;
	}
      modified();
    }
}

void TransformImpl::invert()
{
  if (!valid) recompute();
  if (translate_only)
    {
      mat[0][3] = -mat[0][3];
      mat[1][3] = -mat[1][3];
      mat[2][3] = -mat[2][3];
      modified();
    }
  else
    {
      Coord d = det();
      if (Math::equal(d, 0., tolerance)) return;
      Warsaw::Transform::Matrix m;

      m[0][0] = mat[0][0], m[0][1] = mat[0][1], m[0][2] = mat[0][2], m[0][3] = mat[0][3];
      m[1][0] = mat[1][0], m[1][1] = mat[1][1], m[1][2] = mat[1][2], m[1][3] = mat[1][3];
      m[2][0] = mat[2][0], m[2][1] = mat[2][1], m[2][2] = mat[2][2], m[2][3] = mat[2][3];
      m[3][0] = 0., m[3][1] = 0., m[3][2] = 0., m[3][3] = 1.;


      mat[0][0] =  (m[1][1] * m[2][2] - m[1][2] * m[2][1]) / d;
      mat[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]) / d;
      mat[0][2] =  (m[0][1] * m[1][2] - m[0][2] * m[1][1]) / d;
      mat[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) / d;
      mat[1][1] =  (m[0][0] * m[2][2] - m[0][2] * m[2][0]) / d;
      mat[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]) / d;
      mat[2][0] =  (m[1][0] * m[2][1] - m[1][1] * m[2][0]) / d;
      mat[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]) / d;
      mat[2][2] =  (m[0][0] * m[1][1] - m[0][1] * m[1][0]) / d;

      mat[0][3] = - (m[0][3] * mat[0][0] + m[1][3] * mat[0][1] + m[2][3] * mat[0][2]);
      mat[1][3] = - (m[0][3] * mat[1][0] + m[1][3] * mat[1][1] + m[2][3] * mat[1][2]);
      mat[2][3] = - (m[0][3] * mat[2][0] + m[1][3] * mat[2][1] + m[2][3] * mat[2][2]);

      modified();
    }
}

void TransformImpl::transform_vertex(Vertex &v)
{
//   Prague::Profiler prf("TransformImpl::transform_vertex");
  Coord tx = v.x;
  Coord ty = v.y;
  v.x = mat[0][0] * tx + mat[0][1] * ty + mat[0][2] * v.z + mat[0][3];
  v.y = mat[1][0] * tx + mat[1][1] * ty + mat[1][2] * v.z + mat[1][3];
  v.z = mat[2][0] * tx + mat[2][1] * ty + mat[2][2] * v.z + mat[2][3];
}

void TransformImpl::inverse_transform_vertex(Vertex &v)
{
//   Prague::Profiler prf("TransformImpl::inverse_transform_vertex");
#if 0
  size_t pivot[4];
  Coord vertex[4];
  vertex[0] = v.x;//(v.x - mat[0][3]);
  vertex[1] = v.y;//(v.y - mat[1][3]);
  vertex[2] = v.z;//(v.z - mat[2][3]);
  vertex[3] = 0.;
  Coord lu[4][4];
  for (short i = 0; i != 4; i++)
    for (short j = 0; j != 4; j++)
      lu[i][j] = mat[i][j];
  if (LUfactor<4>(lu, pivot))
    {
      LUsolve<4>(lu, pivot, vertex);
      v.x = vertex[0];
      v.y = vertex[1];
      v.z = vertex[2];
    }
#else
  Coord d = det();
  if (Math::equal(d, 0., tolerance)) return;
  Vertex tmp = v;
  tmp.x -= mat[0][3];
  tmp.y -= mat[1][3];
  tmp.z -= mat[2][3];
  v.x = ((mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) * tmp.x -
	 (mat[0][1] * mat[2][2] - mat[0][2] * mat[2][1]) * tmp.y +
	 (mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1]) * tmp.z) / d;
  v.y = (-(mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) * tmp.x +
	 (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]) * tmp.y -
	 (mat[0][0] * mat[1][2] - mat[0][2] * mat[1][0])) / d;
  v.z = ((mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]) -
	 (mat[0][0] * mat[2][1] - mat[0][1] * mat[2][0]) +
	 (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0])) / d;
#endif
}

