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
#ifndef _Fonts_Font_hh
#define _Fonts_Font_hh

#include <Fresco/config.hh>
#include <Fresco/Font.hh>
#include <Fresco/Unicode.hh>
#include <Berlin/RefCountBaseImpl.hh>
#include <Berlin/IdentifiableImpl.hh>
#include "Glyph.hh"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TRUETYPE_TABLES_H

namespace Berlin
{
namespace FontKit
{

class Font : public virtual POA_Fresco::Font,
             public virtual RefCountBaseImpl,
             public virtual IdentifiableImpl
{
public:
  Font(const char *filename, CORBA::ULong size, FT_Library library);
  virtual ~Font();

  virtual Fresco::Glyph_ptr glyph_char(Fresco::Unichar c);
  virtual CORBA::Boolean has_char(Fresco::Unichar c);
  virtual CORBA::Boolean can_display(Fresco::Unichar begin,
                                     Fresco::Unichar end);
  virtual Fresco::Unistring* encoding();
  virtual Fresco::Unistring* font_family();
  virtual void font_metrics(Fresco::FontMetrics& fm);
  virtual Fresco::Unistring* font_style();
  virtual Fresco::Unistring* fullname();
  virtual Fresco::Coord height();
  virtual Fresco::Vertex kerning(Fresco::Unichar first, Fresco::Unichar second);
  virtual CORBA::Float angle();
  virtual CORBA::Float caret_offset();
private:
  FT_Library my_ftlib;
  FT_Face my_face;
  CORBA::ULong my_size;
};

} // namespace
} // namespace

#endif // header guard
