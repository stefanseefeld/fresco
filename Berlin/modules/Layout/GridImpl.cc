/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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
#include "Layout/GridImpl.hh"
#include "Layout/LayoutManager.hh"
#include "Layout/Placement.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/Math.hh"
#include "Berlin/Memory.hh"

// Span

static void setSpan(GridImpl::Span &s, Coord origin, Coord length, Alignment align)
{
  Coord begin = origin - length * align;
  Coord end = begin + length;
  s.lower = begin;
  s.upper = end;
  s.align = align;
}

static void spansToRegion(GridImpl::Span &x_span, GridImpl::Span &y_span, RegionImpl *r)
{
  r->valid = true;
  r->lower.x = x_span.lower;
  r->upper.x = x_span.upper;
  r->xalign = x_span.align;
  r->lower.y = y_span.lower;
  r->upper.y = y_span.upper;
  r->yalign = y_span.align;
}

static void offsetRegion(RegionImpl *r, Coord dx, Coord dy)
{
  r->lower.x += dx;
  r->upper.x += dx;
  r->lower.y += dy;
  r->upper.y += dy;
}

class LayoutAlignRequest
{
public:
  LayoutAlignRequest();
  
  void margin(Coord margin);
  
  void accumulate(const Graphic::Requirement &r);
  void requirement(Graphic::Requirement &r) const;
 
protected:
  Coord natural_lead;
  Coord min_lead;
  Coord max_lead;
  Coord natural_trail;
  Coord min_trail;
  Coord max_trail;
};
 
LayoutAlignRequest::LayoutAlignRequest()
  : natural_lead(0), min_lead(-GraphicImpl::infinity), max_lead(GraphicImpl::infinity),
    natural_trail(0), min_trail(-GraphicImpl::infinity), max_trail(GraphicImpl::infinity)
{
}
 
void LayoutAlignRequest::margin(Coord margin)
{
  natural_lead += margin;
  min_lead -= margin;
  max_lead += margin;
  natural_trail += margin;
  min_trail -= margin;
  max_trail += margin;
}
 
void LayoutAlignRequest::accumulate(const Graphic::Requirement &r)
{
  if (r.defined)
    {
      Coord r_nat = r.natural;
      Coord r_max = r.maximum;
      Coord r_min = r.minimum;
      Coord r_align = r.align;
      Coord r_inv_align = Coord(1) - r_align;
      natural_lead = Math::max(natural_lead, Coord(r_nat * r_align));
      max_lead = Math::min(max_lead, Coord(r_max * r_align));
      min_lead = Math::max(min_lead, Coord(r_min * r_align));
      natural_trail = Math::max(natural_trail, Coord(r_nat * r_inv_align));
      max_trail = Math::min(max_trail, Coord(r_max * r_inv_align));
      min_trail = Math::max(min_trail, Coord(r_min * r_inv_align));
    }
}
 
