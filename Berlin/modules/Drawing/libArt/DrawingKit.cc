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

#include <Warsaw/config.hh>
#include <Drawing/libArt/LibArtDrawingKit.hh>
#include <Drawing/libArt/LibArtFTFont.hh>
#include <Drawing/libArt/LibArtUnifont.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/IO.hh>
#include <Berlin/Providers.hh>

extern "C"
{
#include <ggi/ggi.h>
}

#include <art_pathcode.h>
#include <art_pixbuf.h>
#include <art_affine.h>
#include <art_rect.h>
#include <art_vpath.h>
#include <art_svp.h>
#include <art_svp_vpath.h>
#include <art_svp_wind.h>
#include <art_rect_svp.h>
#include <art_rgb_svp.h>
#include <art_rgb_pixbuf_affine.h>


LibArtDrawingKit::~LibArtDrawingKit() {}
LibArtDrawingKit::LibArtDrawingKit(KitFactory *f, const PropertySeq &p)
  : KitImpl(f, p),
    drawable(GGI::drawable()), 
    xres(drawable->resolution(xaxis)),
    yres(drawable->resolution(yaxis)),
    font(new LibArtFTFont(drawable)),
    unifont(new LibArtUnifont(drawable)),
    rasters(500)
  // textures(100), 
  // tx(0)
{
  screen.x0 = 0;
  screen.y0 = 0;
  screen.x1 = drawable->width();
  screen.y1 = drawable->height();
  
  agam = art_alphagamma_new (2.5);
  memvis = ggiOpen("display-memory", NULL);
  if(!memvis) {
    cerr << "memory-visual failed to open in LibArt DrawingKit";
    exit(1);
  }
  ggiSetGraphMode(memvis, drawable->width(), drawable->height(), 
		  drawable->width(), drawable->height(), GT_24BIT);
  buf = ggiDBGetBuffer (memvis, 0);
  int stride = buf->buffer.plb.stride;
  pb = art_pixbuf_new_const_rgb ((art_u8 *)buf->write, drawable->width(), drawable->height(), stride);
  bbox.x0 = bbox.y0 = bbox.x1 = bbox.y1 = 0;    
  double step = 1. / 256.;
  for (int i = 0; i < 256; ++i)
    for (int j = 0; j < 256; ++j) 
      alphabank[i][j] = (art_u8)(i * (j * step));
}

static inline art_u32 artColor(Color &c) {
  return (((art_u8)(c.blue * 0xff) << 24) + 
	  ((art_u8)(c.green * 0xff) << 16) + 
	  ((art_u8)(c.red * 0xff) << 8) + 
	  ((art_u8)(c.alpha * 0xff)));
}

static inline ggi_pixel ggiColor(Color c1, ggi_visual_t vis) {
  ggi_color c2;
  // GGI _appears_ to use 16 bit color + alpha throughout. *sigh*
  static double scale = 0xffff;
  c2.r = static_cast<uint16>(c1.red * scale);
  c2.g = static_cast<uint16>(c1.green * scale);
  c2.b = static_cast<uint16>(c1.blue * scale);
  c2.a = static_cast<uint16>(c1.alpha * scale);
  return ggiMapColor(vis,&c2);
}

static inline void fix_order_of_irect(ArtIRect &ir) {
  if (ir.x0 > ir.x1) {int tmp = ir.x0; ir.x1 = ir.x0; ir.x0 = tmp;}
  if (ir.y0 > ir.y1) {int tmp = ir.y0; ir.y0 = ir.y1; ir.y1 = tmp;}
}

void LibArtDrawingKit::setTransformation(Transform_ptr t)
{
  if (CORBA::is_nil(t)) {
    art_affine_identity(affine);
  } else {
    tr = Transform::_duplicate(t);
    Transform::Matrix matrix;
    tr->storeMatrix(matrix);  
    affine[0] = matrix[0][0];
    affine[1] = matrix[1][0];
    affine[2] = matrix[0][1];
    affine[3] = matrix[1][1];
    affine[4] = matrix[0][3];
    affine[5] = matrix[1][3];
  }  
  scaled_affine = affine;
  scaled_affine[0] *= xres;
  scaled_affine[1] *= xres;
  scaled_affine[2] *= yres;
  scaled_affine[3] *= yres;
  scaled_affine[4] *= xres;
  scaled_affine[5] *= yres;
}

