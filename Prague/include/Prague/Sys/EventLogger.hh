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
#ifndef _EventLogger_hh
#define _EventLogger_hh

#include <vector>

class EventLogger
{
public:
  EventLogger(size_t s) : events(s), times(s), next(0), wrapflag(true), wrapped(false) {}
  ~EventLogger() {}
  void wrap(bool flag) { wrapflag = flag;}
  void add(const char *n, double t)
    {
      if (next == events.size()) return;
      events[next] = n;
      times[next] = t;
      next++;
      if (next == events.size() && wrapflag)
	{
	  next = 0;
	  wrapped = true;
	}
    }
  void clear() { next = 0; wrapped = false;}
  void dump(ostream &os)
    {
      vector<const char *>::iterator event;
      vector<double>::iterator time;
      os << "EventLogger::dump =\n";
      if (wrapped)
	for (event = events.begin() + next, time = times.begin() + next; event != events.end(); event++, time++)
	  os << *time << '\t' << *event << '\n';
      for (event = events.begin(), time = times.begin(); event != events.begin() + next; event++, time++)
	os << *time << '\t' << *event << '\n';
    }
private:
  vector<const char *> events;
  vector<double> times;
  unsigned int next;
  bool wrapflag : 1;
  bool wrapped  : 1;
};

#endif /* _EventLogger_hh */
