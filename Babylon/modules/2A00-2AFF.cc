/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 2A00-2AFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:56:02 +0200.
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

#include <map>

namespace Babylon
{
  namespace Module
  {
    class Supplemental_Mathematical_Operators2A00 : public Babylon::Block
    {
      public:
        void clean() { };

        Supplemental_Mathematical_Operators2A00() :
	    my_first_letter(0x2A00),
	    my_last_letter(0x2AFF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00002ADD, 0x00000338)] = 0x2ADC;
            }
        }

        ~Supplemental_Mathematical_Operators2A00() { }

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
	    return "Supplemental Mathematical Operators";
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
            return Babylon::Gen_Cat(CAT_Sm);
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
            return Babylon::Char_Decomp(Supplemental_Mathematical_Operators2A00::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Supplemental_Mathematical_Operators2A00::my_decompStr[uc - my_first_letter][0];
            us[1] = Supplemental_Mathematical_Operators2A00::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

            case 0x2A0C:
                us.resize(4);
                us[2u] = 0x222Bu;
                us[3u] = 0x222Bu;
                break;

            case 0x2A74:
                us.resize(3);
                us[2u] = 0x003Du;
                break;

            case 0x2A76:
                us.resize(3);
                us[2u] = 0x003Du;
                break;
            }
            if (0x0000u == us[1])
                us.resize(1);
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
            return my_composeMap[std::make_pair(starter, last)];
        }

        bool exclude_from_composition(const UCS4 uc) const
        {
            if (my_comp_exclude.test(uc - my_first_letter)) return 1;
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

      private:
        // functions
        Supplemental_Mathematical_Operators2A00(const Supplemental_Mathematical_Operators2A00 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const unsigned char my_decomp[256];
        static const UCS4 my_decompStr[256][2];
        static const std::bitset<256> my_mirror;
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<256> my_comp_exclude;
    }; // class Supplemental_Mathematical_Operators2A00

    const unsigned char Supplemental_Mathematical_Operators2A00::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
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
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, 
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS4 Supplemental_Mathematical_Operators2A00::my_decompStr[][2] =
    {
        { 0x00002A00u, 0x00000000u }, { 0x00002A01u, 0x00000000u },  // 00002A00
        { 0x00002A02u, 0x00000000u }, { 0x00002A03u, 0x00000000u },  // 00002A02
        { 0x00002A04u, 0x00000000u }, { 0x00002A05u, 0x00000000u },  // 00002A04
        { 0x00002A06u, 0x00000000u }, { 0x00002A07u, 0x00000000u },  // 00002A06
        { 0x00002A08u, 0x00000000u }, { 0x00002A09u, 0x00000000u },  // 00002A08
        { 0x00002A0Au, 0x00000000u }, { 0x00002A0Bu, 0x00000000u },  // 00002A0A
        { 0x0000222Bu, 0x0000222Bu }, { 0x00002A0Du, 0x00000000u },  // 00002A0C
        { 0x00002A0Eu, 0x00000000u }, { 0x00002A0Fu, 0x00000000u },  // 00002A0E
        { 0x00002A10u, 0x00000000u }, { 0x00002A11u, 0x00000000u },  // 00002A10
        { 0x00002A12u, 0x00000000u }, { 0x00002A13u, 0x00000000u },  // 00002A12
        { 0x00002A14u, 0x00000000u }, { 0x00002A15u, 0x00000000u },  // 00002A14
        { 0x00002A16u, 0x00000000u }, { 0x00002A17u, 0x00000000u },  // 00002A16
        { 0x00002A18u, 0x00000000u }, { 0x00002A19u, 0x00000000u },  // 00002A18
        { 0x00002A1Au, 0x00000000u }, { 0x00002A1Bu, 0x00000000u },  // 00002A1A
        { 0x00002A1Cu, 0x00000000u }, { 0x00002A1Du, 0x00000000u },  // 00002A1C
        { 0x00002A1Eu, 0x00000000u }, { 0x00002A1Fu, 0x00000000u },  // 00002A1E
        { 0x00002A20u, 0x00000000u }, { 0x00002A21u, 0x00000000u },  // 00002A20
        { 0x00002A22u, 0x00000000u }, { 0x00002A23u, 0x00000000u },  // 00002A22
        { 0x00002A24u, 0x00000000u }, { 0x00002A25u, 0x00000000u },  // 00002A24
        { 0x00002A26u, 0x00000000u }, { 0x00002A27u, 0x00000000u },  // 00002A26
        { 0x00002A28u, 0x00000000u }, { 0x00002A29u, 0x00000000u },  // 00002A28
        { 0x00002A2Au, 0x00000000u }, { 0x00002A2Bu, 0x00000000u },  // 00002A2A
        { 0x00002A2Cu, 0x00000000u }, { 0x00002A2Du, 0x00000000u },  // 00002A2C
        { 0x00002A2Eu, 0x00000000u }, { 0x00002A2Fu, 0x00000000u },  // 00002A2E
        { 0x00002A30u, 0x00000000u }, { 0x00002A31u, 0x00000000u },  // 00002A30
        { 0x00002A32u, 0x00000000u }, { 0x00002A33u, 0x00000000u },  // 00002A32
        { 0x00002A34u, 0x00000000u }, { 0x00002A35u, 0x00000000u },  // 00002A34
        { 0x00002A36u, 0x00000000u }, { 0x00002A37u, 0x00000000u },  // 00002A36
        { 0x00002A38u, 0x00000000u }, { 0x00002A39u, 0x00000000u },  // 00002A38
        { 0x00002A3Au, 0x00000000u }, { 0x00002A3Bu, 0x00000000u },  // 00002A3A
        { 0x00002A3Cu, 0x00000000u }, { 0x00002A3Du, 0x00000000u },  // 00002A3C
        { 0x00002A3Eu, 0x00000000u }, { 0x00002A3Fu, 0x00000000u },  // 00002A3E
        { 0x00002A40u, 0x00000000u }, { 0x00002A41u, 0x00000000u },  // 00002A40
        { 0x00002A42u, 0x00000000u }, { 0x00002A43u, 0x00000000u },  // 00002A42
        { 0x00002A44u, 0x00000000u }, { 0x00002A45u, 0x00000000u },  // 00002A44
        { 0x00002A46u, 0x00000000u }, { 0x00002A47u, 0x00000000u },  // 00002A46
        { 0x00002A48u, 0x00000000u }, { 0x00002A49u, 0x00000000u },  // 00002A48
        { 0x00002A4Au, 0x00000000u }, { 0x00002A4Bu, 0x00000000u },  // 00002A4A
        { 0x00002A4Cu, 0x00000000u }, { 0x00002A4Du, 0x00000000u },  // 00002A4C
        { 0x00002A4Eu, 0x00000000u }, { 0x00002A4Fu, 0x00000000u },  // 00002A4E
        { 0x00002A50u, 0x00000000u }, { 0x00002A51u, 0x00000000u },  // 00002A50
        { 0x00002A52u, 0x00000000u }, { 0x00002A53u, 0x00000000u },  // 00002A52
        { 0x00002A54u, 0x00000000u }, { 0x00002A55u, 0x00000000u },  // 00002A54
        { 0x00002A56u, 0x00000000u }, { 0x00002A57u, 0x00000000u },  // 00002A56
        { 0x00002A58u, 0x00000000u }, { 0x00002A59u, 0x00000000u },  // 00002A58
        { 0x00002A5Au, 0x00000000u }, { 0x00002A5Bu, 0x00000000u },  // 00002A5A
        { 0x00002A5Cu, 0x00000000u }, { 0x00002A5Du, 0x00000000u },  // 00002A5C
        { 0x00002A5Eu, 0x00000000u }, { 0x00002A5Fu, 0x00000000u },  // 00002A5E
        { 0x00002A60u, 0x00000000u }, { 0x00002A61u, 0x00000000u },  // 00002A60
        { 0x00002A62u, 0x00000000u }, { 0x00002A63u, 0x00000000u },  // 00002A62
        { 0x00002A64u, 0x00000000u }, { 0x00002A65u, 0x00000000u },  // 00002A64
        { 0x00002A66u, 0x00000000u }, { 0x00002A67u, 0x00000000u },  // 00002A66
        { 0x00002A68u, 0x00000000u }, { 0x00002A69u, 0x00000000u },  // 00002A68
        { 0x00002A6Au, 0x00000000u }, { 0x00002A6Bu, 0x00000000u },  // 00002A6A
        { 0x00002A6Cu, 0x00000000u }, { 0x00002A6Du, 0x00000000u },  // 00002A6C
        { 0x00002A6Eu, 0x00000000u }, { 0x00002A6Fu, 0x00000000u },  // 00002A6E
        { 0x00002A70u, 0x00000000u }, { 0x00002A71u, 0x00000000u },  // 00002A70
        { 0x00002A72u, 0x00000000u }, { 0x00002A73u, 0x00000000u },  // 00002A72
        { 0x0000003Au, 0x0000003Au }, { 0x0000003Du, 0x0000003Du },  // 00002A74
        { 0x0000003Du, 0x0000003Du }, { 0x00002A77u, 0x00000000u },  // 00002A76
        { 0x00002A78u, 0x00000000u }, { 0x00002A79u, 0x00000000u },  // 00002A78
        { 0x00002A7Au, 0x00000000u }, { 0x00002A7Bu, 0x00000000u },  // 00002A7A
        { 0x00002A7Cu, 0x00000000u }, { 0x00002A7Du, 0x00000000u },  // 00002A7C
        { 0x00002A7Eu, 0x00000000u }, { 0x00002A7Fu, 0x00000000u },  // 00002A7E
        { 0x00002A80u, 0x00000000u }, { 0x00002A81u, 0x00000000u },  // 00002A80
        { 0x00002A82u, 0x00000000u }, { 0x00002A83u, 0x00000000u },  // 00002A82
        { 0x00002A84u, 0x00000000u }, { 0x00002A85u, 0x00000000u },  // 00002A84
        { 0x00002A86u, 0x00000000u }, { 0x00002A87u, 0x00000000u },  // 00002A86
        { 0x00002A88u, 0x00000000u }, { 0x00002A89u, 0x00000000u },  // 00002A88
        { 0x00002A8Au, 0x00000000u }, { 0x00002A8Bu, 0x00000000u },  // 00002A8A
        { 0x00002A8Cu, 0x00000000u }, { 0x00002A8Du, 0x00000000u },  // 00002A8C
        { 0x00002A8Eu, 0x00000000u }, { 0x00002A8Fu, 0x00000000u },  // 00002A8E
        { 0x00002A90u, 0x00000000u }, { 0x00002A91u, 0x00000000u },  // 00002A90
        { 0x00002A92u, 0x00000000u }, { 0x00002A93u, 0x00000000u },  // 00002A92
        { 0x00002A94u, 0x00000000u }, { 0x00002A95u, 0x00000000u },  // 00002A94
        { 0x00002A96u, 0x00000000u }, { 0x00002A97u, 0x00000000u },  // 00002A96
        { 0x00002A98u, 0x00000000u }, { 0x00002A99u, 0x00000000u },  // 00002A98
        { 0x00002A9Au, 0x00000000u }, { 0x00002A9Bu, 0x00000000u },  // 00002A9A
        { 0x00002A9Cu, 0x00000000u }, { 0x00002A9Du, 0x00000000u },  // 00002A9C
        { 0x00002A9Eu, 0x00000000u }, { 0x00002A9Fu, 0x00000000u },  // 00002A9E
        { 0x00002AA0u, 0x00000000u }, { 0x00002AA1u, 0x00000000u },  // 00002AA0
        { 0x00002AA2u, 0x00000000u }, { 0x00002AA3u, 0x00000000u },  // 00002AA2
        { 0x00002AA4u, 0x00000000u }, { 0x00002AA5u, 0x00000000u },  // 00002AA4
        { 0x00002AA6u, 0x00000000u }, { 0x00002AA7u, 0x00000000u },  // 00002AA6
        { 0x00002AA8u, 0x00000000u }, { 0x00002AA9u, 0x00000000u },  // 00002AA8
        { 0x00002AAAu, 0x00000000u }, { 0x00002AABu, 0x00000000u },  // 00002AAA
        { 0x00002AACu, 0x00000000u }, { 0x00002AADu, 0x00000000u },  // 00002AAC
        { 0x00002AAEu, 0x00000000u }, { 0x00002AAFu, 0x00000000u },  // 00002AAE
        { 0x00002AB0u, 0x00000000u }, { 0x00002AB1u, 0x00000000u },  // 00002AB0
        { 0x00002AB2u, 0x00000000u }, { 0x00002AB3u, 0x00000000u },  // 00002AB2
        { 0x00002AB4u, 0x00000000u }, { 0x00002AB5u, 0x00000000u },  // 00002AB4
        { 0x00002AB6u, 0x00000000u }, { 0x00002AB7u, 0x00000000u },  // 00002AB6
        { 0x00002AB8u, 0x00000000u }, { 0x00002AB9u, 0x00000000u },  // 00002AB8
        { 0x00002ABAu, 0x00000000u }, { 0x00002ABBu, 0x00000000u },  // 00002ABA
        { 0x00002ABCu, 0x00000000u }, { 0x00002ABDu, 0x00000000u },  // 00002ABC
        { 0x00002ABEu, 0x00000000u }, { 0x00002ABFu, 0x00000000u },  // 00002ABE
        { 0x00002AC0u, 0x00000000u }, { 0x00002AC1u, 0x00000000u },  // 00002AC0
        { 0x00002AC2u, 0x00000000u }, { 0x00002AC3u, 0x00000000u },  // 00002AC2
        { 0x00002AC4u, 0x00000000u }, { 0x00002AC5u, 0x00000000u },  // 00002AC4
        { 0x00002AC6u, 0x00000000u }, { 0x00002AC7u, 0x00000000u },  // 00002AC6
        { 0x00002AC8u, 0x00000000u }, { 0x00002AC9u, 0x00000000u },  // 00002AC8
        { 0x00002ACAu, 0x00000000u }, { 0x00002ACBu, 0x00000000u },  // 00002ACA
        { 0x00002ACCu, 0x00000000u }, { 0x00002ACDu, 0x00000000u },  // 00002ACC
        { 0x00002ACEu, 0x00000000u }, { 0x00002ACFu, 0x00000000u },  // 00002ACE
        { 0x00002AD0u, 0x00000000u }, { 0x00002AD1u, 0x00000000u },  // 00002AD0
        { 0x00002AD2u, 0x00000000u }, { 0x00002AD3u, 0x00000000u },  // 00002AD2
        { 0x00002AD4u, 0x00000000u }, { 0x00002AD5u, 0x00000000u },  // 00002AD4
        { 0x00002AD6u, 0x00000000u }, { 0x00002AD7u, 0x00000000u },  // 00002AD6
        { 0x00002AD8u, 0x00000000u }, { 0x00002AD9u, 0x00000000u },  // 00002AD8
        { 0x00002ADAu, 0x00000000u }, { 0x00002ADBu, 0x00000000u },  // 00002ADA
        { 0x00002ADDu, 0x00000338u }, { 0x00002ADDu, 0x00000000u },  // 00002ADC
        { 0x00002ADEu, 0x00000000u }, { 0x00002ADFu, 0x00000000u },  // 00002ADE
        { 0x00002AE0u, 0x00000000u }, { 0x00002AE1u, 0x00000000u },  // 00002AE0
        { 0x00002AE2u, 0x00000000u }, { 0x00002AE3u, 0x00000000u },  // 00002AE2
        { 0x00002AE4u, 0x00000000u }, { 0x00002AE5u, 0x00000000u },  // 00002AE4
        { 0x00002AE6u, 0x00000000u }, { 0x00002AE7u, 0x00000000u },  // 00002AE6
        { 0x00002AE8u, 0x00000000u }, { 0x00002AE9u, 0x00000000u },  // 00002AE8
        { 0x00002AEAu, 0x00000000u }, { 0x00002AEBu, 0x00000000u },  // 00002AEA
        { 0x00002AECu, 0x00000000u }, { 0x00002AEDu, 0x00000000u },  // 00002AEC
        { 0x00002AEEu, 0x00000000u }, { 0x00002AEFu, 0x00000000u },  // 00002AEE
        { 0x00002AF0u, 0x00000000u }, { 0x00002AF1u, 0x00000000u },  // 00002AF0
        { 0x00002AF2u, 0x00000000u }, { 0x00002AF3u, 0x00000000u },  // 00002AF2
        { 0x00002AF4u, 0x00000000u }, { 0x00002AF5u, 0x00000000u },  // 00002AF4
        { 0x00002AF6u, 0x00000000u }, { 0x00002AF7u, 0x00000000u },  // 00002AF6
        { 0x00002AF8u, 0x00000000u }, { 0x00002AF9u, 0x00000000u },  // 00002AF8
        { 0x00002AFAu, 0x00000000u }, { 0x00002AFBu, 0x00000000u },  // 00002AFA
        { 0x00002AFCu, 0x00000000u }, { 0x00002AFDu, 0x00000000u },  // 00002AFC
        { 0x00002AFEu, 0x00000000u }, { 0x00002AFFu, 0x00000000u }
    };

    const std::bitset<256> Supplemental_Mathematical_Operators2A00::my_mirror(std::string("0010111110001000011100000111110001010000011111111111111111111111111111111111111110111111110011111111111111111111111111111111111111111110000110011011110000110000000000011000000000000000000000000111000000110000011110100101001111011111111111111111110000000000"));

    const std::bitset<256> Supplemental_Mathematical_Operators2A00::my_comp_exclude(std::string("0000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Supplemental_Mathematical_Operators2A00);
