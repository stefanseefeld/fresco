/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 1F00-1FFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:55:59 +0200.
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
    class Greek_Extended1F00 : public Babylon::Block
    {
      public:
        void clean() { };

        Greek_Extended1F00() :
	    my_first_letter(0x1F00),
	    my_last_letter(0x1FFF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00001F00, 0x00000300)] = 0x1F02;
                my_composeMap[std::make_pair(0x00001F00, 0x00000301)] = 0x1F04;
                my_composeMap[std::make_pair(0x00001F00, 0x00000342)] = 0x1F06;
                my_composeMap[std::make_pair(0x00001F00, 0x00000345)] = 0x1F80;
                my_composeMap[std::make_pair(0x00001F01, 0x00000300)] = 0x1F03;
                my_composeMap[std::make_pair(0x00001F01, 0x00000301)] = 0x1F05;
                my_composeMap[std::make_pair(0x00001F01, 0x00000342)] = 0x1F07;
                my_composeMap[std::make_pair(0x00001F01, 0x00000345)] = 0x1F81;
                my_composeMap[std::make_pair(0x00001F02, 0x00000345)] = 0x1F82;
                my_composeMap[std::make_pair(0x00001F03, 0x00000345)] = 0x1F83;
                my_composeMap[std::make_pair(0x00001F04, 0x00000345)] = 0x1F84;
                my_composeMap[std::make_pair(0x00001F05, 0x00000345)] = 0x1F85;
                my_composeMap[std::make_pair(0x00001F06, 0x00000345)] = 0x1F86;
                my_composeMap[std::make_pair(0x00001F07, 0x00000345)] = 0x1F87;
                my_composeMap[std::make_pair(0x00001F08, 0x00000300)] = 0x1F0A;
                my_composeMap[std::make_pair(0x00001F08, 0x00000301)] = 0x1F0C;
                my_composeMap[std::make_pair(0x00001F08, 0x00000342)] = 0x1F0E;
                my_composeMap[std::make_pair(0x00001F08, 0x00000345)] = 0x1F88;
                my_composeMap[std::make_pair(0x00001F09, 0x00000300)] = 0x1F0B;
                my_composeMap[std::make_pair(0x00001F09, 0x00000301)] = 0x1F0D;
                my_composeMap[std::make_pair(0x00001F09, 0x00000342)] = 0x1F0F;
                my_composeMap[std::make_pair(0x00001F09, 0x00000345)] = 0x1F89;
                my_composeMap[std::make_pair(0x00001F0A, 0x00000345)] = 0x1F8A;
                my_composeMap[std::make_pair(0x00001F0B, 0x00000345)] = 0x1F8B;
                my_composeMap[std::make_pair(0x00001F0C, 0x00000345)] = 0x1F8C;
                my_composeMap[std::make_pair(0x00001F0D, 0x00000345)] = 0x1F8D;
                my_composeMap[std::make_pair(0x00001F0E, 0x00000345)] = 0x1F8E;
                my_composeMap[std::make_pair(0x00001F0F, 0x00000345)] = 0x1F8F;
                my_composeMap[std::make_pair(0x00001F10, 0x00000300)] = 0x1F12;
                my_composeMap[std::make_pair(0x00001F10, 0x00000301)] = 0x1F14;
                my_composeMap[std::make_pair(0x00001F11, 0x00000300)] = 0x1F13;
                my_composeMap[std::make_pair(0x00001F11, 0x00000301)] = 0x1F15;
                my_composeMap[std::make_pair(0x00001F18, 0x00000300)] = 0x1F1A;
                my_composeMap[std::make_pair(0x00001F18, 0x00000301)] = 0x1F1C;
                my_composeMap[std::make_pair(0x00001F19, 0x00000300)] = 0x1F1B;
                my_composeMap[std::make_pair(0x00001F19, 0x00000301)] = 0x1F1D;
                my_composeMap[std::make_pair(0x00001F20, 0x00000300)] = 0x1F22;
                my_composeMap[std::make_pair(0x00001F20, 0x00000301)] = 0x1F24;
                my_composeMap[std::make_pair(0x00001F20, 0x00000342)] = 0x1F26;
                my_composeMap[std::make_pair(0x00001F20, 0x00000345)] = 0x1F90;
                my_composeMap[std::make_pair(0x00001F21, 0x00000300)] = 0x1F23;
                my_composeMap[std::make_pair(0x00001F21, 0x00000301)] = 0x1F25;
                my_composeMap[std::make_pair(0x00001F21, 0x00000342)] = 0x1F27;
                my_composeMap[std::make_pair(0x00001F21, 0x00000345)] = 0x1F91;
                my_composeMap[std::make_pair(0x00001F22, 0x00000345)] = 0x1F92;
                my_composeMap[std::make_pair(0x00001F23, 0x00000345)] = 0x1F93;
                my_composeMap[std::make_pair(0x00001F24, 0x00000345)] = 0x1F94;
                my_composeMap[std::make_pair(0x00001F25, 0x00000345)] = 0x1F95;
                my_composeMap[std::make_pair(0x00001F26, 0x00000345)] = 0x1F96;
                my_composeMap[std::make_pair(0x00001F27, 0x00000345)] = 0x1F97;
                my_composeMap[std::make_pair(0x00001F28, 0x00000300)] = 0x1F2A;
                my_composeMap[std::make_pair(0x00001F28, 0x00000301)] = 0x1F2C;
                my_composeMap[std::make_pair(0x00001F28, 0x00000342)] = 0x1F2E;
                my_composeMap[std::make_pair(0x00001F28, 0x00000345)] = 0x1F98;
                my_composeMap[std::make_pair(0x00001F29, 0x00000300)] = 0x1F2B;
                my_composeMap[std::make_pair(0x00001F29, 0x00000301)] = 0x1F2D;
                my_composeMap[std::make_pair(0x00001F29, 0x00000342)] = 0x1F2F;
                my_composeMap[std::make_pair(0x00001F29, 0x00000345)] = 0x1F99;
                my_composeMap[std::make_pair(0x00001F2A, 0x00000345)] = 0x1F9A;
                my_composeMap[std::make_pair(0x00001F2B, 0x00000345)] = 0x1F9B;
                my_composeMap[std::make_pair(0x00001F2C, 0x00000345)] = 0x1F9C;
                my_composeMap[std::make_pair(0x00001F2D, 0x00000345)] = 0x1F9D;
                my_composeMap[std::make_pair(0x00001F2E, 0x00000345)] = 0x1F9E;
                my_composeMap[std::make_pair(0x00001F2F, 0x00000345)] = 0x1F9F;
                my_composeMap[std::make_pair(0x00001F30, 0x00000300)] = 0x1F32;
                my_composeMap[std::make_pair(0x00001F30, 0x00000301)] = 0x1F34;
                my_composeMap[std::make_pair(0x00001F30, 0x00000342)] = 0x1F36;
                my_composeMap[std::make_pair(0x00001F31, 0x00000300)] = 0x1F33;
                my_composeMap[std::make_pair(0x00001F31, 0x00000301)] = 0x1F35;
                my_composeMap[std::make_pair(0x00001F31, 0x00000342)] = 0x1F37;
                my_composeMap[std::make_pair(0x00001F38, 0x00000300)] = 0x1F3A;
                my_composeMap[std::make_pair(0x00001F38, 0x00000301)] = 0x1F3C;
                my_composeMap[std::make_pair(0x00001F38, 0x00000342)] = 0x1F3E;
                my_composeMap[std::make_pair(0x00001F39, 0x00000300)] = 0x1F3B;
                my_composeMap[std::make_pair(0x00001F39, 0x00000301)] = 0x1F3D;
                my_composeMap[std::make_pair(0x00001F39, 0x00000342)] = 0x1F3F;
                my_composeMap[std::make_pair(0x00001F40, 0x00000300)] = 0x1F42;
                my_composeMap[std::make_pair(0x00001F40, 0x00000301)] = 0x1F44;
                my_composeMap[std::make_pair(0x00001F41, 0x00000300)] = 0x1F43;
                my_composeMap[std::make_pair(0x00001F41, 0x00000301)] = 0x1F45;
                my_composeMap[std::make_pair(0x00001F48, 0x00000300)] = 0x1F4A;
                my_composeMap[std::make_pair(0x00001F48, 0x00000301)] = 0x1F4C;
                my_composeMap[std::make_pair(0x00001F49, 0x00000300)] = 0x1F4B;
                my_composeMap[std::make_pair(0x00001F49, 0x00000301)] = 0x1F4D;
                my_composeMap[std::make_pair(0x00001F50, 0x00000300)] = 0x1F52;
                my_composeMap[std::make_pair(0x00001F50, 0x00000301)] = 0x1F54;
                my_composeMap[std::make_pair(0x00001F50, 0x00000342)] = 0x1F56;
                my_composeMap[std::make_pair(0x00001F51, 0x00000300)] = 0x1F53;
                my_composeMap[std::make_pair(0x00001F51, 0x00000301)] = 0x1F55;
                my_composeMap[std::make_pair(0x00001F51, 0x00000342)] = 0x1F57;
                my_composeMap[std::make_pair(0x00001F59, 0x00000300)] = 0x1F5B;
                my_composeMap[std::make_pair(0x00001F59, 0x00000301)] = 0x1F5D;
                my_composeMap[std::make_pair(0x00001F59, 0x00000342)] = 0x1F5F;
                my_composeMap[std::make_pair(0x00001F60, 0x00000300)] = 0x1F62;
                my_composeMap[std::make_pair(0x00001F60, 0x00000301)] = 0x1F64;
                my_composeMap[std::make_pair(0x00001F60, 0x00000342)] = 0x1F66;
                my_composeMap[std::make_pair(0x00001F60, 0x00000345)] = 0x1FA0;
                my_composeMap[std::make_pair(0x00001F61, 0x00000300)] = 0x1F63;
                my_composeMap[std::make_pair(0x00001F61, 0x00000301)] = 0x1F65;
                my_composeMap[std::make_pair(0x00001F61, 0x00000342)] = 0x1F67;
                my_composeMap[std::make_pair(0x00001F61, 0x00000345)] = 0x1FA1;
                my_composeMap[std::make_pair(0x00001F62, 0x00000345)] = 0x1FA2;
                my_composeMap[std::make_pair(0x00001F63, 0x00000345)] = 0x1FA3;
                my_composeMap[std::make_pair(0x00001F64, 0x00000345)] = 0x1FA4;
                my_composeMap[std::make_pair(0x00001F65, 0x00000345)] = 0x1FA5;
                my_composeMap[std::make_pair(0x00001F66, 0x00000345)] = 0x1FA6;
                my_composeMap[std::make_pair(0x00001F67, 0x00000345)] = 0x1FA7;
                my_composeMap[std::make_pair(0x00001F68, 0x00000300)] = 0x1F6A;
                my_composeMap[std::make_pair(0x00001F68, 0x00000301)] = 0x1F6C;
                my_composeMap[std::make_pair(0x00001F68, 0x00000342)] = 0x1F6E;
                my_composeMap[std::make_pair(0x00001F68, 0x00000345)] = 0x1FA8;
                my_composeMap[std::make_pair(0x00001F69, 0x00000300)] = 0x1F6B;
                my_composeMap[std::make_pair(0x00001F69, 0x00000301)] = 0x1F6D;
                my_composeMap[std::make_pair(0x00001F69, 0x00000342)] = 0x1F6F;
                my_composeMap[std::make_pair(0x00001F69, 0x00000345)] = 0x1FA9;
                my_composeMap[std::make_pair(0x00001F6A, 0x00000345)] = 0x1FAA;
                my_composeMap[std::make_pair(0x00001F6B, 0x00000345)] = 0x1FAB;
                my_composeMap[std::make_pair(0x00001F6C, 0x00000345)] = 0x1FAC;
                my_composeMap[std::make_pair(0x00001F6D, 0x00000345)] = 0x1FAD;
                my_composeMap[std::make_pair(0x00001F6E, 0x00000345)] = 0x1FAE;
                my_composeMap[std::make_pair(0x00001F6F, 0x00000345)] = 0x1FAF;
                my_composeMap[std::make_pair(0x00001F70, 0x00000345)] = 0x1FB2;
                my_composeMap[std::make_pair(0x00001F74, 0x00000345)] = 0x1FC2;
                my_composeMap[std::make_pair(0x00001F7C, 0x00000345)] = 0x1FF2;
                my_composeMap[std::make_pair(0x00001FB6, 0x00000345)] = 0x1FB7;
                my_composeMap[std::make_pair(0x00001FBF, 0x00000300)] = 0x1FCD;
                my_composeMap[std::make_pair(0x00001FBF, 0x00000301)] = 0x1FCE;
                my_composeMap[std::make_pair(0x00001FBF, 0x00000342)] = 0x1FCF;
                my_composeMap[std::make_pair(0x00001FC6, 0x00000345)] = 0x1FC7;
                my_composeMap[std::make_pair(0x00001FF6, 0x00000345)] = 0x1FF7;
                my_composeMap[std::make_pair(0x00001FFE, 0x00000300)] = 0x1FDD;
                my_composeMap[std::make_pair(0x00001FFE, 0x00000301)] = 0x1FDE;
                my_composeMap[std::make_pair(0x00001FFE, 0x00000342)] = 0x1FDF;
            }
        }

        ~Greek_Extended1F00() { }

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
	    return "Greek Extended";
	}

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Greek_Extended1F00::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Greek_Extended1F00::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Greek_Extended1F00::my_title[uc - my_first_letter];
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
            return Babylon::Gen_Cat(Greek_Extended1F00::my_cat[uc - my_first_letter]);
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
            return Greek_Extended1F00::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Greek_Extended1F00::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Greek_Extended1F00::my_decompStr[uc - my_first_letter][0];
            us[1] = Greek_Extended1F00::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(LB_AL);
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
            return 0;
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
        Greek_Extended1F00(const Greek_Extended1F00 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<256> my_is_defined;
        static const UCS4 my_upper[256];
        static const UCS4 my_lower[256];
        static const UCS4 my_title[256];
        static const unsigned char my_cat[256];
        static const Babylon::Bidir_Props my_bidir[256];
        static const unsigned char my_decomp[256];
        static const UCS2 my_decompStr[256][2];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<256> my_Diacritic;
    }; // class Greek_Extended1F00

    const std::bitset<256> Greek_Extended1F00::my_is_defined(std::string("0111111111011100111111111111111111101111110011111111111111011111111111111101111111111111111111111111111111111111111111111111111100111111111111111111111111111111101010101111111100111111001111111111111111111111111111111111111100111111001111111111111111111111"));

    const UCS4 Greek_Extended1F00::my_upper[] =
    {
        0x1F08, 0x1F09, 0x1F0A, 0x1F0B, 0x1F0C, 0x1F0D, 0x1F0E, 0x1F0F, 
        0x1F08, 0x1F09, 0x1F0A, 0x1F0B, 0x1F0C, 0x1F0D, 0x1F0E, 0x1F0F, 
        0x1F18, 0x1F19, 0x1F1A, 0x1F1B, 0x1F1C, 0x1F1D, 0x1F16, 0x1F17, 
        0x1F18, 0x1F19, 0x1F1A, 0x1F1B, 0x1F1C, 0x1F1D, 0x1F1E, 0x1F1F, 
        0x1F28, 0x1F29, 0x1F2A, 0x1F2B, 0x1F2C, 0x1F2D, 0x1F2E, 0x1F2F, 
        0x1F28, 0x1F29, 0x1F2A, 0x1F2B, 0x1F2C, 0x1F2D, 0x1F2E, 0x1F2F, 
        0x1F38, 0x1F39, 0x1F3A, 0x1F3B, 0x1F3C, 0x1F3D, 0x1F3E, 0x1F3F, 
        0x1F38, 0x1F39, 0x1F3A, 0x1F3B, 0x1F3C, 0x1F3D, 0x1F3E, 0x1F3F, 
        0x1F48, 0x1F49, 0x1F4A, 0x1F4B, 0x1F4C, 0x1F4D, 0x1F46, 0x1F47, 
        0x1F48, 0x1F49, 0x1F4A, 0x1F4B, 0x1F4C, 0x1F4D, 0x1F4E, 0x1F4F, 
        0x1F50, 0x1F59, 0x1F52, 0x1F5B, 0x1F54, 0x1F5D, 0x1F56, 0x1F5F, 
        0x1F58, 0x1F59, 0x1F5A, 0x1F5B, 0x1F5C, 0x1F5D, 0x1F5E, 0x1F5F, 
        0x1F68, 0x1F69, 0x1F6A, 0x1F6B, 0x1F6C, 0x1F6D, 0x1F6E, 0x1F6F, 
        0x1F68, 0x1F69, 0x1F6A, 0x1F6B, 0x1F6C, 0x1F6D, 0x1F6E, 0x1F6F, 
        0x1FBA, 0x1FBB, 0x1FC8, 0x1FC9, 0x1FCA, 0x1FCB, 0x1FDA, 0x1FDB, 
        0x1FF8, 0x1FF9, 0x1FEA, 0x1FEB, 0x1FFA, 0x1FFB, 0x1F7E, 0x1F7F, 
        0x1F88, 0x1F89, 0x1F8A, 0x1F8B, 0x1F8C, 0x1F8D, 0x1F8E, 0x1F8F, 
        0x1F88, 0x1F89, 0x1F8A, 0x1F8B, 0x1F8C, 0x1F8D, 0x1F8E, 0x1F8F, 
        0x1F98, 0x1F99, 0x1F9A, 0x1F9B, 0x1F9C, 0x1F9D, 0x1F9E, 0x1F9F, 
        0x1F98, 0x1F99, 0x1F9A, 0x1F9B, 0x1F9C, 0x1F9D, 0x1F9E, 0x1F9F, 
        0x1FA8, 0x1FA9, 0x1FAA, 0x1FAB, 0x1FAC, 0x1FAD, 0x1FAE, 0x1FAF, 
        0x1FA8, 0x1FA9, 0x1FAA, 0x1FAB, 0x1FAC, 0x1FAD, 0x1FAE, 0x1FAF, 
        0x1FB8, 0x1FB9, 0x1FB2, 0x1FBC, 0x1FB4, 0x1FB5, 0x1FB6, 0x1FB7, 
        0x1FB8, 0x1FB9, 0x1FBA, 0x1FBB, 0x1FBC, 0x1FBD, 0x0399, 0x1FBF, 
        0x1FC0, 0x1FC1, 0x1FC2, 0x1FCC, 0x1FC4, 0x1FC5, 0x1FC6, 0x1FC7, 
        0x1FC8, 0x1FC9, 0x1FCA, 0x1FCB, 0x1FCC, 0x1FCD, 0x1FCE, 0x1FCF, 
        0x1FD8, 0x1FD9, 0x1FD2, 0x1FD3, 0x1FD4, 0x1FD5, 0x1FD6, 0x1FD7, 
        0x1FD8, 0x1FD9, 0x1FDA, 0x1FDB, 0x1FDC, 0x1FDD, 0x1FDE, 0x1FDF, 
        0x1FE8, 0x1FE9, 0x1FE2, 0x1FE3, 0x1FE4, 0x1FEC, 0x1FE6, 0x1FE7, 
        0x1FE8, 0x1FE9, 0x1FEA, 0x1FEB, 0x1FEC, 0x1FED, 0x1FEE, 0x1FEF, 
        0x1FF0, 0x1FF1, 0x1FF2, 0x1FFC, 0x1FF4, 0x1FF5, 0x1FF6, 0x1FF7, 
        0x1FF8, 0x1FF9, 0x1FFA, 0x1FFB, 0x1FFC, 0x1FFD, 0x1FFE, 0x1FFF
    };

    const UCS4 Greek_Extended1F00::my_lower[] =
    {
        0x1F00, 0x1F01, 0x1F02, 0x1F03, 0x1F04, 0x1F05, 0x1F06, 0x1F07, 
        0x1F00, 0x1F01, 0x1F02, 0x1F03, 0x1F04, 0x1F05, 0x1F06, 0x1F07, 
        0x1F10, 0x1F11, 0x1F12, 0x1F13, 0x1F14, 0x1F15, 0x1F16, 0x1F17, 
        0x1F10, 0x1F11, 0x1F12, 0x1F13, 0x1F14, 0x1F15, 0x1F1E, 0x1F1F, 
        0x1F20, 0x1F21, 0x1F22, 0x1F23, 0x1F24, 0x1F25, 0x1F26, 0x1F27, 
        0x1F20, 0x1F21, 0x1F22, 0x1F23, 0x1F24, 0x1F25, 0x1F26, 0x1F27, 
        0x1F30, 0x1F31, 0x1F32, 0x1F33, 0x1F34, 0x1F35, 0x1F36, 0x1F37, 
        0x1F30, 0x1F31, 0x1F32, 0x1F33, 0x1F34, 0x1F35, 0x1F36, 0x1F37, 
        0x1F40, 0x1F41, 0x1F42, 0x1F43, 0x1F44, 0x1F45, 0x1F46, 0x1F47, 
        0x1F40, 0x1F41, 0x1F42, 0x1F43, 0x1F44, 0x1F45, 0x1F4E, 0x1F4F, 
        0x1F50, 0x1F51, 0x1F52, 0x1F53, 0x1F54, 0x1F55, 0x1F56, 0x1F57, 
        0x1F58, 0x1F51, 0x1F5A, 0x1F53, 0x1F5C, 0x1F55, 0x1F5E, 0x1F57, 
        0x1F60, 0x1F61, 0x1F62, 0x1F63, 0x1F64, 0x1F65, 0x1F66, 0x1F67, 
        0x1F60, 0x1F61, 0x1F62, 0x1F63, 0x1F64, 0x1F65, 0x1F66, 0x1F67, 
        0x1F70, 0x1F71, 0x1F72, 0x1F73, 0x1F74, 0x1F75, 0x1F76, 0x1F77, 
        0x1F78, 0x1F79, 0x1F7A, 0x1F7B, 0x1F7C, 0x1F7D, 0x1F7E, 0x1F7F, 
        0x1F80, 0x1F81, 0x1F82, 0x1F83, 0x1F84, 0x1F85, 0x1F86, 0x1F87, 
        0x1F80, 0x1F81, 0x1F82, 0x1F83, 0x1F84, 0x1F85, 0x1F86, 0x1F87, 
        0x1F90, 0x1F91, 0x1F92, 0x1F93, 0x1F94, 0x1F95, 0x1F96, 0x1F97, 
        0x1F90, 0x1F91, 0x1F92, 0x1F93, 0x1F94, 0x1F95, 0x1F96, 0x1F97, 
        0x1FA0, 0x1FA1, 0x1FA2, 0x1FA3, 0x1FA4, 0x1FA5, 0x1FA6, 0x1FA7, 
        0x1FA0, 0x1FA1, 0x1FA2, 0x1FA3, 0x1FA4, 0x1FA5, 0x1FA6, 0x1FA7, 
        0x1FB0, 0x1FB1, 0x1FB2, 0x1FB3, 0x1FB4, 0x1FB5, 0x1FB6, 0x1FB7, 
        0x1FB0, 0x1FB1, 0x1F70, 0x1F71, 0x1FB3, 0x1FBD, 0x1FBE, 0x1FBF, 
        0x1FC0, 0x1FC1, 0x1FC2, 0x1FC3, 0x1FC4, 0x1FC5, 0x1FC6, 0x1FC7, 
        0x1F72, 0x1F73, 0x1F74, 0x1F75, 0x1FC3, 0x1FCD, 0x1FCE, 0x1FCF, 
        0x1FD0, 0x1FD1, 0x1FD2, 0x1FD3, 0x1FD4, 0x1FD5, 0x1FD6, 0x1FD7, 
        0x1FD0, 0x1FD1, 0x1F76, 0x1F77, 0x1FDC, 0x1FDD, 0x1FDE, 0x1FDF, 
        0x1FE0, 0x1FE1, 0x1FE2, 0x1FE3, 0x1FE4, 0x1FE5, 0x1FE6, 0x1FE7, 
        0x1FE0, 0x1FE1, 0x1F7A, 0x1F7B, 0x1FE5, 0x1FED, 0x1FEE, 0x1FEF, 
        0x1FF0, 0x1FF1, 0x1FF2, 0x1FF3, 0x1FF4, 0x1FF5, 0x1FF6, 0x1FF7, 
        0x1F78, 0x1F79, 0x1F7C, 0x1F7D, 0x1FF3, 0x1FFD, 0x1FFE, 0x1FFF
    };

    const UCS4 Greek_Extended1F00::my_title[] =
    {
        0x1F08, 0x1F09, 0x1F0A, 0x1F0B, 0x1F0C, 0x1F0D, 0x1F0E, 0x1F0F, 
        0x1F08, 0x1F09, 0x1F0A, 0x1F0B, 0x1F0C, 0x1F0D, 0x1F0E, 0x1F0F, 
        0x1F18, 0x1F19, 0x1F1A, 0x1F1B, 0x1F1C, 0x1F1D, 0x1F16, 0x1F17, 
        0x1F18, 0x1F19, 0x1F1A, 0x1F1B, 0x1F1C, 0x1F1D, 0x1F1E, 0x1F1F, 
        0x1F28, 0x1F29, 0x1F2A, 0x1F2B, 0x1F2C, 0x1F2D, 0x1F2E, 0x1F2F, 
        0x1F28, 0x1F29, 0x1F2A, 0x1F2B, 0x1F2C, 0x1F2D, 0x1F2E, 0x1F2F, 
        0x1F38, 0x1F39, 0x1F3A, 0x1F3B, 0x1F3C, 0x1F3D, 0x1F3E, 0x1F3F, 
        0x1F38, 0x1F39, 0x1F3A, 0x1F3B, 0x1F3C, 0x1F3D, 0x1F3E, 0x1F3F, 
        0x1F48, 0x1F49, 0x1F4A, 0x1F4B, 0x1F4C, 0x1F4D, 0x1F46, 0x1F47, 
        0x1F48, 0x1F49, 0x1F4A, 0x1F4B, 0x1F4C, 0x1F4D, 0x1F4E, 0x1F4F, 
        0x1F50, 0x1F59, 0x1F52, 0x1F5B, 0x1F54, 0x1F5D, 0x1F56, 0x1F5F, 
        0x1F58, 0x1F59, 0x1F5A, 0x1F5B, 0x1F5C, 0x1F5D, 0x1F5E, 0x1F5F, 
        0x1F68, 0x1F69, 0x1F6A, 0x1F6B, 0x1F6C, 0x1F6D, 0x1F6E, 0x1F6F, 
        0x1F68, 0x1F69, 0x1F6A, 0x1F6B, 0x1F6C, 0x1F6D, 0x1F6E, 0x1F6F, 
        0x1FBA, 0x1FBB, 0x1FC8, 0x1FC9, 0x1FCA, 0x1FCB, 0x1FDA, 0x1FDB, 
        0x1FF8, 0x1FF9, 0x1FEA, 0x1FEB, 0x1FFA, 0x1FFB, 0x1F7E, 0x1F7F, 
        0x1F88, 0x1F89, 0x1F8A, 0x1F8B, 0x1F8C, 0x1F8D, 0x1F8E, 0x1F8F, 
        0x1F88, 0x1F89, 0x1F8A, 0x1F8B, 0x1F8C, 0x1F8D, 0x1F8E, 0x1F8F, 
        0x1F98, 0x1F99, 0x1F9A, 0x1F9B, 0x1F9C, 0x1F9D, 0x1F9E, 0x1F9F, 
        0x1F98, 0x1F99, 0x1F9A, 0x1F9B, 0x1F9C, 0x1F9D, 0x1F9E, 0x1F9F, 
        0x1FA8, 0x1FA9, 0x1FAA, 0x1FAB, 0x1FAC, 0x1FAD, 0x1FAE, 0x1FAF, 
        0x1FA8, 0x1FA9, 0x1FAA, 0x1FAB, 0x1FAC, 0x1FAD, 0x1FAE, 0x1FAF, 
        0x1FB8, 0x1FB9, 0x1FB2, 0x1FBC, 0x1FB4, 0x1FB5, 0x1FB6, 0x1FB7, 
        0x1FB8, 0x1FB9, 0x1FBA, 0x1FBB, 0x1FBC, 0x1FBD, 0x0399, 0x1FBF, 
        0x1FC0, 0x1FC1, 0x1FC2, 0x1FCC, 0x1FC4, 0x1FC5, 0x1FC6, 0x1FC7, 
        0x1FC8, 0x1FC9, 0x1FCA, 0x1FCB, 0x1FCC, 0x1FCD, 0x1FCE, 0x1FCF, 
        0x1FD8, 0x1FD9, 0x1FD2, 0x1FD3, 0x1FD4, 0x1FD5, 0x1FD6, 0x1FD7, 
        0x1FD8, 0x1FD9, 0x1FDA, 0x1FDB, 0x1FDC, 0x1FDD, 0x1FDE, 0x1FDF, 
        0x1FE8, 0x1FE9, 0x1FE2, 0x1FE3, 0x1FE4, 0x1FEC, 0x1FE6, 0x1FE7, 
        0x1FE8, 0x1FE9, 0x1FEA, 0x1FEB, 0x1FEC, 0x1FED, 0x1FEE, 0x1FEF, 
        0x1FF0, 0x1FF1, 0x1FF2, 0x1FFC, 0x1FF4, 0x1FF5, 0x1FF6, 0x1FF7, 
        0x1FF8, 0x1FF9, 0x1FFA, 0x1FFB, 0x1FFC, 0x1FFD, 0x1FFE, 0x1FFF
    };

    const unsigned char Greek_Extended1F00::my_cat[] =
    {
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, CAT_Lt, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lt, CAT_Sk, CAT_Ll, CAT_Sk, 
        CAT_Sk, CAT_Sk, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lt, CAT_Sk, CAT_Sk, CAT_Sk, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Sk, CAT_Sk, CAT_Sk, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Sk, CAT_Sk, CAT_Sk, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lt, CAT_Sk, CAT_Sk, CAT_Ll
    };

    const Babylon::Bidir_Props Greek_Extended1F00::my_bidir[] =
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_L
    };

    const unsigned char Greek_Extended1F00::my_decomp[] = {
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
        DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_COMPAT, 
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_CANONICAL
    };

    const UCS2 Greek_Extended1F00::my_decompStr[][2] =
    {
        { 0x000003B1u, 0x00000313u }, { 0x000003B1u, 0x00000314u },  // 00001F00
        { 0x00001F00u, 0x00000300u }, { 0x00001F01u, 0x00000300u },  // 00001F02
        { 0x00001F00u, 0x00000301u }, { 0x00001F01u, 0x00000301u },  // 00001F04
        { 0x00001F00u, 0x00000342u }, { 0x00001F01u, 0x00000342u },  // 00001F06
        { 0x00000391u, 0x00000313u }, { 0x00000391u, 0x00000314u },  // 00001F08
        { 0x00001F08u, 0x00000300u }, { 0x00001F09u, 0x00000300u },  // 00001F0A
        { 0x00001F08u, 0x00000301u }, { 0x00001F09u, 0x00000301u },  // 00001F0C
        { 0x00001F08u, 0x00000342u }, { 0x00001F09u, 0x00000342u },  // 00001F0E
        { 0x000003B5u, 0x00000313u }, { 0x000003B5u, 0x00000314u },  // 00001F10
        { 0x00001F10u, 0x00000300u }, { 0x00001F11u, 0x00000300u },  // 00001F12
        { 0x00001F10u, 0x00000301u }, { 0x00001F11u, 0x00000301u },  // 00001F14
        { 0x00001F16u, 0x00000000u }, { 0x00001F17u, 0x00000000u },  // 00001F16
        { 0x00000395u, 0x00000313u }, { 0x00000395u, 0x00000314u },  // 00001F18
        { 0x00001F18u, 0x00000300u }, { 0x00001F19u, 0x00000300u },  // 00001F1A
        { 0x00001F18u, 0x00000301u }, { 0x00001F19u, 0x00000301u },  // 00001F1C
        { 0x00001F1Eu, 0x00000000u }, { 0x00001F1Fu, 0x00000000u },  // 00001F1E
        { 0x000003B7u, 0x00000313u }, { 0x000003B7u, 0x00000314u },  // 00001F20
        { 0x00001F20u, 0x00000300u }, { 0x00001F21u, 0x00000300u },  // 00001F22
        { 0x00001F20u, 0x00000301u }, { 0x00001F21u, 0x00000301u },  // 00001F24
        { 0x00001F20u, 0x00000342u }, { 0x00001F21u, 0x00000342u },  // 00001F26
        { 0x00000397u, 0x00000313u }, { 0x00000397u, 0x00000314u },  // 00001F28
        { 0x00001F28u, 0x00000300u }, { 0x00001F29u, 0x00000300u },  // 00001F2A
        { 0x00001F28u, 0x00000301u }, { 0x00001F29u, 0x00000301u },  // 00001F2C
        { 0x00001F28u, 0x00000342u }, { 0x00001F29u, 0x00000342u },  // 00001F2E
        { 0x000003B9u, 0x00000313u }, { 0x000003B9u, 0x00000314u },  // 00001F30
        { 0x00001F30u, 0x00000300u }, { 0x00001F31u, 0x00000300u },  // 00001F32
        { 0x00001F30u, 0x00000301u }, { 0x00001F31u, 0x00000301u },  // 00001F34
        { 0x00001F30u, 0x00000342u }, { 0x00001F31u, 0x00000342u },  // 00001F36
        { 0x00000399u, 0x00000313u }, { 0x00000399u, 0x00000314u },  // 00001F38
        { 0x00001F38u, 0x00000300u }, { 0x00001F39u, 0x00000300u },  // 00001F3A
        { 0x00001F38u, 0x00000301u }, { 0x00001F39u, 0x00000301u },  // 00001F3C
        { 0x00001F38u, 0x00000342u }, { 0x00001F39u, 0x00000342u },  // 00001F3E
        { 0x000003BFu, 0x00000313u }, { 0x000003BFu, 0x00000314u },  // 00001F40
        { 0x00001F40u, 0x00000300u }, { 0x00001F41u, 0x00000300u },  // 00001F42
        { 0x00001F40u, 0x00000301u }, { 0x00001F41u, 0x00000301u },  // 00001F44
        { 0x00001F46u, 0x00000000u }, { 0x00001F47u, 0x00000000u },  // 00001F46
        { 0x0000039Fu, 0x00000313u }, { 0x0000039Fu, 0x00000314u },  // 00001F48
        { 0x00001F48u, 0x00000300u }, { 0x00001F49u, 0x00000300u },  // 00001F4A
        { 0x00001F48u, 0x00000301u }, { 0x00001F49u, 0x00000301u },  // 00001F4C
        { 0x00001F4Eu, 0x00000000u }, { 0x00001F4Fu, 0x00000000u },  // 00001F4E
        { 0x000003C5u, 0x00000313u }, { 0x000003C5u, 0x00000314u },  // 00001F50
        { 0x00001F50u, 0x00000300u }, { 0x00001F51u, 0x00000300u },  // 00001F52
        { 0x00001F50u, 0x00000301u }, { 0x00001F51u, 0x00000301u },  // 00001F54
        { 0x00001F50u, 0x00000342u }, { 0x00001F51u, 0x00000342u },  // 00001F56
        { 0x00001F58u, 0x00000000u }, { 0x000003A5u, 0x00000314u },  // 00001F58
        { 0x00001F5Au, 0x00000000u }, { 0x00001F59u, 0x00000300u },  // 00001F5A
        { 0x00001F5Cu, 0x00000000u }, { 0x00001F59u, 0x00000301u },  // 00001F5C
        { 0x00001F5Eu, 0x00000000u }, { 0x00001F59u, 0x00000342u },  // 00001F5E
        { 0x000003C9u, 0x00000313u }, { 0x000003C9u, 0x00000314u },  // 00001F60
        { 0x00001F60u, 0x00000300u }, { 0x00001F61u, 0x00000300u },  // 00001F62
        { 0x00001F60u, 0x00000301u }, { 0x00001F61u, 0x00000301u },  // 00001F64
        { 0x00001F60u, 0x00000342u }, { 0x00001F61u, 0x00000342u },  // 00001F66
        { 0x000003A9u, 0x00000313u }, { 0x000003A9u, 0x00000314u },  // 00001F68
        { 0x00001F68u, 0x00000300u }, { 0x00001F69u, 0x00000300u },  // 00001F6A
        { 0x00001F68u, 0x00000301u }, { 0x00001F69u, 0x00000301u },  // 00001F6C
        { 0x00001F68u, 0x00000342u }, { 0x00001F69u, 0x00000342u },  // 00001F6E
        { 0x000003B1u, 0x00000300u }, { 0x000003ACu, 0x00000000u },  // 00001F70
        { 0x000003B5u, 0x00000300u }, { 0x000003ADu, 0x00000000u },  // 00001F72
        { 0x000003B7u, 0x00000300u }, { 0x000003AEu, 0x00000000u },  // 00001F74
        { 0x000003B9u, 0x00000300u }, { 0x000003AFu, 0x00000000u },  // 00001F76
        { 0x000003BFu, 0x00000300u }, { 0x000003CCu, 0x00000000u },  // 00001F78
        { 0x000003C5u, 0x00000300u }, { 0x000003CDu, 0x00000000u },  // 00001F7A
        { 0x000003C9u, 0x00000300u }, { 0x000003CEu, 0x00000000u },  // 00001F7C
        { 0x00001F7Eu, 0x00000000u }, { 0x00001F7Fu, 0x00000000u },  // 00001F7E
        { 0x00001F00u, 0x00000345u }, { 0x00001F01u, 0x00000345u },  // 00001F80
        { 0x00001F02u, 0x00000345u }, { 0x00001F03u, 0x00000345u },  // 00001F82
        { 0x00001F04u, 0x00000345u }, { 0x00001F05u, 0x00000345u },  // 00001F84
        { 0x00001F06u, 0x00000345u }, { 0x00001F07u, 0x00000345u },  // 00001F86
        { 0x00001F08u, 0x00000345u }, { 0x00001F09u, 0x00000345u },  // 00001F88
        { 0x00001F0Au, 0x00000345u }, { 0x00001F0Bu, 0x00000345u },  // 00001F8A
        { 0x00001F0Cu, 0x00000345u }, { 0x00001F0Du, 0x00000345u },  // 00001F8C
        { 0x00001F0Eu, 0x00000345u }, { 0x00001F0Fu, 0x00000345u },  // 00001F8E
        { 0x00001F20u, 0x00000345u }, { 0x00001F21u, 0x00000345u },  // 00001F90
        { 0x00001F22u, 0x00000345u }, { 0x00001F23u, 0x00000345u },  // 00001F92
        { 0x00001F24u, 0x00000345u }, { 0x00001F25u, 0x00000345u },  // 00001F94
        { 0x00001F26u, 0x00000345u }, { 0x00001F27u, 0x00000345u },  // 00001F96
        { 0x00001F28u, 0x00000345u }, { 0x00001F29u, 0x00000345u },  // 00001F98
        { 0x00001F2Au, 0x00000345u }, { 0x00001F2Bu, 0x00000345u },  // 00001F9A
        { 0x00001F2Cu, 0x00000345u }, { 0x00001F2Du, 0x00000345u },  // 00001F9C
        { 0x00001F2Eu, 0x00000345u }, { 0x00001F2Fu, 0x00000345u },  // 00001F9E
        { 0x00001F60u, 0x00000345u }, { 0x00001F61u, 0x00000345u },  // 00001FA0
        { 0x00001F62u, 0x00000345u }, { 0x00001F63u, 0x00000345u },  // 00001FA2
        { 0x00001F64u, 0x00000345u }, { 0x00001F65u, 0x00000345u },  // 00001FA4
        { 0x00001F66u, 0x00000345u }, { 0x00001F67u, 0x00000345u },  // 00001FA6
        { 0x00001F68u, 0x00000345u }, { 0x00001F69u, 0x00000345u },  // 00001FA8
        { 0x00001F6Au, 0x00000345u }, { 0x00001F6Bu, 0x00000345u },  // 00001FAA
        { 0x00001F6Cu, 0x00000345u }, { 0x00001F6Du, 0x00000345u },  // 00001FAC
        { 0x00001F6Eu, 0x00000345u }, { 0x00001F6Fu, 0x00000345u },  // 00001FAE
        { 0x000003B1u, 0x00000306u }, { 0x000003B1u, 0x00000304u },  // 00001FB0
        { 0x00001F70u, 0x00000345u }, { 0x000003B1u, 0x00000345u },  // 00001FB2
        { 0x000003ACu, 0x00000345u }, { 0x00001FB5u, 0x00000000u },  // 00001FB4
        { 0x000003B1u, 0x00000342u }, { 0x00001FB6u, 0x00000345u },  // 00001FB6
        { 0x00000391u, 0x00000306u }, { 0x00000391u, 0x00000304u },  // 00001FB8
        { 0x00000391u, 0x00000300u }, { 0x00000386u, 0x00000000u },  // 00001FBA
        { 0x00000391u, 0x00000345u }, { 0x00000020u, 0x00000313u },  // 00001FBC
        { 0x000003B9u, 0x00000000u }, { 0x00000020u, 0x00000313u },  // 00001FBE
        { 0x00000020u, 0x00000342u }, { 0x000000A8u, 0x00000342u },  // 00001FC0
        { 0x00001F74u, 0x00000345u }, { 0x000003B7u, 0x00000345u },  // 00001FC2
        { 0x000003AEu, 0x00000345u }, { 0x00001FC5u, 0x00000000u },  // 00001FC4
        { 0x000003B7u, 0x00000342u }, { 0x00001FC6u, 0x00000345u },  // 00001FC6
        { 0x00000395u, 0x00000300u }, { 0x00000388u, 0x00000000u },  // 00001FC8
        { 0x00000397u, 0x00000300u }, { 0x00000389u, 0x00000000u },  // 00001FCA
        { 0x00000397u, 0x00000345u }, { 0x00001FBFu, 0x00000300u },  // 00001FCC
        { 0x00001FBFu, 0x00000301u }, { 0x00001FBFu, 0x00000342u },  // 00001FCE
        { 0x000003B9u, 0x00000306u }, { 0x000003B9u, 0x00000304u },  // 00001FD0
        { 0x000003CAu, 0x00000300u }, { 0x00000390u, 0x00000000u },  // 00001FD2
        { 0x00001FD4u, 0x00000000u }, { 0x00001FD5u, 0x00000000u },  // 00001FD4
        { 0x000003B9u, 0x00000342u }, { 0x000003CAu, 0x00000342u },  // 00001FD6
        { 0x00000399u, 0x00000306u }, { 0x00000399u, 0x00000304u },  // 00001FD8
        { 0x00000399u, 0x00000300u }, { 0x0000038Au, 0x00000000u },  // 00001FDA
        { 0x00001FDCu, 0x00000000u }, { 0x00001FFEu, 0x00000300u },  // 00001FDC
        { 0x00001FFEu, 0x00000301u }, { 0x00001FFEu, 0x00000342u },  // 00001FDE
        { 0x000003C5u, 0x00000306u }, { 0x000003C5u, 0x00000304u },  // 00001FE0
        { 0x000003CBu, 0x00000300u }, { 0x000003B0u, 0x00000000u },  // 00001FE2
        { 0x000003C1u, 0x00000313u }, { 0x000003C1u, 0x00000314u },  // 00001FE4
        { 0x000003C5u, 0x00000342u }, { 0x000003CBu, 0x00000342u },  // 00001FE6
        { 0x000003A5u, 0x00000306u }, { 0x000003A5u, 0x00000304u },  // 00001FE8
        { 0x000003A5u, 0x00000300u }, { 0x0000038Eu, 0x00000000u },  // 00001FEA
        { 0x000003A1u, 0x00000314u }, { 0x000000A8u, 0x00000300u },  // 00001FEC
        { 0x00000385u, 0x00000000u }, { 0x00000060u, 0x00000000u },  // 00001FEE
        { 0x00001FF0u, 0x00000000u }, { 0x00001FF1u, 0x00000000u },  // 00001FF0
        { 0x00001F7Cu, 0x00000345u }, { 0x000003C9u, 0x00000345u },  // 00001FF2
        { 0x000003CEu, 0x00000345u }, { 0x00001FF5u, 0x00000000u },  // 00001FF4
        { 0x000003C9u, 0x00000342u }, { 0x00001FF6u, 0x00000345u },  // 00001FF6
        { 0x0000039Fu, 0x00000300u }, { 0x0000038Cu, 0x00000000u },  // 00001FF8
        { 0x000003A9u, 0x00000300u }, { 0x0000038Fu, 0x00000000u },  // 00001FFA
        { 0x000003A9u, 0x00000345u }, { 0x000000B4u, 0x00000000u },  // 00001FFC
        { 0x00000020u, 0x00000314u }, { 0x00001FFFu, 0x00000000u }
    };

    const std::bitset<256> Greek_Extended1F00::my_Diacritic(std::string("0110000000000000111000000000000011100000000000001110000000000011101000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Greek_Extended1F00);
