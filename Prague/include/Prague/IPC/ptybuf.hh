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
#ifndef _ptybuf_hh
#define _ptybuf_hh

#include <Prague/IPC/ipcbuf.hh>
#include <string>

/* @Class{ptybuf : public ipcbuf}
 *
 * @Description{a streambuf which uses a pty for communication. Reading is done via fgets since tty use line buffered mode normally.}
 */
class ptybuf : public ipcbuf
{
  class backup;
public:
  ptybuf();
  virtual ~ptybuf();
  const string &name() const { return ptydev;}
  int openpty();
  int opentty();
  void setup();
protected:
  string ptydev;
  string ttydev;
private:
  backup *save;
};

#endif /* _ptybuf_hh */
