/*$Id: FE50-FE6F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:29:52 +0100.
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
 
  class Small_Form_VariantsFE50 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Small_Form_VariantsFE50() {
      my_first_letter = 0xFE50;
      my_last_letter  = 0xFE6F;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Small_Form_VariantsFE50() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Small Form Variants";
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
      return Babylon::Gen_Cat(Small_Form_VariantsFE50::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Small_Form_VariantsFE50::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Small_Form_VariantsFE50::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Small_Form_VariantsFE50::decompStr[_uc - my_first_letter][0];
      us[1] = Small_Form_VariantsFE50::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(Small_Form_VariantsFE50::lb[_uc - my_first_letter]);
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
      return Small_Form_VariantsFE50::Dash[_uc - my_first_letter];
    }

    bool is_Hyphen(const UCS4 & _uc) const {
      return Small_Form_VariantsFE50::Hyphen[_uc - my_first_letter];
    }

    bool is_Quotation_Mark(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const UCS4 & _uc) const {
      return Small_Form_VariantsFE50::Terminal_Punctuation[_uc - my_first_letter];
    }

    bool is_Math(const UCS4 & _uc) const {
      return Small_Form_VariantsFE50::Math[_uc - my_first_letter];
    }

    bool is_Paired_Punctuation(const UCS4 & _uc) const {
      return Small_Form_VariantsFE50::Paired_Punctuation[_uc - my_first_letter];
    }

    bool is_Left_of_Pair(const UCS4 & _uc) const {
      return Small_Form_VariantsFE50::Left_of_Pair[_uc - my_first_letter];
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
      return 0;
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
    Small_Form_VariantsFE50(const Small_Form_VariantsFE50 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[32];
    static const unsigned char cat[32];
    static const unsigned char bidir[32];
    static const unsigned char decomp[32];
    static const UCS2 decompStr[32][2];
    static const unsigned char lb[32];
    static const bool Dash[32];
    static const bool Hyphen[32];
    static const bool Terminal_Punctuation[32];
    static const bool Math[32];
    static const bool Paired_Punctuation[32];
    static const bool Left_of_Pair[32];

  }; // class Small_Form_VariantsFE50

  const bool Small_Form_VariantsFE50::isdefined[] = {
    1, 1, 1, 0, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0, 
    1, 1, 1, 1, 0, 0, 0, 0
  };

  const unsigned char Small_Form_VariantsFE50::cat[] = {
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Pd, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Po, 
    CAT_Po, CAT_Po, CAT_Sm, CAT_Pd, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Po, 
    CAT_Po, CAT_Sc, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po
  };

  const unsigned char Small_Form_VariantsFE50::bidir[] = {
    BIDIR_CS, BIDIR_ON, BIDIR_CS, BIDIR_CS, BIDIR_ON, BIDIR_CS, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ET, 
    BIDIR_ON, BIDIR_ON, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_CS, 
    BIDIR_ON, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS
  };

  const unsigned char Small_Form_VariantsFE50::decomp[] = {
    DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_NO_DECOMP, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, 
    DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, 
    DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_NO_DECOMP, 
    DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Small_Form_VariantsFE50::decompStr[][2] = {
    { 0x002C, 0x0000 }, { 0x3001, 0x0000 }, { 0x002E, 0x0000 }, { 0xFE53, 0x0000 }, 
    { 0x003B, 0x0000 }, { 0x003A, 0x0000 }, { 0x003F, 0x0000 }, { 0x0021, 0x0000 }, 
    { 0x2014, 0x0000 }, { 0x0028, 0x0000 }, { 0x0029, 0x0000 }, { 0x007B, 0x0000 }, 
    { 0x007D, 0x0000 }, { 0x3014, 0x0000 }, { 0x3015, 0x0000 }, { 0x0023, 0x0000 }, 
    { 0x0026, 0x0000 }, { 0x002A, 0x0000 }, { 0x002B, 0x0000 }, { 0x002D, 0x0000 }, 
    { 0x003C, 0x0000 }, { 0x003E, 0x0000 }, { 0x003D, 0x0000 }, { 0xFE67, 0x0000 }, 
    { 0x005C, 0x0000 }, { 0x0024, 0x0000 }, { 0x0025, 0x0000 }, { 0x0040, 0x0000 }, 
    { 0xFE6C, 0x0000 }, { 0xFE6D, 0x0000 }, { 0xFE6E, 0x0000 }, { 0xFE6F, 0x0000 }
  };

  const unsigned char Small_Form_VariantsFE50::lb[] = {
    LB_CL, LB_ID, LB_CL, LB_CL, LB_NS, LB_NS, LB_EX, LB_EX, 
    LB_ID, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_CL, 
    LB_ID, LB_PR, LB_PO, LB_AL, LB_CL, LB_CL, LB_CL, LB_CL
  };

    const bool Small_Form_VariantsFE50::Dash[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Small_Form_VariantsFE50::Hyphen[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Small_Form_VariantsFE50::Terminal_Punctuation[] = {
        1, 1, 1, 0, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Small_Form_VariantsFE50::Math[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 0, 
        1, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Small_Form_VariantsFE50::Paired_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Small_Form_VariantsFE50::Left_of_Pair[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 0, 1, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Small_Form_VariantsFE50);
