/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2003 Nick Lewycky <nicholas@fresco.org>
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

#include <Fresco/Raster.hh>
#include <Berlin/RasterImpl.hh>
#include "Glyph.hh"

namespace Berlin
{
namespace FontKit
{

GlyphImpl::GlyphImpl(const FT_Face face, const CORBA::ULong size,
                     Fresco::Unichar char_index)
  : my_face(face), my_size(size*64), my_uc(char_index)
{
  my_tr.xx = 0x10000;
  my_tr.xy = 0x00000;
  my_tr.yx = 0x00000;
  my_tr.yy = 0x10000;
}

GlyphImpl::~GlyphImpl() {}

Fresco::Raster_ptr GlyphImpl::bitmap(CORBA::ULong xdpi, CORBA::ULong ydpi)
{
  if (FT_Set_Char_Size(my_face, 0, my_size, xdpi, ydpi) != 0)
    std::cerr << "FontKit bitmap: set char size failed." << std::endl;
  FT_Set_Transform(my_face, &my_tr, 0);

  if (FT_Load_Glyph(my_face, FT_Get_Char_Index(my_face, my_uc),
		    FT_LOAD_DEFAULT) != 0)
      std::cerr << "FontKit bitmap: load glyph failed." << std::endl;

  FT_Glyph glyph;
  if (FT_Get_Glyph(my_face->glyph, &glyph) != 0)
    std::cerr << "FontKit bitmap: get glyph failed." << std::endl;
  if (FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1) != 0)
    std::cerr << "FontKit bitmap: glyph to bitmap failed." << std::endl;
  FT_BitmapGlyph glyph_bitmap = (FT_BitmapGlyph)glyph;

  unsigned char *buffer = glyph_bitmap->bitmap.buffer;
  int width = glyph_bitmap->bitmap.width;
  int height = glyph_bitmap->bitmap.rows;

  Fresco::Raster::ColorSeq pixels;
  pixels.length(width*height);

  switch (glyph_bitmap->bitmap.pixel_mode)
    {
    case FT_PIXEL_MODE_NONE:
      // should never happen
      std::cout << "FontKit confused: FT_PIXEL_MODE_NONE?" << std::endl;
      break;
    case FT_PIXEL_MODE_MONO: // MSB 1 bpp
      for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
          Fresco::Color c;
          c.red = 1.; c.green = 1.; c.blue = 1.;
          c.alpha = (buffer[i*(width/8)+(j/8)] & (0x80 >> j%8)) ? 1. : 0.;
          pixels[i*width+j] = c;
        }
      break;
    case FT_PIXEL_MODE_GRAY: // 8 bpp count of grey levels in num_bytes
      for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
          Fresco::Color c;
          c.red = 1.; c.green = 1.; c.blue = 1.;
          c.alpha = buffer[i*width+j] / 255.;
          pixels[i*width+j] = c;
        }
      break;
    case FT_PIXEL_MODE_GRAY2: // 2bpp (no known fonts)
      std::cout << "FontKit NYI: FT_PIXEL_MODE_GRAY2" << std::endl;
      break;
    case FT_PIXEL_MODE_GRAY4: // 4bpp (no known fonts)
      std::cout << "FontKit NYI: FT_PIXEL_MODE_GRAY4" << std::endl;
      break;
    case FT_PIXEL_MODE_LCD: // 8bpp RGB or BGR, width=3*glyph_width
      std::cout << "FontKit NYI: FT_PIXEL_MODE_LCD" << std::endl;
      break;
    case FT_PIXEL_MODE_LCD_V: // 8bpp RGB or BGR, height=3*glyph_rows
      std::cout << "FontKit NYI: FT_PIXEL_MODE_LCD_V" << std::endl;
      break;
    default:
      std::cout << "FontKit unknown type: "
                << glyph_bitmap->bitmap.pixel_mode << std::endl;
      break;
    }
  FT_Done_Glyph(glyph);
  FT_Set_Transform(my_face, 0, 0);

  // XXX we should be using the RasterKit.
  Fresco::Raster::Info rinfo;
  rinfo.colortype = 6; // PNG_COLOR_TYPE_RGB_ALPHA (sigh).
  rinfo.depth = 8;
  rinfo.width = width;
  rinfo.height = height;
  RasterImpl *raster = new RasterImpl(rinfo);
  activate(raster);

  Fresco::Raster::Index lower; lower.x = 0; lower.y = 0;
  Fresco::Raster::Index upper; upper.x = width; upper.y = height;
  raster->load_pixels(lower, upper, pixels);

  return raster->_this();
}

