/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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
#include <Fresco/PickTraversal.hh>
#include "TriggerImpl.hh"

using namespace Prague;
using namespace Fresco;

TriggerImpl::TriggerImpl() : ControllerImpl(false), _data(new CORBA::Any) {
}
TriggerImpl::~TriggerImpl()
{
  Trace trace("Trigger::~Trigger");
  if (!CORBA::is_nil(_command))
    try { _command->destroy();}
    catch (const CORBA::OBJECT_NOT_EXIST &) {}
    catch (const CORBA::COMM_FAILURE &) {}
    catch (const CORBA::TRANSIENT &) {}
}
void TriggerImpl::action(Command_ptr c)
{
  Trace trace("TriggerImpl::action");
  Prague::Guard<Mutex> guard(_mutex);
  if (!CORBA::is_nil(_command))
    try { _command->destroy();}
    catch (const CORBA::OBJECT_NOT_EXIST &) {}
    catch (const CORBA::COMM_FAILURE &) {}
    catch (const CORBA::TRANSIENT &) {}
  _command = Command::_duplicate(c);
}

Command_ptr TriggerImpl::action()
{
  Prague::Guard<Mutex> guard(_mutex);
  return Command::_duplicate(_command);
}

void TriggerImpl::payload(const CORBA::Any &a)
{
  Trace trace("TriggerImpl::payload");
  _data = new CORBA::Any(a);
}

CORBA::Any *TriggerImpl::payload()
{
  CORBA::Any_var any(_data);
  return any._retn();
}

void TriggerImpl::release(PickTraversal_ptr traversal, const Input::Event &event)
{
  /*
   * once we have real focus management the command should be executed
   * if we have focus and the Telltale::toggle is to be released... -stefan
   */
  if (inside(traversal) && test(Fresco::Controller::pressed))
    {
      try { execute();}
      catch (...) {}
    }
  ControllerImpl::release(traversal, event);
}

void TriggerImpl::key_press(const Input::Event &event)
{
  const Input::Toggle &toggle = event[0].attr.selection();
  if (toggle.number == 32) // space
    {
      set(Fresco::Controller::pressed);
      if (test(Fresco::Controller::pressed))
	{
	  execute();
	  clear(Fresco::Controller::pressed);
	}
    }
  else ControllerImpl::key_press(event);
}

void TriggerImpl::execute()
{
  Trace trace("TriggerImpl::execute");
  Prague::Guard<Mutex> guard(_mutex);
  if (!CORBA::is_nil(_command))
    try { _command->execute(_data);}
    catch (const CORBA::OBJECT_NOT_EXIST &) { _command = Fresco::Command::_nil();}
    catch (const CORBA::COMM_FAILURE &) { _command = Fresco::Command::_nil();}
    catch (const CORBA::TRANSIENT &) { _command = Fresco::Command::_nil();}
}
