/*+P
 * This file is part of OffiX,
 * a C++ API for the X Window System and Unix
 *
 * this file defines a C++ interface to zlib
 * written by Kevin Ruland <kevin@rodin.wustl.edu>
 * modified by Stefan Seefeld
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
#ifndef _gzbuf_h
#define _gzbuf_h

#include <streambuf.h>
#include "zlib.h"

class gzbuf : public streambuf
{
public:
  gzbuf();
  virtual ~gzbuf();
  gzbuf *open(const char *, int);
  gzbuf *attach(int, int);
  gzbuf *close();
  int setcompressionlevel(short);
  int setcompressionstrategy(short);
  int is_open() const {return file != 0;}
  virtual streampos seekoff(streamoff, ios::seek_dir, int);
  virtual int sync();
protected:
  virtual int underflow();
  virtual int overflow(int = EOF);
private:
  gzFile file;
  short mode;
  bool fd_owner;
  int flushbuf();
  int fillbuf();
};

#endif /* _gzbuf_h */















