/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
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
#include "Prague/IPC/ipcbuf.hh"
#include "Prague/Sys/FdSet.hh"
#include "Prague/Sys/Time.hh"
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>
#include <stdio.h>

using namespace Prague;

/* @Method{ipcbuf::ipcbuf(int mode)}
 *
 * @Description{}
 */
ipcbuf::ipcbuf (int mode)
{
  data = new control;
  if (mode & ios::in)
    {
      char_type *gbuf = new char_type [BUFSIZ];
      setg (gbuf, gbuf, gbuf + BUFSIZ);
      data->gend = gbuf + BUFSIZ;
    }
  if (mode & ios::out)
    {
      char_type *pbuf = new char_type [BUFSIZ];
      setp (pbuf, pbuf + BUFSIZ);
      data->pend = pbuf + BUFSIZ;
    }
}

/* @Method{ipcbuf::ipcbuf(const ipcbuf &ipc)}
 *
 * @Description{}
 */
ipcbuf::ipcbuf (const ipcbuf &ipc)
  : streambuf(ipc), data(ipc.data)
{
  data->count++;
}

/* @Method{ipcbuf::~ipcbuf()}
 *
 * @Description{}
 */
ipcbuf::~ipcbuf ()
{
  overflow (EOF); // flush write buffer
  if (--data->count) return;
  delete [] pbase ();
  delete [] eback ();
  if (fd() != -1 && close (fd()) == -1) perror("ipcbuf::~ipcbuf");
  delete data;
}

/* @Method{ipcbuf &ipcbuf::operator = (const ipcbuf &ipc)}
 *
 * @Description{}
 */
ipcbuf &ipcbuf::operator = (const ipcbuf &ipc)
{
  if (this != &ipc && data != ipc.data && data->fd != ipc.data->fd)
    {
      streambuf::operator = (ipc);
      this->ipcbuf::~ipcbuf();
      // the streambuf::operator = (const streambuf&) is assumed
      // to have handled pbase () and gbase () correctly.
      data  = ipc.data;
      data->count++;
    }
  return *this;
}

/* @Method{bool ipcbuf::readready() const}
 *
 * @Description{}
 */
bool ipcbuf::readready () const
{
  FdSet fds;
  fds.set(fd());
  Time T;
  if (select (fds.max() + 1, fds, 0, 0, &T) == 0) return true;
  return false;
}

/* @Method{bool ipcbuf::writeready() const}
 *
 * @Description{}
 */
bool ipcbuf::writeready () const
{
  FdSet fds;
  fds.set(fd());
  Time T;
  if (select (fds.max() + 1, 0, fds, 0, &T) == 0) return true;
  return false;
}

/* @Method{bool ipcbuf::exceptionpending() const}
 *
 * @Description{}
 */
bool ipcbuf::exceptionpending () const
{
  FdSet fds;
  fds.set(fd());
  Time T;
  if (select(fds.max() + 1, 0, 0, fds, &T) == 0) return true;
  return false;
}

/* @Method{void ipcbuf::setnonblocking(bool flag)}
 *
 * @Description{set the buffer to nonblocking mode if @var{flag} is true, to blocking mode otherwise}
 */
void ipcbuf::setnonblocking (bool flag)
{
  int flags = fcntl(fd(), F_GETFL);
  if (flag) flags |= O_NONBLOCK;
  else flags &= ~(O_NONBLOCK);
  fcntl(fd(), F_SETFL, flags);
}

/* @Method{bool ipcbuf::nonblocking() const}
 *
 * @Description{return true if the buffer is in nonblocking mode, false otherwise}
 */
bool ipcbuf::nonblocking () const
{
  int flags = fcntl(fd(), F_GETFL);
  return flags | O_NONBLOCK;
}

/* @Method{int ipcbuf::sync()}
 *
 * @Description{}
 */
int ipcbuf::sync()
{
  if (pptr () && pbase () < pptr () && pptr () <= epptr ())
    {
      write (pbase (), pptr () - pbase ());
      setp (pbase (), (char *) data->pend);
    }
  return 0;
}

