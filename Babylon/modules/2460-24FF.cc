/*$Id: 2460-24FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon,  8 Jan 2001 23:32:20 +0100.
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
#include <bitset>

namespace Babylon {

  class Enclosed_Alphanumerics2460 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Enclosed_Alphanumerics2460() {
      m_first_letter = 0x2460;
      m_last_letter  = 0x24FF;
      // m_version="3.0.1" // Not yet supported!

    }


    ~Enclosed_Alphanumerics2460() {
    }

    UCS4 firstLetter() {
      return m_first_letter;
    }

    UCS4 lastLetter() {
      return m_last_letter;
    }

    bool is_undef_block() const {
      return 0;
    }

    // query functions:

    string blockname(const UCS4 uc) const {
      return "Enclosed Alphanumerics";
    }

    bool is_defined(const UCS4 uc) const {
      return (m_is_defined.test(uc - m_first_letter));
    }

    UCS4 uppercase(const UCS4 uc) const {
      return Enclosed_Alphanumerics2460::m_upper[uc - m_first_letter];
    }

    UCS4 lowercase(const UCS4 uc) const {
      return Enclosed_Alphanumerics2460::m_lower[uc - m_first_letter];
    }

    UCS4 titlecase(const UCS4 uc) const {
      return Enclosed_Alphanumerics2460::m_title[uc - m_first_letter];
    }

    int dec_digit_value(const UCS4 uc) const {
      return 0;
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      return 0;
    }

    int digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
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
        return 0;
      }
    }

    bool is_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x2460:
      case 0x2461:
      case 0x2462:
      case 0x2463:
      case 0x2464:
      case 0x2465:
      case 0x2466:
      case 0x2467:
      case 0x2468:
      case 0x2474:
      case 0x2475:
      case 0x2476:
      case 0x2477:
      case 0x2478:
      case 0x2479:
      case 0x247A:
      case 0x247B:
      case 0x247C:
      case 0x2488:
      case 0x2489:
      case 0x248A:
      case 0x248B:
      case 0x248C:
      case 0x248D:
      case 0x248E:
      case 0x248F:
      case 0x2490:
      case 0x24EA:
        return 1;
      default:
        return 0;
      }
    }

    float numeric_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
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
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x2460:
      case 0x2461:
      case 0x2462:
      case 0x2463:
      case 0x2464:
      case 0x2465:
      case 0x2466:
      case 0x2467:
      case 0x2468:
      case 0x2469:
      case 0x246A:
      case 0x246B:
      case 0x246C:
      case 0x246D:
      case 0x246E:
      case 0x246F:
      case 0x2470:
      case 0x2471:
      case 0x2472:
      case 0x2473:
      case 0x2474:
      case 0x2475:
      case 0x2476:
      case 0x2477:
      case 0x2478:
      case 0x2479:
      case 0x247A:
      case 0x247B:
      case 0x247C:
      case 0x247D:
      case 0x247E:
      case 0x247F:
      case 0x2480:
      case 0x2481:
      case 0x2482:
      case 0x2483:
      case 0x2484:
      case 0x2485:
      case 0x2486:
      case 0x2487:
      case 0x2488:
      case 0x2489:
      case 0x248A:
      case 0x248B:
      case 0x248C:
      case 0x248D:
      case 0x248E:
      case 0x248F:
      case 0x2490:
      case 0x2491:
      case 0x2492:
      case 0x2493:
      case 0x2494:
      case 0x2495:
      case 0x2496:
      case 0x2497:
      case 0x2498:
      case 0x2499:
      case 0x249A:
      case 0x249B:
      case 0x24EA:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Enclosed_Alphanumerics2460::_cat[uc - m_first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Enclosed_Alphanumerics2460::m_bidir[uc - m_first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Enclosed_Alphanumerics2460::_decomp[uc - m_first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Enclosed_Alphanumerics2460::m_decompStr[uc - m_first_letter][0];
      us[1] = Enclosed_Alphanumerics2460::m_decompStr[uc - m_first_letter][1];

      switch (uc) {

      case 0x2474:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x2475:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x2476:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x2477:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x2478:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x2479:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x247A:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x247B:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x247C:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x247D:
        us.resize(4);
        us[2u] = 0x0030u;
        us[3u] = 0x0029u;
        break;

      case 0x247E:
        us.resize(4);
        us[2u] = 0x0031u;
        us[3u] = 0x0029u;
        break;

      case 0x247F:
        us.resize(4);
        us[2u] = 0x0032u;
        us[3u] = 0x0029u;
        break;

      case 0x2480:
        us.resize(4);
        us[2u] = 0x0033u;
        us[3u] = 0x0029u;
        break;

      case 0x2481:
        us.resize(4);
        us[2u] = 0x0034u;
        us[3u] = 0x0029u;
        break;

      case 0x2482:
        us.resize(4);
        us[2u] = 0x0035u;
        us[3u] = 0x0029u;
        break;

      case 0x2483:
        us.resize(4);
        us[2u] = 0x0036u;
        us[3u] = 0x0029u;
        break;

      case 0x2484:
        us.resize(4);
        us[2u] = 0x0037u;
        us[3u] = 0x0029u;
        break;

      case 0x2485:
        us.resize(4);
        us[2u] = 0x0038u;
        us[3u] = 0x0029u;
        break;

      case 0x2486:
        us.resize(4);
        us[2u] = 0x0039u;
        us[3u] = 0x0029u;
        break;

      case 0x2487:
        us.resize(4);
        us[2u] = 0x0030u;
        us[3u] = 0x0029u;
        break;

      case 0x2491:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x2492:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x2493:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x2494:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x2495:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x2496:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x2497:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x2498:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x2499:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x249A:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x249B:
        us.resize(3);
        us[2u] = 0x002Eu;
        break;

      case 0x249C:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x249D:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x249E:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x249F:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24A0:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24A1:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24A2:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24A3:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24A4:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24A5:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24A6:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24A7:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24A8:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24A9:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24AA:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24AB:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24AC:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24AD:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24AE:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24AF:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24B0:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24B1:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24B2:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24B3:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24B4:
        us.resize(3);
        us[2u] = 0x0029u;
        break;

      case 0x24B5:
        us.resize(3);
        us[2u] = 0x0029u;
        break;
      }
      if (us[1] == 0x0000u) {
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
      return Babylon::Line_Break(Enclosed_Alphanumerics2460::m_lb[uc - m_first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(Enclosed_Alphanumerics2460::m_ea[uc - m_first_letter]);
    }

    UCS4 compose (const UCS4 start, const UCS4 last) {
      return 0;
    }

    bool is_White_space(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_break(const UCS4 uc) const {
      return 0;
    }

    bool is_Format_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Join_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Format_Control(const UCS4 uc) const {
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

    bool is_Composite(const UCS4 uc) const {
      return m_Composite.test(uc - m_first_letter);
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return 0;
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part_Not_Cf(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Uppercase(const UCS4 uc) const {
      return m_Other_Uppercase.test(uc - m_first_letter);
    }

    bool is_Other_Lowercase(const UCS4 uc) const {
      return m_Other_Lowercase.test(uc - m_first_letter);
    }

    bool is_Ideographic(const UCS4 uc) const {
      return 0;
    }

    bool is_Private_Use(const UCS4 uc) const {
      return 0;
    }

    bool is_Noncharacter_Code_Point(const UCS4 uc) const {
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


  private:
    // functions
    Enclosed_Alphanumerics2460(const Enclosed_Alphanumerics2460 &) {}

    Babylon::UCS4 m_first_letter;
    Babylon::UCS4 m_last_letter;
    // Babylon::UCS4_string m_version;
    static const bitset<160> m_is_defined;
    static const UCS4 m_upper[160];
    static const UCS4 m_lower[160];
    static const UCS4 m_title[160];
    static const unsigned char _cat[160];
    static const unsigned char m_bidir[160];
    static const unsigned char _decomp[160];
    static const UCS2 m_decompStr[160][2];
    static const unsigned char m_lb[160];
    static const unsigned char m_ea[160];
    static const bitset<160> m_Composite;
    static const bitset<160> m_Other_Uppercase;
    static const bitset<160> m_Other_Lowercase;

  }; // class Enclosed_Alphanumerics2460

    const bitset<160> Enclosed_Alphanumerics2460::m_is_defined(string("0000000000000000000001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

  const UCS4 Enclosed_Alphanumerics2460::m_upper[] = {
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

  const UCS4 Enclosed_Alphanumerics2460::m_lower[] = {
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

  const UCS4 Enclosed_Alphanumerics2460::m_title[] = {
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

  const unsigned char Enclosed_Alphanumerics2460::_cat[] = {
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

  const unsigned char Enclosed_Alphanumerics2460::m_bidir[] = {
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

  const unsigned char Enclosed_Alphanumerics2460::_decomp[] = {
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

  const UCS2 Enclosed_Alphanumerics2460::m_decompStr[][2] = {
    { 0x0031u, 0x0000u }, { 0x0032u, 0x0000u }, { 0x0033u, 0x0000u }, { 0x0034u, 0x0000u }, 
    { 0x0035u, 0x0000u }, { 0x0036u, 0x0000u }, { 0x0037u, 0x0000u }, { 0x0038u, 0x0000u }, 
    { 0x0039u, 0x0000u }, { 0x0031u, 0x0030u }, { 0x0031u, 0x0031u }, { 0x0031u, 0x0032u }, 
    { 0x0031u, 0x0033u }, { 0x0031u, 0x0034u }, { 0x0031u, 0x0035u }, { 0x0031u, 0x0036u }, 
    { 0x0031u, 0x0037u }, { 0x0031u, 0x0038u }, { 0x0031u, 0x0039u }, { 0x0032u, 0x0030u }, 
    { 0x0028u, 0x0031u }, { 0x0028u, 0x0032u }, { 0x0028u, 0x0033u }, { 0x0028u, 0x0034u }, 
    { 0x0028u, 0x0035u }, { 0x0028u, 0x0036u }, { 0x0028u, 0x0037u }, { 0x0028u, 0x0038u }, 
    { 0x0028u, 0x0039u }, { 0x0028u, 0x0031u }, { 0x0028u, 0x0031u }, { 0x0028u, 0x0031u }, 
    { 0x0028u, 0x0031u }, { 0x0028u, 0x0031u }, { 0x0028u, 0x0031u }, { 0x0028u, 0x0031u }, 
    { 0x0028u, 0x0031u }, { 0x0028u, 0x0031u }, { 0x0028u, 0x0031u }, { 0x0028u, 0x0032u }, 
    { 0x0031u, 0x002Eu }, { 0x0032u, 0x002Eu }, { 0x0033u, 0x002Eu }, { 0x0034u, 0x002Eu }, 
    { 0x0035u, 0x002Eu }, { 0x0036u, 0x002Eu }, { 0x0037u, 0x002Eu }, { 0x0038u, 0x002Eu }, 
    { 0x0039u, 0x002Eu }, { 0x0031u, 0x0030u }, { 0x0031u, 0x0031u }, { 0x0031u, 0x0032u }, 
    { 0x0031u, 0x0033u }, { 0x0031u, 0x0034u }, { 0x0031u, 0x0035u }, { 0x0031u, 0x0036u }, 
    { 0x0031u, 0x0037u }, { 0x0031u, 0x0038u }, { 0x0031u, 0x0039u }, { 0x0032u, 0x0030u }, 
    { 0x0028u, 0x0061u }, { 0x0028u, 0x0062u }, { 0x0028u, 0x0063u }, { 0x0028u, 0x0064u }, 
    { 0x0028u, 0x0065u }, { 0x0028u, 0x0066u }, { 0x0028u, 0x0067u }, { 0x0028u, 0x0068u }, 
    { 0x0028u, 0x0069u }, { 0x0028u, 0x006Au }, { 0x0028u, 0x006Bu }, { 0x0028u, 0x006Cu }, 
    { 0x0028u, 0x006Du }, { 0x0028u, 0x006Eu }, { 0x0028u, 0x006Fu }, { 0x0028u, 0x0070u }, 
    { 0x0028u, 0x0071u }, { 0x0028u, 0x0072u }, { 0x0028u, 0x0073u }, { 0x0028u, 0x0074u }, 
    { 0x0028u, 0x0075u }, { 0x0028u, 0x0076u }, { 0x0028u, 0x0077u }, { 0x0028u, 0x0078u }, 
    { 0x0028u, 0x0079u }, { 0x0028u, 0x007Au }, { 0x0041u, 0x0000u }, { 0x0042u, 0x0000u }, 
    { 0x0043u, 0x0000u }, { 0x0044u, 0x0000u }, { 0x0045u, 0x0000u }, { 0x0046u, 0x0000u }, 
    { 0x0047u, 0x0000u }, { 0x0048u, 0x0000u }, { 0x0049u, 0x0000u }, { 0x004Au, 0x0000u }, 
    { 0x004Bu, 0x0000u }, { 0x004Cu, 0x0000u }, { 0x004Du, 0x0000u }, { 0x004Eu, 0x0000u }, 
    { 0x004Fu, 0x0000u }, { 0x0050u, 0x0000u }, { 0x0051u, 0x0000u }, { 0x0052u, 0x0000u }, 
    { 0x0053u, 0x0000u }, { 0x0054u, 0x0000u }, { 0x0055u, 0x0000u }, { 0x0056u, 0x0000u }, 
    { 0x0057u, 0x0000u }, { 0x0058u, 0x0000u }, { 0x0059u, 0x0000u }, { 0x005Au, 0x0000u }, 
    { 0x0061u, 0x0000u }, { 0x0062u, 0x0000u }, { 0x0063u, 0x0000u }, { 0x0064u, 0x0000u }, 
    { 0x0065u, 0x0000u }, { 0x0066u, 0x0000u }, { 0x0067u, 0x0000u }, { 0x0068u, 0x0000u }, 
    { 0x0069u, 0x0000u }, { 0x006Au, 0x0000u }, { 0x006Bu, 0x0000u }, { 0x006Cu, 0x0000u }, 
    { 0x006Du, 0x0000u }, { 0x006Eu, 0x0000u }, { 0x006Fu, 0x0000u }, { 0x0070u, 0x0000u }, 
    { 0x0071u, 0x0000u }, { 0x0072u, 0x0000u }, { 0x0073u, 0x0000u }, { 0x0074u, 0x0000u }, 
    { 0x0075u, 0x0000u }, { 0x0076u, 0x0000u }, { 0x0077u, 0x0000u }, { 0x0078u, 0x0000u }, 
    { 0x0079u, 0x0000u }, { 0x007Au, 0x0000u }, { 0x0030u, 0x0000u }, { 0x24EBu, 0x0000u }, 
    { 0x24ECu, 0x0000u }, { 0x24EDu, 0x0000u }, { 0x24EEu, 0x0000u }, { 0x24EFu, 0x0000u }, 
    { 0x24F0u, 0x0000u }, { 0x24F1u, 0x0000u }, { 0x24F2u, 0x0000u }, { 0x24F3u, 0x0000u }, 
    { 0x24F4u, 0x0000u }, { 0x24F5u, 0x0000u }, { 0x24F6u, 0x0000u }, { 0x24F7u, 0x0000u }, 
    { 0x24F8u, 0x0000u }, { 0x24F9u, 0x0000u }, { 0x24FAu, 0x0000u }, { 0x24FBu, 0x0000u }, 
    { 0x24FCu, 0x0000u }, { 0x24FDu, 0x0000u }, { 0x24FEu, 0x0000u }, { 0x24FFu, 0x0000u }
  };

  const unsigned char Enclosed_Alphanumerics2460::m_lb[] = {
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

  const unsigned char Enclosed_Alphanumerics2460::m_ea[] = {
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

    const bitset<160> Enclosed_Alphanumerics2460::m_Composite(string("0000000000000000000000000000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111111111111111111111111111111111111111000000000"));

    const bitset<160> Enclosed_Alphanumerics2460::m_Other_Uppercase(string("0000000000000000000000000000000000000000000000001111111111111111111111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const bitset<160> Enclosed_Alphanumerics2460::m_Other_Lowercase(string("0000000000000000000000111111111111111111111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

}; // namespace Babylon

dload(Babylon::Enclosed_Alphanumerics2460);
