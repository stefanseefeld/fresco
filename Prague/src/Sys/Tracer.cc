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

#include "Prague/Sys/Tracer.hh"
#include "Prague/Sys/Time.hh"

using namespace Prague;

std::vector<Tracer::Event>   Tracer::_events(256);
Time                         Tracer::_start = Time::currentTime();
Thread::Data<unsigned short> Tracer::_indent(0);
Mutex                        Tracer::_mutex;
unsigned int                 Tracer::_next = 0;
bool                         Tracer::_wrapped = false;
bool                         Tracer::_log = false;

std::ostream &Prague::operator << (std::ostream &os, const Prague::Tracer::Event &e)
{
  os.setf(ios::fixed);
  os.precision(6);
  os << e.time << '|' << e.thread << '\t' << e.type << ' ' << e.section;
  if (e.object) os << " - " << e.object;
  if (e.start != -1) os << " took " << (e.time-e.start);
  os.unsetf(ios::fixed);
  return os;
}

double Tracer::add(const char *type, const char *object, const char *section, double start)
{
  // Remember the start time for this function, to use in compensating an
  // offset for more accurate tracer timings
  Time time = Time::currentTime(); 

  // Thread guard
  Prague::Guard<Mutex> guard(_mutex);

  if (_next == _events.size()) return 0.;

  // Remember to return the time at the start of the function
  double ret = _events[_next].time = time - _start;
  _events[_next].thread = Thread::self()->id();
  _events[_next].type = type;
  _events[_next].object = object;
  _events[_next].section = section;
  _events[_next].start = start;
  if (_log)
    {
      for (unsigned short i = 0; i != *_indent; i++) std::cerr.put(' ');
      std::cerr << _events[_next] << std::endl;
    }
  _next++;
  if (_next == _events.size()) 
    {
      _next = 0;
      _wrapped = true;
    }

  // Adjust for time taken in this function, which may be lengthy due to
  // outputs to screen etc
  Time end_time = Time::currentTime();
  _start += (end_time - time);
  return ret;
}

void Tracer::dump(std::ostream &os)
{
  std::vector<Event>::iterator e;
  os << "* Tracer::dump =\n";
  if (_wrapped) for (e = _events.begin() + _next; e != _events.end(); e++) os << *e << '\n';
  for (e = _events.begin(); e != _events.begin() + _next; e++) os << *e << '\n';
  os << "* end of Tracer::dump" << std::endl; 
}
