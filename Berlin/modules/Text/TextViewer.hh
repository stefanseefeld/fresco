/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _TextViewer_hh
#define _TextViewer_hh

#include "Warsaw/config.hh"
#include "Warsaw/View.hh"
#include "Warsaw/TextKit.hh"
#include "Berlin/GapBuffer.hh"
#include "Berlin/MonoGraphic.hh"
#include "Layout/Box.hh"
#include <map>

class TextChunk;
class FontChange;
class Compositor;

declare_corba_ptr_type(DrawingKit)
declare_corba_ptr_type(TextBuffer)
declare_corba_ptr_type(DrawTraversal)

class TextViewer : implements(View), public HBox//MonoGraphic
{
 public:
  TextViewer(TextBuffer_ptr txt, TextKit_ptr tk, DrawingKit_ptr dk, Compositor *);
  virtual ~TextViewer();
  void update(const CORBA::Any &);
 protected:
  TextBuffer_var buffer;
  TextKit_var kit;
  DrawingKit_var canonicalDK;
  Compositor  *compositor;
};

#endif
