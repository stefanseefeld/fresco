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

extern "C"
{
#include <ggi/ggi.h>
}

#include <art_pathcode.h>
#include <art_pixbuf.h>
#include <art_rect.h>
#include <art_vpath.h>
#include <art_svp.h>
#include <art_svp_vpath.h>
#include <art_rect_svp.h>
#include <art_rgb_svp.h>
#include <art_rgb_pixbuf_affine.h>


LibArtDrawingKit::~LibArtDrawingKit() {}
LibArtDrawingKit::LibArtDrawingKit(KitFactory *f, const PropertySeq &p)
  : KitImpl(f, p),
    drawable(GGI::drawable()), 
    tr(new TransformImpl), 
    cl(new RegionImpl), 
    font(new LibArtUnifont),
    rasters(500)
  // textures(100), 
  // tx(0)
{
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

void LibArtDrawingKit::setTransformation(Transform_ptr t)
{
  tr->copy(t);
  Transform::Matrix &matrix = tr->matrix();  
  affine[0] = matrix[0][0];
  affine[1] = matrix[1][0];
  affine[2] = matrix[0][1];
  affine[3] = matrix[1][1];
  affine[4] = matrix[0][3];
  affine[5] = matrix[1][3];
}

void LibArtDrawingKit::setClipping(Region_ptr r)
{
  cl->copy(r);
}

void LibArtDrawingKit::setForeground(const Color &c)
{
  fg = c;
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
  ArtVpath vpath[(fs == outlined ? len : len + 1)];
  ArtVpath *tvpath;
  ArtVpath *tsvpath;
  double resScale[6]  = {
    drawable->resolution(xaxis), 0, 0, 
      drawable->resolution(yaxis), 0, 0
      };

  if (fs == outlined) {
    for (int i = 0; i < len; i++) {
      vpath[i].code = (i == 0 ? ART_MOVETO_OPEN 
		       : (i == len - 1 ? ART_END : ART_LINETO));
      vpath[i].x = p[len-i-1].x;
      vpath[i].y = p[len-i-1].y;
    }

  } else {
    for (int i = 0; i < len; i++) {
      vpath[i].code = (i == 0 ? ART_MOVETO : ART_LINETO);
      vpath[i].x = p[len-i-1].x;
      vpath[i].y = p[len-i-1].y;
    }
    vpath[len] = vpath[0];
    vpath[len].code = ART_END;
  }
  
  ArtDRect locd;
  ArtIRect loc;
  ArtDRect clip = {cl->upper.x, cl->upper.y,
		     cl->lower.x, cl->lower.y};
  ArtDRect screen = {0,0,drawable->width(), drawable->height()};

  art_drect_affine_transform(&clip,&clip,resScale);
  tvpath = art_vpath_affine_transform(vpath,affine);
  tsvpath = art_vpath_affine_transform(tvpath,resScale);

  // get an svp
  ArtSVP *svp = art_svp_from_vpath (tsvpath); 

  // prepare clip box for drawing
  art_drect_svp (&locd, svp);
  art_drect_intersect(&locd,&locd,&clip);
  art_drect_intersect(&locd,&locd,&screen);
  art_drect_to_irect(&loc, &locd);
  art_irect_union (&bbox,&bbox,&loc);

  // why this might happen, who knows. they might be insane somehow.
  // it appears to happen in practise sometimes (?)
  if (loc.x0 > loc.x1) {int tmp = loc.x0; loc.x1 = loc.x0; loc.x0 = tmp;}
  if (loc.y0 > loc.y1) {int tmp = loc.y0; loc.y0 = loc.y1; loc.y1 = tmp;}
 
  art_rgb_svp_alpha (svp,
  		     loc.x0, loc.y0, 
  		     loc.x1, loc.y1,
 		     artColor(fg),
 		     ((art_u8 *)buf->write) + (loc.y0 * pb->rowstride) + (loc.x0 * 3), 
 		     buf->buffer.plb.stride,
 		     agam);
  art_svp_free(svp);
}

//void LibArtDrawingKit::drawPatch(const Patch &);

void LibArtDrawingKit::drawRect(const Vertex &bot, const Vertex &top) 
{
  Path path;
  path.length(4);
  path[0].x = top.x, path[0].y = top.y, path[0].z = 0.;
  path[1].x = bot.x, path[1].y = top.y, path[1].z = 0.;
  path[2].x = bot.x, path[2].y = bot.y, path[2].z = 0.;
  path[3].x = top.x, path[3].y = bot.y, path[3].z = 0.;
  this->drawPath(static_cast<const Path>(path));
}

void LibArtDrawingKit::drawEllipse(const Vertex &, const Vertex &) {}

void LibArtDrawingKit::drawImage(Raster_ptr remote) {

  // NOTE: this entire routine takes place "in device space"
  // since that is (a) the source of the raster and (b) the destination
  // of libart's transformation. the goal is to get everything into
  // device space and work with it there.

  LibArtRaster *r = rasters.lookup(Raster::_duplicate(remote));

  // these are coords in the target visual
  double x = affine[4] * drawable->resolution(xaxis);
  double y = affine[5] * drawable->resolution(xaxis);
  
  // this affine is inverted and used to map coords back from the
  // screen to the pixbuf.
  double affinePix[6] = {affine[0], affine[1], affine[2], affine[3],0,0}; 

  ArtDRect locd = {x,y,(double)(x+r->pixbuf->width),(double)(y+r->pixbuf->height)};
  
  ArtIRect loc;
  ArtDRect screen = {0,0,drawable->width(), drawable->height()};
  art_drect_intersect(&locd,&locd,&screen);
  art_drect_to_irect(&loc, &locd);

  // why this might happen, who knows. they might be insane somehow.
  // it appears to happen in practise sometimes (?)
  if (loc.x0 > loc.x1) {int tmp = loc.x0; loc.x1 = loc.x0; loc.x0 = tmp;}
  if (loc.y0 > loc.y1) {int tmp = loc.y0; loc.y0 = loc.y1; loc.y1 = tmp;}

  // extend damage box
  art_irect_union (&bbox,&bbox,&loc);

  // NOTE: yes, I know this is inconsistent with the calling convention that is
  // used to put vectors on the screen. I don't know why libart is designed this
  // way, but after extensive fiddling this appears to be the closest I can get
  // it to doing "the right thing". you are welcome to experiment yourself..

  art_rgb_pixbuf_affine(
			((art_u8 *)buf->write) + (loc.y0 * pb->rowstride) + (loc.x0 * 3), 
			0, 0, 
			loc.x1 - loc.x0, loc.y1 - loc.y0,
			buf->buffer.plb.stride,
			r->pixbuf,
			affinePix,
			ART_FILTER_NEAREST,
			agam);  
}

void LibArtDrawingKit::drawText(const Unistring &u) 
{
  // !!FIXME!! this should do arbitrary linear trafo on text,
  // not just offsets.
  double xr = drawable->resolution(xaxis);
  double yr = drawable->resolution(yaxis);

  Graphic::Requisition req;
  allocateText(u,req);
  ArtIRect r;
  r.x0 = (int)(affine[4] * xr);
  r.y0 = (int)(affine[5] * yr);
  r.x1 = (int)(affine[4] * xr + req.x.maximum);
  r.y1 = (int)(affine[5] * yr + req.y.maximum);

  art_irect_union (&bbox,&bbox,&r);

  font->drawText(u,r.x0,r.y0,pb,fg);
}

void LibArtDrawingKit::allocateText(const Unistring & s, Graphic::Requisition & req) {
  font->allocateText(s,req);
}

void LibArtDrawingKit::flush() {   
  ggiFlush(memvis);
  ggi_visual_t vis = drawable->visual();
  ggiCrossBlit(memvis, bbox.x0,bbox.y0,
	       bbox.x1-bbox.x0,
	       bbox.y1-bbox.y0, 
	       vis, bbox.x0,bbox.y0 );
  bbox.x0 = bbox.y0 = bbox.x1 = bbox.y1 = 0;  
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "LibArtDrawingKit"};
  return new KitFactoryImpl<LibArtDrawingKit> (interface(DrawingKit), properties, 1);
}
