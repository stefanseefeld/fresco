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

#ifndef __DEBUG__
#define __DEBUG__

#include <vector>
#include <string>
#include "Warsaw/config.hh"
#include "Berlin/Thread.hh"

// some NANA stuff
#include <L_times.h>
#include <L_buffer.h>
#include <now.h>

// this is a rewrite of our debugging class to use some NANA features.  the idea
// is that what was previously just a matter of writing to stderr, we now log
// *everything* to an internal buffer, and only write to stderr if the group
// you're writing to is enabled. Then when the system keels over, we dump the
// in-core log and ask users to mail it to us, as a bug report

class Debug {

public:

    Debug(); // this creates the logs
    ~Debug(); // this dumps the logs

    enum debugGroup { corba, loader, traversal, thread, main,
		      agent, message, command, subject, observer,
		      text, widget, image, figure, layout, drawing,
		      picking, geometry //... add more? 
    };

    static void set(debugGroup g);
    static void clear(debugGroup g);
    static void setall();
    static inline void shutdownOk() {
	MutexGuard debugGuard(Debug::myMutex); 
	cleanShutdown = true;
    }
    
    static inline void note(const char *c) {
	MutexGuard debugGuard(Debug::myMutex); 
	L_times_add(Debug::core_times_log, (char *)c, now()); 
    }
    
    static inline void log(debugGroup gr,  const char * format, ...) {
	MutexGuard debugGuard(Debug::myMutex); 
	double n = now();
	int i = Thread::self()->id();
	L_buffer_printf(Debug::core_buf_log, "[%6.6f:%3d:%s] ", n, i, groupNames[gr]);   
	
	va_list ap;
	va_start(ap, format);
	vsnprintf(cbuf,msgsz,format,ap);
	L_buffer_printf(Debug::core_buf_log, cbuf);   
	L_buffer_printf(Debug::core_buf_log, "\n");
	
	if (Debug::g[gr]) { 
	    fprintf(stderr, "[%6.6f:%d:%s] ", n, i, groupNames[gr]); fprintf(stderr, cbuf); 	    
	    fprintf(stderr, "\n");
	}
    } 
    
    protected:
    static const int msgsz = 256;
    static const int logsz = 1024 * 64;
    static const int stampsz = 256;
    static const int numGroups = 18;

    static char cbuf[msgsz];
    static Debug staticTrigger; // this is a global, single trigger object.    
    static bool g[numGroups];
    static char * groupNames[numGroups]; 
    static L_BUFFER *core_buf_log;
    static L_TIMES *core_times_log;    
    static Mutex myMutex;
    static bool cleanShutdown;
};


#endif
