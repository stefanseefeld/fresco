/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org>
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
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/PickTraversal.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Math.hh>
#include <Berlin/Provider.hh>
#include <Berlin/TransformImpl.hh>
#include "ViewportImpl.hh"

using namespace Prague;
using namespace Fresco;
using namespace Layout;

static const double epsilon = 10e-6;

namespace Berlin
{
  namespace LayoutKit
  {
    class ViewportImpl::Adjustment :
      public virtual POA_Fresco::BoundedRange, public SubjectImpl
    {
      public:
        Adjustment();
        virtual ~Adjustment();
        virtual Fresco::BoundedRange::Settings state();
        virtual void state(const Fresco::BoundedRange::Settings &);
        virtual Coord lower();
        virtual void lower(Coord);
        virtual Coord upper();
        virtual void upper(Coord);
        virtual Coord step();
        virtual void step(Coord);
        virtual Coord page();
        virtual void page(Coord);
        virtual Coord lvalue();
        virtual void lvalue(Coord);
        virtual Coord uvalue();
        virtual void uvalue(Coord);
        virtual void forward();
        virtual void backward();
        virtual void fastforward();
        virtual void fastbackward();
        virtual void begin();
        virtual void end();
        virtual void adjust(Coord);
        virtual const char *object_name()
    { return "ViewportImpl::Adjustment"; }
      private:
        Fresco::BoundedRange::Settings my_settings;
        Coord                          my_s;
        Coord                          my_p;
        Mutex                          my_mutex;
    };
    
    ViewportImpl::Adjustment::Adjustment() : my_s(10.), my_p(10.)
    {
    my_settings.lower = my_settings.upper =
        my_settings.lvalue = my_settings.uvalue = 0.;
    }

    ViewportImpl::Adjustment::~Adjustment() { }

    Fresco::BoundedRange::Settings ViewportImpl::Adjustment::state()
    {
        Prague::Guard<Mutex> guard(my_mutex);
        return my_settings;
    }

    void ViewportImpl::Adjustment::state(const Fresco::BoundedRange::Settings &s)
    {
        Prague::Guard<Mutex> guard(my_mutex);
        my_settings = s;
    }

    Coord ViewportImpl::Adjustment::lower()
    {
        Prague::Guard<Mutex> guard(my_mutex);
        return my_settings.lower;
    }

    void ViewportImpl::Adjustment::lower(Coord l)
    {
        CORBA::Any any;
        {
            Prague::Guard<Mutex> guard(my_mutex);
            if (l == my_settings.lower) return;
            my_settings.lower = l;
            my_settings.lvalue = std::max(my_settings.lvalue,
                      my_settings.lower);
            my_settings.uvalue = std::max(my_settings.uvalue,
                      my_settings.lower);
            any <<= my_settings;
        }
        notify(any);
    }

    Coord ViewportImpl::Adjustment::upper()
    {
        Prague::Guard<Mutex> guard(my_mutex);
        return my_settings.upper;
    }

    void ViewportImpl::Adjustment::upper(Coord u)
    {
        CORBA::Any any;
        {
            Prague::Guard<Mutex> guard(my_mutex);
            if (my_settings.upper == u) return;
            my_settings.upper = u;
            my_settings.lvalue = std::min(my_settings.lvalue,
                      my_settings.upper);
            my_settings.uvalue = std::min(my_settings.uvalue,
                      my_settings.upper);
            any <<= my_settings;
        }
        notify(any);
    }

    Coord ViewportImpl::Adjustment::step()
    {
        Prague::Guard<Mutex> guard(my_mutex);
        return my_s;
    }

    void ViewportImpl::Adjustment::step(Coord s)
    {
        Prague::Guard<Mutex> guard(my_mutex);
        my_s = s;
    }

    Coord ViewportImpl::Adjustment::page()
    {
        Prague::Guard<Mutex> guard(my_mutex);
        return my_p;
    }

    void ViewportImpl::Adjustment::page(Coord p)
    {
        Prague::Guard<Mutex> guard(my_mutex);
        my_p = p;
    }

    void ViewportImpl::Adjustment::forward()
    {
        CORBA::Any any;
        {
            Prague::Guard<Mutex> guard(my_mutex);
            Coord t = std::min(my_s,
                   my_settings.upper - my_settings.uvalue);
            if (t <= 0.) return;
            my_settings.lvalue += t;
            my_settings.uvalue += t;
            any <<= my_settings;
        }
        notify(any);
    }

