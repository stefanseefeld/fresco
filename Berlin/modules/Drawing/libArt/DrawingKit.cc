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
#include <Berlin/Plugin.hh>

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

LibArtDrawingKit::~LibArtDrawingKit() {}
LibArtDrawingKit::LibArtDrawingKit() : 
  drawable(GGI::drawable()), 
  tr(new TransformImpl), 
  cl(new RegionImpl), 
  font(new LibArtUnifont) 
  //, textures(100), 
  // images(500), 
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

  // clear the bbox
  bbox.x0 = bbox.y0 = bbox.x1 = bbox.y1 = 0.;  
}

static inline art_u32 artColor(Color c) {
  art_u32 c2 = 0;
  static double scale = 0xff;
  c2 += (static_cast<art_u8>(c.red * scale) << 24);
  c2 += (static_cast<art_u8>(c.green * scale) << 16);
  c2 += (static_cast<art_u8>(c.blue * scale) << 8);
  c2 += (static_cast<art_u8>(c.alpha * scale));
  return c2;
}

void LibArtDrawingKit::setTransformation(Transform_ptr t)
{
  tr->copy(t);
  Transform::Matrix &matrix = tr->matrix();  
  affine[0] = matrix[0][0];
  affine[1] = matrix[0][1];
  affine[2] = matrix[1][0];
  affine[3] = matrix[1][1];
  affine[4] = matrix[0][3] * drawable->resolution(xaxis);
  affine[5] = matrix[1][3] * drawable->resolution(yaxis);
}

void LibArtDrawingKit::setClipping(Region_ptr r)
{
  cl->copy(r);
  double xr = drawable->resolution(xaxis);
  double yr = drawable->resolution(yaxis);
  PixelCoord x = static_cast<PixelCoord>(cl->lower.x*xr);
  PixelCoord y = static_cast<PixelCoord>((drawable->height()/yr - cl->upper.y)*yr);
  PixelCoord x2 = static_cast<PixelCoord>((cl->upper.x)*xr);
  PixelCoord y2 = static_cast<PixelCoord>((cl->upper.y)*yr);
  ggiSetGCClipping(memvis, x, y, x2, y2);
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
  ArtVpath vpath[len];
  ArtVpath *vpath2;
  double xres = drawable->resolution(xaxis);
  double yres = drawable->resolution(yaxis);

  for (int i = 0; i < len; i++) {
    vpath[i].code = i == 0 ? ART_MOVETO : (i == len - 1 ? ART_END : ART_LINETO);
    vpath[i].x = p[i].x * xres;
    vpath[i].y = p[i].y * yres;
  }
  
  vpath2 = art_vpath_affine_transform(vpath,affine);
  ArtSVP *svp = art_svp_from_vpath (vpath2); 
  art_drect_svp_union (&bbox,svp);
  art_rgb_svp_alpha (svp,
		     0, 0, pb->width, pb->height,
		     artColor(fg),
		     pb->pixels, pb->rowstride,
		     agam);
  art_svp_free(svp);
}

//void LibArtDrawingKit::drawPatch(const Patch &);

void LibArtDrawingKit::drawRect(const Vertex &top, const Vertex &bot) 
{

  ArtVpath vpath[6];
  ArtVpath *vpath2;
  double xr = drawable->resolution(xaxis);
  double yr = drawable->resolution(yaxis);
  double x0 = top.x *xr;
  double y0 = top.y * yr;
  double x1 = bot.x * xr;
  double y1 = bot.y * yr;

  vpath[0].code = ART_MOVETO;
  vpath[0].x = x0;
  vpath[0].y = y0;
  vpath[1].code = ART_LINETO;
  vpath[1].x = x0;
  vpath[1].y = y1;
  vpath[2].code = ART_LINETO;
  vpath[2].x = x1;
  vpath[2].y = y1;
  vpath[3].code = ART_LINETO;
  vpath[3].x = x1;
  vpath[3].y = y0;
  vpath[4].code = ART_LINETO;
  vpath[4].x = x0;
  vpath[4].y = y0;
  vpath[5].code = ART_END;
  vpath[5].x = 0;
  vpath[5].y = 0;
  
  vpath2 = art_vpath_affine_transform(vpath,affine);
  ArtSVP *svp = art_svp_from_vpath (vpath2); 
  art_drect_svp_union (&bbox,svp);
  art_rgb_svp_alpha (svp,
		     0, 0, pb->width, pb->height,
		     artColor(fg),
		     pb->pixels, pb->rowstride,
		     agam);
  art_svp_free(svp);
}

void LibArtDrawingKit::drawEllipse(const Vertex &, const Vertex &) {}
void LibArtDrawingKit::drawImage(Raster_ptr) {}

void LibArtDrawingKit::drawText(const Unistring &u) 
{
  font->drawText(u,affine[4],affine[5],pb,fg);
}

void LibArtDrawingKit::allocateText(const Unistring & s, Graphic::Requisition & req) {
  font->allocateText(s,req);
}

void LibArtDrawingKit::flush() {   
  int x = (int)(bbox.x0);
  int y = (int)(bbox.y0);
  int x1 = (int)(bbox.x1);
  int y1 = (int)(bbox.y1);
  ggi_visual_t vis = drawable->visual();
  ggiSetGCClipping(vis, x, y, x1, y1);
  ggiCrossBlit(memvis, x,y,x1-x,y1-y, vis, x,y );
  bbox.x0 = bbox.y0 = bbox.x1 = bbox.y1 = 0.;  
}

EXPORT_PLUGIN(LibArtDrawingKit, interface(DrawingKit))

