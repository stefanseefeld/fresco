/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@fresco.org> 
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

#ifndef _PrimitiveKit_PrimitiveKitImpl_hh
#define _PrimitiveKit_PrimitiveKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/PrimitiveKit.hh>
#include <Fresco/Primitive.hh>
#include <Berlin/KitImpl.hh>

namespace Berlin 
{
  namespace PrimitiveKit 
  {

    class PrimitiveKitImpl : public virtual POA_Fresco::PrimitiveKit,
                 public KitImpl
    {
      public:
    PrimitiveKitImpl(const std::string &,
             const Fresco::Kit::PropertySeq &,
             ServerContextImpl *);
    virtual ~PrimitiveKitImpl();
    virtual Berlin::KitImpl *clone(const Fresco::Kit::PropertySeq &p,
                       ServerContextImpl *c)
    { return new PrimitiveKitImpl(repo_id(), p, c);}

    Fresco::Graphic_ptr root(Fresco::Graphic_ptr);
    Primitive::Geometry_ptr geometry(const Fresco::Mesh &);
    Fresco::Graphic_ptr cube();
    //Fresco::Graphic_ptr sphere();
    //Fresco::Graphic_ptr tetrahedron();
    Fresco::Graphic_ptr transformer(Fresco::Graphic_ptr);
    
    Fresco::Graphic_ptr directional_light(Fresco::Graphic_ptr,
                          const Fresco::Color &,
                          CORBA::Float,
                          const Fresco::Vertex &);
    Fresco::Graphic_ptr point_light(Fresco::Graphic_ptr,
                    const Fresco::Color &,
                    CORBA::Float,
                    const Fresco::Vertex &);
    Fresco::Graphic_ptr spot_light(Fresco::Graphic_ptr,
                       const Fresco::Color &,
                       CORBA::Float,
                       const Fresco::Vertex &,
                       const Fresco::Vertex &,
                       CORBA::Float, CORBA::Float);
    };

  } // namespace
} // namespace

#endif
