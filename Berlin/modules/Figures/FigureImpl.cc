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
#include <Fresco/PickTraversal.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/IO.hh>
#include <Berlin/Geometry.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Color.hh>
#include <Berlin/Vertex.hh>
#include <Berlin/Provider.hh>
#include "FigureImpl.hh"

using namespace Geometry;
using namespace Prague;
using namespace Fresco;

using namespace Berlin::FigureKit;

TransformFigure::TransformFigure() :
    my_mode(Figure::outline),
    my_tx(new TransformImpl),
    my_ext(new RegionImpl)
{
    my_fg.red = my_fg.green = my_fg.blue = 0., my_fg.alpha = 1.;
    my_bg.red = my_bg.green = my_bg.blue = 0., my_bg.alpha = 1.;
}

TransformFigure::~TransformFigure() { }
Transform_ptr TransformFigure::transformation() { return my_tx->_this(); }
void TransformFigure::request(Fresco::Graphic::Requisition &r)
{
    Trace trace("TransformFigure::request");
    Allocation::Info info;
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    extension(info, Region_var(region->_this()));
    if (region->valid)
    {
    Coord x_lead = -region->lower.x, x_trail = region->upper.x;
    Coord y_lead = -region->lower.y, y_trail = region->upper.y;
    GraphicImpl::require_lead_trail(r.x,
                    x_lead, x_lead, x_lead,
                    x_trail, x_trail, x_trail);
    GraphicImpl::require_lead_trail(r.y,
                    y_lead, y_lead, y_lead,y_trail,
                    y_trail, y_trail);
    r.z.defined = false;
    }
    else
    {
    r.x.defined = false;
    r.y.defined = false;
    r.z.defined = false;
    }
}

void TransformFigure::extension(const Allocation::Info &info,
                Region_ptr region)
{
    Trace trace("TransformFigure::extension");
    if (my_ext->valid)
    {
    Lease_var<RegionImpl> tmp(Provider<RegionImpl>::provide());
    tmp->copy(Region_var(my_ext->_this()));
    tmp->xalign = tmp->yalign = tmp->zalign = 0.;
    Lease_var<TransformImpl>
        transformation(Provider<TransformImpl>::provide());
    if (!CORBA::is_nil(info.transformation))
        transformation->copy(info.transformation);
    transformation->premultiply(Transform_var(my_tx->_this()));
    tmp->apply_transform(Transform_var(transformation->_this()));
    region->merge_union(Region_var(tmp->_this()));
    }
}

void TransformFigure::pick(PickTraversal_ptr traversal)
{
    if (my_ext->valid &&
    traversal->intersects_region(Region_var(my_ext->_this())))
    traversal->hit();
}

void TransformFigure::need_redraw()
{
    Trace trace("TransformFigure::need_redraw");
    Allocation::Info info;
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    extension(info, Region_var(region->_this()));
    need_redraw_region(Region_var(region->_this()));
}

void TransformFigure::resize() { }
void TransformFigure::copy(const TransformFigure &tf)
{
    my_mode = tf.my_mode;
    my_fg = tf.my_fg;
    my_bg = tf.my_bg;
    my_tx->copy(Transform_var(tf.my_tx->_this()));
    if (tf.my_ext->valid) my_ext->copy(Region_var(tf.my_ext->_this()));
}

FigureImpl::FigureImpl() : my_path(new Fresco::Path())
{ my_path->shape = convex; }
FigureImpl::~FigureImpl() { }

void FigureImpl::add_point(Coord x, Coord y)
{
    if (my_path->nodes.length() == 0)
    {
    my_ext->lower.x = x;
    my_ext->upper.x = x;
    my_ext->lower.y = y;
    my_ext->upper.y = y;
    my_ext->valid = true;
    }
    else
    {
    my_ext->lower.x = Math::min(my_ext->lower.x, x);
    my_ext->upper.x = Math::max(my_ext->upper.x, x);
    my_ext->lower.y = Math::min(my_ext->lower.y, y);
    my_ext->upper.y = Math::max(my_ext->upper.y, y);
    }
    Vertex v;
    v.x = x;
    v.y = y;
    v.z = 0.;
    CORBA::ULong n = my_path->nodes.length();
    my_path->nodes.length(n + 1);
    my_path->nodes[n] = v;
}

