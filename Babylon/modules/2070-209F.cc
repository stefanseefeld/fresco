/*$Id: 2070-209F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:12:29 +0100.
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
      my_first_letter = 0x2070;
      my_last_letter  = 0x209F;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Superscripts_and_Subscripts2070() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Superscripts and Subscripts";
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
      switch(_uc) {
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
        throw UndefinedProperty(_uc, PROP_DEC_DIGIT_VALUE);
      }
    }

    int digitValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
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
        throw UndefinedProperty(_uc, PROP_DIGIT_VALUE);
      }
    }

    float numericValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
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
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(Superscripts_and_Subscripts2070::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Superscripts_and_Subscripts2070::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Superscripts_and_Subscripts2070::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Superscripts_and_Subscripts2070::decompStr[_uc - my_first_letter][0];
      us[1] = Superscripts_and_Subscripts2070::decompStr[_uc - my_first_letter][1];
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool mustMirror(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Superscripts_and_Subscripts2070::mirror[_uc - my_first_letter];
    }

    Line_Break linebreak(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Line_Break(Superscripts_and_Subscripts2070::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(Superscripts_and_Subscripts2070::ea[_uc - my_first_letter]);
    }

    UCS4 compose (const UCS4 & starter, const UCS4 & last) {
      return 0;
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
      return Superscripts_and_Subscripts2070::Dash[_uc - my_first_letter];
    }

    bool is_Hyphen(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Math(const UCS4 & _uc) const {
      return Superscripts_and_Subscripts2070::Math[_uc - my_first_letter];
    }

    bool is_Paired_Punctuation(const UCS4 & _uc) const {
      return Superscripts_and_Subscripts2070::Paired_Punctuation[_uc - my_first_letter];
    }

    bool is_Left_of_Pair(const UCS4 & _uc) const {
      return Superscripts_and_Subscripts2070::Left_of_Pair[_uc - my_first_letter];
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
      return Superscripts_and_Subscripts2070::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return Superscripts_and_Subscripts2070::Identifier_Part[_uc - my_first_letter];
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
      return Superscripts_and_Subscripts2070::Lowercase[_uc - my_first_letter];
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
    Superscripts_and_Subscripts2070(const Superscripts_and_Subscripts2070 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[48];
    static const unsigned char cat[48];
    static const unsigned char bidir[48];
    static const unsigned char decomp[48];
    static const UCS2 decompStr[48][2];
    static const bool mirror[48];
    static const unsigned char lb[48];
    static const unsigned char ea[48];
    static const bool Dash[48];
    static const bool Math[48];
    static const bool Paired_Punctuation[48];
    static const bool Left_of_Pair[48];
    static const bool Alphabetic[48];
    static const bool Identifier_Part[48];
    static const bool Lowercase[48];

  }; // class Superscripts_and_Subscripts2070

  const bool Superscripts_and_Subscripts2070::isdefined[] = {
    1, 0, 0, 0, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Superscripts_and_Subscripts2070::cat[] = {
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Ps, CAT_Pe, CAT_Ll, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Ps, CAT_Pe, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No
  };

  const unsigned char Superscripts_and_Subscripts2070::bidir[] = {
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN
  };

  const unsigned char Superscripts_and_Subscripts2070::decomp[] = {
    DECOMP_SUPER, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
    DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
    DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, 
    DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Superscripts_and_Subscripts2070::decompStr[][2] = {
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

  const bool Superscripts_and_Subscripts2070::mirror[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 1, 1, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 1, 1, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Superscripts_and_Subscripts2070::lb[] = {
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, LB_AI, 
    LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
  };

  const unsigned char Superscripts_and_Subscripts2070::ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
    EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bool Superscripts_and_Subscripts2070::Dash[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::Math[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::Paired_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::Left_of_Pair[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::Alphabetic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::Identifier_Part[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Superscripts_and_Subscripts2070::Lowercase[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Superscripts_and_Subscripts2070);
