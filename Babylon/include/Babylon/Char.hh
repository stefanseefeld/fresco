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
#ifndef _Babylon_Char_hh
#define _Babylon_Char_hh

#include <Prague/Sys/Thread.hh>

#include <Babylon/defs.hh>
#include <Babylon/exceptions.hh>

/*
 * This header-file defines functions on single
 * unicode characters. For functions on unicode
 * strings check out Babylon/String.hh
 */

namespace Babylon
{

  //. Set the default directory path. Use before using the dictionary
  //. for the first time, or it will be ignored.
  //. An empty path will be silently ignored. All directories of this
  //. path must be valid (or a std::runtime_error exception will be thrown),
  //. but only the very last path will be scanned.
  void override_path(std::string) throw (std::runtime_error);

  class Char
  {
    public:
      // ------------------------------------------------------------
      // CONVERSION:
      // ------------------------------------------------------------
      
      std::string
      convert(const std::string format = Babylon::UTF8_format) const
	  throw (Transfer_Error);
      
      size_t convert(const std::string &,
		     const size_t = 0,
		     const std::string format = Babylon::UTF8_format)
	  throw (Transfer_Error);
      
      // ------------------------------------------------------------
      // QUERIES:
      // ------------------------------------------------------------
      
      //. Returns the (Scalar-) Unicode value of the character.
      UCS4 value() const { return my_value; }
      
      //. Gets the uppercase equivalent of the character.
      //. If no uppercase equivalent is defined then a copy of
      //. the current chracter is returned.
      //.
      //. Warning: For some characters of some locales
      //.          this might not be the character you
      //.          exspect!
      Char uppercase() const throw (Block_Error);
      
      //. Gets the lowercase equivalent of the character.
      //. If no uppercase equivalent is defined then a copy of
      //. the current chracter is returned.
      //.
      //. Warning: For some characters of some locales
      //.          this might not be the character you
      //.          exspect!
      Char lowercase() const throw (Block_Error);
      
      //. Gets the titlecase equivalent of the character.
      //. If no uppercase equivalent is defined then a copy of
      //. the current chracter is returned.
      //.
      //. Warning: For some characters of some locales
      //.          this might not be the character you
      //.          exspect!
      Char titlecase() const throw (Block_Error);
      
      //. Gets the numeric value of the character.
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no numeric property set.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      float numeric_value() const throw (Undefined_Property, Block_Error);
      
      //. return the numeric value of a given unicode character.
      
      //. Gets the digit value of the character.
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no digit value property set.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      int digit_value() const throw (Undefined_Property, Block_Error);
      
      //. Gets the decimal digit value of the character.
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no decimal digit value property set.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      int dec_digit_value() const throw (Undefined_Property, Block_Error);

      bool is_Numeric() const throw (Block_Error);
      bool is_Decimal_Digit() const throw (Block_Error);
      bool is_Digit() const throw (Block_Error);
      
      //. Returns the name of the block (aka. script) the characte
      //. belongs to.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      std::string blockname() const throw (Block_Error);
      
      //. Gets the general category of the character.
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no decimal digit value property set.
      //.          THIS SHOULD NEVER HAPPEN, as all characters should
      //.          have this defined.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      Gen_Cat category() const throw (Undefined_Property, Block_Error);
      
      //. Returns the linguistic direction property of the
      //. given unicode character.
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no decimal digit value property set.
      //.          THIS SHOULD NEVER HAPPEN, as all characters should
      //.          have this defined.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      Bidir_Props direction() const throw (Undefined_Property, Block_Error);
      
      //. Returns the cannonical comnbining class of
      //. the given unicode character.
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no decimal digit value property set.
      //.          THIS SHOULD NEVER HAPPEN, as all characters should
      //.          have this defined.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      Can_Comb_Class comb_class() const
	  throw (Undefined_Property, Block_Error);
      
      //. Returns the decomposition type of a given
      //. unicode character.
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no decimal digit value property set.
      //.          THIS SHOULD NEVER HAPPEN, as all characters should
      //.          have this defined.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      Char_Decomp decomp_type() const
	  throw (Undefined_Property, Block_Error);
      
