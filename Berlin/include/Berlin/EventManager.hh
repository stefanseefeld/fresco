/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#ifndef _EventManager_hh
#define _EventManager_hh

#include <Warsaw/config.hh>
#include <Warsaw/Input.hh>
#include <Warsaw/Controller.hh>
#include <Berlin/ScreenImpl.hh>
#include <Berlin/FocusImpl.hh>
#include <Berlin/GGI.hh>
#include <vector>

class EventManager
//. synthetize events according to a global device and event descriptor map
//. for now, device 0 is the keyboard, device 1 the mouse
{
public:
  EventManager(ScreenImpl *);
  ~EventManager();
  bool requestFocus(Controller_ptr, Input::Device);
  void nextEvent();
  void restore(Region_ptr);
  void damage(Region_ptr);
private:
  long ptrPositionX;
  long ptrPositionY;
  ScreenImpl *screen;
  GGI::Drawable *drawable;
  vector<FocusImpl *> focus;
};

#endif /* _EventManager_hh */
