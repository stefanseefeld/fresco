/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp FE30-FE4F.cc
 *
 * This source file is a part of the Fresco Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 28 Jan 2004 20:49:50 +0100.
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
    class CJK_Compatibility_FormsFE30 : public Babylon::Block
    {
      public:
        void clean() { };

        CJK_Compatibility_FormsFE30() :
        my_first_letter(0xFE30),
        my_last_letter(0xFE4F)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~CJK_Compatibility_FormsFE30() { }

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
        return "CJK Compatibility Forms";
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
            return Babylon::Gen_Cat(CJK_Compatibility_FormsFE30::my_cat[uc - my_first_letter]);
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
            return Babylon::Char_Decomp(CJK_Compatibility_FormsFE30::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(1);
            us[0] = CJK_Compatibility_FormsFE30::my_decompStr[uc - my_first_letter];
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
            return Babylon::Line_Break(CJK_Compatibility_FormsFE30::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_W);
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
            return my_Dash.test(uc - my_first_letter);
        }

        bool is_Hyphen(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Quotation_Mark(const UCS4 uc) const
        {
            return my_Quotation_Mark.test(uc - my_first_letter);
        }

        bool is_Terminal_Punctuation(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Math(const UCS4 uc) const
        {
            return my_Other_Math.test(uc - my_first_letter);
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
        CJK_Compatibility_FormsFE30(const CJK_Compatibility_FormsFE30 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const unsigned char my_cat[32];
        static const unsigned char my_decomp[32];
        static const UCS4 my_decompStr[32];
        static const unsigned char my_lb[32];
        static const std::bitset<32> my_Dash;
        static const std::bitset<32> my_Quotation_Mark;
        static const std::bitset<32> my_Other_Math;
    }; // class CJK_Compatibility_FormsFE30

    const unsigned char CJK_Compatibility_FormsFE30::my_cat[] =
    {
        CAT_Po, CAT_Pd, CAT_Pd, CAT_Pc, CAT_Pc, CAT_Ps, CAT_Pe, CAT_Ps, 
        CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, 
        CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Po, CAT_Po, CAT_Ps, 
        CAT_Pe, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Pc, CAT_Pc, CAT_Pc
    };

    const unsigned char CJK_Compatibility_FormsFE30::my_decomp[] = {
        DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, 
        DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, 
        DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, 
        DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, 
        DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, DECOMP_VERTICAL, 
        DECOMP_VERTICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_VERTICAL, 
        DECOMP_VERTICAL, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT
    };

    const UCS4 CJK_Compatibility_FormsFE30::my_decompStr[] =
    {
        0x00002025u, 0x00002014u, 0x00002013u, 0x0000005Fu,  // 0000FE30
        0x0000005Fu, 0x00000028u, 0x00000029u, 0x0000007Bu,  // 0000FE34
        0x0000007Du, 0x00003014u, 0x00003015u, 0x00003010u,  // 0000FE38
        0x00003011u, 0x0000300Au, 0x0000300Bu, 0x00003008u,  // 0000FE3C
        0x00003009u, 0x0000300Cu, 0x0000300Du, 0x0000300Eu,  // 0000FE40
        0x0000300Fu, 0x0000FE45u, 0x0000FE46u, 0x0000005Bu,  // 0000FE44
        0x0000005Du, 0x0000203Eu, 0x0000203Eu, 0x0000203Eu,  // 0000FE48
        0x0000203Eu, 0x0000005Fu, 0x0000005Fu, 0x0000005Fu
    };

    const unsigned char CJK_Compatibility_FormsFE30::my_lb[] =
    {
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_OP, LB_CL, LB_OP, 
        LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, 
        LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_ID, LB_ID, LB_OP, 
        LB_CL, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID
    };

    const std::bitset<32> CJK_Compatibility_FormsFE30::my_Dash(std::string("00000000000000000000000000000110"));

    const std::bitset<32> CJK_Compatibility_FormsFE30::my_Quotation_Mark(std::string("00000000000111100000000000000000"));

    const std::bitset<32> CJK_Compatibility_FormsFE30::my_Other_Math(std::string("00000001100000000000000111100000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::CJK_Compatibility_FormsFE30);
