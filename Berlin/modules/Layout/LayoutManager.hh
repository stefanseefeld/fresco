/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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
#ifndef _LayoutManager_hh
#define _LayoutManager_hh

#include <Warsaw/config.hh>
#include <Warsaw/Graphic.hh>
#include <Warsaw/Region.hh>

class RegionImpl;

class LayoutManager
{
public:
  typedef RegionImpl **Allocations;

  LayoutManager();
  virtual ~LayoutManager();
  virtual LayoutManager *clone() = 0;

  virtual char *name() = 0;

  virtual void request(long n, Warsaw::Graphic::Requisition *requests, Warsaw::Graphic::Requisition &result) = 0;
  virtual void allocate(long n, Warsaw::Graphic::Requisition *requests, Warsaw::Region_ptr given, LayoutManager::Allocations result) = 0;

  static void set_span(RegionImpl *r, Warsaw::Axis a, Warsaw::Coord origin, Warsaw::Coord length, Warsaw::Alignment align);
};

//. LayoutAlign -- align positions along an axis
class LayoutAlign : public LayoutManager
{
public:
  LayoutAlign(Warsaw::Axis);
  virtual ~LayoutAlign();
  virtual LayoutManager *clone();

  virtual char *name() { return "Align";}

  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);
private:
  Warsaw::Axis axis;
};

//. LayoutCenter -- center positions along an axis
class LayoutCenter : public LayoutManager
{
public:
  LayoutCenter(Warsaw::Axis, Warsaw::Alignment a);
  virtual ~LayoutCenter();

  virtual char *name() { return "Center";}

  virtual LayoutManager *clone();
  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);
private:
  Warsaw::Axis      _axis;
  Warsaw::Alignment _alignment;
};

//. LayoutFixed -- set size along an axis
class LayoutFixed : public LayoutManager
{
public:
  LayoutFixed(Warsaw::Axis, Warsaw::Coord);
  virtual ~LayoutFixed();

  virtual char *name() { return "Fixed";}

  virtual LayoutManager *clone();
  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);
private:
  Warsaw::Axis  _axis;
  Warsaw::Coord _size;
};

//. LayoutVariable -- allow flexibility along an axis
class LayoutVariable : public LayoutManager
{
public:
  LayoutVariable(Warsaw::Axis, Warsaw::Coord stretch, Warsaw::Coord shrink);
  virtual ~LayoutVariable();

  virtual char *name() { return "Variable";}

  virtual LayoutManager* clone();
  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);
private:
  Warsaw::Axis  _axis;
  Warsaw::Coord _stretch;
  Warsaw::Coord _shrink;
};

//. LayoutNatural -- set the natural size along an axis
class LayoutNatural : public LayoutManager
{
public:
  LayoutNatural(Warsaw::Axis, Warsaw::Coord);
  virtual ~LayoutNatural();

  virtual char *name() { return "Natural";}

  virtual LayoutManager *clone();
  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);
private:
  Warsaw::Axis axis;
  Warsaw::Coord natural;
};

//. LayoutMargin -- leave a margin around the sides
class LayoutMargin : public LayoutManager
{
public:
  LayoutMargin(Warsaw::Coord);
  LayoutMargin(Warsaw::Coord, Warsaw::Coord);
  LayoutMargin(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  LayoutMargin(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord,
	       Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord,
	       Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual ~LayoutMargin();

  virtual char *name() { return "Margin";}

  virtual LayoutManager *clone();
  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);
private:
  void allocate_axis(Warsaw::Axis, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord,
		     Warsaw::Coord, Warsaw::Coord, LayoutManager::Allocations);
  static Warsaw::Coord span(Warsaw::Coord, Warsaw::Graphic::Requirement &, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);

  Warsaw::Coord _lnatural, _lstretch, _lshrink;
  Warsaw::Coord _rnatural, _rstretch, _rshrink;
  Warsaw::Coord _bnatural, _bstretch, _bshrink;
  Warsaw::Coord _tnatural, _tstretch, _tshrink;
  Warsaw::Graphic::Requisition _requisition;
};

//. LayoutSuperpose - composite layout manager
class LayoutSuperpose : public LayoutManager
{
public:
  LayoutSuperpose(LayoutManager *, LayoutManager *);
  LayoutSuperpose(LayoutManager *, LayoutManager *, LayoutManager *);
  virtual ~LayoutSuperpose();
  virtual LayoutManager *clone();

  virtual char *name() { return _name;}

  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);
private:
  char          *_name;
  LayoutManager *_first;
  LayoutManager *_second;
  LayoutManager *_third;
};

//. LayoutTile -- side-by-side, first-to-last along an axis
class LayoutTile : public LayoutManager
{
public:
  LayoutTile(Warsaw::Axis);
  virtual ~LayoutTile();
  virtual LayoutManager *clone();

  virtual char *name() { return _name;}

  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);

  static void compute_request(Warsaw::Axis, Warsaw::Alignment, long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  static void compute_allocations(Warsaw::Axis, Warsaw::Graphic::Requisition &, bool, long, Warsaw::Graphic::Requisition *,
				  Warsaw::Region_ptr, LayoutManager::Allocations);
  static Warsaw::Coord compute_length(const Warsaw::Graphic::Requirement &, const Warsaw::Region::Allotment &);
  static Warsaw::Coord compute_squeeze(const Warsaw::Graphic::Requirement &, Warsaw::Coord);
private:
  char                        *_name;
  Warsaw::Axis                 _axis;
  Warsaw::Graphic::Requisition _requisition;
};

//. LayoutTileReversed -- side-by-side, last-to-first
class LayoutTileReversed : public LayoutManager
{
public:
  LayoutTileReversed(Warsaw::Axis);
  virtual ~LayoutTileReversed();
  virtual LayoutManager *clone();

  virtual char *name() { return "TileReversed";}

  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);
  static void compute_reversed_allocations(Warsaw::Axis, Warsaw::Graphic::Requisition &, bool, long, Warsaw::Graphic::Requisition *,
					   Warsaw::Region_ptr, LayoutManager::Allocations);
private:
  Warsaw::Axis                 _axis;
  Warsaw::Graphic::Requisition _requisition;
};

//. LayoutTileFirstAligned -- like Tile but use first element's origin
class LayoutTileFirstAligned : public LayoutManager
{
public:
  LayoutTileFirstAligned(Warsaw::Axis);
  virtual ~LayoutTileFirstAligned();
  virtual LayoutManager *clone();

  virtual char *name() { return "TileFirstAligned";}

  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);
  static void compute_request_first_aligned(Warsaw::Axis, long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
private:
  Warsaw::Axis                 _axis;
  Warsaw::Graphic::Requisition _requisition;
};

//. LayoutTileReversedFirstAligned -- like TileReversed
//. but use first element's origin
class LayoutTileReversedFirstAligned : public LayoutManager
{
public:
  LayoutTileReversedFirstAligned(Warsaw::Axis);
  virtual ~LayoutTileReversedFirstAligned();
  virtual LayoutManager *clone();

  virtual char *name() { return "TileReversedFirstAligned";}

  virtual void request(long, Warsaw::Graphic::Requisition *, Warsaw::Graphic::Requisition &);
  virtual void allocate(long, Warsaw::Graphic::Requisition *, Warsaw::Region_ptr, LayoutManager::Allocations);
private:
  Warsaw::Axis                 _axis;
  Warsaw::Graphic::Requisition _requisition;
};

#endif
