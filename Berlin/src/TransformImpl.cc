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
#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/IO.hh>
#include "Berlin/TransformImpl.hh"
#include "Berlin/Math.hh"
#include "Berlin/Logger.hh"
#include <cassert>

static const double radians_per_degree = Math::pi / 180;
static const double tolerance = 1e-4;

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

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
	if (jp != j) for (size_t k = 0; k < N; k++)
	    swap(matrix[j][k], matrix[jp][k]);
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

TransformImpl::TransformImpl() :
    my_dirty(false),
    my_identity(true),
    my_translation(true),
    my_xy(true),
    my_this_valid(false),
    my_active(true)
{
    init();
}

TransformImpl::TransformImpl(const TransformImpl &transform) :
    my_dirty(transform.my_dirty),
    my_identity(transform.my_identity),
    my_translation(transform.my_translation),
    my_xy(transform.my_xy),
    my_this_valid(false),
    my_active(true)
{
    load_matrix(transform.my_matrix);
}

TransformImpl::TransformImpl(Fresco::Transform::Matrix matrix) :
    my_dirty(true),
    my_identity(false),
    my_translation(false),
    my_xy(false),
    my_this_valid(false),
    my_active(true)
{
    load_matrix(matrix);
}

TransformImpl::~TransformImpl() { }

TransformImpl &TransformImpl::operator = (const TransformImpl &transform)
{
    Trace trace("TransformImpl::operator =");
    load_matrix(transform.my_matrix);
    return *this;
}

void TransformImpl::init()
{
    my_matrix[0][0] = my_matrix[1][1] =
	my_matrix[2][2] = my_matrix[3][3] = 1.;
    my_matrix[0][1] = my_matrix[0][2] = my_matrix[0][3] = 0.;
    my_matrix[1][0] = my_matrix[1][2] = my_matrix[1][3] = 0.;
    my_matrix[2][0] = my_matrix[2][1] = my_matrix[2][3] = 0.;
    my_matrix[3][0] = my_matrix[3][1] = my_matrix[3][2] = 0.;
    my_identity     = true;
    my_translation  = true;
    my_xy           = true;
    my_dirty        = false;
}

void TransformImpl::recompute()
{
    my_translation = (Math::equal(my_matrix[0][0], 1., tolerance) &&
		      Math::equal(my_matrix[1][1], 1., tolerance) &&
		      Math::equal(my_matrix[2][2], 1., tolerance) &&
		      Math::equal(my_matrix[0][1], 0., tolerance) &&
		      Math::equal(my_matrix[1][0], 0., tolerance) &&
		      Math::equal(my_matrix[0][2], 0., tolerance) &&
		      Math::equal(my_matrix[2][0], 0., tolerance) &&
		      Math::equal(my_matrix[1][2], 0., tolerance) &&
		      Math::equal(my_matrix[2][1], 0., tolerance));
    my_xy          = ((my_translation ||
		       (Math::equal(my_matrix[2][2], 1., tolerance) &&
			Math::equal(my_matrix[0][2], 0., tolerance) &&
			Math::equal(my_matrix[2][0], 0., tolerance) &&
			Math::equal(my_matrix[1][2], 0., tolerance) &&
			Math::equal(my_matrix[2][1], 0., tolerance))) &&
		      Math::equal(my_matrix[2][3], 0., tolerance));
    my_identity    = (my_translation &&
		      Math::equal(my_matrix[0][3], 0., tolerance) &&
		      Math::equal(my_matrix[1][3], 0., tolerance) &&
		      Math::equal(my_matrix[2][3], 0., tolerance));
    
    my_dirty       = false;
}

