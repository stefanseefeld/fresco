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
#ifndef _Glyph_hh
#define _Glyph_hh

#include <Fresco/config.hh>
#include <Fresco/Font.hh>
#include <Fresco/Transform.hh>

#include <ft2build.h>
#include FT_FREETYPE_H

class Raster;


class Glyph : public virtual POA_Fresco::Glyph,
              public virtual RefCountBaseImpl,
              public virtual IdentifiableImpl
{
public:
    Raster_ptr bitmap();
    FontShape *decompose();
    void char_info(GlyphMetrics *gm);
    void transformation(Fresco::Transform_var);
private:
    FT_Face my_face;
};

#endif // header guard
