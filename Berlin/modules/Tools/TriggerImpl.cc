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

#include <Prague/Sys/Tracer.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Input.hh>
#include <Warsaw/PickTraversal.hh>
#include "Tool/TriggerImpl.hh"

using namespace Prague;
using namespace Warsaw;

TriggerImpl::TriggerImpl() : ControllerImpl(false) {}
TriggerImpl::~TriggerImpl()
{
  Trace trace("Trigger::~Trigger");
  if (!CORBA::is_nil(command))
    try { command->destroy();}
    catch (const CORBA::OBJECT_NOT_EXIST &) {}
}
void TriggerImpl::action(Command_ptr c)
{
  Trace trace("TriggerImpl::action");
  MutexGuard guard(mutex);
  if (!CORBA::is_nil(command))
    try { command->destroy();}
    catch (const CORBA::OBJECT_NOT_EXIST &) {}
  command = Command::_duplicate(c);
}

Command_ptr TriggerImpl::action()
{
  MutexGuard guard(mutex);
  return Command::_duplicate(command);
}

void TriggerImpl::release(PickTraversal_ptr traversal, const Input::Event &event)
{
  /*
   * once we have real focus management the command should be executed
   * if we have focus and the Telltale::toggle is to be released... -stefan
   */
  if (inside(traversal) && test(Warsaw::Controller::pressed))
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
      set(Warsaw::Controller::pressed);
      if (test(Warsaw::Controller::pressed))
	{
	  CORBA::Any dummy;
	  execute(dummy);
	  clear(Warsaw::Controller::pressed);
	}
    }
  else ControllerImpl::key_press(event);
}

void TriggerImpl::execute(const CORBA::Any &any)
{
  Trace trace("TriggerImpl::execute");
  MutexGuard guard(mutex);
  if (!CORBA::is_nil(command)) command->execute(any);
}
