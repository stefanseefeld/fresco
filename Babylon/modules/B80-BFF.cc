/*$Id: B80-BFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:11:20 +0100.
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
 
  class TamilB80 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    TamilB80() {
      my_first_letter = 0xB80;
      my_last_letter  = 0xBFF;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x0B920BD7] = 0x0B94;
      composeMap[0x0BC60BBE] = 0x0BCA;
      composeMap[0x0BC60BD7] = 0x0BCC;
      composeMap[0x0BC70BBE] = 0x0BCB;

    }


    ~TamilB80() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Tamil";
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
      case 0x0BE7:
        return 1;
        break;
      case 0x0BE8:
        return 2;
        break;
      case 0x0BE9:
        return 3;
        break;
      case 0x0BEA:
        return 4;
        break;
      case 0x0BEB:
        return 5;
        break;
      case 0x0BEC:
        return 6;
        break;
      case 0x0BED:
        return 7;
        break;
      case 0x0BEE:
        return 8;
        break;
      case 0x0BEF:
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
      case 0x0BE7:
        return 1;
        break;
      case 0x0BE8:
        return 2;
        break;
      case 0x0BE9:
        return 3;
        break;
      case 0x0BEA:
        return 4;
        break;
      case 0x0BEB:
        return 5;
        break;
      case 0x0BEC:
        return 6;
        break;
      case 0x0BED:
        return 7;
        break;
      case 0x0BEE:
        return 8;
        break;
      case 0x0BEF:
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
      case 0x0BE7:
        return 1.000000;
        break;
      case 0x0BE8:
        return 2.000000;
        break;
      case 0x0BE9:
        return 3.000000;
        break;
      case 0x0BEA:
        return 4.000000;
        break;
      case 0x0BEB:
        return 5.000000;
        break;
      case 0x0BEC:
        return 6.000000;
        break;
      case 0x0BED:
        return 7.000000;
        break;
      case 0x0BEE:
        return 8.000000;
        break;
      case 0x0BEF:
        return 9.000000;
        break;
      case 0x0BF0:
        return 10.000000;
        break;
      case 0x0BF1:
        return 100.000000;
        break;
      case 0x0BF2:
        return 1000.000000;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(TamilB80::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Can_Comb_Class(TamilB80::combCl[_uc - my_first_letter]);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(TamilB80::bidir[_uc - my_first_letter]);
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
      us[0] = TamilB80::decompStr[_uc - my_first_letter][0];
      us[1] = TamilB80::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(TamilB80::lb[_uc - my_first_letter]);
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
      return 0;
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
      return TamilB80::Combining[_uc - my_first_letter];
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return TamilB80::Non_spacing[_uc - my_first_letter];
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return TamilB80::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return TamilB80::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return TamilB80::Identifier_Part[_uc - my_first_letter];
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
    TamilB80(const TamilB80 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[128];
    static const unsigned char cat[128];
    static const unsigned char combCl[128];
    static const unsigned char bidir[128];
    static const UCS2 decompStr[128][2];
    static const unsigned char lb[128];
    map<UCS4, UCS4> composeMap;
    static const bool Combining[128];
    static const bool Non_spacing[128];
    static const bool Alphabetic[128];
    static const bool Diacritic[128];
    static const bool Identifier_Part[128];

  }; // class TamilB80

  const bool TamilB80::isdefined[] = {
    0, 0, 1, 1, 0, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 1, 1, 
    1, 0, 1, 1, 1, 1, 0, 0, 
    0, 1, 1, 0, 1, 0, 1, 1, 
    0, 0, 0, 1, 1, 0, 0, 0, 
    1, 1, 1, 0, 0, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 0, 1, 
    1, 1, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 0, 0, 0, 1, 1, 
    1, 0, 1, 1, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char TamilB80::cat[] = {
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
    CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_No, CAT_No, CAT_No, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
    CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
  };

  const unsigned char TamilB80::combCl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 9, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char TamilB80::bidir[] = {
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
    BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM
  };

  const UCS2 TamilB80::decompStr[][2] = {
    { 0x0B80, 0x0000 }, { 0x0B81, 0x0000 }, { 0x0B82, 0x0000 }, { 0x0B83, 0x0000 }, 
    { 0x0B84, 0x0000 }, { 0x0B85, 0x0000 }, { 0x0B86, 0x0000 }, { 0x0B87, 0x0000 }, 
    { 0x0B88, 0x0000 }, { 0x0B89, 0x0000 }, { 0x0B8A, 0x0000 }, { 0x0B8B, 0x0000 }, 
    { 0x0B8C, 0x0000 }, { 0x0B8D, 0x0000 }, { 0x0B8E, 0x0000 }, { 0x0B8F, 0x0000 }, 
    { 0x0B90, 0x0000 }, { 0x0B91, 0x0000 }, { 0x0B92, 0x0000 }, { 0x0B93, 0x0000 }, 
    { 0x0B92, 0x0BD7 }, { 0x0B95, 0x0000 }, { 0x0B96, 0x0000 }, { 0x0B97, 0x0000 }, 
    { 0x0B98, 0x0000 }, { 0x0B99, 0x0000 }, { 0x0B9A, 0x0000 }, { 0x0B9B, 0x0000 }, 
    { 0x0B9C, 0x0000 }, { 0x0B9D, 0x0000 }, { 0x0B9E, 0x0000 }, { 0x0B9F, 0x0000 }, 
    { 0x0BA0, 0x0000 }, { 0x0BA1, 0x0000 }, { 0x0BA2, 0x0000 }, { 0x0BA3, 0x0000 }, 
    { 0x0BA4, 0x0000 }, { 0x0BA5, 0x0000 }, { 0x0BA6, 0x0000 }, { 0x0BA7, 0x0000 }, 
    { 0x0BA8, 0x0000 }, { 0x0BA9, 0x0000 }, { 0x0BAA, 0x0000 }, { 0x0BAB, 0x0000 }, 
    { 0x0BAC, 0x0000 }, { 0x0BAD, 0x0000 }, { 0x0BAE, 0x0000 }, { 0x0BAF, 0x0000 }, 
    { 0x0BB0, 0x0000 }, { 0x0BB1, 0x0000 }, { 0x0BB2, 0x0000 }, { 0x0BB3, 0x0000 }, 
    { 0x0BB4, 0x0000 }, { 0x0BB5, 0x0000 }, { 0x0BB6, 0x0000 }, { 0x0BB7, 0x0000 }, 
    { 0x0BB8, 0x0000 }, { 0x0BB9, 0x0000 }, { 0x0BBA, 0x0000 }, { 0x0BBB, 0x0000 }, 
    { 0x0BBC, 0x0000 }, { 0x0BBD, 0x0000 }, { 0x0BBE, 0x0000 }, { 0x0BBF, 0x0000 }, 
    { 0x0BC0, 0x0000 }, { 0x0BC1, 0x0000 }, { 0x0BC2, 0x0000 }, { 0x0BC3, 0x0000 }, 
    { 0x0BC4, 0x0000 }, { 0x0BC5, 0x0000 }, { 0x0BC6, 0x0000 }, { 0x0BC7, 0x0000 }, 
    { 0x0BC8, 0x0000 }, { 0x0BC9, 0x0000 }, { 0x0BC6, 0x0BBE }, { 0x0BC7, 0x0BBE }, 
    { 0x0BC6, 0x0BD7 }, { 0x0BCD, 0x0000 }, { 0x0BCE, 0x0000 }, { 0x0BCF, 0x0000 }, 
    { 0x0BD0, 0x0000 }, { 0x0BD1, 0x0000 }, { 0x0BD2, 0x0000 }, { 0x0BD3, 0x0000 }, 
    { 0x0BD4, 0x0000 }, { 0x0BD5, 0x0000 }, { 0x0BD6, 0x0000 }, { 0x0BD7, 0x0000 }, 
    { 0x0BD8, 0x0000 }, { 0x0BD9, 0x0000 }, { 0x0BDA, 0x0000 }, { 0x0BDB, 0x0000 }, 
    { 0x0BDC, 0x0000 }, { 0x0BDD, 0x0000 }, { 0x0BDE, 0x0000 }, { 0x0BDF, 0x0000 }, 
    { 0x0BE0, 0x0000 }, { 0x0BE1, 0x0000 }, { 0x0BE2, 0x0000 }, { 0x0BE3, 0x0000 }, 
    { 0x0BE4, 0x0000 }, { 0x0BE5, 0x0000 }, { 0x0BE6, 0x0000 }, { 0x0BE7, 0x0000 }, 
    { 0x0BE8, 0x0000 }, { 0x0BE9, 0x0000 }, { 0x0BEA, 0x0000 }, { 0x0BEB, 0x0000 }, 
    { 0x0BEC, 0x0000 }, { 0x0BED, 0x0000 }, { 0x0BEE, 0x0000 }, { 0x0BEF, 0x0000 }, 
    { 0x0BF0, 0x0000 }, { 0x0BF1, 0x0000 }, { 0x0BF2, 0x0000 }, { 0x0BF3, 0x0000 }, 
    { 0x0BF4, 0x0000 }, { 0x0BF5, 0x0000 }, { 0x0BF6, 0x0000 }, { 0x0BF7, 0x0000 }, 
    { 0x0BF8, 0x0000 }, { 0x0BF9, 0x0000 }, { 0x0BFA, 0x0000 }, { 0x0BFB, 0x0000 }, 
    { 0x0BFC, 0x0000 }, { 0x0BFD, 0x0000 }, { 0x0BFE, 0x0000 }, { 0x0BFF, 0x0000 }
  };

  const unsigned char TamilB80::lb[] = {
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
    LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, 
    LB_CM, LB_AL, LB_AL, LB_CM, LB_AL, LB_CM, LB_AL, LB_AL, 
    LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, 
    LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, 
    LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
  };

    const bool TamilB80::Combining[] = {
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 0, 0, 0, 1, 1, 
        1, 0, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool TamilB80::Non_spacing[] = {
        0, 0, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool TamilB80::Alphabetic[] = {
        0, 0, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 1, 1, 
        1, 0, 1, 1, 1, 1, 0, 0, 
        0, 1, 1, 0, 1, 0, 1, 1, 
        0, 0, 0, 1, 1, 0, 0, 0, 
        1, 1, 1, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 1, 
        1, 1, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 0, 0, 0, 1, 1, 
        1, 0, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool TamilB80::Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool TamilB80::Identifier_Part[] = {
        0, 0, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 1, 1, 
        1, 0, 1, 1, 1, 1, 0, 0, 
        0, 1, 1, 0, 1, 0, 1, 1, 
        0, 0, 0, 1, 1, 0, 0, 0, 
        1, 1, 1, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 1, 
        1, 1, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 0, 0, 0, 1, 1, 
        1, 0, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::TamilB80);