void LayoutAlignRequest::requirement(Graphic::Requirement &r) const
{
  GraphicImpl::requireLeadTrail(r, natural_lead, max_lead, min_lead, natural_trail, max_trail, min_trail);
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
 
LayoutTileRequest::LayoutTileRequest() : natural(0), min_size(0), max_size(0) {}

void LayoutTileRequest::space(Coord space)
{
  natural += space;
  max_size += space;
  min_size += space;
}
 
void LayoutTileRequest::flexible()
{
  max_size = GraphicImpl::infinity;
}
 
void LayoutTileRequest::accumulate(const Graphic::Requirement &r)
{
  if (r.defined)
    {
      natural += r.natural;
      max_size += r.maximum;
      min_size += r.minimum;
    }
}
 
void LayoutTileRequest::requirement(Graphic::Requirement &r) const
{
  r.defined = true;
  r.natural = natural;
  r.maximum = max_size;
  r.minimum = min_size;
  r.align = Alignment(0);
}

class LayoutTileAllocate
{
public:
  LayoutTileAllocate(Axis, Graphic::Requisition &, bool, Region_ptr);

  static Coord computeLength(const Graphic::Requirement &, const Region::Allotment &);
  static double computeSqueeze(const Graphic::Requirement &, Coord);

  void nextSpan(const Graphic::Requirement &, GridImpl::Span &);

private:
  bool first_aligned;
  bool growing;
  bool shrinking;
  Coord f;
  Coord p;
  long i;
};

LayoutTileAllocate::LayoutTileAllocate(Axis axis, Graphic::Requisition &total, bool fa, Region_ptr given)
{
  first_aligned = fa;
  Graphic::Requirement *r;
  Region::Allotment a;
  r = GraphicImpl::requirement(total, axis);
  given->span(axis, a);
  Coord length = computeLength(*r, a);
  growing = length > r->natural;
  shrinking = length < r->natural;
  f = computeSqueeze(*r, length);
  p = a.begin + a.align * (a.end - a.begin);
  i = 0;
}

Coord LayoutTileAllocate::computeLength(const Graphic::Requirement &r, const Region::Allotment &a)
{
  Coord length = a.end - a.begin;
  Coord a_a = a.align;
  Coord r_a = r.align;
  if (r_a == 0) length *= (1 - a_a);
  else if (r_a == 1) length *= a_a;
  else length *= Math::min(a_a / r_a, (1 - a_a) / (1 - r_a));
  return length;
}
 
double LayoutTileAllocate::computeSqueeze(const Graphic::Requirement &r, Coord length)
{
  double f;
  Coord nat = r.natural;
  if (length > nat && r.maximum > nat) f = (length - nat) / (r.maximum - nat);
  else if (length < nat && r.minimum < nat) f = (nat - length) / (nat - r.minimum);
  else f = 0.0;
  return f;
}

void LayoutTileAllocate::nextSpan(const Graphic::Requirement &r, GridImpl::Span &s)
{
  if (r.defined)
    {
      Coord cspan = r.natural;
      if (growing) cspan += f * (r.maximum - r.natural);
      else if (shrinking) cspan -= f * (r.natural - r.minimum);
      if (first_aligned && (i == 0)) p -= r.align * cspan;
      setSpan(s, p + cspan * r.align, cspan, r.align);
      p += cspan;
    }
  else setSpan(s, p, Coord(0), Alignment(0));
  ++i;
}

GridImpl::GridImpl(const Grid::Index &upper)
{
  dimensions[xaxis].initialize(upper.col);
  dimensions[yaxis].initialize(upper.row);
  
  cursor.col = cursor.row = 0;
  
  requested = false;
  GridImpl::initRequisition(requisition);
}

GridImpl::~GridImpl()
{
  GridDimension &d = dimensions[int(yaxis)];
  for (long i = 0; i < d.count; ++i)
    {
      GridOffset* next;
      for (GridOffset *o = d.offsets[i]; o; o = next)
	{
	  next = o->next(xaxis);
	  CORBA::release(o);
	}
    }
}

void GridImpl::request(Requisition &r)
{
  cacheRequest();
  r = requisition;
}

void GridImpl::traverse(Traversal_ptr t)
{
  Grid::Range range;
  range.lower.col = 0;
  range.upper.col = dimensions[static_cast<int>(xaxis)].count;
  range.lower.row = 0;
  range.upper.row = dimensions[static_cast<int>(yaxis)].count;
  
  traverseRange(t, range);
}

void GridImpl::append(Graphic_ptr g)
{
  replace(g, cursor);
  
  if (++cursor.col >= dimensions[static_cast<int>(xaxis)].count)
    {
      long count = dimensions[static_cast<int>(yaxis)].count;
      cursor.row = (cursor.row + 1) % count;
      cursor.col = 0;
  }
}

void GridImpl::prepend(Graphic_ptr g)
{
  if (--cursor.col < 0)
    {
      long count = dimensions[static_cast<int>(yaxis)].count;
      cursor.row = (cursor.row - 1 + count) % count;
      cursor.col = dimensions[static_cast<int>(xaxis)].count - 1;
    }
}

void GridImpl::needResize()
{
  requested = false;
  GraphicImpl::needResize();
}

void GridImpl::replace(Graphic_ptr g, const Grid::Index &i)
{
//   fresco_assert((0 <= i.col) && (i.col < dimensions_[int(xaxis)].count_));
//   fresco_assert((0 <= i.row) && (i.row < dimensions_[int(yaxis)].count_));

  GridOffset *offset = g ? new GridOffset(this, g, i) : 0;

  GridOffset **o;
  o = &dimensions[static_cast<int>(xaxis)].offsets[i.col];
  for (; *o && ((*o)->index.row < i.row); o = &(*o)->next(yaxis))
    {
    }
  GridOffset *r = *o && ((*o)->index.row == i.row) ? *o : 0;
  if (offset != 0)
    {
      if (r != 0) offset->next(yaxis) = r->next(yaxis);
      else	  offset->next(yaxis) = *o;
    }
  *o = offset;

  o = &dimensions[static_cast<int>(yaxis)].offsets[i.row];
  for (; *o && ((*o)->index.col < i.col); o = &(*o)->next(xaxis))
    {
    }
  if (offset != 0)
    {
      if (r != 0)
	{
// 	  fresco_assert(r == *o);
	  offset->next(xaxis) = r->next(xaxis);
        }
      else offset->next(xaxis) = *o;
    }
  *o = offset;

  CORBA::release(r);
}

Grid::Index GridImpl::find(Traversal_ptr t)
{
  Grid::Range range;
  range.lower.col = 0;
  range.upper.col = dimensions[static_cast<int>(xaxis)].count;
  range.lower.row = 0;
  range.upper.row = dimensions[static_cast<int>(yaxis)].count;
  
  return findRange(t, range);
}

void GridImpl::allocateCell(Region_ptr given, const Grid::Index &i, Region_ptr a)
{
  Span *x_spans = fullAllocate(xaxis, given);
  Span *y_spans = fullAllocate(yaxis, given);
  RegionImpl r;
  spansToRegion(x_spans[i.col], y_spans[i.row], &r);
  a->copy(&r);
  delete [] x_spans;
  delete [] y_spans;
}

void GridImpl::requestRange(Graphic::Requisition &r, const Grid::Range &a)
{
  cacheRequest();
  
  partialRequest(xaxis, a.lower.col, a.upper.col, r.x);
  partialRequest(yaxis, a.lower.row, a.upper.row, r.y);
}

void GridImpl::traverseRange(Traversal_ptr t, const Grid::Range &a)
{
  Region_var given = t->allocation();
  if (!CORBA::is_nil(given))
    {
      if (t->intersects())
	traverseWithAllocation(t, given, a);
    }
  else
    traverseWithoutAllocation(t, a);
}

Grid::Index GridImpl::findRange(Traversal_ptr t, const Grid::Range &a)
{
  Region_var given = t->allocation();
  Span *x_spans = fullAllocate(xaxis, given);
  Span *y_spans = fullAllocate(yaxis, given);
//   Painter_var p = t->current_painter();
//   Region_var e = p->visible();
  Vertex lower, upper;
//   e->bounds(lower, upper);
  Coord x = lower.x;
  Coord y = lower.y;
  // If the point is outside the range find the outermost cell.
  long c, r;
  for (c = a.lower.col; c < (a.upper.col - 1); ++c)
    if (x <= x_spans[c].upper) break;
  for (r = a.lower.row; r < (a.upper.row - 1); ++r)
    if (y <= y_spans[r].upper) break;
  Grid::Index index;
  index.col = c;
  index.row = r;
  delete [] x_spans;
  delete [] y_spans;
  return index;
}

void GridImpl::rangePosition(Region_ptr given, const Grid::Range &a, Vertex &pos)
{
  Span *x_spans = fullAllocate(xaxis, given);
  Span *y_spans = fullAllocate(yaxis, given);
  pos.x = x_spans[0].lower - x_spans[a.lower.col].lower;
  pos.y = y_spans[0].lower - y_spans[a.lower.row].lower;
  pos.z = Coord(0);
  delete [] x_spans;
  delete [] y_spans;
}

Grid::Index GridImpl::upper()
{
  Grid::Index upper;
  upper.col = dimensions[static_cast<int>(xaxis)].count;
  upper.row = dimensions[static_cast<int>(yaxis)].count;
  return upper;
}

/* Child_allocate doesn't consider range. Thus if this grid is a child
 * of a glyph traversing a range, then we expect that glyph's
 * offset will define child_allocate to adjust for the range position.
 */

void GridImpl::allocateChild(Graphic::AllocationInfo &a, Grid::Index index)
{
  TransformImpl tx;
  allocateCell(a.allocation, index, a.allocation);
  RegionImpl r(a.allocation, 0);
  Placement::normalTransform(&r, &tx);
  a.allocation->copy(&r);
  if (CORBA::is_nil(a.transformation))
    a.transformation = new TransformImpl;
  a.transformation->premultiply(&tx);
}

void GridImpl::cacheRequest()
{
  if (! requested)
    {
      fullRequest(xaxis, yaxis);
      fullRequest(yaxis, xaxis);
      requested = true;
    }
}

void GridImpl::partialRequest(Axis axis, long begin, long end, Graphic::Requirement &r)
{
  GridDimension &d = dimensions[static_cast<int>(axis)];
  LayoutTileRequest tile;
  for (long i = begin; i < end; ++i)
    tile.accumulate(d.requirements[i]);
  tile.requirement(r);
}

void GridImpl::fullRequest(Axis axis, Axis direction)
{
  GridDimension &d = dimensions[static_cast<int>(axis)];
  LayoutTileRequest tile;
  for (int i = 0; i < d.count; ++i)
    {
      LayoutAlignRequest align;
      for (GridOffset *o = d.offsets[i]; o; o = o->next(direction))
	align.accumulate(o->requirement(axis));
      Graphic::Requirement &r = d.requirements[i];
      align.requirement(r);
      tile.accumulate(r);
    }
  Graphic::Requirement &r = *GraphicImpl::requirement(requisition, axis);
  tile.requirement(r);
}

GridImpl::Span *GridImpl::fullAllocate(Axis axis, Region_ptr given)
{
  GridDimension &d = dimensions[static_cast<int>(axis)];
  Span *spans = new Span[d.count];
  LayoutTileAllocate allocate(axis, requisition, false, given);
  for (int i = 0; i < d.count; ++i)
    allocate.nextSpan(d.requirements[i], spans[i]);
  return spans;
}

void GridImpl::traverseWithAllocation(Traversal_ptr t, Region_ptr given, const Grid::Range &range)
{
//   Span *x_spans = fullAllocate(xaxis, given);
//   Span *y_spans = fullAllocate(yaxis, given);
//   Coord dx = x_spans[0].lower - x_spans[range.lower.col].lower;
//   Coord dy = y_spans[0].lower - y_spans[range.lower.row].lower;
//   TransformImpl tx;
//   Painter_var p = t->current_painter();
//   GridDimension& d = dimensions[static_cast<int>(yaxis)];
//   for (long i = range.lower.row; i < range.upper.row; ++i)
//     {
//       for (GridOffset *o = d.offsets[i]; o; o = o->next(xaxis))
// 	{
// 	  if ((range.lower.col <= o->index.col) &&
// 	      (o->index.col < range.upper.col)
// 	      )
// 	    {
// 	      p->push_matrix();
// 	      RegionImpl* r = new RegionImpl;
// 	      spans_to_region(x_spans[o->index_.col], y_spans[o->index_.row], r);
// 	      offset_region(r, dx, dy);
// 	      tx.load_identity();
// 	      Placement::normal_transform(r, &tx);
// 	      p->premultiply(&tx);
// 	      t->traverse_child(o, r);
// 	      CORBA::release(r);
// 	      p->pop_matrix();
//             }
//         }
//     }
//   delete [] x_spans;
//   delete [] y_spans;
}

void GridImpl::traverseWithoutAllocation(Traversal_ptr t, const Grid::Range &range)
{
  GridDimension& d = dimensions[static_cast<int>(yaxis)];
  for (long i = range.lower.row; i < range.upper.row; ++i) {
    for (GridOffset *o = d.offsets[i]; o; o = o->next(xaxis))
      {
	if ((range.lower.col <= o->index.col) &&
	    (o->index.col < range.upper.col))
	  t->traverseChild(o, 0, 0);
    }
  }
}

GridOffset::GridOffset(GridImpl *parent, Graphic_ptr child, Grid::Index index)
{
  parent = parent;
  child = Graphic::_duplicate(child);
  index = index;
  child->addParent(_this());
}

GridOffset::~GridOffset() { child->removeParent(_this());}
 
Graphic::Requirement GridOffset::requirement(Axis axis)
{
  Graphic::Requisition r;
  GraphicImpl::initRequisition(r);
  GraphicImpl::defaultRequisition(r);
  child->request(r);
  return (axis==xaxis) ? r.x : r.y;
}
 
Graphic_ptr GridOffset::Parent() { return Grid::_duplicate(parent);}
Graphic_ptr GridOffset::Child() { return Graphic::_duplicate(child);}
GraphicOffset_ptr GridOffset::next() { return 0;}
GraphicOffset_ptr GridOffset::previous() { return 0;}

void GridOffset::allocations(Collector_ptr c)
{
  long start = c->size();
  parent->allocations(c);
  for (long i = start; i < c->size(); i++)
    parent->allocateChild(*c->get(i), index);
}

void GridOffset::insert(Graphic_ptr) {}
void GridOffset::replace(Graphic_ptr) {}
void GridOffset::remove() {}
void GridOffset::needResize() { parent->needResize();}
void GridOffset::traverse(Traversal_ptr t) { child->traverse(t);}
void GridOffset::visit_trail(Traversal_ptr) {}
void GridOffset::allocateChild(Graphic::AllocationInfo &a) { parent->allocateChild(a, index);}

GridDimension::GridDimension() : count(0), offsets(0), requirements(0) {}
GridDimension::~GridDimension()
{
  delete [] offsets;
  delete [] requirements;
}

void GridDimension::initialize(long count)
{
  count = count;
  offsets = new GridOffset *[count];
  Memory::zero(offsets, sizeof(GridOffset *) *count);
  requirements = new Graphic::Requirement[count];
}

SubGridImpl::SubGridImpl(Grid_ptr grid, const Grid::Range &range)
{
  offset = new SubGridOffset(this, grid, range); 
}

SubGridImpl::~SubGridImpl()
{
  CORBA::release(offset);
}

void SubGridImpl::request(Requisition &r) { offset->request(r);}

void SubGridImpl::traverse(Traversal_ptr t)
{
  t->traverseChild(offset, t->allocation(), 0);
}
 
SubGridOffset::SubGridOffset(SubGridImpl *parent, Grid_ptr child, const Grid::Range &r)
  : range(r)
{
  parent = parent;
  child = Grid::_duplicate(child);
  child->addParent(_this());
}

SubGridOffset::~SubGridOffset() { child->removeParent(_this());}
Graphic_ptr SubGridOffset::Parent() { return SubGridImpl::_duplicate(parent);}
Graphic_ptr SubGridOffset::Child() { return Grid::_duplicate(child);}
GraphicOffset_ptr SubGridOffset::next() { return 0;}
GraphicOffset_ptr SubGridOffset::previous() { return 0;}

void SubGridOffset::allocations(Collector_ptr c)
{
  long start = c->size();
  parent->allocations(c);
  for (long i = start; i < c->size(); i++)
    allocateChild(*c->get(i));
}

void SubGridOffset::insert(Graphic_ptr) {}
void SubGridOffset::replace(Graphic_ptr) {}
void SubGridOffset::remove() {}
void SubGridOffset::needResize() { parent->needResize();}
void SubGridOffset::traverse(Traversal_ptr t) { child->traverseRange(t, range);}
void SubGridOffset::visit_trail(Traversal_ptr) {}

void SubGridOffset::allocateChild(Graphic::AllocationInfo &a)
{
  TransformImpl tx;
  RegionImpl r(a.allocation, 0);
  Placement::normalTransform(&r, &tx);
  Vertex v;
  child->rangePosition(a.allocation, range, v);
  tx.translate(v);
  a.allocation->copy(&r);
  if (CORBA::is_nil(a.transformation))
    a.transformation = new TransformImpl;
  a.transformation->premultiply(&tx);
}

void SubGridOffset::request(Graphic::Requisition &r)
{
  child->requestRange(r, range);
}
