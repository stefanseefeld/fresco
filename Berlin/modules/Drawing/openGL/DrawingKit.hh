/*$Id$
 *
 * This source file is a part of the Berlin Project.
 *
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 *
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
#ifndef _GLDrawingKit_hh
#define _GLDrawingKit_hh

#include "Warsaw/config.hh"
#include "Warsaw/DrawingKit.hh"
#include "Berlin/CloneableImpl.hh"
#include "Drawing/openGL/GLDrawable.hh"
#include "Drawing/openGL/GLPencil.hh"
#include "Drawing/openGL/GLFont.hh"

#include <string>
#include <vector>
extern "C" {
#include <ggi/ggi.h>
}

class GLDrawingKit : implements(DrawingKit), virtual public CloneableImpl
{
public:
  GLDrawingKit();
  ~GLDrawingKit();
  Drawable_ptr getDrawable();

  void setFont(const Text::FontDescriptor &fd, const Style::Spec &sty) 
    throw (Text::NoSuchFontException);
  Text::Font_ptr currentFont();

  ggi_visual_t getVisual() { return drawable->Visual();}
  Pencil_ptr getPencil(const Style::Spec &sty);
 protected:
  omni_mutex myMutex;
  GLFont *myFont;
  GLDrawable *drawable;
  vector<GLPencil *> pencils;
};

#endif /* _GLDrawingKit_hh */
