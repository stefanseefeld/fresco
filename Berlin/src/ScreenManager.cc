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

#include "Berlin/ScreenManager.hh"
#include "Berlin/DrawTraversalImpl.hh"
#include "Berlin/PickTraversalImpl.hh"

ScreenManager::ScreenManager(ScreenImpl *s)
  : screen(s)
{
}

ScreenManager::~ScreenManager()
{
}

void ScreenManager::damage(Region_ptr r)
{
  RegionImpl *region = new RegionImpl;
//   region->_obj_is_ready(_boa());
  region->copy(r);
  damages.push_back(region);
  cout << "ScreenManager::damage region "
       << '(' << region->lower.x << ',' << region->lower.y << "),("
       << region->upper.x << ',' << region->upper.y << ')' << endl;
}

void ScreenManager::repair()
{
  for (DamageList::iterator i = damages.begin(); i != damages.end(); i++)
    {
      DrawTraversalImpl *traversal;//(*i);
      screen->traverse(traversal);
      delete *i;
    }
  damages.erase(damages.begin(), damages.end());
}

void ScreenManager::run()
{
  
}
