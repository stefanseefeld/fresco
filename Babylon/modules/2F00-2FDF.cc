/*$Id: 2F00-2FDF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:13:07 +0100.
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
 
  class Kangxi_Radicals2F00 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Kangxi_Radicals2F00() {
      my_first_letter = 0x2F00;
      my_last_letter  = 0x2FDF;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Kangxi_Radicals2F00() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Kangxi Radicals";
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
      return Babylon::Gen_Cat(CAT_So);
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
      return Babylon::Char_Decomp(Kangxi_Radicals2F00::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Kangxi_Radicals2F00::decompStr[_uc - my_first_letter][0];
      us[1] = Kangxi_Radicals2F00::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(LB_ID);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(EA_WIDTH_W);
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
    Kangxi_Radicals2F00(const Kangxi_Radicals2F00 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[224];
    static const unsigned char decomp[224];
    static const UCS2 decompStr[224][2];

  }; // class Kangxi_Radicals2F00

  const bool Kangxi_Radicals2F00::isdefined[] = {
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
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Kangxi_Radicals2F00::decomp[] = {
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Kangxi_Radicals2F00::decompStr[][2] = {
    { 0x4E00, 0x0000 }, { 0x4E28, 0x0000 }, { 0x4E36, 0x0000 }, { 0x4E3F, 0x0000 }, 
    { 0x4E59, 0x0000 }, { 0x4E85, 0x0000 }, { 0x4E8C, 0x0000 }, { 0x4EA0, 0x0000 }, 
    { 0x4EBA, 0x0000 }, { 0x513F, 0x0000 }, { 0x5165, 0x0000 }, { 0x516B, 0x0000 }, 
    { 0x5182, 0x0000 }, { 0x5196, 0x0000 }, { 0x51AB, 0x0000 }, { 0x51E0, 0x0000 }, 
    { 0x51F5, 0x0000 }, { 0x5200, 0x0000 }, { 0x529B, 0x0000 }, { 0x52F9, 0x0000 }, 
    { 0x5315, 0x0000 }, { 0x531A, 0x0000 }, { 0x5338, 0x0000 }, { 0x5341, 0x0000 }, 
    { 0x535C, 0x0000 }, { 0x5369, 0x0000 }, { 0x5382, 0x0000 }, { 0x53B6, 0x0000 }, 
    { 0x53C8, 0x0000 }, { 0x53E3, 0x0000 }, { 0x56D7, 0x0000 }, { 0x571F, 0x0000 }, 
    { 0x58EB, 0x0000 }, { 0x5902, 0x0000 }, { 0x590A, 0x0000 }, { 0x5915, 0x0000 }, 
    { 0x5927, 0x0000 }, { 0x5973, 0x0000 }, { 0x5B50, 0x0000 }, { 0x5B80, 0x0000 }, 
    { 0x5BF8, 0x0000 }, { 0x5C0F, 0x0000 }, { 0x5C22, 0x0000 }, { 0x5C38, 0x0000 }, 
    { 0x5C6E, 0x0000 }, { 0x5C71, 0x0000 }, { 0x5DDB, 0x0000 }, { 0x5DE5, 0x0000 }, 
    { 0x5DF1, 0x0000 }, { 0x5DFE, 0x0000 }, { 0x5E72, 0x0000 }, { 0x5E7A, 0x0000 }, 
    { 0x5E7F, 0x0000 }, { 0x5EF4, 0x0000 }, { 0x5EFE, 0x0000 }, { 0x5F0B, 0x0000 }, 
    { 0x5F13, 0x0000 }, { 0x5F50, 0x0000 }, { 0x5F61, 0x0000 }, { 0x5F73, 0x0000 }, 
    { 0x5FC3, 0x0000 }, { 0x6208, 0x0000 }, { 0x6236, 0x0000 }, { 0x624B, 0x0000 }, 
    { 0x652F, 0x0000 }, { 0x6534, 0x0000 }, { 0x6587, 0x0000 }, { 0x6597, 0x0000 }, 
    { 0x65A4, 0x0000 }, { 0x65B9, 0x0000 }, { 0x65E0, 0x0000 }, { 0x65E5, 0x0000 }, 
    { 0x66F0, 0x0000 }, { 0x6708, 0x0000 }, { 0x6728, 0x0000 }, { 0x6B20, 0x0000 }, 
    { 0x6B62, 0x0000 }, { 0x6B79, 0x0000 }, { 0x6BB3, 0x0000 }, { 0x6BCB, 0x0000 }, 
    { 0x6BD4, 0x0000 }, { 0x6BDB, 0x0000 }, { 0x6C0F, 0x0000 }, { 0x6C14, 0x0000 }, 
    { 0x6C34, 0x0000 }, { 0x706B, 0x0000 }, { 0x722A, 0x0000 }, { 0x7236, 0x0000 }, 
    { 0x723B, 0x0000 }, { 0x723F, 0x0000 }, { 0x7247, 0x0000 }, { 0x7259, 0x0000 }, 
    { 0x725B, 0x0000 }, { 0x72AC, 0x0000 }, { 0x7384, 0x0000 }, { 0x7389, 0x0000 }, 
    { 0x74DC, 0x0000 }, { 0x74E6, 0x0000 }, { 0x7518, 0x0000 }, { 0x751F, 0x0000 }, 
    { 0x7528, 0x0000 }, { 0x7530, 0x0000 }, { 0x758B, 0x0000 }, { 0x7592, 0x0000 }, 
    { 0x7676, 0x0000 }, { 0x767D, 0x0000 }, { 0x76AE, 0x0000 }, { 0x76BF, 0x0000 }, 
    { 0x76EE, 0x0000 }, { 0x77DB, 0x0000 }, { 0x77E2, 0x0000 }, { 0x77F3, 0x0000 }, 
    { 0x793A, 0x0000 }, { 0x79B8, 0x0000 }, { 0x79BE, 0x0000 }, { 0x7A74, 0x0000 }, 
    { 0x7ACB, 0x0000 }, { 0x7AF9, 0x0000 }, { 0x7C73, 0x0000 }, { 0x7CF8, 0x0000 }, 
    { 0x7F36, 0x0000 }, { 0x7F51, 0x0000 }, { 0x7F8A, 0x0000 }, { 0x7FBD, 0x0000 }, 
    { 0x8001, 0x0000 }, { 0x800C, 0x0000 }, { 0x8012, 0x0000 }, { 0x8033, 0x0000 }, 
    { 0x807F, 0x0000 }, { 0x8089, 0x0000 }, { 0x81E3, 0x0000 }, { 0x81EA, 0x0000 }, 
    { 0x81F3, 0x0000 }, { 0x81FC, 0x0000 }, { 0x820C, 0x0000 }, { 0x821B, 0x0000 }, 
    { 0x821F, 0x0000 }, { 0x826E, 0x0000 }, { 0x8272, 0x0000 }, { 0x8278, 0x0000 }, 
    { 0x864D, 0x0000 }, { 0x866B, 0x0000 }, { 0x8840, 0x0000 }, { 0x884C, 0x0000 }, 
    { 0x8863, 0x0000 }, { 0x897E, 0x0000 }, { 0x898B, 0x0000 }, { 0x89D2, 0x0000 }, 
    { 0x8A00, 0x0000 }, { 0x8C37, 0x0000 }, { 0x8C46, 0x0000 }, { 0x8C55, 0x0000 }, 
    { 0x8C78, 0x0000 }, { 0x8C9D, 0x0000 }, { 0x8D64, 0x0000 }, { 0x8D70, 0x0000 }, 
    { 0x8DB3, 0x0000 }, { 0x8EAB, 0x0000 }, { 0x8ECA, 0x0000 }, { 0x8F9B, 0x0000 }, 
    { 0x8FB0, 0x0000 }, { 0x8FB5, 0x0000 }, { 0x9091, 0x0000 }, { 0x9149, 0x0000 }, 
    { 0x91C6, 0x0000 }, { 0x91CC, 0x0000 }, { 0x91D1, 0x0000 }, { 0x9577, 0x0000 }, 
    { 0x9580, 0x0000 }, { 0x961C, 0x0000 }, { 0x96B6, 0x0000 }, { 0x96B9, 0x0000 }, 
    { 0x96E8, 0x0000 }, { 0x9751, 0x0000 }, { 0x975E, 0x0000 }, { 0x9762, 0x0000 }, 
    { 0x9769, 0x0000 }, { 0x97CB, 0x0000 }, { 0x97ED, 0x0000 }, { 0x97F3, 0x0000 }, 
    { 0x9801, 0x0000 }, { 0x98A8, 0x0000 }, { 0x98DB, 0x0000 }, { 0x98DF, 0x0000 }, 
    { 0x9996, 0x0000 }, { 0x9999, 0x0000 }, { 0x99AC, 0x0000 }, { 0x9AA8, 0x0000 }, 
    { 0x9AD8, 0x0000 }, { 0x9ADF, 0x0000 }, { 0x9B25, 0x0000 }, { 0x9B2F, 0x0000 }, 
    { 0x9B32, 0x0000 }, { 0x9B3C, 0x0000 }, { 0x9B5A, 0x0000 }, { 0x9CE5, 0x0000 }, 
    { 0x9E75, 0x0000 }, { 0x9E7F, 0x0000 }, { 0x9EA5, 0x0000 }, { 0x9EBB, 0x0000 }, 
    { 0x9EC3, 0x0000 }, { 0x9ECD, 0x0000 }, { 0x9ED1, 0x0000 }, { 0x9EF9, 0x0000 }, 
    { 0x9EFD, 0x0000 }, { 0x9F0E, 0x0000 }, { 0x9F13, 0x0000 }, { 0x9F20, 0x0000 }, 
    { 0x9F3B, 0x0000 }, { 0x9F4A, 0x0000 }, { 0x9F52, 0x0000 }, { 0x9F8D, 0x0000 }, 
    { 0x9F9C, 0x0000 }, { 0x9FA0, 0x0000 }, { 0x2FD6, 0x0000 }, { 0x2FD7, 0x0000 }, 
    { 0x2FD8, 0x0000 }, { 0x2FD9, 0x0000 }, { 0x2FDA, 0x0000 }, { 0x2FDB, 0x0000 }, 
    { 0x2FDC, 0x0000 }, { 0x2FDD, 0x0000 }, { 0x2FDE, 0x0000 }, { 0x2FDF, 0x0000 }
  };

}; // namespace Babylon
 
dload(Babylon::Kangxi_Radicals2F00);
