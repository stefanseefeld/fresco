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
				   ServerContextImpl *c) :
    KitImpl(id, p, c),
    my_os(new std::filebuf())
{
    my_os.precision(5);
    my_os.setf(std::ios::fixed);
    my_lt.red = 1.0; my_lt.green = 1.0; my_lt.blue = 1.0;
    my_lt.alpha = 1.0;
    my_fg.red = 1.0; my_fg.green = 1.0; my_fg.blue = 1.0;
    my_fg.alpha = 1.0;
}

PostScript::DrawingKit::~DrawingKit() { }

Berlin::KitImpl *
PostScript::DrawingKit::clone(const Fresco::Kit::PropertySeq &p,
			      ServerContextImpl *c)
{
    DrawingKit *kit = new DrawingKit(repo_id(), p, c);
    kit->init();
    return kit;
}

void PostScript::DrawingKit::start_traversal(Traversal_ptr traversal)
{
    my_os.clear();
    static_cast<std::filebuf *>(my_os.rdbuf())->open("berlin-output.eps",
						     std::ios::out);

    Region_var allocation = traversal->current_allocation();
    Transform_var transformation = traversal->current_transformation();
    RegionImpl region(allocation, transformation);

    my_tr->load_identity();

    Lease_var<RegionImpl> clip(Provider<RegionImpl>::provide());
    my_cl = Region_var(clip->_this());

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
    my_tr_adjust = adjust->_this();

    Vertex lower = region.lower;
    Vertex upper = region.upper;

    my_tr_adjust->transform_vertex(lower);
    my_tr_adjust->transform_vertex(upper);

    Vertex translate; translate.x = 35.; translate.z = 0.;
    translate.y = lower.y - upper.y + 35.;  
    my_tr_adjust->translate(translate);

    my_cl_none = new RegionImpl(region);
    my_cl = Region_var(my_cl_none->_this());

    my_os << "%!PS-Adobe-3.0 EPSF-3.0" << std::endl;
    my_os.precision(0);
    my_os << "%%BoundingBox: "
	  << floor(region.lower.x*resolution(xaxis)*xfactor + 35.) << ' '
	  << floor(region.lower.y*resolution(yaxis)*yfactor + 35.) << ' '
	  << ceil((region.upper.x - region.lower.x)*
		  resolution(xaxis)*xfactor + 35.)
	  << ' '
	  << ceil((region.upper.y - region.lower.y)*
		  resolution(yaxis)*yfactor + 35.) << std::endl;
    my_os.precision(5);
    my_os << "%%HiResBoundingBox: "
	  << region.lower.x*resolution(xaxis)*xfactor + 35. << ' '
	  << region.lower.y*resolution(yaxis)*yfactor + 35. << ' '
	  << (region.upper.x - region.lower.x)*resolution(xaxis)*xfactor + 
	     35. << ' '
	  << (region.upper.y - region.lower.y)*resolution(yaxis)*yfactor +
             35. << std::endl
	  << "%%LanguageLevel: 2" << std::endl
	  << "%%Creator: Fresco" << std::endl
	  << "/Times-Roman findfont 112 scalefont setfont" << std::endl
	  << "0 0 0 setrgbcolor" << std::endl
	  << std::endl;
}

void PostScript::DrawingKit::finish_traversal()
{
    my_os << "%%EOF" << std::endl;
    static_cast<std::filebuf *>(my_os.rdbuf())->close();
}

Fresco::Unistring *PostScript::DrawingKit::font_family()
{
    return
	new Unistring(Unicode::to_CORBA(Babylon::String("Times Roman")));
}
Fresco::Unistring *PostScript::DrawingKit::font_subfamily()
{ return new Unistring(); }
Fresco::Unistring *PostScript::DrawingKit::font_fullname()
{
    return
	new Unistring(Unicode::to_CORBA(Babylon::String("Times Roman")));
}
Fresco::Unistring *PostScript::DrawingKit::font_style()
{ return new Unistring(Unicode::to_CORBA(Babylon::String("Regular"))); }
Fresco::DrawingKit::FontMetrics PostScript::DrawingKit::font_metrics()
{ return Fresco::DrawingKit::FontMetrics(); }
Fresco::DrawingKit::GlyphMetrics
PostScript::DrawingKit::glyph_metrics(Fresco::Unichar)
{ return Fresco::DrawingKit::GlyphMetrics(); }
CORBA::Any *
PostScript::DrawingKit::get_font_attribute(const Fresco::Unistring &)
{ return new CORBA::Any(); }

