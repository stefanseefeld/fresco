/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1998 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _TextChunk_hh
#define _TextChunk_hh

#include <Fresco/config.hh>
#include <Fresco/Unicode.hh>
#include <Berlin/GraphicImpl.hh>

//. A text chunk is constructed with a "canonical size", which is essentially its
//. requisition within the font it was constructed for, on the drawable it was
//. intended to be drawn on. This might not actually be the font it winds up
//. drawing with, nor the drawable it winds up using, but that's for its
//. container to compensate for. At this level, all the chunk needs to do is
//. store and request how big it *thinks* it should be, and ignore how large it
//. winds up being at draw-time.
class TextChunk : public virtual GraphicImpl
{
public:
  TextChunk(const Fresco::Unichar ch, const Fresco::Graphic::Requisition &);
  virtual ~TextChunk();

  virtual void draw(Fresco::DrawTraversal_ptr);
  virtual void request(Fresco::Graphic::Requisition &);
  
  virtual const char *object_name();
  void get_text(Babylon::String &); 
  unsigned long get_length();
protected:
  Fresco::Coord     _width, _height;
  Fresco::Alignment _xalign, _yalign;
  Fresco::Unichar   _char;
  const char       *_obj_name;
};

#endif
