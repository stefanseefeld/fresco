/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
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
#ifndef _DrawingKit_hh
#define _DrawingKit_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/Raster.hh>
#include <Fresco/DrawingKit3D.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/ObjectCache.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Console/GLContext.hh>
#include <Berlin/DrawingKitBase.hh>
#include "FTFont.hh"
#include "Raster.hh"
#include <string>
#include <vector>
#include <bitset>

#include <GL/glu.h>

namespace openGL
{

class DrawingKit : public virtual POA_Fresco::DrawingKit3D,
		   public DrawingKitBase, public KitImpl
{
  friend class Texture;
  friend class Image;

  class Light
  {
  public:
    Light();
    int push();
    int top() const;
    void pop();
  private:
    int _max;
    int _number;
  };
  struct DrawState
  {
    enum { st_lights, st_last};
    DrawState() {}
    std::bitset<st_last> flags;
    size_t lights;
  };
public:
  DrawingKit(const std::string &, const Fresco::Kit::PropertySeq &);
  virtual ~DrawingKit();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &);

  virtual void save();
  virtual void restore();

  virtual void transformation(Fresco::Transform_ptr t) { DrawingKitBase::transformation(t);}
  virtual Fresco::Transform_ptr transformation() { return Fresco::Transform::_duplicate(_tr);}
  virtual void clipping(Fresco::Region_ptr r) { DrawingKitBase::clipping(r);}
  virtual Fresco::Region_ptr clipping() { return Fresco::Region::_duplicate(_cl);}
//   using DrawingKitBase::foreground;
  virtual void foreground(const Fresco::Color &c) { DrawingKitBase::foreground(c);}
  virtual Fresco::Color foreground() { return _fg;}
  virtual void lighting(const Fresco::Color &c) { DrawingKitBase::lighting(c);}
  virtual Fresco::Color lighting() { return _lt;}
  virtual void point_size(Fresco::Coord c) { DrawingKitBase::point_size(c);}
  virtual Fresco::Coord point_size() { return _ps;}
  virtual void line_width(Fresco::Coord c) { DrawingKitBase::line_width(c);}
  virtual Fresco::Coord line_width() { return _lw;}
  virtual void line_endstyle(Fresco::DrawingKit::Endstyle e) { DrawingKitBase::line_endstyle(e);}
  virtual Fresco::DrawingKit::Endstyle line_endstyle() { return _es;}
  virtual void surface_fillstyle(Fresco::DrawingKit::Fillstyle f) { DrawingKitBase::surface_fillstyle(f);}
  virtual Fresco::DrawingKit::Fillstyle surface_fillstyle() { return _fs;}
  virtual void texture(Fresco::Raster_ptr r) { DrawingKitBase::texture(r);}
  virtual Fresco::Raster_ptr texture() { return _tx ? Fresco::Raster::_duplicate(_tx->remote) : Fresco::Raster::_nil();}

  virtual CORBA::ULong font_size() { return _font->size();}
  virtual CORBA::ULong font_weight() { return _font->weight();}
  virtual Fresco::Unistring *font_family() { return _font->family();}
  virtual Fresco::Unistring *font_subfamily() { return _font->subfamily();}
  virtual Fresco::Unistring *font_fullname() { return _font->fullname();}
  virtual Fresco::Unistring *font_style() { return _font->style();}
  virtual Fresco::DrawingKit::FontMetrics font_metrics() { return _font->metrics();}
  virtual Fresco::DrawingKit::GlyphMetrics glyph_metrics(Fresco::Unichar uc) { return _font->metrics(uc);}
  virtual CORBA::Any *get_font_attribute(const Fresco::Unistring & name) { return new CORBA::Any();}

  virtual void material(const Fresco::MaterialAttr &) {}
  virtual Fresco::MaterialAttr material() { return Fresco::MaterialAttr();}
  virtual void textures(const Fresco::Rasters &) {}
  virtual Fresco::Rasters *textures() { return new Fresco::Rasters();}
  virtual void tex_mode(Fresco::DrawingKit3D::TextureMode) {}
  virtual Fresco::DrawingKit3D::TextureMode tex_mode() { return Fresco::DrawingKit3D::TextureOff;}
  virtual void directional_light(const Fresco::Color &, CORBA::Float, const Fresco::Vertex &);
  virtual void point_light(const Fresco::Color &, CORBA::Float, const Fresco::Vertex &);
  virtual void spot_light(const Fresco::Color &, CORBA::Float, const Fresco::Vertex &, const Fresco::Vertex &, CORBA::Float, CORBA::Float);
  virtual void fog_mode(Fresco::DrawingKit3D::FoggingMode) {}
  virtual Fresco::DrawingKit3D::FoggingMode fog_mode() { return Fresco::DrawingKit3D::FogOff;}

