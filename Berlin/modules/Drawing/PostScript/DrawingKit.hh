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
#ifndef _PSDrawingKit_hh
#define _PSDrawingKit_hh

#include <Warsaw/config.hh>
#include <Warsaw/DrawingKit.hh>
#include <Berlin/KitImpl.hh>
#include <string>
#include <vector>
#include <iostream>

class PSDrawingKit : implements(DrawingKit), public KitImpl
{
public:
  PSDrawingKit(KitFactory *, const PropertySeq &);
  virtual ~PSDrawingKit();

  virtual void saveState();
  virtual void restoreState();
  virtual void transformation(Transform_ptr);
  virtual Transform_ptr transformation();
  virtual void clipping(Region_ptr);
  virtual Region_ptr clipping();
  virtual void foreground(const Color &);
  virtual Color foreground();
  virtual void lighting(const Color &);
  virtual Color lighting();
  virtual void pointSize(Coord);
  virtual Coord pointSize();
  virtual void lineWidth(Coord);
  virtual Coord lineWidth();
  virtual void lineEndstyle(Endstyle);
  virtual Endstyle lineEndstyle();
  virtual void surfaceFillstyle(Fillstyle);
  virtual Fillstyle surfaceFillstyle();
  virtual void texture(Raster_ptr);
  virtual Raster_ptr texture();

  virtual void fontSize(CORBA::ULong);
  virtual CORBA::ULong fontSize();
  virtual void fontWeight(CORBA::ULong);
  virtual CORBA::ULong fontWeight();
  virtual void fontFamily(const Unistring &);
  virtual Unistring *fontFamily();
  virtual void fontSubFamily(const Unistring &);
  virtual Unistring *fontSubFamily();
  virtual void fontFullName(const Unistring &);
  virtual Unistring *fontFullName();
  virtual void fontStyle(const Unistring &);
  virtual Unistring *fontStyle();
  virtual FontMetrics metrics();
  virtual CORBA::Any *getFontAttr(const Unistring &);
  virtual void fontAttr(const NVPair &);

  virtual Coord resolution(Axis);
  virtual void drawPath(const Path &);
//   virtual void drawPatch(const Patch &);
  virtual void drawRect(const Vertex &, const Vertex &);
  virtual void drawEllipse(const Vertex &, const Vertex &);
  virtual void drawImage(Raster_ptr);
  virtual void drawText(const Unistring &);
  virtual void allocateText(const Unistring &, Graphic::Requisition &);
  virtual void flush();

//   void clear(Coord, Coord, Coord, Coord);
//   Coord width() { return drawable->width();}
//   Coord height() { return drawable->height();}
 private:
};

#endif /* _PSDrawingKit_hh */
