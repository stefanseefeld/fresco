/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp 2070-209F.cc
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


namespace Babylon
{
  namespace Module
  {
    class Superscripts_and_Subscripts2070 : public Babylon::Block
    {
      public:
        void clean() { };

        Superscripts_and_Subscripts2070() :
        my_first_letter(0x2070),
        my_last_letter(0x209F)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~Superscripts_and_Subscripts2070() { }

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
        return "Superscripts and Subscripts";
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
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x2070u:
                return 0;
            case 0x2074u:
                return 4;
            case 0x2075u:
                return 5;
            case 0x2076u:
                return 6;
            case 0x2077u:
                return 7;
            case 0x2078u:
                return 8;
            case 0x2079u:
                return 9;
            case 0x2080u:
                return 0;
            case 0x2081u:
                return 1;
            case 0x2082u:
                return 2;
            case 0x2083u:
                return 3;
            case 0x2084u:
                return 4;
            case 0x2085u:
                return 5;
            case 0x2086u:
                return 6;
            case 0x2087u:
                return 7;
            case 0x2088u:
                return 8;
            case 0x2089u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x2070u:
            case 0x2074u:
            case 0x2075u:
            case 0x2076u:
            case 0x2077u:
            case 0x2078u:
            case 0x2079u:
            case 0x2080u:
            case 0x2081u:
            case 0x2082u:
            case 0x2083u:
            case 0x2084u:
            case 0x2085u:
            case 0x2086u:
            case 0x2087u:
            case 0x2088u:
            case 0x2089u:
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
            case 0x2070u:
                return 0.000000;
            case 0x2074u:
                return 4.000000;
            case 0x2075u:
                return 5.000000;
            case 0x2076u:
                return 6.000000;
            case 0x2077u:
                return 7.000000;
            case 0x2078u:
                return 8.000000;
            case 0x2079u:
                return 9.000000;
            case 0x2080u:
                return 0.000000;
            case 0x2081u:
                return 1.000000;
            case 0x2082u:
                return 2.000000;
            case 0x2083u:
                return 3.000000;
            case 0x2084u:
                return 4.000000;
            case 0x2085u:
                return 5.000000;
            case 0x2086u:
                return 6.000000;
            case 0x2087u:
                return 7.000000;
            case 0x2088u:
                return 8.000000;
            case 0x2089u:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x2070u:
            case 0x2074u:
            case 0x2075u:
            case 0x2076u:
            case 0x2077u:
            case 0x2078u:
            case 0x2079u:
            case 0x2080u:
            case 0x2081u:
            case 0x2082u:
            case 0x2083u:
            case 0x2084u:
            case 0x2085u:
            case 0x2086u:
            case 0x2087u:
            case 0x2088u:
            case 0x2089u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Superscripts_and_Subscripts2070::my_cat[uc - my_first_letter]);
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
            return Superscripts_and_Subscripts2070::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Superscripts_and_Subscripts2070::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(1);
            us[0] = Superscripts_and_Subscripts2070::my_decompStr[uc - my_first_letter];
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
            return Babylon::Line_Break(Superscripts_and_Subscripts2070::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Superscripts_and_Subscripts2070::my_ea[uc - my_first_letter]);
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
            return 0;
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
            return my_Soft_Dotted.test(uc - my_first_letter);
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
        Superscripts_and_Subscripts2070(const Superscripts_and_Subscripts2070 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<48> my_is_defined;
        static const unsigned char my_cat[48];
        static const Babylon::Bidir_Props my_bidir[48];
        static const unsigned char my_decomp[48];
        static const UCS2 my_decompStr[48];
        static const std::bitset<48> my_mirror;
        static const unsigned char my_lb[48];
        static const unsigned char my_ea[48];
        static const std::bitset<48> my_Dash;
        static const std::bitset<48> my_Other_Math;
        static const std::bitset<48> my_Soft_Dotted;
    }; // class Superscripts_and_Subscripts2070

    const std::bitset<48> Superscripts_and_Subscripts2070::my_is_defined(std::string("000000000000000001111111111111111111111111110011"));

    const unsigned char Superscripts_and_Subscripts2070::my_cat[] =
    {
        CAT_No, CAT_Ll, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Ps, CAT_Pe, CAT_Ll, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Ps, CAT_Pe, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No
    };

    const Babylon::Bidir_Props Superscripts_and_Subscripts2070::my_bidir[] =
    {
        BIDIR_EN, BIDIR_L, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_ET, BIDIR_ET, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_ET, BIDIR_ET, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN
    };

    const unsigned char Superscripts_and_Subscripts2070::my_decomp[] = {
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, 
        DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, 
        DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, 
        DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Superscripts_and_Subscripts2070::my_decompStr[] =
    {
        0x00000030u, 0x00000069u, 0x00002072u, 0x00002073u,  // 00002070
        0x00000034u, 0x00000035u, 0x00000036u, 0x00000037u,  // 00002074
        0x00000038u, 0x00000039u, 0x0000002Bu, 0x00002212u,  // 00002078
        0x0000003Du, 0x00000028u, 0x00000029u, 0x0000006Eu,  // 0000207C
        0x00000030u, 0x00000031u, 0x00000032u, 0x00000033u,  // 00002080
        0x00000034u, 0x00000035u, 0x00000036u, 0x00000037u,  // 00002084
        0x00000038u, 0x00000039u, 0x0000002Bu, 0x00002212u,  // 00002088
        0x0000003Du, 0x00000028u, 0x00000029u, 0x0000208Fu,  // 0000208C
        0x00002090u, 0x00002091u, 0x00002092u, 0x00002093u,  // 00002090
        0x00002094u, 0x00002095u, 0x00002096u, 0x00002097u,  // 00002094
        0x00002098u, 0x00002099u, 0x0000209Au, 0x0000209Bu,  // 00002098
        0x0000209Cu, 0x0000209Du, 0x0000209Eu, 0x0000209Fu
    };

    const std::bitset<48> Superscripts_and_Subscripts2070::my_mirror(std::string("000000000000000001100000000000000110000000000000"));

    const unsigned char Superscripts_and_Subscripts2070::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, LB_AI, 
        LB_AL, LB_AI, LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const unsigned char Superscripts_and_Subscripts2070::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
    };

    const std::bitset<48> Superscripts_and_Subscripts2070::my_Dash(std::string("000000000000000000001000000000000000100000000000"));

    const std::bitset<48> Superscripts_and_Subscripts2070::my_Other_Math(std::string("000000000000000001100000000000000110000000000000"));

    const std::bitset<48> Superscripts_and_Subscripts2070::my_Soft_Dotted(std::string("000000000000000000000000000000000000000000000010"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Superscripts_and_Subscripts2070);
