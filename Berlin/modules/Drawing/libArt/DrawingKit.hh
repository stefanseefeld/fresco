/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999,2000 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 1999,2000 Graydon Hoare <graydon@pobox.com> 
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
#ifndef _LibArtDrawingKit_hh
#define _LibArtDrawingKit_hh

#include <Berlin/ImplVar.hh>
#include <Warsaw/Image.hh>
#include <Drawing/DrawingKitBase.hh>
#include <Drawing/libArt/LibArtFTFont.hh>
#include <Drawing/libArt/LibArtRaster.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/ObjectCache.hh>
#include <Berlin/Console.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Prague/Sys/Thread.hh>

#include <libart_lgpl/art_misc.h>
#include <libart_lgpl/art_alphagamma.h>
#include <libart_lgpl/art_rect.h>
#include <libart_lgpl/art_vpath.h>

#include <string>
#include <vector>

class LibArtDrawingKit : public DrawingKitBase, public KitImpl
{
public:
  LibArtDrawingKit(KitFactory *, const PropertySeq &);
  virtual ~LibArtDrawingKit();

  virtual void transformation(Transform_ptr t) { DrawingKitBase::transformation(t);}
  virtual Transform_ptr transformation() { return Transform::_duplicate(tr);}
  virtual void clipping(Region_ptr r) { DrawingKitBase::clipping(r);}
  virtual Region_ptr clipping() { return Region::_duplicate(cl);}
  virtual void foreground(const Color &c) { DrawingKitBase::foreground(c);}
  virtual Color foreground() { return fg;}
  virtual void lighting(const Color &c) { DrawingKitBase::lighting(c);}
  virtual Color lighting() { return lt;}
  virtual void pointSize(Coord c) { DrawingKitBase::pointSize(c);}
  virtual Coord pointSize() { return ps;}
  virtual void lineWidth(Coord c) { DrawingKitBase::lineWidth(c);}
  virtual Coord lineWidth() { return lw;}
  virtual void lineEndstyle(DrawingKit::Endstyle e) { DrawingKitBase::lineEndstyle(e);}
  virtual DrawingKit::Endstyle lineEndstyle() { return es;}
  virtual void surfaceFillstyle(DrawingKit::Fillstyle f) { DrawingKitBase::surfaceFillstyle(f);}
  virtual DrawingKit::Fillstyle surfaceFillstyle() { return fs;}
  virtual void texture(Raster_ptr r) { DrawingKitBase::texture(r);}
  virtual Raster_ptr texture() { //return tx ? Raster::_duplicate(tx->remote) : 
    return Raster::_nil();}

  virtual CORBA::ULong fontSize() { return font->size();}
  virtual CORBA::ULong fontWeight() { return font->weight();}
  virtual Unistring *fontFamily() { return font->family();}
  virtual Unistring *fontSubFamily() { return font->subfamily();}
  virtual Unistring *fontFullName() { return font->fullname();}
  virtual Unistring *fontStyle() { return font->style();}
  virtual DrawingKit::FontMetrics fmetrics() { return font->metrics();}
  virtual DrawingKit::GlyphMetrics gmetrics(Unichar uc) { return font->metrics(uc);}
  virtual CORBA::Any *getFontAttr(const Unistring & name) { return new CORBA::Any();}

  virtual void setTransformation(Transform_ptr);
  virtual void setClipping(Region_ptr);
  virtual void setForeground(const Color&);
  virtual void setLighting(const Color&);
  virtual void setPointSize(Coord);
  virtual void setLineWidth(Coord);
  virtual void setLineEndstyle(DrawingKit::Endstyle);
  virtual void setSurfaceFillstyle(DrawingKit::Fillstyle);
  virtual void setTexture(Raster_ptr);

  virtual void setFontSize(CORBA::ULong);
  virtual void setFontWeight(CORBA::ULong);
  virtual void setFontFamily(const Unistring&);
  virtual void setFontSubFamily(const Unistring&);
  virtual void setFontFullName(const Unistring&);
  virtual void setFontStyle(const Unistring&);
  virtual void setFontAttr(const NVPair & nvp);

  virtual Coord resolution(Axis a) { return drawable->resolution(a);}
  virtual void drawPath(const Path &);
//   virtual void drawPatch(const Patch &);
  virtual void drawRect(const Vertex &, const Vertex &);
  virtual void drawEllipse(const Vertex &, const Vertex &);
  virtual void drawImage(Raster_ptr);
  virtual void allocateText(const Unistring & s, Graphic::Requisition & req);
  virtual void drawText(const Unistring &);
  virtual void allocateChar(Unichar c, Graphic::Requisition & req);
  virtual void drawChar(Unichar);
  virtual void flush();

 private:
  void rasterizePixbuf(ArtPixBuf *pixbuf);
  void identityPixbuf(ArtPixBuf *pixbuf);

  Console::Drawable *drawable;
  Console::Drawable *buffer;
  ArtPixBuf *pb;
  ArtIRect bbox;
//   const ggi_directbuffer * buf;
  double xres, yres;
  Prague::Mutex mutex;

  double affine[6];
  double scaled_affine[6];

  Transform_var  tr;
  Region_var     cl;
  Color          fg;
  Color          lt;
  Coord          ps;
  Coord          lw;
  DrawingKit::Endstyle       es;
  DrawingKit::Fillstyle      fs;
  LibArtFTFont   *font;
  LibArtFont   *unifont;
  art_u8 alphabank[256][256];
  ArtAlphaGamma *agam;
  art_u32         art_fg;
  Console::Drawable::Pixel con_fg;
  ArtIRect screen,clip;
  
  ObjectCache<Raster_var, LibArtRaster> rasters;
};

#endif /* _LibArtDrawingKit_hh */
