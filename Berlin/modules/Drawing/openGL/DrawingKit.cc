/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
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

#include <Prague/Sys/Profiler.hh>
#include <Fresco/config.hh>
#include <Fresco/Transform.hh>
#include <Fresco/IO.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Color.hh>
#include "Quadric.hh"
#include "DrawingKit.hh"
#include "FTFont.hh"
#include <iostream>

using namespace Prague;
using namespace Fresco;

openGL::DrawingKit::Light::Light()
  : _max(-1), _number(-1)
{
  glGetIntegerv(GL_MAX_LIGHTS, &_max);
}

int openGL::DrawingKit::Light::push()
{
  ++_number;
  if (_number >= _max) return -1;
  glEnable(static_cast<GLenum>(GL_LIGHT0 + _number));
  return GL_LIGHT0 + _number;
}

int openGL::DrawingKit::Light::top() const
{
  return GL_LIGHT0 + _number;
}

void openGL::DrawingKit::Light::pop()
{
  if (_number < _max) glDisable(static_cast<GLenum>(GL_LIGHT0 + _number));
  --_number;
}

openGL::DrawingKit::DrawingKit(const std::string &id, const Fresco::Kit::PropertySeq &p)
  : KitImpl(id, p),
    _drawable(0),
    _tx(0),
    _font(0),
    _light(0),
    _textures(100),
    _images(500)
{
}

KitImpl *openGL::DrawingKit::clone(const Fresco::Kit::PropertySeq &p)
{
  openGL::DrawingKit *kit = new openGL::DrawingKit(repo_id(), p);
  kit->init();
  return kit;
}

void openGL::DrawingKit::save()
{
  DrawingKitBase::save();
  _states.push(DrawState());
  _states.top().lights = _light->top();
}

void openGL::DrawingKit::restore()
{
  DrawingKitBase::restore();
  if (_states.empty()) return; // no state to restore
  DrawState &prev = _states.top();
  while (_light->top() > prev.lights) _light->pop();
  _states.pop();
}

void openGL::DrawingKit::init()
{
  Console *console = Console::instance();
  _drawable = console->drawable();
  _glcontext = console->get_extension<GLContext>("GLContext");

  _font = new FTFont();
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

openGL::DrawingKit::~DrawingKit()
{
  delete _font;
  delete _glcontext;
}

void openGL::DrawingKit::set_transformation(Transform_ptr t)
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

void openGL::DrawingKit::set_clipping(Region_ptr r)
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
      _glcontext->flush();
      sleep(1);
#endif
    }
}

void openGL::DrawingKit::set_foreground(const Color &c)
{
  _fg = c;
  glColor4d(_lt.red * _fg.red, _lt.green * _fg.green, _lt.blue * _fg.blue, _fg.alpha);
}

void openGL::DrawingKit::set_lighting(const Color &c)
{
  _lt = c;
  glColor4d(_lt.red * _fg.red, _lt.green * _fg.green, _lt.blue * _fg.blue, _fg.alpha);
}

void openGL::DrawingKit::set_point_size(Coord s)
{
  _ps = s;
  // FIXME !: glPointSize uses pixel units !
  glPointSize(_ps);
}

void openGL::DrawingKit::set_line_width(Coord w)
{
  _lw = w;
  // FIXME !: glLineWidth uses pixel units !
  glLineWidth(_lw);
}

void openGL::DrawingKit::set_line_endstyle(Fresco::DrawingKit::Endstyle style)
{
  _es = style;
}

void openGL::DrawingKit::set_surface_fillstyle(Fresco::DrawingKit::Fillstyle style)
{
  if (_fs == Fresco::DrawingKit::textured) glDisable(GL_TEXTURE_2D);
  _fs = style;
  if (_fs == Fresco::DrawingKit::textured) glEnable(GL_TEXTURE_2D);
}

