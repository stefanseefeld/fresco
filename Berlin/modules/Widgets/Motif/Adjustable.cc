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
#include <Berlin/CommandImpl.hh>
#include "Widget/Motif/Adjustable.hh"

using namespace Prague;
using namespace Warsaw;
using namespace Motif;

class Adjustable::Adjust : public CommandImpl
{
public:
  Adjust(Adjustable *a) : _adjustable(a) { _adjustable->_add_ref();}
  ~Adjust() { _adjustable->_remove_ref();}
  virtual void execute(const CORBA::Any &any)
  {
    Vertex *delta;
    if (any >>= delta) _adjustable->adjust(*delta);
    else  std::cerr << "Adjustable::Adjust::execute : wrong message type !" << std::endl;
  }
private:
  Adjustable *_adjustable;
};

Adjustable::Adjustable() : ControllerImpl(false), _translate(new Observer(this)) {}

Command_ptr Adjustable::create_adjust_cmd()
{
  Adjust *a = new Adjust(this);
  activate(a);
  return a->_this();
}

Warsaw::Observer_ptr Adjustable::observer()
{
  return _translate->_this();
}

