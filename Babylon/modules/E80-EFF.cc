/*$Id: E80-EFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:23:29 +0100.
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

  class LaoE80 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    LaoE80() {
      _first_letter = 0xE80;
      _last_letter  = 0xEFF;
      // _version="3.0.1" // Not yet supported!

    }


    ~LaoE80() {
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
      return "Lao";
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
      case 0x0ED0:
        return 0;
        break;
      case 0x0ED1:
        return 1;
        break;
      case 0x0ED2:
        return 2;
        break;
      case 0x0ED3:
        return 3;
        break;
      case 0x0ED4:
        return 4;
        break;
      case 0x0ED5:
        return 5;
        break;
      case 0x0ED6:
        return 6;
        break;
      case 0x0ED7:
        return 7;
        break;
      case 0x0ED8:
        return 8;
        break;
      case 0x0ED9:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x0ED0:
      case 0x0ED1:
      case 0x0ED2:
      case 0x0ED3:
      case 0x0ED4:
      case 0x0ED5:
      case 0x0ED6:
      case 0x0ED7:
      case 0x0ED8:
      case 0x0ED9:
        return 1;
      default:
        return 0;
      }
    }

    int digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x0ED0:
        return 0;
        break;
      case 0x0ED1:
        return 1;
        break;
      case 0x0ED2:
        return 2;
        break;
      case 0x0ED3:
        return 3;
        break;
      case 0x0ED4:
        return 4;
        break;
      case 0x0ED5:
        return 5;
        break;
      case 0x0ED6:
        return 6;
        break;
      case 0x0ED7:
        return 7;
        break;
      case 0x0ED8:
        return 8;
        break;
      case 0x0ED9:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x0ED0:
      case 0x0ED1:
      case 0x0ED2:
      case 0x0ED3:
      case 0x0ED4:
      case 0x0ED5:
      case 0x0ED6:
      case 0x0ED7:
      case 0x0ED8:
      case 0x0ED9:
        return 1;
      default:
        return 0;
      }
    }

    float numeric_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x0ED0:
        return 0.000000;
        break;
      case 0x0ED1:
        return 1.000000;
        break;
      case 0x0ED2:
        return 2.000000;
        break;
      case 0x0ED3:
        return 3.000000;
        break;
      case 0x0ED4:
        return 4.000000;
        break;
      case 0x0ED5:
        return 5.000000;
        break;
      case 0x0ED6:
        return 6.000000;
        break;
      case 0x0ED7:
        return 7.000000;
        break;
      case 0x0ED8:
        return 8.000000;
        break;
      case 0x0ED9:
        return 9.000000;
        break;
      default:
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x0ED0:
      case 0x0ED1:
      case 0x0ED2:
      case 0x0ED3:
      case 0x0ED4:
      case 0x0ED5:
      case 0x0ED6:
      case 0x0ED7:
      case 0x0ED8:
      case 0x0ED9:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(LaoE80::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Can_Comb_Class(LaoE80::_comb_cl[uc - _first_letter]);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(LaoE80::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(LaoE80::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = LaoE80::_decompStr[uc - _first_letter][0];
      us[1] = LaoE80::_decompStr[uc - _first_letter][1];
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
      return Babylon::Line_Break(LaoE80::_lb[uc - _first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(EA_WIDTH_N);
    }

    UCS4 compose (const UCS4 starter, const UCS4 last) {
      return 0;
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
      return LaoE80::_Combining[uc - _first_letter];
    }

    bool is_Non_spacing(const UCS4 uc) const {
      return LaoE80::_Non_spacing[uc - _first_letter];
    }

    bool is_Composite(const UCS4 uc) const {
      return LaoE80::_Composite[uc - _first_letter];
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return LaoE80::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return LaoE80::_Diacritic[uc - _first_letter];
    }

    bool is_Extender(const UCS4 uc) const {
      return LaoE80::_Extender[uc - _first_letter];
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return LaoE80::_Identifier_Part[uc - _first_letter];
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
    LaoE80(const LaoE80 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[128];
    static const unsigned char _cat[128];
    static const unsigned char _comb_cl[128];
    static const unsigned char _bidir[128];
    static const unsigned char _decomp[128];
    static const UCS2 _decompStr[128][2];
    static const unsigned char _lb[128];
    static const bool _Combining[128];
    static const bool _Non_spacing[128];
    static const bool _Composite[128];
    static const bool _Alphabetic[128];
    static const bool _Diacritic[128];
    static const bool _Extender[128];
    static const bool _Identifier_Part[128];

  }; // class LaoE80

  const bool LaoE80::_is_defined[] = {
    0, 1, 1, 0, 1, 0, 0, 1, 
    1, 0, 1, 0, 0, 1, 0, 0, 
    0, 0, 0, 0, 1, 1, 1, 1, 
    0, 1, 1, 1, 1, 1, 1, 1, 
    0, 1, 1, 1, 0, 1, 0, 1, 
    0, 0, 1, 1, 0, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 1, 1, 1, 0, 0, 
    1, 1, 1, 1, 1, 0, 1, 0, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 0, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char LaoE80::_cat[] = {
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lm, CAT_Lo, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo
  };

  const unsigned char LaoE80::_comb_cl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    118, 118, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    122, 122, 122, 122, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char LaoE80::_bidir[] = {
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
  };

  const unsigned char LaoE80::_decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 LaoE80::_decompStr[][2] = {
    { 0x0E80, 0x0000 }, { 0x0E81, 0x0000 }, { 0x0E82, 0x0000 }, { 0x0E83, 0x0000 }, 
    { 0x0E84, 0x0000 }, { 0x0E85, 0x0000 }, { 0x0E86, 0x0000 }, { 0x0E87, 0x0000 }, 
    { 0x0E88, 0x0000 }, { 0x0E89, 0x0000 }, { 0x0E8A, 0x0000 }, { 0x0E8B, 0x0000 }, 
    { 0x0E8C, 0x0000 }, { 0x0E8D, 0x0000 }, { 0x0E8E, 0x0000 }, { 0x0E8F, 0x0000 }, 
    { 0x0E90, 0x0000 }, { 0x0E91, 0x0000 }, { 0x0E92, 0x0000 }, { 0x0E93, 0x0000 }, 
    { 0x0E94, 0x0000 }, { 0x0E95, 0x0000 }, { 0x0E96, 0x0000 }, { 0x0E97, 0x0000 }, 
    { 0x0E98, 0x0000 }, { 0x0E99, 0x0000 }, { 0x0E9A, 0x0000 }, { 0x0E9B, 0x0000 }, 
    { 0x0E9C, 0x0000 }, { 0x0E9D, 0x0000 }, { 0x0E9E, 0x0000 }, { 0x0E9F, 0x0000 }, 
    { 0x0EA0, 0x0000 }, { 0x0EA1, 0x0000 }, { 0x0EA2, 0x0000 }, { 0x0EA3, 0x0000 }, 
    { 0x0EA4, 0x0000 }, { 0x0EA5, 0x0000 }, { 0x0EA6, 0x0000 }, { 0x0EA7, 0x0000 }, 
    { 0x0EA8, 0x0000 }, { 0x0EA9, 0x0000 }, { 0x0EAA, 0x0000 }, { 0x0EAB, 0x0000 }, 
    { 0x0EAC, 0x0000 }, { 0x0EAD, 0x0000 }, { 0x0EAE, 0x0000 }, { 0x0EAF, 0x0000 }, 
    { 0x0EB0, 0x0000 }, { 0x0EB1, 0x0000 }, { 0x0EB2, 0x0000 }, { 0x0ECD, 0x0EB2 }, 
    { 0x0EB4, 0x0000 }, { 0x0EB5, 0x0000 }, { 0x0EB6, 0x0000 }, { 0x0EB7, 0x0000 }, 
    { 0x0EB8, 0x0000 }, { 0x0EB9, 0x0000 }, { 0x0EBA, 0x0000 }, { 0x0EBB, 0x0000 }, 
    { 0x0EBC, 0x0000 }, { 0x0EBD, 0x0000 }, { 0x0EBE, 0x0000 }, { 0x0EBF, 0x0000 }, 
    { 0x0EC0, 0x0000 }, { 0x0EC1, 0x0000 }, { 0x0EC2, 0x0000 }, { 0x0EC3, 0x0000 }, 
    { 0x0EC4, 0x0000 }, { 0x0EC5, 0x0000 }, { 0x0EC6, 0x0000 }, { 0x0EC7, 0x0000 }, 
    { 0x0EC8, 0x0000 }, { 0x0EC9, 0x0000 }, { 0x0ECA, 0x0000 }, { 0x0ECB, 0x0000 }, 
    { 0x0ECC, 0x0000 }, { 0x0ECD, 0x0000 }, { 0x0ECE, 0x0000 }, { 0x0ECF, 0x0000 }, 
    { 0x0ED0, 0x0000 }, { 0x0ED1, 0x0000 }, { 0x0ED2, 0x0000 }, { 0x0ED3, 0x0000 }, 
    { 0x0ED4, 0x0000 }, { 0x0ED5, 0x0000 }, { 0x0ED6, 0x0000 }, { 0x0ED7, 0x0000 }, 
    { 0x0ED8, 0x0000 }, { 0x0ED9, 0x0000 }, { 0x0EDA, 0x0000 }, { 0x0EDB, 0x0000 }, 
    { 0x0EAB, 0x0E99 }, { 0x0EAB, 0x0EA1 }, { 0x0EDE, 0x0000 }, { 0x0EDF, 0x0000 }, 
    { 0x0EE0, 0x0000 }, { 0x0EE1, 0x0000 }, { 0x0EE2, 0x0000 }, { 0x0EE3, 0x0000 }, 
    { 0x0EE4, 0x0000 }, { 0x0EE5, 0x0000 }, { 0x0EE6, 0x0000 }, { 0x0EE7, 0x0000 }, 
    { 0x0EE8, 0x0000 }, { 0x0EE9, 0x0000 }, { 0x0EEA, 0x0000 }, { 0x0EEB, 0x0000 }, 
    { 0x0EEC, 0x0000 }, { 0x0EED, 0x0000 }, { 0x0EEE, 0x0000 }, { 0x0EEF, 0x0000 }, 
    { 0x0EF0, 0x0000 }, { 0x0EF1, 0x0000 }, { 0x0EF2, 0x0000 }, { 0x0EF3, 0x0000 }, 
    { 0x0EF4, 0x0000 }, { 0x0EF5, 0x0000 }, { 0x0EF6, 0x0000 }, { 0x0EF7, 0x0000 }, 
    { 0x0EF8, 0x0000 }, { 0x0EF9, 0x0000 }, { 0x0EFA, 0x0000 }, { 0x0EFB, 0x0000 }, 
    { 0x0EFC, 0x0000 }, { 0x0EFD, 0x0000 }, { 0x0EFE, 0x0000 }, { 0x0EFF, 0x0000 }
  };

  const unsigned char LaoE80::_lb[] = {
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_CM, LB_SA, LB_SA, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_SA, LB_CM, LB_CM, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_SA, LB_SA, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_NU, LB_NU, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
    LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA
  };

    const bool LaoE80::_Combining[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 0, 0, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::_Non_spacing[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 0, 0, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::_Composite[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::_Alphabetic[] = {
        0, 1, 1, 0, 1, 0, 0, 1, 
        1, 0, 1, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 1, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        0, 1, 1, 1, 0, 1, 0, 1, 
        0, 0, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::_Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::_Extender[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool LaoE80::_Identifier_Part[] = {
        0, 1, 1, 0, 1, 0, 0, 1, 
        1, 0, 1, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 1, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        0, 1, 1, 1, 0, 1, 0, 1, 
        0, 0, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 0, 1, 0, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon

dload(Babylon::LaoE80);
