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
#include <Prague/config.hh>
#include <iostream>

bool Prague::putenv(const std::string & name, const std::string & value)
{
#ifdef HAVE_SETENV
  return setenv(name.c_str(), value.c_str(), 1) == 0;
#elif HAVE_PUTENV
  char * env_var = new char[name.length() + value.length() + 2];
  strncpy(env_var, name.c_str(), name.length());
  env_var[name.length()] = '=';
  strncpy((env_var + name.length() + 1), value.c_str(), value.length());
  env_var[name.length() + value.length() + 1] = '\0'; // make sure there's a \0
  return ::putenv(env_var);
#else
  std::cerr << "ERROR: Prague::putenv misconfiguration!" << std::endl;
  exit(1);
#endif
  return false;
}

bool Prague::putenv(const std::string & name)
{
#ifdef HAVE_UNSETENV
  return unsetenv(name.c_str());
#elif HAVE_PUTENV
  char * env_var = new char[name.length() + 1];
  strncpy(env_var, name.c_str(), name.length());
  env_var[name.length()] = '\0'; // make sure there's a \0
  return ::putenv(env_var);
#else
  std::cerr << "ERROR: Prague::putenv misconfiguration!" << std::endl;
  exit(1);
#endif
  return false;
}

std::string Prague::getenv(const std::string & name)
{
  char const * const s = ::getenv(name.c_str());
  std::string const value((s!=0)?s:"");
  return value;
}
