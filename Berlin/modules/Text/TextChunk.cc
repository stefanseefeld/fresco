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

TextChunk::TextChunk(Unichar u, const Fresco::Graphic::Requisition &r) :
    my_width(r.x.natural),
    my_height(r.y.natural),
    my_xalign(r.x.align),
    my_yalign(r.y.align),
    my_char(u),
    my_obj_name(0)
{ }

TextChunk::~TextChunk()
{ if(my_obj_name) free(const_cast<char*>(my_obj_name)); }

void TextChunk::request(Fresco::Graphic::Requisition &r)
{
    r.x.defined = true;
    r.x.minimum = r.x.natural = r.x.maximum = my_width;
    r.x.align   = my_xalign;
    r.y.defined = true;
    r.y.minimum = r.y.natural = r.y.maximum = my_height;
    r.y.align   = my_yalign;
}

const char *TextChunk::object_name()
{
    if (my_obj_name) return my_obj_name;
    std::ostringstream buf;
    buf << "Char ";
    if (my_char < 128) buf << (char)my_char << std::ends;
    else buf << my_char << std::ends;
    my_obj_name = strdup(buf.str().c_str());
    return my_obj_name;
}

void TextChunk::get_text(Babylon::String &u) 
{ u = Babylon::String(1, my_char); }

unsigned long TextChunk::get_length() 
{ return 1; }

void TextChunk::draw(DrawTraversal_ptr traversal)
{
  DrawingKit_var drawing = traversal->drawing();
  drawing->draw_char(my_char);  
}
