/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#ifndef _exception_hh
#define _exception_hh

#include <Types.hh>
#include <iostream>

inline ostream &operator << (ostream &os, const CORBA::Exception &exception)
{
  CORBA::Any any;
  any <<= exception;
  CORBA::TypeCode_var tc = any.type();
  const char *p = tc->name();
  if (*p != '\0') os << p;
  else os << tc->id();
  return os;
}

inline ostream &operator << (ostream &os, CORBA::Exception *exception) { return os << *exception;}

#endif /* _exception_hh */
