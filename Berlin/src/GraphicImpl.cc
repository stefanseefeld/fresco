/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 1998 Graydon Hoare <graydon@fresco.org> 
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
#include <Fresco/config.hh>
#include <Fresco/Traversal.hh>
#include <Fresco/Screen.hh>
#include <Fresco/IO.hh>
#include <Berlin/Provider.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/AllocationImpl.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/Math.hh>
#include <Berlin/GraphicDictionary.hh>
#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Stopwatch.hh>
#include <algorithm>
#include <functional>

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

static double tol = 0.005;

static bool rotated (Transform_ptr t)
{
    Transform::Matrix m;
    t->store_matrix(m);
    return (!Math::equal(m[0][1], 0., tol) || !Math::equal(m[1][0], 0., tol));
}

static void set_span(RegionImpl &r, Axis a, Coord origin, Coord length)
{
    Coord begin = origin;
    Coord end = begin + length;
    r.valid = true;
    switch (a)
    {
    case xaxis:
    r.lower.x = begin;
    r.upper.x = end;
    break;
    case yaxis:
    r.lower.y = begin;
    r.upper.y = end;
    break;
    case zaxis:
    r.lower.z = begin;
    r.upper.z = end;
    break;
    }
}

static double compute_squeeze(const Graphic::Requirement &r, Coord length)
{
    if (length > r.natural && r.maximum > r.natural)
    return (length - r.natural) / (r.maximum - r.natural);
    else if (length < r.natural && r.minimum < r.natural)
    return (r.natural - length) / (r.natural - r.minimum);
    else
    return 0.;
}

// compare a requisition (total) with a given allocation (given) and then
// distribute it to the individual children (result) based on the individual
// requisitions (requests)
static void compute_allocations(Axis a, Graphic::Requisition &total,
                CORBA::ULong n,
                Graphic::Requisition *requests,
                RegionImpl &given,
                RegionImpl* result)
{
    Graphic::Requirement *r;
    Region::Allotment s;
    r = GraphicImpl::requirement(total, a);
    given.span(a, s);
    Coord length = s.end - s.begin;
    bool growing = length > r->natural;
    bool shrinking = length < r->natural;
    double f = compute_squeeze(*r, length);
    Coord p = 0.0;
    for (CORBA::ULong i = 0; i < n; i++)
    {
    r = GraphicImpl::requirement(requests[i], a);
    Coord cspan = r->natural;
    if (growing)
        cspan += Coord(f * (r->maximum - r->natural));
    else if (shrinking)
        cspan -= Coord(f * (r->natural - r->minimum));
    set_span(result[i], a, p, cspan);
    p += cspan;
    }
}

