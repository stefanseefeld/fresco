/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
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
#ifndef _Layout_LayoutManager_hh
#define _Layout_LayoutManager_hh

#include <Fresco/config.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/Region.hh>

class RegionImpl;

namespace Berlin
{
  namespace LayoutKit
  {

    class LayoutManager
    {
      public:
	typedef RegionImpl **Allocations;

	LayoutManager();
	virtual ~LayoutManager();
	virtual LayoutManager *clone() = 0;
	
	virtual char *name() = 0;

	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &) = 0;
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations) = 0;

	static void set_span(Berlin::RegionImpl *, Fresco::Axis,
			     Fresco::Coord, Fresco::Coord,
			     Fresco::Alignment);
    };
    
    //. LayoutAlign -- align positions along an axis
    class LayoutAlign : public LayoutManager
    {
      public:
	LayoutAlign(Fresco::Axis);
	virtual ~LayoutAlign();
	virtual LayoutManager *clone();
	
	virtual char *name() { return "Align";}

	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);
      private:
	Fresco::Axis my_axis;
    };

    //. LayoutCenter -- center positions along an axis
    class LayoutCenter : public LayoutManager
    {
      public:
	LayoutCenter(Fresco::Axis, Fresco::Alignment a);
	virtual ~LayoutCenter();

	virtual char *name() { return "Center"; }

	virtual LayoutManager *clone();
	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);
      private:
	Fresco::Axis      my_axis;
	Fresco::Alignment my_alignment;
    };

    //. LayoutFixed -- set size along an axis
    class LayoutFixed : public LayoutManager
    {
      public:
	LayoutFixed(Fresco::Axis, Fresco::Coord);
	virtual ~LayoutFixed();

	virtual char *name() { return "Fixed"; }

	virtual LayoutManager *clone();
	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);
      private:
	Fresco::Axis my_axis;
	Fresco::Coord my_size;
    };

    //. LayoutVariable -- allow flexibility along an axis
    class LayoutVariable : public LayoutManager
    {
      public:
	LayoutVariable(Fresco::Axis, Fresco::Coord stretch,
		       Fresco::Coord shrink);
	virtual ~LayoutVariable();

	virtual char *name() { return "Variable"; }
	
	virtual LayoutManager* clone();
	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);
      private:
	Fresco::Axis my_axis;
	Fresco::Coord my_stretch;
	Fresco::Coord my_shrink;
    };

    //. LayoutNatural -- set the natural size along an axis
    class LayoutNatural : public LayoutManager
    {
      public:
	LayoutNatural(Fresco::Axis, Fresco::Coord);
	virtual ~LayoutNatural();
	
	virtual char *name() { return "Natural"; }
	
	virtual LayoutManager *clone();
	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);
      private:
	Fresco::Axis my_axis;
	Fresco::Coord my_natural;
    };

    //. LayoutMargin -- leave a margin around the sides
    class LayoutMargin : public LayoutManager
    {
      public:
	LayoutMargin(Fresco::Coord);
	LayoutMargin(Fresco::Coord, Fresco::Coord);
	LayoutMargin(Fresco::Coord, Fresco::Coord, Fresco::Coord,
		     Fresco::Coord);
	LayoutMargin(Fresco::Coord, Fresco::Coord, Fresco::Coord,
		     Fresco::Coord, Fresco::Coord, Fresco::Coord,
		     Fresco::Coord, Fresco::Coord, Fresco::Coord,
		     Fresco::Coord, Fresco::Coord, Fresco::Coord);
	virtual ~LayoutMargin();

	virtual char *name() { return "Margin"; }

	virtual LayoutManager *clone();
	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);
      private:
	void allocate_axis(Fresco::Axis,
			   Fresco::Coord, Fresco::Coord, Fresco::Coord,
			   Fresco::Coord, Fresco::Coord, Fresco::Coord,
			   LayoutManager::Allocations);
	static Fresco::Coord span(Fresco::Coord,
				  Fresco::Graphic::Requirement &,
				  Fresco::Coord, Fresco::Coord,
				  Fresco::Coord);

	Fresco::Coord my_lnatural, my_lstretch, my_lshrink;
	Fresco::Coord my_rnatural, my_rstretch, my_rshrink;
	Fresco::Coord my_bnatural, my_bstretch, my_bshrink;
	Fresco::Coord my_tnatural, my_tstretch, my_tshrink;
	Fresco::Graphic::Requisition my_requisition;
    };

    //. LayoutSuperpose - composite layout manager
    class LayoutSuperpose : public LayoutManager
    {
      public:
	LayoutSuperpose(LayoutManager *, LayoutManager *);
	LayoutSuperpose(LayoutManager *, LayoutManager *, LayoutManager *);
	virtual ~LayoutSuperpose();
	virtual LayoutManager *clone();

	virtual char *name() { return my_name; }

	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);
      private:
	char          *my_name;
	LayoutManager *my_first;
	LayoutManager *my_second;
	LayoutManager *my_third;
    };

    //. LayoutTile -- side-by-side, first-to-last along an axis
    class LayoutTile : public LayoutManager
    {
      public:
	LayoutTile(Fresco::Axis);
	virtual ~LayoutTile();
	virtual LayoutManager *clone();

	virtual char *name() { return my_name; }

	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);

	static void compute_request(Fresco::Axis, Fresco::Alignment,
				    long, Fresco::Graphic::Requisition *,
				    Fresco::Graphic::Requisition &);
	static void compute_allocations(Fresco::Axis,
					Fresco::Graphic::Requisition &,
					bool, long,
					Fresco::Graphic::Requisition *,
					Fresco::Region_ptr,
					LayoutManager::Allocations);
	static Fresco::Coord
	compute_length(const Fresco::Graphic::Requirement &,
		       const Fresco::Region::Allotment &);
	static Fresco::Coord
	compute_squeeze(const Fresco::Graphic::Requirement &,
			Fresco::Coord);
      private:
	char                        *my_name;
	Fresco::Axis                 my_axis;
	Fresco::Graphic::Requisition my_requisition;
    };

    //. LayoutTileReversed -- side-by-side, last-to-first
    class LayoutTileReversed : public LayoutManager
    {
      public:
	LayoutTileReversed(Fresco::Axis);
	virtual ~LayoutTileReversed();
	virtual LayoutManager *clone();

	virtual char *name() { return "TileReversed"; }

	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);
	static void
	compute_reversed_allocations(Fresco::Axis,
				     Fresco::Graphic::Requisition &,
				     bool, long,
				     Fresco::Graphic::Requisition *,
				     Fresco::Region_ptr,
				     LayoutManager::Allocations);
      private:
	Fresco::Axis                 my_axis;
	Fresco::Graphic::Requisition my_requisition;
    };

    //. LayoutTileFirstAligned -- like Tile but use first element's origin
    class LayoutTileFirstAligned : public LayoutManager
    {
      public:
	LayoutTileFirstAligned(Fresco::Axis);
	virtual ~LayoutTileFirstAligned();
	virtual LayoutManager *clone();
	
	virtual char *name() { return "TileFirstAligned"; }

	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);
	static void
	compute_request_first_aligned(Fresco::Axis, long,
				      Fresco::Graphic::Requisition *,
				      Fresco::Graphic::Requisition &);
      private:
	Fresco::Axis                 my_axis;
	Fresco::Graphic::Requisition my_requisition;
    };

    //. LayoutTileReversedFirstAligned -- like TileReversed
    //. but use first element's origin
    class LayoutTileReversedFirstAligned : public LayoutManager
    {
      public:
	LayoutTileReversedFirstAligned(Fresco::Axis);
	virtual ~LayoutTileReversedFirstAligned();
	virtual LayoutManager *clone();
	
	virtual char *name() { return "TileReversedFirstAligned"; }

	virtual void request(long, Fresco::Graphic::Requisition *,
			     Fresco::Graphic::Requisition &);
	virtual void allocate(long, Fresco::Graphic::Requisition *,
			      Fresco::Region_ptr,
			      LayoutManager::Allocations);
      private:
	Fresco::Axis                 my_axis;
	Fresco::Graphic::Requisition my_requisition;
    };
    
  } // namespace
} // namespace

#endif
