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
#ifndef _Berlin_TransformImpl_hh
#define _Berlin_TransformImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Transform.hh>
#include <Berlin/ServantBase.hh>
#include <Berlin/Provider.hh>

class TransformImpl;
template <> struct Initializer<TransformImpl>;

class TransformImpl : public virtual POA_Fresco::Transform,
		      public virtual ServantBase
{
  friend class Provider<TransformImpl>;
  friend class Initializer<TransformImpl>;
public:
  TransformImpl();
  TransformImpl(const TransformImpl &);
  TransformImpl(Fresco::Transform_ptr t) : _this_valid (false) { copy(t);}
  TransformImpl(Fresco::Transform::Matrix m);
  virtual ~TransformImpl();
  TransformImpl &operator = (const TransformImpl &);
  virtual void copy(Fresco::Transform_ptr);
  virtual void load_identity();
  virtual void load_matrix(const Fresco::Transform::Matrix);
  virtual void store_matrix(Fresco::Transform::Matrix);
  virtual CORBA::Boolean equal(Fresco::Transform_ptr);
  virtual CORBA::Boolean identity();
  virtual CORBA::Boolean translation();
  virtual CORBA::Boolean det_is_zero();
  virtual void scale(const Fresco::Vertex &);
  virtual void rotate(CORBA::Double, Fresco::Axis);
  virtual void translate(const Fresco::Vertex &);
  virtual void premultiply(Fresco::Transform_ptr);
  virtual void postmultiply(Fresco::Transform_ptr);
  virtual void invert();
  virtual void transform_vertex(Fresco::Vertex &);
  virtual void inverse_transform_vertex(Fresco::Vertex &);

  Fresco::Transform::Matrix &matrix() { return _matrix;}
  const Fresco::Transform::Matrix &matrix() const { return _matrix;}

  Fresco::Transform_ptr _this()
  {
    if (!_this_valid)
      {
	__this = POA_Fresco::Transform::_this ();
	_this_valid = true;
      }
    return Fresco::Transform::_duplicate (__this);
  }

  // Allow for quicker traversals (test)
  void set_and_premult(TransformImpl* set, Fresco::Transform_ptr mult);

private:
  void init();
  void modified() { _dirty = true;}
  void recompute();
  Fresco::Coord det();
  Fresco::Transform::Matrix _matrix;
  bool _dirty       : 1;
  bool _identity    : 1;
  bool _translation : 1;
  bool _xy          : 1;
  bool _this_valid  : 1;
  bool _active      : 1;

  Fresco::Transform_var __this;
};

template <> struct Initializer<TransformImpl>
{
  static void initialize(TransformImpl *t) { t->init();}
};

#endif
