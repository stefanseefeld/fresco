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

#include <Fresco/config.hh>
#include <Fresco/Traversal.hh>
#include <Fresco/Transform.hh>
#include <Fresco/Region.hh>
#include <Fresco/Raster.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Console.hh>
#include "DrawingKit.hh"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace Prague;
using namespace Fresco;

using namespace Berlin::DrawingKit;

PostScript::DrawingKit::DrawingKit(const std::string &id,
				   const Fresco::Kit::PropertySeq &p,
				   ServerContextImpl *c)
  : KitImpl(id, p, c),
    _os(new std::filebuf())
{
  _os.precision(5);
  _os.setf(std::ios::fixed);
  _lt.red = 1.0; _lt.green = 1.0; _lt.blue = 1.0; _lt.alpha = 1.0;
  _fg.red = 1.0; _fg.green = 1.0; _fg.blue = 1.0; _fg.alpha = 1.0;
}

PostScript::DrawingKit::~DrawingKit()
{
}

KitImpl *PostScript::DrawingKit::clone(const Fresco::Kit::PropertySeq &p,
				       ServerContextImpl *c)
{
  DrawingKit *kit = new DrawingKit(repo_id(), p, c);
  kit->init();
  return kit;
}

void PostScript::DrawingKit::start_traversal(Traversal_ptr traversal)
{
  _os.clear();
  static_cast<std::filebuf *>(_os.rdbuf())->open("berlin-output.eps", std::ios::out);

  Region_var allocation = traversal->current_allocation();
  Transform_var transformation = traversal->current_transformation();
  RegionImpl region(allocation, transformation);

  _tr->load_identity();

  Lease_var<RegionImpl> clip(Provider<RegionImpl>::provide());
  _cl = Region_var(clip->_this());

  // FIXME: figure out what is wrong with the resolution,
  //        the problems seems to be in the coordinate system used,
  //        not PS...
  //        -stefan
  double xfactor = resolution(xaxis);
  double yfactor = resolution(yaxis);

  static Transform::Matrix m =
    {{xfactor*xfactor, 0., 0., 0.},
     {0., 0.-yfactor*yfactor, 0., 0.},
     {0., 0., 1., 0.},
     {0., 0., 0., 1.}};
  TransformImpl *adjust = new TransformImpl(m);
  _tr_adjust = adjust->_this();

  Vertex lower = region.lower;
  Vertex upper = region.upper;

  _tr_adjust->transform_vertex(lower);
  _tr_adjust->transform_vertex(upper);

  Vertex translate; translate.x = 35.; translate.z = 0.;
  translate.y = lower.y - upper.y + 35.;  
  _tr_adjust->translate(translate);

  _cl_none = new RegionImpl(region);
  _cl = Region_var(_cl_none->_this());

  _os << "%!PS-Adobe-3.0 EPSF-3.0" << std::endl;
  _os.precision(0);
  _os << "%%BoundingBox: "
      << floor(region.lower.x*resolution(xaxis)*xfactor + 35.) << ' '
      << floor(region.lower.y*resolution(yaxis)*yfactor + 35.) << ' '
      << ceil((region.upper.x - region.lower.x)*resolution(xaxis)*xfactor + 35.) << ' '
      << ceil((region.upper.y - region.lower.y)*resolution(yaxis)*yfactor + 35.) << std::endl;
  _os.precision(5);
  _os << "%%HiResBoundingBox: "
      << region.lower.x*resolution(xaxis)*xfactor + 35. << ' '
      << region.lower.y*resolution(yaxis)*yfactor + 35. << ' '
      << (region.upper.x - region.lower.x)*resolution(xaxis)*xfactor + 35. << ' '
      << (region.upper.y - region.lower.y)*resolution(yaxis)*yfactor + 35. << std::endl;
  _os << "%%LanguageLevel: 2" << std::endl;
  _os << "%%Creator: Fresco" << std::endl;
  _os << "/Times-Roman findfont 112 scalefont setfont" << std::endl;
  _os << "0 0 0 setrgbcolor" << std::endl;
  _os << std::endl;
}

