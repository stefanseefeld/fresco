/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1998 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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

#include <Fresco/config.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/Region.hh>
#include <Fresco/IO.hh>
#include "TextChunk.hh"

#include <sstream>

using namespace Fresco;

using namespace Berlin::TextKit;

TextChunk::TextChunk(Unichar u, const Fresco::Graphic::Requisition &r)
  : _width(r.x.natural), _height(r.y.natural), _xalign(r.x.align), _yalign(r.y.align), _char(u), _obj_name(0)
{
}

TextChunk::~TextChunk()
{
  if (_obj_name) free(const_cast<char*>(_obj_name));
}

void TextChunk::request(Fresco::Graphic::Requisition &r)
{
  r.x.defined = true;
  r.x.minimum = r.x.natural = r.x.maximum = _width;
  r.x.align   = _xalign;
  r.y.defined = true;
  r.y.minimum = r.y.natural = r.y.maximum = _height;
  r.y.align   = _yalign;
}

const char *TextChunk::object_name()
{
  if (_obj_name) return _obj_name;
  std::ostringstream buf;
  buf << "Char ";
  if (_char < 128) buf << (char)_char << std::ends;
  else buf << _char << std::ends;
  _obj_name = strdup(buf.str().c_str());
  return _obj_name;
}

void TextChunk::get_text(Babylon::String &u) 
{ 
  u = Babylon::String(1, _char);
}

unsigned long TextChunk::get_length() 
{ 
  return 1;
}

void TextChunk::draw(DrawTraversal_ptr traversal)
{
  DrawingKit_var drawing = traversal->drawing();
  drawing->draw_char(_char);  
}
