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

#include "Warsaw/config.hh"
#include "Warsaw/Transform.hh"
#include "Drawing/openGL/GLDrawingKit.hh"
#include "Drawing/openGL/GLDrawable.hh"
#include "Drawing/openGL/GLPencil.hh"
#include "Warsaw/Text.hh"
#include "Drawing/openGL/GLFont.hh"
#include "Berlin/Logger.hh"

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
  MutexGuard guard(mutex);
  try
    { 
/*      GLFont *newfont = new GLFont(fd,sty); 
      newfont->_obj_is_ready(_boa());
      if (font) font->_dispose();
      font = newfont;*/
    }
  catch (Text::NoSuchFontException &ex)
    {
      throw ex;
    }
}

Text::Font_ptr GLDrawingKit::currentFont()
{
  MutexGuard guard(mutex);
  return font->_this();
}

Drawable_ptr GLDrawingKit::getDrawable()
{
  MutexGuard guard(mutex);
  return drawable->_this();
}

Pencil_ptr GLDrawingKit::getPencil(const Style::Spec &sty)
{
  MutexGuard guard(mutex);
  GLPencil *pencil = new GLPencil(sty, drawable);
  pencil->_obj_is_ready(applyscope(skeletonize(DrawingKit), _boa()));
  pencils.push_back(pencil);
  return pencil->_this();
}

void GLDrawingKit::clear(Coord l, Coord t, Coord r, Coord b)
{
  glColor4d(0, 0, 0, 0);      
  glRectf(l, t, r, b);
}

void GLDrawingKit::image(Raster_ptr raster, Transform_ptr transform)
{
  Raster::Info info = raster->header();
  Raster::ColorSeq_var pixels;
  Raster::Index lower, upper;
  lower.x = lower.y = 0;
  upper.x = info.width, upper.y = info.height;
  raster->storePixels(lower, upper, pixels);

  /*
   * transform the ColorSeq to the format internally used by openGL
   */
  GLRaster *glraster = new GLRaster(info.width, info.height);
  GLRaster::iterator pixel = glraster->data.begin();
  for (int y = info.height - 1; y >= 0; y--)
    for (int x = 0; x != info.width; x++)
      {
	Color &color = pixels[y * info.width + x];
	*pixel++ = static_cast<char>(color.red * 256);
	*pixel++ = static_cast<char>(color.green * 256);
	*pixel++ = static_cast<char>(color.blue * 256);
	*pixel++ = static_cast<char>(color.alpha * 256);
      }

#if 1
  Vertex origin;
  origin.x = origin.y = origin.z = 0.;
  transform->transformVertex(origin);
  glRasterPos2d(origin.x, origin.y + info.height);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, info.width);
  glDrawPixels(glraster->width, glraster->height, GL_RGBA, GL_UNSIGNED_BYTE, glraster->data.begin());
#else
  Path path;
  path.p.length(5);
  path.p[0].x = path.p[0].y = path.p[0].z = 0.;
  path.p[1].x = info.width, path.p[1].y = path.p[1].z = 0.;
  path.p[2].x = info.width, path.p[2].y = info.height, path.p[2].z = 0.;
  path.p[3].x = 0, path.p[3].y = info.height, path.p[3].z = 0.;
  path.p[4].x = path.p[4].y = path.p[4].z = 0.;
  for (unsigned int i = 0; i != 5; i++) transform->transformVertex(path.p[i]);
  texturedPolygon(path, glraster);
#endif
  delete glraster;
}

void GLDrawingKit::texturedPolygon(const Path &path, GLRaster *raster)
{
  glBegin(GL_POLYGON);
  glEnable(GL_TEXTURE_2D);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, raster->width, raster->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, raster->data.begin());
  for (unsigned long i = 0; i < path.p.length(); i++)
    glVertex3f(path.p[i].x, path.p[i].y, path.p[i].z);   
  glDisable(GL_TEXTURE_2D);
  glEnd();
}

