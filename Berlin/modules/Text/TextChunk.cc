//
// $Id$
//
// This source file is a part of the Berlin Project.
// Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
// http://www.berlin-consortium.org
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public License
// as published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//

#include <Text/TextChunk.hh>
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/DrawTraversal.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/IO.hh>

using namespace Warsaw;

TextChunk::TextChunk(Unichar u, const Warsaw::Graphic::Requisition &r)
  : width(r.x.natural), height(r.y.natural), xalign(r.x.align), yalign(r.y.align), myChar(u)
{
}

void TextChunk::request(Warsaw::Graphic::Requisition &r)
{
  r.x.defined = true;
  r.x.minimum = r.x.natural = r.x.maximum = width;
  r.x.align   = xalign;
  r.y.defined = true;
  r.y.minimum = r.y.natural = r.y.maximum = height;
  r.y.align   = yalign;
}

void TextChunk::get_text(Unicode::String &u) 
{ 
  u = Unicode::String(myChar);
}

unsigned long TextChunk::get_length() 
{ 
  return 1;
}

void TextChunk::draw(DrawTraversal_ptr dt)
{
  DrawingKit_var(dt->kit())->draw_char(myChar);  
}
