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
#ifndef _ScreenImpl_hh
#define _ScreenImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Screen.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/MonoGraphic.hh>
#include <Berlin/ControllerImpl.hh>

class ScreenManager;
class EventManager;
class RegionImpl;

class ScreenImpl : public virtual POA_Warsaw::Screen,
                   public ControllerImpl
{
public:
  ScreenImpl(Warsaw::DrawingKit_ptr);
  virtual ~ScreenImpl();

  virtual void pick(Warsaw::PickTraversal_ptr);
  virtual void allocations(Warsaw::Allocation_ptr);
  virtual void need_resize() { need_redraw();}

  virtual Warsaw::Coord width();
  virtual Warsaw::Coord height();
  virtual Warsaw::DrawingKit_ptr kit();
  virtual void damage(Warsaw::Region_ptr);

  virtual CORBA::Boolean request_focus(Warsaw::Controller_ptr, Warsaw::Input::Device);
  virtual CORBA::Boolean receive_focus(Warsaw::Focus_ptr) { return true;}
  virtual void lose_focus(Warsaw::Input::Device) {}
  virtual CORBA::Boolean handle_positional(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &) { return false;}
  virtual CORBA::Boolean handle_non_positional(const Warsaw::Input::Event &) { return false;}

  ScreenManager *manager();
  Warsaw::Region_ptr get_region();
protected:
  Warsaw::DrawingKit_var  drawing;
  ScreenManager *smanager;
  Impl_var<RegionImpl> region;
  EventManager  *emanager;
};

#endif 
