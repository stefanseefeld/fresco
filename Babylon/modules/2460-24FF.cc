/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 2460-24FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:46 +0200.
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
#include <Babylon/internal/Blocks.hh>
#include <bitset>
#include <utility>


namespace Babylon
{
  namespace Module
  {
    class Enclosed_Alphanumerics2460 : public Babylon::Block
    {
      public:
        void clean() { };

        Enclosed_Alphanumerics2460() :
	    my_first_letter(0x2460),
	    my_last_letter(0x24FF)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~Enclosed_Alphanumerics2460() { }

        UCS4 first_letter() const
        {
	    return my_first_letter;
	}  

	UCS4 last_letter() const
	{
	    return my_last_letter;
	}

	bool is_undef_block() const
	{
	    return 0;
	}

	// query functions:
	std::string blockname(const UCS4 uc) const
	{
	    return "Enclosed Alphanumerics";
	}

        bool is_defined(const UCS4 uc) const
        {
            return 1;
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Enclosed_Alphanumerics2460::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Enclosed_Alphanumerics2460::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Enclosed_Alphanumerics2460::my_title[uc - my_first_letter];
        }

        int dec_digit_value(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            return 0;
        }

        int digit_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x2460u:
                return 1;
            case 0x2461u:
                return 2;
            case 0x2462u:
                return 3;
            case 0x2463u:
                return 4;
            case 0x2464u:
                return 5;
            case 0x2465u:
                return 6;
            case 0x2466u:
                return 7;
            case 0x2467u:
                return 8;
            case 0x2468u:
                return 9;
            case 0x2474u:
                return 1;
            case 0x2475u:
                return 2;
            case 0x2476u:
                return 3;
            case 0x2477u:
                return 4;
            case 0x2478u:
                return 5;
            case 0x2479u:
                return 6;
            case 0x247Au:
                return 7;
            case 0x247Bu:
                return 8;
            case 0x247Cu:
                return 9;
            case 0x2488u:
                return 1;
            case 0x2489u:
                return 2;
            case 0x248Au:
                return 3;
            case 0x248Bu:
                return 4;
            case 0x248Cu:
                return 5;
            case 0x248Du:
                return 6;
            case 0x248Eu:
                return 7;
            case 0x248Fu:
                return 8;
            case 0x2490u:
                return 9;
            case 0x24EAu:
                return 0;
            case 0x24F5u:
                return 1;
            case 0x24F6u:
                return 2;
            case 0x24F7u:
                return 3;
            case 0x24F8u:
                return 4;
            case 0x24F9u:
                return 5;
            case 0x24FAu:
                return 6;
            case 0x24FBu:
                return 7;
            case 0x24FCu:
                return 8;
            case 0x24FDu:
                return 9;
            case 0x24FFu:
                return 0;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x2460u:
            case 0x2461u:
            case 0x2462u:
            case 0x2463u:
            case 0x2464u:
            case 0x2465u:
            case 0x2466u:
            case 0x2467u:
            case 0x2468u:
            case 0x2474u:
            case 0x2475u:
            case 0x2476u:
            case 0x2477u:
            case 0x2478u:
            case 0x2479u:
            case 0x247Au:
            case 0x247Bu:
            case 0x247Cu:
            case 0x2488u:
            case 0x2489u:
            case 0x248Au:
            case 0x248Bu:
            case 0x248Cu:
            case 0x248Du:
            case 0x248Eu:
            case 0x248Fu:
            case 0x2490u:
            case 0x24EAu:
            case 0x24F5u:
            case 0x24F6u:
            case 0x24F7u:
            case 0x24F8u:
            case 0x24F9u:
            case 0x24FAu:
            case 0x24FBu:
            case 0x24FCu:
            case 0x24FDu:
            case 0x24FFu:
                return 1;
            default:
                return 0;
            }
        }

