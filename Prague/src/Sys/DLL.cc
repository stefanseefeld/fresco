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

#include "Prague/Sys/DLL.hh"

/* @Method{DLL::DLL(const string &name)}
 *
 * @Description{opens the library @var{name}}}
 */
DLL::DLL(const string &name)
{
  lib = name;
  handle = dlopen(lib.c_str(), now);
};

/* @Method{DLL::~DLL()}
 *
 * @Description{close the library}}
 */
DLL::~DLL()
{
  if (handle) dlclose(handle);
};

/* @Method{void *DLL::resolve(const string &symbol)}
 *
 * @Description{return a reference to an object with name @var{symbol}}
 */
void *DLL::resolve(const string &symbol)
{
  return handle ? dlsym(handle, symbol.c_str()) : 0;
};

/* @Method{const char *DLL::Error()}
 *
 * @Description{return an error message describing the last occured error or NULL}
 */
const char *DLL::Error() const
{
  return dlerror();
};
