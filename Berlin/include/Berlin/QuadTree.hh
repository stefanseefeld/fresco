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
#ifndef _Berlin_QuadTree_hh
#define _Berlin_QuadTree_hh

#include <Berlin/Geometry.hh>
#include <vector>
#include <algorithm>
#include <functional>

namespace Berlin
{

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
		  node->my_quadrants[idx]->insert(i);
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
      QTNode(const Geometry::Rectangle<T> &r) :
	  my_region(r), 
	  my_elements(0)
      {
	  my_quadrants[0] = my_quadrants[1] =
	      my_quadrants[2] = my_quadrants[3] = 0;
      }
      //. Returns a subnode for the quadrant i.
      QTNode<T, I> *node(index i) { return my_quadrants[i]; }
      //. Deletes this QTNode and frees the memory used.
      ~QTNode() { free(); }
      
      //. Region owned by this node
      const Geometry::Rectangle<T> &extension() const { return my_region; }

      //. Bounding box of all objects in this node
      const Geometry::Rectangle<T> &bbox() const { return my_boundingbox; }

      //. Insert an Item into the QuadTree.
      void insert(I);
      //. Remove an Item from the QuadTree.
      void remove(I);
      //. Number of objects in this node.
      int  size() const { return my_elements;}
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
      bool leaf() const { return my_quadrants[0] == 0;}
      //. Creates the quadrants if they were not allocated before.
      void allocate();
      //. Frees the memory of this node and the subnodes.
      void free()
      {
	  if (!leaf())
	      for (int i = 0; i < 4; i++)
	      {
		  delete my_quadrants[i];
		  my_quadrants[i] = 0;
	      }
      }
      //. Returns the index the point p belongs into.
      index where(const Geometry::Point<T> &p)
      {
	  return index((p.x <= my_region.cx() ? left : right) |
		       (p.y <= my_region.cy() ? bottom : top));
      }
      //. Returns the quadrant the given rectangle is in. Returns 'fence'
      // if the rectangle intersects more then one quadrant.
      index where(const Geometry::Rectangle<T> &);
      //. Returns the quadrant the item i belongs into. Returns 'fence'
      //. if the item i intersects more then one quadrant.
      index where(I i) { return where(i->bbox()); }

      //. The region this node occupies,
      Geometry::Rectangle<T> my_region;
      //. The boundingbox of all objects in this node.
      Geometry::Rectangle<T> my_boundingbox;

      //. Total count of objects at or below this level
      int my_elements;
      //. Items straddling the fence
      list my_items;
      //. The quadrants of this node.
      QTNode<T, I> *my_quadrants[4];

