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

#ifndef _Babylon_Traits_hh
#define _Babylon_Traits_hh

#if __GNUC__ >= 3

#include <Babylon/Char.hh>
#include <Babylon/defs.hh>

namespace std {

// char_traits
template<>
struct char_traits<Babylon::Char>
{
    typedef Babylon::Char char_type;

    static void assign(char_type& c1, const char_type& c2) { c1 = c2; }

    // integer repressentation of characters
    typedef Babylon::UCS4 int_type;

    static char_type
    to_char_type(const int_type& i) { return Babylon::Char(i); }
  
    static int_type
    to_int_type(const char_type& c) { return(c.value()); }

    static bool
    eq_int_type(const int_type& i1, const int_type& i2) { return(i1 == i2); }

    // char_type comparison
    static bool
    eq(const char_type& c1, const char_type& c2) { return(c1 == c2); }

    static bool
    lt(const char_type& c1, const char_type& c2) { return(c1 < c2); }

    // operations on s[n] arrays
    static char_type*
    move(char_type* s, const char_type * s2, size_t n);

    static char_type*
    copy(char_type* s, const char_type * s2, size_t n);

    static char_type*
    assign(char_type* s, size_t n, char_type a);

    static int
    compare(const char_type * s, const char_type * s2, size_t n);

    static size_t length(const char_type * s);

    static const char_type *
    find(const char_type * s, size_t n, const char_type& c);

    // I/O related:
    typedef size_t pos_type;
    typedef size_t off_type;
    typedef mbstate_t state_type;

    static int_type eof() { return(Babylon::UC_NULL); }
    static int_type not_eof(const int_type &);
    static state_type get_state(pos_type p) {} // FIXME: What should go here?
};

}; // namespace std

#endif // __GNUC__ >= 3

#endif
