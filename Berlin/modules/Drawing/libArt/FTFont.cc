
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
#include <cstdlib>
#include <freetype/ftglyph.h>

#define FLOOR(x)  ((x) & -64)
#define CEIL(x)   (((x)+63) & -64)
#define TRUNC(x)  ((x) >> 6)
#define MAX(X,Y) (X>Y?X:Y)
#define MIN(X,Y) (X<Y?X:Y)

using namespace Prague;

bool LibArtFTFont::chooseFaceInteractively(const map<FamStyle,FT_Face> &faces, const char *env, 
					   Unicode::String &fam, Unicode::String &style)
{
  int idx = -1;
  if (env[0] == '\0')
    {
      cout << "list of available fonts :\n";
      unsigned int i = 0;
      for (map<FamStyle,FT_Face>::const_iterator j = faces.begin(); j != faces.end(); ++i, ++j)
	{
	  cout << i << ' ' << (*j).second->family_name << ' ' << (*j).second->style_name << endl;
	}
      cout << "please choose a number :"; cin >> idx;
    }
  else idx = atoi(env);
  map<FamStyle,FT_Face>::const_iterator j = faces.begin();
  for (unsigned int i = 0; i != idx && j != faces.end(); ++i, ++j);
  if (j == faces.end()) return false;
  fam = Unicode::String((*j).second->family_name);
  style = Unicode::String((*j).second->style_name);
  return true;
}

LibArtFTFont::LibArtFTFont(Console::Drawable *drawable)
  : //   xdpi(drawable->dpi(xaxis)),
    //   ydpi(drawable->dpi(yaxis)),
  xdpi(96.),
  ydpi(96.),
  xres(drawable->resolution(xaxis)),
  yres(drawable->resolution(yaxis)),
  mySize(14),
  scale(1),
  myGlyphCache(GlyphFactory(this,&myLibrary),256),
  myFaceMetricsCache(FaceMetricsFactory(this,&myLibrary),64),
  myGlyphMetricsCache(GlyphMetricsFactory(this,&myLibrary),256)
{

  matrix_.xx = 0x10000;
  matrix_.xy = 0x00000;
  matrix_.yx = 0x00000;
  matrix_.yy = 0x10000;

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
  if (!fontdirlist)
    {
      Logger::log(Logger::text) << "cannot open " << fname << endl;
    }
  else
    {
      string fontdir;
      while (fontdirlist >> fontdir)
	{
	  Directory directory(fontdir, Directory::alpha);
	  Logger::log(Logger::text) << "LibArtFTFont: scanning font dir " << fontdir << endl;
	  for (Directory::iterator i = directory.begin(); i != directory.end(); i++)
	    {
	      if ((*i)->name() == "." || (*i)->name() == "..") continue;	  
	      string fontfile = (*i)->longName();
	      if (FT_New_Face(myLibrary, fontfile.c_str(), 0, &myFace))
		{
		  Logger::log(Logger::text) << "LibArtFTFont: can't open font " << fontfile << endl;
		  continue;
		}
	      myFamStr = Unicode::String(myFace->family_name);
	      myStyleStr = Unicode::String(myFace->style_name);
	      myFam = atomize(myFamStr);
	      myStyle = atomize(myStyleStr);
	      Logger::log(Logger::text) << "found FT-readable font "
					<< myFamStr << " (" << myFam << ") " << myStyleStr << " (" << myStyle << ") in "
					<< fontfile << endl;
	      myFaceMap[FamStyle(myFam,myStyle)] = myFace;
	    }
	}
      fontdirlist.close();
      Logger::log(Logger::text) << "completed scaning font directories" << endl;
      char *env = getenv("BERLIN_FONT_CHOOSER");
      Unicode::String tmpFam, tmpStyle;
      if (env && chooseFaceInteractively(myFaceMap, env, tmpFam, tmpStyle))
	{
	  myFamStr = tmpFam;
	  myFam = atomize(myFamStr);
	  myStyleStr = tmpStyle;
	  myStyle = atomize(myStyleStr);
	}
    }
}


LibArtFTFont::~LibArtFTFont() {}
unsigned long LibArtFTFont::size() { return mySize;}
unsigned long LibArtFTFont::weight() { return 100;}
void LibArtFTFont::size(unsigned long sz) { mySize = sz;}
void LibArtFTFont::weight(unsigned long wt) {}

