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
#ifndef _FigureImpl_hh
#define _FigureImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Figure.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/GraphicImpl.hh>

class TransformImpl;
class RegionImpl;

namespace Berlin
{
  namespace FigureKit
  {

    class TransformFigure : public virtual POA_Figure::FigureBase,
			    public GraphicImpl
    {
      public:
	TransformFigure();
	~TransformFigure();
	virtual Fresco::Transform_ptr transformation();
	virtual void request(Fresco::Graphic::Requisition &);
	virtual void extension(const Fresco::Allocation::Info &,
			       Fresco::Region_ptr);
	virtual void pick(Fresco::PickTraversal_ptr);
	virtual void need_redraw();
	
	Figure::Mode type() { return my_mode; }
	void type(Figure::Mode m) { my_mode = m; need_redraw(); }
	Fresco::Color foreground() { return my_fg; }
	void foreground(const Fresco::Color &f) { my_fg = f; need_redraw(); }
	Fresco::Color background() { return my_bg; }
	void background(const Fresco::Color &b) { my_bg = b; need_redraw(); }

	virtual void resize();

	void copy(const TransformFigure &);
      protected:
	Figure::Mode            my_mode;
	Fresco::Color           my_fg, my_bg;
	Impl_var<TransformImpl> my_tx;
	Impl_var<RegionImpl>    my_ext;
    };
    
    class FigureImpl : public TransformFigure
    {
      public:
	FigureImpl();
	virtual ~FigureImpl();

	void add_point(Fresco::Coord, Fresco::Coord);
	void reset();
	virtual void resize();
	
	virtual void extension(const Fresco::Allocation::Info &,
			       Fresco::Region_ptr);
	virtual void draw(Fresco::DrawTraversal_ptr);
	virtual void pick(Fresco::PickTraversal_ptr);
	
	void copy(const FigureImpl &);
      protected:
	Fresco::Path_var my_path;
    };
    
  } // namespace
} // namespace

#endif
