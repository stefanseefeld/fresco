/*$Id: 900-97F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:11:09 +0100.
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
 
  class Devanagari900 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Devanagari900() {
      my_first_letter = 0x900;
      my_last_letter  = 0x97F;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x0915093C] = 0x0958;
      composeMap[0x0916093C] = 0x0959;
      composeMap[0x0917093C] = 0x095A;
      composeMap[0x091C093C] = 0x095B;
      composeMap[0x0921093C] = 0x095C;
      composeMap[0x0922093C] = 0x095D;
      composeMap[0x0928093C] = 0x0929;
      composeMap[0x092B093C] = 0x095E;
      composeMap[0x092F093C] = 0x095F;
      composeMap[0x0930093C] = 0x0931;
      composeMap[0x0933093C] = 0x0934;

    }


    ~Devanagari900() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Devanagari";
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
      case 0x0966:
        return 0;
        break;
      case 0x0967:
        return 1;
        break;
      case 0x0968:
        return 2;
        break;
      case 0x0969:
        return 3;
        break;
      case 0x096A:
        return 4;
        break;
      case 0x096B:
        return 5;
        break;
      case 0x096C:
        return 6;
        break;
      case 0x096D:
        return 7;
        break;
      case 0x096E:
        return 8;
        break;
      case 0x096F:
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
      case 0x0966:
        return 0;
        break;
      case 0x0967:
        return 1;
        break;
      case 0x0968:
        return 2;
        break;
      case 0x0969:
        return 3;
        break;
      case 0x096A:
        return 4;
        break;
      case 0x096B:
        return 5;
        break;
      case 0x096C:
        return 6;
        break;
      case 0x096D:
        return 7;
        break;
      case 0x096E:
        return 8;
        break;
      case 0x096F:
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
      case 0x0966:
        return 0.000000;
        break;
      case 0x0967:
        return 1.000000;
        break;
      case 0x0968:
        return 2.000000;
        break;
      case 0x0969:
        return 3.000000;
        break;
      case 0x096A:
        return 4.000000;
        break;
      case 0x096B:
        return 5.000000;
        break;
      case 0x096C:
        return 6.000000;
        break;
      case 0x096D:
        return 7.000000;
        break;
      case 0x096E:
        return 8.000000;
        break;
      case 0x096F:
        return 9.000000;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(Devanagari900::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Can_Comb_Class(Devanagari900::combCl[_uc - my_first_letter]);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Devanagari900::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Devanagari900::decompStr[_uc - my_first_letter][0];
      us[1] = Devanagari900::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(Devanagari900::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(EA_WIDTH_N);
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
      return Devanagari900::Terminal_Punctuation[_uc - my_first_letter];
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
      return Devanagari900::Combining[_uc - my_first_letter];
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return Devanagari900::Non_spacing[_uc - my_first_letter];
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return Devanagari900::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return Devanagari900::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return Devanagari900::Identifier_Part[_uc - my_first_letter];
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
    Devanagari900(const Devanagari900 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[128];
    static const unsigned char cat[128];
    static const unsigned char combCl[128];
    static const unsigned char bidir[128];
    static const UCS2 decompStr[128][2];
    static const unsigned char lb[128];
    map<UCS4, UCS4> composeMap;
    static const bool Terminal_Punctuation[128];
    static const bool Combining[128];
    static const bool Non_spacing[128];
    static const bool Alphabetic[128];
    static const bool Diacritic[128];
    static const bool Identifier_Part[128];

  }; // class Devanagari900

  const bool Devanagari900::isdefined[] = {
    0, 1, 1, 1, 0, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 0, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 0, 0, 
    1, 1, 1, 1, 1, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Devanagari900::cat[] = {
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Po, CAT_Po, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Po, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
  };

  const unsigned char Devanagari900::combCl[] = {
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
    0, 230, 220, 230, 230, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char Devanagari900::bidir[] = {
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM
  };

  const UCS2 Devanagari900::decompStr[][2] = {
    { 0x0900, 0x0000 }, { 0x0901, 0x0000 }, { 0x0902, 0x0000 }, { 0x0903, 0x0000 }, 
    { 0x0904, 0x0000 }, { 0x0905, 0x0000 }, { 0x0906, 0x0000 }, { 0x0907, 0x0000 }, 
    { 0x0908, 0x0000 }, { 0x0909, 0x0000 }, { 0x090A, 0x0000 }, { 0x090B, 0x0000 }, 
    { 0x090C, 0x0000 }, { 0x090D, 0x0000 }, { 0x090E, 0x0000 }, { 0x090F, 0x0000 }, 
    { 0x0910, 0x0000 }, { 0x0911, 0x0000 }, { 0x0912, 0x0000 }, { 0x0913, 0x0000 }, 
    { 0x0914, 0x0000 }, { 0x0915, 0x0000 }, { 0x0916, 0x0000 }, { 0x0917, 0x0000 }, 
    { 0x0918, 0x0000 }, { 0x0919, 0x0000 }, { 0x091A, 0x0000 }, { 0x091B, 0x0000 }, 
    { 0x091C, 0x0000 }, { 0x091D, 0x0000 }, { 0x091E, 0x0000 }, { 0x091F, 0x0000 }, 
    { 0x0920, 0x0000 }, { 0x0921, 0x0000 }, { 0x0922, 0x0000 }, { 0x0923, 0x0000 }, 
    { 0x0924, 0x0000 }, { 0x0925, 0x0000 }, { 0x0926, 0x0000 }, { 0x0927, 0x0000 }, 
    { 0x0928, 0x0000 }, { 0x0928, 0x093C }, { 0x092A, 0x0000 }, { 0x092B, 0x0000 }, 
    { 0x092C, 0x0000 }, { 0x092D, 0x0000 }, { 0x092E, 0x0000 }, { 0x092F, 0x0000 }, 
    { 0x0930, 0x0000 }, { 0x0930, 0x093C }, { 0x0932, 0x0000 }, { 0x0933, 0x0000 }, 
    { 0x0933, 0x093C }, { 0x0935, 0x0000 }, { 0x0936, 0x0000 }, { 0x0937, 0x0000 }, 
    { 0x0938, 0x0000 }, { 0x0939, 0x0000 }, { 0x093A, 0x0000 }, { 0x093B, 0x0000 }, 
    { 0x093C, 0x0000 }, { 0x093D, 0x0000 }, { 0x093E, 0x0000 }, { 0x093F, 0x0000 }, 
    { 0x0940, 0x0000 }, { 0x0941, 0x0000 }, { 0x0942, 0x0000 }, { 0x0943, 0x0000 }, 
    { 0x0944, 0x0000 }, { 0x0945, 0x0000 }, { 0x0946, 0x0000 }, { 0x0947, 0x0000 }, 
    { 0x0948, 0x0000 }, { 0x0949, 0x0000 }, { 0x094A, 0x0000 }, { 0x094B, 0x0000 }, 
    { 0x094C, 0x0000 }, { 0x094D, 0x0000 }, { 0x094E, 0x0000 }, { 0x094F, 0x0000 }, 
    { 0x0950, 0x0000 }, { 0x0951, 0x0000 }, { 0x0952, 0x0000 }, { 0x0953, 0x0000 }, 
    { 0x0954, 0x0000 }, { 0x0955, 0x0000 }, { 0x0956, 0x0000 }, { 0x0957, 0x0000 }, 
    { 0x0915, 0x093C }, { 0x0916, 0x093C }, { 0x0917, 0x093C }, { 0x091C, 0x093C }, 
    { 0x0921, 0x093C }, { 0x0922, 0x093C }, { 0x092B, 0x093C }, { 0x092F, 0x093C }, 
    { 0x0960, 0x0000 }, { 0x0961, 0x0000 }, { 0x0962, 0x0000 }, { 0x0963, 0x0000 }, 
    { 0x0964, 0x0000 }, { 0x0965, 0x0000 }, { 0x0966, 0x0000 }, { 0x0967, 0x0000 }, 
    { 0x0968, 0x0000 }, { 0x0969, 0x0000 }, { 0x096A, 0x0000 }, { 0x096B, 0x0000 }, 
    { 0x096C, 0x0000 }, { 0x096D, 0x0000 }, { 0x096E, 0x0000 }, { 0x096F, 0x0000 }, 
    { 0x0970, 0x0000 }, { 0x0971, 0x0000 }, { 0x0972, 0x0000 }, { 0x0973, 0x0000 }, 
    { 0x0974, 0x0000 }, { 0x0975, 0x0000 }, { 0x0976, 0x0000 }, { 0x0977, 0x0000 }, 
    { 0x0978, 0x0000 }, { 0x0979, 0x0000 }, { 0x097A, 0x0000 }, { 0x097B, 0x0000 }, 
    { 0x097C, 0x0000 }, { 0x097D, 0x0000 }, { 0x097E, 0x0000 }, { 0x097F, 0x0000 }
  };

  const unsigned char Devanagari900::lb[] = {
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_CM, LB_CM, LB_AL, LB_AL, LB_NU, LB_NU, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
  };

    const bool Devanagari900::Terminal_Punctuation[] = {
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
        0, 0, 0, 0, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Devanagari900::Combining[] = {
        0, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Devanagari900::Non_spacing[] = {
        0, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 0, 0, 0, 1, 0, 0, 
        0, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Devanagari900::Alphabetic[] = {
        0, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Devanagari900::Diacritic[] = {
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
        0, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Devanagari900::Identifier_Part[] = {
        0, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Devanagari900);