Coord TransformImpl::det()
{
    double pos = 0., neg = 0., t;
    t =  my_matrix[0][0] * my_matrix[1][1] * my_matrix[2][2];
    if (t >= 0.) pos += t; else neg += t;
    t =  my_matrix[0][1] * my_matrix[1][2] * my_matrix[2][0];
    if (t >= 0.) pos += t; else neg += t;
    t =  my_matrix[0][2] * my_matrix[1][0] * my_matrix[2][1];
    if (t >= 0.) pos += t; else neg += t;
    t = -my_matrix[0][2] * my_matrix[1][1] * my_matrix[2][0];
    if (t >= 0.) pos += t; else neg += t;
    t = -my_matrix[0][1] * my_matrix[1][0] * my_matrix[2][2];
    if (t >= 0.) pos += t; else neg += t;
    t = -my_matrix[0][0] * my_matrix[1][2] * my_matrix[2][1];
    if (t >= 0.) pos += t; else neg += t;
    return pos + neg;
}

void TransformImpl::copy(Transform_ptr transform)
{
    Trace trace("TransformImpl::copy");
    if (CORBA::is_nil(transform)) init();
    else
    {
	Fresco::Transform::Matrix matrix;
	transform->store_matrix(matrix);
	load_matrix(matrix);
    }
}

void TransformImpl::load_matrix(const Fresco::Transform::Matrix matrix)
{
    Trace trace("TransformImpl::load_matrix");
    assert(my_active);
#if 0
    for (short i = 0; i != 3; i++)
	for (short j = 0; j != 4; j++)
	    _matrix[i][j] = matrix[i][j];
    my_matrix[3][0] = my_matrix[3][1] = my_matrix[3][2] = 0.,
	my_matrix[3][3] = 1.;
#else
    memcpy(&my_matrix[0][0], &matrix[0][0],
	   sizeof(Fresco::Transform::Matrix));
#endif
    modified();
}

void TransformImpl::load_identity() { init(); }

void TransformImpl::store_matrix(Fresco::Transform::Matrix matrix)
{
    Trace trace("TransformImpl::store_matrix");
    assert(my_active);
#if 0
    for (short i = 0; i != 3; i++)
	for (short j = 0; j != 4; j++)
	    matrix[i][j] = _matrix[i][j];
#else
    memcpy(&matrix[0][0], &my_matrix[0][0],
	   sizeof(Fresco::Transform::Matrix));
#endif
}

CORBA::Boolean TransformImpl::equal(Transform_ptr transform)
{
    Trace trace("TransformImpl::equal");
    if (my_dirty) recompute();
    if (my_identity) return CORBA::is_nil(transform) || transform->identity();
    if (CORBA::is_nil(transform) || transform->identity()) return false;
    Fresco::Transform::Matrix matrix;
    transform->store_matrix(matrix);
    return
	Math::equal(my_matrix[0][0], matrix[0][0], tolerance) &&
	Math::equal(my_matrix[0][1], matrix[0][1], tolerance) &&
	Math::equal(my_matrix[0][2], matrix[0][2], tolerance) &&
	Math::equal(my_matrix[0][3], matrix[0][3], tolerance) &&
	Math::equal(my_matrix[1][0], matrix[1][0], tolerance) &&
	Math::equal(my_matrix[1][1], matrix[1][1], tolerance) &&
	Math::equal(my_matrix[1][2], matrix[1][2], tolerance) &&
	Math::equal(my_matrix[1][3], matrix[1][3], tolerance) &&
	Math::equal(my_matrix[2][0], matrix[2][0], tolerance) &&
	Math::equal(my_matrix[2][1], matrix[2][1], tolerance) &&
	Math::equal(my_matrix[2][2], matrix[2][2], tolerance) &&
	Math::equal(my_matrix[2][3], matrix[2][3], tolerance);
}

CORBA::Boolean TransformImpl::identity()
{
    if (my_dirty) recompute();
    return my_identity;
}

CORBA::Boolean TransformImpl::translation()
{
    if (my_dirty) recompute();
    return my_translation;
}

CORBA::Boolean TransformImpl::det_is_zero()
{
    Coord d = det();
    return d < tolerance && d > -tolerance;
}

void TransformImpl::scale(const Vertex &v)
{
    assert(my_active);
    my_matrix[0][0] *= v.x;
    my_matrix[0][1] *= v.x;
    my_matrix[0][2] *= v.x;
    
    my_matrix[1][0] *= v.y;
    my_matrix[1][1] *= v.y;
    my_matrix[1][2] *= v.y;

    my_matrix[2][0] *= v.z;
    my_matrix[2][1] *= v.z;
    my_matrix[2][2] *= v.z;
    modified();
}

