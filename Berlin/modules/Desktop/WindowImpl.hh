/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _DesktopKit_WindowImpl_hh
#define _DesktopKit_WindowImpl_hh

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/Window.hh>
#include <Fresco/Desktop.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ControllerImpl.hh>
#include <Prague/Sys/Thread.hh>
#include <vector>

namespace Berlin
{
  namespace DesktopKit
  {

    class WindowImpl : public virtual POA_Fresco::Window,
		       public ControllerImpl
    {
	class UnmappedStageHandle;
      public:
	WindowImpl();
	virtual ~WindowImpl();
	virtual void need_resize();
	virtual CORBA::Boolean request_focus(Fresco::Controller_ptr,
					     Fresco::Input::Device);
	void insert(Fresco::Desktop_ptr);
	virtual Fresco::Vertex position();
	virtual void position(const Fresco::Vertex &);
	virtual Fresco::Vertex size();
	virtual void size(const Fresco::Vertex &);
	virtual Layout::Stage::Index layer();
	virtual void layer(Layout::Stage::Index);
	virtual CORBA::Boolean mapped();
	virtual void mapped(CORBA::Boolean);
      private:
	Layout::StageHandle_var             my_handle;
	Impl_var<UnmappedStageHandle>       my_unmapped;
	Prague::Mutex                       my_mutex;
	std::vector<Fresco::Controller_var> my_focus;
    };

  } // namespace
} // namespace

#endif