void LibArtDrawingKit::setClipping(Region_ptr r)
{
  if (CORBA::is_nil(r)) {clip = screen; return;}
  cl = Region::_duplicate(r);
    
  Lease<RegionImpl> climpl;
  Providers::region.provide(climpl);
  climpl->copy(cl);

  ArtDRect dclip = {climpl->lower.x * xres, climpl->lower.y * yres, 		      
		      climpl->upper.x * xres, climpl->upper.y * yres};
  art_drect_to_irect(&clip, &dclip); 
  art_irect_intersect(&clip,&clip,&screen);
}

void LibArtDrawingKit::setForeground(const Color &c)
{
  fg = c;
  Color tmp;
  tmp.red = fg.red*lt.red;
  tmp.green = fg.green*lt.green;
  tmp.blue = fg.blue*lt.blue;
  tmp.alpha = fg.alpha;
  art_fg = artColor(tmp);
  ggi_fg = ggiColor(tmp, memvis);
}

void LibArtDrawingKit::setLighting(const Color &c)
{
  lt = c;
  Color tmp;
  tmp.red = fg.red*lt.red;
  tmp.green = fg.green*lt.green;
  tmp.blue = fg.blue*lt.blue;
  art_fg = artColor(tmp);
  ggi_fg = ggiColor(tmp, memvis);
}

void LibArtDrawingKit::setPointSize(Coord s)
{
  ps = s;
}

void LibArtDrawingKit::setLineWidth(Coord w)
{
  lw = w;
}

void LibArtDrawingKit::setLineEndstyle(DrawingKit::Endstyle style)
{
  es = style;
}

void LibArtDrawingKit::setSurfaceFillstyle(DrawingKit::Fillstyle style)
{
  fs = style;
}

void LibArtDrawingKit::setTexture(Raster_ptr t)
{
}

void LibArtDrawingKit::setFontSize(CORBA::ULong) {}
void LibArtDrawingKit::setFontWeight(CORBA::ULong) {}
void LibArtDrawingKit::setFontFamily(const Unistring&) {}
void LibArtDrawingKit::setFontSubFamily(const Unistring&) {}
void LibArtDrawingKit::setFontFullName(const Unistring&) {}
void LibArtDrawingKit::setFontStyle(const Unistring&) {}
void LibArtDrawingKit::setFontAttr(const NVPair & nvp) {}

void LibArtDrawingKit::drawPath(const Path &p) 
{
  int len = p.length();
  ArtVpath vpath[fs == outlined ? len : len + 1];
  ArtVpath *tvpath;  

  if (fs == outlined) {
    for (int i = 0; i < len; ++i){
      vpath[i].x = p[i].x; 
      vpath[i].y = p[i].y;
      vpath[i].code = ART_LINETO;
    }
//     if (len == 3) cerr << "open triangle" << endl;
    vpath[0].code = ART_MOVETO_OPEN;
    vpath[len-1].code = ART_END;

  } else {
    for (int i = 0; i < len; ++i){
      vpath[i].x = p[i].x; 
      vpath[i].y = p[i].y;
      vpath[i].code = ART_LINETO;
    }
//     if (len == 3) cerr << "closed triangle" << endl;
    vpath[0].code = ART_MOVETO;
    vpath[len].x = vpath[0].x;
    vpath[len].y = vpath[0].y;
    vpath[len].code = ART_END;
  }

//   if (len == 3) {
//     cerr << "triangle: ";
//     for (int i = 0; i < 4; i++) {
//       cerr << "(" << vpath[i].x << "," << vpath[i].y << ") ";
//     } 
//     cerr << endl;
//   }    
  
  ArtDRect locd; ArtIRect loc;
  tvpath = art_vpath_affine_transform(vpath,scaled_affine);
  ArtSVP *svp1 = art_svp_from_vpath (tvpath); 
  ArtSVP *svp2 = art_svp_uncross (svp1);
  ArtSVP *svp = art_svp_rewind_uncrossed (svp2, ART_WIND_RULE_ODDEVEN);

  art_drect_svp (&locd, svp);
  art_drect_to_irect(&loc, &locd);
  art_irect_intersect(&loc,&loc,&clip);
  art_irect_union (&bbox,&bbox,&loc);
  fix_order_of_irect(loc); 
  art_rgb_svp_alpha (svp, loc.x0, loc.y0, loc.x1, loc.y1,
 		     art_fg,
 		     ((art_u8 *)buf->write) + (loc.y0 * pb->rowstride) + (loc.x0 * 3), 
 		     buf->buffer.plb.stride,
 		     agam);
  art_svp_free(svp);
  art_svp_free(svp1);
  art_svp_free(svp2);
}

