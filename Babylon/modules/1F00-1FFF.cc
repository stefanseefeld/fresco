/*$Id: 1F00-1FFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 15 Nov 2000 23:26:13 +0100.
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
 
  class Greek_Extended : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Greek_Extended() {
      my_first_letter = 0x1F00;
      my_last_letter  = 0x1FFF;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x1F000300] = 0x1F02;
      composeMap[0x1F000301] = 0x1F04;
      composeMap[0x1F000342] = 0x1F06;
      composeMap[0x1F000345] = 0x1F80;
      composeMap[0x1F010300] = 0x1F03;
      composeMap[0x1F010301] = 0x1F05;
      composeMap[0x1F010342] = 0x1F07;
      composeMap[0x1F010345] = 0x1F81;
      composeMap[0x1F020345] = 0x1F82;
      composeMap[0x1F030345] = 0x1F83;
      composeMap[0x1F040345] = 0x1F84;
      composeMap[0x1F050345] = 0x1F85;
      composeMap[0x1F060345] = 0x1F86;
      composeMap[0x1F070345] = 0x1F87;
      composeMap[0x1F080300] = 0x1F0A;
      composeMap[0x1F080301] = 0x1F0C;
      composeMap[0x1F080342] = 0x1F0E;
      composeMap[0x1F080345] = 0x1F88;
      composeMap[0x1F090300] = 0x1F0B;
      composeMap[0x1F090301] = 0x1F0D;
      composeMap[0x1F090342] = 0x1F0F;
      composeMap[0x1F090345] = 0x1F89;
      composeMap[0x1F0A0345] = 0x1F8A;
      composeMap[0x1F0B0345] = 0x1F8B;
      composeMap[0x1F0C0345] = 0x1F8C;
      composeMap[0x1F0D0345] = 0x1F8D;
      composeMap[0x1F0E0345] = 0x1F8E;
      composeMap[0x1F0F0345] = 0x1F8F;
      composeMap[0x1F100300] = 0x1F12;
      composeMap[0x1F100301] = 0x1F14;
      composeMap[0x1F110300] = 0x1F13;
      composeMap[0x1F110301] = 0x1F15;
      composeMap[0x1F180300] = 0x1F1A;
      composeMap[0x1F180301] = 0x1F1C;
      composeMap[0x1F190300] = 0x1F1B;
      composeMap[0x1F190301] = 0x1F1D;
      composeMap[0x1F200300] = 0x1F22;
      composeMap[0x1F200301] = 0x1F24;
      composeMap[0x1F200342] = 0x1F26;
      composeMap[0x1F200345] = 0x1F90;
      composeMap[0x1F210300] = 0x1F23;
      composeMap[0x1F210301] = 0x1F25;
      composeMap[0x1F210342] = 0x1F27;
      composeMap[0x1F210345] = 0x1F91;
      composeMap[0x1F220345] = 0x1F92;
      composeMap[0x1F230345] = 0x1F93;
      composeMap[0x1F240345] = 0x1F94;
      composeMap[0x1F250345] = 0x1F95;
      composeMap[0x1F260345] = 0x1F96;
      composeMap[0x1F270345] = 0x1F97;
      composeMap[0x1F280300] = 0x1F2A;
      composeMap[0x1F280301] = 0x1F2C;
      composeMap[0x1F280342] = 0x1F2E;
      composeMap[0x1F280345] = 0x1F98;
      composeMap[0x1F290300] = 0x1F2B;
      composeMap[0x1F290301] = 0x1F2D;
      composeMap[0x1F290342] = 0x1F2F;
      composeMap[0x1F290345] = 0x1F99;
      composeMap[0x1F2A0345] = 0x1F9A;
      composeMap[0x1F2B0345] = 0x1F9B;
      composeMap[0x1F2C0345] = 0x1F9C;
      composeMap[0x1F2D0345] = 0x1F9D;
      composeMap[0x1F2E0345] = 0x1F9E;
      composeMap[0x1F2F0345] = 0x1F9F;
      composeMap[0x1F300300] = 0x1F32;
      composeMap[0x1F300301] = 0x1F34;
      composeMap[0x1F300342] = 0x1F36;
      composeMap[0x1F310300] = 0x1F33;
      composeMap[0x1F310301] = 0x1F35;
      composeMap[0x1F310342] = 0x1F37;
      composeMap[0x1F380300] = 0x1F3A;
      composeMap[0x1F380301] = 0x1F3C;
      composeMap[0x1F380342] = 0x1F3E;
      composeMap[0x1F390300] = 0x1F3B;
      composeMap[0x1F390301] = 0x1F3D;
      composeMap[0x1F390342] = 0x1F3F;
      composeMap[0x1F400300] = 0x1F42;
      composeMap[0x1F400301] = 0x1F44;
      composeMap[0x1F410300] = 0x1F43;
      composeMap[0x1F410301] = 0x1F45;
      composeMap[0x1F480300] = 0x1F4A;
      composeMap[0x1F480301] = 0x1F4C;
      composeMap[0x1F490300] = 0x1F4B;
      composeMap[0x1F490301] = 0x1F4D;
      composeMap[0x1F500300] = 0x1F52;
      composeMap[0x1F500301] = 0x1F54;
      composeMap[0x1F500342] = 0x1F56;
      composeMap[0x1F510300] = 0x1F53;
      composeMap[0x1F510301] = 0x1F55;
      composeMap[0x1F510342] = 0x1F57;
      composeMap[0x1F590300] = 0x1F5B;
      composeMap[0x1F590301] = 0x1F5D;
      composeMap[0x1F590342] = 0x1F5F;
      composeMap[0x1F600300] = 0x1F62;
      composeMap[0x1F600301] = 0x1F64;
      composeMap[0x1F600342] = 0x1F66;
      composeMap[0x1F600345] = 0x1FA0;
      composeMap[0x1F610300] = 0x1F63;
      composeMap[0x1F610301] = 0x1F65;
      composeMap[0x1F610342] = 0x1F67;
      composeMap[0x1F610345] = 0x1FA1;
      composeMap[0x1F620345] = 0x1FA2;
      composeMap[0x1F630345] = 0x1FA3;
      composeMap[0x1F640345] = 0x1FA4;
      composeMap[0x1F650345] = 0x1FA5;
      composeMap[0x1F660345] = 0x1FA6;
      composeMap[0x1F670345] = 0x1FA7;
      composeMap[0x1F680300] = 0x1F6A;
      composeMap[0x1F680301] = 0x1F6C;
      composeMap[0x1F680342] = 0x1F6E;
      composeMap[0x1F680345] = 0x1FA8;
      composeMap[0x1F690300] = 0x1F6B;
      composeMap[0x1F690301] = 0x1F6D;
      composeMap[0x1F690342] = 0x1F6F;
      composeMap[0x1F690345] = 0x1FA9;
      composeMap[0x1F6A0345] = 0x1FAA;
      composeMap[0x1F6B0345] = 0x1FAB;
      composeMap[0x1F6C0345] = 0x1FAC;
      composeMap[0x1F6D0345] = 0x1FAD;
      composeMap[0x1F6E0345] = 0x1FAE;
      composeMap[0x1F6F0345] = 0x1FAF;
      composeMap[0x1F700345] = 0x1FB2;
      composeMap[0x1F740345] = 0x1FC2;
      composeMap[0x1F7C0345] = 0x1FF2;
      composeMap[0x1FB60345] = 0x1FB7;
      composeMap[0x1FBF0300] = 0x1FCD;
      composeMap[0x1FBF0301] = 0x1FCE;
      composeMap[0x1FBF0342] = 0x1FCF;
      composeMap[0x1FC60345] = 0x1FC7;
      composeMap[0x1FF60345] = 0x1FF7;
      composeMap[0x1FFE0300] = 0x1FDD;
      composeMap[0x1FFE0301] = 0x1FDE;
      composeMap[0x1FFE0342] = 0x1FDF;

    }


    ~Greek_Extended() {
    }

    _UCS4 firstLetter() {
      return my_first_letter;
    }
 
    _UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const _UCS4 _uc) const {
      return "Greek Extended";
    }

    bool isDefined(const _UCS4 _uc) const {
      return (isdefined[_uc - my_first_letter]);
    }

    _UCS4 uppercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Greek_Extended::upper[_uc - my_first_letter];
    }

    _UCS4 lowercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Greek_Extended::lower[_uc - my_first_letter];
    }

    _UCS4 titlecase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Greek_Extended::title[_uc - my_first_letter];
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
      return Babylon::Gen_Cat(Greek_Extended::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Greek_Extended::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Greek_Extended::decomp[_uc - my_first_letter]);
    }

    _UTF32String decompose(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::_UTF32String us;
      us.resize(2);
      us[0] = Greek_Extended::decompStr[_uc - my_first_letter][0];
      us[1] = Greek_Extended::decompStr[_uc - my_first_letter][1];
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
      return Greek_Extended::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const _UCS4 _uc) const {
      return Greek_Extended::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const _UCS4 _uc) const {
      return Greek_Extended::Identifier_Part[_uc - my_first_letter];
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
      return Greek_Extended::Uppercase[_uc - my_first_letter];
    }

    bool is_Lowercase(const _UCS4 _uc) const {
      return Greek_Extended::Lowercase[_uc - my_first_letter];
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
    Greek_Extended(const Greek_Extended &) {}
 
    Babylon::_UCS4 my_first_letter;
    Babylon::_UCS4 my_last_letter;
    static const bool isdefined[256];
    static const _UCS4 upper[256];
    static const _UCS4 lower[256];
    static const _UCS4 title[256];
    static const unsigned char cat[256];
    static const unsigned char bidir[256];
    static const unsigned char decomp[256];
    static const _UCS2 decompStr[256][2];
    map<_UCS4, _UCS4> composeMap;
    static const bool Alphabetic[256];
    static const bool Diacritic[256];
    static const bool Identifier_Part[256];
    static const bool Uppercase[256];
    static const bool Lowercase[256];

  }; // class Greek_Extended

  const bool Greek_Extended::isdefined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    0, 1, 0, 1, 0, 1, 0, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 1, 1, 
    1, 1, 1, 1, 0, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 1, 1, 1, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0
  };

  const _UCS4 Greek_Extended::upper[] = {
    0x1F08, 0x1F09, 0x1F0A, 0x1F0B, 0x1F0C, 0x1F0D, 0x1F0E, 0x1F0F, 
    0x1F08, 0x1F09, 0x1F0A, 0x1F0B, 0x1F0C, 0x1F0D, 0x1F0E, 0x1F0F, 
    0x1F18, 0x1F19, 0x1F1A, 0x1F1B, 0x1F1C, 0x1F1D, 0x1F16, 0x1F17, 
    0x1F18, 0x1F19, 0x1F1A, 0x1F1B, 0x1F1C, 0x1F1D, 0x1F1E, 0x1F1F, 
    0x1F28, 0x1F29, 0x1F2A, 0x1F2B, 0x1F2C, 0x1F2D, 0x1F2E, 0x1F2F, 
    0x1F28, 0x1F29, 0x1F2A, 0x1F2B, 0x1F2C, 0x1F2D, 0x1F2E, 0x1F2F, 
    0x1F38, 0x1F39, 0x1F3A, 0x1F3B, 0x1F3C, 0x1F3D, 0x1F3E, 0x1F3F, 
    0x1F38, 0x1F39, 0x1F3A, 0x1F3B, 0x1F3C, 0x1F3D, 0x1F3E, 0x1F3F, 
    0x1F48, 0x1F49, 0x1F4A, 0x1F4B, 0x1F4C, 0x1F4D, 0x1F46, 0x1F47, 
    0x1F48, 0x1F49, 0x1F4A, 0x1F4B, 0x1F4C, 0x1F4D, 0x1F4E, 0x1F4F, 
    0x1F50, 0x1F59, 0x1F52, 0x1F5B, 0x1F54, 0x1F5D, 0x1F56, 0x1F5F, 
    0x1F58, 0x1F59, 0x1F5A, 0x1F5B, 0x1F5C, 0x1F5D, 0x1F5E, 0x1F5F, 
    0x1F68, 0x1F69, 0x1F6A, 0x1F6B, 0x1F6C, 0x1F6D, 0x1F6E, 0x1F6F, 
    0x1F68, 0x1F69, 0x1F6A, 0x1F6B, 0x1F6C, 0x1F6D, 0x1F6E, 0x1F6F, 
    0x1FBA, 0x1FBB, 0x1FC8, 0x1FC9, 0x1FCA, 0x1FCB, 0x1FDA, 0x1FDB, 
    0x1FF8, 0x1FF9, 0x1FEA, 0x1FEB, 0x1FFA, 0x1FFB, 0x1F7E, 0x1F7F, 
    0x1F88, 0x1F89, 0x1F8A, 0x1F8B, 0x1F8C, 0x1F8D, 0x1F8E, 0x1F8F, 
    0x1F88, 0x1F89, 0x1F8A, 0x1F8B, 0x1F8C, 0x1F8D, 0x1F8E, 0x1F8F, 
    0x1F98, 0x1F99, 0x1F9A, 0x1F9B, 0x1F9C, 0x1F9D, 0x1F9E, 0x1F9F, 
    0x1F98, 0x1F99, 0x1F9A, 0x1F9B, 0x1F9C, 0x1F9D, 0x1F9E, 0x1F9F, 
    0x1FA8, 0x1FA9, 0x1FAA, 0x1FAB, 0x1FAC, 0x1FAD, 0x1FAE, 0x1FAF, 
    0x1FA8, 0x1FA9, 0x1FAA, 0x1FAB, 0x1FAC, 0x1FAD, 0x1FAE, 0x1FAF, 
    0x1FB8, 0x1FB9, 0x1FB2, 0x1FBC, 0x1FB4, 0x1FB5, 0x1FB6, 0x1FB7, 
    0x1FB8, 0x1FB9, 0x1FBA, 0x1FBB, 0x1FBC, 0x1FBD, 0x0399, 0x1FBF, 
    0x1FC0, 0x1FC1, 0x1FC2, 0x1FCC, 0x1FC4, 0x1FC5, 0x1FC6, 0x1FC7, 
    0x1FC8, 0x1FC9, 0x1FCA, 0x1FCB, 0x1FCC, 0x1FCD, 0x1FCE, 0x1FCF, 
    0x1FD8, 0x1FD9, 0x1FD2, 0x1FD3, 0x1FD4, 0x1FD5, 0x1FD6, 0x1FD7, 
    0x1FD8, 0x1FD9, 0x1FDA, 0x1FDB, 0x1FDC, 0x1FDD, 0x1FDE, 0x1FDF, 
    0x1FE8, 0x1FE9, 0x1FE2, 0x1FE3, 0x1FE4, 0x1FEC, 0x1FE6, 0x1FE7, 
    0x1FE8, 0x1FE9, 0x1FEA, 0x1FEB, 0x1FEC, 0x1FED, 0x1FEE, 0x1FEF, 
    0x1FF0, 0x1FF1, 0x1FF2, 0x1FFC, 0x1FF4, 0x1FF5, 0x1FF6, 0x1FF7, 
    0x1FF8, 0x1FF9, 0x1FFA, 0x1FFB, 0x1FFC, 0x1FFD, 0x1FFE, 0x1FFF
  };

  const _UCS4 Greek_Extended::lower[] = {
    0x1F00, 0x1F01, 0x1F02, 0x1F03, 0x1F04, 0x1F05, 0x1F06, 0x1F07, 
    0x1F00, 0x1F01, 0x1F02, 0x1F03, 0x1F04, 0x1F05, 0x1F06, 0x1F07, 
    0x1F10, 0x1F11, 0x1F12, 0x1F13, 0x1F14, 0x1F15, 0x1F16, 0x1F17, 
    0x1F10, 0x1F11, 0x1F12, 0x1F13, 0x1F14, 0x1F15, 0x1F1E, 0x1F1F, 
    0x1F20, 0x1F21, 0x1F22, 0x1F23, 0x1F24, 0x1F25, 0x1F26, 0x1F27, 
    0x1F20, 0x1F21, 0x1F22, 0x1F23, 0x1F24, 0x1F25, 0x1F26, 0x1F27, 
    0x1F30, 0x1F31, 0x1F32, 0x1F33, 0x1F34, 0x1F35, 0x1F36, 0x1F37, 
    0x1F30, 0x1F31, 0x1F32, 0x1F33, 0x1F34, 0x1F35, 0x1F36, 0x1F37, 
    0x1F40, 0x1F41, 0x1F42, 0x1F43, 0x1F44, 0x1F45, 0x1F46, 0x1F47, 
    0x1F40, 0x1F41, 0x1F42, 0x1F43, 0x1F44, 0x1F45, 0x1F4E, 0x1F4F, 
    0x1F50, 0x1F51, 0x1F52, 0x1F53, 0x1F54, 0x1F55, 0x1F56, 0x1F57, 
    0x1F58, 0x1F51, 0x1F5A, 0x1F53, 0x1F5C, 0x1F55, 0x1F5E, 0x1F57, 
    0x1F60, 0x1F61, 0x1F62, 0x1F63, 0x1F64, 0x1F65, 0x1F66, 0x1F67, 
    0x1F60, 0x1F61, 0x1F62, 0x1F63, 0x1F64, 0x1F65, 0x1F66, 0x1F67, 
    0x1F70, 0x1F71, 0x1F72, 0x1F73, 0x1F74, 0x1F75, 0x1F76, 0x1F77, 
    0x1F78, 0x1F79, 0x1F7A, 0x1F7B, 0x1F7C, 0x1F7D, 0x1F7E, 0x1F7F, 
    0x1F80, 0x1F81, 0x1F82, 0x1F83, 0x1F84, 0x1F85, 0x1F86, 0x1F87, 
    0x1F80, 0x1F81, 0x1F82, 0x1F83, 0x1F84, 0x1F85, 0x1F86, 0x1F87, 
    0x1F90, 0x1F91, 0x1F92, 0x1F93, 0x1F94, 0x1F95, 0x1F96, 0x1F97, 
    0x1F90, 0x1F91, 0x1F92, 0x1F93, 0x1F94, 0x1F95, 0x1F96, 0x1F97, 
    0x1FA0, 0x1FA1, 0x1FA2, 0x1FA3, 0x1FA4, 0x1FA5, 0x1FA6, 0x1FA7, 
    0x1FA0, 0x1FA1, 0x1FA2, 0x1FA3, 0x1FA4, 0x1FA5, 0x1FA6, 0x1FA7, 
    0x1FB0, 0x1FB1, 0x1FB2, 0x1FB3, 0x1FB4, 0x1FB5, 0x1FB6, 0x1FB7, 
    0x1FB0, 0x1FB1, 0x1F70, 0x1F71, 0x1FB3, 0x1FBD, 0x1FBE, 0x1FBF, 
    0x1FC0, 0x1FC1, 0x1FC2, 0x1FC3, 0x1FC4, 0x1FC5, 0x1FC6, 0x1FC7, 
    0x1F72, 0x1F73, 0x1F74, 0x1F75, 0x1FC3, 0x1FCD, 0x1FCE, 0x1FCF, 
    0x1FD0, 0x1FD1, 0x1FD2, 0x1FD3, 0x1FD4, 0x1FD5, 0x1FD6, 0x1FD7, 
    0x1FD0, 0x1FD1, 0x1F76, 0x1F77, 0x1FDC, 0x1FDD, 0x1FDE, 0x1FDF, 
    0x1FE0, 0x1FE1, 0x1FE2, 0x1FE3, 0x1FE4, 0x1FE5, 0x1FE6, 0x1FE7, 
    0x1FE0, 0x1FE1, 0x1F7A, 0x1F7B, 0x1FE5, 0x1FED, 0x1FEE, 0x1FEF, 
    0x1FF0, 0x1FF1, 0x1FF2, 0x1FF3, 0x1FF4, 0x1FF5, 0x1FF6, 0x1FF7, 
    0x1F78, 0x1F79, 0x1F7C, 0x1F7D, 0x1FF3, 0x1FFD, 0x1FFE, 0x1FFF
  };

  const _UCS4 Greek_Extended::title[] = {
    0x1F08, 0x1F09, 0x1F0A, 0x1F0B, 0x1F0C, 0x1F0D, 0x1F0E, 0x1F0F, 
    0x1F08, 0x1F09, 0x1F0A, 0x1F0B, 0x1F0C, 0x1F0D, 0x1F0E, 0x1F0F, 
    0x1F18, 0x1F19, 0x1F1A, 0x1F1B, 0x1F1C, 0x1F1D, 0x1F16, 0x1F17, 
    0x1F18, 0x1F19, 0x1F1A, 0x1F1B, 0x1F1C, 0x1F1D, 0x1F1E, 0x1F1F, 
    0x1F28, 0x1F29, 0x1F2A, 0x1F2B, 0x1F2C, 0x1F2D, 0x1F2E, 0x1F2F, 
    0x1F28, 0x1F29, 0x1F2A, 0x1F2B, 0x1F2C, 0x1F2D, 0x1F2E, 0x1F2F, 
    0x1F38, 0x1F39, 0x1F3A, 0x1F3B, 0x1F3C, 0x1F3D, 0x1F3E, 0x1F3F, 
    0x1F38, 0x1F39, 0x1F3A, 0x1F3B, 0x1F3C, 0x1F3D, 0x1F3E, 0x1F3F, 
    0x1F48, 0x1F49, 0x1F4A, 0x1F4B, 0x1F4C, 0x1F4D, 0x1F46, 0x1F47, 
    0x1F48, 0x1F49, 0x1F4A, 0x1F4B, 0x1F4C, 0x1F4D, 0x1F4E, 0x1F4F, 
    0x1F50, 0x1F59, 0x1F52, 0x1F5B, 0x1F54, 0x1F5D, 0x1F56, 0x1F5F, 
    0x1F58, 0x1F59, 0x1F5A, 0x1F5B, 0x1F5C, 0x1F5D, 0x1F5E, 0x1F5F, 
    0x1F68, 0x1F69, 0x1F6A, 0x1F6B, 0x1F6C, 0x1F6D, 0x1F6E, 0x1F6F, 
    0x1F68, 0x1F69, 0x1F6A, 0x1F6B, 0x1F6C, 0x1F6D, 0x1F6E, 0x1F6F, 
    0x1FBA, 0x1FBB, 0x1FC8, 0x1FC9, 0x1FCA, 0x1FCB, 0x1FDA, 0x1FDB, 
    0x1FF8, 0x1FF9, 0x1FEA, 0x1FEB, 0x1FFA, 0x1FFB, 0x1F7E, 0x1F7F, 
    0x1F88, 0x1F89, 0x1F8A, 0x1F8B, 0x1F8C, 0x1F8D, 0x1F8E, 0x1F8F, 
    0x1F88, 0x1F89, 0x1F8A, 0x1F8B, 0x1F8C, 0x1F8D, 0x1F8E, 0x1F8F, 
    0x1F98, 0x1F99, 0x1F9A, 0x1F9B, 0x1F9C, 0x1F9D, 0x1F9E, 0x1F9F, 
    0x1F98, 0x1F99, 0x1F9A, 0x1F9B, 0x1F9C, 0x1F9D, 0x1F9E, 0x1F9F, 
    0x1FA8, 0x1FA9, 0x1FAA, 0x1FAB, 0x1FAC, 0x1FAD, 0x1FAE, 0x1FAF, 
    0x1FA8, 0x1FA9, 0x1FAA, 0x1FAB, 0x1FAC, 0x1FAD, 0x1FAE, 0x1FAF, 
    0x1FB8, 0x1FB9, 0x1FB2, 0x1FBC, 0x1FB4, 0x1FB5, 0x1FB6, 0x1FB7, 
    0x1FB8, 0x1FB9, 0x1FBA, 0x1FBB, 0x1FBC, 0x1FBD, 0x0399, 0x1FBF, 
    0x1FC0, 0x1FC1, 0x1FC2, 0x1FCC, 0x1FC4, 0x1FC5, 0x1FC6, 0x1FC7, 
    0x1FC8, 0x1FC9, 0x1FCA, 0x1FCB, 0x1FCC, 0x1FCD, 0x1FCE, 0x1FCF, 
    0x1FD8, 0x1FD9, 0x1FD2, 0x1FD3, 0x1FD4, 0x1FD5, 0x1FD6, 0x1FD7, 
    0x1FD8, 0x1FD9, 0x1FDA, 0x1FDB, 0x1FDC, 0x1FDD, 0x1FDE, 0x1FDF, 
    0x1FE8, 0x1FE9, 0x1FE2, 0x1FE3, 0x1FE4, 0x1FEC, 0x1FE6, 0x1FE7, 
    0x1FE8, 0x1FE9, 0x1FEA, 0x1FEB, 0x1FEC, 0x1FED, 0x1FEE, 0x1FEF, 
    0x1FF0, 0x1FF1, 0x1FF2, 0x1FFC, 0x1FF4, 0x1FF5, 0x1FF6, 0x1FF7, 
    0x1FF8, 0x1FF9, 0x1FFA, 0x1FFB, 0x1FFC, 0x1FFD, 0x1FFE, 0x1FFF
  };

  const unsigned char Greek_Extended::cat[] = {
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lt, CAT_Sk, CAT_Ll, CAT_Sk, 
    CAT_Sk, CAT_Sk, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lt, CAT_Sk, CAT_Sk, CAT_Sk, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Sk, CAT_Sk, CAT_Sk, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Sk, CAT_Sk, CAT_Sk, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lt, CAT_Sk, CAT_Sk, CAT_Ll
  };

  const unsigned char Greek_Extended::bidir[] = {
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_L
  };

  const unsigned char Greek_Extended::decomp[] = {
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
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP
  };

  const _UCS2 Greek_Extended::decompStr[][2] = {
    { 0x03B1, 0x0313 }, { 0x03B1, 0x0314 }, { 0x1F00, 0x0300 }, { 0x1F01, 0x0300 }, 
    { 0x1F00, 0x0301 }, { 0x1F01, 0x0301 }, { 0x1F00, 0x0342 }, { 0x1F01, 0x0342 }, 
    { 0x0391, 0x0313 }, { 0x0391, 0x0314 }, { 0x1F08, 0x0300 }, { 0x1F09, 0x0300 }, 
    { 0x1F08, 0x0301 }, { 0x1F09, 0x0301 }, { 0x1F08, 0x0342 }, { 0x1F09, 0x0342 }, 
    { 0x03B5, 0x0313 }, { 0x03B5, 0x0314 }, { 0x1F10, 0x0300 }, { 0x1F11, 0x0300 }, 
    { 0x1F10, 0x0301 }, { 0x1F11, 0x0301 }, { 0x1F16, 0x0000 }, { 0x1F17, 0x0000 }, 
    { 0x0395, 0x0313 }, { 0x0395, 0x0314 }, { 0x1F18, 0x0300 }, { 0x1F19, 0x0300 }, 
    { 0x1F18, 0x0301 }, { 0x1F19, 0x0301 }, { 0x1F1E, 0x0000 }, { 0x1F1F, 0x0000 }, 
    { 0x03B7, 0x0313 }, { 0x03B7, 0x0314 }, { 0x1F20, 0x0300 }, { 0x1F21, 0x0300 }, 
    { 0x1F20, 0x0301 }, { 0x1F21, 0x0301 }, { 0x1F20, 0x0342 }, { 0x1F21, 0x0342 }, 
    { 0x0397, 0x0313 }, { 0x0397, 0x0314 }, { 0x1F28, 0x0300 }, { 0x1F29, 0x0300 }, 
    { 0x1F28, 0x0301 }, { 0x1F29, 0x0301 }, { 0x1F28, 0x0342 }, { 0x1F29, 0x0342 }, 
    { 0x03B9, 0x0313 }, { 0x03B9, 0x0314 }, { 0x1F30, 0x0300 }, { 0x1F31, 0x0300 }, 
    { 0x1F30, 0x0301 }, { 0x1F31, 0x0301 }, { 0x1F30, 0x0342 }, { 0x1F31, 0x0342 }, 
    { 0x0399, 0x0313 }, { 0x0399, 0x0314 }, { 0x1F38, 0x0300 }, { 0x1F39, 0x0300 }, 
    { 0x1F38, 0x0301 }, { 0x1F39, 0x0301 }, { 0x1F38, 0x0342 }, { 0x1F39, 0x0342 }, 
    { 0x03BF, 0x0313 }, { 0x03BF, 0x0314 }, { 0x1F40, 0x0300 }, { 0x1F41, 0x0300 }, 
    { 0x1F40, 0x0301 }, { 0x1F41, 0x0301 }, { 0x1F46, 0x0000 }, { 0x1F47, 0x0000 }, 
    { 0x039F, 0x0313 }, { 0x039F, 0x0314 }, { 0x1F48, 0x0300 }, { 0x1F49, 0x0300 }, 
    { 0x1F48, 0x0301 }, { 0x1F49, 0x0301 }, { 0x1F4E, 0x0000 }, { 0x1F4F, 0x0000 }, 
    { 0x03C5, 0x0313 }, { 0x03C5, 0x0314 }, { 0x1F50, 0x0300 }, { 0x1F51, 0x0300 }, 
    { 0x1F50, 0x0301 }, { 0x1F51, 0x0301 }, { 0x1F50, 0x0342 }, { 0x1F51, 0x0342 }, 
    { 0x1F58, 0x0000 }, { 0x03A5, 0x0314 }, { 0x1F5A, 0x0000 }, { 0x1F59, 0x0300 }, 
    { 0x1F5C, 0x0000 }, { 0x1F59, 0x0301 }, { 0x1F5E, 0x0000 }, { 0x1F59, 0x0342 }, 
    { 0x03C9, 0x0313 }, { 0x03C9, 0x0314 }, { 0x1F60, 0x0300 }, { 0x1F61, 0x0300 }, 
    { 0x1F60, 0x0301 }, { 0x1F61, 0x0301 }, { 0x1F60, 0x0342 }, { 0x1F61, 0x0342 }, 
    { 0x03A9, 0x0313 }, { 0x03A9, 0x0314 }, { 0x1F68, 0x0300 }, { 0x1F69, 0x0300 }, 
    { 0x1F68, 0x0301 }, { 0x1F69, 0x0301 }, { 0x1F68, 0x0342 }, { 0x1F69, 0x0342 }, 
    { 0x03B1, 0x0300 }, { 0x03AC, 0x0000 }, { 0x03B5, 0x0300 }, { 0x03AD, 0x0000 }, 
    { 0x03B7, 0x0300 }, { 0x03AE, 0x0000 }, { 0x03B9, 0x0300 }, { 0x03AF, 0x0000 }, 
    { 0x03BF, 0x0300 }, { 0x03CC, 0x0000 }, { 0x03C5, 0x0300 }, { 0x03CD, 0x0000 }, 
    { 0x03C9, 0x0300 }, { 0x03CE, 0x0000 }, { 0x1F7E, 0x0000 }, { 0x1F7F, 0x0000 }, 
    { 0x1F00, 0x0345 }, { 0x1F01, 0x0345 }, { 0x1F02, 0x0345 }, { 0x1F03, 0x0345 }, 
    { 0x1F04, 0x0345 }, { 0x1F05, 0x0345 }, { 0x1F06, 0x0345 }, { 0x1F07, 0x0345 }, 
    { 0x1F08, 0x0345 }, { 0x1F09, 0x0345 }, { 0x1F0A, 0x0345 }, { 0x1F0B, 0x0345 }, 
    { 0x1F0C, 0x0345 }, { 0x1F0D, 0x0345 }, { 0x1F0E, 0x0345 }, { 0x1F0F, 0x0345 }, 
    { 0x1F20, 0x0345 }, { 0x1F21, 0x0345 }, { 0x1F22, 0x0345 }, { 0x1F23, 0x0345 }, 
    { 0x1F24, 0x0345 }, { 0x1F25, 0x0345 }, { 0x1F26, 0x0345 }, { 0x1F27, 0x0345 }, 
    { 0x1F28, 0x0345 }, { 0x1F29, 0x0345 }, { 0x1F2A, 0x0345 }, { 0x1F2B, 0x0345 }, 
    { 0x1F2C, 0x0345 }, { 0x1F2D, 0x0345 }, { 0x1F2E, 0x0345 }, { 0x1F2F, 0x0345 }, 
    { 0x1F60, 0x0345 }, { 0x1F61, 0x0345 }, { 0x1F62, 0x0345 }, { 0x1F63, 0x0345 }, 
    { 0x1F64, 0x0345 }, { 0x1F65, 0x0345 }, { 0x1F66, 0x0345 }, { 0x1F67, 0x0345 }, 
    { 0x1F68, 0x0345 }, { 0x1F69, 0x0345 }, { 0x1F6A, 0x0345 }, { 0x1F6B, 0x0345 }, 
    { 0x1F6C, 0x0345 }, { 0x1F6D, 0x0345 }, { 0x1F6E, 0x0345 }, { 0x1F6F, 0x0345 }, 
    { 0x03B1, 0x0306 }, { 0x03B1, 0x0304 }, { 0x1F70, 0x0345 }, { 0x03B1, 0x0345 }, 
    { 0x03AC, 0x0345 }, { 0x1FB5, 0x0000 }, { 0x03B1, 0x0342 }, { 0x1FB6, 0x0345 }, 
    { 0x0391, 0x0306 }, { 0x0391, 0x0304 }, { 0x0391, 0x0300 }, { 0x0386, 0x0000 }, 
    { 0x0391, 0x0345 }, { 0x0020, 0x0313 }, { 0x03B9, 0x0000 }, { 0x0020, 0x0313 }, 
    { 0x0020, 0x0342 }, { 0x00A8, 0x0342 }, { 0x1F74, 0x0345 }, { 0x03B7, 0x0345 }, 
    { 0x03AE, 0x0345 }, { 0x1FC5, 0x0000 }, { 0x03B7, 0x0342 }, { 0x1FC6, 0x0345 }, 
    { 0x0395, 0x0300 }, { 0x0388, 0x0000 }, { 0x0397, 0x0300 }, { 0x0389, 0x0000 }, 
    { 0x0397, 0x0345 }, { 0x1FBF, 0x0300 }, { 0x1FBF, 0x0301 }, { 0x1FBF, 0x0342 }, 
    { 0x03B9, 0x0306 }, { 0x03B9, 0x0304 }, { 0x03CA, 0x0300 }, { 0x0390, 0x0000 }, 
    { 0x1FD4, 0x0000 }, { 0x1FD5, 0x0000 }, { 0x03B9, 0x0342 }, { 0x03CA, 0x0342 }, 
    { 0x0399, 0x0306 }, { 0x0399, 0x0304 }, { 0x0399, 0x0300 }, { 0x038A, 0x0000 }, 
    { 0x1FDC, 0x0000 }, { 0x1FFE, 0x0300 }, { 0x1FFE, 0x0301 }, { 0x1FFE, 0x0342 }, 
    { 0x03C5, 0x0306 }, { 0x03C5, 0x0304 }, { 0x03CB, 0x0300 }, { 0x03B0, 0x0000 }, 
    { 0x03C1, 0x0313 }, { 0x03C1, 0x0314 }, { 0x03C5, 0x0342 }, { 0x03CB, 0x0342 }, 
    { 0x03A5, 0x0306 }, { 0x03A5, 0x0304 }, { 0x03A5, 0x0300 }, { 0x038E, 0x0000 }, 
    { 0x03A1, 0x0314 }, { 0x00A8, 0x0300 }, { 0x0385, 0x0000 }, { 0x0060, 0x0000 }, 
    { 0x1FF0, 0x0000 }, { 0x1FF1, 0x0000 }, { 0x1F7C, 0x0345 }, { 0x03C9, 0x0345 }, 
    { 0x03CE, 0x0345 }, { 0x1FF5, 0x0000 }, { 0x03C9, 0x0342 }, { 0x1FF6, 0x0345 }, 
    { 0x039F, 0x0300 }, { 0x038C, 0x0000 }, { 0x03A9, 0x0300 }, { 0x038F, 0x0000 }, 
    { 0x03A9, 0x0345 }, { 0x00B4, 0x0000 }, { 0x0020, 0x0314 }, { 0x1FFF, 0x0000 }
  };

    const bool Greek_Extended::Alphabetic[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 1, 0, 
        0, 0, 1, 1, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        1, 1, 1, 1, 0, 0, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 1, 1, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0
    };

    const bool Greek_Extended::Diacritic[] = {
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
        0, 0, 0, 0, 0, 1, 0, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0
    };

    const bool Greek_Extended::Identifier_Part[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 1, 0, 
        0, 0, 1, 1, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        1, 1, 1, 1, 0, 0, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 1, 1, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0
    };

    const bool Greek_Extended::Uppercase[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 0, 0, 0, 0
    };

    const bool Greek_Extended::Lowercase[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 0, 1, 1, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        0, 0, 1, 1, 1, 0, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 0, 0, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 0, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Greek_Extended);
