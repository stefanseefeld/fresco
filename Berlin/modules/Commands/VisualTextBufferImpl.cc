/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2001 Tobias Hunger <tobias@fresco.org> 
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

#include <Babylon/utils.hh>
#include <Fresco/Unicode.hh>
#include <Berlin/ObserverImpl.hh>
#include "VisualTextBufferImpl.hh"
#include "TextBufferImpl.hh"
#include <iostream>
#include <functional>
#include <algorithm>

/* ***************************** *
 * Glue class
 * ***************************** */

class VisualTextBufferImpl::Observer : public ObserverImpl {
public:
    Observer(VisualTextBufferImpl *);
    ~Observer() {}
    void update(const CORBA::Any &);
private:
    VisualTextBufferImpl * _visual;
};

VisualTextBufferImpl::Observer::Observer(VisualTextBufferImpl * v) {
    Prague::Trace trace("VisualTextBuffer::Observer::Observer(..)");
    _visual = v;
}

void VisualTextBufferImpl::Observer::update(const CORBA::Any & any) {
    Prague::Trace trace("VisualTextBufferImpl::Observer::update(...)");
    Fresco::TextBuffer::Change * ch;
    if(any >>= ch) {
        _visual->update(ch->type, ch->pos, ch->len);
	
    }
}


/* ***************************** *
 * VisualTextBufferImpl
 * ***************************** */

VisualTextBufferImpl::VisualTextBufferImpl(TextBufferImpl * memory) :
    _memory(memory),
    _vis2log(),
    _observer(new Observer(this)) {
    Prague::Trace trace("VisualTextBufferImpl::VisualTextBufferImpl(...)");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    // set our observer up to observe the memory buffer.
    _memory->attach(_observer->_this());

    Babylon::String mem_order(Unicode::to_internal(*_memory->value()));
    _paragraphs = mem_order.get_paragraphs();
    _vis2log = Babylon::get_vis2log(0, _paragraphs);
}

VisualTextBufferImpl::~VisualTextBufferImpl() {
    Prague::Trace trace("VisualTextBufferImpl::~VisualTextBufferImpl()");
    _memory->detach(_observer->_this());
}

CORBA::ULong VisualTextBufferImpl::size() {
    Prague::Trace trace("VisualTextBufferImpl::size()");
    return _memory->size();
}

Fresco::Unistring * VisualTextBufferImpl::value() {
    Prague::Trace trace("VisualTextBufferImpl::value()");
    Fresco::Unistring * result = new Fresco::Unistring();
    for (size_t i = 0; i < size(); ++i)
        result[i] = (*_memory->get_chars(i, 1))[0];
    return result;
}

Fresco::Unistring * VisualTextBufferImpl::get_chars(CORBA::ULong pos,
                                                    CORBA::ULong len) {
    Prague::Trace trace("VisualTextBufferImpl::get_chars(...)"); 
    Prague::Guard<Prague::Mutex> guard(_mutex);

    CORBA::ULong start = std::min(pos, size());
    CORBA::ULong end = std::min(pos + len, size());
    Fresco::Unistring * result = new Fresco::Unistring();
    result->length(end - start);

    for (size_t i = start; i < end; ++i)
        (*result)[i - start] = (*_memory->get_chars(_vis2log[i], 1))[0];

    return result;
}

CORBA::ULong VisualTextBufferImpl::position() {
    Prague::Trace trace("VisualTextBufferImpl::position()");
    Prague::Guard<Prague::Mutex> guard(_mutex);
    return current_position();
}

void VisualTextBufferImpl::position(CORBA::ULong pos) {
    Prague::Trace trace("VisualTextBufferImpl::position(...)");
    CORBA::ULong new_pos;
    {
        Prague::Guard<Prague::Mutex> guard(_mutex);
	new_pos = std::min(pos, size());
        new_pos = _vis2log[pos];
    }
    _memory->position(new_pos);
}

void VisualTextBufferImpl::forward() {
    Prague::Trace trace("VisualTextBufferImpl::forward()");
    CORBA::ULong new_pos;
    {
        Prague::Guard<Prague::Mutex> guard(_mutex);
        new_pos = current_position();
        new_pos = std::min(new_pos + 1, size());
    }
    _memory->position(_vis2log[new_pos - 1] + 1);
}

