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
#ifndef _Prague_MMap_hh
#define _Prague_MMap_hh

#include <unistd.h>
#include <sys/mman.h>
#include <string>
#include <stdexcept>

namespace Prague
{

  //. a convenience wrapper around the mmap family of functions
  class MMap
  {
    public:
      enum protection_t
      {
          none = PROT_NONE, read = PROT_READ, write = PROT_WRITE, exec = PROT_EXEC
      };
      enum map_t
      {
          fixed = MAP_FIXED, shared = MAP_SHARED, priv = MAP_PRIVATE
      };
      MMap(int, int = -1, int = read|write,
           int = priv, void * = 0, off_t = 0) throw(std::runtime_error);
      MMap(const std::string &, int = -1, int = read|write,
           int = priv, void * = 0, off_t = 0) throw(std::runtime_error);
      ~MMap();
      //. return the base address
      void *addr() const { return _base; }
      //. return the size
      size_t size() const { return _length; }
      //. synchronize the memory with the associated file
      void sync(ssize_t = -1, bool = true);
      //. synchronize the memory with the associated file
      void sync(void *, size_t, bool = true);
      //. protect the memory
      void protect(ssize_t = -1, int = read|write);
      //. protect the memory
      void protect(void *, size_t, int = read|write);
    private:
      MMap(const MMap &);
      void  *_base;
      size_t _length;
  };

} // namespace

#endif
