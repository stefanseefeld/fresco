/*$Id: 30A0-30FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:13:15 +0100.
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
#include <map>

namespace Babylon {
 
  class Katakana30A0 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Katakana30A0() {
      my_first_letter = 0x30A0;
      my_last_letter  = 0x30FF;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x30A63099] = 0x30F4;
      composeMap[0x30AB3099] = 0x30AC;
      composeMap[0x30AD3099] = 0x30AE;
      composeMap[0x30AF3099] = 0x30B0;
      composeMap[0x30B13099] = 0x30B2;
      composeMap[0x30B33099] = 0x30B4;
      composeMap[0x30B53099] = 0x30B6;
      composeMap[0x30B73099] = 0x30B8;
      composeMap[0x30B93099] = 0x30BA;
      composeMap[0x30BB3099] = 0x30BC;
      composeMap[0x30BD3099] = 0x30BE;
      composeMap[0x30BF3099] = 0x30C0;
      composeMap[0x30C13099] = 0x30C2;
      composeMap[0x30C43099] = 0x30C5;
      composeMap[0x30C63099] = 0x30C7;
      composeMap[0x30C83099] = 0x30C9;
      composeMap[0x30CF3099] = 0x30D0;
      composeMap[0x30CF309A] = 0x30D1;
      composeMap[0x30D23099] = 0x30D3;
      composeMap[0x30D2309A] = 0x30D4;
      composeMap[0x30D53099] = 0x30D6;
      composeMap[0x30D5309A] = 0x30D7;
      composeMap[0x30D83099] = 0x30D9;
      composeMap[0x30D8309A] = 0x30DA;
      composeMap[0x30DB3099] = 0x30DC;
      composeMap[0x30DB309A] = 0x30DD;
      composeMap[0x30EF3099] = 0x30F7;
      composeMap[0x30F03099] = 0x30F8;
      composeMap[0x30F13099] = 0x30F9;
      composeMap[0x30F23099] = 0x30FA;
      composeMap[0x30FD3099] = 0x30FE;

    }


    ~Katakana30A0() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Katakana";
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
      return Babylon::Gen_Cat(Katakana30A0::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Katakana30A0::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Katakana30A0::decompStr[_uc - my_first_letter][0];
      us[1] = Katakana30A0::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(Katakana30A0::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(EA_WIDTH_W);
    }

    UCS4 compose (const UCS4 & starter, const UCS4 & last) {
      return composeMap[starter << 16 | last];
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
      return Katakana30A0::Hyphen[_uc - my_first_letter];
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
      return Katakana30A0::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return Katakana30A0::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return Katakana30A0::Extender[_uc - my_first_letter];
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return Katakana30A0::Identifier_Part[_uc - my_first_letter];
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
    Katakana30A0(const Katakana30A0 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[96];
    static const unsigned char cat[96];
    static const unsigned char bidir[96];
    static const UCS2 decompStr[96][2];
    static const unsigned char lb[96];
    map<UCS4, UCS4> composeMap;
    static const bool Hyphen[96];
    static const bool Alphabetic[96];
    static const bool Diacritic[96];
    static const bool Extender[96];
    static const bool Identifier_Part[96];

  }; // class Katakana30A0

  const bool Katakana30A0::isdefined[] = {
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

  const unsigned char Katakana30A0::cat[] = {
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Pc, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lo
  };

  const unsigned char Katakana30A0::bidir[] = {
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
  };

  const UCS2 Katakana30A0::decompStr[][2] = {
    { 0x30A0, 0x0000 }, { 0x30A1, 0x0000 }, { 0x30A2, 0x0000 }, { 0x30A3, 0x0000 }, 
    { 0x30A4, 0x0000 }, { 0x30A5, 0x0000 }, { 0x30A6, 0x0000 }, { 0x30A7, 0x0000 }, 
    { 0x30A8, 0x0000 }, { 0x30A9, 0x0000 }, { 0x30AA, 0x0000 }, { 0x30AB, 0x0000 }, 
    { 0x30AB, 0x3099 }, { 0x30AD, 0x0000 }, { 0x30AD, 0x3099 }, { 0x30AF, 0x0000 }, 
    { 0x30AF, 0x3099 }, { 0x30B1, 0x0000 }, { 0x30B1, 0x3099 }, { 0x30B3, 0x0000 }, 
    { 0x30B3, 0x3099 }, { 0x30B5, 0x0000 }, { 0x30B5, 0x3099 }, { 0x30B7, 0x0000 }, 
    { 0x30B7, 0x3099 }, { 0x30B9, 0x0000 }, { 0x30B9, 0x3099 }, { 0x30BB, 0x0000 }, 
    { 0x30BB, 0x3099 }, { 0x30BD, 0x0000 }, { 0x30BD, 0x3099 }, { 0x30BF, 0x0000 }, 
    { 0x30BF, 0x3099 }, { 0x30C1, 0x0000 }, { 0x30C1, 0x3099 }, { 0x30C3, 0x0000 }, 
    { 0x30C4, 0x0000 }, { 0x30C4, 0x3099 }, { 0x30C6, 0x0000 }, { 0x30C6, 0x3099 }, 
    { 0x30C8, 0x0000 }, { 0x30C8, 0x3099 }, { 0x30CA, 0x0000 }, { 0x30CB, 0x0000 }, 
    { 0x30CC, 0x0000 }, { 0x30CD, 0x0000 }, { 0x30CE, 0x0000 }, { 0x30CF, 0x0000 }, 
    { 0x30CF, 0x3099 }, { 0x30CF, 0x309A }, { 0x30D2, 0x0000 }, { 0x30D2, 0x3099 }, 
    { 0x30D2, 0x309A }, { 0x30D5, 0x0000 }, { 0x30D5, 0x3099 }, { 0x30D5, 0x309A }, 
    { 0x30D8, 0x0000 }, { 0x30D8, 0x3099 }, { 0x30D8, 0x309A }, { 0x30DB, 0x0000 }, 
    { 0x30DB, 0x3099 }, { 0x30DB, 0x309A }, { 0x30DE, 0x0000 }, { 0x30DF, 0x0000 }, 
    { 0x30E0, 0x0000 }, { 0x30E1, 0x0000 }, { 0x30E2, 0x0000 }, { 0x30E3, 0x0000 }, 
    { 0x30E4, 0x0000 }, { 0x30E5, 0x0000 }, { 0x30E6, 0x0000 }, { 0x30E7, 0x0000 }, 
    { 0x30E8, 0x0000 }, { 0x30E9, 0x0000 }, { 0x30EA, 0x0000 }, { 0x30EB, 0x0000 }, 
    { 0x30EC, 0x0000 }, { 0x30ED, 0x0000 }, { 0x30EE, 0x0000 }, { 0x30EF, 0x0000 }, 
    { 0x30F0, 0x0000 }, { 0x30F1, 0x0000 }, { 0x30F2, 0x0000 }, { 0x30F3, 0x0000 }, 
    { 0x30A6, 0x3099 }, { 0x30F5, 0x0000 }, { 0x30F6, 0x0000 }, { 0x30EF, 0x3099 }, 
    { 0x30F0, 0x3099 }, { 0x30F1, 0x3099 }, { 0x30F2, 0x3099 }, { 0x30FB, 0x0000 }, 
    { 0x30FC, 0x0000 }, { 0x30FD, 0x0000 }, { 0x30FD, 0x3099 }, { 0x30FF, 0x0000 }
  };

  const unsigned char Katakana30A0::lb[] = {
    LB_NS, LB_NS, LB_ID, LB_NS, LB_ID, LB_NS, LB_ID, LB_NS, 
    LB_ID, LB_NS, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_NS, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_NS, LB_ID, LB_NS, LB_ID, LB_NS, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_NS, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_NS, LB_NS, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_NS, LB_ID, LB_NS, LB_ID, LB_NS
  };

    const bool Katakana30A0::Hyphen[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0
    };

    const bool Katakana30A0::Alphabetic[] = {
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
        1, 1, 1, 0, 0, 0, 0, 0
    };

    const bool Katakana30A0::Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 0, 0
    };

    const bool Katakana30A0::Extender[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 0
    };

    const bool Katakana30A0::Identifier_Part[] = {
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
 
dload(Babylon::Katakana30A0);
