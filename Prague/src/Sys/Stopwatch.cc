/*$Id$
 *
 * This source file is a part of the Fresco Project.
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
#include "Prague/Sys/Stopwatch.hh"
#include <iostream>

#include <sys/times.h>
#include <unistd.h>
#include <cerrno>
#include <string>

using namespace Prague;

clock_t Stopwatch::_ticks = 0;

Stopwatch::Stopwatch() : _state(undef)
{
    if (!_ticks) _ticks = sysconf(_SC_CLK_TCK); // FIXME: This is not the POSIX way! -tobias
    start();
}

void Stopwatch::start() throw(std::runtime_error)
{
    _state = running;
    struct tms cpt;
    _real.begin = times(&cpt);
    _cpu.begin  = cpt.tms_utime;
    _sys.begin  = cpt.tms_stime;
    if (_real.begin == -1)
        throw std::runtime_error(std::string("Failed to start the Stopwatch: ") +
                                 strerror(errno));
}

void Stopwatch::stop() throw(std::runtime_error)
{
    _state = stopped;
    struct tms cpt;
    _real.end = times(&cpt);
    _cpu.end  = cpt.tms_utime;
    _sys.end  = cpt.tms_stime;
    if (_real.end == -1)
        throw std::runtime_error(std::string("Failed to stop the Stopwatch: ") +
                                 strerror(errno));
}

double Stopwatch::real_time()
{
    if (_state == undef) return 0.;
    else if (_state == running) stop();
    return (double) (_real.end - _real.begin)/_ticks;
}

double Stopwatch::cpu_time()
{
    if (_state == undef) return 0.;
    else if (_state == running) stop();
    return (double) (_cpu.end - _cpu.begin)/_ticks;
}

double Stopwatch::sys_time()
{
    if (_state == undef) return 0.;
    else if (_state == running) stop();
    return (double) (_sys.end - _sys.begin)/_ticks;
}
