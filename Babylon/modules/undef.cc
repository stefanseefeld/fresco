/*$Id: undef.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.berlin-fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 28 Nov 2000 00:57:32 +0100.
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

namespace Babylon
{
  namespace Module
  {

    class undef0 : public Babylon::Block
    {
      public:
	void clean() { };

	undef0() :
	    my_first_letter(0x0),
	    my_last_letter(0xFFFFFFFF)
	    // my_version="3.0.1" // Not yet supported!
	{ }


	~undef0() { }

	UCS4 first_letter() const { return my_first_letter; }
	
	UCS4 last_letter() const { return my_last_letter; }
	
	bool is_undef_block() const { return 1; }
	
	// query functions:
	
	std::string blockname(const UCS4 uc) const { return "undefined"; }

	bool is_defined(const UCS4 uc) const { return 0; }
	
	UCS4 uppercase(const UCS4 uc) const { return uc; }
	UCS4 lowercase(const UCS4 uc) const { return uc; }
	UCS4 titlecase(const UCS4 uc) const { return uc; }
	
	int dec_digit_value(const UCS4 uc) const { return 0; }
	
	bool is_Decimal_Digit(const UCS4 uc) const { return 0; }
	int digit_value(const UCS4 uc) const { return 0; }
	
	bool is_Digit(const UCS4 uc) const { return 0; }
	float numeric_value(const UCS4 uc) const { return 0; }
	bool is_Numeric(const UCS4 uc) const { return 0; }
	
	Gen_Cat category(const UCS4 uc) const { return CAT_MAX; }
	
	Can_Comb_Class comb_class(const UCS4 uc) const { return CC_MAX;	}
	
	Bidir_Props bidir_props(const UCS4 uc) const { return BIDIR_INVALID; }
	
	Char_Decomp decomp_type(const UCS4 uc) const { return DECOMP_MAX; }
	UTF32_string decompose(const UCS4 uc) const
	{
	    UTF32_string us;
	    us.resize(1); us[0]=uc;
	    return us;
	}
	
	bool must_mirror(const UCS4 uc) const { return 0; }
	
	Line_Break linebreak(const UCS4 uc) const { return LB_MAX; }
	
	EA_Width EA_width(const UCS4 uc) const
	{
	    if (0x2A6D7 <= uc && uc <= 0x2F7FF) return EA_WIDTH_W;
	    return EA_WIDTH_MAX;
	}

	bool exclude_from_composition(const UCS4 uc) const { return 0; }
	
	UCS4 compose (const UCS4 starter, const UCS4 last) { return 0; }
	
	bool is_White_Space(const UCS4) const { return 0; }
	bool is_Bidi_Control(const UCS4) const { return 0; }
	bool is_Join_Control(const UCS4) const { return 0; }
	bool is_Dash(const UCS4) const { return 0; }
	bool is_Hyphen(const UCS4) const { return 0; }
	bool is_Quotation_Mark(const UCS4) const { return 0; }
	bool is_Terminal_Punctuation(const UCS4) const { return 0; }
	bool is_Other_Math(const UCS4) const { return 0; }
	bool is_Hex_Digit(const UCS4) const { return 0; }
	bool is_ASCII_Hex_Digit(const UCS4) const { return 0; }
	bool is_Other_Alphabetic(const UCS4) const { return 0; }
	bool is_Ideographic(const UCS4) const { return 0; }
	bool is_Diacritic(const UCS4) const { return 0; }
	bool is_Extender(const UCS4) const { return 0; }
	bool is_Other_Lowercase(const UCS4) const { return 0; }
	bool is_Other_Uppercase(const UCS4) const { return 0; }
	bool is_Noncharacter_Code_Point(const UCS4 uc) const
	{
	    return uc <= 0x10FFFF &&
		((uc & 0xFFFF) == 0xFFFE || (uc & 0xFFFF) == 0xFFFF);
	}
	bool is_Other_Grapheme_Extend(const UCS4) const { return 0; }
	bool is_Grapheme_Link(const UCS4) const { return 0; }
	bool is_IDS_Binary_Operator(const UCS4) const { return 0; }
	bool is_IDS_Trinary_Operator(const UCS4) const { return 0; }
	bool is_Radical(const UCS4) const { return 0; }
	bool is_Unified_Ideograph(const UCS4) const { return 0; }
	bool is_Other_Default_Ignorable_Code_Point(const UCS4 uc) const
	{
	    return ((uc >= 0xE0080 && uc <= 0xE00FF) ||
		    (uc >= 0xE01F0 && uc <= 0xE0FFF));
	}
	bool is_Deprecated(const UCS4) const { return 0; }
	bool is_Soft_Dotted(const UCS4) const { return 0; }
	bool is_Logical_Order_Exception(const UCS4) const { return 0; }
	bool is_Other_ID_Start(const UCS4) const { return 0; }
	bool is_XID_Start_Closure(const UCS4 uc) const { return 0; }
	bool is_XID_Continue_Closure(const UCS4 uc) const { return 0; }
      private:
	// functions
	undef0(const undef0 &) ; // no implementation!

	Babylon::UCS4 my_first_letter;
	Babylon::UCS4 my_last_letter;
    }; // class undef0

  }; // namespace
}; // namespace

dload(Babylon::Module::undef0);
