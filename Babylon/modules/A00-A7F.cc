/*$Id: A00-A7F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:11:13 +0100.
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
 
  class GurmukhiA00 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    GurmukhiA00() {
      my_first_letter = 0xA00;
      my_last_letter  = 0xA7F;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x0A160A3C] = 0x0A59;
      composeMap[0x0A170A3C] = 0x0A5A;
      composeMap[0x0A1C0A3C] = 0x0A5B;
      composeMap[0x0A2B0A3C] = 0x0A5E;
      composeMap[0x0A320A3C] = 0x0A33;
      composeMap[0x0A380A3C] = 0x0A36;

    }


    ~GurmukhiA00() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Gurmukhi";
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
      case 0x0A66:
        return 0;
        break;
      case 0x0A67:
        return 1;
        break;
      case 0x0A68:
        return 2;
        break;
      case 0x0A69:
        return 3;
        break;
      case 0x0A6A:
        return 4;
        break;
      case 0x0A6B:
        return 5;
        break;
      case 0x0A6C:
        return 6;
        break;
      case 0x0A6D:
        return 7;
        break;
      case 0x0A6E:
        return 8;
        break;
      case 0x0A6F:
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
      case 0x0A66:
        return 0;
        break;
      case 0x0A67:
        return 1;
        break;
      case 0x0A68:
        return 2;
        break;
      case 0x0A69:
        return 3;
        break;
      case 0x0A6A:
        return 4;
        break;
      case 0x0A6B:
        return 5;
        break;
      case 0x0A6C:
        return 6;
        break;
      case 0x0A6D:
        return 7;
        break;
      case 0x0A6E:
        return 8;
        break;
      case 0x0A6F:
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
      case 0x0A66:
        return 0.000000;
        break;
      case 0x0A67:
        return 1.000000;
        break;
      case 0x0A68:
        return 2.000000;
        break;
      case 0x0A69:
        return 3.000000;
        break;
      case 0x0A6A:
        return 4.000000;
        break;
      case 0x0A6B:
        return 5.000000;
        break;
      case 0x0A6C:
        return 6.000000;
        break;
      case 0x0A6D:
        return 7.000000;
        break;
      case 0x0A6E:
        return 8.000000;
        break;
      case 0x0A6F:
        return 9.000000;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(GurmukhiA00::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Can_Comb_Class(GurmukhiA00::combCl[_uc - my_first_letter]);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(GurmukhiA00::bidir[_uc - my_first_letter]);
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
      us[0] = GurmukhiA00::decompStr[_uc - my_first_letter][0];
      us[1] = GurmukhiA00::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(GurmukhiA00::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(EA_WIDTH_N);
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
      return 0;
    }

    bool is_Paired_Punctuation(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Left_of_Pair(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Combining(const UCS4 & _uc) const {
      return GurmukhiA00::Combining[_uc - my_first_letter];
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return GurmukhiA00::Non_spacing[_uc - my_first_letter];
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return GurmukhiA00::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return GurmukhiA00::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return GurmukhiA00::Identifier_Part[_uc - my_first_letter];
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
    GurmukhiA00(const GurmukhiA00 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[128];
    static const unsigned char cat[128];
    static const unsigned char combCl[128];
    static const unsigned char bidir[128];
    static const UCS2 decompStr[128][2];
    static const unsigned char lb[128];
    map<UCS4, UCS4> composeMap;
    static const bool Combining[128];
    static const bool Non_spacing[128];
    static const bool Alphabetic[128];
    static const bool Diacritic[128];
    static const bool Identifier_Part[128];

  }; // class GurmukhiA00

  const bool GurmukhiA00::isdefined[] = {
    0, 0, 1, 0, 0, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 1, 
    1, 0, 0, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 0, 1, 1, 1, 1, 1, 1, 
    1, 0, 1, 1, 0, 1, 1, 0, 
    1, 1, 0, 0, 1, 0, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 1, 
    1, 0, 0, 1, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 1, 1, 1, 1, 0, 1, 0, 
    0, 0, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char GurmukhiA00::cat[] = {
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, 
    CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
  };

  const unsigned char GurmukhiA00::combCl[] = {
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

  const unsigned char GurmukhiA00::bidir[] = {
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM
  };

  const UCS2 GurmukhiA00::decompStr[][2] = {
    { 0x0A00, 0x0000 }, { 0x0A01, 0x0000 }, { 0x0A02, 0x0000 }, { 0x0A03, 0x0000 }, 
    { 0x0A04, 0x0000 }, { 0x0A05, 0x0000 }, { 0x0A06, 0x0000 }, { 0x0A07, 0x0000 }, 
    { 0x0A08, 0x0000 }, { 0x0A09, 0x0000 }, { 0x0A0A, 0x0000 }, { 0x0A0B, 0x0000 }, 
    { 0x0A0C, 0x0000 }, { 0x0A0D, 0x0000 }, { 0x0A0E, 0x0000 }, { 0x0A0F, 0x0000 }, 
    { 0x0A10, 0x0000 }, { 0x0A11, 0x0000 }, { 0x0A12, 0x0000 }, { 0x0A13, 0x0000 }, 
    { 0x0A14, 0x0000 }, { 0x0A15, 0x0000 }, { 0x0A16, 0x0000 }, { 0x0A17, 0x0000 }, 
    { 0x0A18, 0x0000 }, { 0x0A19, 0x0000 }, { 0x0A1A, 0x0000 }, { 0x0A1B, 0x0000 }, 
    { 0x0A1C, 0x0000 }, { 0x0A1D, 0x0000 }, { 0x0A1E, 0x0000 }, { 0x0A1F, 0x0000 }, 
    { 0x0A20, 0x0000 }, { 0x0A21, 0x0000 }, { 0x0A22, 0x0000 }, { 0x0A23, 0x0000 }, 
    { 0x0A24, 0x0000 }, { 0x0A25, 0x0000 }, { 0x0A26, 0x0000 }, { 0x0A27, 0x0000 }, 
    { 0x0A28, 0x0000 }, { 0x0A29, 0x0000 }, { 0x0A2A, 0x0000 }, { 0x0A2B, 0x0000 }, 
    { 0x0A2C, 0x0000 }, { 0x0A2D, 0x0000 }, { 0x0A2E, 0x0000 }, { 0x0A2F, 0x0000 }, 
    { 0x0A30, 0x0000 }, { 0x0A31, 0x0000 }, { 0x0A32, 0x0000 }, { 0x0A32, 0x0A3C }, 
    { 0x0A34, 0x0000 }, { 0x0A35, 0x0000 }, { 0x0A38, 0x0A3C }, { 0x0A37, 0x0000 }, 
    { 0x0A38, 0x0000 }, { 0x0A39, 0x0000 }, { 0x0A3A, 0x0000 }, { 0x0A3B, 0x0000 }, 
    { 0x0A3C, 0x0000 }, { 0x0A3D, 0x0000 }, { 0x0A3E, 0x0000 }, { 0x0A3F, 0x0000 }, 
    { 0x0A40, 0x0000 }, { 0x0A41, 0x0000 }, { 0x0A42, 0x0000 }, { 0x0A43, 0x0000 }, 
    { 0x0A44, 0x0000 }, { 0x0A45, 0x0000 }, { 0x0A46, 0x0000 }, { 0x0A47, 0x0000 }, 
    { 0x0A48, 0x0000 }, { 0x0A49, 0x0000 }, { 0x0A4A, 0x0000 }, { 0x0A4B, 0x0000 }, 
    { 0x0A4C, 0x0000 }, { 0x0A4D, 0x0000 }, { 0x0A4E, 0x0000 }, { 0x0A4F, 0x0000 }, 
    { 0x0A50, 0x0000 }, { 0x0A51, 0x0000 }, { 0x0A52, 0x0000 }, { 0x0A53, 0x0000 }, 
    { 0x0A54, 0x0000 }, { 0x0A55, 0x0000 }, { 0x0A56, 0x0000 }, { 0x0A57, 0x0000 }, 
    { 0x0A58, 0x0000 }, { 0x0A16, 0x0A3C }, { 0x0A17, 0x0A3C }, { 0x0A1C, 0x0A3C }, 
    { 0x0A5C, 0x0000 }, { 0x0A5D, 0x0000 }, { 0x0A2B, 0x0A3C }, { 0x0A5F, 0x0000 }, 
    { 0x0A60, 0x0000 }, { 0x0A61, 0x0000 }, { 0x0A62, 0x0000 }, { 0x0A63, 0x0000 }, 
    { 0x0A64, 0x0000 }, { 0x0A65, 0x0000 }, { 0x0A66, 0x0000 }, { 0x0A67, 0x0000 }, 
    { 0x0A68, 0x0000 }, { 0x0A69, 0x0000 }, { 0x0A6A, 0x0000 }, { 0x0A6B, 0x0000 }, 
    { 0x0A6C, 0x0000 }, { 0x0A6D, 0x0000 }, { 0x0A6E, 0x0000 }, { 0x0A6F, 0x0000 }, 
    { 0x0A70, 0x0000 }, { 0x0A71, 0x0000 }, { 0x0A72, 0x0000 }, { 0x0A73, 0x0000 }, 
    { 0x0A74, 0x0000 }, { 0x0A75, 0x0000 }, { 0x0A76, 0x0000 }, { 0x0A77, 0x0000 }, 
    { 0x0A78, 0x0000 }, { 0x0A79, 0x0000 }, { 0x0A7A, 0x0000 }, { 0x0A7B, 0x0000 }, 
    { 0x0A7C, 0x0000 }, { 0x0A7D, 0x0000 }, { 0x0A7E, 0x0000 }, { 0x0A7F, 0x0000 }
  };

  const unsigned char GurmukhiA00::lb[] = {
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, 
    LB_AL, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_CM, LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, LB_CM, 
    LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, LB_NU, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
  };

    const bool GurmukhiA00::Combining[] = {
        0, 0, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool GurmukhiA00::Non_spacing[] = {
        0, 0, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 1, 1, 0, 0, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool GurmukhiA00::Alphabetic[] = {
        0, 0, 1, 0, 0, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 0, 1, 1, 0, 
        1, 1, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 1, 
        1, 0, 0, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 0, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool GurmukhiA00::Diacritic[] = {
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

    const bool GurmukhiA00::Identifier_Part[] = {
        0, 0, 1, 0, 0, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 0, 1, 1, 0, 
        1, 1, 0, 0, 1, 0, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 0, 1, 0, 
        0, 0, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::GurmukhiA00);