      //. Returns the decomposition string of a given
      //. unicode character.
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no decimal digit value property set.
      //.          THIS SHOULD NEVER HAPPEN, as all characters should
      //.          have this defined.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      String decompose() const throw (Undefined_Property, Block_Error);
      // UTF32_string decompose() const throw (Undefined_Property, Block_Error);

      //. Returns wether this character needs to be excluded from
      //. the composition process.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      bool exclude_from_composition() const throw (Block_Error);
      
      //. Returns true, if this character must be mirrored
      //. when it appears in a right-to-left context. and false
      //. otherwise. 
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no decimal digit value property set.
      //.          THIS SHOULD NEVER HAPPEN, as all characters should
      //.          have this defined.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      bool must_mirror() const throw (Undefined_Property, Block_Error);
      
      //. Returns the (East Asian) cell width of the character.
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no decimal digit value property set.
      //.          THIS SHOULD NEVER HAPPEN, as all characters should
      //.          have this defined.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      EA_Width  EA_width() const throw (Undefined_Property, Block_Error);
      
      //. Returns the line-breaking property of the character.
      //. Throws : Undefined_Property
      //.          if it character is not defined or
      //.          has no decimal digit value property set.
      //.          THIS SHOULD NEVER HAPPEN, as all characters should
      //.          have this defined.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      Line_Break linebreak() const throw (Undefined_Property, Block_Error);
      
      // ------------------------------------------------------------
      // TESTS:
      // ------------------------------------------------------------
      
      //. Returns true, if this character is defined and false
      //. otherwise. 
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      bool is_defined() const throw (Block_Error);
      
