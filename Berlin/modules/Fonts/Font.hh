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
#ifndef _Font_hh
#define _Font_hh

#include <Fresco/config.hh>
#include <Fresco/Font.hh>
#include "Berlin/RefCountBaseImpl.hh"
#include "Berlin/IdentifiableImpl.hh"

#include <ft2build.h>
#include FT_FREETYPE_H

class Font : public virtual POA_Fresco::Font,
             public virtual RefCountBaseImpl,
             public virtual IdentifiableImpl
{
public:
    Font(const char *filename, int size, int xdpi, int ydpi,
         FT_Library library);
    virtual ~Font();

    virtual Glyph_ptr glyph_char(Unichar c);
    virtual CORBA::Boolean has_char(Unichar c);
    virtual CORBA::Boolean can_display(Unichar begin, Unichar end);
    virtual Unistring* encoding();
    virtual Unistring* font_family();
    virtual void font_metrics(FontMetrics& fm);
    virtual Unistring* font_style();
    virtual Unistring* fullname();
    virtual Coord height();
    virtual Vertex kerning(Unichar first, Unichar second);
    virtual CORBA::Float angle();
    virtual CORBA::Float caret_offset();
private:
    FT_Face my_face;
    int my_size, my_xdpi, my_ydpi;
};

#endif // header guard
