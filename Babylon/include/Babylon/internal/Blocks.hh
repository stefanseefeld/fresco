/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999-2003 Tobias Hunger <Tobias@fresco.org>
 * http://www.fresco.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 */

#ifndef _Babylon_internal_Blocks_hh_
#define _Babylon_internal_Blocks_hh_

#include <Babylon/internal/utfstrings.hh>
#include <Prague/Sys/Plugin.hh>

namespace Babylon {

  class Block {
      // This class is subclassed by plugin libraries.
      // No method bodies here!!
      
      // These Blocks are build for speed, not safety!
      // The Dictionary has to make sure that it is
      // asking the right block about defined properties.
      
      // It can do so by calling the appropriate is_*
      
  public:
      Block() { }
      virtual ~Block() { }
      virtual void clean() { }
      virtual bool is_undef_block() const = 0; // returns 1 if this
	                                       // block is meant to handle
	                                       // all undefined characters
	                                       // 
	                                       // The first undef_block
	                                       // found will be used!
	
      // Query Functions:
      virtual bool is_defined(const UCS4)  const = 0;
      virtual UCS4 uppercase(const UCS4) const = 0;
      virtual UCS4 lowercase(const UCS4) const = 0;
      virtual UCS4 titlecase(const UCS4) const = 0;
      
      virtual float numeric_value(const UCS4) const = 0;
      virtual bool is_Numeric(const UCS4) const = 0;
      virtual int dec_digit_value(const UCS4) const = 0;
      virtual bool is_Decimal_Digit(const UCS4) const = 0;
      virtual int digit_value(const UCS4) const = 0;
      virtual bool is_Digit(const UCS4) const = 0;
      
      virtual std::string blockname(const UCS4) const = 0;
      virtual Gen_Cat category(const UCS4) const = 0;
      virtual Can_Comb_Class comb_class(const UCS4) const = 0;
      virtual Bidir_Props bidir_props(const UCS4) const = 0;
      virtual Char_Decomp decomp_type(const UCS4) const = 0;
      virtual UTF32_string decompose(const UCS4) const = 0;
      virtual bool exclude_from_composition(const UCS4 uc) const = 0;
      virtual UCS4 compose(const UCS4, const UCS4) = 0;
      virtual bool must_mirror(const UCS4) const = 0;
      virtual EA_Width EA_width(const UCS4) const = 0;
      virtual Line_Break linebreak(const UCS4) const = 0;
      
      // Properties:
      virtual bool is_White_Space(const UCS4) const = 0;
      virtual bool is_Bidi_Control(const UCS4) const = 0;
      virtual bool is_Join_Control(const UCS4) const = 0;
      virtual bool is_Dash(const UCS4) const = 0;
      virtual bool is_Hyphen(const UCS4) const = 0;
      virtual bool is_Quotation_Mark(const UCS4) const = 0;
      virtual bool is_Terminal_Punctuation(const UCS4) const = 0;
      virtual bool is_Other_Math(const UCS4) const = 0;
      virtual bool is_Hex_Digit(const UCS4) const = 0;
      virtual bool is_ASCII_Hex_Digit(const UCS4) const = 0;
      virtual bool is_Other_Alphabetic(const UCS4) const = 0;
      virtual bool is_Ideographic(const UCS4) const = 0;
      virtual bool is_Diacritic(const UCS4) const = 0;
      virtual bool is_Extender(const UCS4) const = 0;
      virtual bool is_Other_Uppercase(const UCS4) const = 0;
      virtual bool is_Other_Lowercase(const UCS4) const = 0;
      virtual bool is_Noncharacter_Code_Point(const UCS4) const = 0;
      virtual bool is_Other_Grapheme_Extend(const UCS4) const = 0;
      virtual bool is_Grapheme_Link(const UCS4) const = 0;
      virtual bool is_IDS_Binary_Operator(const UCS4) const = 0;
      virtual bool is_IDS_Trinary_Operator(const UCS4) const = 0;
      virtual bool is_Radical(const UCS4) const = 0;
      virtual bool is_Unified_Ideograph(const UCS4) const = 0;
      virtual bool is_Other_Default_Ignorable_Code_Point(const UCS4) const = 0;
      virtual bool is_Deprecated(const UCS4) const = 0;
      virtual bool is_Soft_Dotted(const UCS4) const = 0;
      virtual bool is_Logical_Order_Exception(const UCS4) const = 0;
      virtual bool is_Other_ID_Start(const UCS4) const = 0;
      
      virtual UCS4 first_letter() const = 0;
      virtual UCS4 last_letter() const = 0;
  protected:
      
  private:
  }; // class Block
    
}; // namespace Babylon

#endif
