/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
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

#include "Berlin/ScreenImpl.hh"
#include "Berlin/ScreenManager.hh"
#include "Berlin/EventManager.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Console.hh"
#include <Prague/Sys/Tracer.hh>
#include <Fresco/Traversal.hh>
#include <iostream>

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

ScreenImpl::ScreenImpl() :
    ControllerImpl(false),
    my_this(POA_Fresco::Screen::_this()),
    my_emanager(0),
    my_smanager(0),
    my_region(new RegionImpl())
{
    Trace trace(this, "ScreenImpl::ScreenImpl");
    Console *console = Console::instance();
    Console::Drawable *drawable = console->drawable();
    my_region->valid = true;
    my_region->lower.x = my_region->lower.y = my_region->lower.z = 0;
    my_region->upper.x = drawable->width() / drawable->resolution(xaxis);
    my_region->upper.y = drawable->height() / drawable->resolution(yaxis);
    my_region->upper.z = 0;
}
ScreenImpl::~ScreenImpl() { }
void ScreenImpl::bind_managers(EventManager *e, ScreenManager *s)
{
  my_emanager = e;
  my_smanager = s;
}

void ScreenImpl::pick(PickTraversal_ptr traversal)
{
    Trace trace(this, "ScreenImpl::pick");
    if (traversal->intersects_allocation())
    {
    traversal->enter_controller(my_this);
    MonoGraphic::traverse(traversal);
    if (!traversal->picked()) traversal->hit();
    traversal->leave_controller();
    }
    else std::cout << "no intersection !" << std::endl;
}

void ScreenImpl::allocations(Allocation_ptr allocation)
{
    allocation->add(Region_var(my_region->_this()), my_this);
}

void ScreenImpl::damage(Region_ptr region) { my_smanager->damage(region); }
CORBA::Boolean ScreenImpl::request_focus(Controller_ptr c, Input::Device d)
{ return my_emanager->request_focus(c, d); }
Region_ptr ScreenImpl::allocation() { return my_region->_this(); }
Coord ScreenImpl::width() { return my_region->upper.x;}
Coord ScreenImpl::height() { return my_region->upper.y;}
