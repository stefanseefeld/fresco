/*
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2002 Stefanus Du Toit <sjdutoit@uwaterloo.ca>
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

#include "GridDemo.hh"

using namespace Fresco;

GridDemo::GridDemo(Application *a)
  : Demo(a)
{
  LayoutKit_var layout = application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
  ToolKit_var tools = application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");

  Layout::Grid::Index upper;
  upper.col = 3;
  upper.row = 3;
  
  Graphic_var grid = layout->fixed_grid(upper);
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::inset);
  Graphic_var frame = tools->frame(layout->fixed_size(Graphic_var(Graphic::_nil()), 100., 100.), 20., spec, true);

  for (int i = 0; i < upper.col * upper.row; i++) {
    grid->append_graphic(tools->rgb(Graphic_var(frame), 1.0, (i % 2 ? 0.0 : 1.0), (i % 2 ? 1.0 : 0.0)));
  }
  Controller_var group = tools->group(grid);

  application->append(group, Babylon::String("grid"));
};
