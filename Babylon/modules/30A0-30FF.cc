/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp 30A0-30FF.cc
 *
 * This source file is a part of the Fresco Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 28 Jan 2004 20:49:12 +0100.
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
    class Katakana30A0 : public Babylon::Block
    {
      public:
        void clean() { };

        Katakana30A0() :
        my_first_letter(0x30A0),
        my_last_letter(0x30FF)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x000030A6, 0x00003099)] = 0x30F4;
                my_composeMap[std::make_pair(0x000030AB, 0x00003099)] = 0x30AC;
                my_composeMap[std::make_pair(0x000030AD, 0x00003099)] = 0x30AE;
                my_composeMap[std::make_pair(0x000030AF, 0x00003099)] = 0x30B0;
                my_composeMap[std::make_pair(0x000030B1, 0x00003099)] = 0x30B2;
                my_composeMap[std::make_pair(0x000030B3, 0x00003099)] = 0x30B4;
                my_composeMap[std::make_pair(0x000030B5, 0x00003099)] = 0x30B6;
                my_composeMap[std::make_pair(0x000030B7, 0x00003099)] = 0x30B8;
                my_composeMap[std::make_pair(0x000030B9, 0x00003099)] = 0x30BA;
                my_composeMap[std::make_pair(0x000030BB, 0x00003099)] = 0x30BC;
                my_composeMap[std::make_pair(0x000030BD, 0x00003099)] = 0x30BE;
                my_composeMap[std::make_pair(0x000030BF, 0x00003099)] = 0x30C0;
                my_composeMap[std::make_pair(0x000030C1, 0x00003099)] = 0x30C2;
                my_composeMap[std::make_pair(0x000030C4, 0x00003099)] = 0x30C5;
                my_composeMap[std::make_pair(0x000030C6, 0x00003099)] = 0x30C7;
                my_composeMap[std::make_pair(0x000030C8, 0x00003099)] = 0x30C9;
                my_composeMap[std::make_pair(0x000030CF, 0x00003099)] = 0x30D0;
                my_composeMap[std::make_pair(0x000030CF, 0x0000309A)] = 0x30D1;
                my_composeMap[std::make_pair(0x000030D2, 0x00003099)] = 0x30D3;
                my_composeMap[std::make_pair(0x000030D2, 0x0000309A)] = 0x30D4;
                my_composeMap[std::make_pair(0x000030D5, 0x00003099)] = 0x30D6;
                my_composeMap[std::make_pair(0x000030D5, 0x0000309A)] = 0x30D7;
                my_composeMap[std::make_pair(0x000030D8, 0x00003099)] = 0x30D9;
                my_composeMap[std::make_pair(0x000030D8, 0x0000309A)] = 0x30DA;
                my_composeMap[std::make_pair(0x000030DB, 0x00003099)] = 0x30DC;
                my_composeMap[std::make_pair(0x000030DB, 0x0000309A)] = 0x30DD;
                my_composeMap[std::make_pair(0x000030EF, 0x00003099)] = 0x30F7;
                my_composeMap[std::make_pair(0x000030F0, 0x00003099)] = 0x30F8;
                my_composeMap[std::make_pair(0x000030F1, 0x00003099)] = 0x30F9;
                my_composeMap[std::make_pair(0x000030F2, 0x00003099)] = 0x30FA;
                my_composeMap[std::make_pair(0x000030FD, 0x00003099)] = 0x30FE;
            }
        }

        ~Katakana30A0() { }

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
        return "Katakana";
    }

        bool is_defined(const UCS4 uc) const
        {
            return 1;
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
            return Babylon::Gen_Cat(Katakana30A0::my_cat[uc - my_first_letter]);
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
            return Katakana30A0::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Katakana30A0::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Katakana30A0::my_decompStr[uc - my_first_letter][0];
            us[1] = Katakana30A0::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Katakana30A0::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_W);
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
            return my_Hyphen.test(uc - my_first_letter);
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
        Katakana30A0(const Katakana30A0 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const unsigned char my_cat[96];
        static const Babylon::Bidir_Props my_bidir[96];
        static const unsigned char my_decomp[96];
        static const UCS4 my_decompStr[96][2];
        static const unsigned char my_lb[96];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<96> my_Hyphen;
        static const std::bitset<96> my_Diacritic;
        static const std::bitset<96> my_Extender;
    }; // class Katakana30A0

    const unsigned char Katakana30A0::my_cat[] =
    {
        CAT_Pd, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Pc, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lo
    };

    const Babylon::Bidir_Props Katakana30A0::my_bidir[] =
    {
        BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
    };

    const unsigned char Katakana30A0::my_decomp[] = {
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_VERTICAL
    };

    const UCS4 Katakana30A0::my_decompStr[][2] =
    {
        { 0x000030A0u, 0x00000000u }, { 0x000030A1u, 0x00000000u },  // 000030A0
        { 0x000030A2u, 0x00000000u }, { 0x000030A3u, 0x00000000u },  // 000030A2
        { 0x000030A4u, 0x00000000u }, { 0x000030A5u, 0x00000000u },  // 000030A4
        { 0x000030A6u, 0x00000000u }, { 0x000030A7u, 0x00000000u },  // 000030A6
        { 0x000030A8u, 0x00000000u }, { 0x000030A9u, 0x00000000u },  // 000030A8
        { 0x000030AAu, 0x00000000u }, { 0x000030ABu, 0x00000000u },  // 000030AA
        { 0x000030ABu, 0x00003099u }, { 0x000030ADu, 0x00000000u },  // 000030AC
        { 0x000030ADu, 0x00003099u }, { 0x000030AFu, 0x00000000u },  // 000030AE
        { 0x000030AFu, 0x00003099u }, { 0x000030B1u, 0x00000000u },  // 000030B0
        { 0x000030B1u, 0x00003099u }, { 0x000030B3u, 0x00000000u },  // 000030B2
        { 0x000030B3u, 0x00003099u }, { 0x000030B5u, 0x00000000u },  // 000030B4
        { 0x000030B5u, 0x00003099u }, { 0x000030B7u, 0x00000000u },  // 000030B6
        { 0x000030B7u, 0x00003099u }, { 0x000030B9u, 0x00000000u },  // 000030B8
        { 0x000030B9u, 0x00003099u }, { 0x000030BBu, 0x00000000u },  // 000030BA
        { 0x000030BBu, 0x00003099u }, { 0x000030BDu, 0x00000000u },  // 000030BC
        { 0x000030BDu, 0x00003099u }, { 0x000030BFu, 0x00000000u },  // 000030BE
        { 0x000030BFu, 0x00003099u }, { 0x000030C1u, 0x00000000u },  // 000030C0
        { 0x000030C1u, 0x00003099u }, { 0x000030C3u, 0x00000000u },  // 000030C2
        { 0x000030C4u, 0x00000000u }, { 0x000030C4u, 0x00003099u },  // 000030C4
        { 0x000030C6u, 0x00000000u }, { 0x000030C6u, 0x00003099u },  // 000030C6
        { 0x000030C8u, 0x00000000u }, { 0x000030C8u, 0x00003099u },  // 000030C8
        { 0x000030CAu, 0x00000000u }, { 0x000030CBu, 0x00000000u },  // 000030CA
        { 0x000030CCu, 0x00000000u }, { 0x000030CDu, 0x00000000u },  // 000030CC
        { 0x000030CEu, 0x00000000u }, { 0x000030CFu, 0x00000000u },  // 000030CE
        { 0x000030CFu, 0x00003099u }, { 0x000030CFu, 0x0000309Au },  // 000030D0
        { 0x000030D2u, 0x00000000u }, { 0x000030D2u, 0x00003099u },  // 000030D2
        { 0x000030D2u, 0x0000309Au }, { 0x000030D5u, 0x00000000u },  // 000030D4
        { 0x000030D5u, 0x00003099u }, { 0x000030D5u, 0x0000309Au },  // 000030D6
        { 0x000030D8u, 0x00000000u }, { 0x000030D8u, 0x00003099u },  // 000030D8
        { 0x000030D8u, 0x0000309Au }, { 0x000030DBu, 0x00000000u },  // 000030DA
        { 0x000030DBu, 0x00003099u }, { 0x000030DBu, 0x0000309Au },  // 000030DC
        { 0x000030DEu, 0x00000000u }, { 0x000030DFu, 0x00000000u },  // 000030DE
        { 0x000030E0u, 0x00000000u }, { 0x000030E1u, 0x00000000u },  // 000030E0
        { 0x000030E2u, 0x00000000u }, { 0x000030E3u, 0x00000000u },  // 000030E2
        { 0x000030E4u, 0x00000000u }, { 0x000030E5u, 0x00000000u },  // 000030E4
        { 0x000030E6u, 0x00000000u }, { 0x000030E7u, 0x00000000u },  // 000030E6
        { 0x000030E8u, 0x00000000u }, { 0x000030E9u, 0x00000000u },  // 000030E8
        { 0x000030EAu, 0x00000000u }, { 0x000030EBu, 0x00000000u },  // 000030EA
        { 0x000030ECu, 0x00000000u }, { 0x000030EDu, 0x00000000u },  // 000030EC
        { 0x000030EEu, 0x00000000u }, { 0x000030EFu, 0x00000000u },  // 000030EE
        { 0x000030F0u, 0x00000000u }, { 0x000030F1u, 0x00000000u },  // 000030F0
        { 0x000030F2u, 0x00000000u }, { 0x000030F3u, 0x00000000u },  // 000030F2
        { 0x000030A6u, 0x00003099u }, { 0x000030F5u, 0x00000000u },  // 000030F4
        { 0x000030F6u, 0x00000000u }, { 0x000030EFu, 0x00003099u },  // 000030F6
        { 0x000030F0u, 0x00003099u }, { 0x000030F1u, 0x00003099u },  // 000030F8
        { 0x000030F2u, 0x00003099u }, { 0x000030FBu, 0x00000000u },  // 000030FA
        { 0x000030FCu, 0x00000000u }, { 0x000030FDu, 0x00000000u },  // 000030FC
        { 0x000030FDu, 0x00003099u }, { 0x000030B3u, 0x000030C8u }
    };

    const unsigned char Katakana30A0::my_lb[] =
    {
        LB_NS, LB_NS, LB_ID, LB_NS, LB_ID, LB_NS, LB_ID, LB_NS, 
        LB_ID, LB_NS, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_NS, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_NS, LB_ID, LB_NS, LB_ID, LB_NS, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_NS, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_NS, LB_NS, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_NS, LB_NS, LB_NS, LB_NS, LB_ID
    };

    const std::bitset<96> Katakana30A0::my_Hyphen(std::string("000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<96> Katakana30A0::my_Diacritic(std::string("000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<96> Katakana30A0::my_Extender(std::string("011100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Katakana30A0);
