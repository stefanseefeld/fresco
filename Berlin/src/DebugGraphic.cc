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
#include "Berlin/DebugGraphic.hh"
#include "Berlin/Math.hh"
#include "Warsaw/Traversal.hh"
#include "Warsaw/DrawTraversal.hh"
#include "Warsaw/PickTraversal.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/ImplVar.hh"
#include <Warsaw/IO.hh>
#include <Prague/Sys/Tracer.hh>
#include <iostream>
#include <iomanip>

using namespace Prague;

DebugGraphic::DebugGraphic(const string &msg, unsigned int f) : message(msg), flags(f) {}
DebugGraphic::~DebugGraphic() {}

void DebugGraphic::request(Requisition &r)
{
  Trace trace("DebugGraphic::request");
  MonoGraphic::request(r);
  if (flags & requests)
    {
      heading(" request\t");
      cout << r << '\n';
    }
}

void DebugGraphic::traverse(Traversal_ptr traversal)
{
  Trace trace("DebugGraphic::traverse");
  if (flags & traversals) traversal->visit(Graphic_var(_this()));
  else MonoGraphic::traverse(traversal);
}

void DebugGraphic::draw(DrawTraversal_ptr traversal)
{
  Trace trace("DebugGraphic::draw");
  if (flags & draws)
    {
      heading(" draw\t");
      Region_var r = traversal->allocation();
      Transform_var t = traversal->transformation();
      Impl_var<RegionImpl> region(new RegionImpl(r, t));
      cout << Region_var(region->_this()) << endl;
    }
  MonoGraphic::traverse(traversal);
};

void DebugGraphic::pick(PickTraversal_ptr traversal)
{
  Trace trace("DebugGraphic::pick");
  if (flags & picks)
    {
      heading(" pick\t");
      Region_var r = traversal->allocation();
      Transform_var t = traversal->transformation();
      Impl_var<RegionImpl> region(new RegionImpl(r, t));
      cout << Region_var(region->_this()) << endl;
    }
  MonoGraphic::traverse(traversal);
}

void DebugGraphic::heading(const char *s)
{
  Graphic_var g = body();
  cout << message << " (" << g << ')' << s;
}