void PostScript::DrawingKit::set_transformation(Transform_ptr t)
{
    if (CORBA::is_nil(t)) my_tr->load_identity();
    else my_tr = Transform::_duplicate(t);
}

void PostScript::DrawingKit::set_clipping(Region_ptr r)
{
    my_cl = Region::_duplicate(r);
#if 0
    my_os << "%set_clipping" << std::endl;
    Vertex lower, upper;
    if (CORBA::is_nil(_cl))
    {
	my_cl_none->bounds(lower, upper);
	my_os << "%none" << std::endl;
    } else {
	my_cl->bounds(lower, upper);
	my_os << "%real" << std::endl;
    }
    my_os << "newpath" << std::endl;
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
    my_os << "closepath clip" << std::endl;
    my_os << std::endl;

    // uncomment this to debug clipping
#if 0
    my_os << "0 0 0 99999 99999 99999 99999 0 1 0 0 setrgbcolor moveto lineto lineto lineto closepath fill";
    set_foreground(_fg);
#endif
#endif
}

void PostScript::DrawingKit::set_foreground(const Color &c)
{
    my_fg = c;
    my_os << "%set_foreground" << std::endl
	  << (my_fg.red*my_lt.red) << ' '
	  << (my_fg.green*my_lt.green) << ' '
	  << (my_fg.blue*my_lt.blue)  << " setrgbcolor" << std::endl
	  << std::endl;
}

void PostScript::DrawingKit::set_lighting(const Color &c)
{
    my_lt = c;
    my_os << "%set_lighting" << std::endl
	  << (my_fg.red*my_lt.red) << ' '
	  << (my_fg.green*my_lt.green) << ' '
	  << (my_fg.blue*my_lt.blue)  << " setrgbcolor" << std::endl
	  << std::endl;
}

void PostScript::DrawingKit::set_point_size(Coord s)
{
    my_ps = s;
}

void PostScript::DrawingKit::set_line_width(Coord w)
{
    my_lw = w;
    my_os << "%set_line_width" << std::endl
	  << my_lw*resolution(xaxis) << " setlinewidth" << std::endl
	  << std::endl;
}

void
PostScript::DrawingKit::set_line_endstyle(Fresco::DrawingKit::Endstyle style)
{
    my_es = style;
    switch (my_es)
    {
    case Fresco::DrawingKit::butt:  my_os << 0; break; //.< Butt
    case Fresco::DrawingKit::round: my_os << 1; break; //.< Round
    case Fresco::DrawingKit::cap:   my_os << 2; break; //.< Square
    }
    my_os << " setlinecap" << std::endl << std::endl;
}

void PostScript::DrawingKit::set_surface_fillstyle(Fresco::DrawingKit::Fillstyle style)
{
    my_fs = style;
}

void PostScript::DrawingKit::set_texture(Raster_ptr t) { }

void PostScript::DrawingKit::draw_path(const Fresco::Path &path)
{
    my_os << "%draw_path" << std::endl
	  << "newpath" << std::endl;
    Vertex v = path.nodes[path.nodes.length()-1];
    vertex(v, " moveto");
    for (unsigned long i = 1; i < path.nodes.length(); ++i)
    {
	v = path.nodes[i];
	vertex(v, " lineto");
    }
    my_os << "closepath";
    if (my_fs == Fresco::DrawingKit::solid)
	my_os << " fill" << std::endl;
    else
	my_os << " stroke" << std::endl;
    my_os << std::endl;
}

void PostScript::DrawingKit::draw_new_path(const Fresco::NewPath &path)
{ }

void PostScript::DrawingKit::draw_rectangle(const Vertex &lower,
					    const Vertex &upper)
{
    my_os << "%draw_rectangle" << std::endl
	  << "newpath" << std::endl;
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
    my_os << "closepath";
    if (my_fs == Fresco::DrawingKit::solid)
	my_os << " fill" << std::endl;
    else
	my_os << " stroke" << std::endl;

    my_os << std::endl;
}

inline void PostScript::DrawingKit::vertex(const Vertex &x,
					   const char *c)
{
    Vertex v = x;
    my_tr->transform_vertex(v);
    my_tr_adjust->transform_vertex(v);
    my_os << v.x << ' ' << v.y << c << std::endl;
}

