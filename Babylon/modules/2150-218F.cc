/*$Id: 2150-218F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:12:33 +0100.
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
 
  class Number_Forms2150 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Number_Forms2150() {
      my_first_letter = 0x2150;
      my_last_letter  = 0x218F;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Number_Forms2150() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Number Forms";
    }

    bool isDefined(const UCS4 & _uc) const {
      return (isdefined[_uc - my_first_letter]);
    }

    UCS4 uppercase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Number_Forms2150::upper[_uc - my_first_letter];
    }

    UCS4 lowercase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Number_Forms2150::lower[_uc - my_first_letter];
    }

    UCS4 titlecase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Number_Forms2150::title[_uc - my_first_letter];
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
      switch(_uc) {
      case 0x2153:
        return 0.333333;
        break;
      case 0x2154:
        return 0.666667;
        break;
      case 0x2155:
        return 0.200000;
        break;
      case 0x2156:
        return 0.400000;
        break;
      case 0x2157:
        return 0.600000;
        break;
      case 0x2158:
        return 0.800000;
        break;
      case 0x2159:
        return 0.166667;
        break;
      case 0x215A:
        return 0.833333;
        break;
      case 0x215B:
        return 0.125000;
        break;
      case 0x215C:
        return 0.375000;
        break;
      case 0x215D:
        return 0.625000;
        break;
      case 0x215E:
        return 0.875000;
        break;
      case 0x215F:
        return 1.000000;
        break;
      case 0x2160:
        return 1.000000;
        break;
      case 0x2161:
        return 2.000000;
        break;
      case 0x2162:
        return 3.000000;
        break;
      case 0x2163:
        return 4.000000;
        break;
      case 0x2164:
        return 5.000000;
        break;
      case 0x2165:
        return 6.000000;
        break;
      case 0x2166:
        return 7.000000;
        break;
      case 0x2167:
        return 8.000000;
        break;
      case 0x2168:
        return 9.000000;
        break;
      case 0x2169:
        return 10.000000;
        break;
      case 0x216A:
        return 11.000000;
        break;
      case 0x216B:
        return 12.000000;
        break;
      case 0x216C:
        return 50.000000;
        break;
      case 0x216D:
        return 100.000000;
        break;
      case 0x216E:
        return 500.000000;
        break;
      case 0x216F:
        return 1000.000000;
        break;
      case 0x2170:
        return 1.000000;
        break;
      case 0x2171:
        return 2.000000;
        break;
      case 0x2172:
        return 3.000000;
        break;
      case 0x2173:
        return 4.000000;
        break;
      case 0x2174:
        return 5.000000;
        break;
      case 0x2175:
        return 6.000000;
        break;
      case 0x2176:
        return 7.000000;
        break;
      case 0x2177:
        return 8.000000;
        break;
      case 0x2178:
        return 9.000000;
        break;
      case 0x2179:
        return 10.000000;
        break;
      case 0x217A:
        return 11.000000;
        break;
      case 0x217B:
        return 12.000000;
        break;
      case 0x217C:
        return 50.000000;
        break;
      case 0x217D:
        return 100.000000;
        break;
      case 0x217E:
        return 500.000000;
        break;
      case 0x217F:
        return 1000.000000;
        break;
      case 0x2180:
        return 1000.000000;
        break;
      case 0x2181:
        return 5000.000000;
        break;
      case 0x2182:
        return 10000.000000;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(Number_Forms2150::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Number_Forms2150::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Number_Forms2150::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Number_Forms2150::decompStr[_uc - my_first_letter][0];
      us[1] = Number_Forms2150::decompStr[_uc - my_first_letter][1];

      switch (_uc) {

      case 0x2153:
        us.resize(3);
        us[2] = 0x0033;
        break;

      case 0x2154:
        us.resize(3);
        us[2] = 0x0033;
        break;

      case 0x2155:
        us.resize(3);
        us[2] = 0x0035;
        break;

      case 0x2156:
        us.resize(3);
        us[2] = 0x0035;
        break;

      case 0x2157:
        us.resize(3);
        us[2] = 0x0035;
        break;

      case 0x2158:
        us.resize(3);
        us[2] = 0x0035;
        break;

      case 0x2159:
        us.resize(3);
        us[2] = 0x0036;
        break;

      case 0x215A:
        us.resize(3);
        us[2] = 0x0036;
        break;

      case 0x215B:
        us.resize(3);
        us[2] = 0x0038;
        break;

      case 0x215C:
        us.resize(3);
        us[2] = 0x0038;
        break;

      case 0x215D:
        us.resize(3);
        us[2] = 0x0038;
        break;

      case 0x215E:
        us.resize(3);
        us[2] = 0x0038;
        break;

      case 0x2162:
        us.resize(3);
        us[2] = 0x0049;
        break;

      case 0x2166:
        us.resize(3);
        us[2] = 0x0049;
        break;

      case 0x2167:
        us.resize(4);
        us[2] = 0x0049;
        us[3] = 0x0049;
        break;

      case 0x216B:
        us.resize(3);
        us[2] = 0x0049;
        break;

      case 0x2172:
        us.resize(3);
        us[2] = 0x0069;
        break;

      case 0x2176:
        us.resize(3);
        us[2] = 0x0069;
        break;

      case 0x2177:
        us.resize(4);
        us[2] = 0x0069;
        us[3] = 0x0069;
        break;

      case 0x217B:
        us.resize(3);
        us[2] = 0x0069;
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
      return Babylon::Line_Break(Number_Forms2150::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(Number_Forms2150::ea[_uc - my_first_letter]);
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
      return Number_Forms2150::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return Number_Forms2150::Identifier_Part[_uc - my_first_letter];
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
      return Number_Forms2150::Uppercase[_uc - my_first_letter];
    }

    bool is_Lowercase(const UCS4 & _uc) const {
      return Number_Forms2150::Lowercase[_uc - my_first_letter];
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
    Number_Forms2150(const Number_Forms2150 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[64];
    static const UCS4 upper[64];
    static const UCS4 lower[64];
    static const UCS4 title[64];
    static const unsigned char cat[64];
    static const unsigned char bidir[64];
    static const unsigned char decomp[64];
    static const UCS2 decompStr[64][2];
    static const unsigned char lb[64];
    static const unsigned char ea[64];
    static const bool Alphabetic[64];
    static const bool Identifier_Part[64];
    static const bool Uppercase[64];
    static const bool Lowercase[64];

  }; // class Number_Forms2150

  const bool Number_Forms2150::isdefined[] = {
    0, 0, 0, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const UCS4 Number_Forms2150::upper[] = {
    0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
    0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
    0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
    0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
    0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
    0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
  };

  const UCS4 Number_Forms2150::lower[] = {
    0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
    0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
    0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 0x2176, 0x2177, 
    0x2178, 0x2179, 0x217A, 0x217B, 0x217C, 0x217D, 0x217E, 0x217F, 
    0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 0x2176, 0x2177, 
    0x2178, 0x2179, 0x217A, 0x217B, 0x217C, 0x217D, 0x217E, 0x217F, 
    0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
    0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
  };

  const UCS4 Number_Forms2150::title[] = {
    0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
    0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
    0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
    0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
    0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
    0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
  };

  const unsigned char Number_Forms2150::cat[] = {
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No
  };

  const unsigned char Number_Forms2150::bidir[] = {
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
  };

  const unsigned char Number_Forms2150::decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, 
    DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Number_Forms2150::decompStr[][2] = {
    { 0x2150, 0x0000 }, { 0x2151, 0x0000 }, { 0x2152, 0x0000 }, { 0x0031, 0x2044 }, 
    { 0x0032, 0x2044 }, { 0x0031, 0x2044 }, { 0x0032, 0x2044 }, { 0x0033, 0x2044 }, 
    { 0x0034, 0x2044 }, { 0x0031, 0x2044 }, { 0x0035, 0x2044 }, { 0x0031, 0x2044 }, 
    { 0x0033, 0x2044 }, { 0x0035, 0x2044 }, { 0x0037, 0x2044 }, { 0x0031, 0x2044 }, 
    { 0x0049, 0x0000 }, { 0x0049, 0x0049 }, { 0x0049, 0x0049 }, { 0x0049, 0x0056 }, 
    { 0x0056, 0x0000 }, { 0x0056, 0x0049 }, { 0x0056, 0x0049 }, { 0x0056, 0x0049 }, 
    { 0x0049, 0x0058 }, { 0x0058, 0x0000 }, { 0x0058, 0x0049 }, { 0x0058, 0x0049 }, 
    { 0x004C, 0x0000 }, { 0x0043, 0x0000 }, { 0x0044, 0x0000 }, { 0x004D, 0x0000 }, 
    { 0x0069, 0x0000 }, { 0x0069, 0x0069 }, { 0x0069, 0x0069 }, { 0x0069, 0x0076 }, 
    { 0x0076, 0x0000 }, { 0x0076, 0x0069 }, { 0x0076, 0x0069 }, { 0x0076, 0x0069 }, 
    { 0x0069, 0x0078 }, { 0x0078, 0x0000 }, { 0x0078, 0x0069 }, { 0x0078, 0x0069 }, 
    { 0x006C, 0x0000 }, { 0x0063, 0x0000 }, { 0x0064, 0x0000 }, { 0x006D, 0x0000 }, 
    { 0x2180, 0x0000 }, { 0x2181, 0x0000 }, { 0x2182, 0x0000 }, { 0x2183, 0x0000 }, 
    { 0x2184, 0x0000 }, { 0x2185, 0x0000 }, { 0x2186, 0x0000 }, { 0x2187, 0x0000 }, 
    { 0x2188, 0x0000 }, { 0x2189, 0x0000 }, { 0x218A, 0x0000 }, { 0x218B, 0x0000 }, 
    { 0x218C, 0x0000 }, { 0x218D, 0x0000 }, { 0x218E, 0x0000 }, { 0x218F, 0x0000 }
  };

  const unsigned char Number_Forms2150::lb[] = {
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AI, LB_AL, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
  };

  const unsigned char Number_Forms2150::ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bool Number_Forms2150::Alphabetic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Number_Forms2150::Identifier_Part[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Number_Forms2150::Uppercase[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Number_Forms2150::Lowercase[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Number_Forms2150);
