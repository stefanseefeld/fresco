/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp B80-BFF.cc
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
    class TamilB80 : public Babylon::Block
    {
      public:
        void clean() { };

        TamilB80() :
        my_first_letter(0xB80),
        my_last_letter(0xBFF)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000B92, 0x00000BD7)] = 0x0B94;
                my_composeMap[std::make_pair(0x00000BC6, 0x00000BBE)] = 0x0BCA;
                my_composeMap[std::make_pair(0x00000BC6, 0x00000BD7)] = 0x0BCC;
                my_composeMap[std::make_pair(0x00000BC7, 0x00000BBE)] = 0x0BCB;
            }
        }

        ~TamilB80() { }

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
        return "Tamil";
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
            case 0x0BE7u:
                return 1;
            case 0x0BE8u:
                return 2;
            case 0x0BE9u:
                return 3;
            case 0x0BEAu:
                return 4;
            case 0x0BEBu:
                return 5;
            case 0x0BECu:
                return 6;
            case 0x0BEDu:
                return 7;
            case 0x0BEEu:
                return 8;
            case 0x0BEFu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0BE7u:
            case 0x0BE8u:
            case 0x0BE9u:
            case 0x0BEAu:
            case 0x0BEBu:
            case 0x0BECu:
            case 0x0BEDu:
            case 0x0BEEu:
            case 0x0BEFu:
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
            case 0x0BE7u:
                return 1;
            case 0x0BE8u:
                return 2;
            case 0x0BE9u:
                return 3;
            case 0x0BEAu:
                return 4;
            case 0x0BEBu:
                return 5;
            case 0x0BECu:
                return 6;
            case 0x0BEDu:
                return 7;
            case 0x0BEEu:
                return 8;
            case 0x0BEFu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0BE7u:
            case 0x0BE8u:
            case 0x0BE9u:
            case 0x0BEAu:
            case 0x0BEBu:
            case 0x0BECu:
            case 0x0BEDu:
            case 0x0BEEu:
            case 0x0BEFu:
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
            case 0x0BE7u:
                return 1.000000;
            case 0x0BE8u:
                return 2.000000;
            case 0x0BE9u:
                return 3.000000;
            case 0x0BEAu:
                return 4.000000;
            case 0x0BEBu:
                return 5.000000;
            case 0x0BECu:
                return 6.000000;
            case 0x0BEDu:
                return 7.000000;
            case 0x0BEEu:
                return 8.000000;
            case 0x0BEFu:
                return 9.000000;
            case 0x0BF0u:
                return 10.000000;
            case 0x0BF1u:
                return 100.000000;
            case 0x0BF2u:
                return 1000.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0BE7u:
            case 0x0BE8u:
            case 0x0BE9u:
            case 0x0BEAu:
            case 0x0BEBu:
            case 0x0BECu:
            case 0x0BEDu:
            case 0x0BEEu:
            case 0x0BEFu:
            case 0x0BF0u:
            case 0x0BF1u:
            case 0x0BF2u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(TamilB80::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(TamilB80::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return TamilB80::my_bidir[uc - my_first_letter];
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
            us[0] = TamilB80::my_decompStr[uc - my_first_letter][0];
            us[1] = TamilB80::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(TamilB80::my_lb[uc - my_first_letter]);
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
        TamilB80(const TamilB80 &) ; // no implementaion!

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
    }; // class TamilB80

    const std::bitset<128> TamilB80::my_is_defined(std::string("00000111111111111111111110000000000000001000000000111101110001111100001110111111110001110001100011010110001111011100011111101100"));

    const unsigned char TamilB80::my_cat[] =
    {
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
        CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_No, CAT_No, CAT_No, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_Sc, CAT_So, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
    };

    const unsigned char TamilB80::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 9, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props TamilB80::my_bidir[] =
    {
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ET, BIDIR_ON, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM
    };

    const UCS2 TamilB80::my_decompStr[][2] =
    {
        { 0x00000B80u, 0x00000000u }, { 0x00000B81u, 0x00000000u },  // 00000B80
        { 0x00000B82u, 0x00000000u }, { 0x00000B83u, 0x00000000u },  // 00000B82
        { 0x00000B84u, 0x00000000u }, { 0x00000B85u, 0x00000000u },  // 00000B84
        { 0x00000B86u, 0x00000000u }, { 0x00000B87u, 0x00000000u },  // 00000B86
        { 0x00000B88u, 0x00000000u }, { 0x00000B89u, 0x00000000u },  // 00000B88
        { 0x00000B8Au, 0x00000000u }, { 0x00000B8Bu, 0x00000000u },  // 00000B8A
        { 0x00000B8Cu, 0x00000000u }, { 0x00000B8Du, 0x00000000u },  // 00000B8C
        { 0x00000B8Eu, 0x00000000u }, { 0x00000B8Fu, 0x00000000u },  // 00000B8E
        { 0x00000B90u, 0x00000000u }, { 0x00000B91u, 0x00000000u },  // 00000B90
        { 0x00000B92u, 0x00000000u }, { 0x00000B93u, 0x00000000u },  // 00000B92
        { 0x00000B92u, 0x00000BD7u }, { 0x00000B95u, 0x00000000u },  // 00000B94
        { 0x00000B96u, 0x00000000u }, { 0x00000B97u, 0x00000000u },  // 00000B96
        { 0x00000B98u, 0x00000000u }, { 0x00000B99u, 0x00000000u },  // 00000B98
        { 0x00000B9Au, 0x00000000u }, { 0x00000B9Bu, 0x00000000u },  // 00000B9A
        { 0x00000B9Cu, 0x00000000u }, { 0x00000B9Du, 0x00000000u },  // 00000B9C
        { 0x00000B9Eu, 0x00000000u }, { 0x00000B9Fu, 0x00000000u },  // 00000B9E
        { 0x00000BA0u, 0x00000000u }, { 0x00000BA1u, 0x00000000u },  // 00000BA0
        { 0x00000BA2u, 0x00000000u }, { 0x00000BA3u, 0x00000000u },  // 00000BA2
        { 0x00000BA4u, 0x00000000u }, { 0x00000BA5u, 0x00000000u },  // 00000BA4
        { 0x00000BA6u, 0x00000000u }, { 0x00000BA7u, 0x00000000u },  // 00000BA6
        { 0x00000BA8u, 0x00000000u }, { 0x00000BA9u, 0x00000000u },  // 00000BA8
        { 0x00000BAAu, 0x00000000u }, { 0x00000BABu, 0x00000000u },  // 00000BAA
        { 0x00000BACu, 0x00000000u }, { 0x00000BADu, 0x00000000u },  // 00000BAC
        { 0x00000BAEu, 0x00000000u }, { 0x00000BAFu, 0x00000000u },  // 00000BAE
        { 0x00000BB0u, 0x00000000u }, { 0x00000BB1u, 0x00000000u },  // 00000BB0
        { 0x00000BB2u, 0x00000000u }, { 0x00000BB3u, 0x00000000u },  // 00000BB2
        { 0x00000BB4u, 0x00000000u }, { 0x00000BB5u, 0x00000000u },  // 00000BB4
        { 0x00000BB6u, 0x00000000u }, { 0x00000BB7u, 0x00000000u },  // 00000BB6
        { 0x00000BB8u, 0x00000000u }, { 0x00000BB9u, 0x00000000u },  // 00000BB8
        { 0x00000BBAu, 0x00000000u }, { 0x00000BBBu, 0x00000000u },  // 00000BBA
        { 0x00000BBCu, 0x00000000u }, { 0x00000BBDu, 0x00000000u },  // 00000BBC
        { 0x00000BBEu, 0x00000000u }, { 0x00000BBFu, 0x00000000u },  // 00000BBE
        { 0x00000BC0u, 0x00000000u }, { 0x00000BC1u, 0x00000000u },  // 00000BC0
        { 0x00000BC2u, 0x00000000u }, { 0x00000BC3u, 0x00000000u },  // 00000BC2
        { 0x00000BC4u, 0x00000000u }, { 0x00000BC5u, 0x00000000u },  // 00000BC4
        { 0x00000BC6u, 0x00000000u }, { 0x00000BC7u, 0x00000000u },  // 00000BC6
        { 0x00000BC8u, 0x00000000u }, { 0x00000BC9u, 0x00000000u },  // 00000BC8
        { 0x00000BC6u, 0x00000BBEu }, { 0x00000BC7u, 0x00000BBEu },  // 00000BCA
        { 0x00000BC6u, 0x00000BD7u }, { 0x00000BCDu, 0x00000000u },  // 00000BCC
        { 0x00000BCEu, 0x00000000u }, { 0x00000BCFu, 0x00000000u },  // 00000BCE
        { 0x00000BD0u, 0x00000000u }, { 0x00000BD1u, 0x00000000u },  // 00000BD0
        { 0x00000BD2u, 0x00000000u }, { 0x00000BD3u, 0x00000000u },  // 00000BD2
        { 0x00000BD4u, 0x00000000u }, { 0x00000BD5u, 0x00000000u },  // 00000BD4
        { 0x00000BD6u, 0x00000000u }, { 0x00000BD7u, 0x00000000u },  // 00000BD6
        { 0x00000BD8u, 0x00000000u }, { 0x00000BD9u, 0x00000000u },  // 00000BD8
        { 0x00000BDAu, 0x00000000u }, { 0x00000BDBu, 0x00000000u },  // 00000BDA
        { 0x00000BDCu, 0x00000000u }, { 0x00000BDDu, 0x00000000u },  // 00000BDC
        { 0x00000BDEu, 0x00000000u }, { 0x00000BDFu, 0x00000000u },  // 00000BDE
        { 0x00000BE0u, 0x00000000u }, { 0x00000BE1u, 0x00000000u },  // 00000BE0
        { 0x00000BE2u, 0x00000000u }, { 0x00000BE3u, 0x00000000u },  // 00000BE2
        { 0x00000BE4u, 0x00000000u }, { 0x00000BE5u, 0x00000000u },  // 00000BE4
        { 0x00000BE6u, 0x00000000u }, { 0x00000BE7u, 0x00000000u },  // 00000BE6
        { 0x00000BE8u, 0x00000000u }, { 0x00000BE9u, 0x00000000u },  // 00000BE8
        { 0x00000BEAu, 0x00000000u }, { 0x00000BEBu, 0x00000000u },  // 00000BEA
        { 0x00000BECu, 0x00000000u }, { 0x00000BEDu, 0x00000000u },  // 00000BEC
        { 0x00000BEEu, 0x00000000u }, { 0x00000BEFu, 0x00000000u },  // 00000BEE
        { 0x00000BF0u, 0x00000000u }, { 0x00000BF1u, 0x00000000u },  // 00000BF0
        { 0x00000BF2u, 0x00000000u }, { 0x00000BF3u, 0x00000000u },  // 00000BF2
        { 0x00000BF4u, 0x00000000u }, { 0x00000BF5u, 0x00000000u },  // 00000BF4
        { 0x00000BF6u, 0x00000000u }, { 0x00000BF7u, 0x00000000u },  // 00000BF6
        { 0x00000BF8u, 0x00000000u }, { 0x00000BF9u, 0x00000000u },  // 00000BF8
        { 0x00000BFAu, 0x00000000u }, { 0x00000BFBu, 0x00000000u },  // 00000BFA
        { 0x00000BFCu, 0x00000000u }, { 0x00000BFDu, 0x00000000u },  // 00000BFC
        { 0x00000BFEu, 0x00000000u }, { 0x00000BFFu, 0x00000000u }
    };

    const unsigned char TamilB80::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, 
        LB_CM, LB_AL, LB_AL, LB_CM, LB_AL, LB_CM, LB_AL, LB_AL, 
        LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, 
        LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_PR, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
    };

    const std::bitset<128> TamilB80::my_Other_Alphabetic(std::string("00000000000000000000000000000000000000001000000000011101110001111100000000000000000000000000000000000000000000000000000000000100"));

    const std::bitset<128> TamilB80::my_Diacritic(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> TamilB80::my_Other_Grapheme_Extend(std::string("00000000000000000000000000000000000000001000000000000000000000000100000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> TamilB80::my_Grapheme_Link(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::TamilB80);
