/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 2150-218F.cc
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
    class Number_Forms2150 : public Babylon::Block
    {
      public:
        void clean() { };

        Number_Forms2150() :
	    my_first_letter(0x2150),
	    my_last_letter(0x218F)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~Number_Forms2150() { }

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
	    return "Number Forms";
	}

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Number_Forms2150::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Number_Forms2150::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Number_Forms2150::my_title[uc - my_first_letter];
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
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x2153u:
                return 0.333333;
            case 0x2154u:
                return 0.666667;
            case 0x2155u:
                return 0.200000;
            case 0x2156u:
                return 0.400000;
            case 0x2157u:
                return 0.600000;
            case 0x2158u:
                return 0.800000;
            case 0x2159u:
                return 0.166667;
            case 0x215Au:
                return 0.833333;
            case 0x215Bu:
                return 0.125000;
            case 0x215Cu:
                return 0.375000;
            case 0x215Du:
                return 0.625000;
            case 0x215Eu:
                return 0.875000;
            case 0x215Fu:
                return 1.000000;
            case 0x2160u:
                return 1.000000;
            case 0x2161u:
                return 2.000000;
            case 0x2162u:
                return 3.000000;
            case 0x2163u:
                return 4.000000;
            case 0x2164u:
                return 5.000000;
            case 0x2165u:
                return 6.000000;
            case 0x2166u:
                return 7.000000;
            case 0x2167u:
                return 8.000000;
            case 0x2168u:
                return 9.000000;
            case 0x2169u:
                return 10.000000;
            case 0x216Au:
                return 11.000000;
            case 0x216Bu:
                return 12.000000;
            case 0x216Cu:
                return 50.000000;
            case 0x216Du:
                return 100.000000;
            case 0x216Eu:
                return 500.000000;
            case 0x216Fu:
                return 1000.000000;
            case 0x2170u:
                return 1.000000;
            case 0x2171u:
                return 2.000000;
            case 0x2172u:
                return 3.000000;
            case 0x2173u:
                return 4.000000;
            case 0x2174u:
                return 5.000000;
            case 0x2175u:
                return 6.000000;
            case 0x2176u:
                return 7.000000;
            case 0x2177u:
                return 8.000000;
            case 0x2178u:
                return 9.000000;
            case 0x2179u:
                return 10.000000;
            case 0x217Au:
                return 11.000000;
            case 0x217Bu:
                return 12.000000;
            case 0x217Cu:
                return 50.000000;
            case 0x217Du:
                return 100.000000;
            case 0x217Eu:
                return 500.000000;
            case 0x217Fu:
                return 1000.000000;
            case 0x2180u:
                return 1000.000000;
            case 0x2181u:
                return 5000.000000;
            case 0x2182u:
                return 10000.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x2153u:
            case 0x2154u:
            case 0x2155u:
            case 0x2156u:
            case 0x2157u:
            case 0x2158u:
            case 0x2159u:
            case 0x215Au:
            case 0x215Bu:
            case 0x215Cu:
            case 0x215Du:
            case 0x215Eu:
            case 0x215Fu:
            case 0x2160u:
            case 0x2161u:
            case 0x2162u:
            case 0x2163u:
            case 0x2164u:
            case 0x2165u:
            case 0x2166u:
            case 0x2167u:
            case 0x2168u:
            case 0x2169u:
            case 0x216Au:
            case 0x216Bu:
            case 0x216Cu:
            case 0x216Du:
            case 0x216Eu:
            case 0x216Fu:
            case 0x2170u:
            case 0x2171u:
            case 0x2172u:
            case 0x2173u:
            case 0x2174u:
            case 0x2175u:
            case 0x2176u:
            case 0x2177u:
            case 0x2178u:
            case 0x2179u:
            case 0x217Au:
            case 0x217Bu:
            case 0x217Cu:
            case 0x217Du:
            case 0x217Eu:
            case 0x217Fu:
            case 0x2180u:
            case 0x2181u:
            case 0x2182u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Number_Forms2150::my_cat[uc - my_first_letter]);
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
            return Number_Forms2150::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Number_Forms2150::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Number_Forms2150::my_decompStr[uc - my_first_letter][0];
            us[1] = Number_Forms2150::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

            case 0x2153:
                us.resize(3);
                us[2u] = 0x0033u;
                break;

            case 0x2154:
                us.resize(3);
                us[2u] = 0x0033u;
                break;

            case 0x2155:
                us.resize(3);
                us[2u] = 0x0035u;
                break;

            case 0x2156:
                us.resize(3);
                us[2u] = 0x0035u;
                break;

            case 0x2157:
                us.resize(3);
                us[2u] = 0x0035u;
                break;

            case 0x2158:
                us.resize(3);
                us[2u] = 0x0035u;
                break;

            case 0x2159:
                us.resize(3);
                us[2u] = 0x0036u;
                break;

            case 0x215A:
                us.resize(3);
                us[2u] = 0x0036u;
                break;

            case 0x215B:
                us.resize(3);
                us[2u] = 0x0038u;
                break;

            case 0x215C:
                us.resize(3);
                us[2u] = 0x0038u;
                break;

            case 0x215D:
                us.resize(3);
                us[2u] = 0x0038u;
                break;

            case 0x215E:
                us.resize(3);
                us[2u] = 0x0038u;
                break;

            case 0x2162:
                us.resize(3);
                us[2u] = 0x0049u;
                break;

            case 0x2166:
                us.resize(3);
                us[2u] = 0x0049u;
                break;

            case 0x2167:
                us.resize(4);
                us[2u] = 0x0049u;
                us[3u] = 0x0049u;
                break;

            case 0x216B:
                us.resize(3);
                us[2u] = 0x0049u;
                break;

            case 0x2172:
                us.resize(3);
                us[2u] = 0x0069u;
                break;

            case 0x2176:
                us.resize(3);
                us[2u] = 0x0069u;
                break;

            case 0x2177:
                us.resize(4);
                us[2u] = 0x0069u;
                us[3u] = 0x0069u;
                break;

            case 0x217B:
                us.resize(3);
                us[2u] = 0x0069u;
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
            return Babylon::Line_Break(Number_Forms2150::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Number_Forms2150::my_ea[uc - my_first_letter]);
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
            return my_Other_Alphabetic.test(uc - my_first_letter);
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

      private:
        // functions
        Number_Forms2150(const Number_Forms2150 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<64> my_is_defined;
        static const UCS4 my_upper[64];
        static const UCS4 my_lower[64];
        static const UCS4 my_title[64];
        static const unsigned char my_cat[64];
        static const Babylon::Bidir_Props my_bidir[64];
        static const unsigned char my_decomp[64];
        static const UCS2 my_decompStr[64][2];
        static const unsigned char my_lb[64];
        static const unsigned char my_ea[64];
        static const std::bitset<64> my_Other_Alphabetic;
        static const std::bitset<64> my_Other_Lowercase;
        static const std::bitset<64> my_Other_Uppercase;
    }; // class Number_Forms2150

    const std::bitset<64> Number_Forms2150::my_is_defined(std::string("0000000000001111111111111111111111111111111111111111111111111000"));

    const UCS4 Number_Forms2150::my_upper[] =
    {
        0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
        0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
        0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
        0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
        0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
        0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
        0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
        0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
    };

    const UCS4 Number_Forms2150::my_lower[] =
    {
        0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
        0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
        0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 0x2176, 0x2177, 
        0x2178, 0x2179, 0x217A, 0x217B, 0x217C, 0x217D, 0x217E, 0x217F, 
        0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 0x2176, 0x2177, 
        0x2178, 0x2179, 0x217A, 0x217B, 0x217C, 0x217D, 0x217E, 0x217F, 
        0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
        0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
    };

    const UCS4 Number_Forms2150::my_title[] =
    {
        0x2150, 0x2151, 0x2152, 0x2153, 0x2154, 0x2155, 0x2156, 0x2157, 
        0x2158, 0x2159, 0x215A, 0x215B, 0x215C, 0x215D, 0x215E, 0x215F, 
        0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
        0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
        0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 
        0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 
        0x2180, 0x2181, 0x2182, 0x2183, 0x2184, 0x2185, 0x2186, 0x2187, 
        0x2188, 0x2189, 0x218A, 0x218B, 0x218C, 0x218D, 0x218E, 0x218F
    };

    const unsigned char Number_Forms2150::my_cat[] =
    {
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
        CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
        CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
        CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
        CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No
    };

    const Babylon::Bidir_Props Number_Forms2150::my_bidir[] =
    {
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
    };

    const unsigned char Number_Forms2150::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_FRACTION, 
        DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, 
        DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, 
        DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Number_Forms2150::my_decompStr[][2] =
    {
        { 0x00002150u, 0x00000000u }, { 0x00002151u, 0x00000000u },  // 00002150
        { 0x00002152u, 0x00000000u }, { 0x00000031u, 0x00002044u },  // 00002152
        { 0x00000032u, 0x00002044u }, { 0x00000031u, 0x00002044u },  // 00002154
        { 0x00000032u, 0x00002044u }, { 0x00000033u, 0x00002044u },  // 00002156
        { 0x00000034u, 0x00002044u }, { 0x00000031u, 0x00002044u },  // 00002158
        { 0x00000035u, 0x00002044u }, { 0x00000031u, 0x00002044u },  // 0000215A
        { 0x00000033u, 0x00002044u }, { 0x00000035u, 0x00002044u },  // 0000215C
        { 0x00000037u, 0x00002044u }, { 0x00000031u, 0x00002044u },  // 0000215E
        { 0x00000049u, 0x00000000u }, { 0x00000049u, 0x00000049u },  // 00002160
        { 0x00000049u, 0x00000049u }, { 0x00000049u, 0x00000056u },  // 00002162
        { 0x00000056u, 0x00000000u }, { 0x00000056u, 0x00000049u },  // 00002164
        { 0x00000056u, 0x00000049u }, { 0x00000056u, 0x00000049u },  // 00002166
        { 0x00000049u, 0x00000058u }, { 0x00000058u, 0x00000000u },  // 00002168
        { 0x00000058u, 0x00000049u }, { 0x00000058u, 0x00000049u },  // 0000216A
        { 0x0000004Cu, 0x00000000u }, { 0x00000043u, 0x00000000u },  // 0000216C
        { 0x00000044u, 0x00000000u }, { 0x0000004Du, 0x00000000u },  // 0000216E
        { 0x00000069u, 0x00000000u }, { 0x00000069u, 0x00000069u },  // 00002170
        { 0x00000069u, 0x00000069u }, { 0x00000069u, 0x00000076u },  // 00002172
        { 0x00000076u, 0x00000000u }, { 0x00000076u, 0x00000069u },  // 00002174
        { 0x00000076u, 0x00000069u }, { 0x00000076u, 0x00000069u },  // 00002176
        { 0x00000069u, 0x00000078u }, { 0x00000078u, 0x00000000u },  // 00002178
        { 0x00000078u, 0x00000069u }, { 0x00000078u, 0x00000069u },  // 0000217A
        { 0x0000006Cu, 0x00000000u }, { 0x00000063u, 0x00000000u },  // 0000217C
        { 0x00000064u, 0x00000000u }, { 0x0000006Du, 0x00000000u },  // 0000217E
        { 0x00002180u, 0x00000000u }, { 0x00002181u, 0x00000000u },  // 00002180
        { 0x00002182u, 0x00000000u }, { 0x00002183u, 0x00000000u },  // 00002182
        { 0x00002184u, 0x00000000u }, { 0x00002185u, 0x00000000u },  // 00002184
        { 0x00002186u, 0x00000000u }, { 0x00002187u, 0x00000000u },  // 00002186
        { 0x00002188u, 0x00000000u }, { 0x00002189u, 0x00000000u },  // 00002188
        { 0x0000218Au, 0x00000000u }, { 0x0000218Bu, 0x00000000u },  // 0000218A
        { 0x0000218Cu, 0x00000000u }, { 0x0000218Du, 0x00000000u },  // 0000218C
        { 0x0000218Eu, 0x00000000u }, { 0x0000218Fu, 0x00000000u }
    };

    const unsigned char Number_Forms2150::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AI, LB_AL, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const unsigned char Number_Forms2150::my_ea[] =
    {
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A
    };

    const std::bitset<64> Number_Forms2150::my_Other_Alphabetic(std::string("0000000000001111111111111111111111111111111111110000000000000000"));

    const std::bitset<64> Number_Forms2150::my_Other_Lowercase(std::string("0000000000000000111111111111111100000000000000000000000000000000"));

    const std::bitset<64> Number_Forms2150::my_Other_Uppercase(std::string("0000000000000000000000000000000011111111111111110000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Number_Forms2150);