Unistring *LibArtFTFont::family()
{ 
  return new Unistring (Unicode::toCORBA(Unicode::String(myFamStr)));
}

Unistring *LibArtFTFont::subfamily() { return 0;}
void LibArtFTFont::subfamily(const Unistring &fname) {}
void LibArtFTFont::fullname(const Unistring &fname) {}

void LibArtFTFont::family(const Unistring &fname)
{ 
  myFamStr = Unicode::toPrague(fname);
  myFam = atomize(myFamStr);
}

void LibArtFTFont::style(const Unistring &sname)
{ 
  myStyleStr = Unicode::toPrague(sname);
  myStyle = atomize(myStyleStr);
}

Unistring *LibArtFTFont::fullname()
{ 
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

DrawingKit::FontMetrics LibArtFTFont::metrics()
{
  DrawingKit::FontMetrics fm;
  FaceSpec key(mySize,FamStyle(myFam,myStyle));
  myFaceMetricsCache.get(key,fm);
  return fm;
}


DrawingKit::GlyphMetrics LibArtFTFont::metrics(Unichar &uc)
{
  DrawingKit::GlyphMetrics gm;
  TGlyphSpec key(matrix_, GlyphSpec(uc,FaceSpec(mySize,FamStyle(myFam,myStyle))));
  myGlyphMetricsCache.get(key,gm);
  return gm;
}

void LibArtFTFont::getPixBuf(const Unichar ch, ArtPixBuf *&pb) {
  TGlyphSpec key(matrix_, GlyphSpec(ch,FaceSpec(((PtSize)(mySize * scale)),FamStyle(myFam,myStyle))));
  myGlyphCache.get(key,pb);
}


void LibArtFTFont::setup_face(FT_Face &f)
{
  FamStyle spec(myFam,myStyle);
  if (myFaceMap.find(spec) != myFaceMap.end()) f = myFaceMap[spec];
  else f = myFace;
}

void LibArtFTFont::setup_size(FT_Face &f) {
  FT_Set_Char_Size
     ( f,                // handle to face object           
      ((PtSize)(mySize * scale * 64)),     // char_width in 1/64th of points  
      ((PtSize)(mySize * scale * 64)),     // char_height in 1/64th of points 
      (unsigned int)0,   // horizontal device resolution    
      (unsigned int)0 ); // vertical device resolution      

//       (unsigned int)xdpi,   // horizontal device resolution    
//       (unsigned int)ydpi ); // vertical device resolution      
}

 bool LibArtFTFont::load_glyph(Unichar c, FT_Face &f) {

   FT_CharMap  found = 0;
   FT_CharMap  charmap;  
   for (int n = 0; n < f->num_charmaps; n++ ){
       charmap = f->charmaps[n];
       if (charmap->encoding == ft_encoding_unicode) {	
 	found = charmap;
 	break;
       }
   }
   if (!found) { 
  //     no way of translating!
     return false; 
   }
   /* now, select the charmap for the face object */
   if (FT_Set_Charmap( f, found )) return false;
   int idx = FT_Get_Char_Index(f,(unsigned char)c);
   if (FT_Load_Glyph (f,idx,0)) {
     return false;
   }
   return true;
}

bool LibArtFTFont::transform(double trafo[4]) {
  scale = trafo[0] * trafo[3] - trafo[1] * trafo[2];
  matrix_.xx = (FT_Fixed)(trafo[0] / scale * 0x10000);
  matrix_.xy = (FT_Fixed)(trafo[1] / scale * 0x10000);
  matrix_.yx = (FT_Fixed)(trafo[2] / scale * 0x10000);
  matrix_.yy = (FT_Fixed)(trafo[3] / scale * 0x10000);
//   cerr << matrix_.xx << ' ' << matrix_.xy << ' ' << matrix_.yx << ' ' << matrix_.yy << endl;
  return true;
}

  
LibArtFTFont::atom LibArtFTFont::Atomizer::atomize(
Unicode::String &u) {
  map<Unicode::String,atom>::iterator i;
  i = atomMap.find(u);
  if (i == atomMap.end()) {	
    atomMap[u] = ++currAtom;
    return currAtom;
  } else {
    return i->second;
  }
}

void LibArtFTFont::allocateChar(Unichar ch, Graphic::Requisition &r) {
  DrawingKit::GlyphMetrics gm = metrics(ch);
  r.x.natural = r.x.minimum = r.x.maximum = gm.horiAdvance / (xres * 64.0);
  r.x.defined = true;
  r.x.align = (gm.width == 0) ? 0. : 
    ((double)gm.horiBearingX)/((double)gm.width); ;
  r.y.natural = r.y.minimum = r.y.maximum = gm.height / (yres * 64.0); 
  r.y.defined = true;
  r.y.align = (gm.height == 0) ? 0. : 
    ((double)gm.horiBearingY)/((double)gm.height); 
}


ArtPixBuf * 
LibArtFTFont::GlyphFactory::produce(const LibArtFTFont::TGlyphSpec &gs)
{

  FT_Face face;
  FT_Glyph glyph;
  font_->setup_face(face);
  font_->setup_size(face);  
  Unichar ch = gs.second.first;

  DrawingKit::GlyphMetrics gm = font_->metrics(ch);
    
  // loads the TRUNCATED char index! note: only works on indicies < 256
  FT_Load_Char( face, (char)(ch), FT_LOAD_DEFAULT );
  FT_Get_Glyph( face->glyph, &glyph );
  FT_Matrix matrix = gs.first;
  FT_Glyph_Transform( glyph, &matrix, 0 );
  FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0,  1 );
  
  FT_BitmapGlyph bglyph = (FT_BitmapGlyph)glyph;
  int height = bglyph->bitmap.rows;
  int width = bglyph->bitmap.width;
  int pitch = bglyph->bitmap.pitch;

  art_u8 *pixels = new art_u8[width * height]; 

  if (width != pitch) {
    for (int i = 0; i < height; ++i)
      memcpy(pixels + (width * i), (bglyph->bitmap.buffer) + (pitch * i), width);
  } else {
    memcpy(pixels, bglyph->bitmap.buffer, (width*height));
  }

  // this is a lie -- we're going to use it as a greymap
  ArtPixBuf *pb = art_pixbuf_new_rgb (pixels, width, height, width);  
  FT_Done_Glyph(glyph);
  return pb;
}


