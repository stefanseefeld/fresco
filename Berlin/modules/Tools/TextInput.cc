/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/Input.hh>
#include <Fresco/Unicode.hh>
#include "TextInput.hh"

using namespace Prague;
using namespace Fresco;

void TextInput::key_press(const Input::Event &event)
{
  Trace trace("TextInput::key_press");
  const Input::Toggle &toggle = event[0].attr.selection();
  Babylon::Char uc(static_cast<Babylon::UCS4>(toggle.number));
  switch (toggle.number)
      {
      case Babylon::UC_BACKSPACE:     buffer->remove_backward(1); break; // backspace
      case Babylon::UC_KEY_CURSOR_LEFT:  buffer->backward(); break;        // left
      case Babylon::UC_KEY_CURSOR_RIGHT: buffer->forward(); break;         // right
      default:
	  if (uc.is_Printable() && !uc.is_Private_Use())
	      buffer->insert_char(Unicode::to_CORBA(uc));
	  else
	      ControllerImpl::key_press(event); break;
      };
}
