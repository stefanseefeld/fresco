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
#ifndef _pipebuf_hh
#define _pipebuf_hh
#include <Prague/IPC/ipcbuf.hh>

/* @Class{pipebuf : public ipcbuf}
 *
 * @Description{a ipcbuf based on a pipe}
 */
class pipebuf : public ipcbuf
{
public:
  pipebuf(int flag) : ipcbuf(flag), fl(flag) {}
  int open();
protected:
  int fl;
};

/* @Method{pipebuf::pipebuf(int mode)}
 * @Description{construct a pipebuf for reading, if @code{mode == ios::in}, writing otherwise}
 */

#endif /* _pipebuf_hh */