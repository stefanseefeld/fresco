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

#include <GL/glu.h>
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

// lower.x, lower.y, upper.x, upper.y
void GLDrawingKit::clear(Coord l, Coord t, Coord r, Coord b)
{
  glColor4d(0., 0., 0., 1.);      
  //glClearColor(0.0,0.0,0.0,1.0);
  //glClear(GL_COLOR_BUFFER_BIT);

  glRectf(l, t, r, b);
}

void GLDrawingKit::image(Raster_ptr raster, Transform_ptr transform)
{
  GLRaster *glraster = rasters.lookup(Raster::_duplicate(raster));
  transformedImage(glraster, transform);
}

/*
 * openGL requires glTexImage2D to take width and height in the form 2^k
 * se we extract the exponent here and the residue
 */
inline void logbase2(unsigned int n, unsigned int &v, float &r)
{
  unsigned int k;
  for (k = 0; n >>= 1; k++);
  v = 1 << (k + 1), r = v - n;
}

void GLDrawingKit::transformedImage(const GLRaster *raster, Transform_ptr transform)
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, raster->texture);
  glColor4f(1., 1., 1., 1.);
  glBegin(GL_POLYGON);
  Path path;
  path.p.length(4);
  path.p[0].x = path.p[0].y = path.p[0].z = 0.;
  path.p[1].x = raster->width, path.p[1].y = path.p[1].z = 0.;
  path.p[2].x = raster->width, path.p[2].y = raster->height, path.p[2].z = 0.;
  path.p[3].x = 0, path.p[3].y = raster->height, path.p[3].z = 0.;
  for (unsigned int i = 0; i != 4; i++) transform->transformVertex(path.p[i]);
  glTexCoord2f(0., 0.);              glVertex3f(path.p[3].x, path.p[3].y, path.p[3].z);
  glTexCoord2f(1., 0.);              glVertex3f(path.p[2].x, path.p[2].y, path.p[2].z);
  glTexCoord2f(1., 1.);              glVertex3f(path.p[1].x, path.p[1].y, path.p[1].z);
  glTexCoord2f(0., 1.);              glVertex3f(path.p[0].x, path.p[0].y, path.p[0].z);
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
