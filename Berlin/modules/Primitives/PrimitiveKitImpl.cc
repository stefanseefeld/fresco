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

#include <Warsaw/config.hh>
#include "Primitive/Root.hh"
#include "Primitive/PrimitiveKitImpl.hh"
// #include "Primitive/PolyPrimitive.hh"
#include "Primitive/Primitives.hh"
#include "Primitive/Transformer.hh"

using namespace Warsaw;

PrimitiveKitImpl::PrimitiveKitImpl(const std::string &id, const Warsaw::Kit::PropertySeq &p)
  : KitImpl(id, p) {}
PrimitiveKitImpl::~PrimitiveKitImpl() {}
Graphic_ptr PrimitiveKitImpl::root(Graphic_ptr child)
{
  GraphicImpl *g = new Root(Alignment(0.5), Alignment(0.5), Alignment(0.5), 
			    Alignment(0.5), Alignment(0.5), Alignment(0.5));
  activate(g);
  g->body(child);
  return g->_this();
}

Primitive::Geometry_ptr PrimitiveKitImpl::geometry(const Warsaw::Mesh &mesh)
{
  GeometryImpl *geometry = new GeometryImpl(mesh);
  activate(geometry);
  return geometry->_this();
}

// Primitive::Box_ptr PrimitiveKitImpl::cube(const Vertex &lower, const Vertex &upper)
// {
//   BoxImpl *box = new BoxImpl(lower, upper);
//   activate(box);
//   return box->_this();
// }

Graphic_ptr PrimitiveKitImpl::transformer(Graphic_ptr g)
{
  Transformer *transformer = new Transformer;
  activate(transformer);
  transformer->body(g);
  return transformer->_this();
}

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "PrimitiveKitImpl"};
  return create_kit<PrimitiveKitImpl> ("IDL:Warsaw/PrimitiveKit:1.0", properties, 2);
}
