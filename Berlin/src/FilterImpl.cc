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

#include "Berlin/FilterImpl.hh"

using namespace Fresco;

Berlin::Accelerator::Accelerator(Input::Device d, const Input::Toggle &t,
                 Input::Bitset b, Command_ptr c) :
    my_device(d),
    my_toggle(t),
    my_modifier(b),
    my_command(Command::_duplicate(c))
{ }

CORBA::Boolean Berlin::Accelerator::handle(const Input::Event &event)
{
    // the device has to be the first one in the event list
    bool found = true;
//    for (size_t i = 0; i !=
    CORBA::Any dummy;
    if (found) my_command->execute(dummy);
    return found;
}
