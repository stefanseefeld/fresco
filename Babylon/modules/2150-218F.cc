/*$Id: 2150-218F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon,  8 Jan 2001 23:32:09 +0100.
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
#include <bitset>

namespace Babylon {

  class Number_Forms2150 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Number_Forms2150() {
      m_first_letter = 0x2150;
      m_last_letter  = 0x218F;
      // m_version="3.0.1" // Not yet supported!

    }


    ~Number_Forms2150() {
    }

    UCS4 firstLetter() {
      return m_first_letter;
    }

    UCS4 lastLetter() {
      return m_last_letter;
    }

    bool is_undef_block() const {
      return 0;
    }

    // query functions:

    string blockname(const UCS4 uc) const {
      return "Number Forms";
    }

    bool is_defined(const UCS4 uc) const {
      return (m_is_defined.test(uc - m_first_letter));
    }

    UCS4 uppercase(const UCS4 uc) const {
      return Number_Forms2150::m_upper[uc - m_first_letter];
    }

    UCS4 lowercase(const UCS4 uc) const {
      return Number_Forms2150::m_lower[uc - m_first_letter];
    }

    UCS4 titlecase(const UCS4 uc) const {
      return Number_Forms2150::m_title[uc - m_first_letter];
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
      return Babylon::Gen_Cat(Number_Forms2150::_cat[uc - m_first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Number_Forms2150::m_bidir[uc - m_first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Number_Forms2150::_decomp[uc - m_first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Number_Forms2150::m_decompStr[uc - m_first_letter][0];
      us[1] = Number_Forms2150::m_decompStr[uc - m_first_letter][1];

      switch (uc) {

      case 0x2153:
        us.resize(3);
        us[2u] = 0x0033u;
        break;

      case 0x2154:
        us.resize(3);
        us[2u] = 0x0033u;
        break;

      case 0x2155:
        us.resize(3);
        us[2u] = 0x0035u;
        break;

      case 0x2156:
        us.resize(3);
        us[2u] = 0x0035u;
        break;

      case 0x2157:
        us.resize(3);
        us[2u] = 0x0035u;
        break;

      case 0x2158:
        us.resize(3);
        us[2u] = 0x0035u;
        break;

      case 0x2159:
        us.resize(3);
        us[2u] = 0x0036u;
        break;

      case 0x215A:
        us.resize(3);
        us[2u] = 0x0036u;
        break;

      case 0x215B:
        us.resize(3);
        us[2u] = 0x0038u;
        break;

      case 0x215C:
        us.resize(3);
        us[2u] = 0x0038u;
        break;

      case 0x215D:
        us.resize(3);
        us[2u] = 0x0038u;
        break;

      case 0x215E:
        us.resize(3);
        us[2u] = 0x0038u;
        break;

      case 0x2162:
        us.resize(3);
        us[2u] = 0x0049u;
        break;

      case 0x2166:
        us.resize(3);
        us[2u] = 0x0049u;
        break;

      case 0x2167:
        us.resize(4);
        us[2u] = 0x0049u;
        us[3u] = 0x0049u;
        break;

      case 0x216B:
        us.resize(3);
        us[2u] = 0x0049u;
        break;

      case 0x2172:
        us.resize(3);
        us[2u] = 0x0069u;
        break;

      case 0x2176:
        us.resize(3);
        us[2u] = 0x0069u;
        break;

      case 0x2177:
        us.resize(4);
        us[2u] = 0x0069u;
        us[3u] = 0x0069u;
        break;

      case 0x217B:
        us.resize(3);
        us[2u] = 0x0069u;
        break;
      }
      if (us[1] == 0x0000u) {
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
      return Babylon::Line_Break(Number_Forms2150::m_lb[uc - m_first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(Number_Forms2150::m_ea[uc - m_first_letter]);
    }

    UCS4 compose (const UCS4 start, const UCS4 last) {
      return 0;
    }

    bool is_White_space(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_break(const UCS4 uc) const {
      return 0;
    }

    bool is_Format_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Join_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Format_Control(const UCS4 uc) const {
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

    bool is_Composite(const UCS4 uc) const {
      return m_Composite.test(uc - m_first_letter);
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return m_Alphabetic.test(uc - m_first_letter);
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part_Not_Cf(const UCS4 uc) const {
      return m_Identifier_Part_Not_Cf.test(uc - m_first_letter);
    }

    bool is_Other_Uppercase(const UCS4 uc) const {
      return m_Other_Uppercase.test(uc - m_first_letter);
    }

    bool is_Other_Lowercase(const UCS4 uc) const {
      return m_Other_Lowercase.test(uc - m_first_letter);
    }

    bool is_Ideographic(const UCS4 uc) const {
      return 0;
    }

    bool is_Private_Use(const UCS4 uc) const {
      return 0;
    }

    bool is_Noncharacter_Code_Point(const UCS4 uc) const {
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


  private:
    // functions
    Number_Forms2150(const Number_Forms2150 &) {}

    Babylon::UCS4 m_first_letter;
    Babylon::UCS4 m_last_letter;
    // Babylon::UCS4_string m_version;
    static const bitset<64> m_is_defined;
    static const UCS4 m_upper[64];
    static const UCS4 m_lower[64];
    static const UCS4 m_title[64];
    static const unsigned char _cat[64];
    static const unsigned char m_bidir[64];
    static const unsigned char _decomp[64];
    static const UCS2 m_decompStr[64][2];
    static const unsigned char m_lb[64];
    static const unsigned char m_ea[64];
    static const bitset<64> m_Composite;
    static const bitset<64> m_Alphabetic;
    static const bitset<64> m_Identifier_Part_Not_Cf;
    static const bitset<64> m_Other_Uppercase;
    static const bitset<64> m_Other_Lowercase;

  }; // class Number_Forms2150

    const bitset<64> Number_Forms2150::m_is_defined(string("0000000000001111111111111111111111111111111111111111111111111000"));

  const UCS4 Number_Forms2150::m_upper[] = {
    0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
    0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
    0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
    0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
    0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
    0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
  };

  const UCS4 Number_Forms2150::m_lower[] = {
    0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
    0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
    0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 0x2176, 0x2177, 
    0x2178, 0x2179, 0x217A, 0x217B, 0x217C, 0x217D, 0x217E, 0x217F, 
    0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 0x2176, 0x2177, 
    0x2178, 0x2179, 0x217A, 0x217B, 0x217C, 0x217D, 0x217E, 0x217F, 
    0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
    0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
  };

  const UCS4 Number_Forms2150::m_title[] = {
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

  const unsigned char Number_Forms2150::m_bidir[] = {
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

  const UCS2 Number_Forms2150::m_decompStr[][2] = {
    { 0x2150u, 0x0000u }, { 0x2151u, 0x0000u }, { 0x2152u, 0x0000u }, { 0x0031u, 0x2044u }, 
    { 0x0032u, 0x2044u }, { 0x0031u, 0x2044u }, { 0x0032u, 0x2044u }, { 0x0033u, 0x2044u }, 
    { 0x0034u, 0x2044u }, { 0x0031u, 0x2044u }, { 0x0035u, 0x2044u }, { 0x0031u, 0x2044u }, 
    { 0x0033u, 0x2044u }, { 0x0035u, 0x2044u }, { 0x0037u, 0x2044u }, { 0x0031u, 0x2044u }, 
    { 0x0049u, 0x0000u }, { 0x0049u, 0x0049u }, { 0x0049u, 0x0049u }, { 0x0049u, 0x0056u }, 
    { 0x0056u, 0x0000u }, { 0x0056u, 0x0049u }, { 0x0056u, 0x0049u }, { 0x0056u, 0x0049u }, 
    { 0x0049u, 0x0058u }, { 0x0058u, 0x0000u }, { 0x0058u, 0x0049u }, { 0x0058u, 0x0049u }, 
    { 0x004Cu, 0x0000u }, { 0x0043u, 0x0000u }, { 0x0044u, 0x0000u }, { 0x004Du, 0x0000u }, 
    { 0x0069u, 0x0000u }, { 0x0069u, 0x0069u }, { 0x0069u, 0x0069u }, { 0x0069u, 0x0076u }, 
    { 0x0076u, 0x0000u }, { 0x0076u, 0x0069u }, { 0x0076u, 0x0069u }, { 0x0076u, 0x0069u }, 
    { 0x0069u, 0x0078u }, { 0x0078u, 0x0000u }, { 0x0078u, 0x0069u }, { 0x0078u, 0x0069u }, 
    { 0x006Cu, 0x0000u }, { 0x0063u, 0x0000u }, { 0x0064u, 0x0000u }, { 0x006Du, 0x0000u }, 
    { 0x2180u, 0x0000u }, { 0x2181u, 0x0000u }, { 0x2182u, 0x0000u }, { 0x2183u, 0x0000u }, 
    { 0x2184u, 0x0000u }, { 0x2185u, 0x0000u }, { 0x2186u, 0x0000u }, { 0x2187u, 0x0000u }, 
    { 0x2188u, 0x0000u }, { 0x2189u, 0x0000u }, { 0x218Au, 0x0000u }, { 0x218Bu, 0x0000u }, 
    { 0x218Cu, 0x0000u }, { 0x218Du, 0x0000u }, { 0x218Eu, 0x0000u }, { 0x218Fu, 0x0000u }
  };

  const unsigned char Number_Forms2150::m_lb[] = {
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AI, LB_AL, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
  };

  const unsigned char Number_Forms2150::m_ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bitset<64> Number_Forms2150::m_Composite(string("0000000000000000000011011110111000001101111011101111111111111000"));

    const bitset<64> Number_Forms2150::m_Alphabetic(string("0000000000001111111111111111111111111111111111110000000000000000"));

    const bitset<64> Number_Forms2150::m_Identifier_Part_Not_Cf(string("0000000000001111111111111111111111111111111111110000000000000000"));

    const bitset<64> Number_Forms2150::m_Other_Uppercase(string("0000000000000000000000000000000011111111111111110000000000000000"));

    const bitset<64> Number_Forms2150::m_Other_Lowercase(string("0000000000000000111111111111111100000000000000000000000000000000"));

}; // namespace Babylon

dload(Babylon::Number_Forms2150);
