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
  LibArtDrawingKit(KitFactory *, const Warsaw::Kit::PropertySeq &);
  virtual ~LibArtDrawingKit();

  virtual void transformation(Warsaw::Transform_ptr t) { DrawingKitBase::transformation(t);}
  virtual Warsaw::Transform_ptr transformation() { return Warsaw::Transform::_duplicate(tr);}
  virtual void clipping(Warsaw::Region_ptr r) { DrawingKitBase::clipping(r);}
  virtual Warsaw::Region_ptr clipping() { return Warsaw::Region::_duplicate(cl);}
  virtual void foreground(const Warsaw::Color &c) { DrawingKitBase::foreground(c);}
  virtual Warsaw::Color foreground() { return fg;}
  virtual void lighting(const Warsaw::Color &c) { DrawingKitBase::lighting(c);}
  virtual Warsaw::Color lighting() { return lt;}
  virtual void pointSize(Warsaw::Coord c) { DrawingKitBase::pointSize(c);}
  virtual Warsaw::Coord pointSize() { return ps;}
  virtual void lineWidth(Warsaw::Coord c) { DrawingKitBase::lineWidth(c);}
  virtual Warsaw::Coord lineWidth() { return lw;}
  virtual void lineEndstyle(Warsaw::DrawingKit::Endstyle e) { DrawingKitBase::lineEndstyle(e);}
  virtual Warsaw::DrawingKit::Endstyle lineEndstyle() { return es;}
  virtual void surfaceFillstyle(Warsaw::DrawingKit::Fillstyle f) { DrawingKitBase::surfaceFillstyle(f);}
  virtual Warsaw::DrawingKit::Fillstyle surfaceFillstyle() { return fs;}
  virtual void texture(Warsaw::Raster_ptr r) { DrawingKitBase::texture(r);}
  virtual Warsaw::Raster_ptr texture() { //return tx ? Raster::_duplicate(tx->remote) : 
    return Warsaw::Raster::_nil();}

  virtual CORBA::ULong fontSize() { return font->size();}
  virtual CORBA::ULong fontWeight() { return font->weight();}
  virtual Warsaw::Unistring *fontFamily() { return font->family();}
  virtual Warsaw::Unistring *fontSubFamily() { return font->subfamily();}
  virtual Warsaw::Unistring *fontFullName() { return font->fullname();}
  virtual Warsaw::Unistring *fontStyle() { return font->style();}
  virtual Warsaw::DrawingKit::FontMetrics fmetrics() { return font->metrics();}
  virtual Warsaw::DrawingKit::GlyphMetrics gmetrics(Warsaw::Unichar uc) { return font->metrics(uc);}
  virtual CORBA::Any *getFontAttr(const Warsaw::Unistring & name) { return new CORBA::Any();}

  virtual void setTransformation(Warsaw::Transform_ptr);
  virtual void setClipping(Warsaw::Region_ptr);
  virtual void setForeground(const Warsaw::Color &);
  virtual void setLighting(const Warsaw::Color &);
  virtual void setPointSize(Warsaw::Coord);
  virtual void setLineWidth(Warsaw::Coord);
  virtual void setLineEndstyle(Warsaw::DrawingKit::Endstyle);
  virtual void setSurfaceFillstyle(Warsaw::DrawingKit::Fillstyle);
  virtual void setTexture(Warsaw::Raster_ptr);

  virtual void setFontSize(CORBA::ULong);
  virtual void setFontWeight(CORBA::ULong);
  virtual void setFontFamily(const Warsaw::Unistring &);
  virtual void setFontSubFamily(const Warsaw::Unistring &);
  virtual void setFontFullName(const Warsaw::Unistring &);
  virtual void setFontStyle(const Warsaw::Unistring &);
  virtual void setFontAttr(const Warsaw::NVPair &);

  virtual Warsaw::Coord resolution(Warsaw::Axis a) { return drawable->resolution(a);}
  virtual void drawPath(const Warsaw::Path &);
//   virtual void drawPatch(const Warsaw::Patch &);
  virtual void drawRect(const Warsaw::Vertex &, const Warsaw::Vertex &);
  virtual void drawEllipse(const Warsaw::Vertex &, const Warsaw::Vertex &);
  virtual void drawImage(Warsaw::Raster_ptr);
  virtual void allocateText(const Warsaw::Unistring &, Warsaw::Graphic::Requisition &);
  virtual void drawText(const Warsaw::Unistring &);
  virtual void allocateChar(Warsaw::Unichar, Warsaw::Graphic::Requisition &);
  virtual void drawChar(Warsaw::Unichar);
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

  Warsaw::Transform_var  tr;
  Warsaw::Region_var     cl;
  Warsaw::Color          fg;
  Warsaw::Color          lt;
  Warsaw::Coord          ps;
  Warsaw::Coord          lw;
  Warsaw::DrawingKit::Endstyle       es;
  Warsaw::DrawingKit::Fillstyle      fs;
  LibArtFTFont   *font;
  LibArtFont   *unifont;
  art_u8 alphabank[256][256];
  ArtAlphaGamma *agam;
  art_u32         art_fg;
  Console::Drawable::Pixel con_fg;
  ArtIRect screen,clip;
  
  ObjectCache<Warsaw::Raster_var, LibArtRaster> rasters;
};

#endif 
