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

#include "Prague/Sys/DLL.hh"

using namespace Prague;

/* @Method{DLL::DLL(const string &name)}
 *
 * @Description{opens the library @var{name}}}
 */
DLL::DLL(const string &name)
{
  lib = name;
  handle = dlopen(lib.c_str(), now);
  if (!handle) err = dlerror();
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
  if (!handle) return 0;
  void *tmp = dlsym(handle, symbol.c_str());
  if (!tmp) err = dlerror();
  return tmp;
};
