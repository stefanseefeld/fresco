/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#ifndef _TextInput_hh
#define _TextInput_hh

#include "Warsaw/config.hh"
#include "Warsaw/TextBuffer.hh"
#include "Berlin/ControllerImpl.hh"

class TextInput : public ControllerImpl
{
 public:
  TextInput(TextBuffer_ptr b) : ControllerImpl(false), buffer(TextBuffer::_duplicate(b)) {}
  ~TextInput() {}
// protected:
  virtual void keyPress(const Input::Event &);
 private:
  TextBuffer_var buffer;
};

#endif /* _TextInput_hh */
