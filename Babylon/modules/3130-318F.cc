/*$Id: 3130-318F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:13:17 +0100.
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
 
  class Hangul_Compatibility_Jamo3130 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Hangul_Compatibility_Jamo3130() {
      my_first_letter = 0x3130;
      my_last_letter  = 0x318F;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Hangul_Compatibility_Jamo3130() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Hangul Compatibility Jamo";
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
      return Babylon::Gen_Cat(CAT_Lo);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(BIDIR_L);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Hangul_Compatibility_Jamo3130::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Hangul_Compatibility_Jamo3130::decompStr[_uc - my_first_letter][0];
      us[1] = Hangul_Compatibility_Jamo3130::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(LB_ID);
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
      return 0;
    }

    bool is_Hyphen(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Math(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Paired_Punctuation(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Left_of_Pair(const UCS4 & _uc) const {
      return 0;
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
      return Hangul_Compatibility_Jamo3130::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return Hangul_Compatibility_Jamo3130::Identifier_Part[_uc - my_first_letter];
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
    Hangul_Compatibility_Jamo3130(const Hangul_Compatibility_Jamo3130 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[96];
    static const unsigned char decomp[96];
    static const UCS2 decompStr[96][2];
    static const bool Alphabetic[96];
    static const bool Identifier_Part[96];

  }; // class Hangul_Compatibility_Jamo3130

  const bool Hangul_Compatibility_Jamo3130::isdefined[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0
  };

  const unsigned char Hangul_Compatibility_Jamo3130::decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP
  };

  const UCS2 Hangul_Compatibility_Jamo3130::decompStr[][2] = {
    { 0x3130, 0x0000 }, { 0x1100, 0x0000 }, { 0x1101, 0x0000 }, { 0x11AA, 0x0000 }, 
    { 0x1102, 0x0000 }, { 0x11AC, 0x0000 }, { 0x11AD, 0x0000 }, { 0x1103, 0x0000 }, 
    { 0x1104, 0x0000 }, { 0x1105, 0x0000 }, { 0x11B0, 0x0000 }, { 0x11B1, 0x0000 }, 
    { 0x11B2, 0x0000 }, { 0x11B3, 0x0000 }, { 0x11B4, 0x0000 }, { 0x11B5, 0x0000 }, 
    { 0x111A, 0x0000 }, { 0x1106, 0x0000 }, { 0x1107, 0x0000 }, { 0x1108, 0x0000 }, 
    { 0x1121, 0x0000 }, { 0x1109, 0x0000 }, { 0x110A, 0x0000 }, { 0x110B, 0x0000 }, 
    { 0x110C, 0x0000 }, { 0x110D, 0x0000 }, { 0x110E, 0x0000 }, { 0x110F, 0x0000 }, 
    { 0x1110, 0x0000 }, { 0x1111, 0x0000 }, { 0x1112, 0x0000 }, { 0x1161, 0x0000 }, 
    { 0x1162, 0x0000 }, { 0x1163, 0x0000 }, { 0x1164, 0x0000 }, { 0x1165, 0x0000 }, 
    { 0x1166, 0x0000 }, { 0x1167, 0x0000 }, { 0x1168, 0x0000 }, { 0x1169, 0x0000 }, 
    { 0x116A, 0x0000 }, { 0x116B, 0x0000 }, { 0x116C, 0x0000 }, { 0x116D, 0x0000 }, 
    { 0x116E, 0x0000 }, { 0x116F, 0x0000 }, { 0x1170, 0x0000 }, { 0x1171, 0x0000 }, 
    { 0x1172, 0x0000 }, { 0x1173, 0x0000 }, { 0x1174, 0x0000 }, { 0x1175, 0x0000 }, 
    { 0x1160, 0x0000 }, { 0x1114, 0x0000 }, { 0x1115, 0x0000 }, { 0x11C7, 0x0000 }, 
    { 0x11C8, 0x0000 }, { 0x11CC, 0x0000 }, { 0x11CE, 0x0000 }, { 0x11D3, 0x0000 }, 
    { 0x11D7, 0x0000 }, { 0x11D9, 0x0000 }, { 0x111C, 0x0000 }, { 0x11DD, 0x0000 }, 
    { 0x11DF, 0x0000 }, { 0x111D, 0x0000 }, { 0x111E, 0x0000 }, { 0x1120, 0x0000 }, 
    { 0x1122, 0x0000 }, { 0x1123, 0x0000 }, { 0x1127, 0x0000 }, { 0x1129, 0x0000 }, 
    { 0x112B, 0x0000 }, { 0x112C, 0x0000 }, { 0x112D, 0x0000 }, { 0x112E, 0x0000 }, 
    { 0x112F, 0x0000 }, { 0x1132, 0x0000 }, { 0x1136, 0x0000 }, { 0x1140, 0x0000 }, 
    { 0x1147, 0x0000 }, { 0x114C, 0x0000 }, { 0x11F1, 0x0000 }, { 0x11F2, 0x0000 }, 
    { 0x1157, 0x0000 }, { 0x1158, 0x0000 }, { 0x1159, 0x0000 }, { 0x1184, 0x0000 }, 
    { 0x1185, 0x0000 }, { 0x1188, 0x0000 }, { 0x1191, 0x0000 }, { 0x1192, 0x0000 }, 
    { 0x1194, 0x0000 }, { 0x119E, 0x0000 }, { 0x11A1, 0x0000 }, { 0x318F, 0x0000 }
  };

    const bool Hangul_Compatibility_Jamo3130::Alphabetic[] = {
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0
    };

    const bool Hangul_Compatibility_Jamo3130::Identifier_Part[] = {
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0
    };

}; // namespace Babylon
 
dload(Babylon::Hangul_Compatibility_Jamo3130);
