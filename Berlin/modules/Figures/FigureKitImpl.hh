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

#ifndef _FigureKitImpl_hh
#define _FigureKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/Figure.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

namespace Berlin 
{
  namespace FigureKit 
  {

    class FigureKitImpl : public virtual POA_Fresco::FigureKit,
			  public KitImpl
    {
      public:
	FigureKitImpl(const std::string &,
		      const Fresco::Kit::PropertySeq &,
		      ServerContextImpl *);
	virtual ~FigureKitImpl();
	virtual KitImpl *clone(const Fresco::Kit::PropertySeq &p,
			       ServerContextImpl *c)
	{ return new FigureKitImpl(repo_id(), p, c); }
	
	Fresco::Graphic_ptr root(Fresco::Graphic_ptr);
	Fresco::Graphic_ptr fitter(Fresco::Graphic_ptr);
	Fresco::Graphic_ptr group();
	Fresco::Graphic_ptr ugroup();
	
	Figure::Point_ptr point(Fresco::Coord, Fresco::Coord);
	Figure::Line_ptr line(Fresco::Coord, Fresco::Coord,
			      Fresco::Coord, Fresco::Coord);
	Figure::Rectangle_ptr rectangle(Fresco::Coord, Fresco::Coord,
					Fresco::Coord, Fresco::Coord);
	Figure::Circle_ptr circle(Fresco::Coord, Fresco::Coord,
				  Fresco::Coord);
	Figure::Ellipse_ptr ellipse(Fresco::Coord, Fresco::Coord,
				    Fresco::Coord, Fresco::Coord);
	// Figures::Path_ptr openBspline(const Figure::Vertices &);
	// Figures::Path_ptr closedBspline(const Figure::Vertices &);
	Figure::Path_ptr multiline(const Fresco::Path &);
	Figure::Path_ptr polygon(const Fresco::Path &);
	
	Fresco::Image_ptr   pixmap(Fresco::Raster_ptr);
	Fresco::Graphic_ptr texture(Fresco::Graphic_ptr, Fresco::Raster_ptr);
	Fresco::Graphic_ptr transformer(Fresco::Graphic_ptr);
    };

  } // namespace
} // namespace

#endif
