/*$Id: 370-3FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:10:50 +0100.
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
 
  class Greek370 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Greek370() {
      my_first_letter = 0x370;
      my_last_letter  = 0x3FF;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x03910300] = 0x1FBA;
      composeMap[0x03910301] = 0x0386;
      composeMap[0x03910304] = 0x1FB9;
      composeMap[0x03910306] = 0x1FB8;
      composeMap[0x03910313] = 0x1F08;
      composeMap[0x03910314] = 0x1F09;
      composeMap[0x03910345] = 0x1FBC;
      composeMap[0x03950300] = 0x1FC8;
      composeMap[0x03950301] = 0x0388;
      composeMap[0x03950313] = 0x1F18;
      composeMap[0x03950314] = 0x1F19;
      composeMap[0x03970300] = 0x1FCA;
      composeMap[0x03970301] = 0x0389;
      composeMap[0x03970313] = 0x1F28;
      composeMap[0x03970314] = 0x1F29;
      composeMap[0x03970345] = 0x1FCC;
      composeMap[0x03990300] = 0x1FDA;
      composeMap[0x03990301] = 0x038A;
      composeMap[0x03990304] = 0x1FD9;
      composeMap[0x03990306] = 0x1FD8;
      composeMap[0x03990308] = 0x03AA;
      composeMap[0x03990313] = 0x1F38;
      composeMap[0x03990314] = 0x1F39;
      composeMap[0x039F0300] = 0x1FF8;
      composeMap[0x039F0301] = 0x038C;
      composeMap[0x039F0313] = 0x1F48;
      composeMap[0x039F0314] = 0x1F49;
      composeMap[0x03A10314] = 0x1FEC;
      composeMap[0x03A50300] = 0x1FEA;
      composeMap[0x03A50301] = 0x038E;
      composeMap[0x03A50304] = 0x1FE9;
      composeMap[0x03A50306] = 0x1FE8;
      composeMap[0x03A50308] = 0x03AB;
      composeMap[0x03A50314] = 0x1F59;
      composeMap[0x03A90300] = 0x1FFA;
      composeMap[0x03A90301] = 0x038F;
      composeMap[0x03A90313] = 0x1F68;
      composeMap[0x03A90314] = 0x1F69;
      composeMap[0x03A90345] = 0x1FFC;
      composeMap[0x03AC0345] = 0x1FB4;
      composeMap[0x03AE0345] = 0x1FC4;
      composeMap[0x03B10300] = 0x1F70;
      composeMap[0x03B10301] = 0x03AC;
      composeMap[0x03B10304] = 0x1FB1;
      composeMap[0x03B10306] = 0x1FB0;
      composeMap[0x03B10313] = 0x1F00;
      composeMap[0x03B10314] = 0x1F01;
      composeMap[0x03B10342] = 0x1FB6;
      composeMap[0x03B10345] = 0x1FB3;
      composeMap[0x03B50300] = 0x1F72;
      composeMap[0x03B50301] = 0x03AD;
      composeMap[0x03B50313] = 0x1F10;
      composeMap[0x03B50314] = 0x1F11;
      composeMap[0x03B70300] = 0x1F74;
      composeMap[0x03B70301] = 0x03AE;
      composeMap[0x03B70313] = 0x1F20;
      composeMap[0x03B70314] = 0x1F21;
      composeMap[0x03B70342] = 0x1FC6;
      composeMap[0x03B70345] = 0x1FC3;
      composeMap[0x03B90300] = 0x1F76;
      composeMap[0x03B90301] = 0x03AF;
      composeMap[0x03B90304] = 0x1FD1;
      composeMap[0x03B90306] = 0x1FD0;
      composeMap[0x03B90308] = 0x03CA;
      composeMap[0x03B90313] = 0x1F30;
      composeMap[0x03B90314] = 0x1F31;
      composeMap[0x03B90342] = 0x1FD6;
      composeMap[0x03BF0300] = 0x1F78;
      composeMap[0x03BF0301] = 0x03CC;
      composeMap[0x03BF0313] = 0x1F40;
      composeMap[0x03BF0314] = 0x1F41;
      composeMap[0x03C10313] = 0x1FE4;
      composeMap[0x03C10314] = 0x1FE5;
      composeMap[0x03C50300] = 0x1F7A;
      composeMap[0x03C50301] = 0x03CD;
      composeMap[0x03C50304] = 0x1FE1;
      composeMap[0x03C50306] = 0x1FE0;
      composeMap[0x03C50308] = 0x03CB;
      composeMap[0x03C50313] = 0x1F50;
      composeMap[0x03C50314] = 0x1F51;
      composeMap[0x03C50342] = 0x1FE6;
      composeMap[0x03C90300] = 0x1F7C;
      composeMap[0x03C90301] = 0x03CE;
      composeMap[0x03C90313] = 0x1F60;
      composeMap[0x03C90314] = 0x1F61;
      composeMap[0x03C90342] = 0x1FF6;
      composeMap[0x03C90345] = 0x1FF3;
      composeMap[0x03CA0300] = 0x1FD2;
      composeMap[0x03CA0301] = 0x0390;
      composeMap[0x03CA0342] = 0x1FD7;
      composeMap[0x03CB0300] = 0x1FE2;
      composeMap[0x03CB0301] = 0x03B0;
      composeMap[0x03CB0342] = 0x1FE7;
      composeMap[0x03CE0345] = 0x1FF4;
      composeMap[0x03D20301] = 0x03D3;
      composeMap[0x03D20308] = 0x03D4;

    }


    ~Greek370() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Greek";
    }

    bool isDefined(const UCS4 & _uc) const {
      return (isdefined[_uc - my_first_letter]);
    }

    UCS4 uppercase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Greek370::upper[_uc - my_first_letter];
    }

    UCS4 lowercase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Greek370::lower[_uc - my_first_letter];
    }

    UCS4 titlecase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Greek370::title[_uc - my_first_letter];
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
      return Babylon::Gen_Cat(Greek370::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Greek370::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Greek370::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Greek370::decompStr[_uc - my_first_letter][0];
      us[1] = Greek370::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(Greek370::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(Greek370::ea[_uc - my_first_letter]);
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
      return Greek370::Terminal_Punctuation[_uc - my_first_letter];
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
      return Greek370::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return Greek370::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return Greek370::Identifier_Part[_uc - my_first_letter];
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
      return Greek370::Uppercase[_uc - my_first_letter];
    }

    bool is_Lowercase(const UCS4 & _uc) const {
      return Greek370::Lowercase[_uc - my_first_letter];
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
    Greek370(const Greek370 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[144];
    static const UCS4 upper[144];
    static const UCS4 lower[144];
    static const UCS4 title[144];
    static const unsigned char cat[144];
    static const unsigned char bidir[144];
    static const unsigned char decomp[144];
    static const UCS2 decompStr[144][2];
    static const unsigned char lb[144];
    static const unsigned char ea[144];
    map<UCS4, UCS4> composeMap;
    static const bool Terminal_Punctuation[144];
    static const bool Alphabetic[144];
    static const bool Diacritic[144];
    static const bool Identifier_Part[144];
    static const bool Uppercase[144];
    static const bool Lowercase[144];

  }; // class Greek370

  const bool Greek370::isdefined[] = {
    0, 0, 0, 0, 1, 1, 0, 0, 
    0, 0, 1, 0, 0, 0, 1, 0, 
    0, 0, 0, 0, 1, 1, 1, 1, 
    1, 1, 1, 0, 1, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const UCS4 Greek370::upper[] = {
    0x0370, 0x0371, 0x0372, 0x0373, 0x0374, 0x0375, 0x0376, 0x0377, 
    0x0378, 0x0379, 0x037A, 0x037B, 0x037C, 0x037D, 0x037E, 0x037F, 
    0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x0386, 0x0387, 
    0x0388, 0x0389, 0x038A, 0x038B, 0x038C, 0x038D, 0x038E, 0x038F, 
    0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 
    0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 
    0x03A0, 0x03A1, 0x03A2, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 
    0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x0386, 0x0388, 0x0389, 0x038A, 
    0x03B0, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 
    0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 
    0x03A0, 0x03A1, 0x03A3, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 
    0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x038C, 0x038E, 0x038F, 0x03CF, 
    0x0392, 0x0398, 0x03D2, 0x03D3, 0x03D4, 0x03A6, 0x03A0, 0x03D7, 
    0x03D8, 0x03D9, 0x03DA, 0x03DA, 0x03DC, 0x03DC, 0x03DE, 0x03DE, 
    0x03E0, 0x03E0, 0x03E2, 0x03E2, 0x03E4, 0x03E4, 0x03E6, 0x03E6, 
    0x03E8, 0x03E8, 0x03EA, 0x03EA, 0x03EC, 0x03EC, 0x03EE, 0x03EE, 
    0x039A, 0x03A1, 0x03A3, 0x03F3, 0x03F4, 0x03F5, 0x03F6, 0x03F7, 
    0x03F8, 0x03F9, 0x03FA, 0x03FB, 0x03FC, 0x03FD, 0x03FE, 0x03FF
  };

  const UCS4 Greek370::lower[] = {
    0x0370, 0x0371, 0x0372, 0x0373, 0x0374, 0x0375, 0x0376, 0x0377, 
    0x0378, 0x0379, 0x037A, 0x037B, 0x037C, 0x037D, 0x037E, 0x037F, 
    0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x03AC, 0x0387, 
    0x03AD, 0x03AE, 0x03AF, 0x038B, 0x03CC, 0x038D, 0x03CD, 0x03CE, 
    0x0390, 0x03B1, 0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6, 0x03B7, 
    0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE, 0x03BF, 
    0x03C0, 0x03C1, 0x03A2, 0x03C3, 0x03C4, 0x03C5, 0x03C6, 0x03C7, 
    0x03C8, 0x03C9, 0x03CA, 0x03CB, 0x03AC, 0x03AD, 0x03AE, 0x03AF, 
    0x03B0, 0x03B1, 0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6, 0x03B7, 
    0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE, 0x03BF, 
    0x03C0, 0x03C1, 0x03C2, 0x03C3, 0x03C4, 0x03C5, 0x03C6, 0x03C7, 
    0x03C8, 0x03C9, 0x03CA, 0x03CB, 0x03CC, 0x03CD, 0x03CE, 0x03CF, 
    0x03D0, 0x03D1, 0x03D2, 0x03D3, 0x03D4, 0x03D5, 0x03D6, 0x03D7, 
    0x03D8, 0x03D9, 0x03DB, 0x03DB, 0x03DD, 0x03DD, 0x03DF, 0x03DF, 
    0x03E1, 0x03E1, 0x03E3, 0x03E3, 0x03E5, 0x03E5, 0x03E7, 0x03E7, 
    0x03E9, 0x03E9, 0x03EB, 0x03EB, 0x03ED, 0x03ED, 0x03EF, 0x03EF, 
    0x03F0, 0x03F1, 0x03F2, 0x03F3, 0x03F4, 0x03F5, 0x03F6, 0x03F7, 
    0x03F8, 0x03F9, 0x03FA, 0x03FB, 0x03FC, 0x03FD, 0x03FE, 0x03FF
  };

  const UCS4 Greek370::title[] = {
    0x0370, 0x0371, 0x0372, 0x0373, 0x0374, 0x0375, 0x0376, 0x0377, 
    0x0378, 0x0379, 0x037A, 0x037B, 0x037C, 0x037D, 0x037E, 0x037F, 
    0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x0386, 0x0387, 
    0x0388, 0x0389, 0x038A, 0x038B, 0x038C, 0x038D, 0x038E, 0x038F, 
    0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 
    0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 
    0x03A0, 0x03A1, 0x03A2, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 
    0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x0386, 0x0388, 0x0389, 0x038A, 
    0x03B0, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 
    0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 
    0x03A0, 0x03A1, 0x03A3, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 
    0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x038C, 0x038E, 0x038F, 0x03CF, 
    0x0392, 0x0398, 0x03D2, 0x03D3, 0x03D4, 0x03A6, 0x03A0, 0x03D7, 
    0x03D8, 0x03D9, 0x03DA, 0x03DA, 0x03DC, 0x03DC, 0x03DE, 0x03DE, 
    0x03E0, 0x03E0, 0x03E2, 0x03E2, 0x03E4, 0x03E4, 0x03E6, 0x03E6, 
    0x03E8, 0x03E8, 0x03EA, 0x03EA, 0x03EC, 0x03EC, 0x03EE, 0x03EE, 
    0x039A, 0x03A1, 0x03A3, 0x03F3, 0x03F4, 0x03F5, 0x03F6, 0x03F7, 
    0x03F8, 0x03F9, 0x03FA, 0x03FB, 0x03FC, 0x03FD, 0x03FE, 0x03FF
  };

  const unsigned char Greek370::cat[] = {
    CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, 
    CAT_Sk, CAT_Sk, CAT_Lm, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Po, CAT_Sk, 
    CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Lu, CAT_Po, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Sk, CAT_Lu, CAT_Sk, CAT_Lu, CAT_Lu, 
    CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Lu, CAT_Lu, CAT_Sk, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Sk, 
    CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Sk, CAT_Sk, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, 
    CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk
  };

  const unsigned char Greek370::bidir[] = {
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_ON, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
  };

  const unsigned char Greek370::decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Greek370::decompStr[][2] = {
    { 0x0370, 0x0000 }, { 0x0371, 0x0000 }, { 0x0372, 0x0000 }, { 0x0373, 0x0000 }, 
    { 0x02B9, 0x0000 }, { 0x0375, 0x0000 }, { 0x0376, 0x0000 }, { 0x0377, 0x0000 }, 
    { 0x0378, 0x0000 }, { 0x0379, 0x0000 }, { 0x0020, 0x0345 }, { 0x037B, 0x0000 }, 
    { 0x037C, 0x0000 }, { 0x037D, 0x0000 }, { 0x003B, 0x0000 }, { 0x037F, 0x0000 }, 
    { 0x0380, 0x0000 }, { 0x0381, 0x0000 }, { 0x0382, 0x0000 }, { 0x0383, 0x0000 }, 
    { 0x0020, 0x0301 }, { 0x00A8, 0x0301 }, { 0x0391, 0x0301 }, { 0x00B7, 0x0000 }, 
    { 0x0395, 0x0301 }, { 0x0397, 0x0301 }, { 0x0399, 0x0301 }, { 0x038B, 0x0000 }, 
    { 0x039F, 0x0301 }, { 0x038D, 0x0000 }, { 0x03A5, 0x0301 }, { 0x03A9, 0x0301 }, 
    { 0x03CA, 0x0301 }, { 0x0391, 0x0000 }, { 0x0392, 0x0000 }, { 0x0393, 0x0000 }, 
    { 0x0394, 0x0000 }, { 0x0395, 0x0000 }, { 0x0396, 0x0000 }, { 0x0397, 0x0000 }, 
    { 0x0398, 0x0000 }, { 0x0399, 0x0000 }, { 0x039A, 0x0000 }, { 0x039B, 0x0000 }, 
    { 0x039C, 0x0000 }, { 0x039D, 0x0000 }, { 0x039E, 0x0000 }, { 0x039F, 0x0000 }, 
    { 0x03A0, 0x0000 }, { 0x03A1, 0x0000 }, { 0x03A2, 0x0000 }, { 0x03A3, 0x0000 }, 
    { 0x03A4, 0x0000 }, { 0x03A5, 0x0000 }, { 0x03A6, 0x0000 }, { 0x03A7, 0x0000 }, 
    { 0x03A8, 0x0000 }, { 0x03A9, 0x0000 }, { 0x0399, 0x0308 }, { 0x03A5, 0x0308 }, 
    { 0x03B1, 0x0301 }, { 0x03B5, 0x0301 }, { 0x03B7, 0x0301 }, { 0x03B9, 0x0301 }, 
    { 0x03CB, 0x0301 }, { 0x03B1, 0x0000 }, { 0x03B2, 0x0000 }, { 0x03B3, 0x0000 }, 
    { 0x03B4, 0x0000 }, { 0x03B5, 0x0000 }, { 0x03B6, 0x0000 }, { 0x03B7, 0x0000 }, 
    { 0x03B8, 0x0000 }, { 0x03B9, 0x0000 }, { 0x03BA, 0x0000 }, { 0x03BB, 0x0000 }, 
    { 0x03BC, 0x0000 }, { 0x03BD, 0x0000 }, { 0x03BE, 0x0000 }, { 0x03BF, 0x0000 }, 
    { 0x03C0, 0x0000 }, { 0x03C1, 0x0000 }, { 0x03C2, 0x0000 }, { 0x03C3, 0x0000 }, 
    { 0x03C4, 0x0000 }, { 0x03C5, 0x0000 }, { 0x03C6, 0x0000 }, { 0x03C7, 0x0000 }, 
    { 0x03C8, 0x0000 }, { 0x03C9, 0x0000 }, { 0x03B9, 0x0308 }, { 0x03C5, 0x0308 }, 
    { 0x03BF, 0x0301 }, { 0x03C5, 0x0301 }, { 0x03C9, 0x0301 }, { 0x03CF, 0x0000 }, 
    { 0x03B2, 0x0000 }, { 0x03B8, 0x0000 }, { 0x03A5, 0x0000 }, { 0x03D2, 0x0301 }, 
    { 0x03D2, 0x0308 }, { 0x03C6, 0x0000 }, { 0x03C0, 0x0000 }, { 0x03D7, 0x0000 }, 
    { 0x03D8, 0x0000 }, { 0x03D9, 0x0000 }, { 0x03DA, 0x0000 }, { 0x03DB, 0x0000 }, 
    { 0x03DC, 0x0000 }, { 0x03DD, 0x0000 }, { 0x03DE, 0x0000 }, { 0x03DF, 0x0000 }, 
    { 0x03E0, 0x0000 }, { 0x03E1, 0x0000 }, { 0x03E2, 0x0000 }, { 0x03E3, 0x0000 }, 
    { 0x03E4, 0x0000 }, { 0x03E5, 0x0000 }, { 0x03E6, 0x0000 }, { 0x03E7, 0x0000 }, 
    { 0x03E8, 0x0000 }, { 0x03E9, 0x0000 }, { 0x03EA, 0x0000 }, { 0x03EB, 0x0000 }, 
    { 0x03EC, 0x0000 }, { 0x03ED, 0x0000 }, { 0x03EE, 0x0000 }, { 0x03EF, 0x0000 }, 
    { 0x03BA, 0x0000 }, { 0x03C1, 0x0000 }, { 0x03C2, 0x0000 }, { 0x03F3, 0x0000 }, 
    { 0x03F4, 0x0000 }, { 0x03F5, 0x0000 }, { 0x03F6, 0x0000 }, { 0x03F7, 0x0000 }, 
    { 0x03F8, 0x0000 }, { 0x03F9, 0x0000 }, { 0x03FA, 0x0000 }, { 0x03FB, 0x0000 }, 
    { 0x03FC, 0x0000 }, { 0x03FD, 0x0000 }, { 0x03FE, 0x0000 }, { 0x03FF, 0x0000 }
  };

  const unsigned char Greek370::lb[] = {
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
  };

  const unsigned char Greek370::ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bool Greek370::Terminal_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Greek370::Alphabetic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        1, 1, 1, 0, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Greek370::Diacritic[] = {
        0, 0, 0, 0, 1, 1, 0, 0, 
        0, 0, 1, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Greek370::Identifier_Part[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        1, 1, 1, 0, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Greek370::Uppercase[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        1, 1, 1, 0, 1, 0, 1, 1, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 0, 0, 0, 
        0, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Greek370::Lowercase[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0, 
        1, 1, 0, 0, 0, 1, 1, 1, 
        0, 0, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Greek370);
