/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp C00-C7F.cc
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
    class TeluguC00 : public Babylon::Block
    {
      public:
        void clean() { };

        TeluguC00() :
        my_first_letter(0xC00),
        my_last_letter(0xC7F)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000C46, 0x00000C56)] = 0x0C48;
            }
        }

        ~TeluguC00() { }

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
        return "Telugu";
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
            case 0x0C66u:
                return 0;
            case 0x0C67u:
                return 1;
            case 0x0C68u:
                return 2;
            case 0x0C69u:
                return 3;
            case 0x0C6Au:
                return 4;
            case 0x0C6Bu:
                return 5;
            case 0x0C6Cu:
                return 6;
            case 0x0C6Du:
                return 7;
            case 0x0C6Eu:
                return 8;
            case 0x0C6Fu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0C66u:
            case 0x0C67u:
            case 0x0C68u:
            case 0x0C69u:
            case 0x0C6Au:
            case 0x0C6Bu:
            case 0x0C6Cu:
            case 0x0C6Du:
            case 0x0C6Eu:
            case 0x0C6Fu:
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
            case 0x0C66u:
                return 0;
            case 0x0C67u:
                return 1;
            case 0x0C68u:
                return 2;
            case 0x0C69u:
                return 3;
            case 0x0C6Au:
                return 4;
            case 0x0C6Bu:
                return 5;
            case 0x0C6Cu:
                return 6;
            case 0x0C6Du:
                return 7;
            case 0x0C6Eu:
                return 8;
            case 0x0C6Fu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0C66u:
            case 0x0C67u:
            case 0x0C68u:
            case 0x0C69u:
            case 0x0C6Au:
            case 0x0C6Bu:
            case 0x0C6Cu:
            case 0x0C6Du:
            case 0x0C6Eu:
            case 0x0C6Fu:
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
            case 0x0C66u:
                return 0.000000;
            case 0x0C67u:
                return 1.000000;
            case 0x0C68u:
                return 2.000000;
            case 0x0C69u:
                return 3.000000;
            case 0x0C6Au:
                return 4.000000;
            case 0x0C6Bu:
                return 5.000000;
            case 0x0C6Cu:
                return 6.000000;
            case 0x0C6Du:
                return 7.000000;
            case 0x0C6Eu:
                return 8.000000;
            case 0x0C6Fu:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0C66u:
            case 0x0C67u:
            case 0x0C68u:
            case 0x0C69u:
            case 0x0C6Au:
            case 0x0C6Bu:
            case 0x0C6Cu:
            case 0x0C6Du:
            case 0x0C6Eu:
            case 0x0C6Fu:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(TeluguC00::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(TeluguC00::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return TeluguC00::my_bidir[uc - my_first_letter];
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
            us[0] = TeluguC00::my_decompStr[uc - my_first_letter][0];
            us[1] = TeluguC00::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(TeluguC00::my_lb[uc - my_first_letter]);
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
        TeluguC00(const TeluguC00 &) ; // no implementaion!

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
        static const std::bitset<128> my_Grapheme_Link;
    }; // class TeluguC00

    const std::bitset<128> TeluguC00::my_is_defined(std::string("00000000000000001111111111000011000000000110000000111101110111111100001111101111111111011111111111111111111111011101111111101110"));

    const unsigned char TeluguC00::my_cat[] =
    {
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc
    };

    const unsigned char TeluguC00::my_comb_cl[] = {
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
        0, 0, 0, 0, 0, 84, 91, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props TeluguC00::my_bidir[] =
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
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
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

    const UCS2 TeluguC00::my_decompStr[][2] =
    {
        { 0x00000C00u, 0x00000000u }, { 0x00000C01u, 0x00000000u },  // 00000C00
        { 0x00000C02u, 0x00000000u }, { 0x00000C03u, 0x00000000u },  // 00000C02
        { 0x00000C04u, 0x00000000u }, { 0x00000C05u, 0x00000000u },  // 00000C04
        { 0x00000C06u, 0x00000000u }, { 0x00000C07u, 0x00000000u },  // 00000C06
        { 0x00000C08u, 0x00000000u }, { 0x00000C09u, 0x00000000u },  // 00000C08
        { 0x00000C0Au, 0x00000000u }, { 0x00000C0Bu, 0x00000000u },  // 00000C0A
        { 0x00000C0Cu, 0x00000000u }, { 0x00000C0Du, 0x00000000u },  // 00000C0C
        { 0x00000C0Eu, 0x00000000u }, { 0x00000C0Fu, 0x00000000u },  // 00000C0E
        { 0x00000C10u, 0x00000000u }, { 0x00000C11u, 0x00000000u },  // 00000C10
        { 0x00000C12u, 0x00000000u }, { 0x00000C13u, 0x00000000u },  // 00000C12
        { 0x00000C14u, 0x00000000u }, { 0x00000C15u, 0x00000000u },  // 00000C14
        { 0x00000C16u, 0x00000000u }, { 0x00000C17u, 0x00000000u },  // 00000C16
        { 0x00000C18u, 0x00000000u }, { 0x00000C19u, 0x00000000u },  // 00000C18
        { 0x00000C1Au, 0x00000000u }, { 0x00000C1Bu, 0x00000000u },  // 00000C1A
        { 0x00000C1Cu, 0x00000000u }, { 0x00000C1Du, 0x00000000u },  // 00000C1C
        { 0x00000C1Eu, 0x00000000u }, { 0x00000C1Fu, 0x00000000u },  // 00000C1E
        { 0x00000C20u, 0x00000000u }, { 0x00000C21u, 0x00000000u },  // 00000C20
        { 0x00000C22u, 0x00000000u }, { 0x00000C23u, 0x00000000u },  // 00000C22
        { 0x00000C24u, 0x00000000u }, { 0x00000C25u, 0x00000000u },  // 00000C24
        { 0x00000C26u, 0x00000000u }, { 0x00000C27u, 0x00000000u },  // 00000C26
        { 0x00000C28u, 0x00000000u }, { 0x00000C29u, 0x00000000u },  // 00000C28
        { 0x00000C2Au, 0x00000000u }, { 0x00000C2Bu, 0x00000000u },  // 00000C2A
        { 0x00000C2Cu, 0x00000000u }, { 0x00000C2Du, 0x00000000u },  // 00000C2C
        { 0x00000C2Eu, 0x00000000u }, { 0x00000C2Fu, 0x00000000u },  // 00000C2E
        { 0x00000C30u, 0x00000000u }, { 0x00000C31u, 0x00000000u },  // 00000C30
        { 0x00000C32u, 0x00000000u }, { 0x00000C33u, 0x00000000u },  // 00000C32
        { 0x00000C34u, 0x00000000u }, { 0x00000C35u, 0x00000000u },  // 00000C34
        { 0x00000C36u, 0x00000000u }, { 0x00000C37u, 0x00000000u },  // 00000C36
        { 0x00000C38u, 0x00000000u }, { 0x00000C39u, 0x00000000u },  // 00000C38
        { 0x00000C3Au, 0x00000000u }, { 0x00000C3Bu, 0x00000000u },  // 00000C3A
        { 0x00000C3Cu, 0x00000000u }, { 0x00000C3Du, 0x00000000u },  // 00000C3C
        { 0x00000C3Eu, 0x00000000u }, { 0x00000C3Fu, 0x00000000u },  // 00000C3E
        { 0x00000C40u, 0x00000000u }, { 0x00000C41u, 0x00000000u },  // 00000C40
        { 0x00000C42u, 0x00000000u }, { 0x00000C43u, 0x00000000u },  // 00000C42
        { 0x00000C44u, 0x00000000u }, { 0x00000C45u, 0x00000000u },  // 00000C44
        { 0x00000C46u, 0x00000000u }, { 0x00000C47u, 0x00000000u },  // 00000C46
        { 0x00000C46u, 0x00000C56u }, { 0x00000C49u, 0x00000000u },  // 00000C48
        { 0x00000C4Au, 0x00000000u }, { 0x00000C4Bu, 0x00000000u },  // 00000C4A
        { 0x00000C4Cu, 0x00000000u }, { 0x00000C4Du, 0x00000000u },  // 00000C4C
        { 0x00000C4Eu, 0x00000000u }, { 0x00000C4Fu, 0x00000000u },  // 00000C4E
        { 0x00000C50u, 0x00000000u }, { 0x00000C51u, 0x00000000u },  // 00000C50
        { 0x00000C52u, 0x00000000u }, { 0x00000C53u, 0x00000000u },  // 00000C52
        { 0x00000C54u, 0x00000000u }, { 0x00000C55u, 0x00000000u },  // 00000C54
        { 0x00000C56u, 0x00000000u }, { 0x00000C57u, 0x00000000u },  // 00000C56
        { 0x00000C58u, 0x00000000u }, { 0x00000C59u, 0x00000000u },  // 00000C58
        { 0x00000C5Au, 0x00000000u }, { 0x00000C5Bu, 0x00000000u },  // 00000C5A
        { 0x00000C5Cu, 0x00000000u }, { 0x00000C5Du, 0x00000000u },  // 00000C5C
        { 0x00000C5Eu, 0x00000000u }, { 0x00000C5Fu, 0x00000000u },  // 00000C5E
        { 0x00000C60u, 0x00000000u }, { 0x00000C61u, 0x00000000u },  // 00000C60
        { 0x00000C62u, 0x00000000u }, { 0x00000C63u, 0x00000000u },  // 00000C62
        { 0x00000C64u, 0x00000000u }, { 0x00000C65u, 0x00000000u },  // 00000C64
        { 0x00000C66u, 0x00000000u }, { 0x00000C67u, 0x00000000u },  // 00000C66
        { 0x00000C68u, 0x00000000u }, { 0x00000C69u, 0x00000000u },  // 00000C68
        { 0x00000C6Au, 0x00000000u }, { 0x00000C6Bu, 0x00000000u },  // 00000C6A
        { 0x00000C6Cu, 0x00000000u }, { 0x00000C6Du, 0x00000000u },  // 00000C6C
        { 0x00000C6Eu, 0x00000000u }, { 0x00000C6Fu, 0x00000000u },  // 00000C6E
        { 0x00000C70u, 0x00000000u }, { 0x00000C71u, 0x00000000u },  // 00000C70
        { 0x00000C72u, 0x00000000u }, { 0x00000C73u, 0x00000000u },  // 00000C72
        { 0x00000C74u, 0x00000000u }, { 0x00000C75u, 0x00000000u },  // 00000C74
        { 0x00000C76u, 0x00000000u }, { 0x00000C77u, 0x00000000u },  // 00000C76
        { 0x00000C78u, 0x00000000u }, { 0x00000C79u, 0x00000000u },  // 00000C78
        { 0x00000C7Au, 0x00000000u }, { 0x00000C7Bu, 0x00000000u },  // 00000C7A
        { 0x00000C7Cu, 0x00000000u }, { 0x00000C7Du, 0x00000000u },  // 00000C7C
        { 0x00000C7Eu, 0x00000000u }, { 0x00000C7Fu, 0x00000000u }
    };

    const unsigned char TeluguC00::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, 
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

    const std::bitset<128> TeluguC00::my_Other_Alphabetic(std::string("00000000000000000000000000000000000000000110000000011101110111111100000000000000000000000000000000000000000000000000000000001110"));

    const std::bitset<128> TeluguC00::my_Diacritic(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> TeluguC00::my_Grapheme_Link(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::TeluguC00);
