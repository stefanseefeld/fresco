/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 2000 Graydon Hoare <graydon@fresco.org> 
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
#ifndef _Berlin_ScreenManager_hh
#define _Berlin_ScreenManager_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/Region.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/Input.hh>
#include <Fresco/DrawingKit.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/Console.hh>
#include <Berlin/DrawTraversalImpl.hh>
#include <Berlin/EventManager.hh>
#include <vector>

namespace Berlin
{

  class RegionImpl;

  //. The ScreenManager contains the main event loop. It queries the
  //. EventManager for those Events, registers damages to the screen's
  //. contents and repairs them by initialising a DrawTraversal whenever
  //. needed.
  class ScreenManager
  {
    public:
      ScreenManager(Fresco::Graphic_ptr, EventManager *,
		    Fresco::DrawingKit_ptr);
      ~ScreenManager();
      //. This method marks the given Region as damaged.
      void damage(Fresco::Region_ptr);
      //. This method redraws the damaged regions of the screen.
      //. The DrawTraversal gets started here!
      void repair();
      //. Start the gui thread
      void start();
    private:
      static void *run_thread(void *);
      void run();
      Fresco::Graphic_var my_screen; //.< The graphic that is managed.
      EventManager *my_emanager;
      Fresco::DrawingKit_var my_drawing; //.< The DrawingKit used to update this screen. 
      Impl_var<RegionImpl> my_theDamage; //.< The region that got damaged.
      Impl_var<RegionImpl> my_tmpDamage; //.< Temporary copy of _theDamage
      Impl_var<DrawTraversalImpl> my_traversal;
      Prague::Mutex my_mutex;
      Prague::Thread my_thread;
  };

} // namespace

#endif
