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
namespace FontKit
{

Font::Font(const char *filename, CORBA::ULong size, FT_Library library)
  : my_ftlib(library), my_size(size)
{
  if (FT_New_Face(my_ftlib, filename, 0, &my_face) != 0)
    { throw Fresco::CreationFailureException(); }
  FT_Set_Char_Size(my_face, 0, my_size*64, 0, 0);
}

Font::~Font() {}

Fresco::Glyph_ptr Font::glyph_char(Fresco::Unichar c)
{
  GlyphImpl *glyph = new GlyphImpl(my_face, my_size, c);
  return glyph->_this();
}

CORBA::Boolean Font::has_char(Fresco::Unichar c)
{
  return FT_Get_Char_Index(my_face, c) != 0;
}

CORBA::Boolean Font::can_display(Fresco::Unichar begin, Fresco::Unichar end)
{
  return true;
}

Fresco::Unistring *Font::encoding()
{
  return new Fresco::Unistring(Unicode::to_CORBA(Babylon::String("encoding NYI")));
}

Fresco::Unistring *Font::font_family()
{
  return new Fresco::Unistring(Unicode::to_CORBA(Babylon::String(my_face->family_name)));
}

Fresco::Unistring *Font::font_style()
{
  return new Fresco::Unistring(Unicode::to_CORBA(Babylon::String(my_face->style_name)));
}

Fresco::Unistring *Font::fullname()
{
  return new Fresco::Unistring(Unicode::to_CORBA(Babylon::String("Fullname NYI")));
}

void Font::font_metrics(Fresco::FontMetrics &fm)
{
  fm.ascent = my_face->ascender;
  fm.descent = my_face->descender;
  fm.baseline = my_face->height;
  fm.underline_offset = my_face->underline_position;
  fm.underline_thickness = my_face->underline_thickness;
}

Fresco::Coord Font::height()
{
  return my_size;
}

Fresco::Vertex Font::kerning(Fresco::Unichar first, Fresco::Unichar second)
{
  // XXX this is BIDI-incorrect, of course...
  Fresco::Vertex k;
  k.x = 0; k.y = 0;
  if (FT_HAS_KERNING(my_face))
    {
      FT_Vector kern;
      FT_Get_Kerning(my_face, FT_Get_Char_Index(my_face, first),
          FT_Get_Char_Index(my_face, second), FT_KERNING_UNFITTED, &kern);
      k.x = kern.x >> 6;
      k.y = kern.y >> 6;
    }
  return k;
}

CORBA::Float Font::angle()
{
  float angle = 0.;

  void *htable = FT_Get_Sfnt_Table(my_face, ft_sfnt_hhea);
  if (htable) {
    TT_HoriHeader *header = (TT_HoriHeader*)htable;
    if (header->caret_Slope_Run != 0)
      angle = header->caret_Slope_Rise / header->caret_Slope_Run;
  }

  void *vtable = FT_Get_Sfnt_Table(my_face, ft_sfnt_vhea);
  if (vtable) {
    TT_VertHeader *header = (TT_VertHeader*)vtable;
    if (header->caret_Slope_Run != 0)
      angle = header->caret_Slope_Rise / header->caret_Slope_Run;
  }

  return angle;
}

CORBA::Float Font::caret_offset()
{
  float offset = 0.;

  void *htable = FT_Get_Sfnt_Table(my_face, ft_sfnt_hhea);
  if (htable) {
    TT_HoriHeader *header = (TT_HoriHeader*)htable;
    if (header->caret_Offset != 0)
      offset = header->caret_Offset;
  }

  void *vtable = FT_Get_Sfnt_Table(my_face, ft_sfnt_vhea);
  if (vtable) {
    TT_VertHeader *header = (TT_VertHeader*)vtable;
    if (header->caret_Slope_Run != 0)
      offset = header->caret_Offset;
  }

  return offset;
}

} // namespace
} // namespace
