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

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/Screen.hh>
#include <Berlin/Provider.hh>
#include <Berlin/AllocationImpl.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/DebugGraphic.hh>
#include <Berlin/QuadTree.hh>
#include <Berlin/Math.hh>
#include <Berlin/RefCountVar.hh>
#include "StageImpl.hh"

#include <list>

using namespace Geometry;
using namespace Prague;
using namespace Fresco;
using namespace Layout;
using namespace Berlin;

using namespace Berlin::LayoutKit;

namespace Berlin
{
  namespace LayoutKit
  {
    class StageImpl::Sequence : public std::vector<StageHandleImpl *>
    {
        typedef std::vector<StageHandleImpl *> parent_t;
      public:
        Sequence() : my_cursor(0) { }
        ~Sequence() { }

        void insert(StageHandleImpl *);
        void remove(StageHandleImpl *);
    
        StageHandleImpl *find(Layout::Stage::Index layer)
    {
        iterator i = lookup(layer);
        return i == end() ? 0 : *i;
        }
        StageHandleImpl *front() { return size() ? parent_t::front() : 0; }
        StageHandleImpl *back() { return size() ? parent_t::back() : 0; }
        StageHandleImpl *current()
        { return my_cursor < size() ? *(begin() + my_cursor) : 0; }

      private:
        iterator lookup(Layout::Stage::Index layer);
        size_t my_cursor;
    };

    class Finder
    {
      public:
        virtual ~Finder() { }
        virtual void found(StageHandleImpl *) = 0;
    };


    class Quad : public QTNode<Coord, StageHandleImpl *>
    {
    typedef QTNode<Coord, StageHandleImpl *> parent_t;
      public:
    Quad(const Geometry::Rectangle<Coord> &);
    Quad(const Geometry::Rectangle<Coord> &, Quad *);
    Quad *node(int i)
    { return static_cast<Quad *>(parent_t::node(static_cast<index>(i))); }
    void within(const Geometry::Rectangle<Coord> &, Finder &);
    void contains(const Geometry::Point<Coord> &, Finder &);
    void intersects(const Geometry::Rectangle<Coord> &, Finder &);
    void intersects(const Geometry::Rectangle<Coord> &,
            const Geometry::Polygon<Coord> &, Finder &);
    };

  } // namespace
} // namespace

class StageImpl::QuadTree : public Berlin::QuadTree<Coord,
                                                StageHandleImpl *>
{
    typedef Berlin::QuadTree<Coord, StageHandleImpl *> parent_t;

  public:
    QuadTree() : my_transaction(0), my_operations(0) { }
    Quad *node() { return static_cast<Quad *>(parent_t::node()); }

    void lock(){ my_transaction++;}
    void insert(StageHandleImpl *);
    void remove(StageHandleImpl *);
    void unlock();
    StageHandleImpl *contains(const Geometry::Point<Coord> &);
    void within(const Geometry::Rectangle<Coord> &r, Finder &f)
    { if (node()) node()->within(r, f); }
    void intersects(const Geometry::Rectangle<Coord> &r, Finder &f)
    { if (node()) node()->intersects(r, f); }
    void intersects(const Geometry::Polygon<Coord> &, Finder &);
  private:
    unsigned int my_transaction;
    unsigned int my_operations;
};

StageImpl::Sequence::iterator
StageImpl::Sequence::lookup(Layout::Stage::Index layer)
{
    Trace trace("StageImpl::Sequence::lookup");
    if (layer == front()->my_layer) return begin();
    if (layer == back()->my_layer) return end() - 1;
    if (layer == current()->my_layer) return begin() + my_cursor;

    // start searching from the closest item
    Layout::Stage::Index fdist = front()->my_layer - layer;
    Layout::Stage::Index bdist = layer;
    Layout::Stage::Index cdist = Math::abs(current()->my_layer - layer);
    if (fdist < bdist)
    { if (fdist < cdist) my_cursor = 0; }
    else if (bdist < cdist) my_cursor = size() - 1;
    my_cursor += layer - current()->my_layer;
    my_cursor = Math::max(size_t(0), Math::min(my_cursor, size()-1));
    return begin() + my_cursor;
}

