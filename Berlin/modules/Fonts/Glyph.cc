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

Glyph::Glyph(FT_Face face, FT_ULong char_index)
    : my_face(face)
{
  FT_Load_Glyph(my_face, char_index, FT_LOAD_DEFAULT);
}

Raster_ptr Glyph::bitmap()
{
  RasterImpl *raster = new RasterImpl();
  activate(raster);

  FT_Set_Transform(my_face, &my_tr, 0);

  FT_Glyph glyph;
  FT_Get_Glyph(my_face->glyph, &glyph);
  FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, &origin, 1);
  FT_BitmapGlyph glyph_bitmap = (FT_BitmapGlyph)glyph;

  Fresco::Raster::Data pixels;

  switch (glyph_bitmap->bitmap.pixel_mode)
    {
    case FT_PIXEL_MODE_NONE:
      // should never happen
      std::cout << "WTF;FT_PIXEL_MODE_NONE" << std::endl;
      break;
    case FT_PIXEL_MODE_MONO: // MSB 1 bpp
      internal_format = GL_ALPHA;
      format = GL_ALPHA;
      type = GL_UNSIGNED_BYTE;
      for (int i = 0; i < height; i++)
	for (int j = 0; j < width; j++)
	  pixels[i*w + j] = (buffer[i*(width/8)+(j/8)] &
			     (0x80 >> j%8)) ? 0xFF : 0;
      break;
    case FT_PIXEL_MODE_GRAY: // 8 bpp count of grey levels in num_bytes
      internal_format = GL_ALPHA;
      format = GL_ALPHA;
      type = GL_UNSIGNED_BYTE;
      for (int i = 0; i < height; i++)
	for (int j = 0; j < width; j++)
	  pixels[i*w+j] = buffer[i*width+j];
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
      std::cout << "FontKit unknown type : "
		<< glyph_bitmap->bitmap.pixel_mode << std::endl;
      break;
    }
  FT_Set_Transform(my_face, 0, 0);
  FT_Done_Glyph(glyph);

  activate(pixels);
  raster->store_pixels(pixels);

  return raster;
}

FontShape *Glyph::decompose()
{
  FT_Set_Transform(that->my_face, &my_tr, 0);
  // use FT_Outline_Decompose
  FT_Set_Transform(that->my_face, 0, 0);
}

void Glyph::char_info(GlyphMetrics *gm)
{
  double scale = 1.;
  gm.size.x = static_cast<CORBA::Long>(my_face->glyph->metrics.width / scale);
  gm.size.y = static_cast<CORBA::Long>(my_face->glyph->metrics.height / scale);
  gm.hori_bearing.x = static_cast<CORBA::Long>(my_face->glyph->metrics.horiBearingX / scale);
  gm.hori_bearing.y = static_cast<CORBA::Long>(my_face->glyph->metrics.horiBearingY /scale);
  gm.hori_advance =  static_cast<CORBA::Long>(my_face->glyph->metrics.horiAdvance / scale);
  gm.vert_bearing.x = static_cast<CORBA::Long>(my_face->glyph->metrics.vertBearingX / scale);
  gm.vert_bearing.y = static_cast<CORBA::Long>(my_face->glyph->metrics.vertBearingY / scale);
  gm.vert_advance = static_cast<CORBA::Long>(my_face->glyph->metrics.vertAdvance / scale);

  gm.italic_correction = 0.;

  void *table = FT_Get_Sfnt_Table(my_face, ft_sfnt_hhea);
  if (table) {
    TT_HoriHeader *header = *table;
    gm.italic_correction = header->caret_Offset / 64.; // XXX MAYBE WRONG
  }
}

void Glyph::transform(Fresco::Transform_var tr)
{
  Fresco::Vertex  o = {0, 0, 0};
  Fresco::Vertex e1 = {1, 0, 0};
  Fresco::Vertex e2 = {0, 1, 0};

  tr->transform_vertex(o);
  tr->transform_vertex(e1);
  tr->transform_vertex(e2);

  my_tr.xx = (e1.x-o.x)*0x10000;
  my_tr.xy = (e1.y-o.y)*0x10000;
  my_tr.yx = (e2.x-o.x)*0x10000;
  my_tr.yy = (e2.y-o.y)*0x10000;
}
