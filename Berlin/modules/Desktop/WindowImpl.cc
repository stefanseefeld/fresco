/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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
#include "WindowImpl.hh"

using namespace Prague;
using namespace Fresco;
using namespace Layout;

using namespace Berlin::DesktopKit;

class WindowImpl::UnmappedStageHandle :
    public virtual POA_Layout::StageHandle, public virtual ServantBase
{
  public:
    UnmappedStageHandle(Stage_ptr, Graphic_ptr, const Vertex &,
			const Vertex &,	Stage::Index);
    UnmappedStageHandle(StageHandle_ptr);
    virtual ~UnmappedStageHandle();
    virtual Stage_ptr parent() { return Stage::_duplicate(my_parent); }
    virtual Graphic_ptr child()
    { return Fresco::Graphic::_duplicate(my_child); }
    virtual void remove() { }
    virtual Vertex position() { return my_position; }
    virtual void position(const Vertex &pp) { my_position = pp; }
    virtual Vertex size() { return my_size; }
    virtual void size(const Vertex &ss) { my_size = ss; }
    virtual Stage::Index layer() { return my_layer; }
    virtual void layer(Stage::Index ll) { my_layer = ll; }
private:
    Stage_var    my_parent;
    Graphic_var  my_child;
    Vertex       my_position;
    Vertex       my_size;
    Stage::Index my_layer;
};

WindowImpl::UnmappedStageHandle::UnmappedStageHandle(Stage_ptr par,
						     Graphic_ptr cc,
						     const Vertex &pp,
						     const Vertex &ss,
						     Stage::Index ll) :
  my_parent(Stage::_duplicate(par)),
  my_child(Fresco::Graphic::_duplicate(cc)),
  my_position(pp),
  my_size(ss),
  my_layer(ll)
{ }

WindowImpl::UnmappedStageHandle::UnmappedStageHandle(StageHandle_ptr handle) :
  my_parent(handle->parent()),
  my_child(handle->child()),
  my_position(handle->position()),
  my_size(handle->size()),
  my_layer(handle->layer())
{ }

WindowImpl::UnmappedStageHandle::~UnmappedStageHandle()
{ Trace trace("UnmappedStageHandle::~UnmappedStageHandle"); }

WindowImpl::WindowImpl() : ControllerImpl(false)
{ Trace trace("WindowImpl::WindowImpl"); }

WindowImpl::~WindowImpl()
{
    Trace trace("WindowImpl::~WindowImpl");
    mapped(false);
}

void WindowImpl::need_resize()
{
    Trace trace("WindowImpl::need_resize");
    Vertex size = my_handle->size();
    Fresco::Graphic::Requisition r;
    GraphicImpl::init_requisition(r);
    request(r);
    if (r.x.minimum <= size.x && r.x.maximum >= size.x &&
	r.y.minimum <= size.y && r.y.maximum >= size.y &&
	r.z.minimum <= size.z && r.z.maximum >= size.z)
	need_redraw();
    else
    {
	size.x = std::min(r.x.maximum, std::max(r.x.minimum, size.x));
	size.y = std::min(r.y.maximum, std::max(r.y.minimum, size.y));
	size.z = std::min(r.z.maximum, std::max(r.z.minimum, size.z));
	my_handle->size(size);
    }
}

// cache the focus holding controllers so we can restore them when the
//  window receives focus again...
CORBA::Boolean WindowImpl::request_focus(Controller_ptr c,
					 Fresco::Input::Device d)
{
    if (my_unmapped) return false;
    Controller_var parent = parent_controller();
    if (CORBA::is_nil(parent)) return false;
    if (parent->request_focus(c, d))
    {
	if (my_focus.size() <= d) my_focus.resize(d + 1);
	my_focus[d] = Fresco::Controller::_duplicate(c);
	return true;
    }
    else return false;
}

void WindowImpl::insert(Desktop_ptr desktop)
{
    Trace trace("WindowImpl::insert");
    Vertex position, size;
    position.x = position.y = 100., position.z = 0.;
    Fresco::Graphic::Requisition r;
    GraphicImpl::init_requisition(r);
    request(r);
    size.x = r.x.natural, size.y = r.y.natural, size.z = 0;
    my_unmapped = new UnmappedStageHandle(desktop,
					  Graphic_var(_this()),
					  position,
					  size,
					  0);
    my_handle = my_unmapped->_this();
}

Vertex WindowImpl::position()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_handle->position();
}

void WindowImpl::position(const Vertex &p)
{
    Trace trace("WindowImpl::position");
    Prague::Guard<Mutex> guard(my_mutex);
    my_handle->position(p);
}

Vertex WindowImpl::size()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_handle->size();
}

void WindowImpl::size(const Vertex &s)
{
    Trace trace("WindowImpl::size");
    Prague::Guard<Mutex> guard(my_mutex);
    my_handle->size(s);
}

Stage::Index WindowImpl::layer()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_handle->layer();
}

void WindowImpl::layer(Stage::Index l)
{
    Trace trace("WindowImpl::layer");
    Prague::Guard<Mutex> guard(my_mutex);
    my_handle->layer(l);
}

CORBA::Boolean WindowImpl::mapped()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return !my_unmapped;
}

void WindowImpl::mapped(CORBA::Boolean flag)
{
    Trace trace("WindowImpl::mapped");
    if (flag)
    // map
    {
	Prague::Guard<Mutex> guard(my_mutex);
	if (!my_unmapped) return;
	Stage_var stage = my_handle->parent();
	stage->lock();
	StageHandle_var tmp = stage->insert(Graphic_var(_this()),
					    my_handle->position(),
					    my_handle->size(),
					    my_handle->layer());
	stage->unlock();
	my_handle = tmp;
	my_unmapped = 0;
    }
    else
    // unmap
    {
	Prague::Guard<Mutex> guard(my_mutex);
	if (my_unmapped) return;
	my_unmapped = new UnmappedStageHandle(my_handle);
	my_handle->remove();
	my_handle = my_unmapped->_this();
    }
}
