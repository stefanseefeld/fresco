/*$Id: 100-17F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 15 Nov 2000 23:22:27 +0100.
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
 
  class Latin_ExtendedA : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Latin_ExtendedA() {
      my_first_letter = 0x0100;
      my_last_letter  = 0x017F;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x01020300] = 0x1EB0;
      composeMap[0x01020301] = 0x1EAE;
      composeMap[0x01020303] = 0x1EB4;
      composeMap[0x01020309] = 0x1EB2;
      composeMap[0x01030300] = 0x1EB1;
      composeMap[0x01030301] = 0x1EAF;
      composeMap[0x01030303] = 0x1EB5;
      composeMap[0x01030309] = 0x1EB3;
      composeMap[0x01120300] = 0x1E14;
      composeMap[0x01120301] = 0x1E16;
      composeMap[0x01130300] = 0x1E15;
      composeMap[0x01130301] = 0x1E17;
      composeMap[0x014C0300] = 0x1E50;
      composeMap[0x014C0301] = 0x1E52;
      composeMap[0x014D0300] = 0x1E51;
      composeMap[0x014D0301] = 0x1E53;
      composeMap[0x015A0307] = 0x1E64;
      composeMap[0x015B0307] = 0x1E65;
      composeMap[0x01600307] = 0x1E66;
      composeMap[0x01610307] = 0x1E67;
      composeMap[0x01680301] = 0x1E78;
      composeMap[0x01690301] = 0x1E79;
      composeMap[0x016A0308] = 0x1E7A;
      composeMap[0x016B0308] = 0x1E7B;
      composeMap[0x017F0307] = 0x1E9B;

    }


    ~Latin_ExtendedA() {
    }

    _UCS4 firstLetter() {
      return my_first_letter;
    }
 
    _UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const _UCS4 _uc) const {
      return "Latin Extended-A";
    }

    bool isDefined(const _UCS4 _uc) const {
      return 1;
    }

    _UCS4 uppercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Latin_ExtendedA::upper[_uc - my_first_letter];
    }

    _UCS4 lowercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Latin_ExtendedA::lower[_uc - my_first_letter];
    }

    _UCS4 titlecase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Latin_ExtendedA::title[_uc - my_first_letter];
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
      return Babylon::Gen_Cat(Latin_ExtendedA::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(BIDIR_L);
    }

    Char_Decomp decompType(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Latin_ExtendedA::decomp[_uc - my_first_letter]);
    }

    _UTF32String decompose(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::_UTF32String us;
      us.resize(2);
      us[0] = Latin_ExtendedA::decompStr[_uc - my_first_letter][0];
      us[1] = Latin_ExtendedA::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(Latin_ExtendedA::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(Latin_ExtendedA::ea[_uc - my_first_letter]);
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
      return 0;
    }

    bool is_Non_spacing(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Hex_Digit(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Alphabetic(const _UCS4 _uc) const {
      return 1;
    }

    bool is_Diacritic(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Extender(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const _UCS4 _uc) const {
      return 1;
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
      return Latin_ExtendedA::Uppercase[_uc - my_first_letter];
    }

    bool is_Lowercase(const _UCS4 _uc) const {
      return Latin_ExtendedA::Lowercase[_uc - my_first_letter];
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
    Latin_ExtendedA(const Latin_ExtendedA &) {}
 
    Babylon::_UCS4 my_first_letter;
    Babylon::_UCS4 my_last_letter;
    static const _UCS4 upper[128];
    static const _UCS4 lower[128];
    static const _UCS4 title[128];
    static const unsigned char cat[128];
    static const unsigned char decomp[128];
    static const _UCS2 decompStr[128][2];
    static const unsigned char lb[128];
    static const unsigned char ea[128];
    map<_UCS4, _UCS4> composeMap;
    static const bool Uppercase[128];
    static const bool Lowercase[128];

  }; // class Latin_ExtendedA

  const _UCS4 Latin_ExtendedA::upper[] = {
    0x0100, 0x0100, 0x0102, 0x0102, 0x0104, 0x0104, 0x0106, 0x0106, 
    0x0108, 0x0108, 0x010A, 0x010A, 0x010C, 0x010C, 0x010E, 0x010E, 
    0x0110, 0x0110, 0x0112, 0x0112, 0x0114, 0x0114, 0x0116, 0x0116, 
    0x0118, 0x0118, 0x011A, 0x011A, 0x011C, 0x011C, 0x011E, 0x011E, 
    0x0120, 0x0120, 0x0122, 0x0122, 0x0124, 0x0124, 0x0126, 0x0126, 
    0x0128, 0x0128, 0x012A, 0x012A, 0x012C, 0x012C, 0x012E, 0x012E, 
    0x0130, 0x0049, 0x0132, 0x0132, 0x0134, 0x0134, 0x0136, 0x0136, 
    0x0138, 0x0139, 0x0139, 0x013B, 0x013B, 0x013D, 0x013D, 0x013F, 
    0x013F, 0x0141, 0x0141, 0x0143, 0x0143, 0x0145, 0x0145, 0x0147, 
    0x0147, 0x0149, 0x014A, 0x014A, 0x014C, 0x014C, 0x014E, 0x014E, 
    0x0150, 0x0150, 0x0152, 0x0152, 0x0154, 0x0154, 0x0156, 0x0156, 
    0x0158, 0x0158, 0x015A, 0x015A, 0x015C, 0x015C, 0x015E, 0x015E, 
    0x0160, 0x0160, 0x0162, 0x0162, 0x0164, 0x0164, 0x0166, 0x0166, 
    0x0168, 0x0168, 0x016A, 0x016A, 0x016C, 0x016C, 0x016E, 0x016E, 
    0x0170, 0x0170, 0x0172, 0x0172, 0x0174, 0x0174, 0x0176, 0x0176, 
    0x0178, 0x0179, 0x0179, 0x017B, 0x017B, 0x017D, 0x017D, 0x0053
  };

  const _UCS4 Latin_ExtendedA::lower[] = {
    0x0101, 0x0101, 0x0103, 0x0103, 0x0105, 0x0105, 0x0107, 0x0107, 
    0x0109, 0x0109, 0x010B, 0x010B, 0x010D, 0x010D, 0x010F, 0x010F, 
    0x0111, 0x0111, 0x0113, 0x0113, 0x0115, 0x0115, 0x0117, 0x0117, 
    0x0119, 0x0119, 0x011B, 0x011B, 0x011D, 0x011D, 0x011F, 0x011F, 
    0x0121, 0x0121, 0x0123, 0x0123, 0x0125, 0x0125, 0x0127, 0x0127, 
    0x0129, 0x0129, 0x012B, 0x012B, 0x012D, 0x012D, 0x012F, 0x012F, 
    0x0069, 0x0131, 0x0133, 0x0133, 0x0135, 0x0135, 0x0137, 0x0137, 
    0x0138, 0x013A, 0x013A, 0x013C, 0x013C, 0x013E, 0x013E, 0x0140, 
    0x0140, 0x0142, 0x0142, 0x0144, 0x0144, 0x0146, 0x0146, 0x0148, 
    0x0148, 0x0149, 0x014B, 0x014B, 0x014D, 0x014D, 0x014F, 0x014F, 
    0x0151, 0x0151, 0x0153, 0x0153, 0x0155, 0x0155, 0x0157, 0x0157, 
    0x0159, 0x0159, 0x015B, 0x015B, 0x015D, 0x015D, 0x015F, 0x015F, 
    0x0161, 0x0161, 0x0163, 0x0163, 0x0165, 0x0165, 0x0167, 0x0167, 
    0x0169, 0x0169, 0x016B, 0x016B, 0x016D, 0x016D, 0x016F, 0x016F, 
    0x0171, 0x0171, 0x0173, 0x0173, 0x0175, 0x0175, 0x0177, 0x0177, 
    0x00FF, 0x017A, 0x017A, 0x017C, 0x017C, 0x017E, 0x017E, 0x017F
  };

  const _UCS4 Latin_ExtendedA::title[] = {
    0x0100, 0x0100, 0x0102, 0x0102, 0x0104, 0x0104, 0x0106, 0x0106, 
    0x0108, 0x0108, 0x010A, 0x010A, 0x010C, 0x010C, 0x010E, 0x010E, 
    0x0110, 0x0110, 0x0112, 0x0112, 0x0114, 0x0114, 0x0116, 0x0116, 
    0x0118, 0x0118, 0x011A, 0x011A, 0x011C, 0x011C, 0x011E, 0x011E, 
    0x0120, 0x0120, 0x0122, 0x0122, 0x0124, 0x0124, 0x0126, 0x0126, 
    0x0128, 0x0128, 0x012A, 0x012A, 0x012C, 0x012C, 0x012E, 0x012E, 
    0x0130, 0x0049, 0x0132, 0x0132, 0x0134, 0x0134, 0x0136, 0x0136, 
    0x0138, 0x0139, 0x0139, 0x013B, 0x013B, 0x013D, 0x013D, 0x013F, 
    0x013F, 0x0141, 0x0141, 0x0143, 0x0143, 0x0145, 0x0145, 0x0147, 
    0x0147, 0x0149, 0x014A, 0x014A, 0x014C, 0x014C, 0x014E, 0x014E, 
    0x0150, 0x0150, 0x0152, 0x0152, 0x0154, 0x0154, 0x0156, 0x0156, 
    0x0158, 0x0158, 0x015A, 0x015A, 0x015C, 0x015C, 0x015E, 0x015E, 
    0x0160, 0x0160, 0x0162, 0x0162, 0x0164, 0x0164, 0x0166, 0x0166, 
    0x0168, 0x0168, 0x016A, 0x016A, 0x016C, 0x016C, 0x016E, 0x016E, 
    0x0170, 0x0170, 0x0172, 0x0172, 0x0174, 0x0174, 0x0176, 0x0176, 
    0x0178, 0x0179, 0x0179, 0x017B, 0x017B, 0x017D, 0x017D, 0x0053
  };

  const unsigned char Latin_ExtendedA::cat[] = {
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
    CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
    CAT_Ll, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll
  };

  const unsigned char Latin_ExtendedA::decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT
  };

  const _UCS2 Latin_ExtendedA::decompStr[][2] = {
    { 0x0041, 0x0304 }, { 0x0061, 0x0304 }, { 0x0041, 0x0306 }, { 0x0061, 0x0306 }, 
    { 0x0041, 0x0328 }, { 0x0061, 0x0328 }, { 0x0043, 0x0301 }, { 0x0063, 0x0301 }, 
    { 0x0043, 0x0302 }, { 0x0063, 0x0302 }, { 0x0043, 0x0307 }, { 0x0063, 0x0307 }, 
    { 0x0043, 0x030C }, { 0x0063, 0x030C }, { 0x0044, 0x030C }, { 0x0064, 0x030C }, 
    { 0x0110, 0x0000 }, { 0x0111, 0x0000 }, { 0x0045, 0x0304 }, { 0x0065, 0x0304 }, 
    { 0x0045, 0x0306 }, { 0x0065, 0x0306 }, { 0x0045, 0x0307 }, { 0x0065, 0x0307 }, 
    { 0x0045, 0x0328 }, { 0x0065, 0x0328 }, { 0x0045, 0x030C }, { 0x0065, 0x030C }, 
    { 0x0047, 0x0302 }, { 0x0067, 0x0302 }, { 0x0047, 0x0306 }, { 0x0067, 0x0306 }, 
    { 0x0047, 0x0307 }, { 0x0067, 0x0307 }, { 0x0047, 0x0327 }, { 0x0067, 0x0327 }, 
    { 0x0048, 0x0302 }, { 0x0068, 0x0302 }, { 0x0126, 0x0000 }, { 0x0127, 0x0000 }, 
    { 0x0049, 0x0303 }, { 0x0069, 0x0303 }, { 0x0049, 0x0304 }, { 0x0069, 0x0304 }, 
    { 0x0049, 0x0306 }, { 0x0069, 0x0306 }, { 0x0049, 0x0328 }, { 0x0069, 0x0328 }, 
    { 0x0049, 0x0307 }, { 0x0131, 0x0000 }, { 0x0049, 0x004A }, { 0x0069, 0x006A }, 
    { 0x004A, 0x0302 }, { 0x006A, 0x0302 }, { 0x004B, 0x0327 }, { 0x006B, 0x0327 }, 
    { 0x0138, 0x0000 }, { 0x004C, 0x0301 }, { 0x006C, 0x0301 }, { 0x004C, 0x0327 }, 
    { 0x006C, 0x0327 }, { 0x004C, 0x030C }, { 0x006C, 0x030C }, { 0x004C, 0x00B7 }, 
    { 0x006C, 0x00B7 }, { 0x0141, 0x0000 }, { 0x0142, 0x0000 }, { 0x004E, 0x0301 }, 
    { 0x006E, 0x0301 }, { 0x004E, 0x0327 }, { 0x006E, 0x0327 }, { 0x004E, 0x030C }, 
    { 0x006E, 0x030C }, { 0x02BC, 0x006E }, { 0x014A, 0x0000 }, { 0x014B, 0x0000 }, 
    { 0x004F, 0x0304 }, { 0x006F, 0x0304 }, { 0x004F, 0x0306 }, { 0x006F, 0x0306 }, 
    { 0x004F, 0x030B }, { 0x006F, 0x030B }, { 0x0152, 0x0000 }, { 0x0153, 0x0000 }, 
    { 0x0052, 0x0301 }, { 0x0072, 0x0301 }, { 0x0052, 0x0327 }, { 0x0072, 0x0327 }, 
    { 0x0052, 0x030C }, { 0x0072, 0x030C }, { 0x0053, 0x0301 }, { 0x0073, 0x0301 }, 
    { 0x0053, 0x0302 }, { 0x0073, 0x0302 }, { 0x0053, 0x0327 }, { 0x0073, 0x0327 }, 
    { 0x0053, 0x030C }, { 0x0073, 0x030C }, { 0x0054, 0x0327 }, { 0x0074, 0x0327 }, 
    { 0x0054, 0x030C }, { 0x0074, 0x030C }, { 0x0166, 0x0000 }, { 0x0167, 0x0000 }, 
    { 0x0055, 0x0303 }, { 0x0075, 0x0303 }, { 0x0055, 0x0304 }, { 0x0075, 0x0304 }, 
    { 0x0055, 0x0306 }, { 0x0075, 0x0306 }, { 0x0055, 0x030A }, { 0x0075, 0x030A }, 
    { 0x0055, 0x030B }, { 0x0075, 0x030B }, { 0x0055, 0x0328 }, { 0x0075, 0x0328 }, 
    { 0x0057, 0x0302 }, { 0x0077, 0x0302 }, { 0x0059, 0x0302 }, { 0x0079, 0x0302 }, 
    { 0x0059, 0x0308 }, { 0x005A, 0x0301 }, { 0x007A, 0x0301 }, { 0x005A, 0x0307 }, 
    { 0x007A, 0x0307 }, { 0x005A, 0x030C }, { 0x007A, 0x030C }, { 0x0073, 0x0000 }
  };

  const unsigned char Latin_ExtendedA::lb[] = {
    LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AI, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, 
    LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, 
    LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, 
    LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
  };

  const unsigned char Latin_ExtendedA::ea[] = {
    EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bool Latin_ExtendedA::Uppercase[] = {
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 1, 0, 1, 0, 1, 0, 0
    };

    const bool Latin_ExtendedA::Lowercase[] = {
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 0, 1, 0, 1, 0, 1, 1
    };

}; // namespace Babylon
 
dload(Babylon::Latin_ExtendedA);
