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

#include <Fresco/config.hh>
#include <Berlin/Allocator.hh>
#include "FigureKitImpl.hh"
#include "FigureImpl.hh"
#include "PolyFigure.hh"
#include "Figures.hh"
#include "ImageImpl.hh"
#include "Transformer.hh"

using namespace Fresco;

using namespace Berlin::FigureKit;

FigureKitImpl::FigureKitImpl(const std::string &id,
			     const Fresco::Kit::PropertySeq &p,
			     ServerContextImpl *c) :
    KitImpl(id, p, c)
{ }
FigureKitImpl::~FigureKitImpl() { }

Graphic_ptr FigureKitImpl::root(Graphic_ptr g)
{
    return
	create_and_set_body<Graphic>(new TransformAllocator(Alignment(0.5),
							    Alignment(0.5),
							    Alignment(0.5),
							    Alignment(0.5),
							    Alignment(0.5),
							    Alignment(0.5)),
				     g, "FigureKit/root");
}

Graphic_ptr FigureKitImpl::fitter(Graphic_ptr g)
{
    /* unimplemented */
    return Graphic::_duplicate(g);
}

Graphic_ptr FigureKitImpl::group()
{
    return create<Graphic>(new PolyFigure, "FigureKit/group");
}

Graphic_ptr FigureKitImpl::ugroup()
{
    return create<Graphic>(new UPolyFigure, "FigureKit/ugroup");
}

Figure::Point_ptr FigureKitImpl::point(Coord x, Coord y)
{
    Vertex v;
    v.x = x, v.y = y; v.z = 0;
    return create<Figure::Point>(new PointImpl(v), "FigureKit/point");
}

Figure::Line_ptr FigureKitImpl::line(Coord x0, Coord y0,
				     Coord x1, Coord y1)
{
    Vertex v1, v2;
    v1.x = x0, v1.y = y0, v1.z = 0;
    v2.x = x1, v2.y = y1, v2.z = 0;
    return create<Figure::Line>(new LineImpl(v1, v2), "FigureKit/line");
}

Figure::Rectangle_ptr FigureKitImpl::rectangle(Coord l, Coord t,
					       Coord r, Coord b)
{
    Vertex lower, upper;
    lower.x = l, lower.y = t, lower.z = 0;
    upper.x = r, upper.y = b, upper.z = 0;
    return create<Figure::Rectangle>(new RectangleImpl(lower, upper),
				     "FigureKit/rectangle");
}

Figure::Circle_ptr FigureKitImpl::circle(Coord x, Coord y, Coord r)
{
    Vertex center;
    center.x = x, center.y = y; center.z = 0;
    return create<Figure::Circle>(new CircleImpl(center, r),
				  "FigureKit/circle");
}

Figure::Ellipse_ptr FigureKitImpl::ellipse(Coord x, Coord y,
					   Coord r1, Coord r2)
{
    Vertex center;
    center.x = x, center.y = y, center.z = 0;
    return create<Figure::Ellipse>(new EllipseImpl(center, r1, r2),
				   "FigureKit/ellipse");
}

Figure::Path_ptr FigureKitImpl::multiline(const Fresco::Path &p)
{
  return create<Figure::Path>(new PathImpl(p, false),
			      "FigureKit/multiline");
}

Figure::Path_ptr FigureKitImpl::polygon(const Fresco::Path &p)
{
    return create<Figure::Path>(new PathImpl(p, true),
				"FigureKit/polygon");
}

Image_ptr FigureKitImpl::pixmap(Raster_ptr raster)
{
    return create<Image>(new ImageImpl(raster), "FigureKit/pixmap");
}

Graphic_ptr FigureKitImpl::texture(Graphic_ptr g, Raster_ptr raster)
{
    return create_and_set_body<Graphic>(new Texture(raster), g,
					"FigureKit/texture");
}

Graphic_ptr FigureKitImpl::transformer(Graphic_ptr g)
{
    return create_and_set_body<Graphic>(new Transformer, g,
					"FigureKit/transformer");
}


extern "C" KitImpl *load()
{
    static std::string properties[] = {"implementation", "FigureKitImpl"};
    return create_prototype<FigureKitImpl> ("IDL:fresco.org/Fresco/FigureKit:1.0", properties, 2);
}
