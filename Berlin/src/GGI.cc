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
#include "Berlin/GGI.hh"
#include "Prague/Sys/FdSet.hh"

vector<GGI::Drawable *> GGI::drawables;

GGI::GGI()// throw (exception)
{
  ggiInit();
}

GGI::~GGI()
{
  for (vector<Drawable *>::iterator i = drawables.begin(); i != drawables.end(); i++) delete *i;
  ggiExit();
}

GGI::Drawable *GGI::drawable()
{
  if (!drawables.size()) drawables.push_back(new Drawable);
  return drawables.front();
}

GGI::Drawable::Drawable() // throw (exception)
{
  vis = ggiOpen(0);
//  vis = ggiOpen("display-memory", 0);
  if (!vis) throw exception();
  mode.visible.x = mode.visible.y = GGI_AUTO;
  mode.virt.x = mode.virt.y = GGI_AUTO;
  mode.size.x = 768;
  mode.size.y = 1000;
  mode.dpp.x = mode.dpp.y = 1;
  mode.graphtype = GT_AUTO;
  mode.frames = 1;
  if (ggiCheckMode(vis, &mode) == 0)
    {
      // Cannot set visual, even though GGI says it's ok???
      if (ggiSetMode(vis, &mode) != 0) throw exception();
    }
  else
    {
      // Hmm. internal GGI problem. The mode GGI gave us still won't work.
      if (ggiCheckMode(vis, &mode) != 0 || ggiSetMode(vis, &mode) != 0) throw exception();
    }
  ggiAddFlags(vis, GGIFLAG_ASYNC);
  pipe(wakeupPipe);
}

GGI::Drawable::~Drawable()
{
  close(wakeupPipe[0]);
  close(wakeupPipe[1]);
  ggiClose(vis);
}

bool GGI::Drawable::nextEvent(ggi_event &event)
{
  ggi_event_mask mask = ggi_event_mask (emKeyboard | emPtrMove | emPtrButtonPress | emPtrButtonRelease);
  Prague::FdSet rfdset;
  rfdset.set(wakeupPipe[0]);
  switch(ggiEventSelect(vis, &mask, rfdset.max() + 1, rfdset, 0, 0, 0))
    {
    case 0: ggiEventRead(vis, &event, mask); return true;
    case 1:{ char c; read(wakeupPipe[0], &c, 1); }
    default: break;
    }
  return false;
}

void GGI::Drawable::wakeup() { char c = 'z'; write(wakeupPipe[1],&c,1);}

GGI ggi;
