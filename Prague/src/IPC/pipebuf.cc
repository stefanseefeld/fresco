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
#include "Prague/IPC/pipebuf.hh"
#include <unistd.h>

/* @Method{int pipebuf::open()}
 *
 * @Description{open the pipe and return the read or write end depending on the flag}
 */
int pipebuf::open()
{
  int fds[2];
  if (pipe(fds) < 0) return -1;
  if (fl & ios::out) {data->fd = fds[1]; return fds[0];}
  else  {data->fd = fds[0]; return fds[1];}
};