void FigureImpl::extension(const Allocation::Info &info, Region_ptr region)
{
    Trace trace("FigureImpl::extension");
    if (my_path->nodes.length() > 0)
    {
    Lease_var<RegionImpl> tmp(Provider<RegionImpl>::provide());
    tmp->copy(Region_var(my_ext->_this()));
    tmp->xalign = tmp->yalign = tmp->zalign = 0.;
    Lease_var<TransformImpl>
        transformation(Provider<TransformImpl>::provide());
    transformation->copy(info.transformation);
    transformation->premultiply(Transform_var(my_tx->_this()));
    tmp->apply_transform(Transform_var(transformation->_this()));
    if (my_mode & Figure::outline)
    {
//             Coord w = 1.;
//             if (is_not_nil(style_))
//             {
//                 Brush_var b = style_->brush_attr();
//                 if (is_not_nil(b))
//                 {
//                     XfBrush::Info* i;
//                     b->brush_info(i);
//                     if (!Math::equal(i->width, float(0), float(1e-2)))
//                         w = i->width;
//                 }
//             }
//            tmp->lower.x -= w; tmp->upper.x += w;
//            tmp->lower.y -= w; tmp->upper.y += w;
//            tmp->lower.z -= w; tmp->upper.z += w;
    }
    region->merge_union(Region_var(tmp->_this()));
    }
}

void FigureImpl::draw(DrawTraversal_ptr traversal)
{
    Trace trace("FigureImpl::draw");
    if (my_path->nodes.length() > 0)
    {
    // bounding box culling, use extension(...) to add brush
    // effect into extension.
    Allocation::Info info;
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    extension(info, Region_var(region->_this()));
    if (traversal->intersects_region(Region_var(region->_this())))
    {
        DrawingKit_var drawing = traversal->drawing();
        Color color = drawing->foreground();
        drawing->save();
        Transform_var tmp = drawing->transformation();
        Lease_var<TransformImpl>
        cumulative(Provider<TransformImpl>::provide());
        cumulative->copy(Transform_var(drawing->transformation()));
        cumulative->premultiply(Transform_var(my_tx->_this()));
        drawing->transformation(Transform_var(cumulative->_this()));
//             if (my_mode & Figure::fill)
//             {
//                 drawing->foreground(my_bg);
//                 drawing->surface_fillstyle(DrawingKit::solid);
//                 drawing->draw_path(my_path);
//             }
//             if (my_mode & Figure::outline)
//             {
//                 drawing->foreground(my_fg);
//                 drawing->surface_fillstyle(DrawingKit::outlined);
        drawing->draw_path(my_path);
//         }
        drawing->restore();
    }
    }
}

