/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _TriggerImpl_hh
#define _TriggerImpl_hh

#include "Warsaw/config.hh"
#include "Warsaw/Trigger.hh"
#include "Warsaw/Command.hh"
#include "Berlin/ControllerImpl.hh"

class TriggerImpl : implements(Trigger), public ControllerImpl
{
 public:
  TriggerImpl() : ControllerImpl(false) {}
  ~TriggerImpl() {}
  void action(Command_ptr c) { command = Command::_duplicate(c);}
  Command_ptr action() { return Command::_duplicate(command);}
// protected:
  virtual void release(PickTraversal_ptr, const Input::Event &);
  virtual void keyPress(const Input::Event &);
  void execute(const CORBA::Any &any) { if (!CORBA::is_nil(command)) command->execute(any);}
 private:
  Command_var command;
};

#endif /* _TriggerImpl_hh */