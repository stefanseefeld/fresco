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
#include <Fresco/IO.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Math.hh>
#include "LayoutManager.hh"
#include <sstream>

using namespace Fresco;

using namespace Berlin::LayoutKit;

namespace
{
  //. names axes
  const char* name_axis(Axis a)
  {
      switch (a)
      {
      case xaxis: return "X";
      case yaxis: return "Y";
      case zaxis: return "Z";
      }
      return "";
  }
};

// class LayoutManager
LayoutManager::LayoutManager() { }
LayoutManager::~LayoutManager() { }

void LayoutManager::set_span(RegionImpl *r, Axis a,
                 Coord origin, Coord length, Alignment align)
{
    Coord begin = origin - length * align;
    Coord end = begin + length;
    switch (a)
    {
    case xaxis:
    r->lower.x = begin;
    r->upper.x = end;
    r->xalign = align;
    break;
    case yaxis:
    r->lower.y = begin;
    r->upper.y = end;
    r->yalign = align;
    break;
    case zaxis:
    r->lower.z = begin;
    r->upper.z = end;
    r->zalign = align;
    break;
    }
}

// class LayoutAlign

LayoutAlign::LayoutAlign(Axis a) : my_axis(a) { }
LayoutAlign::~LayoutAlign() { }
LayoutManager *LayoutAlign::clone() { return new LayoutAlign(my_axis); }

void LayoutAlign::request(long n, Graphic::Requisition *requests,
              Graphic::Requisition &result)
{
    Graphic::Requirement *r, *rr = 
    GraphicImpl::requirement(result, my_axis);
    rr->defined = false;

    Coord natural_lead = -GraphicImpl::infinity;
    Coord natural_trail = -GraphicImpl::infinity;
    Coord min_lead = -GraphicImpl::infinity;  
    Coord max_lead = GraphicImpl::infinity;  
    Coord min_trail = -GraphicImpl::infinity;  
    Coord max_trail = GraphicImpl::infinity;

    for (int i = 0; i < n; i++)
    {
    r = GraphicImpl::requirement(requests[i], my_axis);
    if (r->defined)
    {
        //. maximum of the natural child lengths becomes natural length
        natural_lead = Math::max(natural_lead, r->natural * r->align);
        //. smallest children's maximum length becomes maximum length
        max_lead = Math::min(max_lead, r->maximum * r->align);
        //. largest children's minimum length becomes minimum length
        min_lead = Math::max(min_lead, r->minimum * r->align);
        //. maximum of the natural child lengths becomes natural length
        natural_trail = Math::max(natural_trail, 
                      r->natural * (1. - r->align));
        //. smallest children's maximum length becomes maximum length
        max_trail = Math::min(max_trail, r->maximum * (1. - r->align));
        //. largest children's minimum length becomes minimum length
        min_trail = Math::max(min_trail, r->minimum * (1. - r->align));
        rr->defined = true;
    }
    }
    
    if (rr->defined)
    GraphicImpl::require_lead_trail(*rr,
                    natural_lead, max_lead, min_lead,
                    natural_trail, max_trail,
                    min_trail);
}

void LayoutAlign::allocate(long n, Graphic::Requisition *requests, 
               Region_ptr given, 
               LayoutManager::Allocations result)
{
    Graphic::Requirement* r;
    Region::Allotment a;
    given->span(my_axis, a);
    for (long i = 0; i < n; i++)
    {
    r = GraphicImpl::requirement(requests[i], my_axis);
    if (r->defined)
    {
        Coord length = Math::max(Math::min(a.end - a.begin,
                           r->maximum), r->minimum);
        set_span(result[i], my_axis,
             a.begin + a.align*(a.end-a.begin), length, r->align);
    }
    else set_span(result[i], my_axis, Coord(0), Coord(0), Coord(0));
    }
}

// class LayoutCenter
LayoutCenter::LayoutCenter(Axis a, Alignment align) :
    my_axis(a), my_alignment(align)
{ }
LayoutCenter::~LayoutCenter() { }
LayoutManager *LayoutCenter::clone()
{ return new LayoutCenter(my_axis, my_alignment); }

void LayoutCenter::request(long, Graphic::Requisition*,
               Graphic::Requisition &result)
{
    Graphic::Requirement *r = GraphicImpl::requirement(result, my_axis);
    r->align = my_alignment;
}

