/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 2980-29FF.cc
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


namespace Babylon
{
  namespace Module
  {
    class Miscellaneous_Mathematical_SymbolsB2980 : public Babylon::Block
    {
      public:
        void clean() { };

        Miscellaneous_Mathematical_SymbolsB2980() :
	    my_first_letter(0x2980),
	    my_last_letter(0x29FF)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~Miscellaneous_Mathematical_SymbolsB2980() { }

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
	    return "Miscellaneous Mathematical Symbols-B";
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
            return Babylon::Gen_Cat(Miscellaneous_Mathematical_SymbolsB2980::my_cat[uc - my_first_letter]);
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
            return Babylon::Char_Decomp(DECOMP_CANONICAL);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            UTF32_string us;
            us.resize(1); us[0] = uc;
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
            return Babylon::Line_Break(Miscellaneous_Mathematical_SymbolsB2980::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Miscellaneous_Mathematical_SymbolsB2980::my_ea[uc - my_first_letter]);
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

      private:
        // functions
        Miscellaneous_Mathematical_SymbolsB2980(const Miscellaneous_Mathematical_SymbolsB2980 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const unsigned char my_cat[128];
        static const std::bitset<128> my_mirror;
        static const unsigned char my_lb[128];
        static const unsigned char my_ea[128];
    }; // class Miscellaneous_Mathematical_SymbolsB2980

    const unsigned char Miscellaneous_Mathematical_SymbolsB2980::my_cat[] =
    {
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, 
        CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, 
        CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Ps, 
        CAT_Pe, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Ps, CAT_Pe, CAT_Ps, CAT_Pe, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, 
        CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Ps, CAT_Pe, CAT_Sm, CAT_Sm
    };

    const std::bitset<128> Miscellaneous_Mathematical_SymbolsB2980::my_mirror(std::string("00110011111100000000001100111010000111110011011111000010001111110000000100000000111111111111111111111001111111111111111111111000"));

    const unsigned char Miscellaneous_Mathematical_SymbolsB2980::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, 
        LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, 
        LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, LB_CL, LB_OP, 
        LB_CL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_OP, LB_CL, LB_OP, LB_CL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, LB_AL, LB_AL
    };

    const unsigned char Miscellaneous_Mathematical_SymbolsB2980::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
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

dload(Babylon::Module::Miscellaneous_Mathematical_SymbolsB2980);
