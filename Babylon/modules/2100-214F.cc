/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 2100-214F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:56:00 +0200.
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
    class Letterlike_Symbols2100 : public Babylon::Block
    {
      public:
        void clean() { };

        Letterlike_Symbols2100() :
	    my_first_letter(0x2100),
	    my_last_letter(0x214F)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~Letterlike_Symbols2100() { }

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
	    return "Letterlike Symbols";
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
            return Letterlike_Symbols2100::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return uc;
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
            return 0;
        }

        bool is_Digit(const UCS4 uc) const
        {
            return 0;
        }

        float numeric_value(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Numeric(const UCS4 uc) const
        {
            return 0;
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Letterlike_Symbols2100::my_cat[uc - my_first_letter]);
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
            return Letterlike_Symbols2100::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Letterlike_Symbols2100::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Letterlike_Symbols2100::my_decompStr[uc - my_first_letter][0];
            us[1] = Letterlike_Symbols2100::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

            case 0x2100:
                us.resize(3);
                us[2u] = 0x0063u;
                break;

            case 0x2101:
                us.resize(3);
                us[2u] = 0x0073u;
                break;

            case 0x2105:
                us.resize(3);
                us[2u] = 0x006Fu;
                break;

            case 0x2106:
                us.resize(3);
                us[2u] = 0x0075u;
                break;

            case 0x2121:
                us.resize(3);
                us[2u] = 0x004Cu;
                break;

            case 0x213B:
                us.resize(3);
                us[2u] = 0x0058u;
                break;
            }
            if (0x0000u == us[1])
                us.resize(1);
            return us;
        }

        bool must_mirror(const UCS4 uc) const
        {
            return my_mirror.test(uc - my_first_letter);
        }

        Line_Break linebreak(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return LB_MAX;
            return Babylon::Line_Break(Letterlike_Symbols2100::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Letterlike_Symbols2100::my_ea[uc - my_first_letter]);
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
            return my_Other_Math.test(uc - my_first_letter);
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
            return my_Other_ID_Start.test(uc - my_first_letter);
        }

      private:
        // functions
        Letterlike_Symbols2100(const Letterlike_Symbols2100 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<80> my_is_defined;
        static const UCS4 my_lower[80];
        static const unsigned char my_cat[80];
        static const Babylon::Bidir_Props my_bidir[80];
        static const unsigned char my_decomp[80];
        static const UCS2 my_decompStr[80][2];
        static const std::bitset<80> my_mirror;
        static const unsigned char my_lb[80];
        static const unsigned char my_ea[80];
        static const std::bitset<80> my_Other_Math;
        static const std::bitset<80> my_Other_ID_Start;
    }; // class Letterlike_Symbols2100

    const std::bitset<80> Letterlike_Symbols2100::my_is_defined(std::string("00001111111111111110111111111111111111111111111111111111111111111111111111111111"));

    const UCS4 Letterlike_Symbols2100::my_lower[] =
    {
        0x2100, 0x2101, 0x2102, 0x2103, 0x2104, 0x2105, 0x2106, 0x2107, 
        0x2108, 0x2109, 0x210A, 0x210B, 0x210C, 0x210D, 0x210E, 0x210F, 
        0x2110, 0x2111, 0x2112, 0x2113, 0x2114, 0x2115, 0x2116, 0x2117, 
        0x2118, 0x2119, 0x211A, 0x211B, 0x211C, 0x211D, 0x211E, 0x211F, 
        0x2120, 0x2121, 0x2122, 0x2123, 0x2124, 0x2125, 0x03C9, 0x2127, 
        0x2128, 0x2129, 0x006B, 0x00E5, 0x212C, 0x212D, 0x212E, 0x212F, 
        0x2130, 0x2131, 0x2132, 0x2133, 0x2134, 0x2135, 0x2136, 0x2137, 
        0x2138, 0x2139, 0x213A, 0x213B, 0x213C, 0x213D, 0x213E, 0x213F, 
        0x2140, 0x2141, 0x2142, 0x2143, 0x2144, 0x2145, 0x2146, 0x2147, 
        0x2148, 0x2149, 0x214A, 0x214B, 0x214C, 0x214D, 0x214E, 0x214F
    };

    const unsigned char Letterlike_Symbols2100::my_cat[] =
    {
        CAT_So, CAT_So, CAT_Lu, CAT_So, CAT_So, CAT_So, CAT_So, CAT_Lu, 
        CAT_So, CAT_So, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_So, CAT_Lu, CAT_So, CAT_So, 
        CAT_So, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_Lu, CAT_So, CAT_Lu, CAT_So, 
        CAT_Lu, CAT_So, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_So, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_So, CAT_Lu, CAT_Ll, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Ll, CAT_So, CAT_So, CAT_So, CAT_Ll, CAT_Lu, CAT_Lu, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_So, CAT_Sm, CAT_So, CAT_So, CAT_So, CAT_So
    };

    const Babylon::Bidir_Props Letterlike_Symbols2100::my_bidir[] =
    {
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_L, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_ON, 
        BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ET, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
    };

    const unsigned char Letterlike_Symbols2100::my_decomp[] = {
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_FONT, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_CANONICAL, DECOMP_FONT, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_SUPER, DECOMP_COMPAT, DECOMP_SUPER, DECOMP_CANONICAL, 
        DECOMP_FONT, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_FONT, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_FONT, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Letterlike_Symbols2100::my_decompStr[][2] =
    {
        { 0x00000061u, 0x0000002Fu }, { 0x00000061u, 0x0000002Fu },  // 00002100
        { 0x00000043u, 0x00000000u }, { 0x000000B0u, 0x00000043u },  // 00002102
        { 0x00002104u, 0x00000000u }, { 0x00000063u, 0x0000002Fu },  // 00002104
        { 0x00000063u, 0x0000002Fu }, { 0x00000190u, 0x00000000u },  // 00002106
        { 0x00002108u, 0x00000000u }, { 0x000000B0u, 0x00000046u },  // 00002108
        { 0x00000067u, 0x00000000u }, { 0x00000048u, 0x00000000u },  // 0000210A
        { 0x00000048u, 0x00000000u }, { 0x00000048u, 0x00000000u },  // 0000210C
        { 0x00000068u, 0x00000000u }, { 0x00000127u, 0x00000000u },  // 0000210E
        { 0x00000049u, 0x00000000u }, { 0x00000049u, 0x00000000u },  // 00002110
        { 0x0000004Cu, 0x00000000u }, { 0x0000006Cu, 0x00000000u },  // 00002112
        { 0x00002114u, 0x00000000u }, { 0x0000004Eu, 0x00000000u },  // 00002114
        { 0x0000004Eu, 0x0000006Fu }, { 0x00002117u, 0x00000000u },  // 00002116
        { 0x00002118u, 0x00000000u }, { 0x00000050u, 0x00000000u },  // 00002118
        { 0x00000051u, 0x00000000u }, { 0x00000052u, 0x00000000u },  // 0000211A
        { 0x00000052u, 0x00000000u }, { 0x00000052u, 0x00000000u },  // 0000211C
        { 0x0000211Eu, 0x00000000u }, { 0x0000211Fu, 0x00000000u },  // 0000211E
        { 0x00000053u, 0x0000004Du }, { 0x00000054u, 0x00000045u },  // 00002120
        { 0x00000054u, 0x0000004Du }, { 0x00002123u, 0x00000000u },  // 00002122
        { 0x0000005Au, 0x00000000u }, { 0x00002125u, 0x00000000u },  // 00002124
        { 0x000003A9u, 0x00000000u }, { 0x00002127u, 0x00000000u },  // 00002126
        { 0x0000005Au, 0x00000000u }, { 0x00002129u, 0x00000000u },  // 00002128
        { 0x0000004Bu, 0x00000000u }, { 0x000000C5u, 0x00000000u },  // 0000212A
        { 0x00000042u, 0x00000000u }, { 0x00000043u, 0x00000000u },  // 0000212C
        { 0x0000212Eu, 0x00000000u }, { 0x00000065u, 0x00000000u },  // 0000212E
        { 0x00000045u, 0x00000000u }, { 0x00000046u, 0x00000000u },  // 00002130
        { 0x00002132u, 0x00000000u }, { 0x0000004Du, 0x00000000u },  // 00002132
        { 0x0000006Fu, 0x00000000u }, { 0x000005D0u, 0x00000000u },  // 00002134
        { 0x000005D1u, 0x00000000u }, { 0x000005D2u, 0x00000000u },  // 00002136
        { 0x000005D3u, 0x00000000u }, { 0x00000069u, 0x00000000u },  // 00002138
        { 0x0000213Au, 0x00000000u }, { 0x00000046u, 0x00000041u },  // 0000213A
        { 0x0000213Cu, 0x00000000u }, { 0x000003B3u, 0x00000000u },  // 0000213C
        { 0x00000393u, 0x00000000u }, { 0x000003A0u, 0x00000000u },  // 0000213E
        { 0x00002211u, 0x00000000u }, { 0x00002141u, 0x00000000u },  // 00002140
        { 0x00002142u, 0x00000000u }, { 0x00002143u, 0x00000000u },  // 00002142
        { 0x00002144u, 0x00000000u }, { 0x00000044u, 0x00000000u },  // 00002144
        { 0x00000064u, 0x00000000u }, { 0x00000065u, 0x00000000u },  // 00002146
        { 0x00000069u, 0x00000000u }, { 0x0000006Au, 0x00000000u },  // 00002148
        { 0x0000214Au, 0x00000000u }, { 0x0000214Bu, 0x00000000u },  // 0000214A
        { 0x0000214Cu, 0x00000000u }, { 0x0000214Du, 0x00000000u },  // 0000214C
        { 0x0000214Eu, 0x00000000u }, { 0x0000214Fu, 0x00000000u }
    };

    const std::bitset<80> Letterlike_Symbols2100::my_mirror(std::string("00000000000000010000000000000000000000000000000000000000000000000000000000000000"));

    const unsigned char Letterlike_Symbols2100::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_PO, LB_AL, LB_AI, LB_AL, LB_AL, 
        LB_AL, LB_PO, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_PR, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_PO, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const unsigned char Letterlike_Symbols2100::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
    };

    const std::bitset<80> Letterlike_Symbols2100::my_Other_Math(std::string("00000000000000000000000111111011101100010001000000111110001011111111110000000100"));

    const std::bitset<80> Letterlike_Symbols2100::my_Other_ID_Start(std::string("00000000000000000000000000000000010000000000000000000001000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Letterlike_Symbols2100);
