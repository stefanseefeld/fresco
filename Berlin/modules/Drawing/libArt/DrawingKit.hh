/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999,2000 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 1999,2000 Graydon Hoare <graydon@fresco.org> 
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
#ifndef _libArt_DrawingKit_hh
#define _libArt_DrawingKit_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/Image.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/ObjectCache.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Console.hh>
#include <Berlin/Console/Renderer.hh>
#include <Berlin/Console/DirectBuffer.hh>
#include <Berlin/DrawingKitBase.hh>
#include "FTFont.hh"
#include "Raster.hh"

#include <libart_lgpl/art_misc.h>
#include <libart_lgpl/art_alphagamma.h>
#include <libart_lgpl/art_rect.h>
#include <libart_lgpl/art_vpath.h>

#include <string>
#include <vector>

namespace Berlin 
{
  namespace DrawingKit 
  {
    namespace libArt 
    {
      
      class DrawingKit : public DrawingKitBase, public KitImpl
      {
    public:
      DrawingKit(const std::string &,
             const Fresco::Kit::PropertySeq &,
             ServerContextImpl *);
      virtual ~DrawingKit();
      virtual KitImpl *clone(const Fresco::Kit::PropertySeq &,
                 ServerContextImpl *);
      
      virtual void transformation(Fresco::Transform_ptr t)
      { DrawingKitBase::transformation(t); }
      virtual Fresco::Transform_ptr transformation()
      { return Fresco::Transform::_duplicate(my_tr); }
      virtual void clipping(Fresco::Region_ptr r)
          { DrawingKitBase::clipping(r); }
      virtual Fresco::Region_ptr clipping()
      { return Fresco::Region::_duplicate(my_cl); }
      virtual void foreground(const Fresco::Color &c)
      { DrawingKitBase::foreground(c); }
      virtual Fresco::Color foreground() { return my_fg; }
      virtual void lighting(const Fresco::Color &c)
      { DrawingKitBase::lighting(c); }
      virtual Fresco::Color lighting() { return my_lt; }
      virtual void point_size(Fresco::Coord c)
      { DrawingKitBase::point_size(c); }
      virtual Fresco::Coord point_size() { return my_ps; }
      virtual void line_width(Fresco::Coord c)
      { DrawingKitBase::line_width(c);}
      virtual Fresco::Coord line_width() { return my_lw;}
      virtual void line_endstyle(Fresco::DrawingKit::Endstyle e)
      { DrawingKitBase::line_endstyle(e); }
      virtual Fresco::DrawingKit::Endstyle line_endstyle()
      { return my_es; }
      virtual void surface_fillstyle(Fresco::DrawingKit::Fillstyle f)
      { DrawingKitBase::surface_fillstyle(f); }
      virtual Fresco::DrawingKit::Fillstyle surface_fillstyle()
      { return my_fs; }
      virtual void texture(Fresco::Raster_ptr r)
      { DrawingKitBase::texture(r); }
      virtual Fresco::Raster_ptr texture()
      {
          //return tx ? Raster::_duplicate(tx->remote) : 
          return Fresco::Raster::_nil();
      }

      virtual CORBA::ULong font_size() { return my_font->size(); }
      virtual CORBA::ULong font_weight() { return my_font->weight(); }
      virtual Fresco::Unistring *font_family()
      { return my_font->family(); }
      virtual Fresco::Unistring *font_subfamily()
      { return my_font->subfamily(); }
      virtual Fresco::Unistring *font_fullname()
      { return my_font->fullname(); }
      virtual Fresco::Unistring *font_style()
      { return my_font->style(); }
      virtual Fresco::DrawingKit::FontMetrics font_metrics()
      { return my_font->metrics(); }
      virtual Fresco::DrawingKit::GlyphMetrics
      glyph_metrics(Fresco::Unichar uc)
      { return my_font->metrics(uc); }
      virtual CORBA::Any *
      get_font_attribute(const Fresco::Unistring & name)
      { return new CORBA::Any(); }

      virtual void set_transformation(Fresco::Transform_ptr);
      virtual void set_clipping(Fresco::Region_ptr);
      virtual void set_foreground(const Fresco::Color &);
      virtual void set_lighting(const Fresco::Color &);
      virtual void set_point_size(Fresco::Coord);
      virtual void set_line_width(Fresco::Coord);
      virtual void set_line_endstyle(Fresco::DrawingKit::Endstyle);
      virtual void
      set_surface_fillstyle(Fresco::DrawingKit::Fillstyle);
      virtual void set_texture(Fresco::Raster_ptr);

      virtual void set_font_size(CORBA::ULong);
      virtual void set_font_weight(CORBA::ULong);
      virtual void set_font_family(const Fresco::Unistring &);
      virtual void set_font_subfamily(const Fresco::Unistring &);
      virtual void set_font_fullname(const Fresco::Unistring &);
      virtual void set_font_style(const Fresco::Unistring &);
      virtual void set_font_attribute(const Fresco::NVPair &);
      
      virtual Fresco::Coord resolution(Fresco::Axis a)
      { return my_drawable->resolution(a); }
      virtual void draw_path(const Fresco::Path &);
      virtual void draw_new_path(const Fresco::NewPath &);
          // virtual void drawPatch(const Fresco::Patch &);
      virtual void draw_rectangle(const Fresco::Vertex &,
                      const Fresco::Vertex &);
      virtual void draw_quadric(const Fresco::DrawingKit::Quadric,
                    Fresco::Coord, Fresco::Coord);
      virtual void draw_ellipse(const Fresco::Vertex &,
                    const Fresco::Vertex &);
      virtual void draw_image(Fresco::Raster_ptr);
      virtual void allocate_text(const Fresco::Unistring &,
                     Fresco::Graphic::Requisition &);
      virtual void draw_text(const Fresco::Unistring &);
      virtual void allocate_char(Fresco::Unichar,
                     Fresco::Graphic::Requisition &);
      virtual void draw_char(Fresco::Unichar);
      virtual void copy_drawable(Fresco::Drawable_ptr,
                     Fresco::PixelCoord,
                     Fresco::PixelCoord,
                     Fresco::PixelCoord,
                     Fresco::PixelCoord);
      virtual void flush();

      virtual void start_traversal(Fresco::Traversal_ptr)
      { my_drawable->init(); }
      virtual void finish_traversal() { my_drawable->finish(); }
    private:
      void init();
      void rasterize_pixbuf(ArtPixBuf *pixbuf);
      void identity_pixbuf(ArtPixBuf *pixbuf);

      Console::Drawable *my_drawable;
      Console::Drawable *my_buffer;
      Console_Extension::Renderer *my_renderer;
      Console_Extension::DirectBuffer *my_direct;
      ArtIRect my_bbox;
      double my_xres, my_yres;
      Prague::Mutex my_mutex;

      double my_affine[6];
      double my_scaled_affine[6];
      
      Fresco::Transform_var my_tr;
      Fresco::Region_var my_cl;
      Fresco::Color my_fg;
      Fresco::Color my_lt;
      Fresco::Coord my_ps;
      Fresco::Coord my_lw;
      Fresco::DrawingKit::Endstyle my_es;
      Fresco::DrawingKit::Fillstyle my_fs;
      FTFont *my_font;
      Font *my_unifont;
      art_u8 my_alphabank[256][256];
      ArtAlphaGamma *my_agam;
      Fresco::Color my_con_fg;
      art_u32 my_art_fg;
      ArtIRect my_screen, my_clip;
      
      ObjectCache<Fresco::Raster_var, libArt::Raster> my_rasters;
      };

    } // namespace
  } // namespace
} // namespace

#endif 
