/*$Id: 3200-32FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:13:20 +0100.
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
 
  class Enclosed_CJK_Letters_and_Months3200 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Enclosed_CJK_Letters_and_Months3200() {
      my_first_letter = 0x3200;
      my_last_letter  = 0x32FF;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Enclosed_CJK_Letters_and_Months3200() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Enclosed CJK Letters and Months";
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
      case 0x3220:
        return 1.000000;
        break;
      case 0x3221:
        return 2.000000;
        break;
      case 0x3222:
        return 3.000000;
        break;
      case 0x3223:
        return 4.000000;
        break;
      case 0x3224:
        return 5.000000;
        break;
      case 0x3225:
        return 6.000000;
        break;
      case 0x3226:
        return 7.000000;
        break;
      case 0x3227:
        return 8.000000;
        break;
      case 0x3228:
        return 9.000000;
        break;
      case 0x3229:
        return 10.000000;
        break;
      case 0x3280:
        return 1.000000;
        break;
      case 0x3281:
        return 2.000000;
        break;
      case 0x3282:
        return 3.000000;
        break;
      case 0x3283:
        return 4.000000;
        break;
      case 0x3284:
        return 5.000000;
        break;
      case 0x3285:
        return 6.000000;
        break;
      case 0x3286:
        return 7.000000;
        break;
      case 0x3287:
        return 8.000000;
        break;
      case 0x3288:
        return 9.000000;
        break;
      case 0x3289:
        return 10.000000;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(Enclosed_CJK_Letters_and_Months3200::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(BIDIR_L);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Enclosed_CJK_Letters_and_Months3200::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = Enclosed_CJK_Letters_and_Months3200::decompStr[_uc - my_first_letter][0];
      us[1] = Enclosed_CJK_Letters_and_Months3200::decompStr[_uc - my_first_letter][1];

      switch (_uc) {

      case 0x3200:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3201:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3202:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3203:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3204:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3205:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3206:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3207:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3208:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3209:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x320A:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x320B:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x320C:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x320D:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x320E:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x320F:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x3210:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x3211:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x3212:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x3213:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x3214:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x3215:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x3216:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x3217:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x3218:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x3219:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x321A:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x321B:
        us.resize(4);
        us[2] = 0x1161;
        us[3] = 0x0029;
        break;

      case 0x321C:
        us.resize(4);
        us[2] = 0x116E;
        us[3] = 0x0029;
        break;

      case 0x3220:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3221:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3222:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3223:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3224:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3225:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3226:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3227:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3228:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3229:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x322A:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x322B:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x322C:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x322D:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x322E:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x322F:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3230:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3231:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3232:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3233:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3234:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3235:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3236:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3237:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3238:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3239:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x323A:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x323B:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x323C:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x323D:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x323E:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x323F:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3240:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3241:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3242:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x3243:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x32C9:
        us.resize(3);
        us[2] = 0x6708;
        break;

      case 0x32CA:
        us.resize(3);
        us[2] = 0x6708;
        break;

      case 0x32CB:
        us.resize(3);
        us[2] = 0x6708;
        break;
      }
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
      return Babylon::Line_Break(LB_ID);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(EA_WIDTH_W);
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
      return 0;
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return 0;
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
    Enclosed_CJK_Letters_and_Months3200(const Enclosed_CJK_Letters_and_Months3200 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[256];
    static const unsigned char cat[256];
    static const unsigned char decomp[256];
    static const UCS2 decompStr[256][2];

  }; // class Enclosed_CJK_Letters_and_Months3200

  const bool Enclosed_CJK_Letters_and_Months3200::isdefined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0
  };

  const unsigned char Enclosed_CJK_Letters_and_Months3200::cat[] = {
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So
  };

  const unsigned char Enclosed_CJK_Letters_and_Months3200::decomp[] = {
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_NO_DECOMP
  };

  const UCS2 Enclosed_CJK_Letters_and_Months3200::decompStr[][2] = {
    { 0x0028, 0x1100 }, { 0x0028, 0x1102 }, { 0x0028, 0x1103 }, { 0x0028, 0x1105 }, 
    { 0x0028, 0x1106 }, { 0x0028, 0x1107 }, { 0x0028, 0x1109 }, { 0x0028, 0x110B }, 
    { 0x0028, 0x110C }, { 0x0028, 0x110E }, { 0x0028, 0x110F }, { 0x0028, 0x1110 }, 
    { 0x0028, 0x1111 }, { 0x0028, 0x1112 }, { 0x0028, 0x1100 }, { 0x0028, 0x1102 }, 
    { 0x0028, 0x1103 }, { 0x0028, 0x1105 }, { 0x0028, 0x1106 }, { 0x0028, 0x1107 }, 
    { 0x0028, 0x1109 }, { 0x0028, 0x110B }, { 0x0028, 0x110C }, { 0x0028, 0x110E }, 
    { 0x0028, 0x110F }, { 0x0028, 0x1110 }, { 0x0028, 0x1111 }, { 0x0028, 0x1112 }, 
    { 0x0028, 0x110C }, { 0x321D, 0x0000 }, { 0x321E, 0x0000 }, { 0x321F, 0x0000 }, 
    { 0x0028, 0x4E00 }, { 0x0028, 0x4E8C }, { 0x0028, 0x4E09 }, { 0x0028, 0x56DB }, 
    { 0x0028, 0x4E94 }, { 0x0028, 0x516D }, { 0x0028, 0x4E03 }, { 0x0028, 0x516B }, 
    { 0x0028, 0x4E5D }, { 0x0028, 0x5341 }, { 0x0028, 0x6708 }, { 0x0028, 0x706B }, 
    { 0x0028, 0x6C34 }, { 0x0028, 0x6728 }, { 0x0028, 0x91D1 }, { 0x0028, 0x571F }, 
    { 0x0028, 0x65E5 }, { 0x0028, 0x682A }, { 0x0028, 0x6709 }, { 0x0028, 0x793E }, 
    { 0x0028, 0x540D }, { 0x0028, 0x7279 }, { 0x0028, 0x8CA1 }, { 0x0028, 0x795D }, 
    { 0x0028, 0x52B4 }, { 0x0028, 0x4EE3 }, { 0x0028, 0x547C }, { 0x0028, 0x5B66 }, 
    { 0x0028, 0x76E3 }, { 0x0028, 0x4F01 }, { 0x0028, 0x8CC7 }, { 0x0028, 0x5354 }, 
    { 0x0028, 0x796D }, { 0x0028, 0x4F11 }, { 0x0028, 0x81EA }, { 0x0028, 0x81F3 }, 
    { 0x3244, 0x0000 }, { 0x3245, 0x0000 }, { 0x3246, 0x0000 }, { 0x3247, 0x0000 }, 
    { 0x3248, 0x0000 }, { 0x3249, 0x0000 }, { 0x324A, 0x0000 }, { 0x324B, 0x0000 }, 
    { 0x324C, 0x0000 }, { 0x324D, 0x0000 }, { 0x324E, 0x0000 }, { 0x324F, 0x0000 }, 
    { 0x3250, 0x0000 }, { 0x3251, 0x0000 }, { 0x3252, 0x0000 }, { 0x3253, 0x0000 }, 
    { 0x3254, 0x0000 }, { 0x3255, 0x0000 }, { 0x3256, 0x0000 }, { 0x3257, 0x0000 }, 
    { 0x3258, 0x0000 }, { 0x3259, 0x0000 }, { 0x325A, 0x0000 }, { 0x325B, 0x0000 }, 
    { 0x325C, 0x0000 }, { 0x325D, 0x0000 }, { 0x325E, 0x0000 }, { 0x325F, 0x0000 }, 
    { 0x1100, 0x0000 }, { 0x1102, 0x0000 }, { 0x1103, 0x0000 }, { 0x1105, 0x0000 }, 
    { 0x1106, 0x0000 }, { 0x1107, 0x0000 }, { 0x1109, 0x0000 }, { 0x110B, 0x0000 }, 
    { 0x110C, 0x0000 }, { 0x110E, 0x0000 }, { 0x110F, 0x0000 }, { 0x1110, 0x0000 }, 
    { 0x1111, 0x0000 }, { 0x1112, 0x0000 }, { 0x1100, 0x1161 }, { 0x1102, 0x1161 }, 
    { 0x1103, 0x1161 }, { 0x1105, 0x1161 }, { 0x1106, 0x1161 }, { 0x1107, 0x1161 }, 
    { 0x1109, 0x1161 }, { 0x110B, 0x1161 }, { 0x110C, 0x1161 }, { 0x110E, 0x1161 }, 
    { 0x110F, 0x1161 }, { 0x1110, 0x1161 }, { 0x1111, 0x1161 }, { 0x1112, 0x1161 }, 
    { 0x327C, 0x0000 }, { 0x327D, 0x0000 }, { 0x327E, 0x0000 }, { 0x327F, 0x0000 }, 
    { 0x4E00, 0x0000 }, { 0x4E8C, 0x0000 }, { 0x4E09, 0x0000 }, { 0x56DB, 0x0000 }, 
    { 0x4E94, 0x0000 }, { 0x516D, 0x0000 }, { 0x4E03, 0x0000 }, { 0x516B, 0x0000 }, 
    { 0x4E5D, 0x0000 }, { 0x5341, 0x0000 }, { 0x6708, 0x0000 }, { 0x706B, 0x0000 }, 
    { 0x6C34, 0x0000 }, { 0x6728, 0x0000 }, { 0x91D1, 0x0000 }, { 0x571F, 0x0000 }, 
    { 0x65E5, 0x0000 }, { 0x682A, 0x0000 }, { 0x6709, 0x0000 }, { 0x793E, 0x0000 }, 
    { 0x540D, 0x0000 }, { 0x7279, 0x0000 }, { 0x8CA1, 0x0000 }, { 0x795D, 0x0000 }, 
    { 0x52B4, 0x0000 }, { 0x79D8, 0x0000 }, { 0x7537, 0x0000 }, { 0x5973, 0x0000 }, 
    { 0x9069, 0x0000 }, { 0x512A, 0x0000 }, { 0x5370, 0x0000 }, { 0x6CE8, 0x0000 }, 
    { 0x9805, 0x0000 }, { 0x4F11, 0x0000 }, { 0x5199, 0x0000 }, { 0x6B63, 0x0000 }, 
    { 0x4E0A, 0x0000 }, { 0x4E2D, 0x0000 }, { 0x4E0B, 0x0000 }, { 0x5DE6, 0x0000 }, 
    { 0x53F3, 0x0000 }, { 0x533B, 0x0000 }, { 0x5B97, 0x0000 }, { 0x5B66, 0x0000 }, 
    { 0x76E3, 0x0000 }, { 0x4F01, 0x0000 }, { 0x8CC7, 0x0000 }, { 0x5354, 0x0000 }, 
    { 0x591C, 0x0000 }, { 0x32B1, 0x0000 }, { 0x32B2, 0x0000 }, { 0x32B3, 0x0000 }, 
    { 0x32B4, 0x0000 }, { 0x32B5, 0x0000 }, { 0x32B6, 0x0000 }, { 0x32B7, 0x0000 }, 
    { 0x32B8, 0x0000 }, { 0x32B9, 0x0000 }, { 0x32BA, 0x0000 }, { 0x32BB, 0x0000 }, 
    { 0x32BC, 0x0000 }, { 0x32BD, 0x0000 }, { 0x32BE, 0x0000 }, { 0x32BF, 0x0000 }, 
    { 0x0031, 0x6708 }, { 0x0032, 0x6708 }, { 0x0033, 0x6708 }, { 0x0034, 0x6708 }, 
    { 0x0035, 0x6708 }, { 0x0036, 0x6708 }, { 0x0037, 0x6708 }, { 0x0038, 0x6708 }, 
    { 0x0039, 0x6708 }, { 0x0031, 0x0030 }, { 0x0031, 0x0031 }, { 0x0031, 0x0032 }, 
    { 0x32CC, 0x0000 }, { 0x32CD, 0x0000 }, { 0x32CE, 0x0000 }, { 0x32CF, 0x0000 }, 
    { 0x30A2, 0x0000 }, { 0x30A4, 0x0000 }, { 0x30A6, 0x0000 }, { 0x30A8, 0x0000 }, 
    { 0x30AA, 0x0000 }, { 0x30AB, 0x0000 }, { 0x30AD, 0x0000 }, { 0x30AF, 0x0000 }, 
    { 0x30B1, 0x0000 }, { 0x30B3, 0x0000 }, { 0x30B5, 0x0000 }, { 0x30B7, 0x0000 }, 
    { 0x30B9, 0x0000 }, { 0x30BB, 0x0000 }, { 0x30BD, 0x0000 }, { 0x30BF, 0x0000 }, 
    { 0x30C1, 0x0000 }, { 0x30C4, 0x0000 }, { 0x30C6, 0x0000 }, { 0x30C8, 0x0000 }, 
    { 0x30CA, 0x0000 }, { 0x30CB, 0x0000 }, { 0x30CC, 0x0000 }, { 0x30CD, 0x0000 }, 
    { 0x30CE, 0x0000 }, { 0x30CF, 0x0000 }, { 0x30D2, 0x0000 }, { 0x30D5, 0x0000 }, 
    { 0x30D8, 0x0000 }, { 0x30DB, 0x0000 }, { 0x30DE, 0x0000 }, { 0x30DF, 0x0000 }, 
    { 0x30E0, 0x0000 }, { 0x30E1, 0x0000 }, { 0x30E2, 0x0000 }, { 0x30E4, 0x0000 }, 
    { 0x30E6, 0x0000 }, { 0x30E8, 0x0000 }, { 0x30E9, 0x0000 }, { 0x30EA, 0x0000 }, 
    { 0x30EB, 0x0000 }, { 0x30EC, 0x0000 }, { 0x30ED, 0x0000 }, { 0x30EF, 0x0000 }, 
    { 0x30F0, 0x0000 }, { 0x30F1, 0x0000 }, { 0x30F2, 0x0000 }, { 0x32FF, 0x0000 }
  };

}; // namespace Babylon
 
dload(Babylon::Enclosed_CJK_Letters_and_Months3200);
