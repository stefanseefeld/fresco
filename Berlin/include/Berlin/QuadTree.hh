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
#ifndef _QuadTree_hh
#define _QuadTree_hh

#include <Berlin/Geometry.hh>
#include <vector>
#include <algorithm>
#include <functional>

//. this defines a binary space partitioning (BSP) algorithm
//. in 2D, suitable for object lookup on the screen
//.
//. the parametrization is as follows:
//.  - T is the Domain, most likely Coord or PixelCoord
//.  - I is the Item to store, can be anything which defines a method
//.    const Geometry::Rectangle<T> &I::bbox() returning the bounding box
//.    suitable for use in the quadtree
template <class T, class I>
class QTNode
{
  //. This structure is used to determine wether items can get pushed
  //. into subnodes.
  struct move_down : std::unary_function<I, bool>
  {
    move_down(QTNode<T, I> *n) : node(n) {}
    bool operator()(I i)
    {
      QTNode<T, I>::index idx = node->where(i);
      if (idx != QTNode<T, I>::fence)
	{
	  node->quadrants[idx]->insert(i);
	  return true;
	}
      else return false;
    };
    QTNode<T, I> *node;
  };
  friend class move_down;

public:
  //. An enumeration of the quadrants of the QTNode.
  enum index
  {
    fence = -1,
    none = 0,
    left = 0,
    right = 1,
    top = 0,
    bottom = 2,
    leftbottom = left|bottom, // = 2
    rightbottom = right|bottom, // = 3
    lefttop = left|top, // = 0
    righttop = right|top // = 1
  };

  typedef std::vector<I> list;

  //. Creates an empty QTNode for the region r.
  QTNode(const Geometry::Rectangle<T> &r) : region(r), elements(0)
  { quadrants[0] = quadrants[1] = quadrants[2] = quadrants[3] = 0;}
  //. Returns a subnode for the quadrant i.
  QTNode<T, I> *node(index i) { return quadrants[i];}
  //. Deletes this QTNode and frees the memory used.
  ~QTNode() { free();}

  //. Region owned by this node
  const Geometry::Rectangle<T> &extension() const { return region;}

  //. Bounding box of all objects in this node
  const Geometry::Rectangle<T> &bbox() const { return boundingbox;}

  //. Insert an Item into the QuadTree.
  void insert(I);
  //. Remove an Item from the QuadTree.
  void remove(I);
  //. Number of objects in this node.
  int  size() const { return elements;}
  //. Pushes as many items as possible into subnodes.
  void unfold();
  //. Collapses the branch below this node. Afterwards this node will
  //. be a leaf containing all items of the nodes that used to be below
  //. this one.
  void collaps();
  //. Adjusts the branch starting with this node so that all nodes
  //. below this one meet the following requirements:
  //.   max is the maximum number of objects desired at each node
  //.   min is the minimum number of objects desired at each node
  //.   min_w and min_h are the minimum span desired for a node
  void adjust(int, int, T, T);

protected:
  //. Returns wether this node is a leaf of the QuadTree or not.
  bool leaf() const { return quadrants[0] == 0;}
  //. Creates the quadrants if they were not allocated before.
  void allocate();
  //. Frees the memory of this node and the subnodes.
  void free()
  {
    if (!leaf())
      for (int i = 0; i < 4; i++)
	{
	  delete quadrants[i];
	  quadrants[i] = 0;
	}
  }
  //. Returns the index the point p belongs into.
  index where(const Geometry::Point<T> &p)
  {
    return index((p.x <= region.cx() ? left : right) | (p.y <= region.cy() ? bottom : top));
  }
  //. Returns the quadrant the given rectangle is in. Returns 'fence' if the
  //. if the rectangle intersects more then one quadrant.
  index where(const Geometry::Rectangle<T> &);
  //. Returns the quadrant the item i belongs into. Returns 'fence' if the
  //. item i intersects more then one quadrant.
  index where(I i) { return where(i->bbox());}

  //. The region this node occupies,
  Geometry::Rectangle<T> region;
  //. The boundingbox of all objects in this node.
  Geometry::Rectangle<T> boundingbox;

  //. Total count of objects at or below this level
  int          elements;
  //. Items straddling the fence
  list         items;
  //. The quadrants of this node.
  QTNode<T, I> *quadrants[4];

  //. Dumps the data for this node and its subnotes if there are any.
  friend void dumpQuadNode(const QTNode<T,I> &node, short ind)
  {
    for (short i = 0; i != ind; i++) std::cout.put(' ');
    std::cout << "Node : " << node.elements
	      << '(' << node.items.size()
	      << ") elements, extension : "
	      << node.region << std::endl;
    for (list::const_iterator i = node.items.begin();
	 i != node.items.end();
	 i++)
      std::cout << (*i)->boundingbox << ';';
    std::cout << std::endl;
    if (!node.leaf())
      for (short i = 0; i != 4; i++)
	dumpQuadNode(*node.quadrants[i], ind + 2);
  }
};

