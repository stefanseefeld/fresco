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
#ifndef _Berlin_DesktopImpl_hh
#define _Berlin_DesktopImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Desktop.hh>
#include <Berlin/ControllerImpl.hh>
#include <Berlin/RefCountVar.hh>

class WindowImpl;

class DesktopImpl : public virtual POA_Fresco::Desktop,
                    public ControllerImpl
{
public:
  DesktopImpl(CORBA::ORB_ptr, Layout::Stage_ptr);
  virtual ~DesktopImpl();
  virtual void body(Fresco::Graphic_ptr);
  virtual Fresco::Graphic_ptr body();
  virtual Fresco::Region_ptr bbox();
  virtual CORBA::Long layers();
  virtual Layout::StageHandle_ptr layer(Layout::Stage::Index);
  virtual void lock();
  virtual void unlock();
  virtual Layout::StageHandle_ptr insert(Fresco::Graphic_ptr,
					 const Fresco::Vertex &,
					 const Fresco::Vertex &,
					 Layout::Stage::Index);

protected:
  virtual void key_press(const Fresco::Input::Event &); 
private:
  RefCount_var<Layout::Stage> _stage;
  CORBA::ORB_var              _orb;
};

#endif 
