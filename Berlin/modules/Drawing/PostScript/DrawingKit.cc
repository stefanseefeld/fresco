/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Drawing/PostScript/PSDrawingKit.hh"
#include <Warsaw/Transform.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/Raster.hh>
#include <strstream>
#include <iostream>

// using namespace Prague;

/*
 * this is for now an empty no-op DrawingKit
 * it might be used to measure the performance difference
 * of a DrawTraversal with and without a real DrawingKit
 */

PSDrawingKit::PSDrawingKit(KitFactory *f, const PropertySeq &p) : KitImpl(f, p) {}
PSDrawingKit::~PSDrawingKit() {}

void PSDrawingKit::saveState() {}
void PSDrawingKit::restoreState() {}

void PSDrawingKit::transformation(Transform_ptr) {}
Transform_ptr PSDrawingKit::transformation() { return Transform::_nil();}
void PSDrawingKit::clipping(Region_ptr) {}
Region_ptr PSDrawingKit::clipping() { return Region::_nil();}
void PSDrawingKit::foreground(const Color &) {}
Color PSDrawingKit::foreground() { return Color();}
void PSDrawingKit::lighting(const Color &) {}
Color PSDrawingKit::lighting() { return Color();}
void PSDrawingKit::pointSize(Coord) {}
Coord PSDrawingKit::pointSize() { return 0.;}
void PSDrawingKit::lineWidth(Coord) {}
Coord PSDrawingKit::lineWidth() { return 0.;}
void PSDrawingKit::lineEndstyle(DrawingKit::Endstyle) {}
DrawingKit::Endstyle PSDrawingKit::lineEndstyle() { return round;}
void PSDrawingKit::surfaceFillstyle(DrawingKit::Fillstyle) {}
DrawingKit::Fillstyle PSDrawingKit::surfaceFillstyle() { return solid;}
void PSDrawingKit::texture(Raster_ptr) {}
Raster_ptr PSDrawingKit::texture() { return Raster::_nil();}

void PSDrawingKit::fontSize(CORBA::ULong) {}
CORBA::ULong PSDrawingKit::fontSize() { return 0;}
void PSDrawingKit::fontWeight(CORBA::ULong) {}
CORBA::ULong PSDrawingKit::fontWeight() { return 0;}
void PSDrawingKit::fontFamily(const Unistring &) {}
Unistring *PSDrawingKit::fontFamily() { return new Unistring();}
void PSDrawingKit::fontSubFamily(const Unistring &) {}
Unistring *PSDrawingKit::fontSubFamily() { return new Unistring();}
void PSDrawingKit::fontFullName(const Unistring &) {}
Unistring *PSDrawingKit::fontFullName() { return new Unistring();}
void PSDrawingKit::fontStyle(const Unistring &) {}
Unistring *PSDrawingKit::fontStyle() { return new Unistring();}
FontMetrics PSDrawingKit::metrics() { return FontMetrics();}
CORBA::Any *PSDrawingKit::getFontAttr(const Unistring &) { return new CORBA::Any();}
void PSDrawingKit::fontAttr(const NVPair &) {}

Coord PSDrawingKit::resolution(Axis) { return 1.;}

void PSDrawingKit::drawPath(const Path &) {}
void PSDrawingKit::drawRect(const Vertex &, const Vertex &) {}
void PSDrawingKit::drawEllipse(const Vertex &, const Vertex &) {}
void PSDrawingKit::drawImage(Raster_ptr) {}
void PSDrawingKit::allocateText(const Unistring &, Graphic::Requisition &) {}
void PSDrawingKit::drawText(const Unistring &) {}

void PSDrawingKit::flush() {}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "PSDrawingKit"};
  return new KitFactoryImpl<PSDrawingKit> (interface(DrawingKit), properties, 1);
}