void StageImpl::Sequence::insert(StageHandleImpl *handle)
{
    Trace trace("StageImpl::Sequence::insert");
    Layout::Stage::Index layer = handle->my_layer;
    iterator i;
    if (!size() || layer == 0) i = begin();
    else if (front()->my_layer < layer) i = end();
    // FIXME: Shouldn't this be back(), not front() ? --tobias
    else i = lookup(layer);
    for (iterator j = i; j != end(); ++j)
    (*j)->my_layer = ++layer;
    parent_t::insert(i, handle);
}

void StageImpl::Sequence::remove(StageHandleImpl *handle)
{
    Trace trace("StageImpl::Sequence::remove");
    Layout::Stage::Index layer = handle->my_layer;
    iterator old = lookup(layer);
    if (old == begin() + my_cursor)
        if (current()->my_layer <= (front()->my_layer / 2)) my_cursor++;
    else my_cursor--;
    for (iterator i = old++; i != end(); ++i)
        (*i)->my_layer = layer++;
    parent_t::erase(--old);
    my_cursor = Math::max(size_t(0), Math::min(my_cursor, size()-1));
}

Quad::Quad(const Rectangle<Coord> &region) : parent_t(region) { }

// one child node is given; the other three are added inside
Quad::Quad(const Rectangle<Coord> &r, Quad *node) : parent_t(r)
{
    // SectionLog section("StageQuad::StageQuad(rectangle, StageQuad *)");
    my_elements = node->my_elements;
    my_boundingbox = node->my_boundingbox;

    const Rectangle<Coord> &b = node->my_region;
    int idx = none;

    // now determine in which directions we have to extend.
    // node becomes one of our children, the other three are added
    Coord dl = b.l - r.l;
    Coord dr = r.r - b.r;
    if (dl < dr)
    { 
    idx |= left;
    my_region.l = b.l;
    my_region.r = b.r + b.w();
    }
    else
    {
    idx |= right;
    my_region.l = b.l - b.w();
    my_region.r = b.r;
    }

    Coord dt = b.t - r.t;
    Coord db = r.b - b.b;
    if (dt < db)
    {
    idx |= top;
    my_region.t = b.t;
    my_region.b = b.b + b.h();
    }
    else
    {
    idx |= bottom;
    my_region.t = b.t - b.h();
    my_region.b = b.b;
    }

    my_quadrants[lefttop] =
        idx == lefttop ? node :
        new Quad(Rectangle<Coord>(my_region.l, my_region.t,
                  my_region.cx(), my_region.cy()));
    my_quadrants[righttop] =
        idx == righttop ? node :
        new Quad(Rectangle<Coord>(my_region.cx(), my_region.t,
                  my_region.r, my_region.cy()));
    my_quadrants[leftbottom] =
        idx == leftbottom ? node :
        new Quad(Rectangle<Coord>(my_region.l, my_region.cy(),
                  my_region.cx(), my_region.b));
    my_quadrants[rightbottom] =
        idx == rightbottom ? node :
        new Quad(Rectangle<Coord>(my_region.cx(), my_region.cy(),
                  my_region.r, my_region.b));
}

void Quad::within(const Rectangle<Coord> &r, Finder &finder)
{
    index idx = where(my_region);
    if (idx == fence)
    {
        for (list::iterator i = my_items.begin();
         i != my_items.end();
         ++i)
            if ((*i)->bbox().within(r)) finder.found(*i);
        if (!leaf())
        {
            if (r.r <= my_region.cx())
            {
                node(lefttop)->within(r, finder);
                node(leftbottom)->within(r, finder);
            }
            else if (r.l > my_region.cx())
            {
                node(righttop)->within(r, finder);
                node(rightbottom)->within(r, finder);
            }
            else if (r.b <= my_region.cy())
            {
                node(lefttop)->within(r, finder);
                node(righttop)->within(r, finder);
            }
            else if (r.t > my_region.cy())
            {
                node(leftbottom)->within(r, finder);
                node(rightbottom)->within(r, finder);
            }
            else for (int i = 0; i < 4; ++i)
        node(i)->within(r, finder);
        }
    }
    else node(idx)->within(r, finder);
}

void Quad::contains(const Point<Coord> &point, Finder &finder)
{
    for (list::iterator i = my_items.begin(); i != my_items.end(); ++i)
        if ((*i)->bbox().contains(point))
        {
            /*
               RegionImpl region;
               (*i)->c->shape(region);
               if (region->contains(point.x, point.y)) finder.found(*i);
             */
            finder.found(*i);
        }
        if (!leaf()) node(where(point))->contains(point, finder);
}

