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
#ifndef _Berlin_Color_hh
#define _Berlin_Color_hh

#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <iostream>

inline Fresco::Color brightness(const Fresco::Color &c1, double adjust)
{
  Fresco::Color c2;
  if (adjust >= 0)
    {
      c2.red   = c1.red + (1 - c1.red) * adjust;
      c2.green = c1.green + (1 - c1.green) * adjust;
      c2.blue  = c1.blue + (1 - c1.blue) * adjust;
    }
  else
    {
      c2.red   = c1.red * (1 + adjust);
      c2.green = c1.green * (1 + adjust);
      c2.blue  = c1.blue * (1 + adjust);
    }
  c2.alpha = c1.alpha;
  return c2;
};

inline void CMYtoRGB(Fresco::Coord cyan, Fresco::Coord magenta, Fresco::Coord yellow, Fresco::Color &color)
{
  color.red = 1. - cyan;
  color.green = 1. - magenta;
  color.blue = 1. - yellow;
}

inline void RGBtoHSV(const Fresco::Color &color, Fresco::Coord &hue, Fresco::Coord &saturation, Fresco::Coord &value)
{
  Fresco::Coord max = color.red > color.green ? (color.red > color.blue ? color.red : color.blue) : color.green > color.blue ? color.green : color.blue;
  Fresco::Coord min = color.red < color.green ? (color.red < color.blue ? color.red : color.blue) : color.green < color.blue ? color.green : color.blue;
  value = max;
  saturation = max != 0. ? (max - min) / max : 0.; 
  if (saturation == 0.) hue = 0.; // undefined...
  else
   {
     double delta = max - min;
     if (color.red == max) hue = (color.green - color.blue) / delta;
     else if (color.green == max) hue = 2. + (color.blue - color.red) / delta;
     else if (color.blue == max) hue = 4. + (color.red - color.green) / delta;
     hue *= 60.;
     if (hue < 0.) hue += 360.;
   }
}

inline void HSVtoRGB(Fresco::Coord hue, Fresco::Coord saturation, Fresco::Coord value, Fresco::Color &color)
{
  if (saturation == 0.) color.red = color.green = color.blue = value;
  else
    {
      if (hue == 360.) hue = 0.;
      hue /= 60.;
      int i = static_cast<int>(hue);
      Fresco::Coord f = hue - i;
      Fresco::Coord p = value * (1. - saturation);
      Fresco::Coord q = value * (1. - saturation * f);
      Fresco::Coord t = value * (1. - saturation * (1. - f));
      switch (i)
        {
          case 0: color.red = value; color.green = t; color.blue = p; break;
          case 1: color.red = q; color.green = value; color.blue = p; break;
          case 2: color.red = p; color.green = value; color.blue = t; break;
          case 3: color.red = p; color.green = q; color.blue = value; break;
          case 4: color.red = t; color.green = p; color.blue = value; break;
          case 5: color.red = value; color.green = p; color.blue = q; break;
        }
    }
}

#endif /* _Color_hh */