static void flexible_transform_request(Graphic::Requisition &req,
                       Transform_ptr t)
{
    Trace trace("flexible_transform_request");
    if (t->identity()) return;
    if (t->translation())
    {
    Transform::Matrix mat;
    t->store_matrix(mat);
    Coord tx = mat[0][3];
    Coord ty = mat[1][3];
    Coord tz = mat[2][3];
    
    req.x.align = (req.x.align * req.x.natural - tx) / req.x.natural;
    req.y.align = (req.y.align * req.y.natural - ty) / req.y.natural;
    req.z.align = (req.z.align * req.z.natural - tz) / req.z.natural;
    return;
    }
    
    if (!req.z.defined)
    {
    req.z.natural = req.z.maximum = req.z.minimum = 0.;
    req.z.align = 0;
    req.z.defined = true;
    }
    
    RegionImpl nat, maxi, mini;
    
    nat.xalign = req.x.align;
    nat.lower.x = -req.x.align * req.x.natural;
    nat.upper.x = nat.lower.x + req.x.natural;
    nat.yalign = req.y.align;
    nat.lower.y = -req.y.align * req.y.natural;
    nat.upper.y = nat.lower.y + req.y.natural;
    nat.zalign = req.z.align;
    nat.lower.z = -req.z.align * req.z.natural;
    nat.upper.z = nat.lower.z + req.z.natural;
    nat.valid = true;
    
    maxi.xalign = req.x.align;
    maxi.lower.x = -req.x.align * req.x.maximum;
    maxi.upper.x = maxi.lower.x + req.x.maximum;
    maxi.yalign = req.y.align;
    maxi.lower.y = -req.y.align * req.y.maximum;
    maxi.upper.y = maxi.lower.y + req.y.maximum;
    maxi.zalign = req.z.align;
    maxi.lower.z = -req.z.align * req.z.maximum;
    maxi.upper.z = maxi.lower.z + req.z.maximum;
    maxi.valid = true;
    
    mini.xalign = req.x.align;
    mini.lower.x = -req.x.align * req.x.minimum;
    mini.upper.x = mini.lower.x + req.x.minimum;
    mini.yalign = req.y.align;
    mini.lower.y = -req.y.align * req.y.minimum;
    mini.upper.y = mini.lower.y + req.y.minimum;
    mini.zalign = req.z.align;
    mini.lower.z = -req.z.align * req.z.minimum;
    mini.upper.z = mini.lower.z + req.z.minimum;
    mini.valid = true;
    
//    std::cout << "allocation before transform :\n\t" << nat << "\n\t"
//              << mini << "\n\t" << maxi << std::endl;
    nat.apply_transform(t);
    maxi.apply_transform(t);
    mini.apply_transform(t);
//    std::cout << "allocation after transform :\n\t" << nat << "\n\t"
//              << mini << "\n\t" << maxi << std::endl;

    req.x.defined = true;
    req.x.natural = nat.upper.x - nat.lower.x;
    req.x.maximum = maxi.upper.x - maxi.lower.x;
    req.x.minimum = mini.upper.x - mini.lower.x;
    if (!Math::equal(req.x.natural, 0.0, 1.0e-6))
    req.x.align = -nat.lower.x / req.x.natural;
    else
    req.x.align = 0.0;

    req.y.defined = true;
    req.y.natural = nat.upper.y - nat.lower.y;
    req.y.maximum = maxi.upper.y - maxi.lower.y;
    req.y.minimum = mini.upper.y - mini.lower.y;
    if (!Math::equal(req.y.natural, 0.0, 1.0e-6))
    req.y.align = -nat.lower.y / req.y.natural;
    else
    req.y.align = 0.0;
    
    req.z.defined = true;
    req.z.natural = nat.upper.z - nat.lower.z;
    req.z.maximum = maxi.upper.z - maxi.lower.z;
    req.z.minimum = mini.upper.z - mini.lower.z;
    if (!Math::equal(req.z.natural, 0.0, 1.0e-6))
    req.z.align = -nat.lower.z / req.z.natural;
    else
    req.z.align = 0.0;
}

static void fixed_transform_request(Graphic::Requisition &req,
                    Transform_ptr t)
{
    Trace trace("fixed_transform_request");
    if (t->identity()) return;
    if (t->translation())
    {
    Transform::Matrix mat;
    t->store_matrix(mat);
    Coord tx = mat[0][3];
    Coord ty = mat[1][3];
    Coord tz = mat[2][3];
    
    req.x.align = (req.x.align * req.x.natural - tx) / req.x.natural;
    req.y.align = (req.y.align * req.y.natural - ty) / req.y.natural;
    req.z.align = (req.z.align * req.z.natural - tz) / req.z.natural;
    return;
    }

    if (!req.z.defined)
    {
    req.z.natural = req.z.maximum = req.z.minimum = 0.;
    req.z.align = 0;
    req.z.defined = true;
    }

    RegionImpl nat;

    nat.xalign = req.x.align;
    nat.lower.x = -req.x.align * req.x.natural;
    nat.upper.x = nat.lower.x + req.x.natural;
    nat.yalign = req.y.align;
    nat.lower.y = -req.y.align * req.y.natural;
    nat.upper.y = nat.lower.y + req.y.natural;
    nat.zalign = req.z.align;
    nat.lower.z = -req.z.align * req.z.natural;
    nat.upper.z = nat.lower.z + req.z.natural;
    nat.valid = true;
//    std::cout << "allocation before transform :" << nat << std::endl;
    nat.apply_transform(t);
//    std::cout << "allocation after transform :" << nat << std::endl;
    Coord xlead = -nat.lower.x;
    Coord xtrail = nat.upper.x;
    
    Coord ylead = -nat.lower.y;
    Coord ytrail = nat.upper.y;
    
    Coord zlead = -nat.lower.z;
    Coord ztrail = nat.upper.z;
    
    GraphicImpl::require_lead_trail(req.x, xlead, xlead, xlead,
                    xtrail, xtrail, xtrail);
    GraphicImpl::require_lead_trail(req.y, ylead, ylead, ylead,
                    ytrail, ytrail, ytrail);
    GraphicImpl::require_lead_trail(req.z, zlead, zlead, zlead,
                    ztrail, ztrail, ztrail);
}

