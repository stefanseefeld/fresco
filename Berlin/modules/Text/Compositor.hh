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
#ifndef _TextKit_Compositor_hh
#define _TextKit_Compositor_hh

#include <Fresco/config.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/Region.hh>

class RegionImpl;

namespace Berlin
{
  namespace TextKit
  {
    
    //. this is a strategy object for adjusting text layouts to compensate
    // for font misses or hinting. It plays a very similar role to a
    // LayoutManager.
    class Compositor
    {
      public:
    typedef RegionImpl **Allocations;
    virtual ~Compositor() { }
    virtual void request(long n,
                 Fresco::Graphic::Requisition *requests,
                 Fresco::DrawingKit_ptr dk,
                 Fresco::Graphic::Requisition &result) = 0;
    virtual void allocate(long n,
                  Fresco::Graphic::Requisition *requests,
                  Fresco::DrawingKit_ptr dk,
                  Fresco::Region_ptr given,
                  Allocations result) = 0;
    static void set_span(RegionImpl *r, Fresco::Axis a,
                 Fresco::Coord origin, Fresco::Coord length,
                 Fresco::Alignment align);
    static Fresco::Coord
    compute_length(const Fresco::Graphic::Requirement &,
               const Fresco::Region::Allotment &);
    static Fresco::Coord
    compute_squeeze(const Fresco::Graphic::Requirement &, 
            Fresco::Coord);
    };

    //. left to right compositor -- aligns vertically, tiles left to right
    //. for now it ignores the DrawingKit parameter and does no
    //. compensation no line breaking.
    class LRCompositor : public Compositor
    {
      public:
    virtual void request(long, Fresco::Graphic::Requisition *,
                 Fresco::DrawingKit_ptr,
                 Fresco::Graphic::Requisition &);
    virtual void allocate(long, Fresco::Graphic::Requisition *,
                  Fresco::DrawingKit_ptr, Fresco::Region_ptr,
                  Allocations);    
      private:
    Fresco::Graphic::Requisition my_requisition;
    };

    //. top to button compositor -- aligns horizontally, tiles top to
    //. bottom for now it ignores the DrawingKit parameter and does no
    //. compensation no line breaking.
    class TBCompositor : public Compositor
    {
      public:
    virtual void request(long, Fresco::Graphic::Requisition *,
                 Fresco::DrawingKit_ptr,
                 Fresco::Graphic::Requisition &);
    virtual void allocate(long, Fresco::Graphic::Requisition *,
                  Fresco::DrawingKit_ptr, Fresco::Region_ptr,
                  Allocations);    
      private:
    Fresco::Graphic::Requisition my_requisition;
    };

  } // namespace
} // namespace

#endif
