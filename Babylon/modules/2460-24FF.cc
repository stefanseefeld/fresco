/*$Id: 2460-24FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 15 Nov 2000 23:27:09 +0100.
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
 
  class Enclosed_Alphanumerics : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Enclosed_Alphanumerics() {
      my_first_letter = 0x2460;
      my_last_letter  = 0x24FF;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Enclosed_Alphanumerics() {
    }

    _UCS4 firstLetter() {
      return my_first_letter;
    }
 
    _UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const _UCS4 _uc) const {
      return "Enclosed Alphanumerics";
    }

    bool isDefined(const _UCS4 _uc) const {
      return (isdefined[_uc - my_first_letter]);
    }

    _UCS4 uppercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Enclosed_Alphanumerics::upper[_uc - my_first_letter];
    }

    _UCS4 lowercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Enclosed_Alphanumerics::lower[_uc - my_first_letter];
    }

    _UCS4 titlecase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Enclosed_Alphanumerics::title[_uc - my_first_letter];
    }

    int decDigitValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_DEC_DIGIT_VALUE);
    }

    int digitValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
      case 0x2460:
        return 1;
        break;
      case 0x2461:
        return 2;
        break;
      case 0x2462:
        return 3;
        break;
      case 0x2463:
        return 4;
        break;
      case 0x2464:
        return 5;
        break;
      case 0x2465:
        return 6;
        break;
      case 0x2466:
        return 7;
        break;
      case 0x2467:
        return 8;
        break;
      case 0x2468:
        return 9;
        break;
      case 0x2474:
        return 1;
        break;
      case 0x2475:
        return 2;
        break;
      case 0x2476:
        return 3;
        break;
      case 0x2477:
        return 4;
        break;
      case 0x2478:
        return 5;
        break;
      case 0x2479:
        return 6;
        break;
      case 0x247A:
        return 7;
        break;
      case 0x247B:
        return 8;
        break;
      case 0x247C:
        return 9;
        break;
      case 0x2488:
        return 1;
        break;
      case 0x2489:
        return 2;
        break;
      case 0x248A:
        return 3;
        break;
      case 0x248B:
        return 4;
        break;
      case 0x248C:
        return 5;
        break;
      case 0x248D:
        return 6;
        break;
      case 0x248E:
        return 7;
        break;
      case 0x248F:
        return 8;
        break;
      case 0x2490:
        return 9;
        break;
      case 0x24EA:
        return 0;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_DIGIT_VALUE);
      }
    }

    float numericValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
      case 0x2460:
        return 1.000000;
        break;
      case 0x2461:
        return 2.000000;
        break;
      case 0x2462:
        return 3.000000;
        break;
      case 0x2463:
        return 4.000000;
        break;
      case 0x2464:
        return 5.000000;
        break;
      case 0x2465:
        return 6.000000;
        break;
      case 0x2466:
        return 7.000000;
        break;
      case 0x2467:
        return 8.000000;
        break;
      case 0x2468:
        return 9.000000;
        break;
      case 0x2469:
        return 10.000000;
        break;
      case 0x246A:
        return 11.000000;
        break;
      case 0x246B:
        return 12.000000;
        break;
      case 0x246C:
        return 13.000000;
        break;
      case 0x246D:
        return 14.000000;
        break;
      case 0x246E:
        return 15.000000;
        break;
      case 0x246F:
        return 16.000000;
        break;
      case 0x2470:
        return 17.000000;
        break;
      case 0x2471:
        return 18.000000;
        break;
      case 0x2472:
        return 19.000000;
        break;
      case 0x2473:
        return 20.000000;
        break;
      case 0x2474:
        return 1.000000;
        break;
      case 0x2475:
        return 2.000000;
        break;
      case 0x2476:
        return 3.000000;
        break;
      case 0x2477:
        return 4.000000;
        break;
      case 0x2478:
        return 5.000000;
        break;
      case 0x2479:
        return 6.000000;
        break;
      case 0x247A:
        return 7.000000;
        break;
      case 0x247B:
        return 8.000000;
        break;
      case 0x247C:
        return 9.000000;
        break;
      case 0x247D:
        return 10.000000;
        break;
      case 0x247E:
        return 11.000000;
        break;
      case 0x247F:
        return 12.000000;
        break;
      case 0x2480:
        return 13.000000;
        break;
      case 0x2481:
        return 14.000000;
        break;
      case 0x2482:
        return 15.000000;
        break;
      case 0x2483:
        return 16.000000;
        break;
      case 0x2484:
        return 17.000000;
        break;
      case 0x2485:
        return 18.000000;
        break;
      case 0x2486:
        return 19.000000;
        break;
      case 0x2487:
        return 20.000000;
        break;
      case 0x2488:
        return 1.000000;
        break;
      case 0x2489:
        return 2.000000;
        break;
      case 0x248A:
        return 3.000000;
        break;
      case 0x248B:
        return 4.000000;
        break;
      case 0x248C:
        return 5.000000;
        break;
      case 0x248D:
        return 6.000000;
        break;
      case 0x248E:
        return 7.000000;
        break;
      case 0x248F:
        return 8.000000;
        break;
      case 0x2490:
        return 9.000000;
        break;
      case 0x2491:
        return 10.000000;
        break;
      case 0x2492:
        return 11.000000;
        break;
      case 0x2493:
        return 12.000000;
        break;
      case 0x2494:
        return 13.000000;
        break;
      case 0x2495:
        return 14.000000;
        break;
      case 0x2496:
        return 15.000000;
        break;
      case 0x2497:
        return 16.000000;
        break;
      case 0x2498:
        return 17.000000;
        break;
      case 0x2499:
        return 18.000000;
        break;
      case 0x249A:
        return 19.000000;
        break;
      case 0x249B:
        return 20.000000;
        break;
      case 0x24EA:
        return 0.000000;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(Enclosed_Alphanumerics::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Enclosed_Alphanumerics::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Enclosed_Alphanumerics::decomp[_uc - my_first_letter]);
    }

    _UTF32String decompose(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::_UTF32String us;
      us.resize(2);
      us[0] = Enclosed_Alphanumerics::decompStr[_uc - my_first_letter][0];
      us[1] = Enclosed_Alphanumerics::decompStr[_uc - my_first_letter][1];

      switch (_uc) {

      case 0x2474:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x2475:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x2476:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x2477:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x2478:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x2479:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x247A:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x247B:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x247C:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x247D:
        us.resize(4);
        us[2] = 0x0030;
        us[3] = 0x0029;
        break;

      case 0x247E:
        us.resize(4);
        us[2] = 0x0031;
        us[3] = 0x0029;
        break;

      case 0x247F:
        us.resize(4);
        us[2] = 0x0032;
        us[3] = 0x0029;
        break;

      case 0x2480:
        us.resize(4);
        us[2] = 0x0033;
        us[3] = 0x0029;
        break;

      case 0x2481:
        us.resize(4);
        us[2] = 0x0034;
        us[3] = 0x0029;
        break;

      case 0x2482:
        us.resize(4);
        us[2] = 0x0035;
        us[3] = 0x0029;
        break;

      case 0x2483:
        us.resize(4);
        us[2] = 0x0036;
        us[3] = 0x0029;
        break;

      case 0x2484:
        us.resize(4);
        us[2] = 0x0037;
        us[3] = 0x0029;
        break;

      case 0x2485:
        us.resize(4);
        us[2] = 0x0038;
        us[3] = 0x0029;
        break;

      case 0x2486:
        us.resize(4);
        us[2] = 0x0039;
        us[3] = 0x0029;
        break;

      case 0x2487:
        us.resize(4);
        us[2] = 0x0030;
        us[3] = 0x0029;
        break;

      case 0x2491:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x2492:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x2493:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x2494:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x2495:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x2496:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x2497:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x2498:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x2499:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x249A:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x249B:
        us.resize(3);
        us[2] = 0x002E;
        break;

      case 0x249C:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x249D:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x249E:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x249F:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24A0:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24A1:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24A2:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24A3:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24A4:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24A5:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24A6:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24A7:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24A8:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24A9:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24AA:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24AB:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24AC:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24AD:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24AE:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24AF:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24B0:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24B1:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24B2:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24B3:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24B4:
        us.resize(3);
        us[2] = 0x0029;
        break;

      case 0x24B5:
        us.resize(3);
        us[2] = 0x0029;
        break;
      }
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool mustMirror(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return 0;
    }

    Line_Break linebreak(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Line_Break(Enclosed_Alphanumerics::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(Enclosed_Alphanumerics::ea[_uc - my_first_letter]);
    }

    _UCS4 compose (const _UCS4 starter, const _UCS4 last) {
      return 0;
    }

    bool is_Zero_width(const _UCS4 _uc) const {
      return 0;
    }

    bool is_White_space(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Non_break(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Join_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Format_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Dash(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Hyphen(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Math(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Paired_Punctuation(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Left_of_Pair(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Combining(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Non_spacing(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Hex_Digit(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Alphabetic(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Diacritic(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Extender(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Ignorable_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Embedding_or_Override(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Uppercase(const _UCS4 _uc) const {
      return Enclosed_Alphanumerics::Uppercase[_uc - my_first_letter];
    }

    bool is_Lowercase(const _UCS4 _uc) const {
      return Enclosed_Alphanumerics::Lowercase[_uc - my_first_letter];
    }

    bool is_Space(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zs);
    }

    bool is_ISO_Control(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Cc);
    }

    bool is_Punctuation(const _UCS4 _uc) const {
      return (isDefined(_uc) && (category(_uc) == CAT_Pc ||
                                 category(_uc) == CAT_Pd ||
                                 category(_uc) == CAT_Ps ||
                                 category(_uc) == CAT_Pe ||
                                 category(_uc) == CAT_Pi ||
                                 category(_uc) == CAT_Pf ||
                                 category(_uc) == CAT_Po)
             );
    }

    bool is_Line_Separator(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zl);
    }

    bool is_Paragraph_Separator(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zp);
    }

    bool is_Currency_Symbol(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Sc);
    }

    bool is_Titlecase(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Lt);
    }


  private:
    // functions
    Enclosed_Alphanumerics(const Enclosed_Alphanumerics &) {}
 
    Babylon::_UCS4 my_first_letter;
    Babylon::_UCS4 my_last_letter;
    static const bool isdefined[160];
    static const _UCS4 upper[160];
    static const _UCS4 lower[160];
    static const _UCS4 title[160];
    static const unsigned char cat[160];
    static const unsigned char bidir[160];
    static const unsigned char decomp[160];
    static const _UCS2 decompStr[160][2];
    static const unsigned char lb[160];
    static const unsigned char ea[160];
    static const bool Uppercase[160];
    static const bool Lowercase[160];

  }; // class Enclosed_Alphanumerics

  const bool Enclosed_Alphanumerics::isdefined[] = {
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
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const _UCS4 Enclosed_Alphanumerics::upper[] = {
    0x2460, 0x2461, 0x2462, 0x2463, 0x2464, 0x2465, 0x2466, 0x2467, 
    0x2468, 0x2469, 0x246A, 0x246B, 0x246C, 0x246D, 0x246E, 0x246F, 
    0x2470, 0x2471, 0x2472, 0x2473, 0x2474, 0x2475, 0x2476, 0x2477, 
    0x2478, 0x2479, 0x247A, 0x247B, 0x247C, 0x247D, 0x247E, 0x247F, 
    0x2480, 0x2481, 0x2482, 0x2483, 0x2484, 0x2485, 0x2486, 0x2487, 
    0x2488, 0x2489, 0x248A, 0x248B, 0x248C, 0x248D, 0x248E, 0x248F, 
    0x2490, 0x2491, 0x2492, 0x2493, 0x2494, 0x2495, 0x2496, 0x2497, 
    0x2498, 0x2499, 0x249A, 0x249B, 0x249C, 0x249D, 0x249E, 0x249F, 
    0x24A0, 0x24A1, 0x24A2, 0x24A3, 0x24A4, 0x24A5, 0x24A6, 0x24A7, 
    0x24A8, 0x24A9, 0x24AA, 0x24AB, 0x24AC, 0x24AD, 0x24AE, 0x24AF, 
    0x24B0, 0x24B1, 0x24B2, 0x24B3, 0x24B4, 0x24B5, 0x24B6, 0x24B7, 
    0x24B8, 0x24B9, 0x24BA, 0x24BB, 0x24BC, 0x24BD, 0x24BE, 0x24BF, 
    0x24C0, 0x24C1, 0x24C2, 0x24C3, 0x24C4, 0x24C5, 0x24C6, 0x24C7, 
    0x24C8, 0x24C9, 0x24CA, 0x24CB, 0x24CC, 0x24CD, 0x24CE, 0x24CF, 
    0x24B6, 0x24B7, 0x24B8, 0x24B9, 0x24BA, 0x24BB, 0x24BC, 0x24BD, 
    0x24BE, 0x24BF, 0x24C0, 0x24C1, 0x24C2, 0x24C3, 0x24C4, 0x24C5, 
    0x24C6, 0x24C7, 0x24C8, 0x24C9, 0x24CA, 0x24CB, 0x24CC, 0x24CD, 
    0x24CE, 0x24CF, 0x24EA, 0x24EB, 0x24EC, 0x24ED, 0x24EE, 0x24EF, 
    0x24F0, 0x24F1, 0x24F2, 0x24F3, 0x24F4, 0x24F5, 0x24F6, 0x24F7, 
    0x24F8, 0x24F9, 0x24FA, 0x24FB, 0x24FC, 0x24FD, 0x24FE, 0x24FF
  };

  const _UCS4 Enclosed_Alphanumerics::lower[] = {
    0x2460, 0x2461, 0x2462, 0x2463, 0x2464, 0x2465, 0x2466, 0x2467, 
    0x2468, 0x2469, 0x246A, 0x246B, 0x246C, 0x246D, 0x246E, 0x246F, 
    0x2470, 0x2471, 0x2472, 0x2473, 0x2474, 0x2475, 0x2476, 0x2477, 
    0x2478, 0x2479, 0x247A, 0x247B, 0x247C, 0x247D, 0x247E, 0x247F, 
    0x2480, 0x2481, 0x2482, 0x2483, 0x2484, 0x2485, 0x2486, 0x2487, 
    0x2488, 0x2489, 0x248A, 0x248B, 0x248C, 0x248D, 0x248E, 0x248F, 
    0x2490, 0x2491, 0x2492, 0x2493, 0x2494, 0x2495, 0x2496, 0x2497, 
    0x2498, 0x2499, 0x249A, 0x249B, 0x249C, 0x249D, 0x249E, 0x249F, 
    0x24A0, 0x24A1, 0x24A2, 0x24A3, 0x24A4, 0x24A5, 0x24A6, 0x24A7, 
    0x24A8, 0x24A9, 0x24AA, 0x24AB, 0x24AC, 0x24AD, 0x24AE, 0x24AF, 
    0x24B0, 0x24B1, 0x24B2, 0x24B3, 0x24B4, 0x24B5, 0x24D0, 0x24D1, 
    0x24D2, 0x24D3, 0x24D4, 0x24D5, 0x24D6, 0x24D7, 0x24D8, 0x24D9, 
    0x24DA, 0x24DB, 0x24DC, 0x24DD, 0x24DE, 0x24DF, 0x24E0, 0x24E1, 
    0x24E2, 0x24E3, 0x24E4, 0x24E5, 0x24E6, 0x24E7, 0x24E8, 0x24E9, 
    0x24D0, 0x24D1, 0x24D2, 0x24D3, 0x24D4, 0x24D5, 0x24D6, 0x24D7, 
    0x24D8, 0x24D9, 0x24DA, 0x24DB, 0x24DC, 0x24DD, 0x24DE, 0x24DF, 
    0x24E0, 0x24E1, 0x24E2, 0x24E3, 0x24E4, 0x24E5, 0x24E6, 0x24E7, 
    0x24E8, 0x24E9, 0x24EA, 0x24EB, 0x24EC, 0x24ED, 0x24EE, 0x24EF, 
    0x24F0, 0x24F1, 0x24F2, 0x24F3, 0x24F4, 0x24F5, 0x24F6, 0x24F7, 
    0x24F8, 0x24F9, 0x24FA, 0x24FB, 0x24FC, 0x24FD, 0x24FE, 0x24FF
  };

  const _UCS4 Enclosed_Alphanumerics::title[] = {
    0x2460, 0x2461, 0x2462, 0x2463, 0x2464, 0x2465, 0x2466, 0x2467, 
    0x2468, 0x2469, 0x246A, 0x246B, 0x246C, 0x246D, 0x246E, 0x246F, 
    0x2470, 0x2471, 0x2472, 0x2473, 0x2474, 0x2475, 0x2476, 0x2477, 
    0x2478, 0x2479, 0x247A, 0x247B, 0x247C, 0x247D, 0x247E, 0x247F, 
    0x2480, 0x2481, 0x2482, 0x2483, 0x2484, 0x2485, 0x2486, 0x2487, 
    0x2488, 0x2489, 0x248A, 0x248B, 0x248C, 0x248D, 0x248E, 0x248F, 
    0x2490, 0x2491, 0x2492, 0x2493, 0x2494, 0x2495, 0x2496, 0x2497, 
    0x2498, 0x2499, 0x249A, 0x249B, 0x249C, 0x249D, 0x249E, 0x249F, 
    0x24A0, 0x24A1, 0x24A2, 0x24A3, 0x24A4, 0x24A5, 0x24A6, 0x24A7, 
    0x24A8, 0x24A9, 0x24AA, 0x24AB, 0x24AC, 0x24AD, 0x24AE, 0x24AF, 
    0x24B0, 0x24B1, 0x24B2, 0x24B3, 0x24B4, 0x24B5, 0x24B6, 0x24B7, 
    0x24B8, 0x24B9, 0x24BA, 0x24BB, 0x24BC, 0x24BD, 0x24BE, 0x24BF, 
    0x24C0, 0x24C1, 0x24C2, 0x24C3, 0x24C4, 0x24C5, 0x24C6, 0x24C7, 
    0x24C8, 0x24C9, 0x24CA, 0x24CB, 0x24CC, 0x24CD, 0x24CE, 0x24CF, 
    0x24B6, 0x24B7, 0x24B8, 0x24B9, 0x24BA, 0x24BB, 0x24BC, 0x24BD, 
    0x24BE, 0x24BF, 0x24C0, 0x24C1, 0x24C2, 0x24C3, 0x24C4, 0x24C5, 
    0x24C6, 0x24C7, 0x24C8, 0x24C9, 0x24CA, 0x24CB, 0x24CC, 0x24CD, 
    0x24CE, 0x24CF, 0x24EA, 0x24EB, 0x24EC, 0x24ED, 0x24EE, 0x24EF, 
    0x24F0, 0x24F1, 0x24F2, 0x24F3, 0x24F4, 0x24F5, 0x24F6, 0x24F7, 
    0x24F8, 0x24F9, 0x24FA, 0x24FB, 0x24FC, 0x24FD, 0x24FE, 0x24FF
  };

  const unsigned char Enclosed_Alphanumerics::cat[] = {
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
    CAT_So, CAT_So, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
    CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No
  };

  const unsigned char Enclosed_Alphanumerics::bidir[] = {
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN
  };

  const unsigned char Enclosed_Alphanumerics::decomp[] = {
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
    DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const _UCS2 Enclosed_Alphanumerics::decompStr[][2] = {
    { 0x0031, 0x0000 }, { 0x0032, 0x0000 }, { 0x0033, 0x0000 }, { 0x0034, 0x0000 }, 
    { 0x0035, 0x0000 }, { 0x0036, 0x0000 }, { 0x0037, 0x0000 }, { 0x0038, 0x0000 }, 
    { 0x0039, 0x0000 }, { 0x0031, 0x0030 }, { 0x0031, 0x0031 }, { 0x0031, 0x0032 }, 
    { 0x0031, 0x0033 }, { 0x0031, 0x0034 }, { 0x0031, 0x0035 }, { 0x0031, 0x0036 }, 
    { 0x0031, 0x0037 }, { 0x0031, 0x0038 }, { 0x0031, 0x0039 }, { 0x0032, 0x0030 }, 
    { 0x0028, 0x0031 }, { 0x0028, 0x0032 }, { 0x0028, 0x0033 }, { 0x0028, 0x0034 }, 
    { 0x0028, 0x0035 }, { 0x0028, 0x0036 }, { 0x0028, 0x0037 }, { 0x0028, 0x0038 }, 
    { 0x0028, 0x0039 }, { 0x0028, 0x0031 }, { 0x0028, 0x0031 }, { 0x0028, 0x0031 }, 
    { 0x0028, 0x0031 }, { 0x0028, 0x0031 }, { 0x0028, 0x0031 }, { 0x0028, 0x0031 }, 
    { 0x0028, 0x0031 }, { 0x0028, 0x0031 }, { 0x0028, 0x0031 }, { 0x0028, 0x0032 }, 
    { 0x0031, 0x002E }, { 0x0032, 0x002E }, { 0x0033, 0x002E }, { 0x0034, 0x002E }, 
    { 0x0035, 0x002E }, { 0x0036, 0x002E }, { 0x0037, 0x002E }, { 0x0038, 0x002E }, 
    { 0x0039, 0x002E }, { 0x0031, 0x0030 }, { 0x0031, 0x0031 }, { 0x0031, 0x0032 }, 
    { 0x0031, 0x0033 }, { 0x0031, 0x0034 }, { 0x0031, 0x0035 }, { 0x0031, 0x0036 }, 
    { 0x0031, 0x0037 }, { 0x0031, 0x0038 }, { 0x0031, 0x0039 }, { 0x0032, 0x0030 }, 
    { 0x0028, 0x0061 }, { 0x0028, 0x0062 }, { 0x0028, 0x0063 }, { 0x0028, 0x0064 }, 
    { 0x0028, 0x0065 }, { 0x0028, 0x0066 }, { 0x0028, 0x0067 }, { 0x0028, 0x0068 }, 
    { 0x0028, 0x0069 }, { 0x0028, 0x006A }, { 0x0028, 0x006B }, { 0x0028, 0x006C }, 
    { 0x0028, 0x006D }, { 0x0028, 0x006E }, { 0x0028, 0x006F }, { 0x0028, 0x0070 }, 
    { 0x0028, 0x0071 }, { 0x0028, 0x0072 }, { 0x0028, 0x0073 }, { 0x0028, 0x0074 }, 
    { 0x0028, 0x0075 }, { 0x0028, 0x0076 }, { 0x0028, 0x0077 }, { 0x0028, 0x0078 }, 
    { 0x0028, 0x0079 }, { 0x0028, 0x007A }, { 0x0041, 0x0000 }, { 0x0042, 0x0000 }, 
    { 0x0043, 0x0000 }, { 0x0044, 0x0000 }, { 0x0045, 0x0000 }, { 0x0046, 0x0000 }, 
    { 0x0047, 0x0000 }, { 0x0048, 0x0000 }, { 0x0049, 0x0000 }, { 0x004A, 0x0000 }, 
    { 0x004B, 0x0000 }, { 0x004C, 0x0000 }, { 0x004D, 0x0000 }, { 0x004E, 0x0000 }, 
    { 0x004F, 0x0000 }, { 0x0050, 0x0000 }, { 0x0051, 0x0000 }, { 0x0052, 0x0000 }, 
    { 0x0053, 0x0000 }, { 0x0054, 0x0000 }, { 0x0055, 0x0000 }, { 0x0056, 0x0000 }, 
    { 0x0057, 0x0000 }, { 0x0058, 0x0000 }, { 0x0059, 0x0000 }, { 0x005A, 0x0000 }, 
    { 0x0061, 0x0000 }, { 0x0062, 0x0000 }, { 0x0063, 0x0000 }, { 0x0064, 0x0000 }, 
    { 0x0065, 0x0000 }, { 0x0066, 0x0000 }, { 0x0067, 0x0000 }, { 0x0068, 0x0000 }, 
    { 0x0069, 0x0000 }, { 0x006A, 0x0000 }, { 0x006B, 0x0000 }, { 0x006C, 0x0000 }, 
    { 0x006D, 0x0000 }, { 0x006E, 0x0000 }, { 0x006F, 0x0000 }, { 0x0070, 0x0000 }, 
    { 0x0071, 0x0000 }, { 0x0072, 0x0000 }, { 0x0073, 0x0000 }, { 0x0074, 0x0000 }, 
    { 0x0075, 0x0000 }, { 0x0076, 0x0000 }, { 0x0077, 0x0000 }, { 0x0078, 0x0000 }, 
    { 0x0079, 0x0000 }, { 0x007A, 0x0000 }, { 0x0030, 0x0000 }, { 0x24EB, 0x0000 }, 
    { 0x24EC, 0x0000 }, { 0x24ED, 0x0000 }, { 0x24EE, 0x0000 }, { 0x24EF, 0x0000 }, 
    { 0x24F0, 0x0000 }, { 0x24F1, 0x0000 }, { 0x24F2, 0x0000 }, { 0x24F3, 0x0000 }, 
    { 0x24F4, 0x0000 }, { 0x24F5, 0x0000 }, { 0x24F6, 0x0000 }, { 0x24F7, 0x0000 }, 
    { 0x24F8, 0x0000 }, { 0x24F9, 0x0000 }, { 0x24FA, 0x0000 }, { 0x24FB, 0x0000 }, 
    { 0x24FC, 0x0000 }, { 0x24FD, 0x0000 }, { 0x24FE, 0x0000 }, { 0x24FF, 0x0000 }
  };

  const unsigned char Enclosed_Alphanumerics::lb[] = {
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
    LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI
  };

  const unsigned char Enclosed_Alphanumerics::ea[] = {
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
    EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A
  };

    const bool Enclosed_Alphanumerics::Uppercase[] = {
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
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Enclosed_Alphanumerics::Lowercase[] = {
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
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Enclosed_Alphanumerics);
