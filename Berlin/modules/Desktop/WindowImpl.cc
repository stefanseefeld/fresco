/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

class WindowImpl::UnmappedStageHandle : public virtual POA_Warsaw::StageHandle,
		                        public virtual ServantBase
{
public:
  UnmappedStageHandle(Warsaw::Stage_ptr, Warsaw::Graphic_ptr, const Warsaw::Vertex &, const Warsaw::Vertex &, Warsaw::Stage::Index);
  UnmappedStageHandle(Warsaw::StageHandle_ptr);
  virtual ~UnmappedStageHandle();
  virtual Warsaw::Stage_ptr parent() { return Warsaw::Stage::_duplicate(stage);}
  virtual Warsaw::Graphic_ptr child() { return Warsaw::Graphic::_duplicate(c);}
  virtual void remove() {}
  virtual Warsaw::Vertex position() { return p;}
  virtual void position(const Warsaw::Vertex &pp) { p = pp;}
  virtual Warsaw::Vertex size() { return s;}
  virtual void size(const Warsaw::Vertex &ss) { s = s;}
  virtual Warsaw::Stage::Index layer() { return l;}
  virtual void layer(Warsaw::Stage::Index ll) { l = ll;}
private:
  Warsaw::Stage_var stage;
  Warsaw::Graphic_var c;
  Warsaw::Vertex p;
  Warsaw::Vertex s;
  Warsaw::Stage::Index l;
};

WindowImpl::UnmappedStageHandle::UnmappedStageHandle(Warsaw::Stage_ptr par, Warsaw::Graphic_ptr cc,
						     const Warsaw::Vertex &pp, const Warsaw::Vertex &ss, Warsaw::Stage::Index ll)
  : stage(Warsaw::Stage::_duplicate(par)), c(Warsaw::Graphic::_duplicate(cc)), p(pp), s(ss), l(ll) {}
WindowImpl::UnmappedStageHandle::UnmappedStageHandle(Warsaw::StageHandle_ptr handle)
  : stage(handle->parent()),
    c(handle->child()),
    p(handle->position()),
    s(handle->size()),
    l(handle->layer())
{}
WindowImpl::UnmappedStageHandle::~UnmappedStageHandle() { Prague::Trace trace("UnmappedStageHandle::~UnmappedStageHandle");}

WindowImpl::WindowImpl()
  : ControllerImpl(false)
{
  Trace trace("WindowImpl::WindowImpl");
}

WindowImpl::~WindowImpl()
{
  Trace trace("WindowImpl::~WindowImpl");
  mapped(false);
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

void WindowImpl::insert(Desktop_ptr desktop, bool flag)
{
  Trace trace("WindowImpl::insert");
  Vertex position, size;
  position.x = position.y = 1000., position.z = 0.;
  Warsaw::Graphic::Requisition r;
  request(r);
  size.x = r.x.natural, size.y = r.y.natural, size.z = 0;
  unmapped = new UnmappedStageHandle(desktop, Graphic_var(_this()), position, size, 0);
  handle = unmapped->_this();
  mapped(flag);
}

Vertex WindowImpl::position()
{
  MutexGuard guard(mutex);
  return handle->position();
}

void WindowImpl::position(const Vertex &p)
{
  Trace trace("WindowImpl::position");
  MutexGuard guard(mutex);
  handle->position(p);
}

Vertex WindowImpl::size()
{
  MutexGuard guard(mutex);
  return handle->size();
}

void WindowImpl::size(const Vertex &s)
{
  Trace trace("WindowImpl::size");
  MutexGuard guard(mutex);
  handle->size(s);
}

Stage::Index WindowImpl::layer()
{
  MutexGuard guard(mutex);
  return handle->layer();
}

void WindowImpl::layer(Stage::Index l)
{
  Trace trace("WindowImpl::layer");
  MutexGuard guard(mutex);
  handle->layer(l);
}

CORBA::Boolean WindowImpl::mapped()
{
  MutexGuard guard(mutex);
  return !unmapped;
}

void WindowImpl::mapped(CORBA::Boolean flag)
{
  Trace trace("WindowImpl::mapped");
  if (flag)
    /*
     * map
     */
    {
      MutexGuard guard(mutex);
      if (!unmapped) return;
      Stage_var stage = handle->parent();
      stage->begin();
      StageHandle_var tmp = stage->insert(Graphic_var(_this()), handle->position(), handle->size(), handle->layer()); 
      stage->end();
      handle = tmp;
      unmapped = 0;
    }
  else
    /*
     * unmap
     */
    {
      MutexGuard guard(mutex);
      if (unmapped) return;
      unmapped = new UnmappedStageHandle(handle);
      handle->remove();
    }
}
