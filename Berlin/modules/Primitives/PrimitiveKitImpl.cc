/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@fresco.org> 
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
#include "Root.hh"
#include "PrimitiveKitImpl.hh"
// #include "PolyPrimitive.hh"
#include "Primitives.hh"
#include "Transformer.hh"
#include "Light.hh"

using namespace Fresco;

using namespace Berlin::PrimitiveKit;

PrimitiveKitImpl::PrimitiveKitImpl(const std::string &id,
		                   const Fresco::Kit::PropertySeq &p)
  : KitImpl(id, p) { }

PrimitiveKitImpl::~PrimitiveKitImpl() { }

Graphic_ptr PrimitiveKitImpl::root(Graphic_ptr g)
{
  Graphic_ptr res =
      create<Graphic>(new Root(Alignment(0.5), Alignment(0.5),
			       Alignment(0.5), Alignment(0.5),
			       Alignment(0.5), Alignment(0.5)));
  res->body(g);
  return res;
}

Primitive::Geometry_ptr PrimitiveKitImpl::geometry(const Fresco::Mesh &mesh)
{
  return create<Primitive::Geometry>(new GeometryImpl(mesh));
}

Graphic_ptr PrimitiveKitImpl::cube()
{
  Fresco::Mesh mesh;
  mesh.nodes.length(8);
  mesh.nodes[0].x = -500; mesh.nodes[0].y = -500; mesh.nodes[0].z = -500;
  mesh.nodes[1].x = -500; mesh.nodes[1].y = -500; mesh.nodes[1].z =  500;
  mesh.nodes[2].x = -500; mesh.nodes[2].y =  500; mesh.nodes[2].z =  500;

  mesh.nodes[3].x = -500; mesh.nodes[3].y =  500; mesh.nodes[3].z = -500;
  mesh.nodes[4].x =  500; mesh.nodes[4].y =  500; mesh.nodes[4].z =  500;
  mesh.nodes[5].x =  500; mesh.nodes[5].y = -500; mesh.nodes[5].z =  500;

  mesh.nodes[6].x =  500; mesh.nodes[6].y = -500; mesh.nodes[6].z = -500;
  mesh.nodes[7].x =  500; mesh.nodes[7].y =  500; mesh.nodes[7].z = -500;

  mesh.triangles.length(12);
  /* x=0 side */
  mesh.triangles[0].a = 0; mesh.triangles[0].b = 2; mesh.triangles[0].c = 3;
  mesh.triangles[1].a = 0; mesh.triangles[1].b = 1; mesh.triangles[1].c = 2;
  /* y=0 side */
  mesh.triangles[2].a = 0; mesh.triangles[2].b = 5; mesh.triangles[2].c = 1;
  mesh.triangles[3].a = 0; mesh.triangles[3].b = 6; mesh.triangles[3].c = 5;
  /* z=0 side */
  mesh.triangles[4].a = 0; mesh.triangles[4].b = 3; mesh.triangles[4].c = 7;
  mesh.triangles[5].a = 0; mesh.triangles[5].b = 7; mesh.triangles[5].c = 6;
  /* x=1 side */
  mesh.triangles[6].a = 4; mesh.triangles[6].b = 5; mesh.triangles[6].c = 6;
  mesh.triangles[7].a = 4; mesh.triangles[7].b = 6; mesh.triangles[7].c = 7;
  /* y=1 side */
  mesh.triangles[8].a = 4; mesh.triangles[8].b = 7; mesh.triangles[8].c = 3;
  mesh.triangles[9].a = 4; mesh.triangles[9].b = 3; mesh.triangles[9].c = 2;
  /* z=1 side */
  mesh.triangles[10].a = 4; mesh.triangles[10].b = 1; mesh.triangles[10].c = 5;
  mesh.triangles[11].a = 4; mesh.triangles[11].b = 2; mesh.triangles[11].c = 1;

  mesh.normals.length(12);
  mesh.normals[0].x = -1.; mesh.normals[0].y =  0.; mesh.normals[0].z =  0.;
  mesh.normals[1].x = -1.; mesh.normals[1].y =  0.; mesh.normals[1].z =  0.;
  mesh.normals[2].x =  0.; mesh.normals[2].y = -1.; mesh.normals[2].z =  0.;
  mesh.normals[3].x =  0.; mesh.normals[3].y = -1.; mesh.normals[3].z =  0.;
  mesh.normals[4].x =  0.; mesh.normals[4].y =  0.; mesh.normals[4].z = -1.;
  mesh.normals[5].x =  0.; mesh.normals[5].y =  0.; mesh.normals[5].z = -1.;
  mesh.normals[6].x =  1.; mesh.normals[6].y =  0.; mesh.normals[6].z =  0.;
  mesh.normals[7].x =  1.; mesh.normals[7].y =  0.; mesh.normals[7].z =  0.;
  mesh.normals[8].x =  0.; mesh.normals[8].y =  1.; mesh.normals[8].z =  0.;
  mesh.normals[9].x =  0.; mesh.normals[9].y =  1.; mesh.normals[9].z =  0.;
  mesh.normals[10].x =  0.; mesh.normals[10].y =  0.; mesh.normals[10].z =  1.;
  mesh.normals[11].x =  0.; mesh.normals[11].y =  0.; mesh.normals[11].z =  1.;

  return geometry(mesh);
}


Graphic_ptr PrimitiveKitImpl::transformer(Graphic_ptr g)
{
  Graphic_ptr res = create<Graphic>(new Transformer);
  res->body(g);
  return res;
}

Graphic_ptr PrimitiveKitImpl::directional_light(Fresco::Graphic_ptr g,
						const Fresco::Color &c,
						CORBA::Float i,
						const Fresco::Vertex &d)
{
  Graphic_ptr res = create<Graphic>(new DirectionalLight(c, i, d));
  res->body(g);
  return res;
}

Graphic_ptr PrimitiveKitImpl::point_light(Fresco::Graphic_ptr g,
					  const Fresco::Color &c,
					  CORBA::Float i,
					  const Fresco::Vertex &p)
{
  Graphic_ptr res = create<Graphic>(new PointLight(c, i, p));
  res->body(g);
  return res;
}

Graphic_ptr PrimitiveKitImpl::spot_light(Fresco::Graphic_ptr g,
					 const Fresco::Color &c,
					 CORBA::Float i,
					 const Fresco::Vertex &p,
					 const Fresco::Vertex &d,
					 CORBA::Float r,
					 CORBA::Float a)
{
  Graphic_ptr res = create<Graphic>(new SpotLight(c, i, p, d, r, a));
  res->body(g);
  return res;
}



extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "PrimitiveKitImpl"};
  return create_kit<PrimitiveKitImpl> ("IDL:fresco.org/Fresco/PrimitiveKit:1.0", properties, 2);
}
