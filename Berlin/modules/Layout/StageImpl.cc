/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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

#include <Layout/StageImpl.hh>
#include <Berlin/AllocationImpl.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/DebugGraphic.hh>
#include <Warsaw/Screen.hh>
#include <Berlin/Logger.hh>

using namespace Geometry;

void StageInfoImpl::cacheBBox()
{
  Graphic::Requisition r;
  GraphicImpl::initRequisition(r);    
  child->request(r);
  if (r.x.defined && r.y.defined)
    {
      xalign = r.x.align;
      yalign = r.y.align;
      if (size.x != 0)
	{
	  boundingbox.l = position.x;
	  boundingbox.r = position.x + size.x;
	}
      else
	{
	  boundingbox.l = position.x - r.x.natural * r.x.align;
	  boundingbox.r = position.x + r.x.natural * (1. - r.x.align);
	}
      if (size.y != 0)
	{
	  boundingbox.t = position.y;
	  boundingbox.b = position.y + size.y;
	}
      else
	{
	  boundingbox.t = position.y - r.y.natural * r.y.align;
	  boundingbox.b = position.y + r.y.natural * (1. - r.y.align);
	}
    }
  else
    {
      xalign = 0.;
      yalign = 0.;
      boundingbox.l = position.x;
      boundingbox.r = position.x;
      boundingbox.t = position.y;
      boundingbox.b = position.y;
    }
}

StageSequence::iterator StageSequence::lookup(Stage::Index layer)
{
  SectionLog section(Logger::layout, "StageSequence::lookup");
  if (layer == front()->layer) return begin();
  if (layer == back()->layer) return --end();
  if (layer == (*cursor)->layer) return cursor;

  /*
   * start searching from the closest item
   */
  int fdist = front()->layer - layer;
  int bdist = layer;
  int cdist = Math::abs((*cursor)->layer - layer);
  if (fdist < bdist)
    {
      if (fdist < cdist) cursor = begin();
    }
  else
    {
      if (bdist < cdist) cursor = --end();
    }

  int delta = layer - (*cursor)->layer;
  while (delta > 0) delta--, cursor++;
  while (delta < 0) delta++, cursor--;
  return cursor;
}

void StageSequence::insert(StageInfoImpl *info)
{
  int layer = info->layer;
  iterator i;
  if (!size() || layer == 0) i = begin();
  else if (front()->layer < layer) i = end();
  else i = lookup(layer);
  parent_t::insert(i++, info);
  for (i++; i != end(); i++) (*i)->layer = layer++;
}
 
void StageSequence::remove(StageInfoImpl *info)
{
  if (info == *cursor)
    if ((*cursor)->layer <= (front()->layer / 2)) cursor++;
    else cursor--;
//   int layer = info->layer;
//   if (item == front()) list::erase(--end());
//   if (item == back()) list::erase(begin());
//   int layer = item->layer_;
//   StageOffsetImpl *next = item->next();
//   item->unlink();
//   while (next)
//     {
//       next->layer_ = layer++;
//       next = next->next();
//     }
//   invariants();
}

StageQuad::StageQuad(const Rectangle<Coord> &region) : parent_t(region)
{
  SectionLog section(Logger::layout, "StageQuad::StageQuad(rectangle)");
}

/*
 * one child node is given; the other three are added inside
 */
StageQuad::StageQuad(const Rectangle<Coord> &r, StageQuad *node)
 : parent_t(r)
{
  SectionLog section(Logger::layout, "StageQuad::StageQuad(rectangle, StageQuad *)");
  elements = node->elements;
  boundingbox = node->boundingbox;

  const Rectangle<Coord> &b = node->region;
  int idx = none;

  /*
   * now determine in which directions we have to extend.
   * node becomes one of our children, the other three are added
   */
  Coord dl = b.l - r.l;
  Coord dr = r.r - b.r;
  if (dl < dr) { idx |= left; region.l = b.l; region.r = b.r + b.w();}
  else { idx |= right; region.l = b.l - b.w(); region.r = b.r;}

  Coord dt = b.t - r.t;
  Coord db = r.b - b.b;
  if (dt < db) { idx |= top; region.t = b.t; region.b = b.b + b.h();}
  else { idx |= bottom; region.t = b.t - b.h(); region.b = b.b;}

  quadrants[lefttop] =
    idx == lefttop ? node :
    new StageQuad(Rectangle<Coord>(region.l, region.t, region.cx(), region.cy()));
  quadrants[righttop] =
    idx == righttop ? node :
    new StageQuad(Rectangle<Coord>(region.cx(), region.t, region.r, region.cy()));
  quadrants[leftbottom] =
    idx == leftbottom ? node :
    new StageQuad(Rectangle<Coord>(region.l, region.cy(), region.cx(), region.b));
  quadrants[rightbottom] =
    idx == rightbottom ? node :
    new StageQuad(Rectangle<Coord>(region.cx(), region.cy(), region.r, region.b));
}

