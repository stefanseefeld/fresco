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
#ifndef _Fonts_FontKitImpl_hh
#define _Fonts_FontKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/FontKit.hh>
#include <Fresco/Font.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/Kit.hh>
#include <Fresco/Types.hh>
#include <Fresco/Unicode.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/Logger.hh>
#include <Berlin/RCManager.hh>
#include <Prague/Sys/Directory.hh>
#include <Prague/Sys/Path.hh>

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

  class FontIterator : public virtual POA_Fresco::FontIterator
  {
  public:
    FontIterator(FontKitImpl *);
    virtual ~FontIterator();

    virtual Font_ptr child();
    virtual void next();
    virtual void prev();
    virtual void destroy();

    virtual void begin();
    virtual void end();
    virtual void scan(Prague::Path);
  private:
    FontKitImpl *my_fk;
    std::vector<std::string> faces;
    std::vector<std::string>::iterator faces_iterator;
  };

  FontKitImpl(const std::string &,
              const Fresco::Kit::PropertySeq &,
              ServerContextImpl *);
  virtual ~FontKitImpl();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &,
                         ServerContextImpl *);

  virtual Fresco::Font_ptr _cxx_default();
  virtual Fresco::Font_ptr filename(const char* file, const Fresco::Unistring& style,
			            Fresco::Coord size);
  virtual Fresco::Font_ptr provide(const Fresco::Unistring& family, const Fresco::Unistring& style,
                           const Fresco::Coord size);
  virtual Fresco::Graphic_ptr set_font(Fresco::Graphic_ptr g, const Fresco::Font_ptr f);
  virtual Fresco::Graphic_ptr size(Fresco::Graphic_ptr g, const Fresco::Coord s);
  virtual Fresco::Graphic_ptr style(Fresco::Graphic_ptr g, const Fresco::Unistring& s);
  virtual Fresco::Graphic_ptr delta_size(Fresco::Graphic_ptr g, const Fresco::Coord ds);
  virtual Fresco::Graphic_ptr delta_style(Fresco::Graphic_ptr g, const Fresco::Unistring& ds);

  virtual FT_Library *FontKitImpl::get_ftlibrary();

  virtual Fresco::FontIterator_ptr first_font();
  virtual Fresco::FontIterator_ptr last_font();
private:
  FT_Library my_library;
};

} // namespace
} // namespace

#endif // header guard
