/*$Id: 3000-303F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon,  8 Jan 2001 23:32:39 +0100.
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

  class CJK_Symbols_and_Punctuation3000 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    CJK_Symbols_and_Punctuation3000() {
      m_first_letter = 0x3000;
      m_last_letter  = 0x303F;
      // m_version="3.0.1" // Not yet supported!

    }


    ~CJK_Symbols_and_Punctuation3000() {
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
      return "CJK Symbols and Punctuation";
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
      case 0x3007:
        return 0.000000;
        break;
      case 0x3021:
        return 1.000000;
        break;
      case 0x3022:
        return 2.000000;
        break;
      case 0x3023:
        return 3.000000;
        break;
      case 0x3024:
        return 4.000000;
        break;
      case 0x3025:
        return 5.000000;
        break;
      case 0x3026:
        return 6.000000;
        break;
      case 0x3027:
        return 7.000000;
        break;
      case 0x3028:
        return 8.000000;
        break;
      case 0x3029:
        return 9.000000;
        break;
      case 0x3038:
        return 10.000000;
        break;
      case 0x3039:
        return 20.000000;
        break;
      case 0x303A:
        return 30.000000;
        break;
      default:
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x3007:
      case 0x3021:
      case 0x3022:
      case 0x3023:
      case 0x3024:
      case 0x3025:
      case 0x3026:
      case 0x3027:
      case 0x3028:
      case 0x3029:
      case 0x3038:
      case 0x3039:
      case 0x303A:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(CJK_Symbols_and_Punctuation3000::_cat[uc - m_first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Can_Comb_Class(CJK_Symbols_and_Punctuation3000::_comb_cl[uc - m_first_letter]);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(CJK_Symbols_and_Punctuation3000::m_bidir[uc - m_first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(CJK_Symbols_and_Punctuation3000::_decomp[uc - m_first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(1);
      us[0] = CJK_Symbols_and_Punctuation3000::m_decompStr[uc - m_first_letter];
      return us;
    }

    bool must_mirror(const UCS4 uc) const {
      return m_mirror.test(uc - m_first_letter);
    }

    Line_Break linebreak(const UCS4 uc) const {
      if (!is_defined(uc))
        return LB_MAX;
      return Babylon::Line_Break(CJK_Symbols_and_Punctuation3000::m_lb[uc - m_first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(CJK_Symbols_and_Punctuation3000::m_ea[uc - m_first_letter]);
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
      return m_Quotation_Mark.test(uc - m_first_letter);
    }

    bool is_Terminal_Punctuation(const UCS4 uc) const {
      return m_Terminal_Punctuation.test(uc - m_first_letter);
    }

    bool is_Math(const UCS4 uc) const {
      return 0;
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
      return m_Diacritic.test(uc - m_first_letter);
    }

    bool is_Extender(const UCS4 uc) const {
      return m_Extender.test(uc - m_first_letter);
    }

    bool is_Identifier_Part_Not_Cf(const UCS4 uc) const {
      return m_Identifier_Part_Not_Cf.test(uc - m_first_letter);
    }

    bool is_Other_Uppercase(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Lowercase(const UCS4 uc) const {
      return 0;
    }

    bool is_Ideographic(const UCS4 uc) const {
      return ((uc >= 0x3006 && uc <= 0x3007) ||
              (uc >= 0x3021 && uc <= 0x3029) ||
              (uc >= 0x3038 && uc <= 0x303A));
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
    CJK_Symbols_and_Punctuation3000(const CJK_Symbols_and_Punctuation3000 &) {}

    Babylon::UCS4 m_first_letter;
    Babylon::UCS4 m_last_letter;
    // Babylon::UCS4_string m_version;
    static const bitset<64> m_is_defined;
    static const unsigned char _cat[64];
    static const unsigned char _comb_cl[64];
    static const unsigned char m_bidir[64];
    static const unsigned char _decomp[64];
    static const UCS2 m_decompStr[64];
    static const bitset<64> m_mirror;
    static const unsigned char m_lb[64];
    static const unsigned char m_ea[64];
    static const bitset<64> m_Quotation_Mark;
    static const bitset<64> m_Terminal_Punctuation;
    static const bitset<64> m_Diacritic;
    static const bitset<64> m_Extender;
    static const bitset<64> m_Identifier_Part_Not_Cf;

  }; // class CJK_Symbols_and_Punctuation3000

    const bitset<64> CJK_Symbols_and_Punctuation3000::m_is_defined(string("1100011111111111111111111111111111111111111111111111111111111111"));

  const unsigned char CJK_Symbols_and_Punctuation3000::_cat[] = {
    CAT_Zs, CAT_Po, CAT_Po, CAT_Po, CAT_So, CAT_Lm, CAT_Lo, CAT_Nl, 
    CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, 
    CAT_Ps, CAT_Pe, CAT_So, CAT_So, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, 
    CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Pd, CAT_Ps, CAT_Pe, CAT_Pe, 
    CAT_So, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Pd, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_So, CAT_So, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Zs, CAT_Zs, CAT_Zs, CAT_So, CAT_So
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::_comb_cl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 218, 228, 232, 222, 224, 224, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::m_bidir[] = {
    BIDIR_WS, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_ON, BIDIR_ON
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::_decomp[] = {
    DECOMP_WIDE, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 CJK_Symbols_and_Punctuation3000::m_decompStr[] = {
    0x0020u, 0x3001u, 0x3002u, 0x3003u, 
    0x3004u, 0x3005u, 0x3006u, 0x3007u, 
    0x3008u, 0x3009u, 0x300Au, 0x300Bu, 
    0x300Cu, 0x300Du, 0x300Eu, 0x300Fu, 
    0x3010u, 0x3011u, 0x3012u, 0x3013u, 
    0x3014u, 0x3015u, 0x3016u, 0x3017u, 
    0x3018u, 0x3019u, 0x301Au, 0x301Bu, 
    0x301Cu, 0x301Du, 0x301Eu, 0x301Fu, 
    0x3020u, 0x3021u, 0x3022u, 0x3023u, 
    0x3024u, 0x3025u, 0x3026u, 0x3027u, 
    0x3028u, 0x3029u, 0x302Au, 0x302Bu, 
    0x302Cu, 0x302Du, 0x302Eu, 0x302Fu, 
    0x3030u, 0x3031u, 0x3032u, 0x3033u, 
    0x3034u, 0x3035u, 0x3012u, 0x3037u, 
    0x5341u, 0x5344u, 0x5345u, 0x303Bu, 
    0x303Cu, 0x303Du, 0x303Eu, 0x303Fu
  };

  const bitset<64> CJK_Symbols_and_Punctuation3000::m_mirror(string("0000000000000000000000000000000000001111111100111111111100000000"));

  const unsigned char CJK_Symbols_and_Punctuation3000::m_lb[] = {
    LB_ID, LB_CL, LB_CL, LB_ID, LB_ID, LB_NS, LB_ID, LB_ID, 
    LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, 
    LB_OP, LB_CL, LB_ID, LB_ID, LB_OP, LB_CL, LB_OP, LB_CL, 
    LB_OP, LB_CL, LB_OP, LB_CL, LB_NS, LB_OP, LB_CL, LB_CL, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::m_ea[] = {
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_N
  };

    const bitset<64> CJK_Symbols_and_Punctuation3000::m_Quotation_Mark(string("0000000000000000000000000000000011000000000000000000000000000000"));

    const bitset<64> CJK_Symbols_and_Punctuation3000::m_Terminal_Punctuation(string("0000000000000000000000000000000000000000000000000000000000000110"));

    const bitset<64> CJK_Symbols_and_Punctuation3000::m_Diacritic(string("0000000000000000111111000000000000000000000000000000000000000000"));

    const bitset<64> CJK_Symbols_and_Punctuation3000::m_Extender(string("0000000000111110000000000000000000000000000000000000000000000000"));

    const bitset<64> CJK_Symbols_and_Punctuation3000::m_Identifier_Part_Not_Cf(string("0000011100111110111111111111111000000000000000000000000000000000"));

}; // namespace Babylon

dload(Babylon::CJK_Symbols_and_Punctuation3000);
