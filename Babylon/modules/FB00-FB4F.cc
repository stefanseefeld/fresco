/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp FB00-FB4F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:56:42 +0200.
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
    class Alphabetic_Presentation_FormsFB00 : public Babylon::Block
    {
      public:
        void clean() { };

        Alphabetic_Presentation_FormsFB00() :
	    my_first_letter(0xFB00),
	    my_last_letter(0xFB4F)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x0000FB49, 0x000005C1)] = 0xFB2C;
                my_composeMap[std::make_pair(0x0000FB49, 0x000005C2)] = 0xFB2D;
            }
        }

        ~Alphabetic_Presentation_FormsFB00() { }

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
	    return "Alphabetic Presentation Forms";
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
            return Babylon::Gen_Cat(Alphabetic_Presentation_FormsFB00::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(Alphabetic_Presentation_FormsFB00::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return Alphabetic_Presentation_FormsFB00::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Alphabetic_Presentation_FormsFB00::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Alphabetic_Presentation_FormsFB00::my_decompStr[uc - my_first_letter][0];
            us[1] = Alphabetic_Presentation_FormsFB00::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

            case 0xFB03:
                us.resize(3);
                us[2u] = 0x0069u;
                break;

            case 0xFB04:
                us.resize(3);
                us[2u] = 0x006Cu;
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
            return Babylon::Line_Break(Alphabetic_Presentation_FormsFB00::my_lb[uc - my_first_letter]);
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
        Alphabetic_Presentation_FormsFB00(const Alphabetic_Presentation_FormsFB00 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<80> my_is_defined;
        static const unsigned char my_cat[80];
        static const unsigned char my_comb_cl[80];
        static const Babylon::Bidir_Props my_bidir[80];
        static const unsigned char my_decomp[80];
        static const UCS4 my_decompStr[80][2];
        static const unsigned char my_lb[80];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<80> my_comp_exclude;
        static const std::bitset<80> my_Other_Alphabetic;
        static const std::bitset<80> my_Diacritic;
    }; // class Alphabetic_Presentation_FormsFB00

    const std::bitset<80> Alphabetic_Presentation_FormsFB00::my_is_defined(std::string("11111111110110110101111101111111111111111111111111100000111110000000000001111111"));

    const unsigned char Alphabetic_Presentation_FormsFB00::my_cat[] =
    {
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lo, CAT_Mn, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Sm, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Ll, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Ll, CAT_Lo, CAT_Ll, 
        CAT_Lo, CAT_Lo, CAT_Ll, CAT_Lo, CAT_Lo, CAT_Ll, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo
    };

    const unsigned char Alphabetic_Presentation_FormsFB00::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 26, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props Alphabetic_Presentation_FormsFB00::my_bidir[] =
    {
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_R, BIDIR_NSM, BIDIR_R, 
        BIDIR_R, BIDIR_R, BIDIR_R, BIDIR_R, 
        BIDIR_R, BIDIR_R, BIDIR_R, BIDIR_R, 
        BIDIR_R, BIDIR_ET, BIDIR_R, BIDIR_R, 
        BIDIR_R, BIDIR_R, BIDIR_R, BIDIR_R, 
        BIDIR_R, BIDIR_R, BIDIR_R, BIDIR_R, 
        BIDIR_R, BIDIR_R, BIDIR_R, BIDIR_L, 
        BIDIR_R, BIDIR_R, BIDIR_R, BIDIR_R, 
        BIDIR_R, BIDIR_L, BIDIR_R, BIDIR_L, 
        BIDIR_R, BIDIR_R, BIDIR_L, BIDIR_R, 
        BIDIR_R, BIDIR_L, BIDIR_R, BIDIR_R, 
        BIDIR_R, BIDIR_R, BIDIR_R, BIDIR_R, 
        BIDIR_R, BIDIR_R, BIDIR_R, BIDIR_R
    };

    const unsigned char Alphabetic_Presentation_FormsFB00::my_decomp[] = {
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT
    };

    const UCS4 Alphabetic_Presentation_FormsFB00::my_decompStr[][2] =
    {
        { 0x00000066u, 0x00000066u }, { 0x00000066u, 0x00000069u },  // 0000FB00
        { 0x00000066u, 0x0000006Cu }, { 0x00000066u, 0x00000066u },  // 0000FB02
        { 0x00000066u, 0x00000066u }, { 0x0000017Fu, 0x00000074u },  // 0000FB04
        { 0x00000073u, 0x00000074u }, { 0x0000FB07u, 0x00000000u },  // 0000FB06
        { 0x0000FB08u, 0x00000000u }, { 0x0000FB09u, 0x00000000u },  // 0000FB08
        { 0x0000FB0Au, 0x00000000u }, { 0x0000FB0Bu, 0x00000000u },  // 0000FB0A
        { 0x0000FB0Cu, 0x00000000u }, { 0x0000FB0Du, 0x00000000u },  // 0000FB0C
        { 0x0000FB0Eu, 0x00000000u }, { 0x0000FB0Fu, 0x00000000u },  // 0000FB0E
        { 0x0000FB10u, 0x00000000u }, { 0x0000FB11u, 0x00000000u },  // 0000FB10
        { 0x0000FB12u, 0x00000000u }, { 0x00000574u, 0x00000576u },  // 0000FB12
        { 0x00000574u, 0x00000565u }, { 0x00000574u, 0x0000056Bu },  // 0000FB14
        { 0x0000057Eu, 0x00000576u }, { 0x00000574u, 0x0000056Du },  // 0000FB16
        { 0x0000FB18u, 0x00000000u }, { 0x0000FB19u, 0x00000000u },  // 0000FB18
        { 0x0000FB1Au, 0x00000000u }, { 0x0000FB1Bu, 0x00000000u },  // 0000FB1A
        { 0x0000FB1Cu, 0x00000000u }, { 0x000005D9u, 0x000005B4u },  // 0000FB1C
        { 0x0000FB1Eu, 0x00000000u }, { 0x000005F2u, 0x000005B7u },  // 0000FB1E
        { 0x000005E2u, 0x00000000u }, { 0x000005D0u, 0x00000000u },  // 0000FB20
        { 0x000005D3u, 0x00000000u }, { 0x000005D4u, 0x00000000u },  // 0000FB22
        { 0x000005DBu, 0x00000000u }, { 0x000005DCu, 0x00000000u },  // 0000FB24
        { 0x000005DDu, 0x00000000u }, { 0x000005E8u, 0x00000000u },  // 0000FB26
        { 0x000005EAu, 0x00000000u }, { 0x0000002Bu, 0x00000000u },  // 0000FB28
        { 0x000005E9u, 0x000005C1u }, { 0x000005E9u, 0x000005C2u },  // 0000FB2A
        { 0x0000FB49u, 0x000005C1u }, { 0x0000FB49u, 0x000005C2u },  // 0000FB2C
        { 0x000005D0u, 0x000005B7u }, { 0x000005D0u, 0x000005B8u },  // 0000FB2E
        { 0x000005D0u, 0x000005BCu }, { 0x000005D1u, 0x000005BCu },  // 0000FB30
        { 0x000005D2u, 0x000005BCu }, { 0x000005D3u, 0x000005BCu },  // 0000FB32
        { 0x000005D4u, 0x000005BCu }, { 0x000005D5u, 0x000005BCu },  // 0000FB34
        { 0x000005D6u, 0x000005BCu }, { 0x0000FB37u, 0x00000000u },  // 0000FB36
        { 0x000005D8u, 0x000005BCu }, { 0x000005D9u, 0x000005BCu },  // 0000FB38
        { 0x000005DAu, 0x000005BCu }, { 0x000005DBu, 0x000005BCu },  // 0000FB3A
        { 0x000005DCu, 0x000005BCu }, { 0x0000FB3Du, 0x00000000u },  // 0000FB3C
        { 0x000005DEu, 0x000005BCu }, { 0x0000FB3Fu, 0x00000000u },  // 0000FB3E
        { 0x000005E0u, 0x000005BCu }, { 0x000005E1u, 0x000005BCu },  // 0000FB40
        { 0x0000FB42u, 0x00000000u }, { 0x000005E3u, 0x000005BCu },  // 0000FB42
        { 0x000005E4u, 0x000005BCu }, { 0x0000FB45u, 0x00000000u },  // 0000FB44
        { 0x000005E6u, 0x000005BCu }, { 0x000005E7u, 0x000005BCu },  // 0000FB46
        { 0x000005E8u, 0x000005BCu }, { 0x000005E9u, 0x000005BCu },  // 0000FB48
        { 0x000005EAu, 0x000005BCu }, { 0x000005D5u, 0x000005B9u },  // 0000FB4A
        { 0x000005D1u, 0x000005BFu }, { 0x000005DBu, 0x000005BFu },  // 0000FB4C
        { 0x000005E4u, 0x000005BFu }, { 0x000005D0u, 0x000005DCu }
    };

    const unsigned char Alphabetic_Presentation_FormsFB00::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const std::bitset<80> Alphabetic_Presentation_FormsFB00::my_comp_exclude(std::string("01111111110110110101111101111111111111000000000010100000000000000000000000000000"));

    const std::bitset<80> Alphabetic_Presentation_FormsFB00::my_Other_Alphabetic(std::string("00000000000000000000000000000000000000000000000001000000000000000000000000000000"));

    const std::bitset<80> Alphabetic_Presentation_FormsFB00::my_Diacritic(std::string("00000000000000000000000000000000000000000000000001000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Alphabetic_Presentation_FormsFB00);
