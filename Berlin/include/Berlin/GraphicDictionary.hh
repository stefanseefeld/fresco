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

#ifndef _Berlin_GraphicDictionary_hh
#define _Berlin_GraphicDictionary_hh

#include <Prague/Sys/Thread.hh>

#include <Berlin/GraphicImpl.hh>

#include <Fresco/Graphic.hh>

#include <string>
#include <vector>

namespace Berlin
{
  typedef std::vector<std::string> name_vector;

  class GraphicDictionary
  {
    public:
      GraphicDictionary();
      ~GraphicDictionary();

      //. This member function causes the Dictionary to go active.
      //. It will simply forget all registered Graphics, thus
      //. conserving memory. You need to call this member on the dictionary
      //. *before* registering any Graphic ro avoid losing information.
      void activate();

      //. Finds the current dictionary.
      //. If no dictionary exists it will create one.
      static GraphicDictionary * instance();

      //. Register a new Graphic with the given name. This function
      //. returns the total number of times this Graphic was registered
      // (including this try).
      void add(const Fresco::Graphic_ptr, const GraphicImpl * const,
           const std::string &);
      //. Remove a Graphic from the Dictionary.
      //.
      //. Returns the number of times this Graphic used to be registered
      //. BEFORE this one is removed.
      void remove(const GraphicImpl * const);

      //. Query the Dictionary 
      std::string name(const Fresco::Graphic_ptr) const;
      //. Get the implementation of the CORBA Object.
      const GraphicImpl * const implementation(const Fresco::Graphic_ptr) const;
    private:
      // We will never assign/copy this object, so there is no need
      // to implement these:
      GraphicDictionary(const GraphicDictionary &);
      GraphicDictionary & operator = (const GraphicDictionary &);

      //. A dictionary contains words...
      struct word
      {
      std::string name;
      Fresco::Graphic_var graphic;
      unsigned int hash;
      GraphicImpl * impl;

      word();
      word(const Fresco::Graphic_ptr, const GraphicImpl * const,
           const std::string &);
      word(const word &);
      word & operator = (const word &);
      };

      class word_equal
      {
    public:
      word_equal(const Fresco::Graphic_ptr g,
             const GraphicImpl * i);
      bool operator() (const Berlin::GraphicDictionary::word & w);
    private:
      const unsigned int my_hash;
      const GraphicImpl * my_impl;
      const Fresco::Graphic_ptr my_graphic;
      };

      typedef std::vector<word> dictionary_type;
      dictionary_type my_dictionary;

      bool my_active;

      mutable Prague::Mutex my_mutex;
      static GraphicDictionary * my_self;
      static Prague::Mutex my_singleton_mutex;
  };

} // namespace

#endif
