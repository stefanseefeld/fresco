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
#ifndef _bzbuf_hh
#define _bzbuf_hh

#include <streambuf>
#include <cstdio>
extern "C" 
{
#include <bzlib.h>
}

namespace Prague
{

/* @Class {bzbuf : public streambuf}
 *
 * @Description {filter using bzip2 library}
 */
class bzbuf : public std::streambuf, private bz_stream
{
public:
  typedef char           char_type;
  typedef std::streampos pos_type;
  typedef std::streamoff off_type;
  typedef int            int_type;
  bzbuf(std::streambuf *, int);
  virtual ~bzbuf();
  virtual int sync();
protected:
  virtual int_type underflow();
  virtual int_type uflow();
  virtual int_type overflow(int = EOF);
  char_type  *cbase() const { return my_comp;}
  char_type  *ecptr() const { return my_comp + BUFSIZ;}
  char_type  *cin() const { return next_in + avail_in;}
  char_type  *cout() const { return my_pout;}
private:
  char_type      *my_comp;
  char_type      *my_pout;
  std::streambuf *my_back;
};

};

#endif /* _bzbuf_h */
