/*$Id: UnicodePluginGenerator.pl,v 1.5 2001/05/06 12:18:46 tobias Exp 20D0-20FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Thu, 30 May 2002 20:48:09 +0200.
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

  class Combining_Diacritical_Marks_for_Symbols20D0 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Combining_Diacritical_Marks_for_Symbols20D0() {
      m_first_letter = 0x20D0;
      m_last_letter  = 0x20FF;
      // m_version="3.1" // Not yet supported!
    }

    ~Combining_Diacritical_Marks_for_Symbols20D0() {
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
      return "Combining Diacritical Marks for Symbols";
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
      return 0;
    }

    bool is_Numeric(const UCS4 uc) const {
      return 0;
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Combining_Diacritical_Marks_for_Symbols20D0::_cat[uc - m_first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Can_Comb_Class(Combining_Diacritical_Marks_for_Symbols20D0::_comb_cl[uc - m_first_letter]);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_INVALID;
      return BIDIR_NSM;
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
      return Babylon::Line_Break(LB_CM);
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
      return m_Other_Math.test(uc - m_first_letter);
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
    Combining_Diacritical_Marks_for_Symbols20D0(const Combining_Diacritical_Marks_for_Symbols20D0 &) {}

    Babylon::UCS4 m_first_letter;
    Babylon::UCS4 m_last_letter;
    // Babylon::UCS4_string m_version;
    static const std::bitset<48> m_is_defined;
    static const unsigned char _cat[48];
    static const unsigned char _comb_cl[48];
    static const std::bitset<48> m_Other_Math;
  }; // class Combining_Diacritical_Marks_for_Symbols20D0

    const std::bitset<48> Combining_Diacritical_Marks_for_Symbols20D0::m_is_defined(std::string("000000000000000000000111111111111111111111111111"));

  const unsigned char Combining_Diacritical_Marks_for_Symbols20D0::_cat[] = {
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Me, CAT_Me, CAT_Me, 
    CAT_Me, CAT_Mn, CAT_Me, CAT_Me, CAT_Me, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
  };

  const unsigned char Combining_Diacritical_Marks_for_Symbols20D0::_comb_cl[] = {
    230, 230, 1, 1, 230, 230, 230, 230, 
    1, 1, 1, 230, 230, 0, 0, 0, 
    0, 230, 0, 0, 0, 1, 1, 230, 
    220, 230, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

    const std::bitset<48> Combining_Diacritical_Marks_for_Symbols20D0::m_Other_Math(std::string("000000000000000000000000000000000001111111111111"));

}; // namespace Babylon

dload(Babylon::Combining_Diacritical_Marks_for_Symbols20D0);
