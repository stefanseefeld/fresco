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

#ifndef _Babylon_internal_utfstrings_hh
#define _Babylon_internal_utfstrings_hh

/* String class
 * This class stores and manipulates strings of characters defined 
 * according to ISO10646. 
 */

#include <Babylon/defs.hh>
#include <string>
#include <Babylon/String.hh>

namespace Babylon {

  class String;

  typedef std::basic_string<UCS2> UTF16_string;
  typedef std::basic_string<UCS4> UTF32_string;
  typedef std::string UTF8_string;

  // This function is necessary to hide UTF32_string,
  // which is used internally, from the user and the API he
  // sees in the Char and String classes.
  inline void get_from_UTF32(UTF32_string in, String & out)
  {
      out.resize(in.length());
      Babylon::UTF32_string::const_iterator j = in.begin();
      for (Babylon::String::iterator i = out.begin();
       i != out.end();
       ++i, ++j) i->operator=(*j);
  }


  /*
  class Char_Mapping : public std::basic_string<size_t>
  {
  public:
      Char_Mapping(size_t start, size_t length)
      {
      resize(length);

      for (size_t i = 0; i < length; ++i)
          (*this)[i] = i + start;
      }

      Char_Mapping() {}
  };
  */
};

#endif
