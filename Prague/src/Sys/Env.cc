/*
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2002 Tobias Hunger <tobias@fresco.org> 
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

#include <Prague/Sys/Env.hh>

bool Prague::putenv(const std::string & name, const std::string & value)
{
#ifdef HAVE_SETENV
  return setenv(name.c_str(), value.c_str(), 1)==0;
#elif HAVE_PUTENV
  std::string env_var(name);
  env_var += "=" + value;
  return putenv(env_var.c_str());
#endif
}

bool Prague::putenv(const std::string & name)
{
#ifdef HAVE_UNSETENV
  return unsetenv(name.c_str());
#elif HAVE_PUTENV
  return putenv(name.c_str());
#endif
}

std::string Prague::getenv(const std::string & name)
{
  return std::string(getenv(name.c_str()));
}
