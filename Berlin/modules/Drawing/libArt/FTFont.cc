/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Graydon Hoare <graydon@pobox.com> 
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

#include "Berlin/Logger.hh"
#include <Drawing/libArt/LibArtFTFont.hh>
#include <Prague/Sys/Directory.hh>
#include <fstream>
#include <map>
#include <string>

#define FLOOR(x)  ((x) & -64)
#define CEIL(x)   (((x)+63) & -64)
#define TRUNC(x)  ((x) >> 6)
#define MAX(X,Y) (X>Y?X:Y)
#define MIN(X,Y) (X<Y?X:Y)

using namespace Prague;

LibArtFTFont::LibArtFTFont(GGI::Drawable *drawable) :
  xdpi(drawable->dpi(xaxis)),
  ydpi(drawable->dpi(yaxis)),
  xres(drawable->resolution(xaxis)),
  yres(drawable->resolution(yaxis)),
  mySize(20)
{
  if (FT_Init_FreeType( &myLibrary )) {
      cerr << "failed to open freetype library" << endl;
      exit(-1);    
  }
  char *env = getenv("BERLIN_ROOT");
  if (!env)
    {
      cerr << "Please set environment variable BERLIN_ROOT first" << endl;
      exit(-1);
    }
  string fname = string(env) + "/etc/fonts.txt";
  ifstream fontdirlist(fname.c_str());
  if (!fontdirlist) {
    Logger::log(Logger::text) << "cannot open " << fname << endl;
  } else {
    string fontdir;
    while (fontdirlist >> fontdir) {
      Directory directory(fontdir, Directory::alpha);
      Logger::log(Logger::text) << 
	"LibArtFTFont: scanning font dir " << 
	fontdir << endl;
      for (Directory::iterator i = directory.begin();
	   i != directory.end(); i++)
	{
	  if ((*i)->name() == "." || (*i)->name() == "..") continue;	  
	  string fontfile = (*i)->longName();
	  if (FT_New_Face
	      (myLibrary,
	       fontfile.c_str(),
	       0,
	       &myFace)) {
	    Logger::log(Logger::text) << 
	      "LibArtFTFont: can't open font " << 
	      fontfile << endl;
	    continue;
	  }
	  myFamStr = Unicode::String(myFace->family_name);
	  myStyleStr = Unicode::String(myFace->style_name);
	  myFam = atomize(myFamStr);
	  myStyle = atomize(myStyleStr);
	  Logger::log(Logger::text) << "found FT-readable font " << 
	    myFamStr << " (" << myFam << ") " << myStyleStr << " (" << myStyle << ") in " << fontfile << endl;
	  myFaceMap[FamStyle(myFam,myStyle)] = myFace;
	}
    }
    fontdirlist.close();
    Logger::log(Logger::text) << "completed scaning font directories" << endl;
  }
}


LibArtFTFont::~LibArtFTFont() {}
unsigned long LibArtFTFont::size() { return mySize;}
unsigned long LibArtFTFont::weight() { return 100;}
void LibArtFTFont::size(unsigned long sz) { mySize = sz;}
void LibArtFTFont::weight(unsigned long wt) {}

Unistring *LibArtFTFont::family() { 
  return new Unistring
    (Unicode::toCORBA
     (Unicode::String(myFamStr)));
}

Unistring *LibArtFTFont::subfamily() { 
  return 0;
}

void LibArtFTFont::subfamily(const Unistring &fname) { 
}

void LibArtFTFont::fullname(const Unistring &fname) { 
}

void LibArtFTFont::family(const Unistring &fname) { 
  myFamStr = Unicode::toPrague(fname);
  myFam = atomize(myFamStr);
}

void LibArtFTFont::style(const Unistring &sname) { 
  myStyleStr = Unicode::toPrague(sname);
  myStyle = atomize(myStyleStr);
}

Unistring *LibArtFTFont::fullname() { 
  Unicode::String str = myFamStr;
  str += Unicode::Char(' ');
  str += myStyleStr;
  return new Unistring(Unicode::toCORBA(str));
}

Unistring *LibArtFTFont::style() { 
  return new Unistring
    (Unicode::toCORBA
     (Unicode::String(myStyleStr)));
}

