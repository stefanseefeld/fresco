/*$Id$
 *
 * This source file is a part of the Berlin Project.
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

#include <Prague/Sys/Tracer.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/IO.hh>
#include <Berlin/Provider.hh>
#include "Drawing/libArt/LibArtDrawingKit.hh"
#include "Drawing/libArt/LibArtFTFont.hh"
#include "Drawing/libArt/LibArtUnifont.hh"

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

using namespace Warsaw;

LibArtDrawingKit::~LibArtDrawingKit() {}
LibArtDrawingKit::LibArtDrawingKit(const std::string &id, const Warsaw::Kit::PropertySeq &p)
  : KitImpl(id, p),
    _drawable(0),
    _xres(1.),
    _yres(1.),
    _font(0),
    _unifont(0),
    _rasters(500)
  // textures(100), 
  // tx(0)
{
}

KitImpl *LibArtDrawingKit::clone(const Warsaw::Kit::PropertySeq &p)
{
  LibArtDrawingKit *kit = new LibArtDrawingKit(repo_id(), p);
  kit->init();
  return kit;
}

void LibArtDrawingKit::init()
{
  Console *console = Console::instance();
  _drawable = console->drawable();
  _xres = _drawable->resolution(xaxis);
  _yres = _drawable->resolution(yaxis);
  _font = new LibArtFTFont(_xres, _yres);
  _unifont = new LibArtUnifont(_xres, _yres);
  _screen.x0 = 0;
  _screen.y0 = 0;
  _screen.x1 = _drawable->width();
  _screen.y1 = _drawable->height();
  
  _agam = art_alphagamma_new (2.5);
  _buffer = console->create_drawable(_drawable->width(), _drawable->height(), 3);
  _renderer = console->get_extension<Renderer>("Renderer", _buffer);
  _direct = console->get_extension<DirectBuffer>("DirectBuffer", _buffer);
  _bbox.x0 = _bbox.y0 = _bbox.x1 = _bbox.y1 = 0;    
  double step = 1. / 256.;
  for (int i = 0; i < 256; ++i)
    for (int j = 0; j < 256; ++j) 
      _alphabank[i][j] = (art_u8)(i * (j * step));
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
};

void LibArtDrawingKit::set_transformation(Transform_ptr t)
{
  Prague::Trace trace("LibArtDrawingKit::set_transformation");
  if (CORBA::is_nil(t)) art_affine_identity(_affine);
  else
    {
      _tr = Transform::_duplicate(t);
      Transform::Matrix matrix;
      _tr->store_matrix(matrix);
      _affine[0] = matrix[0][0];
      _affine[1] = matrix[1][0];
      _affine[2] = matrix[0][1];
      _affine[3] = matrix[1][1];
      _affine[4] = matrix[0][3];
      _affine[5] = matrix[1][3];
    }
  _scaled_affine = _affine;
  _scaled_affine[0] *= _xres;
  _scaled_affine[1] *= _xres;
  _scaled_affine[2] *= _yres;
  _scaled_affine[3] *= _yres;
  _scaled_affine[4] *= _xres;
  _scaled_affine[5] *= _yres;
}

void LibArtDrawingKit::set_clipping(Region_ptr r)
{
  if (CORBA::is_nil(r)) {_clip = _screen; return;}
  _cl = Region::_duplicate(r);
    
  Lease_var<RegionImpl> climpl(Provider<RegionImpl>::provide());
  climpl->copy(_cl);

  ArtDRect dclip = {climpl->lower.x * _xres, climpl->lower.y * _yres, 		      
		      climpl->upper.x * _xres, climpl->upper.y * _yres};
  art_drect_to_irect(&_clip, &dclip); 
  art_irect_intersect(&_clip, &_clip, &_screen);
}

void LibArtDrawingKit::set_foreground(const Color &c)
{
  _fg = c;
  _con_fg.red   = _fg.red * _lt.red;
  _con_fg.green = _fg.green * _lt.green;
  _con_fg.blue  = _fg.blue * _lt.blue;
  _con_fg.alpha = _fg.alpha;
  _art_fg       = artColor(_con_fg);
}

void LibArtDrawingKit::set_lighting(const Color &c)
{
  _lt = c;
  _con_fg.red   = _fg.red * _lt.red;
  _con_fg.green = _fg.green * _lt.green;
  _con_fg.blue  = _fg.blue * _lt.blue;
  _art_fg       = artColor(_con_fg);
}

void LibArtDrawingKit::set_point_size(Coord s) { _ps = s;}
void LibArtDrawingKit::set_line_width(Coord w) { _lw = w;}
void LibArtDrawingKit::set_line_endstyle(Warsaw::DrawingKit::Endstyle style) { _es = style;}
void LibArtDrawingKit::set_surface_fillstyle(Warsaw::DrawingKit::Fillstyle style) { _fs = style;}
void LibArtDrawingKit::set_texture(Raster_ptr t) {}
void LibArtDrawingKit::set_font_size(CORBA::ULong) {}
void LibArtDrawingKit::set_font_weight(CORBA::ULong) {}
void LibArtDrawingKit::set_font_family(const Unistring&) {}
void LibArtDrawingKit::set_font_subfamily(const Unistring&) {}
void LibArtDrawingKit::set_font_fullname(const Unistring&) {}
void LibArtDrawingKit::set_font_style(const Unistring&) {}
void LibArtDrawingKit::set_font_attribute(const NVPair & nvp) {}

void LibArtDrawingKit::draw_path(const Path &p) 
{
  int len = p.length();
  ArtVpath vpath[_fs == Warsaw::DrawingKit::outlined ? len : len + 1];
  ArtVpath *tvpath;  

  if (_fs == Warsaw::DrawingKit::outlined)
    {
      for (int i = 0; i < len; ++i)
	{
	  vpath[i].x = p[i].x; 
	  vpath[i].y = p[i].y;
	  vpath[i].code = ART_LINETO;
	}
      vpath[0].code = ART_MOVETO_OPEN;
      vpath[len-1].code = ART_END;
      
    }
  else
    {
      for (int i = 0; i < len; ++i)
	{
	  vpath[i].x = p[i].x; 
	  vpath[i].y = p[i].y;
	  vpath[i].code = ART_LINETO;
	}
      vpath[0].code = ART_MOVETO;
      vpath[len].x = vpath[0].x;
      vpath[len].y = vpath[0].y;
      vpath[len].code = ART_END;
    }
  
  ArtDRect locd; ArtIRect loc;
  tvpath = art_vpath_affine_transform(vpath, _scaled_affine);
  ArtSVP *svp1 = art_svp_from_vpath(tvpath); 
  ArtSVP *svp2 = art_svp_uncross(svp1);
  ArtSVP *svp = art_svp_rewind_uncrossed(svp2, ART_WIND_RULE_ODDEVEN);

  art_drect_svp(&locd, svp);
  art_drect_to_irect(&loc, &locd);
  art_irect_intersect(&loc, &loc ,&_clip);
  art_irect_union(&_bbox, &_bbox, &loc);
  fix_order_of_irect(loc);
  DirectBuffer::Guard pb_buf = _direct->write_buffer();
  ArtPixBuf * pb = art_pixbuf_new_const_rgb ((art_u8 *)(pb_buf.get()),
					     _drawable->width(),
					     _drawable->height(),
					     _buffer->row_length());
  art_rgb_svp_alpha(svp, loc.x0, loc.y0, loc.x1, loc.y1, _art_fg,
		    (art_u8 *)(pb_buf.get()) +
		     (loc.y0 * pb->rowstride) +
		     (loc.x0 * 3), 
		    _buffer->row_length(), _agam);
  art_svp_free(svp);
  art_svp_free(svp1);
  art_svp_free(svp2);
}

//void LibArtDrawingKit::drawPatch(const Patch &);

void LibArtDrawingKit::draw_rectangle(const Vertex &bot, const Vertex &top) 
{
  // fast path opaque non-transformed rectangles
  if (_fg.alpha == 1. &&
      _affine[0] == 1 &&
      _affine[1] == 0 &&
      _affine[2] == 0 &&
      _affine[3] == 1)
    {
      ArtIRect rect;
      rect.x0 = (int)((bot.x + _affine[4]) * _xres);
      rect.x1 = (int)((top.x  + _affine[4])* _xres);
      rect.y0 = (int)((bot.y + _affine[5]) * _yres);
      rect.y1 = (int)((top.y + _affine[5]) * _yres);
      art_irect_intersect(&rect, &rect, &_clip);
      int width = (rect.x1 - rect.x0);
      int height = (rect.y1 - rect.y0);
      if ((height * width) < 1) return;
      _renderer->set_color(_con_fg);
      if (_fs == Warsaw::DrawingKit::solid)
	_renderer->draw_box(rect.x0, rect.y0, width, height);
      else
	{
	  _renderer->draw_hline(rect.x0, rect.y0, width);
	  _renderer->draw_hline(rect.x0, rect.y1, width);
	  _renderer->draw_vline(rect.x0, rect.y0, height);
	  _renderer->draw_vline(rect.x1, rect.y0, height);
	}
      art_irect_union (&_bbox, &_bbox, &rect);
      return;
      
      // non-degenerate rectangles
    }
  else
    {
      Path path;
      if (_fs == Warsaw::DrawingKit::outlined)
	{
	  path.length(4);
	  path[0].x = bot.x, path[0].y = bot.y;
	  path[1].x = top.x, path[1].y = bot.y;
	  path[2].x = top.x, path[2].y = top.y;
	  path[3].x = bot.x, path[2].y = top.y;
	}
      else
	{
	  path.length(5);
	  path[0].x = bot.x, path[0].y = bot.y;
	  path[1].x = top.x, path[1].y = bot.y;
	  path[2].x = top.x, path[2].y = top.y;
	  path[3].x = bot.x, path[3].y = top.y;
	  path[4].x = bot.x, path[4].y = bot.y;
	}
      draw_path(static_cast<const Path>(path));
    }
}

void LibArtDrawingKit::draw_quadric(const Warsaw::DrawingKit::Quadric, Warsaw::Coord, Warsaw::Coord)
{
}

void LibArtDrawingKit::draw_ellipse(const Vertex &, const Vertex &) {}

void LibArtDrawingKit::draw_image(Raster_ptr remote)
{
  rasterize_pixbuf(_rasters.lookup(Raster::_duplicate(remote))->pixbuf);
}

void LibArtDrawingKit::identity_pixbuf(ArtPixBuf *pixbuf)
{
  // fast path for non-transformed grey-scale glyph images
  ArtIRect rect;
  rect.x0 = (int)(_affine[4] * _xres);
  rect.x1 = rect.x0 + pixbuf->width;
  rect.y0 = (int)(_affine[5] * _yres);
  rect.y1 = rect.y0 + pixbuf->height;
  
  // work out offset within source image
  int dx = _clip.x0 - rect.x0;
  int dy = _clip.y0 - rect.y0;
  if (dx < 0) dx = 0;
  if (dy < 0) dy = 0;

  art_irect_intersect(&rect, &rect, &_clip);
  if (((rect.y1 - rect.y0) * (rect.x1 - rect.x0)) < 1) return;
  DirectBuffer::Guard pb_buf = _direct->write_buffer();
  ArtPixBuf * pb = art_pixbuf_new_const_rgb ((art_u8 *)(pb_buf.get()),
					     _drawable->width(),
					     _drawable->height(),
					     _buffer->row_length());
  art_u8 *dst = pb->pixels + rect.y0 * pb->rowstride + rect.x0 * 3;
  art_u8 *src = pixbuf->pixels + dy * pixbuf->rowstride + dx;
  int width = (rect.x1 - rect.x0);
  int height = (rect.y1 - rect.y0);  
  art_u8 *atab = _alphabank[(art_u8)(_art_fg & 0xff)];
  art_u8 *rtab = _alphabank[(art_u8)((_art_fg >> 24) & 0xff)];
  art_u8 *gtab = _alphabank[(art_u8)((_art_fg >> 16) & 0xff)];
  art_u8 *btab = _alphabank[(art_u8)((_art_fg >> 8) & 0xff)];

  int t;
  int dst_skip = pb->rowstride - width * 3;
  int src_skip = pixbuf->rowstride - width;
  art_u8 *ptab;


  for (int row = 0; row < height; ++row, dst += dst_skip, src += src_skip)
    for (int col = 0; col < width; ++col, dst += 3, ++src)
      {            
	ptab = _alphabank[*src];
	dst[0] = t = dst[0] + atab[rtab[*src]] - atab[ptab[dst[0]]]; 
	t &= 0x100; t >>= 8; t -= 1; t =~ t; dst[0] |= (t & 0xff);
	dst[1] = t = dst[1] + atab[gtab[*src]] - atab[ptab[dst[1]]]; 
	t &= 0x100; t >>= 8; t -= 1; t =~ t; dst[1] |= (t & 0xff);
	dst[2] = t = dst[2] + atab[btab[*src]] - atab[ptab[dst[2]]]; 
	t &= 0x100; t >>= 8; t -= 1; t =~ t; dst[2] |= (t & 0xff);
      }
  art_irect_union (&_bbox, &_bbox, &rect);
}


void LibArtDrawingKit::rasterize_pixbuf(ArtPixBuf *pixbuf)
{
  
  // NOTE: this entire routine takes place "in device space"
  // since that is (a) the source of the raster and (b) the destination
  // of libart's transformation. the goal is to get everything into
  // device space and work with it there.
  
  double dev_affine[6] = {_affine[0], _affine[1], _affine[2], _affine[3], 
			  _affine[4] * _xres, _affine[5] * _yres };
  			      
  // pre-transformation target rectangle, in device space coords
  ArtDRect slocd = {0,0,(double)(pixbuf->width),(double)(pixbuf->height)};
  ArtDRect tslocd; 
  ArtIRect tsloci; 

  int width = pixbuf->width;
  int pix = ((pixbuf->n_channels * pixbuf->bits_per_sample + 7) >> 3); 
  int row = (width) * pix;
  int skip = (pixbuf->rowstride - row);
  int size = (_fg.alpha == 1. ? 0 : (pixbuf->height - 1) * pixbuf->rowstride + width * pix);      

  art_u8 tmp[size];
  art_u8 *save = pixbuf->pixels;

  // alpha-correct the image
  if (_fg.alpha != 1.)
    {
      art_u8 *end_write = tmp + (size - 1);
      art_u8 *reader = pixbuf->pixels;
      art_u8 *tab = _alphabank[(art_u8)(_art_fg & 0x000000ff)];
      art_u8 *eol;
      for (art_u8 *writer = tmp; writer < end_write; reader += skip, writer += skip)
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
  art_irect_intersect(&tsloci, &tsloci, &_clip);
  art_irect_union (&_bbox, &_bbox, &tsloci);
  
  // paint
  DirectBuffer::Guard pb_buf = _direct->write_buffer();
  ArtPixBuf * pb = art_pixbuf_new_const_rgb ((art_u8 *)(pb_buf.get()),
					     _drawable->width(),
					     _drawable->height(),
					     _buffer->row_length());
  art_rgb_pixbuf_affine((art_u8 *)(pb_buf.get()) + 
			(tsloci.y0 * pb->rowstride) + 
			(tsloci.x0 * 3), // 3 for "R,G,B" packed pixels			
			tsloci.x0, tsloci.y0, tsloci.x1, tsloci.y1,
			_buffer->row_length(),
			pixbuf, dev_affine,
			ART_FILTER_NEAREST, _agam);
  pixbuf->pixels = save;
}

void LibArtDrawingKit::draw_text(const Unistring &u) 
{
  // presently disabled. should delegate to drawChar
}

void LibArtDrawingKit::draw_char(Unichar c)
{
  double x0 = _affine[4];
  double y0 = _affine[5];
  int width;
  int height;
  Graphic::Requisition r;
  
  if (c > 127)
    {
      _unifont->allocate_char(c,r);
      width = (int) (r.x.maximum * _xres);
      height = (int) (r.y.maximum * _yres);
    }
  else
    {
      _font->allocate_char(c,r);
      Warsaw::DrawingKit::GlyphMetrics gm = _font->metrics(c);
      width = (int) (gm.width >> 6);
      height = (int) (gm.height >> 6);
    }
  
  ArtPixBuf *pb;
  int transformed = false;
  double matrix[4];
  for (int i = 0; i < 4; ++i) matrix[i] = _affine[i];

  if (c > 127)
    {
      transformed = _unifont->transform(matrix);
      _unifont->buffer(c, pb);
    }
  else
    {  
      transformed = _font->transform(matrix);
      _font->buffer(c, pb);
    }

  if (transformed || (_affine[0] == 1 &&
		      _affine[1] == 0 &&
		      _affine[2] == 0 &&
		      _affine[3] == 1))
    {
      _affine[5] -= (_affine[2] * r.x.maximum * r.x.align) + (_affine[3] * r.y.maximum * r.y.align);
      identity_pixbuf(pb);      
    }
  else
    {   
      // *sigh* use primitive libart pixel functions
      _affine[4] -= (r.y.maximum * r.y.align * _affine[2]);
      _affine[5] -= (r.y.maximum * r.y.align * _affine[3]);        
      int pix = 4;
      int row = width * pix; 
      int size = height * row;
      art_u8 pixels[size];    
      //setup foreground color
      for (int i = 0; i < row; ++i)
	{
	  pixels[i] =   (unsigned char) ((_art_fg >> 24) & 0x000000ff);
	  pixels[++i] = (unsigned char) ((_art_fg >> 16) & 0x000000ff);
	  pixels[++i] = (unsigned char) ((_art_fg >> 8) & 0x000000ff);
	  pixels[++i] = (unsigned char) 0;
	}
      for (int i = 0; i < height; ++i) memcpy (pixels + (i * row), pixels, row);
      for (int i = 0; i < (width * height); ++i) pixels[pix*i + 3] = pb->pixels[i];    
      ArtPixBuf *pb2 = art_pixbuf_new_const_rgba (pixels, width, height, row);  
      rasterize_pixbuf(pb2);
      art_pixbuf_free(pb2);
    }
  
  _affine[4] = x0;
  _affine[5] = y0;
}

void LibArtDrawingKit::allocate_char(Unichar c, Graphic::Requisition & req)
{
  if (c > 127) _unifont->allocate_char(c,req);
  else _font->allocate_char(c,req);
}


void LibArtDrawingKit::allocate_text(const Unistring & s, Graphic::Requisition & req)
{
  //   font->allocate(s,req);
}

void LibArtDrawingKit::copy_drawable(Drawable_ptr d, PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h)
{
  CORBA::Double x2 = _affine[4] * _buffer->resolution(xaxis);
  CORBA::Double y2 = _affine[5] * _buffer->resolution(yaxis);
  _buffer->blit(d, x, y, w, h, static_cast<long>(x2 + x), static_cast<long>(y2 + y));
}

void LibArtDrawingKit::flush()
{   
  int x = _bbox.x0;
  int y = _bbox.y0;
  int w = _bbox.x1 - _bbox.x0;
  int h = _bbox.y1 - _bbox.y0;  
  _buffer->flush(x, y, w, h);
  _drawable->blit(*_buffer, x, y, w, h, x, y);
  _bbox.x0 = _bbox.y0 = _bbox.x1 = _bbox.y1 = 0;  
}

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "LibArtDrawingKit"};
  return create_kit<LibArtDrawingKit>("IDL:Warsaw/DrawingKit:1.0", properties, 2);
}
