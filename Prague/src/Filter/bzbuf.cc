/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
 *
 * this file defines a C++ interface to zlib
 * written by Kevin Ruland <kevin@rodin.wustl.edu>
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
#include "Prague/Filter/bzbuf.hh"
#include <iostream>

using namespace Prague;

bzbuf::bzbuf(std::streambuf *b, int mode)
  : my_comp(new char_type [BUFSIZ]), my_back(b)
{
  char_type *buf = new char_type[BUFSIZ];
  if (mode & std::ios::in)
    {
      setg (buf, buf + BUFSIZ, buf + BUFSIZ);
      next_in = my_comp;
      avail_in = BUFSIZ;
      my_pout = eback();
    }
  else if (mode & std::ios::out)
    {
      setp (buf, buf + BUFSIZ);
      next_out = my_comp;
      avail_out = BUFSIZ;
      my_pout = pbase();
    }
  bzalloc = 0;
  bzfree = 0;
  opaque = 0;
  int blocksize = 9;
  int verbosity = 4;
  int workFactor = 30;
  int small = 0;
  if (mode &= std::ios::out)
    int ret = BZ2_bzCompressInit(this, blocksize, verbosity, workFactor);
  else
    int ret = BZ2_bzDecompressInit(this, verbosity, small);
}

bzbuf::~bzbuf()
{
  overflow(EOF);
  if (pbase())
    {
      bool done;
      do
	{
	  done = BZ2_bzCompress(this, BZ_FINISH) == BZ_STREAM_END;
	  if (avail_out) my_pout = next_out;
	  else
	    {
	      my_pout = next_out = cbase();
	      avail_out = BUFSIZ;
	    }
	  std::streamsize l = next_out - cout();//comp + BUFSIZ - next_out;
	  if (l) l = my_back->sputn(cout(), l);
	  next_out -= l;
	  avail_out += l;
	}
      while (!done);
      BZ2_bzCompressEnd(this);
      delete [] pbase();
    }
  else delete [] eback();
  delete [] my_comp;
  my_back->pubsync();
}

int bzbuf::sync()
{
  if (pptr() && avail_in)
    {
      BZ2_bzCompress(this, BZ_RUN);
      if (cin() == epptr()) next_in = pbase();
      setp (cin(), epptr());
      
      std::streamsize l = next_out - cout();
      /*
       * what if sputn returns less than l ???
       */
      if (l) l = my_back->sputn(cout(), l);
      my_pout += l;
      if (avail_out) my_pout = next_out;
      else
	{
	  my_pout = next_out = cbase();
	  avail_out = BUFSIZ;
	}
    }
  return 0;
}

bzbuf::int_type bzbuf::overflow (int c)
{
  if (pbase() == 0) return EOF;
  if (c == EOF) return sync();
  if (pptr() == epptr()) sync();
  *pptr() = (char_type) c;
  pbump(1);
  avail_in++;
  return c;
}

bzbuf::int_type bzbuf::underflow ()
{
  if (gptr() == 0) return EOF;
  if (gptr() < next_out) return (unsigned char) *gptr();
  if (!avail_out)
    {
      next_out = eback();
      avail_out = egptr() - eback();
    }
  if (!avail_in)
    {
      if (cin() == ecptr()) next_in = cbase();
      std::streamsize l = my_back->sgetn(cin(), ecptr() - cin());
      if (l == EOF) return EOF;
      avail_in += l;
    }
  BZ2_bzDecompress(this);  
  setg (cout(), cout(), next_out);
  return (unsigned char) *gptr();
}

/* @Method{bzbuf::int_type ipcbuf::uflow ()}
 *
 * @Description{}
 */
bzbuf::int_type bzbuf::uflow ()
{
  int_type ret = underflow ();
  if (ret == EOF) return EOF;
  gbump(1);
  my_pout++;
  return ret;
}