void LayoutCenter::allocate(long, Graphic::Requisition *requests,
                Region_ptr,
                LayoutManager::Allocations result)
{
    Region::Allotment a;
    result[0]->span(my_axis, a);
    Graphic::Requirement *r =
    GraphicImpl::requirement(requests[0], my_axis);
    if (r->defined)
    {
    Coord length = a.end - a.begin;
    Coord n = Math::min(r->maximum, Math::max(r->minimum, length));
    set_span(result[0], my_axis,
         a.begin + a.align * length +
         (r->align - my_alignment) * n,
         length, r->align);
    }
}

// class LayoutFixed
LayoutFixed::LayoutFixed(Axis a, Coord s) : my_axis(a), my_size(s) { }
LayoutFixed::~LayoutFixed() { }
LayoutManager *LayoutFixed::clone()
{ return new LayoutFixed(my_axis, my_size); }

void LayoutFixed::request(long, Graphic::Requisition *,
              Graphic::Requisition &result)
{
    Graphic::Requirement *r = GraphicImpl::requirement(result, my_axis);
    r->natural = my_size;
    r->maximum = my_size;
    r->minimum = my_size;
    if (!r->defined)
    {
    r->defined = true;
    r->align = Alignment(0);
    }
}

void LayoutFixed::allocate(long, Graphic::Requisition *,
               Region_ptr, LayoutManager::Allocations result)
{
    Region::Allotment a;
    result[0]->span(my_axis, a);
    set_span(result[0], my_axis, a.begin + a.align * (a.end - a.begin),
         my_size, a.align);
}

// class LayoutMargin
LayoutMargin::LayoutMargin(Coord m) :
    my_lnatural(m), my_lstretch(0), my_lshrink(0),
    my_rnatural(m), my_rstretch(0), my_rshrink(0),
    my_tnatural(m), my_tstretch(0), my_tshrink(0),
    my_bnatural(m), my_bstretch(0), my_bshrink(0)
{ }

LayoutMargin::LayoutMargin(Coord h, Coord v) :
    my_lnatural(h), my_lstretch(0), my_lshrink(0),
    my_rnatural(h), my_rstretch(0), my_rshrink(0),
    my_tnatural(v), my_tstretch(0), my_tshrink(0),
    my_bnatural(v), my_bstretch(0), my_bshrink(0)
{ }

LayoutMargin::LayoutMargin(Coord l, Coord r, Coord t, Coord b) :
    my_lnatural(l), my_lstretch(0), my_lshrink(0),
    my_rnatural(r), my_rstretch(0), my_rshrink(0),
    my_tnatural(t), my_tstretch(0), my_tshrink(0),
    my_bnatural(b), my_bstretch(0), my_bshrink(0)
{ }

LayoutMargin::LayoutMargin(Coord lm, Coord lS, Coord ls,
               Coord rm, Coord rS, Coord rs,
               Coord tm, Coord tS, Coord ts,
               Coord bm, Coord bS, Coord bs) :
    my_lnatural(lm), my_lstretch(lS), my_lshrink(ls),
    my_rnatural(rm), my_rstretch(rS), my_rshrink(rs),
    my_tnatural(tm), my_tstretch(tS), my_tshrink(ts),
    my_bnatural(bm), my_bstretch(bS), my_bshrink(bs)
{ }

LayoutMargin::~LayoutMargin() { }

LayoutManager *LayoutMargin::clone()
{
  return new LayoutMargin(my_lnatural, my_lstretch, my_lshrink,
              my_rnatural, my_rstretch, my_rshrink,
              my_tnatural, my_tstretch, my_tshrink,
              my_bnatural, my_bstretch, my_bshrink);
}

void LayoutMargin::request(long, Graphic::Requisition *,
               Graphic::Requisition &result)
{
    Graphic::Requirement &rx = result.x;
    if (!rx.defined)
    {
    rx.defined = true;
    rx.natural = Coord(0);
    rx.maximum = Coord(0);
    rx.minimum = Coord(0);
    }
    
    Coord dx = my_lnatural + my_rnatural;
    rx.natural += dx;
    rx.maximum += dx + (my_lstretch + my_rstretch);
    rx.minimum += dx - (my_lshrink + my_rshrink);
    
    Graphic::Requirement &ry = result.y;
    if (!ry.defined)
    {
    ry.defined = true;
    ry.natural = Coord(0);
    ry.maximum = Coord(0);
    ry.minimum = Coord(0);
    }
    
    Coord dy = my_bnatural + my_tnatural;
    ry.natural += dy;
    ry.maximum += dy + (my_bstretch + my_tstretch);
    ry.minimum += dy - (my_bshrink + my_tshrink);
    my_requisition = result;
}

