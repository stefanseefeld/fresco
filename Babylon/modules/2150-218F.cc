/*$Id: 2150-218F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:25:18 +0100.
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
      _first_letter = 0x2150;
      _last_letter  = 0x218F;
      // _version="3.0.1" // Not yet supported!

    }


    ~Number_Forms2150() {
    }

    UCS4 firstLetter() {
      return _first_letter;
    }

    UCS4 lastLetter() {
      return _last_letter;
    }

    bool is_undef_block() const {
      return 0;
    }

    // query functions:

    string blockname(const UCS4 uc) const {
      return "Number Forms";
    }

    bool is_defined(const UCS4 uc) const {
      return (_is_defined[uc - _first_letter]);
    }

    UCS4 uppercase(const UCS4 uc) const {
      return Number_Forms2150::_upper[uc - _first_letter];
    }

    bool is_Uppercase(const UCS4 uc) const {
      return category(uc) == CAT_Lu;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return Number_Forms2150::_lower[uc - _first_letter];
    }

    bool is_Lowercase(const UCS4 uc) const {
      return category(uc) == CAT_Ll;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return Number_Forms2150::_title[uc - _first_letter];
    }

    bool is_Titlecase(const UCS4 uc) const {
      return category(uc) == CAT_Lt;
    }

    int dec_digit_value(const UCS4 uc) const {
      return 0;
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      return 0;
    }

    int digit_value(const UCS4 uc) const {
      return 0;
    }

    bool is_Digit(const UCS4 uc) const {
      return 0;
    }

    float numeric_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
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
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x2153:
      case 0x2154:
      case 0x2155:
      case 0x2156:
      case 0x2157:
      case 0x2158:
      case 0x2159:
      case 0x215A:
      case 0x215B:
      case 0x215C:
      case 0x215D:
      case 0x215E:
      case 0x215F:
      case 0x2160:
      case 0x2161:
      case 0x2162:
      case 0x2163:
      case 0x2164:
      case 0x2165:
      case 0x2166:
      case 0x2167:
      case 0x2168:
      case 0x2169:
      case 0x216A:
      case 0x216B:
      case 0x216C:
      case 0x216D:
      case 0x216E:
      case 0x216F:
      case 0x2170:
      case 0x2171:
      case 0x2172:
      case 0x2173:
      case 0x2174:
      case 0x2175:
      case 0x2176:
      case 0x2177:
      case 0x2178:
      case 0x2179:
      case 0x217A:
      case 0x217B:
      case 0x217C:
      case 0x217D:
      case 0x217E:
      case 0x217F:
      case 0x2180:
      case 0x2181:
      case 0x2182:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Number_Forms2150::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Number_Forms2150::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Number_Forms2150::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Number_Forms2150::_decompStr[uc - _first_letter][0];
      us[1] = Number_Forms2150::_decompStr[uc - _first_letter][1];

      switch (uc) {

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

    bool must_mirror(const UCS4 uc) const {
      return 0;
    }

    Line_Break linebreak(const UCS4 uc) const {
      if (!is_defined(uc))
        return LB_MAX;
      return Babylon::Line_Break(Number_Forms2150::_lb[uc - _first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(Number_Forms2150::_ea[uc - _first_letter]);
    }

    UCS4 compose (const UCS4 starter, const UCS4 last) {
      return 0;
    }

    bool is_Zero_width(const UCS4 uc) const {
      return 0;
    }

    bool is_White_space(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_break(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Join_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Format_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Dash(const UCS4 uc) const {
      return 0;
    }

    bool is_Hyphen(const UCS4 uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const UCS4 uc) const {
      return 0;
    }

    bool is_Math(const UCS4 uc) const {
      return 0;
    }

    bool is_Paired_Punctuation(const UCS4 uc) const {
      return 0;
    }

    bool is_Left_of_Pair(const UCS4 uc) const {
      return 0;
    }

    bool is_Combining(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_spacing(const UCS4 uc) const {
      return 0;
    }

    bool is_Composite(const UCS4 uc) const {
      return Number_Forms2150::_Composite[uc - _first_letter];
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Number_Forms2150::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Number_Forms2150::_Identifier_Part[uc - _first_letter];
    }

    bool is_Ignorable_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const UCS4 uc) const {
      return 0;
    }

    bool is_Ideographic(const UCS4 uc) const {
      return 0;
    }

    bool is_Private_Use(const UCS4 uc) const {
      return 0;
    }

    bool is_Not_a_Character(const UCS4 uc) const {
      return ((uc & 0xFFFE) == 0xFFFE);
    }

    bool is_Private_Use_High_Surrogate(const UCS4 uc) const {
      return 0;
    }

    bool is_Low_Surrogate(const UCS4 uc) const {
      return 0;
    }

    bool is_High_Surrogate(const UCS4 uc) const {
      return 0;
    }

    bool is_Space(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Zs);
    }

    bool is_ISO_Control(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Cc);
    }

    bool is_Punctuation(const UCS4 uc) const {
      return (is_defined(uc) && (category(uc) == CAT_Pc ||
                                 category(uc) == CAT_Pd ||
                                 category(uc) == CAT_Ps ||
                                 category(uc) == CAT_Pe ||
                                 category(uc) == CAT_Pi ||
                                 category(uc) == CAT_Pf ||
                                 category(uc) == CAT_Po)
             );
    }

    bool is_Line_Separator(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Zl);
    }

    bool is_Paragraph_Separator(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Zp);
    }

    bool is_Currency_Symbol(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Sc);
    }

    bool is_Bidi_Left_to_Right(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_L;
    }

    bool is_Bidi_European_Digit(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_EN;
    }

    bool is_Bidi_Eur_Num_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_ES;
    }

    bool is_Bidi_Eur_Num_Terminator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_ET;
    }

    bool is_Bidi_Arabic_Digit(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_AN;
    }

    bool is_Bidi_Common_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_CS;
    }

    bool is_Bidi_Block_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_B;
    }

    bool is_Bidi_Segment_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_S;
    }

    bool is_Bidi_Whitespace(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_WS;
    }

    bool is_Bidi_Non_spacing_Mark(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_NSM;
    }

    bool is_Bidi_Boundary_Neutral(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_BN;
    }

    bool is_Bidi_PDF(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_PDF;
    }

    bool is_Bidi_Embedding_or_Override(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_LRE ||
             bidir_props(uc) == BIDIR_RLE ||
             bidir_props(uc) == BIDIR_LRO ||
             bidir_props(uc) == BIDIR_RLO;
    }

    bool is_Bidi_LRE(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_LRE;
    }

    bool is_Bidi_RLE(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_RLE;
    }

    bool is_Bidi_LRO(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_LRO;
    }

    bool is_Bidi_RLO(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_RLO;
    }

    bool is_Bidi_Other_Neutral(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_ON;
    }

    bool is_Unassigned_Code_Value(const UCS4 uc) const {
      return !is_defined(uc) && !is_Not_a_Character(uc);
    }


  private:
    // functions
    Number_Forms2150(const Number_Forms2150 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[64];
    static const UCS4 _upper[64];
    static const UCS4 _lower[64];
    static const UCS4 _title[64];
    static const unsigned char _cat[64];
    static const unsigned char _bidir[64];
    static const unsigned char _decomp[64];
    static const UCS2 _decompStr[64][2];
    static const unsigned char _lb[64];
    static const unsigned char _ea[64];
    static const bool _Composite[64];
    static const bool _Alphabetic[64];
    static const bool _Identifier_Part[64];

  }; // class Number_Forms2150

  const bool Number_Forms2150::_is_defined[] = {
    0, 0, 0, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const UCS4 Number_Forms2150::_upper[] = {
    0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
    0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
    0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
    0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
    0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
    0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
  };

  const UCS4 Number_Forms2150::_lower[] = {
    0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
    0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
    0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 0x2176, 0x2177, 
    0x2178, 0x2179, 0x217A, 0x217B, 0x217C, 0x217D, 0x217E, 0x217F, 
    0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 0x2176, 0x2177, 
    0x2178, 0x2179, 0x217A, 0x217B, 0x217C, 0x217D, 0x217E, 0x217F, 
    0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
    0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
  };

  const UCS4 Number_Forms2150::_title[] = {
    0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
    0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
    0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
    0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
    0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
    0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
  };

  const unsigned char Number_Forms2150::_cat[] = {
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No
  };

  const unsigned char Number_Forms2150::_bidir[] = {
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
  };

  const unsigned char Number_Forms2150::_decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, 
    DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Number_Forms2150::_decompStr[][2] = {
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

  const unsigned char Number_Forms2150::_lb[] = {
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AI, LB_AL, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
  };

  const unsigned char Number_Forms2150::_ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bool Number_Forms2150::_Composite[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 0, 1, 1, 1, 
        1, 0, 1, 1, 0, 0, 0, 0, 
        0, 1, 1, 1, 0, 1, 1, 1, 
        1, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Number_Forms2150::_Alphabetic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Number_Forms2150::_Identifier_Part[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon

dload(Babylon::Number_Forms2150);
