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

Berlin::PrimitiveKit::TransformPrimitive::TransformPrimitive() :
    //my_mode(Figure::outline),
    my_tx(new TransformImpl),
    my_ext(new RegionImpl)
{ }

Berlin::PrimitiveKit::TransformPrimitive::~TransformPrimitive() { }

Transform_ptr Berlin::PrimitiveKit::TransformPrimitive::transformation()
{ return my_tx->_this(); }
void Berlin::PrimitiveKit::TransformPrimitive::request(Fresco::Graphic::Requisition &r)
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
        GraphicImpl::require_lead_trail(r.x, x_lead, x_lead, x_lead,
                                        x_trail, x_trail, x_trail);
        GraphicImpl::require_lead_trail(r.y, y_lead, y_lead, y_lead,
                                        y_trail, y_trail, y_trail);
        GraphicImpl::require_lead_trail(r.z, z_lead, z_lead, z_lead,
                                        z_trail, z_trail, z_trail);
    }
    else
    {
        r.x.defined = false;
        r.y.defined = false;
        r.z.defined = false;
    }
}

void Berlin::PrimitiveKit::TransformPrimitive::extension(const Allocation::Info &info,
                                                         Region_ptr region)
{
    Trace trace("TransformPrimitive::extension");
    if (my_ext->valid)
    {
        Lease_var<RegionImpl> tmp(Provider<RegionImpl>::provide());
        tmp->copy(Region_var(my_ext->_this()));
        tmp->xalign = tmp->yalign = tmp->zalign = 0.;
        Lease_var<TransformImpl>
        transformation(Provider<TransformImpl>::provide());
        if (!CORBA::is_nil(info.transformation))
            transformation->copy(info.transformation);
        transformation->premultiply(Transform_var(my_tx->_this()));
        tmp->apply_transform(Transform_var(transformation->_this()));
        region->merge_union(Region_var(tmp->_this()));
    }
}

void Berlin::PrimitiveKit::TransformPrimitive::pick(PickTraversal_ptr traversal)
{
    if (my_ext->valid &&
    traversal->intersects_region(Region_var(my_ext->_this())))
    traversal->hit();
}

void Berlin::PrimitiveKit::TransformPrimitive::need_redraw()
{
    Trace trace("TransformPrimitive::need_redraw");
    Allocation::Info info;
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    extension(info, Region_var(region->_this()));
    need_redraw_region(Region_var(region->_this()));
}

void Berlin::PrimitiveKit::TransformPrimitive::resize() { }
void Berlin::PrimitiveKit::TransformPrimitive::copy(const TransformPrimitive &tp)
{
    // my_mode = tp.my_mode;
    // my_fg = tp.my_fg;
    // my_bg = tp.my_bg;
    my_tx->copy(Transform_var(tp.my_tx->_this()));
    if (tp.my_ext->valid) my_ext->copy(Region_var(tp.my_ext->_this()));
}

Berlin::PrimitiveKit::PrimitiveImpl::PrimitiveImpl() :
    my_mesh(new Fresco::Mesh())
{ }
Berlin::PrimitiveKit::PrimitiveImpl::~PrimitiveImpl() { }

void Berlin::PrimitiveKit::PrimitiveImpl::draw(DrawTraversal_ptr traversal)
{
    Trace trace("PrimitiveImpl::draw");
    if (my_mesh->nodes.length() > 0)
    {
        // bounding box culling, use extension(...) to add brush effect
    // into extension.
        Allocation::Info info;
        Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
        extension(info, Region_var(region->_this()));
        if (traversal->intersects_region(Region_var(region->_this())))
        {
            DrawingKit_var drawing = traversal->drawing();
            DrawingKit3D_var d3d = DrawingKit3D::_narrow(drawing);
            if (CORBA::is_nil(d3d))
            {
                if (my_error == false)
                    std::cerr << "No DrawingKit3D interface found."
                  << std::endl
                              << "Consider passing \"-d GLDrawingKit\" to "
                  << "Berlin."
                              << std::endl;
                my_error = true;
                return;
            }
            d3d->save();
            d3d->draw_mesh(my_mesh);
            d3d->restore();
        }
    }
}

// Picking just does a bounding box test for now.
void Berlin::PrimitiveKit::PrimitiveImpl::pick(PickTraversal_ptr traversal)
{
    TransformPrimitive::pick(traversal);
    return;
    if (my_ext->valid)
    {
        if (traversal->intersects_region(Region_var(my_ext->_this())))
        { }
        traversal->hit();
    }
}

// Reset the primitive's list of vertices
void Berlin::PrimitiveKit::PrimitiveImpl::resize()
{
    my_ext->valid = false;
    if (my_mesh->nodes.length() > 0)
    {
        my_ext->valid = true;
        my_ext->lower = my_mesh->nodes[0];
        my_ext->upper = my_mesh->nodes[0];
        CORBA::ULong n = my_mesh->nodes.length();
        for (CORBA::ULong i = 1; i < n; ++i)
        {
            my_ext->lower.x = Math::min(my_ext->lower.x,
                    my_mesh->nodes[i].x);
            my_ext->upper.x = Math::max(my_ext->upper.x,
                    my_mesh->nodes[i].x);
            my_ext->lower.y = Math::min(my_ext->lower.y,
                    my_mesh->nodes[i].y);
            my_ext->upper.y = Math::max(my_ext->upper.y,
                    my_mesh->nodes[i].y);
            my_ext->lower.z = Math::min(my_ext->lower.z,
                    my_mesh->nodes[i].z);
            my_ext->upper.z = Math::max(my_ext->upper.z,
                    my_mesh->nodes[i].z);
        }
    }
}

void Berlin::PrimitiveKit::PrimitiveImpl::reset()
{ my_ext->valid = false; }

void Berlin::PrimitiveKit::PrimitiveImpl::copy(const PrimitiveImpl &p)
{
    TransformPrimitive::copy(p);
    my_mesh = new Fresco::Mesh(p.my_mesh);
}
