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
#ifndef _Berlin_ScreenImpl_hh
#define _Berlin_ScreenImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Screen.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/MonoGraphic.hh>
#include <Berlin/ControllerImpl.hh>

namespace Berlin
{

  class ScreenManager;
  class EventManager;
  class RegionImpl;
  
  class ScreenImpl : public virtual POA_Fresco::Screen,
             public ControllerImpl
  {
    public:
      //. Sets up the screen to the sizes given by the console in use.
      ScreenImpl();
      virtual ~ScreenImpl();
      //. Sets up the Event- and Screenmanager for this screen.
      void bind_managers(EventManager *, ScreenManager *);
      
      virtual void pick(Fresco::PickTraversal_ptr);
      virtual void allocations(Fresco::Allocation_ptr);
      virtual void need_resize() { need_redraw();}
      
      virtual Fresco::Coord width();
      virtual Fresco::Coord height();
      virtual void damage(Fresco::Region_ptr);
      
      virtual CORBA::Boolean request_focus(Fresco::Controller_ptr,
                       Fresco::Input::Device);
      virtual CORBA::Boolean receive_focus(Fresco::Focus_ptr) { return true; }
      virtual void lose_focus(Fresco::Input::Device) { }
      virtual CORBA::Boolean handle_positional(Fresco::PickTraversal_ptr,
                           const Fresco::Input::Event &)
      { return false; }
      virtual CORBA::Boolean
      handle_non_positional(const Fresco::Input::Event &) { return false; }
    
      Fresco::Region_ptr allocation();
    protected:
      Fresco::Screen_ptr     my_this;
      EventManager          *my_emanager;
      ScreenManager         *my_smanager;
      Impl_var<RegionImpl>   my_region;
  };

} // namespace

#endif 