void PostScript::DrawingKit::finish_traversal()
{
  _os << "%%EOF" << std::endl;
  static_cast<std::filebuf *>(_os.rdbuf())->close();
}

Fresco::Unistring *PostScript::DrawingKit::font_family() { return new Unistring(Unicode::to_CORBA(Babylon::String("Times Roman")));}
Fresco::Unistring *PostScript::DrawingKit::font_subfamily() { return new Unistring();}
Fresco::Unistring *PostScript::DrawingKit::font_fullname() { return new Unistring(Unicode::to_CORBA(Babylon::String("Times Roman")));}
Fresco::Unistring *PostScript::DrawingKit::font_style() { return new Unistring(Unicode::to_CORBA(Babylon::String("Regular")));}
Fresco::DrawingKit::FontMetrics PostScript::DrawingKit::font_metrics() { return Fresco::DrawingKit::FontMetrics();}
Fresco::DrawingKit::GlyphMetrics PostScript::DrawingKit::glyph_metrics(Fresco::Unichar) { return Fresco::DrawingKit::GlyphMetrics();}
CORBA::Any *PostScript::DrawingKit::get_font_attribute(const Fresco::Unistring &) { return new CORBA::Any();}

void PostScript::DrawingKit::set_transformation(Transform_ptr t)
{
  if (CORBA::is_nil(t)) _tr->load_identity();
  else _tr = Transform::_duplicate(t);
}

void PostScript::DrawingKit::set_clipping(Region_ptr r)
{
  _cl = Region::_duplicate(r);
#if 0
  _os << "%set_clipping" << std::endl;
  Vertex lower, upper;
  if (CORBA::is_nil(_cl))
  {
    _cl_none->bounds(lower, upper);
    _os << "%none" << std::endl;
  } else {
    _cl->bounds(lower, upper);
    _os << "%real" << std::endl;
  }
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
  _os << "closepath clip" << std::endl;
  _os << std::endl;

  // uncomment this to debug clipping
#if 0
  _os << "0 0 0 99999 99999 99999 99999 0 1 0 0 setrgbcolor moveto lineto lineto lineto closepath fill";
  set_foreground(_fg);
#endif
#endif
}

void PostScript::DrawingKit::set_foreground(const Color &c)
{
  _fg = c;
  _os << "%set_foreground" << std::endl;
  _os << (_fg.red*_lt.red) << ' ' << (_fg.green*_lt.green) << ' ' << (_fg.blue*_lt.blue)  << " setrgbcolor" << std::endl;
  _os << std::endl;
}

void PostScript::DrawingKit::set_lighting(const Color &c)
{
  _lt = c;
  _os << "%set_lighting" << std::endl;
  _os << (_fg.red*_lt.red) << ' ' << (_fg.green*_lt.green) << ' ' << (_fg.blue*_lt.blue)  << " setrgbcolor" << std::endl;
  _os << std::endl;
}

void PostScript::DrawingKit::set_point_size(Coord s)
{
  _ps = s;
}

void PostScript::DrawingKit::set_line_width(Coord w)
{
  _lw = w;
  _os << "%set_line_width" << std::endl;
  _os << _lw*resolution(xaxis) << " setlinewidth" << std::endl;
  _os << std::endl;
}

void PostScript::DrawingKit::set_line_endstyle(Fresco::DrawingKit::Endstyle style)
{
  _es = style;
  switch (_es) {
  case Fresco::DrawingKit::butt:  _os << 0; break; //.< Butt
  case Fresco::DrawingKit::round: _os << 1; break; //.< Round
  case Fresco::DrawingKit::cap:   _os << 2; break; //.< Square
  }
  _os << " setlinecap" << std::endl;
  _os << std::endl;
}

void PostScript::DrawingKit::set_surface_fillstyle(Fresco::DrawingKit::Fillstyle style)
{
  _fs = style;
}

void PostScript::DrawingKit::set_texture(Raster_ptr t)
{
}

void PostScript::DrawingKit::draw_path(const Fresco::Path &path)
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
  if (_fs == Fresco::DrawingKit::solid)
    _os << " fill" << std::endl;
  else
    _os << " stroke" << std::endl;
  _os << std::endl;
}

