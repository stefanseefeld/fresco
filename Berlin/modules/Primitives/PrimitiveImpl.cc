/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include <Prague/Sys/Tracer.hh>
#include <Warsaw/config.hh>
#include <Warsaw/PickTraversal.hh>
#include <Warsaw/DrawTraversal.hh>
#include <Warsaw/DrawingKit3D.hh>
#include <Warsaw/IO.hh>
#include <Berlin/Geometry.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Color.hh>
#include <Berlin/Vertex.hh>
#include <Berlin/Provider.hh>
#include "Primitive/PrimitiveImpl.hh"

using namespace Geometry;
using namespace Prague;
using namespace Warsaw;

TransformPrimitive::TransformPrimitive()
  : //_mode(Figure::outline),
    _tx(new TransformImpl),
    _ext(new RegionImpl)
{
  //  _fg.red = _fg.green = _fg.blue = 0., _fg.alpha = 1.;
  //  _bg.red = _bg.green = _bg.blue = 0., _bg.alpha = 1.;
}

TransformPrimitive::~TransformPrimitive() {}
Transform_ptr TransformPrimitive::transformation() { return _tx->_this();}
void TransformPrimitive::request(Warsaw::Graphic::Requisition &r)
{
  Trace trace("TransformPrimitive::request");
  Allocation::Info info;
  Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
  extension(info, Region_var(region->_this()));
  if (region->valid)
    {
      Coord x_lead = -region->lower.x, x_trail = region->upper.x;
      Coord y_lead = -region->lower.y, y_trail = region->upper.y;
      Coord z_lead = -region->lower.z, z_trail = region->upper.z;
      GraphicImpl::require_lead_trail(r.x, x_lead, x_lead, x_lead, x_trail, x_trail, x_trail);
      GraphicImpl::require_lead_trail(r.y, y_lead, y_lead, y_lead, y_trail, y_trail, y_trail);
      GraphicImpl::require_lead_trail(r.z, z_lead, z_lead, z_lead, z_trail, z_trail, z_trail);
    }
  else
    {
      r.x.defined = false;
      r.y.defined = false;
      r.z.defined = false;
    }
}

void TransformPrimitive::extension(const Allocation::Info &info, Region_ptr region)
{
  Trace trace("TransformPrimitive::extension");
  if (_ext->valid)
    {
      Lease_var<RegionImpl> tmp(Provider<RegionImpl>::provide());
      tmp->copy(Region_var(_ext->_this()));
      tmp->xalign = tmp->yalign = tmp->zalign = 0.;
      Lease_var<TransformImpl> transformation(Provider<TransformImpl>::provide());
      if (!CORBA::is_nil(info.transformation)) transformation->copy(info.transformation);
      transformation->premultiply(Transform_var(_tx->_this()));
      tmp->apply_transform(Transform_var(transformation->_this()));
      region->merge_union(Region_var(tmp->_this()));
    }
}

void TransformPrimitive::pick(PickTraversal_ptr traversal)
{
  if (_ext->valid && traversal->intersects_region(Region_var(_ext->_this())))
    traversal->hit();
}

void TransformPrimitive::need_redraw()
{
  Trace trace("TransformPrimitive::need_redraw");
  Allocation::Info info;
  Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
  extension(info, Region_var(region->_this()));
  need_redraw_region(Region_var(region->_this()));
}

void TransformPrimitive::resize() {}
void TransformPrimitive::copy(const TransformPrimitive &tp)
{
  //  _mode = tp._mode;
  //  _fg = tp._fg;
  //  _bg = tp._bg;
  _tx->copy(Transform_var(tp._tx->_this()));
  if (tp._ext->valid) _ext->copy(Region_var(tp._ext->_this()));
}

PrimitiveImpl::PrimitiveImpl() : _mesh(new Warsaw::Mesh()) {}
PrimitiveImpl::~PrimitiveImpl() {}

void PrimitiveImpl::draw(DrawTraversal_ptr traversal)
{
  Trace trace("PrimitiveImpl::draw");
  if (_mesh->nodes.length() > 0)
    {
      // bounding box culling, use extension(...) to add brush effect into extension.
      Allocation::Info info;
      Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
      extension(info, Region_var(region->_this()));
      if (traversal->intersects_region(Region_var(region->_this())))
	{
	  DrawingKit_var drawing = traversal->drawing();
	  DrawingKit3D_var d3d = DrawingKit3D::_narrow(drawing);
	  if (CORBA::is_nil(d3d)) return;
	  d3d->save();
// 	  Transform_var tmp = d3d->transformation();
// 	  Lease_var<TransformImpl> cumulative(Provider<TransformImpl>::provide());
// 	  cumulative->copy(Transform_var(d3d->transformation()));
// 	  cumulative->premultiply(Transform_var(_tx->_this()));
// 	  d3d->transformation(Transform_var(cumulative->_this()));

//  	  if (_mode & Figure::fill)
//  	    {
// 	      drawing->foreground(_bg);
// 	      drawing->surface_fillstyle(DrawingKit::solid);
// 	      drawing->draw_mesh(_mesh);
// 	    }
//  	  if (_mode & Figure::outline)
// 	    {
// 	      drawing->foreground(_fg);
// 	      drawing->surface_fillstyle(DrawingKit::outlined);
	  d3d->draw_mesh(_mesh);
	  d3d->restore();
	}
    }
}

/*
 * Picking just does a bounding box test for now.
 */

