/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp A00-A7F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:40 +0200.
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
    class GurmukhiA00 : public Babylon::Block
    {
      public:
        void clean() { };

        GurmukhiA00() :
        my_first_letter(0xA00),
        my_last_letter(0xA7F)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000A16, 0x00000A3C)] = 0x0A59;
                my_composeMap[std::make_pair(0x00000A17, 0x00000A3C)] = 0x0A5A;
                my_composeMap[std::make_pair(0x00000A1C, 0x00000A3C)] = 0x0A5B;
                my_composeMap[std::make_pair(0x00000A2B, 0x00000A3C)] = 0x0A5E;
                my_composeMap[std::make_pair(0x00000A32, 0x00000A3C)] = 0x0A33;
                my_composeMap[std::make_pair(0x00000A38, 0x00000A3C)] = 0x0A36;
            }
        }

        ~GurmukhiA00() { }

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
        return "Gurmukhi";
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
            case 0x0A66u:
                return 0;
            case 0x0A67u:
                return 1;
            case 0x0A68u:
                return 2;
            case 0x0A69u:
                return 3;
            case 0x0A6Au:
                return 4;
            case 0x0A6Bu:
                return 5;
            case 0x0A6Cu:
                return 6;
            case 0x0A6Du:
                return 7;
            case 0x0A6Eu:
                return 8;
            case 0x0A6Fu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0A66u:
            case 0x0A67u:
            case 0x0A68u:
            case 0x0A69u:
            case 0x0A6Au:
            case 0x0A6Bu:
            case 0x0A6Cu:
            case 0x0A6Du:
            case 0x0A6Eu:
            case 0x0A6Fu:
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
            case 0x0A66u:
                return 0;
            case 0x0A67u:
                return 1;
            case 0x0A68u:
                return 2;
            case 0x0A69u:
                return 3;
            case 0x0A6Au:
                return 4;
            case 0x0A6Bu:
                return 5;
            case 0x0A6Cu:
                return 6;
            case 0x0A6Du:
                return 7;
            case 0x0A6Eu:
                return 8;
            case 0x0A6Fu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0A66u:
            case 0x0A67u:
            case 0x0A68u:
            case 0x0A69u:
            case 0x0A6Au:
            case 0x0A6Bu:
            case 0x0A6Cu:
            case 0x0A6Du:
            case 0x0A6Eu:
            case 0x0A6Fu:
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
            case 0x0A66u:
                return 0.000000;
            case 0x0A67u:
                return 1.000000;
            case 0x0A68u:
                return 2.000000;
            case 0x0A69u:
                return 3.000000;
            case 0x0A6Au:
                return 4.000000;
            case 0x0A6Bu:
                return 5.000000;
            case 0x0A6Cu:
                return 6.000000;
            case 0x0A6Du:
                return 7.000000;
            case 0x0A6Eu:
                return 8.000000;
            case 0x0A6Fu:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0A66u:
            case 0x0A67u:
            case 0x0A68u:
            case 0x0A69u:
            case 0x0A6Au:
            case 0x0A6Bu:
            case 0x0A6Cu:
            case 0x0A6Du:
            case 0x0A6Eu:
            case 0x0A6Fu:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(GurmukhiA00::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(GurmukhiA00::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return GurmukhiA00::my_bidir[uc - my_first_letter];
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
            us[0] = GurmukhiA00::my_decompStr[uc - my_first_letter][0];
            us[1] = GurmukhiA00::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(GurmukhiA00::my_lb[uc - my_first_letter]);
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
            if (my_comp_exclude.test(uc - my_first_letter)) return 1;
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
        GurmukhiA00(const GurmukhiA00 &) ; // no implementaion!

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
        static const std::bitset<128> my_comp_exclude;
        static const std::bitset<128> my_Other_Alphabetic;
        static const std::bitset<128> my_Diacritic;
        static const std::bitset<128> my_Grapheme_Link;
    }; // class GurmukhiA00

    const std::bitset<128> GurmukhiA00::my_is_defined(std::string("00000000000111111111111111000000010111100000000000111001100001111101001101101101111111011111111111111111111110011000011111101110"));

    const unsigned char GurmukhiA00::my_cat[] =
    {
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Mn, 
        CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Lo, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Mn, CAT_Mn, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
    };

    const unsigned char GurmukhiA00::my_comb_cl[] = {
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

    const Babylon::Bidir_Props GurmukhiA00::my_bidir[] =
    {
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_NSM, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM
    };

    const UCS2 GurmukhiA00::my_decompStr[][2] =
    {
        { 0x00000A00u, 0x00000000u }, { 0x00000A01u, 0x00000000u },  // 00000A00
        { 0x00000A02u, 0x00000000u }, { 0x00000A03u, 0x00000000u },  // 00000A02
        { 0x00000A04u, 0x00000000u }, { 0x00000A05u, 0x00000000u },  // 00000A04
        { 0x00000A06u, 0x00000000u }, { 0x00000A07u, 0x00000000u },  // 00000A06
        { 0x00000A08u, 0x00000000u }, { 0x00000A09u, 0x00000000u },  // 00000A08
        { 0x00000A0Au, 0x00000000u }, { 0x00000A0Bu, 0x00000000u },  // 00000A0A
        { 0x00000A0Cu, 0x00000000u }, { 0x00000A0Du, 0x00000000u },  // 00000A0C
        { 0x00000A0Eu, 0x00000000u }, { 0x00000A0Fu, 0x00000000u },  // 00000A0E
        { 0x00000A10u, 0x00000000u }, { 0x00000A11u, 0x00000000u },  // 00000A10
        { 0x00000A12u, 0x00000000u }, { 0x00000A13u, 0x00000000u },  // 00000A12
        { 0x00000A14u, 0x00000000u }, { 0x00000A15u, 0x00000000u },  // 00000A14
        { 0x00000A16u, 0x00000000u }, { 0x00000A17u, 0x00000000u },  // 00000A16
        { 0x00000A18u, 0x00000000u }, { 0x00000A19u, 0x00000000u },  // 00000A18
        { 0x00000A1Au, 0x00000000u }, { 0x00000A1Bu, 0x00000000u },  // 00000A1A
        { 0x00000A1Cu, 0x00000000u }, { 0x00000A1Du, 0x00000000u },  // 00000A1C
        { 0x00000A1Eu, 0x00000000u }, { 0x00000A1Fu, 0x00000000u },  // 00000A1E
        { 0x00000A20u, 0x00000000u }, { 0x00000A21u, 0x00000000u },  // 00000A20
        { 0x00000A22u, 0x00000000u }, { 0x00000A23u, 0x00000000u },  // 00000A22
        { 0x00000A24u, 0x00000000u }, { 0x00000A25u, 0x00000000u },  // 00000A24
        { 0x00000A26u, 0x00000000u }, { 0x00000A27u, 0x00000000u },  // 00000A26
        { 0x00000A28u, 0x00000000u }, { 0x00000A29u, 0x00000000u },  // 00000A28
        { 0x00000A2Au, 0x00000000u }, { 0x00000A2Bu, 0x00000000u },  // 00000A2A
        { 0x00000A2Cu, 0x00000000u }, { 0x00000A2Du, 0x00000000u },  // 00000A2C
        { 0x00000A2Eu, 0x00000000u }, { 0x00000A2Fu, 0x00000000u },  // 00000A2E
        { 0x00000A30u, 0x00000000u }, { 0x00000A31u, 0x00000000u },  // 00000A30
        { 0x00000A32u, 0x00000000u }, { 0x00000A32u, 0x00000A3Cu },  // 00000A32
        { 0x00000A34u, 0x00000000u }, { 0x00000A35u, 0x00000000u },  // 00000A34
        { 0x00000A38u, 0x00000A3Cu }, { 0x00000A37u, 0x00000000u },  // 00000A36
        { 0x00000A38u, 0x00000000u }, { 0x00000A39u, 0x00000000u },  // 00000A38
        { 0x00000A3Au, 0x00000000u }, { 0x00000A3Bu, 0x00000000u },  // 00000A3A
        { 0x00000A3Cu, 0x00000000u }, { 0x00000A3Du, 0x00000000u },  // 00000A3C
        { 0x00000A3Eu, 0x00000000u }, { 0x00000A3Fu, 0x00000000u },  // 00000A3E
        { 0x00000A40u, 0x00000000u }, { 0x00000A41u, 0x00000000u },  // 00000A40
        { 0x00000A42u, 0x00000000u }, { 0x00000A43u, 0x00000000u },  // 00000A42
        { 0x00000A44u, 0x00000000u }, { 0x00000A45u, 0x00000000u },  // 00000A44
        { 0x00000A46u, 0x00000000u }, { 0x00000A47u, 0x00000000u },  // 00000A46
        { 0x00000A48u, 0x00000000u }, { 0x00000A49u, 0x00000000u },  // 00000A48
        { 0x00000A4Au, 0x00000000u }, { 0x00000A4Bu, 0x00000000u },  // 00000A4A
        { 0x00000A4Cu, 0x00000000u }, { 0x00000A4Du, 0x00000000u },  // 00000A4C
        { 0x00000A4Eu, 0x00000000u }, { 0x00000A4Fu, 0x00000000u },  // 00000A4E
        { 0x00000A50u, 0x00000000u }, { 0x00000A51u, 0x00000000u },  // 00000A50
        { 0x00000A52u, 0x00000000u }, { 0x00000A53u, 0x00000000u },  // 00000A52
        { 0x00000A54u, 0x00000000u }, { 0x00000A55u, 0x00000000u },  // 00000A54
        { 0x00000A56u, 0x00000000u }, { 0x00000A57u, 0x00000000u },  // 00000A56
        { 0x00000A58u, 0x00000000u }, { 0x00000A16u, 0x00000A3Cu },  // 00000A58
        { 0x00000A17u, 0x00000A3Cu }, { 0x00000A1Cu, 0x00000A3Cu },  // 00000A5A
        { 0x00000A5Cu, 0x00000000u }, { 0x00000A5Du, 0x00000000u },  // 00000A5C
        { 0x00000A2Bu, 0x00000A3Cu }, { 0x00000A5Fu, 0x00000000u },  // 00000A5E
        { 0x00000A60u, 0x00000000u }, { 0x00000A61u, 0x00000000u },  // 00000A60
        { 0x00000A62u, 0x00000000u }, { 0x00000A63u, 0x00000000u },  // 00000A62
        { 0x00000A64u, 0x00000000u }, { 0x00000A65u, 0x00000000u },  // 00000A64
        { 0x00000A66u, 0x00000000u }, { 0x00000A67u, 0x00000000u },  // 00000A66
        { 0x00000A68u, 0x00000000u }, { 0x00000A69u, 0x00000000u },  // 00000A68
        { 0x00000A6Au, 0x00000000u }, { 0x00000A6Bu, 0x00000000u },  // 00000A6A
        { 0x00000A6Cu, 0x00000000u }, { 0x00000A6Du, 0x00000000u },  // 00000A6C
        { 0x00000A6Eu, 0x00000000u }, { 0x00000A6Fu, 0x00000000u },  // 00000A6E
        { 0x00000A70u, 0x00000000u }, { 0x00000A71u, 0x00000000u },  // 00000A70
        { 0x00000A72u, 0x00000000u }, { 0x00000A73u, 0x00000000u },  // 00000A72
        { 0x00000A74u, 0x00000000u }, { 0x00000A75u, 0x00000000u },  // 00000A74
        { 0x00000A76u, 0x00000000u }, { 0x00000A77u, 0x00000000u },  // 00000A76
        { 0x00000A78u, 0x00000000u }, { 0x00000A79u, 0x00000000u },  // 00000A78
        { 0x00000A7Au, 0x00000000u }, { 0x00000A7Bu, 0x00000000u },  // 00000A7A
        { 0x00000A7Cu, 0x00000000u }, { 0x00000A7Du, 0x00000000u },  // 00000A7C
        { 0x00000A7Eu, 0x00000000u }, { 0x00000A7Fu, 0x00000000u }
    };

    const unsigned char GurmukhiA00::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, 
        LB_AL, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, LB_CM, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
    };

    const std::bitset<128> GurmukhiA00::my_comp_exclude(std::string("00000000000000000000000000000000010011100000000000000000000000000000000001001000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> GurmukhiA00::my_Other_Alphabetic(std::string("00000000000000110000000000000000000000000000000000011001100001111100000000000000000000000000000000000000000000000000000000001110"));

    const std::bitset<128> GurmukhiA00::my_Diacritic(std::string("00000000000000000000000000000000000000000000000000100000000000000001000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> GurmukhiA00::my_Grapheme_Link(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::GurmukhiA00);
