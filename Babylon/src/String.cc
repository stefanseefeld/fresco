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

// CONSTRUCTORS:
Babylon::String::String() {
    resize(0);
    currentNorm = NORM_NONE;
}

Babylon::String::String(const Char & uc, Norm norm = NORM_NONE) {
    resize(1);
    (*this)[0] = uc;
    currentNorm = norm;
}

Babylon::String::String(const _UCS4 & _uc, Norm norm = NORM_NONE) {
    resize(1);
    (*this)[0] = _uc;
    currentNorm = norm;
}

void Babylon::String::utf8(const UTF8String & s, Norm norm = NORM_NONE)
    throw (TransError) {
    currentNorm = norm;
    clear();
    string::const_iterator s_it = s.begin();
    char first_byte_mask[] = {0x7F, 0x1F, 0x0F, 0x07, 0x03, 0x01};
    this->erase();
    
    while (s_it != s.end()) {
	unsigned int chars_needed;
	
	if      ((*s_it & 0x80) == 0) chars_needed = 0; // *s_it == 0xxx xxxx
	else if ((*s_it & 0x40) == 0)                   // *s_it == 10xx xxxx, should only happen after
	                                                // a character starting with 11xx xxxx
	    throw TransError(TRANS_INVALID_UTF8_STRING);
	else if ((*s_it & 0x20) == 0) chars_needed = 1; // *s_it == 110x xxxx
	else if ((*s_it & 0x10) == 0) chars_needed = 2; // *s_it == 1110 xxxx
	else if ((*s_it & 0x08) == 0) chars_needed = 3; // *s_it == 1111 0xxx
	else if ((*s_it & 0x04) == 0) chars_needed = 4; // *s_it == 1111 10xx
	else if ((*s_it & 0x02) == 0) chars_needed = 5; // *s_it == 1111 110x
	else throw TransError(TRANS_INVALID_UTF8_CHAR); // *s_it == 1111 111x, should not happen in
	// a sequence of UTF8-Characters
	
	_UCS4 c = 0;
	for (int i = chars_needed; i >= 0; --i) {
	    if (i == 0) {
		c = *s_it & first_byte_mask[chars_needed];
	    } else {
		c << 5;
		c = c | (*s_it & 0x3F);
		
		++s_it;
		if ((s_it == s.end()) || (*s_it & 0x80) == 0 || (*s_it & 0x40) != 0 )
		    // either we are at the end of the UTF8-sequence or the current
		    // character does not is not 10xx xxxx.
		    throw TransError(TRANS_INVALID_UTF8_STRING);
	    }
	}
	
	if (c > 0xFFFF) { // It's a surrogate pair:
	    *this += _UCS4((c - 0x10000) / 0x400 + 0xD800);
	    *this += _UCS4((c - 0x10000) % 0x400 + 0xDC00);
	} else // It's a normal character
	    *this += _UCS4(c);
	
	++s_it;
    } // while
    currentNorm = norm;
}

Babylon::UTF8String Babylon::String::utf8() const {
    Babylon::UTF8String res;
    res.resize(0);
    for(String::const_iterator it = this->begin();
	it != this->end();
	++it) {
	unsigned int chars_needed;

	if      (*it <= 0x0000007F) chars_needed = 0;
	else if (*it <= 0x000007FF) chars_needed = 1;
	else if (*it <= 0x0000FFFF) chars_needed = 2;
	else if (*it <= 0x001FFFFF) chars_needed = 3;
	else if (*it <= 0x03FFFFFF) chars_needed = 4;
	else if (*it <= 0x7FFFFFFF) chars_needed = 5;
	else throw TransError(TRANS_INVALID_UCS4_CHAR);

	for(unsigned int i = chars_needed; i >= 0; i--) {
	    _UCS4 c = it->myValue();
	    if (i == 0) {
		_UCS1 t = 0;
		if (chars_needed != 0)
		    t = 0xFE << (6 - chars_needed);
		t = t & c;
		res += Babylon::_UCS1(t);
	    } else {
		_UCS4 t = c & 0x3F; // t = 00xxxxxx;
		t = t | 0x80;       // t = 10xxxxxx;
		res += Babylon::_UCS1(c);
		c = c >> 5;
	    }
	}
    }
    return res;
}

void Babylon::String::utf16(const UTF16String & in , const Norm norm = NORM_NONE)
    throw (TransError) {
    currentNorm = norm;
    
    clear();

    for(UTF16String::const_iterator it = in.begin();
	it != in.end();
	++it) {
	if (*it < 0x0000D800 || *it > 0x0000DFFF) *this += Babylon::_UCS4(*it);
	else {
	    if (*it >= 0x0000DC00) throw TransError(TRANS_INVALID_UTF16_STRING);
	    _UCS2 h = *it;
	    _UCS4 c = (h & 0x3FF) << 10;
	    it++;
	    if (it == in.end()) throw TransError(TRANS_INVALID_UTF16_STRING);
	    c = c | (h & 0x3FF);
	    c += 0X00010000;
	    *this += Babylon::_UCS4(c);
	}
    }
}

