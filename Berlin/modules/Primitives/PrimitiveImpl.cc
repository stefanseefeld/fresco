/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@fresco.org> 
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

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit3D.hh>
#include <Fresco/IO.hh>
#include <Berlin/Geometry.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Color.hh>
#include <Berlin/Vertex.hh>
#include <Berlin/Provider.hh>
#include "PrimitiveImpl.hh"

using namespace Geometry;
using namespace Prague;
using namespace Fresco;

TransformPrimitive::TransformPrimitive()
  : //_mode(Figure::outline),
    _tx(new TransformImpl),
    _ext(new RegionImpl)
{
}

TransformPrimitive::~TransformPrimitive() {}
Transform_ptr TransformPrimitive::transformation() { return _tx->_this();}
void TransformPrimitive::request(Fresco::Graphic::Requisition &r)
{
  Trace trace("TransformPrimitive::request");
  Allocation::Info info;
  Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
  extension(info, Region_var(region->_this()));
  if (region->valid)
    {
      Coord x_lead = -region->lower.x, x_trail = region->upper.x;
      Coord y_lead = -region->lower.y, y_trail = region->upper.y;
      Coord z_lead = -region->lower.z, z_trail = region->upper.z;
      GraphicImpl::require_lead_trail(r.x, x_lead, x_lead, x_lead, x_trail, x_trail, x_trail);
      GraphicImpl::require_lead_trail(r.y, y_lead, y_lead, y_lead, y_trail, y_trail, y_trail);
      GraphicImpl::require_lead_trail(r.z, z_lead, z_lead, z_lead, z_trail, z_trail, z_trail);
    }
  else
    {
      r.x.defined = false;
      r.y.defined = false;
      r.z.defined = false;
    }
}

void TransformPrimitive::extension(const Allocation::Info &info, Region_ptr region)
{
  Trace trace("TransformPrimitive::extension");
  if (_ext->valid)
    {
      Lease_var<RegionImpl> tmp(Provider<RegionImpl>::provide());
      tmp->copy(Region_var(_ext->_this()));
      tmp->xalign = tmp->yalign = tmp->zalign = 0.;
      Lease_var<TransformImpl> transformation(Provider<TransformImpl>::provide());
      if (!CORBA::is_nil(info.transformation)) transformation->copy(info.transformation);
      transformation->premultiply(Transform_var(_tx->_this()));
      tmp->apply_transform(Transform_var(transformation->_this()));
      region->merge_union(Region_var(tmp->_this()));
    }
}

void TransformPrimitive::pick(PickTraversal_ptr traversal)
{
  if (_ext->valid && traversal->intersects_region(Region_var(_ext->_this())))
    traversal->hit();
}

void TransformPrimitive::need_redraw()
{
  Trace trace("TransformPrimitive::need_redraw");
  Allocation::Info info;
  Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
  extension(info, Region_var(region->_this()));
  need_redraw_region(Region_var(region->_this()));
}

void TransformPrimitive::resize() {}
void TransformPrimitive::copy(const TransformPrimitive &tp)
{
  //  _mode = tp._mode;
  //  _fg = tp._fg;
  //  _bg = tp._bg;
  _tx->copy(Transform_var(tp._tx->_this()));
  if (tp._ext->valid) _ext->copy(Region_var(tp._ext->_this()));
}

PrimitiveImpl::PrimitiveImpl() : _mesh(new Fresco::Mesh()) {}
PrimitiveImpl::~PrimitiveImpl() {}

void PrimitiveImpl::draw(DrawTraversal_ptr traversal)
{
  Trace trace("PrimitiveImpl::draw");
  if (_mesh->nodes.length() > 0)
    {
      // bounding box culling, use extension(...) to add brush effect into extension.
      Allocation::Info info;
      Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
      extension(info, Region_var(region->_this()));
      if (traversal->intersects_region(Region_var(region->_this())))
	{
	  DrawingKit_var drawing = traversal->drawing();
	  DrawingKit3D_var d3d = DrawingKit3D::_narrow(drawing);
	  if (CORBA::is_nil(d3d)) {
	    if (_error == false)
	      std::cerr << "No DrawingKit3D interface found." << std::endl
			<< "Consider passing \"-d GLDrawingKit\" to Berlin."
			<< std::endl;
	    _error = true;
	    return;
	  }
	  d3d->save();
	  d3d->draw_mesh(_mesh);
	  d3d->restore();
	}
    }
}

/*
 * Picking just does a bounding box test for now.
 */

void PrimitiveImpl::pick(PickTraversal_ptr traversal)
{
  TransformPrimitive::pick(traversal);
  return;
  if (_ext->valid)
    {
      if (traversal->intersects_region(Region_var(_ext->_this())))
 	{
 	}
      traversal->hit();
    }
}

/*
 * Reset the primitive's list of vertices
 */

void PrimitiveImpl::resize()
{
  _ext->valid = false;
  if (_mesh->nodes.length() > 0)
    {
      _ext->valid = true;
      _ext->lower = _mesh->nodes[0];
      _ext->upper = _mesh->nodes[0];
      CORBA::ULong n = _mesh->nodes.length();
      for (CORBA::ULong i = 1; i < n; ++i)
 	{
 	  _ext->lower.x = Math::min(_ext->lower.x, _mesh->nodes[i].x);
 	  _ext->upper.x = Math::max(_ext->upper.x, _mesh->nodes[i].x);
 	  _ext->lower.y = Math::min(_ext->lower.y, _mesh->nodes[i].y);
 	  _ext->upper.y = Math::max(_ext->upper.y, _mesh->nodes[i].y);
 	  _ext->lower.z = Math::min(_ext->lower.z, _mesh->nodes[i].z);
 	  _ext->upper.z = Math::max(_ext->upper.z, _mesh->nodes[i].z);
	}
    }	
}

void PrimitiveImpl::reset()
{
  _ext->valid = false;
}

void PrimitiveImpl::copy(const PrimitiveImpl &p)
{
  TransformPrimitive::copy(p);
  _mesh = new Fresco::Mesh(p._mesh);
}
