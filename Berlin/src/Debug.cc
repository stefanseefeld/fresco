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

char Debug::cbuf[msgsz];
Debug Debug::staticTrigger; // this is a global, single trigger object.
bool Debug::g[numGroups] = { false, false, false, false, false, false, false, false, false, 
			    false, false, false, false, false, false, false, false, false };
char * Debug::groupNames[numGroups] = {"corba", "loader", "traversal", "thread", "main",
				       "agent", "message", "command", "subject", 
				       "observer", "text", "widget", "image", "figure",
				       "layout", "drawing", "picking", "geometry"};
L_BUFFER *Debug::core_buf_log;
L_TIMES *Debug::core_times_log;    
Mutex Debug::myMutex;
bool Debug::cleanShutdown;


Debug::Debug() {
    cleanShutdown = false;
    core_buf_log = L_buffer_create(logsz); // 64k log buffer size
    core_times_log = L_times_create(stampsz); // number of timestamps held in stamplog    
    L_times_clear(core_times_log);
}  

Debug::~Debug() {
    if (!cleanShutdown) {
	fprintf(stderr, "\nSomething went wrong. Here's a debugging log. \nPlease mail this output to bugs@berlin-consortium.org :\n\n");
	L_buffer_dump(core_buf_log, stderr);
	L_buffer_delete(core_buf_log);
	fprintf(stderr, "\n\nDetailed Trace:\n");
	L_times_dump(core_times_log, stderr);
	L_times_delete(core_times_log);
    }
}

void Debug::set(debugGroup gr) { g[gr] = true; }
void Debug::clear(debugGroup gr) { g[gr] = false; }
void Debug::setall()
{
  for (int i = 0; i < numGroups; i++)
    g[i] = true;
}
