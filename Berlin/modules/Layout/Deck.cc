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

Deck::Deck() : _requested(false) {}
Deck::~Deck() {}

void Deck::request(Fresco::Graphic::Requisition &r)
{
  if (!_requested)
    {
      GraphicImpl::init_requisition(_requisition);
      long n = _children.size();
      if (n > 0)
	{
	  Fresco::Graphic::Requisition *r = children_requests();
	  LayoutAlign x(xaxis);
	  x.request(n, r, _requisition);
	  LayoutAlign y(yaxis);
	  y.request(n, r, _requisition);
	  _pool.deallocate(r);
	}
      _requested = true;
    }
  r = _requisition;
}

void Deck::extension(const Allocation::Info &a, Region_ptr r)
{
  if (size_t n = _children.size()) _children[n - 1].peer->extension(a, r);
}

void Deck::traverse(Traversal_ptr t)
{
  size_t n = _children.size ();
  if (n == 0) return;
  try { t->traverse_child (_children [n-1].peer, _children [n-1].localId, Region::_nil(), Transform::_nil());}
  catch (const CORBA::OBJECT_NOT_EXIST &) { _children [n-1].peer = Fresco::Graphic::_nil();}
  catch (const CORBA::COMM_FAILURE &) { _children [n-1].peer = Fresco::Graphic::_nil();}
}
