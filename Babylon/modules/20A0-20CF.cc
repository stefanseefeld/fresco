/*$Id: 20A0-20CF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:12:30 +0100.
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
 
  class Currency_Symbols20A0 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Currency_Symbols20A0() {
      my_first_letter = 0x20A0;
      my_last_letter  = 0x20CF;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Currency_Symbols20A0() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Currency Symbols";
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
      return Babylon::Gen_Cat(CAT_Sc);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(BIDIR_ET);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Currency_Symbols20A0::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Currency_Symbols20A0::decompStr[_uc - my_first_letter][0];
      us[1] = Currency_Symbols20A0::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(Currency_Symbols20A0::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(Currency_Symbols20A0::ea[_uc - my_first_letter]);
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
    Currency_Symbols20A0(const Currency_Symbols20A0 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[48];
    static const unsigned char decomp[48];
    static const UCS2 decompStr[48][2];
    static const unsigned char lb[48];
    static const unsigned char ea[48];

  }; // class Currency_Symbols20A0

  const bool Currency_Symbols20A0::isdefined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Currency_Symbols20A0::decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Currency_Symbols20A0::decompStr[][2] = {
    { 0x20A0, 0x0000 }, { 0x20A1, 0x0000 }, { 0x20A2, 0x0000 }, { 0x20A3, 0x0000 }, 
    { 0x20A4, 0x0000 }, { 0x20A5, 0x0000 }, { 0x20A6, 0x0000 }, { 0x20A7, 0x0000 }, 
    { 0x0052, 0x0073 }, { 0x20A9, 0x0000 }, { 0x20AA, 0x0000 }, { 0x20AB, 0x0000 }, 
    { 0x20AC, 0x0000 }, { 0x20AD, 0x0000 }, { 0x20AE, 0x0000 }, { 0x20AF, 0x0000 }, 
    { 0x20B0, 0x0000 }, { 0x20B1, 0x0000 }, { 0x20B2, 0x0000 }, { 0x20B3, 0x0000 }, 
    { 0x20B4, 0x0000 }, { 0x20B5, 0x0000 }, { 0x20B6, 0x0000 }, { 0x20B7, 0x0000 }, 
    { 0x20B8, 0x0000 }, { 0x20B9, 0x0000 }, { 0x20BA, 0x0000 }, { 0x20BB, 0x0000 }, 
    { 0x20BC, 0x0000 }, { 0x20BD, 0x0000 }, { 0x20BE, 0x0000 }, { 0x20BF, 0x0000 }, 
    { 0x20C0, 0x0000 }, { 0x20C1, 0x0000 }, { 0x20C2, 0x0000 }, { 0x20C3, 0x0000 }, 
    { 0x20C4, 0x0000 }, { 0x20C5, 0x0000 }, { 0x20C6, 0x0000 }, { 0x20C7, 0x0000 }, 
    { 0x20C8, 0x0000 }, { 0x20C9, 0x0000 }, { 0x20CA, 0x0000 }, { 0x20CB, 0x0000 }, 
    { 0x20CC, 0x0000 }, { 0x20CD, 0x0000 }, { 0x20CE, 0x0000 }, { 0x20CF, 0x0000 }
  };

  const unsigned char Currency_Symbols20A0::lb[] = {
    LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PO, 
    LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, 
    LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, 
    LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, 
    LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, 
    LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR
  };

  const unsigned char Currency_Symbols20A0::ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_H, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

}; // namespace Babylon
 
dload(Babylon::Currency_Symbols20A0);
