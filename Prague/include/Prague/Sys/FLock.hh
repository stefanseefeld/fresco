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
/* $Id$ */
#ifndef _FLock_hh
#define _FLock_hh

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream.h>

/* @Class{FLock}
 *
 * @Description{provide locking based on fcntl. Locks can be activated in read and in write mode.}
 */
class FLock
{
public:
  enum mode {read = F_RDLCK, write = F_WRLCK};
  FLock();
  FLock(const char *, bool = true);
  ~FLock();
  const char *Name() { return name.c_str();}
  bool trylock(mode m) { return doit(m, false) == 0;}
  bool lock(mode m) { return doit(m, true) == 0;}
  bool unlock() { return doit(F_UNLCK, false) == 0;}
  pid_t locked(mode m) const;
private:
  static const char *tmpname() { return ::tmpnam(0);}
  int doit(int, bool = false);
  string name;
  bool remove;
  int fd;
};

/* @Method{FLock::FLock()}
 *
 * Description{create a FLock using a temporary file}
 */
inline FLock::FLock()
  : name(tmpname()), remove(true)
{
  fd = open(name.c_str(), O_RDWR|O_CREAT, 0600);
  ::write(fd, "l", 1);
};

/* @Method{FLock::FLock(const char *name, bool create = true)}
 *
 * Description{create a FLock using file @var{name}, create if @var{create} is true}
 */
inline FLock::FLock(const char *n, bool create)
  : name(n), remove(false)
{
  if (create) fd = open(name.c_str(), O_RDWR|O_CREAT, 0600);
  else        fd = open(name.c_str(), O_RDWR, 0600);
  if (create) ::write(fd, "l", 1);
};

/* @Method{FLock::~FLock()}
 *
 * Description{close the associated file, removes it if is a temporary one.}
 */
inline FLock::~FLock()
{
  close(fd);
  if (remove) ::remove(name.c_str());
};

/* @Method{bool FLock::lock(FLock::mode m)}
 *
 * Description{try to activate the lock for mode @var{m}, return @var{true} if it successful}
 */
/* @Method{bool FLock::lock(FLock::mode m)}
 *
 * Description{same as @var{lock()} but block if the lock is already active untill it is released}
 */
inline int FLock::doit(int type, bool flag)
{
  struct flock lock;
  lock.l_type  = type;
  lock.l_len   = 1;
  lock.l_start = 0;
  lock.l_whence = SEEK_SET;
  return fcntl(fd, flag ? F_SETLKW : F_SETLK, &lock);
};

/* @Method{pid_t FLock::locked(FLock::mode m)}
 *
 * Description{return the ID of the process currently holding the lock or 0.}
 */
inline pid_t FLock::locked(mode m) const
{
  struct flock lock;
  lock.l_type  = m;
  lock.l_len   = 1;
  lock.l_start = 0;
  lock.l_whence = SEEK_SET;
  if (fcntl(fd, F_GETLK, &lock) < 0);// throw
  return lock.l_type == F_UNLCK ? 0 : lock.l_pid;
};

#endif /* _FLock_hh */