void Quad::intersects(const Rectangle<Coord> &r, Finder &finder)
{
    for (list::iterator i = my_items.begin(); i != my_items.end(); ++i)
    {
        if ((*i)->bbox().intersects(r))
        {
            /*
               RegionImpl shape;
               (*i)->c->shape(my_region);
               if (shape->intersects(my_region.l, my_region.b,
                                 my_region.r, my_region.t))
                   finder.found(item);
             */
            finder.found(*i);
        }
    }
    index idx = where(r);
    if (idx == fence)
    {
        if (!leaf())
        {
            if (r.r <= my_region.cx())
            {
                node(leftbottom)->intersects(r, finder);
                node(lefttop)->intersects(r, finder);
            }
            else if (r.l > my_region.cx())
            {
                node(rightbottom)->intersects(r, finder);
                node(righttop)->intersects(r, finder);
            }
            else if (r.b <= my_region.cy())
            {
                node(lefttop)->intersects(r, finder);
                node(righttop)->intersects(r, finder);
            }
            else if (r.t > my_region.cy())
            {
                node(leftbottom)->intersects(r, finder);
                node(rightbottom)->intersects(r, finder);
            }
            else for (int i = 0; i < 4; ++i)
        node(i)->intersects(r, finder);
        }
    }
    else node(idx)->intersects(r, finder);
}

void Quad::intersects(const Rectangle<Coord> &r,
                      const Polygon<Coord> &polygon, Finder &finder)
{
    for (list::iterator i = my_items.begin(); i != my_items.end(); ++i)
        if (polygon.intersects((*i)->bbox()))
        {
            /*
               RegionImpl shape;
               Graphic_var(item->child())->shape(region);
               if (shape->intersects(Geometry::Polygon))
                   finder.found(item);
             */
            finder.found(*i);
        }
    index idx = where(r);
    if (idx == fence)
    {
        if (!leaf())
        {
            // FIXME: shouldn't this read node(...)->intersects(s, polygon,
            //                                          finder) ??? -stefan
            if (r.r <= my_region.cx())
            {
                node(leftbottom)->intersects(r, finder);
                node(lefttop)->intersects(r, finder);
            }
            else if (r.l > my_region.cx())
            {
                node(rightbottom)->intersects(r, finder);
                node(righttop)->intersects(r, finder);
            }
            else if (r.b <= my_region.cy())
            {
                node(lefttop)->intersects(r, finder);
                node(righttop)->intersects(r, finder);
            }
            else if (r.t > my_region.cy())
            {
                node(leftbottom)->intersects(r, finder);
                node(rightbottom)->intersects(r, finder);
            }
            else for (int i = 0; i < 4; i++)
        node(i)->intersects(r, finder);
        }
    }
    else node(idx)->intersects(r, finder);
}

void StageImpl::QuadTree::insert(StageHandleImpl *handle)
{
    const Rectangle<Coord> &bbox = handle->bbox();
    if (!node()) my_quad = new Quad(bbox);
    /*
     * FIXME: currently, this code inserts new nodes as long as the
     *        outermost doesn't completely contain the handle's
     *        boundingbox. What if the given bbox is infinity ?? On the
     *        other hand, guessing too large values are tricky since we
     *        don't know the scale of this coordinate system, so may be a
     *        limiting depth of the tree would be a solution.
     *                -stefan
     */
    else while (!bbox.within(node()->extension()))
    my_quad = new Quad(bbox, node());
    node()->insert(handle);
}

void StageImpl::QuadTree::remove(StageHandleImpl *handle)
{ node()->remove(handle); }

void StageImpl::QuadTree::unlock()
{
    my_transaction--;
    if (my_transaction == 0)
    {
        // ??? every 32 operations adjust the StageQuad tree -denis
        my_operations++;
        if (my_operations & 0x1f == 0) {
            // ??? desire min of 8, max of 32, smallest span of 16 -denis
            node()->adjust(8, 32, 16, 16);
        }
    }
}

