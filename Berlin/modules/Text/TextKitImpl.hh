#ifndef _TextKitImpl_hh
#define _TextKitImpl_hh
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

#include "Warsaw/config.hh"
#include "Warsaw/TextKit.hh"
#include "Warsaw/Text.hh"
#include "Berlin/CloneableImpl.hh"

/** the idea with a textKit is that it's responsible for "bundling up"
    chunks of unicode and their associated style and font
    settings. If a chunk has no such settings, a simplified chunk
    is built which uses the drawingKit's "default" font. */

class TextKitImpl : implements(TextKit), public virtual CloneableImpl {
 public:
  TextKitImpl();
  virtual ~TextKitImpl();
  Text::FontSeq *enumerateFonts();
  Graphic_ptr textChunk(const Unistring &u);
  Graphic_ptr fontChange(const Text::FontDescriptor &f, const Style::Spec &sty);
};


#endif
