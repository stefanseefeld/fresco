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

#include "Desktop/WindowImpl.hh"
#include <Berlin/Vertex.hh>
#include <Prague/Sys/Tracer.hh>
#include <Warsaw/IO.hh>

using namespace Prague;
using namespace Warsaw;

class Mover : public WindowImpl::Manipulator
{
public:
  virtual void execute(const CORBA::Any &any)
    {
      if (CORBA::is_nil(handle)) return;
      Vertex *delta;
      if (any >>= delta)
	{
 	  Vertex p = handle->position();
	  handle->position(p + *delta);
	}
      else  cerr << "Mover::execute : wrong message type !" << endl;
    }
};

class Resizer : public WindowImpl::Manipulator
{
public:
  virtual void execute(const CORBA::Any &any)
    {
      if (CORBA::is_nil(handle)) return;
      Vertex *delta;
      if (any >>= delta)
	{
 	  Vertex s = handle->size();
          Graphic::Requisition r;
          handle->child()->request(r);
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
	  handle->size(s);
	}
      else cerr << "Resizer::execute : wrong message type !" << endl;
    }
};

class MoveResizer : public WindowImpl::Manipulator
{
public:
  MoveResizer(Alignment x, Alignment y, CORBA::Short b) : xalign(x), yalign(y), border(b) {}
  virtual void execute(const CORBA::Any &any)
    {
      Trace trace("MoveResizer::execute");
      if (CORBA::is_nil(handle)) return;
      Vertex *vertex;
      if (any >>= vertex)
	{
          Warsaw::Graphic::Requisition r;
          handle->child()->request(r);
 	  Vertex pos = handle->position();
 	  Vertex size = handle->size();
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
	  Stage_var parent = handle->parent();
	  parent->begin();
	  handle->position(p);
	  handle->size(s);
	  parent->end();
	}
      else cerr << "MoveResizer::execute : wrong message type !" << endl;
    }
private:
  Alignment xalign, yalign;
  CORBA::Short border;
};

class Relayerer : public WindowImpl::Manipulator
{
public:
  virtual void execute(const CORBA::Any &any)
    {
      if (CORBA::is_nil(handle)) return;
      Warsaw::Stage::Index i;
      if (any >>= i)
	{
	  handle->layer(i);
	}
      else cerr << "Relayerer::execute : wrong message type !" << endl;
    }
};

void WindowImpl::Mapper::execute(const CORBA::Any &)
{
  if (flag) window->map();
  else window->unmap();
}

WindowImpl::WindowImpl()
  : ControllerImpl(false), unmapped(0), manipulators(3), mapper(0)
{
  Trace trace("WindowImpl::WindowImpl");
  manipulators[0] = new Mover;
  manipulators[1] = new Resizer;
  manipulators[2] = new Relayerer;
  mapper = new Mapper(this, true);
  unmapper = new Mapper(this, false);
}

WindowImpl::~WindowImpl()
{
  Trace trace("WindowImpl::~WindowImpl");
  MutexGuard guard(mutex);
  /*
   * FIXME !!:
   * is Window the owner of the manipulators or not ?
   * Should commands be ref counted or not ?
   * if a Window is the owner of its commands, we need an additinal
   * callback such that the manipulator can remove itself from the
   * window (if it was destroyed by the POA before the window...
   *   -stefan
   */
//   for (mtable_t::iterator i = manipulators.begin(); i != manipulators.end(); i++)
//     {
//       cout << "deactivate manipulator...";
//       (*i)->deactivate();
//       cout << "...done";
//     }
}

void WindowImpl::needResize()
{
  Trace trace("WindowImpl::needResize");
  Vertex size = handle->size();
  Warsaw::Graphic::Requisition r;
  request(r);
  if (r.x.minimum <= size.x && r.x.maximum >= size.x &&
      r.y.minimum <= size.y && r.y.maximum >= size.y &&
      r.z.minimum <= size.z && r.z.maximum >= size.z)
    needRedraw();
  else
    {
      size.x = min(r.x.maximum, max(r.x.minimum, size.x));
      size.y = min(r.y.maximum, max(r.y.minimum, size.y));
      size.z = min(r.z.maximum, max(r.z.minimum, size.z));
      handle->size(size);
    }
}


/*
 * cache the focus holding controllers so we can restore them when the window
 * receives focus again...
 */
CORBA::Boolean WindowImpl::requestFocus(Controller_ptr c, Warsaw::Input::Device d)
{
  if (unmapped) return false;
  Controller_var parent = parentController();
  if (CORBA::is_nil(parent)) return false;
  if (parent->requestFocus(c, d))
    {
      if (focus.size() <= d) focus.resize(d + 1);
      focus[d] = Warsaw::Controller::_duplicate(c);
      return true;
    }
  else return false;
}

void WindowImpl::insert(Desktop_ptr desktop, bool mapped)
{
  Trace trace("WindowImpl::insert");
  Vertex position, size;
  position.x = position.y = 1000., position.z = 0.;
  Warsaw::Graphic::Requisition r;
  request(r);
  size.x = r.x.natural, size.y = r.y.natural, size.z = 0;
  unmapped = new UnmappedStageHandle(desktop, Graphic_var(_this()), position, size, 0);
  handle = StageHandle_var(unmapped->_this());
  if (mapped) map();
}

Command_ptr WindowImpl::move() { return manipulators[0]->_this();}
Command_ptr WindowImpl::resize() { return manipulators[1]->_this();}
Command_ptr WindowImpl::moveResize(Alignment x, Alignment y, CORBA::Short b)
{
  MutexGuard guard(mutex);
  manipulators.push_back(new MoveResizer(x, y, b));
  activate(manipulators.back());
  return manipulators.back()->_this();
}
Command_ptr WindowImpl::relayer() { return manipulators[2]->_this();}
Command_ptr WindowImpl::map(CORBA::Boolean f)
{
  return f ? mapper->_this() : unmapper->_this();
}

// void WindowImpl::pick(PickTraversal_ptr traversal)
// {
//   SectionLog section("WindowImpl::pick");
//   traversal->enterController(Controller_var(_this()));
//   MonoGraphic::traverse(traversal);
//   traversal->leaveController();
// }

void WindowImpl::map()
{
  Trace trace("WindowImpl::map");
  MutexGuard guard(mutex);
  if (!unmapped) return;
  Stage_var stage = handle->parent();
  stage->begin();
  StageHandle_var tmp = stage->insert(Graphic_var(_this()), handle->position(), handle->size(), handle->layer()); 
  stage->end();
  handle = tmp;
  for (mtable_t::iterator i = manipulators.begin(); i != manipulators.end(); i++)
    (*i)->bind(handle);
  unmapped = 0;
}

void WindowImpl::unmap()
{
  Trace trace("WindowImpl::unmap");
  MutexGuard guard(mutex);
  if (unmapped) return;
  unmapped = new UnmappedStageHandle(handle);
  handle->remove();
}

void WindowImpl::activateComposite()
{
  Trace trace("WindowImpl::activateComposite");
  ControllerImpl::activateComposite();
  MutexGuard guard(mutex);
  for (mtable_t::iterator i = manipulators.begin(); i != manipulators.end(); ++i)
    activate(*i);
}
