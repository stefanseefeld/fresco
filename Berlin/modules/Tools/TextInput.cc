/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Warsaw/config.hh"
#include "Warsaw/Input.hh"
#include "Tool/TextInput.hh"
#include <Prague/Unicode/Unicode.hh>
#include <Warsaw/Unicode.hh>
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

void TextInput::keyPress(const Input::Event &event)
{
  Trace trace("TextInput::keyPress");
  const Input::Toggle &toggle = event[0].attr.kselection();
  Unicode::Char uc(static_cast<Unicode::_Char>(toggle.number));
  if (uc.is_printable()) buffer->insertChar(Unicode::toCORBA(uc));
  else switch (toggle.number)
    {
    case Unicode::UC_BACKSPACE:     buffer->removeBackward(1); break; // backspace
    case Unicode::KEY_CURSOR_LEFT:  buffer->backward(); break;        // left
    case Unicode::KEY_CURSOR_RIGHT: buffer->forward(); break;         // right
    default:                        ControllerImpl::keyPress(event); break;
    };
}
