/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp E00-E7F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:55:56 +0200.
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
    class ThaiE00 : public Babylon::Block
    {
      public:
        void clean() { };

        ThaiE00() :
	    my_first_letter(0xE00),
	    my_last_letter(0xE7F)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~ThaiE00() { }

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
	    return "Thai";
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
            case 0x0E50u:
                return 0;
            case 0x0E51u:
                return 1;
            case 0x0E52u:
                return 2;
            case 0x0E53u:
                return 3;
            case 0x0E54u:
                return 4;
            case 0x0E55u:
                return 5;
            case 0x0E56u:
                return 6;
            case 0x0E57u:
                return 7;
            case 0x0E58u:
                return 8;
            case 0x0E59u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0E50u:
            case 0x0E51u:
            case 0x0E52u:
            case 0x0E53u:
            case 0x0E54u:
            case 0x0E55u:
            case 0x0E56u:
            case 0x0E57u:
            case 0x0E58u:
            case 0x0E59u:
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
            case 0x0E50u:
                return 0;
            case 0x0E51u:
                return 1;
            case 0x0E52u:
                return 2;
            case 0x0E53u:
                return 3;
            case 0x0E54u:
                return 4;
            case 0x0E55u:
                return 5;
            case 0x0E56u:
                return 6;
            case 0x0E57u:
                return 7;
            case 0x0E58u:
                return 8;
            case 0x0E59u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0E50u:
            case 0x0E51u:
            case 0x0E52u:
            case 0x0E53u:
            case 0x0E54u:
            case 0x0E55u:
            case 0x0E56u:
            case 0x0E57u:
            case 0x0E58u:
            case 0x0E59u:
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
            case 0x0E50u:
                return 0.000000;
            case 0x0E51u:
                return 1.000000;
            case 0x0E52u:
                return 2.000000;
            case 0x0E53u:
                return 3.000000;
            case 0x0E54u:
                return 4.000000;
            case 0x0E55u:
                return 5.000000;
            case 0x0E56u:
                return 6.000000;
            case 0x0E57u:
                return 7.000000;
            case 0x0E58u:
                return 8.000000;
            case 0x0E59u:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0E50u:
            case 0x0E51u:
            case 0x0E52u:
            case 0x0E53u:
            case 0x0E54u:
            case 0x0E55u:
            case 0x0E56u:
            case 0x0E57u:
            case 0x0E58u:
            case 0x0E59u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(ThaiE00::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(ThaiE00::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return ThaiE00::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(ThaiE00::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = ThaiE00::my_decompStr[uc - my_first_letter][0];
            us[1] = ThaiE00::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(ThaiE00::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_N);
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
            return my_Logical_Order_Exception.test(uc - my_first_letter);
        }

        bool is_Other_ID_Start(const UCS4 uc) const
        {
            return 0;
        }

      private:
        // functions
        ThaiE00(const ThaiE00 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<128> my_is_defined;
        static const unsigned char my_cat[128];
        static const unsigned char my_comb_cl[128];
        static const Babylon::Bidir_Props my_bidir[128];
        static const unsigned char my_decomp[128];
        static const UCS2 my_decompStr[128][2];
        static const unsigned char my_lb[128];
        static const std::bitset<128> my_Terminal_Punctuation;
        static const std::bitset<128> my_Other_Alphabetic;
        static const std::bitset<128> my_Diacritic;
        static const std::bitset<128> my_Extender;
        static const std::bitset<128> my_Grapheme_Link;
        static const std::bitset<128> my_Logical_Order_Exception;
    }; // class ThaiE00

    const std::bitset<128> ThaiE00::my_is_defined(std::string("00000000000000000000000000000000000011111111111111111111111111111000011111111111111111111111111111111111111111111111111111111110"));

    const unsigned char ThaiE00::my_cat[] =
    {
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Sc, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lm, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Po, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Po, CAT_Po, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo
    };

    const unsigned char ThaiE00::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        103, 103, 9, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        107, 107, 107, 107, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props ThaiE00::my_bidir[] =
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ET, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
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

    const unsigned char ThaiE00::my_decomp[] = {
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
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

    const UCS2 ThaiE00::my_decompStr[][2] =
    {
        { 0x00000E00u, 0x00000000u }, { 0x00000E01u, 0x00000000u },  // 00000E00
        { 0x00000E02u, 0x00000000u }, { 0x00000E03u, 0x00000000u },  // 00000E02
        { 0x00000E04u, 0x00000000u }, { 0x00000E05u, 0x00000000u },  // 00000E04
        { 0x00000E06u, 0x00000000u }, { 0x00000E07u, 0x00000000u },  // 00000E06
        { 0x00000E08u, 0x00000000u }, { 0x00000E09u, 0x00000000u },  // 00000E08
        { 0x00000E0Au, 0x00000000u }, { 0x00000E0Bu, 0x00000000u },  // 00000E0A
        { 0x00000E0Cu, 0x00000000u }, { 0x00000E0Du, 0x00000000u },  // 00000E0C
        { 0x00000E0Eu, 0x00000000u }, { 0x00000E0Fu, 0x00000000u },  // 00000E0E
        { 0x00000E10u, 0x00000000u }, { 0x00000E11u, 0x00000000u },  // 00000E10
        { 0x00000E12u, 0x00000000u }, { 0x00000E13u, 0x00000000u },  // 00000E12
        { 0x00000E14u, 0x00000000u }, { 0x00000E15u, 0x00000000u },  // 00000E14
        { 0x00000E16u, 0x00000000u }, { 0x00000E17u, 0x00000000u },  // 00000E16
        { 0x00000E18u, 0x00000000u }, { 0x00000E19u, 0x00000000u },  // 00000E18
        { 0x00000E1Au, 0x00000000u }, { 0x00000E1Bu, 0x00000000u },  // 00000E1A
        { 0x00000E1Cu, 0x00000000u }, { 0x00000E1Du, 0x00000000u },  // 00000E1C
        { 0x00000E1Eu, 0x00000000u }, { 0x00000E1Fu, 0x00000000u },  // 00000E1E
        { 0x00000E20u, 0x00000000u }, { 0x00000E21u, 0x00000000u },  // 00000E20
        { 0x00000E22u, 0x00000000u }, { 0x00000E23u, 0x00000000u },  // 00000E22
        { 0x00000E24u, 0x00000000u }, { 0x00000E25u, 0x00000000u },  // 00000E24
        { 0x00000E26u, 0x00000000u }, { 0x00000E27u, 0x00000000u },  // 00000E26
        { 0x00000E28u, 0x00000000u }, { 0x00000E29u, 0x00000000u },  // 00000E28
        { 0x00000E2Au, 0x00000000u }, { 0x00000E2Bu, 0x00000000u },  // 00000E2A
        { 0x00000E2Cu, 0x00000000u }, { 0x00000E2Du, 0x00000000u },  // 00000E2C
        { 0x00000E2Eu, 0x00000000u }, { 0x00000E2Fu, 0x00000000u },  // 00000E2E
        { 0x00000E30u, 0x00000000u }, { 0x00000E31u, 0x00000000u },  // 00000E30
        { 0x00000E32u, 0x00000000u }, { 0x00000E4Du, 0x00000E32u },  // 00000E32
        { 0x00000E34u, 0x00000000u }, { 0x00000E35u, 0x00000000u },  // 00000E34
        { 0x00000E36u, 0x00000000u }, { 0x00000E37u, 0x00000000u },  // 00000E36
        { 0x00000E38u, 0x00000000u }, { 0x00000E39u, 0x00000000u },  // 00000E38
        { 0x00000E3Au, 0x00000000u }, { 0x00000E3Bu, 0x00000000u },  // 00000E3A
        { 0x00000E3Cu, 0x00000000u }, { 0x00000E3Du, 0x00000000u },  // 00000E3C
        { 0x00000E3Eu, 0x00000000u }, { 0x00000E3Fu, 0x00000000u },  // 00000E3E
        { 0x00000E40u, 0x00000000u }, { 0x00000E41u, 0x00000000u },  // 00000E40
        { 0x00000E42u, 0x00000000u }, { 0x00000E43u, 0x00000000u },  // 00000E42
        { 0x00000E44u, 0x00000000u }, { 0x00000E45u, 0x00000000u },  // 00000E44
        { 0x00000E46u, 0x00000000u }, { 0x00000E47u, 0x00000000u },  // 00000E46
        { 0x00000E48u, 0x00000000u }, { 0x00000E49u, 0x00000000u },  // 00000E48
        { 0x00000E4Au, 0x00000000u }, { 0x00000E4Bu, 0x00000000u },  // 00000E4A
        { 0x00000E4Cu, 0x00000000u }, { 0x00000E4Du, 0x00000000u },  // 00000E4C
        { 0x00000E4Eu, 0x00000000u }, { 0x00000E4Fu, 0x00000000u },  // 00000E4E
        { 0x00000E50u, 0x00000000u }, { 0x00000E51u, 0x00000000u },  // 00000E50
        { 0x00000E52u, 0x00000000u }, { 0x00000E53u, 0x00000000u },  // 00000E52
        { 0x00000E54u, 0x00000000u }, { 0x00000E55u, 0x00000000u },  // 00000E54
        { 0x00000E56u, 0x00000000u }, { 0x00000E57u, 0x00000000u },  // 00000E56
        { 0x00000E58u, 0x00000000u }, { 0x00000E59u, 0x00000000u },  // 00000E58
        { 0x00000E5Au, 0x00000000u }, { 0x00000E5Bu, 0x00000000u },  // 00000E5A
        { 0x00000E5Cu, 0x00000000u }, { 0x00000E5Du, 0x00000000u },  // 00000E5C
        { 0x00000E5Eu, 0x00000000u }, { 0x00000E5Fu, 0x00000000u },  // 00000E5E
        { 0x00000E60u, 0x00000000u }, { 0x00000E61u, 0x00000000u },  // 00000E60
        { 0x00000E62u, 0x00000000u }, { 0x00000E63u, 0x00000000u },  // 00000E62
        { 0x00000E64u, 0x00000000u }, { 0x00000E65u, 0x00000000u },  // 00000E64
        { 0x00000E66u, 0x00000000u }, { 0x00000E67u, 0x00000000u },  // 00000E66
        { 0x00000E68u, 0x00000000u }, { 0x00000E69u, 0x00000000u },  // 00000E68
        { 0x00000E6Au, 0x00000000u }, { 0x00000E6Bu, 0x00000000u },  // 00000E6A
        { 0x00000E6Cu, 0x00000000u }, { 0x00000E6Du, 0x00000000u },  // 00000E6C
        { 0x00000E6Eu, 0x00000000u }, { 0x00000E6Fu, 0x00000000u },  // 00000E6E
        { 0x00000E70u, 0x00000000u }, { 0x00000E71u, 0x00000000u },  // 00000E70
        { 0x00000E72u, 0x00000000u }, { 0x00000E73u, 0x00000000u },  // 00000E72
        { 0x00000E74u, 0x00000000u }, { 0x00000E75u, 0x00000000u },  // 00000E74
        { 0x00000E76u, 0x00000000u }, { 0x00000E77u, 0x00000000u },  // 00000E76
        { 0x00000E78u, 0x00000000u }, { 0x00000E79u, 0x00000000u },  // 00000E78
        { 0x00000E7Au, 0x00000000u }, { 0x00000E7Bu, 0x00000000u },  // 00000E7A
        { 0x00000E7Cu, 0x00000000u }, { 0x00000E7Du, 0x00000000u },  // 00000E7C
        { 0x00000E7Eu, 0x00000000u }, { 0x00000E7Fu, 0x00000000u }
    };

    const unsigned char ThaiE00::my_lb[] =
    {
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_CM, LB_SA, LB_SA, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_SA, LB_SA, LB_SA, LB_SA, LB_PR, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NS, LB_NS, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA
    };

    const std::bitset<128> ThaiE00::my_Terminal_Punctuation(std::string("00000000000000000000000000000000000011000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> ThaiE00::my_Other_Alphabetic(std::string("00000000000000000000000000000000000000000000000000100000000000000000011111110010000000000000000000000000000000000000000000000000"));

    const std::bitset<128> ThaiE00::my_Diacritic(std::string("00000000000000000000000000000000000000000000000001011111100000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> ThaiE00::my_Extender(std::string("00000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> ThaiE00::my_Grapheme_Link(std::string("00000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> ThaiE00::my_Logical_Order_Exception(std::string("00000000000000000000000000000000000000000000000000000000000111110000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::ThaiE00);
