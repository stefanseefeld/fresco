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

#include "Desktop/Manipulator.hh"
#include <Berlin/Vertex.hh>
#include <Prague/Sys/Tracer.hh>
#include <Warsaw/IO.hh>

using namespace Prague;
using namespace Warsaw;

void Mover::execute(const CORBA::Any &any)
{
  Vertex *delta;
  if (any >>= delta)
    {
      Vertex p = window->position();
      window->position(p + *delta);
    }
  else  cerr << "Mover::execute : wrong message type !" << endl;
}

void Resizer::execute(const CORBA::Any &any)
{
  Vertex *delta;
  if (any >>= delta)
    {
      Vertex s = window->size();
      Graphic::Requisition r;
      window->request(r);
      if (r.x.defined)
	{
	  if (delta->x > 0.) s.x = min(s.x + delta->x, r.x.maximum);
	  else s.x = max(s.x + delta->x, r.x.minimum);
	}
      else s.x += delta->x;
      if (r.y.defined)
	{
	  if (delta->y > 0.) s.y = min(s.y + delta->y, r.y.maximum);
	  else s.y = max(s.y + delta->y, r.y.minimum);
	}
      else s.y += delta->y;
      window->size(s);
    }
  else cerr << "Resizer::execute : wrong message type !" << endl;
}

MoveResizer::MoveResizer(Window_ptr window, Desktop_ptr d, Alignment x, Alignment y, CORBA::Short b)
  : Manipulator(window), desktop(Desktop::_duplicate(d)), xalign(x), yalign(y), border(b) {}

void MoveResizer::execute(const CORBA::Any &any)
{
  Trace trace("MoveResizer::execute");
  Vertex *vertex;
  if (any >>= vertex)
    {
      Warsaw::Graphic::Requisition r;
      window->request(r);
      Vertex pos = window->position();
      Vertex size = window->size();
      Vertex p = pos, s = size;
      if (border & Warsaw::Window::left && xalign != 0.)
	{
	  s.x = min(r.x.maximum, max(r.x.minimum, size.x - vertex->x/xalign));
	  p.x = pos.x - xalign * (s.x - size.x);
	}
      else if (border & Warsaw::Window::right && xalign != 1.)
	{
	  s.x = min(r.x.maximum, max(r.x.minimum, size.x + vertex->x/(1.-xalign)));
	  p.x = pos.x - xalign * (s.x - size.x);
	}
      if (border & Warsaw::Window::top && yalign != 0.)
	{
	  s.y = min(r.y.maximum, max(r.y.minimum, size.y - vertex->y/yalign));
	  p.y = pos.y - yalign * (s.y - size.y);
	}
      else if (border & Warsaw::Window::bottom && yalign != 1.)
	{
	  s.y = min(r.y.maximum, max(r.y.minimum, size.y + vertex->y/(1.-yalign)));
	  p.y = pos.y - yalign * (s.y - size.y);
	}
      desktop->begin();
      window->position(p);
      window->size(s);
      desktop->end();
    }
  else cerr << "MoveResizer::execute : wrong message type !" << endl;
}

void Relayerer::execute(const CORBA::Any &any)
{
  Warsaw::Stage::Index i;
  if (any >>= i) window->layer(i);
  else cerr << "Relayerer::execute : wrong message type !" << endl;
}

void Mapper::execute(const CORBA::Any &) { window->mapped(true);}
void Unmapper::execute(const CORBA::Any &) { window->mapped(false);}

