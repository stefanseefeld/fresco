/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 1D00-1D7F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:55:59 +0200.
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
    class Phonetic_Extensions1D00 : public Babylon::Block
    {
      public:
        void clean() { };

        Phonetic_Extensions1D00() :
	    my_first_letter(0x1D00),
	    my_last_letter(0x1D7F)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~Phonetic_Extensions1D00() { }

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
	    return "Phonetic Extensions";
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
            return Babylon::Gen_Cat(Phonetic_Extensions1D00::my_cat[uc - my_first_letter]);
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
            return BIDIR_L;
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Phonetic_Extensions1D00::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(1);
            us[0] = Phonetic_Extensions1D00::my_decompStr[uc - my_first_letter];
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
            return Babylon::Line_Break(LB_AL);
    }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_N);
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
            return my_Diacritic.test(uc - my_first_letter);
        }

        bool is_Extender(const UCS4 uc) const
        {
            return 0;
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

      private:
        // functions
        Phonetic_Extensions1D00(const Phonetic_Extensions1D00 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<128> my_is_defined;
        static const unsigned char my_cat[128];
        static const unsigned char my_decomp[128];
        static const UCS2 my_decompStr[128];
        static const std::bitset<128> my_Diacritic;
        static const std::bitset<128> my_Other_Lowercase;
        static const std::bitset<128> my_Soft_Dotted;
    }; // class Phonetic_Extensions1D00

    const std::bitset<128> Phonetic_Extensions1D00::my_is_defined(std::string("00000000000000000000111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const unsigned char Phonetic_Extensions1D00::my_cat[] =
    {
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, CAT_Lm, 
        CAT_Lm, CAT_Lm, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll
    };

    const unsigned char Phonetic_Extensions1D00::my_decomp[] = {
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
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_CANONICAL, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_CANONICAL, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_CANONICAL, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUPER, 
        DECOMP_SUPER, DECOMP_SUPER, DECOMP_SUB, DECOMP_SUB, 
        DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, 
        DECOMP_SUB, DECOMP_SUB, DECOMP_SUB, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Phonetic_Extensions1D00::my_decompStr[] =
    {
        0x00001D00u, 0x00001D01u, 0x00001D02u, 0x00001D03u,  // 00001D00
        0x00001D04u, 0x00001D05u, 0x00001D06u, 0x00001D07u,  // 00001D04
        0x00001D08u, 0x00001D09u, 0x00001D0Au, 0x00001D0Bu,  // 00001D08
        0x00001D0Cu, 0x00001D0Du, 0x00001D0Eu, 0x00001D0Fu,  // 00001D0C
        0x00001D10u, 0x00001D11u, 0x00001D12u, 0x00001D13u,  // 00001D10
        0x00001D14u, 0x00001D15u, 0x00001D16u, 0x00001D17u,  // 00001D14
        0x00001D18u, 0x00001D19u, 0x00001D1Au, 0x00001D1Bu,  // 00001D18
        0x00001D1Cu, 0x00001D1Du, 0x00001D1Eu, 0x00001D1Fu,  // 00001D1C
        0x00001D20u, 0x00001D21u, 0x00001D22u, 0x00001D23u,  // 00001D20
        0x00001D24u, 0x00001D25u, 0x00001D26u, 0x00001D27u,  // 00001D24
        0x00001D28u, 0x00001D29u, 0x00001D2Au, 0x00001D2Bu,  // 00001D28
        0x00000041u, 0x000000C6u, 0x00000042u, 0x00001D2Fu,  // 00001D2C
        0x00000044u, 0x00000045u, 0x0000018Eu, 0x00000047u,  // 00001D30
        0x00000048u, 0x00000049u, 0x0000004Au, 0x0000004Bu,  // 00001D34
        0x0000004Cu, 0x0000004Du, 0x0000004Eu, 0x00001D3Bu,  // 00001D38
        0x0000004Fu, 0x00000222u, 0x00000050u, 0x00000052u,  // 00001D3C
        0x00000054u, 0x00000055u, 0x00000057u, 0x00000061u,  // 00001D40
        0x00000250u, 0x00000251u, 0x00001D02u, 0x00000062u,  // 00001D44
        0x00000064u, 0x00000065u, 0x00000259u, 0x0000025Bu,  // 00001D48
        0x0000025Cu, 0x00000067u, 0x00001D4Eu, 0x0000006Bu,  // 00001D4C
        0x0000006Du, 0x0000014Bu, 0x0000006Fu, 0x00000254u,  // 00001D50
        0x00001D16u, 0x00001D17u, 0x00000070u, 0x00000074u,  // 00001D54
        0x00000075u, 0x00001D1Du, 0x0000026Fu, 0x00000076u,  // 00001D58
        0x00001D25u, 0x000003B2u, 0x000003B3u, 0x000003B4u,  // 00001D5C
        0x000003C6u, 0x000003C7u, 0x00000069u, 0x00000072u,  // 00001D60
        0x00000075u, 0x00000076u, 0x000003B2u, 0x000003B3u,  // 00001D64
        0x000003C1u, 0x000003C6u, 0x000003C7u, 0x00001D6Bu,  // 00001D68
        0x00001D6Cu, 0x00001D6Du, 0x00001D6Eu, 0x00001D6Fu,  // 00001D6C
        0x00001D70u, 0x00001D71u, 0x00001D72u, 0x00001D73u,  // 00001D70
        0x00001D74u, 0x00001D75u, 0x00001D76u, 0x00001D77u,  // 00001D74
        0x00001D78u, 0x00001D79u, 0x00001D7Au, 0x00001D7Bu,  // 00001D78
        0x00001D7Cu, 0x00001D7Du, 0x00001D7Eu, 0x00001D7Fu
    };

    const std::bitset<128> Phonetic_Extensions1D00::my_Diacritic(std::string("00000000000000000000011111111111111111111111111111111111111111111111111111111111111100000000000000000000000000000000000000000000"));

    const std::bitset<128> Phonetic_Extensions1D00::my_Other_Lowercase(std::string("00000000000000000000000000000011111111111111111111111111111111111111111111111111111100000000000000000000000000000000000000000000"));

    const std::bitset<128> Phonetic_Extensions1D00::my_Soft_Dotted(std::string("00000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Phonetic_Extensions1D00);
