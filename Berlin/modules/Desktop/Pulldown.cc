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
#include <Prague/Sys/Tracer.hh>
#include "Desktop/Pulldown.hh"

using namespace Prague;
using namespace Warsaw;

void Pulldown::loseFocus(Input::Device)
{
  Trace trace("Pulldown::loseFocus");
  mapped(false);
}

void Pulldown::mapped(CORBA::Boolean flag)
{
  Trace trace("Pulldown::mapped");
  /*
   * make sure we get focus before we are mapped
   */
//   if (!flag || requestFocus(Controller_var(_this()), 1))
    WindowImpl::mapped(flag);
}
