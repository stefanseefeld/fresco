/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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
#include <Berlin/DebugGraphic.hh>
#include <Berlin/Math.hh>
#include <Warsaw/Traversal.hh>
#include <iostream>
#include <iomanip>

DebugGraphic::DebugGraphic(Graphic_ptr g, const char *msg, unsigned int f)
{
  body(g);
  message = msg;
  flags = f;
}

DebugGraphic::~DebugGraphic() {}

void DebugGraphic::request(Requisition &r)
{
  MonoGraphic::request(r);
  if (flags & requests)
    {
      heading(" request\t");
      printRequirement(r.x);
      cout << ", ";
      printRequirement(r.y);
      cout << ", ";
      printRequirement(r.z);
      cout << endl;
    }
}

void DebugGraphic::traverse(Traversal_ptr t)
{
  if (flags & traversals)
    t->visit(this);
  else MonoGraphic::traverse(t);
}

void DebugGraphic::draw(DrawTraversal_ptr t)
{
  if (flags & draws)
    {
      heading(" draw\t");
      RegionImpl region(Region_var(t->allocation()), t->transformation());
      printRegion(&region);
      cout << endl;
    }
  MonoGraphic::traverse(t);
};

void DebugGraphic::pick(PickTraversal_ptr t)
{
  if (flags & picks)
    {
      heading(" pick\t");
      RegionImpl region(Region_var(t->allocation()), t->transformation());
      printRegion(&region);
      cout << endl;
    }
  MonoGraphic::traverse(t);
}

void DebugGraphic::heading(const char *s)
{
  Graphic_var g = body();
  cout << message << " (" << Graphic_ptr(g) << ')' << s;
}

void DebugGraphic::printRequirement(Graphic::Requirement &r)
{
  if (!r.defined)
    {
      cout << "undef";
    }
  else
    {
      double tol = 1e-2;
      if (Math::equal(r.natural, r.minimum, tol))
	{
	  if (Math::equal(r.natural, r.maximum, tol))
	    cout << setprecision(2) << r.natural;
	  else
	    cout << '(' << setprecision(2) << r.natural
		 << ',' << setprecision(2) << r.maximum << ')';
	}
      else if (Math::equal(r.natural, r.maximum, tol))
	cout << '(' << setprecision(2) << r.minimum
	     << ',' << setprecision(2) << r.natural << ')';
      else
	cout << '(' << setprecision(2) << r.minimum
	     << ',' << setprecision(2) << r.natural
	     << ',' << setprecision(2) << r.maximum << ')';
      if (!Math::equal(r.align, 0., tol))
	cout << " @ " << setprecision(1) << r.align;
    }
}

void DebugGraphic::printRegion(Region_ptr r)
{
  Region::Allotment a;
  cout << "X(";
  r->span(xaxis, a);
  printAllotment(a);
  cout << "), Y(";
  r->span(yaxis, a);
  printAllotment(a);
  cout << "), Z(";
  r->span(zaxis, a);
  printAllotment(a);
  cout << ')' << endl;
}

void DebugGraphic::printAllotment(const Region::Allotment &a)
{
  cout << setprecision(2) << a.begin << ',' << setprecision(2) << a.end;
  if (!Math::equal(a.align, 0., 1e-2)) cout << " @ " << setprecision(1) << a.align;
}
