/*$Id$
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

#ifndef _Fresco_Unicode_hh
#define _Fresco_Unicode_hh

#include <Babylon/Babylon.hh>
#include <Fresco/config.hh>
#include <Fresco/Types.hh>

namespace Unicode {
    
    // This is ugly but necessary since Unistring does not
    // know iterators! So I can't do decent assigment
    // operators :-(
    Fresco::Unistring to_CORBA(const Babylon::String &s);
    Fresco::Unichar   to_CORBA(const Babylon::Char c);

    Babylon::String   to_internal(const Fresco::Unistring & us);
    Babylon::Char     to_internal(const Fresco::Unichar uc);

}; // namespace Unicode

#endif
