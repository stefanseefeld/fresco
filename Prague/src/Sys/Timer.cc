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
#include "Prague/Sys/Timer.hh"

using namespace Prague;

/* @Method{void Timer::start(long msec, bool repeat)}
 *
 * @Description{starts the Timer to produce a @code{timeout} in @var{msec} milliseconds
 @var{repeat} indicates whether this should produce timeouts @strong{every} @var{msec} milliseconds}
 */
void Timer::start(long msec, bool flag)
{
  {
    MutexGuard guard(mutex);
    repeat = flag;
    tint = msec;
    tout = Time::currentTime() + Time(msec);
    run = true;
  }
  Thread::start();
};

/* @Method{void Timer::start(const Time &T)}
 *
 * @Description{start a Timer (single shot) to produce a timeout at absolute time T}
 */
void Timer::start(const Time &time)
{
  {
    MutexGuard guard(mutex);
    repeat = false;
    run = true;
  }
  Thread::start();
};

/* @Method{void Timer::stop()}
 *
 * @Description{stops the Timer}
 */
void Timer::stop()
{
  MutexGuard guard(mutex);
  run = false;
};

void Timer::execute()
{
  do
    if (sleep() && notifier) notifier->notify();
  while (repeat && running());
}

bool Timer::running()
{
  MutexGuard guard(mutex);
  return run;
}

bool Timer::sleep()
{
  {
    MutexGuard guard(mutex);
    tout += tint;
  }
  Thread::delay(tout - Time::currentTime());
  {
    MutexGuard guard(mutex);
    return run;
  }
}
