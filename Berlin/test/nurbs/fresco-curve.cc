/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2002 Massimo Ricci
 * Copyright (C) 2003 Stefan Seefeld <stefan@fresco.org> 
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
#include <iostream>
#include <cstdlib>
#include <time.h>

#include <Berlin/nurbs/Vertex.hh>
#include <Berlin/nurbs/domain.hh>
#include <Berlin/nurbs/nurbs.hh>
#include <Berlin/nurbs/array.hh>

#include <GL/gl.h>
#include <GL/glut.h>

const unsigned int PARAMS = 1;
const unsigned int DEGREE = 3;
const unsigned int CTRLPOINTS = 10;

using namespace Fresco;
using namespace Berlin::nurbs;

typedef _CORBA_Unbounded_Sequence<Vertex> Polyline;
struct Quadric
{
  double a, b; // this should be a real 3x3 matrix, actually
  double phi1, phi2;
};
struct Nurbs
{
  CORBA::UShort degree;
  _CORBA_Unbounded_Sequence<Vertex> controls;
  _CORBA_Unbounded_Sequence_w_FixSizeElement<CORBA::Double, 8, 8> weights;
  _CORBA_Unbounded_Sequence_w_FixSizeElement<CORBA::Double, 8, 8> knots;
};

typedef Vertex Vector;

typedef domain<Vertex, PARAMS> Ctrl;
typedef domain<Vertex, PARAMS> Points;
typedef domain<double, PARAMS> Weights;

bool animationFlag = false;          // 'a'
bool drawingPointsFlag = true;       // 'p'
bool drawingQuadsFlag = true;        // 'q'
bool drawingCtrlPointsFlag = true;   // 'c'
bool drawingDerivativesFlag = false; // 'd'

const short SEGMENTS = 5;

Ctrl *ctrls[SEGMENTS];
Points *points[SEGMENTS];

void polar_view(GLdouble twist, GLdouble elevation, GLdouble azimuth)
{
  glRotated(-twist, 0.0, 0.0, 1.0);
  glRotated(-elevation, 1.0, 0.0, 0.0);
  glRotated(azimuth, 0.0, 1.0, 0.0);
}

void key(unsigned char key, int x, int y)
{
  switch(key) 
  {
  case 27: exit(0); break;
  case 'a': animationFlag = !animationFlag; break;
  case 'q': drawingQuadsFlag = !drawingQuadsFlag; break;
  case 'c': drawingCtrlPointsFlag = !drawingCtrlPointsFlag; break;
  case 'd': drawingDerivativesFlag = !drawingDerivativesFlag; break;
  case 'p': drawingPointsFlag = !drawingPointsFlag; break;
  }
}

void special_key_down(int key, int x, int y)
{
  switch(key)
  {
  case GLUT_KEY_LEFT: polar_view(-1., 0., 0.); break; // twist -1
  case GLUT_KEY_RIGHT: polar_view(1.0, 0.0, 0.0); break; // twist +1
  case GLUT_KEY_UP: polar_view(0.0, -1.0, 0.0); break; // elevation -1
  case GLUT_KEY_DOWN: polar_view(0.0, 1.0, 0.0); break; // elevation +1
  case GLUT_KEY_PAGE_UP: polar_view(0.0, 0.0, -1.0); break; // azimuth -1
  case GLUT_KEY_PAGE_DOWN: polar_view(0.0, 0.0, 1.0); break; // azimuth +1
  }
}

void special_key_up(int, int, int) {}

void idle() { glutPostRedisplay();}

void display()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(animationFlag)
  {
     glRotatef(1.0, 0.0, 0.0, 1.0);
     glRotatef(1.0, 0.0, 1.0, 0.0);
     glRotatef(1.0, 1.0, 0.0, 0.0);
  }

  if(drawingQuadsFlag)
  {
    glColor3f(0.8, 0.2, 0.2);
    for(size_t j = 0; j < SEGMENTS; ++j)
    {
      glBegin(GL_LINE_STRIP);
      for(size_t i = 0; i < points[j]->size(0); ++i)
      {
	glVertex3f((*points[j])(Points::index[i]).x,
		   (*points[j])(Points::index[i]).y,
		   (*points[j])(Points::index[i]).z);
      }
      glEnd();
    }
  }
  
  if(drawingPointsFlag)
  {
    glColor3f(0.8, 0.4, 0.2);
    for (size_t j = 0; j != SEGMENTS; ++j)
    {
      glBegin(GL_POINTS);
      for(size_t i = 0; i < points[j]->length(); ++i)
      {
	glVertex3f((*points[j])[i].x,
		   (*points[j])[i].y,
		   (*points[j])[i].z);
      }
      glEnd();
    }
  }

//   if(drawingDerivativesFlag)
//   {
//     for(size_t i = 0; i < points->length(); ++i)
//     {
//        Vertex p = (*points)[i][0];
//        for(size_t j = 1; j < PARAMS + 1; ++j)
//        {
//          Vector deriv = (*points)[i][j];
//          deriv /= 2 * norm(deriv);

