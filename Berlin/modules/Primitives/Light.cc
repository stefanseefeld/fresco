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
#include <Fresco/Traversal.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/DrawingKit3D.hh>
#include "Light.hh"

using namespace Fresco;

using namespace Berlin::PrimitiveKit;

Light::Light(const Color &color, double intensity) :
    my_color(color), my_intensity(intensity)
{ }
Light::~Light() { }

void Light::traverse(Traversal_ptr traversal)
{ traversal->visit(Graphic_var(_this()));}
void Light::draw(DrawTraversal_ptr traversal)
{
    DrawingKit_var drawing = traversal->drawing();
    drawing->save();
    DrawingKit3D_var d3d = DrawingKit3D::_narrow(drawing);
    if (!CORBA::is_nil(d3d))
	do_draw(d3d);
    MonoGraphic::traverse(traversal);
    drawing->restore();
}

void Light::pick(Fresco::PickTraversal_ptr traversal)
{ MonoGraphic::traverse(traversal); }

DirectionalLight::DirectionalLight(const Fresco::Color &color,
				   double intensity,
				   const Fresco::Vertex &direction) :
    Light(color, intensity), my_direction(direction)
{ }
void DirectionalLight::do_draw(Fresco::DrawingKit3D_ptr drawing)
{ drawing->directional_light(my_color, my_intensity, my_direction); }

PointLight::PointLight(const Fresco::Color &color, double intensity,
		       const Fresco::Vertex &position) :
    Light(color, intensity), my_position(position)
{ }
void PointLight::do_draw(Fresco::DrawingKit3D_ptr drawing)
{ drawing->point_light(my_color, my_intensity, my_position); }

SpotLight::SpotLight(const Fresco::Color &color, double intensity,
		     const Fresco::Vertex &position,
		     const Fresco::Vertex &direction,
		     double dropoffrate, double cutoffangle) :
    Light(color, intensity),
    my_position(position),
    my_direction(direction),
    my_dropoffrate(dropoffrate),
    my_cutoffangle(cutoffangle)
{ }
void SpotLight::do_draw(Fresco::DrawingKit3D_ptr drawing)
{
    drawing->spot_light(my_color, my_intensity, my_position, my_direction,
			my_dropoffrate, my_cutoffangle);
}

