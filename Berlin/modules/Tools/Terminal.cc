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
#include "Terminal.hh"

using namespace Prague;
using namespace Fresco;
using namespace Babylon;

using namespace Berlin::ToolKit;

void Terminal::key_press(const Input::Event &event)
{
    Trace trace("Terminal::key_press");
    StreamBuffer::Data data;
    data.length(1);
    const Input::Toggle &toggle = event[0].attr.selection();
    Char uc(UCS4(toggle.number));
    char ascii = uc.value();
    if (isprint(ascii) || ascii == '\r' || ascii == '\n') data[0] = ascii;
    else switch(toggle.number)
    {
    case Babylon::UC_HORIZONTAL_TABULATION: data[0] = '\t'; break;
    case Babylon::UC_BACKSPACE:             data[0] = '\b'; break;
    default: return; // don't know how to handle...
    }
    my_buffer->write(data);
//   my_buffer->flush();
}