void StageQuad::within(const Rectangle<Coord> &r, StageFinder &finder)
{
  index idx = where(region);
  if (idx == fence)
    {
      for (list::iterator i = items.begin(); i != items.end(); i++)
	if ((*i)->bbox().within(r)) finder.found(*i);
      if (!leaf())
	{
	  if (r.r <= region.cx())
	    {
	      node(lefttop)->within(r, finder);
	      node(leftbottom)->within(r, finder);
	    }
	  else if (r.l > region.cx())
	    {
	      node(righttop)->within(r, finder);
	      node(rightbottom)->within(r, finder);
	    }
	  else if (r.b <= region.cy())
	    {
	      node(lefttop)->within(r, finder);
	      node(righttop)->within(r, finder);
	    }
	  else if (r.t > region.cy())
	    {
	      node(leftbottom)->within(r, finder);
	      node(rightbottom)->within(r, finder);
	    }
	  else for (int i = 0; i < 4; ++i) node(i)->within(r, finder);
	}
    }
  else node(idx)->within(r, finder);
}

void StageQuad::contains(const Point<Coord> &point, StageFinder &finder)
{
  for (list::iterator i = items.begin(); i != items.end(); i++)
    if ((*i)->bbox().contains(point))
      {
	/*
	  RegionImpl region;
	  (*i)->child->shape(region);
	  if (region->contains(point.x, point.y)) finder.found(*i);
	*/
	finder.found(*i);
      }
  if (!leaf()) node(where(point))->contains(point, finder);
}

void StageQuad::intersects(const Rectangle<Coord> &r, StageFinder &finder)
{
  for (list::iterator i = items.begin(); i != items.end(); i++)
    {
      if ((*i)->bbox().intersects(r))
	{
	  /*
	    RegionImpl shape;
	    (*i)->child->shape(region);
	    if (shape->intersects(region.l, region.b, region.r, region.t)) finder.found(item);
	  */
	  finder.found(*i);
	}
    }
  index idx = where(r);
  if (idx == fence)
    {
      if (!leaf())
	{
	  if (r.r <= region.cx())
	    {
	      node(leftbottom)->intersects(r, finder);
	      node(lefttop)->intersects(r, finder);
	    }
	  else if (r.l > region.cx())
	    {
	      node(rightbottom)->intersects(r, finder);
	      node(righttop)->intersects(r, finder);
	    }
	  else if (r.b <= region.cy())
	    {
	      node(lefttop)->intersects(r, finder);
	      node(righttop)->intersects(r, finder);
	    }
	  else if (r.t > region.cy())
	    {
	      node(leftbottom)->intersects(r, finder);
	      node(rightbottom)->intersects(r, finder);
	    }
	  else for (int i = 0; i < 4; ++i) node(i)->intersects(r, finder);
	}
    }
  else node(idx)->intersects(r, finder);
}

void StageQuad::intersects(const Rectangle<Coord> &r, const Polygon<Coord> &polygon, StageFinder &finder)
{
  for (list::iterator i = items.begin(); i != items.end(); i++)
    if (polygon.intersects((*i)->bbox()))
      {
	/*
	  RegionImpl shape;
	  Glyph_var(item->child())->shape(region);
	  if (shape->intersects(Geometry::Polygon)) finder.found(item);
	*/
	finder.found(*i);
      }
  index idx = where(r);
  if (idx == fence)
    {
      if (!leaf())
	{
	  /*
	   * shouldn't this read node(...)->intersects(s, polygon, finder) ??? -stefan
	   */
	  if (r.r <= region.cx())
	    {
	      node(leftbottom)->intersects(r, finder);
	      node(lefttop)->intersects(r, finder);
	    }
	  else if (r.l > region.cx())
	    {
	      node(rightbottom)->intersects(r, finder);
	      node(righttop)->intersects(r, finder);
	    }
	  else if (r.b <= region.cy())
	    {
	      node(lefttop)->intersects(r, finder);
	      node(righttop)->intersects(r, finder);
	    }
	  else if (r.t > region.cy())
	    {
	      node(leftbottom)->intersects(r, finder);
	      node(rightbottom)->intersects(r, finder);
	    }
	  else for (int i = 0; i < 4; i++) node(i)->intersects(r, finder);
	}
    }
  else node(idx)->intersects(r, finder);
}

