/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 2000 Nathaniel Smith <njs@berlin-consortium.org>
 * http://www.berlin-consortium.org
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
#include <Warsaw/config.hh>
#include <Warsaw/TextBuffer.hh>
#include "Text/TextViewer.hh"
#include <Prague/Sys/Tracer.hh>
#include <algorithm>

using namespace Prague;

TextViewer::TextViewer(TextBuffer_ptr txt, TextKit_ptr tk, DrawingKit_ptr dk, Compositor *c)
  : Composition(dk, c),
    kit(TextKit::_duplicate(tk)),
    buffer(TextBuffer::_duplicate(txt))
{
  Trace trace("TextViewer::TextViewer");
}

// FIXME: move all this to the constructor when we go to POA
void TextViewer::init()
{
  MutexGuard guard(childMutex);
//   Trace trace("TextViewer::init");
  Unistring_var us = buffer->value();
  CORBA::ULong len = us->length();
  for (unsigned long i = 0; i < len; i++)
    {
      Graphic_var child = kit->ch(us[i]);
      Edge edge;
      edge.parent = Graphic::_duplicate(child);
      edge.id = tag();
      children.insert(children.begin() + i, edge);
      child->addParent(Graphic_var(_this()), edge.id);
    }
}

TextViewer::~TextViewer() {}

void TextViewer::update(const CORBA::Any &a) 
{
//   Trace trace1("TextViewer::update");
  TextBuffer::Change *ch;  
  if (a >>= ch)
    {
      switch (ch->type)
	{
	case TextBuffer::insert:
	  {
//             Trace trace2("TextViewer::update - insert");
	    MutexGuard guard(childMutex);
	    Unistring_var us = buffer->getChars(ch->pos, (CORBA::ULong)ch->len);
	    CORBA::ULong len = us->length();
	    for (unsigned long i = 0; i < len; i++)
	      {
		Graphic_var child = kit->ch(us[i]);
		Edge edge;
		edge.parent = Graphic::_duplicate(child);
		edge.id = tag();
		children.insert(children.begin() + ch->pos + i, edge);
		child->addParent(Graphic_var(_this()), edge.id);
	      }
	  }
	  break;
	  
	case TextBuffer::remove:
	  {
//             Trace trace2("TextViewer::update - remove");
	    MutexGuard guard(childMutex);
	    unsigned long start = min(ch->pos, static_cast<CORBA::ULong>(children.size()));
	    unsigned long end = min(ch->pos + ch->len, static_cast<CORBA::ULong>(children.size()));
	    if (ch->len < 0) swap(start, end);
	    for (clist_t::iterator i = children.begin() + start; i != children.begin() + end; i++)
	      (*i).parent->removeParent(Graphic_var(_this()), (*i).id);
	    children.erase(children.begin() + start, children.begin() + end);
	  }	
	  break;
	case TextBuffer::cursor:
//           Trace trace2("TextViewer::update - cursor");
	  // we'll do some cursor-ish stuff someday
	  break;
	}
    }
//   needRedraw();
  needResize();
}
