/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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

#include <Warsaw/config.hh>
#include <Berlin/Allocator.hh>
#include "Figure/FigureKitImpl.hh"
#include "Figure/FigureImpl.hh"
#include "Figure/PolyFigure.hh"
#include "Figure/Figures.hh"
#include "Figure/ImageImpl.hh"
#include "Figure/Transformer.hh"

using namespace Figures;

FigureKitImpl::FigureKitImpl(KitFactory *f, const PropertySeq &p) : KitImpl(f, p) {}
FigureKitImpl::~FigureKitImpl()
{
  for (vector<PortableServer::Servant>::iterator i = figures.begin(); i != figures.end(); ++i)
    deactivate(*i);
}

Graphic_ptr FigureKitImpl::root(Graphic_ptr child)
{
  GraphicImpl *g = activate(new TransformAllocator(Alignment(0.5), Alignment(0.5), Alignment(0.5), 
						   Alignment(0.5), Alignment(0.5), Alignment(0.5)));
  g->body(child);
  figures.push_back(g);
  return g->_this();
}

Graphic_ptr FigureKitImpl::fitter(Graphic_ptr g)
{
  /* unimplemented */
  return Graphic::_duplicate(g);
}

Graphic_ptr FigureKitImpl::group()
{
  PolyFigure *pf = activate(new PolyFigure);
  figures.push_back(pf);
  return pf->_this();
}

Graphic_ptr FigureKitImpl::ugroup()
{
  UPolyFigure *pf = activate(new UPolyFigure);
  figures.push_back(pf);
  return pf->_this();
}

Point_ptr FigureKitImpl::point(Coord x, Coord y)
{
  Vertex v;
  v.x = x, v.y = y;
  PointImpl *pt = activate(new PointImpl(v));
  figures.push_back(pt);
  return pt->_this();
}

Line_ptr FigureKitImpl::line(Coord x0, Coord y0, Coord x1, Coord y1)
{
  Vertex v1, v2;
  v1.x = x0, v1.y = y0;
  v2.x = x1, v2.y = y1;
  LineImpl *l = activate(new LineImpl(v1, v2));
  figures.push_back(l);
  return l->_this();
}

Rectangle_ptr FigureKitImpl::rectangle(Coord l, Coord t, Coord r, Coord b)
{
  Vertex lower, upper;
  lower.x = l, lower.y = t;
  upper.x = r, upper.y = b;
  RectangleImpl *rect = activate(new RectangleImpl(lower, upper));
  figures.push_back(rect);
  return rect->_this();
}

Circle_ptr FigureKitImpl::circle(Coord x, Coord y, Coord r)
{
  Vertex center;
  center.x = x, center.y = y;
  CircleImpl *c = activate(new CircleImpl(center, r));
  figures.push_back(c);
  return c->_this();
}

Ellipse_ptr FigureKitImpl::ellipse(Coord x, Coord y, Coord r1, Coord r2)
{
  Vertex center;
  center.x = x, center.y = y;
  EllipseImpl *e = activate(new EllipseImpl(center, r1, r2));
  figures.push_back(e);
  return e->_this();
}

Path_ptr FigureKitImpl::multiline(const Figure::Vertices &v)
{
  PathImpl *p = activate(new PathImpl(v));
  figures.push_back(p);
  return p->_this();
}

Path_ptr FigureKitImpl::polygon(const Figure::Vertices &v)
{
  PathImpl *p = activate(new PathImpl(v));
  figures.push_back(p);
  return p->_this();
}

Image_ptr FigureKitImpl::pixmap(Raster_ptr raster)
{
  ImageImpl *image = activate(new ImageImpl(raster));
  figures.push_back(image);
  return image->_this();
}

Graphic_ptr FigureKitImpl::texture(Graphic_ptr g, Raster_ptr raster)
{
  Texture *t = activate(new Texture(raster));
  t->body(g);
  figures.push_back(t);
  return t->_this();
}

Graphic_ptr FigureKitImpl::transformer(Graphic_ptr g)
{
  Transformer *transformer = activate(new Transformer);
  figures.push_back(transformer);
  transformer->body(g);
  return transformer->_this();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "FigureKitImpl"};
  return new KitFactoryImpl<FigureKitImpl> (FigureKit::_PD_repoId, properties, 1);
}