void TransformImpl::rotate(double angle, Axis a)
{
    assert(my_active);
    Coord r_angle = angle * radians_per_degree;
    Coord c = cos(r_angle);
    Coord s = sin(r_angle);
    Fresco::Transform::Matrix matrix;
    short i = 0, j = 1;
    if (a == xaxis) i = 2;
    else if (a == yaxis) j = 2;
    
    matrix[i][0] = my_matrix[i][0], matrix[i][1] = my_matrix[i][1],
	matrix[i][2] = my_matrix[i][2], matrix[i][3] = my_matrix[i][3];
    matrix[j][0] = my_matrix[j][0], matrix[j][1] = my_matrix[j][1],
	matrix[j][2] = my_matrix[j][2], matrix[j][3] = my_matrix[j][3];

    my_matrix[i][0] = c * matrix[i][0] - s * matrix[j][0];
    my_matrix[i][1] = c * matrix[i][1] - s * matrix[j][1];
    my_matrix[i][2] = c * matrix[i][2] - s * matrix[j][2];
    my_matrix[i][3] = c * matrix[i][3] - s * matrix[j][3];

    my_matrix[j][0] = s * matrix[i][0] + c * matrix[j][0];
    my_matrix[j][1] = s * matrix[i][1] + c * matrix[j][1];
    my_matrix[j][2] = s * matrix[i][2] + c * matrix[j][2];
    my_matrix[j][3] = s * matrix[i][3] + c * matrix[j][3];

    modified();
}

void TransformImpl::translate(const Vertex &v)
{
    assert(my_active);
    my_matrix[0][3] += v.x;
    my_matrix[1][3] += v.y;
    my_matrix[2][3] += v.z;
    modified();
}

void TransformImpl::premultiply(Transform_ptr transform)
{
    Trace trace("TransformImpl::premultiply");
    assert(my_active);
    if (!CORBA::is_nil(transform) && !transform->identity())
    {
	Fresco::Transform::Matrix matrix;
	transform->store_matrix(matrix);
	if (identity()) load_matrix(matrix);
	else
	{
	    for (unsigned short i = 0; i != 3; i++)
	    {
		Coord mi0 = my_matrix[i][0], mi1 = my_matrix[i][1],
		    mi2 = my_matrix[i][2], mi3 = my_matrix[i][3];
		my_matrix[i][0] = mi0 * matrix[0][0] + mi1 * matrix[1][0] +
		    mi2 * matrix[2][0] + mi3 * matrix[3][0];
		my_matrix[i][1] = mi0 * matrix[0][1] + mi1 * matrix[1][1] +
		    mi2 * matrix[2][1] + mi3 * matrix[3][1];
		my_matrix[i][2] = mi0 * matrix[0][2] + mi1 * matrix[1][2] +
		    mi2 * matrix[2][2] + mi3 * matrix[3][2];
		my_matrix[i][3] = mi0 * matrix[0][3] + mi1 * matrix[1][3] +
		    mi2 * matrix[2][3] + mi3 * matrix[3][3];
	    }
	    modified();
	}
    }
}

void TransformImpl::postmultiply(Transform_ptr transform)
{
    Trace trace("TransformImpl::postmultiply");
    assert(my_active);
    if (!CORBA::is_nil(transform) && !transform->identity())
    {
	Fresco::Transform::Matrix matrix;
	transform->store_matrix(matrix);
	if (identity()) load_matrix(matrix);
	else
	{
	    for (unsigned short i = 0; i != 4; i++)
	    {
		Coord m0i = my_matrix[0][i], m1i = my_matrix[1][i],
		    m2i = my_matrix[2][i];
		my_matrix[0][i] = matrix[0][0] * m0i + matrix[0][1] * m1i +
		    matrix[0][2] * m2i;
		my_matrix[1][i] = matrix[1][0] * m0i + matrix[1][1] * m1i +
		    matrix[2][1] * m2i;
		my_matrix[2][i] = matrix[2][0] * m0i + matrix[2][1] * m1i +
		    matrix[2][2] * m2i;
	    }
	    modified();
	}
    }
}