void
PostScript::DrawingKit::draw_quadric(const Fresco::DrawingKit::Quadric,
				     Fresco::Coord, Fresco::Coord)
{ }

void PostScript::DrawingKit::draw_ellipse(const Vertex &lower,
					  const Vertex &upper)
{ }

void PostScript::DrawingKit::draw_image(Raster_ptr raster)
{
    Raster_var r = Raster::_duplicate(raster);
    my_os << "%draw_image" << std::endl
	  << r->header().width << " " << r->header().height << " "
	  << r->header().depth << std::endl;
    {
	Vertex o = {0., 0., 0.};
	Vertex i = {1.28354, 0., 0.};
	Vertex j = {0., 1.28354, 0.};
	my_tr->transform_vertex(o);
	my_tr->transform_vertex(i);
	my_tr->transform_vertex(j);
	my_os << "[ " << i.x-o.x << " " << i.y-o.y
	      << " "  << j.x-o.x << " " << -j.y+o.y;
	my_tr_adjust->transform_vertex(o);
	my_os << " "  << -o.x*resolution(xaxis)
	      << " "  << o.y*resolution(yaxis) << " ]" << std::endl;
    }

    my_os << "{<" << std::endl;
    Raster::Index i;
    for (i.y = 0; i.y < r->header().height; i.y++) {
	for (i.x = 0; i.x < r->header().width; i.x++) {
	    Color c;
	    char color[7];
	    r->store_pixel(i, c);
	    sprintf(color, "%02x%02x%02x",
		    (int)(c.red*255),
		    (int)(c.green*255),
		    (int)(c.blue*255));
	    my_os << color;
	}
	my_os << std::endl;
    }
    my_os << ">}" << std::endl
	  << "false 3 colorimage" << std::endl
	  << std::endl;
}

//FIXME: what units is our font size in?
void PostScript::DrawingKit::set_font_size(CORBA::ULong s)
{
  my_os << "%set_font_size" << std::endl
	<< s << " scalefont" << std::endl
	<< std::endl;
}

void PostScript::DrawingKit::set_font_weight(CORBA::ULong w) { }
void PostScript::DrawingKit::set_font_family(const Unistring &f) { }
void PostScript::DrawingKit::set_font_subfamily(const Unistring &sf) { }
void PostScript::DrawingKit::set_font_fullname(const Unistring &fn) { }
void PostScript::DrawingKit::set_font_style(const Unistring &s) { }
void PostScript::DrawingKit::set_font_attribute(const NVPair & nvp) { }
void PostScript::DrawingKit::allocate_text(const Unistring &s,
					   Graphic::Requisition &req) { }
void PostScript::DrawingKit::draw_text(const Unistring &us) { }

void PostScript::DrawingKit::allocate_char(Unichar c,
					   Graphic::Requisition &req)
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
    my_os << "%draw_char" << std::endl
	  << "gsave" << std::endl;
    Vertex o = {0., 0., 0.}; vertex(o, " moveto");
    Vertex i = {1., 0., 0.};
    Vertex j = {0., 1., 0.};
    my_tr->transform_vertex(o);
    my_tr_adjust->transform_vertex(o);
    my_tr->transform_vertex(i);
    my_tr_adjust->transform_vertex(i);
    my_tr->transform_vertex(j);
    my_tr_adjust->transform_vertex(j);
    // this is transposed from what makes sense to my brain.
    my_os << "[ " << i.x-o.x << " " << j.x-o.x
	  << " "  << o.y-i.y << " " << o.y-j.y
	  << " 0 0 ] concat" << std::endl;
  
    char x[2];
    sprintf(x, "%02x", (int)c);
    my_os << "<" << x << "> show" << std::endl
	  << "grestore" << std::endl
	  << std::endl;
}

void PostScript::DrawingKit::copy_drawable(Drawable_ptr d,
					   PixelCoord x, PixelCoord y,
					   PixelCoord w, PixelCoord h) { }

extern "C" Berlin::KitImpl *load()
{
    static std::string properties[] = {"implementation", "PSDrawingKit"};
    return Berlin::create_prototype<PostScript::DrawingKit>("IDL:fresco.org/Fresco/DrawingKit:1.0", properties, 2);
}
