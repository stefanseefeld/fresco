/*$Id: 3000-303F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:13:11 +0100.
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
      my_first_letter = 0x3000;
      my_last_letter  = 0x303F;
      // my_version="3.0.1" // Not yet supported!

    }


    ~CJK_Symbols_and_Punctuation3000() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "CJK Symbols and Punctuation";
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
      switch(_uc) {
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
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(CJK_Symbols_and_Punctuation3000::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Can_Comb_Class(CJK_Symbols_and_Punctuation3000::combCl[_uc - my_first_letter]);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(CJK_Symbols_and_Punctuation3000::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(CJK_Symbols_and_Punctuation3000::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = CJK_Symbols_and_Punctuation3000::decompStr[_uc - my_first_letter][0];
      us[1] = CJK_Symbols_and_Punctuation3000::decompStr[_uc - my_first_letter][1];
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool mustMirror(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return CJK_Symbols_and_Punctuation3000::mirror[_uc - my_first_letter];
    }

    Line_Break linebreak(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Line_Break(CJK_Symbols_and_Punctuation3000::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(CJK_Symbols_and_Punctuation3000::ea[_uc - my_first_letter]);
    }

    UCS4 compose (const UCS4 & starter, const UCS4 & last) {
      return 0;
    }

    bool is_Zero_width(const UCS4 & _uc) const {
      return 0;
    }

    bool is_White_space(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::White_space[_uc - my_first_letter];
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
      return CJK_Symbols_and_Punctuation3000::Dash[_uc - my_first_letter];
    }

    bool is_Hyphen(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::Quotation_Mark[_uc - my_first_letter];
    }

    bool is_Terminal_Punctuation(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::Terminal_Punctuation[_uc - my_first_letter];
    }

    bool is_Math(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::Math[_uc - my_first_letter];
    }

    bool is_Paired_Punctuation(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::Paired_Punctuation[_uc - my_first_letter];
    }

    bool is_Left_of_Pair(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::Left_of_Pair[_uc - my_first_letter];
    }

    bool is_Combining(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::Combining[_uc - my_first_letter];
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::Non_spacing[_uc - my_first_letter];
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::Extender[_uc - my_first_letter];
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return CJK_Symbols_and_Punctuation3000::Identifier_Part[_uc - my_first_letter];
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
    CJK_Symbols_and_Punctuation3000(const CJK_Symbols_and_Punctuation3000 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[64];
    static const unsigned char cat[64];
    static const unsigned char combCl[64];
    static const unsigned char bidir[64];
    static const unsigned char decomp[64];
    static const UCS2 decompStr[64][2];
    static const bool mirror[64];
    static const unsigned char lb[64];
    static const unsigned char ea[64];
    static const bool White_space[64];
    static const bool Dash[64];
    static const bool Quotation_Mark[64];
    static const bool Terminal_Punctuation[64];
    static const bool Math[64];
    static const bool Paired_Punctuation[64];
    static const bool Left_of_Pair[64];
    static const bool Combining[64];
    static const bool Non_spacing[64];
    static const bool Diacritic[64];
    static const bool Extender[64];
    static const bool Identifier_Part[64];

  }; // class CJK_Symbols_and_Punctuation3000

  const bool CJK_Symbols_and_Punctuation3000::isdefined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 1, 1
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::cat[] = {
    CAT_Zs, CAT_Po, CAT_Po, CAT_Po, CAT_So, CAT_Lm, CAT_Lo, CAT_Nl, 
    CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, 
    CAT_Ps, CAT_Pe, CAT_So, CAT_So, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, 
    CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Pd, CAT_Ps, CAT_Pe, CAT_Pe, 
    CAT_So, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
    CAT_Nl, CAT_Nl, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Pd, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_So, CAT_So, 
    CAT_Nl, CAT_Nl, CAT_Nl, CAT_Zs, CAT_Zs, CAT_Zs, CAT_So, CAT_So
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::combCl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 218, 228, 232, 222, 224, 224, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::bidir[] = {
    BIDIR_WS, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_ON, BIDIR_ON
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::decomp[] = {
    DECOMP_WIDE, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_NO_DECOMP, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 CJK_Symbols_and_Punctuation3000::decompStr[][2] = {
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

  const bool CJK_Symbols_and_Punctuation3000::mirror[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 0, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::lb[] = {
    LB_ID, LB_CL, LB_CL, LB_ID, LB_ID, LB_NS, LB_ID, LB_ID, 
    LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, 
    LB_OP, LB_CL, LB_ID, LB_ID, LB_OP, LB_CL, LB_OP, LB_CL, 
    LB_OP, LB_CL, LB_OP, LB_CL, LB_NS, LB_OP, LB_CL, LB_CL, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID
  };

  const unsigned char CJK_Symbols_and_Punctuation3000::ea[] = {
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
    EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_N
  };

    const bool CJK_Symbols_and_Punctuation3000::White_space[] = {
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Dash[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Quotation_Mark[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Terminal_Punctuation[] = {
        0, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Math[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Paired_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Left_of_Pair[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 1, 0, 1, 0, 1, 0, 
        1, 0, 0, 0, 1, 0, 1, 0, 
        1, 0, 1, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Combining[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Non_spacing[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Extender[] = {
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool CJK_Symbols_and_Punctuation3000::Identifier_Part[] = {
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
