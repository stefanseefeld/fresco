/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp E80-EFF.cc
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
    class LaoE80 : public Babylon::Block
    {
      public:
        void clean() { };

        LaoE80() :
	    my_first_letter(0xE80),
	    my_last_letter(0xEFF)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~LaoE80() { }

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
	    return "Lao";
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
            case 0x0ED0u:
                return 0;
            case 0x0ED1u:
                return 1;
            case 0x0ED2u:
                return 2;
            case 0x0ED3u:
                return 3;
            case 0x0ED4u:
                return 4;
            case 0x0ED5u:
                return 5;
            case 0x0ED6u:
                return 6;
            case 0x0ED7u:
                return 7;
            case 0x0ED8u:
                return 8;
            case 0x0ED9u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0ED0u:
            case 0x0ED1u:
            case 0x0ED2u:
            case 0x0ED3u:
            case 0x0ED4u:
            case 0x0ED5u:
            case 0x0ED6u:
            case 0x0ED7u:
            case 0x0ED8u:
            case 0x0ED9u:
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
            case 0x0ED0u:
                return 0;
            case 0x0ED1u:
                return 1;
            case 0x0ED2u:
                return 2;
            case 0x0ED3u:
                return 3;
            case 0x0ED4u:
                return 4;
            case 0x0ED5u:
                return 5;
            case 0x0ED6u:
                return 6;
            case 0x0ED7u:
                return 7;
            case 0x0ED8u:
                return 8;
            case 0x0ED9u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0ED0u:
            case 0x0ED1u:
            case 0x0ED2u:
            case 0x0ED3u:
            case 0x0ED4u:
            case 0x0ED5u:
            case 0x0ED6u:
            case 0x0ED7u:
            case 0x0ED8u:
            case 0x0ED9u:
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
            case 0x0ED0u:
                return 0.000000;
            case 0x0ED1u:
                return 1.000000;
            case 0x0ED2u:
                return 2.000000;
            case 0x0ED3u:
                return 3.000000;
            case 0x0ED4u:
                return 4.000000;
            case 0x0ED5u:
                return 5.000000;
            case 0x0ED6u:
                return 6.000000;
            case 0x0ED7u:
                return 7.000000;
            case 0x0ED8u:
                return 8.000000;
            case 0x0ED9u:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0ED0u:
            case 0x0ED1u:
            case 0x0ED2u:
            case 0x0ED3u:
            case 0x0ED4u:
            case 0x0ED5u:
            case 0x0ED6u:
            case 0x0ED7u:
            case 0x0ED8u:
            case 0x0ED9u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(LaoE80::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(LaoE80::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return LaoE80::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(LaoE80::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = LaoE80::my_decompStr[uc - my_first_letter][0];
            us[1] = LaoE80::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(LaoE80::my_lb[uc - my_first_letter]);
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
            return my_Logical_Order_Exception.test(uc - my_first_letter);
        }

        bool is_Other_ID_Start(const UCS4 uc) const
        {
            return 0;
        }

      private:
        // functions
        LaoE80(const LaoE80 &) ; // no implementaion!

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
        static const std::bitset<128> my_Other_Alphabetic;
        static const std::bitset<128> my_Diacritic;
        static const std::bitset<128> my_Extender;
        static const std::bitset<128> my_Logical_Order_Exception;
    }; // class LaoE80

    const std::bitset<128> LaoE80::my_is_defined(std::string("00000000000000000000000000000000001100111111111100111111010111110011101111111111111011001010111011111110111100000010010110010110"));

    const unsigned char LaoE80::my_cat[] =
    {
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lm, CAT_Lo, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo
    };

    const unsigned char LaoE80::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        118, 118, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        122, 122, 122, 122, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props LaoE80::my_bidir[] =
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
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
    };

    const unsigned char LaoE80::my_decomp[] = {
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
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 LaoE80::my_decompStr[][2] =
    {
        { 0x00000E80u, 0x00000000u }, { 0x00000E81u, 0x00000000u },  // 00000E80
        { 0x00000E82u, 0x00000000u }, { 0x00000E83u, 0x00000000u },  // 00000E82
        { 0x00000E84u, 0x00000000u }, { 0x00000E85u, 0x00000000u },  // 00000E84
        { 0x00000E86u, 0x00000000u }, { 0x00000E87u, 0x00000000u },  // 00000E86
        { 0x00000E88u, 0x00000000u }, { 0x00000E89u, 0x00000000u },  // 00000E88
        { 0x00000E8Au, 0x00000000u }, { 0x00000E8Bu, 0x00000000u },  // 00000E8A
        { 0x00000E8Cu, 0x00000000u }, { 0x00000E8Du, 0x00000000u },  // 00000E8C
        { 0x00000E8Eu, 0x00000000u }, { 0x00000E8Fu, 0x00000000u },  // 00000E8E
        { 0x00000E90u, 0x00000000u }, { 0x00000E91u, 0x00000000u },  // 00000E90
        { 0x00000E92u, 0x00000000u }, { 0x00000E93u, 0x00000000u },  // 00000E92
        { 0x00000E94u, 0x00000000u }, { 0x00000E95u, 0x00000000u },  // 00000E94
        { 0x00000E96u, 0x00000000u }, { 0x00000E97u, 0x00000000u },  // 00000E96
        { 0x00000E98u, 0x00000000u }, { 0x00000E99u, 0x00000000u },  // 00000E98
        { 0x00000E9Au, 0x00000000u }, { 0x00000E9Bu, 0x00000000u },  // 00000E9A
        { 0x00000E9Cu, 0x00000000u }, { 0x00000E9Du, 0x00000000u },  // 00000E9C
        { 0x00000E9Eu, 0x00000000u }, { 0x00000E9Fu, 0x00000000u },  // 00000E9E
        { 0x00000EA0u, 0x00000000u }, { 0x00000EA1u, 0x00000000u },  // 00000EA0
        { 0x00000EA2u, 0x00000000u }, { 0x00000EA3u, 0x00000000u },  // 00000EA2
        { 0x00000EA4u, 0x00000000u }, { 0x00000EA5u, 0x00000000u },  // 00000EA4
        { 0x00000EA6u, 0x00000000u }, { 0x00000EA7u, 0x00000000u },  // 00000EA6
        { 0x00000EA8u, 0x00000000u }, { 0x00000EA9u, 0x00000000u },  // 00000EA8
        { 0x00000EAAu, 0x00000000u }, { 0x00000EABu, 0x00000000u },  // 00000EAA
        { 0x00000EACu, 0x00000000u }, { 0x00000EADu, 0x00000000u },  // 00000EAC
        { 0x00000EAEu, 0x00000000u }, { 0x00000EAFu, 0x00000000u },  // 00000EAE
        { 0x00000EB0u, 0x00000000u }, { 0x00000EB1u, 0x00000000u },  // 00000EB0
        { 0x00000EB2u, 0x00000000u }, { 0x00000ECDu, 0x00000EB2u },  // 00000EB2
        { 0x00000EB4u, 0x00000000u }, { 0x00000EB5u, 0x00000000u },  // 00000EB4
        { 0x00000EB6u, 0x00000000u }, { 0x00000EB7u, 0x00000000u },  // 00000EB6
        { 0x00000EB8u, 0x00000000u }, { 0x00000EB9u, 0x00000000u },  // 00000EB8
        { 0x00000EBAu, 0x00000000u }, { 0x00000EBBu, 0x00000000u },  // 00000EBA
        { 0x00000EBCu, 0x00000000u }, { 0x00000EBDu, 0x00000000u },  // 00000EBC
        { 0x00000EBEu, 0x00000000u }, { 0x00000EBFu, 0x00000000u },  // 00000EBE
        { 0x00000EC0u, 0x00000000u }, { 0x00000EC1u, 0x00000000u },  // 00000EC0
        { 0x00000EC2u, 0x00000000u }, { 0x00000EC3u, 0x00000000u },  // 00000EC2
        { 0x00000EC4u, 0x00000000u }, { 0x00000EC5u, 0x00000000u },  // 00000EC4
        { 0x00000EC6u, 0x00000000u }, { 0x00000EC7u, 0x00000000u },  // 00000EC6
        { 0x00000EC8u, 0x00000000u }, { 0x00000EC9u, 0x00000000u },  // 00000EC8
        { 0x00000ECAu, 0x00000000u }, { 0x00000ECBu, 0x00000000u },  // 00000ECA
        { 0x00000ECCu, 0x00000000u }, { 0x00000ECDu, 0x00000000u },  // 00000ECC
        { 0x00000ECEu, 0x00000000u }, { 0x00000ECFu, 0x00000000u },  // 00000ECE
        { 0x00000ED0u, 0x00000000u }, { 0x00000ED1u, 0x00000000u },  // 00000ED0
        { 0x00000ED2u, 0x00000000u }, { 0x00000ED3u, 0x00000000u },  // 00000ED2
        { 0x00000ED4u, 0x00000000u }, { 0x00000ED5u, 0x00000000u },  // 00000ED4
        { 0x00000ED6u, 0x00000000u }, { 0x00000ED7u, 0x00000000u },  // 00000ED6
        { 0x00000ED8u, 0x00000000u }, { 0x00000ED9u, 0x00000000u },  // 00000ED8
        { 0x00000EDAu, 0x00000000u }, { 0x00000EDBu, 0x00000000u },  // 00000EDA
        { 0x00000EABu, 0x00000E99u }, { 0x00000EABu, 0x00000EA1u },  // 00000EDC
        { 0x00000EDEu, 0x00000000u }, { 0x00000EDFu, 0x00000000u },  // 00000EDE
        { 0x00000EE0u, 0x00000000u }, { 0x00000EE1u, 0x00000000u },  // 00000EE0
        { 0x00000EE2u, 0x00000000u }, { 0x00000EE3u, 0x00000000u },  // 00000EE2
        { 0x00000EE4u, 0x00000000u }, { 0x00000EE5u, 0x00000000u },  // 00000EE4
        { 0x00000EE6u, 0x00000000u }, { 0x00000EE7u, 0x00000000u },  // 00000EE6
        { 0x00000EE8u, 0x00000000u }, { 0x00000EE9u, 0x00000000u },  // 00000EE8
        { 0x00000EEAu, 0x00000000u }, { 0x00000EEBu, 0x00000000u },  // 00000EEA
        { 0x00000EECu, 0x00000000u }, { 0x00000EEDu, 0x00000000u },  // 00000EEC
        { 0x00000EEEu, 0x00000000u }, { 0x00000EEFu, 0x00000000u },  // 00000EEE
        { 0x00000EF0u, 0x00000000u }, { 0x00000EF1u, 0x00000000u },  // 00000EF0
        { 0x00000EF2u, 0x00000000u }, { 0x00000EF3u, 0x00000000u },  // 00000EF2
        { 0x00000EF4u, 0x00000000u }, { 0x00000EF5u, 0x00000000u },  // 00000EF4
        { 0x00000EF6u, 0x00000000u }, { 0x00000EF7u, 0x00000000u },  // 00000EF6
        { 0x00000EF8u, 0x00000000u }, { 0x00000EF9u, 0x00000000u },  // 00000EF8
        { 0x00000EFAu, 0x00000000u }, { 0x00000EFBu, 0x00000000u },  // 00000EFA
        { 0x00000EFCu, 0x00000000u }, { 0x00000EFDu, 0x00000000u },  // 00000EFC
        { 0x00000EFEu, 0x00000000u }, { 0x00000EFFu, 0x00000000u }
    };

    const unsigned char LaoE80::my_lb[] =
    {
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_CM, LB_SA, LB_SA, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_SA, LB_CM, LB_CM, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_SA, LB_SA, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, 
        LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA, LB_SA
    };

    const std::bitset<128> LaoE80::my_Other_Alphabetic(std::string("00000000000000000000000000000000000000000000000000100000000000000001101111110010000000000000000000000000000000000000000000000000"));

    const std::bitset<128> LaoE80::my_Diacritic(std::string("00000000000000000000000000000000000000000000000000011111000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> LaoE80::my_Extender(std::string("00000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> LaoE80::my_Logical_Order_Exception(std::string("00000000000000000000000000000000000000000000000000000000000111110000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::LaoE80);
