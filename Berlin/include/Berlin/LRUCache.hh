/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Berlin_LRUCache_hh
#define _Berlin_LRUCache_hh

#include <map>
#include <list>

namespace Berlin
{

  /* this is an ultra-simple LRU cache. it requires that your key objects
   * are comparable by <, that your value objects are lightweight enough
   * to be handled by value, you have a factory object for your value type
   * which has 2 methods: produce (which takes a single parameter of key
   * type and copies into it) and recycle (which takes a single parameter
   * of value type and frees its storage), and you do synchronizaiton
   * externally.
   *
   * On the other hand, it's very simple to use.
   */

  template 
  <class kT, class vT, class factoryT, class cacheT = std::map<kT,vT> > 
  class LRUCache
  {
    private:
      unsigned int my_max;
      cacheT my_cache;
      std::list<kT> my_queue;
      factoryT my_factory;

    public:
      LRUCache(factoryT fact, unsigned int i = 256) :
	  my_max(i), my_factory(fact)
      { }

      void get(const kT &k, vT &v) throw () 
      {
	  typename cacheT::iterator iter = my_cache.find(k);
	  if (iter != my_cache.end())
	  {
	      v = iter->second;
	      return;
	  }
	  else
	  {
	      v = my_factory.produce(k);
	      my_cache.insert(std::pair<kT,vT>(k,v));
	      my_queue.push_front(k);
	      if (my_queue.size() >= my_max)
	      {
		  kT victim = my_queue.back();
		  my_factory.recycle(my_cache[victim]);
		  my_cache.erase(victim);
		  my_queue.pop_back();
	      }
	  }
      }
  };

} // namespace

#endif
