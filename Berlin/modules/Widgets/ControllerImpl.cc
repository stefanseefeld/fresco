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

#include "Widget/ControllerImpl.hh"
#include "Warsaw/PickTraversal.hh"
#include "Warsaw/Event.hh"
#include "Berlin/Logger.hh"

ControllerImpl::ControllerImpl() : TelltaleImpl(TelltaleConstraint::_nil()) {}
void ControllerImpl::pick(PickTraversal_ptr traversal)
{
  SectionLog section(Logger::picking, "ControllerImpl::pick");
  /*
   * for now take the even if falls inside our allocation
   */
  if (traversal->intersectsAllocation())
    traversal->hit(Controller_var(_this()));
}
void ControllerImpl::handle(PickTraversal_ptr traversal, const CORBA::Any &any)
{
  SectionLog section(Logger::picking, "ControllerImpl::handle");
  Event::Pointer *pointer;
  if (any >>= pointer) handlePositionalEvent(traversal, pointer);
  /* else key event ? */
}

void ControllerImpl::handlePositionalEvent(PickTraversal_ptr traversal, const Event::Pointer *pointer)
{
  /*
   * for now, only react if pointer is in the controller
   */
  if (traversal->intersectsAllocation())
    switch (pointer->whatHappened)
      {
      case Event::press: press(traversal, pointer); break;
      case Event::release: release(traversal, pointer); break;
      case Event::hold:
	if (test(Telltale::toggle)) drag(traversal, pointer);
	else move(traversal, pointer);
	break;
      default: other(traversal, pointer); break;
      }
}

void ControllerImpl::move(PickTraversal_ptr, const Event::Pointer *)
{
  set(Telltale::active);
}

void ControllerImpl::press(PickTraversal_ptr, const Event::Pointer *)
{
  set(Telltale::toggle);
}

void ControllerImpl::drag(PickTraversal_ptr, const Event::Pointer *)
{
}

void ControllerImpl::release(PickTraversal_ptr, const Event::Pointer *)
{
  clear(Telltale::toggle);
}

void ControllerImpl::doubleClick(PickTraversal_ptr, const Event::Pointer *)
{
}

void ControllerImpl::keyPress(PickTraversal_ptr, const Event::Pointer *)
{
}

void ControllerImpl::keyRelease(PickTraversal_ptr, const Event::Pointer *)
{
}

void ControllerImpl::other(PickTraversal_ptr, const Event::Pointer *)
{
}
