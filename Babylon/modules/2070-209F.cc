/*$Id: 2070-209F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:25:10 +0100.
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

  class Superscripts_and_Subscripts2070 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Superscripts_and_Subscripts2070() {
      _first_letter = 0x2070;
      _last_letter  = 0x209F;
      // _version="3.0.1" // Not yet supported!

    }


    ~Superscripts_and_Subscripts2070() {
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
      return "Superscripts and Subscripts";
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
      case 0x2070:
        return 0;
        break;
      case 0x2074:
        return 4;
        break;
      case 0x2075:
        return 5;
        break;
      case 0x2076:
        return 6;
        break;
      case 0x2077:
        return 7;
        break;
      case 0x2078:
        return 8;
        break;
      case 0x2079:
        return 9;
        break;
      case 0x2080:
        return 0;
        break;
      case 0x2081:
        return 1;
        break;
      case 0x2082:
        return 2;
        break;
      case 0x2083:
        return 3;
        break;
      case 0x2084:
        return 4;
        break;
      case 0x2085:
        return 5;
        break;
      case 0x2086:
        return 6;
        break;
      case 0x2087:
        return 7;
        break;
      case 0x2088:
        return 8;
        break;
      case 0x2089:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x2070:
      case 0x2074:
      case 0x2075:
      case 0x2076:
      case 0x2077:
      case 0x2078:
      case 0x2079:
      case 0x2080:
      case 0x2081:
      case 0x2082:
      case 0x2083:
      case 0x2084:
      case 0x2085:
      case 0x2086:
      case 0x2087:
      case 0x2088:
      case 0x2089:
        return 1;
      default:
        return 0;
      }
    }

    int digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x2070:
        return 0;
        break;
      case 0x2074:
        return 4;
        break;
      case 0x2075:
        return 5;
        break;
      case 0x2076:
        return 6;
        break;
      case 0x2077:
        return 7;
        break;
      case 0x2078:
        return 8;
        break;
      case 0x2079:
        return 9;
        break;
      case 0x2080:
        return 0;
        break;
      case 0x2081:
        return 1;
        break;
      case 0x2082:
        return 2;
        break;
      case 0x2083:
        return 3;
        break;
      case 0x2084:
        return 4;
        break;
      case 0x2085:
        return 5;
        break;
      case 0x2086:
        return 6;
        break;
      case 0x2087:
        return 7;
        break;
      case 0x2088:
        return 8;
        break;
      case 0x2089:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x2070:
      case 0x2074:
      case 0x2075:
      case 0x2076:
      case 0x2077:
      case 0x2078:
      case 0x2079:
      case 0x2080:
      case 0x2081:
      case 0x2082:
      case 0x2083:
      case 0x2084:
      case 0x2085:
      case 0x2086:
      case 0x2087:
      case 0x2088:
      case 0x2089:
        return 1;
      default:
        return 0;
      }
    }

    float numeric_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x2070:
        return 0.000000;
        break;
      case 0x2074:
        return 4.000000;
        break;
      case 0x2075:
        return 5.000000;
        break;
      case 0x2076:
        return 6.000000;
        break;
      case 0x2077:
        return 7.000000;
        break;
      case 0x2078:
        return 8.000000;
        break;
      case 0x2079:
        return 9.000000;
        break;
      case 0x2080:
        return 0.000000;
        break;
      case 0x2081:
        return 1.000000;
        break;
      case 0x2082:
        return 2.000000;
        break;
      case 0x2083:
        return 3.000000;
        break;
      case 0x2084:
        return 4.000000;
        break;
      case 0x2085:
        return 5.000000;
        break;
      case 0x2086:
        return 6.000000;
        break;
      case 0x2087:
        return 7.000000;
        break;
      case 0x2088:
        return 8.000000;
        break;
      case 0x2089:
        return 9.000000;
        break;
      default:
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x2070:
      case 0x2074:
      case 0x2075:
      case 0x2076:
      case 0x2077:
      case 0x2078:
      case 0x2079:
      case 0x2080:
      case 0x2081:
      case 0x2082:
      case 0x2083:
      case 0x2084:
      case 0x2085:
      case 0x2086:
      case 0x2087:
      case 0x2088:
      case 0x2089:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Superscripts_and_Subscripts2070::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Superscripts_and_Subscripts2070::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Superscripts_and_Subscripts2070::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Superscripts_and_Subscripts2070::_decompStr[uc - _first_letter][0];
      us[1] = Superscripts_and_Subscripts2070::_decompStr[uc - _first_letter][1];
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool must_mirror(const UCS4 uc) const {
      return Superscripts_and_Subscripts2070::_mirror[uc - _first_letter];
    }

    Line_Break linebreak(const UCS4 uc) const {
      if (!is_defined(uc))
        return LB_MAX;
      return Babylon::Line_Break(Superscripts_and_Subscripts2070::_lb[uc - _first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(Superscripts_and_Subscripts2070::_ea[uc - _first_letter]);
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
      return Superscripts_and_Subscripts2070::_Dash[uc - _first_letter];
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
      return Superscripts_and_Subscripts2070::_Math[uc - _first_letter];
    }

    bool is_Paired_Punctuation(const UCS4 uc) const {
      return Superscripts_and_Subscripts2070::_Paired_Punctuation[uc - _first_letter];
    }

    bool is_Left_of_Pair(const UCS4 uc) const {
      return Superscripts_and_Subscripts2070::_Left_of_Pair[uc - _first_letter];
    }

    bool is_Combining(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_spacing(const UCS4 uc) const {
      return 0;
    }

    bool is_Composite(const UCS4 uc) const {
      return 0;
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Superscripts_and_Subscripts2070::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Superscripts_and_Subscripts2070::_Identifier_Part[uc - _first_letter];
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
    Superscripts_and_Subscripts2070(const Superscripts_and_Subscripts2070 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[48];
    static const unsigned char _cat[48];
    static const unsigned char _bidir[48];
    static const unsigned char _decomp[48];
    static const UCS2 _decompStr[48][2];
    static const bool _mirror[48];
    static const unsigned char _lb[48];
    static const unsigned char _ea[48];
    static const bool _Dash[48];
    static const bool _Math[48];
    static const bool _Paired_Punctuation[48];
    static const bool _Left_of_Pair[48];
    static const bool _Alphabetic[48];
    static const bool _Identifier_Part[48];

  }; // class Superscripts_and_Subscripts2070

  const bool Superscripts_and_Subscripts2070::_is_defined[] = {
    1, 0, 0, 0, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Superscripts_and_Subscripts2070::_cat[] = {
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Ps, CAT_Pe, CAT_Ll, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Ps, CAT_Pe, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No
  };

  const unsigned char Superscripts_and_Subscripts2070::_bidir[] = {
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN
  };

  const unsigned char Superscripts_and_Subscripts2070::_decomp[] = {
    DECOMP_SUPER, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
    DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
    DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, 
    DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Superscripts_and_Subscripts2070::_decompStr[][2] = {
    { 0x0030, 0x0000 }, { 0x2071, 0x0000 }, { 0x2072, 0x0000 }, { 0x2073, 0x0000 }, 
    { 0x0034, 0x0000 }, { 0x0035, 0x0000 }, { 0x0036, 0x0000 }, { 0x0037, 0x0000 }, 
    { 0x0038, 0x0000 }, { 0x0039, 0x0000 }, { 0x002B, 0x0000 }, { 0x2212, 0x0000 }, 
    { 0x003D, 0x0000 }, { 0x0028, 0x0000 }, { 0x0029, 0x0000 }, { 0x006E, 0x0000 }, 
    { 0x0030, 0x0000 }, { 0x0031, 0x0000 }, { 0x0032, 0x0000 }, { 0x0033, 0x0000 }, 
    { 0x0034, 0x0000 }, { 0x0035, 0x0000 }, { 0x0036, 0x0000 }, { 0x0037, 0x0000 }, 
    { 0x0038, 0x0000 }, { 0x0039, 0x0000 }, { 0x002B, 0x0000 }, { 0x2212, 0x0000 }, 
    { 0x003D, 0x0000 }, { 0x0028, 0x0000 }, { 0x0029, 0x0000 }, { 0x208F, 0x0000 }, 
    { 0x2090, 0x0000 }, { 0x2091, 0x0000 }, { 0x2092, 0x0000 }, { 0x2093, 0x0000 }, 
    { 0x2094, 0x0000 }, { 0x2095, 0x0000 }, { 0x2096, 0x0000 }, { 0x2097, 0x0000 }, 
    { 0x2098, 0x0000 }, { 0x2099, 0x0000 }, { 0x209A, 0x0000 }, { 0x209B, 0x0000 }, 
    { 0x209C, 0x0000 }, { 0x209D, 0x0000 }, { 0x209E, 0x0000 }, { 0x209F, 0x0000 }
  };

  const bool Superscripts_and_Subscripts2070::_mirror[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 1, 1, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 1, 1, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Superscripts_and_Subscripts2070::_lb[] = {
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, LB_AI, 
    LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
  };

  const unsigned char Superscripts_and_Subscripts2070::_ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
    EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bool Superscripts_and_Subscripts2070::_Dash[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::_Math[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::_Paired_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::_Left_of_Pair[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::_Alphabetic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::_Identifier_Part[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon

dload(Babylon::Superscripts_and_Subscripts2070);
