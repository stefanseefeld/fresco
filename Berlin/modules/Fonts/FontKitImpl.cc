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

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/DrawTraversal.hh>
#include <Berlin/MonoGraphic.hh>
#include "FontKitImpl.hh"
#include "Font.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin::FontKit;

namespace Berlin
{
namespace FontKit
{

class FontDecorator : public MonoGraphic
{
public:
  FontDecorator(Font_ptr f) : my_font(f) {}
  virtual void traverse(Traversal_ptr traversal)
  {
    traversal->visit(Graphic_var(_this()));
  }
  virtual void draw(DrawTraversal_ptr traversal)
  {
    DrawingKit_var drawing = traversal->drawing();
    // and do... NOTHING! yet.
    MonoGraphic::traverse(traversal);
  }
  virtual void pick(PickTraversal_ptr traversal)
  {
    MonoGraphic::traverse(traversal);
  }
private:
  Font_ptr my_font;
};

class FontSizeDecorator : public MonoGraphic
{
public:
  FontSizeDecorator(Coord s) : my_size(s) {}
  virtual void traverse(Traversal_ptr traversal)
  {
    traversal->visit(Graphic_var(_this()));
  }
  virtual void draw(DrawTraversal_ptr traversal)
  {
    DrawingKit_var drawing = traversal->drawing();
    // and do... NOTHING! yet.
    MonoGraphic::traverse(traversal);
  }
  virtual void pick(PickTraversal_ptr traversal)
  {
    MonoGraphic::traverse(traversal);
  }
private:
  Coord my_size;
};

FontKitImpl::FontIterator::FontIterator(FontKitImpl *fk)
  : my_fk(fk)
{
  Prague::Path path = RCManager::get_path("unifontpath");
  std::string file = path.lookup_file("unifont.bdf");
  FT_Face my_face;
  if (FT_New_Face(*(my_fk->get_ftlibrary()), file.c_str(), 0, &my_face) == 0)
    faces.push_back(file);
  if (!faces.size())
    Logger::log(Logger::text) << "unifont.bdf not found. This may result in poor unicode rendering!" << std::endl;

  path = RCManager::get_path("fontpath");
  scan(path);
  Logger::log(Logger::text) << faces.size() << " fonts found" << std::endl;
  if (!faces.size())
    throw std::runtime_error("no fonts found. Please check your font path !");
}

FontKitImpl::FontIterator::~FontIterator() {}

Font_ptr FontKitImpl::FontIterator::child()
{
  return my_fk->_cxx_default();
}
void FontKitImpl::FontIterator::next() { faces_iterator++;}
void FontKitImpl::FontIterator::prev() { faces_iterator--;}
void FontKitImpl::FontIterator::destroy() { delete this;}//deactivate();}

void FontKitImpl::FontIterator::begin() { faces_iterator = faces.begin();}
void FontKitImpl::FontIterator::end() { faces_iterator = faces.end();}
void FontKitImpl::FontIterator::scan(Prague::Path path)
{
  FT_Face my_face;
  for (Prague::Path::iterator i = path.begin(); i != path.end(); ++i)
    {
      Directory directory(*i, Directory::alpha);
      for (Prague::Directory::iterator j = directory.begin(); j != directory.end(); ++j)
	{
	  if ((*j)->name()[0] == '.') continue;
	  std::string file = (*j)->long_name();
	  if (FT_New_Face(*(my_fk->get_ftlibrary()), file.c_str(), 0, &my_face))
	    {
	      Logger::log(Logger::text) << "file " << file << " is not a font." << std::endl;
	      continue;
	    }
	  faces.push_back(file);
	}
    }
}

FontKitImpl::FontKitImpl(const std::string &id,
                         const Fresco::Kit::PropertySeq &p,
                         ServerContextImpl *c)
  : KitImpl(id, p, c)
{
  FT_Init_FreeType(&my_library);
}

FontKitImpl::~FontKitImpl() {}

KitImpl *FontKitImpl::clone(const Fresco::Kit::PropertySeq &p,
                            ServerContextImpl *c)
{
  return new FontKitImpl(repo_id(), p, c);
}

Font_ptr FontKitImpl::_cxx_default()
{
  Font *f = new Font("/usr/share/fonts/truetype/commercial/arialuni.ttf", 12, my_library);
  return f->_this();
}

Font_ptr FontKitImpl::filename(const char *fn, const Fresco::Unistring &style,
                               const Fresco::Coord size)
{
  Font *f = new Font(fn, size, my_library);
  return f->_this();
}

Font_ptr FontKitImpl::provide(const Fresco::Unistring &family,
                              const Fresco::Unistring &style,
                              const Fresco::Coord size)
{
  return _cxx_default(); // XXX
}

// pantone 1 and 2 font matching functions belong here.

Fresco::Graphic_ptr FontKitImpl::set_font(Fresco::Graphic_ptr g, Font_ptr f)
{
  Trace trace("FontKitImpl::set_font");
  return create_and_set_body<Graphic>(new FontDecorator(f), g);
}

Fresco::Graphic_ptr FontKitImpl::size(Fresco::Graphic_ptr g,
                                      const Fresco::Coord s)
{
  Trace trace("FontKitImpl::size");
  return create_and_set_body<Graphic>(new FontSizeDecorator(s), g);
}

Fresco::Graphic_ptr FontKitImpl::style(Fresco::Graphic_ptr g,
                                       const Fresco::Unistring &style)
{
  Trace trace("FontKitImpl::style");
  return Graphic::_nil();
}

Fresco::Graphic_ptr FontKitImpl::delta_size(Fresco::Graphic_ptr g,
                                            const Fresco::Coord ds)
{
  Trace trace("FontKitImpl::delta_size");
  return Graphic::_nil();
}

Fresco::Graphic_ptr FontKitImpl::delta_style(Fresco::Graphic_ptr g,
                                             const Fresco::Unistring &style)
{
  Trace trace("FontKitImpl::delta_style");
  return Graphic::_nil();
}

FT_Library *FontKitImpl::get_ftlibrary()
{
  return &my_library;
}

FontIterator_ptr FontKitImpl::first_font()
{
  FontIterator *fi = new FontIterator(this);
  fi->begin();
  return fi->_this();
}

FontIterator_ptr FontKitImpl::last_font()
{
  FontIterator *fi = new FontIterator(this);
  fi->end();
  return fi->_this();
}

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "FontKitImpl"};
  return create_prototype<Berlin::FontKit::FontKitImpl> ("IDL:fresco.org/Fresco/FontKit:1.0", properties, 2);
}

} // namespace
} // namespace
