/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 2002 Nick Lewycky <nicholas@mxc.ca>
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

#include <Warsaw/config.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/Raster.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Console.hh>
#include "Drawing/PostScript/PSDrawingKit.hh"
#include <strstream>
#include <iostream>

using namespace Prague;
using namespace Warsaw;

PSDrawingKit::PSDrawingKit(const std::string &id, const Warsaw::Kit::PropertySeq &p)
  : KitImpl(id, p)
{
  _os.rdbuf(cout.rdbuf());
  _os.precision(5);
}

PSDrawingKit::~PSDrawingKit()
{
}

KitImpl *PSDrawingKit::clone(const Warsaw::Kit::PropertySeq &p)
{
  PSDrawingKit *kit = new PSDrawingKit(repo_id(), p);
  kit->init();
  return kit;
}

void PSDrawingKit::init()
{
  _os << "%!PS-Adobe-3.0 EPSF-3.0" << std::endl;
  _os << "%%BoundingBox: 0 "
      << 0-(int)(Console::instance()->drawable()->width()/resolution(yaxis)+1.) << ' '
      << (int)(Console::instance()->drawable()->height()/resolution(xaxis)+1.) << " 0" << std::endl;
  _os << "%%LanguageLevel: 2" << std::endl;
  _os << "%%Creator: Berlin Consortium" << std::endl;
  _os << "/Times-Roman findfont 12 scalefont setfont" << std::endl;
  _os << "0 0 0 setrgbcolor" << std::endl;
  _os << resolution(xaxis) << " " << -resolution(yaxis) << " scale" << std::endl;
  _os << std::endl;
}

void PSDrawingKit::finish()
{
  _os << "%%EOF" << std::endl;
}

Warsaw::Unistring *PSDrawingKit::font_family() { return new Unistring(Unicode::to_CORBA(Babylon::String("Times Roman")));}
Warsaw::Unistring *PSDrawingKit::font_subfamily() { return new Unistring();}
Warsaw::Unistring *PSDrawingKit::font_fullname() { return new Unistring(Unicode::to_CORBA(Babylon::String("Times Roman")));}
Warsaw::Unistring *PSDrawingKit::font_style() { return new Unistring(Unicode::to_CORBA(Babylon::String("Regular")));}
Warsaw::DrawingKit::FontMetrics PSDrawingKit::font_metrics() { return Warsaw::DrawingKit::FontMetrics();}
Warsaw::DrawingKit::GlyphMetrics PSDrawingKit::glyph_metrics(Warsaw::Unichar) { return Warsaw::DrawingKit::GlyphMetrics();}
CORBA::Any *PSDrawingKit::get_font_attribute(const Warsaw::Unistring &) { return new CORBA::Any();}

void PSDrawingKit::set_transformation(Transform_ptr t)
{
  if (CORBA::is_nil(t)) _tr->load_identity();
  else _tr = Transform::_duplicate(t);
  //set_clipping(_cl);
}

void PSDrawingKit::set_clipping(Region_ptr r)
{
#if 0
  _os << "%set_clipping" << std::endl;
  _cl = Region::_duplicate(r);
  if (CORBA::is_nil(_cl))
  { 
      _os << "initclip" << std::endl;
      _os << std::endl; // disallowed in EPS
  } else {
    Vertex lower, upper;
    _cl->bounds(lower, upper);
    //_tr->transform_vertex(lower);
    //_tr->transform_vertex(upper);
    
    _os << lower.x << " " << lower.y << " " << upper.x - lower.x << " "
	<< upper.x - lower.x << " rectclip" << std::endl;
  }
  _os << std::endl;
#endif
}

void PSDrawingKit::set_foreground(const Color &c)
{
  _fg = c;
  _os << "%set_foreground" << std::endl;
  _os << (_fg.red*_lt.red) << ' ' << (_fg.green*_lt.green) << ' ' << (_fg.blue*_lt.blue)  << " setrgbcolor" << std::endl;
  _os << std::endl;
}

void PSDrawingKit::set_lighting(const Color &c)
{
  _lt = c;
  _os << "%set_lighting" << std::endl;
  _os << (_fg.red*_lt.red) << ' ' << (_fg.green*_lt.green) << ' ' << (_fg.blue*_lt.blue)  << " setrgbcolor" << std::endl;
  _os << std::endl;
}

void PSDrawingKit::set_point_size(Coord s)
{
  _ps = s;
}

void PSDrawingKit::set_line_width(Coord w)
{
  _lw = w;
  _os << "%set_line_width" << std::endl;
  _os << _lw*resolution(xaxis) << " setlinewidth" << std::endl;
  _os << std::endl;
}

void PSDrawingKit::set_line_endstyle(Warsaw::DrawingKit::Endstyle style)
{
  _es = style;
  switch (_es) {
  case Warsaw::DrawingKit::butt:  _os << 0; break; //.< Butt
  case Warsaw::DrawingKit::round: _os << 1; break; //.< Round
  case Warsaw::DrawingKit::cap:   _os << 2; break; //.< Square
  }
  _os << " setlinecap" << std::endl;
  _os << std::endl;
}

void PSDrawingKit::set_surface_fillstyle(Warsaw::DrawingKit::Fillstyle style)
{
  _fs = style;
}

void PSDrawingKit::set_texture(Raster_ptr t)
{
}

