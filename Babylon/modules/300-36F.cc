/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 300-36F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:38 +0200.
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
    class Combining_Diacritical_Marks300 : public Babylon::Block
    {
      public:
        void clean() { };

        Combining_Diacritical_Marks300() :
	    my_first_letter(0x300),
	    my_last_letter(0x36F)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000308, 0x00000301)] = 0x0344;
            }
        }

        ~Combining_Diacritical_Marks300() { }

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
	    return "Combining Diacritical Marks";
	}

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Combining_Diacritical_Marks300::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return uc;
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Combining_Diacritical_Marks300::my_title[uc - my_first_letter];
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
            return Babylon::Gen_Cat(CAT_Mn);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(Combining_Diacritical_Marks300::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return BIDIR_NSM;
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
            us[0] = Combining_Diacritical_Marks300::my_decompStr[uc - my_first_letter][0];
            us[1] = Combining_Diacritical_Marks300::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(LB_CM);
    }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_A);
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
            return my_Other_Default_Ignorable_Code_Point.test(uc - my_first_letter);
        }

        bool is_Deprecated(const UCS4 uc) const
        {
            return my_Deprecated.test(uc - my_first_letter);
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
        Combining_Diacritical_Marks300(const Combining_Diacritical_Marks300 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<112> my_is_defined;
        static const UCS4 my_upper[112];
        static const UCS4 my_title[112];
        static const unsigned char my_comb_cl[112];
        static const UCS2 my_decompStr[112][2];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<112> my_Other_Alphabetic;
        static const std::bitset<112> my_Diacritic;
        static const std::bitset<112> my_Other_Lowercase;
        static const std::bitset<112> my_Grapheme_Link;
        static const std::bitset<112> my_Other_Default_Ignorable_Code_Point;
        static const std::bitset<112> my_Deprecated;
    }; // class Combining_Diacritical_Marks300

    const std::bitset<112> Combining_Diacritical_Marks300::my_is_defined(std::string("1111111111111111111000001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const UCS4 Combining_Diacritical_Marks300::my_upper[] =
    {
        0x0300, 0x0301, 0x0302, 0x0303, 0x0304, 0x0305, 0x0306, 0x0307, 
        0x0308, 0x0309, 0x030A, 0x030B, 0x030C, 0x030D, 0x030E, 0x030F, 
        0x0310, 0x0311, 0x0312, 0x0313, 0x0314, 0x0315, 0x0316, 0x0317, 
        0x0318, 0x0319, 0x031A, 0x031B, 0x031C, 0x031D, 0x031E, 0x031F, 
        0x0320, 0x0321, 0x0322, 0x0323, 0x0324, 0x0325, 0x0326, 0x0327, 
        0x0328, 0x0329, 0x032A, 0x032B, 0x032C, 0x032D, 0x032E, 0x032F, 
        0x0330, 0x0331, 0x0332, 0x0333, 0x0334, 0x0335, 0x0336, 0x0337, 
        0x0338, 0x0339, 0x033A, 0x033B, 0x033C, 0x033D, 0x033E, 0x033F, 
        0x0340, 0x0341, 0x0342, 0x0343, 0x0344, 0x0399, 0x0346, 0x0347, 
        0x0348, 0x0349, 0x034A, 0x034B, 0x034C, 0x034D, 0x034E, 0x034F, 
        0x0350, 0x0351, 0x0352, 0x0353, 0x0354, 0x0355, 0x0356, 0x0357, 
        0x0358, 0x0359, 0x035A, 0x035B, 0x035C, 0x035D, 0x035E, 0x035F, 
        0x0360, 0x0361, 0x0362, 0x0363, 0x0364, 0x0365, 0x0366, 0x0367, 
        0x0368, 0x0369, 0x036A, 0x036B, 0x036C, 0x036D, 0x036E, 0x036F
    };

    const UCS4 Combining_Diacritical_Marks300::my_title[] =
    {
        0x0300, 0x0301, 0x0302, 0x0303, 0x0304, 0x0305, 0x0306, 0x0307, 
        0x0308, 0x0309, 0x030A, 0x030B, 0x030C, 0x030D, 0x030E, 0x030F, 
        0x0310, 0x0311, 0x0312, 0x0313, 0x0314, 0x0315, 0x0316, 0x0317, 
        0x0318, 0x0319, 0x031A, 0x031B, 0x031C, 0x031D, 0x031E, 0x031F, 
        0x0320, 0x0321, 0x0322, 0x0323, 0x0324, 0x0325, 0x0326, 0x0327, 
        0x0328, 0x0329, 0x032A, 0x032B, 0x032C, 0x032D, 0x032E, 0x032F, 
        0x0330, 0x0331, 0x0332, 0x0333, 0x0334, 0x0335, 0x0336, 0x0337, 
        0x0338, 0x0339, 0x033A, 0x033B, 0x033C, 0x033D, 0x033E, 0x033F, 
        0x0340, 0x0341, 0x0342, 0x0343, 0x0344, 0x0399, 0x0346, 0x0347, 
        0x0348, 0x0349, 0x034A, 0x034B, 0x034C, 0x034D, 0x034E, 0x034F, 
        0x0350, 0x0351, 0x0352, 0x0353, 0x0354, 0x0355, 0x0356, 0x0357, 
        0x0358, 0x0359, 0x035A, 0x035B, 0x035C, 0x035D, 0x035E, 0x035F, 
        0x0360, 0x0361, 0x0362, 0x0363, 0x0364, 0x0365, 0x0366, 0x0367, 
        0x0368, 0x0369, 0x036A, 0x036B, 0x036C, 0x036D, 0x036E, 0x036F
    };

    const unsigned char Combining_Diacritical_Marks300::my_comb_cl[] = {
        230, 230, 230, 230, 230, 230, 230, 230, 
        230, 230, 230, 230, 230, 230, 230, 230, 
        230, 230, 230, 230, 230, 232, 220, 220, 
        220, 220, 232, 216, 220, 220, 220, 220, 
        220, 202, 202, 220, 220, 220, 220, 202, 
        202, 220, 220, 220, 220, 220, 220, 220, 
        220, 220, 220, 220, 1, 1, 1, 1, 
        1, 220, 220, 220, 220, 230, 230, 230, 
        230, 230, 230, 230, 230, 240, 230, 220, 
        220, 220, 230, 230, 230, 220, 220, 0, 
        230, 230, 230, 220, 220, 220, 220, 230, 
        0, 0, 0, 0, 0, 234, 234, 233, 
        234, 234, 233, 230, 230, 230, 230, 230, 
        230, 230, 230, 230, 230, 230, 230, 230
    };

    const UCS2 Combining_Diacritical_Marks300::my_decompStr[][2] =
    {
        { 0x00000300u, 0x00000000u }, { 0x00000301u, 0x00000000u },  // 00000300
        { 0x00000302u, 0x00000000u }, { 0x00000303u, 0x00000000u },  // 00000302
        { 0x00000304u, 0x00000000u }, { 0x00000305u, 0x00000000u },  // 00000304
        { 0x00000306u, 0x00000000u }, { 0x00000307u, 0x00000000u },  // 00000306
        { 0x00000308u, 0x00000000u }, { 0x00000309u, 0x00000000u },  // 00000308
        { 0x0000030Au, 0x00000000u }, { 0x0000030Bu, 0x00000000u },  // 0000030A
        { 0x0000030Cu, 0x00000000u }, { 0x0000030Du, 0x00000000u },  // 0000030C
        { 0x0000030Eu, 0x00000000u }, { 0x0000030Fu, 0x00000000u },  // 0000030E
        { 0x00000310u, 0x00000000u }, { 0x00000311u, 0x00000000u },  // 00000310
        { 0x00000312u, 0x00000000u }, { 0x00000313u, 0x00000000u },  // 00000312
        { 0x00000314u, 0x00000000u }, { 0x00000315u, 0x00000000u },  // 00000314
        { 0x00000316u, 0x00000000u }, { 0x00000317u, 0x00000000u },  // 00000316
        { 0x00000318u, 0x00000000u }, { 0x00000319u, 0x00000000u },  // 00000318
        { 0x0000031Au, 0x00000000u }, { 0x0000031Bu, 0x00000000u },  // 0000031A
        { 0x0000031Cu, 0x00000000u }, { 0x0000031Du, 0x00000000u },  // 0000031C
        { 0x0000031Eu, 0x00000000u }, { 0x0000031Fu, 0x00000000u },  // 0000031E
        { 0x00000320u, 0x00000000u }, { 0x00000321u, 0x00000000u },  // 00000320
        { 0x00000322u, 0x00000000u }, { 0x00000323u, 0x00000000u },  // 00000322
        { 0x00000324u, 0x00000000u }, { 0x00000325u, 0x00000000u },  // 00000324
        { 0x00000326u, 0x00000000u }, { 0x00000327u, 0x00000000u },  // 00000326
        { 0x00000328u, 0x00000000u }, { 0x00000329u, 0x00000000u },  // 00000328
        { 0x0000032Au, 0x00000000u }, { 0x0000032Bu, 0x00000000u },  // 0000032A
        { 0x0000032Cu, 0x00000000u }, { 0x0000032Du, 0x00000000u },  // 0000032C
        { 0x0000032Eu, 0x00000000u }, { 0x0000032Fu, 0x00000000u },  // 0000032E
        { 0x00000330u, 0x00000000u }, { 0x00000331u, 0x00000000u },  // 00000330
        { 0x00000332u, 0x00000000u }, { 0x00000333u, 0x00000000u },  // 00000332
        { 0x00000334u, 0x00000000u }, { 0x00000335u, 0x00000000u },  // 00000334
        { 0x00000336u, 0x00000000u }, { 0x00000337u, 0x00000000u },  // 00000336
        { 0x00000338u, 0x00000000u }, { 0x00000339u, 0x00000000u },  // 00000338
        { 0x0000033Au, 0x00000000u }, { 0x0000033Bu, 0x00000000u },  // 0000033A
        { 0x0000033Cu, 0x00000000u }, { 0x0000033Du, 0x00000000u },  // 0000033C
        { 0x0000033Eu, 0x00000000u }, { 0x0000033Fu, 0x00000000u },  // 0000033E
        { 0x00000300u, 0x00000000u }, { 0x00000301u, 0x00000000u },  // 00000340
        { 0x00000342u, 0x00000000u }, { 0x00000313u, 0x00000000u },  // 00000342
        { 0x00000308u, 0x00000301u }, { 0x00000345u, 0x00000000u },  // 00000344
        { 0x00000346u, 0x00000000u }, { 0x00000347u, 0x00000000u },  // 00000346
        { 0x00000348u, 0x00000000u }, { 0x00000349u, 0x00000000u },  // 00000348
        { 0x0000034Au, 0x00000000u }, { 0x0000034Bu, 0x00000000u },  // 0000034A
        { 0x0000034Cu, 0x00000000u }, { 0x0000034Du, 0x00000000u },  // 0000034C
        { 0x0000034Eu, 0x00000000u }, { 0x0000034Fu, 0x00000000u },  // 0000034E
        { 0x00000350u, 0x00000000u }, { 0x00000351u, 0x00000000u },  // 00000350
        { 0x00000352u, 0x00000000u }, { 0x00000353u, 0x00000000u },  // 00000352
        { 0x00000354u, 0x00000000u }, { 0x00000355u, 0x00000000u },  // 00000354
        { 0x00000356u, 0x00000000u }, { 0x00000357u, 0x00000000u },  // 00000356
        { 0x00000358u, 0x00000000u }, { 0x00000359u, 0x00000000u },  // 00000358
        { 0x0000035Au, 0x00000000u }, { 0x0000035Bu, 0x00000000u },  // 0000035A
        { 0x0000035Cu, 0x00000000u }, { 0x0000035Du, 0x00000000u },  // 0000035C
        { 0x0000035Eu, 0x00000000u }, { 0x0000035Fu, 0x00000000u },  // 0000035E
        { 0x00000360u, 0x00000000u }, { 0x00000361u, 0x00000000u },  // 00000360
        { 0x00000362u, 0x00000000u }, { 0x00000363u, 0x00000000u },  // 00000362
        { 0x00000364u, 0x00000000u }, { 0x00000365u, 0x00000000u },  // 00000364
        { 0x00000366u, 0x00000000u }, { 0x00000367u, 0x00000000u },  // 00000366
        { 0x00000368u, 0x00000000u }, { 0x00000369u, 0x00000000u },  // 00000368
        { 0x0000036Au, 0x00000000u }, { 0x0000036Bu, 0x00000000u },  // 0000036A
        { 0x0000036Cu, 0x00000000u }, { 0x0000036Du, 0x00000000u },  // 0000036C
        { 0x0000036Eu, 0x00000000u }, { 0x0000036Fu, 0x00000000u }
    };

    const std::bitset<112> Combining_Diacritical_Marks300::my_Other_Alphabetic(std::string("0000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<112> Combining_Diacritical_Marks300::my_Diacritic(std::string("0000000000000111111000001111111101111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const std::bitset<112> Combining_Diacritical_Marks300::my_Other_Lowercase(std::string("0000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<112> Combining_Diacritical_Marks300::my_Grapheme_Link(std::string("0000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<112> Combining_Diacritical_Marks300::my_Other_Default_Ignorable_Code_Point(std::string("0000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<112> Combining_Diacritical_Marks300::my_Deprecated(std::string("0000000000000000000000000000000000000000000000110000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Combining_Diacritical_Marks300);
