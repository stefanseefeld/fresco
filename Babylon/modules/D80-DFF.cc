/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp D80-DFF.cc
 *
 * This source file is a part of the Fresco Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 28 Jan 2004 20:49:05 +0100.
 *
 * This plugin to libBabylon is free software; you can redistribute it
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
    class SinhalaD80 : public Babylon::Block
    {
      public:
        void clean() { };

        SinhalaD80() :
        my_first_letter(0xD80),
        my_last_letter(0xDFF)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000DD9, 0x00000DCA)] = 0x0DDA;
                my_composeMap[std::make_pair(0x00000DD9, 0x00000DCF)] = 0x0DDC;
                my_composeMap[std::make_pair(0x00000DD9, 0x00000DDF)] = 0x0DDE;
                my_composeMap[std::make_pair(0x00000DDC, 0x00000DCA)] = 0x0DDD;
            }
        }

        ~SinhalaD80() { }

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
        return "Sinhala";
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
            return Babylon::Gen_Cat(SinhalaD80::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(SinhalaD80::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return SinhalaD80::my_bidir[uc - my_first_letter];
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
            us[0] = SinhalaD80::my_decompStr[uc - my_first_letter][0];
            us[1] = SinhalaD80::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(SinhalaD80::my_lb[uc - my_first_letter]);
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
        SinhalaD80(const SinhalaD80 &) ; // no implementaion!

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
    }; // class SinhalaD80

    const std::bitset<128> SinhalaD80::my_is_defined(std::string("00000000000111000000000000000000111111110101111110000100011111110010111111111011111111111111111111111100011111111111111111101100"));

    const unsigned char SinhalaD80::my_cat[] =
    {
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Mc, CAT_Mc, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mn, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Po, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc
    };

    const unsigned char SinhalaD80::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 9, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props SinhalaD80::my_bidir[] =
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
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_L, 
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

    const UCS2 SinhalaD80::my_decompStr[][2] =
    {
        { 0x00000D80u, 0x00000000u }, { 0x00000D81u, 0x00000000u },  // 00000D80
        { 0x00000D82u, 0x00000000u }, { 0x00000D83u, 0x00000000u },  // 00000D82
        { 0x00000D84u, 0x00000000u }, { 0x00000D85u, 0x00000000u },  // 00000D84
        { 0x00000D86u, 0x00000000u }, { 0x00000D87u, 0x00000000u },  // 00000D86
        { 0x00000D88u, 0x00000000u }, { 0x00000D89u, 0x00000000u },  // 00000D88
        { 0x00000D8Au, 0x00000000u }, { 0x00000D8Bu, 0x00000000u },  // 00000D8A
        { 0x00000D8Cu, 0x00000000u }, { 0x00000D8Du, 0x00000000u },  // 00000D8C
        { 0x00000D8Eu, 0x00000000u }, { 0x00000D8Fu, 0x00000000u },  // 00000D8E
        { 0x00000D90u, 0x00000000u }, { 0x00000D91u, 0x00000000u },  // 00000D90
        { 0x00000D92u, 0x00000000u }, { 0x00000D93u, 0x00000000u },  // 00000D92
        { 0x00000D94u, 0x00000000u }, { 0x00000D95u, 0x00000000u },  // 00000D94
        { 0x00000D96u, 0x00000000u }, { 0x00000D97u, 0x00000000u },  // 00000D96
        { 0x00000D98u, 0x00000000u }, { 0x00000D99u, 0x00000000u },  // 00000D98
        { 0x00000D9Au, 0x00000000u }, { 0x00000D9Bu, 0x00000000u },  // 00000D9A
        { 0x00000D9Cu, 0x00000000u }, { 0x00000D9Du, 0x00000000u },  // 00000D9C
        { 0x00000D9Eu, 0x00000000u }, { 0x00000D9Fu, 0x00000000u },  // 00000D9E
        { 0x00000DA0u, 0x00000000u }, { 0x00000DA1u, 0x00000000u },  // 00000DA0
        { 0x00000DA2u, 0x00000000u }, { 0x00000DA3u, 0x00000000u },  // 00000DA2
        { 0x00000DA4u, 0x00000000u }, { 0x00000DA5u, 0x00000000u },  // 00000DA4
        { 0x00000DA6u, 0x00000000u }, { 0x00000DA7u, 0x00000000u },  // 00000DA6
        { 0x00000DA8u, 0x00000000u }, { 0x00000DA9u, 0x00000000u },  // 00000DA8
        { 0x00000DAAu, 0x00000000u }, { 0x00000DABu, 0x00000000u },  // 00000DAA
        { 0x00000DACu, 0x00000000u }, { 0x00000DADu, 0x00000000u },  // 00000DAC
        { 0x00000DAEu, 0x00000000u }, { 0x00000DAFu, 0x00000000u },  // 00000DAE
        { 0x00000DB0u, 0x00000000u }, { 0x00000DB1u, 0x00000000u },  // 00000DB0
        { 0x00000DB2u, 0x00000000u }, { 0x00000DB3u, 0x00000000u },  // 00000DB2
        { 0x00000DB4u, 0x00000000u }, { 0x00000DB5u, 0x00000000u },  // 00000DB4
        { 0x00000DB6u, 0x00000000u }, { 0x00000DB7u, 0x00000000u },  // 00000DB6
        { 0x00000DB8u, 0x00000000u }, { 0x00000DB9u, 0x00000000u },  // 00000DB8
        { 0x00000DBAu, 0x00000000u }, { 0x00000DBBu, 0x00000000u },  // 00000DBA
        { 0x00000DBCu, 0x00000000u }, { 0x00000DBDu, 0x00000000u },  // 00000DBC
        { 0x00000DBEu, 0x00000000u }, { 0x00000DBFu, 0x00000000u },  // 00000DBE
        { 0x00000DC0u, 0x00000000u }, { 0x00000DC1u, 0x00000000u },  // 00000DC0
        { 0x00000DC2u, 0x00000000u }, { 0x00000DC3u, 0x00000000u },  // 00000DC2
        { 0x00000DC4u, 0x00000000u }, { 0x00000DC5u, 0x00000000u },  // 00000DC4
        { 0x00000DC6u, 0x00000000u }, { 0x00000DC7u, 0x00000000u },  // 00000DC6
        { 0x00000DC8u, 0x00000000u }, { 0x00000DC9u, 0x00000000u },  // 00000DC8
        { 0x00000DCAu, 0x00000000u }, { 0x00000DCBu, 0x00000000u },  // 00000DCA
        { 0x00000DCCu, 0x00000000u }, { 0x00000DCDu, 0x00000000u },  // 00000DCC
        { 0x00000DCEu, 0x00000000u }, { 0x00000DCFu, 0x00000000u },  // 00000DCE
        { 0x00000DD0u, 0x00000000u }, { 0x00000DD1u, 0x00000000u },  // 00000DD0
        { 0x00000DD2u, 0x00000000u }, { 0x00000DD3u, 0x00000000u },  // 00000DD2
        { 0x00000DD4u, 0x00000000u }, { 0x00000DD5u, 0x00000000u },  // 00000DD4
        { 0x00000DD6u, 0x00000000u }, { 0x00000DD7u, 0x00000000u },  // 00000DD6
        { 0x00000DD8u, 0x00000000u }, { 0x00000DD9u, 0x00000000u },  // 00000DD8
        { 0x00000DD9u, 0x00000DCAu }, { 0x00000DDBu, 0x00000000u },  // 00000DDA
        { 0x00000DD9u, 0x00000DCFu }, { 0x00000DDCu, 0x00000DCAu },  // 00000DDC
        { 0x00000DD9u, 0x00000DDFu }, { 0x00000DDFu, 0x00000000u },  // 00000DDE
        { 0x00000DE0u, 0x00000000u }, { 0x00000DE1u, 0x00000000u },  // 00000DE0
        { 0x00000DE2u, 0x00000000u }, { 0x00000DE3u, 0x00000000u },  // 00000DE2
        { 0x00000DE4u, 0x00000000u }, { 0x00000DE5u, 0x00000000u },  // 00000DE4
        { 0x00000DE6u, 0x00000000u }, { 0x00000DE7u, 0x00000000u },  // 00000DE6
        { 0x00000DE8u, 0x00000000u }, { 0x00000DE9u, 0x00000000u },  // 00000DE8
        { 0x00000DEAu, 0x00000000u }, { 0x00000DEBu, 0x00000000u },  // 00000DEA
        { 0x00000DECu, 0x00000000u }, { 0x00000DEDu, 0x00000000u },  // 00000DEC
        { 0x00000DEEu, 0x00000000u }, { 0x00000DEFu, 0x00000000u },  // 00000DEE
        { 0x00000DF0u, 0x00000000u }, { 0x00000DF1u, 0x00000000u },  // 00000DF0
        { 0x00000DF2u, 0x00000000u }, { 0x00000DF3u, 0x00000000u },  // 00000DF2
        { 0x00000DF4u, 0x00000000u }, { 0x00000DF5u, 0x00000000u },  // 00000DF4
        { 0x00000DF6u, 0x00000000u }, { 0x00000DF7u, 0x00000000u },  // 00000DF6
        { 0x00000DF8u, 0x00000000u }, { 0x00000DF9u, 0x00000000u },  // 00000DF8
        { 0x00000DFAu, 0x00000000u }, { 0x00000DFBu, 0x00000000u },  // 00000DFA
        { 0x00000DFCu, 0x00000000u }, { 0x00000DFDu, 0x00000000u },  // 00000DFC
        { 0x00000DFEu, 0x00000000u }, { 0x00000DFFu, 0x00000000u }
    };

    const unsigned char SinhalaD80::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, 
        LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_CM, LB_CM, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
    };

    const std::bitset<128> SinhalaD80::my_Other_Alphabetic(std::string("00000000000011000000000000000000111111110101111110000000000000000000000000000000000000000000000000000000000000000000000000001100"));

    const std::bitset<128> SinhalaD80::my_Diacritic(std::string("00000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> SinhalaD80::my_Other_Grapheme_Extend(std::string("00000000000000000000000000000000100000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> SinhalaD80::my_Grapheme_Link(std::string("00000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::SinhalaD80);
