#/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Berlin/Logger.hh"

using namespace Prague;
using namespace Berlin;

bool Logger::my_active[my_numGroups] = {
    false, false, false, false, 
    false, false, false, false,
    false, false, false, false, 
    false, false, false, false,
    false, false, false, false, 
    false };
const char * Logger::my_groupname[my_numGroups] = {
    "corba", "loader", "console", "traversal", 
    "thread", "lifecycle", "agent", "message",
    "command", "subject", "observer", "text",
    "widget", "image", "figure", "layout",
    "drawing", "desktop", "picking", "focus",
    "geometry" };
logbuf Logger::my_buf(1024 * 64);
logstream Logger::my_los(&my_buf);
Time Logger::my_start = Time::currentTime();
Mutex Logger::my_mutex;

void Logger::dump(std::ostream &os)
{
    my_los.dump(os);
    os << "\n\nDetailed Trace:\n";
}
