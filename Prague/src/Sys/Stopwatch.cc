/*$Id$
 *
 * This source file is a part of the Berlin Project.
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
#include "Prague/Sys/Stopwatch.hh"
#include <iostream>

#include <sys/times.h>
#include <stdio.h>
#include <unistd.h>

using namespace Prague;

clock_t Stopwatch::_ticks = 0;

Stopwatch::Stopwatch()
  : s(undef)
{
  if (!_ticks) _ticks = CLK_TCK;
  start();
};

void Stopwatch::start()
{
  s = running;
  struct tms cpt;
  _real.begin = times(&cpt);
  _cpu.begin  = cpt.tms_utime;
  _sys.begin  = cpt.tms_stime;
  if (_real.begin == -1) perror("Stopwatch::start");
};

void Stopwatch::stop()
{
  s = stopped;
  struct tms cpt;
  _real.end = times(&cpt);
  _cpu.end  = cpt.tms_utime;
  _sys.end  = cpt.tms_stime;
  if (_real.end == -1) perror("Stopwatch::stop");
};

double Stopwatch::real_time()
{
  if (s == undef) cerr << "Stopwatch::realTime: no starting point set" << endl;
  else if (s == running) stop();
  return (double) (_real.end - _real.begin)/ticks;
};

double Stopwatch::cpu_time()
{
  if (s == undef) cerr << "Stopwatch::cpuTime: no starting point set" << endl;
  else if (s == running) stop();
  return (double) (_cpu.end - _cpu.begin)/ticks;
};

double Stopwatch::sys_time()
{
  if (s == undef) cerr << "Stopwatch::sysTime: no starting point set" << endl;
  else if (s == running) stop();
  return (double) (_sys.end - _sys.begin)/ticks;
};
