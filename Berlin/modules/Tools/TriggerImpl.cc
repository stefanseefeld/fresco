/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include "Warsaw/PickTraversal.hh"
#include "Tool/TriggerImpl.hh"

void TriggerImpl::release(PickTraversal_ptr traversal, const Input::Event &event)
{
  /*
   * once we have real focus management the command should be executed
   * if we have focus and the Telltale::toggle is to be released... -stefan
   */
  if (inside(traversal) && test(Controller::pressed))
    {
      CORBA::Any dummy;
      execute(dummy);
    }
  ControllerImpl::release(traversal, event);
}

void TriggerImpl::keyPress(const Input::Event &event)
{
  const Input::Toggle &toggle = event[0].attr.selection();
  if (toggle.number == 32) // space
    {
      set(Controller::pressed);
      if (test(Controller::pressed))
	{
	  CORBA::Any dummy;
	  execute(dummy);
	  clear(Controller::pressed);
	}
    }
  else ControllerImpl::keyPress(event);
}