void VisualTextBufferImpl::backward() {
    Prague::Trace trace("VisualTextBufferImpl::backward()");
    CORBA::ULong new_pos;
    {
        Prague::Guard<Prague::Mutex> guard(_mutex);
        new_pos = current_position();
	if (new_pos > 1)
	    new_pos = std::max(CORBA::ULong(_vis2log[new_pos - 2]) + 1,
				CORBA::ULong(0));
	else
	new_pos = 0;
    }
    _memory->position(new_pos);
}

void VisualTextBufferImpl::shift(CORBA::Long d) {
    Prague::Trace trace("VisualTextBufferImpl::shift(...)");
    _memory->shift(d);
}

void VisualTextBufferImpl::insert_char(Fresco::Unichar c) {
    // FIXME: This needs some elaboration.
    Prague::Trace trace("VisualTextBufferImpl::insert_char(...)");
    _memory->insert_char(c);
}

void VisualTextBufferImpl::insert_string(const Fresco::Unistring & s) {
    // FIXME: Same here.
    Prague::Trace trace("VisualTextBufferImpl::insert_string(...)");
    _memory->insert_string(s);
} 

void VisualTextBufferImpl::remove_backward(CORBA::ULong len) {
    // FIXME: and here...
    Prague::Trace trace("VisualTextBufferImpl::remove_backward(...)");
    _memory->remove_backward(len);
}

void VisualTextBufferImpl::remove_forward(CORBA::ULong len) {
    // FIXME: and here again.
    Prague::Trace trace("VisualTextBufferImpl::remove_forward(...)");
    _memory->remove_forward(len);
}

void VisualTextBufferImpl::clear() {
    Prague::Trace trace("VisualTextBufferImpl::clear()");
    _memory->clear();
}

void VisualTextBufferImpl::update(const Fresco::TextBuffer::ChangeType type,
                                  const CORBA::ULong pos,
                                  const CORBA::Long len) {
    Prague::Trace trace("VisualTextBufferImpl::update(...)");
    std::vector<Fresco::TextBuffer::Change> anys;

    switch (type) {
    case Fresco::TextBuffer::insert:
        anys = insert(pos, len);
        break;
    case Fresco::TextBuffer::remove:
        anys = remove(pos, len);
        break;
    case Fresco::TextBuffer::cursor:
        anys = cursor(pos, len);
        break;
    }

    // send all the updates that came up:
    // ---------------------------------------------------------
    for (std::vector<Fresco::TextBuffer::Change>::const_iterator i = anys.begin();
         i != anys.end();
         ++i) {
        CORBA::Any any;
        any <<= *i;
        notify(any);
    }
}

Fresco::TextBuffer::StringOrder VisualTextBufferImpl::order() {
    Prague::Trace trace("VisualTextBufferImpl::order()");
    return Fresco::TextBuffer::visual_order;
}

Fresco::TextBuffer_ptr VisualTextBufferImpl::get_memory_buffer() {
    Prague::Trace trace("VisualTextBufferImpl::get_memory_buffer()");
    return _memory->_this();
}

Fresco::TextBuffer_ptr VisualTextBufferImpl::get_visual_buffer() {
    Prague::Trace trace("VisualTextBufferImpl::get_visual_buffer()");
    return TextBuffer::_this();
}

CORBA::ULong VisualTextBufferImpl::current_position() {
    // Gets only called in a locked environment! No mutex needed.

    if(_vis2log.empty())
        return CORBA::ULong(0);
    CORBA::ULong pos = _memory->position();

    if (pos == 0) return CORBA::ULong(0);

    // assert we got a sane value:
    assert(pos <= size());

    return _vis2log[pos - 1] + 1;
}

