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

#include <Prague/Sys/Thread.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Image.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/ObjectCache.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Console.hh>
#include <Console/Renderer.hh>
#include <Console/DirectBuffer.hh>
#include <Drawing/DrawingKitBase.hh>
#include <Drawing/libArt/LibArtFTFont.hh>
#include <Drawing/libArt/LibArtRaster.hh>

#include <libart_lgpl/art_misc.h>
#include <libart_lgpl/art_alphagamma.h>
#include <libart_lgpl/art_rect.h>
#include <libart_lgpl/art_vpath.h>

#include <string>
#include <vector>

class LibArtDrawingKit : public DrawingKitBase, public KitImpl
{
public:
  LibArtDrawingKit(const std::string &, const Warsaw::Kit::PropertySeq &);
  virtual ~LibArtDrawingKit();
  virtual KitImpl *clone(const Warsaw::Kit::PropertySeq &);

  virtual void transformation(Warsaw::Transform_ptr t) { DrawingKitBase::transformation(t);}
  virtual Warsaw::Transform_ptr transformation() { return Warsaw::Transform::_duplicate(_tr);}
  virtual void clipping(Warsaw::Region_ptr r) { DrawingKitBase::clipping(r);}
  virtual Warsaw::Region_ptr clipping() { return Warsaw::Region::_duplicate(_cl);}
  virtual void foreground(const Warsaw::Color &c) { DrawingKitBase::foreground(c);}
  virtual Warsaw::Color foreground() { return _fg;}
  virtual void lighting(const Warsaw::Color &c) { DrawingKitBase::lighting(c);}
  virtual Warsaw::Color lighting() { return _lt;}
  virtual void point_size(Warsaw::Coord c) { DrawingKitBase::point_size(c);}
  virtual Warsaw::Coord point_size() { return _ps;}
  virtual void line_width(Warsaw::Coord c) { DrawingKitBase::line_width(c);}
  virtual Warsaw::Coord line_width() { return _lw;}
  virtual void line_endstyle(Warsaw::DrawingKit::Endstyle e) { DrawingKitBase::line_endstyle(e);}
  virtual Warsaw::DrawingKit::Endstyle line_endstyle() { return _es;}
  virtual void surface_fillstyle(Warsaw::DrawingKit::Fillstyle f) { DrawingKitBase::surface_fillstyle(f);}
  virtual Warsaw::DrawingKit::Fillstyle surface_fillstyle() { return _fs;}
  virtual void texture(Warsaw::Raster_ptr r) { DrawingKitBase::texture(r);}
  virtual Warsaw::Raster_ptr texture() { //return tx ? Raster::_duplicate(tx->remote) : 
    return Warsaw::Raster::_nil();}

  virtual CORBA::ULong font_size() { return _font->size();}
  virtual CORBA::ULong font_weight() { return _font->weight();}
  virtual Warsaw::Unistring *font_family() { return _font->family();}
  virtual Warsaw::Unistring *font_subfamily() { return _font->subfamily();}
  virtual Warsaw::Unistring *font_fullname() { return _font->fullname();}
  virtual Warsaw::Unistring *font_style() { return _font->style();}
  virtual Warsaw::DrawingKit::FontMetrics font_metrics() { return _font->metrics();}
  virtual Warsaw::DrawingKit::GlyphMetrics glyph_metrics(Warsaw::Unichar uc) { return _font->metrics(uc);}
  virtual CORBA::Any *get_font_attribute(const Warsaw::Unistring & name) { return new CORBA::Any();}

  virtual void set_transformation(Warsaw::Transform_ptr);
  virtual void set_clipping(Warsaw::Region_ptr);
  virtual void set_foreground(const Warsaw::Color &);
  virtual void set_lighting(const Warsaw::Color &);
  virtual void set_point_size(Warsaw::Coord);
  virtual void set_line_width(Warsaw::Coord);
  virtual void set_line_endstyle(Warsaw::DrawingKit::Endstyle);
  virtual void set_surface_fillstyle(Warsaw::DrawingKit::Fillstyle);
  virtual void set_texture(Warsaw::Raster_ptr);

  virtual void set_font_size(CORBA::ULong);
  virtual void set_font_weight(CORBA::ULong);
  virtual void set_font_family(const Warsaw::Unistring &);
  virtual void set_font_subfamily(const Warsaw::Unistring &);
  virtual void set_font_fullname(const Warsaw::Unistring &);
  virtual void set_font_style(const Warsaw::Unistring &);
  virtual void set_font_attribute(const Warsaw::NVPair &);

  virtual Warsaw::Coord resolution(Warsaw::Axis a) { return _drawable->resolution(a);}
  virtual void draw_path(const Warsaw::Path &);
//   virtual void drawPatch(const Warsaw::Patch &);
  virtual void draw_rectangle(const Warsaw::Vertex &, const Warsaw::Vertex &);
  virtual void draw_quadric(const Warsaw::DrawingKit::Quadric, Warsaw::Coord, Warsaw::Coord);
  virtual void draw_ellipse(const Warsaw::Vertex &, const Warsaw::Vertex &);
  virtual void draw_image(Warsaw::Raster_ptr);
  virtual void allocate_text(const Warsaw::Unistring &, Warsaw::Graphic::Requisition &);
  virtual void draw_text(const Warsaw::Unistring &);
  virtual void allocate_char(Warsaw::Unichar, Warsaw::Graphic::Requisition &);
  virtual void draw_char(Warsaw::Unichar);
  virtual void copy_drawable(Warsaw::Drawable_ptr, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord);
  virtual void flush();

  virtual void start_traversal(Warsaw::Traversal_ptr) { _drawable->init(); }
  virtual void finish_traversal() { _drawable->finish(); }
 private:
  void init();
  void rasterize_pixbuf(ArtPixBuf *pixbuf);
  void identity_pixbuf(ArtPixBuf *pixbuf);

  Console::Drawable *_drawable;
  Console::Drawable *_buffer;
  Renderer          *_renderer;
  DirectBuffer      *_direct;
  ArtIRect           _bbox;
  double             _xres, _yres;
  Prague::Mutex      _mutex;

  double             _affine[6];
  double             _scaled_affine[6];

  Warsaw::Transform_var  _tr;
  Warsaw::Region_var     _cl;
  Warsaw::Color          _fg;
  Warsaw::Color          _lt;
  Warsaw::Coord          _ps;
  Warsaw::Coord          _lw;
  Warsaw::DrawingKit::Endstyle       _es;
  Warsaw::DrawingKit::Fillstyle      _fs;
  LibArtFTFont          *_font;
  LibArtFont            *_unifont;
  art_u8                 _alphabank[256][256];
  ArtAlphaGamma         *_agam;
  Warsaw::Color          _con_fg;
  art_u32                _art_fg;
  ArtIRect _screen,      _clip;
  
  ObjectCache<Warsaw::Raster_var, LibArtRaster> _rasters;
};

#endif 