namespace Berlin
{
  namespace LayoutKit
  {
    class StageQuadTreeContains : public Finder
    {
      public:
    StageQuadTreeContains(Traversal::order o) : handle(0), order(o) { }
    virtual void found(StageHandleImpl *h)
        {
        if (!handle ||
            (order == Traversal::down &&
             handle->my_layer > h->my_layer) ||
            handle->my_layer < h->my_layer)
            handle = h;
        }
    StageHandleImpl *handle;
    Traversal::order order;
    };
  } // namespace
} // namespace

StageHandleImpl *StageImpl::QuadTree::contains(const Point<Coord> &point)
{
    StageHandleImpl *handle = 0;
    if (node())
    {
        StageQuadTreeContains finder(Traversal::up);
        node()->contains(point, finder);
        handle = finder.handle;
    }
    return handle;
}

void StageImpl::QuadTree::intersects(const Polygon<Coord> &polygon,
                     Finder &finder)
{
    if (node())
    {
        Rectangle<Coord> bb;
        polygon.boundingBox(bb);
        node()->intersects(bb, polygon, finder);
    }
}

namespace Berlin
{
  namespace LayoutKit
  {
    class StageTraversal : public Finder
    {
      public:
    StageTraversal(Traversal_ptr t);
    virtual ~StageTraversal();
    virtual void found(StageHandleImpl *h) { my_buffer.push_back(h);}
    void execute();
      private:
    void traverse(StageHandleImpl *);
    Traversal_ptr                  my_traversal;
    std::vector<StageHandleImpl *> my_buffer;
    };
  } // namespace
} // namespace

StageTraversal::StageTraversal(Traversal_ptr t) : my_traversal(t) { }
StageTraversal::~StageTraversal() { }

namespace std
{

  template <>
  struct greater<StageHandleImpl *> :
    public binary_function<StageHandleImpl *, StageHandleImpl *, bool>
  {
      bool operator() (StageHandleImpl *a, StageHandleImpl *b) const
      { return a->my_layer > b->my_layer; }
  };

  template <>
  struct less<StageHandleImpl *> :
    public binary_function<StageHandleImpl *, StageHandleImpl *, bool>
  {
      bool operator() (StageHandleImpl *a, StageHandleImpl *b) const
      { return a->my_layer < b->my_layer; }
  };
} // namespace std

void StageTraversal::execute()
{
    if (my_traversal->direction() == Traversal::down)
        sort(my_buffer.begin(), my_buffer.end(),
         std::less<StageHandleImpl *>());
    else
        sort(my_buffer.begin(), my_buffer.end(),
         std::greater<StageHandleImpl *>());
    for (std::vector<StageHandleImpl *>::iterator i = my_buffer.begin();
         i != my_buffer.end() && my_traversal->ok();
         ++i)
    {
        if (!my_traversal->ok()) break;
        traverse(*i);
    }
}