Babylon::UTF16String Babylon::String::utf16() const {
    Babylon::UTF16String res;
    res.resize(0);
    for(String::const_iterator it = this->begin();
	it != this->end();
	++it) {
	Babylon::_UCS4 c = it->myValue();
	if (c > 0x0010FFFF)
	    throw TransError(TRANS_CAN_NOT_ENCODE_CHAR);
	if (c < 0x00010000)
	    res += _UCS2(c);
	else {
	    c -= 0x00010000;
	    _UCS2 h = 0xD800;
	    _UCS2 l = 0xDC00;
	    res += (h | (c & 0x3FF));
	    res += (l | (c >> 10));
	}
    }
    return res;
}

Babylon::String::String(const String & us) {
    resize(us.length());
    
    Babylon::String::const_iterator   us_it = us.begin();
    Babylon::String::iterator       this_it = this->begin();
    
    while (us_it != us.end() && this_it != this->end()) {
	*this_it = *us_it;
	++this_it; ++us_it;
    }
    currentNorm = us.norm();
}

Babylon::String::String(const _UTF32String & _us, Norm norm = NORM_NONE) {
    resize(_us.length());
    
    Babylon::_UTF32String::const_iterator _us_it = _us.begin();
    Babylon::String::iterator this_it = this->begin();
    
    while (_us_it != _us.end() && this_it != this->end()) {
	*this_it = *_us_it;
	++this_it; ++_us_it;
    }
    currentNorm = norm;
}

void Babylon::String::normalize(const Norm norm) {
    String result;
    if (length() > 0 && norm < NORM_NONE && norm != currentNorm) {
	Dictionary * dict = Dictionary::instance();
	
	// do I need to decompose?
	if (currentNorm!=NORM_D || (norm!=NORM_KC && currentNorm!=NORM_NONE)) {
	    bool compat = (norm & 2); // compatibility bit
	    for(String::const_iterator i = this->begin();
		i != this->end(); ++i) {
		String tmp = dict->recursiveDecompose(compat, i->myValue());
		
		for(String::const_iterator j = tmp.begin();
		    j != tmp.end(); ++j) {
		    Can_Comb_Class cClass = dict->findChar(j->myValue())->
			combClass(j->myValue());
		    String::iterator k = result.end();
		    if (cClass == 0)
			result += *j;
		    else {
			for (; k >= result.begin(); k--)
			    if (dict->findChar((k-1)->myValue())->
				combClass((k-1)->myValue()) <= cClass) break;
			result.insert(k, *j);
		    }
		}
	    }
	}      
	
	// do I need to compose?
	if (currentNorm != NORM_C && (norm & 1)) {
	    // decomposition skipped?
	    if (result.length() == 0) result = *this;
	    
	    String::iterator starter = result.begin();
	    String::iterator compPos = starter + 1;
	    Can_Comb_Class lastClass = dict->findChar(starter->myValue())->
		combClass(starter->myValue());
	    if (lastClass != 0)
		lastClass = Can_Comb_Class(256); // fix for irregular comb sequence
	    
	    for(String::iterator ch = starter + 1;
		ch != result.end(); ++ch) {
		Can_Comb_Class chClass = dict->findChar(ch->myValue())->
		    combClass(ch->myValue());
		_UCS4 composite = dict->findChar(starter->myValue())->
		    compose(starter->myValue(), ch->myValue());
		
		if(composite != 0 && (lastClass < chClass || lastClass == 0))
		    *starter = composite;
		else {
		    if(chClass == 0)
			starter = compPos;
		    lastClass=chClass;
		    *compPos = *ch;
		    compPos++;
		}
	    }
	    result.resize(compPos - result.begin());
	} // compose
    }
    if(result.length() != 0) {
	result.overrideNorm(norm);
	*this = result;
    }
}

Babylon::String Babylon::String::norm(Babylon::Norm norm) const {
    String tmp = *this;
    tmp.normalize(norm);
    return tmp;
}

size_t Babylon::String::glyphs() const {
    size_t glyphs = 0;
    
    for (Babylon::String::const_iterator i = this->begin();
	 i != this->end();
	 ++i)
	if(i->combClass() == CC_SPACING) ++glyphs;
    
    return glyphs; 
}

Babylon::String Babylon::String::getGlyph(Babylon::String::const_iterator iter) const {
    String result;
    
    while (iter != this->end()) {
	result += *iter;
	++iter;
	if (iter->combClass() == Babylon::CC_SPACING) break;
    }
    
    return result;
}

void Babylon::String::nextGlyph(Babylon::String::const_iterator & iter) const {
    ++iter; // advance past the first character...
    
    while (iter != this->end() && iter->combClass() != Babylon::CC_SPACING)
	++iter;
}

Babylon::String Babylon::String::getParagraph(Babylon::String::const_iterator iter) {
    String result;
    
    while (iter != this->end()) {
	result += *iter;
	if (iter->category() == Babylon::CAT_Zp) break;
	++iter;
    }
    
    return result;
}

void Babylon::String::nextParagraph(Babylon::String::const_iterator & iter) const {
    while (iter != this->end() && iter->category() != Babylon::CAT_Zp)
	++iter;
    if (iter != this->end()) ++iter;
}

ostream & Babylon::String::_write(ostream & out) const {
    for (Babylon::String::const_iterator i = this->begin();
	 i != this->end(); ++i) {
	i->_write(out);
    }
    return out;
} // _write