  virtual void set_transformation(Fresco::Transform_ptr);
  virtual void set_clipping(Fresco::Region_ptr);
  virtual void set_foreground(const Fresco::Color &);
  virtual void set_lighting(const Fresco::Color &);
  virtual void set_point_size(Fresco::Coord);
  virtual void set_line_width(Fresco::Coord);
  virtual void set_line_endstyle(Fresco::DrawingKit::Endstyle);
  virtual void set_surface_fillstyle(Fresco::DrawingKit::Fillstyle);
  virtual void set_texture(Fresco::Raster_ptr);

  virtual void set_font_size(CORBA::ULong);
  virtual void set_font_weight(CORBA::ULong);
  virtual void set_font_family(const Fresco::Unistring &);
  virtual void set_font_subfamily(const Fresco::Unistring &);
  virtual void set_font_fullname(const Fresco::Unistring &);
  virtual void set_font_style(const Fresco::Unistring &);
  virtual void set_font_attribute(const Fresco::NVPair &);

//   virtual void set_lighting(bool);

  virtual Fresco::Coord resolution(Fresco::Axis a) { return _drawable->resolution(a);}
  virtual void draw_path(const Fresco::Path &);
//   virtual void drawPatch(const Fresco::Patch &);
  virtual void draw_rectangle(const Fresco::Vertex &, const Fresco::Vertex &);
  virtual void draw_quadric(const Fresco::DrawingKit::Quadric, Fresco::Coord, Fresco::Coord);
  virtual void draw_ellipse(const Fresco::Vertex &, const Fresco::Vertex &);
  virtual void draw_image(Fresco::Raster_ptr);
  virtual void allocate_char(Fresco::Unichar, Fresco::Graphic::Requisition &);
  virtual void draw_char(Fresco::Unichar);
  virtual void allocate_text(const Fresco::Unistring &, Fresco::Graphic::Requisition &);
  virtual void draw_text(const Fresco::Unistring &);

  virtual void draw_mesh(const Fresco::Mesh &);
//   virtual void draw_lines(const Fresco::Vertices &coords, const Fresco::TexCoords &tcs);
//   virtual void draw_points(const Fresco::Vertices &coords);

  virtual void copy_drawable(Fresco::Drawable_ptr, Fresco::PixelCoord, Fresco::PixelCoord, Fresco::PixelCoord, Fresco::PixelCoord);

  virtual void start_traversal(Fresco::Traversal_ptr) { }
  virtual void finish_traversal() { }

  virtual void flush() { my_glcontext->flush(); }

//   void clear(Coord, Coord, Coord, Coord);
//   Coord width() { return drawable->width();}
//   Coord height() { return drawable->height();}
private:
  class ResetTrafo;
  class SetTrafo;
  class SetColor;
  class SetClipping;
  class SetPointSize;
  class SetLineWidth;
  class SetTexture;
  class SetOutline;

  class DrawPath;
  class DrawMesh;

  class PointLight;
  class SpotLight;
  class DirectionalLight;

  void init();
  std::stack<DrawState>                    _states;
  Console::Drawable                       *_drawable;
  GLContext                               *my_glcontext;
  Prague::Mutex                            _mutex;
  Fresco::Transform_var                    _tr;
  Fresco::Region_var                       _cl;
  Fresco::Color                            _fg;
  Fresco::Color                            _lt;
  Fresco::Coord                            _ps;
  Fresco::Coord                            _lw;
  Fresco::DrawingKit::Endstyle             _es;
  Fresco::DrawingKit::Fillstyle            _fs;
  Texture                                 *_tx;
  FTFont                                  *_font;
  Light                                   *_light;
  ObjectCache<Fresco::Raster_var, Texture> _textures;
  ObjectCache<Fresco::Raster_var, Image>   _images;
};

}

#endif 