void StageQuadTree::insert(StageInfoImpl *info)
{
  const Rectangle<Coord> &bbox = info->bbox();
  if (!node()) quad = new StageQuad(bbox);
  /*
   * FIXME: currently, this code inserts new nodes as long as the outermost
   *        doesn't completely contain the info's boundingbox. What if the
   *        given bbox is infinity ?? On the other hand, guessing too large
   *        values is tricky since we don't know the scale of this coordinate 
   *        system, so may be a limiting depth of the tree would be a solution.
   *                -stefan
   */
  else while (!bbox.within(node()->extension())) quad = new StageQuad(bbox, node());
  node()->insert(info);
}

void StageQuadTree::remove(StageInfoImpl *info)
{
  node()->remove(info);
}

void StageQuadTree::end()
{
  transaction--;
  if (transaction == 0)
    {
      /*
       * ??? every 32 operations adjust the StageQuad tree -denis
       */
      operations++;
      if (operations & 0x1f == 0)
	{
	  /*
	   * ??? desire min of 8, max of 32, smallest span of 16 -denis
	   */
	  node()->adjust(8, 32, 16, 16);
	}
    }
}

class StageQuadTreeContains : public StageFinder
{
public:
  StageQuadTreeContains(Traversal::order o) : info(0), order(o) {}
  virtual void found(StageInfoImpl *i)
    {
      if (!info ||
	  (order == Traversal::down && info->layer > i->layer) ||
	  info->layer < i->layer)
	info = i;
    }
  StageInfoImpl *info;
  Traversal::order order;
};

StageInfoImpl *StageQuadTree::contains(const Point<Coord> &point)
{
  StageInfoImpl *info = 0;
  if (node())
    {
      StageQuadTreeContains finder(Traversal::up);
      node()->contains(point, finder);
      info = finder.info;
    }
  return info;
}

void StageQuadTree::intersects(const Polygon<Coord> &polygon, StageFinder &finder)
{
  if (node())
    {
      Rectangle<Coord> bb;
      polygon.boundingBox(bb);
      node()->intersects(bb, polygon, finder);
    }
}

class StageTraversal : public StageFinder
{
public:
  StageTraversal(Traversal_ptr t);
  virtual ~StageTraversal();
  virtual void found(StageInfoImpl *i) { buffer.push_back(i);}
  void execute();
private:
  void traverse(StageInfoImpl *);
  Traversal_ptr traversal;
  vector<StageInfoImpl *> buffer;
};

StageTraversal::StageTraversal(Traversal_ptr t) : traversal(t) {}
StageTraversal::~StageTraversal() {}

template <>
struct greater<StageInfoImpl *> : public binary_function<StageInfoImpl *, StageInfoImpl *, bool>
{ bool operator() (StageInfoImpl *a, StageInfoImpl *b) const { return a->layer > b->layer;}};

template <>
struct less<StageInfoImpl *> : public binary_function<StageInfoImpl *, StageInfoImpl *, bool>
{ bool operator() (StageInfoImpl *a, StageInfoImpl *b) const { return a->layer < b->layer;}};

void StageTraversal::execute()
{
  if (traversal->direction() == Traversal::down)
    sort(buffer.begin(), buffer.end(), greater<StageInfoImpl *>());
  else
    sort(buffer.begin(), buffer.end(), less<StageInfoImpl *>());
  for (vector<StageInfoImpl *>::iterator i = buffer.begin(); i != buffer.end() && traversal->ok(); i++)
    traverse(*i);
}

void StageTraversal::traverse(StageInfoImpl *info)
{
  RegionImpl *region = new RegionImpl;
  region->_obj_is_ready(CORBA::BOA::getBOA());
  info->bbox(*region);
  traversal->traverseChild(Graphic::_duplicate(info->child), Region_var(region->_this()), Transform::_nil());
  region->_dispose();
}

