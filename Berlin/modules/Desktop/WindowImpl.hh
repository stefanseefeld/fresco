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
#ifndef _WindowImpl_hh
#define _WindowImpl_hh

#include <Prague/Sys/Tracer.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Window.hh>
#include <Warsaw/Command.hh>
#include <Warsaw/Desktop.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ControllerImpl.hh>
#include <Prague/Sys/Thread.hh>
#include <vector>

class UnmappedStageHandle;

class WindowImpl : public virtual POA_Warsaw::Window,
		   public ControllerImpl
{
  class Manipulator : public virtual POA_Warsaw::Command,
		      public virtual PortableServer::RefCountServantBase,
		      public virtual RefCountBaseImpl
  {
  public:
    virtual ~Manipulator() { Prague::Trace trace("WindowImpl::Manipulator::~Manipulator");}
    void bind(Warsaw::StageHandle_ptr h) { handle = Warsaw::StageHandle::_duplicate(h);}
    virtual void execute(const CORBA::Any &) = 0;
  protected:
    Warsaw::StageHandle_var handle;
  };
  class Mapper : public virtual POA_Warsaw::Command,
		 public virtual PortableServer::RefCountServantBase,
		 public virtual RefCountBaseImpl
  {
  public:
    Mapper(WindowImpl *w, bool f) : window(w), flag(f) {}
    virtual void execute(const CORBA::Any &);
  private:
    WindowImpl *window;
    bool flag;
  };
  typedef vector<Manipulator *> mtable_t;
 public:
  WindowImpl();
  virtual ~WindowImpl();
  virtual void needResize();
  virtual CORBA::Boolean requestFocus(Warsaw::Controller_ptr, Warsaw::Input::Device);
  void insert(Warsaw::Desktop_ptr, bool);
  virtual CORBA::Boolean mapped() { Prague::MutexGuard guard(mutex); return !unmapped;}
  virtual Warsaw::Command_ptr move();
  virtual Warsaw::Command_ptr resize();
  virtual Warsaw::Command_ptr moveResize(Warsaw::Alignment, Warsaw::Alignment, CORBA::Short);
  virtual Warsaw::Command_ptr relayer();
  virtual Warsaw::Command_ptr map(CORBA::Boolean);
//   virtual void pick(PickTraversal_ptr);
  virtual void map();
  virtual void unmap();
protected:
  virtual void activateComposite();
private:
  Warsaw::StageHandle_var handle;
  Impl_var<UnmappedStageHandle> unmapped;
  mtable_t manipulators;
  Impl_var<Mapper> mapper;
  Impl_var<Mapper> unmapper;
  Prague::Mutex mutex;
  vector<Warsaw::Controller_var> focus;
};

class UnmappedStageHandle : public virtual POA_Warsaw::StageHandle,
			    public virtual PortableServer::RefCountServantBase
{
 public:
  UnmappedStageHandle(Warsaw::Stage_ptr par, Warsaw::Graphic_ptr cc, const Warsaw::Vertex &pp, const Warsaw::Vertex &ss, Warsaw::Stage::Index ll)
    : stage(Warsaw::Stage::_duplicate(par)), c(Warsaw::Graphic::_duplicate(cc)), p(pp), s(ss), l(ll) {}
  UnmappedStageHandle(Warsaw::StageHandle_ptr handle)
    : stage(handle->parent()),
    c(handle->child()),
    p(handle->position()),
    s(handle->size()),
    l(handle->layer())
    {}
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

#endif
