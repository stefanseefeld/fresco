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
#ifndef _FigureImpl_hh
#define _FigureImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Figure.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/GraphicImpl.hh>

class TransformImpl;
class RegionImpl;

class TransformFigure : public virtual POA_Warsaw::Figure,
			public GraphicImpl
{
 public:
  TransformFigure();
  ~TransformFigure();
  virtual Warsaw::Transform_ptr transformation();
  virtual void request(Warsaw::Graphic::Requisition &);
  virtual void extension(const Warsaw::Allocation::Info &, Warsaw::Region_ptr);
  virtual void pick(Warsaw::PickTraversal_ptr);
  virtual void needRedraw();
  
  Warsaw::Figure::Mode type() { return mode;}
  void type(Warsaw::Figure::Mode m) { mode = m; needRedraw();}
  Warsaw::Color foreground() { return fg;}
  void foreground(const Warsaw::Color &f) { fg = f; needRedraw();}
  Warsaw::Color background() { return bg;}
  void background(const Warsaw::Color &b) { bg = b; needRedraw();}

  virtual void resize();

  void copy(const TransformFigure &);
 protected:
  Warsaw::Figure::Mode mode;
  Warsaw::Color fg, bg;
  Impl_var<TransformImpl> tx;
  Impl_var<RegionImpl> ext;
};

class FigureImpl : public TransformFigure
{
public:
  FigureImpl();
  virtual ~FigureImpl();

  void addPoint(Warsaw::Coord, Warsaw::Coord);
  void reset();
  virtual void resize();

  virtual void extension(const Warsaw::Allocation::Info &, Warsaw::Region_ptr);
  virtual void draw(Warsaw::DrawTraversal_ptr);
  virtual void pick(Warsaw::PickTraversal_ptr);

  void copy(const FigureImpl &);
protected:
  Warsaw::Figure::Vertices_var path;
  Warsaw::Figure::Vertices_var handle;
};

#endif
