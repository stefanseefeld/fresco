/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 3000-303F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:48 +0200.
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
    class CJK_Symbols_and_Punctuation3000 : public Babylon::Block
    {
      public:
        void clean() { };

        CJK_Symbols_and_Punctuation3000() :
	    my_first_letter(0x3000),
	    my_last_letter(0x303F)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~CJK_Symbols_and_Punctuation3000() { }

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
	    return "CJK Symbols and Punctuation";
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
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x3007u:
                return 0.000000;
            case 0x3021u:
                return 1.000000;
            case 0x3022u:
                return 2.000000;
            case 0x3023u:
                return 3.000000;
            case 0x3024u:
                return 4.000000;
            case 0x3025u:
                return 5.000000;
            case 0x3026u:
                return 6.000000;
            case 0x3027u:
                return 7.000000;
            case 0x3028u:
                return 8.000000;
            case 0x3029u:
                return 9.000000;
            case 0x3038u:
                return 10.000000;
            case 0x3039u:
                return 20.000000;
            case 0x303Au:
                return 30.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x3007u:
            case 0x3021u:
            case 0x3022u:
            case 0x3023u:
            case 0x3024u:
            case 0x3025u:
            case 0x3026u:
            case 0x3027u:
            case 0x3028u:
            case 0x3029u:
            case 0x3038u:
            case 0x3039u:
            case 0x303Au:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(CJK_Symbols_and_Punctuation3000::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(CJK_Symbols_and_Punctuation3000::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return CJK_Symbols_and_Punctuation3000::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(CJK_Symbols_and_Punctuation3000::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(1);
            us[0] = CJK_Symbols_and_Punctuation3000::my_decompStr[uc - my_first_letter];
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
            return Babylon::Line_Break(CJK_Symbols_and_Punctuation3000::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(CJK_Symbols_and_Punctuation3000::my_ea[uc - my_first_letter]);
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
            return my_White_Space.test(uc - my_first_letter);
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
            return my_Terminal_Punctuation.test(uc - my_first_letter);
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
            return my_Ideographic.test(uc - my_first_letter);
        }

        bool is_Diacritic(const UCS4 uc) const
        {
            return my_Diacritic.test(uc - my_first_letter);
        }

        bool is_Extender(const UCS4 uc) const
        {
            return my_Extender.test(uc - my_first_letter);
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
        CJK_Symbols_and_Punctuation3000(const CJK_Symbols_and_Punctuation3000 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const unsigned char my_cat[64];
        static const unsigned char my_comb_cl[64];
        static const Babylon::Bidir_Props my_bidir[64];
        static const unsigned char my_decomp[64];
        static const UCS4 my_decompStr[64];
        static const std::bitset<64> my_mirror;
        static const unsigned char my_lb[64];
        static const unsigned char my_ea[64];
        static const std::bitset<64> my_White_Space;
        static const std::bitset<64> my_Dash;
        static const std::bitset<64> my_Quotation_Mark;
        static const std::bitset<64> my_Terminal_Punctuation;
        static const std::bitset<64> my_Ideographic;
        static const std::bitset<64> my_Diacritic;
        static const std::bitset<64> my_Extender;
    }; // class CJK_Symbols_and_Punctuation3000

    const unsigned char CJK_Symbols_and_Punctuation3000::my_cat[] =
    {
        CAT_Zs, CAT_Po, CAT_Po, CAT_Po, CAT_So, CAT_Lm, CAT_Lo, CAT_Nl, 
        CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, 
        CAT_Ps, CAT_Pe, CAT_So, CAT_So, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, 
        CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Pd, CAT_Ps, CAT_Pe, CAT_Pe, 
        CAT_So, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, CAT_Nl, 
        CAT_Nl, CAT_Nl, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Pd, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_So, CAT_So, 
        CAT_Nl, CAT_Nl, CAT_Nl, CAT_Lm, CAT_Lo, CAT_Po, CAT_So, CAT_So
    };

    const unsigned char CJK_Symbols_and_Punctuation3000::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 218, 228, 232, 222, 224, 224, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props CJK_Symbols_and_Punctuation3000::my_bidir[] =
    {
        BIDIR_WS, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON
    };

    const unsigned char CJK_Symbols_and_Punctuation3000::my_decomp[] = {
        DECOMP_WIDE, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS4 CJK_Symbols_and_Punctuation3000::my_decompStr[] =
    {
        0x00000020u, 0x00003001u, 0x00003002u, 0x00003003u,  // 00003000
        0x00003004u, 0x00003005u, 0x00003006u, 0x00003007u,  // 00003004
        0x00003008u, 0x00003009u, 0x0000300Au, 0x0000300Bu,  // 00003008
        0x0000300Cu, 0x0000300Du, 0x0000300Eu, 0x0000300Fu,  // 0000300C
        0x00003010u, 0x00003011u, 0x00003012u, 0x00003013u,  // 00003010
        0x00003014u, 0x00003015u, 0x00003016u, 0x00003017u,  // 00003014
        0x00003018u, 0x00003019u, 0x0000301Au, 0x0000301Bu,  // 00003018
        0x0000301Cu, 0x0000301Du, 0x0000301Eu, 0x0000301Fu,  // 0000301C
        0x00003020u, 0x00003021u, 0x00003022u, 0x00003023u,  // 00003020
        0x00003024u, 0x00003025u, 0x00003026u, 0x00003027u,  // 00003024
        0x00003028u, 0x00003029u, 0x0000302Au, 0x0000302Bu,  // 00003028
        0x0000302Cu, 0x0000302Du, 0x0000302Eu, 0x0000302Fu,  // 0000302C
        0x00003030u, 0x00003031u, 0x00003032u, 0x00003033u,  // 00003030
        0x00003034u, 0x00003035u, 0x00003012u, 0x00003037u,  // 00003034
        0x00005341u, 0x00005344u, 0x00005345u, 0x0000303Bu,  // 00003038
        0x0000303Cu, 0x0000303Du, 0x0000303Eu, 0x0000303Fu
    };

    const std::bitset<64> CJK_Symbols_and_Punctuation3000::my_mirror(std::string("0000000000000000000000000000000000001111111100111111111100000000"));

    const unsigned char CJK_Symbols_and_Punctuation3000::my_lb[] =
    {
        LB_ID, LB_CL, LB_CL, LB_ID, LB_ID, LB_NS, LB_ID, LB_ID, 
        LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, 
        LB_OP, LB_CL, LB_ID, LB_ID, LB_OP, LB_CL, LB_OP, LB_CL, 
        LB_OP, LB_CL, LB_OP, LB_CL, LB_NS, LB_OP, LB_CL, LB_CL, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_NS, LB_NS, LB_ID, LB_ID, LB_ID
    };

    const unsigned char CJK_Symbols_and_Punctuation3000::my_ea[] =
    {
        EA_WIDTH_F, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, 
        EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_W, EA_WIDTH_N
    };

    const std::bitset<64> CJK_Symbols_and_Punctuation3000::my_White_Space(std::string("0000000000000000000000000000000000000000000000000000000000000001"));

    const std::bitset<64> CJK_Symbols_and_Punctuation3000::my_Dash(std::string("0000000000000001000000000000000000010000000000000000000000000000"));

    const std::bitset<64> CJK_Symbols_and_Punctuation3000::my_Quotation_Mark(std::string("0000000000000000000000000000000011100000000000001111000000000000"));

    const std::bitset<64> CJK_Symbols_and_Punctuation3000::my_Terminal_Punctuation(std::string("0000000000000000000000000000000000000000000000000000000000000110"));

    const std::bitset<64> CJK_Symbols_and_Punctuation3000::my_Ideographic(std::string("0000011100000000000000111111111000000000000000000000000011000000"));

    const std::bitset<64> CJK_Symbols_and_Punctuation3000::my_Diacritic(std::string("0000000000000000111111000000000000000000000000000000000000000000"));

    const std::bitset<64> CJK_Symbols_and_Punctuation3000::my_Extender(std::string("0000000000111110000000000000000000000000000000000000000000100000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::CJK_Symbols_and_Punctuation3000);