void PostScript::DrawingKit::draw_new_path(const Fresco::NewPath &path)
{
}

void PostScript::DrawingKit::draw_rectangle(const Vertex &lower, const Vertex &upper)
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
  if (_fs == Fresco::DrawingKit::solid)
    _os << " fill" << std::endl;
  else
    _os << " stroke" << std::endl;

 _os << std::endl;
}

inline void PostScript::DrawingKit::vertex(const Vertex &x, const char *c) {
  Vertex v = x;
  _tr->transform_vertex(v);
  _tr_adjust->transform_vertex(v);
  _os << v.x << ' ' << v.y << c << std::endl;
}

void PostScript::DrawingKit::draw_quadric(const Fresco::DrawingKit::Quadric, Fresco::Coord, Fresco::Coord)
{
}

void PostScript::DrawingKit::draw_ellipse(const Vertex &lower, const Vertex &upper)
{
}

void PostScript::DrawingKit::draw_image(Raster_ptr raster)
{
  Raster_var r = Raster::_duplicate(raster);
  _os << "%draw_image" << std::endl;

  _os << r->header().width << " " << r->header().height << " "
      << r->header().depth << std::endl;
  {
  Vertex o = {0., 0., 0.};
  Vertex i = {1.28354, 0., 0.};
  Vertex j = {0., 1.28354, 0.};
  _tr->transform_vertex(o);
  _tr->transform_vertex(i);
  _tr->transform_vertex(j);
  _os << "[ " << i.x-o.x << " " << i.y-o.y
      << " "  << j.x-o.x << " " << -j.y+o.y;
  _tr_adjust->transform_vertex(o);
  _os << " "  << -o.x*resolution(xaxis) << " " << o.y*resolution(yaxis) << " ]" << std::endl;
  }

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

//FIXME: what units is our font size in?
void PostScript::DrawingKit::set_font_size(CORBA::ULong s)
{
  _os << "%set_font_size" << std::endl;
  _os << s << " scalefont" << std::endl;
  _os << std::endl;
}

void PostScript::DrawingKit::set_font_weight(CORBA::ULong w) {}
void PostScript::DrawingKit::set_font_family(const Unistring &f) {}
void PostScript::DrawingKit::set_font_subfamily(const Unistring &sf) {}
void PostScript::DrawingKit::set_font_fullname(const Unistring &fn) {}
void PostScript::DrawingKit::set_font_style(const Unistring &s) {}
void PostScript::DrawingKit::set_font_attribute(const NVPair & nvp) {}
void PostScript::DrawingKit::allocate_text(const Unistring &s, Graphic::Requisition &req) {}
void PostScript::DrawingKit::draw_text(const Unistring &us) {}

void PostScript::DrawingKit::allocate_char(Unichar c, Graphic::Requisition &req)
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

void PostScript::DrawingKit::draw_char(Unichar c)
{
  _os << "%draw_char" << std::endl;
  _os << "gsave" << std::endl;
  Vertex o = {0., 0., 0.}; vertex(o, " moveto");
  Vertex i = {1., 0., 0.};
  Vertex j = {0., 1., 0.};
  _tr->transform_vertex(o);
  _tr_adjust->transform_vertex(o);
  _tr->transform_vertex(i);
  _tr_adjust->transform_vertex(i);
  _tr->transform_vertex(j);
  _tr_adjust->transform_vertex(j);
  // this is transposed from what makes sense to my brain.
  _os << "[ " << i.x-o.x << " " << j.x-o.x
      << " "  << o.y-i.y << " " << o.y-j.y
      << " 0 0 ] concat" << std::endl;
  
  char x[2];
  sprintf(x, "%02x", (int)c);
  _os << "<" << x << "> show" << std::endl;
  _os << "grestore" << std::endl;
  _os << std::endl;
}

void PostScript::DrawingKit::copy_drawable(Drawable_ptr d, PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) {}

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "PSDrawingKit"};
  return create_prototype<PostScript::DrawingKit>("IDL:fresco.org/Fresco/DrawingKit:1.0", properties, 2);
}
