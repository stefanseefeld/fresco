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
#include <Prague/IPC/ptybuf.hh>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>

inline char ctrl(char c) { return c & 0x1f;}

class ptybuf::backup
{
public:
  backup(int fd)
    {
      /*
      fstat(fd, &mode);
      tcgetattr (fd, &tios);
      uid = geteuid();
      gid = getegid();
      */
    };
  struct stat mode;
  struct termios tios;
  uid_t uid;
  gid_t gid;
};

/* @Method{ptybuf::ptybuf()}
 *
 * @Description{}
 */
ptybuf::ptybuf()
  : ipcbuf(ios::in|ios::out), save(0)
{
  ptydev[0] = ttydev[0] = '\0';
}

/* @Method{ptybuf::~ptybuf()}
 *
 * @Description{restore backup data}
 */
ptybuf::~ptybuf()
{
//   fclose(ptystream);
  if (save && fd() != -1)
    {
      /*
      seteuid(save->uid);
      setegid(save->gid);
      chmod(ptydev, save->mode.st_mode);
      chown(ptydev, save->mode.st_uid, save->mode.st_gid);
      tcsetattr (fd(), TCSANOW, &save->tios);
      */
    }
  delete save;
}

/* @Method{void ptybuf::setup()}
 *
 * @Description{prepare the stream}
 */
void ptybuf::setup()
{
//   ptystream = fdopen(fd(), "r+");
  if (!save) save = new backup(fd());
}

/* @Method{int ptybuf::open_master()}
 *
 * @Description{open the master side of the pty}
 */
/* @Method{int ptybuf::open_slave(int fd, const char *ptydev)}
 *
 * @Description{open the slave side of the pty. Since this is done from outside the class (after the fork), this is a static method}
 */
#ifdef __linux__ //_bsd_
#include "ptybuf.bsd44.cc"
#elif defined __sgi__ //_svr4_
#include "ptybuf.svr4.cc"
#else
#error sorry, ptybuf not yet implemented for this architecture
#endif