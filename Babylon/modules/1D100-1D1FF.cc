/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 1D100-1D1FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:10:28 +0200.
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
    class Musical_Symbols1D100 : public Babylon::Block
    {
      public:
        void clean() { };

        Musical_Symbols1D100() :
	    my_first_letter(0x1D100),
	    my_last_letter(0x1D1FF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x0001D157, 0x0001D165)] = 0x1D15E;
                my_composeMap[std::make_pair(0x0001D158, 0x0001D165)] = 0x1D15F;
                my_composeMap[std::make_pair(0x0001D15F, 0x0001D16E)] = 0x1D160;
                my_composeMap[std::make_pair(0x0001D15F, 0x0001D16F)] = 0x1D161;
                my_composeMap[std::make_pair(0x0001D15F, 0x0001D170)] = 0x1D162;
                my_composeMap[std::make_pair(0x0001D15F, 0x0001D171)] = 0x1D163;
                my_composeMap[std::make_pair(0x0001D15F, 0x0001D172)] = 0x1D164;
                my_composeMap[std::make_pair(0x0001D1B9, 0x0001D165)] = 0x1D1BB;
                my_composeMap[std::make_pair(0x0001D1BA, 0x0001D165)] = 0x1D1BC;
                my_composeMap[std::make_pair(0x0001D1BB, 0x0001D16E)] = 0x1D1BD;
                my_composeMap[std::make_pair(0x0001D1BB, 0x0001D16F)] = 0x1D1BF;
                my_composeMap[std::make_pair(0x0001D1BC, 0x0001D16E)] = 0x1D1BE;
                my_composeMap[std::make_pair(0x0001D1BC, 0x0001D16F)] = 0x1D1C0;
            }
        }

        ~Musical_Symbols1D100() { }

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
	    return "Musical Symbols";
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
            return Babylon::Gen_Cat(Musical_Symbols1D100::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(Musical_Symbols1D100::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return Musical_Symbols1D100::my_bidir[uc - my_first_letter];
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
            us[0] = Musical_Symbols1D100::my_decompStr[uc - my_first_letter][0];
            us[1] = Musical_Symbols1D100::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Musical_Symbols1D100::my_lb[uc - my_first_letter]);
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
            return my_Other_Grapheme_Extend.test(uc - my_first_letter);
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
        Musical_Symbols1D100(const Musical_Symbols1D100 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<256> my_is_defined;
        static const unsigned char my_cat[256];
        static const unsigned char my_comb_cl[256];
        static const Babylon::Bidir_Props my_bidir[256];
        static const UCS4 my_decompStr[256][2];
        static const unsigned char my_lb[256];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<256> my_comp_exclude;
        static const std::bitset<256> my_Diacritic;
        static const std::bitset<256> my_Other_Grapheme_Extend;
    }; // class Musical_Symbols1D100

    const std::bitset<256> Musical_Symbols1D100::my_is_defined(std::string("0000000000000000000000000000000000111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111000111111111111111111111111111111111111111"));

    const unsigned char Musical_Symbols1D100::my_cat[] =
    {
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_Mc, CAT_Mc, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_So, CAT_So, CAT_So, CAT_Mc, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mc, CAT_Mc, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, 
        CAT_Cf, CAT_Cf, CAT_Cf, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_So, CAT_So, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So
    };

    const unsigned char Musical_Symbols1D100::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 216, 216, 1, 
        1, 1, 0, 0, 0, 226, 216, 216, 
        216, 216, 216, 0, 0, 0, 0, 0, 
        0, 0, 0, 220, 220, 220, 220, 220, 
        220, 220, 220, 0, 0, 230, 230, 230, 
        230, 230, 220, 220, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 230, 230, 230, 230, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props Musical_Symbols1D100::my_bidir[] =
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
    };

    const UCS4 Musical_Symbols1D100::my_decompStr[][2] =
    {
        { 0x0001D100u, 0x00000000u }, { 0x0001D101u, 0x00000000u },  // 0001D100
        { 0x0001D102u, 0x00000000u }, { 0x0001D103u, 0x00000000u },  // 0001D102
        { 0x0001D104u, 0x00000000u }, { 0x0001D105u, 0x00000000u },  // 0001D104
        { 0x0001D106u, 0x00000000u }, { 0x0001D107u, 0x00000000u },  // 0001D106
        { 0x0001D108u, 0x00000000u }, { 0x0001D109u, 0x00000000u },  // 0001D108
        { 0x0001D10Au, 0x00000000u }, { 0x0001D10Bu, 0x00000000u },  // 0001D10A
        { 0x0001D10Cu, 0x00000000u }, { 0x0001D10Du, 0x00000000u },  // 0001D10C
        { 0x0001D10Eu, 0x00000000u }, { 0x0001D10Fu, 0x00000000u },  // 0001D10E
        { 0x0001D110u, 0x00000000u }, { 0x0001D111u, 0x00000000u },  // 0001D110
        { 0x0001D112u, 0x00000000u }, { 0x0001D113u, 0x00000000u },  // 0001D112
        { 0x0001D114u, 0x00000000u }, { 0x0001D115u, 0x00000000u },  // 0001D114
        { 0x0001D116u, 0x00000000u }, { 0x0001D117u, 0x00000000u },  // 0001D116
        { 0x0001D118u, 0x00000000u }, { 0x0001D119u, 0x00000000u },  // 0001D118
        { 0x0001D11Au, 0x00000000u }, { 0x0001D11Bu, 0x00000000u },  // 0001D11A
        { 0x0001D11Cu, 0x00000000u }, { 0x0001D11Du, 0x00000000u },  // 0001D11C
        { 0x0001D11Eu, 0x00000000u }, { 0x0001D11Fu, 0x00000000u },  // 0001D11E
        { 0x0001D120u, 0x00000000u }, { 0x0001D121u, 0x00000000u },  // 0001D120
        { 0x0001D122u, 0x00000000u }, { 0x0001D123u, 0x00000000u },  // 0001D122
        { 0x0001D124u, 0x00000000u }, { 0x0001D125u, 0x00000000u },  // 0001D124
        { 0x0001D126u, 0x00000000u }, { 0x0001D127u, 0x00000000u },  // 0001D126
        { 0x0001D128u, 0x00000000u }, { 0x0001D129u, 0x00000000u },  // 0001D128
        { 0x0001D12Au, 0x00000000u }, { 0x0001D12Bu, 0x00000000u },  // 0001D12A
        { 0x0001D12Cu, 0x00000000u }, { 0x0001D12Du, 0x00000000u },  // 0001D12C
        { 0x0001D12Eu, 0x00000000u }, { 0x0001D12Fu, 0x00000000u },  // 0001D12E
        { 0x0001D130u, 0x00000000u }, { 0x0001D131u, 0x00000000u },  // 0001D130
        { 0x0001D132u, 0x00000000u }, { 0x0001D133u, 0x00000000u },  // 0001D132
        { 0x0001D134u, 0x00000000u }, { 0x0001D135u, 0x00000000u },  // 0001D134
        { 0x0001D136u, 0x00000000u }, { 0x0001D137u, 0x00000000u },  // 0001D136
        { 0x0001D138u, 0x00000000u }, { 0x0001D139u, 0x00000000u },  // 0001D138
        { 0x0001D13Au, 0x00000000u }, { 0x0001D13Bu, 0x00000000u },  // 0001D13A
        { 0x0001D13Cu, 0x00000000u }, { 0x0001D13Du, 0x00000000u },  // 0001D13C
        { 0x0001D13Eu, 0x00000000u }, { 0x0001D13Fu, 0x00000000u },  // 0001D13E
        { 0x0001D140u, 0x00000000u }, { 0x0001D141u, 0x00000000u },  // 0001D140
        { 0x0001D142u, 0x00000000u }, { 0x0001D143u, 0x00000000u },  // 0001D142
        { 0x0001D144u, 0x00000000u }, { 0x0001D145u, 0x00000000u },  // 0001D144
        { 0x0001D146u, 0x00000000u }, { 0x0001D147u, 0x00000000u },  // 0001D146
        { 0x0001D148u, 0x00000000u }, { 0x0001D149u, 0x00000000u },  // 0001D148
        { 0x0001D14Au, 0x00000000u }, { 0x0001D14Bu, 0x00000000u },  // 0001D14A
        { 0x0001D14Cu, 0x00000000u }, { 0x0001D14Du, 0x00000000u },  // 0001D14C
        { 0x0001D14Eu, 0x00000000u }, { 0x0001D14Fu, 0x00000000u },  // 0001D14E
        { 0x0001D150u, 0x00000000u }, { 0x0001D151u, 0x00000000u },  // 0001D150
        { 0x0001D152u, 0x00000000u }, { 0x0001D153u, 0x00000000u },  // 0001D152
        { 0x0001D154u, 0x00000000u }, { 0x0001D155u, 0x00000000u },  // 0001D154
        { 0x0001D156u, 0x00000000u }, { 0x0001D157u, 0x00000000u },  // 0001D156
        { 0x0001D158u, 0x00000000u }, { 0x0001D159u, 0x00000000u },  // 0001D158
        { 0x0001D15Au, 0x00000000u }, { 0x0001D15Bu, 0x00000000u },  // 0001D15A
        { 0x0001D15Cu, 0x00000000u }, { 0x0001D15Du, 0x00000000u },  // 0001D15C
        { 0x0001D157u, 0x0001D165u }, { 0x0001D158u, 0x0001D165u },  // 0001D15E
        { 0x0001D15Fu, 0x0001D16Eu }, { 0x0001D15Fu, 0x0001D16Fu },  // 0001D160
        { 0x0001D15Fu, 0x0001D170u }, { 0x0001D15Fu, 0x0001D171u },  // 0001D162
        { 0x0001D15Fu, 0x0001D172u }, { 0x0001D165u, 0x00000000u },  // 0001D164
        { 0x0001D166u, 0x00000000u }, { 0x0001D167u, 0x00000000u },  // 0001D166
        { 0x0001D168u, 0x00000000u }, { 0x0001D169u, 0x00000000u },  // 0001D168
        { 0x0001D16Au, 0x00000000u }, { 0x0001D16Bu, 0x00000000u },  // 0001D16A
        { 0x0001D16Cu, 0x00000000u }, { 0x0001D16Du, 0x00000000u },  // 0001D16C
        { 0x0001D16Eu, 0x00000000u }, { 0x0001D16Fu, 0x00000000u },  // 0001D16E
        { 0x0001D170u, 0x00000000u }, { 0x0001D171u, 0x00000000u },  // 0001D170
        { 0x0001D172u, 0x00000000u }, { 0x0001D173u, 0x00000000u },  // 0001D172
        { 0x0001D174u, 0x00000000u }, { 0x0001D175u, 0x00000000u },  // 0001D174
        { 0x0001D176u, 0x00000000u }, { 0x0001D177u, 0x00000000u },  // 0001D176
        { 0x0001D178u, 0x00000000u }, { 0x0001D179u, 0x00000000u },  // 0001D178
        { 0x0001D17Au, 0x00000000u }, { 0x0001D17Bu, 0x00000000u },  // 0001D17A
        { 0x0001D17Cu, 0x00000000u }, { 0x0001D17Du, 0x00000000u },  // 0001D17C
        { 0x0001D17Eu, 0x00000000u }, { 0x0001D17Fu, 0x00000000u },  // 0001D17E
        { 0x0001D180u, 0x00000000u }, { 0x0001D181u, 0x00000000u },  // 0001D180
        { 0x0001D182u, 0x00000000u }, { 0x0001D183u, 0x00000000u },  // 0001D182
        { 0x0001D184u, 0x00000000u }, { 0x0001D185u, 0x00000000u },  // 0001D184
        { 0x0001D186u, 0x00000000u }, { 0x0001D187u, 0x00000000u },  // 0001D186
        { 0x0001D188u, 0x00000000u }, { 0x0001D189u, 0x00000000u },  // 0001D188
        { 0x0001D18Au, 0x00000000u }, { 0x0001D18Bu, 0x00000000u },  // 0001D18A
        { 0x0001D18Cu, 0x00000000u }, { 0x0001D18Du, 0x00000000u },  // 0001D18C
        { 0x0001D18Eu, 0x00000000u }, { 0x0001D18Fu, 0x00000000u },  // 0001D18E
        { 0x0001D190u, 0x00000000u }, { 0x0001D191u, 0x00000000u },  // 0001D190
        { 0x0001D192u, 0x00000000u }, { 0x0001D193u, 0x00000000u },  // 0001D192
        { 0x0001D194u, 0x00000000u }, { 0x0001D195u, 0x00000000u },  // 0001D194
        { 0x0001D196u, 0x00000000u }, { 0x0001D197u, 0x00000000u },  // 0001D196
        { 0x0001D198u, 0x00000000u }, { 0x0001D199u, 0x00000000u },  // 0001D198
        { 0x0001D19Au, 0x00000000u }, { 0x0001D19Bu, 0x00000000u },  // 0001D19A
        { 0x0001D19Cu, 0x00000000u }, { 0x0001D19Du, 0x00000000u },  // 0001D19C
        { 0x0001D19Eu, 0x00000000u }, { 0x0001D19Fu, 0x00000000u },  // 0001D19E
        { 0x0001D1A0u, 0x00000000u }, { 0x0001D1A1u, 0x00000000u },  // 0001D1A0
        { 0x0001D1A2u, 0x00000000u }, { 0x0001D1A3u, 0x00000000u },  // 0001D1A2
        { 0x0001D1A4u, 0x00000000u }, { 0x0001D1A5u, 0x00000000u },  // 0001D1A4
        { 0x0001D1A6u, 0x00000000u }, { 0x0001D1A7u, 0x00000000u },  // 0001D1A6
        { 0x0001D1A8u, 0x00000000u }, { 0x0001D1A9u, 0x00000000u },  // 0001D1A8
        { 0x0001D1AAu, 0x00000000u }, { 0x0001D1ABu, 0x00000000u },  // 0001D1AA
        { 0x0001D1ACu, 0x00000000u }, { 0x0001D1ADu, 0x00000000u },  // 0001D1AC
        { 0x0001D1AEu, 0x00000000u }, { 0x0001D1AFu, 0x00000000u },  // 0001D1AE
        { 0x0001D1B0u, 0x00000000u }, { 0x0001D1B1u, 0x00000000u },  // 0001D1B0
        { 0x0001D1B2u, 0x00000000u }, { 0x0001D1B3u, 0x00000000u },  // 0001D1B2
        { 0x0001D1B4u, 0x00000000u }, { 0x0001D1B5u, 0x00000000u },  // 0001D1B4
        { 0x0001D1B6u, 0x00000000u }, { 0x0001D1B7u, 0x00000000u },  // 0001D1B6
        { 0x0001D1B8u, 0x00000000u }, { 0x0001D1B9u, 0x00000000u },  // 0001D1B8
        { 0x0001D1BAu, 0x00000000u }, { 0x0001D1B9u, 0x0001D165u },  // 0001D1BA
        { 0x0001D1BAu, 0x0001D165u }, { 0x0001D1BBu, 0x0001D16Eu },  // 0001D1BC
        { 0x0001D1BCu, 0x0001D16Eu }, { 0x0001D1BBu, 0x0001D16Fu },  // 0001D1BE
        { 0x0001D1BCu, 0x0001D16Fu }, { 0x0001D1C1u, 0x00000000u },  // 0001D1C0
        { 0x0001D1C2u, 0x00000000u }, { 0x0001D1C3u, 0x00000000u },  // 0001D1C2
        { 0x0001D1C4u, 0x00000000u }, { 0x0001D1C5u, 0x00000000u },  // 0001D1C4
        { 0x0001D1C6u, 0x00000000u }, { 0x0001D1C7u, 0x00000000u },  // 0001D1C6
        { 0x0001D1C8u, 0x00000000u }, { 0x0001D1C9u, 0x00000000u },  // 0001D1C8
        { 0x0001D1CAu, 0x00000000u }, { 0x0001D1CBu, 0x00000000u },  // 0001D1CA
        { 0x0001D1CCu, 0x00000000u }, { 0x0001D1CDu, 0x00000000u },  // 0001D1CC
        { 0x0001D1CEu, 0x00000000u }, { 0x0001D1CFu, 0x00000000u },  // 0001D1CE
        { 0x0001D1D0u, 0x00000000u }, { 0x0001D1D1u, 0x00000000u },  // 0001D1D0
        { 0x0001D1D2u, 0x00000000u }, { 0x0001D1D3u, 0x00000000u },  // 0001D1D2
        { 0x0001D1D4u, 0x00000000u }, { 0x0001D1D5u, 0x00000000u },  // 0001D1D4
        { 0x0001D1D6u, 0x00000000u }, { 0x0001D1D7u, 0x00000000u },  // 0001D1D6
        { 0x0001D1D8u, 0x00000000u }, { 0x0001D1D9u, 0x00000000u },  // 0001D1D8
        { 0x0001D1DAu, 0x00000000u }, { 0x0001D1DBu, 0x00000000u },  // 0001D1DA
        { 0x0001D1DCu, 0x00000000u }, { 0x0001D1DDu, 0x00000000u },  // 0001D1DC
        { 0x0001D1DEu, 0x00000000u }, { 0x0001D1DFu, 0x00000000u },  // 0001D1DE
        { 0x0001D1E0u, 0x00000000u }, { 0x0001D1E1u, 0x00000000u },  // 0001D1E0
        { 0x0001D1E2u, 0x00000000u }, { 0x0001D1E3u, 0x00000000u },  // 0001D1E2
        { 0x0001D1E4u, 0x00000000u }, { 0x0001D1E5u, 0x00000000u },  // 0001D1E4
        { 0x0001D1E6u, 0x00000000u }, { 0x0001D1E7u, 0x00000000u },  // 0001D1E6
        { 0x0001D1E8u, 0x00000000u }, { 0x0001D1E9u, 0x00000000u },  // 0001D1E8
        { 0x0001D1EAu, 0x00000000u }, { 0x0001D1EBu, 0x00000000u },  // 0001D1EA
        { 0x0001D1ECu, 0x00000000u }, { 0x0001D1EDu, 0x00000000u },  // 0001D1EC
        { 0x0001D1EEu, 0x00000000u }, { 0x0001D1EFu, 0x00000000u },  // 0001D1EE
        { 0x0001D1F0u, 0x00000000u }, { 0x0001D1F1u, 0x00000000u },  // 0001D1F0
        { 0x0001D1F2u, 0x00000000u }, { 0x0001D1F3u, 0x00000000u },  // 0001D1F2
        { 0x0001D1F4u, 0x00000000u }, { 0x0001D1F5u, 0x00000000u },  // 0001D1F4
        { 0x0001D1F6u, 0x00000000u }, { 0x0001D1F7u, 0x00000000u },  // 0001D1F6
        { 0x0001D1F8u, 0x00000000u }, { 0x0001D1F9u, 0x00000000u },  // 0001D1F8
        { 0x0001D1FAu, 0x00000000u }, { 0x0001D1FBu, 0x00000000u },  // 0001D1FA
        { 0x0001D1FCu, 0x00000000u }, { 0x0001D1FDu, 0x00000000u },  // 0001D1FC
        { 0x0001D1FEu, 0x00000000u }, { 0x0001D1FFu, 0x00000000u }
    };

    const unsigned char Musical_Symbols1D100::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const std::bitset<256> Musical_Symbols1D100::my_comp_exclude(std::string("0000000000000000000000000000000000000000000000000000000000000001111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<256> Musical_Symbols1D100::my_Diacritic(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000111100000000000000000000000000000011111110011111111000000001111110001110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<256> Musical_Symbols1D100::my_Other_Grapheme_Extend(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001100000000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Musical_Symbols1D100);
