/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 20A0-20CF.cc
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


namespace Babylon
{
  namespace Module
  {
    class Currency_Symbols20A0 : public Babylon::Block
    {
      public:
        void clean() { };

        Currency_Symbols20A0() :
        my_first_letter(0x20A0),
        my_last_letter(0x20CF)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~Currency_Symbols20A0() { }

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
        return "Currency Symbols";
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
            return Babylon::Gen_Cat(CAT_Sc);
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
            return BIDIR_ET;
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Currency_Symbols20A0::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Currency_Symbols20A0::my_decompStr[uc - my_first_letter][0];
            us[1] = Currency_Symbols20A0::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Currency_Symbols20A0::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Currency_Symbols20A0::my_ea[uc - my_first_letter]);
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
        Currency_Symbols20A0(const Currency_Symbols20A0 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<48> my_is_defined;
        static const unsigned char my_decomp[48];
        static const UCS2 my_decompStr[48][2];
        static const unsigned char my_lb[48];
        static const unsigned char my_ea[48];
    }; // class Currency_Symbols20A0

    const std::bitset<48> Currency_Symbols20A0::my_is_defined(std::string("000000000000000000000000000000111111111111111111"));

    const unsigned char Currency_Symbols20A0::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
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

    const UCS2 Currency_Symbols20A0::my_decompStr[][2] =
    {
        { 0x000020A0u, 0x00000000u }, { 0x000020A1u, 0x00000000u },  // 000020A0
        { 0x000020A2u, 0x00000000u }, { 0x000020A3u, 0x00000000u },  // 000020A2
        { 0x000020A4u, 0x00000000u }, { 0x000020A5u, 0x00000000u },  // 000020A4
        { 0x000020A6u, 0x00000000u }, { 0x000020A7u, 0x00000000u },  // 000020A6
        { 0x00000052u, 0x00000073u }, { 0x000020A9u, 0x00000000u },  // 000020A8
        { 0x000020AAu, 0x00000000u }, { 0x000020ABu, 0x00000000u },  // 000020AA
        { 0x000020ACu, 0x00000000u }, { 0x000020ADu, 0x00000000u },  // 000020AC
        { 0x000020AEu, 0x00000000u }, { 0x000020AFu, 0x00000000u },  // 000020AE
        { 0x000020B0u, 0x00000000u }, { 0x000020B1u, 0x00000000u },  // 000020B0
        { 0x000020B2u, 0x00000000u }, { 0x000020B3u, 0x00000000u },  // 000020B2
        { 0x000020B4u, 0x00000000u }, { 0x000020B5u, 0x00000000u },  // 000020B4
        { 0x000020B6u, 0x00000000u }, { 0x000020B7u, 0x00000000u },  // 000020B6
        { 0x000020B8u, 0x00000000u }, { 0x000020B9u, 0x00000000u },  // 000020B8
        { 0x000020BAu, 0x00000000u }, { 0x000020BBu, 0x00000000u },  // 000020BA
        { 0x000020BCu, 0x00000000u }, { 0x000020BDu, 0x00000000u },  // 000020BC
        { 0x000020BEu, 0x00000000u }, { 0x000020BFu, 0x00000000u },  // 000020BE
        { 0x000020C0u, 0x00000000u }, { 0x000020C1u, 0x00000000u },  // 000020C0
        { 0x000020C2u, 0x00000000u }, { 0x000020C3u, 0x00000000u },  // 000020C2
        { 0x000020C4u, 0x00000000u }, { 0x000020C5u, 0x00000000u },  // 000020C4
        { 0x000020C6u, 0x00000000u }, { 0x000020C7u, 0x00000000u },  // 000020C6
        { 0x000020C8u, 0x00000000u }, { 0x000020C9u, 0x00000000u },  // 000020C8
        { 0x000020CAu, 0x00000000u }, { 0x000020CBu, 0x00000000u },  // 000020CA
        { 0x000020CCu, 0x00000000u }, { 0x000020CDu, 0x00000000u },  // 000020CC
        { 0x000020CEu, 0x00000000u }, { 0x000020CFu, 0x00000000u }
    };

    const unsigned char Currency_Symbols20A0::my_lb[] =
    {
        LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PO, 
        LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, 
        LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, 
        LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, 
        LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, 
        LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR, LB_PR
    };

    const unsigned char Currency_Symbols20A0::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_H, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
    };

  }; // namespace
}; // namespace

dload(Babylon::Module::Currency_Symbols20A0);
