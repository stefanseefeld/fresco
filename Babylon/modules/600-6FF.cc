/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 600-6FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:55:54 +0200.
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

#include <map>

namespace Babylon
{
  namespace Module
  {
    class Arabic600 : public Babylon::Block
    {
      public:
        void clean() { };

        Arabic600() :
	    my_first_letter(0x600),
	    my_last_letter(0x6FF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000627, 0x00000653)] = 0x0622;
                my_composeMap[std::make_pair(0x00000627, 0x00000654)] = 0x0623;
                my_composeMap[std::make_pair(0x00000627, 0x00000655)] = 0x0625;
                my_composeMap[std::make_pair(0x00000648, 0x00000654)] = 0x0624;
                my_composeMap[std::make_pair(0x0000064A, 0x00000654)] = 0x0626;
                my_composeMap[std::make_pair(0x000006C1, 0x00000654)] = 0x06C2;
                my_composeMap[std::make_pair(0x000006D2, 0x00000654)] = 0x06D3;
                my_composeMap[std::make_pair(0x000006D5, 0x00000654)] = 0x06C0;
            }
        }

        ~Arabic600() { }

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
	    return "Arabic";
	}

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return uc;
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return uc;
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return uc;
        }

        int dec_digit_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x0660u:
                return 0;
            case 0x0661u:
                return 1;
            case 0x0662u:
                return 2;
            case 0x0663u:
                return 3;
            case 0x0664u:
                return 4;
            case 0x0665u:
                return 5;
            case 0x0666u:
                return 6;
            case 0x0667u:
                return 7;
            case 0x0668u:
                return 8;
            case 0x0669u:
                return 9;
            case 0x06F0u:
                return 0;
            case 0x06F1u:
                return 1;
            case 0x06F2u:
                return 2;
            case 0x06F3u:
                return 3;
            case 0x06F4u:
                return 4;
            case 0x06F5u:
                return 5;
            case 0x06F6u:
                return 6;
            case 0x06F7u:
                return 7;
            case 0x06F8u:
                return 8;
            case 0x06F9u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0660u:
            case 0x0661u:
            case 0x0662u:
            case 0x0663u:
            case 0x0664u:
            case 0x0665u:
            case 0x0666u:
            case 0x0667u:
            case 0x0668u:
            case 0x0669u:
            case 0x06F0u:
            case 0x06F1u:
            case 0x06F2u:
            case 0x06F3u:
            case 0x06F4u:
            case 0x06F5u:
            case 0x06F6u:
            case 0x06F7u:
            case 0x06F8u:
            case 0x06F9u:
                return 1;
            default:
                return 0;
            }
        }

        int digit_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x0660u:
                return 0;
            case 0x0661u:
                return 1;
            case 0x0662u:
                return 2;
            case 0x0663u:
                return 3;
            case 0x0664u:
                return 4;
            case 0x0665u:
                return 5;
            case 0x0666u:
                return 6;
            case 0x0667u:
                return 7;
            case 0x0668u:
                return 8;
            case 0x0669u:
                return 9;
            case 0x06F0u:
                return 0;
            case 0x06F1u:
                return 1;
            case 0x06F2u:
                return 2;
            case 0x06F3u:
                return 3;
            case 0x06F4u:
                return 4;
            case 0x06F5u:
                return 5;
            case 0x06F6u:
                return 6;
            case 0x06F7u:
                return 7;
            case 0x06F8u:
                return 8;
            case 0x06F9u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0660u:
            case 0x0661u:
            case 0x0662u:
            case 0x0663u:
            case 0x0664u:
            case 0x0665u:
            case 0x0666u:
            case 0x0667u:
            case 0x0668u:
            case 0x0669u:
            case 0x06F0u:
            case 0x06F1u:
            case 0x06F2u:
            case 0x06F3u:
            case 0x06F4u:
            case 0x06F5u:
            case 0x06F6u:
            case 0x06F7u:
            case 0x06F8u:
            case 0x06F9u:
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
            case 0x0660u:
                return 0.000000;
            case 0x0661u:
                return 1.000000;
            case 0x0662u:
                return 2.000000;
            case 0x0663u:
                return 3.000000;
            case 0x0664u:
                return 4.000000;
            case 0x0665u:
                return 5.000000;
            case 0x0666u:
                return 6.000000;
            case 0x0667u:
                return 7.000000;
            case 0x0668u:
                return 8.000000;
            case 0x0669u:
                return 9.000000;
            case 0x06F0u:
                return 0.000000;
            case 0x06F1u:
                return 1.000000;
            case 0x06F2u:
                return 2.000000;
            case 0x06F3u:
                return 3.000000;
            case 0x06F4u:
                return 4.000000;
            case 0x06F5u:
                return 5.000000;
            case 0x06F6u:
                return 6.000000;
            case 0x06F7u:
                return 7.000000;
            case 0x06F8u:
                return 8.000000;
            case 0x06F9u:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0660u:
            case 0x0661u:
            case 0x0662u:
            case 0x0663u:
            case 0x0664u:
            case 0x0665u:
            case 0x0666u:
            case 0x0667u:
            case 0x0668u:
            case 0x0669u:
            case 0x06F0u:
            case 0x06F1u:
            case 0x06F2u:
            case 0x06F3u:
            case 0x06F4u:
            case 0x06F5u:
            case 0x06F6u:
            case 0x06F7u:
            case 0x06F8u:
            case 0x06F9u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Arabic600::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(Arabic600::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return Arabic600::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Arabic600::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Arabic600::my_decompStr[uc - my_first_letter][0];
            us[1] = Arabic600::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Arabic600::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_N);
        }

        UCS4 compose(const UCS4 starter, const UCS4 last)
        {
            return my_composeMap[std::make_pair(starter, last)];
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
            return my_Terminal_Punctuation.test(uc - my_first_letter);
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
            return my_Other_Alphabetic.test(uc - my_first_letter);
        }

        bool is_Ideographic(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Diacritic(const UCS4 uc) const
        {
            return my_Diacritic.test(uc - my_first_letter);
        }

        bool is_Extender(const UCS4 uc) const
        {
            return my_Extender.test(uc - my_first_letter);
        }

        bool is_Other_Lowercase(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Uppercase(const UCS4 uc) const
        {
            return 0;
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

      private:
        // functions
        Arabic600(const Arabic600 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<256> my_is_defined;
        static const unsigned char my_cat[256];
        static const unsigned char my_comb_cl[256];
        static const Babylon::Bidir_Props my_bidir[256];
        static const unsigned char my_decomp[256];
        static const UCS2 my_decompStr[256][2];
        static const unsigned char my_lb[256];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<256> my_Terminal_Punctuation;
        static const std::bitset<256> my_Other_Alphabetic;
        static const std::bitset<256> my_Diacritic;
        static const std::bitset<256> my_Extender;
    }; // class Arabic600

    const std::bitset<256> Arabic600::my_is_defined(std::string("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111000000011111111111111111111111110000011111111111111111111111111010001000001111111111000000001111"));

    const unsigned char Arabic600::my_cat[] =
    {
        CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, 
        CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Po, CAT_Po, CAT_So, CAT_So, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Cf, CAT_Cf, 
        CAT_Cf, CAT_Cf, CAT_Cf, CAT_Po, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Po, 
        CAT_Cf, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, 
        CAT_Lm, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Lo, CAT_Lo, 
        CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Po, CAT_Lo, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Cf, CAT_Me, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lm, CAT_Lm, CAT_Mn, 
        CAT_Mn, CAT_So, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Lo, CAT_Lo, CAT_Lo, CAT_So, CAT_So, CAT_Lo
    };

    const unsigned char Arabic600::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        230, 230, 230, 230, 230, 230, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 27, 28, 29, 30, 31, 
        32, 33, 34, 230, 230, 220, 220, 230, 
        230, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        35, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 230, 230, 
        230, 230, 230, 230, 230, 0, 0, 230, 
        230, 230, 230, 220, 230, 0, 0, 230, 
        230, 0, 220, 230, 230, 220, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props Arabic600::my_bidir[] =
    {
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_CS, BIDIR_AL, BIDIR_ON, BIDIR_ON, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AN, BIDIR_AN, BIDIR_AN, BIDIR_AN, 
        BIDIR_AN, BIDIR_AN, BIDIR_AN, BIDIR_AN, 
        BIDIR_AN, BIDIR_AN, BIDIR_ET, BIDIR_AN, 
        BIDIR_AN, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_NSM, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_AL, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_AL, BIDIR_AL, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_ON, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_AL, BIDIR_AL, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL
    };

    const unsigned char Arabic600::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Arabic600::my_decompStr[][2] =
    {
        { 0x00000600u, 0x00000000u }, { 0x00000601u, 0x00000000u },  // 00000600
        { 0x00000602u, 0x00000000u }, { 0x00000603u, 0x00000000u },  // 00000602
        { 0x00000604u, 0x00000000u }, { 0x00000605u, 0x00000000u },  // 00000604
        { 0x00000606u, 0x00000000u }, { 0x00000607u, 0x00000000u },  // 00000606
        { 0x00000608u, 0x00000000u }, { 0x00000609u, 0x00000000u },  // 00000608
        { 0x0000060Au, 0x00000000u }, { 0x0000060Bu, 0x00000000u },  // 0000060A
        { 0x0000060Cu, 0x00000000u }, { 0x0000060Du, 0x00000000u },  // 0000060C
        { 0x0000060Eu, 0x00000000u }, { 0x0000060Fu, 0x00000000u },  // 0000060E
        { 0x00000610u, 0x00000000u }, { 0x00000611u, 0x00000000u },  // 00000610
        { 0x00000612u, 0x00000000u }, { 0x00000613u, 0x00000000u },  // 00000612
        { 0x00000614u, 0x00000000u }, { 0x00000615u, 0x00000000u },  // 00000614
        { 0x00000616u, 0x00000000u }, { 0x00000617u, 0x00000000u },  // 00000616
        { 0x00000618u, 0x00000000u }, { 0x00000619u, 0x00000000u },  // 00000618
        { 0x0000061Au, 0x00000000u }, { 0x0000061Bu, 0x00000000u },  // 0000061A
        { 0x0000061Cu, 0x00000000u }, { 0x0000061Du, 0x00000000u },  // 0000061C
        { 0x0000061Eu, 0x00000000u }, { 0x0000061Fu, 0x00000000u },  // 0000061E
        { 0x00000620u, 0x00000000u }, { 0x00000621u, 0x00000000u },  // 00000620
        { 0x00000627u, 0x00000653u }, { 0x00000627u, 0x00000654u },  // 00000622
        { 0x00000648u, 0x00000654u }, { 0x00000627u, 0x00000655u },  // 00000624
        { 0x0000064Au, 0x00000654u }, { 0x00000627u, 0x00000000u },  // 00000626
        { 0x00000628u, 0x00000000u }, { 0x00000629u, 0x00000000u },  // 00000628
        { 0x0000062Au, 0x00000000u }, { 0x0000062Bu, 0x00000000u },  // 0000062A
        { 0x0000062Cu, 0x00000000u }, { 0x0000062Du, 0x00000000u },  // 0000062C
        { 0x0000062Eu, 0x00000000u }, { 0x0000062Fu, 0x00000000u },  // 0000062E
        { 0x00000630u, 0x00000000u }, { 0x00000631u, 0x00000000u },  // 00000630
        { 0x00000632u, 0x00000000u }, { 0x00000633u, 0x00000000u },  // 00000632
        { 0x00000634u, 0x00000000u }, { 0x00000635u, 0x00000000u },  // 00000634
        { 0x00000636u, 0x00000000u }, { 0x00000637u, 0x00000000u },  // 00000636
        { 0x00000638u, 0x00000000u }, { 0x00000639u, 0x00000000u },  // 00000638
        { 0x0000063Au, 0x00000000u }, { 0x0000063Bu, 0x00000000u },  // 0000063A
        { 0x0000063Cu, 0x00000000u }, { 0x0000063Du, 0x00000000u },  // 0000063C
        { 0x0000063Eu, 0x00000000u }, { 0x0000063Fu, 0x00000000u },  // 0000063E
        { 0x00000640u, 0x00000000u }, { 0x00000641u, 0x00000000u },  // 00000640
        { 0x00000642u, 0x00000000u }, { 0x00000643u, 0x00000000u },  // 00000642
        { 0x00000644u, 0x00000000u }, { 0x00000645u, 0x00000000u },  // 00000644
        { 0x00000646u, 0x00000000u }, { 0x00000647u, 0x00000000u },  // 00000646
        { 0x00000648u, 0x00000000u }, { 0x00000649u, 0x00000000u },  // 00000648
        { 0x0000064Au, 0x00000000u }, { 0x0000064Bu, 0x00000000u },  // 0000064A
        { 0x0000064Cu, 0x00000000u }, { 0x0000064Du, 0x00000000u },  // 0000064C
        { 0x0000064Eu, 0x00000000u }, { 0x0000064Fu, 0x00000000u },  // 0000064E
        { 0x00000650u, 0x00000000u }, { 0x00000651u, 0x00000000u },  // 00000650
        { 0x00000652u, 0x00000000u }, { 0x00000653u, 0x00000000u },  // 00000652
        { 0x00000654u, 0x00000000u }, { 0x00000655u, 0x00000000u },  // 00000654
        { 0x00000656u, 0x00000000u }, { 0x00000657u, 0x00000000u },  // 00000656
        { 0x00000658u, 0x00000000u }, { 0x00000659u, 0x00000000u },  // 00000658
        { 0x0000065Au, 0x00000000u }, { 0x0000065Bu, 0x00000000u },  // 0000065A
        { 0x0000065Cu, 0x00000000u }, { 0x0000065Du, 0x00000000u },  // 0000065C
        { 0x0000065Eu, 0x00000000u }, { 0x0000065Fu, 0x00000000u },  // 0000065E
        { 0x00000660u, 0x00000000u }, { 0x00000661u, 0x00000000u },  // 00000660
        { 0x00000662u, 0x00000000u }, { 0x00000663u, 0x00000000u },  // 00000662
        { 0x00000664u, 0x00000000u }, { 0x00000665u, 0x00000000u },  // 00000664
        { 0x00000666u, 0x00000000u }, { 0x00000667u, 0x00000000u },  // 00000666
        { 0x00000668u, 0x00000000u }, { 0x00000669u, 0x00000000u },  // 00000668
        { 0x0000066Au, 0x00000000u }, { 0x0000066Bu, 0x00000000u },  // 0000066A
        { 0x0000066Cu, 0x00000000u }, { 0x0000066Du, 0x00000000u },  // 0000066C
        { 0x0000066Eu, 0x00000000u }, { 0x0000066Fu, 0x00000000u },  // 0000066E
        { 0x00000670u, 0x00000000u }, { 0x00000671u, 0x00000000u },  // 00000670
        { 0x00000672u, 0x00000000u }, { 0x00000673u, 0x00000000u },  // 00000672
        { 0x00000674u, 0x00000000u }, { 0x00000627u, 0x00000674u },  // 00000674
        { 0x00000648u, 0x00000674u }, { 0x000006C7u, 0x00000674u },  // 00000676
        { 0x0000064Au, 0x00000674u }, { 0x00000679u, 0x00000000u },  // 00000678
        { 0x0000067Au, 0x00000000u }, { 0x0000067Bu, 0x00000000u },  // 0000067A
        { 0x0000067Cu, 0x00000000u }, { 0x0000067Du, 0x00000000u },  // 0000067C
        { 0x0000067Eu, 0x00000000u }, { 0x0000067Fu, 0x00000000u },  // 0000067E
        { 0x00000680u, 0x00000000u }, { 0x00000681u, 0x00000000u },  // 00000680
        { 0x00000682u, 0x00000000u }, { 0x00000683u, 0x00000000u },  // 00000682
        { 0x00000684u, 0x00000000u }, { 0x00000685u, 0x00000000u },  // 00000684
        { 0x00000686u, 0x00000000u }, { 0x00000687u, 0x00000000u },  // 00000686
        { 0x00000688u, 0x00000000u }, { 0x00000689u, 0x00000000u },  // 00000688
        { 0x0000068Au, 0x00000000u }, { 0x0000068Bu, 0x00000000u },  // 0000068A
        { 0x0000068Cu, 0x00000000u }, { 0x0000068Du, 0x00000000u },  // 0000068C
        { 0x0000068Eu, 0x00000000u }, { 0x0000068Fu, 0x00000000u },  // 0000068E
        { 0x00000690u, 0x00000000u }, { 0x00000691u, 0x00000000u },  // 00000690
        { 0x00000692u, 0x00000000u }, { 0x00000693u, 0x00000000u },  // 00000692
        { 0x00000694u, 0x00000000u }, { 0x00000695u, 0x00000000u },  // 00000694
        { 0x00000696u, 0x00000000u }, { 0x00000697u, 0x00000000u },  // 00000696
        { 0x00000698u, 0x00000000u }, { 0x00000699u, 0x00000000u },  // 00000698
        { 0x0000069Au, 0x00000000u }, { 0x0000069Bu, 0x00000000u },  // 0000069A
        { 0x0000069Cu, 0x00000000u }, { 0x0000069Du, 0x00000000u },  // 0000069C
        { 0x0000069Eu, 0x00000000u }, { 0x0000069Fu, 0x00000000u },  // 0000069E
        { 0x000006A0u, 0x00000000u }, { 0x000006A1u, 0x00000000u },  // 000006A0
        { 0x000006A2u, 0x00000000u }, { 0x000006A3u, 0x00000000u },  // 000006A2
        { 0x000006A4u, 0x00000000u }, { 0x000006A5u, 0x00000000u },  // 000006A4
        { 0x000006A6u, 0x00000000u }, { 0x000006A7u, 0x00000000u },  // 000006A6
        { 0x000006A8u, 0x00000000u }, { 0x000006A9u, 0x00000000u },  // 000006A8
        { 0x000006AAu, 0x00000000u }, { 0x000006ABu, 0x00000000u },  // 000006AA
        { 0x000006ACu, 0x00000000u }, { 0x000006ADu, 0x00000000u },  // 000006AC
        { 0x000006AEu, 0x00000000u }, { 0x000006AFu, 0x00000000u },  // 000006AE
        { 0x000006B0u, 0x00000000u }, { 0x000006B1u, 0x00000000u },  // 000006B0
        { 0x000006B2u, 0x00000000u }, { 0x000006B3u, 0x00000000u },  // 000006B2
        { 0x000006B4u, 0x00000000u }, { 0x000006B5u, 0x00000000u },  // 000006B4
        { 0x000006B6u, 0x00000000u }, { 0x000006B7u, 0x00000000u },  // 000006B6
        { 0x000006B8u, 0x00000000u }, { 0x000006B9u, 0x00000000u },  // 000006B8
        { 0x000006BAu, 0x00000000u }, { 0x000006BBu, 0x00000000u },  // 000006BA
        { 0x000006BCu, 0x00000000u }, { 0x000006BDu, 0x00000000u },  // 000006BC
        { 0x000006BEu, 0x00000000u }, { 0x000006BFu, 0x00000000u },  // 000006BE
        { 0x000006D5u, 0x00000654u }, { 0x000006C1u, 0x00000000u },  // 000006C0
        { 0x000006C1u, 0x00000654u }, { 0x000006C3u, 0x00000000u },  // 000006C2
        { 0x000006C4u, 0x00000000u }, { 0x000006C5u, 0x00000000u },  // 000006C4
        { 0x000006C6u, 0x00000000u }, { 0x000006C7u, 0x00000000u },  // 000006C6
        { 0x000006C8u, 0x00000000u }, { 0x000006C9u, 0x00000000u },  // 000006C8
        { 0x000006CAu, 0x00000000u }, { 0x000006CBu, 0x00000000u },  // 000006CA
        { 0x000006CCu, 0x00000000u }, { 0x000006CDu, 0x00000000u },  // 000006CC
        { 0x000006CEu, 0x00000000u }, { 0x000006CFu, 0x00000000u },  // 000006CE
        { 0x000006D0u, 0x00000000u }, { 0x000006D1u, 0x00000000u },  // 000006D0
        { 0x000006D2u, 0x00000000u }, { 0x000006D2u, 0x00000654u },  // 000006D2
        { 0x000006D4u, 0x00000000u }, { 0x000006D5u, 0x00000000u },  // 000006D4
        { 0x000006D6u, 0x00000000u }, { 0x000006D7u, 0x00000000u },  // 000006D6
        { 0x000006D8u, 0x00000000u }, { 0x000006D9u, 0x00000000u },  // 000006D8
        { 0x000006DAu, 0x00000000u }, { 0x000006DBu, 0x00000000u },  // 000006DA
        { 0x000006DCu, 0x00000000u }, { 0x000006DDu, 0x00000000u },  // 000006DC
        { 0x000006DEu, 0x00000000u }, { 0x000006DFu, 0x00000000u },  // 000006DE
        { 0x000006E0u, 0x00000000u }, { 0x000006E1u, 0x00000000u },  // 000006E0
        { 0x000006E2u, 0x00000000u }, { 0x000006E3u, 0x00000000u },  // 000006E2
        { 0x000006E4u, 0x00000000u }, { 0x000006E5u, 0x00000000u },  // 000006E4
        { 0x000006E6u, 0x00000000u }, { 0x000006E7u, 0x00000000u },  // 000006E6
        { 0x000006E8u, 0x00000000u }, { 0x000006E9u, 0x00000000u },  // 000006E8
        { 0x000006EAu, 0x00000000u }, { 0x000006EBu, 0x00000000u },  // 000006EA
        { 0x000006ECu, 0x00000000u }, { 0x000006EDu, 0x00000000u },  // 000006EC
        { 0x000006EEu, 0x00000000u }, { 0x000006EFu, 0x00000000u },  // 000006EE
        { 0x000006F0u, 0x00000000u }, { 0x000006F1u, 0x00000000u },  // 000006F0
        { 0x000006F2u, 0x00000000u }, { 0x000006F3u, 0x00000000u },  // 000006F2
        { 0x000006F4u, 0x00000000u }, { 0x000006F5u, 0x00000000u },  // 000006F4
        { 0x000006F6u, 0x00000000u }, { 0x000006F7u, 0x00000000u },  // 000006F6
        { 0x000006F8u, 0x00000000u }, { 0x000006F9u, 0x00000000u },  // 000006F8
        { 0x000006FAu, 0x00000000u }, { 0x000006FBu, 0x00000000u },  // 000006FA
        { 0x000006FCu, 0x00000000u }, { 0x000006FDu, 0x00000000u },  // 000006FC
        { 0x000006FEu, 0x00000000u }, { 0x000006FFu, 0x00000000u }
    };

    const unsigned char Arabic600::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_IS, LB_AL, LB_AL, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_CM, 
        LB_CM, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const std::bitset<256> Arabic600::my_Terminal_Punctuation(std::string("0000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010001000000000000001000000000000"));

    const std::bitset<256> Arabic600::my_Other_Alphabetic(std::string("0000000000000000001000011001111000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000001111111111111000000000000000000000000000000000000000000000000000001111110000000000000000"));

    const std::bitset<256> Arabic600::my_Diacritic(std::string("0000000000000000000111000110000110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011000011111111000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<256> Arabic600::my_Extender(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Arabic600);
