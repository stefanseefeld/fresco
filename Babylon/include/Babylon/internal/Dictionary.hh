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

#ifndef _Babylon_internal_Dictionary_hh_
#define _Babylon_internal_Dictionary_hh_

#include <Babylon/exceptions.hh>
#include <Babylon/internal/utfstrings.hh>

#include <Prague/Sys/Plugin.hh>
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/Path.hh>

namespace Babylon {
  class Block;

  //. Stores character data.
  class Dictionary {

      struct Dict_Guard
      {
	  ~Dict_Guard() { delete Dictionary::my_dictionary; }
      };
      friend struct Dict_Guard;
      
  public:
      //. Scans a directory for modules.
      void update(const std::string &)
	  throw (std::runtime_error, Block_Error);
      
      //. Finds the current dictionary.
      //. If no dictionary exists it will create one.
      static Dictionary * instance();
      
      // Queries for the datastructures stored in the Dictionary:
      
      //. Returns the first letter of the block (aka script)
      //. the given character belongs to. It returns
      //. UC_MAX_DEFINED if the character does not belong
      //. to a block.
      UCS4 first_letter_of_block(const UCS4) const throw ();
      
      //. Returns the last letter of the block (aka script)
      //. the given character belongs to. It returns
      //. UC_MAX_DEFINED if the character does not belong
      //. to a block
      UCS4 last_letter_of_block(const UCS4) const throw ();
      
      //. Returns the first letter of the next block (aka script)
      //. defined block after the given character.
      //. It returns UC_MAX_DEFINED if there is no block after
      //. the character.
      UCS4 start_of_next_block(const UCS4) const throw();
      
      // Query functions:
      bool is_defined(const UCS4 uc) const throw (Block_Error);    
      UCS4 uppercase(const UCS4 uc) const throw (Block_Error);
      UCS4 lowercase(const UCS4 uc) const throw (Block_Error);
      UCS4 titlecase(const UCS4 uc) const throw (Block_Error);
      
      float numeric_value(const UCS4 uc) const
	  throw (Undefined_Property, Block_Error);
      bool is_Numeric(const UCS4 uc) const
	  throw (Block_Error);
      int dec_digit_value(const UCS4 uc) const
	  throw (Undefined_Property, Block_Error);
      bool is_Decimal_Digit(const UCS4 uc) const
	  throw (Block_Error);
      int digit_value(const UCS4 uc) const
	  throw (Undefined_Property, Block_Error);
      bool is_Digit(const UCS4 uc) const
	  throw (Block_Error);
      
      std::string blockname(const UCS4 uc) const
	  throw (Block_Error);
      
      Gen_Cat category(const UCS4) const
	  throw (Undefined_Property, Block_Error);
      Can_Comb_Class comb_class(const UCS4) const
	  throw (Undefined_Property, Block_Error);
      Bidir_Props bidir_props(const UCS4) const
	  throw (Undefined_Property, Block_Error);
      Char_Decomp decomp_type(const UCS4) const
	  throw (Undefined_Property, Block_Error);
      UTF32_string decompose(const UCS4) const
	  throw (Block_Error);
      
      UTF32_string recursive_decompose(const bool compat, const UCS4 uc) const
	  throw (Block_Error);
      
      bool exclude_from_composition(const UCS4) const throw (Block_Error);
      UCS4 compose(const UCS4 starter, const UCS4 last) const
	  throw (Block_Error);
      
      bool must_mirror(const UCS4 uc) const throw (Block_Error);
      
      EA_Width EA_width(const UCS4 uc) const throw (Block_Error);
      Line_Break linebreak(const UCS4 uc) const throw (Block_Error);
      
      // Properties:
      bool is_White_Space(const UCS4) const throw (Block_Error);
      bool is_Bidi_Control(const UCS4) const throw (Block_Error);
      bool is_Join_Control(const UCS4) const throw (Block_Error);
      bool is_Dash(const UCS4) const throw (Block_Error);
      bool is_Hyphen(const UCS4) const throw (Block_Error);
      bool is_Quotation_Mark(const UCS4) const throw (Block_Error);
      bool is_Terminal_Punctuation(const UCS4) const throw (Block_Error);
      bool is_Other_Math(const UCS4) const throw (Block_Error);
      bool is_Hex_Digit(const UCS4) const throw (Block_Error);
      bool is_ASCII_Hex_Digit(const UCS4) const throw (Block_Error);
      bool is_Other_Alphabetic(const UCS4) const throw (Block_Error);
      bool is_Ideographic(const UCS4) const throw (Block_Error);
      bool is_Diacritic(const UCS4) const throw (Block_Error);
      bool is_Extender(const UCS4) const throw (Block_Error);
      bool is_Other_Lowercase(const UCS4) const throw (Block_Error);
      bool is_Other_Uppercase(const UCS4) const throw (Block_Error);
      bool is_Noncharacter_Code_Point(const UCS4) const throw (Block_Error);
      bool is_Other_Grapheme_Extend(const UCS4) const throw (Block_Error);
      bool is_Grapheme_Link(const UCS4) const throw (Block_Error);
      bool is_IDS_Binary_Operator(const UCS4) const throw (Block_Error);
      bool is_IDS_Trinary_Operator(const UCS4) const throw (Block_Error);
      bool is_Radical(const UCS4) const throw (Block_Error);
      bool is_Unified_Ideograph(const UCS4) const throw (Block_Error);
      bool is_Other_Default_Ignorable_Code_Point(const UCS4) const
	  throw (Block_Error);
      bool is_Deprecated(const UCS4) const throw (Block_Error);
      bool is_Soft_Dotted(const UCS4) const throw (Block_Error);
      bool is_Logical_Order_Exception(const UCS4) const throw (Block_Error);
      bool is_Other_ID_Start(const UCS4) const throw (Block_Error);

