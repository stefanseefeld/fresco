/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999-2003 Tobias Hunger <Tobias@fresco.org>
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

/* This file supports Unicode version 3.1 beta */

#ifndef _Babylon_exceptions_hh
#define _Babylon_exceptions_hh

#include <Babylon/defs.hh>

#include <stdexcept>
#include <string>

namespace Babylon
{
  // Classes to throw around as exceptions:
  
  class Undefined_Property : std::exception {
    public:
      Undefined_Property(UCS4 uc, const Char_Props prop) :
	  my_error_uc(uc),
	  my_error_prop(prop)
      { }
      
      const char * what() const throw();
    public:
      UCS4 my_error_uc;
      Char_Props my_error_prop;
  }; // class Undefined_Property
    
  class Transfer_Error : std::exception
  {
    public:
      Transfer_Error(Trans_Error transError) :
	  my_error(transError)
      { }
      ~Transfer_Error() throw() { }
      const char * what() const throw();
    private:
      Trans_Error my_error;
  }; // Transfer_Error

  class Block_Error : std::exception
  {
    public:
      Block_Error(UCS4 startUC, UCS4 endUC, const std::string &em) :
	  my_block_start(startUC),
	  my_block_end(endUC),
	  my_error_message(em)
      { }
      ~Block_Error() throw() {}
      const char * what() const throw();
    private:
      UCS4 my_block_start;
      UCS4 my_block_end;
      std::string my_error_message;
  }; // class Block_Error

}; // namespace

#endif
