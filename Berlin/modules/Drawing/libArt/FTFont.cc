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
#define MAX(X,Y) (X<Y?X:Y)

LibArtFTFont::LibArtFTFont(GGI::Drawable *drawable) :
  xdpi(drawable->dpi(xaxis)),
  ydpi(drawable->dpi(yaxis))
{
  if (FT_Init_FreeType( &library )) {
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
  ifstream fontdirlist(fname);
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
	  FT_Face newface;
	  string fontfile = i->longName();
	  if (FT_New_Face
	      (library,
	       fontfile.c_str(),
	       0,
	       &newface)) {
	    Logger::log(Logger::text) << 
	      "LibArtFTFont: can't open font " << 
	      fontfile << endl;
	    continue;
	  }
	  string fam(newface->family_name);
	  string style(newface->style_name);
	  Logger::log(Logger::text) << "found FT-readable font " << 
	    fam << " " << style << " in " << fontfile << endl;
	  facemap[famStyle(atomize(fam),
			   atomize(style))]
	    = newface;	  
	}
    }
    fontdirlist.close();
  }
}


LibArtFTFont::~LibArtFTFont() {}
unsigned long LibArtFTFont::size() { return my_size;}
unsigned long LibArtFTFont::weight() { return 100;}
void LibArtFTFont::size(unsigned long sz) { my_size = sz;}
void LibArtFTFont::weight(unsigned long wt) {}

Unistring *LibArtFTFont::family() { 
  return new Unistring
    (Unicode::toCORBA
     (Unicode::String(my_famstr)));
}

Unistring *LibArtFTFont::subfamily() { 
  return 0;
}

void LibArtFTFont::subfamily(const Unistring *fname) { 
}

void LibArtFTFont::fullname(const Unistring *fname) { 
}

void LibArtFTFont::family(const Unistring *fname) { 
  my_famstr = Unicode::toPrague(fname);
  my_fam = atomize(my_famstr);
}

void LibArtFTFont::style(const Unistring *sname) { 
  my_stylestr = Unicode::toPrague(sname);
  my_style = atomize(my_style);
}

Unistring *LibArtFTFont::fullname() { 
  return new Unistring
    (Unicode::toCORBA	     
     (Unicode::String
      (my_famstr + " " + my_stylestr)));
                 
}

Unistring *LibArtFTFont::style() { 
  return new Unistring
    (Unicode::toCORBA
     (Unicode::String(my_stylestr)));
}

void LibArtFTFont::setup_face(FT_Face &f) {
  famStyle spec(my_fam,my_style);
  if (facemap.find(spec) != facemap.end()) {
    // found cached face
    f = facemap[spec];
  } else {
    f = face;
  }
}

void LibArtFTFont::setup_size(FT_Face &f) {
  FT_Set_Char_Size
    ( f,                // handle to face object           
      my_size << 6,     // char_width in 1/64th of points  
      my_size << 6,     // char_height in 1/64th of points 
      xdpi,             // horizontal device resolution    
      ydpi );           // vertical device resolution      
}

bool LibArtFTFont::load_glyph(Unichar c, FT_Face &f) {
  int glyph_index = FT_Get_Char_Index
    (f,                // handle to face
     (unsigned char)c,       // the char code (truncated!) 
     1);                     // hinting   
  if (FT_Load_Glyph
      ( f,          // handle to face object 
	glyph_index,   // glyph index           
	load_flags ))  // load flags, see below 
    return false;
  return true;
}
  
static bool render_glyph(ArtPixBuf **pb, 
			 FT_GlyphSlot &glyph,
			 double &pixwidth) {

#define MAX_BUFFER  300000
  static char   bit_buffer[ MAX_BUFFER ];
  
  // first, render the glyph into an intermediate buffer
  FT_Bitmap  bit;
  
  int pixwidth = 4;
  int left  = FLOOR( glyph->metrics.horiBearingX );
  int right = CEIL( glyph->metrics.horiBearingX + glyph->metrics.width );
  int width = TRUNC(right - left);
  int top    = CEIL( glyph->metrics.horiBearingY );
  int bottom = FLOOR( glyph->metrics.horiBearingY - glyph->metrics.height );
  int height = TRUNC( top - bottom );
  
  if ( glyph->format != 
       ft_glyph_format_outline ) return false;
  int pitch  = (width+3) & -4;
  int size   = pitch*height;             
  if (size > MAX_BUFFER) return false;
  bit.width      = width;
  bit.rows       = height;
  bit.pitch      = pitch;
  bit.pixel_mode = ft_pixel_mode_grays;
  bit.buffer     = bit_buffer;      
  FT_Outline_Translate
    (&glyph->outline, -left, -bottom );
  memset( bit_buffer, 0, size );      
  if (FT_Outline_Get_Bitmap
      ( library, &glyph->outline, &bit)) return false;

  // now build a pixbuf
  unsigned char *pixels = 
    new unsigned char[size * pixwidth];
  memset(pixels,0,size * pixwidth);
  *pb = art_pixbuf_new_const_rgba
    (pixels, 
     width, 
     height, 
     width * pixwidth);  
  
  // copy alpha values
  for (int row = 0; row < height; ++row) 
    for (int col = 0; col < width; ++col)
      *(((pixels + (row * width) + col) * pixwidth) + 3) = 
	*(bit + (row * pitch) + col);

  pixwidth = width;  
  return true;
}



void LibArtFTFont::segments
(const Unistring u,
 vector< pair<double,ArtPixBuf *> > &segs) {
  
  FT_Face newface;
  setup_face(newface);
  setup_size(newface);

  unsigned int len = u.length();
  faceSpec fspec(my_size,spec);
  
  for (unsigned int i = 0; i < len; ++i) {
    cacheSpec cspec(u[i],fspec)
    cacheiter ci = cache.find(cspec);
    if (ci == cache.end()) {
      if (!load_glyph(u[i])) continue;
      ArtPixBuf *pb;
      double width;
      if (!render_glyph(&pb,newface->glyph,width)) continue;      
      cache.insert(pair(cspec,pb));
    }
    segs.push_back(pair<double,ArtPixBuf *>(width,cache[ch]));
  }
}
    
      
void LibArtFTFont::allocateText
(const Unistring &u, 
 Graphic::Requisition &r)
{    
  int width = 0;
  int height = 0;
  FT_Face newface;
  setup_face(newface);
  setup_size(newface);
  
  unsigned int len = u.length();
  faceSpec fspec(my_size,spec);
  
  for (unsigned int i = 0; i < len; ++i) {
    cacheSpec cspec(u[i],fspec)
    cacheiter ci = cache.find(cspec);
    if (!load_glyph(u[i])) continue;       
    int left  = FLOOR( glyph->metrics.horiBearingX );
    int right = CEIL( glyph->metrics.horiBearingX + glyph->metrics.width );
    width += TRUNC(right - left);
    int top    = CEIL( glyph->metrics.horiBearingY );
    int bottom = FLOOR( glyph->metrics.horiBearingY - glyph->metrics.height );
    height = MAX(height,TRUNC( top - bottom ));
  }
  r.x.natural = r.x.minimum = r.x.maximum = width*10.;
  r.x.defined = true;
  r.x.align = 0.;
  r.y.natural = r.y.minimum = r.y.maximum = height*10.;
  r.y.defined = true;
  r.y.align = 0.;
}


