/*$Id: 2070-209F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon,  8 Jan 2001 23:32:06 +0100.
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

  class Superscripts_and_Subscripts2070 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Superscripts_and_Subscripts2070() {
      m_first_letter = 0x2070;
      m_last_letter  = 0x209F;
      // m_version="3.0.1" // Not yet supported!

    }


    ~Superscripts_and_Subscripts2070() {
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
      return "Superscripts and Subscripts";
    }

    bool is_defined(const UCS4 uc) const {
      return (m_is_defined.test(uc - m_first_letter));
    }

    UCS4 uppercase(const UCS4 uc) const {
      return uc;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return uc;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return uc;
    }

    int dec_digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x2070:
        return 0;
        break;
      case 0x2074:
        return 4;
        break;
      case 0x2075:
        return 5;
        break;
      case 0x2076:
        return 6;
        break;
      case 0x2077:
        return 7;
        break;
      case 0x2078:
        return 8;
        break;
      case 0x2079:
        return 9;
        break;
      case 0x2080:
        return 0;
        break;
      case 0x2081:
        return 1;
        break;
      case 0x2082:
        return 2;
        break;
      case 0x2083:
        return 3;
        break;
      case 0x2084:
        return 4;
        break;
      case 0x2085:
        return 5;
        break;
      case 0x2086:
        return 6;
        break;
      case 0x2087:
        return 7;
        break;
      case 0x2088:
        return 8;
        break;
      case 0x2089:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x2070:
      case 0x2074:
      case 0x2075:
      case 0x2076:
      case 0x2077:
      case 0x2078:
      case 0x2079:
      case 0x2080:
      case 0x2081:
      case 0x2082:
      case 0x2083:
      case 0x2084:
      case 0x2085:
      case 0x2086:
      case 0x2087:
      case 0x2088:
      case 0x2089:
        return 1;
      default:
        return 0;
      }
    }

    int digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x2070:
        return 0;
        break;
      case 0x2074:
        return 4;
        break;
      case 0x2075:
        return 5;
        break;
      case 0x2076:
        return 6;
        break;
      case 0x2077:
        return 7;
        break;
      case 0x2078:
        return 8;
        break;
      case 0x2079:
        return 9;
        break;
      case 0x2080:
        return 0;
        break;
      case 0x2081:
        return 1;
        break;
      case 0x2082:
        return 2;
        break;
      case 0x2083:
        return 3;
        break;
      case 0x2084:
        return 4;
        break;
      case 0x2085:
        return 5;
        break;
      case 0x2086:
        return 6;
        break;
      case 0x2087:
        return 7;
        break;
      case 0x2088:
        return 8;
        break;
      case 0x2089:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x2070:
      case 0x2074:
      case 0x2075:
      case 0x2076:
      case 0x2077:
      case 0x2078:
      case 0x2079:
      case 0x2080:
      case 0x2081:
      case 0x2082:
      case 0x2083:
      case 0x2084:
      case 0x2085:
      case 0x2086:
      case 0x2087:
      case 0x2088:
      case 0x2089:
        return 1;
      default:
        return 0;
      }
    }

    float numeric_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x2070:
        return 0.000000;
        break;
      case 0x2074:
        return 4.000000;
        break;
      case 0x2075:
        return 5.000000;
        break;
      case 0x2076:
        return 6.000000;
        break;
      case 0x2077:
        return 7.000000;
        break;
      case 0x2078:
        return 8.000000;
        break;
      case 0x2079:
        return 9.000000;
        break;
      case 0x2080:
        return 0.000000;
        break;
      case 0x2081:
        return 1.000000;
        break;
      case 0x2082:
        return 2.000000;
        break;
      case 0x2083:
        return 3.000000;
        break;
      case 0x2084:
        return 4.000000;
        break;
      case 0x2085:
        return 5.000000;
        break;
      case 0x2086:
        return 6.000000;
        break;
      case 0x2087:
        return 7.000000;
        break;
      case 0x2088:
        return 8.000000;
        break;
      case 0x2089:
        return 9.000000;
        break;
      default:
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x2070:
      case 0x2074:
      case 0x2075:
      case 0x2076:
      case 0x2077:
      case 0x2078:
      case 0x2079:
      case 0x2080:
      case 0x2081:
      case 0x2082:
      case 0x2083:
      case 0x2084:
      case 0x2085:
      case 0x2086:
      case 0x2087:
      case 0x2088:
      case 0x2089:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Superscripts_and_Subscripts2070::_cat[uc - m_first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Superscripts_and_Subscripts2070::m_bidir[uc - m_first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Superscripts_and_Subscripts2070::_decomp[uc - m_first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(1);
      us[0] = Superscripts_and_Subscripts2070::m_decompStr[uc - m_first_letter];
      return us;
    }

    bool must_mirror(const UCS4 uc) const {
      return m_mirror.test(uc - m_first_letter);
    }

    Line_Break linebreak(const UCS4 uc) const {
      if (!is_defined(uc))
        return LB_MAX;
      return Babylon::Line_Break(Superscripts_and_Subscripts2070::m_lb[uc - m_first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(Superscripts_and_Subscripts2070::m_ea[uc - m_first_letter]);
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
      return m_Math.test(uc - m_first_letter);
    }

    bool is_Composite(const UCS4 uc) const {
      return 0;
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return 0;
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part_Not_Cf(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Uppercase(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Lowercase(const UCS4 uc) const {
      return 0;
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
    Superscripts_and_Subscripts2070(const Superscripts_and_Subscripts2070 &) {}

    Babylon::UCS4 m_first_letter;
    Babylon::UCS4 m_last_letter;
    // Babylon::UCS4_string m_version;
    static const bitset<48> m_is_defined;
    static const unsigned char _cat[48];
    static const unsigned char m_bidir[48];
    static const unsigned char _decomp[48];
    static const UCS2 m_decompStr[48];
    static const bitset<48> m_mirror;
    static const unsigned char m_lb[48];
    static const unsigned char m_ea[48];
    static const bitset<48> m_Math;

  }; // class Superscripts_and_Subscripts2070

    const bitset<48> Superscripts_and_Subscripts2070::m_is_defined(string("000000000000000001111111111111111111111111110001"));

  const unsigned char Superscripts_and_Subscripts2070::_cat[] = {
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Ps, CAT_Pe, CAT_Ll, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Ps, CAT_Pe, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No
  };

  const unsigned char Superscripts_and_Subscripts2070::m_bidir[] = {
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN
  };

  const unsigned char Superscripts_and_Subscripts2070::_decomp[] = {
    DECOMP_SUPER, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
    DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
    DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, 
    DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Superscripts_and_Subscripts2070::m_decompStr[] = {
    0x0030u, 0x2071u, 0x2072u, 0x2073u, 
    0x0034u, 0x0035u, 0x0036u, 0x0037u, 
    0x0038u, 0x0039u, 0x002Bu, 0x2212u, 
    0x003Du, 0x0028u, 0x0029u, 0x006Eu, 
    0x0030u, 0x0031u, 0x0032u, 0x0033u, 
    0x0034u, 0x0035u, 0x0036u, 0x0037u, 
    0x0038u, 0x0039u, 0x002Bu, 0x2212u, 
    0x003Du, 0x0028u, 0x0029u, 0x208Fu, 
    0x2090u, 0x2091u, 0x2092u, 0x2093u, 
    0x2094u, 0x2095u, 0x2096u, 0x2097u, 
    0x2098u, 0x2099u, 0x209Au, 0x209Bu, 
    0x209Cu, 0x209Du, 0x209Eu, 0x209Fu
  };

  const bitset<48> Superscripts_and_Subscripts2070::m_mirror(string("000000000000000001100000000000000110000000000000"));

  const unsigned char Superscripts_and_Subscripts2070::m_lb[] = {
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, LB_AI, 
    LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
  };

  const unsigned char Superscripts_and_Subscripts2070::m_ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
    EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bitset<48> Superscripts_and_Subscripts2070::m_Math(string("000000000000000000011100000000000001110000000000"));

}; // namespace Babylon

dload(Babylon::Superscripts_and_Subscripts2070);
