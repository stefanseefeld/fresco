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
#ifndef _FilterImpl_hh
#define _FilterImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Input.hh>
#include <Warsaw/Command.hh>

class Accelerator : implementsscoped(Input, Filter)
{
 public:
  Accelerator(Input::Device, const Input::Toggle &, Input::Bitset, Command_ptr);
  virtual ~Accelerator() {}
  virtual CORBA::Boolean handle(const Input::Event &);
 private:
  const Input::Device device;
  const Input::Toggle toggle;
  const Input::Bitset modifier;
  const Command_var command;
};

#endif /* _FocusImpl_hh */
