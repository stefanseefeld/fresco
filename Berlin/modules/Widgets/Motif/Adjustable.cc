/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#include <Fresco/Region.hh>
#include <Berlin/CommandImpl.hh>
#include "Adjustable.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::WidgetKit::Motif;

class Adjustable::Adjust : public CommandImpl
{
  public:
    Adjust(Adjustable *a) : my_adjustable(a) { my_adjustable->_add_ref(); }
    ~Adjust() { my_adjustable->_remove_ref(); }
    virtual void execute(const CORBA::Any &any)
    {
	OriginatedDelta *od;
	if (any >>= od)
	    my_adjustable->adjust(*od);
	else
	    std::cerr << "Adjustable::Adjust::execute: "
		      << "wrong message type !" << std::endl;
    }
  private:
    Adjustable *my_adjustable;
};

Adjustable::Adjustable() :
    ControllerImpl(false), my_translate(new Observer(this))
{ }

Command_ptr Adjustable::create_adjust_cmd()
{
    Adjust *a = new Adjust(this);
    activate(a);
    return a->_this();
}

Fresco::Observer_ptr Adjustable::observer()
{ return my_translate->_this(); }
