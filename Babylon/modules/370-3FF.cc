/*$Id: 370-3FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:22:04 +0100.
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
      _first_letter = 0x370;
      _last_letter  = 0x3FF;
      // _version="3.0.1" // Not yet supported!
      _composeMap[0x03910300] = 0x1FBA;
      _composeMap[0x03910301] = 0x0386;
      _composeMap[0x03910304] = 0x1FB9;
      _composeMap[0x03910306] = 0x1FB8;
      _composeMap[0x03910313] = 0x1F08;
      _composeMap[0x03910314] = 0x1F09;
      _composeMap[0x03910345] = 0x1FBC;
      _composeMap[0x03950300] = 0x1FC8;
      _composeMap[0x03950301] = 0x0388;
      _composeMap[0x03950313] = 0x1F18;
      _composeMap[0x03950314] = 0x1F19;
      _composeMap[0x03970300] = 0x1FCA;
      _composeMap[0x03970301] = 0x0389;
      _composeMap[0x03970313] = 0x1F28;
      _composeMap[0x03970314] = 0x1F29;
      _composeMap[0x03970345] = 0x1FCC;
      _composeMap[0x03990300] = 0x1FDA;
      _composeMap[0x03990301] = 0x038A;
      _composeMap[0x03990304] = 0x1FD9;
      _composeMap[0x03990306] = 0x1FD8;
      _composeMap[0x03990308] = 0x03AA;
      _composeMap[0x03990313] = 0x1F38;
      _composeMap[0x03990314] = 0x1F39;
      _composeMap[0x039F0300] = 0x1FF8;
      _composeMap[0x039F0301] = 0x038C;
      _composeMap[0x039F0313] = 0x1F48;
      _composeMap[0x039F0314] = 0x1F49;
      _composeMap[0x03A10314] = 0x1FEC;
      _composeMap[0x03A50300] = 0x1FEA;
      _composeMap[0x03A50301] = 0x038E;
      _composeMap[0x03A50304] = 0x1FE9;
      _composeMap[0x03A50306] = 0x1FE8;
      _composeMap[0x03A50308] = 0x03AB;
      _composeMap[0x03A50314] = 0x1F59;
      _composeMap[0x03A90300] = 0x1FFA;
      _composeMap[0x03A90301] = 0x038F;
      _composeMap[0x03A90313] = 0x1F68;
      _composeMap[0x03A90314] = 0x1F69;
      _composeMap[0x03A90345] = 0x1FFC;
      _composeMap[0x03AC0345] = 0x1FB4;
      _composeMap[0x03AE0345] = 0x1FC4;
      _composeMap[0x03B10300] = 0x1F70;
      _composeMap[0x03B10301] = 0x03AC;
      _composeMap[0x03B10304] = 0x1FB1;
      _composeMap[0x03B10306] = 0x1FB0;
      _composeMap[0x03B10313] = 0x1F00;
      _composeMap[0x03B10314] = 0x1F01;
      _composeMap[0x03B10342] = 0x1FB6;
      _composeMap[0x03B10345] = 0x1FB3;
      _composeMap[0x03B50300] = 0x1F72;
      _composeMap[0x03B50301] = 0x03AD;
      _composeMap[0x03B50313] = 0x1F10;
      _composeMap[0x03B50314] = 0x1F11;
      _composeMap[0x03B70300] = 0x1F74;
      _composeMap[0x03B70301] = 0x03AE;
      _composeMap[0x03B70313] = 0x1F20;
      _composeMap[0x03B70314] = 0x1F21;
      _composeMap[0x03B70342] = 0x1FC6;
      _composeMap[0x03B70345] = 0x1FC3;
      _composeMap[0x03B90300] = 0x1F76;
      _composeMap[0x03B90301] = 0x03AF;
      _composeMap[0x03B90304] = 0x1FD1;
      _composeMap[0x03B90306] = 0x1FD0;
      _composeMap[0x03B90308] = 0x03CA;
      _composeMap[0x03B90313] = 0x1F30;
      _composeMap[0x03B90314] = 0x1F31;
      _composeMap[0x03B90342] = 0x1FD6;
      _composeMap[0x03BF0300] = 0x1F78;
      _composeMap[0x03BF0301] = 0x03CC;
      _composeMap[0x03BF0313] = 0x1F40;
      _composeMap[0x03BF0314] = 0x1F41;
      _composeMap[0x03C10313] = 0x1FE4;
      _composeMap[0x03C10314] = 0x1FE5;
      _composeMap[0x03C50300] = 0x1F7A;
      _composeMap[0x03C50301] = 0x03CD;
      _composeMap[0x03C50304] = 0x1FE1;
      _composeMap[0x03C50306] = 0x1FE0;
      _composeMap[0x03C50308] = 0x03CB;
      _composeMap[0x03C50313] = 0x1F50;
      _composeMap[0x03C50314] = 0x1F51;
      _composeMap[0x03C50342] = 0x1FE6;
      _composeMap[0x03C90300] = 0x1F7C;
      _composeMap[0x03C90301] = 0x03CE;
      _composeMap[0x03C90313] = 0x1F60;
      _composeMap[0x03C90314] = 0x1F61;
      _composeMap[0x03C90342] = 0x1FF6;
      _composeMap[0x03C90345] = 0x1FF3;
      _composeMap[0x03CA0300] = 0x1FD2;
      _composeMap[0x03CA0301] = 0x0390;
      _composeMap[0x03CA0342] = 0x1FD7;
      _composeMap[0x03CB0300] = 0x1FE2;
      _composeMap[0x03CB0301] = 0x03B0;
      _composeMap[0x03CB0342] = 0x1FE7;
      _composeMap[0x03CE0345] = 0x1FF4;
      _composeMap[0x03D20301] = 0x03D3;
      _composeMap[0x03D20308] = 0x03D4;

    }


    ~Greek370() {
    }

    UCS4 firstLetter() {
      return _first_letter;
    }

    UCS4 lastLetter() {
      return _last_letter;
    }

    bool is_undef_block() const {
      return 0;
    }

    // query functions:

    string blockname(const UCS4 uc) const {
      return "Greek";
    }

    bool is_defined(const UCS4 uc) const {
      return (_is_defined[uc - _first_letter]);
    }

    UCS4 uppercase(const UCS4 uc) const {
      return Greek370::_upper[uc - _first_letter];
    }

    bool is_Uppercase(const UCS4 uc) const {
      return category(uc) == CAT_Lu;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return Greek370::_lower[uc - _first_letter];
    }

    bool is_Lowercase(const UCS4 uc) const {
      return category(uc) == CAT_Ll;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return Greek370::_title[uc - _first_letter];
    }

    bool is_Titlecase(const UCS4 uc) const {
      return category(uc) == CAT_Lt;
    }

    int dec_digit_value(const UCS4 uc) const {
      return 0;
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      return 0;
    }

    int digit_value(const UCS4 uc) const {
      return 0;
    }

    bool is_Digit(const UCS4 uc) const {
      return 0;
    }

    float numeric_value(const UCS4 uc) const {
      return 0;
    }

    bool is_Numeric(const UCS4 uc) const {
      return 0;
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Greek370::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Greek370::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Greek370::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Greek370::_decompStr[uc - _first_letter][0];
      us[1] = Greek370::_decompStr[uc - _first_letter][1];
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool must_mirror(const UCS4 uc) const {
      return 0;
    }

    Line_Break linebreak(const UCS4 uc) const {
      if (!is_defined(uc))
        return LB_MAX;
      return Babylon::Line_Break(Greek370::_lb[uc - _first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(Greek370::_ea[uc - _first_letter]);
    }

    UCS4 compose (const UCS4 starter, const UCS4 last) {
      return _composeMap[starter << 16 | last];
    }

    bool is_Zero_width(const UCS4 uc) const {
      return 0;
    }

    bool is_White_space(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_break(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Join_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Format_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Dash(const UCS4 uc) const {
      return 0;
    }

    bool is_Hyphen(const UCS4 uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const UCS4 uc) const {
      return Greek370::_Terminal_Punctuation[uc - _first_letter];
    }

    bool is_Math(const UCS4 uc) const {
      return 0;
    }

    bool is_Paired_Punctuation(const UCS4 uc) const {
      return 0;
    }

    bool is_Left_of_Pair(const UCS4 uc) const {
      return 0;
    }

    bool is_Combining(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_spacing(const UCS4 uc) const {
      return 0;
    }

    bool is_Composite(const UCS4 uc) const {
      return Greek370::_Composite[uc - _first_letter];
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Greek370::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return Greek370::_Diacritic[uc - _first_letter];
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Greek370::_Identifier_Part[uc - _first_letter];
    }

    bool is_Ignorable_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const UCS4 uc) const {
      return 0;
    }

    bool is_Ideographic(const UCS4 uc) const {
      return 0;
    }

    bool is_Private_Use(const UCS4 uc) const {
      return 0;
    }

    bool is_Not_a_Character(const UCS4 uc) const {
      return ((uc & 0xFFFE) == 0xFFFE);
    }

    bool is_Private_Use_High_Surrogate(const UCS4 uc) const {
      return 0;
    }

    bool is_Low_Surrogate(const UCS4 uc) const {
      return 0;
    }

    bool is_High_Surrogate(const UCS4 uc) const {
      return 0;
    }

    bool is_Space(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Zs);
    }

    bool is_ISO_Control(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Cc);
    }

    bool is_Punctuation(const UCS4 uc) const {
      return (is_defined(uc) && (category(uc) == CAT_Pc ||
                                 category(uc) == CAT_Pd ||
                                 category(uc) == CAT_Ps ||
                                 category(uc) == CAT_Pe ||
                                 category(uc) == CAT_Pi ||
                                 category(uc) == CAT_Pf ||
                                 category(uc) == CAT_Po)
             );
    }

    bool is_Line_Separator(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Zl);
    }

    bool is_Paragraph_Separator(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Zp);
    }

    bool is_Currency_Symbol(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Sc);
    }

    bool is_Bidi_Left_to_Right(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_L;
    }

    bool is_Bidi_European_Digit(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_EN;
    }

    bool is_Bidi_Eur_Num_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_ES;
    }

    bool is_Bidi_Eur_Num_Terminator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_ET;
    }

    bool is_Bidi_Arabic_Digit(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_AN;
    }

    bool is_Bidi_Common_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_CS;
    }

    bool is_Bidi_Block_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_B;
    }

    bool is_Bidi_Segment_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_S;
    }

    bool is_Bidi_Whitespace(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_WS;
    }

    bool is_Bidi_Non_spacing_Mark(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_NSM;
    }

    bool is_Bidi_Boundary_Neutral(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_BN;
    }

    bool is_Bidi_PDF(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_PDF;
    }

    bool is_Bidi_Embedding_or_Override(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_LRE ||
             bidir_props(uc) == BIDIR_RLE ||
             bidir_props(uc) == BIDIR_LRO ||
             bidir_props(uc) == BIDIR_RLO;
    }

    bool is_Bidi_LRE(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_LRE;
    }

    bool is_Bidi_RLE(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_RLE;
    }

    bool is_Bidi_LRO(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_LRO;
    }

    bool is_Bidi_RLO(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_RLO;
    }

    bool is_Bidi_Other_Neutral(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_ON;
    }

    bool is_Unassigned_Code_Value(const UCS4 uc) const {
      return !is_defined(uc) && !is_Not_a_Character(uc);
    }


  private:
    // functions
    Greek370(const Greek370 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[144];
    static const UCS4 _upper[144];
    static const UCS4 _lower[144];
    static const UCS4 _title[144];
    static const unsigned char _cat[144];
    static const unsigned char _bidir[144];
    static const unsigned char _decomp[144];
    static const UCS2 _decompStr[144][2];
    static const unsigned char _lb[144];
    static const unsigned char _ea[144];
    map<UCS4, UCS4> _composeMap;
    static const bool _Terminal_Punctuation[144];
    static const bool _Composite[144];
    static const bool _Alphabetic[144];
    static const bool _Diacritic[144];
    static const bool _Identifier_Part[144];

  }; // class Greek370

  const bool Greek370::_is_defined[] = {
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

  const UCS4 Greek370::_upper[] = {
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

  const UCS4 Greek370::_lower[] = {
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

  const UCS4 Greek370::_title[] = {
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

  const unsigned char Greek370::_cat[] = {
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

  const unsigned char Greek370::_bidir[] = {
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

  const unsigned char Greek370::_decomp[] = {
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

  const UCS2 Greek370::_decompStr[][2] = {
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

  const unsigned char Greek370::_lb[] = {
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

  const unsigned char Greek370::_ea[] = {
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

    const bool Greek370::_Terminal_Punctuation[] = {
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

    const bool Greek370::_Composite[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0, 
        1, 1, 1, 0, 1, 0, 1, 1, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Greek370::_Alphabetic[] = {
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

    const bool Greek370::_Diacritic[] = {
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

    const bool Greek370::_Identifier_Part[] = {
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

}; // namespace Babylon

dload(Babylon::Greek370);