// Picking just does a bounding box test for now.
void FigureImpl::pick(PickTraversal_ptr traversal)
{
    TransformFigure::pick(traversal);
    return;
    if (my_ext->valid)
    {
    if (traversal->intersects_region(Region_var(my_ext->_this())))
     {
//         Vertex lower, upper, center;
//         Region_var visible = p->visible();
//         visible->bounds(lower, upper);
//         visible->center(center);
//         bool hit = false;

//         // FvD - define the surrounding box of the figure in terms
//         // of display pixels rather than coordinates ... cause if
//         // you scale > 1 you figure your picking rect will grow too
//         TransformImpl::Matrix mat;
//         Transform_var(p->current_matrix())->store_matrix(mat);
//         // FvD I agree, the old code was buggy on rotated figures ... -sigh
//         // so we have to pay the price - sniff (I know, it's still a crapy
//         Coord xspace = 4.0 / (mat[0][0]*mat[0][0] + mat[0][1]*mat[0][1]);
//         Coord yspace = 4.0 / (mat[1][0]*mat[1][0] + mat[1][1]*mat[1][1]);
//         xspace = sqrt(xspace);
//         yspace = sqrt(yspace);
//         BoxObj box(lower.x-xspace, lower.y-yspace, upper.x+xspace, upper.y+yspace);
//         //BoxObj box(lower.x-Coord(2), lower.y-Coord(2), upper.x+Coord(2), upper.y+Coord(2));
//         if (!closed_ && !curved_)
//         {
//         if (mode_ == FigureKit::stroke)
//         {
//             MultiLineObj ml(v_);
//             PointObj pt(center.x, center.y);
//             if (ml.intersects(box)) hit = true;
//                 }
//         else if (mode_ == FigureKit::fill_stroke ||
//              mode_ == FigureKit::fill)
//         {
//             FillPolygonObj fp(v_);
//             PointObj pt(center.x, center.y);
//             if (fp.intersects(box)) hit = true;
//         }
//             }
//         else if (closed_ && !curved_)
//         {
//         if (mode_ == FigureKit::stroke)
//         {
//             grow_vertices(v_);
//             (*v_)[v_->_length] = (*v_)[0];
//             v_->_length++;
//             MultiLineObj ml(v_);
//             if (ml.intersects(box)) hit = true;
//             v_->_length--;
//                 }
//         else if (mode_ == FigureKit::fill_stroke ||
//              mode_ == FigureKit::fill)
//         {
//             FillPolygonObj fp(v_);
//             PointObj pt(center.x, center.y);
//             if (fp.intersects(box)) hit = true;
//                 }
//             }
//         else if (!closed_ && curved_)
//         {
//         if (mode_ == FigureKit::stroke)
//         {
//             MultiLineObj ml;
//             ml.spline_to_multiline(*v_);
//             PointObj pt(center.x, center.y);
//             if (ml.intersects(box)) hit = true;
//                 }
//         else if (mode_ == FigureKit::fill_stroke ||
//              mode_ == FigureKit::fill)
//         {
//             FillPolygonObj fp;
//             fp.closed_spline_to_polygon(*v_);
//             if (fp.intersects(box)) hit = true;
//                 }
//             }
//         else
//         {
//         if (mode_ == FigureKit::stroke)
//         {
//             MultiLineObj ml;
//             ml.closed_spline_to_polygon(*v_);
//             if (ml.intersects(box)) hit = true;
//                 }
//         else if (mode_ == FigureKit::fill_stroke ||
//              mode_ == FigureKit::fill)
//         {
//             FillPolygonObj fp;
//             fp.closed_spline_to_polygon(*v_);
//             if (fp.intersects(box)) hit = true;
//                 }
//             }
//         if (hit) t->hit();
     }
    traversal->hit();
    }
}

// Reset the figure's list of vertices
void FigureImpl::resize()
{
    my_ext->valid = false;
    if (my_path->nodes.length() > 0)
    {
    my_ext->valid = true;
    my_ext->lower = my_path->nodes[0];
    my_ext->upper = my_path->nodes[0];
    CORBA::ULong n = my_path->nodes.length();
    for (CORBA::ULong i = 1; i < n; i++)
    {
        my_ext->lower.x = Math::min(my_ext->lower.x,
                    my_path->nodes[i].x);
        my_ext->upper.x = Math::max(my_ext->upper.x,
                    my_path->nodes[i].x);
        my_ext->lower.y = Math::min(my_ext->lower.y,
                    my_path->nodes[i].y);
        my_ext->upper.y = Math::max(my_ext->upper.y,
                    my_path->nodes[i].y);
        }
//     // in case of vertical/horizontal line with nil brush, 
//     // painter->is_visible will be return false, so add 1
//     if ((ext_.lower_.x == ext_.upper_.x) ||
//         (ext_.lower_.y == ext_.upper_.y)) 
//         ext_.upper_.x +=1; ext_.upper_.y +=1;
    }    
}

void FigureImpl::reset()
{
    my_path = new Fresco::Path();
    my_path->shape = convex;
    my_ext->valid = false;
}

void FigureImpl::copy(const FigureImpl &f)
{
    TransformFigure::copy(f);
    my_path = new Fresco::Path(f.my_path);
    my_path->shape = convex;
}
