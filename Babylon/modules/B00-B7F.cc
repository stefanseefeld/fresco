/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp B00-B7F.cc
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
    class OriyaB00 : public Babylon::Block
    {
      public:
        void clean() { };

        OriyaB00() :
	    my_first_letter(0xB00),
	    my_last_letter(0xB7F)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000B21, 0x00000B3C)] = 0x0B5C;
                my_composeMap[std::make_pair(0x00000B22, 0x00000B3C)] = 0x0B5D;
                my_composeMap[std::make_pair(0x00000B47, 0x00000B3E)] = 0x0B4B;
                my_composeMap[std::make_pair(0x00000B47, 0x00000B56)] = 0x0B48;
                my_composeMap[std::make_pair(0x00000B47, 0x00000B57)] = 0x0B4C;
            }
        }

        ~OriyaB00() { }

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
	    return "Oriya";
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
            case 0x0B66u:
                return 0;
            case 0x0B67u:
                return 1;
            case 0x0B68u:
                return 2;
            case 0x0B69u:
                return 3;
            case 0x0B6Au:
                return 4;
            case 0x0B6Bu:
                return 5;
            case 0x0B6Cu:
                return 6;
            case 0x0B6Du:
                return 7;
            case 0x0B6Eu:
                return 8;
            case 0x0B6Fu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0B66u:
            case 0x0B67u:
            case 0x0B68u:
            case 0x0B69u:
            case 0x0B6Au:
            case 0x0B6Bu:
            case 0x0B6Cu:
            case 0x0B6Du:
            case 0x0B6Eu:
            case 0x0B6Fu:
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
            case 0x0B66u:
                return 0;
            case 0x0B67u:
                return 1;
            case 0x0B68u:
                return 2;
            case 0x0B69u:
                return 3;
            case 0x0B6Au:
                return 4;
            case 0x0B6Bu:
                return 5;
            case 0x0B6Cu:
                return 6;
            case 0x0B6Du:
                return 7;
            case 0x0B6Eu:
                return 8;
            case 0x0B6Fu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0B66u:
            case 0x0B67u:
            case 0x0B68u:
            case 0x0B69u:
            case 0x0B6Au:
            case 0x0B6Bu:
            case 0x0B6Cu:
            case 0x0B6Du:
            case 0x0B6Eu:
            case 0x0B6Fu:
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
            case 0x0B66u:
                return 0.000000;
            case 0x0B67u:
                return 1.000000;
            case 0x0B68u:
                return 2.000000;
            case 0x0B69u:
                return 3.000000;
            case 0x0B6Au:
                return 4.000000;
            case 0x0B6Bu:
                return 5.000000;
            case 0x0B6Cu:
                return 6.000000;
            case 0x0B6Du:
                return 7.000000;
            case 0x0B6Eu:
                return 8.000000;
            case 0x0B6Fu:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0B66u:
            case 0x0B67u:
            case 0x0B68u:
            case 0x0B69u:
            case 0x0B6Au:
            case 0x0B6Bu:
            case 0x0B6Cu:
            case 0x0B6Du:
            case 0x0B6Eu:
            case 0x0B6Fu:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(OriyaB00::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(OriyaB00::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return OriyaB00::my_bidir[uc - my_first_letter];
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
            us[0] = OriyaB00::my_decompStr[uc - my_first_letter][0];
            us[1] = OriyaB00::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(OriyaB00::my_lb[uc - my_first_letter]);
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
        OriyaB00(const OriyaB00 &) ; // no implementaion!

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
    }; // class OriyaB00

    const std::bitset<128> OriyaB00::my_is_defined(std::string("00000000000000111111111111000011101100001100000000111001100011111111001111101101111111011111111111111111111110011001111111101110"));

    const unsigned char OriyaB00::my_cat[] =
    {
        CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Mc, CAT_Mn, 
        CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
        CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_So, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
    };

    const unsigned char OriyaB00::my_comb_cl[] = {
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

    const Babylon::Bidir_Props OriyaB00::my_bidir[] =
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
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, 
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
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM
    };

    const UCS2 OriyaB00::my_decompStr[][2] =
    {
        { 0x00000B00u, 0x00000000u }, { 0x00000B01u, 0x00000000u },  // 00000B00
        { 0x00000B02u, 0x00000000u }, { 0x00000B03u, 0x00000000u },  // 00000B02
        { 0x00000B04u, 0x00000000u }, { 0x00000B05u, 0x00000000u },  // 00000B04
        { 0x00000B06u, 0x00000000u }, { 0x00000B07u, 0x00000000u },  // 00000B06
        { 0x00000B08u, 0x00000000u }, { 0x00000B09u, 0x00000000u },  // 00000B08
        { 0x00000B0Au, 0x00000000u }, { 0x00000B0Bu, 0x00000000u },  // 00000B0A
        { 0x00000B0Cu, 0x00000000u }, { 0x00000B0Du, 0x00000000u },  // 00000B0C
        { 0x00000B0Eu, 0x00000000u }, { 0x00000B0Fu, 0x00000000u },  // 00000B0E
        { 0x00000B10u, 0x00000000u }, { 0x00000B11u, 0x00000000u },  // 00000B10
        { 0x00000B12u, 0x00000000u }, { 0x00000B13u, 0x00000000u },  // 00000B12
        { 0x00000B14u, 0x00000000u }, { 0x00000B15u, 0x00000000u },  // 00000B14
        { 0x00000B16u, 0x00000000u }, { 0x00000B17u, 0x00000000u },  // 00000B16
        { 0x00000B18u, 0x00000000u }, { 0x00000B19u, 0x00000000u },  // 00000B18
        { 0x00000B1Au, 0x00000000u }, { 0x00000B1Bu, 0x00000000u },  // 00000B1A
        { 0x00000B1Cu, 0x00000000u }, { 0x00000B1Du, 0x00000000u },  // 00000B1C
        { 0x00000B1Eu, 0x00000000u }, { 0x00000B1Fu, 0x00000000u },  // 00000B1E
        { 0x00000B20u, 0x00000000u }, { 0x00000B21u, 0x00000000u },  // 00000B20
        { 0x00000B22u, 0x00000000u }, { 0x00000B23u, 0x00000000u },  // 00000B22
        { 0x00000B24u, 0x00000000u }, { 0x00000B25u, 0x00000000u },  // 00000B24
        { 0x00000B26u, 0x00000000u }, { 0x00000B27u, 0x00000000u },  // 00000B26
        { 0x00000B28u, 0x00000000u }, { 0x00000B29u, 0x00000000u },  // 00000B28
        { 0x00000B2Au, 0x00000000u }, { 0x00000B2Bu, 0x00000000u },  // 00000B2A
        { 0x00000B2Cu, 0x00000000u }, { 0x00000B2Du, 0x00000000u },  // 00000B2C
        { 0x00000B2Eu, 0x00000000u }, { 0x00000B2Fu, 0x00000000u },  // 00000B2E
        { 0x00000B30u, 0x00000000u }, { 0x00000B31u, 0x00000000u },  // 00000B30
        { 0x00000B32u, 0x00000000u }, { 0x00000B33u, 0x00000000u },  // 00000B32
        { 0x00000B34u, 0x00000000u }, { 0x00000B35u, 0x00000000u },  // 00000B34
        { 0x00000B36u, 0x00000000u }, { 0x00000B37u, 0x00000000u },  // 00000B36
        { 0x00000B38u, 0x00000000u }, { 0x00000B39u, 0x00000000u },  // 00000B38
        { 0x00000B3Au, 0x00000000u }, { 0x00000B3Bu, 0x00000000u },  // 00000B3A
        { 0x00000B3Cu, 0x00000000u }, { 0x00000B3Du, 0x00000000u },  // 00000B3C
        { 0x00000B3Eu, 0x00000000u }, { 0x00000B3Fu, 0x00000000u },  // 00000B3E
        { 0x00000B40u, 0x00000000u }, { 0x00000B41u, 0x00000000u },  // 00000B40
        { 0x00000B42u, 0x00000000u }, { 0x00000B43u, 0x00000000u },  // 00000B42
        { 0x00000B44u, 0x00000000u }, { 0x00000B45u, 0x00000000u },  // 00000B44
        { 0x00000B46u, 0x00000000u }, { 0x00000B47u, 0x00000000u },  // 00000B46
        { 0x00000B47u, 0x00000B56u }, { 0x00000B49u, 0x00000000u },  // 00000B48
        { 0x00000B4Au, 0x00000000u }, { 0x00000B47u, 0x00000B3Eu },  // 00000B4A
        { 0x00000B47u, 0x00000B57u }, { 0x00000B4Du, 0x00000000u },  // 00000B4C
        { 0x00000B4Eu, 0x00000000u }, { 0x00000B4Fu, 0x00000000u },  // 00000B4E
        { 0x00000B50u, 0x00000000u }, { 0x00000B51u, 0x00000000u },  // 00000B50
        { 0x00000B52u, 0x00000000u }, { 0x00000B53u, 0x00000000u },  // 00000B52
        { 0x00000B54u, 0x00000000u }, { 0x00000B55u, 0x00000000u },  // 00000B54
        { 0x00000B56u, 0x00000000u }, { 0x00000B57u, 0x00000000u },  // 00000B56
        { 0x00000B58u, 0x00000000u }, { 0x00000B59u, 0x00000000u },  // 00000B58
        { 0x00000B5Au, 0x00000000u }, { 0x00000B5Bu, 0x00000000u },  // 00000B5A
        { 0x00000B21u, 0x00000B3Cu }, { 0x00000B22u, 0x00000B3Cu },  // 00000B5C
        { 0x00000B5Eu, 0x00000000u }, { 0x00000B5Fu, 0x00000000u },  // 00000B5E
        { 0x00000B60u, 0x00000000u }, { 0x00000B61u, 0x00000000u },  // 00000B60
        { 0x00000B62u, 0x00000000u }, { 0x00000B63u, 0x00000000u },  // 00000B62
        { 0x00000B64u, 0x00000000u }, { 0x00000B65u, 0x00000000u },  // 00000B64
        { 0x00000B66u, 0x00000000u }, { 0x00000B67u, 0x00000000u },  // 00000B66
        { 0x00000B68u, 0x00000000u }, { 0x00000B69u, 0x00000000u },  // 00000B68
        { 0x00000B6Au, 0x00000000u }, { 0x00000B6Bu, 0x00000000u },  // 00000B6A
        { 0x00000B6Cu, 0x00000000u }, { 0x00000B6Du, 0x00000000u },  // 00000B6C
        { 0x00000B6Eu, 0x00000000u }, { 0x00000B6Fu, 0x00000000u },  // 00000B6E
        { 0x00000B70u, 0x00000000u }, { 0x00000B71u, 0x00000000u },  // 00000B70
        { 0x00000B72u, 0x00000000u }, { 0x00000B73u, 0x00000000u },  // 00000B72
        { 0x00000B74u, 0x00000000u }, { 0x00000B75u, 0x00000000u },  // 00000B74
        { 0x00000B76u, 0x00000000u }, { 0x00000B77u, 0x00000000u },  // 00000B76
        { 0x00000B78u, 0x00000000u }, { 0x00000B79u, 0x00000000u },  // 00000B78
        { 0x00000B7Au, 0x00000000u }, { 0x00000B7Bu, 0x00000000u },  // 00000B7A
        { 0x00000B7Cu, 0x00000000u }, { 0x00000B7Du, 0x00000000u },  // 00000B7C
        { 0x00000B7Eu, 0x00000000u }, { 0x00000B7Fu, 0x00000000u }
    };

    const unsigned char OriyaB00::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_AL, 
        LB_AL, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_CM, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
    };

    const std::bitset<128> OriyaB00::my_comp_exclude(std::string("00000000000000000000000000000000001100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> OriyaB00::my_Other_Alphabetic(std::string("00000000000000000000000000000000000000001100000000011001100011111100000000000000000000000000000000000000000000000000000000001110"));

    const std::bitset<128> OriyaB00::my_Diacritic(std::string("00000000000000000000000000000000000000000000000000100000000000000001000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> OriyaB00::my_Other_Grapheme_Extend(std::string("00000000000000000000000000000000000000001000000000000000000000000100000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> OriyaB00::my_Grapheme_Link(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::OriyaB00);