void TransformImpl::invert()
{
    Trace trace("TransformImpl::invert");
    assert(my_active);
    if (my_dirty) recompute();
    if (my_translation)
    {
	my_matrix[0][3] = -my_matrix[0][3];
	my_matrix[1][3] = -my_matrix[1][3];
	my_matrix[2][3] = -my_matrix[2][3];
	modified();
    }
    else
    {
	Coord d = det();
	if (Math::equal(d, 0., tolerance)) return;
	Fresco::Transform::Matrix matrix;

	matrix[0][0] = my_matrix[0][0], matrix[0][1] = my_matrix[0][1],
	    matrix[0][2] = my_matrix[0][2], matrix[0][3] = my_matrix[0][3];
	matrix[1][0] = my_matrix[1][0], matrix[1][1] = my_matrix[1][1],
	    matrix[1][2] = my_matrix[1][2], matrix[1][3] = my_matrix[1][3];
	matrix[2][0] = my_matrix[2][0], matrix[2][1] = my_matrix[2][1],
	    matrix[2][2] = my_matrix[2][2], matrix[2][3] = my_matrix[2][3];
	matrix[3][0] = 0., matrix[3][1] = 0.,
	    matrix[3][2] = 0., matrix[3][3] = 1.;


	my_matrix[0][0] =  (matrix[1][1] * matrix[2][2] -
			    matrix[1][2] * matrix[2][1]) / d;
	my_matrix[0][1] = -(matrix[0][1] * matrix[2][2] -
			    matrix[0][2] * matrix[2][1]) / d;
	my_matrix[0][2] =  (matrix[0][1] * matrix[1][2] -
			    matrix[0][2] * matrix[1][1]) / d;
	my_matrix[1][0] = -(matrix[1][0] * matrix[2][2] -
			    matrix[1][2] * matrix[2][0]) / d;
	my_matrix[1][1] =  (matrix[0][0] * matrix[2][2] -
			    matrix[0][2] * matrix[2][0]) / d;
	my_matrix[1][2] = -(matrix[0][0] * matrix[1][2] -
			    matrix[0][2] * matrix[1][0]) / d;
	my_matrix[2][0] =  (matrix[1][0] * matrix[2][1] -
			    matrix[1][1] * matrix[2][0]) / d;
	my_matrix[2][1] = -(matrix[0][0] * matrix[2][1] -
			    matrix[0][1] * matrix[2][0]) / d;
	my_matrix[2][2] =  (matrix[0][0] * matrix[1][1] -
			    matrix[0][1] * matrix[1][0]) / d;

	my_matrix[0][3] = -(matrix[0][3] * my_matrix[0][0] +
			    matrix[1][3] * my_matrix[0][1] +
			    matrix[2][3] * my_matrix[0][2]);
	my_matrix[1][3] = -(matrix[0][3] * my_matrix[1][0] +
			    matrix[1][3] * my_matrix[1][1] +
			    matrix[2][3] * my_matrix[1][2]);
	my_matrix[2][3] = -(matrix[0][3] * my_matrix[2][0] +
			    matrix[1][3] * my_matrix[2][1] +
			    matrix[2][3] * my_matrix[2][2]);

	modified();
    }
}

void TransformImpl::transform_vertex(Vertex &v)
{
    Coord tx = v.x;
    Coord ty = v.y;
    v.x = my_matrix[0][0] * tx + my_matrix[0][1] * ty +
	my_matrix[0][2] * v.z + my_matrix[0][3];
    v.y = my_matrix[1][0] * tx + my_matrix[1][1] * ty +
	my_matrix[1][2] * v.z + my_matrix[1][3];
    v.z = my_matrix[2][0] * tx + my_matrix[2][1] * ty +
	my_matrix[2][2] * v.z + my_matrix[2][3];
}

