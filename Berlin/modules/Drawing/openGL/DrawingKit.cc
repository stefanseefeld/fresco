/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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

#include "Drawing/openGL/GLDrawingKit.hh"
#include "Drawing/openGL/GLDrawable.hh"
#include "Drawing/openGL/GLPencil.hh"
#include "Warsaw/Text.hh"
#include "Drawing/openGL/GLFont.hh"

extern "C" {
#include "ggi/ggi.h"
}

#include <strstream>
#include <iostream>

GLDrawingKit::GLDrawingKit()
{
  ggiInit();
  drawable = new GLDrawable();
  drawable->_obj_is_ready(CORBA::BOA::getBOA());
}

GLDrawingKit::~GLDrawingKit()
{
  drawable->_dispose();
  ggiExit();
}

void GLDrawingKit::setFont(const Text::FontDescriptor &fd, const Style::Spec &sty) 
  throw (Text::NoSuchFontException)
{
  MutexGuard guard(myMutex);
  try
    { 
      GLFont *newfont = new GLFont(fd,sty); 
      newfont->_obj_is_ready(_boa());
      if (myFont) myFont->_dispose();
      myFont = newfont;
    }
  catch (Text::NoSuchFontException &ex)
    {
      throw ex;
    }
  myMutex.unlock();    
}

Text::Font_ptr GLDrawingKit::currentFont()
{
  MutexGuard guard(myMutex);
  return myFont->_this();
}

Drawable_ptr GLDrawingKit::getDrawable()
{
  MutexGuard guard(myMutex);
  return drawable->_this();
}

Pencil_ptr GLDrawingKit::getPencil(const Style::Spec &sty)
{
  MutexGuard guard(myMutex);
  GLPencil *pencil = new GLPencil(sty, drawable);
  pencil->_obj_is_ready(applyscope(skeletonize(DrawingKit), _boa()));
  pencils.push_back(pencil);
  return pencil->_this();
}
