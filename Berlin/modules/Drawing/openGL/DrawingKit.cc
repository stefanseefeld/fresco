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
#include "Warsaw/Text.hh"
#include "Berlin/Logger.hh"

extern "C" {
#include "ggi/ggi.h"
}

#include <strstream>
#include <iostream>

GLDrawingKit::GLDrawingKit()
  : rasters(500)
{
  ggiInit();
  drawable = new GLDrawable();
  drawable->_obj_is_ready(CORBA::BOA::getBOA());
  gnufont = new GLUnifont();
  gnufont->_obj_is_ready(CORBA::BOA::getBOA());
  Color c = {0.0,0.0,0.0,1.0};
  gnufont->setColor(c);
}

GLDrawingKit::~GLDrawingKit()
{
  drawable->_dispose();
  gnufont->_dispose();
  ggiExit();
}

void GLDrawingKit::setFont(const Text::FontDescriptor &fd, const Style::Spec &sty) 
  throw (Text::NoSuchFontException)
{
  MutexGuard guard(mutex);

  // make sure the gnufont tracks color changes
  for (unsigned long i = 0; i < sty.length(); i++) {    
      Color *tmp;
      if (sty[i].a == Style::fillcolor) {
	  sty[i].val >>= tmp;
	  //	  cerr << "set color " << tmp->red << ", " << tmp->green << ", " << tmp->blue << ", " << tmp->alpha << endl;
	  gnufont->setColor(*tmp);
      }
  }
  
  try
      { 
	  //
	  // at this time, there is _no_ way to add new fonts to the runtime.
	  // it uses GNU Unifont, and nothing else.
	  //
	  // it will eventually look like this, once we get the GLFont truetype &
	  // T1 registry alive.
	  //
	  
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
  if (font) return font->_this();
  else return gnufont->_this();
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
  pencil->_obj_is_ready(_boa());
  pencils.push_back(pencil);
  return pencil->_this();
}

void GLDrawingKit::clear(Coord l, Coord t, Coord r, Coord b)
{
  glColor4d(0, 0, 0, 1.0);      
  glRectf(l, t, r, b);
}

/*
 * FIXME !!!: drawing transformed rasters doesn't work
 *
 * - if the transform only translates we can use glDrawPixels as is
 * - if the transform only scales we can use glDrawPixels with zoom factors
 * - else we can use glDrawPixels with zoom factors
 *      -stefan
 */
void GLDrawingKit::image(Raster_ptr raster, Transform_ptr transform)
{
  GLRaster *glraster = rasters.lookup(Raster::_duplicate(raster));
#if 1
  translatedImage(glraster, transform);
#else
  if (transform->Identity()) translatedImage(glraster, transform);
  else transformedImage(glraster, transform);
#endif
}

/*
 * openGL requires glTexImageXX to take width and height in the form 2^k
 * se we extract the exponent here and the residue
 */
inline void logbase2(unsigned int n, unsigned int &k, unsigned int &r)
{
  unsigned int i = 1;
  k = 0;
  while (n >= i)
    {
      i <<= 1;
      k++;
    }
  i >>= 1;
  r = n - i;
}

void GLDrawingKit::transformedImage(const GLRaster *raster, Transform_ptr transform)
{
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_POLYGON);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, raster->width, raster->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, raster->data.begin());
  Path path;
  path.p.length(5);
  path.p[0].x = path.p[0].y = path.p[0].z = 0.;
  path.p[1].x = raster->width, path.p[1].y = path.p[1].z = 0.;
  path.p[2].x = raster->width, path.p[2].y = raster->height, path.p[2].z = 0.;
  path.p[3].x = 0, path.p[3].y = raster->height, path.p[3].z = 0.;
  path.p[4].x = path.p[4].y = path.p[4].z = 0.;
  for (unsigned int i = 0; i != 5; i++) transform->transformVertex(path.p[i]);
  glTexCoord3f(0.0f, 1.0f, 0.0f); glVertex3f(path.p[0].x, path.p[0].y, path.p[0].z);
  glTexCoord3f(1.0f, 1.0f, 0.0f); glVertex3f(path.p[0].x, path.p[0].y, path.p[0].z);
  glTexCoord3f(1.0f, 0.0f, 0.0f); glVertex3f(path.p[0].x, path.p[0].y, path.p[0].z);
  glTexCoord3f(0.0f, 0.0f, 0.0f); glVertex3f(path.p[0].x, path.p[0].y, path.p[0].z);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void GLDrawingKit::scaledImage(const GLRaster *raster, Transform_ptr transform)
{
}

void GLDrawingKit::translatedImage(const GLRaster *raster, Transform_ptr transform)
{
  Vertex origin;
  origin.x = origin.y = origin.z = 0.;
  transform->transformVertex(origin);
  glRasterPos2d(origin.x, origin.y + raster->height);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, raster->width);
  glDrawPixels(raster->width, raster->height, GL_RGBA, GL_UNSIGNED_BYTE, raster->data.begin());
}
