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
#ifndef _LibArtFTFont_hh
#define _LibArtFTFont_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Graphic.hh>
#include <Berlin/GGI.hh>
#include <Prague/Sys/MMap.hh>
#include <Drawing/libArt/LibArtFont.hh>
#include <freetype/freetype.h>
#include <Warsaw/Unicode.hh>
#include <map>

class LibArtFTFont : public LibArtFont
//. this is a simple Freetype font, which doesn't support
//. ligatures or complex layout features
{
public:
  LibArtFTFont(GGI::Drawable *drawable);
  virtual ~LibArtFTFont();
  virtual unsigned long size();
  virtual void size(unsigned long);
  virtual unsigned long weight();
  virtual void weight(unsigned long);
  virtual void family(const Unistring &);
  virtual void subfamily(const Unistring &);
  virtual void fullname(const Unistring &);
  virtual void style(const Unistring &);
  virtual Unistring *family();
  virtual Unistring *subfamily();
  virtual Unistring *fullname();
  virtual Unistring *style();
  virtual DrawingKit::FontMetrics metrics();
  virtual DrawingKit::GlyphMetrics metrics(Unichar &);
  virtual void getPixBuf(const Unichar ch, ArtPixBuf &);
//   void getGlyphMetrics(const Unichar ch, FT_Glyph_Metrics &);
//   void getFontMetrics(FT_Size_Metrics &);
  virtual void allocateChar(Unichar ch, Graphic::Requisition &);

protected:
  
  typedef unsigned int atom;
  
  class atomizer {
  protected:
    atom currAtom;
    map<Unicode::String,atom> atomMap;
  public:
    atom atomize(Unicode::String &u) {
      map<Unicode::String,atom>::iterator i;
      i = atomMap.find(u);
      if (i == atomMap.end()) {	
	atomMap[u] = ++currAtom;
	return currAtom;
      } else {
	return i->second;
      }
    }
  };
  
  atomizer _a;
  atom atomize(Unicode::String &u) {return _a.atomize(u);}
  void setup_face(FT_Face &f);
  void setup_size(FT_Face &f);
  bool load_glyph(Unichar c, FT_Face &f);
    
  double xres, yres, xdpi, ydpi;  
  typedef pair<atom,atom> FamStyle;
  typedef unsigned int PtSize;
  typedef pair<PtSize,FamStyle> FaceSpec;
  typedef pair<Unichar,FaceSpec> CacheSpec;
  typedef map<CacheSpec,ArtPixBuf *>::iterator CacheIter;
  
  map<CacheSpec,ArtPixBuf *> myCache;
  map<FamStyle,FT_Face> myFaceMap;

  atom myFam, myStyle;
  Unicode::String myFamStr, myStyleStr;
  PtSize mySize;
  FT_Library myLibrary;
  FT_Face myFace;
private:
  bool chooseFaceInteractively(const map<FamStyle,FT_Face> &, const char *, Unicode::String &, Unicode::String &);
};

#endif
