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
#ifndef _ScreenImpl_hh
#define _ScreenImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Screen.hh>
#include <Berlin/MonoGraphic.hh>

class ScreenManager;
class RegionImpl;
class GLDrawingKit;

class ScreenImpl : implements(Screen), virtual public MonoGraphic
{
public:
  ScreenImpl(GLDrawingKit *, Coord, Coord);
  virtual ~ScreenImpl();

  virtual void allocate(Graphic_ptr, Allocation_ptr);

  virtual Coord width();
  virtual Coord height();
  virtual DrawingKit_ptr kit();
  virtual void damage(Region_ptr);

  ScreenManager *Manager();
  Region_ptr getRegion();
protected:
  GLDrawingKit  *drawing;
  ScreenManager *manager;
  RegionImpl    *region;
};

#endif /* _ScreenImpl_hh */
