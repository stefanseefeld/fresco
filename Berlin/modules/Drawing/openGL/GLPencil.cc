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

#include "Drawing/openGL/GLPencil.hh"
#include <iostream>

GLPencil::GLPencil(const Style::Spec &sty, GLDrawable *d)
  : myDrawable(d)
{

  // init default values
  Color defaultColor = {1.0, 1.0, 1.0, 1.0};
  myFillColor = myLineColor = defaultColor;
  myFillMode = Style::solid;
  myThickness = 1.0;

  // !!!FIXME!!! this part is incomplete. at the moment, it only 
  // interprets a couple style parameters and ignores the rest. 
  // please, some GL hackers, set it the way it should be :)
  
  for (unsigned long i = 0; i < sty.length(); i++) {
    switch (sty[i].a) {
    case Style::fillcolor:
      sty[i].val >>= &myFillColor; break;
    case Style::linecolor:
      sty[i].val >>= &myLineColor; break;
    case Style::fill:
      sty[i].val >>= myFillMode; break;
    case Style::linethickness:
      sty[i].val >>= myThickness; break;
    case Style::ends:
    case Style::texture:
    case Style::linegradient:
    case Style::fillgradient:
      break;
    }
  }
};


void GLPencil::drawPath(const Path &p) {
  myDrawable->makeCurrent();
  glLineWidth(myThickness);

  if (p.m.length() == 0) {
    // we're drawing polys
    
    if (myFillMode == Style::solid) {
      // filled polys
      glColor4f(myFillColor.red, myFillColor.green, myFillColor.blue, myFillColor.alpha);
      glBegin(GL_POLYGON);
      for (unsigned long i = 0; i < p.p.length(); i++)       
	glVertex3d(p.p[i].x, p.p[i].y, p.p[i].z);      
      glEnd();
      
    } else { // for the time being there's only solid and nofill
      
      // line strips (no final connecting line)
      glColor4f(myLineColor.red, myLineColor.green, myLineColor.blue, myLineColor.alpha);
      glBegin(GL_LINE_STRIP);
      for (unsigned long i = 0; i < p.p.length(); i++)       
	glVertex3d(p.p[i].x, p.p[i].y, p.p[i].z);      
      glEnd();
    }

    // !!FIXME!! fill in evaluator setup / teardown code for curves
    
  }
}

void GLPencil::drawPatch(const Patch &) {
  // to be completed
}

void GLPencil::drawRect(Coord w, Coord h) {
  myDrawable->makeCurrent();
  glLineWidth(myThickness);

    if (myFillMode == Style::solid) {
      glColor4f(myFillColor.red, myFillColor.green, myFillColor.blue, myFillColor.alpha);
      glRectf(0,0,w,h);
    } else {
      glColor4f(myLineColor.red, myLineColor.green, myLineColor.blue, myLineColor.alpha);
      glBegin(GL_LINE_LOOP);
      glVertex3d(0,0,0);
      glVertex3d(w,0,0);
      glVertex3d(w,h,0);
      glVertex3d(0,h,0);
      glEnd();
    }      
}

void GLPencil::drawEllipse(Coord w, Coord h) {
  // !!!FIXME!!! quadrics code here
}


