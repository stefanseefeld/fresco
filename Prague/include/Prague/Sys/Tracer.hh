/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _Prague_Tracer_hh
#define _Prague_Tracer_hh

#include <Prague/Sys/config.hh>
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/ThreadData.hh>
#include <vector>

namespace Prague
{

class Trace;

class Tracer
//. this class represents a lightweight circular tracing stream
//. similar to the one in GNU NANA except designed for use in 
//. a multithreaded C++ environment with section guards.
{
  struct Event
  {
    double time;
    unsigned long thread;
    const char *type;
    const char *specifics;
    friend ostream &operator << (ostream &os, const Event &e)
    { return os << e.time << ':' << e.thread << '\t' << e.type << ' ' << e.specifics;}
  };
  friend class Trace;
public:
  static void resize(size_t s) { MutexGuard guard(mutex); events.resize(s); if (next >= s) next = 0;}
  static void logging(bool l) { log = l;}
  static void add(const char *n, const char *ty = "")
  {
    {
      MutexGuard guard(mutex);
      if (next == events.size()) return;
      events[next].time = Time::currentTime() - start;
      events[next].thread = Thread::self()->id();
      events[next].type = ty;
      events[next].specifics = n;
      if (log)
	{
	  for (unsigned short i = 0; i != *indent; i++) cerr.put(' ');
	  cerr << events[next] << endl;
	}
      next++;
      if (next == events.size()) 
	{
	  next = 0;
	  wrapped = true;
	}
    }
  }
  static void clear() { next = 0; wrapped = false;}
  static void dump(ostream &os)
  {
    vector<Event>::iterator e;
    os << "* Tracer::dump =\n";
    if (wrapped) for (e = events.begin() + next; e != events.end(); e++) os << *e << '\n';
    for (e = events.begin(); e != events.begin() + next; e++) os << *e << '\n';
    os << "* end of Tracer::dump" << endl; 
  }
private:
  static vector<Event> events;
  static Time start;
  static Thread::Data<unsigned short> indent;
  static Mutex mutex;
  static unsigned int next;
  static bool wrapped;
  static bool log;
};

#ifdef TRACER
class Trace
{
public:
  Trace(const char *s) : section(s) { Tracer::add(section, "enter"); ++*Tracer::indent;}
  ~Trace() { --*Tracer::indent; Tracer::add(section, "leave");}
private:
  const char *section;
};
#else
class Trace
{
public:
  Trace(const char *) {}
  ~Trace() {}
};
#endif

};

#endif /* _Prague_Tracer_hh */
