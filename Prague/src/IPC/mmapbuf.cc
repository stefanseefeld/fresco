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
#include "Prague/IPC/mmapbuf.hh"

using namespace Prague;

mmapbuf::mmapbuf (int fd)
  : mmap(fd), lock(fd)
{
//   data = new control;
//   if (mode & ios::in)
//     {
//       char_type *gbuf = new char_type [BUFSIZ];
//       setg (gbuf, gbuf + BUFSIZ, gbuf + BUFSIZ);
//       data->gend = gbuf + BUFSIZ;
//     }
//   if (mode & ios::out)
//     {
//       char_type *pbuf = new char_type [BUFSIZ];
//       setp (pbuf, pbuf + BUFSIZ);
//       data->pend = pbuf + BUFSIZ;
//     }
}

mmapbuf::~mmapbuf ()
{
//   overflow (EOF); // flush write buffer
//   if (--data->count) return;
//   delete [] pbase ();
//   delete [] eback ();
//   if (fd() != -1 && close (fd()) == -1) perror("mmapbuf::~mmapbuf");
//   delete data;
}

bool mmapbuf::readready () const
{
//   FdSet fds;
//   fds.set(fd());
//   Time T;
//   if (select (fds.max() + 1, fds, 0, 0, &T) == 0) return true;
  return false;
}

bool mmapbuf::writeready () const
{
//   FdSet fds;
//   fds.set(fd());
//   Time T;
//   if (select (fds.max() + 1, 0, fds, 0, &T) == 0) return true;
  return false;
}

bool mmapbuf::exceptionpending () const
{
//   FdSet fds;
//   fds.set(fd());
//   Time T;
//   if (select(fds.max() + 1, 0, 0, fds, &T) == 0) return true;
  return false;
}

void mmapbuf::setnonblocking (bool flag)
{
//   int flags = fcntl(fd(), F_GETFL);
//   if (flag) flags |= O_NONBLOCK;
//   else flags &= ~(O_NONBLOCK);
//   fcntl(fd(), F_SETFL, flags);
}

bool mmapbuf::nonblocking () const
{
//   int flags = fcntl(fd(), F_GETFL);
//   return flags | O_NONBLOCK;
  return false;
}

int mmapbuf::sync()
{
//   if (pptr () && pbase () < pptr () && pptr () <= epptr ())
//     {
//       write (pbase (), pptr () - pbase ());
//       setp (pbase (), (char *) data->pend);
//     }
  return 0;
}

int mmapbuf::showmanyc () const
{
//   if (gptr () && gptr () < egptr ()) return egptr () - gptr ();
  return 0;
}

mmapbuf::int_type mmapbuf::overflow (int c)
{
//   if (pbase () == 0) return EOF;
//   if (c == EOF) return sync();
//   if (pptr () == epptr ()) sync ();
//   *pptr () = (char_type) c;
//   pbump (1);
//   return c;
  return EOF;
}

mmapbuf::int_type mmapbuf::underflow ()
{
//   if (gptr () == 0) return EOF; // input stream has been disabled
//   if (gptr () < egptr ()) return (unsigned char) *gptr (); // EOF is a -ve number; make it unsigned to be diff from EOF
//   int rlen = read (eback (), data->gend - eback ());
//   switch (rlen)
//     {
//     case 0: data->eofbit = true;
//     case EOF: return EOF;
//     default:
//       setg (eback (), eback (), eback () + rlen);
//       return (unsigned char) *gptr ();
//     }
  return EOF;
}

mmapbuf::int_type mmapbuf::uflow ()
{
//   int_type ret = underflow ();
//   if (ret == EOF) return EOF;
//   gbump(1);
//   return ret;
  return EOF;
}

mmapbuf::int_type mmapbuf::pbackfail (int c)
{
  return EOF;
}

streamsize mmapbuf::xsputn (const mmapbuf::char_type *s, streamsize n)
{
//   int wval = epptr () - pptr ();
//   if (n <= wval)
//     {
//       memcpy (pptr (), s, n * sizeof (char_type));
//       pbump (n);
//       return n;
//     }
//   memcpy (pptr (), s, wval * sizeof (char_type));
//   pbump (wval);
//   if (overflow() != EOF) return wval + xsputn (s + wval, n - wval);
//   return wval;
  return 0;
}

streamsize mmapbuf::xsgetn (mmapbuf::char_type *s, streamsize n)
{
//   int rval = showmanyc ();
//   if (rval >= n)
//     {
//       memcpy (s, gptr (), n * sizeof (char_type));
//       gbump (n);
//       return n;
//     }
//   memcpy (s, gptr (), rval * sizeof (char_type));
//   gbump (rval);
//   if (underflow () != EOF) return rval + xsgetn (s + rval, n - rval);
//   return rval;
  return 0;
}

int mmapbuf::write(const void *buf, int len)
{
//   if (!writeready ()) return 0;
//   int wlen = 0;
//   while(len > 0)
//     {
//       int wval = ::write (fd(), (char*) buf, len);
//       if (wval == -1 && errno == EAGAIN) return EOF;
//       else if (wval == -1) perror("mmapbuf::write");
//       len -= wval;
//       wlen += wval;
//     }
//   return wlen; // == len if every thing is all right
  return 0;
}

int mmapbuf::read (void *buf, int len)
{
//   if (!readready ()) return 0;  
//   int rval = ::read (fd(), (char *)buf, len);
//   if (rval == -1 && errno != EAGAIN) perror("mmapbuf::read");
//   return rval;
  return 0;
}
