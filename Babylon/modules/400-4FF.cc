/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 400-4FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:39 +0200.
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
    class Cyrillic400 : public Babylon::Block
    {
      public:
        void clean() { };

        Cyrillic400() :
	    my_first_letter(0x400),
	    my_last_letter(0x4FF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000406, 0x00000308)] = 0x0407;
                my_composeMap[std::make_pair(0x00000410, 0x00000306)] = 0x04D0;
                my_composeMap[std::make_pair(0x00000410, 0x00000308)] = 0x04D2;
                my_composeMap[std::make_pair(0x00000413, 0x00000301)] = 0x0403;
                my_composeMap[std::make_pair(0x00000415, 0x00000300)] = 0x0400;
                my_composeMap[std::make_pair(0x00000415, 0x00000306)] = 0x04D6;
                my_composeMap[std::make_pair(0x00000415, 0x00000308)] = 0x0401;
                my_composeMap[std::make_pair(0x00000416, 0x00000306)] = 0x04C1;
                my_composeMap[std::make_pair(0x00000416, 0x00000308)] = 0x04DC;
                my_composeMap[std::make_pair(0x00000417, 0x00000308)] = 0x04DE;
                my_composeMap[std::make_pair(0x00000418, 0x00000300)] = 0x040D;
                my_composeMap[std::make_pair(0x00000418, 0x00000304)] = 0x04E2;
                my_composeMap[std::make_pair(0x00000418, 0x00000306)] = 0x0419;
                my_composeMap[std::make_pair(0x00000418, 0x00000308)] = 0x04E4;
                my_composeMap[std::make_pair(0x0000041A, 0x00000301)] = 0x040C;
                my_composeMap[std::make_pair(0x0000041E, 0x00000308)] = 0x04E6;
                my_composeMap[std::make_pair(0x00000423, 0x00000304)] = 0x04EE;
                my_composeMap[std::make_pair(0x00000423, 0x00000306)] = 0x040E;
                my_composeMap[std::make_pair(0x00000423, 0x00000308)] = 0x04F0;
                my_composeMap[std::make_pair(0x00000423, 0x0000030B)] = 0x04F2;
                my_composeMap[std::make_pair(0x00000427, 0x00000308)] = 0x04F4;
                my_composeMap[std::make_pair(0x0000042B, 0x00000308)] = 0x04F8;
                my_composeMap[std::make_pair(0x0000042D, 0x00000308)] = 0x04EC;
                my_composeMap[std::make_pair(0x00000430, 0x00000306)] = 0x04D1;
                my_composeMap[std::make_pair(0x00000430, 0x00000308)] = 0x04D3;
                my_composeMap[std::make_pair(0x00000433, 0x00000301)] = 0x0453;
                my_composeMap[std::make_pair(0x00000435, 0x00000300)] = 0x0450;
                my_composeMap[std::make_pair(0x00000435, 0x00000306)] = 0x04D7;
                my_composeMap[std::make_pair(0x00000435, 0x00000308)] = 0x0451;
                my_composeMap[std::make_pair(0x00000436, 0x00000306)] = 0x04C2;
                my_composeMap[std::make_pair(0x00000436, 0x00000308)] = 0x04DD;
                my_composeMap[std::make_pair(0x00000437, 0x00000308)] = 0x04DF;
                my_composeMap[std::make_pair(0x00000438, 0x00000300)] = 0x045D;
                my_composeMap[std::make_pair(0x00000438, 0x00000304)] = 0x04E3;
                my_composeMap[std::make_pair(0x00000438, 0x00000306)] = 0x0439;
                my_composeMap[std::make_pair(0x00000438, 0x00000308)] = 0x04E5;
                my_composeMap[std::make_pair(0x0000043A, 0x00000301)] = 0x045C;
                my_composeMap[std::make_pair(0x0000043E, 0x00000308)] = 0x04E7;
                my_composeMap[std::make_pair(0x00000443, 0x00000304)] = 0x04EF;
                my_composeMap[std::make_pair(0x00000443, 0x00000306)] = 0x045E;
                my_composeMap[std::make_pair(0x00000443, 0x00000308)] = 0x04F1;
                my_composeMap[std::make_pair(0x00000443, 0x0000030B)] = 0x04F3;
                my_composeMap[std::make_pair(0x00000447, 0x00000308)] = 0x04F5;
                my_composeMap[std::make_pair(0x0000044B, 0x00000308)] = 0x04F9;
                my_composeMap[std::make_pair(0x0000044D, 0x00000308)] = 0x04ED;
                my_composeMap[std::make_pair(0x00000456, 0x00000308)] = 0x0457;
                my_composeMap[std::make_pair(0x00000474, 0x0000030F)] = 0x0476;
                my_composeMap[std::make_pair(0x00000475, 0x0000030F)] = 0x0477;
                my_composeMap[std::make_pair(0x000004D8, 0x00000308)] = 0x04DA;
                my_composeMap[std::make_pair(0x000004D9, 0x00000308)] = 0x04DB;
                my_composeMap[std::make_pair(0x000004E8, 0x00000308)] = 0x04EA;
                my_composeMap[std::make_pair(0x000004E9, 0x00000308)] = 0x04EB;
            }
        }

        ~Cyrillic400() { }

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
	    return "Cyrillic";
	}

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Cyrillic400::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Cyrillic400::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Cyrillic400::my_title[uc - my_first_letter];
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
            return Babylon::Gen_Cat(Cyrillic400::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(Cyrillic400::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return Cyrillic400::my_bidir[uc - my_first_letter];
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
            us[0] = Cyrillic400::my_decompStr[uc - my_first_letter][0];
            us[1] = Cyrillic400::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Cyrillic400::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Cyrillic400::my_ea[uc - my_first_letter]);
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
            return my_Soft_Dotted.test(uc - my_first_letter);
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
        Cyrillic400(const Cyrillic400 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<256> my_is_defined;
        static const UCS4 my_upper[256];
        static const UCS4 my_lower[256];
        static const UCS4 my_title[256];
        static const unsigned char my_cat[256];
        static const unsigned char my_comb_cl[256];
        static const Babylon::Bidir_Props my_bidir[256];
        static const UCS2 my_decompStr[256][2];
        static const unsigned char my_lb[256];
        static const unsigned char my_ea[256];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<256> my_Diacritic;
        static const std::bitset<256> my_Soft_Dotted;
    }; // class Cyrillic400

    const std::bitset<256> Cyrillic400::my_is_defined(std::string("0000001100111111111111111111111111111111111111110111111111111111111111111111111111111111111111111111111111111111111111110111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const UCS4 Cyrillic400::my_upper[] =
    {
        0x0400, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 
        0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x040D, 0x040E, 0x040F, 
        0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 
        0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F, 
        0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 
        0x0428, 0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F, 
        0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 
        0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F, 
        0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 
        0x0428, 0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F, 
        0x0400, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 
        0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x040D, 0x040E, 0x040F, 
        0x0460, 0x0460, 0x0462, 0x0462, 0x0464, 0x0464, 0x0466, 0x0466, 
        0x0468, 0x0468, 0x046A, 0x046A, 0x046C, 0x046C, 0x046E, 0x046E, 
        0x0470, 0x0470, 0x0472, 0x0472, 0x0474, 0x0474, 0x0476, 0x0476, 
        0x0478, 0x0478, 0x047A, 0x047A, 0x047C, 0x047C, 0x047E, 0x047E, 
        0x0480, 0x0480, 0x0482, 0x0483, 0x0484, 0x0485, 0x0486, 0x0487, 
        0x0488, 0x0489, 0x048A, 0x048A, 0x048C, 0x048C, 0x048E, 0x048E, 
        0x0490, 0x0490, 0x0492, 0x0492, 0x0494, 0x0494, 0x0496, 0x0496, 
        0x0498, 0x0498, 0x049A, 0x049A, 0x049C, 0x049C, 0x049E, 0x049E, 
        0x04A0, 0x04A0, 0x04A2, 0x04A2, 0x04A4, 0x04A4, 0x04A6, 0x04A6, 
        0x04A8, 0x04A8, 0x04AA, 0x04AA, 0x04AC, 0x04AC, 0x04AE, 0x04AE, 
        0x04B0, 0x04B0, 0x04B2, 0x04B2, 0x04B4, 0x04B4, 0x04B6, 0x04B6, 
        0x04B8, 0x04B8, 0x04BA, 0x04BA, 0x04BC, 0x04BC, 0x04BE, 0x04BE, 
        0x04C0, 0x04C1, 0x04C1, 0x04C3, 0x04C3, 0x04C5, 0x04C5, 0x04C7, 
        0x04C7, 0x04C9, 0x04C9, 0x04CB, 0x04CB, 0x04CD, 0x04CD, 0x04CF, 
        0x04D0, 0x04D0, 0x04D2, 0x04D2, 0x04D4, 0x04D4, 0x04D6, 0x04D6, 
        0x04D8, 0x04D8, 0x04DA, 0x04DA, 0x04DC, 0x04DC, 0x04DE, 0x04DE, 
        0x04E0, 0x04E0, 0x04E2, 0x04E2, 0x04E4, 0x04E4, 0x04E6, 0x04E6, 
        0x04E8, 0x04E8, 0x04EA, 0x04EA, 0x04EC, 0x04EC, 0x04EE, 0x04EE, 
        0x04F0, 0x04F0, 0x04F2, 0x04F2, 0x04F4, 0x04F4, 0x04F6, 0x04F7, 
        0x04F8, 0x04F8, 0x04FA, 0x04FB, 0x04FC, 0x04FD, 0x04FE, 0x04FF
    };

    const UCS4 Cyrillic400::my_lower[] =
    {
        0x0450, 0x0451, 0x0452, 0x0453, 0x0454, 0x0455, 0x0456, 0x0457, 
        0x0458, 0x0459, 0x045A, 0x045B, 0x045C, 0x045D, 0x045E, 0x045F, 
        0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 
        0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E, 0x043F, 
        0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 
        0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F, 
        0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 
        0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E, 0x043F, 
        0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 
        0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F, 
        0x0450, 0x0451, 0x0452, 0x0453, 0x0454, 0x0455, 0x0456, 0x0457, 
        0x0458, 0x0459, 0x045A, 0x045B, 0x045C, 0x045D, 0x045E, 0x045F, 
        0x0461, 0x0461, 0x0463, 0x0463, 0x0465, 0x0465, 0x0467, 0x0467, 
        0x0469, 0x0469, 0x046B, 0x046B, 0x046D, 0x046D, 0x046F, 0x046F, 
        0x0471, 0x0471, 0x0473, 0x0473, 0x0475, 0x0475, 0x0477, 0x0477, 
        0x0479, 0x0479, 0x047B, 0x047B, 0x047D, 0x047D, 0x047F, 0x047F, 
        0x0481, 0x0481, 0x0482, 0x0483, 0x0484, 0x0485, 0x0486, 0x0487, 
        0x0488, 0x0489, 0x048B, 0x048B, 0x048D, 0x048D, 0x048F, 0x048F, 
        0x0491, 0x0491, 0x0493, 0x0493, 0x0495, 0x0495, 0x0497, 0x0497, 
        0x0499, 0x0499, 0x049B, 0x049B, 0x049D, 0x049D, 0x049F, 0x049F, 
        0x04A1, 0x04A1, 0x04A3, 0x04A3, 0x04A5, 0x04A5, 0x04A7, 0x04A7, 
        0x04A9, 0x04A9, 0x04AB, 0x04AB, 0x04AD, 0x04AD, 0x04AF, 0x04AF, 
        0x04B1, 0x04B1, 0x04B3, 0x04B3, 0x04B5, 0x04B5, 0x04B7, 0x04B7, 
        0x04B9, 0x04B9, 0x04BB, 0x04BB, 0x04BD, 0x04BD, 0x04BF, 0x04BF, 
        0x04C0, 0x04C2, 0x04C2, 0x04C4, 0x04C4, 0x04C6, 0x04C6, 0x04C8, 
        0x04C8, 0x04CA, 0x04CA, 0x04CC, 0x04CC, 0x04CE, 0x04CE, 0x04CF, 
        0x04D1, 0x04D1, 0x04D3, 0x04D3, 0x04D5, 0x04D5, 0x04D7, 0x04D7, 
        0x04D9, 0x04D9, 0x04DB, 0x04DB, 0x04DD, 0x04DD, 0x04DF, 0x04DF, 
        0x04E1, 0x04E1, 0x04E3, 0x04E3, 0x04E5, 0x04E5, 0x04E7, 0x04E7, 
        0x04E9, 0x04E9, 0x04EB, 0x04EB, 0x04ED, 0x04ED, 0x04EF, 0x04EF, 
        0x04F1, 0x04F1, 0x04F3, 0x04F3, 0x04F5, 0x04F5, 0x04F6, 0x04F7, 
        0x04F9, 0x04F9, 0x04FA, 0x04FB, 0x04FC, 0x04FD, 0x04FE, 0x04FF
    };

    const UCS4 Cyrillic400::my_title[] =
    {
        0x0400, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 
        0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x040D, 0x040E, 0x040F, 
        0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 
        0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F, 
        0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 
        0x0428, 0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F, 
        0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 
        0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F, 
        0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 
        0x0428, 0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F, 
        0x0400, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 
        0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x040D, 0x040E, 0x040F, 
        0x0460, 0x0460, 0x0462, 0x0462, 0x0464, 0x0464, 0x0466, 0x0466, 
        0x0468, 0x0468, 0x046A, 0x046A, 0x046C, 0x046C, 0x046E, 0x046E, 
        0x0470, 0x0470, 0x0472, 0x0472, 0x0474, 0x0474, 0x0476, 0x0476, 
        0x0478, 0x0478, 0x047A, 0x047A, 0x047C, 0x047C, 0x047E, 0x047E, 
        0x0480, 0x0480, 0x0482, 0x0483, 0x0484, 0x0485, 0x0486, 0x0487, 
        0x0488, 0x0489, 0x048A, 0x048A, 0x048C, 0x048C, 0x048E, 0x048E, 
        0x0490, 0x0490, 0x0492, 0x0492, 0x0494, 0x0494, 0x0496, 0x0496, 
        0x0498, 0x0498, 0x049A, 0x049A, 0x049C, 0x049C, 0x049E, 0x049E, 
        0x04A0, 0x04A0, 0x04A2, 0x04A2, 0x04A4, 0x04A4, 0x04A6, 0x04A6, 
        0x04A8, 0x04A8, 0x04AA, 0x04AA, 0x04AC, 0x04AC, 0x04AE, 0x04AE, 
        0x04B0, 0x04B0, 0x04B2, 0x04B2, 0x04B4, 0x04B4, 0x04B6, 0x04B6, 
        0x04B8, 0x04B8, 0x04BA, 0x04BA, 0x04BC, 0x04BC, 0x04BE, 0x04BE, 
        0x04C0, 0x04C1, 0x04C1, 0x04C3, 0x04C3, 0x04C5, 0x04C5, 0x04C7, 
        0x04C7, 0x04C9, 0x04C9, 0x04CB, 0x04CB, 0x04CD, 0x04CD, 0x04CF, 
        0x04D0, 0x04D0, 0x04D2, 0x04D2, 0x04D4, 0x04D4, 0x04D6, 0x04D6, 
        0x04D8, 0x04D8, 0x04DA, 0x04DA, 0x04DC, 0x04DC, 0x04DE, 0x04DE, 
        0x04E0, 0x04E0, 0x04E2, 0x04E2, 0x04E4, 0x04E4, 0x04E6, 0x04E6, 
        0x04E8, 0x04E8, 0x04EA, 0x04EA, 0x04EC, 0x04EC, 0x04EE, 0x04EE, 
        0x04F0, 0x04F0, 0x04F2, 0x04F2, 0x04F4, 0x04F4, 0x04F6, 0x04F7, 
        0x04F8, 0x04F8, 0x04FA, 0x04FB, 0x04FC, 0x04FD, 0x04FE, 0x04FF
    };

    const unsigned char Cyrillic400::my_cat[] =
    {
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_So, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lu, 
        CAT_Me, CAT_Me, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
        CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu
    };

    const unsigned char Cyrillic400::my_comb_cl[] = {
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
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 230, 230, 230, 230, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props Cyrillic400::my_bidir[] =
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
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

    const UCS2 Cyrillic400::my_decompStr[][2] =
    {
        { 0x00000415u, 0x00000300u }, { 0x00000415u, 0x00000308u },  // 00000400
        { 0x00000402u, 0x00000000u }, { 0x00000413u, 0x00000301u },  // 00000402
        { 0x00000404u, 0x00000000u }, { 0x00000405u, 0x00000000u },  // 00000404
        { 0x00000406u, 0x00000000u }, { 0x00000406u, 0x00000308u },  // 00000406
        { 0x00000408u, 0x00000000u }, { 0x00000409u, 0x00000000u },  // 00000408
        { 0x0000040Au, 0x00000000u }, { 0x0000040Bu, 0x00000000u },  // 0000040A
        { 0x0000041Au, 0x00000301u }, { 0x00000418u, 0x00000300u },  // 0000040C
        { 0x00000423u, 0x00000306u }, { 0x0000040Fu, 0x00000000u },  // 0000040E
        { 0x00000410u, 0x00000000u }, { 0x00000411u, 0x00000000u },  // 00000410
        { 0x00000412u, 0x00000000u }, { 0x00000413u, 0x00000000u },  // 00000412
        { 0x00000414u, 0x00000000u }, { 0x00000415u, 0x00000000u },  // 00000414
        { 0x00000416u, 0x00000000u }, { 0x00000417u, 0x00000000u },  // 00000416
        { 0x00000418u, 0x00000000u }, { 0x00000418u, 0x00000306u },  // 00000418
        { 0x0000041Au, 0x00000000u }, { 0x0000041Bu, 0x00000000u },  // 0000041A
        { 0x0000041Cu, 0x00000000u }, { 0x0000041Du, 0x00000000u },  // 0000041C
        { 0x0000041Eu, 0x00000000u }, { 0x0000041Fu, 0x00000000u },  // 0000041E
        { 0x00000420u, 0x00000000u }, { 0x00000421u, 0x00000000u },  // 00000420
        { 0x00000422u, 0x00000000u }, { 0x00000423u, 0x00000000u },  // 00000422
        { 0x00000424u, 0x00000000u }, { 0x00000425u, 0x00000000u },  // 00000424
        { 0x00000426u, 0x00000000u }, { 0x00000427u, 0x00000000u },  // 00000426
        { 0x00000428u, 0x00000000u }, { 0x00000429u, 0x00000000u },  // 00000428
        { 0x0000042Au, 0x00000000u }, { 0x0000042Bu, 0x00000000u },  // 0000042A
        { 0x0000042Cu, 0x00000000u }, { 0x0000042Du, 0x00000000u },  // 0000042C
        { 0x0000042Eu, 0x00000000u }, { 0x0000042Fu, 0x00000000u },  // 0000042E
        { 0x00000430u, 0x00000000u }, { 0x00000431u, 0x00000000u },  // 00000430
        { 0x00000432u, 0x00000000u }, { 0x00000433u, 0x00000000u },  // 00000432
        { 0x00000434u, 0x00000000u }, { 0x00000435u, 0x00000000u },  // 00000434
        { 0x00000436u, 0x00000000u }, { 0x00000437u, 0x00000000u },  // 00000436
        { 0x00000438u, 0x00000000u }, { 0x00000438u, 0x00000306u },  // 00000438
        { 0x0000043Au, 0x00000000u }, { 0x0000043Bu, 0x00000000u },  // 0000043A
        { 0x0000043Cu, 0x00000000u }, { 0x0000043Du, 0x00000000u },  // 0000043C
        { 0x0000043Eu, 0x00000000u }, { 0x0000043Fu, 0x00000000u },  // 0000043E
        { 0x00000440u, 0x00000000u }, { 0x00000441u, 0x00000000u },  // 00000440
        { 0x00000442u, 0x00000000u }, { 0x00000443u, 0x00000000u },  // 00000442
        { 0x00000444u, 0x00000000u }, { 0x00000445u, 0x00000000u },  // 00000444
        { 0x00000446u, 0x00000000u }, { 0x00000447u, 0x00000000u },  // 00000446
        { 0x00000448u, 0x00000000u }, { 0x00000449u, 0x00000000u },  // 00000448
        { 0x0000044Au, 0x00000000u }, { 0x0000044Bu, 0x00000000u },  // 0000044A
        { 0x0000044Cu, 0x00000000u }, { 0x0000044Du, 0x00000000u },  // 0000044C
        { 0x0000044Eu, 0x00000000u }, { 0x0000044Fu, 0x00000000u },  // 0000044E
        { 0x00000435u, 0x00000300u }, { 0x00000435u, 0x00000308u },  // 00000450
        { 0x00000452u, 0x00000000u }, { 0x00000433u, 0x00000301u },  // 00000452
        { 0x00000454u, 0x00000000u }, { 0x00000455u, 0x00000000u },  // 00000454
        { 0x00000456u, 0x00000000u }, { 0x00000456u, 0x00000308u },  // 00000456
        { 0x00000458u, 0x00000000u }, { 0x00000459u, 0x00000000u },  // 00000458
        { 0x0000045Au, 0x00000000u }, { 0x0000045Bu, 0x00000000u },  // 0000045A
        { 0x0000043Au, 0x00000301u }, { 0x00000438u, 0x00000300u },  // 0000045C
        { 0x00000443u, 0x00000306u }, { 0x0000045Fu, 0x00000000u },  // 0000045E
        { 0x00000460u, 0x00000000u }, { 0x00000461u, 0x00000000u },  // 00000460
        { 0x00000462u, 0x00000000u }, { 0x00000463u, 0x00000000u },  // 00000462
        { 0x00000464u, 0x00000000u }, { 0x00000465u, 0x00000000u },  // 00000464
        { 0x00000466u, 0x00000000u }, { 0x00000467u, 0x00000000u },  // 00000466
        { 0x00000468u, 0x00000000u }, { 0x00000469u, 0x00000000u },  // 00000468
        { 0x0000046Au, 0x00000000u }, { 0x0000046Bu, 0x00000000u },  // 0000046A
        { 0x0000046Cu, 0x00000000u }, { 0x0000046Du, 0x00000000u },  // 0000046C
        { 0x0000046Eu, 0x00000000u }, { 0x0000046Fu, 0x00000000u },  // 0000046E
        { 0x00000470u, 0x00000000u }, { 0x00000471u, 0x00000000u },  // 00000470
        { 0x00000472u, 0x00000000u }, { 0x00000473u, 0x00000000u },  // 00000472
        { 0x00000474u, 0x00000000u }, { 0x00000475u, 0x00000000u },  // 00000474
        { 0x00000474u, 0x0000030Fu }, { 0x00000475u, 0x0000030Fu },  // 00000476
        { 0x00000478u, 0x00000000u }, { 0x00000479u, 0x00000000u },  // 00000478
        { 0x0000047Au, 0x00000000u }, { 0x0000047Bu, 0x00000000u },  // 0000047A
        { 0x0000047Cu, 0x00000000u }, { 0x0000047Du, 0x00000000u },  // 0000047C
        { 0x0000047Eu, 0x00000000u }, { 0x0000047Fu, 0x00000000u },  // 0000047E
        { 0x00000480u, 0x00000000u }, { 0x00000481u, 0x00000000u },  // 00000480
        { 0x00000482u, 0x00000000u }, { 0x00000483u, 0x00000000u },  // 00000482
        { 0x00000484u, 0x00000000u }, { 0x00000485u, 0x00000000u },  // 00000484
        { 0x00000486u, 0x00000000u }, { 0x00000487u, 0x00000000u },  // 00000486
        { 0x00000488u, 0x00000000u }, { 0x00000489u, 0x00000000u },  // 00000488
        { 0x0000048Au, 0x00000000u }, { 0x0000048Bu, 0x00000000u },  // 0000048A
        { 0x0000048Cu, 0x00000000u }, { 0x0000048Du, 0x00000000u },  // 0000048C
        { 0x0000048Eu, 0x00000000u }, { 0x0000048Fu, 0x00000000u },  // 0000048E
        { 0x00000490u, 0x00000000u }, { 0x00000491u, 0x00000000u },  // 00000490
        { 0x00000492u, 0x00000000u }, { 0x00000493u, 0x00000000u },  // 00000492
        { 0x00000494u, 0x00000000u }, { 0x00000495u, 0x00000000u },  // 00000494
        { 0x00000496u, 0x00000000u }, { 0x00000497u, 0x00000000u },  // 00000496
        { 0x00000498u, 0x00000000u }, { 0x00000499u, 0x00000000u },  // 00000498
        { 0x0000049Au, 0x00000000u }, { 0x0000049Bu, 0x00000000u },  // 0000049A
        { 0x0000049Cu, 0x00000000u }, { 0x0000049Du, 0x00000000u },  // 0000049C
        { 0x0000049Eu, 0x00000000u }, { 0x0000049Fu, 0x00000000u },  // 0000049E
        { 0x000004A0u, 0x00000000u }, { 0x000004A1u, 0x00000000u },  // 000004A0
        { 0x000004A2u, 0x00000000u }, { 0x000004A3u, 0x00000000u },  // 000004A2
        { 0x000004A4u, 0x00000000u }, { 0x000004A5u, 0x00000000u },  // 000004A4
        { 0x000004A6u, 0x00000000u }, { 0x000004A7u, 0x00000000u },  // 000004A6
        { 0x000004A8u, 0x00000000u }, { 0x000004A9u, 0x00000000u },  // 000004A8
        { 0x000004AAu, 0x00000000u }, { 0x000004ABu, 0x00000000u },  // 000004AA
        { 0x000004ACu, 0x00000000u }, { 0x000004ADu, 0x00000000u },  // 000004AC
        { 0x000004AEu, 0x00000000u }, { 0x000004AFu, 0x00000000u },  // 000004AE
        { 0x000004B0u, 0x00000000u }, { 0x000004B1u, 0x00000000u },  // 000004B0
        { 0x000004B2u, 0x00000000u }, { 0x000004B3u, 0x00000000u },  // 000004B2
        { 0x000004B4u, 0x00000000u }, { 0x000004B5u, 0x00000000u },  // 000004B4
        { 0x000004B6u, 0x00000000u }, { 0x000004B7u, 0x00000000u },  // 000004B6
        { 0x000004B8u, 0x00000000u }, { 0x000004B9u, 0x00000000u },  // 000004B8
        { 0x000004BAu, 0x00000000u }, { 0x000004BBu, 0x00000000u },  // 000004BA
        { 0x000004BCu, 0x00000000u }, { 0x000004BDu, 0x00000000u },  // 000004BC
        { 0x000004BEu, 0x00000000u }, { 0x000004BFu, 0x00000000u },  // 000004BE
        { 0x000004C0u, 0x00000000u }, { 0x00000416u, 0x00000306u },  // 000004C0
        { 0x00000436u, 0x00000306u }, { 0x000004C3u, 0x00000000u },  // 000004C2
        { 0x000004C4u, 0x00000000u }, { 0x000004C5u, 0x00000000u },  // 000004C4
        { 0x000004C6u, 0x00000000u }, { 0x000004C7u, 0x00000000u },  // 000004C6
        { 0x000004C8u, 0x00000000u }, { 0x000004C9u, 0x00000000u },  // 000004C8
        { 0x000004CAu, 0x00000000u }, { 0x000004CBu, 0x00000000u },  // 000004CA
        { 0x000004CCu, 0x00000000u }, { 0x000004CDu, 0x00000000u },  // 000004CC
        { 0x000004CEu, 0x00000000u }, { 0x000004CFu, 0x00000000u },  // 000004CE
        { 0x00000410u, 0x00000306u }, { 0x00000430u, 0x00000306u },  // 000004D0
        { 0x00000410u, 0x00000308u }, { 0x00000430u, 0x00000308u },  // 000004D2
        { 0x000004D4u, 0x00000000u }, { 0x000004D5u, 0x00000000u },  // 000004D4
        { 0x00000415u, 0x00000306u }, { 0x00000435u, 0x00000306u },  // 000004D6
        { 0x000004D8u, 0x00000000u }, { 0x000004D9u, 0x00000000u },  // 000004D8
        { 0x000004D8u, 0x00000308u }, { 0x000004D9u, 0x00000308u },  // 000004DA
        { 0x00000416u, 0x00000308u }, { 0x00000436u, 0x00000308u },  // 000004DC
        { 0x00000417u, 0x00000308u }, { 0x00000437u, 0x00000308u },  // 000004DE
        { 0x000004E0u, 0x00000000u }, { 0x000004E1u, 0x00000000u },  // 000004E0
        { 0x00000418u, 0x00000304u }, { 0x00000438u, 0x00000304u },  // 000004E2
        { 0x00000418u, 0x00000308u }, { 0x00000438u, 0x00000308u },  // 000004E4
        { 0x0000041Eu, 0x00000308u }, { 0x0000043Eu, 0x00000308u },  // 000004E6
        { 0x000004E8u, 0x00000000u }, { 0x000004E9u, 0x00000000u },  // 000004E8
        { 0x000004E8u, 0x00000308u }, { 0x000004E9u, 0x00000308u },  // 000004EA
        { 0x0000042Du, 0x00000308u }, { 0x0000044Du, 0x00000308u },  // 000004EC
        { 0x00000423u, 0x00000304u }, { 0x00000443u, 0x00000304u },  // 000004EE
        { 0x00000423u, 0x00000308u }, { 0x00000443u, 0x00000308u },  // 000004F0
        { 0x00000423u, 0x0000030Bu }, { 0x00000443u, 0x0000030Bu },  // 000004F2
        { 0x00000427u, 0x00000308u }, { 0x00000447u, 0x00000308u },  // 000004F4
        { 0x000004F6u, 0x00000000u }, { 0x000004F7u, 0x00000000u },  // 000004F6
        { 0x0000042Bu, 0x00000308u }, { 0x0000044Bu, 0x00000308u },  // 000004F8
        { 0x000004FAu, 0x00000000u }, { 0x000004FBu, 0x00000000u },  // 000004FA
        { 0x000004FCu, 0x00000000u }, { 0x000004FDu, 0x00000000u },  // 000004FC
        { 0x000004FEu, 0x00000000u }, { 0x000004FFu, 0x00000000u }
    };

    const unsigned char Cyrillic400::my_lb[] =
    {
        LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, 
        LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const unsigned char Cyrillic400::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
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
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
    };

    const std::bitset<256> Cyrillic400::my_Diacritic(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<256> Cyrillic400::my_Soft_Dotted(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010100000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Cyrillic400);
