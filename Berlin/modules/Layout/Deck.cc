/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include "Layout/Deck.hh"
#include "Layout/LayoutManager.hh"
#include <Warsaw/Traversal.hh>
#include <Warsaw/Transform.hh>

using namespace Warsaw;

Deck::Deck() : requested(false) {}
Deck::~Deck() {}

void Deck::request(Warsaw::Graphic::Requisition &r)
{
  if (!requested)
    {
      GraphicImpl::initRequisition(requisition);
      long n = children.size();
      if (n > 0)
	{
	  Warsaw::Graphic::Requisition *r = childrenRequests();
	  LayoutAlign x(xaxis);
	  x.request(n, r, requisition);
	  LayoutAlign y(yaxis);
	  y.request(n, r, requisition);
	  pool.deallocate(r);
	}
      requested = true;
    }
  r = requisition;
}

void Deck::extension(const Allocation::Info &a, Region_ptr r)
{
  if (size_t n = children.size()) children[n - 1].peer->extension(a, r);
}

void Deck::traverse(Traversal_ptr t)
{
  if (size_t n = children.size()) t->traverseChild(children[n - 1].peer, children[n - 1].localId, Region::_nil(), Transform::_nil());
}
