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

void LibArtUnifont::segments(const Unistring u, 
			     vector<segment> &segs) {
  unsigned int len = u.length();
  segs.reserve(len);
  unsigned char *glyphs = (unsigned char *)glyphmap->addr();  
  int width = 0;
  int height = 16;
  int pixwidth = 4;  
 
  for(unsigned int idx = 0; idx < len; ++idx) {
    unsigned int stride = 33;
    Unichar ch = u[idx];
    unsigned int base = stride * ch;
    bool is_halfwidth = (glyphs[base] == (unsigned char)0xFF) ? 1 : 0;
    width = is_halfwidth ? 8 : 16; 
    if (cache.find(ch) == cache.end()) {
      unsigned char *pixels = new unsigned char[width * height * pixwidth];
      memset(pixels,0,width * height * pixwidth);
      glyph2pixels(ch,pixels);
      ArtPixBuf *buf = art_pixbuf_new_const_rgba(pixels, 
						 width, 
						 height, 
						 width * pixwidth);
      cache.insert(pair<Unichar,ArtPixBuf *>(ch,buf));
    }
    segs.push_back(segment(step(width,0),cache[ch]));		   
  }    
}

void LibArtUnifont::glyph2pixels(const Unichar ch, unsigned char pix[]) {
  unsigned char *glyphs = (unsigned char *)glyphmap->addr();
  const unsigned int stride = 33;
  unsigned long base = stride * ch;
  bool is_halfwidth = (glyphs[base] == (unsigned char)0xFF) ? 1 : 0;
  base++;			// advance past the width marker  
  unsigned int cols = is_halfwidth ? 1 : 2; 
  const unsigned int rows = 16;
  const unsigned int bitsinbyte = 8;
  const unsigned int pixsz = 4;

#define GLYPHBYTE(row,col) (glyphs[base + ((rows-(row+1))*cols) + col])
#define IS_SET(bit,byt) (byt & (1 << (bitsinbyte-(bit+1))))
  
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      for (int bit = 0; bit < bitsinbyte; ++bit, pix += pixsz) {
	if (IS_SET(bit, GLYPHBYTE(row,col))) {
	  *(pix + 3) = 0xff;
	}
      }
    }
  }
}

void LibArtUnifont::allocateText(const Unistring &u, Graphic::Requisition &r)
{    
  unsigned char *glyphs = (unsigned char *)glyphmap->addr();
  
  int width = 0;
  int height = 16;
  
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

