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

#include <Babylon/defs.hh>
#include <Babylon/Dictionary.hh>
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
	UCS4 value() const { return m_value; }
	//. returns the Unicode value of this Unicode character.
    
	Char uppercase() const throw (Block_Error) {
	    return Dictionary::instance()->uppercase(m_value);
	}
	//. return the uppercase equivalent of a given
	//. unicode character.
	//. Warning: For some characters of some locales
	//.          this might not be the character you
	//.          exspect!
    
	Char lowercase() const throw (Block_Error) {
	    return Dictionary::instance()->lowercase(m_value);
	}
	//. return the lowercase equivalent of a given
	//. unicode character.
	//. Warning: For some characters of some locales
	//.          this might not be the character you
	//.          exspect!
    
	Char titlecase() const throw (Block_Error) {
	    return Dictionary::instance()->titlecase(m_value);
	}
	//. return the titlecase equivalent of a given
	//. unicode character.
	//. Warning: For some characters of some locales
	//.          this might not be the character you
	//.          exspect!

	// Conversion:
	UTF8_string utf8() const throw (Trans_Error);
	UTF16_string utf16() const throw (Trans_Error);
	// Warning: UTF-16 can not encode characters outside the
	// Unicode und surrogate pair range!
	UTF32_string utf32() const throw (Trans_Error);

	UTF8_string::const_iterator utf8(const UTF8_string &,
					 UTF8_string::const_iterator)
	    throw (Trans_Error);
	UTF16_string::const_iterator utf16(const UTF16_string &,
					   UTF16_string::const_iterator)
	    throw (Trans_Error);
	// Warning: UTF-16 can not encode characters outside the
	// Unicode und surrogate pair range!
	UTF32_string::const_iterator utf32(const UTF32_string &,
					   UTF32_string::const_iterator)
	    throw (Trans_Error);
    
	float numeric_value() const throw (Undefined_Property, Block_Error)  {
	    return Dictionary::instance()->numeric_value(m_value);
	}
	//. return the numeric value of a given unicode character.
    
	int digit_value() const throw (Undefined_Property, Block_Error) {
	    return Dictionary::instance()->digit_value(m_value);
	}
	//. return the digit value of a given unicode character.
    
	int dec_digit_value() const throw (Undefined_Property, Block_Error) {
	    return Dictionary::instance()->dec_digit_value(m_value);
	}
	//. return the decimal digit value of a given unicode character.
    
	string blockname() const throw (Block_Error) {
	    return Dictionary::instance()->blockname(m_value);
	}
	//. returns the name of the block a given unicode character
	//. belongs to.
    
	Gen_Cat category() const throw (Undefined_Property, Block_Error) {
	    return Dictionary::instance()->category(m_value);
	}
	//. returns the general type of the given unicode
	//. character.
    
	Bidir_Props direction() const throw (Undefined_Property, Block_Error) {
	    return Dictionary::instance()->bidir_props(m_value);
	}
	//. returns the linguistic direction property of the
	//. given unicode character.
    
	Can_Comb_Class comb_class() const throw (Undefined_Property, Block_Error) {
	    return Dictionary::instance()->comb_class(m_value);
	}
	//. returns the cannonical comnbining class of
	//. the given unicode character.
    
	Char_Decomp decomp_type() const
	    throw (Undefined_Property, Block_Error) {
	    return Dictionary::instance()->decomp_type(m_value);
	}
	//. returns the decomposition type of a given
	//. unicode character.
    
	String decompose() const throw (Undefined_Property, Block_Error);
	//. returns the decomposition string of a given
	//. unicode character.

	bool must_mirror() const throw (Undefined_Property, Block_Error) {
	    return Dictionary::instance()->must_mirror(m_value);
	}
	//. returns true, if this character must be mirrored in
	//. when in a right-to-left context. and false otherwise. 
    
	EA_Width  EA_width() const throw (Undefined_Property, Block_Error) {
	    return Dictionary::instance()->EA_width(m_value);
	}
	//. returns the cell width of the character for the
	//. given unicode.
    
	Line_Break linebreak() const throw (Undefined_Property, Block_Error) {
	    return Dictionary::instance()->linebreak(m_value);
	}
	//. returns the line-breaking property of the
	//. given unicode character.
    
	// TESTS:

	bool is_defined() const 
	    throw (Block_Error) {
	    return Dictionary::instance()->is_defined(m_value);
	}
    
	bool is_Zero_width()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Zero_width(m_value);
	}

	bool is_White_space()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_White_space(m_value);
	}

	bool is_Non_break()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Non_break(m_value);
	}

	bool is_Bidi_Control()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Control(m_value);
	}

	bool is_Join_Control()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Join_Control(m_value);
	}

	bool is_Format_Control()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Format_Control(m_value);
	}

	bool is_Dash()
	    throw (Block_Error) {
	     return Dictionary::instance()->is_Dash(m_value);
	}

	bool is_Hyphen()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Hyphen(m_value); 
	}

	bool is_Quotation_Mark()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Quotation_Mark(m_value);
	}

	bool is_Terminal_Punctuation()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Terminal_Punctuation(m_value);
	}

	bool is_Math()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Math(m_value);
	}

	bool is_Paired_Punctuation()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Paired_Punctuation(m_value);
	}

	bool is_Left_of_Pair()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Left_of_Pair(m_value);
	}

	bool is_Combining()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Combining(m_value);
	}

	bool is_Non_spacing()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Non_spacing(m_value);
	}

	bool is_Hex_Digit()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Hex_Digit(m_value);
	}

	bool is_Alphabetic()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Alphabetic(m_value);
	}

	bool is_Diacritic()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Diacritic(m_value);
	}

	bool is_Extender()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Extender(m_value);
	}

	bool is_Identifier_Part()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Identifier_Part(m_value);
	}
	bool is_Ignorable_Control()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Ignorable_Control(m_value);
	}

	bool is_Bidi_Hebrew_Right_to_Left()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Hebrew_Right_to_Left(m_value);
	}

	bool is_Bidi_Arabic_Right_to_Left()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Arabic_Right_to_Left(m_value);
	}

	bool is_Bidi_Embedding_or_Override()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Embedding_or_Override(m_value);
	}

	bool is_Uppercase()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Uppercase(m_value);
	}

	bool is_Lowercase()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Lowercase(m_value);   	     	     
	}

	bool is_Space()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Space(m_value);
	}

	bool is_ISO_Control()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_ISO_Control(m_value);
	}

	bool is_Punctuation()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Punctuation(m_value);
	}

	bool is_Line_Separator()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Line_Separator(m_value);
	}

	bool is_Paragraph_Separator()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Paragraph_Separator(m_value);
	}

	bool is_Currency_Symbol()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Currency_Symbol(m_value);
	}

	bool is_Titlecase()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Titlecase(m_value);
	}
	bool is_Composite()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Composite(m_value);
	}

	bool is_Decimal_Digit()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Decimal_Digit(m_value);
	}

	bool is_Numeric()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Numeric(m_value);
	}

	bool is_Digit()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Digit(m_value);
	}

	bool is_Ideographic()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Ideographic(m_value);
	}

	bool is_Bidi_Left_to_Right()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Left_to_Right(m_value);
	}

	bool is_Bidi_European_Digit()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_European_Digit(m_value);
	}

	bool is_Bidi_Eur_Num_Separator()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Eur_Num_Separator(m_value);
	}

	bool is_Bidi_Eur_Num_Terminator()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Eur_Num_Terminator(m_value);
	}

	bool is_Bidi_Arabic_Digit()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Arabic_Digit(m_value);
	}

	bool is_Bidi_Common_Separator()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Common_Separator(m_value); 
	}

	bool is_Bidi_Block_Separator()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Block_Separator(m_value);
	}

	bool is_Bidi_Segment_Separator()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Segment_Separator(m_value);
	}

	bool is_Bidi_Whitespace()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Whitespace(m_value); 
	}

	bool is_Bidi_Non_spacing_Mark()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Non_spacing_Mark(m_value);
	}

	bool is_Bidi_Boundary_Neutral()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Boundary_Neutral(m_value);
	}

	bool is_Bidi_PDF()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_PDF(m_value); 
	}

	bool is_Bidi_LRE()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_LRE(m_value); 
	}

	bool is_Bidi_RLE()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_RLE(m_value); 
	}

	bool is_Bidi_LRO()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_LRO(m_value); 
	}

	bool is_Bidi_RLO()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_RLO(m_value); 
	}

	bool is_Bidi_Other_Neutral()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Bidi_Other_Neutral(m_value);  
	}

	bool is_Private_Use()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Private_Use(m_value);
	}

	bool is_Low_Surrogate()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Low_Surrogate(m_value);
	}

	bool is_High_Surrogate()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_High_Surrogate(m_value);
	}

	bool is_Private_Use_High_Surrogate()
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Private_Use_High_Surrogate(m_value);
	}

	bool is_Not_a_Character() 
	    throw (Block_Error){
	    return Dictionary::instance()->is_Not_a_Character(m_value);
	}

	bool is_Unassigned_Code_Value() 
	    throw (Block_Error) {
	    return Dictionary::instance()->is_Unassigned_Code_Value(m_value); 
	}

	// TRANSFORMATIONS:
    
	void to_lower() throw (Block_Error);
	//. returns the lowercase equivalent to a given unicode
	//. character. If there is no such aequivalent this
	//. function returns the input character.
    
	void to_upper() throw (Block_Error);
	//. returns the uppercase equivalent to a given unicode
	//. character. If there is no such aequivalent this
	//. function returns the input character.
    
	void to_title() throw (Block_Error);
	//. returns the titlecase equivalent to a given unicode
	//. character. If there is no such aequivalent this
	//. function returns the input character.
    
	// CONSTRUCTORS:
	Char() { m_value = Babylon::UC_NULL; }
	Char(const UCS4 uc)   { m_value = uc; }
	Char(const Char & uc) { m_value = uc.value(); }

	// OPERATORS:
	Char & operator = (const Char & uc) {
	    m_value = uc.m_value;
	    return *this;
	} // operator = (Char)
	
	Char & operator = (const UCS4 & uc){
	    m_value = uc;
	    return *this;
	} // operator = (UCS4)
	
	Char & operator = (const char & c) {
	    m_value = UCS4(c);
	    return *this;
	} // operator = (char)
	
	Char & operator = (const int & i) {
	    m_value = UCS4(i);
	    return *this;
	} // operator = (int)
	
	Char operator ++ (int) {
	    Char before(*this); 
	    m_value++;
	    return before;
	} // operator ++ (int)
	
	Char operator -- (int) {
	    Char before(*this);
	    m_value--;
	    return before;
	} // operator -- (int)
	
	Char & operator ++ () {
	    m_value++;
	    return *this;
	} // operator ++ ()
	
	Char & operator -- () {
	    m_value--;
	    return *this;
	} // operator -- ()
	
	Char & operator += (const Char & uc) {
	    m_value += uc.m_value;
	    return *this;
	} // operator +=
	
	Char & operator += (const UCS4 & uc) {
	    m_value += uc;
	    return *this;
	} // operator +=
	
	Char & operator += (const int & i) {
	    m_value += UCS4(i);
	    return *this;
	} // operator +=
	
	Char & operator += (const char & c) {
	    m_value += UCS4(c);
	    return *this;
	} // operator +=
	
	Char & operator -= (const Char & uc) {
	    m_value -= uc.m_value;
	    return *this;
	} // operator -=
	
	Char & operator -= (const UCS4 & uc) {
	    m_value -= uc;
	    return *this;
	} // operator -=
	
	Char & operator -= (const int & i) {
	    m_value -= UCS4(i);
	    return *this;
	} // operator -=
	
	Char & operator -= (const char & c) {
	    m_value -= UCS4(c);
	    return *this;
	} // operator -=
	
	Char & operator *= (const Char uc) {
	    m_value *= uc.m_value;
	    return *this;
	} // operator *=
	
	Char & operator *= (const UCS4 uc) {
	    m_value *= uc;
	    return *this;
	} // operator *=
	
	Char & operator *= (const int i) {
	    m_value *= UCS4(i);
	    return *this;
	} // operator *=
	
	Char & operator *= (const char c) {
	    m_value *= UCS4(c);
	    return *this;
	} // operator *=
    
	// Destructor:
	// ~Char() // nothing special to do...

	bool equal(const Babylon::Char & UC) const {
	    return m_value == UC.m_value; 
	} // equal
	
	bool less (const Babylon::Char & UC) const {
	    return m_value < UC.m_value ;
	} // less

    private:
	UCS4 m_value;

    }; // class Char

} // namespace Babylon

#endif // _Babylon_Char_hh
