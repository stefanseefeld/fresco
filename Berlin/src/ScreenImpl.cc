/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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

#include "Berlin/ScreenImpl.hh"
#include "Berlin/ScreenManager.hh"
#include "Berlin/EventManager.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Console.hh"
#include <Prague/Sys/Tracer.hh>
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/Traversal.hh>
#include <iostream>

using namespace Prague;
using namespace Warsaw;

ScreenImpl::ScreenImpl(DrawingKit_ptr d)
  : ControllerImpl(false), drawing(DrawingKit::_duplicate(d))
{
  Trace trace("ScreenImpl::ScreenImpl");
  emanager = new EventManager(this);
  smanager = new ScreenManager(this, emanager, drawing);
  region = new RegionImpl;
  region->valid = true;
  region->lower.x = region->lower.y = region->lower.z = 0;
  region->upper.x = Console::drawable()->width()/Console::drawable()->resolution(xaxis);
  region->upper.y = Console::drawable()->height()/Console::drawable()->resolution(yaxis);
  region->upper.z = 0;
}

ScreenImpl::~ScreenImpl()
{
  delete smanager;
  delete emanager;
}

void ScreenImpl::pick(PickTraversal_ptr traversal)
{
  Trace trace("ScreenImpl::pick");
  if (traversal->intersects_allocation())
    {
      traversal->enter_controller(Controller_var(_this()));
      MonoGraphic::traverse(traversal);
      if (!traversal->picked()) traversal->hit();
      traversal->leave_controller();
    }
  else cout << "no intersection !" << endl;
}

void ScreenImpl::allocations(Allocation_ptr allocation)
{
  allocation->add(Region_var(region->_this()), Screen_var(_this()));
}

void ScreenImpl::damage(Region_ptr region) { smanager->damage(region);}

bool ScreenImpl::request_focus(Controller_ptr c, Input::Device d)
{
  return emanager->request_focus(c, d);
}

DrawingKit_ptr ScreenImpl::kit() { return DrawingKit::_duplicate(drawing);}

ScreenManager *ScreenImpl::manager() { return smanager;}
Region_ptr ScreenImpl::get_region() {return region->_this();}

Coord ScreenImpl::width() { return region->upper.x;}
Coord ScreenImpl::height() { return region->upper.y;}
