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

#include <Babylon/Char.hh>
#include <Babylon/String.hh>
#include <Babylon/utils.hh>
#include <Prague/Sys/Tracer.hh>
#include <functional>

// CONSTRUCTORS:
Babylon::String::String() : m_current_norm(Babylon::NORM_NONE) {
    Prague::Trace trace("Babylon::String::String()");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    resize(0);
}

Babylon::String::String(const Char uc, Norm norm = NORM_NONE)  :
    m_current_norm(norm) {
    Prague::Trace trace("Babylon::String::String(Char, ...)");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    resize(1);
    (*this)[0] = uc;
    m_current_norm = norm;
}

Babylon::String::String(const UCS4 uc, Norm norm = NORM_NONE) :
    m_current_norm(norm) {
    Prague::Trace trace("Babylon::String::String(UCS4, ...)");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    resize(1);
    (*this)[0] = uc;
}

Babylon::String::String(const UTF8_string & s, const Norm norm = NORM_NONE) :
    m_current_norm(norm) {
    Prague::Trace trace("Babylon::String::String(UTF8_string, ...)");
    utf8(s, norm);
}

Babylon::String::String(const char * s, const Norm norm = NORM_NONE) {
    Prague::Trace trace("Babylon::String::String(char *, ...)");
    utf8(s, norm);
}

Babylon::String::String(size_t len, Char * data, const Norm norm = NORM_NONE) :
    m_current_norm(norm) {
    Prague::Trace trace("Babylon::String::String(size_t, ...)");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    this->assign(data, len);
}

Babylon::String::String(const String & us) {
    Prague::Trace trace("Babylon::String::String(String)");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    resize(us.length());
    
    Babylon::String::const_iterator   us_it = us.begin();
    Babylon::String::iterator       this_it = this->begin();
    
    while (us_it != us.end() && this_it != this->end()) {
	*this_it = *us_it;
	++this_it; ++us_it;
    }
    m_current_norm = us.norm();
}

Babylon::String::String(const UTF32_string & us, Norm norm = NORM_NONE) :
    m_current_norm(norm) {
    Prague::Trace trace("Babylon::String::String(UTF32_string, ...)"); 
    Prague::Guard<Prague::Mutex> guard(_mutex);
    resize(us.length());
    
    Babylon::UTF32_string::const_iterator us_it = us.begin();
    Babylon::String::iterator this_it = this->begin();
    
    while (us_it != us.end() && this_it != this->end()) {
	*this_it = *us_it;
	++this_it; ++us_it;
    }
}


// DESTRUCTORS

Babylon::String::~String() {
    Prague::Trace trace("Babylon::String::~String()");
}

void Babylon::String::utf8(const UTF8_string & s, Norm norm = NORM_NONE)
    throw (Trans_Error) {
    Prague::Trace trace("Babylon::String::utf8(...)");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    m_current_norm = norm;
    erase();
    
    UTF8_string::const_iterator it = s.begin();
    while(it != s.end()) {
	Char t;
	it = t.utf8(s, it);
	*this += t;
    }
}

Babylon::UTF8_string Babylon::String::utf8() const throw (Trans_Error) {
    Prague::Trace trace("Babylon::String::utf8()");
    Babylon::UTF8_string res;

    for(String::const_iterator it = this->begin();
	it != this->end();
	++it)
	res += it->utf8();
    return res;
}

void Babylon::String::utf16(const UTF16_string & in , const Norm norm = NORM_NONE)
    throw (Trans_Error) {
    Prague::Trace trace("Babylon::String::utf16(...)");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    m_current_norm = norm;
    erase();

    UTF16_string::const_iterator it = in.begin();
    while(it != in.end()) {
	Char t;
	it = t.utf16(in, it);
	*this += t;
    }
}

Babylon::UTF16_string Babylon::String::utf16() const throw (Trans_Error) {
    Prague::Trace trace("Babylon::String::utf16()");
    UTF16_string res;
    for(String::const_iterator it = this->begin();
	it != this->end();
	++it)
	res += it->utf16();
    return res;
}

void Babylon::String::utf32(const UTF32_string & s,
			    const Norm norm = NORM_NONE) {
    Prague::Trace trace("Babylon::String::utf32(...)");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    erase();
    m_current_norm = norm;
    UTF32_string::const_iterator it = s.begin();
    while(it != s.end()) {
	Char t;
	it = t.utf32(s, it);
	*this += t;
    }
}

Babylon::UTF32_string Babylon::String::utf32() const throw (Trans_Error) {
    Prague::Trace trace("Babylon::String::utf32()");
    UTF32_string res;

    for(String::const_iterator it = this->begin();
	it != this->end();
	++it)
	res += it->utf32();
    return res;
}

void Babylon::String::swap(String & that) {
    Prague::Trace trace("Babylon::String::swap(...)");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    std::swap(*this, that);
    std::swap(m_current_norm, that.m_current_norm);
}