//          glBegin(GL_LINE_STRIP);
//          glColor3f(0.8, 0.8, 0.8);
//          glVertex3f(p.x, p.y, p.z);
//          glColor3f(0.8, 0.2, 0.2);
//          glVertex3f(p.x + deriv.x, p.y + deriv.y, p.z + deriv.z);
//          glEnd();
//        }
//     }
//   }

  if(drawingCtrlPointsFlag)
  {
    glColor3f(0.2, 0.8, 0.2);
    for (size_t j = 0; j != SEGMENTS; ++j)
      for(size_t i = 0; i < (*ctrls[j]).length(); ++i)
      {
	const Vertex &p = (*ctrls[j])[i];
	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	glutSolidSphere(0.1, 6, 6);
	glPopMatrix();
      }
  }
  
  glutSwapBuffers();
}

void init() 
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void reshape(GLsizei w, GLsizei h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40., static_cast<double>(w)/static_cast<double>(h), 1, 1000);
  gluLookAt(0, 0, 40, 0, 0, 0, 0, 1, 0);
  glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h)); 
  glMatrixMode(GL_MODELVIEW);
}

int startGL(int argc, char** argv)
{
  std::cout << "Keys:\n"
	    << "'p'           switch on/off nurbs calculated points\n"
	    << "'c'           switch on/off nurbs control points\n"
	    << "'q'           switch on/off wire-frame visualization\n"
	    << "'a'           switch on/off animation\n"
	    << '\n'
	    << "left/right    rotate around z axis\n"
	    << "up/down       rotate around x axis\n"
	    << "pgUp/pgDn     rotate around y axis\n"
	    << '\n'
	    << "ESC           exit\n"
	    << '\n'
	    << std::endl;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(300, 300);
  glutInitWindowPosition(10, 10);
  
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape); 
  glutIdleFunc(idle);
  
  glutKeyboardFunc(key);	
  glutSpecialFunc(special_key_down);
  glutSpecialUpFunc(special_key_up);
  init();
  glutMainLoop();
  return 0;
}

