/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include <Warsaw/config.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/IO.hh>
#include "Drawing/openGL/GLQuadric.hh"
#include "Drawing/openGL/GLDrawingKit.hh"
#include "Drawing/openGL/GLUnifont.hh"
#include <Berlin/Logger.hh>
#include <Berlin/Color.hh>
#include <Prague/Sys/Profiler.hh>

#include <strstream>
#include <iostream>

using namespace Prague;
using namespace Warsaw;

GLDrawingKit::Light::Light()
  : _max(-1), _number(-1)
{
  glGetIntegerv(GL_MAX_LIGHTS, &_max);
}

int GLDrawingKit::Light::push()
{
  ++_number;
  if (_number >= _max) return -1;
  glEnable(static_cast<GLenum>(GL_LIGHT0 + _number));
  return GL_LIGHT0 + _number;
}

int GLDrawingKit::Light::top() const
{
  return GL_LIGHT0 + _number;
}

void GLDrawingKit::Light::pop()
{
  if (_number < _max) glDisable(static_cast<GLenum>(GL_LIGHT0 + _number));
  --_number;
}

GLDrawingKit::GLDrawingKit(const std::string &id, const Warsaw::Kit::PropertySeq &p)
  : KitImpl(id, p),
    _drawable(0),
    _tx(0),
    _font(0),
    _light(0),
    _textures(100),
    _images(500)
{
}

KitImpl *GLDrawingKit::clone(const Warsaw::Kit::PropertySeq &p)
{
  GLDrawingKit *kit = new GLDrawingKit(repo_id(), p);
  kit->init();
  return kit;
}

void GLDrawingKit::save()
{
  DrawingKitBase::save();
  _states.push(DrawState());
  _states.top().lights = _light->top();
}

void GLDrawingKit::restore()
{
  DrawingKitBase::restore();
  if (_states.empty()) return; // no state to restore
  DrawState &prev = _states.top();
  while (_light->top() > prev.lights) _light->pop();
  _states.pop();
}

void GLDrawingKit::init()
{
  Console *console = Console::instance();
  _drawable = console->drawable();
  _glcontext = console->get_extension<GLContext>("GLContext", _drawable);

  _font = new GLUnifont();
  _light = new Light();
  glViewport(0, 0, _drawable->width(), _drawable->height());
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  glOrtho(0, _drawable->width()/_drawable->resolution(xaxis), _drawable->height()/_drawable->resolution(yaxis), 0, -5000.0, 5000.0); 
  glTranslatef(0.375, 0.375, 0.);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glShadeModel(GL_SMOOTH);
//   glEnable(GL_LIGHTING);
  glFrontFace(GL_CW);
  glDisable(GL_DITHER);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_SCISSOR_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

GLDrawingKit::~GLDrawingKit()
{
  delete _font;
  delete _glcontext;
}

void GLDrawingKit::set_transformation(Transform_ptr t)
{
  static GLdouble identity[16] = {1., 0., 0., 0.,
				  0., 1., 0., 0.,
				  0., 0., 1., 0.,
				  0., 0., 0., 1.};
  if (CORBA::is_nil(t)) glLoadMatrixd(identity);
  else
    {
      _tr = Transform::_duplicate(t);
      Transform::Matrix matrix;
      _tr->store_matrix(matrix);
      GLdouble glmatrix[16] = {matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
			       matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
			       matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
			       matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]};
      glLoadMatrixd(glmatrix);
    }
}

void GLDrawingKit::set_clipping(Region_ptr r)
{
  _cl = Region::_duplicate(r);
  if (CORBA::is_nil(_cl)) glScissor(0, 0, _drawable->width(), _drawable->height());
  else
    {
      Vertex lower, upper;
      _cl->bounds(lower, upper);
      PixelCoord x = static_cast<PixelCoord>(lower.x*_drawable->resolution(xaxis) + 0.5);
      PixelCoord y = static_cast<PixelCoord>((_drawable->height()/_drawable->resolution(yaxis) - upper.y)*_drawable->resolution(yaxis) + 0.5);
      PixelCoord w = static_cast<PixelCoord>((upper.x - lower.x)*_drawable->resolution(xaxis) + 0.5);
      PixelCoord h = static_cast<PixelCoord>((upper.y - lower.y)*_drawable->resolution(yaxis) + 0.5);
      glScissor(x, y, w, h);
#if 0 // uncomment this if you want to debug the repairing of regions
      glColor4d(1., 0., 0., 1.);
      glRectf(0, 0, 10000., 10000.);
      glFlush();
      Console::drawable()->flush();
      sleep(1);
#endif
    }
}

