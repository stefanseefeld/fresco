/*+P
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
 -P*/
/*$Id$*/
#ifndef _Timer_hh
#define _Timer_hh

#include <Prague/Sys/Time.hh>

/* @Class{Timer}
 *
 * @Description{}
 */
class Timer
{
public:
  struct Notifier { virtual ~Notifier(){}; virtual void notify() = 0;};
  Timer(Notifier *n) : notifier(n), repeat(false) {}
  ~Timer();
  bool active() const { return id != 0;}
  int  start(long, bool flag = false);
  int  start(const Time &);
  void stop();
  void setInterval(long msec) { tint = msec;}
protected:
  void timeout();
private:
  Notifier *notifier;
  static int count;
  int id;
  long tint;
  Time tout;
  bool repeat;
};

#endif /* _Timer_hh */
