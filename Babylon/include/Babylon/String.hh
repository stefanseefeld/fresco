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

#ifndef _Babylon_String_hh
#define _Babylon_String_hh

/* String class
 * This class stores and manipulates strings of characters defined 
 * acordding to ISO10646. 
 */

#include <Babylon/defs.hh>
#include <Babylon/Dictionary.hh>
#include <Babylon/Char.hh>

namespace Babylon {
    typedef std::basic_string<size_t> Char_Mapping;
    struct Paragraph;
    typedef vector<struct Paragraph> Paragraphs;

    // g++ does not yet support char_traits :-(
    class String : public std::basic_string<Babylon::Char> {
    public:
	// CONSTRUCTORS:
	/// Creates a string of the length 0.
	String();

	/// Creates a string of the length 1 containing 
	String(const Char, const Norm norm = NORM_NONE);
	String(const UCS4, const Norm norm = NORM_NONE);

	// Creates a string out of other types of strings
	String(const UTF8_string & s, const Norm norm = NORM_NONE);
	String(const char * s, const Norm norm = NORM_NONE);
	String(const UTF32_string &, const Norm norm = NORM_NONE);
	String(size_t len, Char * data, const Norm norm = NORM_NONE);
	String(const String &);

	// Transformators:
	void utf8(const UTF8_string &, const Norm norm = NORM_NONE)
	    throw (Trans_Error);
	void utf8(const char * s, const Norm norm = NORM_NONE)
	    throw (Trans_Error) { utf8(UTF8_string(s), norm); }
	void utf16(const UTF16_string &, const Norm norm = NORM_NONE)
	    throw (Trans_Error);
	void utf16(const UCS2 * s, const Norm norm = NORM_NONE)
	    throw (Trans_Error) { utf16(UTF16_string(s), norm); }
	void utf32(const UTF32_string &, const Norm norm = NORM_NONE);
	UTF8_string  utf8() const throw (Trans_Error);
	UTF16_string utf16() const throw(Trans_Error);
	UTF32_string utf32() const throw(Trans_Error);

	void swap(String &);
    
	// normalizes a String.
	void normalize(const Norm);
    
	// returns the norm the string is in
	Norm norm() const { return m_current_norm; }
    
	// sets the norm the String is in. Does NOT change the
	// string itself, so USE WITH CAUTION!
	void override_norm(const Norm norm) { m_current_norm = norm; }
    
	// returns the normalized form of a string without changing it.
	String norm(const Norm norm) const;

	vector<size_t> get_defined();
	vector<size_t> get_Spaces();
	vector<size_t> get_ISO_Controls();
	vector<size_t> get_Punctuations();
	vector<size_t> get_Line_Separators();
	vector<size_t> get_Paragraph_Separators();
	vector<size_t> get_Currency_Symbols();
	vector<size_t> get_Bidi_Left_to_Rights();
	vector<size_t> get_Bidi_European_Digits();
	vector<size_t> get_Bidi_Eur_Num_Separators();
	vector<size_t> get_Bidi_Eur_Num_Terminators();
	vector<size_t> get_Bidi_Arabic_Digits();
	vector<size_t> get_Bidi_Common_Separator();
	vector<size_t> get_Bidi_Block_Separator();
	vector<size_t> get_Bidi_Segment_Separator();
	vector<size_t> get_Bidi_Whitespaces();
	vector<size_t> get_Bidi_Non_spacing_Marks();
	vector<size_t> get_Bidi_Boundary_Neutrals();
	vector<size_t> get_Bidi_PDFs();
	vector<size_t> get_Bidi_Embedding_or_Overrides();
	vector<size_t> get_Bidi_Other_Neutrals();
	vector<size_t> get_Viramas();
	vector<size_t> get_Printables();
	vector<size_t> get_Not_a_Characters();
	vector<size_t> get_Maths();
	vector<size_t> get_Alphabetics();
	vector<size_t> get_Lowercases();
	vector<size_t> get_Uppercases();
	vector<size_t> get_Titlecases();
	vector<size_t> get_ID_Starts();
	vector<size_t> get_ID_Continues();
	vector<size_t> get_XID_Starts();
	vector<size_t> get_XID_Continues();
	vector<size_t> get_Decimals();
	vector<size_t> get_Digits();
	vector<size_t> get_Numerics();
	vector<size_t> get_Private_Uses();

	// OPERATORS:
    
	// UTILITIES:
	// void erase();

	//. Get a list of paragraphs, their beginnings and ends etc.
	Paragraphs get_paragraphs();

	// DESTRUCTOR:
	~String(); // nothing special needed...

    protected:
    private:
	Babylon::Norm m_current_norm;
	Prague::Mutex _mutex;
    }; // class String

    struct Paragraph {
	size_t begin;
	size_t end;
	Embedding_Levels levels;

	Paragraph() : begin(0), end(0), levels() {}
	Paragraph(size_t b, size_t e) : begin(b), end(e), levels() {}
    };

    class Paragraph_lt {
    public:
	Paragraph_lt() {}
	bool operator() (const Paragraph &, const Paragraph &);
    };

    class Paragraph_eq {
    public:
	Paragraph_eq() {}
	bool operator() (const Paragraph &, const Paragraph &);
    };

} // namespace Babylon

namespace std {
    template<>
    inline void swap(Babylon::String & a, Babylon::String & b) {
	a.swap(b);
    }
}

#endif // _Babylon_String_hh
