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
#include <Fresco/IO.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/Provider.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/Math.hh>
#include "GridImpl.hh"
#include "LayoutManager.hh"

using namespace Prague;
using namespace Fresco;
using namespace Layout;

using namespace Berlin::LayoutKit;

namespace std
{
  std::ostream &operator << (std::ostream &os,
                 const GridImpl::Span &span)
  {
      return os << '(' << span.lower << ',' << span.upper
        << '@' << span.align << ')';
  }
} // namespace

static void set_span(GridImpl::Span &s, Coord origin, Coord length,
             Alignment align)
{
    Coord begin = origin - length * align;
    Coord end = begin + length;
    s.lower = begin;
    s.upper = end;
    s.align = align;
}

static inline void spans_to_region(GridImpl::Span &x_span,
                   GridImpl::Span &y_span,
                   Berlin::RegionImpl *r)
{
    r->valid = true;
    r->lower.x = x_span.lower;
    r->upper.x = x_span.upper;
    r->xalign = x_span.align;
    r->lower.y = y_span.lower;
    r->upper.y = y_span.upper;
    r->yalign = y_span.align;
}

static void offset_region(Berlin::RegionImpl *r, Coord dx, Coord dy)
{
    r->lower.x += dx;
    r->upper.x += dx;
    r->lower.y += dy;
    r->upper.y += dy;
}

namespace Berlin
{
  namespace LayoutKit
  {
    class LayoutAlignRequest
    {
      public:
        LayoutAlignRequest();
    
        void margin(Coord margin);
    
        void accumulate(const Graphic::Requirement &r);
        void requirement(Graphic::Requirement &r) const;
    
      protected:
        Coord my_natural_lead;
        Coord my_min_lead;
        Coord my_max_lead;
        Coord my_natural_trail;
        Coord my_min_trail;
        Coord my_max_trail;
    };

    LayoutAlignRequest::LayoutAlignRequest() :
      my_natural_lead(0),
      my_min_lead(-GraphicImpl::infinity),
      my_max_lead(GraphicImpl::infinity),
      my_natural_trail(0),
      my_min_trail(-GraphicImpl::infinity),
      my_max_trail(GraphicImpl::infinity)
    { }

    void LayoutAlignRequest::margin(Coord margin)
    {
        my_natural_lead += margin;
        my_min_lead -= margin;
        my_max_lead += margin;
        my_natural_trail += margin;
        my_min_trail -= margin;
        my_max_trail += margin;
    }

    void LayoutAlignRequest::accumulate(const Graphic::Requirement &r)
    {
        if (!r.defined) return;

        Coord r_nat = r.natural;
        Coord r_max = r.maximum;
        Coord r_min = r.minimum;
        Coord r_align = r.align;
        Coord r_inv_align = Coord(1) - r_align;
        my_natural_lead = Math::max(my_natural_lead,
                    Coord(r_nat * r_align));
        my_max_lead = Math::min(my_max_lead, Coord(r_max * r_align));
        my_min_lead = Math::max(my_min_lead, Coord(r_min * r_align));
        my_natural_trail = Math::max(my_natural_trail,
                     Coord(r_nat * r_inv_align));
        my_max_trail = Math::min(my_max_trail, Coord(r_max * r_inv_align));
        my_min_trail = Math::max(my_min_trail, Coord(r_min * r_inv_align));
    }

    void LayoutAlignRequest::requirement(Graphic::Requirement &r) const
    {
        GraphicImpl::require_lead_trail(r,
                                        my_natural_lead, my_max_lead,
                    my_min_lead, my_natural_trail,
                    my_max_trail, my_min_trail);
    }

    class LayoutTileRequest
    {
      public:
        LayoutTileRequest();
    
        void space(Coord space);
        void flexible();

        void accumulate(const Graphic::Requirement &r);
        void requirement(Graphic::Requirement &r) const;

        Coord natural;
        Coord min_size;
        Coord max_size;
    };

    LayoutTileRequest::LayoutTileRequest() :
    natural(0), min_size(0), max_size(0) 
    { }

    void LayoutTileRequest::space(Coord space)
    {
        natural += space;
        max_size += space;
        min_size += space;
    }

    void LayoutTileRequest::flexible()
    { max_size = GraphicImpl::infinity; }

    void LayoutTileRequest::accumulate(const Graphic::Requirement &r)
    {
        if (!r.defined) return;
    
        natural += r.natural;
        max_size += r.maximum;
        min_size += r.minimum;
    }

    void LayoutTileRequest::requirement(Graphic::Requirement &r) const
    {
        r.defined = true;
        r.natural = natural;
        r.maximum = max_size;
        r.minimum = min_size;
        r.align = 0.;
    }

