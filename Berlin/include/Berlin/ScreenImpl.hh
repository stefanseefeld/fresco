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
#include <Berlin/RegionImpl.hh>
#include <Berlin/DamageImpl.hh>
#include <Berlin/MonoGraphic.hh>
#include <Drawing/openGL/GLDrawingKit.hh>

class ScreenManager;

class ScreenImpl : implements(Screen), virtual public MonoGraphic
{
public:
  ScreenImpl(GLDrawingKit *, Coord, Coord);
  virtual ~ScreenImpl();

  Coord width();
  Coord height();
  ScreenManager *Manager() { return manager;}
  Region_ptr getRegion() {return region->_this();}
protected:
  ScreenManager *manager;
  RegionImpl *region;
  DamageImpl *damage;
};

#endif /* _ScreenImpl_hh */
