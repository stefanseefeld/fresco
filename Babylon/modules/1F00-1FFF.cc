/*$Id: 1F00-1FFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:24:57 +0100.
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

  class Greek_Extended1F00 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Greek_Extended1F00() {
      _first_letter = 0x1F00;
      _last_letter  = 0x1FFF;
      // _version="3.0.1" // Not yet supported!
      _composeMap[0x1F000300] = 0x1F02;
      _composeMap[0x1F000301] = 0x1F04;
      _composeMap[0x1F000342] = 0x1F06;
      _composeMap[0x1F000345] = 0x1F80;
      _composeMap[0x1F010300] = 0x1F03;
      _composeMap[0x1F010301] = 0x1F05;
      _composeMap[0x1F010342] = 0x1F07;
      _composeMap[0x1F010345] = 0x1F81;
      _composeMap[0x1F020345] = 0x1F82;
      _composeMap[0x1F030345] = 0x1F83;
      _composeMap[0x1F040345] = 0x1F84;
      _composeMap[0x1F050345] = 0x1F85;
      _composeMap[0x1F060345] = 0x1F86;
      _composeMap[0x1F070345] = 0x1F87;
      _composeMap[0x1F080300] = 0x1F0A;
      _composeMap[0x1F080301] = 0x1F0C;
      _composeMap[0x1F080342] = 0x1F0E;
      _composeMap[0x1F080345] = 0x1F88;
      _composeMap[0x1F090300] = 0x1F0B;
      _composeMap[0x1F090301] = 0x1F0D;
      _composeMap[0x1F090342] = 0x1F0F;
      _composeMap[0x1F090345] = 0x1F89;
      _composeMap[0x1F0A0345] = 0x1F8A;
      _composeMap[0x1F0B0345] = 0x1F8B;
      _composeMap[0x1F0C0345] = 0x1F8C;
      _composeMap[0x1F0D0345] = 0x1F8D;
      _composeMap[0x1F0E0345] = 0x1F8E;
      _composeMap[0x1F0F0345] = 0x1F8F;
      _composeMap[0x1F100300] = 0x1F12;
      _composeMap[0x1F100301] = 0x1F14;
      _composeMap[0x1F110300] = 0x1F13;
      _composeMap[0x1F110301] = 0x1F15;
      _composeMap[0x1F180300] = 0x1F1A;
      _composeMap[0x1F180301] = 0x1F1C;
      _composeMap[0x1F190300] = 0x1F1B;
      _composeMap[0x1F190301] = 0x1F1D;
      _composeMap[0x1F200300] = 0x1F22;
      _composeMap[0x1F200301] = 0x1F24;
      _composeMap[0x1F200342] = 0x1F26;
      _composeMap[0x1F200345] = 0x1F90;
      _composeMap[0x1F210300] = 0x1F23;
      _composeMap[0x1F210301] = 0x1F25;
      _composeMap[0x1F210342] = 0x1F27;
      _composeMap[0x1F210345] = 0x1F91;
      _composeMap[0x1F220345] = 0x1F92;
      _composeMap[0x1F230345] = 0x1F93;
      _composeMap[0x1F240345] = 0x1F94;
      _composeMap[0x1F250345] = 0x1F95;
      _composeMap[0x1F260345] = 0x1F96;
      _composeMap[0x1F270345] = 0x1F97;
      _composeMap[0x1F280300] = 0x1F2A;
      _composeMap[0x1F280301] = 0x1F2C;
      _composeMap[0x1F280342] = 0x1F2E;
      _composeMap[0x1F280345] = 0x1F98;
      _composeMap[0x1F290300] = 0x1F2B;
      _composeMap[0x1F290301] = 0x1F2D;
      _composeMap[0x1F290342] = 0x1F2F;
      _composeMap[0x1F290345] = 0x1F99;
      _composeMap[0x1F2A0345] = 0x1F9A;
      _composeMap[0x1F2B0345] = 0x1F9B;
      _composeMap[0x1F2C0345] = 0x1F9C;
      _composeMap[0x1F2D0345] = 0x1F9D;
      _composeMap[0x1F2E0345] = 0x1F9E;
      _composeMap[0x1F2F0345] = 0x1F9F;
      _composeMap[0x1F300300] = 0x1F32;
      _composeMap[0x1F300301] = 0x1F34;
      _composeMap[0x1F300342] = 0x1F36;
      _composeMap[0x1F310300] = 0x1F33;
      _composeMap[0x1F310301] = 0x1F35;
      _composeMap[0x1F310342] = 0x1F37;
      _composeMap[0x1F380300] = 0x1F3A;
      _composeMap[0x1F380301] = 0x1F3C;
      _composeMap[0x1F380342] = 0x1F3E;
      _composeMap[0x1F390300] = 0x1F3B;
      _composeMap[0x1F390301] = 0x1F3D;
      _composeMap[0x1F390342] = 0x1F3F;
      _composeMap[0x1F400300] = 0x1F42;
      _composeMap[0x1F400301] = 0x1F44;
      _composeMap[0x1F410300] = 0x1F43;
      _composeMap[0x1F410301] = 0x1F45;
      _composeMap[0x1F480300] = 0x1F4A;
      _composeMap[0x1F480301] = 0x1F4C;
      _composeMap[0x1F490300] = 0x1F4B;
      _composeMap[0x1F490301] = 0x1F4D;
      _composeMap[0x1F500300] = 0x1F52;
      _composeMap[0x1F500301] = 0x1F54;
      _composeMap[0x1F500342] = 0x1F56;
      _composeMap[0x1F510300] = 0x1F53;
      _composeMap[0x1F510301] = 0x1F55;
      _composeMap[0x1F510342] = 0x1F57;
      _composeMap[0x1F590300] = 0x1F5B;
      _composeMap[0x1F590301] = 0x1F5D;
      _composeMap[0x1F590342] = 0x1F5F;
      _composeMap[0x1F600300] = 0x1F62;
      _composeMap[0x1F600301] = 0x1F64;
      _composeMap[0x1F600342] = 0x1F66;
      _composeMap[0x1F600345] = 0x1FA0;
      _composeMap[0x1F610300] = 0x1F63;
      _composeMap[0x1F610301] = 0x1F65;
      _composeMap[0x1F610342] = 0x1F67;
      _composeMap[0x1F610345] = 0x1FA1;
      _composeMap[0x1F620345] = 0x1FA2;
      _composeMap[0x1F630345] = 0x1FA3;
      _composeMap[0x1F640345] = 0x1FA4;
      _composeMap[0x1F650345] = 0x1FA5;
      _composeMap[0x1F660345] = 0x1FA6;
      _composeMap[0x1F670345] = 0x1FA7;
      _composeMap[0x1F680300] = 0x1F6A;
      _composeMap[0x1F680301] = 0x1F6C;
      _composeMap[0x1F680342] = 0x1F6E;
      _composeMap[0x1F680345] = 0x1FA8;
      _composeMap[0x1F690300] = 0x1F6B;
      _composeMap[0x1F690301] = 0x1F6D;
      _composeMap[0x1F690342] = 0x1F6F;
      _composeMap[0x1F690345] = 0x1FA9;
      _composeMap[0x1F6A0345] = 0x1FAA;
      _composeMap[0x1F6B0345] = 0x1FAB;
      _composeMap[0x1F6C0345] = 0x1FAC;
      _composeMap[0x1F6D0345] = 0x1FAD;
      _composeMap[0x1F6E0345] = 0x1FAE;
      _composeMap[0x1F6F0345] = 0x1FAF;
      _composeMap[0x1F700345] = 0x1FB2;
      _composeMap[0x1F740345] = 0x1FC2;
      _composeMap[0x1F7C0345] = 0x1FF2;
      _composeMap[0x1FB60345] = 0x1FB7;
      _composeMap[0x1FBF0300] = 0x1FCD;
      _composeMap[0x1FBF0301] = 0x1FCE;
      _composeMap[0x1FBF0342] = 0x1FCF;
      _composeMap[0x1FC60345] = 0x1FC7;
      _composeMap[0x1FF60345] = 0x1FF7;
      _composeMap[0x1FFE0300] = 0x1FDD;
      _composeMap[0x1FFE0301] = 0x1FDE;
      _composeMap[0x1FFE0342] = 0x1FDF;

    }


    ~Greek_Extended1F00() {
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
      return "Greek Extended";
    }

    bool is_defined(const UCS4 uc) const {
      return (_is_defined[uc - _first_letter]);
    }

    UCS4 uppercase(const UCS4 uc) const {
      return Greek_Extended1F00::_upper[uc - _first_letter];
    }

    bool is_Uppercase(const UCS4 uc) const {
      return category(uc) == CAT_Lu;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return Greek_Extended1F00::_lower[uc - _first_letter];
    }

    bool is_Lowercase(const UCS4 uc) const {
      return category(uc) == CAT_Ll;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return Greek_Extended1F00::_title[uc - _first_letter];
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
      return Babylon::Gen_Cat(Greek_Extended1F00::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Greek_Extended1F00::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Greek_Extended1F00::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Greek_Extended1F00::_decompStr[uc - _first_letter][0];
      us[1] = Greek_Extended1F00::_decompStr[uc - _first_letter][1];
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
      return Babylon::Line_Break(LB_AL);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(EA_WIDTH_N);
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
      return 0;
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
      return Greek_Extended1F00::_Composite[uc - _first_letter];
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Greek_Extended1F00::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return Greek_Extended1F00::_Diacritic[uc - _first_letter];
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Greek_Extended1F00::_Identifier_Part[uc - _first_letter];
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
    Greek_Extended1F00(const Greek_Extended1F00 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[256];
    static const UCS4 _upper[256];
    static const UCS4 _lower[256];
    static const UCS4 _title[256];
    static const unsigned char _cat[256];
    static const unsigned char _bidir[256];
    static const unsigned char _decomp[256];
    static const UCS2 _decompStr[256][2];
    map<UCS4, UCS4> _composeMap;
    static const bool _Composite[256];
    static const bool _Alphabetic[256];
    static const bool _Diacritic[256];
    static const bool _Identifier_Part[256];

  }; // class Greek_Extended1F00

  const bool Greek_Extended1F00::_is_defined[] = {
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

  const UCS4 Greek_Extended1F00::_upper[] = {
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

  const UCS4 Greek_Extended1F00::_lower[] = {
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

  const UCS4 Greek_Extended1F00::_title[] = {
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

  const unsigned char Greek_Extended1F00::_cat[] = {
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

  const unsigned char Greek_Extended1F00::_bidir[] = {
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

  const unsigned char Greek_Extended1F00::_decomp[] = {
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

  const UCS2 Greek_Extended1F00::_decompStr[][2] = {
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

    const bool Greek_Extended1F00::_Composite[] = {
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
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 1, 1, 1, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 1, 1, 
        1, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0, 
        0, 0, 1, 1, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0
    };

    const bool Greek_Extended1F00::_Alphabetic[] = {
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

    const bool Greek_Extended1F00::_Diacritic[] = {
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

    const bool Greek_Extended1F00::_Identifier_Part[] = {
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

}; // namespace Babylon

dload(Babylon::Greek_Extended1F00);
