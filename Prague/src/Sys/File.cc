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

#include "Prague/Sys/File.hh"
#include <string.h>
#include <unistd.h>
#include <iostream>

/* @Method{File::File(const string &name)}
 *
 * @Description{}
 */
File::File(const string &n)
  : longname (n),
    shortname(BaseName(n)),
    error(0)
{
  getStatus();
}

/* @Method{File::File(const File &f)}
 *
 * @Description{}
 */
File::File(const File &f)
  : longname(f.longname),
    shortname(f.shortname),
    error(0)
{
  getStatus();
}

/* @Method{File::~File()}
 *
 * @Description{}
 */
File::~File() {}

/* @Method{File &File::operator = (const File &f)}
 *
 * @Description{}
 */
File &File::operator = (const File &f)
{
  longname = f.longname;
  shortname = f.longname;
  getStatus();
  return *this;
}

/* @Method{File &File::operator = (const string &name)}
 *
 * @Description{}
 */
File &File::operator = (const string &n)
{
  longname = n;
  shortname = BaseName(n);
  getStatus();
  return *this;
}

/* @Method{File File::Parent() const}
 *
 * @Description{}
 */
File File::Parent() const
{
  if (shortname == "/") return *this;
  return File(longname.substr(0, longname.find_last_of('/')));
}

/* @Method{bool File::chmod(access a)}
 *
 * @Description{}
 */
bool File::chmod(access a)
{
  if (::chmod(longname.c_str(), a) == -1) error = errno;
  else if (!getStatus()) return false;
  else return true;
  return false;
}

/* @Method{bool File::mv(const string &name)}
 *
 * @Description{}
 */
bool File::mv(const string &name)
{
  if (rename(longname.c_str(), name.c_str()) == -1)
    {
      error = errno;
      return false;
    }
  else
    {
      longname  = name;
      shortname = BaseName(name);
      return true;
    }
}

/* @Method{bool File::rm()}
 *
 * @Description{}
 */
bool File::rm()
{
  if (remove(longname.c_str()) == -1)
    {
      error = errno;
      return false;
    }
  else
    {
      longname  = "";
      shortname = "";
      status.st_mode = 0;
      return true;
    }
}

/* @Method{const char *File::lastError() const}
 *
 * @Description{}
 */
const char *File::lastError() const { return sys_errlist[error];}