        float numeric_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x2460u:
                return 1.000000;
            case 0x2461u:
                return 2.000000;
            case 0x2462u:
                return 3.000000;
            case 0x2463u:
                return 4.000000;
            case 0x2464u:
                return 5.000000;
            case 0x2465u:
                return 6.000000;
            case 0x2466u:
                return 7.000000;
            case 0x2467u:
                return 8.000000;
            case 0x2468u:
                return 9.000000;
            case 0x2469u:
                return 10.000000;
            case 0x246Au:
                return 11.000000;
            case 0x246Bu:
                return 12.000000;
            case 0x246Cu:
                return 13.000000;
            case 0x246Du:
                return 14.000000;
            case 0x246Eu:
                return 15.000000;
            case 0x246Fu:
                return 16.000000;
            case 0x2470u:
                return 17.000000;
            case 0x2471u:
                return 18.000000;
            case 0x2472u:
                return 19.000000;
            case 0x2473u:
                return 20.000000;
            case 0x2474u:
                return 1.000000;
            case 0x2475u:
                return 2.000000;
            case 0x2476u:
                return 3.000000;
            case 0x2477u:
                return 4.000000;
            case 0x2478u:
                return 5.000000;
            case 0x2479u:
                return 6.000000;
            case 0x247Au:
                return 7.000000;
            case 0x247Bu:
                return 8.000000;
            case 0x247Cu:
                return 9.000000;
            case 0x247Du:
                return 10.000000;
            case 0x247Eu:
                return 11.000000;
            case 0x247Fu:
                return 12.000000;
            case 0x2480u:
                return 13.000000;
            case 0x2481u:
                return 14.000000;
            case 0x2482u:
                return 15.000000;
            case 0x2483u:
                return 16.000000;
            case 0x2484u:
                return 17.000000;
            case 0x2485u:
                return 18.000000;
            case 0x2486u:
                return 19.000000;
            case 0x2487u:
                return 20.000000;
            case 0x2488u:
                return 1.000000;
            case 0x2489u:
                return 2.000000;
            case 0x248Au:
                return 3.000000;
            case 0x248Bu:
                return 4.000000;
            case 0x248Cu:
                return 5.000000;
            case 0x248Du:
                return 6.000000;
            case 0x248Eu:
                return 7.000000;
            case 0x248Fu:
                return 8.000000;
            case 0x2490u:
                return 9.000000;
            case 0x2491u:
                return 10.000000;
            case 0x2492u:
                return 11.000000;
            case 0x2493u:
                return 12.000000;
            case 0x2494u:
                return 13.000000;
            case 0x2495u:
                return 14.000000;
            case 0x2496u:
                return 15.000000;
            case 0x2497u:
                return 16.000000;
            case 0x2498u:
                return 17.000000;
            case 0x2499u:
                return 18.000000;
            case 0x249Au:
                return 19.000000;
            case 0x249Bu:
                return 20.000000;
            case 0x24EAu:
                return 0.000000;
            case 0x24EBu:
                return 11.000000;
            case 0x24ECu:
                return 12.000000;
            case 0x24EDu:
                return 13.000000;
            case 0x24EEu:
                return 14.000000;
            case 0x24EFu:
                return 15.000000;
            case 0x24F0u:
                return 16.000000;
            case 0x24F1u:
                return 17.000000;
            case 0x24F2u:
                return 18.000000;
            case 0x24F3u:
                return 19.000000;
            case 0x24F4u:
                return 20.000000;
            case 0x24F5u:
                return 1.000000;
            case 0x24F6u:
                return 2.000000;
            case 0x24F7u:
                return 3.000000;
            case 0x24F8u:
                return 4.000000;
            case 0x24F9u:
                return 5.000000;
            case 0x24FAu:
                return 6.000000;
            case 0x24FBu:
                return 7.000000;
            case 0x24FCu:
                return 8.000000;
            case 0x24FDu:
                return 9.000000;
            case 0x24FEu:
                return 10.000000;
            case 0x24FFu:
                return 0.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x2460u:
            case 0x2461u:
            case 0x2462u:
            case 0x2463u:
            case 0x2464u:
            case 0x2465u:
            case 0x2466u:
            case 0x2467u:
            case 0x2468u:
            case 0x2469u:
            case 0x246Au:
            case 0x246Bu:
            case 0x246Cu:
            case 0x246Du:
            case 0x246Eu:
            case 0x246Fu:
            case 0x2470u:
            case 0x2471u:
            case 0x2472u:
            case 0x2473u:
            case 0x2474u:
            case 0x2475u:
            case 0x2476u:
            case 0x2477u:
            case 0x2478u:
            case 0x2479u:
            case 0x247Au:
            case 0x247Bu:
            case 0x247Cu:
            case 0x247Du:
            case 0x247Eu:
            case 0x247Fu:
            case 0x2480u:
            case 0x2481u:
            case 0x2482u:
            case 0x2483u:
            case 0x2484u:
            case 0x2485u:
            case 0x2486u:
            case 0x2487u:
            case 0x2488u:
            case 0x2489u:
            case 0x248Au:
            case 0x248Bu:
            case 0x248Cu:
            case 0x248Du:
            case 0x248Eu:
            case 0x248Fu:
            case 0x2490u:
            case 0x2491u:
            case 0x2492u:
            case 0x2493u:
            case 0x2494u:
            case 0x2495u:
            case 0x2496u:
            case 0x2497u:
            case 0x2498u:
            case 0x2499u:
            case 0x249Au:
            case 0x249Bu:
            case 0x24EAu:
            case 0x24EBu:
            case 0x24ECu:
            case 0x24EDu:
            case 0x24EEu:
            case 0x24EFu:
            case 0x24F0u:
            case 0x24F1u:
            case 0x24F2u:
            case 0x24F3u:
            case 0x24F4u:
            case 0x24F5u:
            case 0x24F6u:
            case 0x24F7u:
            case 0x24F8u:
            case 0x24F9u:
            case 0x24FAu:
            case 0x24FBu:
            case 0x24FCu:
            case 0x24FDu:
            case 0x24FEu:
            case 0x24FFu:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Enclosed_Alphanumerics2460::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Babylon::Can_Comb_Class(0);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return Enclosed_Alphanumerics2460::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Enclosed_Alphanumerics2460::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Enclosed_Alphanumerics2460::my_decompStr[uc - my_first_letter][0];
            us[1] = Enclosed_Alphanumerics2460::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

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
            if (0x0000u == us[1])
                us.resize(1);
            return us;
        }

        bool must_mirror(const UCS4 uc) const
        {
            return 0;
        }

        Line_Break linebreak(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return LB_MAX;
            return Babylon::Line_Break(Enclosed_Alphanumerics2460::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Enclosed_Alphanumerics2460::my_ea[uc - my_first_letter]);
        }

        UCS4 compose(const UCS4 starter, const UCS4 last)
        {
            return 0;
        }

        bool exclude_from_composition(const UCS4 uc) const
        {
            return 0;
        }

        bool is_White_Space(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Bidi_Control(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Join_Control(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Dash(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Hyphen(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Quotation_Mark(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Terminal_Punctuation(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Math(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Hex_Digit(const UCS4 uc) const
        {
            return 0;
        }

        bool is_ASCII_Hex_Digit(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Alphabetic(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Ideographic(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Diacritic(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Extender(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Lowercase(const UCS4 uc) const
        {
            return my_Other_Lowercase.test(uc - my_first_letter);
        }

        bool is_Other_Uppercase(const UCS4 uc) const
        {
            return my_Other_Uppercase.test(uc - my_first_letter);
        }

        bool is_Noncharacter_Code_Point(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Grapheme_Extend(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Grapheme_Link(const UCS4 uc) const
        {
            return 0;
        }

        bool is_IDS_Binary_Operator(const UCS4 uc) const
        {
            return 0;
        }

        bool is_IDS_Trinary_Operator(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Radical(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Unified_Ideograph(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Default_Ignorable_Code_Point(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Deprecated(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Soft_Dotted(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Logical_Order_Exception(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_ID_Start(const UCS4 uc) const
        {
            return 0;
        }

        bool is_XID_Start_Closure(const UCS4 uc) const
        {
            return 0;
        }

        bool is_XID_Continue_Closure(const UCS4 uc) const
        {
            return 0;
        }

      private:
        // functions
        Enclosed_Alphanumerics2460(const Enclosed_Alphanumerics2460 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const UCS4 my_upper[160];
        static const UCS4 my_lower[160];
        static const UCS4 my_title[160];
        static const unsigned char my_cat[160];
        static const Babylon::Bidir_Props my_bidir[160];
        static const unsigned char my_decomp[160];
        static const UCS2 my_decompStr[160][2];
        static const unsigned char my_lb[160];
        static const unsigned char my_ea[160];
        static const std::bitset<160> my_Other_Lowercase;
        static const std::bitset<160> my_Other_Uppercase;
    }; // class Enclosed_Alphanumerics2460

    const UCS4 Enclosed_Alphanumerics2460::my_upper[] =
    {
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

    const UCS4 Enclosed_Alphanumerics2460::my_lower[] =
    {
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

    const UCS4 Enclosed_Alphanumerics2460::my_title[] =
    {
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

    const unsigned char Enclosed_Alphanumerics2460::my_cat[] =
    {
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

    const Babylon::Bidir_Props Enclosed_Alphanumerics2460::my_bidir[] =
    {
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_EN, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
    };

    const unsigned char Enclosed_Alphanumerics2460::my_decomp[] = {
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Enclosed_Alphanumerics2460::my_decompStr[][2] =
    {
        { 0x00000031u, 0x00000000u }, { 0x00000032u, 0x00000000u },  // 00002460
        { 0x00000033u, 0x00000000u }, { 0x00000034u, 0x00000000u },  // 00002462
        { 0x00000035u, 0x00000000u }, { 0x00000036u, 0x00000000u },  // 00002464
        { 0x00000037u, 0x00000000u }, { 0x00000038u, 0x00000000u },  // 00002466
        { 0x00000039u, 0x00000000u }, { 0x00000031u, 0x00000030u },  // 00002468
        { 0x00000031u, 0x00000031u }, { 0x00000031u, 0x00000032u },  // 0000246A
        { 0x00000031u, 0x00000033u }, { 0x00000031u, 0x00000034u },  // 0000246C
        { 0x00000031u, 0x00000035u }, { 0x00000031u, 0x00000036u },  // 0000246E
        { 0x00000031u, 0x00000037u }, { 0x00000031u, 0x00000038u },  // 00002470
        { 0x00000031u, 0x00000039u }, { 0x00000032u, 0x00000030u },  // 00002472
        { 0x00000028u, 0x00000031u }, { 0x00000028u, 0x00000032u },  // 00002474
        { 0x00000028u, 0x00000033u }, { 0x00000028u, 0x00000034u },  // 00002476
        { 0x00000028u, 0x00000035u }, { 0x00000028u, 0x00000036u },  // 00002478
        { 0x00000028u, 0x00000037u }, { 0x00000028u, 0x00000038u },  // 0000247A
        { 0x00000028u, 0x00000039u }, { 0x00000028u, 0x00000031u },  // 0000247C
        { 0x00000028u, 0x00000031u }, { 0x00000028u, 0x00000031u },  // 0000247E
        { 0x00000028u, 0x00000031u }, { 0x00000028u, 0x00000031u },  // 00002480
        { 0x00000028u, 0x00000031u }, { 0x00000028u, 0x00000031u },  // 00002482
        { 0x00000028u, 0x00000031u }, { 0x00000028u, 0x00000031u },  // 00002484
        { 0x00000028u, 0x00000031u }, { 0x00000028u, 0x00000032u },  // 00002486
        { 0x00000031u, 0x0000002Eu }, { 0x00000032u, 0x0000002Eu },  // 00002488
        { 0x00000033u, 0x0000002Eu }, { 0x00000034u, 0x0000002Eu },  // 0000248A
        { 0x00000035u, 0x0000002Eu }, { 0x00000036u, 0x0000002Eu },  // 0000248C
        { 0x00000037u, 0x0000002Eu }, { 0x00000038u, 0x0000002Eu },  // 0000248E
        { 0x00000039u, 0x0000002Eu }, { 0x00000031u, 0x00000030u },  // 00002490
        { 0x00000031u, 0x00000031u }, { 0x00000031u, 0x00000032u },  // 00002492
        { 0x00000031u, 0x00000033u }, { 0x00000031u, 0x00000034u },  // 00002494
        { 0x00000031u, 0x00000035u }, { 0x00000031u, 0x00000036u },  // 00002496
        { 0x00000031u, 0x00000037u }, { 0x00000031u, 0x00000038u },  // 00002498
        { 0x00000031u, 0x00000039u }, { 0x00000032u, 0x00000030u },  // 0000249A
        { 0x00000028u, 0x00000061u }, { 0x00000028u, 0x00000062u },  // 0000249C
        { 0x00000028u, 0x00000063u }, { 0x00000028u, 0x00000064u },  // 0000249E
        { 0x00000028u, 0x00000065u }, { 0x00000028u, 0x00000066u },  // 000024A0
        { 0x00000028u, 0x00000067u }, { 0x00000028u, 0x00000068u },  // 000024A2
        { 0x00000028u, 0x00000069u }, { 0x00000028u, 0x0000006Au },  // 000024A4
        { 0x00000028u, 0x0000006Bu }, { 0x00000028u, 0x0000006Cu },  // 000024A6
        { 0x00000028u, 0x0000006Du }, { 0x00000028u, 0x0000006Eu },  // 000024A8
        { 0x00000028u, 0x0000006Fu }, { 0x00000028u, 0x00000070u },  // 000024AA
        { 0x00000028u, 0x00000071u }, { 0x00000028u, 0x00000072u },  // 000024AC
        { 0x00000028u, 0x00000073u }, { 0x00000028u, 0x00000074u },  // 000024AE
        { 0x00000028u, 0x00000075u }, { 0x00000028u, 0x00000076u },  // 000024B0
        { 0x00000028u, 0x00000077u }, { 0x00000028u, 0x00000078u },  // 000024B2
        { 0x00000028u, 0x00000079u }, { 0x00000028u, 0x0000007Au },  // 000024B4
        { 0x00000041u, 0x00000000u }, { 0x00000042u, 0x00000000u },  // 000024B6
        { 0x00000043u, 0x00000000u }, { 0x00000044u, 0x00000000u },  // 000024B8
        { 0x00000045u, 0x00000000u }, { 0x00000046u, 0x00000000u },  // 000024BA
        { 0x00000047u, 0x00000000u }, { 0x00000048u, 0x00000000u },  // 000024BC
        { 0x00000049u, 0x00000000u }, { 0x0000004Au, 0x00000000u },  // 000024BE
        { 0x0000004Bu, 0x00000000u }, { 0x0000004Cu, 0x00000000u },  // 000024C0
        { 0x0000004Du, 0x00000000u }, { 0x0000004Eu, 0x00000000u },  // 000024C2
        { 0x0000004Fu, 0x00000000u }, { 0x00000050u, 0x00000000u },  // 000024C4
        { 0x00000051u, 0x00000000u }, { 0x00000052u, 0x00000000u },  // 000024C6
        { 0x00000053u, 0x00000000u }, { 0x00000054u, 0x00000000u },  // 000024C8
        { 0x00000055u, 0x00000000u }, { 0x00000056u, 0x00000000u },  // 000024CA
        { 0x00000057u, 0x00000000u }, { 0x00000058u, 0x00000000u },  // 000024CC
        { 0x00000059u, 0x00000000u }, { 0x0000005Au, 0x00000000u },  // 000024CE
        { 0x00000061u, 0x00000000u }, { 0x00000062u, 0x00000000u },  // 000024D0
        { 0x00000063u, 0x00000000u }, { 0x00000064u, 0x00000000u },  // 000024D2
        { 0x00000065u, 0x00000000u }, { 0x00000066u, 0x00000000u },  // 000024D4
        { 0x00000067u, 0x00000000u }, { 0x00000068u, 0x00000000u },  // 000024D6
        { 0x00000069u, 0x00000000u }, { 0x0000006Au, 0x00000000u },  // 000024D8
        { 0x0000006Bu, 0x00000000u }, { 0x0000006Cu, 0x00000000u },  // 000024DA
        { 0x0000006Du, 0x00000000u }, { 0x0000006Eu, 0x00000000u },  // 000024DC
        { 0x0000006Fu, 0x00000000u }, { 0x00000070u, 0x00000000u },  // 000024DE
        { 0x00000071u, 0x00000000u }, { 0x00000072u, 0x00000000u },  // 000024E0
        { 0x00000073u, 0x00000000u }, { 0x00000074u, 0x00000000u },  // 000024E2
        { 0x00000075u, 0x00000000u }, { 0x00000076u, 0x00000000u },  // 000024E4
        { 0x00000077u, 0x00000000u }, { 0x00000078u, 0x00000000u },  // 000024E6
        { 0x00000079u, 0x00000000u }, { 0x0000007Au, 0x00000000u },  // 000024E8
        { 0x00000030u, 0x00000000u }, { 0x000024EBu, 0x00000000u },  // 000024EA
        { 0x000024ECu, 0x00000000u }, { 0x000024EDu, 0x00000000u },  // 000024EC
        { 0x000024EEu, 0x00000000u }, { 0x000024EFu, 0x00000000u },  // 000024EE
        { 0x000024F0u, 0x00000000u }, { 0x000024F1u, 0x00000000u },  // 000024F0
        { 0x000024F2u, 0x00000000u }, { 0x000024F3u, 0x00000000u },  // 000024F2
        { 0x000024F4u, 0x00000000u }, { 0x000024F5u, 0x00000000u },  // 000024F4
        { 0x000024F6u, 0x00000000u }, { 0x000024F7u, 0x00000000u },  // 000024F6
        { 0x000024F8u, 0x00000000u }, { 0x000024F9u, 0x00000000u },  // 000024F8
        { 0x000024FAu, 0x00000000u }, { 0x000024FBu, 0x00000000u },  // 000024FA
        { 0x000024FCu, 0x00000000u }, { 0x000024FDu, 0x00000000u },  // 000024FC
        { 0x000024FEu, 0x00000000u }, { 0x000024FFu, 0x00000000u }
    };

    const unsigned char Enclosed_Alphanumerics2460::my_lb[] =
    {
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
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AL
    };

    const unsigned char Enclosed_Alphanumerics2460::my_ea[] =
    {
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A
    };

    const std::bitset<160> Enclosed_Alphanumerics2460::my_Other_Lowercase(std::string("0000000000000000000000111111111111111111111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<160> Enclosed_Alphanumerics2460::my_Other_Uppercase(std::string("0000000000000000000000000000000000000000000000001111111111111111111111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Enclosed_Alphanumerics2460);
