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
#ifndef _Prague_Env_hh
#define _Prague_Env_hh

#include <string>
#include <stdlib.h>

namespace Prague {

  //. Set the environment variable name to a value.
  bool putenv(const std::string &, const std::string &);
  //. Unset the environment variable name.
  bool putenv(const std::string &);
  //. get the value of the environment variable name.
  std::string getenv(const std::string &);

};

#endif
