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

#ifndef _String_hh
#define _String_hh

/* String class
 * This class stores and manipulates strings of characters defined 
 * acordding to the Unicode[tm] Standard. 
 */


#include <Babylon/Babylon.hh>
#include <Babylon/Dictionary.hh>

namespace Babylon {
    
class String : public basic_string<Babylon::Char> {
public:
    // CONSTRUCTORS:
    /// Creates a string of the length 0.
    String();

    /// Creates a string of the length 1 containing 
    String(const Babylon::Char, const Norm norm = NORM_NONE);
    String(const Babylon::UCS4, const Norm norm = NORM_NONE);

    // Creates a string out of other types of strings
    String(const String &);
    String(const char * s, const Norm norm = NORM_NONE) { utf8(s); overrideNorm(norm); }
    String(const UTF32String &, const Norm norm = NORM_NONE);
    String(unsigned long len, Babylon::Char * data ) { this->assign(data, len); }

    // Transformators:
    void utf8(const UTF8String &, const Norm norm = NORM_NONE) throw (TransError);
    void utf8(const char * s, const Norm norm = NORM_NONE)
	throw (TransError) { utf8(UTF8String(s), norm); }
    void utf16(const UTF16String &, const Norm norm = NORM_NONE) throw (TransError);
    void utf32(const UTF32String &, const Norm norm = NORM_NONE);
    UTF8String  utf8() const throw (TransError);
    UTF16String utf16() const throw(TransError);
    UTF32String utf32() const;
    
    // normalizes a String.
    void normalize(const Norm);
    
    // returns the norm the string is in
    Babylon::Norm norm() const { return currentNorm; }
    
    // sets the norm the String is in. Does NOT change the
    // string itself, so USE WITH CAUTION!
    void overrideNorm(const Norm norm) { currentNorm = norm; }
    
    // returns the normalized form of a string without changing it.
    String norm(const Norm norm) const;
    
    // returns the number of glyphs in a string
    size_t glyphs() const;
    
    // returns all characters starting at the iterator position up to the start of
    // the next Glyph.
    String getGlyph(String::const_iterator) const;
    
    // sets the iterator to the start of the next glyph.
    void nextGlyph(String::const_iterator &) const;
    
    // returns all characters up to the next line break opportunity. Those are
    // supposed to happen only between words, in all languages!
    // String getWord(String::const_iterator) const;
    
    // sets the iterator to the start of the next word
    // void nextWord(String::const_iterator &) const;
    
    // returns all characters up to the next linebreak.
    // (NOT IMPLEMENTED YET SINCE LINEBREAKING IS STILL MISSING.)
    // String getLine(String::iterator) const;
    
    // sets the iterator to the start of the next line
    // (NOT IMPLEMENTED YET SINCE LINEBREAKING IS STILL MISSING.)
    // void nextLine(String::iterator &) const;
    
    // returns all characters up to the next Paragraph separator.
    String getParagraph(String::const_iterator);
    
    // sets the iterator to the start of the next paragraph
    void nextParagraph(String::const_iterator &) const;
    
    // OPERATORS:
    
    // UTILITIES:
    ostream & _write(ostream &) const;

    void clear() {
	currentNorm = Babylon::NORM_NONE;
	this->resize(0); // Workaround: this->basic_string::clear()
    }

    // DESTRUCTOR:
    // ~String() {} // Noting special needed...
protected:
private:
    Babylon::Norm currentNorm;
}; // class String
    
} // namespace Babylon

// OPERATORS:
inline ostream & operator <<
    (ostream & out, const Babylon::String & us) {
    return us._write(out);
}

#endif // _String_hh