template <class T, class I>
class QuadTree
{
public:
  //. Creates an empty QuadTree.
  QuadTree() : _quad(0) {}
  ~QuadTree() {}

  //. Returns the bounding box of all items in the QuadTree.
  Geometry::Rectangle<T> bbox()
  {
    return node() ? node()->bbox() : Geometry::Rectangle<T>();
  }
  //. Returns the number of items in this QuadTree.
  int size() { return _quad ? _quad->size() : 0;}
  //. Returns the rootnode of the QuadTree.
  QTNode<T, I> *node() { return _quad;}
protected:
  QTNode<T, I> *_quad;

  //. Dumps the data for this QuadTree.
  friend void dumpQuadTree(const QuadTree<T,I> &tree)
  {
    if (tree._quad) dumpQuadNode(*tree._quad, 0);
  }
};

// inline functions only below this line.

template <class T, class I>
inline void QTNode<T, I>::allocate()
{
  using namespace Geometry;
  if (leaf()) {
    quadrants[lefttop] = new QTNode<T, I>(Rectangle<T>(region.l, region.t, region.cx(), region.cy()));
    quadrants[righttop] = new QTNode<T, I>(Rectangle<T>(region.cx(), region.t, region.r, region.cy()));
    quadrants[leftbottom] = new QTNode<T, I>(Rectangle<T>(region.l, region.cy(), region.cx(), region.b));
    quadrants[rightbottom] = new QTNode<T, I>(Rectangle<T>(region.cx(), region.cy(), region.r, region.b));
  }
}

template <class T, class I>
inline void QTNode<T, I>::adjust(int min, int max, T min_w, T min_h)
{
  // If we are over the maximum then unfold
  // and push down as many objects as we can.
  if (items.size() > (uint) max && ((region.w() > (min_w * 2)) || (region.h() > (min_h * 2)))) unfold();
  if (!leaf())
    {
      for (int i = 0; i < 4; ++i) quadrants[i]->adjust(min, max, min_w, min_h);
      // If our sub-tree is under the minimum then flatten it away.
      if (elements < min || elements - items.size() == 0 || (region.w() < min_w && region.h() < min_h)) collaps();
    }
}

template <class T, class I>
inline void QTNode<T, I>::unfold()
{
  if (! leaf()) return;
  allocate();
  list::iterator i = remove_if(items.begin(), items.end(), move_down(this));
  items.erase(i, items.end());
}

template <class T, class I>
inline void QTNode<T, I>::collaps()
{
  if (leaf()) return;
  for (int i = 0; i < 4; i++)
    {
      QTNode<T, I> *node = quadrants[i];
      node->collaps();
      list childItems = node->items;
      items.insert(items.end(), childItems.begin(), childItems.end());
    }
  free();
}

template <class T, class I>
inline QTNode<T, I>::index QTNode<T, I>::where(const Geometry::Rectangle<T> &r)
{
  int idx = fence;
  if (!leaf())
    {
      const T x = region.cx();
      const T y = region.cy();
      /*
       * is r inside one of the quarters ?
       */
      if ((r.r <= x) == (r.l < x) && (r.b <= y) == (r.t < y))
	idx = (r.r <= x ? left : right) | (r.b <= y ? top : bottom);
    }
  return static_cast<index>(idx);
}

template <class T, class I>
inline void QTNode<T, I>::insert(I i)
{
  index idx = where(i);
  if (idx == fence) items.push_back(i);
  else quadrants[idx]->insert(i);
  elements++;
  
  const Geometry::Rectangle<T> &bb = i->bbox();
  if (elements > 1) boundingbox.merge(bb);
  else boundingbox = bb;
}

template <class T, class I>
inline void QTNode<T, I>::remove(I i)
{
  index idx = where(i);
  if (idx == fence)
    {
      for (list::iterator j = items.begin(); j != items.end(); j++)
	if (*j == i)
	  {
	    items.erase(j);
	    break;
	  }
    }
  else quadrants[idx]->remove(i);
  elements--;

  if (boundingbox.touches(i->bbox(), epsilon))
    {
      boundingbox.clear();
      bool first = true;
      for (list::iterator j = items.begin(); j != items.end(); j++)
	{
	  if (first) { boundingbox = (*j)->bbox(); first = false;}
	  else boundingbox.merge((*j)->bbox());
	}
      if (!leaf())
	{
	  for (int j = 0; j < 4; j++)
	    {
	      QTNode<T, I> *node = quadrants[j];
	      if (node->elements > 0)
		{
		  if (first) { boundingbox = node->bbox(); first = 0;}
		  else boundingbox.merge(node->bbox());
		}
	    }
	}
    }
}

#endif /* _QuadTree_h */
