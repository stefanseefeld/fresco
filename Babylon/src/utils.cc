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

#include <Babylon/utils.hh>
#include <functional>
#include <algorithm>
#include <stack>

namespace Babylon {

bool Babylon::is_graphem_boundary(Babylon::Char a, Babylon::Char b) {
    // FIXME!
    return 0;
} // isGraphemBoundary(...)  

// The following code is a copy of fribidi 0.9.0 published under LGPL
// by Behdad Esfahbod and Dov Grobgeld.
//
// I didn't use the original since I don't want Berlin to depend of GLib.

std::vector<Babylon::Type>
run_length_encode_types(std::vector<Babylon::Bidir_Props> char_type) {
    std::vector<Babylon::Type> result;
    // Sweep over the string_types
    Babylon::Type current;
    current.start = 0;
    current.length = 1;
    current.bidir_type = char_type[0];

    for(size_t i = 1; i < char_type.size(); i++) {
	if(char_type[i] == current.bidir_type)
	    current.length++;
	else {
	    result.push_back(current);
	    current.start = i;
	    current.length = 1;
	    current.bidir_type = char_type[i];
	}
    }
    result.push_back(current);

    return(result);
}

inline bool bidir_is_strong(const Babylon::Bidir_Props & p) {
    return (p & Babylon::BIDIR_MASK_STRONG);
}

inline bool bidir_is_neutral(const Babylon::Bidir_Props & p) {
    return (p & Babylon::BIDIR_MASK_NEUTRAL);
}

inline bool bidir_is_explicit_or_bn(const Babylon::Bidir_Props & p) {
    return (p & (BIDIR_MASK_EXPLICIT | BIDIR_MASK_SEPARATOR |
		 BIDIR_MASK_BN | BIDIR_MASK_WS));
}

inline bool bidir_is_letter(const Babylon::Bidir_Props & p) {
    return (p & Babylon::BIDIR_MASK_LETTER);
}

inline bool bidir_is_number(const Babylon::Bidir_Props & p) {
    return (p & Babylon::BIDIR_MASK_NUMBER);
}

inline bool bidir_is_override(const Babylon::Bidir_Props & p) {
    return (p & Babylon::BIDIR_MASK_OVERRIDE);
}

inline bool bidir_is_ES_or_CS(const Babylon::Bidir_Props & p) {
    return (p & (Babylon::BIDIR_MASK_ES | Babylon::BIDIR_MASK_CS));
}

inline bool bidir_is_separator(const Babylon::Bidir_Props & p) {
    return (p & Babylon::BIDIR_MASK_SEPARATOR);
}

inline bool
bidir_is_explicit_or_separator_or_BN_or_WS(const Babylon::Bidir_Props & p) {
    return (p & (Babylon::BIDIR_MASK_EXPLICIT |
		 Babylon::BIDIR_MASK_SEPARATOR |
		 Babylon::BIDIR_MASK_BN |
		 Babylon::BIDIR_MASK_WS));
}

inline bool
bidir_is_number_separator_or_terminator(const Babylon::Bidir_Props & p) {
    return (p & Babylon::BIDIR_MASK_NUMSEPTER);
}

inline bool bidir_is_PDF(const Babylon::Bidir_Props & p) {
    return (p == BIDIR_PDF);
}

inline unsigned char bidir_to_level(const Babylon::Bidir_Props&  p) {
    return (p & 1);
}

inline Babylon::Bidir_Props level_to_bidir(const unsigned char lev) {
    return Babylon::Bidir_Props(Babylon::BIDIR_L | (lev & 1));
}

inline Babylon::Bidir_Props
bidir_explicit_to_override_dir(const Babylon::Bidir_Props & p) {
    return (bidir_is_override(p) ?
	    level_to_bidir(bidir_to_level(p)) : 
	    BIDIR_ON);
}

inline bool compact (const Babylon::Type & a, const Babylon::Type &b) {
    return (a.bidir_type == b.bidir_type && a.embed_level == b.embed_level);
}

inline bool compact_neutrals(const Babylon::Type & a,
			     const Babylon::Type & b) {
    return (a.embed_level == b.embed_level &&
	    (a.bidir_type == b.bidir_type ||
	     bidir_is_neutral(a.bidir_type) && bidir_is_neutral(b.bidir_type)));
}

inline Babylon::Bidir_Props change_number_to_rtl(Babylon::Bidir_Props p) {
    return (bidir_is_number(p) ? Babylon::BIDIR_R : p);
}


std::vector<Babylon::Type>::iterator
compact(const std::vector<Babylon::Type>::iterator & start,
	const std::vector<Babylon::Type>::iterator & end) {
    if (start == end) return end;

    std::vector<Babylon::Type>::iterator last_used = start;
    std::vector<Babylon::Type>::iterator current = start;
    ++current;

    while(current != end) {
	if(last_used->embed_level == current->embed_level &&
	   last_used->bidir_type == current->bidir_type)
	    last_used->length += current->length;
	else {
	    ++last_used;
	    std::iter_swap(last_used, current);
	}
	++current;
    }

    return ++last_used;
}

std::vector<Babylon::Type>::iterator
compact_neutrals(const std::vector<Babylon::Type>::iterator & start,
		 const std::vector<Babylon::Type>::iterator & end) {
    if (start == end) return end;

    std::vector<Babylon::Type>::iterator last_used = start;
    std::vector<Babylon::Type>::iterator current = start;
    ++current;

    while(current != end) {
	if(last_used->embed_level == current->embed_level &&
	   (last_used->bidir_type == current->bidir_type ||
	    bidir_is_neutral(last_used->bidir_type) &&
	    bidir_is_neutral(current->bidir_type)))
	    last_used->length += current->length;
	else {
	    ++last_used;
	    std::iter_swap(last_used, current);
	}
	++current;
    }

    return ++last_used;
}

vector<Babylon::Type> override(vector<Babylon::Type> & base,
			       const vector<Babylon::Type> & over) {
    
    if (base.empty()) return over;

    if (over.empty()) return base;

    vector<Babylon::Type>::const_iterator over_it = over.begin();
    vector<Babylon::Type>::iterator base_it = base.begin();

    vector<Babylon::Type> result;

    while(!(over_it == over.end() && base_it == base.end())) {
	if (over_it == over.end()) {
	    // copy base
	    std::copy(base_it, base.end(),
		      std::back_inserter(result));
	    base_it = base.end();
	} else if (base_it == base.end()) {
	    // copy over
	    std::copy(over_it, over.end(),
		      std::back_inserter(result));
	    base_it = base.end();
	} else {
	    // mix...
	    if (over_it->length == 0 ||
		over_it->start < 0) {
		++over_it;
		continue;
	    }

	    if (base_it->length == 0 ||
		base_it->start < 0) {
		++base_it;
		continue;
	    }

	    Babylon::Type current = *base_it;
	    size_t max_current = current.start + current.length - 1;
	    if (current.start < over_it->start) {
		current.length = over_it->start - current.start;
		result.push_back(current);
		result.push_back(*over_it);
		++over_it;
	    } else {
		result.push_back(*over_it);
		++over_it;
	    }
	    base_it->start = over_it->start + over_it->length + 1;
	    base_it->length = max_current - base_it->start;
	}
    }

    return result;
}

Embedding_Levels
Babylon::analyse(const Babylon::String::const_iterator start,
		 const Babylon::String::const_iterator end,
		 const Babylon::Base_Dir & pbase_dir) {
    Embedding_Levels emb;
    if (start == end) return emb;

    size_t str_length(distance(start, end) -  1);

    std::vector<Babylon::Type> type_rl;
    std::vector<Babylon::Bidir_Props> char_type(str_length);
    {
	// Determinate character types
	transform(start, end,
		  char_type.begin(),
		  std::mem_fun_ref(& Babylon::Char::direction));
	
	// Run length encode the character types
	type_rl = run_length_encode_types(char_type);
    }

    unsigned char base_level = 0;
    Babylon::Bidir_Props base_dir = Babylon::BIDIR_ON;
    if(bidir_is_strong(Babylon::Bidir_Props(pbase_dir)))
	base_level = bidir_to_level(Babylon::Bidir_Props(pbase_dir));
    else {
	// P2. P3. Search for first strong character and use its
	// direction as base direction
	base_level = 0; // default
	for(std::vector<Babylon::Type>::const_iterator i = type_rl.begin();
	    i != type_rl.end();
	    ++i)
	    if(bidir_is_letter(i->bidir_type)) {
		base_level = bidir_to_level(i->bidir_type);
		base_dir = level_to_bidir(base_level);
		break;
	    }
	// If no strong base_dir was found, resort to the weak direction
	// that was passed on input.
	if (bidir_is_neutral(base_dir))
	    base_level = bidir_to_level(Babylon::Bidir_Props(pbase_dir));
    }
    base_dir = level_to_bidir(base_level);

    // Explicit Levels and Directions
    std::vector<Babylon::Type> explicits;
    {
	// X1. Begin by setting the current embeding level to the paragraph
	// embedding level. Set the directional override status to neutral.
	// Process each character iteratively, applying rules X2 through X9.
	// Only embedding levels from 0 to 61 are valid in this phase.
	unsigned char level(base_level);
	Babylon::Bidir_Props override(Babylon::BIDIR_ON);
	std::stack<std::pair<unsigned char, Babylon::Bidir_Props> > stack;
	size_t over_pushed = 0;
	size_t first_interval = 0;

	for(std::vector<Babylon::Type>::iterator i = type_rl.begin();
	    i != type_rl.end();
	    ++i) {
	    Babylon::Bidir_Props this_type = i->bidir_type;
	    if (bidir_is_explicit_or_bn(this_type)) {
		if (bidir_is_strong(this_type)) { // LRE, RLE, LRO, RLO
		    // 1. Explicit Embeddings 
		    //   X2. With each RLE, compute the least greater odd
		    //       embedding level.
		    //   X3. With each LRE, compute the least greater even
		    //       embedding level.
		    // 2. Explicit Overrides
		    //   X4. With each RLO, compute the least greater odd
		    //       embedding level.
		    //   X5. With each LRO, compute the least greater even
		    //       embedding level.
		    Babylon::Bidir_Props new_override =
			bidir_explicit_to_override_dir(this_type);
		    
		    for(size_t j = 0; j < i->length; j++) {
			unsigned char new_level =
			    ((level + bidir_to_level(this_type) + 2) & ~1) -
			    bidir_to_level(this_type);
			// PUSH_STATUS:
			if(new_level <= MAX_BIDIR_LEVEL) {
			    stack.push(std::make_pair(level, override));

			    level = new_level;
			    override = new_override;

			    if(level == MAX_BIDIR_LEVEL - 1)
				first_interval = over_pushed;
			} else over_pushed++;
		    }
		} else if(bidir_is_PDF(this_type)) {
		    // 3. Terminating Embeddings and Overrides
		    //   X7. With each PDF, determine the matching embedding
		    //       or override code.
		    for(size_t j = 0; j <= i->length; j++) {
			// POP_STATUS:
			if(over_pushed || !stack.empty()) {
			    if (over_pushed > first_interval) over_pushed--;
			    else {
				if(over_pushed == first_interval)
				    first_interval = 0;
				std::pair<unsigned char, Babylon::Bidir_Props>
				    tmp(stack.top());
				level = tmp.first;
				override = tmp.second;
				stack.pop();
			    }
			}
		    }
		} // else if(bidir_is_PDF(...))
		// X9. Remove all RLE, LRE, RLO, LRO, PDF and BN codes.
		// Remove element and add to explicits_list:
		i->embed_level = Babylon::LEVEL_REMOVED;
		explicits.push_back(*i);
		type_rl.erase(i);
	    } else {
		// X6.  For all typed besides RLE, LRE, RLO, LRO, and PDF:
		//      a. Set the level of the current character to the current
		//         embedding level.
		//      b. Whenever the directional override status is not neutral,
                //         reset the current character type to the directional
		//         override status.
		i->embed_level = level;
		if(!bidir_is_neutral(override))
		    i->bidir_type = override;
	    }
	    /* X8. All explicit directional embeddings and overrides are
	       completely terminated at the end of each paragraph. Paragraph
	       separators are not included in the embedding. */
	    /* This function is running on a single paragraph, so we can do
	       X8 after all the input is processed. */
	} // for(i...)
	
	// Implementing X8. It has no effect on a single paragraph!
	level = base_level;
	override = Babylon::BIDIR_ON;
    }

     /* X10. The remaining rules are applied to each run of characters at the
	same level. For each run, determine the start-of-level-run (sor) and
	end-of-level-run (eor) type, either L or R. This depends on the
	higher of the two levels on either side of the boundary (at the start
	or end of the paragraph, the level of the 'other' run is the base
	embedding level). If the higher level is odd, the type is R, otherwise
	it is L. */
    /* Resolving Implicit Levels can be done out of X10 loop, so only change
       of Resolving Weak Types and Resolving Neutral Types is needed. */

    type_rl.erase(compact(type_rl.begin(), type_rl.end()),
		  type_rl.end());

    // 4. Resolving weak types
    {
	std::vector<Babylon::Type>::iterator i = type_rl.begin();
	Babylon::Bidir_Props last_strong(base_dir);
	Babylon::Bidir_Props prev_type(Babylon::BIDIR_INVALID);
	Babylon::Bidir_Props this_type(i->bidir_type);
	Babylon::Bidir_Props next_type;
	if ((i+1) != type_rl.end())
	    next_type = (i+1)->bidir_type;
	else
	    next_type = Babylon::BIDIR_INVALID;

	for( ; i != type_rl.end(); ++i) {
	    // get next_type:
	    if ((i+1) != type_rl.end())
		next_type = (i+1)->bidir_type;
	    else
		next_type = Babylon::BIDIR_INVALID;
	    
	    if(bidir_is_strong(prev_type))
		last_strong = prev_type;

	    // W1: NSM
	    // Examine each non-spacing mark (NSM) in the level run, and change the
	    // type of the NSM to the type of the previous character. If the NSM
	    // is at the start of the level run, it will get the type of sor. */
	    if(this_type == Babylon::BIDIR_NSM)
		i->bidir_type = prev_type;

	    // W2: European numbers
	    else if(this_type == Babylon::BIDIR_EN &&
	       last_strong == Babylon::BIDIR_AL) {
		i->bidir_type = Babylon::BIDIR_AN;
		// Resolving dependency of loops for rules W1 and W2, so we
		// can merge them in one loop.
		if(next_type == Babylon::BIDIR_NSM)
		    (i+1)->bidir_type = Babylon::BIDIR_AN;
	    }
	    
	    prev_type = this_type;
	    this_type = next_type;
	} // for(i...)
	
	last_strong = base_dir;
	// Resolving dependency of loops for rules W4 and W5, W5 may
	// want to prevent W4 to take effect in the next turn, do this
	// through "w4".
	bool w4 = 1;

	// Resolving dependency of loops for rules W4 and W5 with W7,
	// W7 may change an EN to L but it sets the prev_type_org if needed,
	// so W4 and W5 in next turn can still do their works.
	Babylon::Bidir_Props prev_type_org(Babylon::BIDIR_ON);
	i = type_rl.begin();
	prev_type = i->bidir_type;
	++i;
	if(i != type_rl.end())
	    this_type = i->bidir_type;
	else
	    this_type = Babylon::BIDIR_INVALID;

	for( ; i != type_rl.end(); ++i) {
	    if ((i+1) != type_rl.end())
		next_type = (i+1)->bidir_type;
	    else
		next_type = Babylon::BIDIR_INVALID; 

	    if(bidir_is_strong(prev_type))
		last_strong = prev_type;

	    // W3: Change ALs to R
	    if(this_type == Babylon::BIDIR_AL) {
		i->bidir_type = Babylon::BIDIR_R;
		w4 = 1;
		prev_type_org = Babylon::BIDIR_ON;
	    } else {
		// W4. A single european separator changes to a european number.
		//     A single common separator between two numbers of the same
		//     type changes to that type.
		if(w4 &&
		   i->length == 1 &&
		   bidir_is_ES_or_CS(this_type) &&
		   bidir_is_number(prev_type_org) &&
		   prev_type_org == next_type &&
		   (prev_type_org == Babylon::BIDIR_EN ||
		    this_type == Babylon::BIDIR_CS)) {
		    i->bidir_type = prev_type;
		    this_type = prev_type;
		}
		w4 = 1;
		
		// W5. A sequence of European terminators adjacent to European
		//     numbers changes to All European numbers.
		if(this_type == Babylon::BIDIR_ET &&
		   (prev_type_org == Babylon::BIDIR_EN ||
		    next_type == Babylon::BIDIR_EN)) {
		    i->bidir_type = Babylon::BIDIR_EN;
		    this_type = Babylon::BIDIR_EN;
		    w4 = 0;
		}
		
		// W6. Otherwise change separators and terminators to other
		//     neutral.
		if(bidir_is_number_separator_or_terminator(this_type))
		    i->bidir_type = Babylon::BIDIR_ON;

		// W7. Change european numbers to L.
		if (this_type == Babylon::BIDIR_EN &&
		    last_strong == Babylon::BIDIR_L) {
		    i->bidir_type = Babylon::BIDIR_L;
		    if ((i+1) != type_rl.end())
			prev_type_org = (i->embed_level == (i+1)->embed_level) ?
			    Babylon::BIDIR_EN :
			    Babylon::BIDIR_ON;
		} else 
		    prev_type_org = i->bidir_type;
	    }
	    prev_type = this_type;
	    this_type = next_type;
	} // for (i...)
    }

    type_rl.erase(compact_neutrals(type_rl.begin(), type_rl.end()),
		  type_rl.end());

    // 5. Resolving Neutral Types
    {
	// N1. and N2.
	// For each neutral, resolve it.
	std::vector<Babylon::Type>::iterator i = type_rl.begin();
	Babylon::Bidir_Props prev_type(Babylon::BIDIR_INVALID);
	Babylon::Bidir_Props this_type(i->bidir_type);
	Babylon::Bidir_Props next_type;
	if ((i+1) != type_rl.end())
	    next_type = (i+1)->bidir_type;
	else
	    next_type = Babylon::BIDIR_INVALID;	
	    
	for( ; i != type_rl.end(); ++i) {
	    // "European and arabic numbers are treated as though they were R"
	    if(bidir_is_neutral(this_type))
		i->bidir_type = (prev_type == next_type) ?
		    /* N1. */ prev_type :
		    /* N2. */ level_to_bidir(i->embed_level);
	    prev_type = this_type;
	    this_type = next_type;
	    if ((i+1) != type_rl.end())
		next_type = (i+1)->bidir_type;
	    else
		next_type = Babylon::BIDIR_INVALID;
	} // for(i...)
    }

    type_rl.erase(compact(type_rl.begin(), type_rl.end()),
		  type_rl.end());    

    // 6. Resolving implicit levels
    unsigned char max_level = base_level;
    for(std::vector<Babylon::Type>::iterator i = type_rl.begin();
	    i != type_rl.end();
	    ++i) {
	Babylon::Bidir_Props this_type = i->bidir_type;
	unsigned char level = i->embed_level;

	/* I1. Even */
	/* I2. Odd */
	if(bidir_is_number(this_type))
	    i->embed_level = (i->embed_level + 2) & ~1;
	else
	    i->embed_level = (i->embed_level ^ bidir_to_level(this_type)) +
		(i->embed_level & 1);

	if (i->embed_level > max_level)
	    max_level = i->embed_level;
    }

    type_rl.erase(compact(type_rl.begin(), type_rl.end()),
		  type_rl.end());

    // Reinsert the explicit codes & bn's that were removed, from the
    // explicits to type_rl_list.
    type_rl = override(type_rl, explicits);
    vector<Babylon::Type>::iterator i = type_rl.begin();
    if (i->embed_level < 0)
	i->embed_level = base_level;
    for ( ; i != type_rl.end();	++i)
	if (i->embed_level < 0)
	    i->embed_level = (i-1)->embed_level;

    // L1. Reset the embedding levels.
    {
	vector<Babylon::Type> list;
	bool state = 1;
	size_t pos = str_length - 1;
	for(int i = str_length - 1; i >= 0; --i) {
	    Babylon::Bidir_Props k = char_type[i];
	    if (!state && bidir_is_separator(k)) {
		state = 1;
		pos = i;
	    } else {
		if (state
		    && !(i && bidir_is_explicit_or_separator_or_BN_or_WS(k))) {
		    // if state is on at the first of string, do this too.
		    if (!i)
			--i;
		    state = 0;
		    Babylon::Type tmp;
		    tmp.start = i + 1;
		    tmp.length = pos - i;
		    tmp.bidir_type = base_dir;
		    tmp.embed_level = base_level;
		    list.insert(list.begin(), tmp);
		}
	    }
	}
	type_rl = override(type_rl, list);
    }

    emb.types = type_rl;
    emb.max_level = max_level;

    return emb;
}

void log2vis(const Babylon::String::const_iterator start,
	     const Babylon::String::const_iterator end,
	     const Babylon::Base_Dir & pbase_dir,
	     std::basic_string<size_t> & log2vis_str,
	     std::basic_string<size_t> & vis2log_str,
	     std::basic_string<unsigned char> & embed_levels,
	     size_t start_offset = 0) {
    // Initialise result-strings:
    log2vis_str.erase();
    for(size_t i = 0; i <= std::distance(start, end); ++i)
	log2vis_str.push_back(i + start_offset);
    vis2log_str = log2vis_str;

    Babylon::Embedding_Levels emb = analyse(start, end, pbase_dir);
    
    embed_levels.erase();
    for(vector<Babylon::Type>::const_iterator i = emb.types.begin();
	i != emb.types.end();
	++i)
	for(size_t j = 0; j < i->length; ++j)
	    embed_levels.push_back(i->embed_level);

    // FIXME: This is missing:
    // L4. Mirror all characters that are in odd levels and have mirrors

    // L2. Reorder
    for(unsigned char level_idx = emb.max_level;
	level_idx > 0;
	--level_idx)
	for(std::vector<Babylon::Type>::const_iterator j = emb.types.begin();
	    j != emb.types.end();
	    ++j) {
	    if(j->embed_level >= level_idx) {
		size_t pos = j->start;
		size_t len = j->length;
		std::vector<Babylon::Type>::const_iterator k = j + 1;
		while(k != emb.types.end() && k->embed_level >= level_idx) {
		    len += k->length;
		    ++k;
		}
		std::reverse(vis2log_str.begin() + pos,
			     vis2log_str.begin() + pos +len);
	    }
	}

    // Convert vis2log_str into log2vis_str:
    for(size_t i = 0; i < std::distance(start, end) - 1; ++i)
	log2vis_str[vis2log_str[i] - start_offset] = i + start_offset;
}

} // namespace Babylon
