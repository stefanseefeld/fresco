/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 2002 Nick Lewycky <nicholas@fresco.org> 
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

#include <Prague/Sys/MMap.hh>
#include <Prague/Sys/Path.hh>
#include <Berlin/RCManager.hh>
#include <Berlin/GraphicImpl.hh>
#include "FTFont.hh"
#include FT_GLYPH_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

using namespace Prague;
using namespace Fresco;

openGL::FTFont::FTFont()
  : _family(Unicode::to_CORBA(Babylon::String("GNU Unifont"))),
    _subfamily(),
    _fullname(),
    _style(Unicode::to_CORBA(Babylon::String("monospace")))
{
  Prague::Path path = RCManager::get_path("unifontpath");
  std::string font_file = path.lookup_file("unifont.bdf");
  FT_Init_FreeType(&my_library);
  FT_New_Face(my_library, font_file.c_str(), 0, &my_face);
  FT_Set_Pixel_Sizes(my_face, 0, 14);
}

openGL::FTFont::~FTFont() {
}

CORBA::ULong openGL::FTFont::weight() { return 100;}
Unistring *openGL::FTFont::family() { return new Unistring(_family);}
Unistring *openGL::FTFont::subfamily() { return new Unistring(_subfamily);}
Unistring *openGL::FTFont::fullname() { return new Unistring(_fullname);}
Unistring *openGL::FTFont::style() { return new Unistring(_style);}

DrawingKit::FontMetrics openGL::FTFont::metrics()
{
  DrawingKit::FontMetrics fm;

  if (!FT_IS_SCALABLE(my_face)) { // XXX
    // GNU Unifont . the bdf reader returns all 0s through size->metrics.
    fm.ascender = 16 << 6;
    fm.descender = 0;
    fm.height = 16 << 6;
    fm.max_advance = 16 << 6;
  } else {
    fm.ascender = my_face->size->metrics.ascender;
    fm.descender = my_face->size->metrics.descender;
    fm.height = my_face->size->metrics.height;
    fm.max_advance = my_face->size->metrics.max_advance;
  }

  return fm;
}

DrawingKit::GlyphMetrics openGL::FTFont::metrics(Unichar uc)
{
  DrawingKit::GlyphMetrics gm;

  FT_Load_Glyph(my_face, FT_Get_Char_Index(my_face, (FT_ULong)uc), FT_LOAD_DEFAULT);

  double scale = 1.;
  gm.width = static_cast<CORBA::Long>(my_face->glyph->metrics.width / scale);
  gm.height = static_cast<CORBA::Long>(my_face->glyph->metrics.height / scale);
  gm.horiBearingX = static_cast<CORBA::Long>(my_face->glyph->metrics.horiBearingX / scale);
  gm.horiBearingY = static_cast<CORBA::Long>(my_face->glyph->metrics.horiBearingY /scale);
  gm.horiAdvance =  static_cast<CORBA::Long>(my_face->glyph->metrics.horiAdvance / scale);
  gm.vertBearingX = static_cast<CORBA::Long>(my_face->glyph->metrics.vertBearingX / scale);
  gm.vertBearingY = static_cast<CORBA::Long>(my_face->glyph->metrics.vertBearingY / scale);
  gm.vertAdvance = static_cast<CORBA::Long>(my_face->glyph->metrics.vertAdvance / scale);

  return gm;
}

static inline bool is_pow2(unsigned int x)
{
  return x != 0 && !(x & (x-1));
}

// The LSB is 0, the MSB is (e.g.) 31.
static inline unsigned int highest_bit_set(unsigned int x)
{
  assert(x != 0);

  unsigned int k;
  for (k = 0; x >>= 1; k++)
    /* nothing */;
  return k;
}

static inline unsigned int next_pow2(unsigned int n)
{
  assert(n <= UINT_MAX / 2);

  if (n == 0 || is_pow2(n)) return n;
  else return 1 << (highest_bit_set(n) + 1);
}

