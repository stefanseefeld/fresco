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
#ifndef _ToolKit_Triangle_hh
#define _ToolKit_Triangle_hh

#include <Fresco/config.hh>
#include <Fresco/ToolKit.hh>
#include "Frame.hh"

namespace Berlin
{
  namespace ToolKit
  {

    class InvisibleTriangle : public Frame::Renderer
    {
      public:
	InvisibleTriangle(Fresco::Coord t, bool f,
			  Fresco::ToolKit::Direction d) :
	    Frame::Renderer(t, f), my_direction(d)
	{ }
	virtual void draw(Fresco::DrawTraversal_ptr);
      private:
	Fresco::ToolKit::Direction my_direction;
    };

    class BeveledTriangle : public Bevel
    {
      public:
	BeveledTriangle(Fresco::Coord t, type s, Fresco::Coord b,
			bool f, Fresco::ToolKit::Direction d) :
	    Bevel(t, s, b, f), my_direction(d) { }
	virtual void draw(Fresco::DrawTraversal_ptr);
      protected:
	Fresco::ToolKit::Direction my_direction;
    };
    
    class ColoredTriangle : public ColoredFrame
    {
      public:
	ColoredTriangle(Fresco::Coord t, const Fresco::Color &c, bool f,
			Fresco::ToolKit::Direction d) :
	    ColoredFrame(t, c, f), my_direction(d)
	{ }
	virtual void draw(Fresco::DrawTraversal_ptr);
      protected:
	Fresco::ToolKit::Direction my_direction;
    };

  } // namespace
} // namespace

#endif
