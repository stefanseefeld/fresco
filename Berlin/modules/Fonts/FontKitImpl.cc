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
#include "FontKitImpl.hh"

using namespace Fresco;

class FontDecorator : public MonoGraphic
{
public:
  FontDecorator(Font f) : my_font(f) {}
  virtual void traverse(Traversal_ptr traversal) { traversal->visit(Graphic_var(_this()));}
  virtual void draw(DrawTraversal_ptr traversal)
  {
    DrawingKit_var drawing = traversal->drawing();
    // and do... NOTHING! yet.
    MonoGraphic::traverse(traversal);
  }
  virtual void pick(PickTraversal_ptr traversal) { MonoGraphic::traverse(traversal);}
private:
  Font_ptr my_font;
};

FontKitImpl::FontKitImpl(const std::string &id, const Fresco::Kit::PropertySeq &p)
  : KitImpl(id, p) {}

FontKitImpl::~FontKitImpl() { }

Graphic_ptr FontKitImpl::set_font(Graphic_ptr g, Font f)
{
  Trace trace("FontKitImpl::set_font");
  FontDecorator *decorator = new FontDecorator(f);
  activate(decorator);
  decorator->body(f);
  return decorator->_this();
}
