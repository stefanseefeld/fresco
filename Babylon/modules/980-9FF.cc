/*$Id: 980-9FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 15 Nov 2000 23:23:33 +0100.
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
 
  class Bengali : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Bengali() {
      my_first_letter = 0x0980;
      my_last_letter  = 0x09FF;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x09A109BC] = 0x09DC;
      composeMap[0x09A209BC] = 0x09DD;
      composeMap[0x09AF09BC] = 0x09DF;
      composeMap[0x09C709BE] = 0x09CB;
      composeMap[0x09C709D7] = 0x09CC;

    }


    ~Bengali() {
    }

    _UCS4 firstLetter() {
      return my_first_letter;
    }
 
    _UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const _UCS4 _uc) const {
      return "Bengali";
    }

    bool isDefined(const _UCS4 _uc) const {
      return (isdefined[_uc - my_first_letter]);
    }

    _UCS4 uppercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    _UCS4 lowercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    _UCS4 titlecase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    int decDigitValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
      case 0x09E6:
        return 0;
        break;
      case 0x09E7:
        return 1;
        break;
      case 0x09E8:
        return 2;
        break;
      case 0x09E9:
        return 3;
        break;
      case 0x09EA:
        return 4;
        break;
      case 0x09EB:
        return 5;
        break;
      case 0x09EC:
        return 6;
        break;
      case 0x09ED:
        return 7;
        break;
      case 0x09EE:
        return 8;
        break;
      case 0x09EF:
        return 9;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_DEC_DIGIT_VALUE);
      }
    }

    int digitValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
      case 0x09E6:
        return 0;
        break;
      case 0x09E7:
        return 1;
        break;
      case 0x09E8:
        return 2;
        break;
      case 0x09E9:
        return 3;
        break;
      case 0x09EA:
        return 4;
        break;
      case 0x09EB:
        return 5;
        break;
      case 0x09EC:
        return 6;
        break;
      case 0x09ED:
        return 7;
        break;
      case 0x09EE:
        return 8;
        break;
      case 0x09EF:
        return 9;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_DIGIT_VALUE);
      }
    }

    float numericValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
      case 0x09E6:
        return 0.000000;
        break;
      case 0x09E7:
        return 1.000000;
        break;
      case 0x09E8:
        return 2.000000;
        break;
      case 0x09E9:
        return 3.000000;
        break;
      case 0x09EA:
        return 4.000000;
        break;
      case 0x09EB:
        return 5.000000;
        break;
      case 0x09EC:
        return 6.000000;
        break;
      case 0x09ED:
        return 7.000000;
        break;
      case 0x09EE:
        return 8.000000;
        break;
      case 0x09EF:
        return 9.000000;
        break;
      case 0x09F4:
        return 1.000000;
        break;
      case 0x09F5:
        return 2.000000;
        break;
      case 0x09F6:
        return 3.000000;
        break;
      case 0x09F7:
        return 4.000000;
        break;
      case 0x09F9:
        return 16.000000;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(Bengali::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Can_Comb_Class(Bengali::combCl[_uc - my_first_letter]);
    }

    Bidir_Props bidirProps(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Bengali::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    _UTF32String decompose(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::_UTF32String us;
      us.resize(2);
      us[0] = Bengali::decompStr[_uc - my_first_letter][0];
      us[1] = Bengali::decompStr[_uc - my_first_letter][1];
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool mustMirror(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return 0;
    }

    Line_Break linebreak(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Line_Break(Bengali::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(EA_WIDTH_N);
    }

    _UCS4 compose (const _UCS4 starter, const _UCS4 last) {
      return composeMap[starter << 16 | last];
    }

    bool is_Zero_width(const _UCS4 _uc) const {
      return 0;
    }

    bool is_White_space(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Non_break(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Join_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Format_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Dash(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Hyphen(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Math(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Paired_Punctuation(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Left_of_Pair(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Combining(const _UCS4 _uc) const {
      return Bengali::Combining[_uc - my_first_letter];
    }

    bool is_Non_spacing(const _UCS4 _uc) const {
      return Bengali::Non_spacing[_uc - my_first_letter];
    }

    bool is_Hex_Digit(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Alphabetic(const _UCS4 _uc) const {
      return Bengali::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const _UCS4 _uc) const {
      return Bengali::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const _UCS4 _uc) const {
      return Bengali::Identifier_Part[_uc - my_first_letter];
    }

    bool is_Ignorable_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Embedding_or_Override(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Uppercase(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Lowercase(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Space(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zs);
    }

    bool is_ISO_Control(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Cc);
    }

    bool is_Punctuation(const _UCS4 _uc) const {
      return (isDefined(_uc) && (category(_uc) == CAT_Pc ||
                                 category(_uc) == CAT_Pd ||
                                 category(_uc) == CAT_Ps ||
                                 category(_uc) == CAT_Pe ||
                                 category(_uc) == CAT_Pi ||
                                 category(_uc) == CAT_Pf ||
                                 category(_uc) == CAT_Po)
             );
    }

    bool is_Line_Separator(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zl);
    }

    bool is_Paragraph_Separator(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zp);
    }

    bool is_Currency_Symbol(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Sc);
    }

    bool is_Titlecase(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Lt);
    }


  private:
    // functions
    Bengali(const Bengali &) {}
 
    Babylon::_UCS4 my_first_letter;
    Babylon::_UCS4 my_last_letter;
    static const bool isdefined[128];
    static const unsigned char cat[128];
    static const unsigned char combCl[128];
    static const unsigned char bidir[128];
    static const _UCS2 decompStr[128][2];
    static const unsigned char lb[128];
    map<_UCS4, _UCS4> composeMap;
    static const bool Combining[128];
    static const bool Non_spacing[128];
    static const bool Alphabetic[128];
    static const bool Diacritic[128];
    static const bool Identifier_Part[128];

  }; // class Bengali

  const bool Bengali::isdefined[] = {
    0, 1, 1, 1, 0, 1, 1, 1, 
    1, 1, 1, 1, 1, 0, 0, 1, 
    1, 0, 0, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 0, 1, 1, 1, 1, 1, 1, 
    1, 0, 1, 0, 0, 0, 1, 1, 
    1, 1, 0, 0, 1, 0, 1, 1, 
    1, 1, 1, 1, 1, 0, 0, 1, 
    1, 0, 0, 1, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 1, 1, 0, 1, 
    1, 1, 1, 1, 0, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0
  };

  const unsigned char Bengali::cat[] = {
    CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
    CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Lo, CAT_Lo, CAT_Sc, CAT_Sc, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_So, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
  };

  const unsigned char Bengali::combCl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 7, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 9, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Bengali::bidir[] = {
    BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_ET, BIDIR_ET, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM
  };

  const _UCS2 Bengali::decompStr[][2] = {
    { 0x0980, 0x0000 }, { 0x0981, 0x0000 }, { 0x0982, 0x0000 }, { 0x0983, 0x0000 }, 
    { 0x0984, 0x0000 }, { 0x0985, 0x0000 }, { 0x0986, 0x0000 }, { 0x0987, 0x0000 }, 
    { 0x0988, 0x0000 }, { 0x0989, 0x0000 }, { 0x098A, 0x0000 }, { 0x098B, 0x0000 }, 
    { 0x098C, 0x0000 }, { 0x098D, 0x0000 }, { 0x098E, 0x0000 }, { 0x098F, 0x0000 }, 
    { 0x0990, 0x0000 }, { 0x0991, 0x0000 }, { 0x0992, 0x0000 }, { 0x0993, 0x0000 }, 
    { 0x0994, 0x0000 }, { 0x0995, 0x0000 }, { 0x0996, 0x0000 }, { 0x0997, 0x0000 }, 
    { 0x0998, 0x0000 }, { 0x0999, 0x0000 }, { 0x099A, 0x0000 }, { 0x099B, 0x0000 }, 
    { 0x099C, 0x0000 }, { 0x099D, 0x0000 }, { 0x099E, 0x0000 }, { 0x099F, 0x0000 }, 
    { 0x09A0, 0x0000 }, { 0x09A1, 0x0000 }, { 0x09A2, 0x0000 }, { 0x09A3, 0x0000 }, 
    { 0x09A4, 0x0000 }, { 0x09A5, 0x0000 }, { 0x09A6, 0x0000 }, { 0x09A7, 0x0000 }, 
    { 0x09A8, 0x0000 }, { 0x09A9, 0x0000 }, { 0x09AA, 0x0000 }, { 0x09AB, 0x0000 }, 
    { 0x09AC, 0x0000 }, { 0x09AD, 0x0000 }, { 0x09AE, 0x0000 }, { 0x09AF, 0x0000 }, 
    { 0x09B0, 0x0000 }, { 0x09B1, 0x0000 }, { 0x09B2, 0x0000 }, { 0x09B3, 0x0000 }, 
    { 0x09B4, 0x0000 }, { 0x09B5, 0x0000 }, { 0x09B6, 0x0000 }, { 0x09B7, 0x0000 }, 
    { 0x09B8, 0x0000 }, { 0x09B9, 0x0000 }, { 0x09BA, 0x0000 }, { 0x09BB, 0x0000 }, 
    { 0x09BC, 0x0000 }, { 0x09BD, 0x0000 }, { 0x09BE, 0x0000 }, { 0x09BF, 0x0000 }, 
    { 0x09C0, 0x0000 }, { 0x09C1, 0x0000 }, { 0x09C2, 0x0000 }, { 0x09C3, 0x0000 }, 
    { 0x09C4, 0x0000 }, { 0x09C5, 0x0000 }, { 0x09C6, 0x0000 }, { 0x09C7, 0x0000 }, 
    { 0x09C8, 0x0000 }, { 0x09C9, 0x0000 }, { 0x09CA, 0x0000 }, { 0x09C7, 0x09BE }, 
    { 0x09C7, 0x09D7 }, { 0x09CD, 0x0000 }, { 0x09CE, 0x0000 }, { 0x09CF, 0x0000 }, 
    { 0x09D0, 0x0000 }, { 0x09D1, 0x0000 }, { 0x09D2, 0x0000 }, { 0x09D3, 0x0000 }, 
    { 0x09D4, 0x0000 }, { 0x09D5, 0x0000 }, { 0x09D6, 0x0000 }, { 0x09D7, 0x0000 }, 
    { 0x09D8, 0x0000 }, { 0x09D9, 0x0000 }, { 0x09DA, 0x0000 }, { 0x09DB, 0x0000 }, 
    { 0x09A1, 0x09BC }, { 0x09A2, 0x09BC }, { 0x09DE, 0x0000 }, { 0x09AF, 0x09BC }, 
    { 0x09E0, 0x0000 }, { 0x09E1, 0x0000 }, { 0x09E2, 0x0000 }, { 0x09E3, 0x0000 }, 
    { 0x09E4, 0x0000 }, { 0x09E5, 0x0000 }, { 0x09E6, 0x0000 }, { 0x09E7, 0x0000 }, 
    { 0x09E8, 0x0000 }, { 0x09E9, 0x0000 }, { 0x09EA, 0x0000 }, { 0x09EB, 0x0000 }, 
    { 0x09EC, 0x0000 }, { 0x09ED, 0x0000 }, { 0x09EE, 0x0000 }, { 0x09EF, 0x0000 }, 
    { 0x09F0, 0x0000 }, { 0x09F1, 0x0000 }, { 0x09F2, 0x0000 }, { 0x09F3, 0x0000 }, 
    { 0x09F4, 0x0000 }, { 0x09F5, 0x0000 }, { 0x09F6, 0x0000 }, { 0x09F7, 0x0000 }, 
    { 0x09F8, 0x0000 }, { 0x09F9, 0x0000 }, { 0x09FA, 0x0000 }, { 0x09FB, 0x0000 }, 
    { 0x09FC, 0x0000 }, { 0x09FD, 0x0000 }, { 0x09FE, 0x0000 }, { 0x09FF, 0x0000 }
  };

  const unsigned char Bengali::lb[] = {
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_AL, 
    LB_AL, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_CM, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_CM, LB_AL, 
    LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, LB_NU, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_AL, LB_AL, LB_PR, LB_PR, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
  };

    const bool Bengali::Combining[] = {
        0, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Bengali::Non_spacing[] = {
        0, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Bengali::Alphabetic[] = {
        0, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 0, 0, 0, 1, 1, 
        1, 1, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 0, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 1, 1, 0, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Bengali::Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Bengali::Identifier_Part[] = {
        0, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 0, 0, 0, 1, 1, 
        1, 1, 0, 0, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 1, 1, 0, 1, 
        1, 1, 1, 1, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Bengali);
