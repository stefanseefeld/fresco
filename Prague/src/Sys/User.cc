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
#include "Prague/Sys/User.hh"
#include <sys/types.h>
#include <unistd.h>

using namespace Prague;

/* @Method{User::User(int uid = -1)}
 *
 * @Description{constructor, gets user information about user with ID @var{uid}, if not @code{-1}, the process owner otherwise}
 */
User::User(int uid)
{
  if (uid == -1) uid = getuid();
  pwd = getpwuid(uid);
};

/* @Method{User::User(const string &)}
 *
 * @Description{constructor, gets user information about user @var{name}}
 */
User::User(const string &name)
{
  pwd = getpwnam(name.c_str());
};
