/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp FE50-FE6F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:10:26 +0200.
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
    class Small_Form_VariantsFE50 : public Babylon::Block
    {
      public:
        void clean() { };

        Small_Form_VariantsFE50() :
        my_first_letter(0xFE50),
        my_last_letter(0xFE6F)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~Small_Form_VariantsFE50() { }

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
        return "Small Form Variants";
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
            return Babylon::Gen_Cat(Small_Form_VariantsFE50::my_cat[uc - my_first_letter]);
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
            return Small_Form_VariantsFE50::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Small_Form_VariantsFE50::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(1);
            us[0] = Small_Form_VariantsFE50::my_decompStr[uc - my_first_letter];
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
            return Babylon::Line_Break(Small_Form_VariantsFE50::my_lb[uc - my_first_letter]);
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
            return my_Hyphen.test(uc - my_first_letter);
        }

        bool is_Quotation_Mark(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Terminal_Punctuation(const UCS4 uc) const
        {
            return my_Terminal_Punctuation.test(uc - my_first_letter);
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
        Small_Form_VariantsFE50(const Small_Form_VariantsFE50 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<32> my_is_defined;
        static const unsigned char my_cat[32];
        static const Babylon::Bidir_Props my_bidir[32];
        static const unsigned char my_decomp[32];
        static const UCS4 my_decompStr[32];
        static const unsigned char my_lb[32];
        static const std::bitset<32> my_Dash;
        static const std::bitset<32> my_Hyphen;
        static const std::bitset<32> my_Terminal_Punctuation;
        static const std::bitset<32> my_Other_Math;
    }; // class Small_Form_VariantsFE50

    const std::bitset<32> Small_Form_VariantsFE50::my_is_defined(std::string("00001111011111111111111111110111"));

    const unsigned char Small_Form_VariantsFE50::my_cat[] =
    {
        CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
        CAT_Pd, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Po, 
        CAT_Po, CAT_Po, CAT_Sm, CAT_Pd, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Po, 
        CAT_Po, CAT_Sc, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po
    };

    const Babylon::Bidir_Props Small_Form_VariantsFE50::my_bidir[] =
    {
        BIDIR_CS, BIDIR_ON, BIDIR_CS, BIDIR_CS, 
        BIDIR_ON, BIDIR_CS, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ET, 
        BIDIR_ON, BIDIR_ON, BIDIR_ET, BIDIR_ET, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_CS, 
        BIDIR_ON, BIDIR_ET, BIDIR_ET, BIDIR_ON, 
        BIDIR_CS, BIDIR_CS, BIDIR_CS, BIDIR_CS
    };

    const unsigned char Small_Form_VariantsFE50::my_decomp[] = {
        DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_CANONICAL, 
        DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, 
        DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, 
        DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, 
        DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, 
        DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_CANONICAL, 
        DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, DECOMP_SMALL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS4 Small_Form_VariantsFE50::my_decompStr[] =
    {
        0x0000002Cu, 0x00003001u, 0x0000002Eu, 0x0000FE53u,  // 0000FE50
        0x0000003Bu, 0x0000003Au, 0x0000003Fu, 0x00000021u,  // 0000FE54
        0x00002014u, 0x00000028u, 0x00000029u, 0x0000007Bu,  // 0000FE58
        0x0000007Du, 0x00003014u, 0x00003015u, 0x00000023u,  // 0000FE5C
        0x00000026u, 0x0000002Au, 0x0000002Bu, 0x0000002Du,  // 0000FE60
        0x0000003Cu, 0x0000003Eu, 0x0000003Du, 0x0000FE67u,  // 0000FE64
        0x0000005Cu, 0x00000024u, 0x00000025u, 0x00000040u,  // 0000FE68
        0x0000FE6Cu, 0x0000FE6Du, 0x0000FE6Eu, 0x0000FE6Fu
    };

    const unsigned char Small_Form_VariantsFE50::my_lb[] =
    {
        LB_CL, LB_ID, LB_CL, LB_CL, LB_NS, LB_NS, LB_EX, LB_EX, 
        LB_ID, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_CL, 
        LB_ID, LB_PR, LB_PO, LB_ID, LB_CL, LB_CL, LB_CL, LB_CL
    };

    const std::bitset<32> Small_Form_VariantsFE50::my_Dash(std::string("00000000000010000000000100000000"));

    const std::bitset<32> Small_Form_VariantsFE50::my_Hyphen(std::string("00000000000010000000000000000000"));

    const std::bitset<32> Small_Form_VariantsFE50::my_Terminal_Punctuation(std::string("00000000000000000000000011110111"));

    const std::bitset<32> Small_Form_VariantsFE50::my_Other_Math(std::string("00000001000010100001111000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Small_Form_VariantsFE50);
