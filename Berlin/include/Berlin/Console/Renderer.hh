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

#ifndef _Berlin_Console_Renderer_hh
#define _Berlin_Console_Renderer_hh

#include <Berlin/config.hh>
#include <Berlin/Console.hh>

class Renderer : virtual public Console::Drawable::Extension
{
public:
  //. Set the color used for all drawing operations to the one given.
  virtual void set_color(const Fresco::Color &) = 0;

  //. Set the pixel at the given position to the current drawing color.
  virtual void draw_pixel(Fresco::PixelCoord, //.< x position
			  Fresco::PixelCoord) = 0; //.< y position

  //. Draw a horizontal line starting at the given position with the given length
  //. using the current drawing color. The line is one pixel thick.
  virtual void draw_hline(Fresco::PixelCoord, //. x position of one end
			  Fresco::PixelCoord, //.< y position
			  Fresco::PixelCoord) = 0; //.< width of the line
  //. Draw a vertical line starting at the given position with the given length
  //. using the current drawing color. The line is one pixel thick.
  virtual void draw_vline(Fresco::PixelCoord, //. x positon
			  Fresco::PixelCoord, //. y position of one end
			  Fresco::PixelCoord) = 0; //.< height of the line
  //. Draw a line starting at the given position using the current drawing color.
  //. The line is one pixel thick and exact (no more then 0.5 pixels from the
  //. 'real' position away). It starts at the given position and ends at
  //. (x + delta_x, y + delta_y).
  virtual void draw_line(Fresco::PixelCoord, //.< x position of one end
			 Fresco::PixelCoord, //.< y position of that end
			 Fresco::PixelCoord, //.< delta_x 
			 Fresco::PixelCoord) = 0; //.< delta_y
  //. Draws a rectangle filled with the current drawing color. One corner of it is
  //. at the given position and it has the given width and height.
  virtual void draw_box(Fresco::PixelCoord, //.< x position of a corner
			Fresco::PixelCoord, //.< y position of that corner
			Fresco::PixelCoord, //.< width
			Fresco::PixelCoord) = 0; //.< height
};

#endif