std::vector<Fresco::TextBuffer::Change>
VisualTextBufferImpl::insert(const CORBA::ULong pos,
                             const CORBA::Long len) {
    Prague::Trace trace("VisualTextBufferImpl::insert(...)");

    CORBA::ULong vis_size(_vis2log.size());

    // 0) make sure our input is valid.
    // ---------------------------------------------------------
    assert(len > 0);
    assert(pos >= 0);
    assert(pos <= vis_size);

    std::vector<Fresco::TextBuffer::Change> anys;
    CORBA::ULong end = pos + len;
    {
        Prague::Guard<Prague::Mutex> guard(_mutex);

	// 1) find paragraph we are inserting into
	// ---------------------------------------------------------
	Babylon::Paragraphs::iterator first_par;
	if(_paragraphs.empty())
	    first_par = _paragraphs.end();
	else {
	    Babylon::Paragraph search(pos, pos);
	    first_par = std::lower_bound(_paragraphs.begin(), _paragraphs.end(),
					 search, Babylon::Paragraph_lt());
	}
        Babylon::Paragraphs::iterator last_par;

	// we now have a iterator into the paragraphs which might be
	// _paragraphs.end()!

        // 2) Insert at the end of string?
	// ---------------------------------------------------------
	//    we might need to append a paragraph then...
	int modifier = 0; // this is either 0 or -1.
	                  // set to -1 to create a paragraph of length 0
	if(first_par == _paragraphs.end()) {
	    // We examine the last paragraph: Either it ends in a
	    // paragraph separator (then we need to append a new paragraph
	    // and insert there) or not (then we'll append to the last
	    // used paragraph).
	    if(_paragraphs.empty() ||
	       (_vis2log.size() > 1 &&
	       Babylon::UCS2((*_memory->get_chars(_vis2log[vis_size - 1], 1))[0]) ==
	       Babylon::UCS2(Babylon::UC_PARAGRAPH_SEPARATOR))) {
		// We have text and that ends in a Paragraph separator,
		Babylon::Paragraph tmp(vis_size, vis_size);
		first_par = _paragraphs.insert(_paragraphs.end(), tmp);
		modifier = -1;
	    } else
		--first_par; // OK, we checked above.
	}
	last_par = first_par + 1; // to be consistent with *.end()

	// we now have first_par (which is an iterator to an existing paragraph
	// and last_par which is one psst first_par.

	// 3) examine string and check it for paragraph separators
	// ---------------------------------------------------------
	size_t patch_begin = first_par->begin;
	size_t patch_end = first_par->end + len + modifier;

        Babylon::String ins_str(Unicode::to_internal(
	    *_memory->get_chars(patch_begin, patch_end - patch_begin + 1)));
        std::vector<size_t> separators = ins_str.get_Paragraph_Separators();

        // 4) Insert additional paragraphs if there are paragraph
	//    separators
	// ---------------------------------------------------------
	if (separators.empty() ||
	    (separators.size() == 1 &&
	     separators[0] == patch_end - patch_begin)) {
	    // just some chars inserted into the middle of the paragraph:
	    // add len chars to the affected paragraph
	    first_par->end += len + modifier;

	    first_par->levels =	Babylon::analyse(ins_str.begin(),
						 ins_str.end());
	} else {
	    // insert new paragraphs:

	    // store in case first_par becomes invalid:
	    size_t first_par_pos = std::distance(_paragraphs.begin(), first_par);

	    // update first paragraph...
	    std::vector<size_t>::const_iterator i = separators.begin();
	    first_par->end = first_par->begin + *i;
	    first_par->levels = Babylon::analyse(ins_str.begin(),
						 ins_str.begin() +
						 first_par->end);
	    // go on:
	    ++i;
	    Babylon::Paragraph new_para;
	    for (;
		 i != separators.end();
		 ++i) {
		new_para.begin = patch_begin + *i;
		if (i+1 != separators.end())
		    new_para.end = patch_begin + *(i + 1);
		else
		    new_para.end = patch_end;
		new_para.levels =
		    Babylon::analyse(ins_str.begin() + new_para.begin,
				     ins_str.begin() + new_para.end);
		last_par =
		    _paragraphs.insert(last_par, new_para);
	    }
	    // reset first_par as it might have become invalid.
	    first_par = _paragraphs.begin();
	    std::advance(first_par, first_par_pos);
	    ++last_par; // to make it bahave more like *.end()
	}

	// 5) insert len 'spaces' into _vis2log after start
	// ---------------------------------------------------------
	_vis2log.insert(_vis2log.begin() + pos,
			size_t(len),
			size_t(0));

	// 6) calculate vis2log-patch:
	// ---------------------------------------------------------
	Babylon::Char_Mapping vis2log_patch(Babylon::get_vis2log(patch_begin,
								 first_par,
								 last_par));

	// 7) add len to start and end of all paragraphs after those
	//    affected (move them len chars to the right).
	// ---------------------------------------------------------
	for(Babylon::Paragraphs::iterator i = last_par;
	    i != _paragraphs.end();
	    ++i) {
	    i->begin += len;
	    i->end += len;
	}

	// 8) replace the spaces inserted earlier and old values with
	//    vis2log_patch:
	// ---------------------------------------------------------
	std::copy(vis2log_patch.begin(), vis2log_patch.end(),
		  _vis2log.begin() + patch_begin);

	// 9) move all positions in vis2log after the end of the last affected
	//    paragraph len letters to the right:
	// ---------------------------------------------------------
	if(last_par != _paragraphs.end())
	    std::for_each(_vis2log.begin() + last_par->begin,
			  _vis2log.end(),
			  std::bind2nd(std::plus<size_t>(), len));

	// 10) calculate new anys to send:
	// ---------------------------------------------------------

	// get positions of those elements inserted:
	std::vector<size_t> ins_elem;
	for(Babylon::Char_Mapping::const_iterator i = vis2log_patch.begin();
	    i != vis2log_patch.end();
	    ++i) {
	    if (*i >= pos && *i <= pos + len)
		ins_elem.push_back(i - vis2log_patch.begin() +
				   patch_begin);
	}
	std::sort(ins_elem.begin(), ins_elem.end());
	
	std::vector<size_t>::const_iterator i = ins_elem.begin();
	size_t start(*i);
	size_t last(*i);
	++i; // This is OK since we asserted that len is != 0.

	Fresco::TextBuffer::Change current;
	current.visual = 1;
	current.type = Fresco::TextBuffer::insert;
	for(; i != ins_elem.end(); ++i)
	    if (*i != last + 1) {
		current.pos = start;
		current.len = last - start;
		anys.push_back(current);
		start = last = *i;
	    } else
		++last;
	current.pos = start;
	current.len = last - start + 1;
	anys.push_back(current);
    }

    return anys;
}



