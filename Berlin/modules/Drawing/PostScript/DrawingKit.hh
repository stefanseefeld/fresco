/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 2002 Nick Lewycky <nicholas@fresco.org>
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

#include <Fresco/config.hh>
#include <Fresco/Raster.hh>
#include <Fresco/Unicode.hh>
#include <Berlin/KitImpl.hh>
#include "Berlin/DrawingKitBase.hh"
#include <string>
#include <iostream>

namespace PostScript
{
class DrawingKit : public DrawingKitBase, public KitImpl
{
public:
  DrawingKit(const std::string &, const Fresco::Kit::PropertySeq &);
  virtual ~DrawingKit();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &);

  virtual void transformation(Fresco::Transform_ptr t) { DrawingKitBase::transformation(t);}
  virtual Fresco::Transform_ptr transformation() { return Fresco::Transform::_duplicate(_tr);}
  virtual void clipping(Fresco::Region_ptr r) { DrawingKitBase::clipping(r);}
  virtual Fresco::Region_ptr clipping() { return Fresco::Region::_duplicate(_cl);}
//   using DrawingKitBase::foreground;
  virtual Fresco::Color foreground() { return _fg;}
  virtual Fresco::Color lighting() { return _lt;}
  virtual Fresco::Coord point_size() { return _ps;}
  virtual Fresco::Coord line_width() { return _lw;}
  virtual Fresco::DrawingKit::Endstyle line_endstyle() { return _es;}
  virtual Fresco::DrawingKit::Fillstyle surface_fillstyle() { return _fs;}
  virtual Fresco::Raster_ptr texture() { return Fresco::Raster::_nil();}

  virtual CORBA::ULong font_size() { return 12;}
  virtual CORBA::ULong font_weight() { return 1;}
  virtual Fresco::Unistring *font_family();
  virtual Fresco::Unistring *font_subfamily();
  virtual Fresco::Unistring *font_fullname();
  virtual Fresco::Unistring *font_style();
  virtual Fresco::DrawingKit::FontMetrics font_metrics();
  virtual Fresco::DrawingKit::GlyphMetrics glyph_metrics(Fresco::Unichar);
  virtual CORBA::Any *get_font_attribute(const Fresco::Unistring &);

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

  virtual Fresco::Coord resolution(Fresco::Axis) { return 0.283464566929;}
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
  virtual void copy_drawable(Fresco::Drawable_ptr, Fresco::PixelCoord, Fresco::PixelCoord, Fresco::PixelCoord, Fresco::PixelCoord);

  virtual void start_traversal(Fresco::Traversal_ptr);
  virtual void finish_traversal();

  virtual void flush() {}
private:
  void vertex(const Fresco::Vertex &, const char *);
  Prague::Mutex                 _mutex;
  Fresco::Transform_var         _tr;
  Fresco::Transform_var         _tr_adjust;
  Fresco::Region_var            _cl;
  RegionImpl                   *_cl_none;
  Fresco::Color                 _fg;
  Fresco::Color                 _lt;
  Fresco::Coord                 _ps;
  Fresco::Coord                 _lw;
  Fresco::DrawingKit::Endstyle  _es;
  Fresco::DrawingKit::Fillstyle _fs;
  std::ostream                  _os;
};
}

#endif
