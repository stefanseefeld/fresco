/*$Id: E80-EFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:11:34 +0100.
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
 
  class LaoE80 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    LaoE80() {
      my_first_letter = 0xE80;
      my_last_letter  = 0xEFF;
      // my_version="3.0.1" // Not yet supported!

    }


    ~LaoE80() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Lao";
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
      switch(_uc) {
      case 0x0ED0:
        return 0;
        break;
      case 0x0ED1:
        return 1;
        break;
      case 0x0ED2:
        return 2;
        break;
      case 0x0ED3:
        return 3;
        break;
      case 0x0ED4:
        return 4;
        break;
      case 0x0ED5:
        return 5;
        break;
      case 0x0ED6:
        return 6;
        break;
      case 0x0ED7:
        return 7;
        break;
      case 0x0ED8:
        return 8;
        break;
      case 0x0ED9:
        return 9;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_DEC_DIGIT_VALUE);
      }
    }

    int digitValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
      case 0x0ED0:
        return 0;
        break;
      case 0x0ED1:
        return 1;
        break;
      case 0x0ED2:
        return 2;
        break;
      case 0x0ED3:
        return 3;
        break;
      case 0x0ED4:
        return 4;
        break;
      case 0x0ED5:
        return 5;
        break;
      case 0x0ED6:
        return 6;
        break;
      case 0x0ED7:
        return 7;
        break;
      case 0x0ED8:
        return 8;
        break;
      case 0x0ED9:
        return 9;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_DIGIT_VALUE);
      }
    }

    float numericValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
      case 0x0ED0:
        return 0.000000;
        break;
      case 0x0ED1:
        return 1.000000;
        break;
      case 0x0ED2:
        return 2.000000;
        break;
      case 0x0ED3:
        return 3.000000;
        break;
      case 0x0ED4:
        return 4.000000;
        break;
      case 0x0ED5:
        return 5.000000;
        break;
      case 0x0ED6:
        return 6.000000;
        break;
      case 0x0ED7:
        return 7.000000;
        break;
      case 0x0ED8:
        return 8.000000;
        break;
      case 0x0ED9:
        return 9.000000;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(LaoE80::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Can_Comb_Class(LaoE80::combCl[_uc - my_first_letter]);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(LaoE80::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(LaoE80::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = LaoE80::decompStr[_uc - my_first_letter][0];
      us[1] = LaoE80::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(LaoE80::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(EA_WIDTH_N);
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
      return LaoE80::Combining[_uc - my_first_letter];
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return LaoE80::Non_spacing[_uc - my_first_letter];
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return LaoE80::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return LaoE80::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return LaoE80::Extender[_uc - my_first_letter];
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return LaoE80::Identifier_Part[_uc - my_first_letter];
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
    LaoE80(const LaoE80 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[128];
    static const unsigned char cat[128];
    static const unsigned char combCl[128];
    static const unsigned char bidir[128];
    static const unsigned char decomp[128];
    static const UCS2 decompStr[128][2];
    static const unsigned char lb[128];
    static const bool Combining[128];
    static const bool Non_spacing[128];
    static const bool Alphabetic[128];
    static const bool Diacritic[128];
    static const bool Extender[128];
    static const bool Identifier_Part[128];

  }; // class LaoE80

  const bool LaoE80::isdefined[] = {
    0, 1, 1, 0, 1, 0, 0, 1, 
    1, 0, 1, 0, 0, 1, 0, 0, 
    0, 0, 0, 0, 1, 1, 1, 1, 
    0, 1, 1, 1, 1, 1, 1, 1, 
    0, 1, 1, 1, 0, 1, 0, 1, 
    0, 0, 1, 1, 0, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 1, 1, 1, 0, 0, 
    1, 1, 1, 1, 1, 0, 1, 0, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 0, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char LaoE80::cat[] = {
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lm, CAT_Lo, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo
  };

  const unsigned char LaoE80::combCl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    118, 118, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    122, 122, 122, 122, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char LaoE80::bidir[] = {
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
  };

  const unsigned char LaoE80::decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 LaoE80::decompStr[][2] = {
    { 0x0E80, 0x0000 }, { 0x0E81, 0x0000 }, { 0x0E82, 0x0000 }, { 0x0E83, 0x0000 }, 
    { 0x0E84, 0x0000 }, { 0x0E85, 0x0000 }, { 0x0E86, 0x0000 }, { 0x0E87, 0x0000 }, 
    { 0x0E88, 0x0000 }, { 0x0E89, 0x0000 }, { 0x0E8A, 0x0000 }, { 0x0E8B, 0x0000 }, 
    { 0x0E8C, 0x0000 }, { 0x0E8D, 0x0000 }, { 0x0E8E, 0x0000 }, { 0x0E8F, 0x0000 }, 
    { 0x0E90, 0x0000 }, { 0x0E91, 0x0000 }, { 0x0E92, 0x0000 }, { 0x0E93, 0x0000 }, 
    { 0x0E94, 0x0000 }, { 0x0E95, 0x0000 }, { 0x0E96, 0x0000 }, { 0x0E97, 0x0000 }, 
    { 0x0E98, 0x0000 }, { 0x0E99, 0x0000 }, { 0x0E9A, 0x0000 }, { 0x0E9B, 0x0000 }, 
    { 0x0E9C, 0x0000 }, { 0x0E9D, 0x0000 }, { 0x0E9E, 0x0000 }, { 0x0E9F, 0x0000 }, 
    { 0x0EA0, 0x0000 }, { 0x0EA1, 0x0000 }, { 0x0EA2, 0x0000 }, { 0x0EA3, 0x0000 }, 
    { 0x0EA4, 0x0000 }, { 0x0EA5, 0x0000 }, { 0x0EA6, 0x0000 }, { 0x0EA7, 0x0000 }, 
    { 0x0EA8, 0x0000 }, { 0x0EA9, 0x0000 }, { 0x0EAA, 0x0000 }, { 0x0EAB, 0x0000 }, 
    { 0x0EAC, 0x0000 }, { 0x0EAD, 0x0000 }, { 0x0EAE, 0x0000 }, { 0x0EAF, 0x0000 }, 
    { 0x0EB0, 0x0000 }, { 0x0EB1, 0x0000 }, { 0x0EB2, 0x0000 }, { 0x0ECD, 0x0EB2 }, 
    { 0x0EB4, 0x0000 }, { 0x0EB5, 0x0000 }, { 0x0EB6, 0x0000 }, { 0x0EB7, 0x0000 }, 
    { 0x0EB8, 0x0000 }, { 0x0EB9, 0x0000 }, { 0x0EBA, 0x0000 }, { 0x0EBB, 0x0000 }, 
    { 0x0EBC, 0x0000 }, { 0x0EBD, 0x0000 }, { 0x0EBE, 0x0000 }, { 0x0EBF, 0x0000 }, 
    { 0x0EC0, 0x0000 }, { 0x0EC1, 0x0000 }, { 0x0EC2, 0x0000 }, { 0x0EC3, 0x0000 }, 
    { 0x0EC4, 0x0000 }, { 0x0EC5, 0x0000 }, { 0x0EC6, 0x0000 }, { 0x0EC7, 0x0000 }, 
    { 0x0EC8, 0x0000 }, { 0x0EC9, 0x0000 }, { 0x0ECA, 0x0000 }, { 0x0ECB, 0x0000 }, 
    { 0x0ECC, 0x0000 }, { 0x0ECD, 0x0000 }, { 0x0ECE, 0x0000 }, { 0x0ECF, 0x0000 }, 
    { 0x0ED0, 0x0000 }, { 0x0ED1, 0x0000 }, { 0x0ED2, 0x0000 }, { 0x0ED3, 0x0000 }, 
    { 0x0ED4, 0x0000 }, { 0x0ED5, 0x0000 }, { 0x0ED6, 0x0000 }, { 0x0ED7, 0x0000 }, 
    { 0x0ED8, 0x0000 }, { 0x0ED9, 0x0000 }, { 0x0EDA, 0x0000 }, { 0x0EDB, 0x0000 }, 
    { 0x0EAB, 0x0E99 }, { 0x0EAB, 0x0EA1 }, { 0x0EDE, 0x0000 }, { 0x0EDF, 0x0000 }, 
    { 0x0EE0, 0x0000 }, { 0x0EE1, 0x0000 }, { 0x0EE2, 0x0000 }, { 0x0EE3, 0x0000 }, 
    { 0x0EE4, 0x0000 }, { 0x0EE5, 0x0000 }, { 0x0EE6, 0x0000 }, { 0x0EE7, 0x0000 }, 
    { 0x0EE8, 0x0000 }, { 0x0EE9, 0x0000 }, { 0x0EEA, 0x0000 }, { 0x0EEB, 0x0000 }, 
    { 0x0EEC, 0x0000 }, { 0x0EED, 0x0000 }, { 0x0EEE, 0x0000 }, { 0x0EEF, 0x0000 }, 
    { 0x0EF0, 0x0000 }, { 0x0EF1, 0x0000 }, { 0x0EF2, 0x0000 }, { 0x0EF3, 0x0000 }, 
    { 0x0EF4, 0x0000 }, { 0x0EF5, 0x0000 }, { 0x0EF6, 0x0000 }, { 0x0EF7, 0x0000 }, 
    { 0x0EF8, 0x0000 }, { 0x0EF9, 0x0000 }, { 0x0EFA, 0x0000 }, { 0x0EFB, 0x0000 }, 
    { 0x0EFC, 0x0000 }, { 0x0EFD, 0x0000 }, { 0x0EFE, 0x0000 }, { 0x0EFF, 0x0000 }
  };

  const unsigned char LaoE80::lb[] = {
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_CM, LB_SA, LB_SA, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_SA, LB_CM, LB_CM, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_SA, LB_SA, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_NU, LB_NU, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA
  };

    const bool LaoE80::Combining[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 0, 0, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::Non_spacing[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 0, 0, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::Alphabetic[] = {
        0, 1, 1, 0, 1, 0, 0, 1, 
        1, 0, 1, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 1, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        0, 1, 1, 1, 0, 1, 0, 1, 
        0, 0, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::Extender[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::Identifier_Part[] = {
        0, 1, 1, 0, 1, 0, 0, 1, 
        1, 0, 1, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 1, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        0, 1, 1, 1, 0, 1, 0, 1, 
        0, 0, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 0, 1, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::LaoE80);