void Babylon::String::normalize(const Norm norm) {
    Prague::Trace trace("Babylon::String::normalize(...)");
    String result;
    Prague::Guard<Prague::Mutex> guard(_mutex);
    if (length() > 0 && norm < NORM_NONE && norm != m_current_norm) {
	Dictionary * dict = Dictionary::instance();
	
	// do I need to decompose?
	if (m_current_norm!=NORM_D || (norm!=NORM_KC && m_current_norm!=NORM_NONE)) {
	    bool compat = (norm & 2); // compatibility bit
	    for(String::const_iterator i = this->begin();
		i != this->end(); ++i) {
		String tmp = dict->recursive_decompose(compat, i->value());
		
		for(String::const_iterator j = tmp.begin();
		    j != tmp.end(); ++j) {
		    Can_Comb_Class c_class = dict->find_char(j->value())->
			comb_class(j->value());
		    String::iterator k = result.end();
		    if (c_class == 0)
			result += *j;
		    else {
			for (; k >= result.begin(); k--)
			    if (dict->find_char((k-1)->value())->
				comb_class((k-1)->value()) <= c_class) break;
			result.insert(k, *j);
		    }
		}
	    }
	}      
	
	// do I need to compose?
	if (m_current_norm != NORM_C && (norm & 1)) {
	    // decomposition skipped?
	    if (result.length() == 0) result = *this;
	    
	    String::iterator starter = result.begin();
	    String::iterator comp_pos = starter + 1;
	    Can_Comb_Class last_class = dict->find_char(starter->value())->
		comb_class(starter->value());
	    if (last_class != 0)
		last_class = Can_Comb_Class(256); // fix for irregular comb sequence
	    
	    for(String::iterator ch = starter + 1;
		ch != result.end(); ++ch) {
		Can_Comb_Class ch_class = dict->find_char(ch->value())->
		    comb_class(ch->value());
		UCS4 composite = dict->find_char(starter->value())->
		    compose(starter->value(), ch->value());
		
		if(composite != 0 && (last_class < ch_class || last_class == 0))
		    *starter = composite;
		else {
		    if(ch_class == 0)
			starter = comp_pos;
		    last_class=ch_class;
		    *comp_pos = *ch;
		    comp_pos++;
		}
	    }
	    result.resize(comp_pos - result.begin());
	} // compose
    }
    if(result.length() != 0) {
	m_current_norm = norm;
	*this = result;
    }
}

Babylon::String Babylon::String::norm(Babylon::Norm norm) const {
    Prague::Trace trace("Babylon::String::norm(...)");
    String tmp = *this;
    tmp.normalize(norm);
    return tmp;
}

/*
void Babylon::String::erase() {
    m_current_norm = Babylon::NORM_NONE;
    std::basic_string<Char>::erase();
}
*/

Babylon::Paragraphs Babylon::String::get_paragraphs() {
    Prague::Trace trace("Babylon::String::get_paragraphs()");
    Babylon::Paragraphs result;
    Babylon::Paragraph current;
    Prague::Guard<Prague::Mutex> guard(_mutex);
    if (this->empty()) return result;

    current.begin = 0;
    for(Babylon::String::iterator i = this->begin();
	i != this->end();
	i = find_if(i, this->end(), std::mem_fun_ref
		    (&Babylon::Char::is_Paragraph_Separator))) {
	current.end = std::distance(this->begin(), i);
	result.push_back(current);
	current.begin = std::distance(this->begin(), i) + 1; 
	                // i != mem_order.end(), so this is ok.
    }
    current.end = std::distance(this->begin(), this->end());
    result.push_back(current);

    for(Babylon::Paragraphs::iterator i = result.begin();
	i != result.end();
	++i)
	i->levels = analyse(this->begin() + i->begin,
			    this->begin() + i->end);

    cerr << "String::get_paragraphs(): size: " << result.size() << endl;

    return result;
}

std::vector<size_t> Babylon::String::get_defined() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_defined())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Spaces() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Space())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_ISO_Controls() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_ISO_Control())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Punctuations() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Punctuation())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Line_Separators() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Line_Separator())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Paragraph_Separators() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Paragraph_Separator())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Currency_Symbols() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Currency_Symbol())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Left_to_Rights() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Left_to_Right())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_European_Digits() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_European_Digit())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Eur_Num_Separators() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Eur_Num_Separator())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Eur_Num_Terminators() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Eur_Num_Terminator())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Arabic_Digits() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Arabic_Digit())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Common_Separator() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Common_Separator())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Block_Separator() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Block_Separator())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Segment_Separator() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Segment_Separator())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Whitespaces() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_defined()) result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Non_spacing_Marks() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Non_spacing_Mark())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Boundary_Neutrals() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Boundary_Neutral())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_PDFs() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_PDF())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Embedding_or_Overrides() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Embedding_or_Override())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Bidi_Other_Neutrals() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Bidi_Other_Neutral())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Viramas() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Virama())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Printables() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Printable())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Not_a_Characters() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Not_a_Character())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Maths() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Math())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Alphabetics() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Alphabetic())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Lowercases() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Lowercase())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Uppercases() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Uppercase())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Titlecases() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Titlecase())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_ID_Starts() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_ID_Start())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_ID_Continues() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_ID_Continue())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_XID_Starts() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_XID_Start())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_XID_Continues() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_XID_Continue())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Decimals() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Decimal())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Digits() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Digit())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Numerics() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Numeric())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

std::vector<size_t> Babylon::String::get_Private_Uses() {
    std::vector<size_t> result;
    for(Babylon::String::const_iterator i = this->begin();
	i != this->end();
	++i)
	if (i->is_Private_Use())
	    result.push_back(std::distance(static_cast<Babylon::String::const_iterator>(this->begin()), i));
    return result;
}

bool Babylon::Paragraph_lt::operator() (const Paragraph & p1,
					 const Paragraph & p2) {
    return p1.end < p2.begin;
}


bool Babylon::Paragraph_eq::operator() (const Paragraph & p1,
					 const Paragraph & p2) {
    return p1.begin == p2.begin && p1.end == p2.end;
}
