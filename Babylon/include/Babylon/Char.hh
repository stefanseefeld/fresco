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
#ifndef _Babylon_Char_hh
#define _Babylon_Char_hh

#include <Babylon/Babylon.hh>
#include <streambuf.h>
#include <iostream.h>
#include <iomanip.h>

/*
 * This header-file defines functions on single
 * unicode characters. For functions on unicode
 * strings check out Babylon/String.hh
 */

namespace Babylon {
    
class Char {
public:
    
    // QUERIES:
    UCS4 myValue() const { return my_unicode; }
    //. returns the Unicode value of this Unicode character.
    
    Char uppercase() const throw (UndefinedProperty, BlockError);
    //. return the uppercase equivalent of a given
    //. unicode character.
    //. Warning: For some characters of some locales
    //.          this might not be the character you
    //.          exspect!
    
    Char lowercase() const throw (UndefinedProperty, BlockError);
    //. return the lowercase equivalent of a given
    //. unicode character.
    //. Warning: For some characters of some locales
    //.          this might not be the character you
    //.          exspect!
    
    Char titlecase() const throw (UndefinedProperty, BlockError);
    //. return the titlecase equivalent of a given
    //. unicode character.
    //. Warning: For some characters of some locales
    //.          this might not be the character you
    //.          exspect!
    
    float numericValue() const throw (UndefinedProperty, BlockError);
    //. return the numeric value of a given unicode character.
    
    int digitValue() const throw (UndefinedProperty, BlockError);
    //. return the digit value of a given unicode character.
    
    int decDigitValue() const throw (UndefinedProperty, BlockError);
    //. return the decimal digit value of a given unicode character.
    
    string blockname() const throw (BlockError);
    //. returns the name of the block a given unicode character
    //. belongs to.
    
    Gen_Cat category() const throw (UndefinedProperty, BlockError);
    //. returns the general type of the given unicode
    //. character.
    
    Bidir_Props direction() const throw (UndefinedProperty, BlockError);
    //. returns the linguistic direction property of the
    //. given unicode character.
    
    Can_Comb_Class combClass() const throw (UndefinedProperty, BlockError);
    //. returns the cannonical comnbining class of
    //. the given unicode character.
    
    Char_Decomp decompType() const throw (UndefinedProperty, BlockError);
    //. returns the decomposition type of a given
    //. unicode character.
    
    String decompose() const throw (UndefinedProperty, BlockError);
    //. returns the decomposition string of a given
    //. unicode character.
    
    bool mustMirror() const throw (UndefinedProperty, BlockError);
    //. returns true, if this character must be mirrored in
    //. when in a right-to-left context. and false otherwise. 
    
    EA_Width  EAWidth() const throw (UndefinedProperty, BlockError);
    //. returns the cell width of the character for the
    //. given unicode.
    
    Line_Break linebreak() const throw (UndefinedProperty, BlockError);
    //. returns the line-breaking property of the
    //. given unicode character.
    
    // TESTS:
    
    bool is_lowercase() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. lowercase and false otherwise.
    
    bool is_uppercase() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. uppercase and false otherwise. 
    
    bool is_titlecase() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. titlecase and false otherwise.
    
    bool is_digit() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. a digit and false otherwise.
    
    bool is_defined() const throw (BlockError);
    //. returns true if the input Unicode character is
    //. defined and false otherwise.
    
    bool is_alpha() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. a letter and false otherwise.
    
    bool is_space() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. a space character and false otherwise.
    
    bool is_control() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. control character and false otherwise.
    
    bool is_printable() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. printable and false otherwise. This does not
    //. tell wether the character is included in a given font.
    
    bool is_base() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. in base form and false otherwise.
    
    bool is_ascii() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. a ASCII character and false otherwise.
    
    bool is_mark() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. a mark and false otherwise.
    
    bool is_number() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. a number and false otherwise.
    
    bool is_punctuation() const throw (UndefinedProperty, BlockError);
    //. returns true if the input Unicode character is
    //. a punctuation mark and false otherwise. 
    
    // TRANSFORMATIONS:
    
    void to_lower() throw (UndefinedProperty, BlockError);
    //. returns the lowercase equivalent to a given unicode
    //. character. If there is no such aequivalent this
    //. function returns the input character.
    
    void to_upper() throw (UndefinedProperty, BlockError);
    //. returns the uppercase equivalent to a given unicode
    //. character. If there is no such aequivalent this
    //. function returns the input character.
    
