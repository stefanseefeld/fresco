/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Tobias Hunger <Tobias@berlin-consortium.org>
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

#include <Babylon/vis_iterator.hh>

Babylon::vis_iterator::vis_iterator(const Babylon::String::iterator start,
				    const Babylon::String::iterator end) : m_start(start),
									   m_end(end),
									   m_current(start) {
    std::basic_string<size_t> log2vis_str;
    std::basic_string<unsigned char> embed_levels;
    Babylon::log2vis(start, end, BASE_DIR_WL,
		     log2vis_str, m_vis2log_str, embed_levels, 0);
    m_vis_current = m_vis2log_str.begin();
    m_current = start;
}

Babylon::vis_iterator::vis_iterator(Babylon::String str) : m_start(str.begin()),
							   m_end(str.end()),
							   m_current(str.begin()) {
    cerr << "[Creating iterator";
    std::basic_string<size_t> log2vis_str;
    std::basic_string<unsigned char> embed_levels;
    cerr << ".";
    Babylon::log2vis(m_start, m_end, BASE_DIR_WL,
		     log2vis_str, m_vis2log_str, embed_levels, 0); 
    cerr << ".";
    m_vis_current = m_vis2log_str.begin();
    cerr << "]";
}
    
Babylon::vis_iterator::reference_type
Babylon::vis_iterator::operator * () const {
    return *m_current;
}

Babylon::vis_iterator::reference_type
Babylon::vis_iterator::operator -> () const {
    return *m_current;
}

Babylon::vis_iterator
Babylon::vis_iterator::operator + (Babylon::vis_iterator::Dist d) {
    m_vis_current += d;
    m_current = m_start + *m_vis_current;
    return *this;
}

Babylon::vis_iterator::reference_type
Babylon::vis_iterator::operator [] (Babylon::vis_iterator::Dist d) const {
    return *(m_start + m_vis_current[d]);
}

Babylon::vis_iterator &
Babylon::vis_iterator::operator ++ () {
    ++m_vis_current;
    if (m_vis_current == m_vis2log_str.end()) m_current = m_end;
    else m_current = m_start + *m_vis_current;
    return *this;
}

Babylon::vis_iterator
Babylon::vis_iterator::operator ++ (int) {
    Babylon::vis_iterator tmp(*this);
    ++*this;
    return tmp;
}

Babylon::vis_iterator &
Babylon::vis_iterator::operator -- () {
    --m_vis_current;
    m_current = m_start + *m_vis_current;
    return *this;
}

Babylon::vis_iterator
Babylon::vis_iterator::operator -- (int) {
    Babylon::vis_iterator tmp(*this);
    --*this;
    return tmp;
}

Babylon::vis_iterator &
Babylon::vis_iterator::operator = (const Babylon::String::iterator & i) {
    m_vis_current[distance(m_start, i)];
    if (m_vis_current == m_vis2log_str.end()) m_current == m_end;
    else m_current = m_start + *(m_vis_current);
    return *this;
}
