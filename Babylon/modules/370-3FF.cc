/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 370-3FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:55:53 +0200.
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
    class Greek_and_Coptic370 : public Babylon::Block
    {
      public:
        void clean() { };

        Greek_and_Coptic370() :
	    my_first_letter(0x370),
	    my_last_letter(0x3FF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000391, 0x00000300)] = 0x1FBA;
                my_composeMap[std::make_pair(0x00000391, 0x00000301)] = 0x0386;
                my_composeMap[std::make_pair(0x00000391, 0x00000304)] = 0x1FB9;
                my_composeMap[std::make_pair(0x00000391, 0x00000306)] = 0x1FB8;
                my_composeMap[std::make_pair(0x00000391, 0x00000313)] = 0x1F08;
                my_composeMap[std::make_pair(0x00000391, 0x00000314)] = 0x1F09;
                my_composeMap[std::make_pair(0x00000391, 0x00000345)] = 0x1FBC;
                my_composeMap[std::make_pair(0x00000395, 0x00000300)] = 0x1FC8;
                my_composeMap[std::make_pair(0x00000395, 0x00000301)] = 0x0388;
                my_composeMap[std::make_pair(0x00000395, 0x00000313)] = 0x1F18;
                my_composeMap[std::make_pair(0x00000395, 0x00000314)] = 0x1F19;
                my_composeMap[std::make_pair(0x00000397, 0x00000300)] = 0x1FCA;
                my_composeMap[std::make_pair(0x00000397, 0x00000301)] = 0x0389;
                my_composeMap[std::make_pair(0x00000397, 0x00000313)] = 0x1F28;
                my_composeMap[std::make_pair(0x00000397, 0x00000314)] = 0x1F29;
                my_composeMap[std::make_pair(0x00000397, 0x00000345)] = 0x1FCC;
                my_composeMap[std::make_pair(0x00000399, 0x00000300)] = 0x1FDA;
                my_composeMap[std::make_pair(0x00000399, 0x00000301)] = 0x038A;
                my_composeMap[std::make_pair(0x00000399, 0x00000304)] = 0x1FD9;
                my_composeMap[std::make_pair(0x00000399, 0x00000306)] = 0x1FD8;
                my_composeMap[std::make_pair(0x00000399, 0x00000308)] = 0x03AA;
                my_composeMap[std::make_pair(0x00000399, 0x00000313)] = 0x1F38;
                my_composeMap[std::make_pair(0x00000399, 0x00000314)] = 0x1F39;
                my_composeMap[std::make_pair(0x0000039F, 0x00000300)] = 0x1FF8;
                my_composeMap[std::make_pair(0x0000039F, 0x00000301)] = 0x038C;
                my_composeMap[std::make_pair(0x0000039F, 0x00000313)] = 0x1F48;
                my_composeMap[std::make_pair(0x0000039F, 0x00000314)] = 0x1F49;
                my_composeMap[std::make_pair(0x000003A1, 0x00000314)] = 0x1FEC;
                my_composeMap[std::make_pair(0x000003A5, 0x00000300)] = 0x1FEA;
                my_composeMap[std::make_pair(0x000003A5, 0x00000301)] = 0x038E;
                my_composeMap[std::make_pair(0x000003A5, 0x00000304)] = 0x1FE9;
                my_composeMap[std::make_pair(0x000003A5, 0x00000306)] = 0x1FE8;
                my_composeMap[std::make_pair(0x000003A5, 0x00000308)] = 0x03AB;
                my_composeMap[std::make_pair(0x000003A5, 0x00000314)] = 0x1F59;
                my_composeMap[std::make_pair(0x000003A9, 0x00000300)] = 0x1FFA;
                my_composeMap[std::make_pair(0x000003A9, 0x00000301)] = 0x038F;
                my_composeMap[std::make_pair(0x000003A9, 0x00000313)] = 0x1F68;
                my_composeMap[std::make_pair(0x000003A9, 0x00000314)] = 0x1F69;
                my_composeMap[std::make_pair(0x000003A9, 0x00000345)] = 0x1FFC;
                my_composeMap[std::make_pair(0x000003AC, 0x00000345)] = 0x1FB4;
                my_composeMap[std::make_pair(0x000003AE, 0x00000345)] = 0x1FC4;
                my_composeMap[std::make_pair(0x000003B1, 0x00000300)] = 0x1F70;
                my_composeMap[std::make_pair(0x000003B1, 0x00000301)] = 0x03AC;
                my_composeMap[std::make_pair(0x000003B1, 0x00000304)] = 0x1FB1;
                my_composeMap[std::make_pair(0x000003B1, 0x00000306)] = 0x1FB0;
                my_composeMap[std::make_pair(0x000003B1, 0x00000313)] = 0x1F00;
                my_composeMap[std::make_pair(0x000003B1, 0x00000314)] = 0x1F01;
                my_composeMap[std::make_pair(0x000003B1, 0x00000342)] = 0x1FB6;
                my_composeMap[std::make_pair(0x000003B1, 0x00000345)] = 0x1FB3;
                my_composeMap[std::make_pair(0x000003B5, 0x00000300)] = 0x1F72;
                my_composeMap[std::make_pair(0x000003B5, 0x00000301)] = 0x03AD;
                my_composeMap[std::make_pair(0x000003B5, 0x00000313)] = 0x1F10;
                my_composeMap[std::make_pair(0x000003B5, 0x00000314)] = 0x1F11;
                my_composeMap[std::make_pair(0x000003B7, 0x00000300)] = 0x1F74;
                my_composeMap[std::make_pair(0x000003B7, 0x00000301)] = 0x03AE;
                my_composeMap[std::make_pair(0x000003B7, 0x00000313)] = 0x1F20;
                my_composeMap[std::make_pair(0x000003B7, 0x00000314)] = 0x1F21;
                my_composeMap[std::make_pair(0x000003B7, 0x00000342)] = 0x1FC6;
                my_composeMap[std::make_pair(0x000003B7, 0x00000345)] = 0x1FC3;
                my_composeMap[std::make_pair(0x000003B9, 0x00000300)] = 0x1F76;
                my_composeMap[std::make_pair(0x000003B9, 0x00000301)] = 0x03AF;
                my_composeMap[std::make_pair(0x000003B9, 0x00000304)] = 0x1FD1;
                my_composeMap[std::make_pair(0x000003B9, 0x00000306)] = 0x1FD0;
                my_composeMap[std::make_pair(0x000003B9, 0x00000308)] = 0x03CA;
                my_composeMap[std::make_pair(0x000003B9, 0x00000313)] = 0x1F30;
                my_composeMap[std::make_pair(0x000003B9, 0x00000314)] = 0x1F31;
                my_composeMap[std::make_pair(0x000003B9, 0x00000342)] = 0x1FD6;
                my_composeMap[std::make_pair(0x000003BF, 0x00000300)] = 0x1F78;
                my_composeMap[std::make_pair(0x000003BF, 0x00000301)] = 0x03CC;
                my_composeMap[std::make_pair(0x000003BF, 0x00000313)] = 0x1F40;
                my_composeMap[std::make_pair(0x000003BF, 0x00000314)] = 0x1F41;
                my_composeMap[std::make_pair(0x000003C1, 0x00000313)] = 0x1FE4;
                my_composeMap[std::make_pair(0x000003C1, 0x00000314)] = 0x1FE5;
                my_composeMap[std::make_pair(0x000003C5, 0x00000300)] = 0x1F7A;
                my_composeMap[std::make_pair(0x000003C5, 0x00000301)] = 0x03CD;
                my_composeMap[std::make_pair(0x000003C5, 0x00000304)] = 0x1FE1;
                my_composeMap[std::make_pair(0x000003C5, 0x00000306)] = 0x1FE0;
                my_composeMap[std::make_pair(0x000003C5, 0x00000308)] = 0x03CB;
                my_composeMap[std::make_pair(0x000003C5, 0x00000313)] = 0x1F50;
                my_composeMap[std::make_pair(0x000003C5, 0x00000314)] = 0x1F51;
                my_composeMap[std::make_pair(0x000003C5, 0x00000342)] = 0x1FE6;
                my_composeMap[std::make_pair(0x000003C9, 0x00000300)] = 0x1F7C;
                my_composeMap[std::make_pair(0x000003C9, 0x00000301)] = 0x03CE;
                my_composeMap[std::make_pair(0x000003C9, 0x00000313)] = 0x1F60;
                my_composeMap[std::make_pair(0x000003C9, 0x00000314)] = 0x1F61;
                my_composeMap[std::make_pair(0x000003C9, 0x00000342)] = 0x1FF6;
                my_composeMap[std::make_pair(0x000003C9, 0x00000345)] = 0x1FF3;
                my_composeMap[std::make_pair(0x000003CA, 0x00000300)] = 0x1FD2;
                my_composeMap[std::make_pair(0x000003CA, 0x00000301)] = 0x0390;
                my_composeMap[std::make_pair(0x000003CA, 0x00000342)] = 0x1FD7;
                my_composeMap[std::make_pair(0x000003CB, 0x00000300)] = 0x1FE2;
                my_composeMap[std::make_pair(0x000003CB, 0x00000301)] = 0x03B0;
                my_composeMap[std::make_pair(0x000003CB, 0x00000342)] = 0x1FE7;
                my_composeMap[std::make_pair(0x000003CE, 0x00000345)] = 0x1FF4;
                my_composeMap[std::make_pair(0x000003D2, 0x00000301)] = 0x03D3;
                my_composeMap[std::make_pair(0x000003D2, 0x00000308)] = 0x03D4;
            }
        }

        ~Greek_and_Coptic370() { }

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
	    return "Greek and Coptic";
	}

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Greek_and_Coptic370::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Greek_and_Coptic370::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Greek_and_Coptic370::my_title[uc - my_first_letter];
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
            return Babylon::Gen_Cat(Greek_and_Coptic370::my_cat[uc - my_first_letter]);
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
            return Greek_and_Coptic370::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Greek_and_Coptic370::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Greek_and_Coptic370::my_decompStr[uc - my_first_letter][0];
            us[1] = Greek_and_Coptic370::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Greek_and_Coptic370::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Greek_and_Coptic370::my_ea[uc - my_first_letter]);
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
            return my_Other_Lowercase.test(uc - my_first_letter);
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
        Greek_and_Coptic370(const Greek_and_Coptic370 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<144> my_is_defined;
        static const UCS4 my_upper[144];
        static const UCS4 my_lower[144];
        static const UCS4 my_title[144];
        static const unsigned char my_cat[144];
        static const Babylon::Bidir_Props my_bidir[144];
        static const unsigned char my_decomp[144];
        static const UCS2 my_decompStr[144][2];
        static const unsigned char my_lb[144];
        static const unsigned char my_ea[144];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<144> my_Terminal_Punctuation;
        static const std::bitset<144> my_Diacritic;
        static const std::bitset<144> my_Other_Lowercase;
    }; // class Greek_and_Coptic370

    const std::bitset<144> Greek_and_Coptic370::my_is_defined(std::string("000011111111111111111111111111111111111111111111011111111111111111111111111111111111111111111011111111111111111111010111111100000100010000110000"));

    const UCS4 Greek_and_Coptic370::my_upper[] =
    {
        0x0370, 0x0371, 0x0372, 0x0373, 0x0374, 0x0375, 0x0376, 0x0377, 
        0x0378, 0x0379, 0x037A, 0x037B, 0x037C, 0x037D, 0x037E, 0x037F, 
        0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x0386, 0x0387, 
        0x0388, 0x0389, 0x038A, 0x038B, 0x038C, 0x038D, 0x038E, 0x038F, 
        0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 
        0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 
        0x03A0, 0x03A1, 0x03A2, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 
        0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x0386, 0x0388, 0x0389, 0x038A, 
        0x03B0, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 
        0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 
        0x03A0, 0x03A1, 0x03A3, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 
        0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x038C, 0x038E, 0x038F, 0x03CF, 
        0x0392, 0x0398, 0x03D2, 0x03D3, 0x03D4, 0x03A6, 0x03A0, 0x03D7, 
        0x03D8, 0x03D8, 0x03DA, 0x03DA, 0x03DC, 0x03DC, 0x03DE, 0x03DE, 
        0x03E0, 0x03E0, 0x03E2, 0x03E2, 0x03E4, 0x03E4, 0x03E6, 0x03E6, 
        0x03E8, 0x03E8, 0x03EA, 0x03EA, 0x03EC, 0x03EC, 0x03EE, 0x03EE, 
        0x039A, 0x03A1, 0x03F9, 0x03F3, 0x03F4, 0x0395, 0x03F6, 0x03F7, 
        0x03F7, 0x03F9, 0x03FA, 0x03FA, 0x03FC, 0x03FD, 0x03FE, 0x03FF
    };

    const UCS4 Greek_and_Coptic370::my_lower[] =
    {
        0x0370, 0x0371, 0x0372, 0x0373, 0x0374, 0x0375, 0x0376, 0x0377, 
        0x0378, 0x0379, 0x037A, 0x037B, 0x037C, 0x037D, 0x037E, 0x037F, 
        0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x03AC, 0x0387, 
        0x03AD, 0x03AE, 0x03AF, 0x038B, 0x03CC, 0x038D, 0x03CD, 0x03CE, 
        0x0390, 0x03B1, 0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6, 0x03B7, 
        0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE, 0x03BF, 
        0x03C0, 0x03C1, 0x03A2, 0x03C3, 0x03C4, 0x03C5, 0x03C6, 0x03C7, 
        0x03C8, 0x03C9, 0x03CA, 0x03CB, 0x03AC, 0x03AD, 0x03AE, 0x03AF, 
        0x03B0, 0x03B1, 0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6, 0x03B7, 
        0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE, 0x03BF, 
        0x03C0, 0x03C1, 0x03C2, 0x03C3, 0x03C4, 0x03C5, 0x03C6, 0x03C7, 
        0x03C8, 0x03C9, 0x03CA, 0x03CB, 0x03CC, 0x03CD, 0x03CE, 0x03CF, 
        0x03D0, 0x03D1, 0x03D2, 0x03D3, 0x03D4, 0x03D5, 0x03D6, 0x03D7, 
        0x03D9, 0x03D9, 0x03DB, 0x03DB, 0x03DD, 0x03DD, 0x03DF, 0x03DF, 
        0x03E1, 0x03E1, 0x03E3, 0x03E3, 0x03E5, 0x03E5, 0x03E7, 0x03E7, 
        0x03E9, 0x03E9, 0x03EB, 0x03EB, 0x03ED, 0x03ED, 0x03EF, 0x03EF, 
        0x03F0, 0x03F1, 0x03F2, 0x03F3, 0x03B8, 0x03F5, 0x03F6, 0x03F8, 
        0x03F8, 0x03F2, 0x03FB, 0x03FB, 0x03FC, 0x03FD, 0x03FE, 0x03FF
    };

    const UCS4 Greek_and_Coptic370::my_title[] =
    {
        0x0370, 0x0371, 0x0372, 0x0373, 0x0374, 0x0375, 0x0376, 0x0377, 
        0x0378, 0x0379, 0x037A, 0x037B, 0x037C, 0x037D, 0x037E, 0x037F, 
        0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x0386, 0x0387, 
        0x0388, 0x0389, 0x038A, 0x038B, 0x038C, 0x038D, 0x038E, 0x038F, 
        0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 
        0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 
        0x03A0, 0x03A1, 0x03A2, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 
        0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x0386, 0x0388, 0x0389, 0x038A, 
        0x03B0, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 
        0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 
        0x03A0, 0x03A1, 0x03A3, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 
        0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x038C, 0x038E, 0x038F, 0x03CF, 
        0x0392, 0x0398, 0x03D2, 0x03D3, 0x03D4, 0x03A6, 0x03A0, 0x03D7, 
        0x03D8, 0x03D8, 0x03DA, 0x03DA, 0x03DC, 0x03DC, 0x03DE, 0x03DE, 
        0x03E0, 0x03E0, 0x03E2, 0x03E2, 0x03E4, 0x03E4, 0x03E6, 0x03E6, 
        0x03E8, 0x03E8, 0x03EA, 0x03EA, 0x03EC, 0x03EC, 0x03EE, 0x03EE, 
        0x039A, 0x03A1, 0x03F9, 0x03F3, 0x03F4, 0x0395, 0x03F6, 0x03F7, 
        0x03F7, 0x03F9, 0x03FA, 0x03FA, 0x03FC, 0x03FD, 0x03FE, 0x03FF
    };

    const unsigned char Greek_and_Coptic370::my_cat[] =
    {
        CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, 
        CAT_Sk, CAT_Sk, CAT_Lm, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Po, CAT_Sk, 
        CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Lu, CAT_Po, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Sk, CAT_Lu, CAT_Sk, CAT_Lu, CAT_Lu, 
        CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Sk, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Sk, 
        CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Sm, CAT_Lu, 
        CAT_Ll, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk
    };

    const Babylon::Bidir_Props Greek_and_Coptic370::my_bidir[] =
    {
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
        BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_L, 
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
    };

    const unsigned char Greek_and_Coptic370::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Greek_and_Coptic370::my_decompStr[][2] =
    {
        { 0x00000370u, 0x00000000u }, { 0x00000371u, 0x00000000u },  // 00000370
        { 0x00000372u, 0x00000000u }, { 0x00000373u, 0x00000000u },  // 00000372
        { 0x000002B9u, 0x00000000u }, { 0x00000375u, 0x00000000u },  // 00000374
        { 0x00000376u, 0x00000000u }, { 0x00000377u, 0x00000000u },  // 00000376
        { 0x00000378u, 0x00000000u }, { 0x00000379u, 0x00000000u },  // 00000378
        { 0x00000020u, 0x00000345u }, { 0x0000037Bu, 0x00000000u },  // 0000037A
        { 0x0000037Cu, 0x00000000u }, { 0x0000037Du, 0x00000000u },  // 0000037C
        { 0x0000003Bu, 0x00000000u }, { 0x0000037Fu, 0x00000000u },  // 0000037E
        { 0x00000380u, 0x00000000u }, { 0x00000381u, 0x00000000u },  // 00000380
        { 0x00000382u, 0x00000000u }, { 0x00000383u, 0x00000000u },  // 00000382
        { 0x00000020u, 0x00000301u }, { 0x000000A8u, 0x00000301u },  // 00000384
        { 0x00000391u, 0x00000301u }, { 0x000000B7u, 0x00000000u },  // 00000386
        { 0x00000395u, 0x00000301u }, { 0x00000397u, 0x00000301u },  // 00000388
        { 0x00000399u, 0x00000301u }, { 0x0000038Bu, 0x00000000u },  // 0000038A
        { 0x0000039Fu, 0x00000301u }, { 0x0000038Du, 0x00000000u },  // 0000038C
        { 0x000003A5u, 0x00000301u }, { 0x000003A9u, 0x00000301u },  // 0000038E
        { 0x000003CAu, 0x00000301u }, { 0x00000391u, 0x00000000u },  // 00000390
        { 0x00000392u, 0x00000000u }, { 0x00000393u, 0x00000000u },  // 00000392
        { 0x00000394u, 0x00000000u }, { 0x00000395u, 0x00000000u },  // 00000394
        { 0x00000396u, 0x00000000u }, { 0x00000397u, 0x00000000u },  // 00000396
        { 0x00000398u, 0x00000000u }, { 0x00000399u, 0x00000000u },  // 00000398
        { 0x0000039Au, 0x00000000u }, { 0x0000039Bu, 0x00000000u },  // 0000039A
        { 0x0000039Cu, 0x00000000u }, { 0x0000039Du, 0x00000000u },  // 0000039C
        { 0x0000039Eu, 0x00000000u }, { 0x0000039Fu, 0x00000000u },  // 0000039E
        { 0x000003A0u, 0x00000000u }, { 0x000003A1u, 0x00000000u },  // 000003A0
        { 0x000003A2u, 0x00000000u }, { 0x000003A3u, 0x00000000u },  // 000003A2
        { 0x000003A4u, 0x00000000u }, { 0x000003A5u, 0x00000000u },  // 000003A4
        { 0x000003A6u, 0x00000000u }, { 0x000003A7u, 0x00000000u },  // 000003A6
        { 0x000003A8u, 0x00000000u }, { 0x000003A9u, 0x00000000u },  // 000003A8
        { 0x00000399u, 0x00000308u }, { 0x000003A5u, 0x00000308u },  // 000003AA
        { 0x000003B1u, 0x00000301u }, { 0x000003B5u, 0x00000301u },  // 000003AC
        { 0x000003B7u, 0x00000301u }, { 0x000003B9u, 0x00000301u },  // 000003AE
        { 0x000003CBu, 0x00000301u }, { 0x000003B1u, 0x00000000u },  // 000003B0
        { 0x000003B2u, 0x00000000u }, { 0x000003B3u, 0x00000000u },  // 000003B2
        { 0x000003B4u, 0x00000000u }, { 0x000003B5u, 0x00000000u },  // 000003B4
        { 0x000003B6u, 0x00000000u }, { 0x000003B7u, 0x00000000u },  // 000003B6
        { 0x000003B8u, 0x00000000u }, { 0x000003B9u, 0x00000000u },  // 000003B8
        { 0x000003BAu, 0x00000000u }, { 0x000003BBu, 0x00000000u },  // 000003BA
        { 0x000003BCu, 0x00000000u }, { 0x000003BDu, 0x00000000u },  // 000003BC
        { 0x000003BEu, 0x00000000u }, { 0x000003BFu, 0x00000000u },  // 000003BE
        { 0x000003C0u, 0x00000000u }, { 0x000003C1u, 0x00000000u },  // 000003C0
        { 0x000003C2u, 0x00000000u }, { 0x000003C3u, 0x00000000u },  // 000003C2
        { 0x000003C4u, 0x00000000u }, { 0x000003C5u, 0x00000000u },  // 000003C4
        { 0x000003C6u, 0x00000000u }, { 0x000003C7u, 0x00000000u },  // 000003C6
        { 0x000003C8u, 0x00000000u }, { 0x000003C9u, 0x00000000u },  // 000003C8
        { 0x000003B9u, 0x00000308u }, { 0x000003C5u, 0x00000308u },  // 000003CA
        { 0x000003BFu, 0x00000301u }, { 0x000003C5u, 0x00000301u },  // 000003CC
        { 0x000003C9u, 0x00000301u }, { 0x000003CFu, 0x00000000u },  // 000003CE
        { 0x000003B2u, 0x00000000u }, { 0x000003B8u, 0x00000000u },  // 000003D0
        { 0x000003A5u, 0x00000000u }, { 0x000003D2u, 0x00000301u },  // 000003D2
        { 0x000003D2u, 0x00000308u }, { 0x000003C6u, 0x00000000u },  // 000003D4
        { 0x000003C0u, 0x00000000u }, { 0x000003D7u, 0x00000000u },  // 000003D6
        { 0x000003D8u, 0x00000000u }, { 0x000003D9u, 0x00000000u },  // 000003D8
        { 0x000003DAu, 0x00000000u }, { 0x000003DBu, 0x00000000u },  // 000003DA
        { 0x000003DCu, 0x00000000u }, { 0x000003DDu, 0x00000000u },  // 000003DC
        { 0x000003DEu, 0x00000000u }, { 0x000003DFu, 0x00000000u },  // 000003DE
        { 0x000003E0u, 0x00000000u }, { 0x000003E1u, 0x00000000u },  // 000003E0
        { 0x000003E2u, 0x00000000u }, { 0x000003E3u, 0x00000000u },  // 000003E2
        { 0x000003E4u, 0x00000000u }, { 0x000003E5u, 0x00000000u },  // 000003E4
        { 0x000003E6u, 0x00000000u }, { 0x000003E7u, 0x00000000u },  // 000003E6
        { 0x000003E8u, 0x00000000u }, { 0x000003E9u, 0x00000000u },  // 000003E8
        { 0x000003EAu, 0x00000000u }, { 0x000003EBu, 0x00000000u },  // 000003EA
        { 0x000003ECu, 0x00000000u }, { 0x000003EDu, 0x00000000u },  // 000003EC
        { 0x000003EEu, 0x00000000u }, { 0x000003EFu, 0x00000000u },  // 000003EE
        { 0x000003BAu, 0x00000000u }, { 0x000003C1u, 0x00000000u },  // 000003F0
        { 0x000003C2u, 0x00000000u }, { 0x000003F3u, 0x00000000u },  // 000003F2
        { 0x00000398u, 0x00000000u }, { 0x000003B5u, 0x00000000u },  // 000003F4
        { 0x000003F6u, 0x00000000u }, { 0x000003F7u, 0x00000000u },  // 000003F6
        { 0x000003F8u, 0x00000000u }, { 0x000003A3u, 0x00000000u },  // 000003F8
        { 0x000003FAu, 0x00000000u }, { 0x000003FBu, 0x00000000u },  // 000003FA
        { 0x000003FCu, 0x00000000u }, { 0x000003FDu, 0x00000000u },  // 000003FC
        { 0x000003FEu, 0x00000000u }, { 0x000003FFu, 0x00000000u }
    };

    const unsigned char Greek_and_Coptic370::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const unsigned char Greek_and_Coptic370::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
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

    const std::bitset<144> Greek_and_Coptic370::my_Terminal_Punctuation(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000100000000000000"));

    const std::bitset<144> Greek_and_Coptic370::my_Diacritic(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001100000000010000110000"));

    const std::bitset<144> Greek_and_Coptic370::my_Other_Lowercase(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Greek_and_Coptic370);
