/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp D00-D7F.cc
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
    class MalayalamD00 : public Babylon::Block
    {
      public:
        void clean() { };

        MalayalamD00() :
        my_first_letter(0xD00),
        my_last_letter(0xD7F)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000D46, 0x00000D3E)] = 0x0D4A;
                my_composeMap[std::make_pair(0x00000D46, 0x00000D57)] = 0x0D4C;
                my_composeMap[std::make_pair(0x00000D47, 0x00000D3E)] = 0x0D4B;
            }
        }

        ~MalayalamD00() { }

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
        return "Malayalam";
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
            case 0x0D66u:
                return 0;
            case 0x0D67u:
                return 1;
            case 0x0D68u:
                return 2;
            case 0x0D69u:
                return 3;
            case 0x0D6Au:
                return 4;
            case 0x0D6Bu:
                return 5;
            case 0x0D6Cu:
                return 6;
            case 0x0D6Du:
                return 7;
            case 0x0D6Eu:
                return 8;
            case 0x0D6Fu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0D66u:
            case 0x0D67u:
            case 0x0D68u:
            case 0x0D69u:
            case 0x0D6Au:
            case 0x0D6Bu:
            case 0x0D6Cu:
            case 0x0D6Du:
            case 0x0D6Eu:
            case 0x0D6Fu:
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
            case 0x0D66u:
                return 0;
            case 0x0D67u:
                return 1;
            case 0x0D68u:
                return 2;
            case 0x0D69u:
                return 3;
            case 0x0D6Au:
                return 4;
            case 0x0D6Bu:
                return 5;
            case 0x0D6Cu:
                return 6;
            case 0x0D6Du:
                return 7;
            case 0x0D6Eu:
                return 8;
            case 0x0D6Fu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0D66u:
            case 0x0D67u:
            case 0x0D68u:
            case 0x0D69u:
            case 0x0D6Au:
            case 0x0D6Bu:
            case 0x0D6Cu:
            case 0x0D6Du:
            case 0x0D6Eu:
            case 0x0D6Fu:
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
            case 0x0D66u:
                return 0.000000;
            case 0x0D67u:
                return 1.000000;
            case 0x0D68u:
                return 2.000000;
            case 0x0D69u:
                return 3.000000;
            case 0x0D6Au:
                return 4.000000;
            case 0x0D6Bu:
                return 5.000000;
            case 0x0D6Cu:
                return 6.000000;
            case 0x0D6Du:
                return 7.000000;
            case 0x0D6Eu:
                return 8.000000;
            case 0x0D6Fu:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0D66u:
            case 0x0D67u:
            case 0x0D68u:
            case 0x0D69u:
            case 0x0D6Au:
            case 0x0D6Bu:
            case 0x0D6Cu:
            case 0x0D6Du:
            case 0x0D6Eu:
            case 0x0D6Fu:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(MalayalamD00::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(MalayalamD00::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return MalayalamD00::my_bidir[uc - my_first_letter];
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
            us[0] = MalayalamD00::my_decompStr[uc - my_first_letter][0];
            us[1] = MalayalamD00::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(MalayalamD00::my_lb[uc - my_first_letter]);
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
        MalayalamD00(const MalayalamD00 &) ; // no implementaion!

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
    }; // class MalayalamD00

    const std::bitset<128> MalayalamD00::my_is_defined(std::string("00000000000000001111111111000011000000001000000000111101110011111100001111111111111111011111111111111111111111011101111111101100"));

    const unsigned char MalayalamD00::my_cat[] =
    {
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc
    };

    const unsigned char MalayalamD00::my_comb_cl[] = {
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

    const Babylon::Bidir_Props MalayalamD00::my_bidir[] =
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
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, 
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

    const UCS2 MalayalamD00::my_decompStr[][2] =
    {
        { 0x00000D00u, 0x00000000u }, { 0x00000D01u, 0x00000000u },  // 00000D00
        { 0x00000D02u, 0x00000000u }, { 0x00000D03u, 0x00000000u },  // 00000D02
        { 0x00000D04u, 0x00000000u }, { 0x00000D05u, 0x00000000u },  // 00000D04
        { 0x00000D06u, 0x00000000u }, { 0x00000D07u, 0x00000000u },  // 00000D06
        { 0x00000D08u, 0x00000000u }, { 0x00000D09u, 0x00000000u },  // 00000D08
        { 0x00000D0Au, 0x00000000u }, { 0x00000D0Bu, 0x00000000u },  // 00000D0A
        { 0x00000D0Cu, 0x00000000u }, { 0x00000D0Du, 0x00000000u },  // 00000D0C
        { 0x00000D0Eu, 0x00000000u }, { 0x00000D0Fu, 0x00000000u },  // 00000D0E
        { 0x00000D10u, 0x00000000u }, { 0x00000D11u, 0x00000000u },  // 00000D10
        { 0x00000D12u, 0x00000000u }, { 0x00000D13u, 0x00000000u },  // 00000D12
        { 0x00000D14u, 0x00000000u }, { 0x00000D15u, 0x00000000u },  // 00000D14
        { 0x00000D16u, 0x00000000u }, { 0x00000D17u, 0x00000000u },  // 00000D16
        { 0x00000D18u, 0x00000000u }, { 0x00000D19u, 0x00000000u },  // 00000D18
        { 0x00000D1Au, 0x00000000u }, { 0x00000D1Bu, 0x00000000u },  // 00000D1A
        { 0x00000D1Cu, 0x00000000u }, { 0x00000D1Du, 0x00000000u },  // 00000D1C
        { 0x00000D1Eu, 0x00000000u }, { 0x00000D1Fu, 0x00000000u },  // 00000D1E
        { 0x00000D20u, 0x00000000u }, { 0x00000D21u, 0x00000000u },  // 00000D20
        { 0x00000D22u, 0x00000000u }, { 0x00000D23u, 0x00000000u },  // 00000D22
        { 0x00000D24u, 0x00000000u }, { 0x00000D25u, 0x00000000u },  // 00000D24
        { 0x00000D26u, 0x00000000u }, { 0x00000D27u, 0x00000000u },  // 00000D26
        { 0x00000D28u, 0x00000000u }, { 0x00000D29u, 0x00000000u },  // 00000D28
        { 0x00000D2Au, 0x00000000u }, { 0x00000D2Bu, 0x00000000u },  // 00000D2A
        { 0x00000D2Cu, 0x00000000u }, { 0x00000D2Du, 0x00000000u },  // 00000D2C
        { 0x00000D2Eu, 0x00000000u }, { 0x00000D2Fu, 0x00000000u },  // 00000D2E
        { 0x00000D30u, 0x00000000u }, { 0x00000D31u, 0x00000000u },  // 00000D30
        { 0x00000D32u, 0x00000000u }, { 0x00000D33u, 0x00000000u },  // 00000D32
        { 0x00000D34u, 0x00000000u }, { 0x00000D35u, 0x00000000u },  // 00000D34
        { 0x00000D36u, 0x00000000u }, { 0x00000D37u, 0x00000000u },  // 00000D36
        { 0x00000D38u, 0x00000000u }, { 0x00000D39u, 0x00000000u },  // 00000D38
        { 0x00000D3Au, 0x00000000u }, { 0x00000D3Bu, 0x00000000u },  // 00000D3A
        { 0x00000D3Cu, 0x00000000u }, { 0x00000D3Du, 0x00000000u },  // 00000D3C
        { 0x00000D3Eu, 0x00000000u }, { 0x00000D3Fu, 0x00000000u },  // 00000D3E
        { 0x00000D40u, 0x00000000u }, { 0x00000D41u, 0x00000000u },  // 00000D40
        { 0x00000D42u, 0x00000000u }, { 0x00000D43u, 0x00000000u },  // 00000D42
        { 0x00000D44u, 0x00000000u }, { 0x00000D45u, 0x00000000u },  // 00000D44
        { 0x00000D46u, 0x00000000u }, { 0x00000D47u, 0x00000000u },  // 00000D46
        { 0x00000D48u, 0x00000000u }, { 0x00000D49u, 0x00000000u },  // 00000D48
        { 0x00000D46u, 0x00000D3Eu }, { 0x00000D47u, 0x00000D3Eu },  // 00000D4A
        { 0x00000D46u, 0x00000D57u }, { 0x00000D4Du, 0x00000000u },  // 00000D4C
        { 0x00000D4Eu, 0x00000000u }, { 0x00000D4Fu, 0x00000000u },  // 00000D4E
        { 0x00000D50u, 0x00000000u }, { 0x00000D51u, 0x00000000u },  // 00000D50
        { 0x00000D52u, 0x00000000u }, { 0x00000D53u, 0x00000000u },  // 00000D52
        { 0x00000D54u, 0x00000000u }, { 0x00000D55u, 0x00000000u },  // 00000D54
        { 0x00000D56u, 0x00000000u }, { 0x00000D57u, 0x00000000u },  // 00000D56
        { 0x00000D58u, 0x00000000u }, { 0x00000D59u, 0x00000000u },  // 00000D58
        { 0x00000D5Au, 0x00000000u }, { 0x00000D5Bu, 0x00000000u },  // 00000D5A
        { 0x00000D5Cu, 0x00000000u }, { 0x00000D5Du, 0x00000000u },  // 00000D5C
        { 0x00000D5Eu, 0x00000000u }, { 0x00000D5Fu, 0x00000000u },  // 00000D5E
        { 0x00000D60u, 0x00000000u }, { 0x00000D61u, 0x00000000u },  // 00000D60
        { 0x00000D62u, 0x00000000u }, { 0x00000D63u, 0x00000000u },  // 00000D62
        { 0x00000D64u, 0x00000000u }, { 0x00000D65u, 0x00000000u },  // 00000D64
        { 0x00000D66u, 0x00000000u }, { 0x00000D67u, 0x00000000u },  // 00000D66
        { 0x00000D68u, 0x00000000u }, { 0x00000D69u, 0x00000000u },  // 00000D68
        { 0x00000D6Au, 0x00000000u }, { 0x00000D6Bu, 0x00000000u },  // 00000D6A
        { 0x00000D6Cu, 0x00000000u }, { 0x00000D6Du, 0x00000000u },  // 00000D6C
        { 0x00000D6Eu, 0x00000000u }, { 0x00000D6Fu, 0x00000000u },  // 00000D6E
        { 0x00000D70u, 0x00000000u }, { 0x00000D71u, 0x00000000u },  // 00000D70
        { 0x00000D72u, 0x00000000u }, { 0x00000D73u, 0x00000000u },  // 00000D72
        { 0x00000D74u, 0x00000000u }, { 0x00000D75u, 0x00000000u },  // 00000D74
        { 0x00000D76u, 0x00000000u }, { 0x00000D77u, 0x00000000u },  // 00000D76
        { 0x00000D78u, 0x00000000u }, { 0x00000D79u, 0x00000000u },  // 00000D78
        { 0x00000D7Au, 0x00000000u }, { 0x00000D7Bu, 0x00000000u },  // 00000D7A
        { 0x00000D7Cu, 0x00000000u }, { 0x00000D7Du, 0x00000000u },  // 00000D7C
        { 0x00000D7Eu, 0x00000000u }, { 0x00000D7Fu, 0x00000000u }
    };

    const unsigned char MalayalamD00::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
    };

    const std::bitset<128> MalayalamD00::my_Other_Alphabetic(std::string("00000000000000000000000000000000000000001000000000011101110011111100000000000000000000000000000000000000000000000000000000001100"));

    const std::bitset<128> MalayalamD00::my_Diacritic(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> MalayalamD00::my_Other_Grapheme_Extend(std::string("00000000000000000000000000000000000000001000000000000000000000000100000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> MalayalamD00::my_Grapheme_Link(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::MalayalamD00);
