/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 2200-22FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:45 +0200.
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
    class Mathematical_Operators2200 : public Babylon::Block
    {
      public:
        void clean() { };

        Mathematical_Operators2200() :
        my_first_letter(0x2200),
        my_last_letter(0x22FF)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00002203, 0x00000338)] = 0x2204;
                my_composeMap[std::make_pair(0x00002208, 0x00000338)] = 0x2209;
                my_composeMap[std::make_pair(0x0000220B, 0x00000338)] = 0x220C;
                my_composeMap[std::make_pair(0x00002223, 0x00000338)] = 0x2224;
                my_composeMap[std::make_pair(0x00002225, 0x00000338)] = 0x2226;
                my_composeMap[std::make_pair(0x0000223C, 0x00000338)] = 0x2241;
                my_composeMap[std::make_pair(0x00002243, 0x00000338)] = 0x2244;
                my_composeMap[std::make_pair(0x00002245, 0x00000338)] = 0x2247;
                my_composeMap[std::make_pair(0x00002248, 0x00000338)] = 0x2249;
                my_composeMap[std::make_pair(0x0000224D, 0x00000338)] = 0x226D;
                my_composeMap[std::make_pair(0x00002261, 0x00000338)] = 0x2262;
                my_composeMap[std::make_pair(0x00002264, 0x00000338)] = 0x2270;
                my_composeMap[std::make_pair(0x00002265, 0x00000338)] = 0x2271;
                my_composeMap[std::make_pair(0x00002272, 0x00000338)] = 0x2274;
                my_composeMap[std::make_pair(0x00002273, 0x00000338)] = 0x2275;
                my_composeMap[std::make_pair(0x00002276, 0x00000338)] = 0x2278;
                my_composeMap[std::make_pair(0x00002277, 0x00000338)] = 0x2279;
                my_composeMap[std::make_pair(0x0000227A, 0x00000338)] = 0x2280;
                my_composeMap[std::make_pair(0x0000227B, 0x00000338)] = 0x2281;
                my_composeMap[std::make_pair(0x0000227C, 0x00000338)] = 0x22E0;
                my_composeMap[std::make_pair(0x0000227D, 0x00000338)] = 0x22E1;
                my_composeMap[std::make_pair(0x00002282, 0x00000338)] = 0x2284;
                my_composeMap[std::make_pair(0x00002283, 0x00000338)] = 0x2285;
                my_composeMap[std::make_pair(0x00002286, 0x00000338)] = 0x2288;
                my_composeMap[std::make_pair(0x00002287, 0x00000338)] = 0x2289;
                my_composeMap[std::make_pair(0x00002291, 0x00000338)] = 0x22E2;
                my_composeMap[std::make_pair(0x00002292, 0x00000338)] = 0x22E3;
                my_composeMap[std::make_pair(0x000022A2, 0x00000338)] = 0x22AC;
                my_composeMap[std::make_pair(0x000022A8, 0x00000338)] = 0x22AD;
                my_composeMap[std::make_pair(0x000022A9, 0x00000338)] = 0x22AE;
                my_composeMap[std::make_pair(0x000022AB, 0x00000338)] = 0x22AF;
                my_composeMap[std::make_pair(0x000022B2, 0x00000338)] = 0x22EA;
                my_composeMap[std::make_pair(0x000022B3, 0x00000338)] = 0x22EB;
                my_composeMap[std::make_pair(0x000022B4, 0x00000338)] = 0x22EC;
                my_composeMap[std::make_pair(0x000022B5, 0x00000338)] = 0x22ED;
            }
        }

        ~Mathematical_Operators2200() { }

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
        return "Mathematical Operators";
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
            return Babylon::Gen_Cat(CAT_Sm);
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
            return Mathematical_Operators2200::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Mathematical_Operators2200::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Mathematical_Operators2200::my_decompStr[uc - my_first_letter][0];
            us[1] = Mathematical_Operators2200::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

            case 0x222D:
                us.resize(3);
                us[2u] = 0x222Bu;
                break;

            case 0x2230:
                us.resize(3);
                us[2u] = 0x222Eu;
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
            return Babylon::Line_Break(Mathematical_Operators2200::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Mathematical_Operators2200::my_ea[uc - my_first_letter]);
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
            return my_Dash.test(uc - my_first_letter);
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
        Mathematical_Operators2200(const Mathematical_Operators2200 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const Babylon::Bidir_Props my_bidir[256];
        static const unsigned char my_decomp[256];
        static const UCS2 my_decompStr[256][2];
        static const std::bitset<256> my_mirror;
        static const unsigned char my_lb[256];
        static const unsigned char my_ea[256];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<256> my_Dash;
    }; // class Mathematical_Operators2200

    const Babylon::Bidir_Props Mathematical_Operators2200::my_bidir[] =
    {
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ET, BIDIR_ET, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
    };

    const unsigned char Mathematical_Operators2200::my_decomp[] = {
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
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_COMPAT, 
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Mathematical_Operators2200::my_decompStr[][2] =
    {
        { 0x00002200u, 0x00000000u }, { 0x00002201u, 0x00000000u },  // 00002200
        { 0x00002202u, 0x00000000u }, { 0x00002203u, 0x00000000u },  // 00002202
        { 0x00002203u, 0x00000338u }, { 0x00002205u, 0x00000000u },  // 00002204
        { 0x00002206u, 0x00000000u }, { 0x00002207u, 0x00000000u },  // 00002206
        { 0x00002208u, 0x00000000u }, { 0x00002208u, 0x00000338u },  // 00002208
        { 0x0000220Au, 0x00000000u }, { 0x0000220Bu, 0x00000000u },  // 0000220A
        { 0x0000220Bu, 0x00000338u }, { 0x0000220Du, 0x00000000u },  // 0000220C
        { 0x0000220Eu, 0x00000000u }, { 0x0000220Fu, 0x00000000u },  // 0000220E
        { 0x00002210u, 0x00000000u }, { 0x00002211u, 0x00000000u },  // 00002210
        { 0x00002212u, 0x00000000u }, { 0x00002213u, 0x00000000u },  // 00002212
        { 0x00002214u, 0x00000000u }, { 0x00002215u, 0x00000000u },  // 00002214
        { 0x00002216u, 0x00000000u }, { 0x00002217u, 0x00000000u },  // 00002216
        { 0x00002218u, 0x00000000u }, { 0x00002219u, 0x00000000u },  // 00002218
        { 0x0000221Au, 0x00000000u }, { 0x0000221Bu, 0x00000000u },  // 0000221A
        { 0x0000221Cu, 0x00000000u }, { 0x0000221Du, 0x00000000u },  // 0000221C
        { 0x0000221Eu, 0x00000000u }, { 0x0000221Fu, 0x00000000u },  // 0000221E
        { 0x00002220u, 0x00000000u }, { 0x00002221u, 0x00000000u },  // 00002220
        { 0x00002222u, 0x00000000u }, { 0x00002223u, 0x00000000u },  // 00002222
        { 0x00002223u, 0x00000338u }, { 0x00002225u, 0x00000000u },  // 00002224
        { 0x00002225u, 0x00000338u }, { 0x00002227u, 0x00000000u },  // 00002226
        { 0x00002228u, 0x00000000u }, { 0x00002229u, 0x00000000u },  // 00002228
        { 0x0000222Au, 0x00000000u }, { 0x0000222Bu, 0x00000000u },  // 0000222A
        { 0x0000222Bu, 0x0000222Bu }, { 0x0000222Bu, 0x0000222Bu },  // 0000222C
        { 0x0000222Eu, 0x00000000u }, { 0x0000222Eu, 0x0000222Eu },  // 0000222E
        { 0x0000222Eu, 0x0000222Eu }, { 0x00002231u, 0x00000000u },  // 00002230
        { 0x00002232u, 0x00000000u }, { 0x00002233u, 0x00000000u },  // 00002232
        { 0x00002234u, 0x00000000u }, { 0x00002235u, 0x00000000u },  // 00002234
        { 0x00002236u, 0x00000000u }, { 0x00002237u, 0x00000000u },  // 00002236
        { 0x00002238u, 0x00000000u }, { 0x00002239u, 0x00000000u },  // 00002238
        { 0x0000223Au, 0x00000000u }, { 0x0000223Bu, 0x00000000u },  // 0000223A
        { 0x0000223Cu, 0x00000000u }, { 0x0000223Du, 0x00000000u },  // 0000223C
        { 0x0000223Eu, 0x00000000u }, { 0x0000223Fu, 0x00000000u },  // 0000223E
        { 0x00002240u, 0x00000000u }, { 0x0000223Cu, 0x00000338u },  // 00002240
        { 0x00002242u, 0x00000000u }, { 0x00002243u, 0x00000000u },  // 00002242
        { 0x00002243u, 0x00000338u }, { 0x00002245u, 0x00000000u },  // 00002244
        { 0x00002246u, 0x00000000u }, { 0x00002245u, 0x00000338u },  // 00002246
        { 0x00002248u, 0x00000000u }, { 0x00002248u, 0x00000338u },  // 00002248
        { 0x0000224Au, 0x00000000u }, { 0x0000224Bu, 0x00000000u },  // 0000224A
        { 0x0000224Cu, 0x00000000u }, { 0x0000224Du, 0x00000000u },  // 0000224C
        { 0x0000224Eu, 0x00000000u }, { 0x0000224Fu, 0x00000000u },  // 0000224E
        { 0x00002250u, 0x00000000u }, { 0x00002251u, 0x00000000u },  // 00002250
        { 0x00002252u, 0x00000000u }, { 0x00002253u, 0x00000000u },  // 00002252
        { 0x00002254u, 0x00000000u }, { 0x00002255u, 0x00000000u },  // 00002254
        { 0x00002256u, 0x00000000u }, { 0x00002257u, 0x00000000u },  // 00002256
        { 0x00002258u, 0x00000000u }, { 0x00002259u, 0x00000000u },  // 00002258
        { 0x0000225Au, 0x00000000u }, { 0x0000225Bu, 0x00000000u },  // 0000225A
        { 0x0000225Cu, 0x00000000u }, { 0x0000225Du, 0x00000000u },  // 0000225C
        { 0x0000225Eu, 0x00000000u }, { 0x0000225Fu, 0x00000000u },  // 0000225E
        { 0x0000003Du, 0x00000338u }, { 0x00002261u, 0x00000000u },  // 00002260
        { 0x00002261u, 0x00000338u }, { 0x00002263u, 0x00000000u },  // 00002262
        { 0x00002264u, 0x00000000u }, { 0x00002265u, 0x00000000u },  // 00002264
        { 0x00002266u, 0x00000000u }, { 0x00002267u, 0x00000000u },  // 00002266
        { 0x00002268u, 0x00000000u }, { 0x00002269u, 0x00000000u },  // 00002268
        { 0x0000226Au, 0x00000000u }, { 0x0000226Bu, 0x00000000u },  // 0000226A
        { 0x0000226Cu, 0x00000000u }, { 0x0000224Du, 0x00000338u },  // 0000226C
        { 0x0000003Cu, 0x00000338u }, { 0x0000003Eu, 0x00000338u },  // 0000226E
        { 0x00002264u, 0x00000338u }, { 0x00002265u, 0x00000338u },  // 00002270
        { 0x00002272u, 0x00000000u }, { 0x00002273u, 0x00000000u },  // 00002272
        { 0x00002272u, 0x00000338u }, { 0x00002273u, 0x00000338u },  // 00002274
        { 0x00002276u, 0x00000000u }, { 0x00002277u, 0x00000000u },  // 00002276
        { 0x00002276u, 0x00000338u }, { 0x00002277u, 0x00000338u },  // 00002278
        { 0x0000227Au, 0x00000000u }, { 0x0000227Bu, 0x00000000u },  // 0000227A
        { 0x0000227Cu, 0x00000000u }, { 0x0000227Du, 0x00000000u },  // 0000227C
        { 0x0000227Eu, 0x00000000u }, { 0x0000227Fu, 0x00000000u },  // 0000227E
        { 0x0000227Au, 0x00000338u }, { 0x0000227Bu, 0x00000338u },  // 00002280
        { 0x00002282u, 0x00000000u }, { 0x00002283u, 0x00000000u },  // 00002282
        { 0x00002282u, 0x00000338u }, { 0x00002283u, 0x00000338u },  // 00002284
        { 0x00002286u, 0x00000000u }, { 0x00002287u, 0x00000000u },  // 00002286
        { 0x00002286u, 0x00000338u }, { 0x00002287u, 0x00000338u },  // 00002288
        { 0x0000228Au, 0x00000000u }, { 0x0000228Bu, 0x00000000u },  // 0000228A
        { 0x0000228Cu, 0x00000000u }, { 0x0000228Du, 0x00000000u },  // 0000228C
        { 0x0000228Eu, 0x00000000u }, { 0x0000228Fu, 0x00000000u },  // 0000228E
        { 0x00002290u, 0x00000000u }, { 0x00002291u, 0x00000000u },  // 00002290
        { 0x00002292u, 0x00000000u }, { 0x00002293u, 0x00000000u },  // 00002292
        { 0x00002294u, 0x00000000u }, { 0x00002295u, 0x00000000u },  // 00002294
        { 0x00002296u, 0x00000000u }, { 0x00002297u, 0x00000000u },  // 00002296
        { 0x00002298u, 0x00000000u }, { 0x00002299u, 0x00000000u },  // 00002298
        { 0x0000229Au, 0x00000000u }, { 0x0000229Bu, 0x00000000u },  // 0000229A
        { 0x0000229Cu, 0x00000000u }, { 0x0000229Du, 0x00000000u },  // 0000229C
        { 0x0000229Eu, 0x00000000u }, { 0x0000229Fu, 0x00000000u },  // 0000229E
        { 0x000022A0u, 0x00000000u }, { 0x000022A1u, 0x00000000u },  // 000022A0
        { 0x000022A2u, 0x00000000u }, { 0x000022A3u, 0x00000000u },  // 000022A2
        { 0x000022A4u, 0x00000000u }, { 0x000022A5u, 0x00000000u },  // 000022A4
        { 0x000022A6u, 0x00000000u }, { 0x000022A7u, 0x00000000u },  // 000022A6
        { 0x000022A8u, 0x00000000u }, { 0x000022A9u, 0x00000000u },  // 000022A8
        { 0x000022AAu, 0x00000000u }, { 0x000022ABu, 0x00000000u },  // 000022AA
        { 0x000022A2u, 0x00000338u }, { 0x000022A8u, 0x00000338u },  // 000022AC
        { 0x000022A9u, 0x00000338u }, { 0x000022ABu, 0x00000338u },  // 000022AE
        { 0x000022B0u, 0x00000000u }, { 0x000022B1u, 0x00000000u },  // 000022B0
        { 0x000022B2u, 0x00000000u }, { 0x000022B3u, 0x00000000u },  // 000022B2
        { 0x000022B4u, 0x00000000u }, { 0x000022B5u, 0x00000000u },  // 000022B4
        { 0x000022B6u, 0x00000000u }, { 0x000022B7u, 0x00000000u },  // 000022B6
        { 0x000022B8u, 0x00000000u }, { 0x000022B9u, 0x00000000u },  // 000022B8
        { 0x000022BAu, 0x00000000u }, { 0x000022BBu, 0x00000000u },  // 000022BA
        { 0x000022BCu, 0x00000000u }, { 0x000022BDu, 0x00000000u },  // 000022BC
        { 0x000022BEu, 0x00000000u }, { 0x000022BFu, 0x00000000u },  // 000022BE
        { 0x000022C0u, 0x00000000u }, { 0x000022C1u, 0x00000000u },  // 000022C0
        { 0x000022C2u, 0x00000000u }, { 0x000022C3u, 0x00000000u },  // 000022C2
        { 0x000022C4u, 0x00000000u }, { 0x000022C5u, 0x00000000u },  // 000022C4
        { 0x000022C6u, 0x00000000u }, { 0x000022C7u, 0x00000000u },  // 000022C6
        { 0x000022C8u, 0x00000000u }, { 0x000022C9u, 0x00000000u },  // 000022C8
        { 0x000022CAu, 0x00000000u }, { 0x000022CBu, 0x00000000u },  // 000022CA
        { 0x000022CCu, 0x00000000u }, { 0x000022CDu, 0x00000000u },  // 000022CC
        { 0x000022CEu, 0x00000000u }, { 0x000022CFu, 0x00000000u },  // 000022CE
        { 0x000022D0u, 0x00000000u }, { 0x000022D1u, 0x00000000u },  // 000022D0
        { 0x000022D2u, 0x00000000u }, { 0x000022D3u, 0x00000000u },  // 000022D2
        { 0x000022D4u, 0x00000000u }, { 0x000022D5u, 0x00000000u },  // 000022D4
        { 0x000022D6u, 0x00000000u }, { 0x000022D7u, 0x00000000u },  // 000022D6
        { 0x000022D8u, 0x00000000u }, { 0x000022D9u, 0x00000000u },  // 000022D8
        { 0x000022DAu, 0x00000000u }, { 0x000022DBu, 0x00000000u },  // 000022DA
        { 0x000022DCu, 0x00000000u }, { 0x000022DDu, 0x00000000u },  // 000022DC
        { 0x000022DEu, 0x00000000u }, { 0x000022DFu, 0x00000000u },  // 000022DE
        { 0x0000227Cu, 0x00000338u }, { 0x0000227Du, 0x00000338u },  // 000022E0
        { 0x00002291u, 0x00000338u }, { 0x00002292u, 0x00000338u },  // 000022E2
        { 0x000022E4u, 0x00000000u }, { 0x000022E5u, 0x00000000u },  // 000022E4
        { 0x000022E6u, 0x00000000u }, { 0x000022E7u, 0x00000000u },  // 000022E6
        { 0x000022E8u, 0x00000000u }, { 0x000022E9u, 0x00000000u },  // 000022E8
        { 0x000022B2u, 0x00000338u }, { 0x000022B3u, 0x00000338u },  // 000022EA
        { 0x000022B4u, 0x00000338u }, { 0x000022B5u, 0x00000338u },  // 000022EC
        { 0x000022EEu, 0x00000000u }, { 0x000022EFu, 0x00000000u },  // 000022EE
        { 0x000022F0u, 0x00000000u }, { 0x000022F1u, 0x00000000u },  // 000022F0
        { 0x000022F2u, 0x00000000u }, { 0x000022F3u, 0x00000000u },  // 000022F2
        { 0x000022F4u, 0x00000000u }, { 0x000022F5u, 0x00000000u },  // 000022F4
        { 0x000022F6u, 0x00000000u }, { 0x000022F7u, 0x00000000u },  // 000022F6
        { 0x000022F8u, 0x00000000u }, { 0x000022F9u, 0x00000000u },  // 000022F8
        { 0x000022FAu, 0x00000000u }, { 0x000022FBu, 0x00000000u },  // 000022FA
        { 0x000022FCu, 0x00000000u }, { 0x000022FDu, 0x00000000u },  // 000022FC
        { 0x000022FEu, 0x00000000u }, { 0x000022FFu, 0x00000000u }
    };

    const std::bitset<256> Mathematical_Operators2200::my_mirror(std::string("1111111111111111001111111111111111111111110000110011111000000000110000011111111111111111110011000000000100000111100111111111111111111111111111111100111111110101100000000011110000011111111111111111101000001111111110000101011110111100011000100011111100011110"));

    const unsigned char Mathematical_Operators2200::my_lb[] =
    {
        LB_AI, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AI, 
        LB_AI, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AI, 
        LB_AL, LB_AI, LB_PR, LB_PR, LB_AL, LB_AI, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AI, LB_AI, LB_AI, 
        LB_AI, LB_AL, LB_AL, LB_AI, LB_AL, LB_AI, LB_AL, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AI, LB_AL, LB_AI, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AI, LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AI, LB_AI, LB_AL, LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, 
        LB_AL, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, LB_AI, LB_AI, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, LB_AI, LB_AI, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, 
        LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const unsigned char Mathematical_Operators2200::my_ea[] =
    {
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
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

    const std::bitset<256> Mathematical_Operators2200::my_Dash(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Mathematical_Operators2200);