/*****************************************************/

GraphicImpl::GraphicImpl() { }
GraphicImpl::~GraphicImpl() { }

void GraphicImpl::deactivate()
{
    Trace trace(this, "GraphicImpl::deactivate");
    Prague::Guard<Mutex> guard(my_mutex);
    for (glist_t::iterator i = my_parents.begin(); i != my_parents.end(); ++i)
    {
    if (!CORBA::is_nil((*i).peer)) 
        try { (*i).peer->remove_child_graphic((*i).peerId);}
        catch(const CORBA::OBJECT_NOT_EXIST &) {}
        catch (const CORBA::COMM_FAILURE &) {}
        catch (const CORBA::TRANSIENT &) {}
    }
    my_parents.clear();
    ServantBase::deactivate(this);
    Berlin::GraphicDictionary::instance()->remove(this);
}

Graphic_ptr GraphicImpl::body() { return Fresco::Graphic::_nil(); }
void GraphicImpl::body(Graphic_ptr) { }
void GraphicImpl::append_graphic(Graphic_ptr) { }
void GraphicImpl::prepend_graphic(Graphic_ptr) { }
void GraphicImpl::remove_graphic(Tag) { }
void GraphicImpl::remove_child_graphic(Tag) { }

Tag GraphicImpl::unique_parent_id()
{
    Tag t;
    for (t = 0;
     find_if(my_parents.begin(), my_parents.end(), localId_eq(t)) !=
         my_parents.end();
     t++);
    return t;
}

Tag GraphicImpl::add_parent_graphic(Graphic_ptr parent, Tag peerId)
{
    Trace trace(this, "GraphicImpl::add_parent_graphic");
    /*
     * note: we don't do ref counting on the parents to avoid cyclic
     * dependencies. Whenever a graphic node has no more parents (and no
     * other party holding a reference to it, it is considered to be a
     * candidate for deactivation, which then will result in the destruction
     * of this servant and by this, the decrement of the ref counter for all
     * children. Eventually the loop will just start over again then...
     */
    Edge edge;
    edge.peer = Fresco::Graphic::_duplicate(parent);
    edge.peerId = peerId;
    edge.localId = unique_parent_id();
    {
    Prague::Guard<Mutex> guard(my_mutex);
    my_parents.push_back(edge);
    }
    return edge.localId;
}

void GraphicImpl::remove_parent_graphic(Tag localId)
{
    Trace trace(this, "GraphicImpl::remove_parent_graphic");
    Prague::Guard<Mutex> guard(my_mutex);
    for (glist_t::iterator i = my_parents.begin(); i != my_parents.end(); ++i)
    if ((*i).localId == localId)
    {
        my_parents.erase(i);
        return;
    }
}

/*
 * the following two methods need to be implemented...
 */
Fresco::GraphicIterator_ptr GraphicImpl::first_child_graphic()
{ return Fresco::GraphicIterator::_nil(); }
Fresco::GraphicIterator_ptr GraphicImpl::last_child_graphic()
{ return Fresco::GraphicIterator::_nil(); }

/*
 * these are default implementations of the layout, picking and drawing
 * protocol which are *intended* to be overridden in children of Graphic,
 * if you want them to actually do anything remotely exciting.
 */

Transform_ptr GraphicImpl::transformation() { return Transform::_nil(); }
void GraphicImpl::request(Fresco::Graphic::Requisition &) { }
void GraphicImpl::extension(const Allocation::Info &a, Region_ptr r)
{ GraphicImpl::default_extension(a, r); }
void GraphicImpl::shape(Region_ptr) { }

