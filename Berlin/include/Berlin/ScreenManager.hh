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
#ifndef _ScreenManager_hh
#define _ScreenManager_hh

#include "Warsaw/config.hh"

extern "C" {
#include <ggi/ggi.h>
}

#include "Warsaw/Region.hh"
#include "Berlin/Thread.hh"
#include <vector>

class GLDrawingKit;
class Pointer;
class ScreenImpl;
class RegionImpl;

class ScreenManager
{
    public:
    ScreenManager(ScreenImpl *, GLDrawingKit *);
    ~ScreenManager();
    void damage(Region_ptr);
    void repair();
    void nextEvent();
    void run();
    private:
    long ptrPositionX;
    long ptrPositionY;
    ScreenImpl *screen;
    GLDrawingKit *drawing;
    Pointer *pointer;
    ggi_visual_t visual;
    typedef vector<RegionImpl *> DamageList;
    DamageList damages;
    Mutex damageMutex;
};

#endif /* _ScreenManager_hh */