    class LayoutTileAllocate
    {
      public:
        LayoutTileAllocate(Axis, Graphic::Requisition &, bool, Region_ptr);

        static Coord compute_length(const Graphic::Requirement &,
                                    const Region::Allotment &);
        static double compute_squeeze(const Graphic::Requirement &, Coord);

        void next_span(const Graphic::Requirement &, GridImpl::Span &);

      private:
        bool my_first_aligned;
        bool my_growing;
        bool my_shrinking;
        Coord my_f;
        Coord my_p;
        long my_i;
    };

    LayoutTileAllocate::LayoutTileAllocate(Axis axis,
                                           Graphic::Requisition &total,
                       bool fa,
                                           Region_ptr given)
    {
        my_first_aligned = fa;
        Graphic::Requirement *r;
        Region::Allotment a;
        r = GraphicImpl::requirement(total, axis);
        given->span(axis, a);
        Coord length = compute_length(*r, a);
        my_growing = length > r->natural;
        my_shrinking = length < r->natural;
        my_f = compute_squeeze(*r, length);
        my_p = a.begin + a.align * (a.end - a.begin);
        my_i = 0;
    }

    Coord LayoutTileAllocate::compute_length(const Graphic::Requirement &r,
                                             const Region::Allotment &a)
    {
        Coord length = a.end - a.begin;
        Coord a_a = a.align;
        Coord r_a = r.align;
        if (r_a == 0) length *= (1 - a_a);
        else if (r_a == 1) length *= a_a;
        else length *= Math::min(a_a / r_a, (1 - a_a) / (1 - r_a));
        return length;
    }

    double LayoutTileAllocate::compute_squeeze(const Graphic::Requirement &r,
                                               Coord length)
    {
        double f;
        Coord nat = r.natural;
        if (length > nat && r.maximum > nat)
        f = (length - nat) / (r.maximum - nat);
        else if (length < nat && r.minimum < nat)
            f = (nat - length) / (nat - r.minimum);
        else f = 0.0;
        return f;
    }

    void LayoutTileAllocate::next_span(const Graphic::Requirement &r,
                                       GridImpl::Span &s)
    {
        if (r.defined)
        {
            Coord cspan = r.natural;
            if (my_growing) cspan += my_f * (r.maximum - r.natural);
            else if (my_shrinking) cspan -= my_f * (r.natural - r.minimum);
            if (my_first_aligned && (my_i == 0))
        my_p -= r.align * cspan;
            set_span(s, my_p + cspan * r.align, cspan, r.align);
            my_p += cspan;
        }
        else set_span(s, my_p, Coord(0), Alignment(0));
        ++my_i;
    }
  } // namespace
} // namespace

GridImpl::GridImpl(const Layout::Grid::Index &upper)
{
    my_dimensions[xaxis].init(upper.col, upper.row);
    my_dimensions[yaxis].init(upper.row, upper.col);
    my_cursor.col = my_cursor.row = 0;
    my_requested = false;
    GridImpl::init_requisition(my_requisition);
}

GridImpl::~GridImpl() { }

void GridImpl::append_graphic(Graphic_ptr g)
{
    replace(g, my_cursor);

    if (++my_cursor.col >= my_dimensions[xaxis].size())
    {
    long count = my_dimensions[yaxis].size();
    my_cursor.row = (my_cursor.row + 1) % count;
    my_cursor.col = 0;
    }
}

void GridImpl::prepend_graphic(Graphic_ptr g)
{
  if (--my_cursor.col < 0)
  {
      long count = my_dimensions[yaxis].size();
      my_cursor.row = (my_cursor.row - 1 + count) % count;
      my_cursor.col = my_dimensions[xaxis].size() - 1;
  }
  replace(g, my_cursor);
}

void GridImpl::request(Fresco::Graphic::Requisition &r)
{
    cache_request();
    r = my_requisition;
}

void GridImpl::traverse(Traversal_ptr traversal)
{
    Layout::Grid::Range range;
    range.lower.col = 0;
    range.upper.col = my_dimensions[xaxis].size();
    range.lower.row = 0;
    range.upper.row = my_dimensions[yaxis].size();

    traverse_range(traversal, range);
}

void GridImpl::need_resize()
{
    my_requested = false;
    GraphicImpl::need_resize();
}