StageImpl::StageImpl()
{
  nesting = 0;
  damage_ = new RegionImpl;
  damage_->_obj_is_ready(CORBA::BOA::getBOA());
  bbregion = new RegionImpl;
  bbregion->_obj_is_ready(CORBA::BOA::getBOA());
  need_redraw = false;
  need_resize = false;
}

StageImpl::~StageImpl()
{
  bbregion->_dispose();
  damage_->_dispose();
}

void StageImpl::request(Requisition &r)
{
  GraphicImpl::initRequisition(r);
  if (tree.size() > 0)
    {
      Geometry::Rectangle<Coord> b = tree.bbox();
      Coord w = b.r - b.l;
      Coord h = b.b - b.t;
      Coord ax = (Math::equal(w, 0., epsilon) ? 0 : (-b.l / w));
      Coord ay = (Math::equal(h, 0., epsilon) ? 0 : (-b.t / h));
      GraphicImpl::require(r.x, w, 0, 0, ax);
      GraphicImpl::require(r.y, h, 0, 0, ay);
    }
}

void StageImpl::traverse(Traversal_ptr traversal)
{
  SectionLog section(Logger::traversal, "StageImpl::traverse");
  RegionImpl region(Region_var(traversal->allocation()), Transform::_nil());
  Geometry::Rectangle<Coord> rectangle;
  rectangle.l = region.lower.x;
  rectangle.t = region.lower.y;
  rectangle.r = region.upper.x;
  rectangle.b = region.upper.y;
//   dumpQuadTree(tree);
  StageTraversal st(traversal);
  tree.intersects(rectangle, st);
  st.execute();
}

void StageImpl::allocate(Graphic_ptr child, Allocation_ptr a)
{
  Allocation_var allocation = a;
  StageInfoImpl *sinfo = 0;
  for (StageSequence::iterator i = list.begin(); i != list.end(); i++)
    if ((*i)->child == child)
      {
	sinfo = *i;
	break;
      }
  if (sinfo)
    {
      CORBA::Long begin = allocation->size();
      allocateParents(Allocation::_duplicate(allocation));
      CORBA::Long end = allocation->size();
      for (CORBA::Long i = begin; i != end; i++)
	{
	  Allocation::Info_var info = allocation->get(i);
	  allocateChild(sinfo, info);
	}
    }
}

void StageImpl::needRedraw()
{
  SectionLog section(Logger::layout, "StageImpl::needRedraw");
  AllocationImpl *allocation = new AllocationImpl;
  allocation->_obj_is_ready(_boa());
  allocateParents(Allocation_var(allocation->_this()));
  for (long i = 0; i < allocation->size(); i++)
    {
      Allocation::Info_var info = allocation->get(i);
      RegionImpl *region = new RegionImpl;
      region->_obj_is_ready(_boa());
      extension(info, Region_var(region->_this()));
      if (region->valid)
	{
	  Vertex origin;
	  info->allocation->origin(origin);
	  TransformImpl *tx = new TransformImpl;
	  tx->_obj_is_ready(_boa());
	  tx->translate(origin);
	  region->applyTransform(Transform_var(tx->_this()));
	  if (region->valid) info->root->damage(Region_var(region->_this()));
	  tx->_dispose();
	  region->_dispose();
	}
    }
  allocation->_dispose();
}

void StageImpl::needRedrawRegion(Region_ptr region)
{
  SectionLog section(Logger::layout, "StageImpl::needRedrawRegion");
  AllocationImpl *allocation = new AllocationImpl;
  allocation->_obj_is_ready(_boa());
  allocateParents(Allocation_var(allocation->_this()));
  CORBA::Long size = allocation->size();
  for (long i = 0; i < size; i++)
    {
      Allocation::Info_var info = allocation->get(i);
      RegionImpl *tmp = new RegionImpl(region, info->transformation);
      tmp->_obj_is_ready(_boa());
      Vertex origin;
      info->allocation->origin(origin);
      TransformImpl *tx = new TransformImpl;
      tx->_obj_is_ready(_boa());
      tx->translate(origin);
      tmp->applyTransform(Transform_var(tx->_this()));
      if (tmp->valid) info->root->damage(Region_var(tmp->_this()));
      tx->_dispose();
      tmp->_dispose();
    }
  allocation->_dispose();
}

void StageImpl::needResize()
{
  SectionLog section(Logger::layout, "StageImpl::needResize");
  /*
   * FIXME !!!: need to work out how to process this. (which sub region to damage etc...)
   */
  GraphicImpl::needResize();
}

