/*$Id: UnicodePluginGenerator.pl,v 1.5 2001/05/06 12:18:46 tobias Exp 500-52F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Thu, 30 May 2002 20:47:59 +0200.
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
#include <utility>

namespace Babylon {

  class Cyrillic_Supplementary500 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Cyrillic_Supplementary500() {
      m_first_letter = 0x500;
      m_last_letter  = 0x52F;
      // m_version="3.1" // Not yet supported!
    }

    ~Cyrillic_Supplementary500() {
    }

    UCS4 first_letter() const {
      return m_first_letter;
    }

    UCS4 last_letter() const {
      return m_last_letter;
    }

    bool is_undef_block() const {
      return 0;
    }

    // query functions:
    std::string blockname(const UCS4 uc) const {
      return "Cyrillic Supplementary";
    }

    bool is_defined(const UCS4 uc) const {
      return (m_is_defined.test(uc - m_first_letter));
    }

    UCS4 uppercase(const UCS4 uc) const {
      return Cyrillic_Supplementary500::m_upper[uc - m_first_letter];
    }

    UCS4 lowercase(const UCS4 uc) const {
      return Cyrillic_Supplementary500::m_lower[uc - m_first_letter];
    }

    UCS4 titlecase(const UCS4 uc) const {
      return Cyrillic_Supplementary500::m_title[uc - m_first_letter];
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
      return 0;
    }

    bool is_Numeric(const UCS4 uc) const {
      return 0;
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Cyrillic_Supplementary500::_cat[uc - m_first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_INVALID;
      return BIDIR_L;
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(DECOMP_CANONICAL);
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

    bool is_White_Space(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Join_Control(const UCS4 uc) const {
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

    bool is_Other_Math(const UCS4 uc) const {
      return 0;
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_ASCII_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Alphabetic(const UCS4 uc) const {
      return 0;
    }

    bool is_Ideographic(const UCS4 uc) const {
      return 0;
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Lowercase(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Uppercase(const UCS4 uc) const {
      return 0;
    }

    bool is_Noncharacter_Code_Point(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Grapheme_Extend(const UCS4 uc) const {
      return 0;
    }

    bool is_Grapheme_Link(const UCS4 uc) const {
      return 0;
    }

    bool is_IDS_Binary_Operator(const UCS4 uc) const {
      return 0;
    }

    bool is_IDS_Trinary_Operator(const UCS4 uc) const {
      return 0;
    }

    bool is_Radical(const UCS4 uc) const {
      return 0;
    }

    bool is_Unified_Ideograph(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Default_Ignorable_Code_Point(const UCS4 uc) const {
      return 0;
    }

    bool is_Deprecated(const UCS4 uc) const {
      return 0;
    }

    bool is_Soft_Dotted(const UCS4 uc) const {
      return 0;
    }

    bool is_Logical_Order_Exception(const UCS4 uc) const {
      return 0;
    }

  private:
    // functions
    Cyrillic_Supplementary500(const Cyrillic_Supplementary500 &) {}

    Babylon::UCS4 m_first_letter;
    Babylon::UCS4 m_last_letter;
    // Babylon::UCS4_string m_version;
    static const std::bitset<48> m_is_defined;
    static const UCS4 m_upper[48];
    static const UCS4 m_lower[48];
    static const UCS4 m_title[48];
    static const unsigned char _cat[48];
  }; // class Cyrillic_Supplementary500

    const std::bitset<48> Cyrillic_Supplementary500::m_is_defined(std::string("000000000000000000000000000000001111111111111111"));

  const UCS4 Cyrillic_Supplementary500::m_upper[] = {
    0x0500, 0x0500, 0x0502, 0x0502, 0x0504, 0x0504, 0x0506, 0x0506, 
    0x0508, 0x0508, 0x050A, 0x050A, 0x050C, 0x050C, 0x050E, 0x050E, 
    0x0510, 0x0511, 0x0512, 0x0513, 0x0514, 0x0515, 0x0516, 0x0517, 
    0x0518, 0x0519, 0x051A, 0x051B, 0x051C, 0x051D, 0x051E, 0x051F, 
    0x0520, 0x0521, 0x0522, 0x0523, 0x0524, 0x0525, 0x0526, 0x0527, 
    0x0528, 0x0529, 0x052A, 0x052B, 0x052C, 0x052D, 0x052E, 0x052F
  };

  const UCS4 Cyrillic_Supplementary500::m_lower[] = {
    0x0501, 0x0501, 0x0503, 0x0503, 0x0505, 0x0505, 0x0507, 0x0507, 
    0x0509, 0x0509, 0x050B, 0x050B, 0x050D, 0x050D, 0x050F, 0x050F, 
    0x0510, 0x0511, 0x0512, 0x0513, 0x0514, 0x0515, 0x0516, 0x0517, 
    0x0518, 0x0519, 0x051A, 0x051B, 0x051C, 0x051D, 0x051E, 0x051F, 
    0x0520, 0x0521, 0x0522, 0x0523, 0x0524, 0x0525, 0x0526, 0x0527, 
    0x0528, 0x0529, 0x052A, 0x052B, 0x052C, 0x052D, 0x052E, 0x052F
  };

  const UCS4 Cyrillic_Supplementary500::m_title[] = {
    0x0500, 0x0500, 0x0502, 0x0502, 0x0504, 0x0504, 0x0506, 0x0506, 
    0x0508, 0x0508, 0x050A, 0x050A, 0x050C, 0x050C, 0x050E, 0x050E, 
    0x0510, 0x0511, 0x0512, 0x0513, 0x0514, 0x0515, 0x0516, 0x0517, 
    0x0518, 0x0519, 0x051A, 0x051B, 0x051C, 0x051D, 0x051E, 0x051F, 
    0x0520, 0x0521, 0x0522, 0x0523, 0x0524, 0x0525, 0x0526, 0x0527, 
    0x0528, 0x0529, 0x052A, 0x052B, 0x052C, 0x052D, 0x052E, 0x052F
  };

  const unsigned char Cyrillic_Supplementary500::_cat[] = {
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu
  };

}; // namespace Babylon

dload(Babylon::Cyrillic_Supplementary500);