void StageTraversal::traverse(StageHandleImpl *handle)
{
    Trace trace("StageTraversal::traverse");
    if (CORBA::is_nil(handle->my_child)) return;
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    handle->bbox(*region);
    Vertex origin;
    region->normalize(origin);
    Lease_var<TransformImpl>
    transformation(Provider<TransformImpl>::provide());
    transformation->load_identity();
    transformation->translate(origin);
    try
    {
        my_traversal->traverse_child(handle->my_child,
                     handle->my_tag,
                     Region_var(region->_this()),
                     Transform_var(transformation->_this()));
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { handle->my_child = Fresco::Graphic::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { handle->my_child = Fresco::Graphic::_nil(); }
}

class StageImpl::Iterator : public virtual POA_Fresco::GraphicIterator,
                            public virtual GraphicIteratorImpl
{
  public:
    Iterator(StageImpl *p, Tag c) :
    my_parent(p),
    my_cursor(c)
    { my_parent->_add_ref(); }
    virtual ~Iterator() { my_parent->_remove_ref(); }

    virtual Fresco::Graphic_ptr child()
    {
    Prague::Guard<Mutex> guard(my_parent->my_mutex);
    if (my_cursor >= my_parent->my_children->size())
            return Fresco::Graphic::_nil();
        return RefCount_var<Fresco::Graphic>::increment(
        my_parent->my_children->find(my_cursor)->child());
    }
    virtual void next() { my_cursor++; }
    virtual void prev() { my_cursor--; }
    virtual void insert(Graphic_ptr child) { }
    virtual void replace(Graphic_ptr child) { }

    virtual void remove() { }
  private:
    StageImpl * my_parent;
    CORBA::ULong my_cursor;
};


StageImpl::StageImpl() :
  my_children(new Sequence),
  my_tree(new QuadTree),
  my_nesting(0),
  my_damage(new RegionImpl),
  my_bbregion(new RegionImpl),
  my_need_redraw(false),
  my_need_resize(false)
{ }

StageImpl::~StageImpl()
{
    delete my_tree;
    delete my_children;
}

Fresco::GraphicIterator_ptr StageImpl::first_child_graphic()
{
    Iterator *iterator = new Iterator(this, 0);
    activate(iterator);
    return iterator->_this();
}

Fresco::GraphicIterator_ptr StageImpl::last_child_graphic()
{
    Iterator *iterator =
        new Iterator(this, my_children->size() ?
             my_children->size() - 1 : 0);
    activate(iterator);
    return iterator->_this();
}

void StageImpl::request(Fresco::Graphic::Requisition &r)
{
    GraphicImpl::init_requisition(r);
    if (my_tree->size() > 0)
    {
        Geometry::Rectangle<Coord> b = my_tree->bbox();
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
    Trace trace(this, "StageImpl::traverse");
    Prague::Guard<Mutex> guard(my_mutex);
    RegionImpl region(Region_var(traversal->current_allocation()));
    Geometry::Rectangle<Coord> rectangle;
    rectangle.l = region.lower.x;
    rectangle.t = region.lower.y;
    rectangle.r = region.upper.x;
    rectangle.b = region.upper.y;
    // dumpQuadTree(*tree);
    StageTraversal st(traversal);
    my_tree->intersects(rectangle, st);
    st.execute();
}

void StageImpl::allocate(Tag tag, const Allocation::Info &a)
{
    StageHandleImpl *handle = tag_to_handle(tag);
    if (handle)
    {
        Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
        Lease_var<TransformImpl>
        transform(Provider<TransformImpl>::provide());
        transform->load_identity();
        Vertex origin;
        handle->bbox(*region);
        region->normalize(origin);
        transform->translate(handle->my_position);
        a.allocation->copy(Region_var(region->_this()));
        a.transformation->premultiply(Transform_var(transform->_this()));
    }
}

void StageImpl::need_redraw()
{
    Trace trace(this, "StageImpl::need_redraw");
    Lease_var<AllocationImpl>
    allocation(Provider<AllocationImpl>::provide());
    allocations(Allocation_var(allocation->_this()));
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
    for (CORBA::Long i = 0; i < allocation->size(); i++)
    {
        const Allocation::Info_var info = allocation->get(i);
        region->valid = false;
        extension(info.in(), Region_var(region->_this()));
        if (region->valid)
        {
            Vertex origin;
            info->allocation->origin(origin);
            tx->load_identity();
            tx->translate(origin);
            region->apply_transform(Transform_var(tx->_this()));
            if (region->valid)
        info->root->damage(Region_var(region->_this()));
        }
    }
}

void StageImpl::need_redraw_region(Region_ptr region)
{
    Trace trace(this, "StageImpl::need_redraw_region");
    Lease_var<AllocationImpl>
    allocation(Provider<AllocationImpl>::provide());
    allocations(Allocation_var(allocation->_this()));
    CORBA::Long size = allocation->size();
    Lease_var<RegionImpl> tmp(Provider<RegionImpl>::provide());
    Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
    for (CORBA::Long i = 0; i < size; i++)
    {
        const Allocation::Info_var info = allocation->get(i);
        tmp->copy(region);
        tmp->apply_transform(info->transformation);
        Vertex origin;
        info->allocation->origin(origin);
        tx->load_identity();
        tx->translate(origin);
        tmp->apply_transform(Transform_var(tx->_this()));
        if (tmp->valid) info->root->damage(Region_var(tmp->_this()));
    }
}

void StageImpl::need_resize()
{
    Trace trace(this, "StageImpl::need_resize");
    // FIXME: need to work out how to process this. (which sub region to
    //        damage etc...)
    GraphicImpl::need_resize();
}

Region_ptr StageImpl::bbox()
{
    Prague::Guard<Mutex> guard(my_mutex);
    Geometry::Rectangle<Coord> bb = my_tree->bbox();
    my_bbregion->valid = true;
    my_bbregion->lower.x = bb.l;
    my_bbregion->lower.y = bb.t;
    my_bbregion->lower.z = 0.;
    my_bbregion->upper.x = bb.r;
    my_bbregion->upper.y = bb.b;
    my_bbregion->upper.z = 0.;
    return my_bbregion->_this();
}

CORBA::Long StageImpl::layers()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_tree->size();
}

StageHandle_ptr StageImpl::layer(Layout::Stage::Index i)
{
    Prague::Guard<Mutex> guard(my_mutex);
    StageHandleImpl *handle = my_children->find(i);
    return handle ? handle->_this() : StageHandle::_nil();
}

void StageImpl::lock()
{
    if (!my_nesting++)
    {
        Geometry::Rectangle<Coord> bb = my_tree->bbox();
        my_bbregion->lower.x = bb.l;
        my_bbregion->lower.y = bb.t;
        my_bbregion->upper.x = bb.r;
        my_bbregion->upper.y = bb.b;
        my_tree->lock();
    }
}

void StageImpl::unlock()
{
    Trace trace(this, "StageImpl::end");
    Prague::Guard<Mutex> guard(my_mutex);
    if (!--my_nesting)
    {
        my_tree->unlock();
        if (my_need_redraw)
        {
            need_redraw_region(Region_var(my_damage->_this()));
            my_need_redraw = false;
        }
        if (my_need_resize)
        {
            Geometry::Rectangle<Coord> bb = my_tree->bbox();
            if (! Math::equal(my_bbregion->lower.x, bb.l, epsilon) ||
                ! Math::equal(my_bbregion->lower.y, bb.t, epsilon) ||
                ! Math::equal(my_bbregion->upper.x, bb.r, epsilon) ||
                ! Math::equal(my_bbregion->upper.y, bb.b, epsilon))
                GraphicImpl::need_resize();
            my_need_resize = false;
        }
    }
}

StageHandle_ptr StageImpl::insert(Graphic_ptr g, const Vertex &position,
                                  const Vertex &size,
                  Layout::Stage::Index layer)
{
    Trace trace(this, "StageImpl::insert");
    Prague::Guard<Mutex> guard(my_mutex);
    StageHandleImpl *handle = new StageHandleImpl(this,
                                                  g, unique_tag(),
                                                  position,    size,
                                                  layer);
    my_tree->insert(handle);
    // dumpQuadTree(*tree);
    my_children->insert(handle);
    damage(handle);
    return handle->_this();
}

void StageImpl::remove(StageHandle_ptr h)
{
    Trace trace(this, "StageImpl::remove");
    Prague::Guard<Mutex> guard(my_mutex);
    StageHandleImpl *handle = my_children->find(h->layer());
    if (!handle) return;
    my_tree->remove(handle);
    // dumpQuadTree(*tree);
    my_children->remove(handle);
    
    damage(handle);
    // handle->_dispose();
    my_need_resize = true;
}

void StageImpl::move(StageHandleImpl *handle, const Vertex &p)
{
    Trace trace(this, "StageImpl::move");
    Prague::Guard<Mutex> guard(my_mutex);
    my_tree->remove(handle);
    
    damage(handle);
    
    Coord dx = p.x - handle->my_position.x;
    Coord dy = p.y - handle->my_position.y;
    handle->my_bbox.l += dx;
    handle->my_bbox.t += dy;
    handle->my_bbox.r += dx;
    handle->my_bbox.b += dy;
    handle->my_position = p;
    my_tree->insert(handle);
    // dumpQuadTree(*tree);
    
    damage(handle);
    my_need_redraw = true;
}

void StageImpl::resize(StageHandleImpl *handle, const Vertex &s)
{
    Trace trace(this, "StageImpl::resize");
    Prague::Guard<Mutex> guard(my_mutex);
    my_tree->remove(handle);
    
    damage(handle);
    my_need_resize = true;
    
    handle->my_bbox.r = handle->my_bbox.l + s.x;
    handle->my_bbox.b = handle->my_bbox.t + s.y;
    handle->my_size = s;
    my_tree->insert(handle);
    // dumpQuadTree(*tree);
    
    damage(handle);
    my_need_resize = true;
}

void StageImpl::relayer(StageHandleImpl *handle, Layout::Stage::Index l)
{
    Trace trace(this, "StageImpl::relayer");
    Prague::Guard<Mutex> guard(my_mutex);
    my_children->remove(handle);
    handle->my_layer = l;
    my_children->insert(handle);
    damage(handle);
}

Tag StageImpl::unique_tag()
{
    Tag t = 0;
    do
    {
        Sequence::iterator i;
        for (i = my_children->begin(); i != my_children->end(); i++)
            if ((*i)->my_tag == t) break;
        if (i == my_children->end()) return t;
    }
    while (++t);
    return 0;
}

StageHandleImpl *StageImpl::tag_to_handle(Tag tag)
{
    for (Sequence::iterator i = my_children->begin();
     i != my_children->end();
     ++i)
        if ((*i)->my_tag == tag) return *i;
    return 0;
}

void StageImpl::damage(StageHandleImpl *handle)
{
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    handle->bbox(*region);
    if (my_need_redraw)
    my_damage->merge_union(Region_var(region->_this()));
    else
    {
        my_need_redraw = true;
        my_damage->copy(Region_var(region->_this()));
    }
}

StageHandleImpl::StageHandleImpl(StageImpl *stage,
                                 Graphic_ptr g,
                                 Tag t,
                                 const Vertex &p, const Vertex &s,
                                 Layout::Stage::Index l) :
    my_parent(stage),
    my_child(Graphic::_duplicate(g)),
    my_tag(t),
    my_position(p),
    my_size(s),
    my_layer(l)
{
    my_child->add_parent_graphic(Stage_var(my_parent->_this()), my_tag);
    cache_bbox();
}

Layout::Stage_ptr StageHandleImpl::parent()
{ return my_parent->_this(); }

Fresco::Graphic_ptr StageHandleImpl::child()
{ return Fresco::Graphic::_duplicate(my_child); }

void StageHandleImpl::remove()
{
    my_parent->lock();
    my_parent->remove(StageHandle_var(_this()));
    my_parent->unlock();
}

Fresco::Vertex StageHandleImpl::position()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_position;
}

void StageHandleImpl::position(const Vertex &pp)
{
    my_parent->lock();
    my_parent->move(this, pp);
    my_parent->unlock();
}

Fresco::Vertex StageHandleImpl::size()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_size;
}

