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

#include <Fresco/config.hh>
#include <Fresco/DrawingKit3D.hh>
#include <Fresco/DrawTraversal.hh>
#include "Primitives.hh"

// using namespace Geometry;
using namespace Fresco;

using namespace Berlin::PrimitiveKit;

// PointImpl::PointImpl() { add_point(0., 0.); }
// PointImpl::PointImpl (const Vertex &v) { add_point(v.x, v.y); }
// PointImpl::PointImpl (const PointImpl &f) { copy(f); }
// PointImpl::~PointImpl() { }
// Vertex PointImpl::pt() { return my_path[0]; }
// void PointImpl::pt(const Vertex &v) { my_path[0] = v; resize();}

// LineImpl::LineImpl()
// {
//     add_point(0., 0.);
//     add_point(0., 0.);
// }

// LineImpl::LineImpl (const Vertex &v1, const Vertex &v2)
// {
//     add_point(v1.x, v1.y);
//     add_point(v2.x, v2.y);
// }

// LineImpl::LineImpl (const LineImpl &line) { copy(line); }
// LineImpl::~LineImpl() { }
// Vertex LineImpl::pt1() { return my_path[0]; }
// void LineImpl::pt1(const Vertex &v) { my_path[0] = v; resize(); }
// Vertex LineImpl::pt2() { return my_path[1]; }
// void LineImpl::pt2(const Vertex &v) { my_path[1] = v; resize(); }

BoxImpl::BoxImpl()
{
//   add_point(0., 0.);
//   add_point(0., 0.);
//   add_point(0., 0.);
//   add_point(0., 0.);
}

BoxImpl::BoxImpl(const Vertex &v1, const Vertex &v2) :
    my_lower(v1),
    my_upper(v2)
{ }

BoxImpl::BoxImpl (const BoxImpl &box) :
    my_lower(box.my_lower), my_upper(box.my_upper)
{ }
BoxImpl::~BoxImpl() { }
Vertex BoxImpl::pt1() { return my_lower; }
void BoxImpl::pt1(const Vertex &v1) { my_lower = v1; }

Vertex BoxImpl::pt2() { return my_upper; }
void BoxImpl::pt2(const Vertex &v2) { my_upper = v2; }

void BoxImpl::request(Fresco::Graphic::Requisition &r)
{
    r.x.defined = true;
    r.x.minimum = r.x.natural = r.x.maximum = my_upper.x - my_lower.x;
    r.x.align   = 0.;
    r.y.defined = true;
    r.y.minimum = r.y.natural = r.y.maximum = my_upper.y - my_lower.y;
    r.y.align   = 0.;
    r.z.defined = true;
    r.z.minimum = r.z.natural = r.z.maximum = my_upper.z - my_lower.z;
    r.z.align   = 0.;
}

void BoxImpl::draw(DrawTraversal_ptr traversal)
{ DrawingKit_var drawing = traversal->drawing(); }

// static const float magic = 0.5522847498307934f; // 4/3 * (sqrt(2) - 1)

// CircleImpl::CircleImpl() { }

// CircleImpl::CircleImpl (const Vertex &c, Coord r) :
//     my_center(c), my_radius(r)
// { resize(); }

// CircleImpl::CircleImpl(const CircleImpl &circle)
// {
//   copy(circle);
//   my_center = circle.my_center;
//   my_radius = circle.my_radius;
// }

// CircleImpl::~CircleImpl() { }

// void CircleImpl::resize()
// {
//     Vertex &c = my_center;
//     Coord &r = my_radius;

// //   float r0 = magic * r;
//     reset();
//     add_point(c.x + r, c.y);
// //   add_curve(c.x, c.y - r, c.x + r, c.y - r0, c.x + r0, c.y - r);
// //   add_curve(c.x - r, c.y, c.x - r0, c.y - r, c.x - r, c.y - r0);
// //   add_curve(c.x, c.y + r, c.x - r, c.y + r0, c.x - r0, c.y + r);
// //   add_curve(c.x + r, c.y, c.x + r0, c.y + r, c.x + r, c.y + r0);
//     std::cerr << "sorry, CircleImpl::resize not implemented" << std::endl;
// }

