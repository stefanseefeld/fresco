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
static char *rcsid = "$Id$";
#include "Prague/Sys/Timer.hh"

int Timer::count = 0;

/* @Method{Timer::~Timer()}
 *
 * @Description{}
 */
Timer::~Timer()
{
};

/* @Method{int Timer::start(long msec, bool repeat)}
 *
 * @Description{starts the Timer to produce a @code{timeout} in @var{msec} milliseconds
 @var{repeat} indicates whether this should produce timeouts @strong{every} @var{msec} milliseconds}
 */
int Timer::start(long msec, bool flag)
{
  id = ++count;
  repeat = flag;
  tint = msec;
//   AsyncManager *manager = AsyncManager::Instance();
  tout = Time::currentTime() + Time(msec);
//   manager->addTimeout(this, tout);
  return id;
};

/* @Method{int Timer::start(const Time &T)}
 *
 * @Description{start a Timer (single shot) to produce a timeout at absolute time T}
 */
int Timer::start(const Time &T)
{
  id = ++count;
  repeat = false;
//   AsyncManager *manager = AsyncManager::Instance();
//   manager->addTimeout(this, T);
  return id;
};

/* @Method name{void Timer::stop()}
 *
 * @Description{stops the Timer}
 */
void Timer::stop()
{
  id = 0;
  repeat = false;
};

/* @Method{void Timer::timeout()}
 *
 * @Description{broadcasts a @code{timeout} signal}
 */
void Timer::timeout()
{
  if (id)
    {
      if (repeat)
	{
	  tout += Time(tint);
// 	  AsyncManager *manager = AsyncManager::Instance();
// 	  manager->addTimeout(this, tout);
	}
      if (notifier) notifier->notify();
    }
};
