/*$Id: 3300-33FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:13:24 +0100.
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
 
  class CJK_Compatibility3300 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    CJK_Compatibility3300() {
      my_first_letter = 0x3300;
      my_last_letter  = 0x33FF;
      // my_version="3.0.1" // Not yet supported!

    }


    ~CJK_Compatibility3300() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "CJK Compatibility";
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
      throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(CAT_So);
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
      return Babylon::Char_Decomp(CJK_Compatibility3300::decomp[_uc - my_first_letter]);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = CJK_Compatibility3300::decompStr[_uc - my_first_letter][0];
      us[1] = CJK_Compatibility3300::decompStr[_uc - my_first_letter][1];

      switch (_uc) {

      case 0x3300:
        us.resize(4);
        us[2] = 0x30FC;
        us[3] = 0x30C8;
        break;

      case 0x3301:
        us.resize(4);
        us[2] = 0x30D5;
        us[3] = 0x30A1;
        break;

      case 0x3302:
        us.resize(4);
        us[2] = 0x30DA;
        us[3] = 0x30A2;
        break;

      case 0x3303:
        us.resize(3);
        us[2] = 0x30EB;
        break;

      case 0x3304:
        us.resize(4);
        us[2] = 0x30F3;
        us[3] = 0x30B0;
        break;

      case 0x3305:
        us.resize(3);
        us[2] = 0x30C1;
        break;

      case 0x3306:
        us.resize(3);
        us[2] = 0x30F3;
        break;

      case 0x3307:
        us.resize(5);
        us[2] = 0x30AF;
        us[3] = 0x30FC;
        us[4] = 0x30C9;
        break;

      case 0x3308:
        us.resize(4);
        us[2] = 0x30AB;
        us[3] = 0x30FC;
        break;

      case 0x3309:
        us.resize(3);
        us[2] = 0x30B9;
        break;

      case 0x330A:
        us.resize(3);
        us[2] = 0x30E0;
        break;

      case 0x330B:
        us.resize(3);
        us[2] = 0x30EA;
        break;

      case 0x330C:
        us.resize(4);
        us[2] = 0x30C3;
        us[3] = 0x30C8;
        break;

      case 0x330D:
        us.resize(4);
        us[2] = 0x30EA;
        us[3] = 0x30FC;
        break;

      case 0x330E:
        us.resize(3);
        us[2] = 0x30F3;
        break;

      case 0x330F:
        us.resize(3);
        us[2] = 0x30DE;
        break;

      case 0x3311:
        us.resize(3);
        us[2] = 0x30FC;
        break;

      case 0x3312:
        us.resize(4);
        us[2] = 0x30EA;
        us[3] = 0x30FC;
        break;

      case 0x3313:
        us.resize(4);
        us[2] = 0x30C0;
        us[3] = 0x30FC;
        break;

      case 0x3315:
        us.resize(5);
        us[2] = 0x30B0;
        us[3] = 0x30E9;
        us[4] = 0x30E0;
        break;

      case 0x3316:
        us.resize(6);
        us[2] = 0x30E1;
        us[3] = 0x30FC;
        us[4] = 0x30C8;
        us[5] = 0x30EB;
        break;

      case 0x3317:
        us.resize(5);
        us[2] = 0x30EF;
        us[3] = 0x30C3;
        us[4] = 0x30C8;
        break;

      case 0x3318:
        us.resize(3);
        us[2] = 0x30E0;
        break;

      case 0x3319:
        us.resize(5);
        us[2] = 0x30E0;
        us[3] = 0x30C8;
        us[4] = 0x30F3;
        break;

      case 0x331A:
        us.resize(5);
        us[2] = 0x30BC;
        us[3] = 0x30A4;
        us[4] = 0x30ED;
        break;

      case 0x331B:
        us.resize(4);
        us[2] = 0x30FC;
        us[3] = 0x30CD;
        break;

      case 0x331C:
        us.resize(3);
        us[2] = 0x30B9;
        break;

      case 0x331D:
        us.resize(3);
        us[2] = 0x30CA;
        break;

      case 0x331E:
        us.resize(3);
        us[2] = 0x30DD;
        break;

      case 0x331F:
        us.resize(4);
        us[2] = 0x30AF;
        us[3] = 0x30EB;
        break;

      case 0x3320:
        us.resize(5);
        us[2] = 0x30C1;
        us[3] = 0x30FC;
        us[4] = 0x30E0;
        break;

      case 0x3321:
        us.resize(4);
        us[2] = 0x30F3;
        us[3] = 0x30B0;
        break;

      case 0x3322:
        us.resize(3);
        us[2] = 0x30C1;
        break;

      case 0x3323:
        us.resize(3);
        us[2] = 0x30C8;
        break;

      case 0x3324:
        us.resize(3);
        us[2] = 0x30B9;
        break;

      case 0x3329:
        us.resize(3);
        us[2] = 0x30C8;
        break;

      case 0x332A:
        us.resize(3);
        us[2] = 0x30C4;
        break;

      case 0x332B:
        us.resize(5);
        us[2] = 0x30BB;
        us[3] = 0x30F3;
        us[4] = 0x30C8;
        break;

      case 0x332C:
        us.resize(3);
        us[2] = 0x30C4;
        break;

      case 0x332D:
        us.resize(4);
        us[2] = 0x30EC;
        us[3] = 0x30EB;
        break;

      case 0x332E:
        us.resize(5);
        us[2] = 0x30B9;
        us[3] = 0x30C8;
        us[4] = 0x30EB;
        break;

      case 0x332F:
        us.resize(3);
        us[2] = 0x30EB;
        break;

      case 0x3332:
        us.resize(5);
        us[2] = 0x30E9;
        us[3] = 0x30C3;
        us[4] = 0x30C9;
        break;

      case 0x3333:
        us.resize(4);
        us[2] = 0x30FC;
        us[3] = 0x30C8;
        break;

      case 0x3334:
        us.resize(5);
        us[2] = 0x30B7;
        us[3] = 0x30A7;
        us[4] = 0x30EB;
        break;

      case 0x3335:
        us.resize(3);
        us[2] = 0x30F3;
        break;

      case 0x3336:
        us.resize(5);
        us[2] = 0x30BF;
        us[3] = 0x30FC;
        us[4] = 0x30EB;
        break;

      case 0x3338:
        us.resize(3);
        us[2] = 0x30D2;
        break;

      case 0x3339:
        us.resize(3);
        us[2] = 0x30C4;
        break;

      case 0x333A:
        us.resize(3);
        us[2] = 0x30B9;
        break;

      case 0x333B:
        us.resize(3);
        us[2] = 0x30B8;
        break;

      case 0x333C:
        us.resize(3);
        us[2] = 0x30BF;
        break;

      case 0x333D:
        us.resize(4);
        us[2] = 0x30F3;
        us[3] = 0x30C8;
        break;

      case 0x333E:
        us.resize(3);
        us[2] = 0x30C8;
        break;

      case 0x3340:
        us.resize(3);
        us[2] = 0x30C9;
        break;

      case 0x3341:
        us.resize(3);
        us[2] = 0x30EB;
        break;

      case 0x3342:
        us.resize(3);
        us[2] = 0x30F3;
        break;

      case 0x3343:
        us.resize(4);
        us[2] = 0x30AF;
        us[3] = 0x30ED;
        break;

      case 0x3344:
        us.resize(3);
        us[2] = 0x30EB;
        break;

      case 0x3345:
        us.resize(3);
        us[2] = 0x30CF;
        break;

      case 0x3346:
        us.resize(3);
        us[2] = 0x30AF;
        break;

      case 0x3347:
        us.resize(5);
        us[2] = 0x30B7;
        us[3] = 0x30E7;
        us[4] = 0x30F3;
        break;

      case 0x3348:
        us.resize(4);
        us[2] = 0x30ED;
        us[3] = 0x30F3;
        break;

      case 0x334A:
        us.resize(5);
        us[2] = 0x30D0;
        us[3] = 0x30FC;
        us[4] = 0x30EB;
        break;

      case 0x334C:
        us.resize(4);
        us[2] = 0x30C8;
        us[3] = 0x30F3;
        break;

      case 0x334D:
        us.resize(4);
        us[2] = 0x30C8;
        us[3] = 0x30EB;
        break;

      case 0x334E:
        us.resize(3);
        us[2] = 0x30C9;
        break;

      case 0x334F:
        us.resize(3);
        us[2] = 0x30EB;
        break;

      case 0x3350:
        us.resize(3);
        us[2] = 0x30F3;
        break;

      case 0x3351:
        us.resize(4);
        us[2] = 0x30C8;
        us[3] = 0x30EB;
        break;

      case 0x3353:
        us.resize(3);
        us[2] = 0x30FC;
        break;

      case 0x3354:
        us.resize(4);
        us[2] = 0x30D6;
        us[3] = 0x30EB;
        break;

      case 0x3356:
        us.resize(5);
        us[2] = 0x30C8;
        us[3] = 0x30B2;
        us[4] = 0x30F3;
        break;

      case 0x3357:
        us.resize(3);
        us[2] = 0x30C8;
        break;

      case 0x3362:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x3363:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x3364:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x3365:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x3366:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x3367:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x3368:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x3369:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x336A:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x336B:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x336C:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x336D:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x336E:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x336F:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x3370:
        us.resize(3);
        us[2] = 0x70B9;
        break;

      case 0x3371:
        us.resize(3);
        us[2] = 0x0061;
        break;

      case 0x3374:
        us.resize(3);
        us[2] = 0x0072;
        break;

      case 0x337F:
        us.resize(4);
        us[2] = 0x4F1A;
        us[3] = 0x793E;
        break;

      case 0x3388:
        us.resize(3);
        us[2] = 0x006C;
        break;

      case 0x3389:
        us.resize(4);
        us[2] = 0x0061;
        us[3] = 0x006C;
        break;

      case 0x3391:
        us.resize(3);
        us[2] = 0x007A;
        break;

      case 0x3392:
        us.resize(3);
        us[2] = 0x007A;
        break;

      case 0x3393:
        us.resize(3);
        us[2] = 0x007A;
        break;

      case 0x3394:
        us.resize(3);
        us[2] = 0x007A;
        break;

      case 0x339F:
        us.resize(3);
        us[2] = 0x00B2;
        break;

      case 0x33A0:
        us.resize(3);
        us[2] = 0x00B2;
        break;

      case 0x33A2:
        us.resize(3);
        us[2] = 0x00B2;
        break;

      case 0x33A3:
        us.resize(3);
        us[2] = 0x00B3;
        break;

      case 0x33A4:
        us.resize(3);
        us[2] = 0x00B3;
        break;

      case 0x33A6:
        us.resize(3);
        us[2] = 0x00B3;
        break;

      case 0x33A7:
        us.resize(3);
        us[2] = 0x0073;
        break;

      case 0x33A8:
        us.resize(4);
        us[2] = 0x0073;
        us[3] = 0x00B2;
        break;

      case 0x33AA:
        us.resize(3);
        us[2] = 0x0061;
        break;

      case 0x33AB:
        us.resize(3);
        us[2] = 0x0061;
        break;

      case 0x33AC:
        us.resize(3);
        us[2] = 0x0061;
        break;

      case 0x33AD:
        us.resize(3);
        us[2] = 0x0064;
        break;

      case 0x33AE:
        us.resize(5);
        us[2] = 0x0064;
        us[3] = 0x2215;
        us[4] = 0x0073;
        break;

      case 0x33AF:
        us.resize(6);
        us[2] = 0x0064;
        us[3] = 0x2215;
        us[4] = 0x0073;
        us[5] = 0x00B2;
        break;

      case 0x33C2:
        us.resize(4);
        us[2] = 0x006D;
        us[3] = 0x002E;
        break;

      case 0x33C6:
        us.resize(4);
        us[2] = 0x006B;
        us[3] = 0x0067;
        break;

      case 0x33C7:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x33D2:
        us.resize(3);
        us[2] = 0x0067;
        break;

      case 0x33D5:
        us.resize(3);
        us[2] = 0x006C;
        break;

      case 0x33D6:
        us.resize(3);
        us[2] = 0x006C;
        break;

      case 0x33D8:
        us.resize(4);
        us[2] = 0x006D;
        us[3] = 0x002E;
        break;

      case 0x33D9:
        us.resize(3);
        us[2] = 0x004D;
        break;

      case 0x33E9:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33EA:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33EB:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33EC:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33ED:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33EE:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33EF:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33F0:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33F1:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33F2:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33F3:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33F4:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33F5:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33F6:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33F7:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33F8:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33F9:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33FA:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33FB:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33FC:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33FD:
        us.resize(3);
        us[2] = 0x65E5;
        break;

      case 0x33FE:
        us.resize(3);
        us[2] = 0x65E5;
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
    CJK_Compatibility3300(const CJK_Compatibility3300 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[256];
    static const unsigned char decomp[256];
    static const UCS2 decompStr[256][2];

  }; // class CJK_Compatibility3300

  const bool CJK_Compatibility3300::isdefined[] = {
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
    1, 1, 1, 1, 1, 1, 1, 0, 
    0, 0, 0, 1, 1, 1, 1, 1, 
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
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0
  };

  const unsigned char CJK_Compatibility3300::decomp[] = {
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
    DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP
  };

  const UCS2 CJK_Compatibility3300::decompStr[][2] = {
    { 0x30A2, 0x30D1 }, { 0x30A2, 0x30EB }, { 0x30A2, 0x30F3 }, { 0x30A2, 0x30FC }, 
    { 0x30A4, 0x30CB }, { 0x30A4, 0x30F3 }, { 0x30A6, 0x30A9 }, { 0x30A8, 0x30B9 }, 
    { 0x30A8, 0x30FC }, { 0x30AA, 0x30F3 }, { 0x30AA, 0x30FC }, { 0x30AB, 0x30A4 }, 
    { 0x30AB, 0x30E9 }, { 0x30AB, 0x30ED }, { 0x30AC, 0x30ED }, { 0x30AC, 0x30F3 }, 
    { 0x30AE, 0x30AC }, { 0x30AE, 0x30CB }, { 0x30AD, 0x30E5 }, { 0x30AE, 0x30EB }, 
    { 0x30AD, 0x30ED }, { 0x30AD, 0x30ED }, { 0x30AD, 0x30ED }, { 0x30AD, 0x30ED }, 
    { 0x30B0, 0x30E9 }, { 0x30B0, 0x30E9 }, { 0x30AF, 0x30EB }, { 0x30AF, 0x30ED }, 
    { 0x30B1, 0x30FC }, { 0x30B3, 0x30EB }, { 0x30B3, 0x30FC }, { 0x30B5, 0x30A4 }, 
    { 0x30B5, 0x30F3 }, { 0x30B7, 0x30EA }, { 0x30BB, 0x30F3 }, { 0x30BB, 0x30F3 }, 
    { 0x30C0, 0x30FC }, { 0x30C7, 0x30B7 }, { 0x30C9, 0x30EB }, { 0x30C8, 0x30F3 }, 
    { 0x30CA, 0x30CE }, { 0x30CE, 0x30C3 }, { 0x30CF, 0x30A4 }, { 0x30D1, 0x30FC }, 
    { 0x30D1, 0x30FC }, { 0x30D0, 0x30FC }, { 0x30D4, 0x30A2 }, { 0x30D4, 0x30AF }, 
    { 0x30D4, 0x30B3 }, { 0x30D3, 0x30EB }, { 0x30D5, 0x30A1 }, { 0x30D5, 0x30A3 }, 
    { 0x30D6, 0x30C3 }, { 0x30D5, 0x30E9 }, { 0x30D8, 0x30AF }, { 0x30DA, 0x30BD }, 
    { 0x30DA, 0x30CB }, { 0x30D8, 0x30EB }, { 0x30DA, 0x30F3 }, { 0x30DA, 0x30FC }, 
    { 0x30D9, 0x30FC }, { 0x30DD, 0x30A4 }, { 0x30DC, 0x30EB }, { 0x30DB, 0x30F3 }, 
    { 0x30DD, 0x30F3 }, { 0x30DB, 0x30FC }, { 0x30DB, 0x30FC }, { 0x30DE, 0x30A4 }, 
    { 0x30DE, 0x30A4 }, { 0x30DE, 0x30C3 }, { 0x30DE, 0x30EB }, { 0x30DE, 0x30F3 }, 
    { 0x30DF, 0x30AF }, { 0x30DF, 0x30EA }, { 0x30DF, 0x30EA }, { 0x30E1, 0x30AC }, 
    { 0x30E1, 0x30AC }, { 0x30E1, 0x30FC }, { 0x30E4, 0x30FC }, { 0x30E4, 0x30FC }, 
    { 0x30E6, 0x30A2 }, { 0x30EA, 0x30C3 }, { 0x30EA, 0x30E9 }, { 0x30EB, 0x30D4 }, 
    { 0x30EB, 0x30FC }, { 0x30EC, 0x30E0 }, { 0x30EC, 0x30F3 }, { 0x30EF, 0x30C3 }, 
    { 0x0030, 0x70B9 }, { 0x0031, 0x70B9 }, { 0x0032, 0x70B9 }, { 0x0033, 0x70B9 }, 
    { 0x0034, 0x70B9 }, { 0x0035, 0x70B9 }, { 0x0036, 0x70B9 }, { 0x0037, 0x70B9 }, 
    { 0x0038, 0x70B9 }, { 0x0039, 0x70B9 }, { 0x0031, 0x0030 }, { 0x0031, 0x0031 }, 
    { 0x0031, 0x0032 }, { 0x0031, 0x0033 }, { 0x0031, 0x0034 }, { 0x0031, 0x0035 }, 
    { 0x0031, 0x0036 }, { 0x0031, 0x0037 }, { 0x0031, 0x0038 }, { 0x0031, 0x0039 }, 
    { 0x0032, 0x0030 }, { 0x0032, 0x0031 }, { 0x0032, 0x0032 }, { 0x0032, 0x0033 }, 
    { 0x0032, 0x0034 }, { 0x0068, 0x0050 }, { 0x0064, 0x0061 }, { 0x0041, 0x0055 }, 
    { 0x0062, 0x0061 }, { 0x006F, 0x0056 }, { 0x0070, 0x0063 }, { 0x3377, 0x0000 }, 
    { 0x3378, 0x0000 }, { 0x3379, 0x0000 }, { 0x337A, 0x0000 }, { 0x5E73, 0x6210 }, 
    { 0x662D, 0x548C }, { 0x5927, 0x6B63 }, { 0x660E, 0x6CBB }, { 0x682A, 0x5F0F }, 
    { 0x0070, 0x0041 }, { 0x006E, 0x0041 }, { 0x03BC, 0x0041 }, { 0x006D, 0x0041 }, 
    { 0x006B, 0x0041 }, { 0x004B, 0x0042 }, { 0x004D, 0x0042 }, { 0x0047, 0x0042 }, 
    { 0x0063, 0x0061 }, { 0x006B, 0x0063 }, { 0x0070, 0x0046 }, { 0x006E, 0x0046 }, 
    { 0x03BC, 0x0046 }, { 0x03BC, 0x0067 }, { 0x006D, 0x0067 }, { 0x006B, 0x0067 }, 
    { 0x0048, 0x007A }, { 0x006B, 0x0048 }, { 0x004D, 0x0048 }, { 0x0047, 0x0048 }, 
    { 0x0054, 0x0048 }, { 0x03BC, 0x2113 }, { 0x006D, 0x2113 }, { 0x0064, 0x2113 }, 
    { 0x006B, 0x2113 }, { 0x0066, 0x006D }, { 0x006E, 0x006D }, { 0x03BC, 0x006D }, 
    { 0x006D, 0x006D }, { 0x0063, 0x006D }, { 0x006B, 0x006D }, { 0x006D, 0x006D }, 
    { 0x0063, 0x006D }, { 0x006D, 0x00B2 }, { 0x006B, 0x006D }, { 0x006D, 0x006D }, 
    { 0x0063, 0x006D }, { 0x006D, 0x00B3 }, { 0x006B, 0x006D }, { 0x006D, 0x2215 }, 
    { 0x006D, 0x2215 }, { 0x0050, 0x0061 }, { 0x006B, 0x0050 }, { 0x004D, 0x0050 }, 
    { 0x0047, 0x0050 }, { 0x0072, 0x0061 }, { 0x0072, 0x0061 }, { 0x0072, 0x0061 }, 
    { 0x0070, 0x0073 }, { 0x006E, 0x0073 }, { 0x03BC, 0x0073 }, { 0x006D, 0x0073 }, 
    { 0x0070, 0x0056 }, { 0x006E, 0x0056 }, { 0x03BC, 0x0056 }, { 0x006D, 0x0056 }, 
    { 0x006B, 0x0056 }, { 0x004D, 0x0056 }, { 0x0070, 0x0057 }, { 0x006E, 0x0057 }, 
    { 0x03BC, 0x0057 }, { 0x006D, 0x0057 }, { 0x006B, 0x0057 }, { 0x004D, 0x0057 }, 
    { 0x006B, 0x03A9 }, { 0x004D, 0x03A9 }, { 0x0061, 0x002E }, { 0x0042, 0x0071 }, 
    { 0x0063, 0x0063 }, { 0x0063, 0x0064 }, { 0x0043, 0x2215 }, { 0x0043, 0x006F }, 
    { 0x0064, 0x0042 }, { 0x0047, 0x0079 }, { 0x0068, 0x0061 }, { 0x0048, 0x0050 }, 
    { 0x0069, 0x006E }, { 0x004B, 0x004B }, { 0x004B, 0x004D }, { 0x006B, 0x0074 }, 
    { 0x006C, 0x006D }, { 0x006C, 0x006E }, { 0x006C, 0x006F }, { 0x006C, 0x0078 }, 
    { 0x006D, 0x0062 }, { 0x006D, 0x0069 }, { 0x006D, 0x006F }, { 0x0050, 0x0048 }, 
    { 0x0070, 0x002E }, { 0x0050, 0x0050 }, { 0x0050, 0x0052 }, { 0x0073, 0x0072 }, 
    { 0x0053, 0x0076 }, { 0x0057, 0x0062 }, { 0x33DE, 0x0000 }, { 0x33DF, 0x0000 }, 
    { 0x0031, 0x65E5 }, { 0x0032, 0x65E5 }, { 0x0033, 0x65E5 }, { 0x0034, 0x65E5 }, 
    { 0x0035, 0x65E5 }, { 0x0036, 0x65E5 }, { 0x0037, 0x65E5 }, { 0x0038, 0x65E5 }, 
    { 0x0039, 0x65E5 }, { 0x0031, 0x0030 }, { 0x0031, 0x0031 }, { 0x0031, 0x0032 }, 
    { 0x0031, 0x0033 }, { 0x0031, 0x0034 }, { 0x0031, 0x0035 }, { 0x0031, 0x0036 }, 
    { 0x0031, 0x0037 }, { 0x0031, 0x0038 }, { 0x0031, 0x0039 }, { 0x0032, 0x0030 }, 
    { 0x0032, 0x0031 }, { 0x0032, 0x0032 }, { 0x0032, 0x0033 }, { 0x0032, 0x0034 }, 
    { 0x0032, 0x0035 }, { 0x0032, 0x0036 }, { 0x0032, 0x0037 }, { 0x0032, 0x0038 }, 
    { 0x0032, 0x0039 }, { 0x0033, 0x0030 }, { 0x0033, 0x0031 }, { 0x33FF, 0x0000 }
  };

}; // namespace Babylon
 
dload(Babylon::CJK_Compatibility3300);