void GLDrawingKit::set_foreground(const Color &c)
{
  _fg = c;
  glColor4d(_lt.red * _fg.red, _lt.green * _fg.green, _lt.blue * _fg.blue, _fg.alpha);
}

void GLDrawingKit::set_lighting(const Color &c)
{
  _lt = c;
  glColor4d(_lt.red * _fg.red, _lt.green * _fg.green, _lt.blue * _fg.blue, _fg.alpha);
}

void GLDrawingKit::set_point_size(Coord s)
{
  _ps = s;
  // FIXME !: glPointSize uses pixel units !
  glPointSize(_ps);
}

void GLDrawingKit::set_line_width(Coord w)
{
  _lw = w;
  // FIXME !: glLineWidth uses pixel units !
  glLineWidth(_lw);
}

void GLDrawingKit::set_line_endstyle(Warsaw::DrawingKit::Endstyle style)
{
  _es = style;
}

void GLDrawingKit::set_surface_fillstyle(Warsaw::DrawingKit::Fillstyle style)
{
  if (_fs == Warsaw::DrawingKit::textured) glDisable(GL_TEXTURE_2D);
  _fs = style;
  if (_fs == Warsaw::DrawingKit::textured) glEnable(GL_TEXTURE_2D);
}

void GLDrawingKit::set_texture(Raster_ptr t)
{
  _tx = CORBA::is_nil(t) ? 0 : _textures.lookup(Raster::_duplicate(t));
  if (_tx) glBindTexture(GL_TEXTURE_2D, _tx->texture);
}

// void GLDrawingKit::clear(Coord l, Coord t, Coord r, Coord b)
// {
//   glColor4d(0., 0., 0., 1.);
//   glRectf(l, t, r, b);
// }

void GLDrawingKit::draw_path(const Path &path)
{
  if (_fs == Warsaw::DrawingKit::solid)
    {
//       glBegin(GL_POLYGON);
      glBegin(GL_LINE_LOOP);
      for (unsigned long i = 0; i < path.length(); i++) glVertex3f(path[i].x, path[i].y, path[i].z);
      glEnd();
    }
  else if (_fs == Warsaw::DrawingKit::textured)
    {
//       glBegin(GL_TRIANGLE_FAN);
      glBegin(GL_LINE_LOOP);
      for (unsigned long i = 0; i < path.length(); i++)
	{
	  glTexCoord2f(path[i].x * _tx->width * 10., path[i].y * _tx->height * 10.); 
	  glVertex3f(path[i].x, path[i].y, path[i].z);
	}
      glEnd();
    }
  else
    {
//       glBegin(GL_TRIANGLE_FAN);
      glBegin(GL_LINE_LOOP);
      // line strips (no final connecting line)      
      for (unsigned long i = 0; i < path.length(); i++) glVertex3f(path[i].x, path[i].y, path[i].z);
      glEnd();
    }
}

