/*$Id: 980-9FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:22:44 +0100.
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

  class Bengali980 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Bengali980() {
      _first_letter = 0x980;
      _last_letter  = 0x9FF;
      // _version="3.0.1" // Not yet supported!
      _composeMap[0x09A109BC] = 0x09DC;
      _composeMap[0x09A209BC] = 0x09DD;
      _composeMap[0x09AF09BC] = 0x09DF;
      _composeMap[0x09C709BE] = 0x09CB;
      _composeMap[0x09C709D7] = 0x09CC;

    }


    ~Bengali980() {
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
      return "Bengali";
    }

    bool is_defined(const UCS4 uc) const {
      return (_is_defined[uc - _first_letter]);
    }

    UCS4 uppercase(const UCS4 uc) const {
      return uc;
    }

    bool is_Uppercase(const UCS4 uc) const {
      return category(uc) == CAT_Lu;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return uc;
    }

    bool is_Lowercase(const UCS4 uc) const {
      return category(uc) == CAT_Ll;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return uc;
    }

    bool is_Titlecase(const UCS4 uc) const {
      return category(uc) == CAT_Lt;
    }

    int dec_digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x09E6:
        return 0;
        break;
      case 0x09E7:
        return 1;
        break;
      case 0x09E8:
        return 2;
        break;
      case 0x09E9:
        return 3;
        break;
      case 0x09EA:
        return 4;
        break;
      case 0x09EB:
        return 5;
        break;
      case 0x09EC:
        return 6;
        break;
      case 0x09ED:
        return 7;
        break;
      case 0x09EE:
        return 8;
        break;
      case 0x09EF:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x09E6:
      case 0x09E7:
      case 0x09E8:
      case 0x09E9:
      case 0x09EA:
      case 0x09EB:
      case 0x09EC:
      case 0x09ED:
      case 0x09EE:
      case 0x09EF:
        return 1;
      default:
        return 0;
      }
    }

    int digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x09E6:
        return 0;
        break;
      case 0x09E7:
        return 1;
        break;
      case 0x09E8:
        return 2;
        break;
      case 0x09E9:
        return 3;
        break;
      case 0x09EA:
        return 4;
        break;
      case 0x09EB:
        return 5;
        break;
      case 0x09EC:
        return 6;
        break;
      case 0x09ED:
        return 7;
        break;
      case 0x09EE:
        return 8;
        break;
      case 0x09EF:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x09E6:
      case 0x09E7:
      case 0x09E8:
      case 0x09E9:
      case 0x09EA:
      case 0x09EB:
      case 0x09EC:
      case 0x09ED:
      case 0x09EE:
      case 0x09EF:
        return 1;
      default:
        return 0;
      }
    }

    float numeric_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x09E6:
        return 0.000000;
        break;
      case 0x09E7:
        return 1.000000;
        break;
      case 0x09E8:
        return 2.000000;
        break;
      case 0x09E9:
        return 3.000000;
        break;
      case 0x09EA:
        return 4.000000;
        break;
      case 0x09EB:
        return 5.000000;
        break;
      case 0x09EC:
        return 6.000000;
        break;
      case 0x09ED:
        return 7.000000;
        break;
      case 0x09EE:
        return 8.000000;
        break;
      case 0x09EF:
        return 9.000000;
        break;
      case 0x09F4:
        return 1.000000;
        break;
      case 0x09F5:
        return 2.000000;
        break;
      case 0x09F6:
        return 3.000000;
        break;
      case 0x09F7:
        return 4.000000;
        break;
      case 0x09F9:
        return 16.000000;
        break;
      default:
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x09E6:
      case 0x09E7:
      case 0x09E8:
      case 0x09E9:
      case 0x09EA:
      case 0x09EB:
      case 0x09EC:
      case 0x09ED:
      case 0x09EE:
      case 0x09EF:
      case 0x09F4:
      case 0x09F5:
      case 0x09F6:
      case 0x09F7:
      case 0x09F9:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Bengali980::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Can_Comb_Class(Bengali980::_comb_cl[uc - _first_letter]);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Bengali980::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Bengali980::_decompStr[uc - _first_letter][0];
      us[1] = Bengali980::_decompStr[uc - _first_letter][1];
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
      return Babylon::Line_Break(Bengali980::_lb[uc - _first_letter]);
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
      return Bengali980::_Combining[uc - _first_letter];
    }

    bool is_Non_spacing(const UCS4 uc) const {
      return Bengali980::_Non_spacing[uc - _first_letter];
    }

    bool is_Composite(const UCS4 uc) const {
      return Bengali980::_Composite[uc - _first_letter];
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Bengali980::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return Bengali980::_Diacritic[uc - _first_letter];
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Bengali980::_Identifier_Part[uc - _first_letter];
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
    Bengali980(const Bengali980 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[128];
    static const unsigned char _cat[128];
    static const unsigned char _comb_cl[128];
    static const unsigned char _bidir[128];
    static const UCS2 _decompStr[128][2];
    static const unsigned char _lb[128];
    map<UCS4, UCS4> _composeMap;
    static const bool _Combining[128];
    static const bool _Non_spacing[128];
    static const bool _Composite[128];
    static const bool _Alphabetic[128];
    static const bool _Diacritic[128];
    static const bool _Identifier_Part[128];

  }; // class Bengali980

  const bool Bengali980::_is_defined[] = {
    0, 1, 1, 1, 0, 1, 1, 1, 
    1, 1, 1, 1, 1, 0, 0, 1, 
    1, 0, 0, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 0, 1, 1, 1, 1, 1, 1, 
    1, 0, 1, 0, 0, 0, 1, 1, 
    1, 1, 0, 0, 1, 0, 1, 1, 
    1, 1, 1, 1, 1, 0, 0, 1, 
    1, 0, 0, 1, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 1, 1, 0, 1, 
    1, 1, 1, 1, 0, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0
  };

  const unsigned char Bengali980::_cat[] = {
    CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
    CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Lo, CAT_Lo, CAT_Sc, CAT_Sc, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_So, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
  };

  const unsigned char Bengali980::_comb_cl[] = {
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

  const unsigned char Bengali980::_bidir[] = {
    BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_ET, BIDIR_ET, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM
  };

  const UCS2 Bengali980::_decompStr[][2] = {
    { 0x0980, 0x0000 }, { 0x0981, 0x0000 }, { 0x0982, 0x0000 }, { 0x0983, 0x0000 }, 
    { 0x0984, 0x0000 }, { 0x0985, 0x0000 }, { 0x0986, 0x0000 }, { 0x0987, 0x0000 }, 
    { 0x0988, 0x0000 }, { 0x0989, 0x0000 }, { 0x098A, 0x0000 }, { 0x098B, 0x0000 }, 
    { 0x098C, 0x0000 }, { 0x098D, 0x0000 }, { 0x098E, 0x0000 }, { 0x098F, 0x0000 }, 
    { 0x0990, 0x0000 }, { 0x0991, 0x0000 }, { 0x0992, 0x0000 }, { 0x0993, 0x0000 }, 
    { 0x0994, 0x0000 }, { 0x0995, 0x0000 }, { 0x0996, 0x0000 }, { 0x0997, 0x0000 }, 
    { 0x0998, 0x0000 }, { 0x0999, 0x0000 }, { 0x099A, 0x0000 }, { 0x099B, 0x0000 }, 
    { 0x099C, 0x0000 }, { 0x099D, 0x0000 }, { 0x099E, 0x0000 }, { 0x099F, 0x0000 }, 
    { 0x09A0, 0x0000 }, { 0x09A1, 0x0000 }, { 0x09A2, 0x0000 }, { 0x09A3, 0x0000 }, 
    { 0x09A4, 0x0000 }, { 0x09A5, 0x0000 }, { 0x09A6, 0x0000 }, { 0x09A7, 0x0000 }, 
    { 0x09A8, 0x0000 }, { 0x09A9, 0x0000 }, { 0x09AA, 0x0000 }, { 0x09AB, 0x0000 }, 
    { 0x09AC, 0x0000 }, { 0x09AD, 0x0000 }, { 0x09AE, 0x0000 }, { 0x09AF, 0x0000 }, 
    { 0x09B0, 0x0000 }, { 0x09B1, 0x0000 }, { 0x09B2, 0x0000 }, { 0x09B3, 0x0000 }, 
    { 0x09B4, 0x0000 }, { 0x09B5, 0x0000 }, { 0x09B6, 0x0000 }, { 0x09B7, 0x0000 }, 
    { 0x09B8, 0x0000 }, { 0x09B9, 0x0000 }, { 0x09BA, 0x0000 }, { 0x09BB, 0x0000 }, 
    { 0x09BC, 0x0000 }, { 0x09BD, 0x0000 }, { 0x09BE, 0x0000 }, { 0x09BF, 0x0000 }, 
    { 0x09C0, 0x0000 }, { 0x09C1, 0x0000 }, { 0x09C2, 0x0000 }, { 0x09C3, 0x0000 }, 
    { 0x09C4, 0x0000 }, { 0x09C5, 0x0000 }, { 0x09C6, 0x0000 }, { 0x09C7, 0x0000 }, 
    { 0x09C8, 0x0000 }, { 0x09C9, 0x0000 }, { 0x09CA, 0x0000 }, { 0x09C7, 0x09BE }, 
    { 0x09C7, 0x09D7 }, { 0x09CD, 0x0000 }, { 0x09CE, 0x0000 }, { 0x09CF, 0x0000 }, 
    { 0x09D0, 0x0000 }, { 0x09D1, 0x0000 }, { 0x09D2, 0x0000 }, { 0x09D3, 0x0000 }, 
    { 0x09D4, 0x0000 }, { 0x09D5, 0x0000 }, { 0x09D6, 0x0000 }, { 0x09D7, 0x0000 }, 
    { 0x09D8, 0x0000 }, { 0x09D9, 0x0000 }, { 0x09DA, 0x0000 }, { 0x09DB, 0x0000 }, 
    { 0x09A1, 0x09BC }, { 0x09A2, 0x09BC }, { 0x09DE, 0x0000 }, { 0x09AF, 0x09BC }, 
    { 0x09E0, 0x0000 }, { 0x09E1, 0x0000 }, { 0x09E2, 0x0000 }, { 0x09E3, 0x0000 }, 
    { 0x09E4, 0x0000 }, { 0x09E5, 0x0000 }, { 0x09E6, 0x0000 }, { 0x09E7, 0x0000 }, 
    { 0x09E8, 0x0000 }, { 0x09E9, 0x0000 }, { 0x09EA, 0x0000 }, { 0x09EB, 0x0000 }, 
    { 0x09EC, 0x0000 }, { 0x09ED, 0x0000 }, { 0x09EE, 0x0000 }, { 0x09EF, 0x0000 }, 
    { 0x09F0, 0x0000 }, { 0x09F1, 0x0000 }, { 0x09F2, 0x0000 }, { 0x09F3, 0x0000 }, 
    { 0x09F4, 0x0000 }, { 0x09F5, 0x0000 }, { 0x09F6, 0x0000 }, { 0x09F7, 0x0000 }, 
    { 0x09F8, 0x0000 }, { 0x09F9, 0x0000 }, { 0x09FA, 0x0000 }, { 0x09FB, 0x0000 }, 
    { 0x09FC, 0x0000 }, { 0x09FD, 0x0000 }, { 0x09FE, 0x0000 }, { 0x09FF, 0x0000 }
  };

  const unsigned char Bengali980::_lb[] = {
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_AL, 
    LB_AL, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_CM, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_CM, LB_AL, 
    LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, LB_NU, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_AL, LB_AL, LB_PR, LB_PR, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
  };

    const bool Bengali980::_Combining[] = {
        0, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Bengali980::_Non_spacing[] = {
        0, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Bengali980::_Composite[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Bengali980::_Alphabetic[] = {
        0, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 0, 0, 0, 1, 1, 
        1, 1, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 0, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 1, 1, 0, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Bengali980::_Diacritic[] = {
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

    const bool Bengali980::_Identifier_Part[] = {
        0, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 0, 0, 0, 1, 1, 
        1, 1, 0, 0, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 0, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 1, 1, 0, 1, 
        1, 1, 1, 1, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon

dload(Babylon::Bengali980);
