/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp 2190-21FF.cc
 *
 * This source file is a part of the Fresco Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 28 Jan 2004 20:49:09 +0100.
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
    class Arrows2190 : public Babylon::Block
    {
      public:
        void clean() { };

        Arrows2190() :
        my_first_letter(0x2190),
        my_last_letter(0x21FF)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00002190, 0x00000338)] = 0x219A;
                my_composeMap[std::make_pair(0x00002192, 0x00000338)] = 0x219B;
                my_composeMap[std::make_pair(0x00002194, 0x00000338)] = 0x21AE;
                my_composeMap[std::make_pair(0x000021D0, 0x00000338)] = 0x21CD;
                my_composeMap[std::make_pair(0x000021D2, 0x00000338)] = 0x21CF;
                my_composeMap[std::make_pair(0x000021D4, 0x00000338)] = 0x21CE;
            }
        }

        ~Arrows2190() { }

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
        return "Arrows";
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
            return Babylon::Gen_Cat(Arrows2190::my_cat[uc - my_first_letter]);
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
            return BIDIR_ON;
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
            us[0] = Arrows2190::my_decompStr[uc - my_first_letter][0];
            us[1] = Arrows2190::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Arrows2190::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Arrows2190::my_ea[uc - my_first_letter]);
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
            return 0;
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
        Arrows2190(const Arrows2190 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const unsigned char my_cat[112];
        static const UCS2 my_decompStr[112][2];
        static const unsigned char my_lb[112];
        static const unsigned char my_ea[112];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
    }; // class Arrows2190

    const unsigned char Arrows2190::my_cat[] =
    {
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_Sm, CAT_Sm, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_Sm, CAT_So, CAT_So, CAT_Sm, CAT_So, CAT_So, CAT_Sm, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_Sm, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_Sm, CAT_Sm, 
        CAT_So, CAT_So, CAT_Sm, CAT_So, CAT_Sm, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm
    };

    const UCS2 Arrows2190::my_decompStr[][2] =
    {
        { 0x00002190u, 0x00000000u }, { 0x00002191u, 0x00000000u },  // 00002190
        { 0x00002192u, 0x00000000u }, { 0x00002193u, 0x00000000u },  // 00002192
        { 0x00002194u, 0x00000000u }, { 0x00002195u, 0x00000000u },  // 00002194
        { 0x00002196u, 0x00000000u }, { 0x00002197u, 0x00000000u },  // 00002196
        { 0x00002198u, 0x00000000u }, { 0x00002199u, 0x00000000u },  // 00002198
        { 0x00002190u, 0x00000338u }, { 0x00002192u, 0x00000338u },  // 0000219A
        { 0x0000219Cu, 0x00000000u }, { 0x0000219Du, 0x00000000u },  // 0000219C
        { 0x0000219Eu, 0x00000000u }, { 0x0000219Fu, 0x00000000u },  // 0000219E
        { 0x000021A0u, 0x00000000u }, { 0x000021A1u, 0x00000000u },  // 000021A0
        { 0x000021A2u, 0x00000000u }, { 0x000021A3u, 0x00000000u },  // 000021A2
        { 0x000021A4u, 0x00000000u }, { 0x000021A5u, 0x00000000u },  // 000021A4
        { 0x000021A6u, 0x00000000u }, { 0x000021A7u, 0x00000000u },  // 000021A6
        { 0x000021A8u, 0x00000000u }, { 0x000021A9u, 0x00000000u },  // 000021A8
        { 0x000021AAu, 0x00000000u }, { 0x000021ABu, 0x00000000u },  // 000021AA
        { 0x000021ACu, 0x00000000u }, { 0x000021ADu, 0x00000000u },  // 000021AC
        { 0x00002194u, 0x00000338u }, { 0x000021AFu, 0x00000000u },  // 000021AE
        { 0x000021B0u, 0x00000000u }, { 0x000021B1u, 0x00000000u },  // 000021B0
        { 0x000021B2u, 0x00000000u }, { 0x000021B3u, 0x00000000u },  // 000021B2
        { 0x000021B4u, 0x00000000u }, { 0x000021B5u, 0x00000000u },  // 000021B4
        { 0x000021B6u, 0x00000000u }, { 0x000021B7u, 0x00000000u },  // 000021B6
        { 0x000021B8u, 0x00000000u }, { 0x000021B9u, 0x00000000u },  // 000021B8
        { 0x000021BAu, 0x00000000u }, { 0x000021BBu, 0x00000000u },  // 000021BA
        { 0x000021BCu, 0x00000000u }, { 0x000021BDu, 0x00000000u },  // 000021BC
        { 0x000021BEu, 0x00000000u }, { 0x000021BFu, 0x00000000u },  // 000021BE
        { 0x000021C0u, 0x00000000u }, { 0x000021C1u, 0x00000000u },  // 000021C0
        { 0x000021C2u, 0x00000000u }, { 0x000021C3u, 0x00000000u },  // 000021C2
        { 0x000021C4u, 0x00000000u }, { 0x000021C5u, 0x00000000u },  // 000021C4
        { 0x000021C6u, 0x00000000u }, { 0x000021C7u, 0x00000000u },  // 000021C6
        { 0x000021C8u, 0x00000000u }, { 0x000021C9u, 0x00000000u },  // 000021C8
        { 0x000021CAu, 0x00000000u }, { 0x000021CBu, 0x00000000u },  // 000021CA
        { 0x000021CCu, 0x00000000u }, { 0x000021D0u, 0x00000338u },  // 000021CC
        { 0x000021D4u, 0x00000338u }, { 0x000021D2u, 0x00000338u },  // 000021CE
        { 0x000021D0u, 0x00000000u }, { 0x000021D1u, 0x00000000u },  // 000021D0
        { 0x000021D2u, 0x00000000u }, { 0x000021D3u, 0x00000000u },  // 000021D2
        { 0x000021D4u, 0x00000000u }, { 0x000021D5u, 0x00000000u },  // 000021D4
        { 0x000021D6u, 0x00000000u }, { 0x000021D7u, 0x00000000u },  // 000021D6
        { 0x000021D8u, 0x00000000u }, { 0x000021D9u, 0x00000000u },  // 000021D8
        { 0x000021DAu, 0x00000000u }, { 0x000021DBu, 0x00000000u },  // 000021DA
        { 0x000021DCu, 0x00000000u }, { 0x000021DDu, 0x00000000u },  // 000021DC
        { 0x000021DEu, 0x00000000u }, { 0x000021DFu, 0x00000000u },  // 000021DE
        { 0x000021E0u, 0x00000000u }, { 0x000021E1u, 0x00000000u },  // 000021E0
        { 0x000021E2u, 0x00000000u }, { 0x000021E3u, 0x00000000u },  // 000021E2
        { 0x000021E4u, 0x00000000u }, { 0x000021E5u, 0x00000000u },  // 000021E4
        { 0x000021E6u, 0x00000000u }, { 0x000021E7u, 0x00000000u },  // 000021E6
        { 0x000021E8u, 0x00000000u }, { 0x000021E9u, 0x00000000u },  // 000021E8
        { 0x000021EAu, 0x00000000u }, { 0x000021EBu, 0x00000000u },  // 000021EA
        { 0x000021ECu, 0x00000000u }, { 0x000021EDu, 0x00000000u },  // 000021EC
        { 0x000021EEu, 0x00000000u }, { 0x000021EFu, 0x00000000u },  // 000021EE
        { 0x000021F0u, 0x00000000u }, { 0x000021F1u, 0x00000000u },  // 000021F0
        { 0x000021F2u, 0x00000000u }, { 0x000021F3u, 0x00000000u },  // 000021F2
        { 0x000021F4u, 0x00000000u }, { 0x000021F5u, 0x00000000u },  // 000021F4
        { 0x000021F6u, 0x00000000u }, { 0x000021F7u, 0x00000000u },  // 000021F6
        { 0x000021F8u, 0x00000000u }, { 0x000021F9u, 0x00000000u },  // 000021F8
        { 0x000021FAu, 0x00000000u }, { 0x000021FBu, 0x00000000u },  // 000021FA
        { 0x000021FCu, 0x00000000u }, { 0x000021FDu, 0x00000000u },  // 000021FC
        { 0x000021FEu, 0x00000000u }, { 0x000021FFu, 0x00000000u }
    };

    const unsigned char Arrows2190::my_lb[] =
    {
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AI, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const unsigned char Arrows2190::my_ea[] =
    {
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
    };

  }; // namespace
}; // namespace

dload(Babylon::Module::Arrows2190);