std::vector<Fresco::TextBuffer::Change>
VisualTextBufferImpl::remove(const CORBA::ULong pos,
			     const CORBA::Long len) {
    Prague::Trace trace("VisualTextBufferImpl::remove(...)");

    // 0) make sure our input is valid:
    // ---------------------------------------------------------
    assert(pos + len >= 0);
    assert(pos + len <= _vis2log.size());

    std::vector<Fresco::TextBuffer::Change> anys;
    if(_paragraphs.empty())
	return anys; // nothing to remove!
 
    CORBA::ULong start;
    CORBA::ULong end;
    
    if (len < 0) {
	start = std::max(CORBA::ULong(0), pos + len);
	end = std::min(CORBA::ULong(_vis2log.size()) - 1, pos - 1);
    } else {
	start = std::min(CORBA::ULong(0), pos - 1);
	end = std::max(CORBA::ULong(_vis2log.size()) - 1, pos + len - 2);
    }

    const CORBA::ULong length(end - start + 1);
    {
	Prague::Guard<Prague::Mutex> guard(_mutex);

	// 1) find first and last affected paragraph:
	// ---------------------------------------------------------
	Babylon::Paragraphs::iterator first_par;
	Babylon::Paragraphs::iterator last_par;
	{
	    Babylon::Paragraph search(start, start);
	    first_par = std::lower_bound(_paragraphs.begin(), _paragraphs.end(),
					 search, Babylon::Paragraph_lt());
	    search.begin = end; search.end = end;
	    last_par = std::lower_bound(_paragraphs.begin(), _paragraphs.end(),
					search, Babylon::Paragraph_lt());
	    // both should be != _paragraphs.end() because of the assertions!
	}
	size_t patch_begin = first_par->begin;
	size_t patch_end = last_par->end;

	// 2) calculate new anys to send:
	// ---------------------------------------------------------
	std::vector<size_t> rem_elem;
	{
	    for(Babylon::Char_Mapping::const_iterator i =
		    _vis2log.begin() + patch_begin ;
		i != _vis2log.end() + patch_end + 1;
		++i)
		if (*i >= start && *i <= end)
		    rem_elem.push_back(i - _vis2log.begin());
	    std::sort(rem_elem.begin(), rem_elem.end());

	    std::vector<size_t>::const_iterator i = rem_elem.begin();
	    size_t first_char = *i;
	    size_t last_char = *i;
	    ++i; // This is OK since we asserted that len is != 0.

	    Fresco::TextBuffer::Change current;
	    current.visual = 1;
	    current.type = Fresco::TextBuffer::remove;
	    for (; i != rem_elem.end(); ++i)
		if (*i != last_char + 1) {
		    if (len > 0) {
			current.pos = first_char;
			current.len = last_char - first_char + 1;
		    } else {
			current.pos = last_char + 1;
			current.len = first_char - last_char - 1;
		    }
		    anys.push_back(current);
		    first_char = last_char = *i;
		} else
		    ++last_char;

	    current.pos = first_char;
	    if(len > 0) {
		current.pos = first_char;
		current.len = last_char - first_char + 1;
	    } else {
		current.pos = last_char + 1;
		current.len = first_char - last_char - 1;
	    }

	    anys.push_back(current);
	}

	// 3) 'extend' the first paragraph to include all characters
	//    in all touched paragraphs minus those removed:
	// ---------------------------------------------------------
	if (last_par != _paragraphs.end())
	    first_par->end = last_par->end - length;
	else first_par->end = first_par->end - length;
	
	// 4) remove the other touched paragraphs:
	// ---------------------------------------------------------
	if (first_par != last_par)
	    _paragraphs.erase(first_par + 1, last_par);
       
	// reset last_par to match the new _paragraphs:
	last_par = first_par + 1;

	// 5) get all chars now in the only affected paragraph left:
	// ---------------------------------------------------------
	if (first_par->begin > first_par->end)
	    // paragraph is now empty and must be removed.
	    last_par = _paragraphs.erase(first_par);
	else {
	    Babylon::String
		first_par_str(Unicode::to_internal(*_memory->
						   get_chars(first_par->begin,
							     first_par->end -
							     first_par->begin + 1)));
	    first_par->levels = Babylon::analyse(first_par_str.begin(),
						 first_par_str.end());
	}

	// 6) move all paragraphs after those affected len chars to
	//    the left.
	// ---------------------------------------------------------
	for(Babylon::Paragraphs::iterator i = last_par;
	    i != _paragraphs.end();
	    ++i) {
	    i->begin -= length;
	    i->end += length;
	}

	// 7) remove len chars from _vis2log
	// ---------------------------------------------------------
	_vis2log.erase(patch_begin, length);

	// 8) move all chars in _vis2log after the affected paragraph
	//    length chars to the left:
	// ---------------------------------------------------------
	if(last_par != _paragraphs.end())
	    std::for_each(_vis2log.begin() + last_par->begin,
			  _vis2log.end(),
			  std::bind2nd(std::minus<size_t>(), length));

	// 9) calculate a patch for vis2log and insert it into
	//     _vis2log
	// ---------------------------------------------------------
	Babylon::Char_Mapping vis2log_patch = 
	    Babylon::get_vis2log(first_par->begin, first_par->levels);

	std::copy(vis2log_patch.begin(), vis2log_patch.end(),
		  _vis2log.begin() + patch_begin);

    }

    return anys;
}




std::vector<Fresco::TextBuffer::Change>
VisualTextBufferImpl::cursor(const CORBA::ULong pos,
			     const CORBA::Long len) {
    Prague::Trace trace("VisualTextBufferImpl::cursor(...)");

    // 0) make sure our input is valid:
    // ---------------------------------------------------------
    assert(pos >= 0);
    assert(pos <= size());

    // 1) calculate anys to send:
    // ---------------------------------------------------------
    
    // there will be exactly one.
    std::vector<Fresco::TextBuffer::Change> anys;

    Fresco::TextBuffer::Change current;
    current.visual = 1;
    current.type = Fresco::TextBuffer::cursor;
    current.len = 0;
    {
	Prague::Guard<Prague::Mutex> guard(_mutex);
	current.pos = current_position();
    }
    anys.push_back(current);

    return anys;
}
