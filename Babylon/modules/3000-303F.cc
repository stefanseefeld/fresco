/*$Id: 3000-303F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:26:27 +0100.
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

  class CJK_Symbols_and_Punctuation3000 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    CJK_Symbols_and_Punctuation3000() {
      _first_letter = 0x3000;
      _last_letter  = 0x303F;
      // _version="3.0.1" // Not yet supported!

    }


    ~CJK_Symbols_and_Punctuation3000() {
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
      return "CJK Symbols and Punctuation";
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
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x3007:
        return 0.000000;
        break;
      case 0x3021:
        return 1.000000;
        break;
      case 0x3022:
        return 2.000000;
        break;
      case 0x3023:
        return 3.000000;
        break;
      case 0x3024:
        return 4.000000;
        break;
      case 0x3025:
        return 5.000000;
        break;
      case 0x3026:
        return 6.000000;
        break;
      case 0x3027:
        return 7.000000;
        break;
      case 0x3028:
        return 8.000000;
        break;
      case 0x3029:
        return 9.000000;
        break;
      case 0x3038:
        return 10.000000;
        break;
      case 0x3039:
        return 20.000000;
        break;
      case 0x303A:
        return 30.000000;
        break;
      default:
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x3007:
      case 0x3021:
      case 0x3022:
      case 0x3023:
      case 0x3024:
      case 0x3025:
      case 0x3026:
      case 0x3027:
      case 0x3028:
      case 0x3029:
      case 0x3038:
      case 0x3039:
      case 0x303A:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(CJK_Symbols_and_Punctuation3000::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Can_Comb_Class(CJK_Symbols_and_Punctuation3000::_comb_cl[uc - _first_letter]);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(CJK_Symbols_and_Punctuation3000::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(CJK_Symbols_and_Punctuation3000::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = CJK_Symbols_and_Punctuation3000::_decompStr[uc - _first_letter][0];
      us[1] = CJK_Symbols_and_Punctuation3000::_decompStr[uc - _first_letter][1];
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool must_mirror(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_mirror[uc - _first_letter];
    }

    Line_Break linebreak(const UCS4 uc) const {
      if (!is_defined(uc))
        return LB_MAX;
      return Babylon::Line_Break(CJK_Symbols_and_Punctuation3000::_lb[uc - _first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(CJK_Symbols_and_Punctuation3000::_ea[uc - _first_letter]);
    }

    UCS4 compose (const UCS4 starter, const UCS4 last) {
      return 0;
    }

    bool is_Zero_width(const UCS4 uc) const {
      return 0;
    }

    bool is_White_space(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_White_space[uc - _first_letter];
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
      return CJK_Symbols_and_Punctuation3000::_Dash[uc - _first_letter];
    }

    bool is_Hyphen(const UCS4 uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_Quotation_Mark[uc - _first_letter];
    }

    bool is_Terminal_Punctuation(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_Terminal_Punctuation[uc - _first_letter];
    }

    bool is_Math(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_Math[uc - _first_letter];
    }

    bool is_Paired_Punctuation(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_Paired_Punctuation[uc - _first_letter];
    }

    bool is_Left_of_Pair(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_Left_of_Pair[uc - _first_letter];
    }

    bool is_Combining(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_Combining[uc - _first_letter];
    }

    bool is_Non_spacing(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_Non_spacing[uc - _first_letter];
    }

    bool is_Composite(const UCS4 uc) const {
      return 0;
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return 0;
    }

    bool is_Diacritic(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_Diacritic[uc - _first_letter];
    }

    bool is_Extender(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_Extender[uc - _first_letter];
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return CJK_Symbols_and_Punctuation3000::_Identifier_Part[uc - _first_letter];
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
      return ((uc >= 0x3006 && uc <= 0x3007) ||
              (uc >= 0x3021 && uc <= 0x3029) ||
              (uc >= 0x3038 && uc <= 0x303A));
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
    CJK_Symbols_and_Punctuation3000(const CJK_Symbols_and_Punctuation3000 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[64];
    static const unsigned char _cat[64];
    static const unsigned char _comb_cl[64];
    static const unsigned char _bidir[64];
    static const unsigned char _decomp[64];
    static const UCS2 _decompStr[64][2];
    static const bool _mirror[64];
    static const unsigned char _lb[64];
    static const unsigned char _ea[64];
    static const bool _White_space[64];
    static const bool _Dash[64];
    static const bool _Quotation_Mark[64];
    static const bool _Terminal_Punctuation[64];
    static const bool _Math[64];
    static const bool _Paired_Punctuation[64];
    static const bool _Left_of_Pair[64];
    static const bool _Combining[64];
    static const bool _Non_spacing[64];
    static const bool _Diacritic[64];
    static const bool _Extender[64];
    static const bool _Identifier_Part[64];

  }; // class CJK_Symbols_and_Punctuation3000

  const bool CJK_Symbols_and_Punctuation3000::_is_defined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 1, 1
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::_cat[] = {
    CAT_Zs, CAT_Po, CAT_Po, CAT_Po, CAT_So, CAT_Lm, CAT_Lo, CAT_Nl, 
    CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, 
    CAT_Ps, CAT_Pe, CAT_So, CAT_So, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, 
    CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Pd, CAT_Ps, CAT_Pe, CAT_Pe, 
    CAT_So, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Pd, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_So, CAT_So, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Zs, CAT_Zs, CAT_Zs, CAT_So, CAT_So
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::_comb_cl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 218, 228, 232, 222, 224, 224, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::_bidir[] = {
    BIDIR_WS, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_ON, BIDIR_ON
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::_decomp[] = {
    DECOMP_WIDE, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 CJK_Symbols_and_Punctuation3000::_decompStr[][2] = {
    { 0x0020, 0x0000 }, { 0x3001, 0x0000 }, { 0x3002, 0x0000 }, { 0x3003, 0x0000 }, 
    { 0x3004, 0x0000 }, { 0x3005, 0x0000 }, { 0x3006, 0x0000 }, { 0x3007, 0x0000 }, 
    { 0x3008, 0x0000 }, { 0x3009, 0x0000 }, { 0x300A, 0x0000 }, { 0x300B, 0x0000 }, 
    { 0x300C, 0x0000 }, { 0x300D, 0x0000 }, { 0x300E, 0x0000 }, { 0x300F, 0x0000 }, 
    { 0x3010, 0x0000 }, { 0x3011, 0x0000 }, { 0x3012, 0x0000 }, { 0x3013, 0x0000 }, 
    { 0x3014, 0x0000 }, { 0x3015, 0x0000 }, { 0x3016, 0x0000 }, { 0x3017, 0x0000 }, 
    { 0x3018, 0x0000 }, { 0x3019, 0x0000 }, { 0x301A, 0x0000 }, { 0x301B, 0x0000 }, 
    { 0x301C, 0x0000 }, { 0x301D, 0x0000 }, { 0x301E, 0x0000 }, { 0x301F, 0x0000 }, 
    { 0x3020, 0x0000 }, { 0x3021, 0x0000 }, { 0x3022, 0x0000 }, { 0x3023, 0x0000 }, 
    { 0x3024, 0x0000 }, { 0x3025, 0x0000 }, { 0x3026, 0x0000 }, { 0x3027, 0x0000 }, 
    { 0x3028, 0x0000 }, { 0x3029, 0x0000 }, { 0x302A, 0x0000 }, { 0x302B, 0x0000 }, 
    { 0x302C, 0x0000 }, { 0x302D, 0x0000 }, { 0x302E, 0x0000 }, { 0x302F, 0x0000 }, 
    { 0x3030, 0x0000 }, { 0x3031, 0x0000 }, { 0x3032, 0x0000 }, { 0x3033, 0x0000 }, 
    { 0x3034, 0x0000 }, { 0x3035, 0x0000 }, { 0x3012, 0x0000 }, { 0x3037, 0x0000 }, 
    { 0x5341, 0x0000 }, { 0x5344, 0x0000 }, { 0x5345, 0x0000 }, { 0x303B, 0x0000 }, 
    { 0x303C, 0x0000 }, { 0x303D, 0x0000 }, { 0x303E, 0x0000 }, { 0x303F, 0x0000 }
  };

  const bool CJK_Symbols_and_Punctuation3000::_mirror[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 0, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::_lb[] = {
    LB_ID, LB_CL, LB_CL, LB_ID, LB_ID, LB_NS, LB_ID, LB_ID, 
    LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, 
    LB_OP, LB_CL, LB_ID, LB_ID, LB_OP, LB_CL, LB_OP, LB_CL, 
    LB_OP, LB_CL, LB_OP, LB_CL, LB_NS, LB_OP, LB_CL, LB_CL, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::_ea[] = {
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_N
  };

    const bool CJK_Symbols_and_Punctuation3000::_White_space[] = {
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Dash[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Quotation_Mark[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Terminal_Punctuation[] = {
        0, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Math[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Paired_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Left_of_Pair[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 0, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Combining[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Non_spacing[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Extender[] = {
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::_Identifier_Part[] = {
        0, 0, 0, 0, 0, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 0, 0, 0, 0, 0
    };

}; // namespace Babylon

dload(Babylon::CJK_Symbols_and_Punctuation3000);
