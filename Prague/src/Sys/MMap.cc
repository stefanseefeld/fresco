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

#ifdef sun
#define _XPG4_2
#endif

#include "Prague/Sys/MMap.hh"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <cerrno>
#include <cstdio>
#include <cstring>

using namespace Prague;

MMap::MMap(int fd, int l, int prot, int share, void *addr, off_t offset) throw(std::runtime_error) :
  _base(MAP_FAILED),
  _length(0)
{
    struct stat sb;
    _length = l > -1 ? l : fstat(fd, &sb) == -1 ? -1 : sb.st_size;
    if (l > static_cast<int>(_length))
    {
        _length = l;
        ftruncate(fd, _length);
    }
    else if (l > 0 && l < static_cast<int>(_length)) _length = l;
    _base = mmap(addr, _length, prot, share, fd, offset);
    if (_base == MAP_FAILED) throw std::runtime_error(strerror(errno));
}

MMap::MMap(const std::string &filename, int l, int prot, int share, void *addr, off_t offset) throw(std::runtime_error) :
  _base(MAP_FAILED),
  _length(0)
{
    int fd = -1;
    if (prot == read) fd = open(filename.c_str(), O_RDONLY);
    else fd = open(filename.c_str(), O_RDWR|O_CREAT, 0666);

    if (fd == -1)
    {
          std::string message = "Failed to map \"" + filename + "\": " +
                                strerror(errno);
          throw std::runtime_error(message);
    }
    struct stat sb;
    _length = fstat(fd, &sb) == -1 ? -1 : sb.st_size;
    if (l > static_cast<int>(_length))
    {
        _length = l;
        ftruncate(fd, _length);
    }
    else if (l > 0 && l < static_cast<int>(_length)) _length = l;
    _base = mmap(addr, _length, prot, share, fd, offset);
    if (_base == MAP_FAILED)
    {
        std::string message = "Failed to map \"" + filename + "\": " +
                              strerror(errno);
        throw std::runtime_error(message);
    }
    close(fd);
}

MMap::~MMap() { if (_base != MAP_FAILED) munmap(_base, _length); }
void MMap::sync(ssize_t len, bool wait) { msync(_base, len < 0 ? _length : len, wait ? MS_SYNC : MS_ASYNC); }
void MMap::sync(void *addr, size_t len, bool wait) { msync(addr, len, wait ? MS_SYNC : MS_ASYNC); }
void MMap::protect(ssize_t len, int prot) { mprotect(_base, len < 0 ? _length : len, prot); }
void MMap::protect(void *addr, size_t len, int prot) { mprotect(addr, len, prot); }
