/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp F00-FFF.cc
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

#include <map>

namespace Babylon
{
  namespace Module
  {
    class TibetanF00 : public Babylon::Block
    {
      public:
        void clean() { };

        TibetanF00() :
	    my_first_letter(0xF00),
	    my_last_letter(0xFFF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000F40, 0x00000FB5)] = 0x0F69;
                my_composeMap[std::make_pair(0x00000F42, 0x00000FB7)] = 0x0F43;
                my_composeMap[std::make_pair(0x00000F4C, 0x00000FB7)] = 0x0F4D;
                my_composeMap[std::make_pair(0x00000F51, 0x00000FB7)] = 0x0F52;
                my_composeMap[std::make_pair(0x00000F56, 0x00000FB7)] = 0x0F57;
                my_composeMap[std::make_pair(0x00000F5B, 0x00000FB7)] = 0x0F5C;
                my_composeMap[std::make_pair(0x00000F71, 0x00000F72)] = 0x0F73;
                my_composeMap[std::make_pair(0x00000F71, 0x00000F74)] = 0x0F75;
                my_composeMap[std::make_pair(0x00000F71, 0x00000F80)] = 0x0F81;
                my_composeMap[std::make_pair(0x00000F90, 0x00000FB5)] = 0x0FB9;
                my_composeMap[std::make_pair(0x00000F92, 0x00000FB7)] = 0x0F93;
                my_composeMap[std::make_pair(0x00000F9C, 0x00000FB7)] = 0x0F9D;
                my_composeMap[std::make_pair(0x00000FA1, 0x00000FB7)] = 0x0FA2;
                my_composeMap[std::make_pair(0x00000FA6, 0x00000FB7)] = 0x0FA7;
                my_composeMap[std::make_pair(0x00000FAB, 0x00000FB7)] = 0x0FAC;
                my_composeMap[std::make_pair(0x00000FB2, 0x00000F80)] = 0x0F76;
                my_composeMap[std::make_pair(0x00000FB3, 0x00000F80)] = 0x0F78;
            }
        }

        ~TibetanF00() { }

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
	    return "Tibetan";
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
            case 0x0F20u:
                return 0;
            case 0x0F21u:
                return 1;
            case 0x0F22u:
                return 2;
            case 0x0F23u:
                return 3;
            case 0x0F24u:
                return 4;
            case 0x0F25u:
                return 5;
            case 0x0F26u:
                return 6;
            case 0x0F27u:
                return 7;
            case 0x0F28u:
                return 8;
            case 0x0F29u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0F20u:
            case 0x0F21u:
            case 0x0F22u:
            case 0x0F23u:
            case 0x0F24u:
            case 0x0F25u:
            case 0x0F26u:
            case 0x0F27u:
            case 0x0F28u:
            case 0x0F29u:
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
            case 0x0F20u:
                return 0;
            case 0x0F21u:
                return 1;
            case 0x0F22u:
                return 2;
            case 0x0F23u:
                return 3;
            case 0x0F24u:
                return 4;
            case 0x0F25u:
                return 5;
            case 0x0F26u:
                return 6;
            case 0x0F27u:
                return 7;
            case 0x0F28u:
                return 8;
            case 0x0F29u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0F20u:
            case 0x0F21u:
            case 0x0F22u:
            case 0x0F23u:
            case 0x0F24u:
            case 0x0F25u:
            case 0x0F26u:
            case 0x0F27u:
            case 0x0F28u:
            case 0x0F29u:
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
            case 0x0F20u:
                return 0.000000;
            case 0x0F21u:
                return 1.000000;
            case 0x0F22u:
                return 2.000000;
            case 0x0F23u:
                return 3.000000;
            case 0x0F24u:
                return 4.000000;
            case 0x0F25u:
                return 5.000000;
            case 0x0F26u:
                return 6.000000;
            case 0x0F27u:
                return 7.000000;
            case 0x0F28u:
                return 8.000000;
            case 0x0F29u:
                return 9.000000;
            case 0x0F2Au:
                return 0.500000;
            case 0x0F2Bu:
                return 1.500000;
            case 0x0F2Cu:
                return 2.500000;
            case 0x0F2Du:
                return 3.500000;
            case 0x0F2Eu:
                return 4.500000;
            case 0x0F2Fu:
                return 5.500000;
            case 0x0F30u:
                return 6.500000;
            case 0x0F31u:
                return 7.500000;
            case 0x0F32u:
                return 8.500000;
            case 0x0F33u:
                return -0.500000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0F20u:
            case 0x0F21u:
            case 0x0F22u:
            case 0x0F23u:
            case 0x0F24u:
            case 0x0F25u:
            case 0x0F26u:
            case 0x0F27u:
            case 0x0F28u:
            case 0x0F29u:
            case 0x0F2Au:
            case 0x0F2Bu:
            case 0x0F2Cu:
            case 0x0F2Du:
            case 0x0F2Eu:
            case 0x0F2Fu:
            case 0x0F30u:
            case 0x0F31u:
            case 0x0F32u:
            case 0x0F33u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(TibetanF00::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(TibetanF00::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return TibetanF00::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(TibetanF00::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = TibetanF00::my_decompStr[uc - my_first_letter][0];
            us[1] = TibetanF00::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(TibetanF00::my_lb[uc - my_first_letter]);
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
        TibetanF00(const TibetanF00 &) ; // no implementaion!

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
        static const std::bitset<256> my_comp_exclude;
        static const std::bitset<256> my_Other_Alphabetic;
        static const std::bitset<256> my_Diacritic;
    }; // class TibetanF00

    const std::bitset<256> TibetanF00::my_is_defined(std::string("0000000000000000000000000000000000000000000000001001111111111111110111111111111111111111111111111111111011111111000011111111111111111111111111100000011111111111111111111111111111111110111111111111111111111111111111111111111111111111111111111111111111111111"));

    const unsigned char TibetanF00::my_cat[] =
    {
        CAT_Lo, CAT_So, CAT_So, CAT_So, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
        CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
        CAT_Po, CAT_Po, CAT_Po, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_Mn, CAT_Mn, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_So, CAT_Mn, CAT_So, CAT_Mn, 
        CAT_So, CAT_Mn, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Mc, CAT_Mc, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Po, CAT_Mn, CAT_Mn, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_Mn, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_Lo, CAT_Lo, CAT_So, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo
    };

    const unsigned char TibetanF00::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        220, 220, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 220, 0, 220, 
        0, 216, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 129, 130, 0, 132, 0, 0, 0, 
        0, 0, 130, 130, 130, 130, 0, 0, 
        130, 0, 230, 230, 9, 0, 230, 230, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 220, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props TibetanF00::my_bidir[] =
    {
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
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_NSM, 
        BIDIR_L, BIDIR_NSM, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, 
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
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, 
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

    const unsigned char TibetanF00::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_NOBREAK, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
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

    const UCS2 TibetanF00::my_decompStr[][2] =
    {
        { 0x00000F00u, 0x00000000u }, { 0x00000F01u, 0x00000000u },  // 00000F00
        { 0x00000F02u, 0x00000000u }, { 0x00000F03u, 0x00000000u },  // 00000F02
        { 0x00000F04u, 0x00000000u }, { 0x00000F05u, 0x00000000u },  // 00000F04
        { 0x00000F06u, 0x00000000u }, { 0x00000F07u, 0x00000000u },  // 00000F06
        { 0x00000F08u, 0x00000000u }, { 0x00000F09u, 0x00000000u },  // 00000F08
        { 0x00000F0Au, 0x00000000u }, { 0x00000F0Bu, 0x00000000u },  // 00000F0A
        { 0x00000F0Bu, 0x00000000u }, { 0x00000F0Du, 0x00000000u },  // 00000F0C
        { 0x00000F0Eu, 0x00000000u }, { 0x00000F0Fu, 0x00000000u },  // 00000F0E
        { 0x00000F10u, 0x00000000u }, { 0x00000F11u, 0x00000000u },  // 00000F10
        { 0x00000F12u, 0x00000000u }, { 0x00000F13u, 0x00000000u },  // 00000F12
        { 0x00000F14u, 0x00000000u }, { 0x00000F15u, 0x00000000u },  // 00000F14
        { 0x00000F16u, 0x00000000u }, { 0x00000F17u, 0x00000000u },  // 00000F16
        { 0x00000F18u, 0x00000000u }, { 0x00000F19u, 0x00000000u },  // 00000F18
        { 0x00000F1Au, 0x00000000u }, { 0x00000F1Bu, 0x00000000u },  // 00000F1A
        { 0x00000F1Cu, 0x00000000u }, { 0x00000F1Du, 0x00000000u },  // 00000F1C
        { 0x00000F1Eu, 0x00000000u }, { 0x00000F1Fu, 0x00000000u },  // 00000F1E
        { 0x00000F20u, 0x00000000u }, { 0x00000F21u, 0x00000000u },  // 00000F20
        { 0x00000F22u, 0x00000000u }, { 0x00000F23u, 0x00000000u },  // 00000F22
        { 0x00000F24u, 0x00000000u }, { 0x00000F25u, 0x00000000u },  // 00000F24
        { 0x00000F26u, 0x00000000u }, { 0x00000F27u, 0x00000000u },  // 00000F26
        { 0x00000F28u, 0x00000000u }, { 0x00000F29u, 0x00000000u },  // 00000F28
        { 0x00000F2Au, 0x00000000u }, { 0x00000F2Bu, 0x00000000u },  // 00000F2A
        { 0x00000F2Cu, 0x00000000u }, { 0x00000F2Du, 0x00000000u },  // 00000F2C
        { 0x00000F2Eu, 0x00000000u }, { 0x00000F2Fu, 0x00000000u },  // 00000F2E
        { 0x00000F30u, 0x00000000u }, { 0x00000F31u, 0x00000000u },  // 00000F30
        { 0x00000F32u, 0x00000000u }, { 0x00000F33u, 0x00000000u },  // 00000F32
        { 0x00000F34u, 0x00000000u }, { 0x00000F35u, 0x00000000u },  // 00000F34
        { 0x00000F36u, 0x00000000u }, { 0x00000F37u, 0x00000000u },  // 00000F36
        { 0x00000F38u, 0x00000000u }, { 0x00000F39u, 0x00000000u },  // 00000F38
        { 0x00000F3Au, 0x00000000u }, { 0x00000F3Bu, 0x00000000u },  // 00000F3A
        { 0x00000F3Cu, 0x00000000u }, { 0x00000F3Du, 0x00000000u },  // 00000F3C
        { 0x00000F3Eu, 0x00000000u }, { 0x00000F3Fu, 0x00000000u },  // 00000F3E
        { 0x00000F40u, 0x00000000u }, { 0x00000F41u, 0x00000000u },  // 00000F40
        { 0x00000F42u, 0x00000000u }, { 0x00000F42u, 0x00000FB7u },  // 00000F42
        { 0x00000F44u, 0x00000000u }, { 0x00000F45u, 0x00000000u },  // 00000F44
        { 0x00000F46u, 0x00000000u }, { 0x00000F47u, 0x00000000u },  // 00000F46
        { 0x00000F48u, 0x00000000u }, { 0x00000F49u, 0x00000000u },  // 00000F48
        { 0x00000F4Au, 0x00000000u }, { 0x00000F4Bu, 0x00000000u },  // 00000F4A
        { 0x00000F4Cu, 0x00000000u }, { 0x00000F4Cu, 0x00000FB7u },  // 00000F4C
        { 0x00000F4Eu, 0x00000000u }, { 0x00000F4Fu, 0x00000000u },  // 00000F4E
        { 0x00000F50u, 0x00000000u }, { 0x00000F51u, 0x00000000u },  // 00000F50
        { 0x00000F51u, 0x00000FB7u }, { 0x00000F53u, 0x00000000u },  // 00000F52
        { 0x00000F54u, 0x00000000u }, { 0x00000F55u, 0x00000000u },  // 00000F54
        { 0x00000F56u, 0x00000000u }, { 0x00000F56u, 0x00000FB7u },  // 00000F56
        { 0x00000F58u, 0x00000000u }, { 0x00000F59u, 0x00000000u },  // 00000F58
        { 0x00000F5Au, 0x00000000u }, { 0x00000F5Bu, 0x00000000u },  // 00000F5A
        { 0x00000F5Bu, 0x00000FB7u }, { 0x00000F5Du, 0x00000000u },  // 00000F5C
        { 0x00000F5Eu, 0x00000000u }, { 0x00000F5Fu, 0x00000000u },  // 00000F5E
        { 0x00000F60u, 0x00000000u }, { 0x00000F61u, 0x00000000u },  // 00000F60
        { 0x00000F62u, 0x00000000u }, { 0x00000F63u, 0x00000000u },  // 00000F62
        { 0x00000F64u, 0x00000000u }, { 0x00000F65u, 0x00000000u },  // 00000F64
        { 0x00000F66u, 0x00000000u }, { 0x00000F67u, 0x00000000u },  // 00000F66
        { 0x00000F68u, 0x00000000u }, { 0x00000F40u, 0x00000FB5u },  // 00000F68
        { 0x00000F6Au, 0x00000000u }, { 0x00000F6Bu, 0x00000000u },  // 00000F6A
        { 0x00000F6Cu, 0x00000000u }, { 0x00000F6Du, 0x00000000u },  // 00000F6C
        { 0x00000F6Eu, 0x00000000u }, { 0x00000F6Fu, 0x00000000u },  // 00000F6E
        { 0x00000F70u, 0x00000000u }, { 0x00000F71u, 0x00000000u },  // 00000F70
        { 0x00000F72u, 0x00000000u }, { 0x00000F71u, 0x00000F72u },  // 00000F72
        { 0x00000F74u, 0x00000000u }, { 0x00000F71u, 0x00000F74u },  // 00000F74
        { 0x00000FB2u, 0x00000F80u }, { 0x00000FB2u, 0x00000F81u },  // 00000F76
        { 0x00000FB3u, 0x00000F80u }, { 0x00000FB3u, 0x00000F81u },  // 00000F78
        { 0x00000F7Au, 0x00000000u }, { 0x00000F7Bu, 0x00000000u },  // 00000F7A
        { 0x00000F7Cu, 0x00000000u }, { 0x00000F7Du, 0x00000000u },  // 00000F7C
        { 0x00000F7Eu, 0x00000000u }, { 0x00000F7Fu, 0x00000000u },  // 00000F7E
        { 0x00000F80u, 0x00000000u }, { 0x00000F71u, 0x00000F80u },  // 00000F80
        { 0x00000F82u, 0x00000000u }, { 0x00000F83u, 0x00000000u },  // 00000F82
        { 0x00000F84u, 0x00000000u }, { 0x00000F85u, 0x00000000u },  // 00000F84
        { 0x00000F86u, 0x00000000u }, { 0x00000F87u, 0x00000000u },  // 00000F86
        { 0x00000F88u, 0x00000000u }, { 0x00000F89u, 0x00000000u },  // 00000F88
        { 0x00000F8Au, 0x00000000u }, { 0x00000F8Bu, 0x00000000u },  // 00000F8A
        { 0x00000F8Cu, 0x00000000u }, { 0x00000F8Du, 0x00000000u },  // 00000F8C
        { 0x00000F8Eu, 0x00000000u }, { 0x00000F8Fu, 0x00000000u },  // 00000F8E
        { 0x00000F90u, 0x00000000u }, { 0x00000F91u, 0x00000000u },  // 00000F90
        { 0x00000F92u, 0x00000000u }, { 0x00000F92u, 0x00000FB7u },  // 00000F92
        { 0x00000F94u, 0x00000000u }, { 0x00000F95u, 0x00000000u },  // 00000F94
        { 0x00000F96u, 0x00000000u }, { 0x00000F97u, 0x00000000u },  // 00000F96
        { 0x00000F98u, 0x00000000u }, { 0x00000F99u, 0x00000000u },  // 00000F98
        { 0x00000F9Au, 0x00000000u }, { 0x00000F9Bu, 0x00000000u },  // 00000F9A
        { 0x00000F9Cu, 0x00000000u }, { 0x00000F9Cu, 0x00000FB7u },  // 00000F9C
        { 0x00000F9Eu, 0x00000000u }, { 0x00000F9Fu, 0x00000000u },  // 00000F9E
        { 0x00000FA0u, 0x00000000u }, { 0x00000FA1u, 0x00000000u },  // 00000FA0
        { 0x00000FA1u, 0x00000FB7u }, { 0x00000FA3u, 0x00000000u },  // 00000FA2
        { 0x00000FA4u, 0x00000000u }, { 0x00000FA5u, 0x00000000u },  // 00000FA4
        { 0x00000FA6u, 0x00000000u }, { 0x00000FA6u, 0x00000FB7u },  // 00000FA6
        { 0x00000FA8u, 0x00000000u }, { 0x00000FA9u, 0x00000000u },  // 00000FA8
        { 0x00000FAAu, 0x00000000u }, { 0x00000FABu, 0x00000000u },  // 00000FAA
        { 0x00000FABu, 0x00000FB7u }, { 0x00000FADu, 0x00000000u },  // 00000FAC
        { 0x00000FAEu, 0x00000000u }, { 0x00000FAFu, 0x00000000u },  // 00000FAE
        { 0x00000FB0u, 0x00000000u }, { 0x00000FB1u, 0x00000000u },  // 00000FB0
        { 0x00000FB2u, 0x00000000u }, { 0x00000FB3u, 0x00000000u },  // 00000FB2
        { 0x00000FB4u, 0x00000000u }, { 0x00000FB5u, 0x00000000u },  // 00000FB4
        { 0x00000FB6u, 0x00000000u }, { 0x00000FB7u, 0x00000000u },  // 00000FB6
        { 0x00000FB8u, 0x00000000u }, { 0x00000F90u, 0x00000FB5u },  // 00000FB8
        { 0x00000FBAu, 0x00000000u }, { 0x00000FBBu, 0x00000000u },  // 00000FBA
        { 0x00000FBCu, 0x00000000u }, { 0x00000FBDu, 0x00000000u },  // 00000FBC
        { 0x00000FBEu, 0x00000000u }, { 0x00000FBFu, 0x00000000u },  // 00000FBE
        { 0x00000FC0u, 0x00000000u }, { 0x00000FC1u, 0x00000000u },  // 00000FC0
        { 0x00000FC2u, 0x00000000u }, { 0x00000FC3u, 0x00000000u },  // 00000FC2
        { 0x00000FC4u, 0x00000000u }, { 0x00000FC5u, 0x00000000u },  // 00000FC4
        { 0x00000FC6u, 0x00000000u }, { 0x00000FC7u, 0x00000000u },  // 00000FC6
        { 0x00000FC8u, 0x00000000u }, { 0x00000FC9u, 0x00000000u },  // 00000FC8
        { 0x00000FCAu, 0x00000000u }, { 0x00000FCBu, 0x00000000u },  // 00000FCA
        { 0x00000FCCu, 0x00000000u }, { 0x00000FCDu, 0x00000000u },  // 00000FCC
        { 0x00000FCEu, 0x00000000u }, { 0x00000FCFu, 0x00000000u },  // 00000FCE
        { 0x00000FD0u, 0x00000000u }, { 0x00000FD1u, 0x00000000u },  // 00000FD0
        { 0x00000FD2u, 0x00000000u }, { 0x00000FD3u, 0x00000000u },  // 00000FD2
        { 0x00000FD4u, 0x00000000u }, { 0x00000FD5u, 0x00000000u },  // 00000FD4
        { 0x00000FD6u, 0x00000000u }, { 0x00000FD7u, 0x00000000u },  // 00000FD6
        { 0x00000FD8u, 0x00000000u }, { 0x00000FD9u, 0x00000000u },  // 00000FD8
        { 0x00000FDAu, 0x00000000u }, { 0x00000FDBu, 0x00000000u },  // 00000FDA
        { 0x00000FDCu, 0x00000000u }, { 0x00000FDDu, 0x00000000u },  // 00000FDC
        { 0x00000FDEu, 0x00000000u }, { 0x00000FDFu, 0x00000000u },  // 00000FDE
        { 0x00000FE0u, 0x00000000u }, { 0x00000FE1u, 0x00000000u },  // 00000FE0
        { 0x00000FE2u, 0x00000000u }, { 0x00000FE3u, 0x00000000u },  // 00000FE2
        { 0x00000FE4u, 0x00000000u }, { 0x00000FE5u, 0x00000000u },  // 00000FE4
        { 0x00000FE6u, 0x00000000u }, { 0x00000FE7u, 0x00000000u },  // 00000FE6
        { 0x00000FE8u, 0x00000000u }, { 0x00000FE9u, 0x00000000u },  // 00000FE8
        { 0x00000FEAu, 0x00000000u }, { 0x00000FEBu, 0x00000000u },  // 00000FEA
        { 0x00000FECu, 0x00000000u }, { 0x00000FEDu, 0x00000000u },  // 00000FEC
        { 0x00000FEEu, 0x00000000u }, { 0x00000FEFu, 0x00000000u },  // 00000FEE
        { 0x00000FF0u, 0x00000000u }, { 0x00000FF1u, 0x00000000u },  // 00000FF0
        { 0x00000FF2u, 0x00000000u }, { 0x00000FF3u, 0x00000000u },  // 00000FF2
        { 0x00000FF4u, 0x00000000u }, { 0x00000FF5u, 0x00000000u },  // 00000FF4
        { 0x00000FF6u, 0x00000000u }, { 0x00000FF7u, 0x00000000u },  // 00000FF6
        { 0x00000FF8u, 0x00000000u }, { 0x00000FF9u, 0x00000000u },  // 00000FF8
        { 0x00000FFAu, 0x00000000u }, { 0x00000FFBu, 0x00000000u },  // 00000FFA
        { 0x00000FFCu, 0x00000000u }, { 0x00000FFDu, 0x00000000u },  // 00000FFC
        { 0x00000FFEu, 0x00000000u }, { 0x00000FFFu, 0x00000000u }
    };

    const unsigned char TibetanF00::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_BA, LB_GL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_CM, 
        LB_AL, LB_CM, LB_OP, LB_CL, LB_OP, LB_CL, LB_CM, LB_CM, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, LB_CM, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const std::bitset<256> TibetanF00::my_comp_exclude(std::string("0000000000000000000000000000000000000000000000000000000000000000000000100000000000010000100001000010000000001000000000000000000000000001010000000000001000000000000100001000010000100000000010000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<256> TibetanF00::my_Other_Alphabetic(std::string("0000000000000000000000000000000000000000000000000000000000000000000111111111111111111111111111111111111011111111000000000000001111111111111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<256> TibetanF00::my_Diacritic(std::string("0000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000001101110000000000000000000000000000000000000000000000000000000000000000001100001010100000000000000000000000000011000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::TibetanF00);
