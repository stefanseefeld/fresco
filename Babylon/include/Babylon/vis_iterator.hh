/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2001 Tobias Hunger <Tobias@berlin-consortium.org>
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

/*
 * This file contains iterators that traverse a String
 * in visual order.
 */

#ifndef _Babylon_vis_iterator_hh
#define _Babylon_vis_iterator_hh

#include <Babylon/defs.hh>
#include <Babylon/utils.hh>
#include <Babylon/String.hh>
#include <iterator>

namespace Babylon {

class vis_iterator : public iterator_traits<Babylon::String::iterator> {
    typedef Babylon::Char reference_type;
    typedef int Dist;
public:
    vis_iterator(const Babylon::String::iterator,
		 const Babylon::String::iterator);
    vis_iterator(Babylon::String);

    friend bool operator == (const vis_iterator & a,
			 const vis_iterator & b) {
	return a.m_current == b.m_current;
    }

    friend bool operator == (const vis_iterator & a,
			 const Babylon::String::iterator & b) {
	return a.m_current == b;
    }

    friend bool operator == (const Babylon::String::iterator & b,
			 const vis_iterator & a) {
	return a.m_current == b;
    }

    friend bool operator != (const vis_iterator & a,
			 const vis_iterator & b) {
	return a.m_current != b.m_current;
    }

    friend bool operator != (const vis_iterator & a,
			 const Babylon::String::iterator & b) {
	return a.m_current != b;
    }

    friend bool operator != (const Babylon::String::iterator & b,
			 const vis_iterator & a) {
	return a.m_current != b;
    }

    vis_iterator & operator = (const Babylon::String::iterator &);
    reference_type operator * () const;
    reference_type operator -> () const;
    vis_iterator operator + (Dist d);
    reference_type operator [] (Dist d) const;
    vis_iterator& operator++ ();
    vis_iterator operator++ (int);
    vis_iterator& operator-- ();
    vis_iterator operator-- (int);
private:
    std::basic_string<size_t> m_vis2log_str;
    Babylon::String::iterator m_current;
    Babylon::String::iterator m_start;
    Babylon::String::iterator m_end;
    std::basic_string<size_t>::iterator m_vis_current;
};

}; // namespace Babylon

#endif // _Babylon_vis_iterator_hh
