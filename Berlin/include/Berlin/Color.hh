/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#ifndef _Color_hh
#define _Color_hh

Color brightness(const Color &c1, double adjust)
{
  Color c2;
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
  return c2;
};

#endif /* _Color_hh */
