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
#include <Berlin/Vertex.hh>
#include <Fresco/IO.hh>
#include <Berlin/Logger.hh>
#include "Manipulator.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::DesktopKit;

void Mover::execute(const CORBA::Any &any)
{
  OriginatedDelta *od;
  if (any >>= od)
    {
      Vertex p = window->position();
      window->position(p + od->delta);
    }
  else  std::cerr << "Mover::execute : wrong message type !" << std::endl;
}

void Resizer::execute(const CORBA::Any &any)
{
  OriginatedDelta *od;
  if (any >>= od)
    {
      Vertex s = window->size();
      Graphic::Requisition r;
      // We need to initialise manually:-(
      r.x.defined = false;
      r.y.defined = false;
      r.z.defined = false;
      r.preserve_aspect = false;

      window->request(r);
      if (r.x.defined)
	{
	  if (od->delta.x > 0.) s.x = std::min(s.x + od->delta.x, r.x.maximum);
	  else s.x = std::max(s.x + od->delta.x, r.x.minimum);
	}
      else s.x += od->delta.x;
      if (r.y.defined)
	{
	  if (od->delta.y > 0.) s.y = std::min(s.y + od->delta.y, r.y.maximum);
	  else s.y = std::max(s.y + od->delta.y, r.y.minimum);
	}
      else s.y += od->delta.y;
      window->size(s);
    }
  else std::cerr << "Resizer::execute : wrong message type !" << std::endl;
}

MoveResizer::MoveResizer(Window_ptr window, Desktop_ptr d, Alignment x, Alignment y, CORBA::Short b)
  : Manipulator(window), desktop(Desktop::_duplicate(d)), xalign(x), yalign(y), border(b) {}

void MoveResizer::execute(const CORBA::Any &any)
{

  // We need to check now whether the origin + delta are > the left
  // side when resizing the right side.
  // Vice versa for the other side. And then top + bottom.
  Trace trace("MoveResizer::execute");
  OriginatedDelta *od;
  if (any >>= od)
    {
      Fresco::Graphic::Requisition r;
      // We need to initialise manually:-(
      r.x.defined = false;
      r.y.defined = false;
      r.z.defined = false;
      r.preserve_aspect = false;

      window->request(r);
      Vertex pos = window->position();
      Vertex size = window->size();
      Vertex p = pos, s = size;
      Logger::log(Logger::desktop) << "od: " << (od->delta.x +
						 od->origin.x) <<
	", p: " << (p.x + r.x.minimum) << std::endl;
      if (border & Fresco::Window::left && xalign != 0.)
	{
	  if ((od->delta.x > 0 &&
	       od->delta.x + od->origin.x >= p.x)
	      ||
	      (od->delta.x < 0 &&
	       od->delta.x + od->origin.x <= p.x)
	      ) {
	    s.x = std::min(r.x.maximum, std::max(r.x.minimum, size.x - od->delta.x/xalign));
	    p.x = pos.x - xalign * (s.x - size.x);
	  }
	}
      else if (border & Fresco::Window::right && xalign != 1.)
	{
	  if ((od->delta.x > 0 &&
	       od->delta.x + od->origin.x >= p.x + size.x)
	      ||
	      (od->delta.x < 0 &&
	       od->delta.x + od->origin.x <= p.x + size.x)
	      ) {
	    s.x = std::min(r.x.maximum, std::max(r.x.minimum, size.x + od->delta.x/(1.-xalign)));
	    p.x = pos.x - xalign * (s.x - size.x);
	  }
	}
      if (border & Fresco::Window::top && yalign != 0.)
	{
	  if ((od->delta.y > 0 &&
	       od->delta.y + od->origin.y >= p.y)
	      ||
	      (od->delta.y < 0 &&
	       od->delta.y + od->origin.y <= p.y)
	      ) {
	    s.y = std::min(r.y.maximum, std::max(r.y.minimum, size.y - od->delta.y/yalign));
	    p.y = pos.y - yalign * (s.y - size.y);
	  }
	}
      else if (border & Fresco::Window::bottom && yalign != 1.)
	{
	  if ((od->delta.y > 0 &&
	       od->delta.y + od->origin.y >= p.y + size.y)
	      ||
	      (od->delta.y < 0 &&
	       od->delta.y + od->origin.y <= p.y + size.y)
	      ) {
	    s.y = std::min(r.y.maximum, std::max(r.y.minimum, size.y + od->delta.y/(1.-yalign)));
	    p.y = pos.y - yalign * (s.y - size.y);
	  }
	}
      desktop->lock();
      window->position(p);
      window->size(s);
      desktop->unlock();
    }
  else std::cerr << "MoveResizer::execute : wrong message type !" << std::endl;
}

void Relayerer::execute(const CORBA::Any &any)
{
  Layout::Stage::Index i;
  if (any >>= i) window->layer(i);
  else std::cerr << "Relayerer::execute : wrong message type !" << std::endl;
}

void Mapper::execute(const CORBA::Any &) { window->mapped(true);}
void Unmapper::execute(const CORBA::Any &) { window->mapped(false);}
