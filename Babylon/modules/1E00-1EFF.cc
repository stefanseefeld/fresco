/*$Id: 1E00-1EFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 15 Nov 2000 23:26:02 +0100.
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
 
  class Latin_Extended_Additional : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Latin_Extended_Additional() {
      my_first_letter = 0x1E00;
      my_last_letter  = 0x1EFF;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x1E360304] = 0x1E38;
      composeMap[0x1E370304] = 0x1E39;
      composeMap[0x1E5A0304] = 0x1E5C;
      composeMap[0x1E5B0304] = 0x1E5D;
      composeMap[0x1E620307] = 0x1E68;
      composeMap[0x1E630307] = 0x1E69;
      composeMap[0x1EA00302] = 0x1EAC;
      composeMap[0x1EA00306] = 0x1EB6;
      composeMap[0x1EA10302] = 0x1EAD;
      composeMap[0x1EA10306] = 0x1EB7;
      composeMap[0x1EB80302] = 0x1EC6;
      composeMap[0x1EB90302] = 0x1EC7;
      composeMap[0x1ECC0302] = 0x1ED8;
      composeMap[0x1ECD0302] = 0x1ED9;

    }


    ~Latin_Extended_Additional() {
    }

    _UCS4 firstLetter() {
      return my_first_letter;
    }
 
    _UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const _UCS4 _uc) const {
      return "Latin Extended Additional";
    }

    bool isDefined(const _UCS4 _uc) const {
      return (isdefined[_uc - my_first_letter]);
    }

    _UCS4 uppercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Latin_Extended_Additional::upper[_uc - my_first_letter];
    }

    _UCS4 lowercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Latin_Extended_Additional::lower[_uc - my_first_letter];
    }

    _UCS4 titlecase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Latin_Extended_Additional::title[_uc - my_first_letter];
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
      return Babylon::Gen_Cat(Latin_Extended_Additional::cat[_uc - my_first_letter]);
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
      return Babylon::Char_Decomp(Latin_Extended_Additional::decomp[_uc - my_first_letter]);
    }

    _UTF32String decompose(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::_UTF32String us;
      us.resize(2);
      us[0] = Latin_Extended_Additional::decompStr[_uc - my_first_letter][0];
      us[1] = Latin_Extended_Additional::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(LB_AL);
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
      return 0;
    }

    bool is_Non_spacing(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Hex_Digit(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Alphabetic(const _UCS4 _uc) const {
      return Latin_Extended_Additional::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Extender(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const _UCS4 _uc) const {
      return Latin_Extended_Additional::Identifier_Part[_uc - my_first_letter];
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
      return Latin_Extended_Additional::Uppercase[_uc - my_first_letter];
    }

    bool is_Lowercase(const _UCS4 _uc) const {
      return Latin_Extended_Additional::Lowercase[_uc - my_first_letter];
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
    Latin_Extended_Additional(const Latin_Extended_Additional &) {}
 
    Babylon::_UCS4 my_first_letter;
    Babylon::_UCS4 my_last_letter;
    static const bool isdefined[256];
    static const _UCS4 upper[256];
    static const _UCS4 lower[256];
    static const _UCS4 title[256];
    static const unsigned char cat[256];
    static const unsigned char decomp[256];
    static const _UCS2 decompStr[256][2];
    map<_UCS4, _UCS4> composeMap;
    static const bool Alphabetic[256];
    static const bool Identifier_Part[256];
    static const bool Uppercase[256];
    static const bool Lowercase[256];

  }; // class Latin_Extended_Additional

  const bool Latin_Extended_Additional::isdefined[] = {
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
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0, 
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
    1, 1, 0, 0, 0, 0, 0, 0
  };

  const _UCS4 Latin_Extended_Additional::upper[] = {
    0x1E00, 0x1E00, 0x1E02, 0x1E02, 0x1E04, 0x1E04, 0x1E06, 0x1E06, 
    0x1E08, 0x1E08, 0x1E0A, 0x1E0A, 0x1E0C, 0x1E0C, 0x1E0E, 0x1E0E, 
    0x1E10, 0x1E10, 0x1E12, 0x1E12, 0x1E14, 0x1E14, 0x1E16, 0x1E16, 
    0x1E18, 0x1E18, 0x1E1A, 0x1E1A, 0x1E1C, 0x1E1C, 0x1E1E, 0x1E1E, 
    0x1E20, 0x1E20, 0x1E22, 0x1E22, 0x1E24, 0x1E24, 0x1E26, 0x1E26, 
    0x1E28, 0x1E28, 0x1E2A, 0x1E2A, 0x1E2C, 0x1E2C, 0x1E2E, 0x1E2E, 
    0x1E30, 0x1E30, 0x1E32, 0x1E32, 0x1E34, 0x1E34, 0x1E36, 0x1E36, 
    0x1E38, 0x1E38, 0x1E3A, 0x1E3A, 0x1E3C, 0x1E3C, 0x1E3E, 0x1E3E, 
    0x1E40, 0x1E40, 0x1E42, 0x1E42, 0x1E44, 0x1E44, 0x1E46, 0x1E46, 
    0x1E48, 0x1E48, 0x1E4A, 0x1E4A, 0x1E4C, 0x1E4C, 0x1E4E, 0x1E4E, 
    0x1E50, 0x1E50, 0x1E52, 0x1E52, 0x1E54, 0x1E54, 0x1E56, 0x1E56, 
    0x1E58, 0x1E58, 0x1E5A, 0x1E5A, 0x1E5C, 0x1E5C, 0x1E5E, 0x1E5E, 
    0x1E60, 0x1E60, 0x1E62, 0x1E62, 0x1E64, 0x1E64, 0x1E66, 0x1E66, 
    0x1E68, 0x1E68, 0x1E6A, 0x1E6A, 0x1E6C, 0x1E6C, 0x1E6E, 0x1E6E, 
    0x1E70, 0x1E70, 0x1E72, 0x1E72, 0x1E74, 0x1E74, 0x1E76, 0x1E76, 
    0x1E78, 0x1E78, 0x1E7A, 0x1E7A, 0x1E7C, 0x1E7C, 0x1E7E, 0x1E7E, 
    0x1E80, 0x1E80, 0x1E82, 0x1E82, 0x1E84, 0x1E84, 0x1E86, 0x1E86, 
    0x1E88, 0x1E88, 0x1E8A, 0x1E8A, 0x1E8C, 0x1E8C, 0x1E8E, 0x1E8E, 
    0x1E90, 0x1E90, 0x1E92, 0x1E92, 0x1E94, 0x1E94, 0x1E96, 0x1E97, 
    0x1E98, 0x1E99, 0x1E9A, 0x1E60, 0x1E9C, 0x1E9D, 0x1E9E, 0x1E9F, 
    0x1EA0, 0x1EA0, 0x1EA2, 0x1EA2, 0x1EA4, 0x1EA4, 0x1EA6, 0x1EA6, 
    0x1EA8, 0x1EA8, 0x1EAA, 0x1EAA, 0x1EAC, 0x1EAC, 0x1EAE, 0x1EAE, 
    0x1EB0, 0x1EB0, 0x1EB2, 0x1EB2, 0x1EB4, 0x1EB4, 0x1EB6, 0x1EB6, 
    0x1EB8, 0x1EB8, 0x1EBA, 0x1EBA, 0x1EBC, 0x1EBC, 0x1EBE, 0x1EBE, 
    0x1EC0, 0x1EC0, 0x1EC2, 0x1EC2, 0x1EC4, 0x1EC4, 0x1EC6, 0x1EC6, 
    0x1EC8, 0x1EC8, 0x1ECA, 0x1ECA, 0x1ECC, 0x1ECC, 0x1ECE, 0x1ECE, 
    0x1ED0, 0x1ED0, 0x1ED2, 0x1ED2, 0x1ED4, 0x1ED4, 0x1ED6, 0x1ED6, 
    0x1ED8, 0x1ED8, 0x1EDA, 0x1EDA, 0x1EDC, 0x1EDC, 0x1EDE, 0x1EDE, 
    0x1EE0, 0x1EE0, 0x1EE2, 0x1EE2, 0x1EE4, 0x1EE4, 0x1EE6, 0x1EE6, 
    0x1EE8, 0x1EE8, 0x1EEA, 0x1EEA, 0x1EEC, 0x1EEC, 0x1EEE, 0x1EEE, 
    0x1EF0, 0x1EF0, 0x1EF2, 0x1EF2, 0x1EF4, 0x1EF4, 0x1EF6, 0x1EF6, 
    0x1EF8, 0x1EF8, 0x1EFA, 0x1EFB, 0x1EFC, 0x1EFD, 0x1EFE, 0x1EFF
  };

  const _UCS4 Latin_Extended_Additional::lower[] = {
    0x1E01, 0x1E01, 0x1E03, 0x1E03, 0x1E05, 0x1E05, 0x1E07, 0x1E07, 
    0x1E09, 0x1E09, 0x1E0B, 0x1E0B, 0x1E0D, 0x1E0D, 0x1E0F, 0x1E0F, 
    0x1E11, 0x1E11, 0x1E13, 0x1E13, 0x1E15, 0x1E15, 0x1E17, 0x1E17, 
    0x1E19, 0x1E19, 0x1E1B, 0x1E1B, 0x1E1D, 0x1E1D, 0x1E1F, 0x1E1F, 
    0x1E21, 0x1E21, 0x1E23, 0x1E23, 0x1E25, 0x1E25, 0x1E27, 0x1E27, 
    0x1E29, 0x1E29, 0x1E2B, 0x1E2B, 0x1E2D, 0x1E2D, 0x1E2F, 0x1E2F, 
    0x1E31, 0x1E31, 0x1E33, 0x1E33, 0x1E35, 0x1E35, 0x1E37, 0x1E37, 
    0x1E39, 0x1E39, 0x1E3B, 0x1E3B, 0x1E3D, 0x1E3D, 0x1E3F, 0x1E3F, 
    0x1E41, 0x1E41, 0x1E43, 0x1E43, 0x1E45, 0x1E45, 0x1E47, 0x1E47, 
    0x1E49, 0x1E49, 0x1E4B, 0x1E4B, 0x1E4D, 0x1E4D, 0x1E4F, 0x1E4F, 
    0x1E51, 0x1E51, 0x1E53, 0x1E53, 0x1E55, 0x1E55, 0x1E57, 0x1E57, 
    0x1E59, 0x1E59, 0x1E5B, 0x1E5B, 0x1E5D, 0x1E5D, 0x1E5F, 0x1E5F, 
    0x1E61, 0x1E61, 0x1E63, 0x1E63, 0x1E65, 0x1E65, 0x1E67, 0x1E67, 
    0x1E69, 0x1E69, 0x1E6B, 0x1E6B, 0x1E6D, 0x1E6D, 0x1E6F, 0x1E6F, 
    0x1E71, 0x1E71, 0x1E73, 0x1E73, 0x1E75, 0x1E75, 0x1E77, 0x1E77, 
    0x1E79, 0x1E79, 0x1E7B, 0x1E7B, 0x1E7D, 0x1E7D, 0x1E7F, 0x1E7F, 
    0x1E81, 0x1E81, 0x1E83, 0x1E83, 0x1E85, 0x1E85, 0x1E87, 0x1E87, 
    0x1E89, 0x1E89, 0x1E8B, 0x1E8B, 0x1E8D, 0x1E8D, 0x1E8F, 0x1E8F, 
    0x1E91, 0x1E91, 0x1E93, 0x1E93, 0x1E95, 0x1E95, 0x1E96, 0x1E97, 
    0x1E98, 0x1E99, 0x1E9A, 0x1E9B, 0x1E9C, 0x1E9D, 0x1E9E, 0x1E9F, 
    0x1EA1, 0x1EA1, 0x1EA3, 0x1EA3, 0x1EA5, 0x1EA5, 0x1EA7, 0x1EA7, 
    0x1EA9, 0x1EA9, 0x1EAB, 0x1EAB, 0x1EAD, 0x1EAD, 0x1EAF, 0x1EAF, 
    0x1EB1, 0x1EB1, 0x1EB3, 0x1EB3, 0x1EB5, 0x1EB5, 0x1EB7, 0x1EB7, 
    0x1EB9, 0x1EB9, 0x1EBB, 0x1EBB, 0x1EBD, 0x1EBD, 0x1EBF, 0x1EBF, 
    0x1EC1, 0x1EC1, 0x1EC3, 0x1EC3, 0x1EC5, 0x1EC5, 0x1EC7, 0x1EC7, 
    0x1EC9, 0x1EC9, 0x1ECB, 0x1ECB, 0x1ECD, 0x1ECD, 0x1ECF, 0x1ECF, 
    0x1ED1, 0x1ED1, 0x1ED3, 0x1ED3, 0x1ED5, 0x1ED5, 0x1ED7, 0x1ED7, 
    0x1ED9, 0x1ED9, 0x1EDB, 0x1EDB, 0x1EDD, 0x1EDD, 0x1EDF, 0x1EDF, 
    0x1EE1, 0x1EE1, 0x1EE3, 0x1EE3, 0x1EE5, 0x1EE5, 0x1EE7, 0x1EE7, 
    0x1EE9, 0x1EE9, 0x1EEB, 0x1EEB, 0x1EED, 0x1EED, 0x1EEF, 0x1EEF, 
    0x1EF1, 0x1EF1, 0x1EF3, 0x1EF3, 0x1EF5, 0x1EF5, 0x1EF7, 0x1EF7, 
    0x1EF9, 0x1EF9, 0x1EFA, 0x1EFB, 0x1EFC, 0x1EFD, 0x1EFE, 0x1EFF
  };

  const _UCS4 Latin_Extended_Additional::title[] = {
    0x1E00, 0x1E00, 0x1E02, 0x1E02, 0x1E04, 0x1E04, 0x1E06, 0x1E06, 
    0x1E08, 0x1E08, 0x1E0A, 0x1E0A, 0x1E0C, 0x1E0C, 0x1E0E, 0x1E0E, 
    0x1E10, 0x1E10, 0x1E12, 0x1E12, 0x1E14, 0x1E14, 0x1E16, 0x1E16, 
    0x1E18, 0x1E18, 0x1E1A, 0x1E1A, 0x1E1C, 0x1E1C, 0x1E1E, 0x1E1E, 
    0x1E20, 0x1E20, 0x1E22, 0x1E22, 0x1E24, 0x1E24, 0x1E26, 0x1E26, 
    0x1E28, 0x1E28, 0x1E2A, 0x1E2A, 0x1E2C, 0x1E2C, 0x1E2E, 0x1E2E, 
    0x1E30, 0x1E30, 0x1E32, 0x1E32, 0x1E34, 0x1E34, 0x1E36, 0x1E36, 
    0x1E38, 0x1E38, 0x1E3A, 0x1E3A, 0x1E3C, 0x1E3C, 0x1E3E, 0x1E3E, 
    0x1E40, 0x1E40, 0x1E42, 0x1E42, 0x1E44, 0x1E44, 0x1E46, 0x1E46, 
    0x1E48, 0x1E48, 0x1E4A, 0x1E4A, 0x1E4C, 0x1E4C, 0x1E4E, 0x1E4E, 
    0x1E50, 0x1E50, 0x1E52, 0x1E52, 0x1E54, 0x1E54, 0x1E56, 0x1E56, 
    0x1E58, 0x1E58, 0x1E5A, 0x1E5A, 0x1E5C, 0x1E5C, 0x1E5E, 0x1E5E, 
    0x1E60, 0x1E60, 0x1E62, 0x1E62, 0x1E64, 0x1E64, 0x1E66, 0x1E66, 
    0x1E68, 0x1E68, 0x1E6A, 0x1E6A, 0x1E6C, 0x1E6C, 0x1E6E, 0x1E6E, 
    0x1E70, 0x1E70, 0x1E72, 0x1E72, 0x1E74, 0x1E74, 0x1E76, 0x1E76, 
    0x1E78, 0x1E78, 0x1E7A, 0x1E7A, 0x1E7C, 0x1E7C, 0x1E7E, 0x1E7E, 
    0x1E80, 0x1E80, 0x1E82, 0x1E82, 0x1E84, 0x1E84, 0x1E86, 0x1E86, 
    0x1E88, 0x1E88, 0x1E8A, 0x1E8A, 0x1E8C, 0x1E8C, 0x1E8E, 0x1E8E, 
    0x1E90, 0x1E90, 0x1E92, 0x1E92, 0x1E94, 0x1E94, 0x1E96, 0x1E97, 
    0x1E98, 0x1E99, 0x1E9A, 0x1E60, 0x1E9C, 0x1E9D, 0x1E9E, 0x1E9F, 
    0x1EA0, 0x1EA0, 0x1EA2, 0x1EA2, 0x1EA4, 0x1EA4, 0x1EA6, 0x1EA6, 
    0x1EA8, 0x1EA8, 0x1EAA, 0x1EAA, 0x1EAC, 0x1EAC, 0x1EAE, 0x1EAE, 
    0x1EB0, 0x1EB0, 0x1EB2, 0x1EB2, 0x1EB4, 0x1EB4, 0x1EB6, 0x1EB6, 
    0x1EB8, 0x1EB8, 0x1EBA, 0x1EBA, 0x1EBC, 0x1EBC, 0x1EBE, 0x1EBE, 
    0x1EC0, 0x1EC0, 0x1EC2, 0x1EC2, 0x1EC4, 0x1EC4, 0x1EC6, 0x1EC6, 
    0x1EC8, 0x1EC8, 0x1ECA, 0x1ECA, 0x1ECC, 0x1ECC, 0x1ECE, 0x1ECE, 
    0x1ED0, 0x1ED0, 0x1ED2, 0x1ED2, 0x1ED4, 0x1ED4, 0x1ED6, 0x1ED6, 
    0x1ED8, 0x1ED8, 0x1EDA, 0x1EDA, 0x1EDC, 0x1EDC, 0x1EDE, 0x1EDE, 
    0x1EE0, 0x1EE0, 0x1EE2, 0x1EE2, 0x1EE4, 0x1EE4, 0x1EE6, 0x1EE6, 
    0x1EE8, 0x1EE8, 0x1EEA, 0x1EEA, 0x1EEC, 0x1EEC, 0x1EEE, 0x1EEE, 
    0x1EF0, 0x1EF0, 0x1EF2, 0x1EF2, 0x1EF4, 0x1EF4, 0x1EF6, 0x1EF6, 
    0x1EF8, 0x1EF8, 0x1EFA, 0x1EFB, 0x1EFC, 0x1EFD, 0x1EFE, 0x1EFF
  };

  const unsigned char Latin_Extended_Additional::cat[] = {
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu
  };

  const unsigned char Latin_Extended_Additional::decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const _UCS2 Latin_Extended_Additional::decompStr[][2] = {
    { 0x0041, 0x0325 }, { 0x0061, 0x0325 }, { 0x0042, 0x0307 }, { 0x0062, 0x0307 }, 
    { 0x0042, 0x0323 }, { 0x0062, 0x0323 }, { 0x0042, 0x0331 }, { 0x0062, 0x0331 }, 
    { 0x00C7, 0x0301 }, { 0x00E7, 0x0301 }, { 0x0044, 0x0307 }, { 0x0064, 0x0307 }, 
    { 0x0044, 0x0323 }, { 0x0064, 0x0323 }, { 0x0044, 0x0331 }, { 0x0064, 0x0331 }, 
    { 0x0044, 0x0327 }, { 0x0064, 0x0327 }, { 0x0044, 0x032D }, { 0x0064, 0x032D }, 
    { 0x0112, 0x0300 }, { 0x0113, 0x0300 }, { 0x0112, 0x0301 }, { 0x0113, 0x0301 }, 
    { 0x0045, 0x032D }, { 0x0065, 0x032D }, { 0x0045, 0x0330 }, { 0x0065, 0x0330 }, 
    { 0x0228, 0x0306 }, { 0x0229, 0x0306 }, { 0x0046, 0x0307 }, { 0x0066, 0x0307 }, 
    { 0x0047, 0x0304 }, { 0x0067, 0x0304 }, { 0x0048, 0x0307 }, { 0x0068, 0x0307 }, 
    { 0x0048, 0x0323 }, { 0x0068, 0x0323 }, { 0x0048, 0x0308 }, { 0x0068, 0x0308 }, 
    { 0x0048, 0x0327 }, { 0x0068, 0x0327 }, { 0x0048, 0x032E }, { 0x0068, 0x032E }, 
    { 0x0049, 0x0330 }, { 0x0069, 0x0330 }, { 0x00CF, 0x0301 }, { 0x00EF, 0x0301 }, 
    { 0x004B, 0x0301 }, { 0x006B, 0x0301 }, { 0x004B, 0x0323 }, { 0x006B, 0x0323 }, 
    { 0x004B, 0x0331 }, { 0x006B, 0x0331 }, { 0x004C, 0x0323 }, { 0x006C, 0x0323 }, 
    { 0x1E36, 0x0304 }, { 0x1E37, 0x0304 }, { 0x004C, 0x0331 }, { 0x006C, 0x0331 }, 
    { 0x004C, 0x032D }, { 0x006C, 0x032D }, { 0x004D, 0x0301 }, { 0x006D, 0x0301 }, 
    { 0x004D, 0x0307 }, { 0x006D, 0x0307 }, { 0x004D, 0x0323 }, { 0x006D, 0x0323 }, 
    { 0x004E, 0x0307 }, { 0x006E, 0x0307 }, { 0x004E, 0x0323 }, { 0x006E, 0x0323 }, 
    { 0x004E, 0x0331 }, { 0x006E, 0x0331 }, { 0x004E, 0x032D }, { 0x006E, 0x032D }, 
    { 0x00D5, 0x0301 }, { 0x00F5, 0x0301 }, { 0x00D5, 0x0308 }, { 0x00F5, 0x0308 }, 
    { 0x014C, 0x0300 }, { 0x014D, 0x0300 }, { 0x014C, 0x0301 }, { 0x014D, 0x0301 }, 
    { 0x0050, 0x0301 }, { 0x0070, 0x0301 }, { 0x0050, 0x0307 }, { 0x0070, 0x0307 }, 
    { 0x0052, 0x0307 }, { 0x0072, 0x0307 }, { 0x0052, 0x0323 }, { 0x0072, 0x0323 }, 
    { 0x1E5A, 0x0304 }, { 0x1E5B, 0x0304 }, { 0x0052, 0x0331 }, { 0x0072, 0x0331 }, 
    { 0x0053, 0x0307 }, { 0x0073, 0x0307 }, { 0x0053, 0x0323 }, { 0x0073, 0x0323 }, 
    { 0x015A, 0x0307 }, { 0x015B, 0x0307 }, { 0x0160, 0x0307 }, { 0x0161, 0x0307 }, 
    { 0x1E62, 0x0307 }, { 0x1E63, 0x0307 }, { 0x0054, 0x0307 }, { 0x0074, 0x0307 }, 
    { 0x0054, 0x0323 }, { 0x0074, 0x0323 }, { 0x0054, 0x0331 }, { 0x0074, 0x0331 }, 
    { 0x0054, 0x032D }, { 0x0074, 0x032D }, { 0x0055, 0x0324 }, { 0x0075, 0x0324 }, 
    { 0x0055, 0x0330 }, { 0x0075, 0x0330 }, { 0x0055, 0x032D }, { 0x0075, 0x032D }, 
    { 0x0168, 0x0301 }, { 0x0169, 0x0301 }, { 0x016A, 0x0308 }, { 0x016B, 0x0308 }, 
    { 0x0056, 0x0303 }, { 0x0076, 0x0303 }, { 0x0056, 0x0323 }, { 0x0076, 0x0323 }, 
    { 0x0057, 0x0300 }, { 0x0077, 0x0300 }, { 0x0057, 0x0301 }, { 0x0077, 0x0301 }, 
    { 0x0057, 0x0308 }, { 0x0077, 0x0308 }, { 0x0057, 0x0307 }, { 0x0077, 0x0307 }, 
    { 0x0057, 0x0323 }, { 0x0077, 0x0323 }, { 0x0058, 0x0307 }, { 0x0078, 0x0307 }, 
    { 0x0058, 0x0308 }, { 0x0078, 0x0308 }, { 0x0059, 0x0307 }, { 0x0079, 0x0307 }, 
    { 0x005A, 0x0302 }, { 0x007A, 0x0302 }, { 0x005A, 0x0323 }, { 0x007A, 0x0323 }, 
    { 0x005A, 0x0331 }, { 0x007A, 0x0331 }, { 0x0068, 0x0331 }, { 0x0074, 0x0308 }, 
    { 0x0077, 0x030A }, { 0x0079, 0x030A }, { 0x0061, 0x02BE }, { 0x017F, 0x0307 }, 
    { 0x1E9C, 0x0000 }, { 0x1E9D, 0x0000 }, { 0x1E9E, 0x0000 }, { 0x1E9F, 0x0000 }, 
    { 0x0041, 0x0323 }, { 0x0061, 0x0323 }, { 0x0041, 0x0309 }, { 0x0061, 0x0309 }, 
    { 0x00C2, 0x0301 }, { 0x00E2, 0x0301 }, { 0x00C2, 0x0300 }, { 0x00E2, 0x0300 }, 
    { 0x00C2, 0x0309 }, { 0x00E2, 0x0309 }, { 0x00C2, 0x0303 }, { 0x00E2, 0x0303 }, 
    { 0x1EA0, 0x0302 }, { 0x1EA1, 0x0302 }, { 0x0102, 0x0301 }, { 0x0103, 0x0301 }, 
    { 0x0102, 0x0300 }, { 0x0103, 0x0300 }, { 0x0102, 0x0309 }, { 0x0103, 0x0309 }, 
    { 0x0102, 0x0303 }, { 0x0103, 0x0303 }, { 0x1EA0, 0x0306 }, { 0x1EA1, 0x0306 }, 
    { 0x0045, 0x0323 }, { 0x0065, 0x0323 }, { 0x0045, 0x0309 }, { 0x0065, 0x0309 }, 
    { 0x0045, 0x0303 }, { 0x0065, 0x0303 }, { 0x00CA, 0x0301 }, { 0x00EA, 0x0301 }, 
    { 0x00CA, 0x0300 }, { 0x00EA, 0x0300 }, { 0x00CA, 0x0309 }, { 0x00EA, 0x0309 }, 
    { 0x00CA, 0x0303 }, { 0x00EA, 0x0303 }, { 0x1EB8, 0x0302 }, { 0x1EB9, 0x0302 }, 
    { 0x0049, 0x0309 }, { 0x0069, 0x0309 }, { 0x0049, 0x0323 }, { 0x0069, 0x0323 }, 
    { 0x004F, 0x0323 }, { 0x006F, 0x0323 }, { 0x004F, 0x0309 }, { 0x006F, 0x0309 }, 
    { 0x00D4, 0x0301 }, { 0x00F4, 0x0301 }, { 0x00D4, 0x0300 }, { 0x00F4, 0x0300 }, 
    { 0x00D4, 0x0309 }, { 0x00F4, 0x0309 }, { 0x00D4, 0x0303 }, { 0x00F4, 0x0303 }, 
    { 0x1ECC, 0x0302 }, { 0x1ECD, 0x0302 }, { 0x01A0, 0x0301 }, { 0x01A1, 0x0301 }, 
    { 0x01A0, 0x0300 }, { 0x01A1, 0x0300 }, { 0x01A0, 0x0309 }, { 0x01A1, 0x0309 }, 
    { 0x01A0, 0x0303 }, { 0x01A1, 0x0303 }, { 0x01A0, 0x0323 }, { 0x01A1, 0x0323 }, 
    { 0x0055, 0x0323 }, { 0x0075, 0x0323 }, { 0x0055, 0x0309 }, { 0x0075, 0x0309 }, 
    { 0x01AF, 0x0301 }, { 0x01B0, 0x0301 }, { 0x01AF, 0x0300 }, { 0x01B0, 0x0300 }, 
    { 0x01AF, 0x0309 }, { 0x01B0, 0x0309 }, { 0x01AF, 0x0303 }, { 0x01B0, 0x0303 }, 
    { 0x01AF, 0x0323 }, { 0x01B0, 0x0323 }, { 0x0059, 0x0300 }, { 0x0079, 0x0300 }, 
    { 0x0059, 0x0323 }, { 0x0079, 0x0323 }, { 0x0059, 0x0309 }, { 0x0079, 0x0309 }, 
    { 0x0059, 0x0303 }, { 0x0079, 0x0303 }, { 0x1EFA, 0x0000 }, { 0x1EFB, 0x0000 }, 
    { 0x1EFC, 0x0000 }, { 0x1EFD, 0x0000 }, { 0x1EFE, 0x0000 }, { 0x1EFF, 0x0000 }
  };

    const bool Latin_Extended_Additional::Alphabetic[] = {
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
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
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
        1, 1, 0, 0, 0, 0, 0, 0
    };

    const bool Latin_Extended_Additional::Identifier_Part[] = {
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
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
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
        1, 1, 0, 0, 0, 0, 0, 0
    };

    const bool Latin_Extended_Additional::Uppercase[] = {
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Latin_Extended_Additional::Lowercase[] = {
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Latin_Extended_Additional);