void LibArtFTFont::setup_face(FT_Face &f) {
  FamStyle spec(myFam,myStyle);
  if (myFaceMap.find(spec) != myFaceMap.end()) {
    f = myFaceMap[spec];
  } else {
    f = myFace;
  }
}

void LibArtFTFont::setup_size(FT_Face &f) {
  FT_Set_Char_Size
    ( f,                // handle to face object           
      mySize << 6,     // char_width in 1/64th of points  
       mySize << 6,     // char_height in 1/64th of points 
      72, 72);
//       (unsigned int)xdpi,             // horizontal device resolution    
//       (unsigned int)ydpi );           // vertical device resolution      
}

bool LibArtFTFont::load_glyph(Unichar c, FT_Face &f) {
  int idx = FT_Get_Char_Index(f,(unsigned char)c);
  if (FT_Load_Glyph (f,idx,0)) {
    return false;
  }
  return true;
}
  
static inline bool render_pixbuf(ArtPixBuf **pb, 
				  FT_GlyphSlot &glyph,
				  FT_Library &library) {
    
  // first, render the glyph into an intermediate buffer
  FT_Bitmap  bit;

  int pixwidth = 4;
  int left  = FLOOR( glyph->metrics.horiBearingX );
  int right = CEIL( glyph->metrics.horiBearingX + glyph->metrics.width );
  int width = TRUNC(right - left);
  int top    = CEIL( glyph->metrics.horiBearingY );
  int bottom = FLOOR( glyph->metrics.horiBearingY - glyph->metrics.height );
  int height = TRUNC( top - bottom );
  
  if ( glyph->format != ft_glyph_format_outline ) return false;
       
  int pitch  = (width+3) & -4;
  int size   = pitch*height;             
  char   bit_buffer[size];
  bit.width      = width;
  bit.rows       = height;
  bit.pitch      = pitch;
  bit.pixel_mode = ft_pixel_mode_grays;
  bit.buffer     = bit_buffer;      

  FT_Outline_Translate(&glyph->outline, -left, -bottom );    
  memset( bit_buffer, 0, size );      
  if (FT_Outline_Get_Bitmap( library, &glyph->outline, &bit)) return false;
      
  // now build a pixbuf
  unsigned char *pixels = 
    new unsigned char[size * pixwidth];
  memset(pixels,0,size * pixwidth);
  *pb = art_pixbuf_new_const_rgba
    (pixels, width, height, width * pixwidth);
  
  // copy alpha values
  for (int row = 0; row < height; ++row) 
    for (int col = 0; col < width; ++col)
      *(pixels + (((row * width) + col) * pixwidth) + 3) = 
	*(bit_buffer + (row * pitch) + col);
  return true;
}


ArtPixBuf *LibArtFTFont::getPixBuf(const Unichar ch) {
  FT_Face newface;
  setup_face(newface);
  setup_size(newface);
  FaceSpec fspec(mySize,FamStyle(myFam,myStyle));
  CacheSpec cspec(ch,fspec);
  CacheIter ci = myCache.find(cspec);
  ArtPixBuf *pb;
  if (ci == myCache.end()) {
    if (!load_glyph(ch,newface)) return 0;
    if (!render_pixbuf(&pb,newface->glyph,myLibrary)) return 0;      
    myCache.insert(pair<CacheSpec,ArtPixBuf *>(cspec,pb));
    return pb;
  } else {
    return ci->second;
  }
}


void LibArtFTFont::allocateChar(Unichar ch, Graphic::Requisition &r) {
  FT_Face newface;
  setup_face(newface);
  setup_size(newface);
  FT_GlyphSlot glyph = newface->glyph;
  if (!load_glyph(ch,newface)) return;       

  double yscale = yres * 64;
  double xscale = xres * 64;

  r.x.natural = r.x.minimum = r.x.maximum = ((double)(glyph->metrics.horiAdvance)) / xscale;
  r.x.defined = true;
  r.x.align = 0.;
  r.y.natural = r.y.minimum = r.y.maximum = ((double)(glyph->metrics.height)) / yscale; 
  r.y.defined = true;
     
  double b = glyph->metrics.horiBearingY;
  double h = glyph->metrics.height;
  r.y.align = (h == 0.) ? 0. : b/h; 
}