Fresco::FontShape *GlyphImpl::decompose()
{
  FT_Set_Char_Size(my_face, 0, my_size, 0, 0);
  FT_Set_Transform(my_face, &my_tr, 0);
  if (FT_Load_Glyph(my_face, FT_Get_Char_Index(my_face, my_uc),
		    FT_LOAD_DEFAULT) != 0)
      std::cerr << "FontKit decompose: load glyph failed." << std::endl;
  Fresco::FontShape *f = new Fresco::FontShape(); f->length(0);
  // use FT_Outline_Decompose

  FT_Outline_Funcs funcs;
  funcs.move_to = &moveto;
  funcs.line_to = &lineto;
  funcs.conic_to = &conicto;
  funcs.shift = 0;
  funcs.delta = 0;

  FT_Glyph glyph;
  FT_Get_Glyph(my_face->glyph, &glyph);
  FT_OutlineGlyph oglyph = (FT_OutlineGlyph)glyph;

  FT_Outline_Decompose(&(oglyph->outline), &funcs, 0);

  FT_Done_Glyph(glyph);
  FT_Set_Transform(my_face, 0, 0);

  return f;
}

void GlyphImpl::char_info(Fresco::GlyphMetrics &gm)
{
  if (FT_Load_Glyph(my_face, FT_Get_Char_Index(my_face, my_uc),
		    FT_LOAD_DEFAULT) != 0)
      std::cerr << "FontKit char_info: load glyph failed." << std::endl;

  double scale = 1.;

  gm.size.x = static_cast<CORBA::Long>(my_face->glyph->metrics.width / scale);
  gm.size.y = static_cast<CORBA::Long>(my_face->glyph->metrics.height / scale);
  gm.hori_bearing.x = static_cast<CORBA::Long>(my_face->glyph->metrics.horiBearingX / scale);
  gm.hori_bearing.y = static_cast<CORBA::Long>(my_face->glyph->metrics.horiBearingY / scale);
  gm.hori_advance =  static_cast<CORBA::Long>(my_face->glyph->metrics.horiAdvance / scale);
  gm.vert_bearing.x = static_cast<CORBA::Long>(my_face->glyph->metrics.vertBearingX / scale);
  gm.vert_bearing.y = static_cast<CORBA::Long>(my_face->glyph->metrics.vertBearingY / scale);
  gm.vert_advance = static_cast<CORBA::Long>(my_face->glyph->metrics.vertAdvance / scale);

  gm.italic_correction = 0.;

  void *table = FT_Get_Sfnt_Table(my_face, ft_sfnt_hhea);
  if (table) {
    TT_HoriHeader *header = (TT_HoriHeader*)table;
    gm.italic_correction = header->caret_Offset / scale; // XXX MAYBE WRONG
  }
}

void GlyphImpl::transformation(Fresco::Transform_ptr tr)
{
  Fresco::Vertex  o = {0, 0, 0};
  Fresco::Vertex e1 = {1, 0, 0};
  Fresco::Vertex e2 = {0, 1, 0};

  tr->transform_vertex(o);
  tr->transform_vertex(e1);
  tr->transform_vertex(e2);

  my_tr.xx = static_cast<FT_Fixed>((e1.x-o.x)*0x10000);
  my_tr.xy = static_cast<FT_Fixed>((e1.y-o.y)*0x10000);
  my_tr.yx = static_cast<FT_Fixed>((e2.x-o.x)*0x10000);
  my_tr.yy = static_cast<FT_Fixed>((e2.y-o.y)*0x10000);
}

int moveto(FT_Vector *to, void*f)
{
  Fresco::FontShape *fs = (Fresco::FontShape*)f;

  Fresco::FontShapeSegment *fss = new Fresco::FontShapeSegment;
  fss->type = Fresco::move;
  fss->to.x = to->x; fss->to.y = to->y;
  return 0;
}

int lineto(FT_Vector *to, void*f)
{
  Fresco::FontShape *fs = (Fresco::FontShape*)f;

  Fresco::FontShapeSegment *fss = new Fresco::FontShapeSegment;
  fss->type = Fresco::line;
  fss->to.x = to->x; fss->to.y = to->y;
  return 0;
}

int conicto(FT_Vector *c, FT_Vector *to, void*f)
{
  Fresco::FontShape *fs = (Fresco::FontShape*)f;

  Fresco::FontShapeSegment *fss = new Fresco::FontShapeSegment;
  fss->type = Fresco::conic;
  fss->to.x = to->x; fss->to.y = to->y;
  fss->control1.x = c->x; fss->control1.y = c->y;
  return 0;
}

int cubicto(FT_Vector *c1, FT_Vector *c2, FT_Vector *to, void*f)
{
  Fresco::FontShape *fs = (Fresco::FontShape*)f;

  Fresco::FontShapeSegment *fss = new Fresco::FontShapeSegment;
  fss->type = Fresco::conic;
  fss->to.x = to->x; fss->to.y = to->y;
  fss->control1.x = c1->x; fss->control1.y = c1->y;
  fss->control2.x = c2->x; fss->control2.y = c2->y;
  return 0;
}

} // namespace
} // namespace
