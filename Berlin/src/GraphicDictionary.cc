/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2003 Tobias Hunger <tobias@fresco.org> 
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

#include <Berlin/GraphicDictionary.hh>
#include <Berlin/Logger.hh>

#include <limits>

// ----------------------------------------------------------------------
// static variables:
// ----------------------------------------------------------------------

Berlin::GraphicDictionary * Berlin::GraphicDictionary::my_self;
Prague::Mutex Berlin::GraphicDictionary::my_singleton_mutex;


// ----------------------------------------------------------------------
// Helper classes
// ----------------------------------------------------------------------

Berlin::GraphicDictionary::word_equal::word_equal(const Fresco::Graphic_ptr g,
                       const GraphicImpl * i) :
    my_hash(g->_hash(std::numeric_limits<unsigned int>::max())),
    my_impl(i),
    my_graphic(g)
{ }
bool
Berlin::GraphicDictionary::word_equal::operator() (const Berlin::GraphicDictionary::word & w)
{
    if (CORBA::is_nil(my_graphic))
    if (my_impl == w.impl) return true;
    else return false;
        
    if ((w.hash == my_hash) &&
    ((my_impl != 0 && my_impl == w.impl) ||
     (my_impl == 0 && my_graphic->is_identical(w.graphic))))
    return true;
    return false;
    
}


// ----------------------------------------------------------------------
// GraphicDictionary
// ----------------------------------------------------------------------

Berlin::GraphicDictionary::word::word() :
    name(),
    graphic(Fresco::Graphic::_nil()),
    impl(0),
    hash(0)
{ }

Berlin::GraphicDictionary::word::word(const Fresco::Graphic_ptr g,
                      const GraphicImpl * const p,
                      const std::string & n) :
    name(n),
    graphic(Fresco::Graphic::_duplicate(g)),
    impl(const_cast<GraphicImpl *>(p)),
    hash(g->_hash(std::numeric_limits<unsigned int>::max()))
{ }

Berlin::GraphicDictionary::word::word(const word & w) :
    name(w.name),
    graphic(Fresco::Graphic::_duplicate(w.graphic)),
    impl(w.impl),
    hash(w.hash)
{ }

Berlin::GraphicDictionary::word &
Berlin::GraphicDictionary::word::operator = (const word & w)
{
    name = w.name;
    graphic = Fresco::Graphic::_duplicate(w.graphic);
    impl = w.impl;
    hash = w.hash;
}


Berlin::GraphicDictionary::GraphicDictionary() :
    my_dictionary(),
    my_active(false)
{ }


Berlin::GraphicDictionary::~GraphicDictionary() { }

void Berlin::GraphicDictionary::activate()
{
    my_active = true;
}

Berlin::GraphicDictionary * Berlin::GraphicDictionary::instance() {
    // Create GraphicDictionary just once
    Prague::Guard<Prague::Mutex> guard(my_singleton_mutex);
    if (!my_self) my_self = new GraphicDictionary;
    return my_self;
} // instance


void Berlin::GraphicDictionary::add(const Fresco::Graphic_ptr g,
                    const GraphicImpl * const p,
                    const std::string & n)
{
    if (!p) return;

    Prague::Guard<Prague::Mutex> guard(my_mutex);

    // Is the Graphic already known?
    dictionary_type::iterator i(find_if(my_dictionary.begin(),
                    my_dictionary.end(),
                    word_equal(g, p)));
    word w(g, p, n);
    if (my_dictionary.end() == i && my_active)
    {
    // register new graphic
    my_dictionary.push_back(w);
    i = my_dictionary.end() - 1; // works, we just added one element.
    }

    Logger::log(Logger::lifecycle)
    << "GraphicDictionary: \"" << w.name
    << "\" (#" << w.hash
    << ") registered." << std::endl;

    return;
}


void Berlin::GraphicDictionary::remove(const GraphicImpl * const p)
{
    Prague::Guard<Prague::Mutex> guard(my_mutex);

    dictionary_type::iterator i(find_if(my_dictionary.begin(),
                    my_dictionary.end(),
                    word_equal(Fresco::Graphic::_nil(), p)));
    if (my_dictionary.end() != i)
    {
    Logger::log(Logger::lifecycle)
        << "GraphicDictionary: \"" << i->name
        << "\" (#" << i->hash
        << ") removed." << std::endl;
    my_dictionary.erase(i);
    }
    else
    Logger::log(Logger::lifecycle)
        << "GraphicDictionary: unknown graphic removed." << std::endl;
    return;
}



std::string
Berlin::GraphicDictionary::name(const Fresco::Graphic_ptr g) const
{
    std::string result("unknown");

    Prague::Guard<Prague::Mutex> guard(my_mutex);
    dictionary_type::const_iterator i(find_if(my_dictionary.begin(),
                          my_dictionary.end(),
                          word_equal(g, 0)));
    if (my_dictionary.end() != i)
    result = i->name;

    return result;
}

const Berlin::GraphicImpl * const
Berlin::GraphicDictionary::implementation(const Fresco::Graphic_ptr g) const
{
    Prague::Guard<Prague::Mutex> guard(my_mutex);
    dictionary_type::const_iterator i(find_if(my_dictionary.begin(),
                          my_dictionary.end(),
                          word_equal(g, 0)));
    if (my_dictionary.end() != i)
    return i->impl;
    else
    return 0;
}