void openGL::FTFont::draw_char(Unichar uc) 
{
  Fresco::Graphic::Requisition r;
  GraphicImpl::init_requisition(r);
  allocate_char(uc, r);

  //std::cerr << "loading: " << (FT_ULong)uc << " (";
  //std::cerr << FT_Get_Char_Index(my_face, (FT_ULong)uc) << ")";
  if (FT_Load_Glyph(my_face, FT_Get_Char_Index(my_face, (FT_ULong)uc), FT_LOAD_DEFAULT)) { return; }
  //assert(!FT_Load_Glyph(my_face, FT_Get_Char_Index(my_face, (FT_ULong)uc), FT_LOAD_DEFAULT));
  //std::cerr << std::endl;

  FT_Vector origin; origin.x = 0; origin.y = 0;

  FT_Glyph glyph;
  FT_Get_Glyph(my_face->glyph, &glyph);

  FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, &origin, 1);
  FT_BitmapGlyph glyph_bitmap = (FT_BitmapGlyph)glyph;

  unsigned char *buffer = glyph_bitmap->bitmap.buffer;
  int width = glyph_bitmap->bitmap.width;
  int height = glyph_bitmap->bitmap.rows;

  int x_zoom = 10;
  int y_zoom = 10;

  // XXX: every return in the following block. Instead we should be
  // breaking oversized characters into pieces of textures and drawing
  // them all. Max texture size on a Voodoo is just 256 texels on a side.
  GLint maxsize, w, h; 
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxsize);
  w = next_pow2(width);
  h = next_pow2(height);

  while (w*h < 64)
    if (w < h) { w = next_pow2(w+1); } else { h = next_pow2(h+1); }

  if (w > maxsize || h > maxsize) {
    std::cerr << "Character too large to render." << std::endl;
    return;
  }

  std::vector<unsigned char> pixels(w*h, 0);

  GLint internal_format;
  GLenum format, type;  

  switch (glyph_bitmap->bitmap.pixel_mode)
    {
    case FT_PIXEL_MODE_NONE:
      std::cout << "WTF;FT_PIXEL_MODE_NONE" << std::endl; // should never happen
      break;
    case FT_PIXEL_MODE_MONO: // MSB 1 bpp
      internal_format = GL_ALPHA;
      format = GL_ALPHA;
      type = GL_UNSIGNED_BYTE;
      //x_zoom = 10; y_zoom = 10;
      for (int i = 0; i < height; i++) {
	for (int j = 0; j < width; j++) {
	  pixels[i*w + j] = (buffer[i*(width/8)+(j/8)] & (0x80 >> j%8)) ? 0xFF : 0;
	}
      }
      break;
    case FT_PIXEL_MODE_GRAY: // 8 bpp count of grey levels in num_bytes
      //x_zoom = 1; y_zoom = 1;
      internal_format = GL_ALPHA;
      format = GL_ALPHA;
      type = GL_UNSIGNED_BYTE;
      for (int i = 0; i < height; i++) {
	for (int j = 0; j < width; j++) {
	  pixels[i*w+j] = buffer[i*width+j];
	}
      }
      break;
    case FT_PIXEL_MODE_GRAY2: // 2bpp (no known fonts)
      std::cout << "NYI;FT_PIXEL_MODE_GRAY2" << std::endl;
      break;
    case FT_PIXEL_MODE_GRAY4: // 4bpp (no known fonts)
      std::cout << "NYI;FT_PIXEL_MODE_GRAY4" << std::endl;
      break;
    case FT_PIXEL_MODE_LCD: // 8bpp RGB or BGR, width=3*glyph_width
      std::cout << "NYI;FT_PIXEL_MODE_LCD" << std::endl;
      break;
    case FT_PIXEL_MODE_LCD_V: // 8bpp RGB or BGR, height=3*glyph_rows
      std::cout << "NYI;FT_PIXEL_MODE_LCD_V" << std::endl;
      break;
    default:
      std::cout << "Unknown: " << glyph_bitmap->bitmap.pixel_mode << std::endl;
      break;
    }

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, internal_format, w, h, 0, format, type, &pixels[0]);
  gluBuild2DMipmaps(GL_TEXTURE_2D, internal_format, w, h, format, type, &pixels[0]);
  
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  float top = -height * r.y.align;
  glTexCoord2f(0, 1); glVertex3f(0.0, (top+h)*y_zoom, 0.0);
  glTexCoord2f(1, 1); glVertex3f(w*x_zoom, (top+h)*y_zoom, 0.0);
  glTexCoord2f(1, 0); glVertex3f(w*x_zoom, top*y_zoom, 0.0);
  glTexCoord2f(0, 0); glVertex3f(0.0, top*y_zoom, 0.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &texture);
}

void openGL::FTFont::allocate_char(Unichar uc, Graphic::Requisition &r)
{
  FT_Load_Glyph(my_face, FT_Get_Char_Index(my_face, (FT_ULong)uc), FT_LOAD_DEFAULT);

  DrawingKit::GlyphMetrics gm = metrics(uc);
  r.x.natural = r.x.minimum = r.x.maximum = (gm.horiAdvance*10) >> 6;
  r.x.defined = true;
  r.x.align = gm.width == 0 ? 0. : ((double)gm.horiBearingX)/((double)gm.horiAdvance);
  r.y.natural = r.y.minimum = r.y.maximum = (gm.height*10) >> 6;
  r.y.defined = true;
  r.y.align = gm.height == 0 ? 0. : ((double)gm.horiBearingY)/((double)gm.height); 
}

// what's this in? points? Fresco::Coord? Fresco::PixelCoord?
void openGL::FTFont::size(CORBA::ULong s)
{
  my_size = s;
  FT_Set_Pixel_Sizes(my_face, 0, my_size);
}

CORBA::ULong openGL::FTFont::size()
{
  return my_size;
}
