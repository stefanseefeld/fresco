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

#include "Prague/Sys/MMap.hh"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

MMap::MMap(int fd, int l, int prot, int share, void *addr, off_t offset)
  : base(MAP_FAILED), length(l)
{
  struct stat sb;
  if (l == -1) length = fstat(fd, &sb) == -1 ? -1 : sb.st_size;
  base = mmap(addr, length, prot, share, fd, offset);
}

MMap::MMap(const string &filename, int l, int prot, int share, void *addr, off_t offset)
  : base(MAP_FAILED), length(l)
{
  int fd = open(filename.c_str(), O_RDWR|O_CREAT, 0666);
  struct stat sb;
  if (l == -1) length = fstat(fd, &sb) == -1 ? -1 : sb.st_size;
  base = mmap(addr, length, prot, share, fd, offset);
  close(fd);
}

MMap::~MMap() { if (base != MAP_FAILED) munmap(base, length);}
void MMap::sync(ssize_t len, bool wait) { msync(base, len < 0 ? length : len, wait ? MS_SYNC : MS_ASYNC);}
void MMap::sync(void *addr, size_t len, bool wait) { msync(addr, len, wait ? MS_SYNC : MS_ASYNC);}
void MMap::protect(ssize_t len, int prot) { mprotect(base, len < 0 ? length : len, prot);}
void MMap::protect(void *addr, size_t len, int prot) { mprotect(addr, len, prot);}
