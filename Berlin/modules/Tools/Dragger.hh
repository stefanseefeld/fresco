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
#ifndef _Dragger_hh
#define _Dragger_hh

#include "Warsaw/config.hh"
#include "Warsaw/Command.hh"
#include "Berlin/ControllerImpl.hh"

class Dragger : public ControllerImpl
{
public:
  Dragger(Command_ptr);
  virtual ~Dragger();
//protected:
  virtual void press(PickTraversal_ptr, const Input::Event &);
  virtual void drag(PickTraversal_ptr, const Input::Event &);
  virtual void release(PickTraversal_ptr, const Input::Event &);
private:
  Vertex offset;
  Command_var command;
};

#endif /* _Dragger_hh */