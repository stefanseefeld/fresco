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
									   m_end(end) {
    Babylon::Embedding_Levels emb = Babylon::analyse(start, end, BASE_DIR_WL);
    m_vis2log = Babylon::get_vis2log(0, emb);
    m_vis_current = m_vis2log.begin();
    m_current = start + (*m_vis_current);
}

Babylon::vis_iterator
Babylon::vis_iterator::operator + (Babylon::vis_iterator::Dist d) {
    m_vis_current += d;
    m_current = m_start + *m_vis_current;
    return *this;
}

Babylon::vis_iterator &
Babylon::vis_iterator::operator ++ () {
    ++m_vis_current;
    if (m_vis_current == m_vis2log.end()) m_current = m_end;
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
    m_vis_current = std::find(m_vis2log.begin(),
			      m_vis2log.end(),
			      distance(m_start, i));
    if (m_vis_current == m_vis2log.end()) m_current == m_end;
    else m_current = m_start + *(m_vis_current);
    return *this;
}