      // Derived Properties:
      bool is_Math(const UCS4) const throw (Block_Error);
      bool is_Alphabetic(const UCS4) const throw (Block_Error);
      bool is_Lowercase(const UCS4) const throw (Block_Error);
      bool is_Uppercase(const UCS4) const throw (Block_Error);
      bool is_ID_Start(const UCS4) const throw (Block_Error);
      bool is_ID_Continue(const UCS4) const throw (Block_Error);
      bool is_XID_Start(const UCS4) const throw (Block_Error);
      bool is_XID_Continue(const UCS4) const throw (Block_Error);
      bool is_Default_Ignorable_Code_Point(const UCS4) const
	  throw (Block_Error);
      bool is_Grapheme_Extend(const UCS4) const throw (Block_Error);
      bool is_Grapheme_Base(const UCS4) const throw (Block_Error);
      bool is_FC_NFKC_Closure(const UCS4) const throw (Block_Error);
      bool is_Full_Composition_Exclusion(const UCS4) const
	  throw (Block_Error);
      bool is_NFD_QuickCheck(const UCS4) const throw (Block_Error);
      bool is_NFC_QuickCheck(const UCS4) const throw (Block_Error);
      bool is_NFKD_QuickCheck(const UCS4) const throw (Block_Error);
      bool is_NFKC_QuickCheck(const UCS4) const throw (Block_Error);
      bool is_Expands_On_NFD(const UCS4) const throw (Block_Error);
      bool is_Expands_On_NFC(const UCS4) const throw (Block_Error);
      bool is_Expands_On_NFKD(const UCS4) const throw (Block_Error);
      bool is_Expands_On_NFKC(const UCS4) const throw (Block_Error);

      // Further Properties:
      bool is_Space(const UCS4) const throw (Block_Error);
      bool is_Punctuation(const UCS4) const throw (Block_Error);
      bool is_Line_Separator(const UCS4) const throw (Block_Error);
      bool is_Paragraph_Separator(const UCS4) const throw (Block_Error);
      bool is_Currency_Symbol(const UCS4) const throw (Block_Error);
      bool is_Bidi_Left_to_Right(const UCS4) const throw (Block_Error);
      bool is_Bidi_European_Digit(const UCS4) const throw (Block_Error);
      bool is_Bidi_Eur_Num_Separator(const UCS4) const throw (Block_Error);
      bool is_Bidi_Eur_Num_Terminator(const UCS4) const throw (Block_Error);
      bool is_Bidi_Arabic_Digit(const UCS4) const throw (Block_Error);
      bool is_Bidi_Common_Separator(const UCS4) const throw (Block_Error);
      bool is_Bidi_Block_Separator(const UCS4) const throw (Block_Error);
      bool is_Bidi_Segment_Separator(const UCS4) const throw (Block_Error);
      bool is_Bidi_Whitespace(const UCS4) const throw (Block_Error);
      bool is_Bidi_Non_spacing_Mark(const UCS4) const throw (Block_Error);
      bool is_Bidi_Boundary_Neutral(const UCS4) const throw (Block_Error);
      bool is_Bidi_PDF(const UCS4) const throw (Block_Error);
      bool is_Bidi_Embedding_or_Override(const UCS4) const
	  throw (Block_Error);
      bool is_Bidi_Other_Neutral(const UCS4) const throw (Block_Error);
      bool is_Virama(const UCS4) const throw (Block_Error);
      bool is_Printable(const UCS4) const throw (Block_Error);
      bool is_Titlecase(const UCS4) const throw (Block_Error);
      bool is_Private_Use(const UCS4) const throw (Block_Error);

    private:

      struct Data
      {
	  UCS4 my_start;
	  UCS4 my_end;
	  std::string my_file;
	  int operator < (const Data & data) const
	  {
	      return my_start < data.my_start;
	  }
	  bool my_can_remove;
	  Prague::Plugin<Babylon::Block> * my_block;
	  
	  Data(UCS4 start, UCS4 end)
	  {
	      my_start = start;
	      my_end = end;
	      my_file = "";
	      my_can_remove = 0;
	      my_block = 0;
	  }
      }; // struct Data

      class DataLess {
      public:
	  bool operator() (const Data & d1, const Data & d2)
	  {
	      return d1.my_end < d2.my_start;
	  }
      }; // class DataLess
      
      Prague::Plugin<Babylon::Block> * my_undef_block;
      
      Babylon::Block * find_char(const UCS4) const throw (Block_Error);
      
      Dictionary();
      Dictionary(const Dictionary &) {}
      ~Dictionary();
      void clean();
      
      static Dictionary * my_dictionary;
      static Dict_Guard my_guard;
      static Prague::Mutex my_singleton_mutex;
      
      mutable std::vector<Data> my_data;
      
      mutable Prague::RWLock my_rw_lock;
      
  }; // class Dictionary
    
}; // namespace Babylon

#endif