void TransformImpl::inverse_transform_vertex(Vertex &v)
{
#if 0
    size_t pivot[4];
    Coord vertex[4];
    vertex[0] = v.x;//(v.x - my_matrix[0][3]);
    vertex[1] = v.y;//(v.y - my_matrix[1][3]);
    vertex[2] = v.z;//(v.z - my_matrix[2][3]);
    vertex[3] = 0.;
    Coord lu[4][4];
    for (short i = 0; i != 4; i++)
	for (short j = 0; j != 4; j++)
	    lu[i][j] = my_matrix[i][j];
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
    tmp.x -= my_matrix[0][3];
    tmp.y -= my_matrix[1][3];
    tmp.z -= my_matrix[2][3];
    v.x = ((my_matrix[1][1] * my_matrix[2][2] -
	    my_matrix[1][2] * my_matrix[2][1]) * tmp.x -
	   (my_matrix[0][1] * my_matrix[2][2] -
	    my_matrix[0][2] * my_matrix[2][1]) * tmp.y +
	   (my_matrix[0][1] * my_matrix[1][2] -
	    my_matrix[0][2] * my_matrix[1][1]) * tmp.z) / d;
    v.y = (-(my_matrix[1][0] * my_matrix[2][2] -
	     my_matrix[1][2] * my_matrix[2][0]) * tmp.x +
	   (my_matrix[0][0] * my_matrix[2][2] -
	    my_matrix[0][2] * my_matrix[2][0]) * tmp.y -
	   (my_matrix[0][0] * my_matrix[1][2] -
	    my_matrix[0][2] * my_matrix[1][0])) / d;
    v.z = ((my_matrix[1][0] * my_matrix[2][1] -
	    my_matrix[1][1] * my_matrix[2][0]) -
	   (my_matrix[0][0] * my_matrix[2][1] -
	    my_matrix[0][1] * my_matrix[2][0]) +
	   (my_matrix[0][0] * my_matrix[1][1] -
	    my_matrix[0][1] * my_matrix[1][0])) / d;
#endif
}

void TransformImpl::set_and_premult(TransformImpl* set, Fresco::Transform_ptr mult)
{
    Trace trace("TransformImpl::set_and_premult");
//     operator = load_matrix(transform.my_matrix);
//     assert(my_active);
//     for (short i = 0; i != 3; i++)
//         for (short j = 0; j != 4; j++)
// 	    my_matrix[i][j] = matrix[i][j];
//     my_matrix[3][0] = my_matrix[3][1] = my_matrix[3][2] = 0.,
//         my_matrix[3][3] = 1.;
//     modified();
    memcpy(&my_matrix[0][0], &set->my_matrix[0][0],
	   sizeof(Fresco::Transform::Matrix));
//     if (!CORBA::is_nil(transform)) cumulative->premultiply(transform);
    if (!CORBA::is_nil(mult) && !mult->identity())
    {
	Fresco::Transform::Matrix matrix;
	mult->store_matrix(matrix);
	if (set->identity())// load_matrix(matrix);
	    memcpy(&my_matrix[0][0], &matrix[0][0],
		   sizeof(Fresco::Transform::Matrix));
	else
	{
	    for (unsigned short i = 0; i != 3; i++)
	    {
		Coord mi0 = my_matrix[i][0], mi1 = my_matrix[i][1],
		    mi2 = my_matrix[i][2], mi3 = my_matrix[i][3];
		my_matrix[i][0] = mi0 * matrix[0][0] + mi1 * matrix[1][0] +
		    mi2 * matrix[2][0] + mi3 * matrix[3][0];
		my_matrix[i][1] = mi0 * matrix[0][1] + mi1 * matrix[1][1] +
		    mi2 * matrix[2][1] + mi3 * matrix[3][1];
		my_matrix[i][2] = mi0 * matrix[0][2] + mi1 * matrix[1][2] +
		    mi2 * matrix[2][2] + mi3 * matrix[3][2];
		my_matrix[i][3] = mi0 * matrix[0][3] + mi1 * matrix[1][3] +
		    mi2 * matrix[2][3] + mi3 * matrix[3][3];
	    }
	}
    }
    modified();
}