void LayoutMargin::allocate(long, Graphic::Requisition *,
                Region_ptr, LayoutManager::Allocations result)
{
    allocate_axis(xaxis, my_lnatural, my_lstretch, my_lshrink,
          my_rnatural, my_rstretch, my_rshrink, result);
    allocate_axis(yaxis, my_tnatural, my_tstretch, my_tshrink,
          my_bnatural, my_bstretch, my_bshrink, result);
}

void LayoutMargin::allocate_axis(Axis axis,
                 Coord natural_lead, Coord stretch_lead,
                 Coord shrink_lead, Coord natural_trail,
                 Coord stretch_trail, Coord shrink_trail,
                 LayoutManager::Allocations result)
{
    Region::Allotment a;
    result[0]->span(axis, a);
    Graphic::Requirement *r =
    GraphicImpl::requirement(my_requisition, axis);
    Coord lead = span(a.end - a.begin, *r,
              natural_lead, stretch_lead, shrink_lead);
    Coord trail = span(a.end - a.begin, *r,
               natural_trail, stretch_trail, shrink_trail);
    Coord length = a.end - a.begin - (lead + trail);
    Coord origin = a.begin + a.align * (a.end - a.begin) +
    ((1 - r->align) * lead - r->align * trail);
    set_span(result[0], axis, origin, length, a.align);
}

Coord LayoutMargin::span(Coord span,
             Graphic::Requirement &total,
             Coord natural, Coord stretch, Coord shrink)
{
    Coord extra = span - total.natural;
    Coord result = natural;
    Coord ss = 0.;
    Coord total_stretch = total.maximum - total.natural;
    Coord total_shrink = total.natural - total.minimum;
    if (extra > 0 && total_stretch > 0) ss = stretch / total_stretch;
    else if (extra < 0 && total_shrink > 0) ss = shrink / total_shrink;
    return result + ss * extra;
}

// class LayoutNatural
LayoutNatural::LayoutNatural(Axis a, Coord n) :
    my_axis(a), my_natural(n)
{ }
LayoutNatural::~LayoutNatural() { }
LayoutManager *LayoutNatural::clone()
{ return new LayoutNatural(my_axis, my_natural); }

void LayoutNatural::request(long, Graphic::Requisition *,
                Graphic::Requisition &result)
{
    Graphic::Requirement *r = GraphicImpl::requirement(result, my_axis);
    r->defined = true;
    r->natural = my_natural;
}

void LayoutNatural::allocate(long, Graphic::Requisition *,
                 Region_ptr, LayoutManager::Allocations)
{ } // leave it as is

// class LayoutSuperpose
LayoutSuperpose::LayoutSuperpose(LayoutManager *f, LayoutManager *s) :
    my_first(f), my_second(s), my_third(0)
{
    // Concatenate names to form this name
    char* fn = f->name(), *sn = s->name();
    std::ostringstream buf;
    buf << fn << "/" << sn << std::ends;
    my_name = strdup(buf.str().c_str());
}
LayoutSuperpose::LayoutSuperpose(LayoutManager *f, LayoutManager *s,
                 LayoutManager *t) : 
    my_first(f), my_second(s), my_third(t)
{
    // Concatenate names to form this name
    char* fn = f->name(), *sn = s->name(), *tn = t->name();
    std::ostringstream buf;
    buf << fn << "/" << sn << "/" << tn << std::ends;
    my_name = strdup(buf.str().c_str());
}
LayoutSuperpose::~LayoutSuperpose()
{
    free(my_name); // strdup implies free, not delete
    delete my_first;
    delete my_second;
    delete my_third;
}

LayoutManager *LayoutSuperpose::clone()
{
    return new LayoutSuperpose(my_first ? my_first->clone() : 0,
                   my_second ? my_second->clone() : 0,
                   my_third ? my_third->clone() : 0);
}

void LayoutSuperpose::request(long n, Graphic::Requisition *requests,
                  Graphic::Requisition &result)
{
    if (my_first) my_first->request(n, requests, result);
    if (my_second) my_second->request(n, requests, result);
    if (my_third) my_third->request(n, requests, result);
}

void LayoutSuperpose::allocate(long n, Graphic::Requisition *requests,
                   Region_ptr given,
                   LayoutManager::Allocations result)
{
    if (my_first) my_first->allocate(n, requests, given, result);
    if (my_second) my_second->allocate(n, requests, given, result);
    if (my_third) my_third->allocate(n, requests, given, result);
}

// class LayoutTile
LayoutTile::LayoutTile(Axis a) : my_axis(a)
{
    // The name is Tile followed by the axis name (X, Y or Z)
    std::ostringstream buf;
    buf << "Tile" << name_axis(a) << std::ends;
    my_name = strdup(buf.str().c_str());
}
LayoutTile::~LayoutTile() { free(my_name); }
LayoutManager *LayoutTile::clone() { return new LayoutTile(my_axis); }

