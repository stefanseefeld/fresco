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
#include <Fresco/Focus.hh>
#include "Pulldown.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::DesktopKit;

CORBA::Boolean Pulldown::receive_focus(Fresco::Focus_ptr focus)
{
    Trace trace("Pulldown::receive_focus");
    // Make sure we're mapped for keyboard focus
    if (focus->device() == 0)
    mapped(true);

    return WindowImpl::receive_focus(focus);
}

void Pulldown::lose_focus(Input::Device device)
{
    Trace trace("Pulldown::lose_focus");
    if (device == 0)
    mapped(false);
    
    WindowImpl::lose_focus(device);
}

void Pulldown::mapped(CORBA::Boolean flag)
{
    Trace trace("Pulldown::mapped");
    // make sure we get focus before we are mapped
//   if (!flag || request_focus(Controller_var(_this()), 1))
    WindowImpl::mapped(flag);
}
