/*$Id$
 *
 * This source file is a part of the Fresco Project.
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

#include <Prague/Sys/Path.hh>
#include <Prague/Sys/MMap.hh>
#include <Berlin/RCManager.hh>
#include "Unifont.hh"

#include <libart_lgpl/art_rgb.h> // for art_rgb_run_alpha

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cerrno>

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

// This is a default font, just in case -- a character cell bitmapped unicode
// font which is generated "on the fly" from the GNU unifont, which we're
// storing in a packed binary array we mmap() in. this is so that, even if all
// the font manufactureres in the world turn against us, we can still render
// multilingual text, albeit not quite as well as certain (ahem) proprietary
// text systems

using namespace Prague;
using namespace Fresco;

libArt::Unifont::Unifont(double xres, double yres)
  : _xres(xres),
    _yres(yres)
{
  Prague::Path path = RCManager::get_path("unifontpath");
  std::string glyphDB = path.lookup_file("glyph.dat");
  _glyphmap = new MMap(glyphDB, -1, MMap::read, MMap::shared, 0, 0);
  _buffer = art_pixbuf_new_rgb (_slab, 16, 16, 16);  
}

libArt::Unifont::~Unifont() { delete _glyphmap; art_pixbuf_free(_buffer);}
CORBA::ULong libArt::Unifont::size() { return 16;}
CORBA::ULong libArt::Unifont::weight() { return 100;}
Unistring *libArt::Unifont::family() { return new Unistring(Unicode::to_CORBA(Babylon::String("GNU Unifont")));}
Unistring *libArt::Unifont::subfamily() { return 0;}
Unistring *libArt::Unifont::fullname() { return 0;}
Unistring *libArt::Unifont::style() { return new Unistring(Unicode::to_CORBA(Babylon::String("monospace")));}

DrawingKit::FontMetrics libArt::Unifont::metrics()
{
  DrawingKit::FontMetrics fm;
  fm.ascender = 16 << 6;
  fm.descender = 0;
  fm.height = 16 << 6;
  fm.max_advance = 16 << 6;
  return fm;
}

DrawingKit::GlyphMetrics libArt::Unifont::metrics(Unichar &uc)
{
  unsigned char *glyphs = (unsigned char *)_glyphmap->addr();  

  DrawingKit::GlyphMetrics gm;
  gm.width = (glyphs[uc * 33] == (unsigned char)0xFF) ? 8  << 6: 16 << 6;
  gm.height = 16 << 6;
  gm.horiBearingX = 0;
  gm.horiBearingY = gm.height;
  gm.horiAdvance =  gm.width;
  gm.vertBearingX = 0;
  gm.vertBearingY = 0;
  gm.vertAdvance = gm.height;
  return gm;
}

void libArt::Unifont::buffer(Unichar ch, ArtPixBuf *&pb)
{
  unsigned char *glyphs = (unsigned char *)_glyphmap->addr();  
  int width = (glyphs[ch * 33] == (unsigned char)0xFF) ? 8 : 16;  
  memset(_slab, 0, 16*16);
  glyph_to_pixels(ch, _slab);
  _buffer->width = _buffer->rowstride = width;
  pb = _buffer;
}

void libArt::Unifont::glyph_to_pixels(Unichar ch, unsigned char pix[])
{
  unsigned char *glyphs = (unsigned char *)_glyphmap->addr();
  const unsigned int stride = 33;
  unsigned long base = stride * ch;
  bool is_halfwidth = (glyphs[base] == (unsigned char)0xFF) ? 1 : 0;
  base++;			// advance past the width marker  
  unsigned int cols = is_halfwidth ? 1 : 2; 
  const unsigned int rows = 16;
  const unsigned int bitsinbyte = 8;
  const unsigned int pixsz = 1;

#define GLYPHBYTE(row,col) (glyphs[base + ((rows-(row+1))*cols) + col])
#define IS_SET(bit,byt) (byt & (1 << (bitsinbyte-(bit+1))))
  
  for (unsigned int row = 0; row < rows; ++row) {
    for (unsigned int col = 0; col < cols; ++col) {
      for (unsigned int bit = 0; bit < bitsinbyte; ++bit, pix += pixsz) {
	if (IS_SET(bit, GLYPHBYTE(row,col))) {
	  *(pix) = 0xff;
	}
      }
    }
  }
}

void libArt::Unifont::allocate_char(Unichar u, Graphic::Requisition &r)
{    
  unsigned char *glyphs = (unsigned char *)_glyphmap->addr();  
  int height = 16;
  int width = (glyphs[u * 33] == (unsigned char)0xFF) ? 8 : 16;  
  r.x.natural = r.x.minimum = r.x.maximum = width / _xres;
  r.x.defined = true;
  r.x.align = 0.;
  r.y.natural = r.y.minimum = r.y.maximum = height / _yres;
  r.y.defined = true;
  r.y.align = 1.;
}

