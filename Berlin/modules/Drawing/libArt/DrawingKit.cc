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
  bbox.x0 = bbox.y0 = bbox.x1 = bbox.y1 = 0;  
}

static inline ggi_pixel ggiColor(Color c1, ggi_visual_t vis) {
  ggi_color c2;
  static double scale = 0xffff;
  c2.r = static_cast<uint16>(c1.red * scale);
  c2.g = static_cast<uint16>(c1.green * scale);
  c2.b = static_cast<uint16>(c1.blue * scale);
  c2.a = static_cast<uint16>(c1.alpha * scale);
  return ggiMapColor(vis,&c2);
}

static inline art_u32 artColor(Color c) {
  art_u32 c2 = 0;
  static double scale = 0xff;
  c2 += (static_cast<art_u8>(c.blue * scale) << 24);
  c2 += (static_cast<art_u8>(c.green * scale) << 16);
  c2 += (static_cast<art_u8>(c.red * scale) << 8);
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
  affine[4] = matrix[0][3];
  affine[5] = matrix[1][3];
}

void LibArtDrawingKit::setClipping(Region_ptr r)
{
  cl->copy(r);
//   double xr = drawable->resolution(xaxis);
//   double yr = drawable->resolution(yaxis);

//   int x = (int)(cl->upper.x * xr);
//   int y = (int)(cl->upper.y * yr);
//   int x2 = (int)(cl->lower.x * xr);  
//   int y2 = (int)(cl->lower.y * yr);

//   ggiSetGCClipping(memvis, x, y, x2, y2);
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
  ArtVpath vpath[(fs == outline ? len : len + 1)];
  ArtVpath *tvpath;
  ArtVpath *tsvpath;
  double resScale[6]  = {
    drawable->resolution(xaxis), 0, 0, 
      drawable->resolution(yaxis), 0, 0
      };

  if (fs == outline) {
    for (int i = 0; i < len; i++) {
      vpath[i].code = i == 0 ? ART_MOVETO_OPEN 
	: (i == len - 1 ? ART_END : ART_LINETO);
      vpath[i].x = p[i].x;
      vpath[i].y = p[i].y;
    }

  } else {
    for (int i = 0; i < len; i++) {
      vpath[i].code = i == 0 ? ART_MOVETO : ART_LINETO;
      vpath[i].x = p[i].x;
      vpath[i].y = p[i].y;
    }
    vpath[len] = vpath[0];
    vpath[len].code = ART_END;
  }
  
  ArtDRect locd;
  ArtIRect loc;
  ArtDRect clip = {cl->upper.x, cl->upper.y,
		     cl->lower.x, cl->lower.y};
  art_drect_affine_transform(&clip,&clip,resScale);

  tvpath = art_vpath_affine_transform(vpath,affine);
  tsvpath = art_vpath_affine_transform(tvpath,resScale);

  ArtSVP *svp = art_svp_from_vpath (tsvpath); 
  art_drect_svp (&locd, svp);
  art_drect_intersect(&locd,&locd,&clip);
  art_drect_to_irect(&loc, &locd);
  art_irect_union (&bbox,&bbox,&loc);
//   cerr << "bbox " << loc.x0 << " " << loc.y0 << " " << loc.x1 << " " << loc.y1 << endl;

  // WARNING: I do not know why these parameters work for rgb_svp..
  // imho they should not, but they appear to. I have asked raph
  // levien why, and hope to hear back soon. in the mean time,
  // do not assume that I actually know how libart does coordinates
  // :(

  art_rgb_svp_alpha (svp,
		     0, 0, 
		     loc.x1, loc.y1,
		     artColor(fg),
		     pb->pixels, 
		     pb->rowstride,
		     agam);
  art_svp_free(svp);
}

//void LibArtDrawingKit::drawPatch(const Patch &);

void LibArtDrawingKit::drawRect(const Vertex &bot, const Vertex &top) 
{

  // this needs work, if you want to try to speed it up..
//   if (affine[0] == 1. && affine[3] == 1. && 
//       affine[1] == 0. && affine[2] == 0. &&
//       fg.alpha == 1. // !!FIXME!! add in texture check here.
//       )
//     {
//       // short circuit identity-transformed
//       // boxes of solid non-alpha colors.
//       double xr = drawable->resolution(xaxis);
//       double yr = drawable->resolution(yaxis);
//       int a = (int)(top.x * xr + affine[4]);
//       int b = (int)(top.y * yr + affine[5]);
//       int c = (int)(bot.x * xr + affine[4]);
//       int d = (int)(bot.y * yr + affine[5]);
//       ggiSetGCForeground(memvis, ggiColor(fg, memvis));
//       ggiDrawBox(memvis, a,b,c,d);
//       ArtIRect loc = {a,b,c,d};
//       art_irect_union (&bbox,&bbox,&loc);
//       return;
//     }
  
  Path path;
  path.length(5);
  path[0].x = top.x, path[0].y = top.y, path[0].z = 0.;
  path[1].x = bot.x, path[1].y = top.y, path[1].z = 0.;
  path[2].x = bot.x, path[2].y = bot.y, path[2].z = 0.;
  path[3].x = top.x, path[3].y = bot.y, path[3].z = 0.;
  path[4].x = top.x, path[4].y = top.y, path[4].z = 0.;
  drawPath(path);
}

void LibArtDrawingKit::drawEllipse(const Vertex &, const Vertex &) {}
void LibArtDrawingKit::drawImage(Raster_ptr) {}

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
  ggi_visual_t vis = drawable->visual();
  //   ggiSetGCClipping(vis, bbox.x0, bbox.y0, bbox.x1, bbox.y1);
  ggiCrossBlit(memvis, bbox.x0,bbox.y0,
	       bbox.x1-bbox.x0,
	       bbox.y1-bbox.y0, 
	       vis, bbox.x0,bbox.y0 );
  bbox.x0 = bbox.y0 = bbox.x1 = bbox.y1 = 0;  
}

EXPORT_PLUGIN(LibArtDrawingKit, interface(DrawingKit))