DrawingKit::FontMetrics 
LibArtFTFont::FaceMetricsFactory::produce(const LibArtFTFont::FaceSpec &cs) 
{
  DrawingKit::FontMetrics fm;
  FT_Face newface;
  font_->setup_face(newface);
  font_->setup_size(newface);
  fm.ascender = newface->size->metrics.ascender;
  fm.descender = newface->size->metrics.descender;
  fm.height = newface->size->metrics.height;
  fm.max_advance = newface->size->metrics.max_advance;
  return fm;
}


DrawingKit::GlyphMetrics 
LibArtFTFont::GlyphMetricsFactory::produce(const LibArtFTFont::TGlyphSpec &cs) 
{
  double scale = font_->getScale();
  DrawingKit::GlyphMetrics gm;
  FT_Face face;
  font_->setup_face(face);
  font_->setup_size(face);
  Unichar ch = cs.second.first;
  if (!font_->load_glyph(ch, face)) return gm;
  FT_GlyphSlot glyph = face->glyph;
  gm.width = static_cast<CORBA::Long>(glyph->metrics.width / scale);
  gm.height = static_cast<CORBA::Long>(glyph->metrics.height / scale);
  gm.horiBearingX = static_cast<CORBA::Long>(glyph->metrics.horiBearingX / scale);
  gm.horiBearingY = static_cast<CORBA::Long>(glyph->metrics.horiBearingY / scale);
  gm.horiAdvance =  static_cast<CORBA::Long>(glyph->metrics.horiAdvance / scale);
  gm.vertBearingX = static_cast<CORBA::Long>(glyph->metrics.vertBearingX / scale);
  gm.vertBearingY = static_cast<CORBA::Long>(glyph->metrics.vertBearingY / scale);
  gm.vertAdvance = static_cast<CORBA::Long>(glyph->metrics.vertAdvance / scale);
  return gm;
}

