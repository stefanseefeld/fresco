/*$Id$
 *
 * This source file is a part of the Fresco Project.
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
#ifndef _ToolKit_TextInput_hh
#define _ToolKit_TextInput_hh

#include <Fresco/config.hh>
#include <Fresco/TextBuffer.hh>
#include <Berlin/ControllerImpl.hh>

namespace Berlin
{
  namespace ToolKit
  {

    class TextInput : public ControllerImpl
    {
      public:
    TextInput(Fresco::TextBuffer_ptr b) :
        ControllerImpl(false),
        my_buffer(Fresco::TextBuffer::_duplicate(b))
    { }
    ~TextInput() { }
//      protected:
    virtual void key_press(const Fresco::Input::Event &);
      private:
    Fresco::TextBuffer_var my_buffer;
    };
    
  } // namespace
} // namespace

#endif
