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
#ifndef _PrimitiveKit_Light_hh
#define _PrimitiveKit_Light_hh

#include <Fresco/config.hh>
#include <Fresco/DrawingKit3D.hh>
#include <Berlin/MonoGraphic.hh>

namespace Berlin
{
  namespace PrimitiveKit
  {

    //. Abstract base light source node
    class Light : public MonoGraphic
    {
      public:
	Light(const Fresco::Color &, double);
	virtual ~Light();
	virtual void traverse(Fresco::Traversal_ptr);
	virtual void draw(Fresco::DrawTraversal_ptr);
	virtual void pick(Fresco::PickTraversal_ptr);  
      protected:
	virtual void do_draw(Fresco::DrawingKit3D_ptr) = 0;
//        //. Whether light is on
//        bool          _on;
          //. RGB source color
	Fresco::Color my_color;
	//. Source intensity (0 to 1)
	double        my_intensity;
    };

    class DirectionalLight : public Light
    {
      public:
	DirectionalLight(const Fresco::Color &, double,
			 const Fresco::Vertex &);
      protected:
	virtual void do_draw(Fresco::DrawingKit3D_ptr);
	Fresco::Vertex my_direction;
    };

    class PointLight : public Light
    {
      public:
	PointLight(const Fresco::Color &, double, const Fresco::Vertex &);
      protected:
	virtual void do_draw(Fresco::DrawingKit3D_ptr);
	Fresco::Vertex my_position;
    };

    class SpotLight : public Light
    {
      public:
	SpotLight(const Fresco::Color &, double, const Fresco::Vertex &,
		  const Fresco::Vertex &,
		  double, double);
      protected:
	virtual void do_draw(Fresco::DrawingKit3D_ptr);
	Fresco::Vertex my_direction;
	Fresco::Vertex my_position;
	double         my_dropoffrate;
	double         my_cutoffangle;
    };
    
  } // namespace
} // namespace

#endif