      // Properties
      bool is_White_Space() const throw (Block_Error);
      bool is_Bidi_Control() const throw (Block_Error);
      bool is_Join_Control() const throw (Block_Error);
      bool is_Dash() const throw (Block_Error);
      bool is_Hyphen() const throw (Block_Error);
      bool is_Quotation_Mark() const throw (Block_Error);
      bool is_Terminal_Punctuation() const throw (Block_Error);
      bool is_Other_Math() const throw (Block_Error);
      bool is_Hex_Digit() const throw (Block_Error);
      bool is_ASCII_Hex_Digit() const throw (Block_Error);
      bool is_Other_Alphabetic() const throw (Block_Error);
      bool is_Ideographic() const throw (Block_Error);
      bool is_Diacritic() const throw (Block_Error);
      bool is_Extender() const throw (Block_Error);
      bool is_Other_Lowercase() const throw (Block_Error);
      bool is_Other_Uppercase() const throw (Block_Error);
      bool is_Noncharacter_Code_Point() const throw (Block_Error);
      bool is_Other_Grapheme_Extend() const throw (Block_Error);
      bool is_Grapheme_Link() const throw (Block_Error);
      bool is_IDS_Binary_Operator() const throw (Block_Error);
      bool is_IDS_Trinary_Operator() const throw (Block_Error);
      bool is_Radical() const throw (Block_Error);
      bool is_Unified_Ideograph() const throw (Block_Error);
      bool is_Other_Default_Ignorable_Code_Point() const throw (Block_Error);
      bool is_Deprecated() const throw (Block_Error);
      bool is_Soft_Dotted() const throw (Block_Error);
      bool is_Logical_Order_Exception() const throw (Block_Error);
      bool is_Other_ID_Start() const throw (Block_Error);
      // Derived Properties
      bool is_Math() const throw (Block_Error);
      bool is_Alphabetic() const throw (Block_Error);
      bool is_Lowercase() const throw (Block_Error);
      bool is_Uppercase() const throw (Block_Error);
      bool is_ID_Start() const throw (Block_Error);
      bool is_ID_Continue() const throw (Block_Error);
      bool is_XID_Start() const throw (Block_Error);
      bool is_XID_Continue() const throw (Block_Error);
      bool is_Default_Ignorable_Code_Point() const throw (Block_Error);
      bool is_Grapheme_Extend() const throw (Block_Error);
      bool is_Grapheme_Base() const throw (Block_Error);
      bool is_FC_NFKC_Closure() const throw (Block_Error);
      bool is_Full_Composition_Exclusion() const throw (Block_Error);
      bool is_NFD_QuickCheck() const throw (Block_Error);
      bool is_NFC_QuickCheck() const throw (Block_Error);
      bool is_NFKD_QuickCheck() const throw (Block_Error);
      bool is_NFKC_QuickCheck() const throw (Block_Error);
      bool is_Expands_On_NFD() const throw (Block_Error);
      bool is_Expands_On_NFC() const throw (Block_Error);
      bool is_Expands_On_NFKD() const throw (Block_Error);
      bool is_Expands_On_NFKC() const throw (Block_Error);
      // Further Properties
      bool is_Space() const throw (Block_Error);
      bool is_Punctuation() const throw (Block_Error);
      bool is_Line_Separator() const throw (Block_Error);
      bool is_Paragraph_Separator() const throw (Block_Error);
      bool is_Currency_Symbol() const throw (Block_Error);
      bool is_Bidi_Left_to_Right() const throw (Block_Error);
      bool is_Bidi_European_Digit() const throw (Block_Error);
      bool is_Bidi_Eur_Num_Separator() const throw (Block_Error);
      bool is_Bidi_Eur_Num_Terminator() const throw (Block_Error);
      bool is_Bidi_Arabic_Digit() const throw (Block_Error);
      bool is_Bidi_Common_Separator() const throw (Block_Error);
      bool is_Bidi_Block_Separator() const throw (Block_Error);
      bool is_Bidi_Segment_Separator() const throw (Block_Error);
      bool is_Bidi_Whitespace() const throw (Block_Error);
      bool is_Bidi_Non_spacing_Mark() const throw (Block_Error);
      bool is_Bidi_Boundary_Neutral() const throw (Block_Error);
      bool is_Bidi_PDF() const throw (Block_Error);
      bool is_Bidi_Embedding_or_Override() const throw (Block_Error);
      bool is_Bidi_Other_Neutral() const throw (Block_Error);
      bool is_Virama() const throw (Block_Error);
      bool is_Printable() const throw (Block_Error);
      bool is_Titlecase() const throw (Block_Error);
      bool is_Private_Use() const throw (Block_Error);

      bool is_Control() const throw (Block_Error);
      bool is_hangul_L() const throw (Block_Error);
      bool is_hangul_V() const throw (Block_Error);
      bool is_hangul_T() const throw (Block_Error);
      bool is_hangul_LV() const throw (Block_Error);
      bool is_hangul_LVT() const throw (Block_Error);
      
      // ------------------------------------------------------------
      // TRANSFORMATIONS:
      // ------------------------------------------------------------
      
      //. Turns ths character to lowercase.
      //. Leaves it as it is if there is no lowercase equivalent defined
      //. for it.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      void to_lower() throw (Block_Error);
      
      //. Turns ths character to uppercase.
      //. Leaves it as it is if there is no lowercase equivalent defined
      //. for it.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      void to_upper() throw (Block_Error);
      
      //. Turns ths character to titlecase.
      //. Leaves it as it is if there is no lowercase equivalent defined
      //. for it.
      //. Throws : Block_Error
      //.          if the block containing the character
      //.          could not get loaded.
      //.          THIS SHOULD NEVER HAPPEN!
      void to_title() throw (Block_Error);
      
      // ------------------------------------------------------------
      // CONSTRUCTORS:
      // ------------------------------------------------------------

      Char() : my_value(Babylon::UC_NULL) { }
      // Char(const std::string &, size_t &,
      //     const std::string format = Babylon::UTF8_format);
      Char(const UCS4 uc) : my_value(uc) { }
      Char(const Char & uc) : my_value(uc.value()) { }
      Char(const std::string &, size_t & pos,
	   const std::string format = Babylon::UTF8_format);
      