void GLDrawingKit::draw_rectangle(const Vertex &lower, const Vertex &upper)
{
  if (_fs == Warsaw::DrawingKit::solid) glRectf(lower.x, lower.y, upper.x, upper.y);
  else if (_fs == Warsaw::DrawingKit::textured)
    {
      double w = (upper.x - lower.x)/(_tx->width * 10.);
      double h = (upper.y - lower.y)/(_tx->height * 10.);
      glBegin(GL_POLYGON);
      glTexCoord2f(0., 0.); glVertex2d(lower.x, lower.y);
      glTexCoord2f(w, 0.);  glVertex2d(upper.x, lower.y);
      glTexCoord2f(w, h);   glVertex2d(upper.x, upper.y);
      glTexCoord2f(0., h);  glVertex2d(lower.x, upper.y);
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

void GLDrawingKit::draw_quadric(const Warsaw::DrawingKit::Quadric, Warsaw::Coord, Warsaw::Coord)
{
}

void GLDrawingKit::draw_ellipse(const Vertex &lower, const Vertex &upper)
{
  glPushMatrix();
  glScaled(upper.x - lower.x, upper.y - lower.y, upper.z - lower.z);
  glTranslated(lower.x, lower.y, lower.z);
  GLQuadric quadric(_fs, GLQuadric::out);
  quadric.disk(0., 1., 360, 100);
  glPopMatrix();
}

void GLDrawingKit::draw_image(Raster_ptr raster)
{
  Profiler prf("GLDrawingKit::draw_image");
  GLImage *glimage = _images.lookup(Raster::_duplicate(raster));
  GLint tbackup = -1;
  if (_fs == Warsaw::DrawingKit::textured) glGetIntegerv(GL_TEXTURE_BINDING_2D, &tbackup);
  else glEnable(GL_TEXTURE_2D);
  GLfloat color_cache[4];
  glGetFloatv(GL_CURRENT_COLOR, color_cache);
  glBindTexture(GL_TEXTURE_2D, glimage->texture);
  glColor4f(_lt.red, _lt.green, _lt.blue, color_cache[3]); // use the current lighting
  glBegin(GL_POLYGON);
  Path path;
  path.length(4);
  Coord width = glimage->width*10.;
  Coord height = glimage->height*10.;
  path[0].x = path[0].y = path[0].z = 0.;
  path[1].x = width, path[1].y = path[1].z = 0.;
  path[2].x = width, path[2].y = height, path[2].z = 0.;
  path[3].x = 0, path[3].y = height, path[3].z = 0.;
  glTexCoord2f(0., 0.);                   glVertex3f(path[3].x, path[3].y, path[3].z);
  glTexCoord2f(glimage->s, 0.);           glVertex3f(path[2].x, path[2].y, path[2].z);
  glTexCoord2f(glimage->s, glimage->t);   glVertex3f(path[1].x, path[1].y, path[1].z);
  glTexCoord2f(0., glimage->t);           glVertex3f(path[0].x, path[0].y, path[0].z);
  glEnd();
  glColor4fv(color_cache);  
  if (_fs != Warsaw::DrawingKit::textured) glDisable(GL_TEXTURE_2D);
  else glBindTexture(GL_TEXTURE_2D, tbackup);
}

void GLDrawingKit::set_font_size(CORBA::ULong s) {}
void GLDrawingKit::set_font_weight(CORBA::ULong w) {}
void GLDrawingKit::set_font_family(const Unistring &f) {}
void GLDrawingKit::set_font_subfamily(const Unistring &sf) {}
void GLDrawingKit::set_font_fullname(const Unistring &fn) {}
void GLDrawingKit::set_font_style(const Unistring &s) {}
void GLDrawingKit::set_font_attribute(const NVPair & nvp) {}

void GLDrawingKit::directional_light(const Color &color,
				     CORBA::Float intensity,
				     const Vertex &direction)
{
  int id = _light->push();
  if (id < GL_LIGHT0) return;

  // RGBA intensities of source are the product of the color and
  // intensity, with 1.0 alpha
  GLfloat black[] = {0., 0., 0., 1.};
  GLfloat light[] = {color.red * intensity, color.green * intensity, color.blue * intensity, 1.};
  glLightfv(static_cast<GLenum>(id), GL_AMBIENT, black);
  glLightfv(static_cast<GLenum>(id), GL_DIFFUSE,  light);
  glLightfv(static_cast<GLenum>(id), GL_SPECULAR, light);

  // "Position" is the direction vector negated with a 0.0 w
  // component. Yet another GL peccadillo.
  GLfloat dir[] = {-direction.x, -direction.y, -direction.z, 0.};
  glLightfv(static_cast<GLenum>(id), GL_POSITION, dir);

  // Make sure no spotlight stuff is on
  glLightf(static_cast<GLenum>(id), GL_SPOT_EXPONENT, 0.0);
  glLightf(static_cast<GLenum>(id), GL_SPOT_CUTOFF, 180.0);

  // Attenuation does not matter for directional sources.
}

void GLDrawingKit::point_light(const Warsaw::Color &color,
			       CORBA::Float intensity,
			       const Warsaw::Vertex &position)
{
  int id = _light->push();
  if (id < GL_LIGHT0) return;

  // RGBA intensities of source are the product of the color and
  // intensity, with 1.0 alpha
  GLfloat black[] = {0., 0., 0., 1.};
  GLfloat light[] = {color.red * intensity, color.green * intensity, color.blue * intensity, 1.};
  glLightfv(static_cast<GLenum>(id), GL_AMBIENT, black);
  glLightfv(static_cast<GLenum>(id), GL_DIFFUSE,  light);
  glLightfv(static_cast<GLenum>(id), GL_SPECULAR, light);

  // Set position
  GLfloat dir[] = {position.x, position.y, position.z, 1.0};
  glLightfv(static_cast<GLenum>(id), GL_POSITION, dir);

  // Make sure no spotlight stuff is on
  glLightf(static_cast<GLenum>(id), GL_SPOT_EXPONENT, 0.0);
  glLightf(static_cast<GLenum>(id), GL_SPOT_CUTOFF, 180.0);

  // Attenuation is accessed from the state
  //   const SbVec3f &atten = SoLightAttenuationElement::get(action->getState());
  //   glLightf(static_cast<GLenum>(id), GL_CONSTANT_ATTENUATION,  atten[2]);
  //   glLightf(static_cast<GLenum>(id), GL_LINEAR_ATTENUATION,    atten[1]);
  //   glLightf(static_cast<GLenum>(id), GL_QUADRATIC_ATTENUATION, atten[0]);
}

void GLDrawingKit::spot_light(const Color &color,
			      CORBA::Float intensity,
			      const Vertex &position,
			      const Vertex &direction,
			      CORBA::Float dropoffrate,
			      CORBA::Float cutoffangle)
{
  int id = _light->push();
  if (id < GL_LIGHT0) return;

  // RGBA intensities of source are the product of the color and
  // intensity, with 1.0 alpha
  GLfloat black[] = {0., 0., 0., 1.};
  GLfloat light[] = {color.red * intensity, color.green * intensity, color.blue * intensity, 1.};
  glLightfv(static_cast<GLenum>(id), GL_AMBIENT, black);
  glLightfv(static_cast<GLenum>(id), GL_DIFFUSE,  light);
  glLightfv(static_cast<GLenum>(id), GL_SPECULAR, light);

  // Set position
  GLfloat pos[] = {position.x, position.y, position.z, 1.0};
  glLightfv(static_cast<GLenum>(id), GL_POSITION, pos);

  // Set up spotlight stuff. Note that the GL angle must be specified
  // in degrees, though the field is in radians
  GLfloat dir[] = {direction.x, direction.y, direction.z, 1.0};
  glLightfv(static_cast<GLenum>(id), GL_SPOT_DIRECTION, dir);

  if (dropoffrate <= 0.0)
    glLightf(static_cast<GLenum>(id), GL_SPOT_EXPONENT, .01);
  else 
    glLightf(static_cast<GLenum>(id), GL_SPOT_EXPONENT,  dropoffrate * 128.0);
  glLightf(static_cast<GLenum>(id), GL_SPOT_CUTOFF, cutoffangle*(180.0/M_PI));

  // Attenuation is accessed from the state
  //   const SbVec3f &atten = SoLightAttenuationElement::get(action->getState());
  //   glLightf(static_cast<GLenum>(id), GL_CONSTANT_ATTENUATION,  atten[2]);
  //   glLightf(static_cast<GLenum>(id), GL_LINEAR_ATTENUATION,    atten[1]);
  //   glLightf(static_cast<GLenum>(id), GL_QUADRATIC_ATTENUATION, atten[0]);
}

void GLDrawingKit::allocate_text(const Unistring &s, Graphic::Requisition &req) {}
void GLDrawingKit::draw_text(const Unistring &us) {}
void GLDrawingKit::allocate_char(Unichar c, Graphic::Requisition &req) { _font->allocate_char(c, req);}
void GLDrawingKit::draw_char(Unichar c) { _font->draw_char(c);}

void GLDrawingKit::draw_mesh(const Warsaw::Mesh &mesh)
{
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat light_position[] = { 5., 5., 10., 0.};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_CULL_FACE);

  bool normals = mesh.normals.length() == mesh.triangles.length();
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < mesh.triangles.length(); ++i)
    {
      if (normals)
	{
	  const Vertex &n = mesh.normals[i];
	  glNormal3f(n.x, n.y, n.z);
	}
      const Vertex &a = mesh.nodes[mesh.triangles[i].a];
      const Vertex &b = mesh.nodes[mesh.triangles[i].b];
      const Vertex &c = mesh.nodes[mesh.triangles[i].c];
      glVertex3f(a.x, a.y, a.z);
      glVertex3f(b.x, b.y, b.z);
      glVertex3f(c.x, c.y, c.z);
    }
  glEnd();
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_CULL_FACE);
}

void GLDrawingKit::copy_drawable(Drawable_ptr d, PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) {}

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "GLDrawingKit"};
  return create_kit<GLDrawingKit> ("IDL:Warsaw/DrawingKit3D:1.0", properties, 2);
}

