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

#include <Prague/config.hh>
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/ThreadData.hh>
#include <vector>

namespace Prague
{

class Trace;

//. this class represents a lightweight circular tracing stream
//. similar to the one in GNU NANA except designed for use in 
//. a multithreaded C++ environment with section guards.
class Tracer
{
  struct Event
  {
    double time, start;
    unsigned long thread;
    const char *type;
    const char *object;
    const char *section;
  };
  friend std::ostream &Prague::operator << (std::ostream &os, const Event &e);
  friend class Trace;
public:
  static void resize(size_t s)
  {
    Prague::Guard<Mutex> guard(_mutex);
    _events.resize(s);
    if (_next >= s) _next = 0;
  }
  static void logging(bool l) { _log = l;}
  static double add(const char *, const char *, const char *, double start = -1);
  static void clear() { _next = 0; _wrapped = false;}
  static void dump(std::ostream &);
  static void reset_clock() { _start = Time::currentTime();}
private:
  static std::vector<Event>           _events;
  static Time                         _start;
  static Thread::Data<unsigned short> _indent;
  static Mutex                        _mutex;
  static unsigned int                 _next;
  static bool                         _wrapped;
  static bool                         _log;
};

//. An abstract class defining the NamedObject 'interface' providing a method
//. of retrieving the name of implementing objects. This will usually be used
//. for debugging purposes, eg: the Tracer
class NamedObject
{
public:
  //. Return a decriptive name for this object, used mainly for debugging
  //. and introspection purposes. This should be short, only a couple of
  //. words if that, and encapsulate the type and kit of the object.
  virtual const char *object_name() = 0;
};

#ifdef TRACER
//. The guard class which marks the start and end of a scope, typically used
//. to mark function calls in the trace dump. It will append an item to the
//. trace log upon construction, and another upon destruction.
//.
//. Usage: Trace(this, "MyObject::ThisFunc");
class Trace
{
public:
  //. Constructor for classes that don't inherit NamedObject. Those that do
  //. should use the other constructor.
  Trace(const char *s) : _section(s), _obj_name(0)
  {
    _start = Tracer::add("enter", 0, _section);
    ++*Tracer::_indent;
  }
  
  //. Constructor for classes that do inherit NamedObject. The name of the
  //. object is extracted using the 'object_name()' method, and stored in the
  //. trace log.
  Trace(NamedObject *obj, const char *section) : _section(section), _obj_name(0)
  {
    if (obj) _obj_name = obj->object_name();
    _start = Tracer::add("enter", _obj_name, _section);
    ++*Tracer::_indent;
  }

  //. Destructor, adds another trace log entry to signify the end of the
  //. section this object was guarding
  ~Trace() 
  {
    --*Tracer::_indent;
    Tracer::add("leave", _obj_name, _section, _start);
  }
private:
  //. The name of the section, or function
  const char *_section;
  //. The name of the object (which may contain more info than just the class
  //. name)
  const char *_obj_name;
  //. The starting time of the guard section
  double      _start;
};
#else
class Trace
{
public:
  Trace(const char *) {}
  Trace(NamedObject *, const char *) {}
  ~Trace() {}
};
#endif

};

#endif