    void ViewportImpl::Adjustment::backward()
    {
        CORBA::Any any;
        {
            Prague::Guard<Mutex> guard(my_mutex);
            Coord t = std::min(my_s,+
                   my_settings.lvalue - my_settings.lower);
            if (t <= 0.) return;
            my_settings.lvalue -= t;
            my_settings.uvalue -= t;
            any <<= my_settings;
        }
        notify(any);
    }

    void ViewportImpl::Adjustment::fastforward()
    {
        CORBA::Any any;
        {
            Prague::Guard<Mutex> guard(my_mutex);
            Coord t = std::min(my_p,
                   my_settings.upper - my_settings.uvalue);
            if (t <= 0.) return;
            my_settings.lvalue += t;
            my_settings.uvalue += t;
            any <<= my_settings;
        }
        notify(any);
    }

    void ViewportImpl::Adjustment::fastbackward()
    {
        CORBA::Any any;
        {
            Prague::Guard<Mutex> guard(my_mutex);
            Coord t = std::min(my_p,
                   my_settings.lvalue - my_settings.lower);
            if (t <= 0.) return;
            my_settings.lvalue -= t;
            my_settings.uvalue -= t;
            any <<= my_settings;
        }
        notify(any);
    }

    void ViewportImpl::Adjustment::begin()
    {
        CORBA::Any any;
        {
            Prague::Guard<Mutex> guard(my_mutex);
            Coord t = my_settings.lvalue - my_settings.lower;
            if (t == 0.) return;
            my_settings.lvalue -= t;
            my_settings.uvalue -= t;
            any <<= my_settings;
        }
        notify(any);
    }

    void ViewportImpl::Adjustment::end()
    {
        CORBA::Any any;
        {
            Prague::Guard<Mutex> guard(my_mutex);
            Coord t = my_settings.upper - my_settings.uvalue;
            if (t == 0.) return;
            my_settings.lvalue += t;
            my_settings.uvalue += t;
            any <<= my_settings;
        }
        notify(any);
    }

    void ViewportImpl::Adjustment::lvalue(Coord lv)
    {
        CORBA::Any any;
        {
            lv = std::min(std::max(my_settings.lower, lv),
              my_settings.upper);
            Prague::Guard<Mutex> guard(my_mutex);
            if (lv == my_settings.lvalue) return;
            my_settings.lvalue = lv;
            any <<= my_settings;
        }
        notify(any);
    }

    Coord ViewportImpl::Adjustment::lvalue()
    {
        Prague::Guard<Mutex> guard(my_mutex);
        return my_settings.lvalue;
    }


    void ViewportImpl::Adjustment::uvalue(Coord uv)
    {
        CORBA::Any any;
        {
            uv = std::min(std::max(my_settings.lower, uv),
              my_settings.upper);
            Prague::Guard<Mutex> guard(my_mutex);
            if (my_settings.uvalue == uv) return;
            my_settings.uvalue = uv;
            any <<= my_settings;
        }
        notify(any);
    }

    Coord ViewportImpl::Adjustment::uvalue()
    {
        Prague::Guard<Mutex> guard(my_mutex);
        return my_settings.uvalue;
    }


    void ViewportImpl::Adjustment::adjust(Coord d)
    {
        CORBA::Any any;
        {
            Prague::Guard<Mutex> guard(my_mutex);
            Coord t =
        std::min(std::max(d,
                  my_settings.lower - my_settings.lvalue),
             my_settings.upper - my_settings.uvalue);
            if (t == 0.) return;
            my_settings.lvalue += t;
            my_settings.uvalue += t;
            any <<= my_settings;
        }
        notify(any);
    }
    
    ViewportImpl::ViewportImpl() : my_requested(false)
    {
        init_requisition(my_requisition);
        my_settings[xaxis].lower = my_settings[xaxis].upper =
        my_settings[xaxis].lvalue = my_settings[xaxis].uvalue = 0;
        my_settings[yaxis].lower = my_settings[yaxis].upper =
        my_settings[yaxis].lvalue = my_settings[yaxis].uvalue = 0;
    }

    ViewportImpl::~ViewportImpl() { }

    void ViewportImpl::body(Graphic_ptr g)
    {
        MonoGraphic::body(g);
        need_resize();
        MonoGraphic::need_resize();
    }

    Transform_ptr ViewportImpl::transformation()
    { return Transform::_nil(); }

