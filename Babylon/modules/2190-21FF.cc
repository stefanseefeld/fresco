/*$Id: 2190-21FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:12:34 +0100.
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
 
  class Arrows2190 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Arrows2190() {
      my_first_letter = 0x2190;
      my_last_letter  = 0x21FF;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x21900338] = 0x219A;
      composeMap[0x21920338] = 0x219B;
      composeMap[0x21940338] = 0x21AE;
      composeMap[0x21D00338] = 0x21CD;
      composeMap[0x21D20338] = 0x21CF;
      composeMap[0x21D40338] = 0x21CE;

    }


    ~Arrows2190() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Arrows";
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
      return Babylon::Gen_Cat(Arrows2190::cat[_uc - my_first_letter]);
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
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Arrows2190::decompStr[_uc - my_first_letter][0];
      us[1] = Arrows2190::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(Arrows2190::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(Arrows2190::ea[_uc - my_first_letter]);
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
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Math(const UCS4 & _uc) const {
      return Arrows2190::Math[_uc - my_first_letter];
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
    Arrows2190(const Arrows2190 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[112];
    static const unsigned char cat[112];
    static const UCS2 decompStr[112][2];
    static const unsigned char lb[112];
    static const unsigned char ea[112];
    map<UCS4, UCS4> composeMap;
    static const bool Math[112];

  }; // class Arrows2190

  const bool Arrows2190::isdefined[] = {
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
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Arrows2190::cat[] = {
    CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_Sm, CAT_Sm, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_Sm, CAT_So, CAT_So, CAT_Sm, CAT_So, CAT_So, CAT_Sm, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_Sm, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_Sm, CAT_Sm, 
    CAT_So, CAT_So, CAT_Sm, CAT_So, CAT_Sm, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
    CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm
  };

  const UCS2 Arrows2190::decompStr[][2] = {
    { 0x2190, 0x0000 }, { 0x2191, 0x0000 }, { 0x2192, 0x0000 }, { 0x2193, 0x0000 }, 
    { 0x2194, 0x0000 }, { 0x2195, 0x0000 }, { 0x2196, 0x0000 }, { 0x2197, 0x0000 }, 
    { 0x2198, 0x0000 }, { 0x2199, 0x0000 }, { 0x2190, 0x0338 }, { 0x2192, 0x0338 }, 
    { 0x219C, 0x0000 }, { 0x219D, 0x0000 }, { 0x219E, 0x0000 }, { 0x219F, 0x0000 }, 
    { 0x21A0, 0x0000 }, { 0x21A1, 0x0000 }, { 0x21A2, 0x0000 }, { 0x21A3, 0x0000 }, 
    { 0x21A4, 0x0000 }, { 0x21A5, 0x0000 }, { 0x21A6, 0x0000 }, { 0x21A7, 0x0000 }, 
    { 0x21A8, 0x0000 }, { 0x21A9, 0x0000 }, { 0x21AA, 0x0000 }, { 0x21AB, 0x0000 }, 
    { 0x21AC, 0x0000 }, { 0x21AD, 0x0000 }, { 0x2194, 0x0338 }, { 0x21AF, 0x0000 }, 
    { 0x21B0, 0x0000 }, { 0x21B1, 0x0000 }, { 0x21B2, 0x0000 }, { 0x21B3, 0x0000 }, 
    { 0x21B4, 0x0000 }, { 0x21B5, 0x0000 }, { 0x21B6, 0x0000 }, { 0x21B7, 0x0000 }, 
    { 0x21B8, 0x0000 }, { 0x21B9, 0x0000 }, { 0x21BA, 0x0000 }, { 0x21BB, 0x0000 }, 
    { 0x21BC, 0x0000 }, { 0x21BD, 0x0000 }, { 0x21BE, 0x0000 }, { 0x21BF, 0x0000 }, 
    { 0x21C0, 0x0000 }, { 0x21C1, 0x0000 }, { 0x21C2, 0x0000 }, { 0x21C3, 0x0000 }, 
    { 0x21C4, 0x0000 }, { 0x21C5, 0x0000 }, { 0x21C6, 0x0000 }, { 0x21C7, 0x0000 }, 
    { 0x21C8, 0x0000 }, { 0x21C9, 0x0000 }, { 0x21CA, 0x0000 }, { 0x21CB, 0x0000 }, 
    { 0x21CC, 0x0000 }, { 0x21D0, 0x0338 }, { 0x21D4, 0x0338 }, { 0x21D2, 0x0338 }, 
    { 0x21D0, 0x0000 }, { 0x21D1, 0x0000 }, { 0x21D2, 0x0000 }, { 0x21D3, 0x0000 }, 
    { 0x21D4, 0x0000 }, { 0x21D5, 0x0000 }, { 0x21D6, 0x0000 }, { 0x21D7, 0x0000 }, 
    { 0x21D8, 0x0000 }, { 0x21D9, 0x0000 }, { 0x21DA, 0x0000 }, { 0x21DB, 0x0000 }, 
    { 0x21DC, 0x0000 }, { 0x21DD, 0x0000 }, { 0x21DE, 0x0000 }, { 0x21DF, 0x0000 }, 
    { 0x21E0, 0x0000 }, { 0x21E1, 0x0000 }, { 0x21E2, 0x0000 }, { 0x21E3, 0x0000 }, 
    { 0x21E4, 0x0000 }, { 0x21E5, 0x0000 }, { 0x21E6, 0x0000 }, { 0x21E7, 0x0000 }, 
    { 0x21E8, 0x0000 }, { 0x21E9, 0x0000 }, { 0x21EA, 0x0000 }, { 0x21EB, 0x0000 }, 
    { 0x21EC, 0x0000 }, { 0x21ED, 0x0000 }, { 0x21EE, 0x0000 }, { 0x21EF, 0x0000 }, 
    { 0x21F0, 0x0000 }, { 0x21F1, 0x0000 }, { 0x21F2, 0x0000 }, { 0x21F3, 0x0000 }, 
    { 0x21F4, 0x0000 }, { 0x21F5, 0x0000 }, { 0x21F6, 0x0000 }, { 0x21F7, 0x0000 }, 
    { 0x21F8, 0x0000 }, { 0x21F9, 0x0000 }, { 0x21FA, 0x0000 }, { 0x21FB, 0x0000 }, 
    { 0x21FC, 0x0000 }, { 0x21FD, 0x0000 }, { 0x21FE, 0x0000 }, { 0x21FF, 0x0000 }
  };

  const unsigned char Arrows2190::lb[] = {
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AI, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI
  };

  const unsigned char Arrows2190::ea[] = {
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A
  };

    const bool Arrows2190::Math[] = {
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        1, 0, 0, 1, 0, 0, 1, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 1, 
        0, 0, 1, 0, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Arrows2190);