    void to_title() throw (UndefinedProperty, BlockError);
    //. returns the titlecase equivalent to a given unicode
    //. character. If there is no such aequivalent this
    //. function returns the input character.
    
    // CONSTRUCTORS:
    Char() { my_unicode = Babylon::UC_NULL; }
    Char(const char & c) throw (TransError) {
	if (c < 0) throw TransError(TRANS_NO_ASCII);
	my_unicode = c;
    }
    Char(const UCS4 & _uc) { my_unicode = _uc; }
    Char(const int & i) { my_unicode = UCS4(i); };
    
    Char(const Char & UC) { my_unicode = UC.myValue(); }
    
    // OPERATORS:
    Char & operator = (const Char & UC) {
	my_unicode = UC.my_unicode;
	return *this;
    } // operator = (Char)
    
    Char & operator = (const UCS4 & UC){
	my_unicode = UC;
	return *this;
    } // operator = (UCS4)
    
    Char & operator = (const char & C) {
	my_unicode = UCS4(C);
	return *this;
    } // operator = (char)
    
    Char & operator = (const int & I) {
	my_unicode = UCS4(I);
	return *this;
    } // operator = (int)
    
    Char operator ++ (int) {
	Char before(*this); 
	my_unicode++;
	return before;
    } // operator ++ (int)
    
    Char operator -- (int) {
	Char before(*this);
	my_unicode--;
	return before;
    } // operator -- (int)
    
    Char & operator ++ () {
	my_unicode++;
	return *this;
    } // operator ++ ()
    
    Char & operator -- () {
	my_unicode--;
	return *this;
    } // operator -- ()
    
    Char & operator += (Char & UC) {
	my_unicode += UC.my_unicode;
	return *this;
    } // operator +=
    
    Char & operator += (UCS4 & UC) {
	my_unicode += UC;
	return *this;
    } // operator +=
    
    Char & operator += (int & I) {
	my_unicode += UCS4(I);
	return *this;
    } // operator +=
    
    Char & operator += (char & C) {
	my_unicode += UCS4(C);
	return *this;
    } // operator +=
    
    Char & operator -= (Char & UC) {
	my_unicode -= UC.my_unicode;
	return *this;
    } // operator -=
    
    Char & operator -= (UCS4 & UC) {
	my_unicode -= UC;
	return *this;
    } // operator -=
    
    Char & operator -= (int & I) {
	my_unicode -= UCS4(I);
	return *this;
    } // operator -=
    
    Char & operator -= (char & C) {
	my_unicode -= UCS4(C);
	return *this;
    } // operator -=
    
    Char & operator *= (Char & UC) {
	my_unicode *= UC.my_unicode;
	return *this;
    } // operator *=
    
    Char & operator *= (UCS4 & UC) {
	my_unicode *= UC;
	return *this;
    } // operator *=
    
    Char & operator *= (int & I) {
	my_unicode *= UCS4(I);
	return *this;
    } // operator *=
    
    Char & operator *= (char & C) {
	my_unicode *= UCS4(C);
	return *this;
    } // operator *=
    
    // UTILITIES:
    ostream & _write(ostream &) const;
    
    bool equal(const Babylon::Char & UC) const {
	return my_unicode == UC.my_unicode; 
    } // equal
    
    bool less (const Babylon::Char & UC) const {
	return my_unicode < UC.my_unicode ;
    } // less
    
    // Destructor:
    // ~Char() // nothing special to do...
private:
    UCS4 my_unicode;
}; // class Char
    
} // namespace Babylon

// OPERATORS:
inline ostream & operator <<
    (ostream & out, const Babylon::Char & uc) {
    return uc._write(out);
}

// The relational operators look at the unicode values
// ONLY! So semantically identical characters will not be
// recognized.
inline bool operator ==
(const Babylon::Char & lhs, const Babylon::Char & rhs) {
    return lhs.equal(rhs);
}

inline bool operator !=
(const Babylon::Char & lhs, const Babylon::Char & rhs) {
    return ! (lhs == rhs);
}

inline bool operator <
(const Babylon::Char & lhs, const Babylon::Char & rhs) {
    return lhs.less(rhs);
}

inline bool operator >
(const Babylon::Char & lhs, const Babylon::Char & rhs) {
    return rhs < lhs;
}

inline bool operator <=
(const Babylon::Char & lhs, const Babylon::Char & rhs) {
    return ! (lhs > rhs);
}

inline bool operator >=
(const Babylon::Char & lhs, const Babylon::Char & rhs) {
    return rhs <= lhs;
}

#endif // _Unichar_hh
