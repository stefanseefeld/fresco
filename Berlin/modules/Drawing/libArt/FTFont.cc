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

using namespace Prague;

LibArtFTFont::LibArtFTFont(GGI::Drawable *drawable) :
  xdpi(drawable->dpi(xaxis)),
  ydpi(drawable->dpi(yaxis)),
  mySize(18)
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
  //cerr << "setting up face" << endl;
  FamStyle spec(myFam,myStyle);
  if (myFaceMap.find(spec) != myFaceMap.end()) {
    // found cached face
    f = myFaceMap[spec];
  } else {
    f = myFace;
  }
}

void LibArtFTFont::setup_size(FT_Face &f) {
  FT_Set_Pixel_Sizes(f,24,24);
//   FT_Set_Char_Size
//     ( f,                // handle to face object           
//       mySize << 6,     // char_width in 1/64th of points  
//       mySize << 6,     // char_height in 1/64th of points 
//       (unsigned int)xdpi,             // horizontal device resolution    
//       (unsigned int)ydpi );           // vertical device resolution      
//   //cerr << "dpi: " << xdpi << " " << xdpi << endl;
}

bool LibArtFTFont::load_glyph(Unichar c, FT_Face &f) {
  int glyph_index = FT_Get_Char_Index
    (f,                // handle to face
     (unsigned char)c       // the char code (truncated!) 
     );                     
  if (FT_Load_Glyph (       
		     f,          // handle to face object 
		     glyph_index,   // glyph index           
		     0 ))  // default load flags 
    {
      return false;
    }
  return true;
}
  
static bool render_glyph(ArtPixBuf **pb, 
			 FT_GlyphSlot &glyph,
			 FT_Library &library) {

  //cerr << "rendering glyph" << endl;

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
      *(pixels + (((row * width) + col) * pixwidth) + 3) = 
	*(bit_buffer + (row * pitch) + col);
  return true;
}



void LibArtFTFont::segments
(const Unistring u,
 vector< pair<double,ArtPixBuf *> > &segs) {
  
  FT_Face newface;
  setup_face(newface);
  setup_size(newface);

  unsigned int len = u.length();
  //cerr << "rasterizing " << len << " glyphs " << endl;
  FaceSpec fspec(mySize,FamStyle(myFam,myStyle));
  
  for (unsigned int i = 0; i < len; ++i) {
    Unichar c = u[i];
    CacheSpec cspec(c,fspec);
    CacheIter ci = myCache.find(cspec);
    if (ci == myCache.end()) {
      //cerr << "loading glyph " << c << endl;
      if (!load_glyph(c,newface)) continue;
      //cerr << "loaded " << c << " OK " << endl;
      ArtPixBuf *pb;
      //cerr << "rendering glyph " << c << endl;
      if (!render_glyph(&pb,newface->glyph,myLibrary)) continue;      
      //cerr << "rendered " << c << " OK " << endl;
      myCache.insert(pair<CacheSpec,ArtPixBuf *>(cspec,pb));
    } else {
      //cerr << "cache hit on " << c << myFamStr << " " << myStyleStr << endl;
    }
    ArtPixBuf *pb = myCache[cspec];
    segs.push_back(pair<double,ArtPixBuf *>(pb->width,pb));
  }
}
    
      
void LibArtFTFont::allocateText
(const Unistring &u, 
 Graphic::Requisition &r)
{    
  int width = 0;
  int height = 0;
  FT_Face newface;
  FT_GlyphSlot glyph = newface->glyph;
  setup_face(newface);
  setup_size(newface);
  
  unsigned int len = u.length();
  //cerr << "measuring " << len << " unichars" << endl;
  FaceSpec fspec(mySize,FamStyle(myFam,myStyle));
  
  for (unsigned int i = 0; i < len; ++i) {
    CacheSpec cspec(u[i],fspec);
    CacheIter ci = myCache.find(cspec);
    if (!load_glyph(u[i],newface)) continue;       
    //cerr << i << endl;
    int left  = FLOOR(glyph->metrics.horiBearingX );
    int right = CEIL(glyph->metrics.horiBearingX + glyph->metrics.width );
    width += TRUNC(right - left);
    int top    = CEIL(glyph->metrics.horiBearingY );
    int bottom = FLOOR(glyph->metrics.horiBearingY - glyph->metrics.height );    
    height = MAX(height,TRUNC( top - bottom ));
    height = 2;
    //    //cerr << "glyph left " << left << " right " << right << " width " << width << " top " << top << " bottom " << bottom << " height " << height << endl;    
  }
  r.x.natural = r.x.minimum = r.x.maximum = len*24*10.;
  r.x.defined = true;
  r.x.align = 0.;
  r.y.natural = r.y.minimum = r.y.maximum = 24*10.;
  r.y.defined = true;
  r.y.align = 0.;
  //cerr << "allocated " << r.x.minimum << "x" << r.y.minimum << endl;
}


