/*$Id: 600-6FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:22:25 +0100.
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

  class Arabic600 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Arabic600() {
      _first_letter = 0x600;
      _last_letter  = 0x6FF;
      // _version="3.0.1" // Not yet supported!
      _composeMap[0x06270653] = 0x0622;
      _composeMap[0x06270654] = 0x0623;
      _composeMap[0x06270655] = 0x0625;
      _composeMap[0x06480654] = 0x0624;
      _composeMap[0x064A0654] = 0x0626;
      _composeMap[0x06C10654] = 0x06C2;
      _composeMap[0x06D20654] = 0x06D3;
      _composeMap[0x06D50654] = 0x06C0;

    }


    ~Arabic600() {
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
      return "Arabic";
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
      case 0x0660:
        return 0;
        break;
      case 0x0661:
        return 1;
        break;
      case 0x0662:
        return 2;
        break;
      case 0x0663:
        return 3;
        break;
      case 0x0664:
        return 4;
        break;
      case 0x0665:
        return 5;
        break;
      case 0x0666:
        return 6;
        break;
      case 0x0667:
        return 7;
        break;
      case 0x0668:
        return 8;
        break;
      case 0x0669:
        return 9;
        break;
      case 0x06F0:
        return 0;
        break;
      case 0x06F1:
        return 1;
        break;
      case 0x06F2:
        return 2;
        break;
      case 0x06F3:
        return 3;
        break;
      case 0x06F4:
        return 4;
        break;
      case 0x06F5:
        return 5;
        break;
      case 0x06F6:
        return 6;
        break;
      case 0x06F7:
        return 7;
        break;
      case 0x06F8:
        return 8;
        break;
      case 0x06F9:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x0660:
      case 0x0661:
      case 0x0662:
      case 0x0663:
      case 0x0664:
      case 0x0665:
      case 0x0666:
      case 0x0667:
      case 0x0668:
      case 0x0669:
      case 0x06F0:
      case 0x06F1:
      case 0x06F2:
      case 0x06F3:
      case 0x06F4:
      case 0x06F5:
      case 0x06F6:
      case 0x06F7:
      case 0x06F8:
      case 0x06F9:
        return 1;
      default:
        return 0;
      }
    }

    int digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x0660:
        return 0;
        break;
      case 0x0661:
        return 1;
        break;
      case 0x0662:
        return 2;
        break;
      case 0x0663:
        return 3;
        break;
      case 0x0664:
        return 4;
        break;
      case 0x0665:
        return 5;
        break;
      case 0x0666:
        return 6;
        break;
      case 0x0667:
        return 7;
        break;
      case 0x0668:
        return 8;
        break;
      case 0x0669:
        return 9;
        break;
      case 0x06F0:
        return 0;
        break;
      case 0x06F1:
        return 1;
        break;
      case 0x06F2:
        return 2;
        break;
      case 0x06F3:
        return 3;
        break;
      case 0x06F4:
        return 4;
        break;
      case 0x06F5:
        return 5;
        break;
      case 0x06F6:
        return 6;
        break;
      case 0x06F7:
        return 7;
        break;
      case 0x06F8:
        return 8;
        break;
      case 0x06F9:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x0660:
      case 0x0661:
      case 0x0662:
      case 0x0663:
      case 0x0664:
      case 0x0665:
      case 0x0666:
      case 0x0667:
      case 0x0668:
      case 0x0669:
      case 0x06F0:
      case 0x06F1:
      case 0x06F2:
      case 0x06F3:
      case 0x06F4:
      case 0x06F5:
      case 0x06F6:
      case 0x06F7:
      case 0x06F8:
      case 0x06F9:
        return 1;
      default:
        return 0;
      }
    }

    float numeric_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x0660:
        return 0.000000;
        break;
      case 0x0661:
        return 1.000000;
        break;
      case 0x0662:
        return 2.000000;
        break;
      case 0x0663:
        return 3.000000;
        break;
      case 0x0664:
        return 4.000000;
        break;
      case 0x0665:
        return 5.000000;
        break;
      case 0x0666:
        return 6.000000;
        break;
      case 0x0667:
        return 7.000000;
        break;
      case 0x0668:
        return 8.000000;
        break;
      case 0x0669:
        return 9.000000;
        break;
      case 0x06F0:
        return 0.000000;
        break;
      case 0x06F1:
        return 1.000000;
        break;
      case 0x06F2:
        return 2.000000;
        break;
      case 0x06F3:
        return 3.000000;
        break;
      case 0x06F4:
        return 4.000000;
        break;
      case 0x06F5:
        return 5.000000;
        break;
      case 0x06F6:
        return 6.000000;
        break;
      case 0x06F7:
        return 7.000000;
        break;
      case 0x06F8:
        return 8.000000;
        break;
      case 0x06F9:
        return 9.000000;
        break;
      default:
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x0660:
      case 0x0661:
      case 0x0662:
      case 0x0663:
      case 0x0664:
      case 0x0665:
      case 0x0666:
      case 0x0667:
      case 0x0668:
      case 0x0669:
      case 0x06F0:
      case 0x06F1:
      case 0x06F2:
      case 0x06F3:
      case 0x06F4:
      case 0x06F5:
      case 0x06F6:
      case 0x06F7:
      case 0x06F8:
      case 0x06F9:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Arabic600::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Can_Comb_Class(Arabic600::_comb_cl[uc - _first_letter]);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Arabic600::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Arabic600::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Arabic600::_decompStr[uc - _first_letter][0];
      us[1] = Arabic600::_decompStr[uc - _first_letter][1];
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
      return Babylon::Line_Break(Arabic600::_lb[uc - _first_letter]);
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
      return Arabic600::_Terminal_Punctuation[uc - _first_letter];
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
      return Arabic600::_Combining[uc - _first_letter];
    }

    bool is_Non_spacing(const UCS4 uc) const {
      return Arabic600::_Non_spacing[uc - _first_letter];
    }

    bool is_Composite(const UCS4 uc) const {
      return Arabic600::_Composite[uc - _first_letter];
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Arabic600::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return Arabic600::_Diacritic[uc - _first_letter];
    }

    bool is_Extender(const UCS4 uc) const {
      return Arabic600::_Extender[uc - _first_letter];
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Arabic600::_Identifier_Part[uc - _first_letter];
    }

    bool is_Ignorable_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const UCS4 uc) const {
      return Arabic600::_Bidi_Arabic_Right_to_Left[uc - _first_letter];
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
    Arabic600(const Arabic600 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[256];
    static const unsigned char _cat[256];
    static const unsigned char _comb_cl[256];
    static const unsigned char _bidir[256];
    static const unsigned char _decomp[256];
    static const UCS2 _decompStr[256][2];
    static const unsigned char _lb[256];
    map<UCS4, UCS4> _composeMap;
    static const bool _Terminal_Punctuation[256];
    static const bool _Combining[256];
    static const bool _Non_spacing[256];
    static const bool _Composite[256];
    static const bool _Alphabetic[256];
    static const bool _Diacritic[256];
    static const bool _Extender[256];
    static const bool _Identifier_Part[256];
    static const bool _Bidi_Arabic_Right_to_Left[256];

  }; // class Arabic600

  const bool Arabic600::_is_defined[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 1, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 1, 0, 0, 0, 1, 
    0, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 0, 0, 
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
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0
  };

  const unsigned char Arabic600::_cat[] = {
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Po, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Lm, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Po, CAT_Po, 
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Po, CAT_Lo, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Me, CAT_Me, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lm, CAT_Lm, CAT_Mn, 
    CAT_Mn, CAT_So, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Po, CAT_Po, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Lo, CAT_Lo, CAT_Lo, CAT_So, CAT_So, CAT_Po
  };

  const unsigned char Arabic600::_comb_cl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 27, 28, 29, 30, 31, 
    32, 33, 34, 230, 230, 220, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    35, 0, 0, 0, 0, 0, 0, 0, 
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
    0, 0, 0, 0, 0, 0, 230, 230, 
    230, 230, 230, 230, 230, 0, 0, 230, 
    230, 230, 230, 220, 230, 0, 0, 230, 
    230, 0, 220, 230, 230, 220, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Arabic600::_bidir[] = {
    BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, 
    BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, 
    BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, 
    BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_AL, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_AL, 
    BIDIR_CS, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_CS, BIDIR_CS, 
    BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS, 
    BIDIR_AN, BIDIR_AN, BIDIR_AN, BIDIR_AN, BIDIR_AN, BIDIR_AN, BIDIR_AN, BIDIR_AN, 
    BIDIR_AN, BIDIR_AN, BIDIR_ET, BIDIR_AN, BIDIR_AN, BIDIR_AL, BIDIR_CS, BIDIR_CS, 
    BIDIR_NSM, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_AL, BIDIR_AL, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_ON, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_CS, BIDIR_CS, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_CS
  };

  const unsigned char Arabic600::_decomp[] = {
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
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
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
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Arabic600::_decompStr[][2] = {
    { 0x0600, 0x0000 }, { 0x0601, 0x0000 }, { 0x0602, 0x0000 }, { 0x0603, 0x0000 }, 
    { 0x0604, 0x0000 }, { 0x0605, 0x0000 }, { 0x0606, 0x0000 }, { 0x0607, 0x0000 }, 
    { 0x0608, 0x0000 }, { 0x0609, 0x0000 }, { 0x060A, 0x0000 }, { 0x060B, 0x0000 }, 
    { 0x060C, 0x0000 }, { 0x060D, 0x0000 }, { 0x060E, 0x0000 }, { 0x060F, 0x0000 }, 
    { 0x0610, 0x0000 }, { 0x0611, 0x0000 }, { 0x0612, 0x0000 }, { 0x0613, 0x0000 }, 
    { 0x0614, 0x0000 }, { 0x0615, 0x0000 }, { 0x0616, 0x0000 }, { 0x0617, 0x0000 }, 
    { 0x0618, 0x0000 }, { 0x0619, 0x0000 }, { 0x061A, 0x0000 }, { 0x061B, 0x0000 }, 
    { 0x061C, 0x0000 }, { 0x061D, 0x0000 }, { 0x061E, 0x0000 }, { 0x061F, 0x0000 }, 
    { 0x0620, 0x0000 }, { 0x0621, 0x0000 }, { 0x0627, 0x0653 }, { 0x0627, 0x0654 }, 
    { 0x0648, 0x0654 }, { 0x0627, 0x0655 }, { 0x064A, 0x0654 }, { 0x0627, 0x0000 }, 
    { 0x0628, 0x0000 }, { 0x0629, 0x0000 }, { 0x062A, 0x0000 }, { 0x062B, 0x0000 }, 
    { 0x062C, 0x0000 }, { 0x062D, 0x0000 }, { 0x062E, 0x0000 }, { 0x062F, 0x0000 }, 
    { 0x0630, 0x0000 }, { 0x0631, 0x0000 }, { 0x0632, 0x0000 }, { 0x0633, 0x0000 }, 
    { 0x0634, 0x0000 }, { 0x0635, 0x0000 }, { 0x0636, 0x0000 }, { 0x0637, 0x0000 }, 
    { 0x0638, 0x0000 }, { 0x0639, 0x0000 }, { 0x063A, 0x0000 }, { 0x063B, 0x0000 }, 
    { 0x063C, 0x0000 }, { 0x063D, 0x0000 }, { 0x063E, 0x0000 }, { 0x063F, 0x0000 }, 
    { 0x0640, 0x0000 }, { 0x0641, 0x0000 }, { 0x0642, 0x0000 }, { 0x0643, 0x0000 }, 
    { 0x0644, 0x0000 }, { 0x0645, 0x0000 }, { 0x0646, 0x0000 }, { 0x0647, 0x0000 }, 
    { 0x0648, 0x0000 }, { 0x0649, 0x0000 }, { 0x064A, 0x0000 }, { 0x064B, 0x0000 }, 
    { 0x064C, 0x0000 }, { 0x064D, 0x0000 }, { 0x064E, 0x0000 }, { 0x064F, 0x0000 }, 
    { 0x0650, 0x0000 }, { 0x0651, 0x0000 }, { 0x0652, 0x0000 }, { 0x0653, 0x0000 }, 
    { 0x0654, 0x0000 }, { 0x0655, 0x0000 }, { 0x0656, 0x0000 }, { 0x0657, 0x0000 }, 
    { 0x0658, 0x0000 }, { 0x0659, 0x0000 }, { 0x065A, 0x0000 }, { 0x065B, 0x0000 }, 
    { 0x065C, 0x0000 }, { 0x065D, 0x0000 }, { 0x065E, 0x0000 }, { 0x065F, 0x0000 }, 
    { 0x0660, 0x0000 }, { 0x0661, 0x0000 }, { 0x0662, 0x0000 }, { 0x0663, 0x0000 }, 
    { 0x0664, 0x0000 }, { 0x0665, 0x0000 }, { 0x0666, 0x0000 }, { 0x0667, 0x0000 }, 
    { 0x0668, 0x0000 }, { 0x0669, 0x0000 }, { 0x066A, 0x0000 }, { 0x066B, 0x0000 }, 
    { 0x066C, 0x0000 }, { 0x066D, 0x0000 }, { 0x066E, 0x0000 }, { 0x066F, 0x0000 }, 
    { 0x0670, 0x0000 }, { 0x0671, 0x0000 }, { 0x0672, 0x0000 }, { 0x0673, 0x0000 }, 
    { 0x0674, 0x0000 }, { 0x0627, 0x0674 }, { 0x0648, 0x0674 }, { 0x06C7, 0x0674 }, 
    { 0x064A, 0x0674 }, { 0x0679, 0x0000 }, { 0x067A, 0x0000 }, { 0x067B, 0x0000 }, 
    { 0x067C, 0x0000 }, { 0x067D, 0x0000 }, { 0x067E, 0x0000 }, { 0x067F, 0x0000 }, 
    { 0x0680, 0x0000 }, { 0x0681, 0x0000 }, { 0x0682, 0x0000 }, { 0x0683, 0x0000 }, 
    { 0x0684, 0x0000 }, { 0x0685, 0x0000 }, { 0x0686, 0x0000 }, { 0x0687, 0x0000 }, 
    { 0x0688, 0x0000 }, { 0x0689, 0x0000 }, { 0x068A, 0x0000 }, { 0x068B, 0x0000 }, 
    { 0x068C, 0x0000 }, { 0x068D, 0x0000 }, { 0x068E, 0x0000 }, { 0x068F, 0x0000 }, 
    { 0x0690, 0x0000 }, { 0x0691, 0x0000 }, { 0x0692, 0x0000 }, { 0x0693, 0x0000 }, 
    { 0x0694, 0x0000 }, { 0x0695, 0x0000 }, { 0x0696, 0x0000 }, { 0x0697, 0x0000 }, 
    { 0x0698, 0x0000 }, { 0x0699, 0x0000 }, { 0x069A, 0x0000 }, { 0x069B, 0x0000 }, 
    { 0x069C, 0x0000 }, { 0x069D, 0x0000 }, { 0x069E, 0x0000 }, { 0x069F, 0x0000 }, 
    { 0x06A0, 0x0000 }, { 0x06A1, 0x0000 }, { 0x06A2, 0x0000 }, { 0x06A3, 0x0000 }, 
    { 0x06A4, 0x0000 }, { 0x06A5, 0x0000 }, { 0x06A6, 0x0000 }, { 0x06A7, 0x0000 }, 
    { 0x06A8, 0x0000 }, { 0x06A9, 0x0000 }, { 0x06AA, 0x0000 }, { 0x06AB, 0x0000 }, 
    { 0x06AC, 0x0000 }, { 0x06AD, 0x0000 }, { 0x06AE, 0x0000 }, { 0x06AF, 0x0000 }, 
    { 0x06B0, 0x0000 }, { 0x06B1, 0x0000 }, { 0x06B2, 0x0000 }, { 0x06B3, 0x0000 }, 
    { 0x06B4, 0x0000 }, { 0x06B5, 0x0000 }, { 0x06B6, 0x0000 }, { 0x06B7, 0x0000 }, 
    { 0x06B8, 0x0000 }, { 0x06B9, 0x0000 }, { 0x06BA, 0x0000 }, { 0x06BB, 0x0000 }, 
    { 0x06BC, 0x0000 }, { 0x06BD, 0x0000 }, { 0x06BE, 0x0000 }, { 0x06BF, 0x0000 }, 
    { 0x06D5, 0x0654 }, { 0x06C1, 0x0000 }, { 0x06C1, 0x0654 }, { 0x06C3, 0x0000 }, 
    { 0x06C4, 0x0000 }, { 0x06C5, 0x0000 }, { 0x06C6, 0x0000 }, { 0x06C7, 0x0000 }, 
    { 0x06C8, 0x0000 }, { 0x06C9, 0x0000 }, { 0x06CA, 0x0000 }, { 0x06CB, 0x0000 }, 
    { 0x06CC, 0x0000 }, { 0x06CD, 0x0000 }, { 0x06CE, 0x0000 }, { 0x06CF, 0x0000 }, 
    { 0x06D0, 0x0000 }, { 0x06D1, 0x0000 }, { 0x06D2, 0x0000 }, { 0x06D2, 0x0654 }, 
    { 0x06D4, 0x0000 }, { 0x06D5, 0x0000 }, { 0x06D6, 0x0000 }, { 0x06D7, 0x0000 }, 
    { 0x06D8, 0x0000 }, { 0x06D9, 0x0000 }, { 0x06DA, 0x0000 }, { 0x06DB, 0x0000 }, 
    { 0x06DC, 0x0000 }, { 0x06DD, 0x0000 }, { 0x06DE, 0x0000 }, { 0x06DF, 0x0000 }, 
    { 0x06E0, 0x0000 }, { 0x06E1, 0x0000 }, { 0x06E2, 0x0000 }, { 0x06E3, 0x0000 }, 
    { 0x06E4, 0x0000 }, { 0x06E5, 0x0000 }, { 0x06E6, 0x0000 }, { 0x06E7, 0x0000 }, 
    { 0x06E8, 0x0000 }, { 0x06E9, 0x0000 }, { 0x06EA, 0x0000 }, { 0x06EB, 0x0000 }, 
    { 0x06EC, 0x0000 }, { 0x06ED, 0x0000 }, { 0x06EE, 0x0000 }, { 0x06EF, 0x0000 }, 
    { 0x06F0, 0x0000 }, { 0x06F1, 0x0000 }, { 0x06F2, 0x0000 }, { 0x06F3, 0x0000 }, 
    { 0x06F4, 0x0000 }, { 0x06F5, 0x0000 }, { 0x06F6, 0x0000 }, { 0x06F7, 0x0000 }, 
    { 0x06F8, 0x0000 }, { 0x06F9, 0x0000 }, { 0x06FA, 0x0000 }, { 0x06FB, 0x0000 }, 
    { 0x06FC, 0x0000 }, { 0x06FD, 0x0000 }, { 0x06FE, 0x0000 }, { 0x06FF, 0x0000 }
  };

  const unsigned char Arabic600::_lb[] = {
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_NU, LB_NU, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_CM, 
    LB_CM, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_NU, LB_NU, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
  };

    const bool Arabic600::_Terminal_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 1, 
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
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Arabic600::_Combining[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Arabic600::_Non_spacing[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 0, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Arabic600::_Composite[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 0, 
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
        1, 0, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Arabic600::_Alphabetic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
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
        1, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 0, 0, 0
    };

    const bool Arabic600::_Diacritic[] = {
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
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        1, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Arabic600::_Extender[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Arabic600::_Identifier_Part[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
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
        1, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0
    };

    const bool Arabic600::_Bidi_Arabic_Right_to_Left[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 1, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 1, 
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
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 0
    };

}; // namespace Babylon

dload(Babylon::Arabic600);
