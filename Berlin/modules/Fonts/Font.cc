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

} // namespace
} // namespace

Font::~Font() {}

Glyph_ptr Font::glyph_char(Unichar c)
{
    return new Glyph(my_face, FT_Get_Char_Index(my_face, (FT_ULong)uc));
}

Glyph::Glyph(FT_Face face, Foo char_index)
{
    FT_Load_Glyph(my_face, char_index, FT_LOAD_DEFAULT);
}
