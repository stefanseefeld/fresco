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

template<class SEQUENCE>
SEQUENCE translate(Babylon::String & bs) {
    SEQUENCE res;
    res.resize(1);
    if (sizeof(res[0]) == 1) {
	// Use UTF8:
	Babylon::UTF8String & tmp = bs.utf8();
	res.resize(tmp.length());
	copy(tmp.begin(), tmp.end(), res.get_buffer());
    } else if (sizeof(res[0]) == 2) {
	// Use UTF16:
	Babylon::UTF16String & tmp2 = bs.utf16();
	res.resize(tmp.length());
	copy(tmp.begin(), tmp.end(), res.get_buffer());
    } else if (sizeof(res[0]) == 4) {
	// Use UTF32:
	res.resize(bs.length());
	copy(bs.begin(), bs.end(), res.get_buffer());
    } else {
	throw TransError(TRANS_CAN_NOT_AUTOTRANSLATE);
    }
    return res;
}

template<class SEQUENCE>
Babylon::String translate(SEQUENCE & s) {
    Babylon::String bs;
    if (sizeof(s[0]) == 1) {
	Babylon::UTF8String tmp1;
	tmp.resize(s.length());
	copy(s.get_buffer(), s.get_buffer() + s.length(), tmp.begin());
	bs.utf8(tmp);
    } else if (sizeof(s[0]) == 2) {
	Babylon::UTF16String tmp2;
	tmp.resize(s.length());
	copy(s.get_buffer(), s.get_buffer() + s.length(), tmp.begin());
	bs.utf16(tmp);
    } else if (sizeof(s[0]) == 4) {
	bs.resize(s.length());
	copy(s.get_buffer(), s.get_buffer() + s.length(), bs.begin());
    } else {
	throw TransError(TRANS_CAN_NOT_AUTOTRANSLATE);
    }
    return bs;
}

} // namespace Babylon
