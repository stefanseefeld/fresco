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
#ifndef _TriggerImpl_hh
#define _TriggerImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/Trigger.hh>
#include <Fresco/Command.hh>
#include <Berlin/ControllerImpl.hh>
#include <Berlin/RefCountVar.hh>

class TriggerImpl : public virtual POA_Fresco::Trigger,
		    public ControllerImpl
{
 public:
  TriggerImpl();
  ~TriggerImpl();
  void action(Fresco::Command_ptr);
  Fresco::Command_ptr action();
  void payload(const CORBA::Any &);
  CORBA::Any *payload();
  virtual void release(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
  virtual void key_press(const Fresco::Input::Event &);
  void execute();
 private:
  CORBA::Any_var      _data;
  Prague::Mutex       _mutex;
  Fresco::Command_var _command;
};

#endif