void LayoutTile::request(long n, Graphic::Requisition *requests,
             Graphic::Requisition &result)
{
    compute_request(my_axis, Alignment(0), n, requests, result);
    my_requisition = result;
}

void LayoutTile::allocate(long n, Graphic::Requisition *requests,
              Region_ptr given,
              LayoutManager::Allocations result)
{
    compute_allocations(my_axis, my_requisition, false, n,
            requests, given, result);
}

void LayoutTile::compute_request(Axis a, Alignment align, long n,
                 Graphic::Requisition *requests,
                 Graphic::Requisition &result)
{
    Graphic::Requirement *r;
    Coord natural = Coord(0), min_size = Coord(0), max_size = Coord(0);
    for (long i = 0; i < n; i++)
    {
    r = GraphicImpl::requirement(requests[i], a);
    if (r->defined)
    {
        natural += r->natural;
        max_size += r->maximum;
        min_size += r->minimum;
    }
    }
    r = GraphicImpl::requirement(result, a);
    r->defined = true;
    r->natural = natural;
    r->maximum = max_size;
    r->minimum = min_size;
    r->align = align;
}

void LayoutTile::compute_allocations(Axis axis,
                     Graphic::Requisition &total,
                     bool first_aligned, long n,
                     Graphic::Requisition *requests,
                     Region_ptr given,
                     LayoutManager::Allocations result)
{
    Graphic::Requirement *r = GraphicImpl::requirement(total, axis);
    Region::Allotment a;
    given->span(axis, a);
    Coord length = compute_length(*r, a);
    bool growing = length > r->natural;
    bool shrinking = length < r->natural;
    Coord f = compute_squeeze(*r, length);
    Coord p = a.begin + a.align * (a.end - a.begin);
    for (long i = 0; i < n; i++)
    {
    r = GraphicImpl::requirement(requests[i], axis);
    if (r->defined)
    {
        Coord cspan = r->natural;
        if (growing) cspan += f * (r->maximum - r->natural);
        else if (shrinking) cspan -= f * (r->natural - r->minimum);
        if (first_aligned && i == 0) p -= r->align * cspan;
        set_span(result[i], axis, p + cspan * r->align, cspan, 
             r->align);
        p += cspan;
        }
    else set_span(result[i], axis, p, Coord(0), Coord(0));
    }
}

Coord LayoutTile::compute_length(const Graphic::Requirement &r,
                 const Region::Allotment &a)
{
    Coord length = a.end - a.begin;
    Coord s_a = a.align;
    Coord r_a = r.align;
    if (r_a == 0) length *= (1 - s_a);
    else if (r_a == 1) length *= s_a;
    else length *= Math::min(s_a / r_a, (1 - s_a) / (1 - r_a));
    return length;
}

Coord LayoutTile::compute_squeeze(const Graphic::Requirement &r,
                  Coord length)
{
    Coord f;
    Coord nat = r.natural;
    if (length > nat && r.maximum > nat)
    f = (length - nat) / (r.maximum - nat);
    else if (length < nat && r.minimum < nat)
    f = (nat - length) / (nat - r.minimum);
    else f = 0.0;
    return f;
}

// class LayoutTileReversed
LayoutTileReversed::LayoutTileReversed(Axis a) : my_axis(a) { }
LayoutTileReversed::~LayoutTileReversed() { }
LayoutManager *LayoutTileReversed::clone()
{ return new LayoutTileReversed(my_axis);}

void LayoutTileReversed::request(long n, Graphic::Requisition *requests,
                 Graphic::Requisition &result)
{
    LayoutTile::compute_request(my_axis, Alignment(1), n,
                requests, result);
    my_requisition = result;
}

void LayoutTileReversed::allocate(long n, Graphic::Requisition *requests,
                  Region_ptr given,
                  LayoutManager::Allocations result)
{
    compute_reversed_allocations(my_axis, my_requisition, false, n,
                 requests, given, result);
}