int main(int argc, char *argv[])
{
  // define first segment
  Polyline polyline1;
  {
    polyline1.length(4);
    polyline1[0].x = 0.;
    polyline1[0].y = 0.;
    polyline1[0].z = 0.;
    polyline1[1].x = 1.;
    polyline1[1].y = 1.;
    polyline1[1].z = 0.;
    polyline1[2].x = 2.;
    polyline1[2].y = 0.;
    polyline1[2].z = 0.;
    polyline1[3].x = 3.;
    polyline1[3].y = 2.;
    polyline1[3].z = 1.;
  }

  // define second segment
  Nurbs nurbs1;
  {
    nurbs1.degree = DEGREE;
    nurbs1.controls.length(CTRLPOINTS);
    nurbs1.weights.length(CTRLPOINTS);
    srand(time(0));
    for(size_t i = 0; i < CTRLPOINTS; ++i)
    {
      nurbs1.controls[i] = make_vertex(static_cast<double>(i) - (CTRLPOINTS - 1)/2.,
				       static_cast<double>(rand() % 500) / 100. -1.,
				       0.);
      nurbs1.weights[i] = 1.0;
    }
    nurbs1.knots.length(CTRLPOINTS + DEGREE + 1);
    double delta = 1. / (CTRLPOINTS + DEGREE);
    for (size_t i = 0; i != nurbs1.knots.length(); ++i) nurbs1.knots[i] = i * delta;
  }
  // define third segment
  Polyline polyline2;
  {
    polyline2.length(4);
    polyline2[0].x = 0.;
    polyline2[0].y = 0.;
    polyline2[0].z = 0.;
    polyline2[1].x = 1.;
    polyline2[1].y = 1.;
    polyline2[1].z = 0.;
    polyline2[2].x = 2.;
    polyline2[2].y = 0.;
    polyline2[2].z = 0.;
    polyline2[3].x = 3.;
    polyline2[3].y = 2.;
    polyline2[3].z = 1.;
  }
  // define fourth segment
  Nurbs nurbs2;
  {
    nurbs2.degree = DEGREE;
    nurbs2.controls.length(CTRLPOINTS);
    nurbs2.weights.length(CTRLPOINTS);
    srand(time(0));
    for(size_t i = 0; i < CTRLPOINTS; ++i)
    {
      nurbs2.controls[i] = make_vertex(static_cast<double>(i) - (CTRLPOINTS - 1)/2.,
				       static_cast<double>(rand() % 500) / 100. -1.,
				       0.);
      nurbs2.weights[i] = 1.0;
    }
    nurbs2.knots.length(CTRLPOINTS + DEGREE + 1);
    double delta = 1. / (CTRLPOINTS + DEGREE);
    for (size_t i = 0; i != nurbs2.knots.length(); ++i) nurbs2.knots[i] = i * delta;
  }
  // define third segment
  Quadric quadric1;
  {
    quadric1.a = 5;
    quadric1.b = 2.;
    quadric1.phi1 = 0.;
    quadric1.phi2 = 3.142;
  }

  array<size_t, PARAMS> steps(4);

  // evaluation...
  {
    size_t length = polyline1.length();
    points[0] = new Points(&length);
    for (size_t i = 0; i != 4; ++i) (*points[0])[i] = polyline1[i];
    ctrls[0] = new Ctrl(&length);
    for (size_t i = 0; i != 4; ++i) (*ctrls[0])[i] = polyline1[i];
  }
  {
    size_t length = nurbs1.controls.length();
    ctrls[1] = new Ctrl(&length);
    for (size_t i = 0; i != length; ++i)
      (*ctrls[1])[i] = nurbs1.controls[i];
    length = nurbs1.weights.length();
    domain<double, PARAMS> weights(&length);
    for (size_t i = 0; i != nurbs1.weights.length(); ++i)
      weights[i] = nurbs1.weights[i];
    array<size_t, PARAMS> degrees(nurbs1.degree);
    array<std::vector<double>, PARAMS> knots;
    knots[0].resize(nurbs1.knots.length());
    for (size_t i = 0; i != knots[0].size(); ++i)
      knots[0][i] = nurbs1.knots[i];
    
    // compute the first point of this segment
    array<double, 1> param(knots[0][DEGREE]);
    Vertex first = evaluate_at(*ctrls[1], weights, degrees, knots, param);
    
    param[0] = knots[0][knots[0].size() - 1];
    Vertex last = evaluate_at(*ctrls[1], weights, degrees, knots, param);
    
    // now translate the curve to superpose the first point of this segment
    // with the last point of the last segment
    Vertex delta = (*points[0])[3];
    delta -= first;
    for (size_t i = 0; i != length; ++i)
      (*ctrls[1])[i] += delta;
    // evaluate the segment
    points[1] = evaluate(*ctrls[1], weights, degrees, knots, steps);
  }
  {
    size_t length = polyline2.length();
    points[2] = new Points(&length);
    for (size_t i = 0; i != 4; ++i) (*points[2])[i] = polyline2[i];
    ctrls[2] = new Ctrl(&length);
    for (size_t i = 0; i != 4; ++i) (*ctrls[2])[i] = polyline2[i];

    // now translate the curve to superpose the first point of this segment
    // with the last point of the last segment
    Vertex delta = (*points[1])[points[1]->length() - 1];
    delta -= (*points[2])[0];
    for (size_t i = 0; i != length; ++i)
    {
      (*points[2])[i] += delta;
      (*ctrls[2])[i] += delta;
    }
    
    {
      size_t length = nurbs2.controls.length();
      ctrls[3] = new Ctrl(&length);
      for (size_t i = 0; i != length; ++i)
	(*ctrls[3])[i] = nurbs2.controls[i];
      length = nurbs2.weights.length();
      domain<double, PARAMS> weights(&length);
      for (size_t i = 0; i != nurbs2.weights.length(); ++i)
	weights[i] = nurbs2.weights[i];
      array<size_t, PARAMS> degrees(nurbs2.degree);
      array<std::vector<double>, PARAMS> knots;
      knots[0].resize(nurbs2.knots.length());
      for (size_t i = 0; i != knots[0].size(); ++i)
	knots[0][i] = nurbs2.knots[i];

      // compute the first point of this segment
      array<double, 1> param(knots[0][DEGREE]);
      Vertex first = evaluate_at(*ctrls[3], weights, degrees, knots, param);

      param[0] = knots[0][knots[0].size() - 1];
      Vertex last = evaluate_at(*ctrls[3], weights, degrees, knots, param);

      // now translate the curve to superpose the first point of this segment
      // with the last point of the last segment
      Vertex delta = (*points[2])[3];
      delta.x -= first.x, delta.y -= first.y, delta.z -= first.z;
      for (size_t i = 0; i != length; ++i)
	{
	  (*ctrls[3])[i].x += delta.x;
	  (*ctrls[3])[i].y += delta.y;
	  (*ctrls[3])[i].z += delta.z;
	}
      // evaluate the segment
      points[3] = evaluate(*ctrls[3], weights, degrees, knots, steps);
    }
  }
  {
    size_t length = 10;
    points[4] = new Points(&length);
    double phi = quadric1.phi1;
    double dphi = (quadric1.phi2 - quadric1.phi1)/10;
    for (size_t i = 0; i != 10; ++i, phi += dphi)
      (*points[4])[i] = make_vertex(quadric1.a * sin(phi),
				    quadric1.b * cos(phi),
				    0.);
    for (size_t i = 0; i != 10; ++i) std::cout << (*points[4])[i].x << ' ' << (*points[4])[i].y << std::endl;
    ctrls[4] = new Ctrl(&length);
    for (size_t i = 0; i != 10; ++i) (*ctrls[4])[i] = (*points[4])[0];

    // now translate the curve to superpose the first point of this segment
    // with the last point of the last segment
    Vertex delta = (*points[3])[points[3]->length() - 1];
    delta -= (*points[4])[0];
    for (size_t i = 0; i != length; ++i)
    {
      (*points[4])[i] += delta;
      (*ctrls[4])[i] += delta;
    }
  }

  startGL (argc, argv);
  return 0;
}
