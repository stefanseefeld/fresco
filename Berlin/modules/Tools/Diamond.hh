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
#ifndef _ToolKit_Diamond_hh
#define _ToolKit_Diamond_hh

#include <Fresco/config.hh>
#include <Fresco/ToolKit.hh>
#include "Frame.hh"

namespace Berlin
{
  namespace ToolKit
  {

    class InvisibleDiamond : public Frame::Renderer
    {
      public:
    InvisibleDiamond(Fresco::Coord t, bool f) :
        Frame::Renderer(t, f)
    { }
    virtual void draw(Fresco::DrawTraversal_ptr);
    };

    class BeveledDiamond : public Bevel
    {
      public:
    BeveledDiamond(Fresco::Coord t, type s, Fresco::Coord b, bool f) :
        Bevel(t, s, b, f)
    { }
    virtual void draw(Fresco::DrawTraversal_ptr);
    };

    class ColoredDiamond : public ColoredFrame
    {
      public:
    ColoredDiamond(Fresco::Coord t, const Fresco::Color &c, bool f) :
        ColoredFrame(t, c, f)
        { }
    virtual void draw(Fresco::DrawTraversal_ptr);
    };
    
  } // namespace
} // namespace

#endif
