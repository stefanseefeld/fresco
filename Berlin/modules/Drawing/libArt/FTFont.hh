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
#include <Berlin/LRUCache.hh>
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
  virtual void getPixBuf(const Unichar ch, ArtPixBuf *&);
  virtual bool transform(double trafo[4]);
  virtual void allocateChar(Unichar ch, Graphic::Requisition &);

  void setup_face(FT_Face &f);
  void setup_size(FT_Face &f);
  bool load_glyph(Unichar c, FT_Face &f);
  void matrix(FT_Matrix &m) {m = matrix_;}
  
protected:
  
  typedef unsigned int atom;  
  class Atomizer {
  protected:
    atom currAtom;
    map<Unicode::String,atom> atomMap;
  public:
    atom atomize(Unicode::String &u);
  };  
  Atomizer _a;
  atom atomize(Unicode::String &u) {return _a.atomize(u);}
    
  double xres, yres, xdpi, ydpi;  
  typedef unsigned int PtSize;
  FT_Matrix matrix_;
  typedef pair<atom,atom> FamStyle;
  typedef pair<PtSize,FamStyle> FaceSpec;
  typedef pair<Unichar,FaceSpec>  GlyphSpec;
  typedef pair<FT_Matrix, GlyphSpec>  TGlyphSpec;

  class TGlyphSpec_cmp {
  public:
    bool operator ()(const TGlyphSpec &a, const TGlyphSpec &b) {
      return 
	// this is why a generalized product type constructor is better than
	// ad-hoc memory structure definition. *sigh*
	((a.first.xx < b.first.xx)) ||
	((a.first.xx == b.first.xx) && (a.first.xy < b.first.xy)) ||
	((a.first.xx == b.first.xx) && (a.first.xy == b.first.xy) && (a.first.yx < b.first.yx)) ||
	((a.first.xx == b.first.xx) && (a.first.xy == b.first.xy) && (a.first.yx == b.first.yx) && (a.first.yy < b.first.yy)) ||
	((a.first.xx == b.first.xx) && (a.first.xy == b.first.xy) && (a.first.yx == b.first.yx) && (a.first.yy == b.first.yy) &&
	 (a.second < b.second))
	;      
    }
  };

  class GlyphMetricsFactory {
  private:
    LibArtFTFont *font_;
    FT_Library *lib_;
  public:
    GlyphMetricsFactory(LibArtFTFont *f, FT_Library *l) : font_(f), lib_(l) {}
    DrawingKit::GlyphMetrics produce(const GlyphSpec &cs);
    void recycle(DrawingKit::GlyphMetrics) {};
  };
 
  class FaceMetricsFactory {
  private:
    LibArtFTFont *font_;
    FT_Library *lib_;
  public:
    FaceMetricsFactory(LibArtFTFont *f, FT_Library *l) : font_(f), lib_(l) {}
    DrawingKit::FontMetrics produce(const FaceSpec &fs);
    void recycle(DrawingKit::FontMetrics) {};
  };

  class GlyphFactory {
  private:
    LibArtFTFont *font_;
    FT_Library *lib_;
  public:
    GlyphFactory(LibArtFTFont *f, FT_Library *l) : font_(f), lib_(l) {};
    ArtPixBuf *produce(const TGlyphSpec &cs);
    void recycle(ArtPixBuf *pb) {art_pixbuf_free(pb);};
  };
   
  atom myFam, myStyle;
  Unicode::String myFamStr, myStyleStr;
  PtSize mySize;
  FT_Library myLibrary;
  FT_Face myFace;
  map<FamStyle,FT_Face> myFaceMap;

  // caches!
  LRUCache<TGlyphSpec,ArtPixBuf *, GlyphFactory, map<TGlyphSpec,ArtPixBuf *,TGlyphSpec_cmp> > myGlyphCache;
  LRUCache<FaceSpec,DrawingKit::FontMetrics, FaceMetricsFactory> myFaceMetricsCache;
  LRUCache<GlyphSpec,DrawingKit::GlyphMetrics, GlyphMetricsFactory> myGlyphMetricsCache;   

private:
  bool chooseFaceInteractively(const map<FamStyle,FT_Face> &, const char *, Unicode::String &, Unicode::String &);
};

#endif
