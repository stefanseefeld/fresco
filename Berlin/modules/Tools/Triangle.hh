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
#ifndef _Triangle_hh
#define _Triangle_hh

#include "Warsaw/config.hh"
#include "Warsaw/ToolKit.hh"
#include "Tool/Frame.hh"

class InvisibleTriangle : public Frame::Renderer
{
public:
  InvisibleTriangle(Coord t, bool f, ToolKit::Direction d) : Frame::Renderer(t, f), direction(d) {}
  virtual void draw(DrawTraversal_ptr);
private:
  ToolKit::Direction direction;
};

class BeveledTriangle : public Bevel
{
public:
  BeveledTriangle(Coord t, type s, Coord b, bool f, ToolKit::Direction d) : Bevel(t, s, b, f), direction(d) {}
  virtual void draw(DrawTraversal_ptr);
protected:
  ToolKit::Direction direction;
};

class ColoredTriangle : public ColoredFrame
{
public:
  ColoredTriangle(Coord t, const Color &c, bool f, ToolKit::Direction d) : ColoredFrame(t, c, f), direction(d) {}
  virtual void draw(DrawTraversal_ptr);
protected:
  ToolKit::Direction direction;
};

#endif /* _Triangle_hh */
