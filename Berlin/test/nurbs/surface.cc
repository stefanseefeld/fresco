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

#include <Berlin/nurbs/point.hh>
#include <Berlin/nurbs/domain.hh>
#include <Berlin/nurbs/nurbs.hh>

#include <GL/gl.h>
#include <GL/glut.h>

namespace nurbs = Berlin::nurbs;

const unsigned int PARAMS = 2;
const unsigned int ROW_CTRLPOINTS = 10;
const unsigned int COL_CTRLPOINTS = 10;

typedef nurbs::point<double, 3> Point;
typedef Point Vector;

typedef nurbs::domain<Point, PARAMS> Ctrl;
typedef nurbs::domain<nurbs::array<Point, PARAMS + 1>, PARAMS> Points;
typedef nurbs::domain<double, PARAMS> Weights;
typedef nurbs::domain<Vector, PARAMS> Normals;

Point make_point(double x, double y, double z)
{
   Point p;
   p[0] = x;
   p[1] = y;
   p[2] = z;
   return p;
}

Vector cross(const Vector &p, const Vector &q)
{
   Vector retn;
   retn[0] = p[1] * q[2] - p[2] * q[1];
   retn[1] = p[2] * q[0] - p[0] * q[2];
   retn[2] = p[0] * q[1] - p[1] * q[0];
   return retn;
}

Vector calc_normal(const nurbs::array<Point, PARAMS + 1> &derivs)
{
  return cross(derivs[1], derivs[2]);
}

Normals *evaluate_normals(Points *points)
{
  Normals *normals = new Normals(points->sizes());

  double max_norm = 0;
     
  for(size_t i = 0; i < points->length(); ++i)
  {
    (*normals)[i] = calc_normal((*points)[i]);
    max_norm = std::max(max_norm, nurbs::norm((*normals)[i]));
  }

  for(size_t i = 0; i < points->length(); ++i) (*normals)[i] /= max_norm;
  return normals;
}

bool animationFlag = false;          // 'a'
bool drawingPointsFlag = true;       // 'p'
bool drawingQuadsFlag = true;        // 'q'
bool drawingCtrlPointsFlag = true;   // 'c'
bool drawingDerivativesFlag = false; // 'd'
bool drawingNormalsFlag = true;      // 'n'
bool lightFlag = false;              // 'l'

Ctrl   *ctrls;
Points *points;
Normals *normals;

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
  case 'n': drawingNormalsFlag = !drawingNormalsFlag; break;
  case 'l': lightFlag = !lightFlag; break;
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

  if(drawingCtrlPointsFlag)
  {
     glColor3f(0.2, 0.8, 0.2);
     for(size_t i = 0; i < ctrls->length(); ++i)
     {
        const Point &p = (*ctrls)[i];
        glPushMatrix();
        glTranslatef(p[0], p[1], p[2]);
        glutSolidCube(0.035);
        glPopMatrix();
     }
  }
  
  if(lightFlag)
  {
    glPushMatrix();
    glLoadIdentity();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    GLfloat mat_specular[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat mat_shininess[] = {50.0};
    GLfloat mat_diffuse[] = {0.8, 0.1, 0.1, 1.0};
     
    GLfloat lmodel_ambient[] = {0.3, 0.3, 0.3, 1.0};
     
    GLfloat light_position0[] = {0.0, 0.0, 20.0};
      
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glShadeModel(GL_SMOOTH);
     
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
     
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
     
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
     
    glPopMatrix();
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glColor3f(0.4, 0.1, 0.1);
  }

  if(drawingQuadsFlag)
  {
    glColor3f(0.8, 0.2, 0.2);
    glBegin(GL_LINE_STRIP);
    for(size_t i = 0; i < points->size(0) - 1; ++i)
    {
      glBegin(GL_QUAD_STRIP);
      for(size_t j = 0; j < points->size(1); ++j)
      {
        if(lightFlag)
          glNormal3f((*normals)(Normals::index[i][j])[0],
                     (*normals)(Normals::index[i][j])[1],
                     (*normals)(Normals::index[i][j])[2]);
        glVertex3f((*points)(Points::index[i][j])[0][0],
                   (*points)(Points::index[i][j])[0][1],
                   (*points)(Points::index[i][j])[0][2]);
        
        if(lightFlag)
          glNormal3f((*normals)(Normals::index[i+1][j])[0],
                     (*normals)(Normals::index[i+1][j])[1],
                     (*normals)(Normals::index[i+1][j])[2]);
        glVertex3f((*points)(Points::index[i+1][j])[0][0],
                   (*points)(Points::index[i+1][j])[0][1],
                   (*points)(Points::index[i+1][j])[0][2]);
      }
      glEnd();
    }
  }
  
  if(drawingPointsFlag)
  {
    glColor3f(0.8, 0.4, 0.2);
    glBegin(GL_POINTS);
    for(size_t i = 0; i < points->length(); ++i)
    {
      glVertex3f((*points)[i][0][0], (*points)[i][0][1], (*points)[i][0][2]);
    }
    glEnd();
  }

  if(drawingDerivativesFlag)
  {
    for(size_t i = 0; i < points->length(); ++i)
    {
       const Point &p = (*points)[i][0];
       for(size_t j = 1; j < PARAMS + 1; ++j)
       {
         Vector deriv = (*points)[i][j];
         deriv /= 2 * norm(deriv);
         glBegin(GL_LINE_STRIP);
         glColor3f(0.8, 0.8, 0.8);
         glVertex3f(p[0], p[1], p[2]);
         glColor3f(0.8, 0.2, 0.2);
         glVertex3f(p[0] + deriv[0], p[1] + deriv[1], p[2] + deriv[2]);
         glEnd();
       }
    }
  }

  if(drawingNormalsFlag)
  {
    for(size_t i = 0; i < points->length(); ++i)
    {
      const Point &p = (*points)[i][0];
        
      glBegin(GL_LINE_STRIP);
      glColor3f(0.8, 0.8, 0.8);
      glVertex3f(p[0], p[1], p[2]);
      glColor3f(0.2, 0.2, 0.8);
      glVertex3f(p[0] + (*normals)[i][0], p[1] + (*normals)[i][1], p[2] + (*normals)[i][2]);
      glEnd();
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
  gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
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

int main(int argc, char **argv)
{
  ctrls = new Ctrl(Ctrl::index[ROW_CTRLPOINTS][COL_CTRLPOINTS]);
  Weights weights(Weights::index[ROW_CTRLPOINTS][COL_CTRLPOINTS]);
  srand(time(0));  
  for(size_t i = 0; i < ROW_CTRLPOINTS; ++i)
    for(size_t j = 0; j < COL_CTRLPOINTS; ++j)
    {
      (*ctrls)(Ctrl::index[i][j]) =
         make_point(static_cast<double>(j)-(COL_CTRLPOINTS - 1)/2.,
                    static_cast<double>((rand() % 150) / 100. - 1.),
                    static_cast<double>(i)-(ROW_CTRLPOINTS - 1)/2.);
      weights(Weights::index[i][j]) = 1.0;
    }
  
  nurbs::array<size_t, PARAMS> degrees(3);
  nurbs::array<size_t, PARAMS> steps(2);

  points = nurbs::evaluate_with_derivations(*ctrls, weights, degrees, steps);
  normals = evaluate_normals(points);
  
  startGL(argc, argv);

  return 0;
}
