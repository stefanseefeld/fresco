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
#ifndef _FontKitImpl_hh
#define _FontKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/FontKit.hh>
#include <Fresco/Font.hh>
#include <Berlin/KitImpl.hh>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Berlin
{
namespace FontKit
{

using namespace Fresco;

class FontKitImpl : public virtual POA_Fresco::FontKit,
                    public KitImpl
{
public:
    FontKitImpl(const std::string &, const Fresco::Kit::PropertySeq &);
    virtual ~FontKitImpl();
    virtual KitImpl *clone(const Fresco::Kit::PropertySeq &p)
    {
        return new FontKitImpl(repo_id(), p);
    }

    virtual Font_ptr _cxx_default();
    virtual Font_ptr filename(const char* file, const Fresco::Unistring& style,
                              Coord size);
    virtual Font_ptr provide(const Unistring& family, const Unistring& style,
                             Coord size);
    virtual Graphic_ptr set_font(Graphic_ptr g, Font_ptr f);
    virtual Graphic_ptr size(Graphic_ptr g, Coord s);
    virtual Graphic_ptr style(Graphic_ptr g, const Unistring& s);
    virtual Graphic_ptr delta_size(Graphic_ptr g, Coord ds);
    virtual Graphic_ptr delta_style(Graphic_ptr g, const Unistring& ds);

    virtual FontIterator_ptr first_font();
    virtual FontIterator_ptr last_font();
private:
    FT_Library my_library;
};

} // namespace
} // namespace

#endif // header guard
