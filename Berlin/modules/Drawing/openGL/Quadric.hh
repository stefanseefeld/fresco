/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Quadric_hh
#define _Quadric_hh

#include <Fresco/config.hh>
#include <Fresco/DrawingKit.hh>

namespace Berlin
{
  namespace DrawingKit
  {
    namespace openGL
    {

      class Quadric
      {
    public:
      enum orientation {in, out};
      enum normals {none, flat, smooth};
      Quadric(Fresco::DrawingKit::Fillstyle s,
          orientation o, normals n = none) :
          my_style(s), my_orient(o), my_norm(n)
      { }
      ~Quadric() { }
      void cylinder(double, double, double, int, int);
      void sphere(double, int, int);
      void disk(double, double, int, int);
      void partialDisk(double, double, int, int, double, double);
    private:
      Fresco::DrawingKit::Fillstyle my_style;
      orientation my_orient;
      normals my_norm;
      };
      
    } // namespace
  } // namespace
} // namespace

#endif 
