/*$Id: 1000-109F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:11:41 +0100.
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
 
  class Myanmar1000 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Myanmar1000() {
      my_first_letter = 0x1000;
      my_last_letter  = 0x109F;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Myanmar1000() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Myanmar";
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
      case 0x1040:
        return 0;
        break;
      case 0x1041:
        return 1;
        break;
      case 0x1042:
        return 2;
        break;
      case 0x1043:
        return 3;
        break;
      case 0x1044:
        return 4;
        break;
      case 0x1045:
        return 5;
        break;
      case 0x1046:
        return 6;
        break;
      case 0x1047:
        return 7;
        break;
      case 0x1048:
        return 8;
        break;
      case 0x1049:
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
      case 0x1040:
        return 0;
        break;
      case 0x1041:
        return 1;
        break;
      case 0x1042:
        return 2;
        break;
      case 0x1043:
        return 3;
        break;
      case 0x1044:
        return 4;
        break;
      case 0x1045:
        return 5;
        break;
      case 0x1046:
        return 6;
        break;
      case 0x1047:
        return 7;
        break;
      case 0x1048:
        return 8;
        break;
      case 0x1049:
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
      case 0x1040:
        return 0.000000;
        break;
      case 0x1041:
        return 1.000000;
        break;
      case 0x1042:
        return 2.000000;
        break;
      case 0x1043:
        return 3.000000;
        break;
      case 0x1044:
        return 4.000000;
        break;
      case 0x1045:
        return 5.000000;
        break;
      case 0x1046:
        return 6.000000;
        break;
      case 0x1047:
        return 7.000000;
        break;
      case 0x1048:
        return 8.000000;
        break;
      case 0x1049:
        return 9.000000;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(Myanmar1000::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Can_Comb_Class(Myanmar1000::combCl[_uc - my_first_letter]);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Myanmar1000::bidir[_uc - my_first_letter]);
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
      us[0] = Myanmar1000::decompStr[_uc - my_first_letter][0];
      us[1] = Myanmar1000::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(Myanmar1000::lb[_uc - my_first_letter]);
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
      return Myanmar1000::Terminal_Punctuation[_uc - my_first_letter];
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
      return Myanmar1000::Combining[_uc - my_first_letter];
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return Myanmar1000::Non_spacing[_uc - my_first_letter];
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return Myanmar1000::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return Myanmar1000::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return Myanmar1000::Identifier_Part[_uc - my_first_letter];
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
    Myanmar1000(const Myanmar1000 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[160];
    static const unsigned char cat[160];
    static const unsigned char combCl[160];
    static const unsigned char bidir[160];
    static const UCS2 decompStr[160][2];
    static const unsigned char lb[160];
    static const bool Terminal_Punctuation[160];
    static const bool Combining[160];
    static const bool Non_spacing[160];
    static const bool Alphabetic[160];
    static const bool Diacritic[160];
    static const bool Identifier_Part[160];

  }; // class Myanmar1000

  const bool Myanmar1000::isdefined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 1, 1, 1, 1, 1, 
    0, 1, 1, 0, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 1, 1, 
    1, 1, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Myanmar1000::cat[] = {
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, 
    CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mc, 
    CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo
  };

  const unsigned char Myanmar1000::combCl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 7, 
    0, 9, 0, 0, 0, 0, 0, 0, 
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

  const unsigned char Myanmar1000::bidir[] = {
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
  };

  const UCS2 Myanmar1000::decompStr[][2] = {
    { 0x1000, 0x0000 }, { 0x1001, 0x0000 }, { 0x1002, 0x0000 }, { 0x1003, 0x0000 }, 
    { 0x1004, 0x0000 }, { 0x1005, 0x0000 }, { 0x1006, 0x0000 }, { 0x1007, 0x0000 }, 
    { 0x1008, 0x0000 }, { 0x1009, 0x0000 }, { 0x100A, 0x0000 }, { 0x100B, 0x0000 }, 
    { 0x100C, 0x0000 }, { 0x100D, 0x0000 }, { 0x100E, 0x0000 }, { 0x100F, 0x0000 }, 
    { 0x1010, 0x0000 }, { 0x1011, 0x0000 }, { 0x1012, 0x0000 }, { 0x1013, 0x0000 }, 
    { 0x1014, 0x0000 }, { 0x1015, 0x0000 }, { 0x1016, 0x0000 }, { 0x1017, 0x0000 }, 
    { 0x1018, 0x0000 }, { 0x1019, 0x0000 }, { 0x101A, 0x0000 }, { 0x101B, 0x0000 }, 
    { 0x101C, 0x0000 }, { 0x101D, 0x0000 }, { 0x101E, 0x0000 }, { 0x101F, 0x0000 }, 
    { 0x1020, 0x0000 }, { 0x1021, 0x0000 }, { 0x1022, 0x0000 }, { 0x1023, 0x0000 }, 
    { 0x1024, 0x0000 }, { 0x1025, 0x0000 }, { 0x1025, 0x102E }, { 0x1027, 0x0000 }, 
    { 0x1028, 0x0000 }, { 0x1029, 0x0000 }, { 0x102A, 0x0000 }, { 0x102B, 0x0000 }, 
    { 0x102C, 0x0000 }, { 0x102D, 0x0000 }, { 0x102E, 0x0000 }, { 0x102F, 0x0000 }, 
    { 0x1030, 0x0000 }, { 0x1031, 0x0000 }, { 0x1032, 0x0000 }, { 0x1033, 0x0000 }, 
    { 0x1034, 0x0000 }, { 0x1035, 0x0000 }, { 0x1036, 0x0000 }, { 0x1037, 0x0000 }, 
    { 0x1038, 0x0000 }, { 0x1039, 0x0000 }, { 0x103A, 0x0000 }, { 0x103B, 0x0000 }, 
    { 0x103C, 0x0000 }, { 0x103D, 0x0000 }, { 0x103E, 0x0000 }, { 0x103F, 0x0000 }, 
    { 0x1040, 0x0000 }, { 0x1041, 0x0000 }, { 0x1042, 0x0000 }, { 0x1043, 0x0000 }, 
    { 0x1044, 0x0000 }, { 0x1045, 0x0000 }, { 0x1046, 0x0000 }, { 0x1047, 0x0000 }, 
    { 0x1048, 0x0000 }, { 0x1049, 0x0000 }, { 0x104A, 0x0000 }, { 0x104B, 0x0000 }, 
    { 0x104C, 0x0000 }, { 0x104D, 0x0000 }, { 0x104E, 0x0000 }, { 0x104F, 0x0000 }, 
    { 0x1050, 0x0000 }, { 0x1051, 0x0000 }, { 0x1052, 0x0000 }, { 0x1053, 0x0000 }, 
    { 0x1054, 0x0000 }, { 0x1055, 0x0000 }, { 0x1056, 0x0000 }, { 0x1057, 0x0000 }, 
    { 0x1058, 0x0000 }, { 0x1059, 0x0000 }, { 0x105A, 0x0000 }, { 0x105B, 0x0000 }, 
    { 0x105C, 0x0000 }, { 0x105D, 0x0000 }, { 0x105E, 0x0000 }, { 0x105F, 0x0000 }, 
    { 0x1060, 0x0000 }, { 0x1061, 0x0000 }, { 0x1062, 0x0000 }, { 0x1063, 0x0000 }, 
    { 0x1064, 0x0000 }, { 0x1065, 0x0000 }, { 0x1066, 0x0000 }, { 0x1067, 0x0000 }, 
    { 0x1068, 0x0000 }, { 0x1069, 0x0000 }, { 0x106A, 0x0000 }, { 0x106B, 0x0000 }, 
    { 0x106C, 0x0000 }, { 0x106D, 0x0000 }, { 0x106E, 0x0000 }, { 0x106F, 0x0000 }, 
    { 0x1070, 0x0000 }, { 0x1071, 0x0000 }, { 0x1072, 0x0000 }, { 0x1073, 0x0000 }, 
    { 0x1074, 0x0000 }, { 0x1075, 0x0000 }, { 0x1076, 0x0000 }, { 0x1077, 0x0000 }, 
    { 0x1078, 0x0000 }, { 0x1079, 0x0000 }, { 0x107A, 0x0000 }, { 0x107B, 0x0000 }, 
    { 0x107C, 0x0000 }, { 0x107D, 0x0000 }, { 0x107E, 0x0000 }, { 0x107F, 0x0000 }, 
    { 0x1080, 0x0000 }, { 0x1081, 0x0000 }, { 0x1082, 0x0000 }, { 0x1083, 0x0000 }, 
    { 0x1084, 0x0000 }, { 0x1085, 0x0000 }, { 0x1086, 0x0000 }, { 0x1087, 0x0000 }, 
    { 0x1088, 0x0000 }, { 0x1089, 0x0000 }, { 0x108A, 0x0000 }, { 0x108B, 0x0000 }, 
    { 0x108C, 0x0000 }, { 0x108D, 0x0000 }, { 0x108E, 0x0000 }, { 0x108F, 0x0000 }, 
    { 0x1090, 0x0000 }, { 0x1091, 0x0000 }, { 0x1092, 0x0000 }, { 0x1093, 0x0000 }, 
    { 0x1094, 0x0000 }, { 0x1095, 0x0000 }, { 0x1096, 0x0000 }, { 0x1097, 0x0000 }, 
    { 0x1098, 0x0000 }, { 0x1099, 0x0000 }, { 0x109A, 0x0000 }, { 0x109B, 0x0000 }, 
    { 0x109C, 0x0000 }, { 0x109D, 0x0000 }, { 0x109E, 0x0000 }, { 0x109F, 0x0000 }
  };

  const unsigned char Myanmar1000::lb[] = {
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_SA, LB_SA, LB_SA, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_NU, LB_NU, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA
  };

    const bool Myanmar1000::Terminal_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
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

    const bool Myanmar1000::Combining[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Myanmar1000::Non_spacing[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 1, 
        1, 0, 1, 0, 0, 0, 1, 1, 
        0, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Myanmar1000::Alphabetic[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 1, 1, 
        0, 1, 1, 0, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 1, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Myanmar1000::Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 1, 0, 0, 0, 0, 0, 0, 
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

    const bool Myanmar1000::Identifier_Part[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 1, 1, 
        0, 1, 1, 0, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
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
 
dload(Babylon::Myanmar1000);
