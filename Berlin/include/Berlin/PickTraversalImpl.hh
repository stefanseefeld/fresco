/*$Id$
 *
 * This source file is a part of the Berlin Project.
 *
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 *
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
#ifndef _PickTraversalImpl_hh
#define _PickTraversalImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Traversal.hh>
#include <Warsaw/Event.hh>
#include <Warsaw/Graphic.hh>
#include <Berlin/TraversalImpl.hh>
#include <Berlin/RegionImpl.hh>

/* this is a traversal which is responsible for distributing events to
   graphics.  as such, speed is somewhat important. We set everything for
   "full throttle" */

class PickTraversalImpl : implements(PickTraversal), public TraversalImpl
{
 public:
    PickTraversalImpl(const CORBA::Any &e, Region_ptr r);
    PickTraversalImpl(const PickTraversalImpl &t);
    ~PickTraversalImpl();
    
    inline void visit(Graphic_ptr g) { g->pick(this->_this()); }
    inline order direction() { return down;} 
    inline CORBA::Boolean ok() { return true;}
    inline CORBA::Boolean intersects() {  
	RegionImpl region(stack.back().allocation, transformation());
	 Event::Pointer ptrEv;
	if (myEvent >>= &ptrEv) 
	    return region.contains(ptrEv.location);
	else 
	    return true;
    }
    inline CORBA::Any *event() {return &myEvent;}

 private:
    const CORBA::Any myEvent;
};

#endif /* _PickTraversalImpl_hh */
