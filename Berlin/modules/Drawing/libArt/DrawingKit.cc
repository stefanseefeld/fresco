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
#include <Drawing/libArt/LibArtUnifont.hh>
#include <Warsaw/Transform.hh>
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
    font(new LibArtUnifont),
    rasters(500)
  // textures(100), 
  // tx(0)
{
  screen.x0 = 0;
  screen.y0 = 0;
  screen.x1 = drawable->width();
  screen.y1 = drawable->height();
  
  for (int i = 0; i < max_vpath_sz; i++)
    vpath[i].code = ART_LINETO;

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
}

static inline art_u32 artColor(Color &c) {
  return (((art_u8)(c.blue * 0xff) << 24) + 
	  ((art_u8)(c.green * 0xff) << 16) + 
	  ((art_u8)(c.red * 0xff) << 8) + 
	  ((art_u8)(c.alpha * 0xff)));
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
  art_fg = artColor(fg);
}

void LibArtDrawingKit::setLighting(const Color &c)
{
  lt = c;
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
  ArtVpath *tvpath;

  for (int i = 0, j = len - 1; i < len; ++i, --j){
    // there's a bug in libart; it rasterizes alpha segments
    // in our "normal" clockwise order incorrectly. so we
    // are for the time being installing the horrendous hack
    // of "unclockwising" things. this should _not_ be an issue.
    // ~FIXME~
    vpath[i].x = p[j].x; 
    vpath[i].y = p[j].y;
  }

  if (fs == outlined) {
    vpath[0].code = ART_MOVETO_OPEN;
    vpath[len-1].code = ART_END;
  } else {
    // close off filled path
    vpath[len] = vpath[0];
    vpath[0].code = ART_MOVETO;
    vpath[len].code = ART_END;
  }
  
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

  // reset damaged code points
  vpath[0].code = ART_LINETO;
  vpath[len].code = ART_LINETO;
  vpath[len-1].code = ART_LINETO;
}

//void LibArtDrawingKit::drawPatch(const Patch &);

void LibArtDrawingKit::drawRect(const Vertex &bot, const Vertex &top) 
{
  Path path;
  /**
  // fast path (not presently working)
  if (fg.alpha == 1. &&
      affine[0] == 1 &&
      affine[1] == 0 &&
      affine[2] == 0 &&
      affine[3] == 1
      ) {

#define MIN(a,b)  (a<b?a:b)
#define MAX(a,b) (a<b?b:a)
#define TRUNC(a) (a<0?0:a)
    ArtIRect rect;
    rect.x0 = (int)(bot.x * xres);
    rect.x1 = (int)(top.x * xres);
    rect.y0 = (int)(bot.y * yres);
    rect.y1 = (int)(top.y * yres);
    art_irect_intersect(&rect,&rect,&clip);
    int offset = (int)((affine[4] * xres) + (((int)(affine[5] * yres)) * pb->rowstride));
    int width = 1 + (rect.x1 - rect.x0);
    int height = 1 + (rect.y1 - rect.y0);
    int skip = pb->rowstride - width;
    int last = width - 1;
    int sz = height * width;
    unsigned char *writer = (unsigned char *)(pb->pixels);
    writer += offset;
    if (fs == outlined) {
//       for (int i = 0; i < sz; ++i, writer += 3) {
// 	if ((i % width == 0) ||
// 	    (i % width == last) ||
// 	    (i < width) ||
// 	    (i > (sz - width)))
// 	  *writer = art_fg;
// 	if (i % width == last) writer += skip;      
//       }
    } else {
      cerr << "fastpath " << sz << " pixels " << bot.x << " " << bot.y << " " << top.x << " " << top.y << " :" 
	   << rect.x0 << " " << rect.y0 << " " << rect.x1 << " " << rect.y1 << endl;
      for (int i = 0; i < sz; ++i, writer += 3) {
// 	cerr << i << endl;	   
	*writer = art_fg;
	if (i % width == last) writer += skip;      
      }
    }
    return;
  }

  cerr << "affine" << affine[0] << affine[1] << affine[2] << affine[3] << affine[4] << affine[5] << endl;
  */
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
  int row = width * pix;
  int size = (fg.alpha == 1. ? 0 : (pixbuf->height - 1) * pixbuf->rowstride + width * pix);      
  unsigned char tmp[size];
  unsigned char *save = pixbuf->pixels;

  // alpha-correct the image
  if (fg.alpha != 1.) {
    int skip = pixbuf->rowstride - row;
    int last = width - 1;
    unsigned char *writer = tmp;
    unsigned char *reader = pixbuf->pixels;
    for (int i = 0; i < size; ++i, ++reader, ++writer) {
      *writer = (unsigned char)((*reader) * fg.alpha);
      if (i % width == last) reader += skip;	
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
  typedef vector< pair<double, ArtPixBuf *> >::iterator seg_iter;
  vector< pair<double, ArtPixBuf *> > segs;
  font->segments(u,segs);
  for(seg_iter i = segs.begin(); i != segs.end(); i++) {
    rasterizePixbuf(i->second);
    // !!!FIXME!!! this does only unidirectional text
    affine[4] += (i->first * affine[0]) / xres;
    affine[5] += (i->first * affine[1]) / xres;    
  }
}

void LibArtDrawingKit::allocateText(const Unistring & s, Graphic::Requisition & req) {
  font->allocateText(s,req);
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
