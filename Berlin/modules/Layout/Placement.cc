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
#include <Berlin/TraversalImpl.hh>
#include <Berlin/Provider.hh>
#include <Berlin/ImplVar.hh>
#include "Layout/Placement.hh"
#include "Layout/LayoutManager.hh"
#include <strstream>

using namespace Warsaw;
using namespace Prague;

Placement::Placement(LayoutManager *l)
  : _layout(l),
    _region(new RegionImpl())
{
  std::ostrstream buf;
  buf << "Placement" << _layout->name() << std::ends;
  _name = strdup(buf.str());
}

Placement::~Placement()
{
  delete _layout;
}

void Placement::request(Warsaw::Graphic::Requisition::Requisition &r)
{
  MonoGraphic::request(r);
  _layout->request(0, 0, r);
}

void Placement::traverse(Traversal_ptr traversal)
{
  Trace trace(this, "Placement::traverse");
  Region_var allocation = traversal->current_allocation();
  if (!CORBA::is_nil(allocation))
    {
      Warsaw::Graphic::Requisition r;
      GraphicImpl::init_requisition(r);
      MonoGraphic::request(r);
      Graphic_var child = body();
      if (CORBA::is_nil(child)) return;
      Lease_var<RegionImpl> result(Provider<RegionImpl>::provide());
      result->copy(allocation);
      RegionImpl *tmp = static_cast<RegionImpl *>(result);
      _layout->allocate(1, &r, allocation, &tmp);
      Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
      tx->load_identity();
      result->normalize(Transform_var(tx->_this()));
      try { traversal->traverse_child (child, 0, Region_var(result->_this()), Transform_var(tx->_this()));}
      catch (const CORBA::OBJECT_NOT_EXIST &) { body (Warsaw::Graphic::_nil());}
      catch (const CORBA::COMM_FAILURE &) { body(Warsaw::Graphic::_nil());}
    }
  else MonoGraphic::traverse(traversal);
}

void Placement::allocate(Tag, const Allocation::Info &a)
{
  Trace trace(this, "Placement::allocate");
  _region->copy(a.allocation);
  Warsaw::Graphic::Requisition r;
  GraphicImpl::init_requisition(r);
  MonoGraphic::request(r);
  RegionImpl *cast = _region;
  _layout->allocate(1, &r, a.allocation, &cast);
  Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
  tx->load_identity();
  _region->normalize(Transform_var(tx->_this()));
  a.transformation->premultiply(Transform_var(tx->_this()));
  a.allocation->copy(Region_var(_region->_this()));
}

LayoutLayer::LayoutLayer(Graphic_ptr between, Graphic_ptr under, Graphic_ptr over)
  : _under(Warsaw::Graphic::_duplicate(under)),
    _over(Warsaw::Graphic::_duplicate(over))
{
  body(between);
}

LayoutLayer::~LayoutLayer()
{
}

void LayoutLayer::traverse(Traversal_ptr t)
{
  if (!CORBA::is_nil(_under))
    try { _under->traverse(t);}
    catch (const CORBA::OBJECT_NOT_EXIST &) { _under = Warsaw::Graphic::_nil();}
    catch (const CORBA::COMM_FAILURE &) { _under = Warsaw::Graphic::_nil();}
  MonoGraphic::traverse(t);
  if (!CORBA::is_nil(_over))
    try { _over->traverse(t);}
    catch (const CORBA::OBJECT_NOT_EXIST &) { _over = Warsaw::Graphic::_nil();}
    catch (const CORBA::COMM_FAILURE &) { _over = Warsaw::Graphic::_nil();}
}
