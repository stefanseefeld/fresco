/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
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
#ifndef _TextKit_Composition_hh
#define _TextKit_Composition_hh

#include <Fresco/config.hh>
#include <Fresco/View.hh>
#include <Fresco/TextKit.hh>
#include <Berlin/PolyGraphic.hh>

namespace Berlin
{
  namespace TextKit
  {

    class Compositor;
    
    class Composition : public PolyGraphic
    {
      public:
    Composition(Fresco::DrawingKit_ptr, Compositor *);
    virtual ~Composition();
    virtual void request(Fresco::Graphic::Requisition &);
    virtual void extension(const Fresco::Allocation::Info &,
                   Fresco::Region_ptr);
    virtual void traverse(Fresco::Traversal_ptr);
    virtual void need_resize();
    virtual void need_resize(Fresco::Tag);
    virtual void allocate(Fresco::Tag,
                  const Fresco::Allocation::Info &);
      protected:
    RegionImpl **children_allocations(Fresco::Region_ptr);
    Fresco::DrawingKit_var my_canonicalDK;
    Compositor  *my_compositor;
    bool my_requested;
    Fresco::Graphic::Requisition my_requisition;
    };
    
  } // namespace
} // namespace

#endif