// Vertex CircleImpl::center() { return my_center; }
// void CircleImpl::center(const Vertex &c) { my_center = c; resize(); }
// Coord CircleImpl::radius() { return my_radius; }
// void CircleImpl::radius(Coord r) { my_radius = r; resize(); }

// static const float p0 = 1.00000000f;
// static const float p1 = 0.89657547f;   // cos 30 * sqrt(1 + tan 15 * tan 15)
// static const float p2 = 0.70710678f;   // cos 45
// static const float p3 = 0.51763809f;   // cos 60 * sqrt(1 + tan 15 * tan 15)
// static const float p4 = 0.26794919f;   // tan 15

// EllipseImpl::EllipseImpl() { }
// EllipseImpl::EllipseImpl(const Vertex &c, Coord r1, Coord r2) :
//     my_center(c), my_radius1(r1), my_radius2(r2)
// { resize(); }

// EllipseImpl::EllipseImpl(const EllipseImpl &ellipse) :
//     my_center(ellipse.my_center),
//     my_radius1(ellipse.my_radius1),
//     my_radius2(ellipse.my_radius2)
// { copy(ellipse); }

// EllipseImpl::~EllipseImpl() { }

// void EllipseImpl::resize()
// {
//     Coord &r1 = my_radius1;
//     Coord &r2 = my_radius2;
//     Coord &x = my_center.x;
//     Coord &y = my_center.y;

// //   float px0 = p0 * r1, py0 = p0 * r2;
// //   float px1 = p1 * r1, py1 = p1 * r2;
// //   float px2 = p2 * r1, py2 = p2 * r2;
// //   float px3 = p3 * r1, py3 = p3 * r2;
// //   float px4 = p4 * r1, py4 = p4 * r2;

//     reset();
//     add_point(x + r1, y);
// //     add_curve(x + px2, y + py2, x + px0, y + py4, x + px1, y + py3);
// //     add_curve(x, y + r2, x + px3, y + py1, x + px4, y + py0);
// //     add_curve(x - px2, y + py2, x - px4, y + py0, x - px3, y + py1);
// //     add_curve(x - r1, y, x - px1, y + py3, x - px0, y + py4);
// //     add_curve(x - px2, y - py2, x - px0, y - py4, x - px1, y - py3);
// //     add_curve(x, y - r2, x - px3, y - py1, x - px4, y - py0);
// //     add_curve(x + px2, y - py2, x + px4, y - py0, x + px3, y - py1);
// //     add_curve(x + r1, y, x + px1, y - py3, x + px0, y - py4);
//     std::cerr << "sorry, EllipseImpl::resize not implemented" << std::endl;
// }

// Vertex EllipseImpl::center() { return my_center; }
// void EllipseImpl::center(const Vertex &c) { my_center = c; resize(); }
// Coord EllipseImpl::radius1() { return my_radius1; }
// void EllipseImpl::radius1(Coord r) { my_radius1 = r; resize(); }
// Coord EllipseImpl::radius2() { return my_radius2; }
// void EllipseImpl::radius2(Coord r) { my_radius2 = r; resize(); }

GeometryImpl::GeometryImpl (const Fresco::Mesh &mesh)
{ my_mesh = new Fresco::Mesh(mesh); resize(); }
GeometryImpl::GeometryImpl(const GeometryImpl &geometry) { resize(); }
GeometryImpl::~GeometryImpl () { }

Fresco::Mesh *GeometryImpl::mesh() { return new Fresco::Mesh(my_mesh); }
void GeometryImpl::mesh(const Fresco::Mesh &m)
{ my_mesh = new Fresco::Mesh(m); resize(); }
