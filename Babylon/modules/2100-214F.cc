/*$Id: 2100-214F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:12:31 +0100.
 *
 * This plugin to libPrague is free software; you can redistribute it
 * and/or  modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA
 */

#include <Babylon/defs.hh>
#include <Babylon/Dictionary.hh>

namespace Babylon {
 
  class Letterlike_Symbols2100 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Letterlike_Symbols2100() {
      my_first_letter = 0x2100;
      my_last_letter  = 0x214F;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Letterlike_Symbols2100() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Letterlike Symbols";
    }

    bool isDefined(const UCS4 & _uc) const {
      return (isdefined[_uc - my_first_letter]);
    }

    UCS4 uppercase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    UCS4 lowercase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Letterlike_Symbols2100::lower[_uc - my_first_letter];
    }

    UCS4 titlecase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    int decDigitValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_DEC_DIGIT_VALUE);
    }

    int digitValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_DIGIT_VALUE);
    }

    float numericValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(Letterlike_Symbols2100::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Letterlike_Symbols2100::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Letterlike_Symbols2100::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Letterlike_Symbols2100::decompStr[_uc - my_first_letter][0];
      us[1] = Letterlike_Symbols2100::decompStr[_uc - my_first_letter][1];

      switch (_uc) {

      case 0x2100:
        us.resize(3);
        us[2] = 0x0063;
        break;

      case 0x2101:
        us.resize(3);
        us[2] = 0x0073;
        break;

      case 0x2105:
        us.resize(3);
        us[2] = 0x006F;
        break;

      case 0x2106:
        us.resize(3);
        us[2] = 0x0075;
        break;

      case 0x2121:
        us.resize(3);
        us[2] = 0x004C;
        break;
      }
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool mustMirror(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return 0;
    }

    Line_Break linebreak(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Line_Break(Letterlike_Symbols2100::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(Letterlike_Symbols2100::ea[_uc - my_first_letter]);
    }

    UCS4 compose (const UCS4 & starter, const UCS4 & last) {
      return 0;
    }

    bool is_Zero_width(const UCS4 & _uc) const {
      return 0;
    }

    bool is_White_space(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Non_break(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Join_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Format_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Dash(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Hyphen(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Math(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Paired_Punctuation(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Left_of_Pair(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Combining(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return Letterlike_Symbols2100::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return Letterlike_Symbols2100::Identifier_Part[_uc - my_first_letter];
    }

    bool is_Ignorable_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Embedding_or_Override(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Uppercase(const UCS4 & _uc) const {
      return Letterlike_Symbols2100::Uppercase[_uc - my_first_letter];
    }

    bool is_Lowercase(const UCS4 & _uc) const {
      return Letterlike_Symbols2100::Lowercase[_uc - my_first_letter];
    }

    bool is_Space(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zs);
    }

    bool is_ISO_Control(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Cc);
    }

    bool is_Punctuation(const UCS4 & _uc) const {
      return (isDefined(_uc) && (category(_uc) == CAT_Pc ||
                                 category(_uc) == CAT_Pd ||
                                 category(_uc) == CAT_Ps ||
                                 category(_uc) == CAT_Pe ||
                                 category(_uc) == CAT_Pi ||
                                 category(_uc) == CAT_Pf ||
                                 category(_uc) == CAT_Po)
             );
    }

    bool is_Line_Separator(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zl);
    }

    bool is_Paragraph_Separator(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zp);
    }

    bool is_Currency_Symbol(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Sc);
    }

    bool is_Titlecase(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Lt);
    }


  private:
    // functions
    Letterlike_Symbols2100(const Letterlike_Symbols2100 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[80];
    static const UCS4 lower[80];
    static const unsigned char cat[80];
    static const unsigned char bidir[80];
    static const unsigned char decomp[80];
    static const UCS2 decompStr[80][2];
    static const unsigned char lb[80];
    static const unsigned char ea[80];
    static const bool Alphabetic[80];
    static const bool Identifier_Part[80];
    static const bool Uppercase[80];
    static const bool Lowercase[80];

  }; // class Letterlike_Symbols2100

  const bool Letterlike_Symbols2100::isdefined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const UCS4 Letterlike_Symbols2100::lower[] = {
    0x2100, 0x2101, 0x2102, 0x2103, 0x2104, 0x2105, 0x2106, 0x2107, 
    0x2108, 0x2109, 0x210A, 0x210B, 0x210C, 0x210D, 0x210E, 0x210F, 
    0x2110, 0x2111, 0x2112, 0x2113, 0x2114, 0x2115, 0x2116, 0x2117, 
    0x2118, 0x2119, 0x211A, 0x211B, 0x211C, 0x211D, 0x211E, 0x211F, 
    0x2120, 0x2121, 0x2122, 0x2123, 0x2124, 0x2125, 0x03C9, 0x2127, 
    0x2128, 0x2129, 0x006B, 0x00E5, 0x212C, 0x212D, 0x212E, 0x212F, 
    0x2130, 0x2131, 0x2132, 0x2133, 0x2134, 0x2135, 0x2136, 0x2137, 
    0x2138, 0x2139, 0x213A, 0x213B, 0x213C, 0x213D, 0x213E, 0x213F, 
    0x2140, 0x2141, 0x2142, 0x2143, 0x2144, 0x2145, 0x2146, 0x2147, 
    0x2148, 0x2149, 0x214A, 0x214B, 0x214C, 0x214D, 0x214E, 0x214F
  };

  const unsigned char Letterlike_Symbols2100::cat[] = {
    CAT_So, CAT_So, CAT_Lu, CAT_So, CAT_So, CAT_So, CAT_So, CAT_Lu, 
    CAT_So, CAT_So, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_So, CAT_Lu, CAT_So, CAT_So, 
    CAT_So, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_Lu, CAT_So, CAT_Lu, CAT_So, 
    CAT_Lu, CAT_So, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_So, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_So, CAT_Lu, CAT_Ll, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Ll, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So
  };

  const unsigned char Letterlike_Symbols2100::bidir[] = {
    BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, 
    BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_ON, 
    BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ET, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
  };

  const unsigned char Letterlike_Symbols2100::decomp[] = {
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_FONT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
    DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_NO_DECOMP, DECOMP_FONT, DECOMP_COMPAT, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_SUPER, DECOMP_COMPAT, DECOMP_SUPER, DECOMP_NO_DECOMP, DECOMP_FONT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_FONT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_FONT, DECOMP_FONT, DECOMP_NO_DECOMP, DECOMP_FONT, 
    DECOMP_FONT, DECOMP_FONT, DECOMP_NO_DECOMP, DECOMP_FONT, DECOMP_FONT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_FONT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Letterlike_Symbols2100::decompStr[][2] = {
    { 0x0061, 0x002F }, { 0x0061, 0x002F }, { 0x0043, 0x0000 }, { 0x00B0, 0x0043 }, 
    { 0x2104, 0x0000 }, { 0x0063, 0x002F }, { 0x0063, 0x002F }, { 0x0190, 0x0000 }, 
    { 0x2108, 0x0000 }, { 0x00B0, 0x0046 }, { 0x0067, 0x0000 }, { 0x0048, 0x0000 }, 
    { 0x0048, 0x0000 }, { 0x0048, 0x0000 }, { 0x0068, 0x0000 }, { 0x0127, 0x0000 }, 
    { 0x0049, 0x0000 }, { 0x0049, 0x0000 }, { 0x004C, 0x0000 }, { 0x006C, 0x0000 }, 
    { 0x2114, 0x0000 }, { 0x004E, 0x0000 }, { 0x004E, 0x006F }, { 0x2117, 0x0000 }, 
    { 0x2118, 0x0000 }, { 0x0050, 0x0000 }, { 0x0051, 0x0000 }, { 0x0052, 0x0000 }, 
    { 0x0052, 0x0000 }, { 0x0052, 0x0000 }, { 0x211E, 0x0000 }, { 0x211F, 0x0000 }, 
    { 0x0053, 0x004D }, { 0x0054, 0x0045 }, { 0x0054, 0x004D }, { 0x2123, 0x0000 }, 
    { 0x005A, 0x0000 }, { 0x2125, 0x0000 }, { 0x03A9, 0x0000 }, { 0x2127, 0x0000 }, 
    { 0x005A, 0x0000 }, { 0x2129, 0x0000 }, { 0x004B, 0x0000 }, { 0x00C5, 0x0000 }, 
    { 0x0042, 0x0000 }, { 0x0043, 0x0000 }, { 0x212E, 0x0000 }, { 0x0065, 0x0000 }, 
    { 0x0045, 0x0000 }, { 0x0046, 0x0000 }, { 0x2132, 0x0000 }, { 0x004D, 0x0000 }, 
    { 0x006F, 0x0000 }, { 0x05D0, 0x0000 }, { 0x05D1, 0x0000 }, { 0x05D2, 0x0000 }, 
    { 0x05D3, 0x0000 }, { 0x0069, 0x0000 }, { 0x213A, 0x0000 }, { 0x213B, 0x0000 }, 
    { 0x213C, 0x0000 }, { 0x213D, 0x0000 }, { 0x213E, 0x0000 }, { 0x213F, 0x0000 }, 
    { 0x2140, 0x0000 }, { 0x2141, 0x0000 }, { 0x2142, 0x0000 }, { 0x2143, 0x0000 }, 
    { 0x2144, 0x0000 }, { 0x2145, 0x0000 }, { 0x2146, 0x0000 }, { 0x2147, 0x0000 }, 
    { 0x2148, 0x0000 }, { 0x2149, 0x0000 }, { 0x214A, 0x0000 }, { 0x214B, 0x0000 }, 
    { 0x214C, 0x0000 }, { 0x214D, 0x0000 }, { 0x214E, 0x0000 }, { 0x214F, 0x0000 }
  };

  const unsigned char Letterlike_Symbols2100::lb[] = {
    LB_AL, LB_AL, LB_AL, LB_PO, LB_AL, LB_AI, LB_AL, LB_AL, 
    LB_AL, LB_PO, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_PR, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_PO, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
  };

  const unsigned char Letterlike_Symbols2100::ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bool Letterlike_Symbols2100::Alphabetic[] = {
        0, 0, 1, 0, 0, 0, 0, 1, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 1, 0, 0, 
        0, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 1, 0, 1, 0, 
        1, 0, 1, 1, 1, 1, 0, 1, 
        1, 1, 0, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Letterlike_Symbols2100::Identifier_Part[] = {
        0, 0, 1, 0, 0, 0, 0, 1, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 1, 0, 0, 
        0, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 1, 0, 1, 0, 
        1, 0, 1, 1, 1, 1, 0, 1, 
        1, 1, 0, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Letterlike_Symbols2100::Uppercase[] = {
        0, 0, 1, 0, 0, 0, 0, 1, 
        0, 0, 0, 1, 1, 1, 0, 0, 
        1, 1, 1, 0, 0, 1, 0, 0, 
        0, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 1, 0, 1, 0, 
        1, 0, 1, 1, 1, 1, 0, 0, 
        1, 1, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Letterlike_Symbols2100::Lowercase[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 0, 0, 0, 1, 1, 
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Letterlike_Symbols2100);