Region_ptr StageImpl::bbox()
{
  Geometry::Rectangle<Coord> bb = tree.bbox();
  bbregion->valid = true;
  bbregion->lower.x = bb.l;
  bbregion->lower.y = bb.t;
  bbregion->lower.z = 0.;
  bbregion->upper.x = bb.r;
  bbregion->upper.y = bb.b;
  bbregion->upper.z = 0.;
  return bbregion->_this();
}

void StageImpl::begin()
{
  if (!nesting++)
    {
      Geometry::Rectangle<Coord> bb = tree.bbox();
      bbregion->lower.x = bb.l;
      bbregion->lower.y = bb.t;
      bbregion->upper.x = bb.r;
      bbregion->upper.y = bb.b;
      tree.begin();
    }
}

void StageImpl::end()
{
  SectionLog section(Logger::layout, "StageImpl::end");
  MutexGuard guard(childMutex);
  if (!--nesting)
    {
      tree.end();
      if (need_redraw)
	{
	  SectionLog section(Logger::layout, "StageImpl::need_redraw");
	  needRedrawRegion(Region_var(damage_->_this()));
	  need_redraw = false;
	}
      if (need_resize)
	{
 	  SectionLog section(Logger::layout, "StageImpl::need_resize");
 	  Geometry::Rectangle<Coord> bb = tree.bbox();
 	  if (! Math::equal(bbregion->lower.x, bb.l, epsilon) ||
 	      ! Math::equal(bbregion->lower.y, bb.t, epsilon) ||
 	      ! Math::equal(bbregion->upper.x, bb.r, epsilon) ||
 	      ! Math::equal(bbregion->upper.y, bb.b, epsilon))
 	    GraphicImpl::needResize();
 	  need_resize = false;
	}
    }
}

Stage::Info StageImpl::insert(Graphic_ptr g, const Vertex &position, const Vertex &size, Index layer)
{
  SectionLog section(Logger::layout, "StageImpl::insert");
  MutexGuard guard(childMutex);
  StageInfoImpl *info = new StageInfoImpl(Graphic::_duplicate(g), position, size, layer);
  info->child->addParent(Stage_var(_this()));
  tree.insert(info);
//   dumpQuadTree(tree);
  list.insert(info);
  damage(info);
  return *info;
}

void StageImpl::erase(const Stage::Info &i)
{
  SectionLog section(Logger::layout, "StageImpl::erase");
  MutexGuard guard(childMutex);
  StageInfoImpl *info = list.find(i.layer);
  if (!info) return;
  tree.remove(info);
//   dumpQuadTree(tree);
  list.remove(info);

  damage(info);
  delete info;
  need_resize = true;
}

void StageImpl::reposition(const Stage::Info &i, const Vertex &p)
{
  SectionLog section(Logger::layout, "StageImpl::reposition");
  MutexGuard guard(childMutex);
  StageInfoImpl *info = list.find(i.layer);
  if (!info) return;
  tree.remove(info);

  damage(info);
  need_resize = true;
  
  Coord dx = p.x - info->position.x;
  Coord dy = p.y - info->position.y;
  info->boundingbox.l += dx;
  info->boundingbox.t += dy;
  info->boundingbox.r += dx;
  info->boundingbox.b += dy;
  info->position = p;
  tree.insert(info);
//   dumpQuadTree(tree);

  damage(info);
  need_resize = true;
}

void StageImpl::relayer(const Stage::Info &i, Stage::Index l)
{
  SectionLog section(Logger::layout, "StageImpl::relayer");
  MutexGuard guard(childMutex);
  StageInfoImpl *info = list.find(i.layer);
  list.remove(info);
  info->layer = l;
  list.insert(info);
  damage(info);
}

void StageImpl::allocateChild(StageInfoImpl *i, Allocation::Info &info)
{
  RegionImpl *region = new RegionImpl;
  region->_obj_is_ready(_boa());
  i->bbox(*region);
  info.allocation->copy(Region_var(region->_this()));
  region->_dispose();
}

void StageImpl::damage(StageInfoImpl *info)
{
  RegionImpl *region = new RegionImpl;
  region->_obj_is_ready(_boa());
  info->bbox(*region);
  if (need_redraw) damage_->mergeUnion(Region_var(region->_this()));
  else
    {
      need_redraw = true;
      damage_->copy(Region_var(region->_this()));
    }
  region->_dispose();
}
