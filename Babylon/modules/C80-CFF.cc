/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp C80-CFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:41 +0200.
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
    class KannadaC80 : public Babylon::Block
    {
      public:
        void clean() { };

        KannadaC80() :
	    my_first_letter(0xC80),
	    my_last_letter(0xCFF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000CBF, 0x00000CD5)] = 0x0CC0;
                my_composeMap[std::make_pair(0x00000CC6, 0x00000CC2)] = 0x0CCA;
                my_composeMap[std::make_pair(0x00000CC6, 0x00000CD5)] = 0x0CC7;
                my_composeMap[std::make_pair(0x00000CC6, 0x00000CD6)] = 0x0CC8;
                my_composeMap[std::make_pair(0x00000CCA, 0x00000CD5)] = 0x0CCB;
            }
        }

        ~KannadaC80() { }

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
	    return "Kannada";
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
            case 0x0CE6u:
                return 0;
            case 0x0CE7u:
                return 1;
            case 0x0CE8u:
                return 2;
            case 0x0CE9u:
                return 3;
            case 0x0CEAu:
                return 4;
            case 0x0CEBu:
                return 5;
            case 0x0CECu:
                return 6;
            case 0x0CEDu:
                return 7;
            case 0x0CEEu:
                return 8;
            case 0x0CEFu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0CE6u:
            case 0x0CE7u:
            case 0x0CE8u:
            case 0x0CE9u:
            case 0x0CEAu:
            case 0x0CEBu:
            case 0x0CECu:
            case 0x0CEDu:
            case 0x0CEEu:
            case 0x0CEFu:
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
            case 0x0CE6u:
                return 0;
            case 0x0CE7u:
                return 1;
            case 0x0CE8u:
                return 2;
            case 0x0CE9u:
                return 3;
            case 0x0CEAu:
                return 4;
            case 0x0CEBu:
                return 5;
            case 0x0CECu:
                return 6;
            case 0x0CEDu:
                return 7;
            case 0x0CEEu:
                return 8;
            case 0x0CEFu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0CE6u:
            case 0x0CE7u:
            case 0x0CE8u:
            case 0x0CE9u:
            case 0x0CEAu:
            case 0x0CEBu:
            case 0x0CECu:
            case 0x0CEDu:
            case 0x0CEEu:
            case 0x0CEFu:
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
            case 0x0CE6u:
                return 0.000000;
            case 0x0CE7u:
                return 1.000000;
            case 0x0CE8u:
                return 2.000000;
            case 0x0CE9u:
                return 3.000000;
            case 0x0CEAu:
                return 4.000000;
            case 0x0CEBu:
                return 5.000000;
            case 0x0CECu:
                return 6.000000;
            case 0x0CEDu:
                return 7.000000;
            case 0x0CEEu:
                return 8.000000;
            case 0x0CEFu:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0CE6u:
            case 0x0CE7u:
            case 0x0CE8u:
            case 0x0CE9u:
            case 0x0CEAu:
            case 0x0CEBu:
            case 0x0CECu:
            case 0x0CEDu:
            case 0x0CEEu:
            case 0x0CEFu:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(KannadaC80::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(KannadaC80::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return KannadaC80::my_bidir[uc - my_first_letter];
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
            us[0] = KannadaC80::my_decompStr[uc - my_first_letter][0];
            us[1] = KannadaC80::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(KannadaC80::my_lb[uc - my_first_letter]);
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
        KannadaC80(const KannadaC80 &) ; // no implementaion!

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
        static const std::bitset<128> my_Other_Alphabetic;
        static const std::bitset<128> my_Diacritic;
        static const std::bitset<128> my_Other_Grapheme_Extend;
        static const std::bitset<128> my_Grapheme_Link;
    }; // class KannadaC80

    const std::bitset<128> KannadaC80::my_is_defined(std::string("00000000000000001111111111000011010000000110000000111101110111111111001111101111111111011111111111111111111111011101111111101100"));

    const unsigned char KannadaC80::my_cat[] =
    {
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Lo, CAT_Mc, CAT_Mn, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Lo, CAT_Mc, 
        CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc
    };

    const unsigned char KannadaC80::my_comb_cl[] = {
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

    const Babylon::Bidir_Props KannadaC80::my_bidir[] =
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
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
    };

    const UCS2 KannadaC80::my_decompStr[][2] =
    {
        { 0x00000C80u, 0x00000000u }, { 0x00000C81u, 0x00000000u },  // 00000C80
        { 0x00000C82u, 0x00000000u }, { 0x00000C83u, 0x00000000u },  // 00000C82
        { 0x00000C84u, 0x00000000u }, { 0x00000C85u, 0x00000000u },  // 00000C84
        { 0x00000C86u, 0x00000000u }, { 0x00000C87u, 0x00000000u },  // 00000C86
        { 0x00000C88u, 0x00000000u }, { 0x00000C89u, 0x00000000u },  // 00000C88
        { 0x00000C8Au, 0x00000000u }, { 0x00000C8Bu, 0x00000000u },  // 00000C8A
        { 0x00000C8Cu, 0x00000000u }, { 0x00000C8Du, 0x00000000u },  // 00000C8C
        { 0x00000C8Eu, 0x00000000u }, { 0x00000C8Fu, 0x00000000u },  // 00000C8E
        { 0x00000C90u, 0x00000000u }, { 0x00000C91u, 0x00000000u },  // 00000C90
        { 0x00000C92u, 0x00000000u }, { 0x00000C93u, 0x00000000u },  // 00000C92
        { 0x00000C94u, 0x00000000u }, { 0x00000C95u, 0x00000000u },  // 00000C94
        { 0x00000C96u, 0x00000000u }, { 0x00000C97u, 0x00000000u },  // 00000C96
        { 0x00000C98u, 0x00000000u }, { 0x00000C99u, 0x00000000u },  // 00000C98
        { 0x00000C9Au, 0x00000000u }, { 0x00000C9Bu, 0x00000000u },  // 00000C9A
        { 0x00000C9Cu, 0x00000000u }, { 0x00000C9Du, 0x00000000u },  // 00000C9C
        { 0x00000C9Eu, 0x00000000u }, { 0x00000C9Fu, 0x00000000u },  // 00000C9E
        { 0x00000CA0u, 0x00000000u }, { 0x00000CA1u, 0x00000000u },  // 00000CA0
        { 0x00000CA2u, 0x00000000u }, { 0x00000CA3u, 0x00000000u },  // 00000CA2
        { 0x00000CA4u, 0x00000000u }, { 0x00000CA5u, 0x00000000u },  // 00000CA4
        { 0x00000CA6u, 0x00000000u }, { 0x00000CA7u, 0x00000000u },  // 00000CA6
        { 0x00000CA8u, 0x00000000u }, { 0x00000CA9u, 0x00000000u },  // 00000CA8
        { 0x00000CAAu, 0x00000000u }, { 0x00000CABu, 0x00000000u },  // 00000CAA
        { 0x00000CACu, 0x00000000u }, { 0x00000CADu, 0x00000000u },  // 00000CAC
        { 0x00000CAEu, 0x00000000u }, { 0x00000CAFu, 0x00000000u },  // 00000CAE
        { 0x00000CB0u, 0x00000000u }, { 0x00000CB1u, 0x00000000u },  // 00000CB0
        { 0x00000CB2u, 0x00000000u }, { 0x00000CB3u, 0x00000000u },  // 00000CB2
        { 0x00000CB4u, 0x00000000u }, { 0x00000CB5u, 0x00000000u },  // 00000CB4
        { 0x00000CB6u, 0x00000000u }, { 0x00000CB7u, 0x00000000u },  // 00000CB6
        { 0x00000CB8u, 0x00000000u }, { 0x00000CB9u, 0x00000000u },  // 00000CB8
        { 0x00000CBAu, 0x00000000u }, { 0x00000CBBu, 0x00000000u },  // 00000CBA
        { 0x00000CBCu, 0x00000000u }, { 0x00000CBDu, 0x00000000u },  // 00000CBC
        { 0x00000CBEu, 0x00000000u }, { 0x00000CBFu, 0x00000000u },  // 00000CBE
        { 0x00000CBFu, 0x00000CD5u }, { 0x00000CC1u, 0x00000000u },  // 00000CC0
        { 0x00000CC2u, 0x00000000u }, { 0x00000CC3u, 0x00000000u },  // 00000CC2
        { 0x00000CC4u, 0x00000000u }, { 0x00000CC5u, 0x00000000u },  // 00000CC4
        { 0x00000CC6u, 0x00000000u }, { 0x00000CC6u, 0x00000CD5u },  // 00000CC6
        { 0x00000CC6u, 0x00000CD6u }, { 0x00000CC9u, 0x00000000u },  // 00000CC8
        { 0x00000CC6u, 0x00000CC2u }, { 0x00000CCAu, 0x00000CD5u },  // 00000CCA
        { 0x00000CCCu, 0x00000000u }, { 0x00000CCDu, 0x00000000u },  // 00000CCC
        { 0x00000CCEu, 0x00000000u }, { 0x00000CCFu, 0x00000000u },  // 00000CCE
        { 0x00000CD0u, 0x00000000u }, { 0x00000CD1u, 0x00000000u },  // 00000CD0
        { 0x00000CD2u, 0x00000000u }, { 0x00000CD3u, 0x00000000u },  // 00000CD2
        { 0x00000CD4u, 0x00000000u }, { 0x00000CD5u, 0x00000000u },  // 00000CD4
        { 0x00000CD6u, 0x00000000u }, { 0x00000CD7u, 0x00000000u },  // 00000CD6
        { 0x00000CD8u, 0x00000000u }, { 0x00000CD9u, 0x00000000u },  // 00000CD8
        { 0x00000CDAu, 0x00000000u }, { 0x00000CDBu, 0x00000000u },  // 00000CDA
        { 0x00000CDCu, 0x00000000u }, { 0x00000CDDu, 0x00000000u },  // 00000CDC
        { 0x00000CDEu, 0x00000000u }, { 0x00000CDFu, 0x00000000u },  // 00000CDE
        { 0x00000CE0u, 0x00000000u }, { 0x00000CE1u, 0x00000000u },  // 00000CE0
        { 0x00000CE2u, 0x00000000u }, { 0x00000CE3u, 0x00000000u },  // 00000CE2
        { 0x00000CE4u, 0x00000000u }, { 0x00000CE5u, 0x00000000u },  // 00000CE4
        { 0x00000CE6u, 0x00000000u }, { 0x00000CE7u, 0x00000000u },  // 00000CE6
        { 0x00000CE8u, 0x00000000u }, { 0x00000CE9u, 0x00000000u },  // 00000CE8
        { 0x00000CEAu, 0x00000000u }, { 0x00000CEBu, 0x00000000u },  // 00000CEA
        { 0x00000CECu, 0x00000000u }, { 0x00000CEDu, 0x00000000u },  // 00000CEC
        { 0x00000CEEu, 0x00000000u }, { 0x00000CEFu, 0x00000000u },  // 00000CEE
        { 0x00000CF0u, 0x00000000u }, { 0x00000CF1u, 0x00000000u },  // 00000CF0
        { 0x00000CF2u, 0x00000000u }, { 0x00000CF3u, 0x00000000u },  // 00000CF2
        { 0x00000CF4u, 0x00000000u }, { 0x00000CF5u, 0x00000000u },  // 00000CF4
        { 0x00000CF6u, 0x00000000u }, { 0x00000CF7u, 0x00000000u },  // 00000CF6
        { 0x00000CF8u, 0x00000000u }, { 0x00000CF9u, 0x00000000u },  // 00000CF8
        { 0x00000CFAu, 0x00000000u }, { 0x00000CFBu, 0x00000000u },  // 00000CFA
        { 0x00000CFCu, 0x00000000u }, { 0x00000CFDu, 0x00000000u },  // 00000CFC
        { 0x00000CFEu, 0x00000000u }, { 0x00000CFFu, 0x00000000u }
    };

    const unsigned char KannadaC80::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
    };

    const std::bitset<128> KannadaC80::my_Other_Alphabetic(std::string("00000000000000000000000000000000000000000110000000011101110111111100000000000000000000000000000000000000000000000000000000001100"));

    const std::bitset<128> KannadaC80::my_Diacritic(std::string("00000000000000000000000000000000000000000000000000100000000000000001000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> KannadaC80::my_Other_Grapheme_Extend(std::string("00000000000000000000000000000000000000000110000000000000000001000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> KannadaC80::my_Grapheme_Link(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::KannadaC80);
