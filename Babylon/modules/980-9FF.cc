/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 980-9FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:40 +0200.
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
    class Bengali980 : public Babylon::Block
    {
      public:
        void clean() { };

        Bengali980() :
	    my_first_letter(0x980),
	    my_last_letter(0x9FF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x000009A1, 0x000009BC)] = 0x09DC;
                my_composeMap[std::make_pair(0x000009A2, 0x000009BC)] = 0x09DD;
                my_composeMap[std::make_pair(0x000009AF, 0x000009BC)] = 0x09DF;
                my_composeMap[std::make_pair(0x000009C7, 0x000009BE)] = 0x09CB;
                my_composeMap[std::make_pair(0x000009C7, 0x000009D7)] = 0x09CC;
            }
        }

        ~Bengali980() { }

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
	    return "Bengali";
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
            case 0x09E6u:
                return 0;
            case 0x09E7u:
                return 1;
            case 0x09E8u:
                return 2;
            case 0x09E9u:
                return 3;
            case 0x09EAu:
                return 4;
            case 0x09EBu:
                return 5;
            case 0x09ECu:
                return 6;
            case 0x09EDu:
                return 7;
            case 0x09EEu:
                return 8;
            case 0x09EFu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x09E6u:
            case 0x09E7u:
            case 0x09E8u:
            case 0x09E9u:
            case 0x09EAu:
            case 0x09EBu:
            case 0x09ECu:
            case 0x09EDu:
            case 0x09EEu:
            case 0x09EFu:
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
            case 0x09E6u:
                return 0;
            case 0x09E7u:
                return 1;
            case 0x09E8u:
                return 2;
            case 0x09E9u:
                return 3;
            case 0x09EAu:
                return 4;
            case 0x09EBu:
                return 5;
            case 0x09ECu:
                return 6;
            case 0x09EDu:
                return 7;
            case 0x09EEu:
                return 8;
            case 0x09EFu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x09E6u:
            case 0x09E7u:
            case 0x09E8u:
            case 0x09E9u:
            case 0x09EAu:
            case 0x09EBu:
            case 0x09ECu:
            case 0x09EDu:
            case 0x09EEu:
            case 0x09EFu:
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
            case 0x09E6u:
                return 0.000000;
            case 0x09E7u:
                return 1.000000;
            case 0x09E8u:
                return 2.000000;
            case 0x09E9u:
                return 3.000000;
            case 0x09EAu:
                return 4.000000;
            case 0x09EBu:
                return 5.000000;
            case 0x09ECu:
                return 6.000000;
            case 0x09EDu:
                return 7.000000;
            case 0x09EEu:
                return 8.000000;
            case 0x09EFu:
                return 9.000000;
            case 0x09F4u:
                return 1.000000;
            case 0x09F5u:
                return 2.000000;
            case 0x09F6u:
                return 3.000000;
            case 0x09F7u:
                return 4.000000;
            case 0x09F9u:
                return 16.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x09E6u:
            case 0x09E7u:
            case 0x09E8u:
            case 0x09E9u:
            case 0x09EAu:
            case 0x09EBu:
            case 0x09ECu:
            case 0x09EDu:
            case 0x09EEu:
            case 0x09EFu:
            case 0x09F4u:
            case 0x09F5u:
            case 0x09F6u:
            case 0x09F7u:
            case 0x09F9u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Bengali980::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(Bengali980::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return Bengali980::my_bidir[uc - my_first_letter];
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
            us[0] = Bengali980::my_decompStr[uc - my_first_letter][0];
            us[1] = Bengali980::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Bengali980::my_lb[uc - my_first_letter]);
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
            if (my_comp_exclude.test(uc - my_first_letter)) return 1;
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
            return my_Other_Grapheme_Extend.test(uc - my_first_letter);
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
        Bengali980(const Bengali980 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<128> my_is_defined;
        static const unsigned char my_cat[128];
        static const unsigned char my_comb_cl[128];
        static const Babylon::Bidir_Props my_bidir[128];
        static const UCS2 my_decompStr[128][2];
        static const unsigned char my_lb[128];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<128> my_comp_exclude;
        static const std::bitset<128> my_Other_Alphabetic;
        static const std::bitset<128> my_Diacritic;
        static const std::bitset<128> my_Other_Grapheme_Extend;
        static const std::bitset<128> my_Grapheme_Link;
    }; // class Bengali980

    const std::bitset<128> Bengali980::my_is_defined(std::string("00000111111111111111111111001111101100001000000000111001100111111111001111000101111111011111111111111111111110011001111111101110"));

    const unsigned char Bengali980::my_cat[] =
    {
        CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
        CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Lo, CAT_Lo, CAT_Sc, CAT_Sc, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_So, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
    };

    const unsigned char Bengali980::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 7, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 9, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props Bengali980::my_bidir[] =
    {
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ET, BIDIR_ET, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM
    };

    const UCS2 Bengali980::my_decompStr[][2] =
    {
        { 0x00000980u, 0x00000000u }, { 0x00000981u, 0x00000000u },  // 00000980
        { 0x00000982u, 0x00000000u }, { 0x00000983u, 0x00000000u },  // 00000982
        { 0x00000984u, 0x00000000u }, { 0x00000985u, 0x00000000u },  // 00000984
        { 0x00000986u, 0x00000000u }, { 0x00000987u, 0x00000000u },  // 00000986
        { 0x00000988u, 0x00000000u }, { 0x00000989u, 0x00000000u },  // 00000988
        { 0x0000098Au, 0x00000000u }, { 0x0000098Bu, 0x00000000u },  // 0000098A
        { 0x0000098Cu, 0x00000000u }, { 0x0000098Du, 0x00000000u },  // 0000098C
        { 0x0000098Eu, 0x00000000u }, { 0x0000098Fu, 0x00000000u },  // 0000098E
        { 0x00000990u, 0x00000000u }, { 0x00000991u, 0x00000000u },  // 00000990
        { 0x00000992u, 0x00000000u }, { 0x00000993u, 0x00000000u },  // 00000992
        { 0x00000994u, 0x00000000u }, { 0x00000995u, 0x00000000u },  // 00000994
        { 0x00000996u, 0x00000000u }, { 0x00000997u, 0x00000000u },  // 00000996
        { 0x00000998u, 0x00000000u }, { 0x00000999u, 0x00000000u },  // 00000998
        { 0x0000099Au, 0x00000000u }, { 0x0000099Bu, 0x00000000u },  // 0000099A
        { 0x0000099Cu, 0x00000000u }, { 0x0000099Du, 0x00000000u },  // 0000099C
        { 0x0000099Eu, 0x00000000u }, { 0x0000099Fu, 0x00000000u },  // 0000099E
        { 0x000009A0u, 0x00000000u }, { 0x000009A1u, 0x00000000u },  // 000009A0
        { 0x000009A2u, 0x00000000u }, { 0x000009A3u, 0x00000000u },  // 000009A2
        { 0x000009A4u, 0x00000000u }, { 0x000009A5u, 0x00000000u },  // 000009A4
        { 0x000009A6u, 0x00000000u }, { 0x000009A7u, 0x00000000u },  // 000009A6
        { 0x000009A8u, 0x00000000u }, { 0x000009A9u, 0x00000000u },  // 000009A8
        { 0x000009AAu, 0x00000000u }, { 0x000009ABu, 0x00000000u },  // 000009AA
        { 0x000009ACu, 0x00000000u }, { 0x000009ADu, 0x00000000u },  // 000009AC
        { 0x000009AEu, 0x00000000u }, { 0x000009AFu, 0x00000000u },  // 000009AE
        { 0x000009B0u, 0x00000000u }, { 0x000009B1u, 0x00000000u },  // 000009B0
        { 0x000009B2u, 0x00000000u }, { 0x000009B3u, 0x00000000u },  // 000009B2
        { 0x000009B4u, 0x00000000u }, { 0x000009B5u, 0x00000000u },  // 000009B4
        { 0x000009B6u, 0x00000000u }, { 0x000009B7u, 0x00000000u },  // 000009B6
        { 0x000009B8u, 0x00000000u }, { 0x000009B9u, 0x00000000u },  // 000009B8
        { 0x000009BAu, 0x00000000u }, { 0x000009BBu, 0x00000000u },  // 000009BA
        { 0x000009BCu, 0x00000000u }, { 0x000009BDu, 0x00000000u },  // 000009BC
        { 0x000009BEu, 0x00000000u }, { 0x000009BFu, 0x00000000u },  // 000009BE
        { 0x000009C0u, 0x00000000u }, { 0x000009C1u, 0x00000000u },  // 000009C0
        { 0x000009C2u, 0x00000000u }, { 0x000009C3u, 0x00000000u },  // 000009C2
        { 0x000009C4u, 0x00000000u }, { 0x000009C5u, 0x00000000u },  // 000009C4
        { 0x000009C6u, 0x00000000u }, { 0x000009C7u, 0x00000000u },  // 000009C6
        { 0x000009C8u, 0x00000000u }, { 0x000009C9u, 0x00000000u },  // 000009C8
        { 0x000009CAu, 0x00000000u }, { 0x000009C7u, 0x000009BEu },  // 000009CA
        { 0x000009C7u, 0x000009D7u }, { 0x000009CDu, 0x00000000u },  // 000009CC
        { 0x000009CEu, 0x00000000u }, { 0x000009CFu, 0x00000000u },  // 000009CE
        { 0x000009D0u, 0x00000000u }, { 0x000009D1u, 0x00000000u },  // 000009D0
        { 0x000009D2u, 0x00000000u }, { 0x000009D3u, 0x00000000u },  // 000009D2
        { 0x000009D4u, 0x00000000u }, { 0x000009D5u, 0x00000000u },  // 000009D4
        { 0x000009D6u, 0x00000000u }, { 0x000009D7u, 0x00000000u },  // 000009D6
        { 0x000009D8u, 0x00000000u }, { 0x000009D9u, 0x00000000u },  // 000009D8
        { 0x000009DAu, 0x00000000u }, { 0x000009DBu, 0x00000000u },  // 000009DA
        { 0x000009A1u, 0x000009BCu }, { 0x000009A2u, 0x000009BCu },  // 000009DC
        { 0x000009DEu, 0x00000000u }, { 0x000009AFu, 0x000009BCu },  // 000009DE
        { 0x000009E0u, 0x00000000u }, { 0x000009E1u, 0x00000000u },  // 000009E0
        { 0x000009E2u, 0x00000000u }, { 0x000009E3u, 0x00000000u },  // 000009E2
        { 0x000009E4u, 0x00000000u }, { 0x000009E5u, 0x00000000u },  // 000009E4
        { 0x000009E6u, 0x00000000u }, { 0x000009E7u, 0x00000000u },  // 000009E6
        { 0x000009E8u, 0x00000000u }, { 0x000009E9u, 0x00000000u },  // 000009E8
        { 0x000009EAu, 0x00000000u }, { 0x000009EBu, 0x00000000u },  // 000009EA
        { 0x000009ECu, 0x00000000u }, { 0x000009EDu, 0x00000000u },  // 000009EC
        { 0x000009EEu, 0x00000000u }, { 0x000009EFu, 0x00000000u },  // 000009EE
        { 0x000009F0u, 0x00000000u }, { 0x000009F1u, 0x00000000u },  // 000009F0
        { 0x000009F2u, 0x00000000u }, { 0x000009F3u, 0x00000000u },  // 000009F2
        { 0x000009F4u, 0x00000000u }, { 0x000009F5u, 0x00000000u },  // 000009F4
        { 0x000009F6u, 0x00000000u }, { 0x000009F7u, 0x00000000u },  // 000009F6
        { 0x000009F8u, 0x00000000u }, { 0x000009F9u, 0x00000000u },  // 000009F8
        { 0x000009FAu, 0x00000000u }, { 0x000009FBu, 0x00000000u },  // 000009FA
        { 0x000009FCu, 0x00000000u }, { 0x000009FDu, 0x00000000u },  // 000009FC
        { 0x000009FEu, 0x00000000u }, { 0x000009FFu, 0x00000000u }
    };

    const unsigned char Bengali980::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_AL, 
        LB_AL, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_CM, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_AL, LB_AL, LB_PR, LB_PR, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
    };

    const std::bitset<128> Bengali980::my_comp_exclude(std::string("00000000000000000000000000000000101100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> Bengali980::my_Other_Alphabetic(std::string("00000000000000000000000000001100000000001000000000011001100111111100000000000000000000000000000000000000000000000000000000001110"));

    const std::bitset<128> Bengali980::my_Diacritic(std::string("00000000000000000000000000000000000000000000000000100000000000000001000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> Bengali980::my_Other_Grapheme_Extend(std::string("00000000000000000000000000000000000000001000000000000000000000000100000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> Bengali980::my_Grapheme_Link(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Bengali980);
