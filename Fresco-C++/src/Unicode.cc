/*$Id Unicode.cc,v 1.6 2002/05/29 06:49:41 stefan Exp $
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Tobias Hunger <tobias@fresco.org>
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

// This headerfile is necessary since Prague does not know about
// the Unistring (defined in Warsaw) that CORBA needs.

#include <Fresco/Unicode.hh>

using namespace Fresco;

// This is ugly but necessary since Unistring does not
// know iterators! So I can´t do decent assigment
// operators :-(

Unistring Unicode::to_CORBA(const Babylon::String &s) {
  Babylon::UTF16_string tmp = s.utf16();
  Fresco::Unistring res(tmp.length(),
			tmp.length(),
			const_cast<Babylon::UCS2 *>(tmp.data()));
  return res;
}

Fresco::Unichar Unicode::to_CORBA(const Babylon::Char c) {
    return Fresco::Unichar(c.value());
}

Babylon::String Unicode::to_internal(const Unistring & us) {
    std::cerr << "to_internal: started." << std::endl;
    Babylon::String res;
    std::cerr << "to_internal: got res." << std::endl;
    for (size_t i = 0; i < us.length(); ++i)
      res.push_back(Babylon::Char(static_cast<const Babylon::UCS2>(us[i])));
    std::cerr << "to_internal: res set." << std::endl;
    return res;
}

Babylon::Char Unicode::to_internal(const Fresco::Unichar uc) {
    return Babylon::Char(Babylon::UCS4(uc));
}
