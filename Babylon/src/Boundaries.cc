/*$Id$
 *
 * This source file is a part of the Berlin Project.
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

#include <Babylon/internal/Boundaries.hh>
#include <Babylon/Char.hh>

bool
Babylon::is_graphem_cluster_boundary(const Babylon::Char & f,
				     const Babylon::Char & s)
{
    // Break after Start_Of_Text and before End_Of_Text
    if (UC_START_OF_TEXT == f.value() ||
	UC_END_OF_TEXT == s.value()) return 1;
    // Don't break between CR and LF
    if (UC_CARRIAGE_RETURN == f.value() &&
	UC_LINE_FEED == s.value()) return 0;
    // Break before/after (Control | CR | LF)
    if (f.is_Control() ||
	s.is_Control()) return 1;
    // Do not break Hangul syllable sequences.
    if ((f.is_hangul_L() && (s.is_hangul_L() || s.is_hangul_V() ||
			     s.is_hangul_LV() || s.is_hangul_LVT())) ||
	((f.is_hangul_LV() || f.is_hangul_V()) && (s.is_hangul_V() ||
						   s.is_hangul_T())) ||
	((f.is_hangul_LVT() || f.is_hangul_T()) && s.is_hangul_T()))
	return 0;
    // Don't break before extending characters.
    if (s.is_Grapheme_Extend()) return 0;
    // Otherwise break everywhere.
    return 1;
}

bool Babylon::is_word_boundary(const Babylon::Char & f,
		      const Babylon::Char & s)
{
    if (UC_START_OF_TEXT == f.value() ||
	UC_END_OF_TEXT == s.value()) return 1;
    return 0;
}

bool Babylon::is_sentense_boundary(const Babylon::Char & f,
				   const Babylon::Char & s)
{
    if (UC_START_OF_TEXT == f.value() ||
	UC_END_OF_TEXT == s.value()) return 1;
    return 0;
}