void GraphicImpl::traverse(Traversal_ptr traversal)
{ traversal->visit(Graphic_var(_this())); }
void GraphicImpl::draw(DrawTraversal_ptr) { }
void GraphicImpl::pick(PickTraversal_ptr) { }

void GraphicImpl::allocate(Tag, const Allocation::Info &) { }
void GraphicImpl::allocations(Allocation_ptr allocation)
{
    Prague::Guard<Mutex> guard(my_mutex);
    CORBA::Long begin = allocation->size();
    for (glist_t::iterator i = my_parents.begin(); i != my_parents.end(); i++)
    {
    if (CORBA::is_nil((*i).peer)) continue;
    try
    {
        (*i).peer->allocations(allocation);      
        CORBA::Long end = allocation->size();
        for (CORBA::Long j = begin; j != end; j++)
        {
        const Allocation::Info_var info = allocation->get(j);
        (*i).peer->allocate((*i).peerId, info.in());
        }
        begin = end;
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { (*i).peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { (*i).peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::TRANSIENT &)
    { (*i).peer = Fresco::Graphic::_nil(); }
    }
}

/*
 * this is the method which causes DrawTraversals to get queued up to run over
 * the scene graph.  It does so by retrieving a list of all the current
 * graphic's Allocation::infos (places on the screen where the graphic
 * appears) and then sequentially extending the provided "damaged areas" with
 * the current graphic's own allocated region. As the damaged regions are
 * extended, they queue DrawTraversals in the ScreenManager, which will send
 * them down to redraw this node when an appropriate time comes 
 */
void GraphicImpl::need_redraw()
{
    Trace trace(this, "GraphicImpl::needRedraw");
    Lease_var<AllocationImpl> allocation(Provider<AllocationImpl>::provide());
    allocation->clear();
    allocations(Allocation_var(allocation->_this()));
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    CORBA::Long size = allocation->size();
    for (CORBA::Long i = 0; i < size; i++)
    {
    const Allocation::Info_var info = allocation->get(i);
    region->valid = false;
    extension(info.in(), Region_var(region->_this()));
    if (region->valid) info->root->damage(Region_var(region->_this()));
    }
}

/* this does almost exactly the same as needRedraw(), only it extends the
 * parent-supplied damage region by a user-supplied subregion of the current
 * graphic. It does this by copying and then transforming the user-supplied
 * region to fit within the transformation of each Allocation::info received
 * from the parents 
 */
void GraphicImpl::need_redraw_region(Region_ptr region)
{
    Trace trace(this, "GraphicImpl::need_redraw_region");
    if (region->defined())
    {
    Lease_var<AllocationImpl>
        allocation(Provider<AllocationImpl>::provide());
    allocation->clear();
    allocations(Allocation_var(allocation->_this()));
    Lease_var<RegionImpl> dr(Provider<RegionImpl>::provide());
    for (CORBA::Long i = 0; i < allocation->size(); i++)
    {
        Allocation::Info_var info = allocation->get(i);
        dr->copy(region);
        dr->apply_transform(info->transformation);
        info->root->damage(Region_var(dr->_this()));
    }
    }
}

void GraphicImpl::need_resize()
{
    Prague::Guard<Mutex> guard(my_mutex);
    for (glist_t::iterator i = my_parents.begin(); i != my_parents.end(); i++)
    try
    { (*i).peer->need_resize(); }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { (*i).peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { (*i).peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::TRANSIENT &)
    { (*i).peer = Fresco::Graphic::_nil(); }
}

void GraphicImpl::init_requisition(Fresco::Graphic::Requisition &r)
{
    r.x.defined = false;
    r.y.defined = false;
    r.z.defined = false;
    r.preserve_aspect = false;
}

void GraphicImpl::default_requisition(Fresco::Graphic::Requisition &r)
{
    Coord zero = 0.;
    require(r.x, zero, zero, zero, zero);
    require(r.y, zero, zero, zero, zero);
    require(r.z, zero, zero, zero, zero);
    r.preserve_aspect = false;
}

void GraphicImpl::require(Fresco::Graphic::Requirement &r,
              Coord natural, Coord stretch, Coord shrink,
              Coord alignment)
{
    r.defined = true;
    r.natural = natural;
    r.maximum = natural + stretch;
    r.minimum = natural - shrink;
    r.align = alignment;
}

void GraphicImpl::require_lead_trail(Fresco::Graphic::Requirement &r,
                     Coord natural_lead, Coord max_lead,
                     Coord min_lead,
                     Coord natural_trail, Coord max_trail,
                     Coord min_trail)
{
    Coord zero = 0;
    r.defined = true;
    natural_lead = Math::max(min_lead, Math::min(max_lead, natural_lead));
    max_lead = Math::max(max_lead, natural_lead);
    min_lead = Math::min(min_lead, natural_lead);
    natural_trail = Math::max(min_trail, Math::min(max_trail, natural_trail));
    max_trail = Math::max(max_trail, natural_trail);
    min_trail = Math::min(min_trail, natural_trail);
    r.natural = natural_lead + natural_trail;
    if (natural_lead == zero)
    {
    r.minimum = min_trail;
    r.maximum = max_trail;
    r.align = 0.;
    }
    else if (natural_trail == zero)
    {
    r.minimum = min_lead;
    r.maximum = max_lead;
    r.align = 1.;
    }
    else
    {
    r.minimum = min_lead + min_trail;
    r.maximum = max_lead + max_trail;
    if (r.natural == zero)
        r.align = zero;
    else
        r.align = natural_lead / r.natural;
    }
}

Fresco::Graphic::Requirement *
GraphicImpl::requirement(Fresco::Graphic::Requisition &r, Axis a)
{
    Fresco::Graphic::Requirement *req;
    switch (a)
    {
    case xaxis: req = &r.x; break;
    case yaxis: req = &r.y; break;
    case zaxis: req = &r.z; break;
    default: req = 0; break;
    }
    return req;
}

void GraphicImpl::default_extension(const Fresco::Allocation::Info &info,
                    Region_ptr region)
{
    if (!CORBA::is_nil(info.allocation))
    {
    if (CORBA::is_nil(info.transformation))
        region->merge_union(info.allocation);
    else
    {
        Lease_var<RegionImpl> tmp(Provider<RegionImpl>::provide());
        tmp->clear();
        tmp->copy(info.allocation);
        if (!CORBA::is_nil(info.transformation) &&
        !info.transformation->identity())
        tmp->apply_transform(info.transformation);      
        region->merge_union(Region_var(tmp->_this()));
    }
    }
}

void GraphicImpl::natural_allocation (Graphic_ptr g, RegionImpl &nat)
{
    Fresco::Graphic::Requisition r;
    GraphicImpl::init_requisition(r);
    
    g->request(r);
    if (r.x.defined)
    {
    nat.xalign = r.x.align;
    nat.lower.x = -r.x.align * r.x.natural;
    nat.upper.x = nat.lower.x + r.x.natural;
    nat.valid = true;
    }
    if (r.y.defined)
    {
    nat.yalign = r.y.align;
    nat.lower.y = -r.y.align * r.y.natural;
    nat.upper.y = nat.lower.y + r.y.natural;
    nat.valid = true;
    }
    if (r.z.defined)
    {
    nat.lower.z = -r.z.align * r.z.natural;
    nat.upper.z = nat.lower.z + r.z.natural;
    nat.zalign = r.z.align;
    nat.valid = true;
    }
}

void GraphicImpl::transform_request (Fresco::Graphic::Requisition &req,
                     Transform_ptr tx)
{
    if (CORBA::is_nil(tx) || tx->identity()) return;
    if (Math::equal(req.x.natural, req.x.maximum, tol) &&
    Math::equal(req.y.natural, req.y.maximum, tol) &&
    Math::equal(req.z.natural, req.z.maximum, tol) &&
    Math::equal(req.x.natural, req.x.minimum, tol) &&
    Math::equal(req.y.natural, req.y.minimum, tol) &&
    Math::equal(req.z.natural, req.z.minimum, tol))
    fixed_transform_request(req, tx);
    else
    flexible_transform_request(req, tx);
}

static void compensate(Coord a, Coord &x, Coord &y)
{
    if (a > 0.)
    {
    if (Math::equal(x, 0., 1.0e-6)) y = a * x;
    else
    {
        Coord aspect = y/x;
        if (aspect > a) y = a * x;
        else if (aspect < a) x = y / a;
    }
    }
}

/*
 * the point here is to take <region> as a given allocation and produce an
 * allocation for the child given a requisition and a transformation.
 *
 *   +-----x-+
 *   | Rp / \|
 *   |   /  /|
 *   |  /Rc/ |
 *   | /  /  |
 *   |/  /   |
 *   |\ /    |
 *   +-x-----+
 */
Vertex
GraphicImpl::transform_allocate(RegionImpl &region,
                const Fresco::Graphic::Requisition &_req,
                Transform_ptr t)
{
    Trace trace("GraphicImpl::transform_allocation");
    Vertex delta;
    delta.x = delta.y = delta.z = 0.;

    //FIXME: this is a hack! we need to figure out how to treat undefined
    // requisitions - stefan
    Fresco::Graphic::Requisition req = _req;
    if (!req.z.defined)
    {
    req.z.natural = req.z.maximum = req.z.minimum = 0.;
    req.z.align = 0.5; //region.zalign;
    req.z.defined = true;
    }
    
    if (!rotated(t))
    {
    Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
    tx->copy(t);
    tx->invert();
    region.apply_transform(Transform_var(tx->_this()));
    region.xalign = req.x.align;
    region.yalign = req.y.align;
    region.zalign = req.z.align;
    }
    else
    {
    Vertex center;
    center.x = (region.lower.x + region.upper.x) * 0.5;
    center.y = (region.lower.y + region.upper.y) * 0.5;
    center.z = (region.lower.z + region.upper.z) * 0.5;
    Fresco::Transform::Matrix m;
    t->store_matrix(m);
    Fresco::Graphic::Requisition r[3], total;
    GraphicImpl::init_requisition(r[0]);
    GraphicImpl::init_requisition(r[1]);
    GraphicImpl::init_requisition(r[2]);
    GraphicImpl::init_requisition(total);    
    
    RegionImpl a[3];
//        Coord a0 = -1; Coord a1 = -1; Coord a2 = -1;
//        if (!Math::equal(m[0][0], 0.0, tol))
//            a0 = Math::abs(m[1][0] / m[0][0]);
//       if (!Math::equal(m[0][1], 0.0, tol))
//            a1 = Math::abs(m[1][1] / m[0][1]);

    r[0].x.natural = Math::abs(req.x.natural*m[0][0]);
    r[0].x.maximum = Math::abs(req.x.maximum*m[0][0]);
    r[0].x.minimum = Math::abs(req.x.minimum*m[0][0]);
    r[0].x.align = 0.;
    r[0].x.defined = true;
    r[0].y.natural = Math::abs(req.x.natural*m[1][0]);
    r[0].y.maximum = Math::abs(req.x.maximum*m[1][0]);
    r[0].y.minimum = Math::abs(req.x.minimum*m[1][0]);
    r[0].y.align = 0.;
    r[0].y.defined = true;
    r[0].z.natural = Math::abs(req.x.natural*m[2][0]);
    r[0].z.maximum = Math::abs(req.x.maximum*m[2][0]);
    r[0].z.minimum = Math::abs(req.x.minimum*m[2][0]);
    r[0].z.align = 0.;
    r[0].z.defined = true;
    
    r[1].x.natural = Math::abs(req.y.natural*m[0][1]);
    r[1].x.maximum = Math::abs(req.y.maximum*m[0][1]);
    r[1].x.minimum = Math::abs(req.y.minimum*m[0][1]);
    r[1].x.align = 0.;
    r[1].x.defined = true;
    r[1].y.natural = Math::abs(req.y.natural*m[1][1]);
    r[1].y.maximum = Math::abs(req.y.maximum*m[1][1]);
    r[1].y.minimum = Math::abs(req.y.minimum*m[1][1]);
    r[1].y.align = 0.;
    r[1].y.defined = true;
    r[1].z.natural = Math::abs(req.y.natural*m[2][1]);
    r[1].z.maximum = Math::abs(req.y.maximum*m[2][1]);
    r[1].z.minimum = Math::abs(req.y.minimum*m[2][1]);
    r[1].z.align = 0.;
    r[1].z.defined = true;
    
    r[2].x.natural = Math::abs(req.z.natural*m[0][2]);
    r[2].x.maximum = Math::abs(req.z.maximum*m[0][2]);
    r[2].x.minimum = Math::abs(req.z.minimum*m[0][2]);
    r[2].x.align = 0.;
    r[2].x.defined = true;
    r[2].y.natural = Math::abs(req.z.natural*m[1][2]);
    r[2].y.maximum = Math::abs(req.z.maximum*m[1][2]);
    r[2].y.minimum = Math::abs(req.z.minimum*m[1][2]);
    r[2].y.align = 0.;
    r[2].y.defined = true;
    r[2].z.natural = Math::abs(req.z.natural*m[2][2]);
    r[2].z.maximum = Math::abs(req.z.maximum*m[2][2]);
    r[2].z.minimum = Math::abs(req.z.minimum*m[2][2]);
    r[2].z.align = 0.;
    r[2].z.defined = true;
    
    total.x.natural = r[0].x.natural + r[1].x.natural + r[2].x.natural;
    total.x.maximum = r[0].x.maximum + r[1].x.maximum + r[2].x.maximum;
    total.x.minimum = r[0].x.minimum + r[1].x.minimum + r[2].x.minimum;
    total.x.defined = true;
    total.y.natural = r[0].y.natural + r[1].y.natural + r[2].y.natural;
    total.y.maximum = r[0].y.maximum + r[1].y.maximum + r[2].y.maximum;
    total.y.minimum = r[0].y.minimum + r[1].y.minimum + r[2].y.minimum;
    total.y.defined = true;
    total.z.natural = r[0].z.natural + r[1].z.natural + r[2].z.natural;
    total.z.maximum = r[0].z.maximum + r[1].z.maximum + r[2].z.maximum;
    total.z.minimum = r[0].z.minimum + r[1].z.minimum + r[2].z.minimum;
    total.z.defined = true;
    
    compute_allocations(xaxis, total, 3, r, region, a);
    compute_allocations(yaxis, total, 3, r, region, a);
    compute_allocations(zaxis, total, 3, r, region, a);
    Coord x0 = a[0].upper.x - a[0].lower.x;
    Coord y0 = a[0].upper.y - a[0].lower.y;
    Coord z0 = a[0].upper.z - a[0].lower.z;
    Coord x1 = a[1].upper.x - a[1].lower.x;
    Coord y1 = a[1].upper.y - a[1].lower.y;
    Coord z1 = a[1].upper.z - a[1].lower.z;
    Coord x2 = a[2].upper.x - a[2].lower.x;
    Coord y2 = a[2].upper.y - a[2].lower.y;
    Coord z2 = a[2].upper.z - a[2].lower.z;
//        compensate(a0, x0, y0);
//        compensate(a1, x1, y1);
//        compensate(a2, x2, y2);

    Coord lx = sqrt(x0*x0 + y0*y0 + z0*z0) /
        sqrt(m[0][0]*m[0][0] + m[1][0]*m[1][0] + m[2][0]*m[2][0]);
    Coord ly = sqrt(x1*x1 + y1*y1 + z1*z1) /
        sqrt(m[0][1]*m[0][1] + m[1][1]*m[1][1] + m[2][1]*m[2][1]);
    Coord lz = sqrt(x2*x2 + y2*y2 + z2*z2) /
        sqrt(m[0][2]*m[0][2] + m[1][2]*m[1][2] + m[2][2]*m[2][2]);

    region.xalign = req.x.align;
    region.yalign = req.y.align;
    region.zalign = req.z.align;
    t->inverse_transform_vertex(center);
    
    delta.x = center.x - lx * 0.5 - region.lower.x;
    delta.y = center.y - ly * 0.5 - region.lower.y;
    delta.z = center.z - lz * 0.5 - region.lower.z;
    region.lower.x = -region.xalign * lx;
    region.lower.y = -region.yalign * ly;
    region.lower.z = -region.zalign * lz;
    region.upper.x = region.lower.x + lx;
    region.upper.y = region.lower.y + ly;
    region.upper.z = region.lower.z + lz;
    }
    return delta;
}
