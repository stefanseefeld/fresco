/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Brent Fulgham <bfulgham@debian.org>
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org>
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

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include "ImageImpl.hh"

using namespace Prague;
using namespace Fresco;

Berlin::FigureKit::ImageImpl::ImageImpl(Raster_ptr r) :
  raster(RefCount_var<Fresco::Raster>::increment(r))
{
    Fresco::Raster::Info info = raster->header();
    width = info.width*10.;
    height = info.height*10.;
}
Berlin::FigureKit::ImageImpl::~ImageImpl()
{ Trace trace("ImageImpl::~ImageImpl"); }
void Berlin::FigureKit::ImageImpl::request(Fresco::Graphic::Requisition &r)
{
    r.x.defined = true;
    r.x.natural = r.x.maximum = r.x.minimum = width;
    r.x.align = 0.;
    r.y.defined = true;
    r.y.natural = r.y.maximum = r.y.minimum = height;
    r.y.align = 0.;
}

void Berlin::FigureKit::ImageImpl::draw(DrawTraversal_ptr traversal)
{
    if (!traversal->intersects_allocation()) return;
    DrawingKit_var drawing = traversal->drawing();
    drawing->draw_image(raster);
}

void Berlin::FigureKit::ImageImpl::update(const CORBA::Any &)
{
    need_redraw();
}

void Berlin::FigureKit::ImageImpl::activate_composite()
{
    raster->attach(Observer_var(_this()));
}

Berlin::FigureKit::Texture::Texture(Raster_ptr r) :
  raster(RefCount_var<Fresco::Raster>::increment(r)) { }
Berlin::FigureKit::Texture::~Texture() { }
void Berlin::FigureKit::Texture::traverse(Traversal_ptr traversal)
{ traversal->visit(Graphic_var(_this())); }
void Berlin::FigureKit::Texture::draw(DrawTraversal_ptr traversal)
{
    DrawingKit_var drawing = traversal->drawing();
    drawing->save();
    drawing->texture(raster);
    drawing->surface_fillstyle(DrawingKit::textured);
    MonoGraphic::traverse(traversal);
    drawing->restore();
}

void Berlin::FigureKit::Texture::pick(PickTraversal_ptr traversal)
{
    MonoGraphic::traverse(traversal);
}