    void ViewportImpl::request(Fresco::Graphic::Requisition &r)
    {
        cache_requisition();
        GraphicImpl::require(r.x, my_requisition.x.natural, 0.,
                             my_requisition.x.natural,
                 my_requisition.x.align);
        GraphicImpl::require(r.y, my_requisition.y.natural, 0.,
                             my_requisition.y.natural,
                 my_requisition.y.align);
        if(my_requisition.z.defined)
            GraphicImpl::require(r.z, my_requisition.z.natural, 0.,
                                 my_requisition.z.natural,
                 my_requisition.z.align);
    }

    void ViewportImpl::traverse(Traversal_ptr traversal)
    {
        Graphic_var child = body();
        if (!CORBA::is_nil(child) && traversal->intersects_allocation())
        {
            // first update the cached allocation and the adjustments
            Region_var allocation = traversal->current_allocation();
            cache_allocation(allocation);
            traversal->visit(Graphic_var(_this()));
        }
    }

    void ViewportImpl::draw(DrawTraversal_ptr traversal)
    {
        /*
         * now simply traverse the child with it's desired allocation
         * and a suitable offset
         */
        Region_var allocation = traversal->current_allocation();
        Transform_var transformation = traversal->current_transformation();

        Lease_var<RegionImpl> clipping(Provider<RegionImpl>::provide());
        clipping->copy(allocation);
        if (!CORBA::is_nil(transformation) && !transformation->identity())
            clipping->apply_transform(transformation);

        DrawingKit_var drawing = traversal->drawing();
        drawing->save();
        clipping->merge_intersect(drawing->clipping());
        drawing->clipping(Region_var(clipping->_this()));

        Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
        Lease_var<RegionImpl> b(Provider<RegionImpl>::provide());
        body_allocation(allocation, b);
        region->copy(Region_var(b->_this()));

        Lease_var<TransformImpl>
        transform(Provider<TransformImpl>::provide());
        transform->load_identity();

        region->normalize(Transform_var(transform->_this()));
        try
        {
            traversal->traverse_child(my_child.peer, my_child.localId,
                                      Region_var(region->_this()),
                                      Transform_var(transform->_this()));
        }
        catch (const CORBA::OBJECT_NOT_EXIST &)
    { body(Fresco::Graphic::_nil()); }
        catch (const CORBA::COMM_FAILURE &)
    { body(Fresco::Graphic::_nil()); }
        catch (const CORBA::TRANSIENT &)
    { body(Fresco::Graphic::_nil()); }
        drawing->restore();
    }

    void ViewportImpl::pick(PickTraversal_ptr traversal)
    {
        /*
         * now simply traverse the child with it's desired allocation
         * and a suitable offset
         */
        Region_var allocation = traversal->current_allocation();
        Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
        Lease_var<RegionImpl> b(Provider<RegionImpl>::provide());
        body_allocation(allocation, b);
        region->copy(Region_var(b->_this()));

        Lease_var<TransformImpl>
        transform(Provider<TransformImpl>::provide());
        transform->load_identity();

        region->normalize(Transform_var(transform->_this()));
        try
        {
            traversal->traverse_child (my_child.peer, my_child.localId,
                                       Region_var(region->_this()),
                                       Transform_var(transform->_this()));
        }
        catch (const CORBA::OBJECT_NOT_EXIST &)
    { body(Fresco::Graphic::_nil()); }
        catch (const CORBA::COMM_FAILURE &)
    { body(Fresco::Graphic::_nil()); }
        catch (const CORBA::TRANSIENT &)
    { body(Fresco::Graphic::_nil()); }
    }

    void ViewportImpl::need_resize()
    {
        // set adjustment's outer range according to the body size
        my_requested = false;
        cache_requisition();
        need_redraw();
    }

    void ViewportImpl::update(const CORBA::Any &)
    {
        /*
         * we are only interested in changes concerning the outer range
     * (body) or the offset
         */
        Fresco::BoundedRange::Settings x = my_xadjustment->state();
        Fresco::BoundedRange::Settings y = my_yadjustment->state();
        bool damage = (x.lower != my_settings[xaxis].lower ||
                       y.lower != my_settings[yaxis].lower ||
                       x.upper != my_settings[xaxis].upper ||
                       y.upper != my_settings[yaxis].upper ||
                       x.lvalue != my_settings[xaxis].lvalue ||
                       y.lvalue != my_settings[yaxis].lvalue);
        my_settings[xaxis].lvalue = x.lvalue;
        my_settings[xaxis].uvalue = x.uvalue;
        my_settings[yaxis].lvalue = y.lvalue;
        my_settings[yaxis].uvalue = y.uvalue;
        if (damage) need_redraw();
    }