      bool equal(Char uc) const { return my_value == uc.my_value;}
      bool less(Char uc) const { return my_value < uc.my_value;}
      // ------------------------------------------------------------
      // OPERATORS:
      // ------------------------------------------------------------
      //. The relational operators look at the unicode values
      //. ONLY! So semantically identical characters will not be
      //. recognized.
      bool operator == (Char uc) const { return my_value == uc.my_value;}
      bool operator != (Char uc) const { return my_value != uc.my_value;}
      bool operator < (Char uc) const { return my_value < uc.my_value;}
      bool operator > (Char uc) const { return my_value > uc.my_value;}
      bool operator <= (Char uc) const { return my_value <= uc.my_value;}
      bool operator >= (Char uc) const { return my_value >= uc.my_value;}
      Char &operator = (Char uc) { my_value = uc.my_value; return *this;}
      Char &operator = (UCS4 uc) { my_value = uc; return *this;}
      Char &operator = (char c) { my_value = UCS4(c); return *this;}
      Char &operator = (int i) { my_value = UCS4(i); return *this;}
      Char operator ++ (int) { Char before(*this); my_value++; return before;}
      Char operator -- (int) { Char before(*this); my_value--; return before;}
      Char &operator ++ () { my_value++; return *this;}
      Char &operator -- () { my_value--; return *this;}
      Char &operator += (Char uc) { my_value += uc.my_value; return *this;}
      Char &operator += (UCS4 uc) { my_value += uc; return *this;}
      Char &operator += (int i) { my_value += UCS4(i); return *this;}
      Char &operator += (char c) { my_value += UCS4(c); return *this;}
      Char &operator -= (Char uc) { my_value -= uc.my_value; return *this;}
      Char &operator -= (UCS4 uc) { my_value -= uc; return *this;}
      Char &operator -= (int i) { my_value -= UCS4(i); return *this;}
      Char &operator -= (char c) { my_value -= UCS4(c); return *this;}
      Char &operator *= (Char uc) { my_value *= uc.my_value; return *this;}
      Char &operator *= (UCS4 uc) { my_value *= uc; return *this;}
      Char &operator *= (int i) { my_value *= UCS4(i); return *this;}
      Char &operator *= (char c) { my_value *= UCS4(c); return *this;}
      Char &operator /= (Char uc) { my_value /= uc.my_value; return *this;}
      Char &operator /= (UCS4 uc) { my_value /= uc; return *this;}
      Char &operator /= (int i) { my_value /= UCS4(i); return *this;}
      Char &operator /= (char c) { my_value /= UCS4(c); return *this;}
      Char &operator + (Char uc) { my_value += uc.my_value; return *this; }
      Char &operator + (UCS4 uc) { my_value += uc; return *this; }
      Char &operator + (int i) { my_value += i; return *this; }
      Char &operator + (char c) { my_value += c; return *this; }
      Char &operator - (Char uc) { my_value -= uc.my_value; return *this; }
      Char &operator - (UCS4 uc) { my_value -= uc; return *this; }
      Char &operator - (int i) { my_value -= i; return *this; }
      Char &operator - (char c) { my_value -= c; return *this; }
      Char &operator * (Char uc) { my_value *= uc.my_value; return *this; }
      Char &operator * (UCS4 uc) { my_value *= uc; return *this; }
      Char &operator * (int i) { my_value *= i; return *this; }
      Char &operator * (char c) { my_value *= c; return *this; }
      Char &operator / (Char uc) { my_value /= uc.my_value; return *this; }
      Char &operator / (UCS4 uc) { my_value /= uc; return *this; }
      Char &operator / (int i) { my_value /= i; return *this; }
      Char &operator / (char c) { my_value /= c; return *this; }
      
    private:
      void iconv_wrapper(const std::string &, const char *, size_t &,
			 const std::string &, char *, size_t &) const;
      
      UCS4 my_value;
  }; // class Char

}; // namespace Babylon

#endif // _Babylon_Char_hh
