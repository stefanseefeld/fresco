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
#ifndef _Berlin_RegionImpl_hh
#define _Berlin_RegionImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Region.hh>
#include <Berlin/ServantBase.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/Vertex.hh>
#include <Berlin/Math.hh>
#include <Berlin/Provider.hh>
#include <iostream>

namespace Berlin
{

  class RegionImpl;
  template <> struct Initializer<RegionImpl>;

  class RegionImpl : public virtual POA_Fresco::Region,
		     public virtual ServantBase
  {
      friend class Provider<RegionImpl>;
    public:
      RegionImpl();
      RegionImpl(const RegionImpl &);
      RegionImpl(Fresco::Region_ptr);
      RegionImpl(Fresco::Region_ptr, Fresco::Transform_ptr);
      RegionImpl(Fresco::Region_ptr, TransformImpl *);
      virtual ~RegionImpl();
      RegionImpl &operator = (const RegionImpl &);
      virtual CORBA::Boolean defined();
      virtual CORBA::Boolean contains(const Fresco::Vertex &);
      virtual CORBA::Boolean contains_plane(const Fresco::Vertex &,
					    Fresco::Axis a);
      virtual CORBA::Boolean intersects(Fresco::Region_ptr);
      CORBA::Boolean intersects(const RegionImpl &) const;
      virtual void copy(Fresco::Region_ptr);
      virtual void merge_intersect(Fresco::Region_ptr);
      virtual void merge_union(Fresco::Region_ptr);
      virtual void subtract(Fresco::Region_ptr);
      virtual void apply_transform(Fresco::Transform_ptr);
      void apply_transform(const Fresco::Transform::Matrix &);
      virtual void bounds(Fresco::Vertex &, Fresco::Vertex &);
      virtual void center(Fresco::Vertex &);
      virtual void origin(Fresco::Vertex &);
      virtual void span(Fresco::Axis, Fresco::Region::Allotment &);
      virtual void outline(Fresco::Path_out);
      
      void clear();
      
      Fresco::Region_ptr _this ()
      {
	  if (!my_this_valid)
	  {
	      my_this = POA_Fresco::Region::_this();
	      my_this_valid = true;
	  }
	  return Fresco::Region::_duplicate (my_this);
      }
      
    public:
      void normalize(Fresco::Vertex &);
      void normalize(Fresco::Transform_ptr);
      bool valid;
      Fresco::Vertex lower, upper;
      Fresco::Alignment xalign, yalign, zalign;

      static void merge_min(Fresco::Vertex &, const Fresco::Vertex &);
      static void merge_max(Fresco::Vertex &, const Fresco::Vertex &);
      static Fresco::Coord span_align(Fresco::Coord, Fresco::Coord,
				      Fresco::Coord);
      static Fresco::Coord span_origin(Fresco::Coord, Fresco::Coord,
				       Fresco::Coord);

    private:
      bool my_active : 1;
      bool my_this_valid;
      Fresco::Region_var my_this;
  };
  
  template <> struct Initializer<RegionImpl>
  {
      static void initialize(RegionImpl *r) { r->clear();}
  };
  
  inline Fresco::Coord RegionImpl::span_origin(Fresco::Coord lower,
					       Fresco::Coord upper,
					       Fresco::Coord align)
  {
      Fresco::Coord orig;
      if (Math::equal(lower, upper, 1e-4)) orig = 0.;
      else orig = lower + align * (upper - lower);
      return orig;
  }

  inline Fresco::Coord RegionImpl::span_align(Fresco::Coord lower,
					      Fresco::Coord upper,
					      Fresco::Coord origin)
  {
      Fresco::Coord s;
      if (Math::equal(lower, upper, 1e-4)) s = 0.;
      else s = (origin - lower) / (upper - lower);
      return s;
  }

  inline void RegionImpl::merge_min(Fresco::Vertex &v0,
				    const Fresco::Vertex &v)
  {
      v0.x = Math::min(v0.x, v.x);
      v0.y = Math::min(v0.y, v.y);
      v0.z = Math::min(v0.z, v.z);
  }
  
  inline void RegionImpl::merge_max(Fresco::Vertex &v0,
				    const Fresco::Vertex &v)
  {
      v0.x = Math::max(v0.x, v.x);
      v0.y = Math::max(v0.y, v.y);
      v0.z = Math::max(v0.z, v.z);
  }
  
  inline void RegionImpl::normalize(Fresco::Vertex &o)
  {
      o.x = span_origin(lower.x, upper.x, xalign);
      o.y = span_origin(lower.y, upper.y, yalign);
      o.z = span_origin(lower.z, upper.z, zalign);
      lower -= o;
      upper -= o;
  }
  
  inline void RegionImpl::normalize(Fresco::Transform_ptr t)
  {
      Fresco::Vertex o;
      normalize(o);
      if (!CORBA::is_nil(t)) t->translate(o);
  }

}

namespace std
{
  std::ostream &operator << (std::ostream &, const Berlin::RegionImpl &);
}

#endif
