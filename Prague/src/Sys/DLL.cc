/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Prague/config.hh"
#include "Prague/Sys/DLL.hh"
#if defined(HAVE_DLFCN)
#include <dlfcn.h>
#elif defined(HAVE_DLAIX)
#include <dl.h>
#endif

using namespace Prague;

DLL::DLL(const std::string &name, bool now) throw(std::runtime_error, std::logic_error)
  : _name(name)
{
  if (!_name.empty())
    {
#if defined(HAVE_DLFCN)
      int flags = now ? RTLD_NOW : RTLD_LAZY;
      flags |= RTLD_GLOBAL;
      _handle = dlopen(_name.c_str(), flags);
      if (!_handle) throw std::runtime_error(dlerror());
#elif defined(HAVE_DLAIX)
      shl_t shl_handle = shl_load (_name.c_str(), (now ? BIND_DEFERRED : BIND_IMMEDIATE) | BIND_NONFATAL | BIND_VERBOSE, 0);
      if (!shl_handle) throw std::runtime_error(strerror(errno));
      else _handle = shl_handle;
#endif
    }
  else throw std::logic_error("empty filename");
}

DLL::~DLL() throw()
{
#if defined(HAVE_DLFCN)
  dlclose(_handle);
#elif defined(HAVE_AIX)
  shl_unload (reinterpret_cast<shl_t>(_handle));
#endif
}

void *DLL::resolve(const std::string &symbol) throw(std::runtime_error)
{
#if defined(HAVE_DLFCN)
  void *tmp = dlsym(_handle, symbol.c_str());
  if (!tmp) throw std::runtime_error(dlerror());
#elif defined(HAVE_DLAIX)
  void *tmp;
  if (shl_findsym(reinterpret_cast<shl_t *>(&_handle), symbol.c_str(), TYPE_UNDEFINED, &tmp) != 0 || _handle == 0 || tmp == 0)
    throw std::runtime_error(strerror(errno));
#endif
  return tmp;
};
