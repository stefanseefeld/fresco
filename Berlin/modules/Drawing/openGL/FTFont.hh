/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 2002 Nick Lewycky <nicholas@fresco.org> 
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
#ifndef _FTFont_hh
#define _FTFont_hh

#include <Prague/Sys/MMap.hh>
#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/Unicode.hh>
#include "Font.hh"
#include <GL/gl.h>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace openGL
{

class FTFont : public Font
//. This is a Freetype font.
{
public:
  FTFont();
  virtual ~FTFont();
  virtual CORBA::ULong size();
  virtual CORBA::ULong weight();
  virtual Fresco::Unistring *family();
  virtual Fresco::Unistring *subfamily();
  virtual Fresco::Unistring *fullname();
  virtual Fresco::Unistring *style();
  virtual Fresco::DrawingKit::FontMetrics metrics();
  virtual Fresco::DrawingKit::GlyphMetrics metrics(Fresco::Unichar);

  virtual void size(CORBA::ULong);

  void draw_char(Fresco::Unichar);
  void allocate_char(Fresco::Unichar, Fresco::Graphic::Requisition &);
private:
  FT_Library my_library;
  FT_Face    my_face;
  Fresco::Unistring _family;
  Fresco::Unistring _subfamily;
  Fresco::Unistring _fullname;
  Fresco::Unistring _style;

  CORBA::ULong my_size;
};

}

#endif
