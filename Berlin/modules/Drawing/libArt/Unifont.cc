/*$Id$
 *
 * This source file is a part of the Berlin Project.
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

#include <Drawing/libArt/LibArtUnifont.hh>
#include <Prague/Sys/MMap.hh>

#include <art_rgb.h> // for art_rgb_run_alpha

#include <string>
#include <string.h>
#include <iostream>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

// This is a default font, just in case -- a character cell bitmapped unicode
// font which is generated "on the fly" from the GNU unifont, which we're
// storing in a packed binary array we mmap() in. this is so that, even if all
// the font manufactureres in the world turn against us, we can still render
// multilingual text, albeit not quite as well as certain (ahem) proprietary
// text systems

LibArtUnifont::LibArtUnifont()
{
    char *env = getenv("BERLIN_ROOT");
    if (!env)
      {
	cerr << "Please set environment variable BERLIN_ROOT first" << endl;
	exit(-1);
      }
    string glyphDB = string(env) + "/etc/glyph.dat";
    glyphmap = new MMap(glyphDB, -1, MMap::read, MMap::shared, 0, 0);
}

LibArtUnifont::~LibArtUnifont() { delete glyphmap ;}
unsigned long LibArtUnifont::size() { return 16;}
unsigned long LibArtUnifont::weight() { return 100;}
Unistring *LibArtUnifont::family() { return new Unistring(Unicode::toCORBA(Unicode::String("GNU Unifont")));}
Unistring *LibArtUnifont::subfamily() { return 0;}
Unistring *LibArtUnifont::fullname() { return 0;}
Unistring *LibArtUnifont::style() { return new Unistring(Unicode::toCORBA(Unicode::String("monospace")));}

void LibArtUnifont::drawText(const Unistring &u, const int x, const int y, ArtPixBuf *pb, Color &myColor)
{
  unsigned char *glyphs = (unsigned char *)glyphmap->addr();
  // prepare LibArt to draw

  int byte_off_in_pixbuf = 0;  
  for (unsigned long idx = 0; idx < u.length(); idx++)
    {
      art_u8 r = (art_u8)(myColor.red * 0xff);
      art_u8 g = (art_u8)(myColor.green * 0xff);
      art_u8 b = (art_u8)(myColor.blue * 0xff);
      art_u8 a = (art_u8)(myColor.alpha * 0xff);
      int stride = 33;
      int base = stride * u[idx];
      bool is_halfwidth = (glyphs[base] == (unsigned char)0xFF) ? 1 : 0;
      base++;			// advance past the width marker

      int width = is_halfwidth ? 1 : 2; 

#define bitsinbyte 8
#define bpp 3

      int pixbuf_base = (y * pb->rowstride) + (x * bpp) + byte_off_in_pixbuf;
      int pixbuf_max_pos = pb->rowstride * pb->height;

#define height 16
#define colbytes 24

#define GLYPHBYTE(row,col) (glyphs[base + ((height-(row+1))*width) + col])
#define IS_SET(bit,byt) (byt & (1 << (bitsinbyte-(bit+1))))

      for (int row = 0; row < height; row++) {
	for (int col = 0; col < width; col++) {
	  for (int bit = 0; bit < bitsinbyte; bit++) {
	    int off = pixbuf_base + row * pb->rowstride + col*colbytes + bit*bpp;
	    if (IS_SET(bit, GLYPHBYTE(row,col)) 
		&& (off) < pixbuf_max_pos) {		
	      art_rgb_run_alpha(pb->pixels + off, r,g,b,a, 1);
	    }
	  }
	}
      }
      byte_off_in_pixbuf += width * colbytes;
    }
}

void LibArtUnifont::allocateText(const Unistring &u, Graphic::Requisition &r)
{    
  unsigned char *glyphs = (unsigned char *)glyphmap->addr();
  
  int width = 0;
  
  for(unsigned int idx = 0; idx < u.length(); idx++) {
    unsigned int stride = 33;
    unsigned int base = stride * u[idx];
    bool is_halfwidth = (glyphs[base] == (unsigned char)0xFF) ? 1 : 0;
    width += is_halfwidth ? 8 : 16; 
  }
  
  r.x.natural = r.x.minimum = r.x.maximum = width*10.;
  r.x.defined = true;
  r.x.align = 0.;
  r.y.natural = r.y.minimum = r.y.maximum = height*10.;
  r.y.defined = true;
  r.y.align = 0.;
}

