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
#ifndef _Prague_Process_hh
#define _Prague_Process_hh

#include <cstdio>
#include <cerrno>
#include <stdexcept>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

namespace Prague
{

  //. provide process information
  class Process
  {
    public:
      Process() { update(); }
      ~Process() { }
      double cpu() const { return 0.; }
      long memory() const { return _usage.ru_idrss; }
      void update() throw(std::runtime_error)
      {
          if (getrusage(RUSAGE_SELF, &_usage) == -1)
              throw std::runtime_error("Process::update: " + strerror(errno));
      }
      //. return the process' id
      static pid_t id() { return getpid(); }
    private:
      rusage _usage;
  };

} // namespace

#endif
