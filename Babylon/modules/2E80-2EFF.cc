/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 2E80-2EFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:56:03 +0200.
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
    class CJK_Radicals_Supplement2E80 : public Babylon::Block
    {
      public:
        void clean() { };

        CJK_Radicals_Supplement2E80() :
	    my_first_letter(0x2E80),
	    my_last_letter(0x2EFF)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~CJK_Radicals_Supplement2E80() { }

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
	    return "CJK Radicals Supplement";
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
            return Babylon::Gen_Cat(CAT_So);
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
            return Babylon::Char_Decomp(CJK_Radicals_Supplement2E80::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(1);
            us[0] = CJK_Radicals_Supplement2E80::my_decompStr[uc - my_first_letter];
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
            return Babylon::Line_Break(LB_ID);
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
            return my_Radical.test(uc - my_first_letter);
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

      private:
        // functions
        CJK_Radicals_Supplement2E80(const CJK_Radicals_Supplement2E80 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<128> my_is_defined;
        static const unsigned char my_decomp[128];
        static const UCS4 my_decompStr[128];
        static const std::bitset<128> my_Radical;
    }; // class CJK_Radicals_Supplement2E80

    const std::bitset<128> CJK_Radicals_Supplement2E80::my_is_defined(std::string("00000000000011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111011111111111111111111111111"));

    const unsigned char CJK_Radicals_Supplement2E80::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS4 CJK_Radicals_Supplement2E80::my_decompStr[] =
    {
        0x00002E80u, 0x00002E81u, 0x00002E82u, 0x00002E83u,  // 00002E80
        0x00002E84u, 0x00002E85u, 0x00002E86u, 0x00002E87u,  // 00002E84
        0x00002E88u, 0x00002E89u, 0x00002E8Au, 0x00002E8Bu,  // 00002E88
        0x00002E8Cu, 0x00002E8Du, 0x00002E8Eu, 0x00002E8Fu,  // 00002E8C
        0x00002E90u, 0x00002E91u, 0x00002E92u, 0x00002E93u,  // 00002E90
        0x00002E94u, 0x00002E95u, 0x00002E96u, 0x00002E97u,  // 00002E94
        0x00002E98u, 0x00002E99u, 0x00002E9Au, 0x00002E9Bu,  // 00002E98
        0x00002E9Cu, 0x00002E9Du, 0x00002E9Eu, 0x00006BCDu,  // 00002E9C
        0x00002EA0u, 0x00002EA1u, 0x00002EA2u, 0x00002EA3u,  // 00002EA0
        0x00002EA4u, 0x00002EA5u, 0x00002EA6u, 0x00002EA7u,  // 00002EA4
        0x00002EA8u, 0x00002EA9u, 0x00002EAAu, 0x00002EABu,  // 00002EA8
        0x00002EACu, 0x00002EADu, 0x00002EAEu, 0x00002EAFu,  // 00002EAC
        0x00002EB0u, 0x00002EB1u, 0x00002EB2u, 0x00002EB3u,  // 00002EB0
        0x00002EB4u, 0x00002EB5u, 0x00002EB6u, 0x00002EB7u,  // 00002EB4
        0x00002EB8u, 0x00002EB9u, 0x00002EBAu, 0x00002EBBu,  // 00002EB8
        0x00002EBCu, 0x00002EBDu, 0x00002EBEu, 0x00002EBFu,  // 00002EBC
        0x00002EC0u, 0x00002EC1u, 0x00002EC2u, 0x00002EC3u,  // 00002EC0
        0x00002EC4u, 0x00002EC5u, 0x00002EC6u, 0x00002EC7u,  // 00002EC4
        0x00002EC8u, 0x00002EC9u, 0x00002ECAu, 0x00002ECBu,  // 00002EC8
        0x00002ECCu, 0x00002ECDu, 0x00002ECEu, 0x00002ECFu,  // 00002ECC
        0x00002ED0u, 0x00002ED1u, 0x00002ED2u, 0x00002ED3u,  // 00002ED0
        0x00002ED4u, 0x00002ED5u, 0x00002ED6u, 0x00002ED7u,  // 00002ED4
        0x00002ED8u, 0x00002ED9u, 0x00002EDAu, 0x00002EDBu,  // 00002ED8
        0x00002EDCu, 0x00002EDDu, 0x00002EDEu, 0x00002EDFu,  // 00002EDC
        0x00002EE0u, 0x00002EE1u, 0x00002EE2u, 0x00002EE3u,  // 00002EE0
        0x00002EE4u, 0x00002EE5u, 0x00002EE6u, 0x00002EE7u,  // 00002EE4
        0x00002EE8u, 0x00002EE9u, 0x00002EEAu, 0x00002EEBu,  // 00002EE8
        0x00002EECu, 0x00002EEDu, 0x00002EEEu, 0x00002EEFu,  // 00002EEC
        0x00002EF0u, 0x00002EF1u, 0x00002EF2u, 0x00009F9Fu,  // 00002EF0
        0x00002EF4u, 0x00002EF5u, 0x00002EF6u, 0x00002EF7u,  // 00002EF4
        0x00002EF8u, 0x00002EF9u, 0x00002EFAu, 0x00002EFBu,  // 00002EF8
        0x00002EFCu, 0x00002EFDu, 0x00002EFEu, 0x00002EFFu
    };

    const std::bitset<128> CJK_Radicals_Supplement2E80::my_Radical(std::string("00000000000011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111011111111111111111111111111"));

  }; // namespace
}; // namespace

dload(Babylon::Module::CJK_Radicals_Supplement2E80);
