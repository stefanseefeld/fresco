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

// this file encapsulates a debugging facility
// you can use to log messages to (in logical groups)
// it's a singleton, and it's synchronized, which are both 
// reasonably important :)

#include <vector>
#include <string>
#include <Warsaw/config.hh>
#include <Berlin/Thread.hh>

#ifndef __DEBUG__
#define __DEBUG__

class debug {

public:
  enum debugGroup { corba, loader, ggi, gwt, name,
		       gfh, main, widget, mmap,  
		     message, reactor, thread };
  
  static void log(string msg, debugGroup g);
  static void set(debugGroup g);
  static void clear(debugGroup g);
  static void setall();

private:
  static vector<bool> activeDebugGroups;
  static Mutex cerrMutex;
};


#endif
