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

#include <Warsaw/config.hh>
#include <Warsaw/Raster.hh>
#include <Warsaw/DrawingKit3D.hh>
#include <Drawing/DrawingKitBase.hh>
#include <Drawing/openGL/GLFont.hh>
#include <Drawing/openGL/GLRaster.hh>
#include <Prague/Sys/Thread.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/ObjectCache.hh>
#include <Berlin/Console.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>

#if defined(CONSOLE_GGI)
#  include <GL/ggimesa.h>
#elif defined(CONSOLE_SDL)
#elif defined(CONSOLE_GLUT)
#else
#  error "GLDrawingKit needs a OpenGL-enabled console to compile"
#endif

#include <string>
#include <vector>

class GLDrawingKit : public virtual POA_Warsaw::DrawingKit3D,
		     public DrawingKitBase, public KitImpl
{
  struct DrawState
  {
    enum { st_lighting, st_lights};
    DrawState() : flags(0) {}
//     bitset<st_last> flags;
    unsigned long flags;
    bool lighting;
    size_t lights;
  };
public:
  GLDrawingKit(const std::string &, const Warsaw::Kit::PropertySeq &);
  virtual ~GLDrawingKit();
  virtual KitImpl *clone(const Warsaw::Kit::PropertySeq &);

  virtual void save();
  virtual void restore();

  virtual void transformation(Warsaw::Transform_ptr t) { DrawingKitBase::transformation(t);}
  virtual Warsaw::Transform_ptr transformation() { return Warsaw::Transform::_duplicate(_tr);}
  virtual void clipping(Warsaw::Region_ptr r) { DrawingKitBase::clipping(r);}
  virtual Warsaw::Region_ptr clipping() { return Warsaw::Region::_duplicate(_cl);}
//   using DrawingKitBase::foreground;
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
  virtual Warsaw::Raster_ptr texture() { return _tx ? Warsaw::Raster::_duplicate(_tx->remote) : Warsaw::Raster::_nil();}

  virtual CORBA::ULong font_size() { return _font->size();}
  virtual CORBA::ULong font_weight() { return _font->weight();}
  virtual Warsaw::Unistring *font_family() { return _font->family();}
  virtual Warsaw::Unistring *font_subfamily() { return _font->subfamily();}
  virtual Warsaw::Unistring *font_fullname() { return _font->fullname();}
  virtual Warsaw::Unistring *font_style() { return _font->style();}
  virtual Warsaw::DrawingKit::FontMetrics font_metrics() { return _font->metrics();}
  virtual Warsaw::DrawingKit::GlyphMetrics glyph_metrics(Warsaw::Unichar uc) { return _font->metrics(uc);}
  virtual CORBA::Any *get_font_attribute(const Warsaw::Unistring & name) { return new CORBA::Any();}

  virtual void material(const Warsaw::MaterialAttr &) {}
  virtual Warsaw::MaterialAttr material() { return Warsaw::MaterialAttr();}
  virtual void textures(const Warsaw::Rasters &) {}
  virtual Warsaw::Rasters *textures() { return new Warsaw::Rasters();}
  virtual void tex_mode(Warsaw::DrawingKit3D::TextureMode) {}
  virtual Warsaw::DrawingKit3D::TextureMode tex_mode() { return Warsaw::DrawingKit3D::TextureOff;}
//   virtual void lighting(CORBA::Boolean) {}
//   virtual CORBA::Boolean lighting();
  virtual void fog_mode(Warsaw::DrawingKit3D::FoggingMode) {}
  virtual Warsaw::DrawingKit3D::FoggingMode fog_mode() { return Warsaw::DrawingKit3D::FogOff;}

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

//   virtual void set_lighting(bool);

  virtual Warsaw::Coord resolution(Warsaw::Axis a) { return _drawable->resolution(a);}
  virtual void draw_path(const Warsaw::Path &);
//   virtual void drawPatch(const Warsaw::Patch &);
  virtual void draw_rectangle(const Warsaw::Vertex &, const Warsaw::Vertex &);
  virtual void draw_quadric(const Warsaw::DrawingKit::Quadric, Warsaw::Coord, Warsaw::Coord);
  virtual void draw_ellipse(const Warsaw::Vertex &, const Warsaw::Vertex &);
  virtual void draw_image(Warsaw::Raster_ptr);
  virtual void allocate_char(Warsaw::Unichar, Warsaw::Graphic::Requisition &);
  virtual void draw_char(Warsaw::Unichar);
  virtual void allocate_text(const Warsaw::Unistring &, Warsaw::Graphic::Requisition &);
  virtual void draw_text(const Warsaw::Unistring &);

  virtual void draw_mesh(const Warsaw::Mesh &);
//   virtual void draw_lines(const Warsaw::Vertices &coords, const Warsaw::TexCoords &tcs);
//   virtual void draw_points(const Warsaw::Vertices &coords);

  virtual void copy_drawable(Warsaw::Drawable_ptr, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord);
  virtual void flush() { glFlush();}

//   void clear(Coord, Coord, Coord, Coord);
//   Coord width() { return drawable->width();}
//   Coord height() { return drawable->height();}
 private:
  void init();
  std::stack<DrawState>                      _states;
  Console::Drawable                         *_drawable;
#if defined(CONSOLE_GGI)
  GGIMesaContext                             _context;
#endif
  Prague::Mutex                              _mutex;
  Warsaw::Transform_var                      _tr;
  Warsaw::Region_var                         _cl;
  Warsaw::Color                              _fg;
  Warsaw::Color                              _lt;
  Warsaw::Coord                              _ps;
  Warsaw::Coord                              _lw;
  Warsaw::DrawingKit::Endstyle               _es;
  Warsaw::DrawingKit::Fillstyle              _fs;
  GLRaster                                  *_tx;
  GLFont                                    *_font;
  
  ObjectCache<Warsaw::Raster_var, GLTexture> _textures;
  ObjectCache<Warsaw::Raster_var, GLImage>   _images;
};

#endif 
