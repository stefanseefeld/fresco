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
#ifndef _ToolKit_DrawingStateImpl_hh
#define _ToolKit_DrawingStateImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/State.hh>
#include <Berlin/MonoGraphic.hh>

namespace Berlin
{
  namespace ToolKit
  {

    class DrawingStateImpl : public virtual POA_Fresco::DrawingState,
			     public MonoGraphic
    {
      public:
	DrawingStateImpl();
	virtual ~DrawingStateImpl();
	
	virtual void traverse(Fresco::Traversal_ptr);
	virtual void draw(Fresco::DrawTraversal_ptr);
	virtual void pick(Fresco::PickTraversal_ptr);

	virtual Fresco::Color foreground();
	virtual void foreground(const Fresco::Color &);
	virtual Fresco::Color lighting();
	virtual void lighting(const Fresco::Color &);
	virtual Fresco::Coord point_size();
	virtual void point_size(Fresco::Coord);
	virtual Fresco::Coord line_width();
	virtual void line_width(Fresco::Coord);
	virtual Fresco::DrawingKit::Endstyle line_endstyle();
	virtual void line_endstyle(Fresco::DrawingKit::Endstyle);
	virtual Fresco::DrawingKit::Fillstyle surface_fillstyle();
	virtual void surface_fillstyle(Fresco::DrawingKit::Fillstyle);
	virtual Fresco::Raster_ptr texture();
	virtual void texture(Fresco::Raster_ptr);
      private:
	enum
	{
	    color  = 0x01, light  = 0x02, point = 0x04, line = 0x8,
	    estyle = 0x10, fstyle = 0x20, tex   = 0x40
	};
	long                          my_enabled;
	Fresco::Color                 my_color;
	Fresco::Color                 my_light;
	Fresco::Coord                 my_point;
	Fresco::Coord                 my_line;
	Fresco::DrawingKit::Endstyle  my_estyle;
	Fresco::DrawingKit::Fillstyle my_fstyle;
	Fresco::Raster_var            my_texture;
    };
    
  } // namespace
} // namespace

#endif