      //. Dumps the data for this node and its subnotes if there are any.
      friend void dumpQuadNode(const QTNode<T,I> &node, short ind)
      {
	  for (short i = 0; i != ind; i++) std::cout.put(' ');
	  std::cout << "Node : " << node.elements
		    << '(' << node.items.size()
		    << ") elements, extension : "
		    << node.region << std::endl;
	  for (typename list::const_iterator i = node.items.begin();
	       i != node.items.end();
	       ++i)
	      std::cout << (*i)->boundingbox << ';';
	  std::cout << std::endl;
	  if (!node.leaf())
	      for (short i = 0; i != 4; i++)
		  dumpQuadNode(*node.my_quadrants[i], ind + 2);
      }
  };

  template <class T, class I>
  class QuadTree
  {
    public:
      //. Creates an empty QuadTree.
      QuadTree() : my_quad(0) { }
      ~QuadTree() { }
      
      //. Returns the bounding box of all items in the QuadTree.
      Geometry::Rectangle<T> bbox()
      { return node() ? node()->bbox() : Geometry::Rectangle<T>(); }
      //. Returns the number of items in this QuadTree.
      int size() { return my_quad ? my_quad->size() : 0; }
      //. Returns the rootnode of the QuadTree.
      QTNode<T, I> *node() { return my_quad; }
    protected:
      QTNode<T, I> *my_quad;
      
      //. Dumps the data for this QuadTree.
      friend void dumpQuadTree(const QuadTree<T,I> &tree)
      {
	  if (tree.my_quad) dumpQuadNode(*tree.my_quad, 0);
      }
  };

  // inline functions only below this line.

  template <class T, class I>
  inline void QTNode<T, I>::allocate()
  {
      using namespace Geometry;
      if (leaf())
      {
	  my_quadrants[lefttop] =
	      new QTNode<T, I>(Rectangle<T>(my_region.l, my_region.t,
					    my_region.cx(),
					    my_region.cy()));
	  my_quadrants[righttop] =
	      new QTNode<T, I>(Rectangle<T>(my_region.cx(), my_region.t,
					    my_region.r, my_region.cy()));
	  my_quadrants[leftbottom] =
	      new QTNode<T, I>(Rectangle<T>(my_region.l, my_region.cy(),
					    my_region.cx(), my_region.b));
	  my_quadrants[rightbottom] =
	      new QTNode<T, I>(Rectangle<T>(my_region.cx(), my_region.cy(),
					    my_region.r, my_region.b));
      }
  }
  
  template <class T, class I>
  inline void QTNode<T, I>::adjust(int min, int max, T min_w, T min_h)
  {
      // If we are over the maximum then unfold
      // and push down as many objects as we can.
      if (my_items.size() > (uint) max &&
	  ((my_region.w() > (min_w * 2)) || (my_region.h() > (min_h * 2))))
	  unfold();
      if (!leaf())
      {
	  for (int i = 0; i < 4; ++i)
	      my_quadrants[i]->adjust(min, max, min_w, min_h);
	  // If our sub-tree is under the minimum then flatten it away.
	  if (my_elements < min || my_elements - my_items.size() == 0 ||
	      (my_region.w() < min_w && my_region.h() < min_h))
	      collaps();
      }
  }
  
  template <class T, class I>
  inline void QTNode<T, I>::unfold()
  {
      if (! leaf()) return;
      allocate();
      typename list::iterator i =
	  remove_if(my_items.begin(), my_items.end(), move_down(this));
      my_items.erase(i, my_items.end());
  }

  template <class T, class I>
  inline void QTNode<T, I>::collaps()
  {
      if (leaf()) return;
      for (int i = 0; i < 4; i++)
      {
	  QTNode<T, I> *node = my_quadrants[i];
	  node->collaps();
	  list childItems = node->my_items;
	  my_items.insert(my_items.end(),
			  childItems.begin(), childItems.end());
      }
      free();
  }

  template <class T, class I>
  inline typename QTNode<T, I>::index
  QTNode<T, I>::where(const Geometry::Rectangle<T> &r)
  {
      int idx = fence;
      if (!leaf())
      {
	  const T x = my_region.cx();
	  const T y = my_region.cy();
	  // is r inside one of the quarters ?
	  if ((r.r <= x) == (r.l < x) && (r.b <= y) == (r.t < y))
	      idx = (r.r <= x ? left : right) | (r.b <= y ? top : bottom);
      }
      return static_cast<index>(idx);
  }

  template <class T, class I>
  inline void QTNode<T, I>::insert(I i)
  {
      index idx = where(i);
      if (idx == fence) my_items.push_back(i);
      else my_quadrants[idx]->insert(i);
      my_elements++;
      
      const Geometry::Rectangle<T> &bb = i->bbox();
      if (my_elements > 1) my_boundingbox.merge(bb);
      else my_boundingbox = bb;
  }

  template <class T, class I>
  inline void QTNode<T, I>::remove(I i)
  {
      index idx = where(i);
      if (idx == fence)
      {
	  for (typename list::iterator j = my_items.begin();
	       j != my_items.end();
	       ++j)
	      if (*j == i)
	      {
		  my_items.erase(j);
		  break;
	      }
      }
      else my_quadrants[idx]->remove(i);
      my_elements--;
      
      if (my_boundingbox.touches(i->bbox(), epsilon))
      {
	  my_boundingbox.clear();
	  bool first = true;
	  for (typename list::iterator j = my_items.begin();
	       j != my_items.end();
	       ++j)
	  {
	      if (first)
	      {
		  my_boundingbox = (*j)->bbox();
		  first = false;
	      }
	      else my_boundingbox.merge((*j)->bbox());
	  }
	  if (!leaf())
	  {
	      for (int j = 0; j < 4; j++)
	      {
		  QTNode<T, I> *node = my_quadrants[j];
		  if (node->my_elements > 0)
		  {
		      if (first)
		      {
			  my_boundingbox = node->bbox();
			  first = false;
		      }
		      else my_boundingbox.merge(node->bbox());
		  }
	      }
	  }
      }
  }

} // namespace

#endif