void openGL::DrawingKit::set_texture(Raster_ptr t)
{
  _tx = CORBA::is_nil(t) ? 0 : _textures.lookup(Fresco::Raster::_duplicate(t));
  if (_tx) {
    glBindTexture(GL_TEXTURE_2D, _tx->texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }
}

// void openGL::DrawingKit::clear(Coord l, Coord t, Coord r, Coord b)
// {
//   glColor4d(0., 0., 0., 1.);
//   glRectf(l, t, r, b);
// }

void openGL::DrawingKit::draw_path(const Fresco::Path &path)
{
  if (path.shape != convex)
    {
      std::cerr << "openGL::DrawingKit::draw_path : sorry, non-convex paths not yet supported" << std::endl;
      return;
    }
  if (_fs == Fresco::DrawingKit::solid)
    {
      glBegin(GL_POLYGON);
//       glBegin(GL_LINE_LOOP);
      for (CORBA::ULong i = 0; i < path.nodes.length(); i++) glVertex3f(path.nodes[i].x, path.nodes[i].y, path.nodes[i].z);
      glEnd();
    }
  else if (_fs == Fresco::DrawingKit::textured)
    {
//       glBegin(GL_TRIANGLE_FAN);
      glBegin(GL_LINE_LOOP);
      for (CORBA::ULong i = 0; i < path.nodes.length(); i++)
	{
	  glTexCoord2f(path.nodes[i].x * _tx->width * 10., path.nodes[i].y * _tx->height * 10.); 
	  glVertex3f(path.nodes[i].x, path.nodes[i].y, path.nodes[i].z);
	}
      glEnd();
    }
  else
    {
//       glBegin(GL_TRIANGLE_FAN);
      glBegin(GL_LINE_LOOP);
      // line strips (no final connecting line)      
      for (CORBA::ULong i = 0; i < path.nodes.length(); i++) glVertex3f(path.nodes[i].x, path.nodes[i].y, path.nodes[i].z);
      glEnd();
    }
}

void openGL::DrawingKit::draw_rectangle(const Vertex &lower, const Vertex &upper)
{
  if (_fs == Fresco::DrawingKit::solid) glRectf(lower.x, lower.y, upper.x, upper.y);
  else if (_fs == Fresco::DrawingKit::textured)
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

void openGL::DrawingKit::draw_quadric(const Fresco::DrawingKit::Quadric, Fresco::Coord, Fresco::Coord)
{
}

void openGL::DrawingKit::draw_ellipse(const Vertex &lower, const Vertex &upper)
{
  glPushMatrix();
  glScaled(upper.x - lower.x, upper.y - lower.y, upper.z - lower.z);
  glTranslated(lower.x, lower.y, lower.z);
  Quadric quadric(_fs, Quadric::out);
  quadric.disk(0., 1., 360, 100);
  glPopMatrix();
}

void openGL::DrawingKit::draw_image(Raster_ptr raster)
{
  Profiler prf("openGL::DrawingKit::draw_image");
  Image *image = _images.lookup(Fresco::Raster::_duplicate(raster));
  GLint tbackup = -1;
  if (_fs == Fresco::DrawingKit::textured) glGetIntegerv(GL_TEXTURE_BINDING_2D, &tbackup);
  else glEnable(GL_TEXTURE_2D);
  GLfloat color_cache[4];
  glGetFloatv(GL_CURRENT_COLOR, color_cache);
  glBindTexture(GL_TEXTURE_2D, image->texture);
  glColor4f(_lt.red, _lt.green, _lt.blue, color_cache[3]); // use the current lighting
  glBegin(GL_POLYGON);
  Fresco::Path path;
  path.nodes.length(4);
  path.shape = convex;
  Coord width = image->width*10.;
  Coord height = image->height*10.;
  path.nodes[0].x = path.nodes[0].y = path.nodes[0].z = 0.;
  path.nodes[1].x = width, path.nodes[1].y = path.nodes[1].z = 0.;
  path.nodes[2].x = width, path.nodes[2].y = height, path.nodes[2].z = 0.;
  path.nodes[3].x = 0, path.nodes[3].y = height, path.nodes[3].z = 0.;
  glTexCoord2f(0., 0.);               glVertex3f(path.nodes[3].x, path.nodes[3].y, path.nodes[3].z);
  glTexCoord2f(image->s, 0.);         glVertex3f(path.nodes[2].x, path.nodes[2].y, path.nodes[2].z);
  glTexCoord2f(image->s, image->t);   glVertex3f(path.nodes[1].x, path.nodes[1].y, path.nodes[1].z);
  glTexCoord2f(0., image->t);         glVertex3f(path.nodes[0].x, path.nodes[0].y, path.nodes[0].z);
  glEnd();
  glColor4fv(color_cache);  
  if (_fs != Fresco::DrawingKit::textured) glDisable(GL_TEXTURE_2D);
  else glBindTexture(GL_TEXTURE_2D, tbackup);
}

void openGL::DrawingKit::set_font_size(CORBA::ULong s) { _font->size(s); }
void openGL::DrawingKit::set_font_weight(CORBA::ULong w) {}
void openGL::DrawingKit::set_font_family(const Unistring &f) {}
void openGL::DrawingKit::set_font_subfamily(const Unistring &sf) {}
void openGL::DrawingKit::set_font_fullname(const Unistring &fn) {}
void openGL::DrawingKit::set_font_style(const Unistring &s) {}
void openGL::DrawingKit::set_font_attribute(const NVPair & nvp) {}

void openGL::DrawingKit::directional_light(const Color &color,
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

void openGL::DrawingKit::point_light(const Fresco::Color &color,
			       CORBA::Float intensity,
			       const Fresco::Vertex &position)
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

void openGL::DrawingKit::spot_light(const Color &color,
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

void openGL::DrawingKit::allocate_text(const Unistring &s, Graphic::Requisition &req) {}
void openGL::DrawingKit::draw_text(const Unistring &us) {}
void openGL::DrawingKit::allocate_char(Unichar c, Graphic::Requisition &req) { _font->allocate_char(c, req);}
void openGL::DrawingKit::draw_char(Unichar c) { _font->draw_char(c);}

void openGL::DrawingKit::draw_mesh(const Fresco::Mesh &mesh)
{
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
//   GLfloat light_position[] = { 5., 5., 10., 0.};
//   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_COLOR_MATERIAL);
  //glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  bool normals = mesh.normals.length() == mesh.triangles.length();
  glBegin(GL_TRIANGLES);
  for (CORBA::ULong i = 0; i < mesh.triangles.length(); ++i)
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
  glDisable(GL_DEPTH_TEST);
  glClear(GL_DEPTH_BUFFER_BIT);
  //glDisable(GL_CULL_FACE);
}

void openGL::DrawingKit::copy_drawable(Drawable_ptr d, PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) {}

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "GLDrawingKit"};
  return create_kit<openGL::DrawingKit> ("IDL:fresco.org/Fresco/DrawingKit3D:1.0", properties, 2);
}