void PrimitiveImpl::pick(PickTraversal_ptr traversal)
{
  TransformPrimitive::pick(traversal);
  return;
  if (_ext->valid)
    {
      if (traversal->intersects_region(Region_var(_ext->_this())))
 	{
// 	  Vertex lower, upper, center;
// 	  Region_var visible = p->visible();
// 	  visible->bounds(lower, upper);
// 	  visible->center(center);
// 	  bool hit = false;

// 	  // FvD - define the surrounding box of the figure in terms
// 	  // of display pixels rather than coordinates ... cause if
// 	  // you scale > 1 you figure your picking rect will grow too
// 	  TransformImpl::Matrix mat;
// 	  Transform_var(p->current_matrix())->store_matrix(mat);
// 	  // FvD I agree, the old code was buggy on rotated figures ... -sigh
// 	  // so we have to pay the price - sniff (I know, it's still a crapy
// 	  Coord xspace = 4.0 / (mat[0][0]*mat[0][0] + mat[0][1]*mat[0][1]);
// 	  Coord yspace = 4.0 / (mat[1][0]*mat[1][0] + mat[1][1]*mat[1][1]);
// 	  xspace = sqrt(xspace);
// 	  yspace = sqrt(yspace);
// 	  BoxObj box(lower.x-xspace, lower.y-yspace, upper.x+xspace, upper.y+yspace);
// 	  //BoxObj box(lower.x-Coord(2), lower.y-Coord(2), upper.x+Coord(2), upper.y+Coord(2));
// 	  if (!closed_ && !curved_)
// 	    {
// 	      if (mode_ == FigureKit::stroke)
// 		{
// 		  MultiLineObj ml(v_);
// 		  PointObj pt(center.x, center.y);
// 		  if (ml.intersects(box)) hit = true;
//                 }
// 	      else if (mode_ == FigureKit::fill_stroke ||
// 		       mode_ == FigureKit::fill)
// 		{
// 		  FillPolygonObj fp(v_);
// 		  PointObj pt(center.x, center.y);
// 		  if (fp.intersects(box)) hit = true;
// 		}
//             }
// 	  else if (closed_ && !curved_)
// 	    {
// 	      if (mode_ == FigureKit::stroke)
// 		{
// 		  grow_vertices(v_);
// 		  (*v_)[v_->_length] = (*v_)[0];
// 		  v_->_length++;
// 		  MultiLineObj ml(v_);
// 		  if (ml.intersects(box)) hit = true;
// 		  v_->_length--;
//                 }
// 	      else if (mode_ == FigureKit::fill_stroke ||
// 		       mode_ == FigureKit::fill)
// 		{
// 		  FillPolygonObj fp(v_);
// 		  PointObj pt(center.x, center.y);
// 		  if (fp.intersects(box)) hit = true;
//                 }
//             }
// 	  else if (!closed_ && curved_)
// 	    {
// 	      if (mode_ == FigureKit::stroke)
// 		{
// 		  MultiLineObj ml;
// 		  ml.spline_to_multiline(*v_);
// 		  PointObj pt(center.x, center.y);
// 		  if (ml.intersects(box)) hit = true;
//                 }
// 	      else if (mode_ == FigureKit::fill_stroke ||
// 		       mode_ == FigureKit::fill)
// 		{
// 		  FillPolygonObj fp;
// 		  fp.closed_spline_to_polygon(*v_);
// 		  if (fp.intersects(box)) hit = true;
//                 }
//             }
// 	  else
// 	    {
// 	      if (mode_ == FigureKit::stroke)
// 		{
// 		  MultiLineObj ml;
// 		  ml.closed_spline_to_polygon(*v_);
// 		  if (ml.intersects(box)) hit = true;
//                 }
// 	      else if (mode_ == FigureKit::fill_stroke ||
// 		       mode_ == FigureKit::fill)
// 		{
// 		  FillPolygonObj fp;
// 		  fp.closed_spline_to_polygon(*v_);
// 		  if (fp.intersects(box)) hit = true;
//                 }
//             }
// 	  if (hit) t->hit();
 	}
      traversal->hit();
    }
}

/*
 * Reset the primitive's list of vertices
 */

void PrimitiveImpl::resize()
{
  _ext->valid = false;
  if (_mesh->nodes.length() > 0)
    {
      _ext->valid = true;
      _ext->lower = _mesh->nodes[0];
      _ext->upper = _mesh->nodes[0];
      CORBA::ULong n = _mesh->nodes.length();
      for (CORBA::ULong i = 1; i < n; ++i)
 	{
 	  _ext->lower.x = Math::min(_ext->lower.x, _mesh->nodes[i].x);
 	  _ext->upper.x = Math::max(_ext->upper.x, _mesh->nodes[i].x);
 	  _ext->lower.y = Math::min(_ext->lower.y, _mesh->nodes[i].y);
 	  _ext->upper.y = Math::max(_ext->upper.y, _mesh->nodes[i].y);
 	  _ext->lower.z = Math::min(_ext->lower.z, _mesh->nodes[i].z);
 	  _ext->upper.z = Math::max(_ext->upper.z, _mesh->nodes[i].z);
	}
      // in case of vertical/horizontal line with nil brush, 
      // painter->is_visible will be return false, so add 1
//       if ((ext_.lower_.x == ext_.upper_.x) ||
//  	  (ext_.lower_.y == ext_.upper_.y)) 
// 	ext_.upper_.x +=1; ext_.upper_.y +=1;
    }	
}

void PrimitiveImpl::reset()
{
//   _mesh = new Warsaw::Mesh();
  _ext->valid = false;
}

void PrimitiveImpl::copy(const PrimitiveImpl &p)
{
  TransformPrimitive::copy(p);
  _mesh = new Warsaw::Mesh(p._mesh);
}
