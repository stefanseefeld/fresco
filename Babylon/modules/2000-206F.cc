/*$Id: 2000-206F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 15 Nov 2000 23:26:24 +0100.
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
 
  class General_Punctuation : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    General_Punctuation() {
      my_first_letter = 0x2000;
      my_last_letter  = 0x206F;
      // my_version="3.0.1" // Not yet supported!

    }


    ~General_Punctuation() {
    }

    _UCS4 firstLetter() {
      return my_first_letter;
    }
 
    _UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const _UCS4 _uc) const {
      return "General Punctuation";
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
      throw UndefinedProperty(_uc, PROP_DEC_DIGIT_VALUE);
    }

    int digitValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_DIGIT_VALUE);
    }

    float numericValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
    }

    Gen_Cat category(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(General_Punctuation::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(General_Punctuation::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(General_Punctuation::decomp[_uc - my_first_letter]);
    }

    _UTF32String decompose(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::_UTF32String us;
      us.resize(2);
      us[0] = General_Punctuation::decompStr[_uc - my_first_letter][0];
      us[1] = General_Punctuation::decompStr[_uc - my_first_letter][1];

      switch (_uc) {

      case 0x2026:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x2034:
        us.resize(3);
        us[2] = 0x2032;
        break;

      case 0x2037:
        us.resize(3);
        us[2] = 0x2035;
        break;
      }
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool mustMirror(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return General_Punctuation::mirror[_uc - my_first_letter];
    }

    Line_Break linebreak(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Line_Break(General_Punctuation::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(General_Punctuation::ea[_uc - my_first_letter]);
    }

    _UCS4 compose (const _UCS4 starter, const _UCS4 last) {
      return 0;
    }

    bool is_Zero_width(const _UCS4 _uc) const {
      return General_Punctuation::Zero_width[_uc - my_first_letter];
    }

    bool is_White_space(const _UCS4 _uc) const {
      return General_Punctuation::White_space[_uc - my_first_letter];
    }

    bool is_Non_break(const _UCS4 _uc) const {
      return General_Punctuation::Non_break[_uc - my_first_letter];
    }

    bool is_Bidi_Control(const _UCS4 _uc) const {
      return General_Punctuation::Bidi_Control[_uc - my_first_letter];
    }

    bool is_Join_Control(const _UCS4 _uc) const {
      return General_Punctuation::Join_Control[_uc - my_first_letter];
    }

    bool is_Format_Control(const _UCS4 _uc) const {
      return General_Punctuation::Format_Control[_uc - my_first_letter];
    }

    bool is_Dash(const _UCS4 _uc) const {
      return General_Punctuation::Dash[_uc - my_first_letter];
    }

    bool is_Hyphen(const _UCS4 _uc) const {
      return General_Punctuation::Hyphen[_uc - my_first_letter];
    }

    bool is_Quotation_Mark(const _UCS4 _uc) const {
      return General_Punctuation::Quotation_Mark[_uc - my_first_letter];
    }

    bool is_Terminal_Punctuation(const _UCS4 _uc) const {
      return General_Punctuation::Terminal_Punctuation[_uc - my_first_letter];
    }

    bool is_Math(const _UCS4 _uc) const {
      return General_Punctuation::Math[_uc - my_first_letter];
    }

    bool is_Paired_Punctuation(const _UCS4 _uc) const {
      return General_Punctuation::Paired_Punctuation[_uc - my_first_letter];
    }

    bool is_Left_of_Pair(const _UCS4 _uc) const {
      return General_Punctuation::Left_of_Pair[_uc - my_first_letter];
    }

    bool is_Combining(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Non_spacing(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Hex_Digit(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Alphabetic(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Diacritic(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Extender(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const _UCS4 _uc) const {
      return General_Punctuation::Identifier_Part[_uc - my_first_letter];
    }

    bool is_Ignorable_Control(const _UCS4 _uc) const {
      return General_Punctuation::Ignorable_Control[_uc - my_first_letter];
    }

    bool is_Bidi_Hebrew_Right_to_Left(const _UCS4 _uc) const {
      return General_Punctuation::Bidi_Hebrew_Right_to_Left[_uc - my_first_letter];
    }

    bool is_Bidi_Arabic_Right_to_Left(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Embedding_or_Override(const _UCS4 _uc) const {
      return General_Punctuation::Bidi_Embedding_or_Override[_uc - my_first_letter];
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
    General_Punctuation(const General_Punctuation &) {}
 
    Babylon::_UCS4 my_first_letter;
    Babylon::_UCS4 my_last_letter;
    static const bool isdefined[112];
    static const unsigned char cat[112];
    static const unsigned char bidir[112];
    static const unsigned char decomp[112];
    static const _UCS2 decompStr[112][2];
    static const bool mirror[112];
    static const unsigned char lb[112];
    static const unsigned char ea[112];
    static const bool Zero_width[112];
    static const bool White_space[112];
    static const bool Non_break[112];
    static const bool Bidi_Control[112];
    static const bool Join_Control[112];
    static const bool Format_Control[112];
    static const bool Dash[112];
    static const bool Hyphen[112];
    static const bool Quotation_Mark[112];
    static const bool Terminal_Punctuation[112];
    static const bool Math[112];
    static const bool Paired_Punctuation[112];
    static const bool Left_of_Pair[112];
    static const bool Identifier_Part[112];
    static const bool Ignorable_Control[112];
    static const bool Bidi_Hebrew_Right_to_Left[112];
    static const bool Bidi_Embedding_or_Override[112];

  }; // class General_Punctuation

  const bool General_Punctuation::isdefined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 1, 1, 1, 1, 1, 1
  };

  const unsigned char General_Punctuation::cat[] = {
    CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, 
    CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, 
    CAT_Pd, CAT_Pd, CAT_Pd, CAT_Pd, CAT_Pd, CAT_Pd, CAT_Po, CAT_Po, 
    CAT_Pi, CAT_Pf, CAT_Ps, CAT_Pi, CAT_Pi, CAT_Pf, CAT_Ps, CAT_Pi, 
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Zl, CAT_Zp, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Zs, 
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Po, CAT_Pi, CAT_Pf, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Pc, 
    CAT_Pc, CAT_Po, CAT_Po, CAT_Po, CAT_Sm, CAT_Ps, CAT_Pe, CAT_Zs, 
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Zs, CAT_Zs, 
    CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, 
    CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, 
    CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, 
    CAT_Zs, CAT_Zs, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf
  };

  const unsigned char General_Punctuation::bidir[] = {
    BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, 
    BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_L, BIDIR_R, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_WS, BIDIR_B, BIDIR_LRE, BIDIR_RLE, BIDIR_PDF, BIDIR_LRO, BIDIR_RLO, BIDIR_WS, 
    BIDIR_ET, BIDIR_ET, BIDIR_ET, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_WS, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_WS, BIDIR_WS, 
    BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, 
    BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, 
    BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, 
    BIDIR_WS, BIDIR_WS, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN
  };

  const unsigned char General_Punctuation::decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NOBREAK, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NOBREAK, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NOBREAK, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const _UCS2 General_Punctuation::decompStr[][2] = {
    { 0x2002, 0x0000 }, { 0x2003, 0x0000 }, { 0x0020, 0x0000 }, { 0x0020, 0x0000 }, 
    { 0x0020, 0x0000 }, { 0x0020, 0x0000 }, { 0x0020, 0x0000 }, { 0x0020, 0x0000 }, 
    { 0x0020, 0x0000 }, { 0x0020, 0x0000 }, { 0x0020, 0x0000 }, { 0x200B, 0x0000 }, 
    { 0x200C, 0x0000 }, { 0x200D, 0x0000 }, { 0x200E, 0x0000 }, { 0x200F, 0x0000 }, 
    { 0x2010, 0x0000 }, { 0x2010, 0x0000 }, { 0x2012, 0x0000 }, { 0x2013, 0x0000 }, 
    { 0x2014, 0x0000 }, { 0x2015, 0x0000 }, { 0x2016, 0x0000 }, { 0x0020, 0x0333 }, 
    { 0x2018, 0x0000 }, { 0x2019, 0x0000 }, { 0x201A, 0x0000 }, { 0x201B, 0x0000 }, 
    { 0x201C, 0x0000 }, { 0x201D, 0x0000 }, { 0x201E, 0x0000 }, { 0x201F, 0x0000 }, 
    { 0x2020, 0x0000 }, { 0x2021, 0x0000 }, { 0x2022, 0x0000 }, { 0x2023, 0x0000 }, 
    { 0x002E, 0x0000 }, { 0x002E, 0x002E }, { 0x002E, 0x002E }, { 0x2027, 0x0000 }, 
    { 0x2028, 0x0000 }, { 0x2029, 0x0000 }, { 0x202A, 0x0000 }, { 0x202B, 0x0000 }, 
    { 0x202C, 0x0000 }, { 0x202D, 0x0000 }, { 0x202E, 0x0000 }, { 0x0020, 0x0000 }, 
    { 0x2030, 0x0000 }, { 0x2031, 0x0000 }, { 0x2032, 0x0000 }, { 0x2032, 0x2032 }, 
    { 0x2032, 0x2032 }, { 0x2035, 0x0000 }, { 0x2035, 0x2035 }, { 0x2035, 0x2035 }, 
    { 0x2038, 0x0000 }, { 0x2039, 0x0000 }, { 0x203A, 0x0000 }, { 0x203B, 0x0000 }, 
    { 0x0021, 0x0021 }, { 0x203D, 0x0000 }, { 0x0020, 0x0305 }, { 0x203F, 0x0000 }, 
    { 0x2040, 0x0000 }, { 0x2041, 0x0000 }, { 0x2042, 0x0000 }, { 0x2043, 0x0000 }, 
    { 0x2044, 0x0000 }, { 0x2045, 0x0000 }, { 0x2046, 0x0000 }, { 0x2047, 0x0000 }, 
    { 0x003F, 0x0021 }, { 0x0021, 0x003F }, { 0x204A, 0x0000 }, { 0x204B, 0x0000 }, 
    { 0x204C, 0x0000 }, { 0x204D, 0x0000 }, { 0x204E, 0x0000 }, { 0x204F, 0x0000 }, 
    { 0x2050, 0x0000 }, { 0x2051, 0x0000 }, { 0x2052, 0x0000 }, { 0x2053, 0x0000 }, 
    { 0x2054, 0x0000 }, { 0x2055, 0x0000 }, { 0x2056, 0x0000 }, { 0x2057, 0x0000 }, 
    { 0x2058, 0x0000 }, { 0x2059, 0x0000 }, { 0x205A, 0x0000 }, { 0x205B, 0x0000 }, 
    { 0x205C, 0x0000 }, { 0x205D, 0x0000 }, { 0x205E, 0x0000 }, { 0x205F, 0x0000 }, 
    { 0x2060, 0x0000 }, { 0x2061, 0x0000 }, { 0x2062, 0x0000 }, { 0x2063, 0x0000 }, 
    { 0x2064, 0x0000 }, { 0x2065, 0x0000 }, { 0x2066, 0x0000 }, { 0x2067, 0x0000 }, 
    { 0x2068, 0x0000 }, { 0x2069, 0x0000 }, { 0x206A, 0x0000 }, { 0x206B, 0x0000 }, 
    { 0x206C, 0x0000 }, { 0x206D, 0x0000 }, { 0x206E, 0x0000 }, { 0x206F, 0x0000 }
  };

  const bool General_Punctuation::mirror[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 1, 1, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char General_Punctuation::lb[] = {
    LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_GL, 
    LB_BA, LB_BA, LB_BA, LB_ZW, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_BA, LB_GL, LB_BA, LB_BA, LB_B2, LB_AL, LB_AI, LB_AL, 
    LB_QU, LB_QU, LB_OP, LB_QU, LB_QU, LB_QU, LB_OP, LB_QU, 
    LB_AI, LB_AI, LB_AL, LB_AL, LB_IN, LB_IN, LB_IN, LB_BA, 
    LB_BK, LB_BK, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_GL, 
    LB_PO, LB_PO, LB_PO, LB_PO, LB_PO, LB_PO, LB_PO, LB_PO, 
    LB_AL, LB_QU, LB_QU, LB_AI, LB_NS, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_NS, LB_OP, LB_CL, LB_BA, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_BA, LB_BA, 
    LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, 
    LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, 
    LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, 
    LB_BA, LB_BA, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
  };

  const unsigned char General_Punctuation::ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bool General_Punctuation::Zero_width[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 1
    };

    const bool General_Punctuation::White_space[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Non_break[] = {
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Bidi_Control[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Join_Control[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Format_Control[] = {
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
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 1
    };

    const bool General_Punctuation::Dash[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Hyphen[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Quotation_Mark[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Terminal_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Math[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Paired_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Left_of_Pair[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 1, 1, 1, 0, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Identifier_Part[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Ignorable_Control[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 1
    };

    const bool General_Punctuation::Bidi_Hebrew_Right_to_Left[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool General_Punctuation::Bidi_Embedding_or_Override[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::General_Punctuation);
