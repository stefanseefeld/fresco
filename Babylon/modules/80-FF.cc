/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 80-FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:55:52 +0200.
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
    class Latin1_Supplement80 : public Babylon::Block
    {
      public:
        void clean() { };

        Latin1_Supplement80() :
	    my_first_letter(0x80),
	    my_last_letter(0xFF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x000000A8, 0x00000300)] = 0x1FED;
                my_composeMap[std::make_pair(0x000000A8, 0x00000301)] = 0x0385;
                my_composeMap[std::make_pair(0x000000A8, 0x00000342)] = 0x1FC1;
                my_composeMap[std::make_pair(0x000000C2, 0x00000300)] = 0x1EA6;
                my_composeMap[std::make_pair(0x000000C2, 0x00000301)] = 0x1EA4;
                my_composeMap[std::make_pair(0x000000C2, 0x00000303)] = 0x1EAA;
                my_composeMap[std::make_pair(0x000000C2, 0x00000309)] = 0x1EA8;
                my_composeMap[std::make_pair(0x000000C4, 0x00000304)] = 0x01DE;
                my_composeMap[std::make_pair(0x000000C5, 0x00000301)] = 0x01FA;
                my_composeMap[std::make_pair(0x000000C6, 0x00000301)] = 0x01FC;
                my_composeMap[std::make_pair(0x000000C6, 0x00000304)] = 0x01E2;
                my_composeMap[std::make_pair(0x000000C7, 0x00000301)] = 0x1E08;
                my_composeMap[std::make_pair(0x000000CA, 0x00000300)] = 0x1EC0;
                my_composeMap[std::make_pair(0x000000CA, 0x00000301)] = 0x1EBE;
                my_composeMap[std::make_pair(0x000000CA, 0x00000303)] = 0x1EC4;
                my_composeMap[std::make_pair(0x000000CA, 0x00000309)] = 0x1EC2;
                my_composeMap[std::make_pair(0x000000CF, 0x00000301)] = 0x1E2E;
                my_composeMap[std::make_pair(0x000000D4, 0x00000300)] = 0x1ED2;
                my_composeMap[std::make_pair(0x000000D4, 0x00000301)] = 0x1ED0;
                my_composeMap[std::make_pair(0x000000D4, 0x00000303)] = 0x1ED6;
                my_composeMap[std::make_pair(0x000000D4, 0x00000309)] = 0x1ED4;
                my_composeMap[std::make_pair(0x000000D5, 0x00000301)] = 0x1E4C;
                my_composeMap[std::make_pair(0x000000D5, 0x00000304)] = 0x022C;
                my_composeMap[std::make_pair(0x000000D5, 0x00000308)] = 0x1E4E;
                my_composeMap[std::make_pair(0x000000D6, 0x00000304)] = 0x022A;
                my_composeMap[std::make_pair(0x000000D8, 0x00000301)] = 0x01FE;
                my_composeMap[std::make_pair(0x000000DC, 0x00000300)] = 0x01DB;
                my_composeMap[std::make_pair(0x000000DC, 0x00000301)] = 0x01D7;
                my_composeMap[std::make_pair(0x000000DC, 0x00000304)] = 0x01D5;
                my_composeMap[std::make_pair(0x000000DC, 0x0000030C)] = 0x01D9;
                my_composeMap[std::make_pair(0x000000E2, 0x00000300)] = 0x1EA7;
                my_composeMap[std::make_pair(0x000000E2, 0x00000301)] = 0x1EA5;
                my_composeMap[std::make_pair(0x000000E2, 0x00000303)] = 0x1EAB;
                my_composeMap[std::make_pair(0x000000E2, 0x00000309)] = 0x1EA9;
                my_composeMap[std::make_pair(0x000000E4, 0x00000304)] = 0x01DF;
                my_composeMap[std::make_pair(0x000000E5, 0x00000301)] = 0x01FB;
                my_composeMap[std::make_pair(0x000000E6, 0x00000301)] = 0x01FD;
                my_composeMap[std::make_pair(0x000000E6, 0x00000304)] = 0x01E3;
                my_composeMap[std::make_pair(0x000000E7, 0x00000301)] = 0x1E09;
                my_composeMap[std::make_pair(0x000000EA, 0x00000300)] = 0x1EC1;
                my_composeMap[std::make_pair(0x000000EA, 0x00000301)] = 0x1EBF;
                my_composeMap[std::make_pair(0x000000EA, 0x00000303)] = 0x1EC5;
                my_composeMap[std::make_pair(0x000000EA, 0x00000309)] = 0x1EC3;
                my_composeMap[std::make_pair(0x000000EF, 0x00000301)] = 0x1E2F;
                my_composeMap[std::make_pair(0x000000F4, 0x00000300)] = 0x1ED3;
                my_composeMap[std::make_pair(0x000000F4, 0x00000301)] = 0x1ED1;
                my_composeMap[std::make_pair(0x000000F4, 0x00000303)] = 0x1ED7;
                my_composeMap[std::make_pair(0x000000F4, 0x00000309)] = 0x1ED5;
                my_composeMap[std::make_pair(0x000000F5, 0x00000301)] = 0x1E4D;
                my_composeMap[std::make_pair(0x000000F5, 0x00000304)] = 0x022D;
                my_composeMap[std::make_pair(0x000000F5, 0x00000308)] = 0x1E4F;
                my_composeMap[std::make_pair(0x000000F6, 0x00000304)] = 0x022B;
                my_composeMap[std::make_pair(0x000000F8, 0x00000301)] = 0x01FF;
                my_composeMap[std::make_pair(0x000000FC, 0x00000300)] = 0x01DC;
                my_composeMap[std::make_pair(0x000000FC, 0x00000301)] = 0x01D8;
                my_composeMap[std::make_pair(0x000000FC, 0x00000304)] = 0x01D6;
                my_composeMap[std::make_pair(0x000000FC, 0x0000030C)] = 0x01DA;
            }
        }

        ~Latin1_Supplement80() { }

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
	    return "Latin-1 Supplement";
	}

        bool is_defined(const UCS4 uc) const
        {
            return 1;
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Latin1_Supplement80::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Latin1_Supplement80::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Latin1_Supplement80::my_title[uc - my_first_letter];
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
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x00B2u:
                return 2;
            case 0x00B3u:
                return 3;
            case 0x00B9u:
                return 1;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x00B2u:
            case 0x00B3u:
            case 0x00B9u:
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
            case 0x00B2u:
                return 2.000000;
            case 0x00B3u:
                return 3.000000;
            case 0x00B9u:
                return 1.000000;
            case 0x00BCu:
                return 0.250000;
            case 0x00BDu:
                return 0.500000;
            case 0x00BEu:
                return 0.750000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x00B2u:
            case 0x00B3u:
            case 0x00B9u:
            case 0x00BCu:
            case 0x00BDu:
            case 0x00BEu:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Latin1_Supplement80::my_cat[uc - my_first_letter]);
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
            return Latin1_Supplement80::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Latin1_Supplement80::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Latin1_Supplement80::my_decompStr[uc - my_first_letter][0];
            us[1] = Latin1_Supplement80::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

            case 0x00BC:
                us.resize(3);
                us[2u] = 0x0034u;
                break;

            case 0x00BD:
                us.resize(3);
                us[2u] = 0x0032u;
                break;

            case 0x00BE:
                us.resize(3);
                us[2u] = 0x0034u;
                break;
            }
            if (0x0000u == us[1])
                us.resize(1);
            return us;
        }

        bool must_mirror(const UCS4 uc) const
        {
            return my_mirror.test(uc - my_first_letter);
        }

        Line_Break linebreak(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return LB_MAX;
            return Babylon::Line_Break(Latin1_Supplement80::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Latin1_Supplement80::my_ea[uc - my_first_letter]);
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
            return my_White_Space.test(uc - my_first_letter);
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
            return my_Hyphen.test(uc - my_first_letter);
        }

        bool is_Quotation_Mark(const UCS4 uc) const
        {
            return my_Quotation_Mark.test(uc - my_first_letter);
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
            return 0;
        }

        bool is_Other_ID_Start(const UCS4 uc) const
        {
            return 0;
        }

      private:
        // functions
        Latin1_Supplement80(const Latin1_Supplement80 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const UCS4 my_upper[128];
        static const UCS4 my_lower[128];
        static const UCS4 my_title[128];
        static const unsigned char my_cat[128];
        static const Babylon::Bidir_Props my_bidir[128];
        static const unsigned char my_decomp[128];
        static const UCS2 my_decompStr[128][2];
        static const std::bitset<128> my_mirror;
        static const unsigned char my_lb[128];
        static const unsigned char my_ea[128];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<128> my_White_Space;
        static const std::bitset<128> my_Hyphen;
        static const std::bitset<128> my_Quotation_Mark;
        static const std::bitset<128> my_Diacritic;
        static const std::bitset<128> my_Extender;
    }; // class Latin1_Supplement80

    const UCS4 Latin1_Supplement80::my_upper[] =
    {
        0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 
        0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F, 
        0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 
        0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F, 
        0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 
        0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF, 
        0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x039C, 0x00B6, 0x00B7, 
        0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF, 
        0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 
        0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF, 
        0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 
        0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF, 
        0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 
        0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF, 
        0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00F7, 
        0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x0178
    };

    const UCS4 Latin1_Supplement80::my_lower[] =
    {
        0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 
        0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F, 
        0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 
        0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F, 
        0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 
        0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF, 
        0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 
        0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF, 
        0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 
        0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF, 
        0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00D7, 
        0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00DF, 
        0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 
        0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF, 
        0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 
        0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF
    };

    const UCS4 Latin1_Supplement80::my_title[] =
    {
        0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 
        0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F, 
        0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 
        0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F, 
        0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 
        0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF, 
        0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x039C, 0x00B6, 0x00B7, 
        0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF, 
        0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 
        0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF, 
        0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 
        0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF, 
        0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 
        0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF, 
        0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00F7, 
        0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x0178
    };

    const unsigned char Latin1_Supplement80::my_cat[] =
    {
        CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, 
        CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, 
        CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, 
        CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, 
        CAT_Zs, CAT_Po, CAT_Sc, CAT_Sc, CAT_Sc, CAT_Sc, CAT_So, CAT_So, 
        CAT_Sk, CAT_So, CAT_Ll, CAT_Pi, CAT_Sm, CAT_Cf, CAT_So, CAT_Sk, 
        CAT_So, CAT_Sm, CAT_No, CAT_No, CAT_Sk, CAT_Ll, CAT_So, CAT_Po, 
        CAT_Sk, CAT_No, CAT_Ll, CAT_Pf, CAT_No, CAT_No, CAT_No, CAT_Po, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Sm, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Sm, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll
    };

    const Babylon::Bidir_Props Latin1_Supplement80::my_bidir[] =
    {
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_B, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_CS, BIDIR_ON, BIDIR_ET, BIDIR_ET, 
        BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ET, BIDIR_ET, BIDIR_EN, BIDIR_EN, 
        BIDIR_ON, BIDIR_L, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_EN, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
    };

    const unsigned char Latin1_Supplement80::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_NOBREAK, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_SUPER, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_SUPER, DECOMP_SUPER, DECOMP_CANONICAL, 
        DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_FRACTION, DECOMP_CANONICAL, 
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

    const UCS2 Latin1_Supplement80::my_decompStr[][2] =
    {
        { 0x00000080u, 0x00000000u }, { 0x00000081u, 0x00000000u },  // 00000080
        { 0x00000082u, 0x00000000u }, { 0x00000083u, 0x00000000u },  // 00000082
        { 0x00000084u, 0x00000000u }, { 0x00000085u, 0x00000000u },  // 00000084
        { 0x00000086u, 0x00000000u }, { 0x00000087u, 0x00000000u },  // 00000086
        { 0x00000088u, 0x00000000u }, { 0x00000089u, 0x00000000u },  // 00000088
        { 0x0000008Au, 0x00000000u }, { 0x0000008Bu, 0x00000000u },  // 0000008A
        { 0x0000008Cu, 0x00000000u }, { 0x0000008Du, 0x00000000u },  // 0000008C
        { 0x0000008Eu, 0x00000000u }, { 0x0000008Fu, 0x00000000u },  // 0000008E
        { 0x00000090u, 0x00000000u }, { 0x00000091u, 0x00000000u },  // 00000090
        { 0x00000092u, 0x00000000u }, { 0x00000093u, 0x00000000u },  // 00000092
        { 0x00000094u, 0x00000000u }, { 0x00000095u, 0x00000000u },  // 00000094
        { 0x00000096u, 0x00000000u }, { 0x00000097u, 0x00000000u },  // 00000096
        { 0x00000098u, 0x00000000u }, { 0x00000099u, 0x00000000u },  // 00000098
        { 0x0000009Au, 0x00000000u }, { 0x0000009Bu, 0x00000000u },  // 0000009A
        { 0x0000009Cu, 0x00000000u }, { 0x0000009Du, 0x00000000u },  // 0000009C
        { 0x0000009Eu, 0x00000000u }, { 0x0000009Fu, 0x00000000u },  // 0000009E
        { 0x00000020u, 0x00000000u }, { 0x000000A1u, 0x00000000u },  // 000000A0
        { 0x000000A2u, 0x00000000u }, { 0x000000A3u, 0x00000000u },  // 000000A2
        { 0x000000A4u, 0x00000000u }, { 0x000000A5u, 0x00000000u },  // 000000A4
        { 0x000000A6u, 0x00000000u }, { 0x000000A7u, 0x00000000u },  // 000000A6
        { 0x00000020u, 0x00000308u }, { 0x000000A9u, 0x00000000u },  // 000000A8
        { 0x00000061u, 0x00000000u }, { 0x000000ABu, 0x00000000u },  // 000000AA
        { 0x000000ACu, 0x00000000u }, { 0x000000ADu, 0x00000000u },  // 000000AC
        { 0x000000AEu, 0x00000000u }, { 0x00000020u, 0x00000304u },  // 000000AE
        { 0x000000B0u, 0x00000000u }, { 0x000000B1u, 0x00000000u },  // 000000B0
        { 0x00000032u, 0x00000000u }, { 0x00000033u, 0x00000000u },  // 000000B2
        { 0x00000020u, 0x00000301u }, { 0x000003BCu, 0x00000000u },  // 000000B4
        { 0x000000B6u, 0x00000000u }, { 0x000000B7u, 0x00000000u },  // 000000B6
        { 0x00000020u, 0x00000327u }, { 0x00000031u, 0x00000000u },  // 000000B8
        { 0x0000006Fu, 0x00000000u }, { 0x000000BBu, 0x00000000u },  // 000000BA
        { 0x00000031u, 0x00002044u }, { 0x00000031u, 0x00002044u },  // 000000BC
        { 0x00000033u, 0x00002044u }, { 0x000000BFu, 0x00000000u },  // 000000BE
        { 0x00000041u, 0x00000300u }, { 0x00000041u, 0x00000301u },  // 000000C0
        { 0x00000041u, 0x00000302u }, { 0x00000041u, 0x00000303u },  // 000000C2
        { 0x00000041u, 0x00000308u }, { 0x00000041u, 0x0000030Au },  // 000000C4
        { 0x000000C6u, 0x00000000u }, { 0x00000043u, 0x00000327u },  // 000000C6
        { 0x00000045u, 0x00000300u }, { 0x00000045u, 0x00000301u },  // 000000C8
        { 0x00000045u, 0x00000302u }, { 0x00000045u, 0x00000308u },  // 000000CA
        { 0x00000049u, 0x00000300u }, { 0x00000049u, 0x00000301u },  // 000000CC
        { 0x00000049u, 0x00000302u }, { 0x00000049u, 0x00000308u },  // 000000CE
        { 0x000000D0u, 0x00000000u }, { 0x0000004Eu, 0x00000303u },  // 000000D0
        { 0x0000004Fu, 0x00000300u }, { 0x0000004Fu, 0x00000301u },  // 000000D2
        { 0x0000004Fu, 0x00000302u }, { 0x0000004Fu, 0x00000303u },  // 000000D4
        { 0x0000004Fu, 0x00000308u }, { 0x000000D7u, 0x00000000u },  // 000000D6
        { 0x000000D8u, 0x00000000u }, { 0x00000055u, 0x00000300u },  // 000000D8
        { 0x00000055u, 0x00000301u }, { 0x00000055u, 0x00000302u },  // 000000DA
        { 0x00000055u, 0x00000308u }, { 0x00000059u, 0x00000301u },  // 000000DC
        { 0x000000DEu, 0x00000000u }, { 0x000000DFu, 0x00000000u },  // 000000DE
        { 0x00000061u, 0x00000300u }, { 0x00000061u, 0x00000301u },  // 000000E0
        { 0x00000061u, 0x00000302u }, { 0x00000061u, 0x00000303u },  // 000000E2
        { 0x00000061u, 0x00000308u }, { 0x00000061u, 0x0000030Au },  // 000000E4
        { 0x000000E6u, 0x00000000u }, { 0x00000063u, 0x00000327u },  // 000000E6
        { 0x00000065u, 0x00000300u }, { 0x00000065u, 0x00000301u },  // 000000E8
        { 0x00000065u, 0x00000302u }, { 0x00000065u, 0x00000308u },  // 000000EA
        { 0x00000069u, 0x00000300u }, { 0x00000069u, 0x00000301u },  // 000000EC
        { 0x00000069u, 0x00000302u }, { 0x00000069u, 0x00000308u },  // 000000EE
        { 0x000000F0u, 0x00000000u }, { 0x0000006Eu, 0x00000303u },  // 000000F0
        { 0x0000006Fu, 0x00000300u }, { 0x0000006Fu, 0x00000301u },  // 000000F2
        { 0x0000006Fu, 0x00000302u }, { 0x0000006Fu, 0x00000303u },  // 000000F4
        { 0x0000006Fu, 0x00000308u }, { 0x000000F7u, 0x00000000u },  // 000000F6
        { 0x000000F8u, 0x00000000u }, { 0x00000075u, 0x00000300u },  // 000000F8
        { 0x00000075u, 0x00000301u }, { 0x00000075u, 0x00000302u },  // 000000FA
        { 0x00000075u, 0x00000308u }, { 0x00000079u, 0x00000301u },  // 000000FC
        { 0x000000FEu, 0x00000000u }, { 0x00000079u, 0x00000308u }
    };

    const std::bitset<128> Latin1_Supplement80::my_mirror(std::string("00000000000000000000000000000000000000000000000000000000000000000000100000000000000010000000000000000000000000000000000000000000"));

    const unsigned char Latin1_Supplement80::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_NL, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_GL, LB_AI, LB_PO, LB_PR, LB_PR, LB_PR, LB_AL, LB_AI, 
        LB_AI, LB_AL, LB_AI, LB_QU, LB_AL, LB_BA, LB_AL, LB_AL, 
        LB_PO, LB_PR, LB_AI, LB_AI, LB_BB, LB_AL, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_QU, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, 
        LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, 
        LB_AI, LB_AI, LB_AI, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, 
        LB_AI, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AL, LB_AI, LB_AL, LB_AI, LB_AL
    };

    const unsigned char Latin1_Supplement80::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_A, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_Na, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_Na, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N
    };

    const std::bitset<128> Latin1_Supplement80::my_White_Space(std::string("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000100000"));

    const std::bitset<128> Latin1_Supplement80::my_Hyphen(std::string("00000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000"));

    const std::bitset<128> Latin1_Supplement80::my_Quotation_Mark(std::string("00000000000000000000000000000000000000000000000000000000000000000000100000000000000010000000000000000000000000000000000000000000"));

    const std::bitset<128> Latin1_Supplement80::my_Diacritic(std::string("00000000000000000000000000000000000000000000000000000000000000000000000110010000100000010000000000000000000000000000000000000000"));

    const std::bitset<128> Latin1_Supplement80::my_Extender(std::string("00000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Latin1_Supplement80);
