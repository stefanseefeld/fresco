/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#include <Berlin/CloneableImpl.hh>
// #include "Drawing/openGL/GLFont.hh"
#include "Drawing/openGL/GLUnifont.hh"
#include <Drawing/openGL/GLRaster.hh>
#include <Berlin/Thread.hh>
#include <Berlin/ObjectCache.hh>
#include <Berlin/GGI.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Warsaw/Image.hh>
#include <GL/ggimesa.h>

#include <string>
#include <vector>

class GLDrawingKit : public DrawingKitBase, public CloneableImpl
{
public:
  GLDrawingKit();
  ~GLDrawingKit();

  virtual void transformation(Transform_ptr t) { DrawingKitBase::transformation(t);}
  virtual Transform_ptr transformation() { return tr->_this();}
  virtual void clipping(Region_ptr r) { DrawingKitBase::clipping(r);}
  virtual Region_ptr clipping() { return cl->_this();}
  virtual void foreground(const Color &c) { DrawingKitBase::foreground(c);}
  virtual Color foreground() { return fg;}
  virtual void pointSize(Coord c) { DrawingKitBase::pointSize(c);}
  virtual Coord pointSize() { return ps;}
  virtual void lineWidth(Coord c) { DrawingKitBase::lineWidth(c);}
  virtual Coord lineWidth() { return lw;}
  virtual void lineEndstyle(Endstyle e) { DrawingKitBase::lineEndstyle(e);}
  virtual Endstyle lineEndstyle() { return es;}
  virtual void surfaceFillstyle(Fillstyle f) { DrawingKitBase::surfaceFillstyle(f);}
  virtual Fillstyle surfaceFillstyle() { return fs;}
  virtual void texture(Raster_ptr r) { DrawingKitBase::texture(r);}
  virtual Raster_ptr texture() { return tx;}

  virtual Text::Font_ptr font(); 
  virtual Text::Font_ptr findFont(const Text::FontDescriptor &fd);


  virtual void setTransformation(Transform_ptr);
  virtual void setClipping(Region_ptr);
  virtual void setForeground(Color);
  virtual void setPointSize(Coord);
  virtual void setLineWidth(Coord);
  virtual void setLineEndstyle(Endstyle);
  virtual void setSurfaceFillstyle(Fillstyle);
  virtual void setTexture(Raster_ptr);

  virtual Coord resolution(Axis a) { return drawable->resolution(a);}
  virtual void drawPath(const Path &);
//   virtual void drawPatch(const Patch &);
  virtual void drawRect(const Vertex &, const Vertex &);
  virtual void drawEllipse(const Vertex &, const Vertex &);
  virtual void drawImage(Raster_ptr);
  virtual void drawText(const Unistring &);
  virtual void flush() { glFlush();}

//   void clear(Coord, Coord, Coord, Coord);
//   Coord width() { return drawable->width();}
//   Coord height() { return drawable->height();}
 private:
  GLUnifont unifont;
  GGI::Drawable *drawable;
  GGIMesaContext context;
  Mutex mutex;
  TransformImpl *tr;
  RegionImpl    *cl;
  Color          fg;
  Coord          ps;
  Coord          lw;
  Endstyle       es;
  Fillstyle      fs;
  Raster_var     tx;
  
  ObjectCache<Raster_var, GLRaster> rasters;
};

#endif /* _GLDrawingKit_hh */