void PSDrawingKit::draw_path(const Path &path)
{
  _os << "%draw_path" << std::endl;
  _os << "newpath" << std::endl;
  Vertex v = path.nodes[path.nodes.length()-1];
  vertex(v, " moveto");
  for (unsigned long i = 1; i < path.nodes.length(); i++) {
    v = path.nodes[i];
    vertex(v, " lineto");
  }
  _os << "closepath";
  if (_fs == Warsaw::DrawingKit::solid)
    _os << " fill" << std::endl;
  else
    _os << " stroke" << std::endl;
  _os << std::endl;
}

void PSDrawingKit::draw_rectangle(const Vertex &lower, const Vertex &upper)
{
  _os << "%draw_rectangle" << std::endl;
  _os << "newpath" << std::endl;
  Vertex v;
  v.x = lower.x; v.y = lower.y; v.z = 0;
  vertex(v, " moveto");
  v.x = lower.x; v.y = upper.y; v.z = 0;
  vertex(v, " lineto");
  v.x = upper.x; v.y = upper.y; v.z = 0;
  vertex(v, " lineto");
  v.x = upper.x; v.y = lower.y; v.z = 0;
  vertex(v, " lineto");
  v.x = lower.x; v.y = lower.y; v.z = 0;
  vertex(v, " lineto");
  _os << "closepath";
  if (_fs == Warsaw::DrawingKit::solid)
    _os << " fill" << std::endl;
  else
    _os << " stroke" << std::endl;

 _os << std::endl;
}

inline void PSDrawingKit::vertex(const Vertex &x, char *c) {
  Vertex v = x;
  _tr->transform_vertex(v);
  _os << v.x*resolution(xaxis) << ' ' << v.y*resolution(yaxis) << c << std::endl;
}

void PSDrawingKit::draw_quadric(const Warsaw::DrawingKit::Quadric, Warsaw::Coord, Warsaw::Coord)
{
}

void PSDrawingKit::draw_ellipse(const Vertex &lower, const Vertex &upper)
{
}

void PSDrawingKit::draw_image(Raster_ptr raster)
{
  Raster_var r = Raster::_duplicate(raster);
  _os << "%draw_image" << std::endl;
  Warsaw::Transform::Matrix matrix;
  _tr->store_matrix(matrix);
  Vertex o; _tr->transform_vertex(o);
  o.x *= (matrix[0][0]+matrix[1][0]) * resolution(xaxis);
  o.y *= (matrix[0][1]+matrix[1][1]) * resolution(yaxis);

  _os << r->header().width << " " << r->header().height << " "
      << r->header().depth << std::endl;
  _os << "[ " << matrix[0][0]*resolution(xaxis) << " " << matrix[0][1]*resolution(xaxis) << " " << matrix[1][0]*resolution(yaxis) << " " << matrix[1][1]*resolution(yaxis) << " " << 0-o.x*resolution(xaxis) << " " << 0-o.y*resolution(yaxis) << " ]" << std::endl;
  _os << "{<" << std::endl;
  Raster::Index i;
  for (i.y = 0; i.y < r->header().height; i.y++) {
    for (i.x = 0; i.x < r->header().width; i.x++) {
      Color c;
      char color[7];
      r->store_pixel(i, c);
      sprintf(color, "%02x%02x%02x", (int)(c.red*255), (int)(c.green*255), (int)(c.blue*255));
      _os << color;
    }
    _os << std::endl;
  }
  _os << ">}" << std::endl;
  _os << "false 3 colorimage" << std::endl;
  _os << std::endl;
}

void PSDrawingKit::set_font_size(CORBA::ULong s)
{
  _os << "%set_font_size" << std::endl;
  _os << s << " scalefont" << std::endl;
  _os << std::endl;
}

void PSDrawingKit::set_font_weight(CORBA::ULong w) {}
void PSDrawingKit::set_font_family(const Unistring &f) {}
void PSDrawingKit::set_font_subfamily(const Unistring &sf) {}
void PSDrawingKit::set_font_fullname(const Unistring &fn) {}
void PSDrawingKit::set_font_style(const Unistring &s) {}
void PSDrawingKit::set_font_attribute(const NVPair & nvp) {}
void PSDrawingKit::allocate_text(const Unistring &s, Graphic::Requisition &req) {}
void PSDrawingKit::draw_text(const Unistring &us) {}

void PSDrawingKit::allocate_char(Unichar c, Graphic::Requisition &req)
{
  int width = 10;
  int height = 20;
  req.x.natural = req.x.minimum = req.x.maximum = width*10.;
  req.x.defined = true;
  req.x.align = 0.;
  req.y.natural = req.y.minimum = req.y.maximum = height*10.;
  req.y.defined = true;
  req.y.align = 1.;
}

void PSDrawingKit::draw_char(Unichar c)
{
  _os << "%draw_char" << std::endl;
  _os << "gsave" << std::endl;
  Warsaw::Transform::Matrix matrix;
  _tr->store_matrix(matrix);
  _os << matrix[0][3]*resolution(xaxis) << " " << matrix[1][3]*resolution(yaxis) << " moveto" << std::endl;
  _os << "[ " << matrix[0][0] << " " << 0-matrix[0][1] << " " << matrix[1][0] << " " << 0-matrix[1][1] << " 0 0 ] concat" << std::endl;
  _os << 1./resolution(xaxis) << " " << 1./resolution(yaxis) << " scale" << std::endl;
  _os << "(" << (char)c << ") show" << std::endl;
  _os << "grestore" << std::endl;
  _os << std::endl;
}

void PSDrawingKit::copy_drawable(Drawable_ptr d, PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) {}

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "PSDrawingKit"};
  return create_kit<PSDrawingKit> ("IDL:Warsaw/DrawingKit:1.0", properties, 2);
}
