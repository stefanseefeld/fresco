/*$Id: FE30-FE4F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:40:03 +0100.
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

  class CJK_Compatibility_FormsFE30 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    CJK_Compatibility_FormsFE30() {
      _first_letter = 0xFE30;
      _last_letter  = 0xFE4F;
      // _version="3.0.1" // Not yet supported!

    }


    ~CJK_Compatibility_FormsFE30() {
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
      return "CJK Compatibility Forms";
    }

    bool is_defined(const UCS4 uc) const {
      return (_is_defined[uc - _first_letter]);
    }

    UCS4 uppercase(const UCS4 uc) const {
      return uc;
    }

    bool is_Uppercase(const UCS4 uc) const {
      return category(uc) == CAT_Lu;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return uc;
    }

    bool is_Lowercase(const UCS4 uc) const {
      return category(uc) == CAT_Ll;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return uc;
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
      return 0;
    }

    bool is_Numeric(const UCS4 uc) const {
      return 0;
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(CJK_Compatibility_FormsFE30::_cat[uc - _first_letter]);
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
      return Babylon::Char_Decomp(CJK_Compatibility_FormsFE30::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = CJK_Compatibility_FormsFE30::_decompStr[uc - _first_letter][0];
      us[1] = CJK_Compatibility_FormsFE30::_decompStr[uc - _first_letter][1];
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
      return Babylon::Line_Break(CJK_Compatibility_FormsFE30::_lb[uc - _first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(EA_WIDTH_W);
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
      return CJK_Compatibility_FormsFE30::_Dash[uc - _first_letter];
    }

    bool is_Hyphen(const UCS4 uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 uc) const {
      return CJK_Compatibility_FormsFE30::_Quotation_Mark[uc - _first_letter];
    }

    bool is_Terminal_Punctuation(const UCS4 uc) const {
      return 0;
    }

    bool is_Math(const UCS4 uc) const {
      return CJK_Compatibility_FormsFE30::_Math[uc - _first_letter];
    }

    bool is_Paired_Punctuation(const UCS4 uc) const {
      return CJK_Compatibility_FormsFE30::_Paired_Punctuation[uc - _first_letter];
    }

    bool is_Left_of_Pair(const UCS4 uc) const {
      return CJK_Compatibility_FormsFE30::_Left_of_Pair[uc - _first_letter];
    }

    bool is_Combining(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_spacing(const UCS4 uc) const {
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

    bool is_Identifier_Part(const UCS4 uc) const {
      return CJK_Compatibility_FormsFE30::_Identifier_Part[uc - _first_letter];
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
    CJK_Compatibility_FormsFE30(const CJK_Compatibility_FormsFE30 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[32];
    static const unsigned char _cat[32];
    static const unsigned char _decomp[32];
    static const UCS2 _decompStr[32][2];
    static const unsigned char _lb[32];
    static const bool _Dash[32];
    static const bool _Quotation_Mark[32];
    static const bool _Math[32];
    static const bool _Paired_Punctuation[32];
    static const bool _Left_of_Pair[32];
    static const bool _Identifier_Part[32];

  }; // class CJK_Compatibility_FormsFE30

  const bool CJK_Compatibility_FormsFE30::_is_defined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 0, 0, 0, 
    0, 1, 1, 1, 1, 1, 1, 1
  };

  const unsigned char CJK_Compatibility_FormsFE30::_cat[] = {
    CAT_Po, CAT_Pd, CAT_Pd, CAT_Pc, CAT_Pc, CAT_Ps, CAT_Pe, CAT_Ps, 
    CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, 
    CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Pc, CAT_Pc, CAT_Pc
  };

  const unsigned char CJK_Compatibility_FormsFE30::_decomp[] = {
    DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, 
    DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, 
    DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT
  };

  const UCS2 CJK_Compatibility_FormsFE30::_decompStr[][2] = {
    { 0x2025, 0x0000 }, { 0x2014, 0x0000 }, { 0x2013, 0x0000 }, { 0x005F, 0x0000 }, 
    { 0x005F, 0x0000 }, { 0x0028, 0x0000 }, { 0x0029, 0x0000 }, { 0x007B, 0x0000 }, 
    { 0x007D, 0x0000 }, { 0x3014, 0x0000 }, { 0x3015, 0x0000 }, { 0x3010, 0x0000 }, 
    { 0x3011, 0x0000 }, { 0x300A, 0x0000 }, { 0x300B, 0x0000 }, { 0x3008, 0x0000 }, 
    { 0x3009, 0x0000 }, { 0x300C, 0x0000 }, { 0x300D, 0x0000 }, { 0x300E, 0x0000 }, 
    { 0x300F, 0x0000 }, { 0xFE45, 0x0000 }, { 0xFE46, 0x0000 }, { 0xFE47, 0x0000 }, 
    { 0xFE48, 0x0000 }, { 0x203E, 0x0000 }, { 0x203E, 0x0000 }, { 0x203E, 0x0000 }, 
    { 0x203E, 0x0000 }, { 0x005F, 0x0000 }, { 0x005F, 0x0000 }, { 0x005F, 0x0000 }
  };

  const unsigned char CJK_Compatibility_FormsFE30::_lb[] = {
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_OP, LB_CL, LB_OP, 
    LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, 
    LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID
  };

    const bool CJK_Compatibility_FormsFE30::_Dash[] = {
        0, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Compatibility_FormsFE30::_Quotation_Mark[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Compatibility_FormsFE30::_Math[] = {
        0, 0, 0, 0, 0, 1, 1, 1, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Compatibility_FormsFE30::_Paired_Punctuation[] = {
        0, 0, 0, 0, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Compatibility_FormsFE30::_Left_of_Pair[] = {
        0, 0, 0, 0, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Compatibility_FormsFE30::_Identifier_Part[] = {
        0, 0, 0, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 1
    };

}; // namespace Babylon

dload(Babylon::CJK_Compatibility_FormsFE30);
