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
#ifndef _Frame_hh
#define _Frame_hh

#include "Warsaw/config.hh"
#include "Warsaw/View.hh"
#include "Warsaw/Telltale.hh"
#include "Warsaw/Region.hh"
#include "Berlin/MonoGraphic.hh"

class Frame : public MonoGraphic
{
public:
  class Renderer
  {
  public:
    Renderer(Coord t, bool f) : thickness(t), fill(f) {}
    virtual void draw(DrawTraversal_ptr) = 0;
    Coord thickness;
    bool  fill;  
  };
  Frame(Coord, Renderer *);
  virtual ~Frame();
  virtual void request(Requisition &);
  virtual void traverse(Traversal_ptr);
  virtual void extension(const Allocation::Info &a, Region_ptr);
  virtual void allocate(Tag, const Allocation::Info &);

  virtual void draw(DrawTraversal_ptr traversal) { if (renderer) renderer->draw(traversal);}
protected:
  void allocateSpan(const Requirement &, Region::Allotment &, Coord, Alignment);
  Coord       thickness;
  RegionImpl *allocation;
  Renderer   *renderer;
};

class DynamicFrame : implements(View), public Frame
{
 public:
  DynamicFrame(Coord t, Telltale::Flag, Frame::Renderer *, Frame::Renderer *);
  virtual ~DynamicFrame();
  virtual void attach(Telltale_ptr);
  virtual void update(const CORBA::Any &);
 protected:
  Telltale_var telltale;
  Frame::Renderer *renderer1, *renderer2;
  bool on;
  Telltale::Flag mask;
};

class InvisibleFrame : public Frame::Renderer
{
public:
  InvisibleFrame(Coord t, bool f) : Frame::Renderer(t, f) {}
  virtual void draw(DrawTraversal_ptr);
};

class Bevel : public Frame::Renderer
{
public:
  enum type { inset, outset, convex, concav};
  Bevel(Coord t, type s, Coord b, bool f) : Frame::Renderer(t, f), style(s), bright(b) {}
  virtual void draw(DrawTraversal_ptr);
private:
  type style;
  Coord bright;
};

class ColoredFrame : public Frame::Renderer
{
public:
  ColoredFrame(Coord t, const Color &c, bool f) : Frame::Renderer(t, f), color(c) {}
  virtual void draw(DrawTraversal_ptr);
private:
  Color color;
};

#endif /* _Frame_hh */
