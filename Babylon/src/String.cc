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

#include <Prague/Sys/Tracer.hh>

#include <Babylon/String.hh>
#include <Babylon/internal/Dictionary.hh>

// Constructors:

Babylon::String::String() :
    my_norm(NORM_NONE),
    my_data()
{ }

Babylon::String::String(const String & s,
			const size_type p1, const size_type p2) :
    my_norm(s.my_norm),
    my_data(s.my_data, p1, p2)
{ }

Babylon::String::String(const char_type * c, const Norm n) :
    my_norm(n),
    my_data(c)
{ }

Babylon::String::String(const char_type * c, const size_type l,
			const Norm n) :
    my_norm(n),
    my_data(c, l)
{ }

Babylon::String::String(const size_type l, const char_type c, const Norm n) :
    my_norm(n),
    my_data(l, c)
{ }

Babylon::String::String(const string_type & s) :
    my_norm(NORM_NONE),
    my_data(s)
{ }

template<class InputIterator>
Babylon::String::String(InputIterator b, InputIterator e,
			const Norm n) :
    my_norm(n),
    my_data(b, e)
{ }

Babylon::String::~String() { }

// members:

void Babylon::String::norm(const Norm n)
{
    String tmp(get_normalized(n));
    swap(tmp);
}

Babylon::String Babylon::String::get_normalized(const Norm n) const
{
    // catch common conditions in which we can just return this string:
    if (empty() || n == my_norm || n == NORM_NONE) return *this;

    String r;
    Dictionary * dict = Dictionary::instance();

    // Do I need to decompose?
    if (my_norm > n || (n == NORM_KD && my_norm == NORM_C))
    {
	 for(String::const_iterator i = begin(); i != end(); ++i)
	 {
	     String tmp;
	     get_from_UTF32(dict->recursive_decompose(((n & NORM_MASK_K)
						       != 0),
						      i->value()), tmp);

	     for(String::const_iterator j = tmp.begin(); j != tmp.end(); ++j)
	     {
		 Can_Comb_Class c_class = dict->comb_class(j->value());
		 if (CC_SPACING == c_class)
		     r.push_back(*j);
		 else
		 {
		     size_type k = r.length();
		     for ( ; k > 0; --k)
			 if (dict->comb_class(r[k - 1].value()) <= c_class)
			     break;
		     r.insert(k, 1, *j);
		 }
	     }
	 }
    }
    else r = my_data;

    // Do I need to compose?
    if ((my_norm != NORM_C) && (n & NORM_MASK_C))
    {
	String::iterator starter = r.begin();
	String::iterator comp_pos = starter + 1; // we have at least 1 char!
	Can_Comb_Class last_class = dict->comb_class(starter->value());
	if (last_class != 0) // fix for irregular comb sequence
	    last_class = Can_Comb_Class(256);
	
	for(String::iterator ch = comp_pos; ch != r.end(); ++ch)
	{
	    Can_Comb_Class ch_class = dict->comb_class(ch->value());
	    UCS4 composite(dict->compose(starter->value(), ch->value()));
	    if (dict->is_Full_Composition_Exclusion(composite))
		composite = UC_NULL;

	    if ( (composite != 0) &&
		 (last_class < ch_class || last_class == 0) )
		*starter = composite;
	    else
	    {
		if (ch_class == 0) starter = comp_pos;
		last_class = ch_class;
		*comp_pos = *ch;
		comp_pos++;
	    }
	}
	r.resize(std::distance(r.begin(), comp_pos));
    }
    r.override_norm(n);
    return r;
}

int Babylon::String::compare(const size_type, const size_type,
			     const String &) const
{
    // FIXME:
}

int Babylon::String::compare(const size_type, const size_type, const String &,
			     const size_type, const size_type) const
{
    // FIXME:
}

int Babylon::String::compare(const char_type *) const
{
    // FIXME:
}

int Babylon::String::compare(const size_type, const size_type,
			     const char_type *) const
{
    // FIXME:
}

int Babylon::String::compare(const size_type, const size_type,
			     const char_type *, const size_type) const
{
    // FIXME:
}

Babylon::String::char_type & Babylon::String::operator[](const size_type p)
{
    return my_data[p];
}

Babylon::String::char_type & Babylon::String::at(const size_type p)
{
    return my_data.at(p);
}

