//
// $Id$
//
// This source file is a part of the Berlin Project.
// Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
// http://www.berlin-consortium.org
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public License
// as published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//

#include "Berlin/Debug.hh"

vector<bool> debug::activeDebugGroups(12, false);
Mutex debug::cerrMutex;
  
void debug::log(string msg, debugGroup g)
{
  MutexGuard guard(cerrMutex);
  if (activeDebugGroups[g])  cerr << msg << endl;
}

void debug::set(debugGroup g) { activeDebugGroups[g] = true; }
void debug::clear(debugGroup g) { activeDebugGroups[g] = false; }
void debug::setall()
{
  for (vector<bool>::iterator i = activeDebugGroups.begin(); i != activeDebugGroups.end(); i++)
    *i = true;
}