void GridImpl::replace(Graphic_ptr g, const Layout::Grid::Index &i)
{
    // use at(n) for ranged checked access throws out_of_range
    Graphic_ptr old = my_dimensions[xaxis].children.at(i.col).at(i.row);
    if (!CORBA::is_nil(old))
    try
    { old->remove_parent_graphic(index_to_tag(i)); }
    catch (const CORBA::OBJECT_NOT_EXIST &) { }
    catch (const CORBA::COMM_FAILURE &) { }
    catch (const CORBA::TRANSIENT &) { }
    my_dimensions[xaxis].children[i.col][i.row] = 
    Fresco::Graphic::_duplicate(g);
    my_dimensions[yaxis].children[i.row][i.col] = 
    Fresco::Graphic::_duplicate(g);
    g->add_parent_graphic(Graphic_var(_this()), index_to_tag(i));
}

Layout::Grid::Index GridImpl::find(Traversal_ptr traversal)
{
    Layout::Grid::Range range;
    range.lower.col = 0;
    range.upper.col = my_dimensions[xaxis].size();
    range.lower.row = 0;
    range.upper.row = my_dimensions[yaxis].size();
    
    return find_range(traversal, range);
}

void GridImpl::allocate_cell(Region_ptr given,
                 const Layout::Grid::Index &i, Region_ptr a)
{
    Span *xspans = full_allocate(xaxis, given);
    Span *yspans = full_allocate(yaxis, given);

    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    spans_to_region(xspans[i.col], yspans[i.row], region);
    a->copy(Region_var(region->_this()));
    delete [] xspans;
    delete [] yspans;
}

void GridImpl::request_range(Fresco::Graphic::Requisition &r,
                 const Layout::Grid::Range &a)
{
    cache_request();
  
    partial_request(xaxis, a.lower.col, a.upper.col, r.x);
    partial_request(yaxis, a.lower.row, a.upper.row, r.y);
}

void GridImpl::traverse_range(Traversal_ptr traversal,
                  const Layout::Grid::Range &a)
{
    Region_var given = traversal->current_allocation();
    if (!CORBA::is_nil(given))
    {
    if (traversal->intersects_allocation())
        traverse_with_allocation(traversal, given, a);
    }
    else
    traverse_without_allocation(traversal, a);
}

Layout::Grid::Index GridImpl::find_range(Traversal_ptr traversal,
                     const Layout::Grid::Range &a)
{
    Region_var given = traversal->current_allocation();
    Span *xspans = full_allocate(xaxis, given);
    Span *yspans = full_allocate(yaxis, given);
    Vertex lower;//, upper;
//    e->bounds(lower, upper);
    Coord x = lower.x;
    Coord y = lower.y;
    // If the point is outside the range find the outermost cell.
    long c, r;
    for (c = a.lower.col; c < (a.upper.col - 1); c++)
    if (x <= xspans[c].upper) break;
    for (r = a.lower.row; r < (a.upper.row - 1); r++)
    if (y <= yspans[r].upper) break;
    Layout::Grid::Index index;
    index.col = c;
    index.row = r;
    delete [] xspans;
    delete [] yspans;
    return index;
}

void GridImpl::range_position(Region_ptr given,
                  const Layout::Grid::Range &a, Vertex &pos)
{
    Span *xspans = full_allocate(xaxis, given);
    Span *yspans = full_allocate(yaxis, given);
    pos.x = xspans[0].lower - xspans[a.lower.col].lower;
    pos.y = yspans[0].lower - yspans[a.lower.row].lower;
    pos.z = 0.;
    delete [] xspans;
    delete [] yspans;
}

Layout::Grid::Index GridImpl::upper()
{
    Layout::Grid::Index upper;
    upper.col = my_dimensions[xaxis].size();
    upper.row = my_dimensions[yaxis].size();
    return upper;
}

namespace std
{
  std::ostream &operator << (std::ostream &os,
                 const Layout::Grid::Index &i)
  { return os << i.col << ' ' << i.row; }
} // namespace

void GridImpl::allocate(Tag tag, const Allocation::Info &info)
{
    Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
    tx->load_identity();
    allocate_cell(info.allocation, tag_to_index(tag), info.allocation);
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    region->copy(info.allocation);
    region->normalize(Transform_var(tx->_this()));
    info.allocation->copy(Region_var(region->_this()));
    info.transformation->premultiply(Transform_var(tx->_this()));
}

void GridImpl::cache_request()
{
    if (!my_requested)
    {
    full_request(xaxis, yaxis);
    full_request(yaxis, xaxis);
    my_requested = true;
    }
}

void GridImpl::partial_request(Axis axis, long begin, long end,
                   Fresco::Graphic::Requirement &r)
{
    Dimension &d = my_dimensions[axis];
    LayoutTileRequest tile;
    for (long i = begin; i < end; i++)
    tile.accumulate(d.requirements[i]);
    tile.requirement(r);
}