    void ViewportImpl::activate_composite()
    {
        Adjustment *adjustment = new Adjustment;
        activate(adjustment);
        my_xadjustment =
        RefCount_var<BoundedRange>::increment(adjustment->_this(),
                          false);
        my_xadjustment->attach(Observer_var(_this()));
        adjustment = new Adjustment;
        activate(adjustment);
        my_yadjustment =
        RefCount_var<BoundedRange>::increment(adjustment->_this(),
                          false);
        my_yadjustment->attach(Observer_var(_this()));
    }

    void ViewportImpl::allocate_child(Allocation::Info &info)
    {
        scroll_transform(info.transformation);
        Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
        Lease_var<RegionImpl> b(Provider<RegionImpl>::provide());
        body_allocation(info.allocation, b);
        region->copy(Region_var(b->_this()));
        info.allocation->copy(Region_var(region->_this()));
    }

    BoundedRange_ptr ViewportImpl::adjustment(Axis a)
    {
        // FIXME: What about the zaxis? I know... it is not really useful
        //        but it is allowed for input and should not just return
        //        the value for the yaxis. -- tobias
        return a == xaxis ?
        RefCount_var<BoundedRange>::increment(my_xadjustment) :
        RefCount_var<BoundedRange>::increment(my_yadjustment);
    }

    void ViewportImpl::cache_requisition()
    //. retrieves requisition from body and updates adjustments
    {
        if (!my_requested)
        {
            my_requested = true;
            MonoGraphic::request(my_requisition);
            Fresco::Graphic::Requirement &rx = my_requisition.x;
            Fresco::Graphic::Requirement &ry = my_requisition.y;

            my_settings[xaxis].lvalue = my_settings[xaxis].lower =
              rx.defined ? - rx.natural * rx.align : 0.;
            my_settings[xaxis].uvalue = my_settings[xaxis].upper =
              rx.defined ? my_settings[xaxis].lvalue + rx.natural : 0.;
            if (rx.defined)
            {
                my_xadjustment->lower(my_settings[xaxis].lower);
                my_xadjustment->upper(my_settings[xaxis].upper);
            }
            my_settings[yaxis].lvalue = my_settings[yaxis].lower =
              ry.defined ? - ry.natural * ry.align : 0.;
            my_settings[yaxis].uvalue = my_settings[yaxis].upper =
              ry.defined ? my_settings[yaxis].lvalue + ry.natural : 0.;
            if (ry.defined)
            {
                my_yadjustment->lower(my_settings[yaxis].lower);
                my_yadjustment->upper(my_settings[yaxis].upper);
            }
        }
    }

    void ViewportImpl::cache_allocation(Region_ptr allocation)
    {
        if (!CORBA::is_nil(allocation))
        {
            Region::Allotment xa, ya;
            allocation->span(xaxis, xa);
            allocation->span(yaxis, ya);

            if (!Math::equal(xa.end - xa.begin,
                 my_settings[xaxis].uvalue -
                 my_settings[xaxis].lvalue,
                 epsilon))
            {
                my_settings[xaxis].uvalue =
            my_settings[xaxis].lvalue + xa.end - xa.begin;
                my_xadjustment->uvalue(my_settings[xaxis].uvalue);
            }
            if (!Math::equal(ya.end - ya.begin,
                 my_settings[yaxis].uvalue -
                 my_settings[yaxis].lvalue,
                 epsilon))
            {
                my_settings[yaxis].uvalue = ya.end - ya.begin;
                my_yadjustment->uvalue(my_settings[yaxis].uvalue);
            }
        }
    }

    void ViewportImpl::body_allocation(Region_ptr, RegionImpl *ca)
    {
        /*
         * FIXME!! : this implementation ignores completely the body
     *           alignment...
         */
        ca->valid = true;
        ca->lower.x = -(my_settings[xaxis].lvalue -
            my_settings[xaxis].lower);
        ca->lower.y = -(my_settings[yaxis].lvalue -
            my_settings[yaxis].lower);
        ca->lower.z = 0.;
        ca->upper.x = -(my_settings[xaxis].lvalue -
            my_settings[xaxis].upper);
        ca->upper.y = -(my_settings[yaxis].lvalue -
            my_settings[yaxis].upper);
        ca->upper.z = 0.;
        ca->xalign = ca->yalign = ca->yalign = 0.;
    }

    void ViewportImpl::scroll_transform(Transform_ptr tx)
    {
        Vertex v;
        v.x = my_settings[xaxis].lvalue - my_settings[xaxis].lower;
        v.y = my_settings[yaxis].lvalue - my_settings[yaxis].lower;
        v.z = 0.;
        tx->translate(v);
    }

  } // namespace
} // namespace
