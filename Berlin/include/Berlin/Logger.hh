/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1998 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
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
#ifndef _Berlin_Logger_hh
#define _Berlin_Logger_hh

#include "Prague/Sys/logstream.hh"
#include "Prague/Sys/Time.hh"
#include "Prague/Sys/Thread.hh"
#include "Fresco/config.hh"

namespace Berlin
{

  class Logger
  //. this is a rewrite of our debugging class to use some NANA features.
  //. The idea is that what was previously just a matter of writing to
  //. stderr, we now log *everything* to an internal buffer, and only
  //. write to stderr if the group you're writing to is enabled. Then
  //. when the system keels over, we dump the in-core log and ask users
  //, to mail it to us, as a bug report,
  {
    public:
      enum group
      {
	  corba,
	  loader,
	  console,
	  traversal,
	  thread,
	  lifecycle,
	  agent,
	  message,
	  command,
	  subject,
	  observer,
	  text,
	  widget,
	  image,
	  figure,
	  layout,
	  drawing,
	  desktop,
	  picking,
	  focus,
	  geometry
      };
    private:
      struct streamlock;
      friend struct streamlock;
      template <class T>
      static void write(group g, const T &t)
      {
	  my_los << t;
	  if (my_active[g]) std::cerr << t;
      }
      static const int my_numGroups = 21;
    public:
      static void set(group g) { my_active[g] = true; }
      static void clear(group g) { my_active[g] = false; }
      static void setall()
      { for (int i = 0; i < my_numGroups; i++) my_active[i] = true; }
      static streamlock log(group g)
      {
	  streamlock slock(g);
	  write(g, '[');
	  write(g, static_cast<double>(Prague::Time::currentTime() -
				       my_start));
	  write(g, ':');
	  write(g, Prague::Thread::id());
	  write(g, ':');
	  write(g, my_groupname[g]);
	  write(g, "]\t");
	  return slock;
      } 
      static void dump(std::ostream &);
    protected:
    private:
      struct streamlock
      {
	  streamlock(group gg) :
	      owner(true), g(gg)
	  { Logger::my_mutex.lock(); }
	  streamlock(const streamlock &sl) :
	      owner(true), g(sl.g)
	  { sl.owner = false; }
	  ~streamlock() { if (owner) Logger::my_mutex.unlock(); }
	  mutable bool owner;
	  group g;
      };
      friend const streamlock &
      operator << (const streamlock &sl,
		   std::ostream & (func)(std::ostream &))
      { Logger::write(sl.g, func); return sl; }
      template <class T>
      friend const streamlock &
      operator << (const streamlock &sl, const T &t)
      { Logger::write(sl.g, t); return sl;}
      static bool my_active[my_numGroups];
      static const char *my_groupname[my_numGroups]; 
      static Prague::logbuf my_buf;
      static Prague::logstream my_los;
      static Prague::Time my_start;
      static Prague::Mutex my_mutex;
  };

} // namespace

#endif
