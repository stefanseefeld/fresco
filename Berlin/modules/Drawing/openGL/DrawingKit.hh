/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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
#ifndef _GLDrawingKit_hh
#define _GLDrawingKit_hh

#include <Drawing/DrawingKitBase.hh>
#include <Drawing/openGL/FontServer.hh>
#include <Drawing/openGL/GLRaster.hh>
#include <Prague/Sys/Thread.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/ObjectCache.hh>
#include <Berlin/GGI.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Warsaw/Image.hh>
#include <GL/ggimesa.h>

#include <string>
#include <vector>

class GLDrawingKit : public DrawingKitBase, public KitImpl
{
public:
  GLDrawingKit(KitFactory *, const PropertySeq &);
  virtual ~GLDrawingKit();

  virtual void transformation(Transform_ptr t) { DrawingKitBase::transformation(t);}
  virtual Transform_ptr transformation() { return Transform::_duplicate(tr);}
  virtual void clipping(Region_ptr r) { DrawingKitBase::clipping(r);}
  virtual Region_ptr clipping() { return Region::_duplicate(cl);}
//   using DrawingKitBase::foreground;
  virtual void foreground(const Color &c) { DrawingKitBase::foreground(c);}
  virtual Color foreground() { return fg;}
  virtual void lighting(const Color &c) { DrawingKitBase::lighting(c);}
  virtual Color lighting() { return lt;}
  virtual void pointSize(Coord c) { DrawingKitBase::pointSize(c);}
  virtual Coord pointSize() { return ps;}
  virtual void lineWidth(Coord c) { DrawingKitBase::lineWidth(c);}
  virtual Coord lineWidth() { return lw;}
  virtual void lineEndstyle(Endstyle e) { DrawingKitBase::lineEndstyle(e);}
  virtual Endstyle lineEndstyle() { return es;}
  virtual void surfaceFillstyle(Fillstyle f) { DrawingKitBase::surfaceFillstyle(f);}
  virtual Fillstyle surfaceFillstyle() { return fs;}
  virtual void texture(Raster_ptr r) { DrawingKitBase::texture(r);}
  virtual Raster_ptr texture() { return tx ? Raster::_duplicate(tx->remote) : Raster::_nil();}

  virtual CORBA::ULong fontSize() { return fontServer.size();}
  virtual CORBA::ULong fontWeight() { return fontServer.weight();}
  virtual Unistring *fontFamily() { return new Unistring(fontServer.family());}
  virtual Unistring *fontSubFamily() { return new Unistring(fontServer.subfamily());}
  virtual Unistring *fontFullName() { return new Unistring(fontServer.fullname());}
  virtual Unistring *fontStyle() { return new Unistring(fontServer.style());}
  virtual FontMetrics metrics() { return FontMetrics();}
  virtual CORBA::Any *getFontAttr(const Unistring & name) { return new CORBA::Any();}

  virtual void setTransformation(Transform_ptr);
  virtual void setClipping(Region_ptr);
  virtual void setForeground(const Color &);
  virtual void setLighting(const Color &);
  virtual void setPointSize(Coord);
  virtual void setLineWidth(Coord);
  virtual void setLineEndstyle(Endstyle);
  virtual void setSurfaceFillstyle(Fillstyle);
  virtual void setTexture(Raster_ptr);

  virtual void setFontSize(CORBA::ULong);
  virtual void setFontWeight(CORBA::ULong);
  virtual void setFontFamily(const Unistring &);
  virtual void setFontSubFamily(const Unistring &);
  virtual void setFontFullName(const Unistring &);
  virtual void setFontStyle(const Unistring &);
  virtual void setFontAttr(const NVPair &);

  virtual Coord resolution(Axis a) { return drawable->resolution(a);}
  virtual void drawPath(const Path &);
//   virtual void drawPatch(const Patch &);
  virtual void drawRect(const Vertex &, const Vertex &);
  virtual void drawEllipse(const Vertex &, const Vertex &);
  virtual void drawImage(Raster_ptr);
  virtual void drawText(const Unistring &);
  virtual void allocateText(const Unistring & s, Graphic::Requisition & req);
  virtual void flush() { glFlush();}

//   void clear(Coord, Coord, Coord, Coord);
//   Coord width() { return drawable->width();}
//   Coord height() { return drawable->height();}
 private:
  GGI::Drawable *drawable;
  GGIMesaContext context;
  Prague::Mutex  mutex;
  Transform_var  tr;
  Region_var     cl;
  Color          fg;
  Color          lt;
  Coord          ps;
  Coord          lw;
  Endstyle       es;
  Fillstyle      fs;
  GLRaster      *tx;
  GL::FontServer fontServer;
  
  ObjectCache<Raster_var, GLTexture> textures;
  ObjectCache<Raster_var, GLImage> images;
};

#endif /* _GLDrawingKit_hh */
