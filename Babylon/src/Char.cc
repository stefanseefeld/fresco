/*
 *$Id$
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

#include <Babylon/Char.hh>
#include <Babylon/String.hh>
#include <Babylon/internal/Dictionary.hh>
#include <Babylon/internal/utfstrings.hh>

#include <Prague/Sys/Tracer.hh>

#include <memory>

extern "C"
{
#include <iconv.h>
}

// Conversion:

std::string Babylon::Char::convert(const std::string format) const
    throw (Transfer_Error)
{
    Prague::Trace trace("Babylon::Char::convert(OUT OF Babylon)");

    // prepare input buffer
    size_t in_bound(sizeof(UCS4));

    // prepare output buffer
    // 16Byte should be more then enough to encode two characters;-)
    std::vector<char> out_buf(16);
    size_t out_bound(16);

    iconv_wrapper(Babylon::internal_format,
          reinterpret_cast<const char *>(&my_value), in_bound,
          format, &out_buf[0], out_bound);
    
    // put result into a string
    std::string result(&out_buf[0], 16 - out_bound);
    
    return result;
}

size_t Babylon::Char::convert(const std::string & s,
                  const size_t pos,
                  const std::string format)
    throw (Transfer_Error)
{
    Prague::Trace trace("Babylon::Char::convert(INTO babylon)");
    
    // check whether start position is valid.
    if (pos >= s.length())
    {
    my_value = Babylon::UC_NULL;
    return(std::string::npos);
    }

    // prepare input buffer
    size_t in_bound(s.length() - pos);
    
    // prepare output buffer
    UCS4 c;
    size_t out_bound(sizeof(UCS4));

    iconv_wrapper(format, s.data() + pos, in_bound,
          Babylon::internal_format,
          reinterpret_cast<char *>(&c), out_bound);

    my_value = c;
    return (0 == in_bound) ? std::string::npos : s.length() - in_bound;
}

void Babylon::Char::iconv_wrapper(const std::string & in_format,
                  const char * in_buf,
                  size_t & in_buf_size,
                  const std::string & out_format,
                  char * out_buf,
                  size_t & out_buf_size) const
{
    // Setup iconv
    iconv_t cd = iconv_open(out_format.c_str(), in_format.c_str());

    if (iconv_t(-1) == cd)
    throw Trans_Error(Babylon::TRANS_ICONV_FAILED);

    // convert
    size_t retval = iconv(cd,
              const_cast<char **>(&in_buf), &in_buf_size,
              &out_buf, &out_buf_size);

    if (-1 == retval)
    {
        if (E2BIG != errno) throw Trans_Error(Babylon::TRANS_ICONV_FAILED);
    }

    // clean up iconv
    iconv_close(cd);
}

// TRANSFORMATIONS:
void Babylon::Char::to_lower()
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Char::to_lower()");
    *this = this->lowercase();
} // to_lowercase

void Babylon::Char::to_upper()
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Char::to_upper()");
    
    *this = this->uppercase();
} // to_uppercase

void Babylon::Char::to_title()
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Char::to_title()");

    *this = this->titlecase();
} // to_titlecase

Babylon::String Babylon::Char::decompose() const
    throw (Undefined_Property, Block_Error)
{
    String r;
    get_from_UTF32(Dictionary::instance()->decompose(my_value), r);
    return r;
} // decompose

bool Babylon::Char::exclude_from_composition() const
    throw (Block_Error)
{
    return Dictionary::instance()->exclude_from_composition(my_value);
}

Babylon::Char Babylon::Char::uppercase() const throw (Block_Error)
{
  return Dictionary::instance()->uppercase(my_value);
}

Babylon::Char Babylon::Char::lowercase() const throw (Block_Error)
{
    return Dictionary::instance()->lowercase(my_value);
}

Babylon::Char Babylon::Char::titlecase() const throw (Block_Error)
{
    return Dictionary::instance()->titlecase(my_value);
}

float Babylon::Char::numeric_value() const
    throw (Undefined_Property, Block_Error)
{
    return Dictionary::instance()->numeric_value(my_value);
}

int Babylon::Char::digit_value() const
    throw (Undefined_Property, Block_Error)
{
    return Dictionary::instance()->digit_value(my_value);
}

int Babylon::Char::dec_digit_value() const
    throw (Undefined_Property, Block_Error)
{
    return Dictionary::instance()->dec_digit_value(my_value);
}

bool Babylon::Char::is_Digit() const throw (Block_Error)
{
    return Dictionary::instance()->is_Digit(my_value);
}

bool Babylon::Char::is_Numeric() const throw (Block_Error)
{
    return Dictionary::instance()->is_Numeric(my_value);
}

bool Babylon::Char::is_Decimal_Digit() const throw (Block_Error)
{
    return Dictionary::instance()->is_Decimal_Digit(my_value);
}

std::string Babylon::Char::blockname() const throw (Block_Error)
{
    return Dictionary::instance()->blockname(my_value);
}

Babylon::Gen_Cat Babylon::Char::category() const
    throw (Undefined_Property, Block_Error)
{
    return Dictionary::instance()->category(my_value);
}

Babylon::Bidir_Props Babylon::Char::direction() const
    throw (Undefined_Property, Block_Error)
{
    return Dictionary::instance()->bidir_props(my_value);
}

Babylon::Can_Comb_Class Babylon::Char::comb_class() const
    throw (Undefined_Property, Block_Error)
{
    return Dictionary::instance()->comb_class(my_value);
}

Babylon::Char_Decomp Babylon::Char::decomp_type() const
    throw (Undefined_Property, Block_Error)
{
    return Dictionary::instance()->decomp_type(my_value);
}

bool Babylon::Char::must_mirror() const
    throw (Undefined_Property, Block_Error)
{
    return Dictionary::instance()->must_mirror(my_value);
}

Babylon::EA_Width  Babylon::Char::EA_width() const
    throw (Undefined_Property, Block_Error)
{
    return Dictionary::instance()->EA_width(my_value);
}

Babylon::Line_Break Babylon::Char::linebreak() const
    throw (Undefined_Property, Block_Error)
{
    return Dictionary::instance()->linebreak(my_value);
}

bool Babylon::Char::is_defined() const 
    throw (Block_Error)
{
    return Dictionary::instance()->is_defined(my_value);
}

// Properties
bool Babylon::Char::is_White_Space() const throw (Block_Error)
{
    return Dictionary::instance()->is_White_Space(my_value);
}

bool Babylon::Char::is_Bidi_Control() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Control(my_value);
}

bool Babylon::Char::is_Join_Control() const throw (Block_Error)
{
    return Dictionary::instance()->is_Join_Control(my_value);
}

bool Babylon::Char::is_Dash() const throw (Block_Error)
{
    return Dictionary::instance()->is_Dash(my_value);
}

bool Babylon::Char::is_Hyphen() const throw (Block_Error)
{
    return Dictionary::instance()->is_Hyphen(my_value);
}

bool Babylon::Char::is_Quotation_Mark() const throw (Block_Error)
{
    return Dictionary::instance()->is_Quotation_Mark(my_value);
}

bool Babylon::Char::is_Terminal_Punctuation() const throw (Block_Error)
{
    return Dictionary::instance()->is_Terminal_Punctuation(my_value);
}

bool Babylon::Char::is_Other_Math() const throw (Block_Error)
{
    return Dictionary::instance()->is_Other_Math(my_value);
}

bool Babylon::Char::is_Hex_Digit() const throw (Block_Error)
{
    return Dictionary::instance()->is_Hex_Digit(my_value);
}

bool Babylon::Char::is_ASCII_Hex_Digit() const throw (Block_Error)
{
    return Dictionary::instance()->is_ASCII_Hex_Digit(my_value);
}

bool Babylon::Char::is_Other_Alphabetic() const throw (Block_Error)
{
    return Dictionary::instance()->is_Other_Alphabetic(my_value);
}

bool Babylon::Char::is_Ideographic() const throw (Block_Error)
{
    return Dictionary::instance()->is_Ideographic(my_value);
}

bool Babylon::Char::is_Diacritic() const throw (Block_Error)
{
    return Dictionary::instance()->is_Diacritic(my_value);
}

bool Babylon::Char::is_Extender() const throw (Block_Error)
{
    return Dictionary::instance()->is_Extender(my_value);
}

bool Babylon::Char::is_Other_Lowercase() const throw (Block_Error)
{
    return Dictionary::instance()->is_Other_Lowercase(my_value);
}

bool Babylon::Char::is_Other_Uppercase() const throw (Block_Error)
{
    return Dictionary::instance()->is_Other_Uppercase(my_value);
}

bool Babylon::Char::is_Noncharacter_Code_Point() const throw (Block_Error)
{
    return Dictionary::instance()->is_Noncharacter_Code_Point(my_value);
}

bool Babylon::Char::is_Other_Grapheme_Extend() const throw (Block_Error)
{
    return Dictionary::instance()->is_Other_Grapheme_Extend(my_value);
}

bool Babylon::Char::is_Grapheme_Link() const throw (Block_Error)
{
    return Dictionary::instance()->is_Grapheme_Link(my_value);
}

bool Babylon::Char::is_IDS_Binary_Operator() const throw (Block_Error)
{
    return Dictionary::instance()->is_IDS_Binary_Operator(my_value);
}

bool Babylon::Char::is_IDS_Trinary_Operator() const throw (Block_Error)
{
    return Dictionary::instance()->is_IDS_Trinary_Operator(my_value);
}

bool Babylon::Char::is_Radical() const throw (Block_Error)
{
    return Dictionary::instance()->is_Radical(my_value);
}

bool Babylon::Char::is_Unified_Ideograph() const throw (Block_Error)
{
    return Dictionary::instance()->is_Unified_Ideograph(my_value);
}

bool Babylon::Char::is_Other_Default_Ignorable_Code_Point() const
    throw (Block_Error)
{
    return Dictionary::instance()->
    is_Other_Default_Ignorable_Code_Point(my_value);
}

bool Babylon::Char::is_Deprecated() const throw (Block_Error)
{
    return Dictionary::instance()->is_Deprecated(my_value);
}

bool Babylon::Char::is_Soft_Dotted() const throw (Block_Error)
{
    return Dictionary::instance()->is_Soft_Dotted(my_value);
}

bool Babylon::Char::is_Logical_Order_Exception() const throw (Block_Error)
{
    return Dictionary::instance()->is_Logical_Order_Exception(my_value);
}

bool Babylon::Char::is_Other_ID_Start() const throw (Block_Error)
{
    return Dictionary::instance()->is_Other_ID_Start(my_value);
}

// Derived Properties
bool Babylon::Char::is_Math() const throw (Block_Error)
{
    return Dictionary::instance()->is_Math(my_value);
}

bool Babylon::Char::is_Alphabetic() const throw (Block_Error)
{
    return Dictionary::instance()->is_Alphabetic(my_value);
}

bool Babylon::Char::is_Lowercase() const throw (Block_Error)
{
    return Dictionary::instance()->is_Lowercase(my_value);
}

bool Babylon::Char::is_Uppercase() const throw (Block_Error)
{
    return Dictionary::instance()->is_Uppercase(my_value);
}

bool Babylon::Char::is_ID_Start() const throw (Block_Error)
{
    return Dictionary::instance()->is_ID_Start(my_value);
}

bool Babylon::Char::is_ID_Continue() const throw (Block_Error)
{
    return Dictionary::instance()->is_ID_Continue(my_value);
}

bool Babylon::Char::is_XID_Start() const throw (Block_Error)
{
    return Dictionary::instance()->is_XID_Start(my_value);
}

bool Babylon::Char::is_XID_Continue() const throw (Block_Error)
{
    return Dictionary::instance()->is_XID_Continue(my_value);
}

bool Babylon::Char::is_Default_Ignorable_Code_Point() const
    throw (Block_Error)
{
    return Dictionary::instance()->is_Default_Ignorable_Code_Point(my_value);
}

bool Babylon::Char::is_Grapheme_Extend() const throw (Block_Error)
{
    return Dictionary::instance()->is_Grapheme_Extend(my_value);
}

bool Babylon::Char::is_Grapheme_Base() const throw (Block_Error)
{
    return Dictionary::instance()->is_Grapheme_Base(my_value);
}

bool Babylon::Char::is_FC_NFKC_Closure() const throw (Block_Error)
{
    return Dictionary::instance()->is_FC_NFKC_Closure(my_value);
}

bool Babylon::Char::is_Full_Composition_Exclusion() const throw (Block_Error)
{
    return Dictionary::instance()->is_Full_Composition_Exclusion(my_value);
}

bool Babylon::Char::is_NFD_QuickCheck() const throw (Block_Error)
{
    return Dictionary::instance()->is_NFD_QuickCheck(my_value);
}

bool Babylon::Char::is_NFC_QuickCheck() const throw (Block_Error)
{
    return Dictionary::instance()->is_NFC_QuickCheck(my_value);
}

bool Babylon::Char::is_NFKD_QuickCheck() const throw (Block_Error)
{
    return Dictionary::instance()->is_NFKD_QuickCheck(my_value);
}

bool Babylon::Char::is_NFKC_QuickCheck() const throw (Block_Error)
{
    return Dictionary::instance()->is_NFKC_QuickCheck(my_value);
}

bool Babylon::Char::is_Expands_On_NFD() const throw (Block_Error)
{
    return Dictionary::instance()->is_Expands_On_NFD(my_value);
}

bool Babylon::Char::is_Expands_On_NFC() const throw (Block_Error)
{
    return Dictionary::instance()->is_Expands_On_NFC(my_value);
}

bool Babylon::Char::is_Expands_On_NFKD() const throw (Block_Error)
{
    return Dictionary::instance()->is_Expands_On_NFKD(my_value);
}

bool Babylon::Char::is_Expands_On_NFKC() const throw (Block_Error)
{
    return Dictionary::instance()->is_Expands_On_NFKC(my_value);
}

// Further Properties
bool Babylon::Char::is_Space() const throw (Block_Error)
{
    return Dictionary::instance()->is_Space(my_value);
}

bool Babylon::Char::is_Punctuation() const throw (Block_Error)
{
    return Dictionary::instance()->is_Punctuation(my_value);
}

bool Babylon::Char::is_Line_Separator() const throw (Block_Error)
{
    return Dictionary::instance()->is_Line_Separator(my_value);
}

bool Babylon::Char::is_Paragraph_Separator() const throw (Block_Error)
{
    return Dictionary::instance()->is_Paragraph_Separator(my_value);
}

bool Babylon::Char::is_Currency_Symbol() const throw (Block_Error)
{
    return Dictionary::instance()->is_Currency_Symbol(my_value);
}

bool Babylon::Char::is_Bidi_Left_to_Right() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Left_to_Right(my_value);
}

bool Babylon::Char::is_Bidi_European_Digit() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_European_Digit(my_value);
}

bool Babylon::Char::is_Bidi_Eur_Num_Separator() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Eur_Num_Separator(my_value);
}

bool Babylon::Char::is_Bidi_Eur_Num_Terminator() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Eur_Num_Terminator(my_value);
}

bool Babylon::Char::is_Bidi_Arabic_Digit() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Arabic_Digit(my_value);
}

bool Babylon::Char::is_Bidi_Common_Separator() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Common_Separator(my_value);
}

bool Babylon::Char::is_Bidi_Block_Separator() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Block_Separator(my_value);
}

bool Babylon::Char::is_Bidi_Segment_Separator() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Segment_Separator(my_value);
}

bool Babylon::Char::is_Bidi_Whitespace() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Whitespace(my_value);
}

bool Babylon::Char::is_Bidi_Non_spacing_Mark() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Non_spacing_Mark(my_value);
}

bool Babylon::Char::is_Bidi_Boundary_Neutral() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Boundary_Neutral(my_value);
}

bool Babylon::Char::is_Bidi_PDF() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_PDF(my_value);
}

bool Babylon::Char::is_Bidi_Embedding_or_Override() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Embedding_or_Override(my_value);
}

bool Babylon::Char::is_Bidi_Other_Neutral() const throw (Block_Error)
{
    return Dictionary::instance()->is_Bidi_Other_Neutral(my_value);
}

bool Babylon::Char::is_Virama() const throw (Block_Error)
{
    return Dictionary::instance()->is_Virama(my_value);
}

bool Babylon::Char::is_Printable() const throw (Block_Error)
{
    return Dictionary::instance()->is_Printable(my_value);
}

bool Babylon::Char::is_Titlecase() const throw (Block_Error)
{
    return Dictionary::instance()->is_Titlecase(my_value);
}

bool Babylon::Char::is_Private_Use() const throw (Block_Error)
{
    return Dictionary::instance()->is_Private_Use(my_value);
}

bool Babylon::Char::is_Control() const throw (Block_Error)
{
    Gen_Cat c = Dictionary::instance()->category(my_value);
    return (CAT_Zl == c || CAT_Zp == c || CAT_Cc == c || CAT_Cf == c);
}


bool Babylon::Char::is_hangul_L() const throw (Block_Error)
{
    if ((0x1100 <= my_value && 0x1159 >= my_value) ||
    0x115f == my_value) return 1;
    return 0;
}

bool Babylon::Char::is_hangul_V() const throw (Block_Error)
{
    if (0x1160 <= my_value && 0x11A2 >= my_value) return 1;
    return 0;
}

bool Babylon::Char::is_hangul_T() const throw (Block_Error)
{
    if (0x11A8 <= my_value && 0x11F9 >= my_value) return 1;
    return 0;
}

bool Babylon::Char::is_hangul_LV() const throw (Block_Error)
{
    if (!(0xAC00 <= my_value && 0xD788 >= my_value)) return 0;
    return (Dictionary::instance()->decompose(my_value).length() == 2);
}

bool Babylon::Char::is_hangul_LVT() const throw (Block_Error)
{
    if (!(0xAC01 <= my_value && 0xD7A3 >= my_value)) return 0;
    return (Dictionary::instance()->decompose(my_value).length() == 3);
}

Babylon::Char::Char(const std::string & s, size_t & pos,
            const std::string format)
{
    pos = convert(s, pos, format);
}
