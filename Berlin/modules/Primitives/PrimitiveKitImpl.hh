/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#ifndef _PrimitiveKitImpl_hh
#define _PrimitiveKitImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/PrimitiveKit.hh>
#include <Warsaw/Primitive.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

class PrimitiveKitImpl : public virtual POA_Warsaw::PrimitiveKit,
			 public KitImpl
{
public:
  PrimitiveKitImpl(const std::string &, const Warsaw::Kit::PropertySeq &);
  virtual ~PrimitiveKitImpl();
  virtual KitImpl *clone(const Warsaw::Kit::PropertySeq &p) { return new PrimitiveKitImpl(repo_id(), p);}

  Warsaw::Graphic_ptr root(Warsaw::Graphic_ptr);
  Primitive::Geometry_ptr geometry(const Warsaw::Mesh &);
  Warsaw::Graphic_ptr cube();
  //Warsaw::Graphic_ptr sphere();
  //Warsaw::Graphic_ptr tetrahedron();
  Warsaw::Graphic_ptr transformer(Warsaw::Graphic_ptr);

  Warsaw::Graphic_ptr directional_light(Warsaw::Graphic_ptr, const Warsaw::Color &, CORBA::Float, const Warsaw::Vertex &);
  Warsaw::Graphic_ptr point_light(Warsaw::Graphic_ptr, const Warsaw::Color &, CORBA::Float, const Warsaw::Vertex &);
  Warsaw::Graphic_ptr spot_light(Warsaw::Graphic_ptr, const Warsaw::Color &, CORBA::Float, const Warsaw::Vertex &, const Warsaw::Vertex &,
				 CORBA::Float, CORBA::Float);
};

#endif
