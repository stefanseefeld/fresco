/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp 2B0-2FF.cc
 *
 * This source file is a part of the Fresco Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 28 Jan 2004 20:49:03 +0100.
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


namespace Babylon
{
  namespace Module
  {
    class Spacing_Modifier_Letters2B0 : public Babylon::Block
    {
      public:
        void clean() { };

        Spacing_Modifier_Letters2B0() :
        my_first_letter(0x2B0),
        my_last_letter(0x2FF)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~Spacing_Modifier_Letters2B0() { }

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
        return "Spacing Modifier Letters";
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
            return Babylon::Gen_Cat(Spacing_Modifier_Letters2B0::my_cat[uc - my_first_letter]);
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
            return Spacing_Modifier_Letters2B0::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Spacing_Modifier_Letters2B0::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Spacing_Modifier_Letters2B0::my_decompStr[uc - my_first_letter][0];
            us[1] = Spacing_Modifier_Letters2B0::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Spacing_Modifier_Letters2B0::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Spacing_Modifier_Letters2B0::my_ea[uc - my_first_letter]);
        }

        UCS4 compose(const UCS4 starter, const UCS4 last)
        {
            return 0;
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
            return 1;
        }

        bool is_Extender(const UCS4 uc) const
        {
            return my_Extender.test(uc - my_first_letter);
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
        Spacing_Modifier_Letters2B0(const Spacing_Modifier_Letters2B0 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const unsigned char my_cat[80];
        static const Babylon::Bidir_Props my_bidir[80];
        static const unsigned char my_decomp[80];
        static const UCS2 my_decompStr[80][2];
        static const unsigned char my_lb[80];
        static const unsigned char my_ea[80];
        static const std::bitset<80> my_Extender;
        static const std::bitset<80> my_Other_Lowercase;
    }; // class Spacing_Modifier_Letters2B0

    const unsigned char Spacing_Modifier_Letters2B0::my_cat[] =
    {
        CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, 
        CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, 
        CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Sk, CAT_Sk, CAT_Sk, 
        CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Lm, CAT_Sk, 
        CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, 
        CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk, CAT_Sk
    };

    const Babylon::Bidir_Props Spacing_Modifier_Letters2B0::my_bidir[] =
    {
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
    };

    const unsigned char Spacing_Modifier_Letters2B0::my_decomp[] = {
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Spacing_Modifier_Letters2B0::my_decompStr[][2] =
    {
        { 0x00000068u, 0x00000000u }, { 0x00000266u, 0x00000000u },  // 000002B0
        { 0x0000006Au, 0x00000000u }, { 0x00000072u, 0x00000000u },  // 000002B2
        { 0x00000279u, 0x00000000u }, { 0x0000027Bu, 0x00000000u },  // 000002B4
        { 0x00000281u, 0x00000000u }, { 0x00000077u, 0x00000000u },  // 000002B6
        { 0x00000079u, 0x00000000u }, { 0x000002B9u, 0x00000000u },  // 000002B8
        { 0x000002BAu, 0x00000000u }, { 0x000002BBu, 0x00000000u },  // 000002BA
        { 0x000002BCu, 0x00000000u }, { 0x000002BDu, 0x00000000u },  // 000002BC
        { 0x000002BEu, 0x00000000u }, { 0x000002BFu, 0x00000000u },  // 000002BE
        { 0x000002C0u, 0x00000000u }, { 0x000002C1u, 0x00000000u },  // 000002C0
        { 0x000002C2u, 0x00000000u }, { 0x000002C3u, 0x00000000u },  // 000002C2
        { 0x000002C4u, 0x00000000u }, { 0x000002C5u, 0x00000000u },  // 000002C4
        { 0x000002C6u, 0x00000000u }, { 0x000002C7u, 0x00000000u },  // 000002C6
        { 0x000002C8u, 0x00000000u }, { 0x000002C9u, 0x00000000u },  // 000002C8
        { 0x000002CAu, 0x00000000u }, { 0x000002CBu, 0x00000000u },  // 000002CA
        { 0x000002CCu, 0x00000000u }, { 0x000002CDu, 0x00000000u },  // 000002CC
        { 0x000002CEu, 0x00000000u }, { 0x000002CFu, 0x00000000u },  // 000002CE
        { 0x000002D0u, 0x00000000u }, { 0x000002D1u, 0x00000000u },  // 000002D0
        { 0x000002D2u, 0x00000000u }, { 0x000002D3u, 0x00000000u },  // 000002D2
        { 0x000002D4u, 0x00000000u }, { 0x000002D5u, 0x00000000u },  // 000002D4
        { 0x000002D6u, 0x00000000u }, { 0x000002D7u, 0x00000000u },  // 000002D6
        { 0x00000020u, 0x00000306u }, { 0x00000020u, 0x00000307u },  // 000002D8
        { 0x00000020u, 0x0000030Au }, { 0x00000020u, 0x00000328u },  // 000002DA
        { 0x00000020u, 0x00000303u }, { 0x00000020u, 0x0000030Bu },  // 000002DC
        { 0x000002DEu, 0x00000000u }, { 0x000002DFu, 0x00000000u },  // 000002DE
        { 0x00000263u, 0x00000000u }, { 0x0000006Cu, 0x00000000u },  // 000002E0
        { 0x00000073u, 0x00000000u }, { 0x00000078u, 0x00000000u },  // 000002E2
        { 0x00000295u, 0x00000000u }, { 0x000002E5u, 0x00000000u },  // 000002E4
        { 0x000002E6u, 0x00000000u }, { 0x000002E7u, 0x00000000u },  // 000002E6
        { 0x000002E8u, 0x00000000u }, { 0x000002E9u, 0x00000000u },  // 000002E8
        { 0x000002EAu, 0x00000000u }, { 0x000002EBu, 0x00000000u },  // 000002EA
        { 0x000002ECu, 0x00000000u }, { 0x000002EDu, 0x00000000u },  // 000002EC
        { 0x000002EEu, 0x00000000u }, { 0x000002EFu, 0x00000000u },  // 000002EE
        { 0x000002F0u, 0x00000000u }, { 0x000002F1u, 0x00000000u },  // 000002F0
        { 0x000002F2u, 0x00000000u }, { 0x000002F3u, 0x00000000u },  // 000002F2
        { 0x000002F4u, 0x00000000u }, { 0x000002F5u, 0x00000000u },  // 000002F4
        { 0x000002F6u, 0x00000000u }, { 0x000002F7u, 0x00000000u },  // 000002F6
        { 0x000002F8u, 0x00000000u }, { 0x000002F9u, 0x00000000u },  // 000002F8
        { 0x000002FAu, 0x00000000u }, { 0x000002FBu, 0x00000000u },  // 000002FA
        { 0x000002FCu, 0x00000000u }, { 0x000002FDu, 0x00000000u },  // 000002FC
        { 0x000002FEu, 0x00000000u }, { 0x000002FFu, 0x00000000u }
    };

    const unsigned char Spacing_Modifier_Letters2B0::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, 
        LB_BB, LB_AI, LB_AI, LB_AI, LB_BB, LB_AI, LB_AL, LB_AL, 
        LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AI, LB_AI, LB_AI, LB_AI, LB_AL, LB_AI, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const unsigned char Spacing_Modifier_Letters2B0::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
    };

    const std::bitset<80> Spacing_Modifier_Letters2B0::my_Extender(std::string("00000000000000000000000000000000000000000000001100000000000000000000000000000000"));

    const std::bitset<80> Spacing_Modifier_Letters2B0::my_Other_Lowercase(std::string("00000000000000000000000000011111000000000000000000000000000000110000000111111111"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Spacing_Modifier_Letters2B0);
