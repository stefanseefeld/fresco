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
// #include "Warsaw/Text.hh"
#include "Berlin/Logger.hh"
#include "Berlin/Plugin.hh"

#include <GL/glu.h>
#include <strstream>
#include <iostream>

GLDrawingKit::GLDrawingKit()
  : drawable(GGI::drawable()), tr(new TransformImpl), cl(new RegionImpl), rasters(500)
{
  tr->_obj_is_ready(_boa());
  cl->_obj_is_ready(_boa());
  context = GGIMesaCreateContext();
  if (!context)
    {
      cerr << "GGIMesaCreateContext() failed" << endl;
      exit(4);
    }
  if (GGIMesaSetVisual(context, drawable->visual(), GL_TRUE, GL_FALSE))
    {
      cerr << "GGIMesaSetVisual() failed" << endl;
      exit(7);
    }
  GGIMesaMakeCurrent(context);
  glViewport(0, 0, drawable->width(), drawable->height());
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  glOrtho(0, drawable->width()/drawable->resolution(xaxis), drawable->height()/drawable->resolution(yaxis), 0, -1000.0, 1000.0); 
  glTranslatef(0.375, 0.375, 0.);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glShadeModel(GL_SMOOTH);
  glDisable(GL_LIGHTING);  
  glFrontFace(GL_CW);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_SCISSOR_TEST);
  glScissor(0, 0, drawable->width(), drawable->height());
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLDrawingKit::~GLDrawingKit()
{
  GGIMesaDestroyContext(context);
  cl->_dispose();
  tr->_dispose();
}

void GLDrawingKit::setTransformation(Transform_ptr t)
{
  tr->copy(t);
  Transform::Matrix &matrix = tr->matrix();
  GLdouble glmatrix[16] = {matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
			   matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
			   matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
			   matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]};
  glLoadMatrixd(glmatrix);
}

void GLDrawingKit::setClipping(Region_ptr r)
{
  cl->copy(r);
  //...
}

void GLDrawingKit::setForeground(const Color &c)
{
  fg = c;
  glColor4d(fg.red, fg.green, fg.blue, fg.alpha);
}

void GLDrawingKit::setPointSize(Coord s)
{
  ps = s;
  // FIXME !: glPointSize uses pixel units !
  glPointSize(ps);
}

void GLDrawingKit::setLineWidth(Coord w)
{
  lw = w;
  // FIXME !: glLineWidth uses pixel units !
  glLineWidth(lw);
}

void GLDrawingKit::setLineEndstyle(DrawingKit::Endstyle style)
{
  es = style;
}

void GLDrawingKit::setSurfaceFillstyle(DrawingKit::Fillstyle style)
{
  fs = style;
}

void GLDrawingKit::setTexture(Raster_ptr t)
{
  tx = t;
  GLRaster *glraster = rasters.lookup(Raster::_duplicate(t));
  glBindTexture(GL_TEXTURE_2D, glraster->texture);
}

// void GLDrawingKit::clear(Coord l, Coord t, Coord r, Coord b)
// {
//   glColor4d(0., 0., 0., 1.);
//   glRectf(l, t, r, b);
// }

void GLDrawingKit::drawPath(const Path &path)
{
//   myDrawable->makeCurrent();
  if (fs == solid || (fs == textured && CORBA::is_nil(tx)))
    {
      glBegin(GL_POLYGON);
      for (unsigned long i = 0; i < path.length(); i++) glVertex3f(path[i].x, path[i].y, path[i].z);
      glEnd();
    }
  else if (fs == textured)
    {
      cerr << "sorry, implementation for textured polygons not finished..." << endl;
//       GLRaster *glraster = rasters.lookup(tx);
      glBegin(GL_POLYGON);
      for (unsigned long i = 0; i < path.length(); i++) glVertex3f(path[i].x, path[i].y, path[i].z);
      glEnd();
    }
  else
    {
      glBegin(GL_LINE_STRIP);
      // line strips (no final connecting line)      
      for (unsigned long i = 0; i < path.length(); i++) glVertex3f(path[i].x, path[i].y, path[i].z);
      glEnd();
    }
}

void GLDrawingKit::drawRect(const Vertex &lower, const Vertex &upper)
{
  if (fs == solid || (fs == textured && CORBA::is_nil(tx)))
    {
      glRectf(lower.x, lower.y, upper.x, upper.y);
    }
  else if (fs == textured)
    {
      GLRaster *glraster = rasters.lookup(tx);
      glBegin(GL_POLYGON);
      glTexCoord2f(0., 0.);                   glVertex2d(lower.x, lower.y);
      glTexCoord2f(glraster->s, 0.);          glVertex2d(upper.x, lower.y);
      glTexCoord2f(glraster->s, glraster->t); glVertex2d(upper.x, upper.y);
      glTexCoord2f(0., glraster->t);          glVertex2d(lower.x, upper.y);
      glEnd();
    }
  else
    {
      glBegin(GL_LINE_LOOP);
      glVertex2d(lower.x, lower.y);
      glVertex2d(upper.x, lower.y);
      glVertex2d(upper.x, upper.y);
      glVertex2d(lower.x, upper.y);
      glEnd();
    }
}

void GLDrawingKit::drawEllipse(const Vertex &lower, const Vertex &upper)
{
  // !!!FIXME!!! quadrics code here
}


void GLDrawingKit::drawImage(Raster_ptr raster)
{
  GLRaster *glraster = rasters.lookup(Raster::_duplicate(raster));
  glraster->draw();
}

void GLDrawingKit::drawText(const Unistring &us)
{

}

EXPORT_PLUGIN(GLDrawingKit, interface(DrawingKit))
