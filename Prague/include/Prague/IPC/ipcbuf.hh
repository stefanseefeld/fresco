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
#ifndef _ipcbuf_hh
#define _ipcbuf_hh

#include <streambuf.h>

/* @Class{ipcbuf : public streambuf}
 *
 * @Description{ipcbuf is a streambuffer for inter process communication, i.e. pipes, sockets, ptys. The low level reading/writing is based on file descriptors. The difference between an ipcbuf and a normal filebuf is the meaning of EOF: in the context of IPC an EOF means that the connection is closed. This case is not handled by the stream but by the corresponding Agent. If the ipcbuf is in nonblocking mode, it returns eof if the underlying read/write causes an EAGAIN error (operation would block). If a real EOF is encountered, a flag is set so the corresponding agent may terminate the process (or reestablish the connection...)}
 */
class ipcbuf : public streambuf
{
public:
  typedef char          char_type;
  typedef streampos     pos_type;
  typedef streamoff     off_type;
  typedef int           int_type;
  typedef ios::seek_dir seekdir;

  ipcbuf(int);
  ipcbuf(const ipcbuf &);
  virtual ~ipcbuf();
  ipcbuf &operator = (const ipcbuf &);
  bool readready() const;
  bool writeready() const;
  bool exceptionpending() const;
  int write (const void *, int);
  int read (void *, int);
  int fd() const { return data->fd;}
  void setnonblocking(bool flag = true);
  bool nonblocking() const;
  bool eof() const { return data->eofbit;}
protected:
  struct control
  {
    control() : fd(-1), count(1), stmo (-1), rtmo (-1), oobbit(false), eofbit(false), gend (0), pend (0) {}
    int	fd;
    int	count;
    int stmo;        // -1==block, 0==poll, >0 == waiting time in secs
    int rtmo;        // -1==block, 0==poll, >0 == waiting time in secs
    bool oobbit : 1; // check for out-of-band byte while reading
    bool eofbit : 1; // connection closed
    char_type *gend; // end of input buffer
    char_type *pend; // end of output buffer
  };
  control *data;  // counts the # refs to sock
  virtual int        sync ();
  virtual int        showmanyc () const;
  virtual int_type   overflow (int c = EOF);
  virtual int_type   underflow ();
  virtual int_type   uflow ();
  virtual int_type   pbackfail (int c = EOF);
  virtual streamsize xsputn (const char *, streamsize);
  virtual streamsize xsgetn (char *, streamsize);
private:
};

#endif /* _ipcbuf_hh */