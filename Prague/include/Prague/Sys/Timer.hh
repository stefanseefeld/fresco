/*$Id$
 *
 * This file is part of OffiX,
 * a C++ API for the X Window System and Unix
 * Copyright (C) 1995-98  Stefan Seefeld
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
#ifndef _Timer_hh
#define _Timer_hh

#include <Prague/Sys/Time.hh>
#include <Prague/Sys/Thread.hh>

/* @Class{Timer}
 *
 * @Description{}
 */
class Timer : public Thread
{
public:
  struct Notifier { virtual ~Notifier(){}; virtual void notify() = 0;};
  Timer(Notifier *n) : notifier(n), repeat(false) {}
  virtual ~Timer() {}
  void  start(long, bool flag = false);
  void  start(const Time &);
  void stop();
//   void setInterval(long msec) { tint = msec;}
protected:
  virtual void execute(); 
private:
  bool running();
  bool sleep();
  Notifier *notifier;
  long tint;
  Time tout;
  bool repeat : 1;
  bool run :    1;
  Mutex mutex;
};

#endif /* _Timer_hh */
