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
#ifndef _Prague_DLL_hh
#define _Prague_DLL_hh

#include <stdexcept>
#include <string>

namespace Prague
{

  //. DLL represents a dynamic library
  class DLL
  {
    public:
      //. create a library handle for the named library
      DLL(const std::string &name, bool now = true) throw(std::runtime_error, std::logic_error);
      ~DLL() throw();
      //. resolve the given symbol
      void *resolve(const std::string &) throw(std::runtime_error);
      //. return the library's name
      const std::string &name() const throw() { return my_name; }
    private:
      std::string my_name;
      void       *my_handle;
  };

} // namespace

#endif