void LayoutTileReversed::compute_reversed_allocations(Axis axis,
                              Graphic::Requisition &total, bool first_aligned,
                              long n, 
                              Graphic::Requisition *requests,
                              Region_ptr given,
                              LayoutManager::Allocations result)
{
    Graphic::Requirement *r;
    Region::Allotment a;
    r = GraphicImpl::requirement(total, axis);
    given->span(axis, a);
    Coord length = LayoutTile::compute_length(*r, a);
    bool growing = length > r->natural;
    bool shrinking = length < r->natural;
    Coord f = LayoutTile::compute_squeeze(*r, length);
    Coord p = a.begin + a.align * (a.end - a.begin);
    for (long i = 0; i < n; i++)
    {
    r = GraphicImpl::requirement(requests[i], axis);
    if (r->defined)
    {
        Coord cspan = r->natural;
        if (growing) cspan += f * (r->maximum - r->natural);
        else if (shrinking) cspan -= f * (r->natural - r->minimum);
        if (first_aligned && i == 0) p += (1 - r->align) * cspan;
        p -= cspan;
        set_span(result[i], axis, p + r->align * cspan, cspan,
             r->align);
        }
    else set_span(result[i], axis, p, Coord(0), Coord(0));
    }
}

// class LayoutTileFirstAligned
LayoutTileFirstAligned::LayoutTileFirstAligned(Axis a) : my_axis(a) { }
LayoutTileFirstAligned::~LayoutTileFirstAligned() { }
LayoutManager *LayoutTileFirstAligned::clone()
{ return new LayoutTileFirstAligned(my_axis); }

void LayoutTileFirstAligned::request(long n,
                     Graphic::Requisition *requests,
                     Graphic::Requisition &result)
{
    compute_request_first_aligned(my_axis, n, requests, result);
    my_requisition = result;
}

void LayoutTileFirstAligned::allocate(long n,
                      Graphic::Requisition *requests,
                      Region_ptr given,
                      LayoutManager::Allocations result)
{
    LayoutTile::compute_allocations(my_axis, my_requisition, true, n,
                    requests, given, result);
}

void LayoutTileFirstAligned::compute_request_first_aligned(Axis a, long n,
                               Graphic::Requisition *requests,
                               Graphic::Requisition &result)
{
    Graphic::Requirement *r;
    Coord natural_lead = Coord(0);
    Coord min_lead = Coord(0);
    Coord max_lead = Coord(0);
    Coord natural_trail = Coord(0);
    Coord min_trail = Coord(0);
    Coord max_trail = Coord(0);
    for (long i = 0; i < n; i++)
    {
    r = GraphicImpl::requirement(requests[i], a);
    if (r->defined)
    {
        if (i == 0)
        {
        Alignment a = r->align;
        Alignment aa = 1 - a;
        natural_lead = a * r->natural;
        max_lead = a * r->maximum;
        min_lead = a * r->minimum;
        natural_trail = aa * r->natural;
        max_trail = aa * r->maximum;
        min_trail = aa * r->minimum;
            }
        else
        {
        natural_trail += r->natural;
        max_trail += r->maximum;
        min_trail += r->minimum;
            }
        }
    }
    r = GraphicImpl::requirement(result, a);
    GraphicImpl::require_lead_trail(*r, natural_lead, max_lead, min_lead,
                    natural_trail, max_trail, min_trail);
}

// class LayoutTileReversedFirstAligned
LayoutTileReversedFirstAligned::LayoutTileReversedFirstAligned(Axis a) :
    my_axis(a)
{ }
LayoutTileReversedFirstAligned::~LayoutTileReversedFirstAligned() { }
LayoutManager *LayoutTileReversedFirstAligned::clone()
{ return new LayoutTileReversedFirstAligned(my_axis); }

void LayoutTileReversedFirstAligned::request(long n,
                         Graphic::Requisition *requests,
                         Graphic::Requisition &result)
{
    LayoutTileFirstAligned::compute_request_first_aligned(my_axis, n,
                              requests,
                              result);
    my_requisition = result;
}

void LayoutTileReversedFirstAligned::allocate(long n,
                          Graphic::Requisition *requests,
                          Region_ptr given,
                          LayoutManager::Allocations result)
{
    LayoutTileReversed::compute_reversed_allocations(my_axis,
                             my_requisition,
                             true, n, requests,
                             given, result);
}

// class LayoutVariable
LayoutVariable::LayoutVariable(Axis a, Coord S, Coord s) :
    my_axis(a), my_stretch(S), my_shrink(s)
{ }
LayoutVariable::~LayoutVariable() { }
LayoutManager *LayoutVariable::clone()
{ return new LayoutVariable(my_axis, my_stretch, my_shrink); }

void LayoutVariable::request(long, Graphic::Requisition *,
                 Graphic::Requisition &result)
{
    Graphic::Requirement *r = GraphicImpl::requirement(result, my_axis);
    r->maximum = r->natural + my_stretch;
    r->minimum = r->natural - my_shrink;
}

void LayoutVariable::allocate(long, Graphic::Requisition *,
                  Region_ptr, LayoutManager::Allocations)
{ } // leave it as is
