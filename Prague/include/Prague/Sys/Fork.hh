/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org>
 * http://www.fresco.org
 *
 * this file is based on code from the socket++ library
 * Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
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

#ifndef _Prague_Fork_hh
#define _Prague_Fork_hh

#include <Prague/Sys/Signal.hh>
#include <unistd.h>
#include <sys/types.h>

namespace Prague
{

  //. Fork encapsulates the housekeeping associated with the fork() system call
  class Fork
  {
      struct Process;
    public:
      Fork (bool = false, bool = false);
      ~Fork();
      //. return whether this is the child process
      bool child() const;
      //. return whether this is the parent process
      bool parent() const;
      //. return the child process id
      pid_t pid() const;
      //. commit suicide at the signal signo
      static void suicide_on_signal(Signal::type signo = Signal::terminate);
    private:
      Process *process;
      Fork (const Fork &);
      Fork &operator = (const Fork &);
  };

} // namespace

#endif
