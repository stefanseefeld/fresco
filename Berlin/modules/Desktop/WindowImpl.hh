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
#include <Warsaw/Desktop.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ControllerImpl.hh>
#include <Prague/Sys/Thread.hh>
#include <vector>

class WindowImpl : public virtual POA_Warsaw::Window,
		   public ControllerImpl
{
  class UnmappedStageHandle;
public:
  WindowImpl();
  virtual ~WindowImpl();
  virtual void needResize();
  virtual CORBA::Boolean requestFocus(Warsaw::Controller_ptr, Warsaw::Input::Device);
  void insert(Warsaw::Desktop_ptr, bool);
  virtual Warsaw::Vertex position();
  virtual void position(const Warsaw::Vertex &);
  virtual Warsaw::Vertex size();
  virtual void size(const Warsaw::Vertex &);
  virtual Warsaw::Stage::Index layer();
  virtual void layer(Warsaw::Stage::Index);
  virtual CORBA::Boolean mapped();
  virtual void mapped(CORBA::Boolean);
private:
  Warsaw::StageHandle_var handle;
  Impl_var<UnmappedStageHandle> unmapped;
  Prague::Mutex mutex;
  vector<Warsaw::Controller_var> focus;
};

#endif
