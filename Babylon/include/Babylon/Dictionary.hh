/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999,2000 Tobias Hunger <Tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
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

#ifndef _Dictionary_hh_
#define _Dictionary_hh_

#include <Babylon/defs.hh>
#include <Prague/Sys/Plugin.hh>
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/Directory.hh>
#include <Prague/Sys/DLL.hh>
#include <Prague/Filter/gzstream.hh>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace Babylon {

    class Dictionary {

	struct Guard { ~Guard() { delete Dictionary::m_dictionary;}};
	friend struct Guard;
    
    public:
	void update(const string &);
	static Dictionary * instance();
    
    private:
	Dictionary * lock() { m_rw_lock.rlock(); return this; };
	void unlock() { m_rw_lock.unlock(); };
    
	// Query functions:
	bool is_defined(const UCS4 uc)
	    throw (Block_Error);    
	UCS4 uppercase(const UCS4 uc)
	    throw (Block_Error);
	UCS4 lowercase(const UCS4 uc)
	    throw (Block_Error);
	UCS4 titlecase(const UCS4 uc)
	    throw (Block_Error);
    
	float numeric_value(const UCS4 uc)
	    throw (Undefined_Property, Block_Error);
	int dec_digit_value(const UCS4 uc)
	    throw (Undefined_Property, Block_Error);
	int digit_value(const UCS4 uc)
	    throw (Undefined_Property, Block_Error);
    
	string blockname(const UCS4 uc)
	    throw (Block_Error);
    
	Gen_Cat category(const UCS4 uc)
	    throw (Undefined_Property, Block_Error);
	Can_Comb_Class comb_class(const UCS4 uc)
	    throw (Undefined_Property, Block_Error);
	Bidir_Props bidir_props(const UCS4 uc)
	    throw (Undefined_Property, Block_Error);
	Char_Decomp decomp_type(const UCS4 uc) 
	    throw (Undefined_Property, Block_Error);
	UTF32_string decompose(const UCS4 uc)
	    throw (Block_Error);
    
	UTF32_string recursive_decompose(const bool compat, const UCS4 uc)
	    throw (Block_Error);
    
	UCS4 compose(const UCS4 starter, const UCS4 last)
	    throw (Block_Error);
    
	bool must_mirror(const UCS4 uc)
	    throw (Block_Error);
    
	EA_Width EA_width(const UCS4 uc)
	    throw (Block_Error);
	Line_Break linebreak(const UCS4 uc)
	    throw (Block_Error);

	bool is_Zero_width(const UCS4 uc)
	    throw (Block_Error);
	bool is_White_space(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Non_break(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Control(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Join_Control(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Format_Control(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Dash(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Hyphen(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Quotation_Mark(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Terminal_Punctuation(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Math(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Paired_Punctuation(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Left_of_Pair(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Combining(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Non_spacing(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Hex_Digit(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Alphabetic(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Diacritic(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Extender(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Identifier_Part(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Ignorable_Control(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Hebrew_Right_to_Left(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Arabic_Right_to_Left(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Embedding_or_Override(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Uppercase(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Lowercase(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Space(const UCS4 uc) 
	    throw (Block_Error);
	bool is_ISO_Control(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Punctuation(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Line_Separator(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Paragraph_Separator(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Currency_Symbol(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Titlecase(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Composite(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Decimal_Digit(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Numeric(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Digit(const UCS4 uc)
	    throw (Block_Error);
	bool is_Ideographic(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Left_to_Right(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_European_Digit(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Eur_Num_Separator(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Eur_Num_Terminator(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Arabic_Digit(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Common_Separator(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Block_Separator(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Segment_Separator(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Whitespace(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Non_spacing_Mark(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Boundary_Neutral(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_PDF(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_LRE(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_RLE(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_LRO(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_RLO(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Bidi_Other_Neutral(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Private_Use(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Not_a_Character(const UCS4 uc) 
	    throw (Block_Error);
	bool is_Unassigned_Code_Value(const UCS4) 
	    throw (Block_Error);
	bool is_Low_Surrogate(const UCS4)
	    throw (Block_Error);
	bool is_High_Surrogate(const UCS4)
	    throw (Block_Error);
	bool is_Private_Use_High_Surrogate(const UCS4)
	    throw (Block_Error);

    
	class Block {
	    // This class is subclassed by plugin libraries.
	    // No method bodies here!!

	    // These Blocks are build for speed, not safety!
	    // The Dictionary has to make sure, that it is
	    // asking the right block about defined properties.

	    // It can do so by calling the appropriate is_*

	public:
	    Block();
	    virtual ~Block();
	    virtual void clean();
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
	    virtual int dec_digit_value(const UCS4) const = 0;
	    virtual int digit_value(const UCS4) const = 0;
	    virtual string blockname(const UCS4) const = 0;
	    virtual Gen_Cat category(const UCS4) const = 0;
	    virtual Can_Comb_Class comb_class(const UCS4) const = 0;
	    virtual Bidir_Props bidir_props(const UCS4) const = 0;
	    virtual Char_Decomp decomp_type(const UCS4) const = 0;
	    virtual UTF32_string decompose(const UCS4) const = 0;
	    virtual UCS4 compose(const UCS4, const UCS4) = 0;
	    virtual bool must_mirror(const UCS4) const = 0;
	    virtual EA_Width EA_width(const UCS4) const = 0;
	    virtual Line_Break linebreak(const UCS4) const = 0;
	    virtual bool is_Zero_width(const UCS4) const = 0;
	    virtual bool is_White_space(const UCS4) const = 0;
	    virtual bool is_Non_break(const UCS4) const = 0;
	    virtual bool is_Bidi_Control(const UCS4) const = 0;
	    virtual bool is_Join_Control(const UCS4) const = 0;
	    virtual bool is_Format_Control(const UCS4) const = 0;
	    virtual bool is_Dash(const UCS4) const = 0;
	    virtual bool is_Hyphen(const UCS4) const = 0;
	    virtual bool is_Quotation_Mark(const UCS4) const = 0;
	    virtual bool is_Terminal_Punctuation(const UCS4) const = 0;
	    virtual bool is_Math(const UCS4) const = 0;
	    virtual bool is_Paired_Punctuation(const UCS4) const = 0;
	    virtual bool is_Left_of_Pair(const UCS4) const = 0;
	    virtual bool is_Combining(const UCS4) const = 0;
	    virtual bool is_Non_spacing(const UCS4) const = 0;
	    virtual bool is_Hex_Digit(const UCS4) const = 0;
	    virtual bool is_Alphabetic(const UCS4) const = 0;
	    virtual bool is_Diacritic(const UCS4) const = 0;
	    virtual bool is_Extender(const UCS4) const = 0;
	    virtual bool is_Identifier_Part(const UCS4) const = 0;
	    virtual bool is_Ignorable_Control(const UCS4) const = 0;
	    virtual bool is_Bidi_Hebrew_Right_to_Left(const UCS4) const = 0;
	    virtual bool is_Bidi_Arabic_Right_to_Left(const UCS4) const = 0;
	    virtual bool is_Bidi_Embedding_or_Override(const UCS4) const = 0;
	    virtual bool is_Uppercase(const UCS4) const = 0;
	    virtual bool is_Lowercase(const UCS4) const = 0;
	    virtual bool is_Titlecase(const UCS4) const = 0;
	    virtual bool is_Space(const UCS4) const = 0;
	    virtual bool is_ISO_Control(const UCS4) const = 0;
	    virtual bool is_Punctuation(const UCS4) const = 0;
	    virtual bool is_Line_Separator(const UCS4) const = 0;
	    virtual bool is_Paragraph_Separator(const UCS4) const = 0;
	    virtual bool is_Currency_Symbol(const UCS4) const = 0;
	    virtual bool is_Composite(const UCS4) const = 0;
	    virtual bool is_Decimal_Digit(const UCS4) const = 0;
	    virtual bool is_Digit(const UCS4) const = 0;
	    virtual bool is_Numeric(const UCS4) const = 0;
	    virtual bool is_Ideographic(const UCS4) const = 0;
	    virtual bool is_Bidi_Left_to_Right(const UCS4) const = 0;
	    virtual bool is_Bidi_European_Digit(const UCS4) const = 0;
	    virtual bool is_Bidi_Eur_Num_Separator(const UCS4) const = 0;
	    virtual bool is_Bidi_Eur_Num_Terminator(const UCS4) const = 0;
	    virtual bool is_Bidi_Arabic_Digit(const UCS4) const = 0;
	    virtual bool is_Bidi_Common_Separator(const UCS4) const = 0;
	    virtual bool is_Bidi_Block_Separator(const UCS4) const = 0;
	    virtual bool is_Bidi_Segment_Separator(const UCS4) const = 0;
	    virtual bool is_Bidi_Whitespace(const UCS4) const = 0;
	    virtual bool is_Bidi_Non_spacing_Mark(const UCS4) const = 0;
	    virtual bool is_Bidi_Boundary_Neutral(const UCS4) const = 0;
	    virtual bool is_Bidi_PDF(const UCS4) const = 0;
	    virtual bool is_Bidi_LRE(const UCS4) const = 0;
	    virtual bool is_Bidi_RLE(const UCS4) const = 0;
	    virtual bool is_Bidi_LRO(const UCS4) const = 0;
	    virtual bool is_Bidi_RLO(const UCS4) const = 0;
	    virtual bool is_Bidi_Other_Neutral(const UCS4) const = 0;
	    virtual bool is_Private_Use(const UCS4) const = 0;
	    virtual bool is_Not_a_Character(const UCS4) const = 0;
	    virtual bool is_Unassigned_Code_Value(const UCS4) const = 0;
	    virtual bool is_Low_Surrogate(const UCS4) const = 0;
	    virtual bool is_High_Surrogate(const UCS4) const = 0;
	    virtual bool is_Private_Use_High_Surrogate(const UCS4) const = 0;

	    virtual UCS4 firstLetter() = 0;
	    virtual UCS4 lastLetter() = 0;
	protected:
	
	private:
	}; // class Block
    
	struct Data {
	    UCS4 m_start;
	    UCS4 m_end;
	    string m_file;
	    int operator < (const Data & data) const {return m_start < data.m_start;}
	    bool m_can_remove;
	    Prague::Plugin<Dictionary::Block> * m_block;
	}; // struct Data

	Prague::Plugin<Dictionary::Block> * m_undef_block;
    
	Block * find_char(const UCS4)
	    throw (Block_Error);
    
	Dictionary();
	Dictionary(const Dictionary &) {}
	~Dictionary();
	void clean();
    
	static Dictionary * m_dictionary;
	static Guard m_guard;
	static Prague::Mutex m_singleton_mutex;
    
	vector<Data> m_data;
    
	UTF32_string m_version;
    
	Prague::RWLock m_rw_lock;
    
	// friends:
	friend class Babylon::Char;
	friend class Babylon::String;
    }; // class Dictionary
    
} // namespace Babylon

#endif // _Dictionary_hh_