/* @Method{int ipcbuf::showmanyc () const}
 *
 * @Description{return the number of chars in the input sequence}
 */
int ipcbuf::showmanyc () const
{
  if (gptr () && gptr () < egptr ()) return egptr () - gptr ();
  return 0;
}

/* @Method{ipcbuf::int_type ipcbuf::overflow (int c) const}
 *
 * @Description{if pbase () == 0, no write is allowed and thus return EOF. if c == EOF, we sync the output and return 0. if pptr () == epptr (), buffer is full and thus sync the output, insert c into buffer, and return c.}
 */
ipcbuf::int_type ipcbuf::overflow (int c)
{
  if (pbase () == 0) return EOF;
  if (c == EOF) return sync();
  if (pptr () == epptr ()) sync ();
  *pptr () = (char_type) c;
  pbump (1);
  return c;
}

/* @Method{ipcbuf::int_type ipcbuf::underflow ()}
 *
 * @Description{}
 */
ipcbuf::int_type ipcbuf::underflow ()
{
  if (gptr () == 0) return EOF; // input stream has been disabled
  if (gptr () < egptr ()) return (unsigned char) *gptr (); // EOF is a -ve number; make it unsigned to be diff from EOF
  int rlen = read (eback (), data->gend - eback ());
  switch (rlen)
    {
    case 0: data->eofbit = true;
    case EOF: return EOF;
    default:
      setg (eback (), eback (), eback () + rlen);
      return (unsigned char) *gptr ();
    }
}

/* @Method{ipcbuf::int_type ipcbuf::uflow ()}
 *
 * @Description{}
 */
ipcbuf::int_type ipcbuf::uflow ()
{
  int_type ret = underflow ();
  if (ret == EOF) return EOF;
  gbump(1);
  return ret;
}

/* @Method{ipcbuf::int_type ipcbuf::pbackfail (int c)}
 *
 * @Description{}
 */
ipcbuf::int_type ipcbuf::pbackfail (int c)
{
  return EOF;
}

/* @Method{streamsize ipcbuf::xsputn (const ipcbuf::char_type *s, streamsize n)}
 *
 * @Description{}
 */
streamsize ipcbuf::xsputn (const ipcbuf::char_type *s, streamsize n)
{
  int wval = epptr () - pptr ();
  if (n <= wval)
    {
      memcpy (pptr (), s, n * sizeof (char_type));
      pbump (n);
      return n;
    }
  memcpy (pptr (), s, wval * sizeof (char_type));
  pbump (wval);
  if (overflow() != EOF) return wval + xsputn (s + wval, n - wval);
  return wval;
}

/* @Method{streamsize ipcbuf::xsgetn (ipcbuf::char_type *s, streamsize n)}
 *
 * @Description{}
 */
streamsize ipcbuf::xsgetn (ipcbuf::char_type *s, streamsize n)
{
  int rval = showmanyc ();
  if (rval >= n)
    {
      memcpy (s, gptr (), n * sizeof (char_type));
      gbump (n);
      return n;
    }
  memcpy (s, gptr (), rval * sizeof (char_type));
  gbump (rval);
  if (underflow () != EOF) return rval + xsgetn (s + rval, n - rval);
  return rval;
}

/* @Method{int ipcbuf::write(const void *buf, int len)}
 *
 * @Description{}
 */
int ipcbuf::write(const void *buf, int len)
{
//   if (!writeready ()) return 0;
  int wlen = 0;
  while(len > 0)
    {
      int wval = ::write (fd(), (char*) buf, len);
      if (wval == -1 && errno == EAGAIN) return EOF;
      else if (wval == -1) perror("ipcbuf::write");
      len -= wval;
      wlen += wval;
    }
  return wlen; // == len if every thing is all right
}

/* @Method{int ipcbuf::read(void *buf, int len)}
 *
 * @Description{}
 */
int ipcbuf::read (void *buf, int len)
{
//   if (!readready ()) return 0;  
  int rval = ::read (fd(), (char *)buf, len);
  if (rval == -1 && errno != EAGAIN) perror("ipcbuf::read");
  return rval;
}
