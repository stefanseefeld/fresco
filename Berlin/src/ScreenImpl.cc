/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#include "Berlin/Logger.hh"
#include "Drawing/openGL/GLDrawingKit.hh"

#include "Warsaw/Traversal.hh"
#include <iostream>

ScreenImpl::ScreenImpl(GLDrawingKit *d, Coord w, Coord h)
  : drawing(d)
{
  emanager = new EventManager(this);
  smanager = new ScreenManager(this, emanager, drawing);
  region = new RegionImpl;
  region->valid = true;
  region->lower.x = region->lower.y = region->lower.z = 0;
  region->upper.x = w, region->upper.y = h, region->upper.z = 0;
  region->_obj_is_ready(CORBA::BOA::getBOA());
}

ScreenImpl::~ScreenImpl()
{
  region->_dispose();
  delete smanager;
  delete emanager;
}

void ScreenImpl::traverse(Traversal_ptr traversal) { MonoGraphic::traverse(traversal);}

void ScreenImpl::allocate(Graphic_ptr g, Allocation_ptr allocation)
{
  if (!g->_is_equivalent(Graphic_var(body()))) return;
  allocation->add(Region_var(region->_this()), Screen_var(_this()));
}

void ScreenImpl::damage(Region_ptr region) { smanager->damage(region);}

CORBA::Boolean ScreenImpl::handle(PickTraversal_ptr traversal, const CORBA::Any &any)
{
  SectionLog section(Logger::picking, "ScreenImpl::handle");
  Graphic_var child = body();
  if (!CORBA::is_nil(child))
    {
      child->traverse(traversal);
      PickTraversal_var picked = traversal->picked();
      if (!CORBA::is_nil(picked))
	return Controller_var(picked->receiver())->handle(picked, any);
    }
  return false;
}

DrawingKit_ptr ScreenImpl::kit() { return drawing->_this();}

ScreenManager *ScreenImpl::manager() { return smanager;}
Region_ptr ScreenImpl::getRegion() {return region->_this();}

Coord ScreenImpl::width() { return region->upper.x;}
Coord ScreenImpl::height() { return region->upper.y;}
