/*$Id$
 *
 * This source file is a part of the Fresco Project.
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

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/Transform.hh>
#include <Fresco/IO.hh>
#include <Berlin/Provider.hh>
#include "DrawingKit.hh"
#include "FTFont.hh"
#include "Unifont.hh"

#include <libart_lgpl/art_pathcode.h>
#include <libart_lgpl/art_pixbuf.h>
#include <libart_lgpl/art_affine.h>
#include <libart_lgpl/art_rect.h>
#include <libart_lgpl/art_vpath.h>
#include <libart_lgpl/art_svp.h>
#include <libart_lgpl/art_svp_vpath.h>
#include <libart_lgpl/art_svp_wind.h>
#include <libart_lgpl/art_rect_svp.h>
#include <libart_lgpl/art_rgb_svp.h>
#include <libart_lgpl/art_rgb_pixbuf_affine.h>

#include <memory>

using namespace Fresco;
using namespace Berlin::DrawingKit;

libArt::DrawingKit::~DrawingKit() { }

libArt::DrawingKit::DrawingKit(const std::string &id,
                               const Fresco::Kit::PropertySeq &p,
			       ServerContextImpl *c) :
    KitImpl(id, p, c),
    my_drawable(0),
    my_xres(1.),
    my_yres(1.),
    my_font(0),
    my_unifont(0),
    my_rasters(500)
    // textures(100), 
    // tx(0)
{
    my_lt.red = 1.0; my_lt.green = 1.0; my_lt.blue = 1.0;
    my_lt.alpha = 1.0;
    my_fg.red = 1.0; my_fg.green = 1.0; my_fg.blue = 1.0;
    my_fg.alpha = 1.0;
}

Berlin::KitImpl *
libArt::DrawingKit::clone(const Fresco::Kit::PropertySeq &p,
			  ServerContextImpl *c)
{
    libArt::DrawingKit *kit = new libArt::DrawingKit(repo_id(), p, c);
    kit->init();
    return kit;
}

void libArt::DrawingKit::init()
{
    Console *console = Console::instance();
    my_drawable = console->drawable();
    my_xres = my_drawable->resolution(xaxis);
    my_yres = my_drawable->resolution(yaxis);
    my_font = new FTFont(my_xres, my_yres);
    my_unifont = new Unifont(my_xres, my_yres);
    my_screen.x0 = 0;
    my_screen.y0 = 0;
    my_screen.x1 = my_drawable->width();
    my_screen.y1 = my_drawable->height();
  
    my_agam = art_alphagamma_new(2.5);
    my_buffer = console->create_drawable(my_drawable->width(),
					 my_drawable->height(), 3);
    my_renderer =
	console->get_extension<Console_Extension::Renderer>("Renderer");
    my_renderer->attach(my_buffer);
    my_direct = console->
	get_extension<Console_Extension::DirectBuffer>("DirectBuffer");
    my_direct->attach(my_buffer);
    my_bbox.x0 = my_bbox.y0 = my_bbox.x1 = my_bbox.y1 = 0;    
    double step = 1. / 256.;
    for (int i = 0; i < 256; ++i)
	for (int j = 0; j < 256; ++j) 
	    my_alphabank[i][j] = (art_u8)(i * (j * step));
}

namespace
{
  inline art_u32 artColor(const Color &c)
  {
      return (((art_u8)(c.blue * 0xff) << 24) | 
	      ((art_u8)(c.green * 0xff) << 16) | 
	      ((art_u8)(c.red * 0xff) << 8) | 
	      ((art_u8)(c.alpha * 0xff)));
  }

  inline void fix_order_of_irect(ArtIRect &ir)
  {
      if (ir.x0 > ir.x1) {int tmp = ir.x0; ir.x1 = ir.x0; ir.x0 = tmp;}
      if (ir.y0 > ir.y1) {int tmp = ir.y0; ir.y0 = ir.y1; ir.y1 = tmp;}
  }
} // namespace

void libArt::DrawingKit::set_transformation(Transform_ptr t)
{
    Prague::Trace trace("libArt::DrawingKit::set_transformation");
    if (CORBA::is_nil(t)) art_affine_identity(my_affine);
    else
    {
	my_tr = Transform::_duplicate(t);
	Transform::Matrix matrix;
	my_tr->store_matrix(matrix);
	my_affine[0] = matrix[0][0];
	my_affine[1] = matrix[1][0];
	my_affine[2] = matrix[0][1];
	my_affine[3] = matrix[1][1];
	my_affine[4] = matrix[0][3];
	my_affine[5] = matrix[1][3];
    }
    my_scaled_affine[0] = my_affine[0] * my_xres;
    my_scaled_affine[1] = my_affine[1] * my_xres;
    my_scaled_affine[2] = my_affine[2] * my_yres;
    my_scaled_affine[3] = my_affine[3] * my_yres;
    my_scaled_affine[4] = my_affine[4] * my_xres;
    my_scaled_affine[5] = my_affine[5] * my_yres;
}

void libArt::DrawingKit::set_clipping(Region_ptr r)
{
    if (CORBA::is_nil(r))
    {
	my_clip = my_screen;
	return; 
    }
    my_cl = Region::_duplicate(r);
    
    Lease_var<RegionImpl> climpl(Provider<RegionImpl>::provide());
    climpl->copy(my_cl);

    ArtDRect dclip = {climpl->lower.x * my_xres,
		      climpl->lower.y * my_yres, 		      
		      climpl->upper.x * my_xres,
		      climpl->upper.y * my_yres};
    art_drect_to_irect(&my_clip, &dclip); 
    art_irect_intersect(&my_clip, &my_clip, &my_screen);
}

void libArt::DrawingKit::set_foreground(const Color &c)
{
    my_fg = c;
    my_con_fg.red   = my_fg.red * my_lt.red;
    my_con_fg.green = my_fg.green * my_lt.green;
    my_con_fg.blue  = my_fg.blue * my_lt.blue;
    my_con_fg.alpha = my_fg.alpha;
    my_art_fg       = artColor(my_con_fg);
}

void libArt::DrawingKit::set_lighting(const Color &c)
{
    my_lt = c;
    my_con_fg.red   = my_fg.red * my_lt.red;
    my_con_fg.green = my_fg.green * my_lt.green;
    my_con_fg.blue  = my_fg.blue * my_lt.blue;
    my_art_fg       = artColor(my_con_fg);
}

void libArt::DrawingKit::set_point_size(Coord s) { my_ps = s; }
void libArt::DrawingKit::set_line_width(Coord w) { my_lw = w; }
void libArt::DrawingKit::set_line_endstyle(Fresco::DrawingKit::Endstyle style)
{ my_es = style; }
void libArt::DrawingKit::set_surface_fillstyle(Fresco::DrawingKit::Fillstyle style)
{ my_fs = style; }
void libArt::DrawingKit::set_texture(Raster_ptr t) { }
void libArt::DrawingKit::set_font_size(CORBA::ULong) { }
void libArt::DrawingKit::set_font_weight(CORBA::ULong) { }
void libArt::DrawingKit::set_font_family(const Unistring&) { }
void libArt::DrawingKit::set_font_subfamily(const Unistring&) { }
void libArt::DrawingKit::set_font_fullname(const Unistring&) { }
void libArt::DrawingKit::set_font_style(const Unistring&) { }
void libArt::DrawingKit::set_font_attribute(const NVPair & nvp) { }

void libArt::DrawingKit::draw_path(const Path &p) 
{
    int len = p.nodes.length();
    ArtVpath vpath[my_fs == Fresco::DrawingKit::outlined ? len : len + 1];
    ArtVpath *tvpath;  

    if (my_fs == Fresco::DrawingKit::outlined)
    {
	for (int i = 0; i < len; ++i)
	{
	    vpath[i].x = p.nodes[i].x; 
	    vpath[i].y = p.nodes[i].y;
	    vpath[i].code = ART_LINETO;
	}
	vpath[0].code = ART_MOVETO_OPEN;
	vpath[len-1].code = ART_END;
      
    }
    else
    {
	for (int i = 0; i < len; ++i)
	{
	    vpath[i].x = p.nodes[i].x; 
	    vpath[i].y = p.nodes[i].y;
	    vpath[i].code = ART_LINETO;
	}
	vpath[0].code = ART_MOVETO;
	vpath[len].x = vpath[0].x;
	vpath[len].y = vpath[0].y;
	vpath[len].code = ART_END;
    }
    
    ArtDRect locd; ArtIRect loc;
    tvpath = art_vpath_affine_transform(vpath, my_scaled_affine);
    ArtSVP *svp1 = art_svp_from_vpath(tvpath); 
    ArtSVP *svp2 = art_svp_uncross(svp1);
    ArtSVP *svp = art_svp_rewind_uncrossed(svp2, ART_WIND_RULE_ODDEVEN);

    art_drect_svp(&locd, svp);
    art_drect_to_irect(&loc, &locd);
    art_irect_intersect(&loc, &loc ,&my_clip);
    art_irect_union(&my_bbox, &my_bbox, &loc);
    fix_order_of_irect(loc);
    Console_Extension::DirectBuffer::Guard pb_buf =
	my_direct->write_buffer();
    ArtPixBuf * pb = art_pixbuf_new_const_rgb ((art_u8 *)(pb_buf.get()),
					       my_drawable->width(),
					       my_drawable->height(),
					       my_buffer->row_length());
    art_rgb_svp_alpha(svp, loc.x0, loc.y0, loc.x1, loc.y1, my_art_fg,
		      (art_u8 *)(pb_buf.get()) +
		      (loc.y0 * pb->rowstride) +
		      (loc.x0 * 3), 
		      my_buffer->row_length(), my_agam);
    art_svp_free(svp);
    art_svp_free(svp1);
    art_svp_free(svp2);
}

void libArt::DrawingKit::draw_new_path(const NewPath &p) { }

//void libArt;;DrawingKit::drawPatch(const Patch &);

void libArt::DrawingKit::draw_rectangle(const Vertex &bot,
					const Vertex &top) 
{
    // fast path opaque non-transformed rectangles
    if (my_fg.alpha == 1. &&
	my_affine[0] == 1 &&
	my_affine[1] == 0 &&
	my_affine[2] == 0 &&
	my_affine[3] == 1)
    {
	ArtIRect rect;
	rect.x0 = (int)((bot.x + my_affine[4]) * my_xres);
	rect.x1 = (int)((top.x  + my_affine[4])* my_xres);
	rect.y0 = (int)((bot.y + my_affine[5]) * my_yres);
	rect.y1 = (int)((top.y + my_affine[5]) * my_yres);
	art_irect_intersect(&rect, &rect, &my_clip);
	int width = (rect.x1 - rect.x0);
	int height = (rect.y1 - rect.y0);
	if ((height * width) < 1) return;
	my_renderer->set_color(my_con_fg);
	if (my_fs == Fresco::DrawingKit::solid)
	    my_renderer->draw_box(rect.x0, rect.y0, width, height);
	else
	{
	    my_renderer->draw_hline(rect.x0, rect.y0, width);
	    my_renderer->draw_hline(rect.x0, rect.y1, width);
	    my_renderer->draw_vline(rect.x0, rect.y0, height);
	    my_renderer->draw_vline(rect.x1, rect.y0, height);
	}
	art_irect_union (&my_bbox, &my_bbox, &rect);
	return;
	
	// non-degenerate rectangles
    }
    else
    {
	Path path;
	if (my_fs == Fresco::DrawingKit::outlined)
	{
	    path.nodes.length(4);
	    path.nodes[0].x = bot.x, path.nodes[0].y = bot.y;
	    path.nodes[1].x = top.x, path.nodes[1].y = bot.y;
	    path.nodes[2].x = top.x, path.nodes[2].y = top.y;
	    path.nodes[3].x = bot.x, path.nodes[2].y = top.y;
	    path.shape = convex;
	}
	else
	{
	    path.nodes.length(5);
	    path.nodes[0].x = bot.x, path.nodes[0].y = bot.y;
	    path.nodes[1].x = top.x, path.nodes[1].y = bot.y;
	    path.nodes[2].x = top.x, path.nodes[2].y = top.y;
	    path.nodes[3].x = bot.x, path.nodes[3].y = top.y;
	    path.nodes[4].x = bot.x, path.nodes[4].y = bot.y;
	    path.shape = convex;
	}
	draw_path(static_cast<const Path>(path));
    }
}

void libArt::DrawingKit::draw_quadric(const Fresco::DrawingKit::Quadric,
		                      Fresco::Coord, Fresco::Coord) { }

void libArt::DrawingKit::draw_ellipse(const Vertex &, const Vertex &) { }

void libArt::DrawingKit::draw_image(Raster_ptr remote)
{
  rasterize_pixbuf(my_rasters.lookup(Fresco::Raster::_duplicate(remote))->pixbuf);
}

void libArt::DrawingKit::identity_pixbuf(ArtPixBuf *pixbuf)
{
    // fast path for non-transformed grey-scale glyph images
    ArtIRect rect;
    rect.x0 = (int)(my_affine[4] * my_xres);
    rect.x1 = rect.x0 + pixbuf->width;
    rect.y0 = (int)(my_affine[5] * my_yres);
    rect.y1 = rect.y0 + pixbuf->height;
  
    // work out offset within source image
    int dx = my_clip.x0 - rect.x0;
    int dy = my_clip.y0 - rect.y0;
    if (dx < 0) dx = 0;
    if (dy < 0) dy = 0;

    art_irect_intersect(&rect, &rect, &my_clip);
    if (((rect.y1 - rect.y0) * (rect.x1 - rect.x0)) < 1) return;
    Console_Extension::DirectBuffer::Guard pb_buf =
	my_direct->write_buffer();
    ArtPixBuf * pb = art_pixbuf_new_const_rgb ((art_u8 *)(pb_buf.get()),
					       my_drawable->width(),
					       my_drawable->height(),
					       my_buffer->row_length());
    art_u8 *dst = pb->pixels + rect.y0 * pb->rowstride + rect.x0 * 3;
    art_u8 *src = pixbuf->pixels + dy * pixbuf->rowstride + dx;
    int width = (rect.x1 - rect.x0);
    int height = (rect.y1 - rect.y0);  
    art_u8 *atab = my_alphabank[(art_u8)(my_art_fg & 0xff)];
    art_u8 *rtab = my_alphabank[(art_u8)((my_art_fg >> 24) & 0xff)];
    art_u8 *gtab = my_alphabank[(art_u8)((my_art_fg >> 16) & 0xff)];
    art_u8 *btab = my_alphabank[(art_u8)((my_art_fg >> 8) & 0xff)];

    int t;
    int dst_skip = pb->rowstride - width * 3;
    int src_skip = pixbuf->rowstride - width;
    art_u8 *ptab;

    for (int row = 0;
	 row < height;
	 ++row, dst += dst_skip, src += src_skip)
	for (int col = 0;
	     col < width;
	     ++col, dst += 3, ++src)
	{            
	    ptab = my_alphabank[*src];
	    dst[0] = t = dst[0] + atab[rtab[*src]] - atab[ptab[dst[0]]]; 
	    t &= 0x100; t >>= 8; t -= 1; t =~ t; dst[0] |= (t & 0xff);
	    dst[1] = t = dst[1] + atab[gtab[*src]] - atab[ptab[dst[1]]]; 
	    t &= 0x100; t >>= 8; t -= 1; t =~ t; dst[1] |= (t & 0xff);
	    dst[2] = t = dst[2] + atab[btab[*src]] - atab[ptab[dst[2]]]; 
	    t &= 0x100; t >>= 8; t -= 1; t =~ t; dst[2] |= (t & 0xff);
	}
    art_irect_union (&my_bbox, &my_bbox, &rect);
}


void libArt::DrawingKit::rasterize_pixbuf(ArtPixBuf *pixbuf)
{
  
    // NOTE: this entire routine takes place "in device space"
    // since that is (a) the source of the raster and (b) the destination
    // of libart's transformation. the goal is to get everything into
    // device space and work with it there.
  
    double dev_affine[6] = {my_affine[0], my_affine[1],
			    my_affine[2], my_affine[3],
			    my_affine[4] * my_xres,
			    my_affine[5] * my_yres};
  			      
    // pre-transformation target rectangle, in device space coords
    ArtDRect slocd = {0,0,(double)(pixbuf->width),
		      (double)(pixbuf->height)};
    ArtDRect tslocd; 
    ArtIRect tsloci; 

    int width = pixbuf->width;
    int pix = ((pixbuf->n_channels * pixbuf->bits_per_sample + 7) >> 3); 
    int row = (width) * pix;
    int skip = (pixbuf->rowstride - row);
    int size = (my_fg.alpha == 1. ? 0 :
		(pixbuf->height - 1) * pixbuf->rowstride + width * pix);      

    art_u8 tmp[size];
    art_u8 *save = pixbuf->pixels;

    // alpha-correct the image
    if (my_fg.alpha != 1.)
    {
	art_u8 *end_write = tmp + (size - 1);
	art_u8 *reader = pixbuf->pixels;
	art_u8 *tab = my_alphabank[(art_u8)(my_art_fg & 0x000000ff)];
	art_u8 *eol;
	for (art_u8 *writer = tmp;
	     writer < end_write;
	     reader += skip, writer += skip)
	{
	    memcpy(writer,reader,row);
	    eol = writer + row;      
	    while (writer < eol)
	    {
		writer += 3; reader += 3;
		*writer++ = *(tab + *reader++);      
	    }
	}
	pixbuf->pixels = tmp;
    }
  
    // transform target (in device space)
    art_drect_affine_transform(&tslocd, &slocd, dev_affine); 
    art_drect_to_irect(&tsloci, &tslocd); 
    fix_order_of_irect(tsloci); 
  
    // clip 
    art_irect_intersect(&tsloci, &tsloci, &my_clip);
    art_irect_union (&my_bbox, &my_bbox, &tsloci);
  
    // paint
    Console_Extension::DirectBuffer::Guard pb_buf =
	my_direct->write_buffer();
    ArtPixBuf * pb = art_pixbuf_new_const_rgb ((art_u8 *)(pb_buf.get()),
					       my_drawable->width(),
					       my_drawable->height(),
					       my_buffer->row_length());
    art_rgb_pixbuf_affine((art_u8 *)(pb_buf.get()) + 
			  (tsloci.y0 * pb->rowstride) + 
			  (tsloci.x0 * 3), // 3 for "R,G,B" packed pixels			
			  tsloci.x0, tsloci.y0, tsloci.x1, tsloci.y1,
			  my_buffer->row_length(),
			  pixbuf, dev_affine,
			  ART_FILTER_NEAREST, my_agam);
    pixbuf->pixels = save;
}

void libArt::DrawingKit::draw_text(const Unistring &u) 
{
  // FIXME: presently disabled. should delegate to drawChar
}

void libArt::DrawingKit::draw_char(Unichar c)
{
    double x0 = my_affine[4];
    double y0 = my_affine[5];
    int width;
    int height;
    Graphic::Requisition r;
    // We need to initialise this manually:
    r.x.defined = false;
    r.y.defined = false;
    r.z.defined = false;
    r.preserve_aspect = false;
  
    if (c > 127)
    {
	my_unifont->allocate_char(c,r);
	width = (int) (r.x.maximum * my_xres);
	height = (int) (r.y.maximum * my_yres);
    }
    else
    {
	my_font->allocate_char(c,r);
	Fresco::DrawingKit::GlyphMetrics gm = my_font->metrics(c);
	width = (int) (gm.width >> 6);
	height = (int) (gm.height >> 6);
    }
  
    ArtPixBuf *pb;
    int transformed = false;
    double matrix[4];
    // FIXME: USe memcopy!
    for (int i = 0; i < 4; ++i) matrix[i] = my_affine[i];

    if (c > 127)
    {
	transformed = my_unifont->transform(matrix);
	my_unifont->buffer(c, pb);
    }
    else
    {  
	transformed = my_font->transform(matrix);
	my_font->buffer(c, pb);
    }

    if (transformed || (my_affine[0] == 1 &&
			my_affine[1] == 0 &&
			my_affine[2] == 0 &&
			my_affine[3] == 1))
    {
	my_affine[5] -= (my_affine[2] * r.x.maximum * r.x.align) +
	    (my_affine[3] * r.y.maximum * r.y.align);
	identity_pixbuf(pb);      
    }
    else
    {   
	// *sigh* use primitive libart pixel functions
	my_affine[4] -= (r.y.maximum * r.y.align * my_affine[2]);
	my_affine[5] -= (r.y.maximum * r.y.align * my_affine[3]);        
	int pix = 4;
	int row = width * pix; 
	int size = height * row;
	art_u8 pixels[size];    
	//setup foreground color
	for (int i = 0; i < row; ++i)
	{
	    pixels[i] =   (unsigned char) ((my_art_fg >> 24) & 0x000000ff);
	    pixels[++i] = (unsigned char) ((my_art_fg >> 16) & 0x000000ff);
	    pixels[++i] = (unsigned char) ((my_art_fg >> 8) & 0x000000ff);
	    pixels[++i] = (unsigned char) 0;
	}
	for (int i = 0; i < height; ++i)
	    memcpy(pixels + (i * row), pixels, row);
	for (int i = 0; i < (width * height); ++i)
	    pixels[pix*i + 3] = pb->pixels[i];    
	ArtPixBuf *pb2 =
	    art_pixbuf_new_const_rgba(pixels, width, height, row);  
	rasterize_pixbuf(pb2);
	art_pixbuf_free(pb2);
    }
  
    my_affine[4] = x0;
    my_affine[5] = y0;
}

void libArt::DrawingKit::allocate_char(Unichar c,
				       Graphic::Requisition & req)
{
    if (c > 127) my_unifont->allocate_char(c, req);
    else my_font->allocate_char(c, req);
}


void libArt::DrawingKit::allocate_text(const Unistring & s,
		                       Graphic::Requisition & req)
{
    // font->allocate(s,req);
}

void libArt::DrawingKit::copy_drawable(Drawable_ptr d,
		                       PixelCoord x, PixelCoord y,
				       PixelCoord w, PixelCoord h)
{
    CORBA::Double x2 = my_affine[4] * my_buffer->resolution(xaxis);
    CORBA::Double y2 = my_affine[5] * my_buffer->resolution(yaxis);
    my_buffer->blit(d, x, y, w, h,
		    static_cast<long>(x2 + x),
		    static_cast<long>(y2 + y));
}

void libArt::DrawingKit::flush()
{   
    int x = my_bbox.x0;
    int y = my_bbox.y0;
    int w = my_bbox.x1 - my_bbox.x0;
    int h = my_bbox.y1 - my_bbox.y0;  
    my_buffer->flush(x, y, w, h);
    my_drawable->blit(*my_buffer, x, y, w, h, x, y);
    my_bbox.x0 = my_bbox.y0 = my_bbox.x1 = my_bbox.y1 = 0;  
    my_drawable->flush(x, y, w, h);
}

extern "C" Berlin::KitImpl *load()
{
    static std::string properties[] = {"implementation", "LibArtDrawingKit"};
    return Berlin::create_prototype<libArt::DrawingKit>("IDL:fresco.org/Fresco/DrawingKit:1.0", properties, 2);
}
