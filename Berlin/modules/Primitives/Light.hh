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
#ifndef _Light_hh
#define _Light_hh

#include <Warsaw/config.hh>
#include <Warsaw/DrawingKit3D.hh>
#include <Berlin/MonoGraphic.hh>

//. Abstract base light source node
class Light : public MonoGraphic
{
public:
  Light(const Warsaw::Color &, double);
  virtual ~Light();
  virtual void traverse(Warsaw::Traversal_ptr);
  virtual void draw(Warsaw::DrawTraversal_ptr);
  virtual void pick(Warsaw::PickTraversal_ptr);  
protected:
  virtual void do_draw(Warsaw::DrawingKit3D_ptr) = 0;
//   //. Whether light is on
//   bool          _on;
  //. RGB source color
  Warsaw::Color _color;
  //. Source intensity (0 to 1)
  double        _intensity;
};

class DirectionalLight : public Light
{
public:
  DirectionalLight(const Warsaw::Color &, double, const Warsaw::Vertex &);
protected:
  virtual void do_draw(Warsaw::DrawingKit3D_ptr);
  Warsaw::Vertex _direction;
};

class PointLight : public Light
{
public:
  PointLight(const Warsaw::Color &, double, const Warsaw::Vertex &);
protected:
  virtual void do_draw(Warsaw::DrawingKit3D_ptr);
  Warsaw::Vertex _position;
};

class SpotLight : public Light
{
public:
  SpotLight(const Warsaw::Color &, double, const Warsaw::Vertex &, const Warsaw::Vertex &,
	    double, double);
protected:
  virtual void do_draw(Warsaw::DrawingKit3D_ptr);
  Warsaw::Vertex _direction;
  Warsaw::Vertex _position;
  double         _dropoffrate;
  double         _cutoffangle;
};

#endif
