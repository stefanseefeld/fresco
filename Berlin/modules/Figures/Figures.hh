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
#ifndef _Figures_hh
#define _Figures_hh

#include "FigureImpl.hh"

namespace Berlin
{
  namespace FigureKit
  {

    class PointImpl : public virtual POA_Figure::Point,
		      public FigureImpl
    {
      public:
	PointImpl();
	PointImpl(const Fresco::Vertex &);
	PointImpl(const PointImpl &);
	virtual ~PointImpl();
	virtual Fresco::Vertex pt();
	virtual void pt(const Fresco::Vertex &);
    };
  
    class LineImpl : public virtual POA_Figure::Line,
		     public FigureImpl
    {
      public:
	LineImpl();
	LineImpl(const Fresco::Vertex &, const Fresco::Vertex &);
	LineImpl(const LineImpl &);
	virtual ~LineImpl();
	virtual Fresco::Vertex pt1();
	virtual void pt1(const Fresco::Vertex &);
	virtual Fresco::Vertex pt2();
	virtual void pt2(const Fresco::Vertex &);
    };
    
    class RectangleImpl : public virtual POA_Figure::Rectangle,
			  public FigureImpl
    {
      public:
	RectangleImpl();
	RectangleImpl(const Fresco::Vertex &, const Fresco::Vertex &);
	RectangleImpl(const RectangleImpl &);
	virtual ~RectangleImpl();
	virtual Fresco::Vertex pt1();
	virtual void pt1(const Fresco::Vertex &);
	virtual Fresco::Vertex pt2();
	virtual void pt2(const Fresco::Vertex &);
    };
    
    class CircleImpl : public virtual POA_Figure::Circle,
		       public FigureImpl
    {
      public:
	CircleImpl();
	CircleImpl(const Fresco::Vertex &, Fresco::Coord);
	CircleImpl(const CircleImpl &);
	virtual ~CircleImpl();
	virtual void resize();
	virtual Fresco::Vertex center();
	virtual void center(const Fresco::Vertex &);
	virtual Fresco::Coord radius();
	virtual void radius(Fresco::Coord);
      protected:
	Fresco::Vertex my_center;
	Fresco::Coord  my_radius;
    };
    
    class EllipseImpl : public virtual POA_Figure::Ellipse,
			public FigureImpl
    {
      public:
	EllipseImpl();
	EllipseImpl(const Fresco::Vertex &, Fresco::Coord, Fresco::Coord);
	EllipseImpl(const EllipseImpl &);
	virtual ~EllipseImpl();
	virtual void resize();
	virtual Fresco::Vertex center();
	virtual void center(const Fresco::Vertex &);
	virtual Fresco::Coord radius1();
	virtual void radius1(Fresco::Coord);
	virtual Fresco::Coord radius2();
	virtual void radius2(Fresco::Coord);
      protected:
	Fresco::Vertex my_center;
	Fresco::Coord  my_radius1;
	Fresco::Coord  my_radius2;
    };
    
    class PathImpl : public virtual POA_Figure::Path,
		     public FigureImpl
    {
      public:
	PathImpl(bool);
	PathImpl(const Fresco::Path &, bool);
	PathImpl(const PathImpl &);
	virtual ~PathImpl();
	virtual void resize();
	Fresco::Path *handles();
	void handles(const Fresco::Path &);
	CORBA::Boolean closed();
      private:
	Fresco::Path_var my_handles;
	bool             my_closed;
    };

  } // namespace
} // namespace

#endif
