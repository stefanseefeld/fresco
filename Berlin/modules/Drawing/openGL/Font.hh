/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _GLFont_hh
#define _GLFont_hh

#include "Warsaw/config.hh"
#include "Warsaw/Types.hh"
#include "Warsaw/Graphic.hh"
#include <string>
#include <GL/gl.h>

class GLFont
{
public:
  GLFont() {}
  virtual ~GLFont() {}
  virtual unsigned long size() = 0;
  virtual unsigned long weight() = 0;
  virtual Unistring *family() = 0;
  virtual Unistring *subfamily() = 0;
  virtual Unistring *fullname() = 0;
  virtual Unistring *style() = 0;
  virtual void drawChar(Unichar) = 0;
  virtual void allocateChar(Unichar, Graphic::Requisition &) = 0;
};

#endif

