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
#include <fstream>

namespace Babylon {

class Dictionary {

    struct Guard { ~Guard() { delete Dictionary::dictionary;}};
    friend struct Guard;
    
public:
    void update(const string &) throw (FileError);
    static Dictionary * instance();
    
private:
    Dictionary * lock() { rwLock.rlock(); return this; };
    void unlock() { rwLock.unlock(); };
    
    // Query functions:
    bool isDefined(const UCS4 & _uc) throw (BlockError);    
    UCS4 uppercase(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    UCS4 lowercase(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    UCS4 titlecase(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    
    float numericValue(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    int decDigitValue(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    int digitValue(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    
    string blockname(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    
    Gen_Cat category(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    Can_Comb_Class combClass(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    Bidir_Props bidirProps(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    Char_Decomp decompType(const UCS4 & _uc) 
	throw (UndefinedProperty, BlockError);
    UTF32String decompose(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    
    UTF32String recursiveDecompose(const bool & compat, const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    
    UCS4 compose(const UCS4 & starter, const UCS4 & last)
	throw (UndefinedProperty, BlockError);
    
    bool mustMirror(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    
    EA_Width EAWidth(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);
    Line_Break linebreak(const UCS4 & _uc)
	throw (UndefinedProperty, BlockError);

    bool is_Zero_width(const UCS4 & _uc) {
	return findChar(_uc)->is_Zero_width(_uc);
    }
    bool is_White_space(const UCS4 & _uc) {
	return findChar(_uc)->is_White_space(_uc);
    }
    bool is_Non_break(const UCS4 & _uc) {
	return findChar(_uc)->is_Non_break(_uc);
    }
    bool is_Bidi_Control(const UCS4 & _uc) {
	return findChar(_uc)->is_Bidi_Control(_uc);
    }
    bool is_Join_Control(const UCS4 & _uc) {
	return findChar(_uc)->is_Join_Control(_uc);
    }
    bool is_Format_Control(const UCS4 & _uc) {
	return findChar(_uc)->is_Format_Control(_uc);
    }
    bool is_Dash(const UCS4 & _uc) {
	return findChar(_uc)->is_Dash(_uc);
    }
    bool is_Hyphen(const UCS4 & _uc) {
	return findChar(_uc)->is_Hyphen(_uc);
    }
    bool is_Quotation_Mark(const UCS4 & _uc) {
	return findChar(_uc)->is_Quotation_Mark(_uc);
    }
    bool is_Terminal_Punctuation(const UCS4 & _uc) {
	return findChar(_uc)->is_Terminal_Punctuation(_uc);
    }
    bool is_Math(const UCS4 & _uc) {
	return findChar(_uc)->is_Math(_uc);
    }
    bool is_Paired_Punctuation(const UCS4 & _uc) {
	return findChar(_uc)->is_Paired_Punctuation(_uc);
    }
    bool is_Left_of_Pair(const UCS4 & _uc) {
	return findChar(_uc)->is_Left_of_Pair(_uc);
    }
    bool is_Combining(const UCS4 & _uc) {
	return findChar(_uc)->is_Combining(_uc);
    }
    bool is_Non_spacing(const UCS4 & _uc) {
	return findChar(_uc)->is_Non_spacing(_uc);
    }
    bool is_Hex_Digit(const UCS4 & _uc) {
	return findChar(_uc)->is_Hex_Digit(_uc);
    }
    bool is_Alphabetic(const UCS4 & _uc) {
	return findChar(_uc)->is_Alphabetic(_uc);
    }
    bool is_Diacritic(const UCS4 & _uc) {
	return findChar(_uc)->is_Diacritic(_uc);
    }
    bool is_Extender(const UCS4 & _uc) {
	return findChar(_uc)->is_Extender(_uc);
    }
    bool is_Identifier_Part(const UCS4 & _uc) {
	return findChar(_uc)->is_Identifier_Part(_uc);
    }
    bool is_Ignorable_Control(const UCS4 & _uc) {
	return findChar(_uc)->is_Ignorable_Control(_uc);
    }
    bool is_Bidi_Hebrew_Right_to_Left(const UCS4 & _uc) {
	return findChar(_uc)->is_Bidi_Hebrew_Right_to_Left(_uc);
    }
    bool is_Bidi_Arabic_Right_to_Left(const UCS4 & _uc) {
	return findChar(_uc)->is_Bidi_Arabic_Right_to_Left(_uc);
    }
    bool is_Bidi_Embedding_or_Override(const UCS4 & _uc) {
	return findChar(_uc)->is_Bidi_Embedding_or_Override(_uc);
    }
    bool is_Uppercase(const UCS4 & _uc) {
	return findChar(_uc)->is_Uppercase(_uc);
    }
    bool is_Lowercase(const UCS4 & _uc) {
	return findChar(_uc)->is_Lowercase(_uc);
    }
    bool is_Space(const UCS4 & _uc) {
	return findChar(_uc)->is_Space(_uc);
    }
    bool is_ISO_Control(const UCS4 & _uc) {
	return findChar(_uc)->is_ISO_Control(_uc);
    }
    bool is_Punctuation(const UCS4 & _uc) {
	return findChar(_uc)->is_Punctuation(_uc);
    }
    bool is_Line_Separator(const UCS4 & _uc) {
	return findChar(_uc)->is_Line_Separator(_uc);
    }
    bool is_Paragraph_Separator(const UCS4 & _uc) {
	return findChar(_uc)->is_Paragraph_Separator(_uc);
    }
    bool is_Currency_Symbol(const UCS4 & _uc) {
	return findChar(_uc)->is_Currency_Symbol(_uc);
    }
    bool is_Titlecase(const UCS4 & _uc) {
	return findChar(_uc)->is_Titlecase(_uc);
    }
    
    class Block {
	// This class is subclassed by plugin libraries.
	// No method bodies here!!

    public:
	Block();
	virtual ~Block();
	virtual void clean();
	
	// Query Functions:
	virtual bool isDefined(const UCS4 &) const
	    throw (BlockError) = 0;
	virtual UCS4 uppercase(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual UCS4 lowercase(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual UCS4 titlecase(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual float numericValue(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual int decDigitValue(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual int digitValue(const UCS4 &) const 
	    throw (UndefinedProperty) = 0;
	virtual string blockname(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual Gen_Cat category(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual Can_Comb_Class combClass(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual Bidir_Props bidirProps(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual Char_Decomp decompType(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual UTF32String decompose(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual UCS4 compose(const UCS4 &, const UCS4 &)
	    throw (UndefinedProperty) = 0;
	virtual bool mustMirror(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual EA_Width EAWidth(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual Line_Break linebreak(const UCS4 &) const
	    throw (UndefinedProperty) = 0;
	virtual bool is_Zero_width(const UCS4 &) const = 0;
	virtual bool is_White_space(const UCS4 &) const = 0;
	virtual bool is_Non_break(const UCS4 &) const = 0;
	virtual bool is_Bidi_Control(const UCS4 &) const = 0;
	virtual bool is_Join_Control(const UCS4 &) const = 0;
	virtual bool is_Format_Control(const UCS4 &) const = 0;
	virtual bool is_Dash(const UCS4 &) const = 0;
	virtual bool is_Hyphen(const UCS4 &) const = 0;
	virtual bool is_Quotation_Mark(const UCS4 &) const = 0;
	virtual bool is_Terminal_Punctuation(const UCS4 &) const = 0;
	virtual bool is_Math(const UCS4 &) const = 0;
	virtual bool is_Paired_Punctuation(const UCS4 &) const = 0;
	virtual bool is_Left_of_Pair(const UCS4 &) const = 0;
	virtual bool is_Combining(const UCS4 &) const = 0;
	virtual bool is_Non_spacing(const UCS4 &) const = 0;
	virtual bool is_Hex_Digit(const UCS4 &) const = 0;
	virtual bool is_Alphabetic(const UCS4 &) const = 0;
	virtual bool is_Diacritic(const UCS4 &) const = 0;
	virtual bool is_Extender(const UCS4 &) const = 0;
	virtual bool is_Identifier_Part(const UCS4 &) const = 0;
	virtual bool is_Ignorable_Control(const UCS4 &) const = 0;
	virtual bool is_Bidi_Hebrew_Right_to_Left(const UCS4 &) const = 0;
	virtual bool is_Bidi_Arabic_Right_to_Left(const UCS4 &) const = 0;
	virtual bool is_Bidi_Embedding_or_Override(const UCS4 &) const = 0;
	virtual bool is_Uppercase(const UCS4 &) const = 0;
	virtual bool is_Lowercase(const UCS4 &) const = 0;
	virtual bool is_Space(const UCS4 &) const = 0;
	virtual bool is_ISO_Control(const UCS4 &) const = 0;
	virtual bool is_Punctuation(const UCS4 &) const = 0;
	virtual bool is_Line_Separator(const UCS4 &) const = 0;
	virtual bool is_Paragraph_Separator(const UCS4 &) const = 0;
	virtual bool is_Currency_Symbol(const UCS4 &) const = 0;
	virtual bool is_Titlecase(const UCS4 &) const = 0;

	virtual UCS4 firstLetter() = 0;
	virtual UCS4 lastLetter() = 0;
    protected:
	
    private:
    }; // class Block
    
    struct Data {
	UCS4 start;
	UCS4 end;
	string file;
	int operator < (const Data & data) const {return start < data.start;}
	bool canRemove;
	Prague::Plugin<Dictionary::Block> * block;
    }; // struct Data
    
    Block * findChar(const UCS4 &)
	throw (UndefinedProperty, BlockError);
    
    Dictionary();
    Dictionary(const Dictionary &) {}
    ~Dictionary();
    void clean();
    
    static Dictionary *dictionary;
    static Guard guard;
    static Prague::Mutex singletonMutex;
    
    vector<Data> data;
    
    UTF32String my_version;
    
    Prague::RWLock rwLock;
    
    string plugindir;
    
    // friends:
    friend class Babylon::Char;
    friend class Babylon::String;
}; // class Dictionary
    
}; // namespace Babylon

#endif // _Dictionary_hh_
