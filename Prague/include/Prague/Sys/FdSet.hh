/* $Id$
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
#ifndef _FdSet_hh
#define _FdSet_hh

#include <sys/time.h>
#include <sys/types.h>
#include <cstring> // some platforms seem to need this (solaris, bsd)
#include <cassert>

#undef isset // *sigh* -stefan

namespace Prague
{

  //. FdSet is a helper class used when selecting available fds for non-blocking i/o
  class FdSet
  {
    public:
      FdSet() : my_m(-1) { FD_ZERO(&my_fds); }
      FdSet(const FdSet &F) : my_fds(F.my_fds), my_m(F.my_m) { }
      ~FdSet() { }
      FdSet &operator = (const FdSet &F) { my_fds = F.my_fds; my_m = F.my_m; return *this; }
      //. Add a fd to the set
      void set(int fd) { assert(fd >= 0); FD_SET(fd, &my_fds); if (fd > my_m) my_m = fd; }
      //. return whether the given fd is available for non-blocking i/o
      bool isset(int fd) const { assert(fd >= 0); return FD_ISSET(fd, &my_fds); }
      //. clear fd from the set
      void clear(int fd)
      {
          FD_CLR(fd, &my_fds);
          if (fd == my_m)
              for (int i = fd - 1; i >= 0; --i)
                  if (isset(i))
                  {
                      my_m = i;
                      break;
                  }
      }
      //. return max fd
      int max() const { return my_m; }
      operator fd_set *() { return &my_fds; }
    protected:
      fd_set my_fds;
      int my_m;
  };

} // namespace

#endif
