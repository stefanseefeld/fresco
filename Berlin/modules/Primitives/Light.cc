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

#include <Warsaw/config.hh>
#include <Warsaw/Traversal.hh>
#include <Warsaw/DrawTraversal.hh>
#include <Warsaw/PickTraversal.hh>
#include <Warsaw/DrawingKit3D.hh>
#include "Primitive/Light.hh"

using namespace Warsaw;

Light::Light(const Color &color, double intensity) : _color(color), _intensity(intensity) {}
Light::~Light() {}

void Light::traverse(Traversal_ptr traversal) { traversal->visit(Graphic_var(_this()));}
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

void Light::pick(Warsaw::PickTraversal_ptr traversal)
{
  MonoGraphic::traverse(traversal);
}

DirectionalLight::DirectionalLight(const Warsaw::Color &color, double intensity, const Warsaw::Vertex &direction)
  : Light(color, intensity), _direction(direction) {}
void DirectionalLight::do_draw(Warsaw::DrawingKit3D_ptr drawing)
{
  drawing->directional_light(_color, _intensity, _direction);
}

PointLight::PointLight(const Warsaw::Color &color, double intensity, const Warsaw::Vertex &position)
  : Light(color, intensity), _position(position) {}
void PointLight::do_draw(Warsaw::DrawingKit3D_ptr drawing)
{
  drawing->point_light(_color, _intensity, _position);
}

SpotLight::SpotLight(const Warsaw::Color &color, double intensity, const Warsaw::Vertex &position, const Warsaw::Vertex &direction,
		     double dropoffrate, double cutoffangle)
  : Light(color, intensity), _position(position), _direction(direction), _dropoffrate(dropoffrate), _cutoffangle(cutoffangle) {}
void SpotLight::do_draw(Warsaw::DrawingKit3D_ptr drawing)
{
  drawing->spot_light(_color, _intensity, _position, _direction, _dropoffrate, _cutoffangle);
}

