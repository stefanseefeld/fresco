/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#include <Fresco/config.hh>
#include <Fresco/Traversal.hh>
#include <Fresco/Transform.hh>
#include "Deck.hh"
#include "LayoutManager.hh"

using namespace Fresco;

using namespace Berlin::LayoutKit;

Deck::Deck() : my_requested(false) { }
Deck::~Deck() { }

void Deck::request(Fresco::Graphic::Requisition &r)
{
    if (!my_requested)
    {
	GraphicImpl::init_requisition(my_requisition);
	long n = my_children.size();
	if (n > 0)
	{
	    Fresco::Graphic::Requisition *r = children_requests();
	    LayoutAlign x(xaxis);
	    x.request(n, r, my_requisition);
	    LayoutAlign y(yaxis);
	    y.request(n, r, my_requisition);
	    my_pool.deallocate(r);
	}
	my_requested = true;
    }
    r = my_requisition;
}

void Deck::extension(const Allocation::Info &a, Region_ptr r)
{
    if (size_t n = my_children.size())
	my_children[n - 1].peer->extension(a, r);
}

void Deck::traverse(Traversal_ptr t)
{
    size_t n = my_children.size ();
    if (n == 0) return;
    try
    {
	t->traverse_child(my_children [n-1].peer,
			  my_children [n-1].localId, Region::_nil(),
			  Transform::_nil());
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { my_children[n-1].peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { my_children[n-1].peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::TRANSIENT &)
    { my_children[n-1].peer = Fresco::Graphic::_nil(); }
}
