/*$Id: FE30-FE4F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:29:51 +0100.
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
      my_first_letter = 0xFE30;
      my_last_letter  = 0xFE4F;
      // my_version="3.0.1" // Not yet supported!

    }


    ~CJK_Compatibility_FormsFE30() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "CJK Compatibility Forms";
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
      return _uc;
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
      return Babylon::Gen_Cat(CJK_Compatibility_FormsFE30::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(BIDIR_ON);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(CJK_Compatibility_FormsFE30::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = CJK_Compatibility_FormsFE30::decompStr[_uc - my_first_letter][0];
      us[1] = CJK_Compatibility_FormsFE30::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(CJK_Compatibility_FormsFE30::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(EA_WIDTH_W);
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
      return CJK_Compatibility_FormsFE30::Dash[_uc - my_first_letter];
    }

    bool is_Hyphen(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 & _uc) const {
      return CJK_Compatibility_FormsFE30::Quotation_Mark[_uc - my_first_letter];
    }

    bool is_Terminal_Punctuation(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Math(const UCS4 & _uc) const {
      return CJK_Compatibility_FormsFE30::Math[_uc - my_first_letter];
    }

    bool is_Paired_Punctuation(const UCS4 & _uc) const {
      return CJK_Compatibility_FormsFE30::Paired_Punctuation[_uc - my_first_letter];
    }

    bool is_Left_of_Pair(const UCS4 & _uc) const {
      return CJK_Compatibility_FormsFE30::Left_of_Pair[_uc - my_first_letter];
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
      return 0;
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return CJK_Compatibility_FormsFE30::Identifier_Part[_uc - my_first_letter];
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
      return 0;
    }

    bool is_Lowercase(const UCS4 & _uc) const {
      return 0;
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
    CJK_Compatibility_FormsFE30(const CJK_Compatibility_FormsFE30 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[32];
    static const unsigned char cat[32];
    static const unsigned char decomp[32];
    static const UCS2 decompStr[32][2];
    static const unsigned char lb[32];
    static const bool Dash[32];
    static const bool Quotation_Mark[32];
    static const bool Math[32];
    static const bool Paired_Punctuation[32];
    static const bool Left_of_Pair[32];
    static const bool Identifier_Part[32];

  }; // class CJK_Compatibility_FormsFE30

  const bool CJK_Compatibility_FormsFE30::isdefined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 0, 0, 0, 
    0, 1, 1, 1, 1, 1, 1, 1
  };

  const unsigned char CJK_Compatibility_FormsFE30::cat[] = {
    CAT_Po, CAT_Pd, CAT_Pd, CAT_Pc, CAT_Pc, CAT_Ps, CAT_Pe, CAT_Ps, 
    CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, 
    CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Pc, CAT_Pc, CAT_Pc
  };

  const unsigned char CJK_Compatibility_FormsFE30::decomp[] = {
    DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, 
    DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, 
    DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT
  };

  const UCS2 CJK_Compatibility_FormsFE30::decompStr[][2] = {
    { 0x2025, 0x0000 }, { 0x2014, 0x0000 }, { 0x2013, 0x0000 }, { 0x005F, 0x0000 }, 
    { 0x005F, 0x0000 }, { 0x0028, 0x0000 }, { 0x0029, 0x0000 }, { 0x007B, 0x0000 }, 
    { 0x007D, 0x0000 }, { 0x3014, 0x0000 }, { 0x3015, 0x0000 }, { 0x3010, 0x0000 }, 
    { 0x3011, 0x0000 }, { 0x300A, 0x0000 }, { 0x300B, 0x0000 }, { 0x3008, 0x0000 }, 
    { 0x3009, 0x0000 }, { 0x300C, 0x0000 }, { 0x300D, 0x0000 }, { 0x300E, 0x0000 }, 
    { 0x300F, 0x0000 }, { 0xFE45, 0x0000 }, { 0xFE46, 0x0000 }, { 0xFE47, 0x0000 }, 
    { 0xFE48, 0x0000 }, { 0x203E, 0x0000 }, { 0x203E, 0x0000 }, { 0x203E, 0x0000 }, 
    { 0x203E, 0x0000 }, { 0x005F, 0x0000 }, { 0x005F, 0x0000 }, { 0x005F, 0x0000 }
  };

  const unsigned char CJK_Compatibility_FormsFE30::lb[] = {
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_OP, LB_CL, LB_OP, 
    LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, 
    LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID
  };

    const bool CJK_Compatibility_FormsFE30::Dash[] = {
        0, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Compatibility_FormsFE30::Quotation_Mark[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Compatibility_FormsFE30::Math[] = {
        0, 0, 0, 0, 0, 1, 1, 1, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Compatibility_FormsFE30::Paired_Punctuation[] = {
        0, 0, 0, 0, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Compatibility_FormsFE30::Left_of_Pair[] = {
        0, 0, 0, 0, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Compatibility_FormsFE30::Identifier_Part[] = {
        0, 0, 0, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 1
    };

}; // namespace Babylon
 
dload(Babylon::CJK_Compatibility_FormsFE30);
