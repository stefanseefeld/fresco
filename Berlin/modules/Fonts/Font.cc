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

#include "Font.hh"

namespace Berlin
{
namespace Font
{

Font::Font(const char *filename, int size, int xdpi, int ydpi,
           FT_Library library)
  : my_ftlib(library), my_size(size), my_xdpi(xdpi), my_ydpi(ydpi)
{
  FT_New_Face(my_ftlib, filename.c_str(), 0, &my_face);
  FT_Set_Char_Size(my_face, 0, my_size*64, xdpi, ydpi);
}

Font::~Font() {}

Glyph_ptr Font::glyph_char(Unichar c)
{
  return new Glyph(my_face, FT_Get_Char_Index(my_face, (FT_ULong)uc));
}

bool Font::has_char(Unichar c)
{
  return true;
}

bool Font::can_display(Unichar begin, Unichar end)
{
  return true;
}

Unistring Font::encoding()
{
  //
}

Unistring Font::font_family()
{
  return new Unistring(Unicode::to_CORBA(Babylon::String(my_face->family_name)));
}

Unistring Font::font_style()
{
  return new Unistring(Unicode::to_CORBA(Babylon::String(my_face->style_name)));
}

Unistring Font::fullname()
{
    // ??
}

void Font::font_metrics(FontMetrics &fm)
{
  fm.ascent = my_face->ascender;
  fm.descent = my_face->descender;
  fm.baseline = my_face->height;
  fm.underline_offset = my_face->underline_position;
  fm.underline_thickness = my_face->underline_width;
}

Coord height() const
{
  return my_size;
}

float angle()
{
  float angle = 0.;

  void *htable = FT_Get_Sfnt_Table(my_face, ft_sfnt_hhea);
  if (htable) {
    TT_HoriHeader *header = *htable;
    if (header->caret_Slope_Run != 0)
      angle = header->caret_Slope_Rise / header->caret_Slope_Run;
  }

  void *vtable = FT_Get_Sfnt_Table(my_face, ft_sfnt_vhea);
  if (vtable) {
    TT_VertHeader *header = *vtable;
    if (header->caret_Slope_Run != 0)
      angle = header->caret_Slope_Rise / header->caret_Slope_Run;
  }

  return angle;
}

float caret_offset()
{
  float offset = 0.;

  void *htable = FT_Get_Sfnt_Table(my_face, ft_sfnt_hhea);
  if (htable) {
    TT_HoriHeader *header = *htable;
    if (header->caret_Offset != 0)
      offset = header->caret_Offset;
  }

  void *vtable = FT_Get_Sfnt_Table(my_face, ft_sfnt_vhea);
  if (vtable) {
    TT_VertHeader *header = *vtable;
    if (header->caret_Slope_Run != 0)
      offset = header->caret_Offset;
  }

  return offset;
}

} // namespace
} // namespace
