/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 1000-109F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:42 +0200.
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
    class Myanmar1000 : public Babylon::Block
    {
      public:
        void clean() { };

        Myanmar1000() :
	    my_first_letter(0x1000),
	    my_last_letter(0x109F)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00001025, 0x0000102E)] = 0x1026;
            }
        }

        ~Myanmar1000() { }

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
	    return "Myanmar";
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
            case 0x1040u:
                return 0;
            case 0x1041u:
                return 1;
            case 0x1042u:
                return 2;
            case 0x1043u:
                return 3;
            case 0x1044u:
                return 4;
            case 0x1045u:
                return 5;
            case 0x1046u:
                return 6;
            case 0x1047u:
                return 7;
            case 0x1048u:
                return 8;
            case 0x1049u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x1040u:
            case 0x1041u:
            case 0x1042u:
            case 0x1043u:
            case 0x1044u:
            case 0x1045u:
            case 0x1046u:
            case 0x1047u:
            case 0x1048u:
            case 0x1049u:
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
            case 0x1040u:
                return 0;
            case 0x1041u:
                return 1;
            case 0x1042u:
                return 2;
            case 0x1043u:
                return 3;
            case 0x1044u:
                return 4;
            case 0x1045u:
                return 5;
            case 0x1046u:
                return 6;
            case 0x1047u:
                return 7;
            case 0x1048u:
                return 8;
            case 0x1049u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x1040u:
            case 0x1041u:
            case 0x1042u:
            case 0x1043u:
            case 0x1044u:
            case 0x1045u:
            case 0x1046u:
            case 0x1047u:
            case 0x1048u:
            case 0x1049u:
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
            case 0x1040u:
                return 0.000000;
            case 0x1041u:
                return 1.000000;
            case 0x1042u:
                return 2.000000;
            case 0x1043u:
                return 3.000000;
            case 0x1044u:
                return 4.000000;
            case 0x1045u:
                return 5.000000;
            case 0x1046u:
                return 6.000000;
            case 0x1047u:
                return 7.000000;
            case 0x1048u:
                return 8.000000;
            case 0x1049u:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x1040u:
            case 0x1041u:
            case 0x1042u:
            case 0x1043u:
            case 0x1044u:
            case 0x1045u:
            case 0x1046u:
            case 0x1047u:
            case 0x1048u:
            case 0x1049u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Myanmar1000::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(Myanmar1000::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return Myanmar1000::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(DECOMP_CANONICAL);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Myanmar1000::my_decompStr[uc - my_first_letter][0];
            us[1] = Myanmar1000::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Myanmar1000::my_lb[uc - my_first_letter]);
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
            return my_Grapheme_Link.test(uc - my_first_letter);
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
        Myanmar1000(const Myanmar1000 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<160> my_is_defined;
        static const unsigned char my_cat[160];
        static const unsigned char my_comb_cl[160];
        static const Babylon::Bidir_Props my_bidir[160];
        static const UCS2 my_decompStr[160][2];
        static const unsigned char my_lb[160];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<160> my_Terminal_Punctuation;
        static const std::bitset<160> my_Other_Alphabetic;
        static const std::bitset<160> my_Diacritic;
        static const std::bitset<160> my_Grapheme_Link;
    }; // class Myanmar1000

    const std::bitset<160> Myanmar1000::my_is_defined(std::string("0000000000000000000000000000000000000000000000000000000000000000000000111111111111111111111111110000001111000111111101101111101111111111111111111111111111111111"));

    const unsigned char Myanmar1000::my_cat[] =
    {
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, 
        CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mc, 
        CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo
    };

    const unsigned char Myanmar1000::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 7, 
        0, 9, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props Myanmar1000::my_bidir[] =
    {
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
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
    };

    const UCS2 Myanmar1000::my_decompStr[][2] =
    {
        { 0x00001000u, 0x00000000u }, { 0x00001001u, 0x00000000u },  // 00001000
        { 0x00001002u, 0x00000000u }, { 0x00001003u, 0x00000000u },  // 00001002
        { 0x00001004u, 0x00000000u }, { 0x00001005u, 0x00000000u },  // 00001004
        { 0x00001006u, 0x00000000u }, { 0x00001007u, 0x00000000u },  // 00001006
        { 0x00001008u, 0x00000000u }, { 0x00001009u, 0x00000000u },  // 00001008
        { 0x0000100Au, 0x00000000u }, { 0x0000100Bu, 0x00000000u },  // 0000100A
        { 0x0000100Cu, 0x00000000u }, { 0x0000100Du, 0x00000000u },  // 0000100C
        { 0x0000100Eu, 0x00000000u }, { 0x0000100Fu, 0x00000000u },  // 0000100E
        { 0x00001010u, 0x00000000u }, { 0x00001011u, 0x00000000u },  // 00001010
        { 0x00001012u, 0x00000000u }, { 0x00001013u, 0x00000000u },  // 00001012
        { 0x00001014u, 0x00000000u }, { 0x00001015u, 0x00000000u },  // 00001014
        { 0x00001016u, 0x00000000u }, { 0x00001017u, 0x00000000u },  // 00001016
        { 0x00001018u, 0x00000000u }, { 0x00001019u, 0x00000000u },  // 00001018
        { 0x0000101Au, 0x00000000u }, { 0x0000101Bu, 0x00000000u },  // 0000101A
        { 0x0000101Cu, 0x00000000u }, { 0x0000101Du, 0x00000000u },  // 0000101C
        { 0x0000101Eu, 0x00000000u }, { 0x0000101Fu, 0x00000000u },  // 0000101E
        { 0x00001020u, 0x00000000u }, { 0x00001021u, 0x00000000u },  // 00001020
        { 0x00001022u, 0x00000000u }, { 0x00001023u, 0x00000000u },  // 00001022
        { 0x00001024u, 0x00000000u }, { 0x00001025u, 0x00000000u },  // 00001024
        { 0x00001025u, 0x0000102Eu }, { 0x00001027u, 0x00000000u },  // 00001026
        { 0x00001028u, 0x00000000u }, { 0x00001029u, 0x00000000u },  // 00001028
        { 0x0000102Au, 0x00000000u }, { 0x0000102Bu, 0x00000000u },  // 0000102A
        { 0x0000102Cu, 0x00000000u }, { 0x0000102Du, 0x00000000u },  // 0000102C
        { 0x0000102Eu, 0x00000000u }, { 0x0000102Fu, 0x00000000u },  // 0000102E
        { 0x00001030u, 0x00000000u }, { 0x00001031u, 0x00000000u },  // 00001030
        { 0x00001032u, 0x00000000u }, { 0x00001033u, 0x00000000u },  // 00001032
        { 0x00001034u, 0x00000000u }, { 0x00001035u, 0x00000000u },  // 00001034
        { 0x00001036u, 0x00000000u }, { 0x00001037u, 0x00000000u },  // 00001036
        { 0x00001038u, 0x00000000u }, { 0x00001039u, 0x00000000u },  // 00001038
        { 0x0000103Au, 0x00000000u }, { 0x0000103Bu, 0x00000000u },  // 0000103A
        { 0x0000103Cu, 0x00000000u }, { 0x0000103Du, 0x00000000u },  // 0000103C
        { 0x0000103Eu, 0x00000000u }, { 0x0000103Fu, 0x00000000u },  // 0000103E
        { 0x00001040u, 0x00000000u }, { 0x00001041u, 0x00000000u },  // 00001040
        { 0x00001042u, 0x00000000u }, { 0x00001043u, 0x00000000u },  // 00001042
        { 0x00001044u, 0x00000000u }, { 0x00001045u, 0x00000000u },  // 00001044
        { 0x00001046u, 0x00000000u }, { 0x00001047u, 0x00000000u },  // 00001046
        { 0x00001048u, 0x00000000u }, { 0x00001049u, 0x00000000u },  // 00001048
        { 0x0000104Au, 0x00000000u }, { 0x0000104Bu, 0x00000000u },  // 0000104A
        { 0x0000104Cu, 0x00000000u }, { 0x0000104Du, 0x00000000u },  // 0000104C
        { 0x0000104Eu, 0x00000000u }, { 0x0000104Fu, 0x00000000u },  // 0000104E
        { 0x00001050u, 0x00000000u }, { 0x00001051u, 0x00000000u },  // 00001050
        { 0x00001052u, 0x00000000u }, { 0x00001053u, 0x00000000u },  // 00001052
        { 0x00001054u, 0x00000000u }, { 0x00001055u, 0x00000000u },  // 00001054
        { 0x00001056u, 0x00000000u }, { 0x00001057u, 0x00000000u },  // 00001056
        { 0x00001058u, 0x00000000u }, { 0x00001059u, 0x00000000u },  // 00001058
        { 0x0000105Au, 0x00000000u }, { 0x0000105Bu, 0x00000000u },  // 0000105A
        { 0x0000105Cu, 0x00000000u }, { 0x0000105Du, 0x00000000u },  // 0000105C
        { 0x0000105Eu, 0x00000000u }, { 0x0000105Fu, 0x00000000u },  // 0000105E
        { 0x00001060u, 0x00000000u }, { 0x00001061u, 0x00000000u },  // 00001060
        { 0x00001062u, 0x00000000u }, { 0x00001063u, 0x00000000u },  // 00001062
        { 0x00001064u, 0x00000000u }, { 0x00001065u, 0x00000000u },  // 00001064
        { 0x00001066u, 0x00000000u }, { 0x00001067u, 0x00000000u },  // 00001066
        { 0x00001068u, 0x00000000u }, { 0x00001069u, 0x00000000u },  // 00001068
        { 0x0000106Au, 0x00000000u }, { 0x0000106Bu, 0x00000000u },  // 0000106A
        { 0x0000106Cu, 0x00000000u }, { 0x0000106Du, 0x00000000u },  // 0000106C
        { 0x0000106Eu, 0x00000000u }, { 0x0000106Fu, 0x00000000u },  // 0000106E
        { 0x00001070u, 0x00000000u }, { 0x00001071u, 0x00000000u },  // 00001070
        { 0x00001072u, 0x00000000u }, { 0x00001073u, 0x00000000u },  // 00001072
        { 0x00001074u, 0x00000000u }, { 0x00001075u, 0x00000000u },  // 00001074
        { 0x00001076u, 0x00000000u }, { 0x00001077u, 0x00000000u },  // 00001076
        { 0x00001078u, 0x00000000u }, { 0x00001079u, 0x00000000u },  // 00001078
        { 0x0000107Au, 0x00000000u }, { 0x0000107Bu, 0x00000000u },  // 0000107A
        { 0x0000107Cu, 0x00000000u }, { 0x0000107Du, 0x00000000u },  // 0000107C
        { 0x0000107Eu, 0x00000000u }, { 0x0000107Fu, 0x00000000u },  // 0000107E
        { 0x00001080u, 0x00000000u }, { 0x00001081u, 0x00000000u },  // 00001080
        { 0x00001082u, 0x00000000u }, { 0x00001083u, 0x00000000u },  // 00001082
        { 0x00001084u, 0x00000000u }, { 0x00001085u, 0x00000000u },  // 00001084
        { 0x00001086u, 0x00000000u }, { 0x00001087u, 0x00000000u },  // 00001086
        { 0x00001088u, 0x00000000u }, { 0x00001089u, 0x00000000u },  // 00001088
        { 0x0000108Au, 0x00000000u }, { 0x0000108Bu, 0x00000000u },  // 0000108A
        { 0x0000108Cu, 0x00000000u }, { 0x0000108Du, 0x00000000u },  // 0000108C
        { 0x0000108Eu, 0x00000000u }, { 0x0000108Fu, 0x00000000u },  // 0000108E
        { 0x00001090u, 0x00000000u }, { 0x00001091u, 0x00000000u },  // 00001090
        { 0x00001092u, 0x00000000u }, { 0x00001093u, 0x00000000u },  // 00001092
        { 0x00001094u, 0x00000000u }, { 0x00001095u, 0x00000000u },  // 00001094
        { 0x00001096u, 0x00000000u }, { 0x00001097u, 0x00000000u },  // 00001096
        { 0x00001098u, 0x00000000u }, { 0x00001099u, 0x00000000u },  // 00001098
        { 0x0000109Au, 0x00000000u }, { 0x0000109Bu, 0x00000000u },  // 0000109A
        { 0x0000109Cu, 0x00000000u }, { 0x0000109Du, 0x00000000u },  // 0000109C
        { 0x0000109Eu, 0x00000000u }, { 0x0000109Fu, 0x00000000u }
    };

    const unsigned char Myanmar1000::my_lb[] =
    {
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_SA, LB_SA, LB_SA, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA
    };

    const std::bitset<160> Myanmar1000::my_Terminal_Punctuation(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000001100000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<160> Myanmar1000::my_Other_Alphabetic(std::string("0000000000000000000000000000000000000000000000000000000000000000000000111100000000000000000000000000000101000111111100000000000000000000000000000000000000000000"));

    const std::bitset<160> Myanmar1000::my_Diacritic(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001010000000000000000000000000000000000000000000000000000000"));

    const std::bitset<160> Myanmar1000::my_Grapheme_Link(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Myanmar1000);
