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

#include "Text/TextKitImpl.hh"
#include "Text/TextChunk.hh"
#include "Text/FontChange.hh"
#include "Berlin/Plugin.hh"

TextKitImpl::TextKitImpl() {}
TextKitImpl::~TextKitImpl() {}

Text::FontSeq *TextKitImpl::enumerateFonts() {
  Text::FontSeq *fsq = new Text::FontSeq();
  return fsq;
}

Graphic_ptr TextKitImpl::textChunk(const Unistring &u) {
  TextChunk *t = new TextChunk(u);
  t->_obj_is_ready(_boa());
  return t->_this();
}

Graphic_ptr TextKitImpl::fontChange(const Text::FontDescriptor &f, const Style::Spec &sty) {
  FontChange *fc = new FontChange(f,sty);
  fc->_obj_is_ready(_boa());
  return fc->_this();
}


EXPORT_PLUGIN(TextKitImpl, interface(TextKit))