Babylon::String &
Babylon::String::assign(const Babylon::String & s,
			const size_type p1, const size_type p2)
{
    my_data.assign(s.my_data, p1, p2);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String & Babylon::String::assign(const char_type * c, const Norm n)
{
    my_data.assign(c);
    my_norm = n;
    return *this;
}

Babylon::String &
Babylon::String::assign(const char_type * c, const size_type l,	const Norm n)
{
    my_data.assign(c, l);
    my_norm = n;
    return *this;
}

Babylon::String &
Babylon::String::assign(const size_type l, const char_type c)
{
    my_data.assign(l, c);
    my_norm = NORM_NONE;
    return *this;
}

void Babylon::String::swap(Babylon::String & that) throw()
{
    std::swap(my_data, that.my_data);
    std::swap(my_norm, that.my_norm);
}

Babylon::String &
Babylon::String::append(const Babylon::String & s,
			const size_type p1, const size_type p2)
{
    size_type start = my_data.length();
    my_data.append(s.my_data, p1, p2);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String &
Babylon::String::append(const char_type * c, const size_type l,	const Norm n)
{
    size_type start = my_data.length();
    my_data.append(c, l);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String & Babylon::String::append(const char_type * c, const Norm n)
{
    my_data.append(c);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String &
Babylon::String::append(const size_type l, const char_type c)
{
    my_data.append(l, c);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String &
Babylon::String::insert(const size_type p1, const Babylon::String & s,
			const size_type p2, const size_type p3)
{
    my_data.insert(p1, s.my_data, p2, p3);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String &
Babylon::String::insert(const size_type p1,
			const char_type * c, const size_type p2)
{
    my_data.insert(p1, c, p2);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String &
Babylon::String::insert(const size_type p1, const char_type * c)
{
    size_type old_length = my_data.length();
    my_data.insert(p1, c);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String &
Babylon::String::insert(const size_type p1, const size_type p2,
			const char_type c)
{
    my_data.insert(p1, p2, c);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String &
Babylon::String::replace(const size_type p1, const size_type p2,
			 const Babylon::String & s,
			 const size_type p3, const size_type p4)
{
    my_data.replace(p1, p2, s.my_data, p3, p4);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String &
Babylon::String::replace(const size_type p1, const size_type p2,
			 const char_type * c, const size_type l)
{
    my_data.replace(p1, p2, c, l);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String &
Babylon::String::replace(const size_type p1,  const size_type p2,
			 const char_type * c)
{
    my_data.replace(p1, p2, c);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

Babylon::String &
Babylon::String::replace(const size_type p1, const size_type p2,
			 const size_type p3, char_type c)
{
    my_data.replace(p1, p2, p3, c);
    my_norm = NORM_NONE; // FIXME: Can we do better?
    return *this;
}

void Babylon::String::resize(const size_type l)
{
    my_data.resize(l);
}

void Babylon::String::resize(const size_type l, char_type c)
{
    my_data.resize(l, c);
}

void Babylon::String::clear()
{
    my_data.clear();
}

Babylon::String & Babylon::String::erase()
{
    my_data.erase();
    return *this;
}

Babylon::String & Babylon::String::erase(const size_type i)
{
    my_data.erase(i);
    return *this;
}

Babylon::String & Babylon::String::erase(const size_type i, const size_type l)
{
    my_data.erase(i, l);
    return *this;
}

Babylon::String & Babylon::String::erase(iterator b, iterator e)
{
    my_data.erase(b, e);
    return *this;
}

Babylon::String::String(const std::string & s, const size_t pos,
			const std::string format,
			const Babylon::Norm norm)
{
    convert(s, pos, format, norm);
}

Babylon::String::String(const char * c,
			const std::string format,
			const Babylon::Norm norm)
{
    std::string s(c);
    convert(s, 0, format, norm);
}

Babylon::String::String(const char * c, const size_t len,
			const std::string format,
			const Babylon::Norm norm)
{
    std::string s(c, len);
    convert(s, 0, format, norm);
}

std::string Babylon::String::convert(const std::string & format) const
    throw (Babylon::Transfer_Error)
{
    std::string result;
    for (Babylon::String::const_iterator i = this->begin();
         i != this->end();
         ++i)
        result.append(i->convert(format));
    return result;
}
    
size_t Babylon::String::convert(const std::string & s,
				const size_t p,
				const std::string & format,
				const Babylon::Norm norm)
    throw (Babylon::Transfer_Error, std::length_error)
{
    clear();

    size_type i = (p >= s.length()) ? std::string::npos : p;
    for ( ; i <= s.length(); )
    {
	push_back(Char(s, i, format));
        if (i == max_size())
            throw (std::length_error("Input String too long."));
    }
    my_norm = norm;
    return i;
}

void Babylon::String::debug_dump() const
{
    std::cerr << "Babylon::String at " << std::hex << this << " Norm: ";
    if (NORM_NONE == my_norm)
	std::cerr << "none";
    else if (NORM_D == my_norm)
	std::cerr << "D";
    else if (NORM_C == my_norm)
	std::cerr << "C";
    else if (NORM_KD == my_norm)
	std::cerr << "KD";
    else if (NORM_KC == my_norm)
	std::cerr << "KC";
    else
	std::cerr << "UNKNOWN";

    std::cerr << " (" << length() << ")  >";
    for(const_iterator i = begin(); i != end(); ++i)
	std::cerr << i->value() << " ";
    std::cerr << "<" << std::dec << std::endl;
}
