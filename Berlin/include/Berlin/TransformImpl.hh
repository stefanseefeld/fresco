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
#ifndef _TransformImpl_h
#define _TransformImpl_h

#include <Warsaw/config.hh>
#include <Warsaw/Transform.hh>
#include <Berlin/ServantBase.hh>
#include <Berlin/Provider.hh>

class TransformImpl : public virtual POA_Warsaw::Transform,
		      public virtual ServantBase
{
public:
  TransformImpl();
  TransformImpl(Warsaw::Transform_ptr t) { copy(t);}
  TransformImpl(Warsaw::Transform::Matrix m);
  virtual ~TransformImpl();

  virtual void copy(Warsaw::Transform_ptr);
  virtual void load_identity();
  virtual void load_matrix(const Warsaw::Transform::Matrix);
  virtual void store_matrix(Warsaw::Transform::Matrix);
  virtual CORBA::Boolean equal(Warsaw::Transform_ptr);
  virtual CORBA::Boolean identity();
  virtual CORBA::Boolean translation();
  virtual CORBA::Boolean det_is_zero();
  virtual void scale(const Warsaw::Vertex &);
  virtual void rotate(CORBA::Double, Warsaw::Axis);
  virtual void translate(const Warsaw::Vertex &);
  virtual void premultiply(Warsaw::Transform_ptr);
  virtual void postmultiply(Warsaw::Transform_ptr);
  virtual void invert();
  virtual void transform_vertex(Warsaw::Vertex &);
  virtual void inverse_transform_vertex(Warsaw::Vertex &);

  Warsaw::Transform::Matrix &matrix() { return mat;}
private:
  Warsaw::Transform::Matrix mat;
  bool valid;
  bool ident;
  bool translate_only;
  bool xy;

  void init();
  void modified() { valid = false;}
  void recompute();
  Warsaw::Coord det();
};

#endif
