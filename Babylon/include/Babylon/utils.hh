/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999,2000,2001 Tobias Hunger <Tobias@berlin-consortium.org>
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

/* This file contains a lot of code ported over from libfribidi 0.9.0.
 * The latest version of fribidi can be found at
 *     http://fribidi.sourceforge.net/
 
 * Here is the Copyright notice of fribidi:

 * Fribidi is:
 * Copyright (C) 1999,2000 Dov Grobgeld, and
 * Copyright (C) 2001 Behdad Esfahbod.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library, in a file named COPYING.LIB; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * For licensing issues, contact <dov@imagic.weizmann.ac.il> and
 * <fwpg@sharif.edu>. 
 */

#ifndef _Babylon_utils_hh
#define _Babylon_utils_hh

#include <Babylon/defs.hh>
#include <Babylon/Char.hh>
#include <Babylon/String.hh>

namespace Babylon {

//. This takes a single paragraph for input!
//. Returns a vector of embedding levels and the max. embedding level used
Embedding_Levels analyse(const Babylon::String::const_iterator, //.< start of input string
			 const Babylon::String::const_iterator, //.< end of input string
			 const Babylon::Base_Dir &);

//. This function gets returns a string of embedding levels from
//. the runlength encoded list of levels in Embedding_Level.
std::basic_string<unsigned char>
get_embedding_levels(const Babylon::Embedding_Levels & emb);

//. Generates a mapping from the visual string of characters to the
//. logical string.
Babylon::Char_Mapping
get_vis2log(const size_t & start_offset,
	    const Babylon::Embedding_Levels & emb);

//. Generates a mapping from the logical string of characters to the
//. visual string.
Babylon::Char_Mapping
get_log2vis(const size_t & start_offset,
	    const Babylon::Char_Mapping & vis2log);

} // namespace Babylon

// OPERATORS:
inline std::ostream & operator << (std::ostream & out, Babylon::Char uc) { return out << uc.utf8();}
inline std::ostream & operator << (std::ostream & out, const Babylon::String & us) { return out << us.utf8();}

#endif // _Babylon_utils_hh
