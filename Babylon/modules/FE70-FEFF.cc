/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp FE70-FEFF.cc
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
    class Arabic_Presentation_FormsBFE70 : public Babylon::Block
    {
      public:
        void clean() { };

        Arabic_Presentation_FormsBFE70() :
	    my_first_letter(0xFE70),
	    my_last_letter(0xFEFF)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~Arabic_Presentation_FormsBFE70() { }

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
	    return "Arabic Presentation Forms-B";
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
            return Babylon::Gen_Cat(Arabic_Presentation_FormsBFE70::my_cat[uc - my_first_letter]);
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
            return Arabic_Presentation_FormsBFE70::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Arabic_Presentation_FormsBFE70::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Arabic_Presentation_FormsBFE70::my_decompStr[uc - my_first_letter][0];
            us[1] = Arabic_Presentation_FormsBFE70::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Arabic_Presentation_FormsBFE70::my_lb[uc - my_first_letter]);
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
            return my_XID_Start_Closure.test(uc - my_first_letter);
        }

        bool is_XID_Continue_Closure(const UCS4 uc) const
        {
            return my_XID_Continue_Closure.test(uc - my_first_letter);
        }

      private:
        // functions
        Arabic_Presentation_FormsBFE70(const Arabic_Presentation_FormsBFE70 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<144> my_is_defined;
        static const unsigned char my_cat[144];
        static const Babylon::Bidir_Props my_bidir[144];
        static const unsigned char my_decomp[144];
        static const UCS4 my_decompStr[144][2];
        static const unsigned char my_lb[144];
        static const std::bitset<144> my_XID_Start_Closure;
        static const std::bitset<144> my_XID_Continue_Closure;
    }; // class Arabic_Presentation_FormsBFE70

    const std::bitset<144> Arabic_Presentation_FormsBFE70::my_is_defined(std::string("100111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111011111"));

    const unsigned char Arabic_Presentation_FormsBFE70::my_cat[] =
    {
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Cf
    };

    const Babylon::Bidir_Props Arabic_Presentation_FormsBFE70::my_bidir[] =
    {
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_BN
    };

    const unsigned char Arabic_Presentation_FormsBFE70::my_decomp[] = {
        DECOMP_ISOLATED, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_CANONICAL, 
        DECOMP_ISOLATED, DECOMP_CANONICAL, DECOMP_ISOLATED, DECOMP_MEDIAL, 
        DECOMP_ISOLATED, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_MEDIAL, 
        DECOMP_ISOLATED, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_MEDIAL, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS4 Arabic_Presentation_FormsBFE70::my_decompStr[][2] =
    {
        { 0x00000020u, 0x0000064Bu }, { 0x00000640u, 0x0000064Bu },  // 0000FE70
        { 0x00000020u, 0x0000064Cu }, { 0x0000FE73u, 0x00000000u },  // 0000FE72
        { 0x00000020u, 0x0000064Du }, { 0x0000FE75u, 0x00000000u },  // 0000FE74
        { 0x00000020u, 0x0000064Eu }, { 0x00000640u, 0x0000064Eu },  // 0000FE76
        { 0x00000020u, 0x0000064Fu }, { 0x00000640u, 0x0000064Fu },  // 0000FE78
        { 0x00000020u, 0x00000650u }, { 0x00000640u, 0x00000650u },  // 0000FE7A
        { 0x00000020u, 0x00000651u }, { 0x00000640u, 0x00000651u },  // 0000FE7C
        { 0x00000020u, 0x00000652u }, { 0x00000640u, 0x00000652u },  // 0000FE7E
        { 0x00000621u, 0x00000000u }, { 0x00000622u, 0x00000000u },  // 0000FE80
        { 0x00000622u, 0x00000000u }, { 0x00000623u, 0x00000000u },  // 0000FE82
        { 0x00000623u, 0x00000000u }, { 0x00000624u, 0x00000000u },  // 0000FE84
        { 0x00000624u, 0x00000000u }, { 0x00000625u, 0x00000000u },  // 0000FE86
        { 0x00000625u, 0x00000000u }, { 0x00000626u, 0x00000000u },  // 0000FE88
        { 0x00000626u, 0x00000000u }, { 0x00000626u, 0x00000000u },  // 0000FE8A
        { 0x00000626u, 0x00000000u }, { 0x00000627u, 0x00000000u },  // 0000FE8C
        { 0x00000627u, 0x00000000u }, { 0x00000628u, 0x00000000u },  // 0000FE8E
        { 0x00000628u, 0x00000000u }, { 0x00000628u, 0x00000000u },  // 0000FE90
        { 0x00000628u, 0x00000000u }, { 0x00000629u, 0x00000000u },  // 0000FE92
        { 0x00000629u, 0x00000000u }, { 0x0000062Au, 0x00000000u },  // 0000FE94
        { 0x0000062Au, 0x00000000u }, { 0x0000062Au, 0x00000000u },  // 0000FE96
        { 0x0000062Au, 0x00000000u }, { 0x0000062Bu, 0x00000000u },  // 0000FE98
        { 0x0000062Bu, 0x00000000u }, { 0x0000062Bu, 0x00000000u },  // 0000FE9A
        { 0x0000062Bu, 0x00000000u }, { 0x0000062Cu, 0x00000000u },  // 0000FE9C
        { 0x0000062Cu, 0x00000000u }, { 0x0000062Cu, 0x00000000u },  // 0000FE9E
        { 0x0000062Cu, 0x00000000u }, { 0x0000062Du, 0x00000000u },  // 0000FEA0
        { 0x0000062Du, 0x00000000u }, { 0x0000062Du, 0x00000000u },  // 0000FEA2
        { 0x0000062Du, 0x00000000u }, { 0x0000062Eu, 0x00000000u },  // 0000FEA4
        { 0x0000062Eu, 0x00000000u }, { 0x0000062Eu, 0x00000000u },  // 0000FEA6
        { 0x0000062Eu, 0x00000000u }, { 0x0000062Fu, 0x00000000u },  // 0000FEA8
        { 0x0000062Fu, 0x00000000u }, { 0x00000630u, 0x00000000u },  // 0000FEAA
        { 0x00000630u, 0x00000000u }, { 0x00000631u, 0x00000000u },  // 0000FEAC
        { 0x00000631u, 0x00000000u }, { 0x00000632u, 0x00000000u },  // 0000FEAE
        { 0x00000632u, 0x00000000u }, { 0x00000633u, 0x00000000u },  // 0000FEB0
        { 0x00000633u, 0x00000000u }, { 0x00000633u, 0x00000000u },  // 0000FEB2
        { 0x00000633u, 0x00000000u }, { 0x00000634u, 0x00000000u },  // 0000FEB4
        { 0x00000634u, 0x00000000u }, { 0x00000634u, 0x00000000u },  // 0000FEB6
        { 0x00000634u, 0x00000000u }, { 0x00000635u, 0x00000000u },  // 0000FEB8
        { 0x00000635u, 0x00000000u }, { 0x00000635u, 0x00000000u },  // 0000FEBA
        { 0x00000635u, 0x00000000u }, { 0x00000636u, 0x00000000u },  // 0000FEBC
        { 0x00000636u, 0x00000000u }, { 0x00000636u, 0x00000000u },  // 0000FEBE
        { 0x00000636u, 0x00000000u }, { 0x00000637u, 0x00000000u },  // 0000FEC0
        { 0x00000637u, 0x00000000u }, { 0x00000637u, 0x00000000u },  // 0000FEC2
        { 0x00000637u, 0x00000000u }, { 0x00000638u, 0x00000000u },  // 0000FEC4
        { 0x00000638u, 0x00000000u }, { 0x00000638u, 0x00000000u },  // 0000FEC6
        { 0x00000638u, 0x00000000u }, { 0x00000639u, 0x00000000u },  // 0000FEC8
        { 0x00000639u, 0x00000000u }, { 0x00000639u, 0x00000000u },  // 0000FECA
        { 0x00000639u, 0x00000000u }, { 0x0000063Au, 0x00000000u },  // 0000FECC
        { 0x0000063Au, 0x00000000u }, { 0x0000063Au, 0x00000000u },  // 0000FECE
        { 0x0000063Au, 0x00000000u }, { 0x00000641u, 0x00000000u },  // 0000FED0
        { 0x00000641u, 0x00000000u }, { 0x00000641u, 0x00000000u },  // 0000FED2
        { 0x00000641u, 0x00000000u }, { 0x00000642u, 0x00000000u },  // 0000FED4
        { 0x00000642u, 0x00000000u }, { 0x00000642u, 0x00000000u },  // 0000FED6
        { 0x00000642u, 0x00000000u }, { 0x00000643u, 0x00000000u },  // 0000FED8
        { 0x00000643u, 0x00000000u }, { 0x00000643u, 0x00000000u },  // 0000FEDA
        { 0x00000643u, 0x00000000u }, { 0x00000644u, 0x00000000u },  // 0000FEDC
        { 0x00000644u, 0x00000000u }, { 0x00000644u, 0x00000000u },  // 0000FEDE
        { 0x00000644u, 0x00000000u }, { 0x00000645u, 0x00000000u },  // 0000FEE0
        { 0x00000645u, 0x00000000u }, { 0x00000645u, 0x00000000u },  // 0000FEE2
        { 0x00000645u, 0x00000000u }, { 0x00000646u, 0x00000000u },  // 0000FEE4
        { 0x00000646u, 0x00000000u }, { 0x00000646u, 0x00000000u },  // 0000FEE6
        { 0x00000646u, 0x00000000u }, { 0x00000647u, 0x00000000u },  // 0000FEE8
        { 0x00000647u, 0x00000000u }, { 0x00000647u, 0x00000000u },  // 0000FEEA
        { 0x00000647u, 0x00000000u }, { 0x00000648u, 0x00000000u },  // 0000FEEC
        { 0x00000648u, 0x00000000u }, { 0x00000649u, 0x00000000u },  // 0000FEEE
        { 0x00000649u, 0x00000000u }, { 0x0000064Au, 0x00000000u },  // 0000FEF0
        { 0x0000064Au, 0x00000000u }, { 0x0000064Au, 0x00000000u },  // 0000FEF2
        { 0x0000064Au, 0x00000000u }, { 0x00000644u, 0x00000622u },  // 0000FEF4
        { 0x00000644u, 0x00000622u }, { 0x00000644u, 0x00000623u },  // 0000FEF6
        { 0x00000644u, 0x00000623u }, { 0x00000644u, 0x00000625u },  // 0000FEF8
        { 0x00000644u, 0x00000625u }, { 0x00000644u, 0x00000627u },  // 0000FEFA
        { 0x00000644u, 0x00000627u }, { 0x0000FEFDu, 0x00000000u },  // 0000FEFC
        { 0x0000FEFEu, 0x00000000u }, { 0x0000FEFFu, 0x00000000u }
    };

    const unsigned char Arabic_Presentation_FormsBFE70::my_lb[] =
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
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_WJ
    };

    const std::bitset<144> Arabic_Presentation_FormsBFE70::my_XID_Start_Closure(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000101010101010101"));

    const std::bitset<144> Arabic_Presentation_FormsBFE70::my_XID_Continue_Closure(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000101010101010101"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Arabic_Presentation_FormsBFE70);
