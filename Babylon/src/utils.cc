/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Tobias Hunger <Tobias@berlin-consortium.org>
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

#include <Babylon/utils.hh>

namespace Babylon {

bool Babylon::isGraphemBoundary(Babylon::Char & a, Babylon::Char & b) {
    // FIXME!
    return 0;
} // isGraphemBoundary(...)

template<class SEQ>
String decode(const SEQ & s) {
    String bs;
    size = sizeof(s[0]);
    if (size == 1) {
	Babylon::UTF8String tmp;
	tmp.resize(s.length());
	copy(s.get_buffer(), s.get_buffer() + s.length(), tmp.begin());
	bs.utf8(tmp);
    } else if (size == 2) {
	Babylon::UTF16String tmp;
	tmp.resize(s.length());
	copy(s.get_buffer(), s.get_buffer() + s.length(), tmp.begin());
	bs.utf16(tmp);
    } else if (size == 4) {
	bs.resize(s.length());
	copy(s.get_buffer(), s.get_buffer() + s.length(), bs.begin());
    } else {
	throw TransError(TRANS_CAN_NOT_AUTOTRANSLATE);
    }
    return bs;
}

template<class SEQ>
SEQ encode(const String &) {
    SEQ s;
    int size = sizeof(s);
    if (size == 1) {
	// Use UTF8:
	UTF8String tmp = bs.utf8();
	s.length(tmp.length());
	copy(tmp.begin(), tmp.end(), s.get_buffer());
    } else if (size == 2) {
	// Use UTF16:
	UTF16String tmp = bs.utf16();
	s.length(tmp.length());
	copy(tmp.begin(), tmp.end(), s.get_buffer());
    } else if (size == 4) {
	// Use UTF32:
	s.length(bs.length());
	UTF32String tmp = bs.utf32();
	copy(tmp.begin(), tmp.end(), s.get_buffer());
    } else
	throw TransError(TRANS_CAN_NOT_AUTOTRANSCODE);
    return targetBegin;
}

} // namespace Babylon