//void LibArtDrawingKit::drawPatch(const Patch &);

void LibArtDrawingKit::drawRect(const Vertex &bot, const Vertex &top) 
{
  // fast path opaque non-transformed rectangles
  if (fg.alpha == 1. &&
      affine[0] == 1 &&
      affine[1] == 0 &&
      affine[2] == 0 &&
      affine[3] == 1) {

    ArtIRect rect;
    rect.x0 = (int)((bot.x + affine[4]) * xres);
    rect.x1 = (int)((top.x  + affine[4])* xres);
    rect.y0 = (int)((bot.y + affine[5]) * yres);
    rect.y1 = (int)((top.y + affine[5]) * yres);
    art_irect_intersect(&rect,&rect,&clip);
    int width = (rect.x1 - rect.x0);
    int height = (rect.y1 - rect.y0);
    if ((height * width) < 1) return;
    ggiSetGCForeground(memvis, ggi_fg);
    if ( fs == solid ) {
      ggiDrawBox(memvis, rect.x0, rect.y0, width, height);
    } else {
      ggiDrawHLine(memvis, rect.x0, rect.y0, width);
      ggiDrawHLine(memvis, rect.x0, rect.y1, width);
      ggiDrawVLine(memvis, rect.x0, rect.y0, height);
      ggiDrawVLine(memvis, rect.x1, rect.y0, height);
    }
    art_irect_union (&bbox,&bbox,&rect);
    return;
    
    // non-degenerate rectangles
  } else {
    Path path;
    if (fs == outlined) {
      path.length(4);
      path[0].x = bot.x, path[0].y = bot.y;
      path[1].x = top.x, path[1].y = bot.y;
      path[2].x = top.x, path[2].y = top.y;
      path[3].x = bot.x, path[2].y = top.y;
    } else {
      path.length(5);
      path[0].x = bot.x, path[0].y = bot.y;
      path[1].x = top.x, path[1].y = bot.y;
      path[2].x = top.x, path[2].y = top.y;
      path[3].x = bot.x, path[3].y = top.y;
      path[4].x = bot.x, path[4].y = bot.y;
    }
    this->drawPath(static_cast<const Path>(path));
  }
}

void LibArtDrawingKit::drawEllipse(const Vertex &, const Vertex &) {}

void LibArtDrawingKit::drawImage(Raster_ptr remote) {
  rasterizePixbuf(rasters.lookup(Raster::_duplicate(remote))->pixbuf);
}

