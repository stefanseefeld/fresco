/*$Id: 2700-27BF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon,  8 Jan 2001 23:32:29 +0100.
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

  class Dingbats2700 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Dingbats2700() {
      m_first_letter = 0x2700;
      m_last_letter  = 0x27BF;
      // m_version="3.0.1" // Not yet supported!

    }


    ~Dingbats2700() {
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
      return "Dingbats";
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
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x2776:
        return 1;
        break;
      case 0x2777:
        return 2;
        break;
      case 0x2778:
        return 3;
        break;
      case 0x2779:
        return 4;
        break;
      case 0x277A:
        return 5;
        break;
      case 0x277B:
        return 6;
        break;
      case 0x277C:
        return 7;
        break;
      case 0x277D:
        return 8;
        break;
      case 0x277E:
        return 9;
        break;
      case 0x2780:
        return 1;
        break;
      case 0x2781:
        return 2;
        break;
      case 0x2782:
        return 3;
        break;
      case 0x2783:
        return 4;
        break;
      case 0x2784:
        return 5;
        break;
      case 0x2785:
        return 6;
        break;
      case 0x2786:
        return 7;
        break;
      case 0x2787:
        return 8;
        break;
      case 0x2788:
        return 9;
        break;
      case 0x278A:
        return 1;
        break;
      case 0x278B:
        return 2;
        break;
      case 0x278C:
        return 3;
        break;
      case 0x278D:
        return 4;
        break;
      case 0x278E:
        return 5;
        break;
      case 0x278F:
        return 6;
        break;
      case 0x2790:
        return 7;
        break;
      case 0x2791:
        return 8;
        break;
      case 0x2792:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x2776:
      case 0x2777:
      case 0x2778:
      case 0x2779:
      case 0x277A:
      case 0x277B:
      case 0x277C:
      case 0x277D:
      case 0x277E:
      case 0x2780:
      case 0x2781:
      case 0x2782:
      case 0x2783:
      case 0x2784:
      case 0x2785:
      case 0x2786:
      case 0x2787:
      case 0x2788:
      case 0x278A:
      case 0x278B:
      case 0x278C:
      case 0x278D:
      case 0x278E:
      case 0x278F:
      case 0x2790:
      case 0x2791:
      case 0x2792:
        return 1;
      default:
        return 0;
      }
    }

    float numeric_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x2776:
        return 1.000000;
        break;
      case 0x2777:
        return 2.000000;
        break;
      case 0x2778:
        return 3.000000;
        break;
      case 0x2779:
        return 4.000000;
        break;
      case 0x277A:
        return 5.000000;
        break;
      case 0x277B:
        return 6.000000;
        break;
      case 0x277C:
        return 7.000000;
        break;
      case 0x277D:
        return 8.000000;
        break;
      case 0x277E:
        return 9.000000;
        break;
      case 0x277F:
        return 10.000000;
        break;
      case 0x2780:
        return 1.000000;
        break;
      case 0x2781:
        return 2.000000;
        break;
      case 0x2782:
        return 3.000000;
        break;
      case 0x2783:
        return 4.000000;
        break;
      case 0x2784:
        return 5.000000;
        break;
      case 0x2785:
        return 6.000000;
        break;
      case 0x2786:
        return 7.000000;
        break;
      case 0x2787:
        return 8.000000;
        break;
      case 0x2788:
        return 9.000000;
        break;
      case 0x2789:
        return 10.000000;
        break;
      case 0x278A:
        return 1.000000;
        break;
      case 0x278B:
        return 2.000000;
        break;
      case 0x278C:
        return 3.000000;
        break;
      case 0x278D:
        return 4.000000;
        break;
      case 0x278E:
        return 5.000000;
        break;
      case 0x278F:
        return 6.000000;
        break;
      case 0x2790:
        return 7.000000;
        break;
      case 0x2791:
        return 8.000000;
        break;
      case 0x2792:
        return 9.000000;
        break;
      case 0x2793:
        return 10.000000;
        break;
      default:
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x2776:
      case 0x2777:
      case 0x2778:
      case 0x2779:
      case 0x277A:
      case 0x277B:
      case 0x277C:
      case 0x277D:
      case 0x277E:
      case 0x277F:
      case 0x2780:
      case 0x2781:
      case 0x2782:
      case 0x2783:
      case 0x2784:
      case 0x2785:
      case 0x2786:
      case 0x2787:
      case 0x2788:
      case 0x2789:
      case 0x278A:
      case 0x278B:
      case 0x278C:
      case 0x278D:
      case 0x278E:
      case 0x278F:
      case 0x2790:
      case 0x2791:
      case 0x2792:
      case 0x2793:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Dingbats2700::_cat[uc - m_first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(BIDIR_ON);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    UTF32_string decompose(const UCS4 uc) const {
      UTF32_string us;
      us.resize(1); us[0] = uc;
      return us;
    }

    bool must_mirror(const UCS4 uc) const {
      return 0;
    }

    Line_Break linebreak(const UCS4 uc) const {
      if (!is_defined(uc))
        return LB_MAX;
      return Babylon::Line_Break(LB_AL);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(EA_WIDTH_N);
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
    Dingbats2700(const Dingbats2700 &) {}

    Babylon::UCS4 m_first_letter;
    Babylon::UCS4 m_last_letter;
    // Babylon::UCS4_string m_version;
    static const bitset<192> m_is_defined;
    static const unsigned char _cat[192];

  }; // class Dingbats2700

    const bitset<192> Dingbats2700::m_is_defined(string("011111111111111011111111111111111111111100011111111111111111111111111111110000000000000011111110011111110100011110101111111111111111111111111111111111101111111111111111111111111111001111011110"));

  const unsigned char Dingbats2700::_cat[] = {
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So
  };

}; // namespace Babylon

dload(Babylon::Dingbats2700);