void GridImpl::full_request(Axis axis, Axis direction)
{
    Dimension &d = my_dimensions[axis];
    LayoutTileRequest tile;
    for (int i = 0; i < d.size(); i++)
    {
    LayoutAlignRequest align;
    for (std::vector<Graphic_var>::iterator j = d.children[i].begin();
         j != d.children[i].end();
         ++j)
        if (!CORBA::is_nil(*j))
        {
        Fresco::Graphic::Requisition r;
        GraphicImpl::init_requisition(r);
        GraphicImpl::default_requisition(r);
        (*j)->request(r);
        align.accumulate(axis == xaxis ? r.x : r.y);
        }
    Fresco::Graphic::Requirement &r = d.requirements[i];
    align.requirement(r);
    tile.accumulate(r);
    }
    Fresco::Graphic::Requirement &r = 
    *GraphicImpl::requirement(my_requisition, axis);
    tile.requirement(r);
}

GridImpl::Span *GridImpl::full_allocate(Axis axis, Region_ptr given)
{
    Dimension &d = my_dimensions[axis];
    Span *spans = new Span[d.size()];
    LayoutTileAllocate allocate(axis, my_requisition, false, given);
    for (int i = 0; i < d.size(); ++i)
    allocate.next_span(d.requirements[i], spans[i]);
    return spans;
}

void GridImpl::traverse_with_allocation(Traversal_ptr t,
                    Region_ptr given,
                    const Layout::Grid::Range &range)
{
    Span *xspans = full_allocate(xaxis, given);
    Span *yspans = full_allocate(yaxis, given);
    Coord dx = xspans[0].lower - xspans[range.lower.col].lower;
    Coord dy = yspans[0].lower - yspans[range.lower.row].lower;
    Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
    tx->load_identity();
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    Dimension &d = my_dimensions[yaxis];
    Layout::Grid::Index i;
    for (i.row = range.lower.row;
     i.row != range.upper.row && t->ok();
     ++i.row)
    for (i.col = range.lower.col;
         i.col != range.upper.col && t->ok();
         ++i.col)
    {
        Graphic_var child = d.children [i.row][i.col];
        if (CORBA::is_nil(child)) continue;
        tx->load_identity();
        spans_to_region(xspans[i.col], yspans[i.row], region);
        offset_region(region, dx, dy);
        region->normalize(Transform_var(tx->_this()));
        try
        { 
        t->traverse_child (child, index_to_tag(i),
                   Region_var(region->_this()),
                   Transform_var(tx->_this()));
        }
        catch (const CORBA::OBJECT_NOT_EXIST &)
        { d.children [i.row][i.col] = Fresco::Graphic::_nil(); }
        catch (const CORBA::COMM_FAILURE &)
        { d.children [i.row][i.col] = Fresco::Graphic::_nil(); }
        catch (const CORBA::TRANSIENT &)
        { d.children [i.row][i.col] = Fresco::Graphic::_nil(); }
    }
    delete [] xspans;
    delete [] yspans;
}

void
GridImpl::traverse_without_allocation(Traversal_ptr t,
                      const Layout::Grid::Range &range)
{
    Dimension &d = my_dimensions[yaxis];
    Layout::Grid::Index i;
    for (i.row = range.lower.row;
     i.row != range.upper.row && t->ok();
     ++i.row)
    for (i.col = range.lower.col;
         i.col != range.upper.col && t->ok();
         ++i.col)
    {
        Graphic_var child = d.children [i.row][i.col];
        if (CORBA::is_nil(child)) continue;
        try
        {
        t->traverse_child (child, index_to_tag(i), Region::_nil(),
                   Transform::_nil());
        }
        catch (const CORBA::OBJECT_NOT_EXIST &)
        { d.children [i.row][i.col] = Fresco::Graphic::_nil(); }
        catch (const CORBA::COMM_FAILURE &) 
        { d.children [i.row][i.col] = Fresco::Graphic::_nil(); }
        catch (const CORBA::TRANSIENT &)
        { d.children [i.row][i.col] = Fresco::Graphic::_nil(); }
    }
}

SubGridImpl::SubGridImpl(Grid_ptr grid, const Layout::Grid::Range &r) :
    my_child(Layout::Grid::_duplicate(grid)), my_range(r)
{ }

SubGridImpl::~SubGridImpl() { }
void SubGridImpl::request(Fresco::Graphic::Requisition &r)
{ my_child->request_range(r, my_range); }

void SubGridImpl::traverse(Traversal_ptr t)
{
    if (CORBA::is_nil(my_child)) return;
    try
    {
    t->traverse_child(my_child, 0, Region::_nil(), Transform::_nil());
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { my_child = Layout::Grid::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { my_child = Layout::Grid::_nil(); }
    catch (const CORBA::TRANSIENT &) 
    { my_child = Layout::Grid::_nil(); }
}