void LibArtDrawingKit::rasterizePixbuf(ArtPixBuf *pixbuf) {

  // NOTE: this entire routine takes place "in device space"
  // since that is (a) the source of the raster and (b) the destination
  // of libart's transformation. the goal is to get everything into
  // device space and work with it there.

  double dev_affine[6] = {affine[0], affine[1], affine[2], affine[3], 
			    affine[4] * xres, affine[5] * yres };
  			      
  // pre-transformation target rectangle, in device space coords
  ArtDRect slocd = {0,0,(double)(pixbuf->width),(double)(pixbuf->height)};
  ArtDRect tslocd; 
  ArtIRect tsloci; 
  int width = pixbuf->width;
  int pix = ((pixbuf->n_channels * pixbuf->bits_per_sample + 7) >> 3); 
  int row = (width) * pix;
  int size = (fg.alpha == 1. ? 0 : (pixbuf->height - 1) * pixbuf->rowstride + width * pix);      
  art_u8 tmp[size];
  art_u8 *save = pixbuf->pixels;

  // alpha-correct the image
  if (fg.alpha != 1.) {
    int skip = (pixbuf->rowstride - row);
    art_u8 *end_write = tmp + (size - 1);
    art_u8 *reader = pixbuf->pixels;
    art_u8 *tab = alphabank[(art_u8)(art_fg & 0x000000ff)];
    art_u8 *eol;
    for (art_u8 *writer = tmp; writer < end_write; reader += skip, writer += skip) {
      memcpy(writer,reader,row);
      eol = writer + row;      
      while (writer < eol) {
	writer += 3; reader += 3;
	*writer++ = *(tab + *reader++);      
      }
    }
    pixbuf->pixels = tmp;
  }
  
  // transform target (in device space)
  art_drect_affine_transform(&tslocd,&slocd,dev_affine); 
  art_drect_to_irect(&tsloci, &tslocd); 
  fix_order_of_irect(tsloci); 

  // clip 
  art_irect_intersect(&tsloci,&tsloci,&clip);
  art_irect_union (&bbox,&bbox,&tsloci);
	  	 
  // paint
  art_rgb_pixbuf_affine((art_u8 *)buf->write + 
			(tsloci.y0 * pb->rowstride) + 
			(tsloci.x0 * 3), // 3 for "R,G,B" packed pixels			
			tsloci.x0, tsloci.y0, tsloci.x1, tsloci.y1,
			buf->buffer.plb.stride,
			pixbuf, dev_affine,
			ART_FILTER_NEAREST, agam);  

  pixbuf->pixels = save;
}

void LibArtDrawingKit::drawText(const Unistring &u) 
{
  // presently disabled. should delegate to drawChar
}

void LibArtDrawingKit::drawChar(Unichar c) {
  double x0 = affine[4];
  double y0 = affine[5];
  int width;
  int height;
  Graphic::Requisition r;

  if (c > 127) {
    unifont->allocateChar(c,r);
    width = (int) (r.x.maximum * xres);
    height = (int) (r.y.maximum * yres);
  } else {
    font->allocateChar(c,r);
    FT_Glyph_Metrics metrics;
    font->getMetrics(c,metrics);
    width = (int) (metrics.width >> 6);
    height = (int) (metrics.height >> 6);
  }
  
  affine[4] -= (r.y.maximum * r.y.align * affine[2]);
  affine[5] -= (r.y.maximum * r.y.align * affine[3]);        

  int pix = 4;
  int row = width * pix; 
  int size = height * row;
  art_u8 pixels[size];
  
  // setup foreground color
  for (int i = 0; i < row; ++i){
    pixels[i] = (unsigned char) ((art_fg >> 24) & 0x000000ff);
    pixels[++i] = (unsigned char) ((art_fg >> 16) & 0x000000ff);
    pixels[++i] = (unsigned char) ((art_fg >> 8) & 0x000000ff);
    pixels[++i] = (unsigned char) 0;
  }
  for (int i = 0; i < height; ++i) 
    memcpy (pixels + (i * row), pixels, row);
  
  ArtPixBuf *pb = art_pixbuf_new_const_rgba (pixels, width, height, row);  
  if (c > 127) {
    unifont->getPixBuf(c,*pb);
  } else {
    font->getPixBuf(c,*pb);
  }
  rasterizePixbuf(pb);
  art_pixbuf_free(pb);
  affine[4] = x0;
  affine[5] = y0;
}

void LibArtDrawingKit::allocateChar(Unichar c, Graphic::Requisition & req) {
  if (c > 127) {
    unifont->allocateChar(c,req);
  } else {
    font->allocateChar(c,req);
  }
}


void LibArtDrawingKit::allocateText(const Unistring & s, Graphic::Requisition & req) {
//   font->allocate(s,req);
}

void LibArtDrawingKit::flush() {   
  int 
    x = bbox.x0,
    y = bbox.y0,
    w = bbox.x1-bbox.x0,
    h = bbox.y1-bbox.y0;  
  ggiFlushRegion(memvis,x,y,w,h);
  ggi_visual_t vis = drawable->visual();
  ggiCrossBlit(memvis,x,y,w,h,vis,x,y);
  bbox.x0 = bbox.y0 = bbox.x1 = bbox.y1 = 0;  
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "LibArtDrawingKit"};
  return new KitFactoryImpl<LibArtDrawingKit> (interface(DrawingKit), properties, 1);
}
