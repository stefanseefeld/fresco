/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999,2000 Tobias Hunger <Tobias@berlin-consortium.org>
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

#include <Babylon/String.hh>
#include <Babylon/Char.hh>

// Conversion:
Babylon::UTF8_string Babylon::Char::utf8() const throw (Trans_Error) {
    unsigned int chars_needed;
    
    UCS4 c = m_value;
    UTF8_string res;

    if      (c <= 0x0000007F) chars_needed = 0;
    else if (c <= 0x000007FF) chars_needed = 1;
    else if (c <= 0x0000FFFF) chars_needed = 2;
    else if (c <= 0x001FFFFF) chars_needed = 3;
    else if (c <= 0x03FFFFFF) chars_needed = 4;
    else if (c <= 0x7FFFFFFF) chars_needed = 5;
    else throw Trans_Error(TRANS_CAN_NOT_ENCODE);
    
    for(int i = chars_needed; i >= 0; i--) {
	if (i == 0) {
	    UCS1 t = 0;
	    if (chars_needed != 0)
		t = 0xFE << (6 - chars_needed);
	    t = t | c;
	    res += UCS1(t);
	} else {
	    UCS4 t = c & 0x3F; // t = 00xxxxxx;
	    t = t | 0x80;      // t = 10xxxxxx;
	    res += UCS1(t);
	    c = c >> 5;
	}
    }
    return res;
}

Babylon::UTF16_string Babylon::Char::utf16() const throw (Trans_Error) {
    UTF16_string res;
    UCS4 c = m_value;
    if (c > 0x0010FFFF)
	throw Trans_Error(TRANS_CAN_NOT_ENCODE);
    if (c < 0x00010000)
	res += UCS2(c);
    else {
	c -= 0x00010000;
	UCS2 h = 0xD800;
	UCS2 l = 0xDC00;
	res += (h | (c & 0x3FF));
	res += (l | (c >> 10));
    }

    return res;
}

Babylon::UTF32_string Babylon::Char::utf32() const throw () {
    UTF32_string res(m_value, Babylon::NORM_NONE);
    return res;
}

Babylon::UTF8_string::const_iterator
Babylon::Char::utf8(const Babylon::UTF8_string & s,
		    Babylon::UTF8_string::const_iterator it)
    throw (Trans_Error) {
    char first_byte_mask[] = {0x7F, 0x1F, 0x0F, 0x07, 0x03, 0x01};
    
    UCS4 h = 0;

    READ_UTF8_CHAR:
    unsigned int chars_needed;
    
    if      ((*it & 0x80) == 0) chars_needed = 0; // *s_it == 0xxx xxxx
    else if ((*it & 0x40) == 0)                   // *s_it == 10xx xxxx, should only
	                                            // happen after a character
	                                            // starting with 11xx xxxx
	throw Trans_Error(TRANS_CAN_NOT_DECODE);
    else if ((*it & 0x20) == 0) chars_needed = 1; // *s_it == 110x xxxx
    else if ((*it & 0x10) == 0) chars_needed = 2; // *s_it == 1110 xxxx
    else if ((*it & 0x08) == 0) chars_needed = 3; // *s_it == 1111 0xxx
    else if ((*it & 0x04) == 0) chars_needed = 4; // *s_it == 1111 10xx
    else if ((*it & 0x02) == 0) chars_needed = 5; // *s_it == 1111 110x
    else throw Trans_Error(TRANS_CAN_NOT_DECODE); // *s_it == 1111 111x,
                                                    // should not happen in
                                                    // a sequence of UTF8-Characters
    
    UCS4 c = 0;
    for (int i = chars_needed; i >= 0; --i) {
	if (i == 0) {
	    c = *it & first_byte_mask[chars_needed];
	} else {
	    c << 5;
	    c = c | (*it & 0x3F);
	    
	    ++it;
	    if ((it == s.end()) || (*it & 0x80) == 0 || (*it & 0x40) != 0 )
		// either we are at the end of the UTF8-sequence or the current
		// character is not 10xx xxxx.
		throw Trans_Error(TRANS_CAN_NOT_DECODE);
	}
    }
    
    if (c >= 0xD800 && c <= 0xDBFF) {
	// c is a high surrogate
	if (h != 0)
	    throw Trans_Error(TRANS_CAN_NOT_DECODE);
	h = c;
	++it; // read the next character (wich should be a low surrogate)
	goto READ_UTF8_CHAR;
    }
    
    if (c >= 0xDC00 && c <= 0xDFFFF) {
	if (h == 0)
	    throw Trans_Error(TRANS_CAN_NOT_DECODE);
	c = (((h & 0x3FF) << 10) | (c & 0x3FF)) + 0x10000;
    }
    
    m_value = UCS4(c);

    ++it; // advance one past the last octet read.

    return it;
}

Babylon::UTF16_string::const_iterator
Babylon::Char::utf16(const Babylon::UTF16_string & s,
		     Babylon::UTF16_string::const_iterator it)
    throw (Trans_Error) {
    UCS4 c = *it;
    if (c >= 0xD800 && c <= 0xDFFF) {
	// we found part of a surrogate pair...
	if (c >= 0xDC00)
	    // it was a low surrogate...
	    throw Trans_Error(TRANS_CAN_NOT_DECODE);
	++it;
	if (it == s.end() || *it <= 0xDC00 || *it > 0xDFFF)
	    // didn't find a corresponding low surrogate...
	    throw Trans_Error(TRANS_CAN_NOT_DECODE);
	c = (((c & 0x3FF) << 10) | (*it & 0x3FFF)) + 0x10000;
    }
    m_value = c;
    ++it;
    return it;
}

Babylon::UTF32_string::const_iterator
Babylon::Char::utf32(const Babylon::UTF32_string & s,
		     Babylon::UTF32_string::const_iterator it)
    throw () {
    m_value = *it;
    ++it;
    return it;
}

// TRANSFORMATIONS:
void Babylon::Char::to_lower()
    throw (Block_Error) {
    *this = this->lowercase();
} // to_lowercase

void Babylon::Char::to_upper()
    throw (Block_Error) {
    *this = this->uppercase();
} // to_uppercase

void Babylon::Char::to_title()
    throw (Block_Error) {
    *this = this->titlecase();
} // to_titlecase

Babylon::String Babylon::Char::decompose() const
    throw (Undefined_Property, Block_Error) {
    return String(Dictionary::instance()->decompose(m_value));
} // decompose
