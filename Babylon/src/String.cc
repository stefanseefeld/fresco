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

Babylon::String::String(const ::string & s, Norm norm = NORM_NONE)
throw (TransError) {
  string::const_iterator s_it = s.begin();
  _UCS4 first_byte_mask[] = {0x7F, 0x1F, 0x0F, 0x07};
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
      else throw TransError(TRANS_INVALID_UTF8_CHAR); // *s_it == 1111 1xxx, should not happen in
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
	String tmp = dict->recursiveDecompose(compat, i->myUnicode());
	
	for(String::const_iterator j = tmp.begin();
	     j != tmp.end(); ++j) {
	  Can_Comb_Class cClass = dict->findChar(j->myUnicode())->
	    combClass(j->myUnicode());
	  String::iterator k = result.end();
	  if (cClass == 0) result += *j;
	  else {
	    for (; k >= result.begin(); k--) {
	      if (dict->findChar((k-1)->myUnicode())->
		  combClass((k-1)->myUnicode()) <= cClass) break;
	    }
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
      Can_Comb_Class lastClass = dict->findChar(starter->myUnicode())->
	combClass(starter->myUnicode());
      if (lastClass != 0)
	lastClass = Can_Comb_Class(256); // fix for irregular comb sequence
      
      for(String::iterator ch = starter + 1;
	  ch != result.end(); ++ch) {
	Can_Comb_Class chClass = dict->findChar(ch->myUnicode())->
	  combClass(ch->myUnicode());
	_UCS4 composite = dict->findChar(starter->myUnicode())->
	  compose(starter->myUnicode(), ch->myUnicode());

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
       i != this->end(); ++i) {
    if(i->combClass() == CC_SPACING) ++glyphs;
  }
  
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
