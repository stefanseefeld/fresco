/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 2000 Graydon Hoare <graydon@pobox.com> 
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
#ifndef _ScreenManager_hh
#define _ScreenManager_hh

#include <Prague/Sys/Thread.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/Graphic.hh>
#include <Warsaw/Input.hh>
#include <Warsaw/DrawingKit.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/Console.hh>
#include <Berlin/DrawTraversalImpl.hh>
#include <Berlin/EventManager.hh>
#include <vector>

class RegionImpl;

class ScreenManager
{
public:
  ScreenManager(Warsaw::Graphic_ptr, EventManager *, Warsaw::DrawingKit_ptr);
  ~ScreenManager();
  //. This method marks the given Region as damaged.
  void damage(Warsaw::Region_ptr);
  //. This method redraws the damaged regions of the screen.
  void repair();
  //. Main event loop.
  void run();
private:
  Warsaw::Graphic_var         _screen;    //.< The graphic that is managed.
  EventManager               *_emanager;
  Warsaw::DrawingKit_var      _drawing;   //.< The DrawingKit used to update this screen. 
  Console::Drawable          *_drawable;  //.< A chunk of memory we are drawing into.
  Impl_var<RegionImpl>        _theDamage; //.< The region that got damaged.
  Impl_var<RegionImpl>        _tmpDamage; //.< Temporary copy of _theDamage
  Impl_var<DrawTraversalImpl> _traversal;
  Prague::Mutex               _mutex;
};

#endif