void StageHandleImpl::size(const Vertex &ss)
{
    my_parent->lock();
    my_parent->resize(this, ss);
    my_parent->unlock();
}

Layout::Stage::Index StageHandleImpl::layer()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_layer;
}

void StageHandleImpl::layer(Layout::Stage::Index ll)
{
    my_parent->lock();
    my_parent->relayer(this, ll);
    my_parent->unlock();
}

const Geometry::Rectangle<Fresco::Coord> &StageHandleImpl::bbox()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_bbox;
}

void StageHandleImpl::bbox(RegionImpl &region)
{
    Prague::Guard<Mutex> guard(my_mutex);
    region.valid   = true;
    region.lower.x = my_bbox.l;
    region.upper.x = my_bbox.r;
    region.xalign  = my_xalign;
    region.lower.y = my_bbox.t;
    region.upper.y = my_bbox.b;
    region.yalign  = my_yalign;
}

void StageHandleImpl::cache_bbox()
{
    Trace trace("StageHandleImpl::cache_bbox");
    Graphic::Requisition r;
    GraphicImpl::init_requisition(r);
    my_child->request(r);
    if (r.x.defined && r.y.defined)
    {
        my_xalign = r.x.align;
        my_yalign = r.y.align;
        if (my_size.x != 0)
        {
            my_bbox.l = my_position.x;
            my_bbox.r = my_position.x + my_size.x;
        }
        else
        {
            my_bbox.l = my_position.x - r.x.natural * r.x.align;
            my_bbox.r = my_position.x + r.x.natural * (1. - r.x.align);
        }
        if (my_size.y != 0)
        {
            my_bbox.t = my_position.y;
            my_bbox.b = my_position.y + my_size.y;
        }
        else
        {
            my_bbox.t = my_position.y - r.y.natural * r.y.align;
            my_bbox.b = my_position.y + r.y.natural * (1. - r.y.align);
        }
    }
    else
    {
        my_xalign = 0.;
        my_yalign = 0.;
        my_bbox.l = my_position.x;
        my_bbox.r = my_position.x;
        my_bbox.t = my_position.y;
        my_bbox.b = my_position.y;
    }
}
