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
#ifndef _FTFont_hh
#define _FTFont_hh

#include <Prague/Sys/MMap.hh>
#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/Unicode.hh>
#include <Berlin/LRUCache.hh>
#include "Font.hh"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>

namespace Berlin {
namespace DrawingKit {
namespace libArt {

//. this is a simple Freetype font, which doesn't support
//. ligatures or complex layout features
class FTFont : public Font
{
public:
  FTFont(double, double);
  virtual ~FTFont();
  virtual CORBA::ULong size();
  virtual void size(CORBA::ULong);
  virtual CORBA::ULong weight();
  virtual void weight(CORBA::ULong);
  virtual void family(const Fresco::Unistring &);
  virtual void subfamily(const Fresco::Unistring &);
  virtual void fullname(const Fresco::Unistring &);
  virtual void style(const Fresco::Unistring &);
  virtual Fresco::Unistring *family();
  virtual Fresco::Unistring *subfamily();
  virtual Fresco::Unistring *fullname();
  virtual Fresco::Unistring *style();
  virtual Fresco::DrawingKit::FontMetrics metrics();
  virtual Fresco::DrawingKit::GlyphMetrics metrics(Fresco::Unichar &);
  virtual void buffer(Fresco::Unichar, ArtPixBuf *&);
  virtual bool transform(double trafo[4]);
  virtual void allocate_char(Fresco::Unichar, Fresco::Graphic::Requisition &);

  void setup_face(FT_Face &f);
  void setup_size(FT_Face &f);
  bool load_glyph(Fresco::Unichar c, FT_Face &f);
  void matrix(FT_Matrix &m) {m = _matrix;}

  double get_scale() const { return _scale;} 
  
protected:

  typedef unsigned int atom;  
  class Atomizer
  {
  protected:
    atom _atom;
    std::map<Babylon::String, atom> _atoms;
  public:
    atom atomize(Babylon::String &);
  };
  Atomizer _a;
  atom atomize(Babylon::String &u) {return _a.atomize(u);}
    
  double _xres, _yres, _xdpi, _ydpi;  
  typedef unsigned int PtSize;
  FT_Matrix _matrix;
  typedef std::pair<atom,atom> FamStyle;
  typedef std::pair<PtSize,FamStyle> FaceSpec;
  typedef std::pair<Fresco::Unichar,FaceSpec>  GlyphSpec;
  typedef std::pair<FT_Matrix, GlyphSpec>  TGlyphSpec;

  class TGlyphSpec_cmp
  {
  public:
    bool operator ()(const TGlyphSpec &a, const TGlyphSpec &b)
    {
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

  class GlyphMetricsFactory
  {
  private:
    FTFont *_font;
    FT_Library   *_lib;
  public:
    GlyphMetricsFactory(FTFont *f, FT_Library *l) : _font(f), _lib(l) {}
    Fresco::DrawingKit::GlyphMetrics produce(const TGlyphSpec &);
    void recycle(Fresco::DrawingKit::GlyphMetrics) {};
  };
  
  class FaceMetricsFactory
  {
  private:
    FTFont     *_font;
    FT_Library *_lib;
  public:
    FaceMetricsFactory(FTFont *f, FT_Library *l) : _font(f), _lib(l) {}
    Fresco::DrawingKit::FontMetrics produce(const FaceSpec &);
    void recycle(Fresco::DrawingKit::FontMetrics) {};
  };

  class GlyphFactory
  {
  private:
    FTFont     *_font;
    FT_Library *_lib;
  public:
    GlyphFactory(FTFont *f, FT_Library *l) : _font(f), _lib(l) {};
    ArtPixBuf *produce(const TGlyphSpec &);
    void recycle(ArtPixBuf *pb) { art_pixbuf_free(pb);};
  };
  
  atom                        _family;
  atom                        _style;
  Babylon::String             _familyStr;
  Babylon::String             _styleStr;
  PtSize                      _size; 
  double                      _scale;
  FT_Library                  _library;
  FT_Face                     _face;
  std::map<FamStyle, FT_Face> _faces;

  // caches!
  LRUCache<TGlyphSpec,ArtPixBuf *, GlyphFactory, 
	   std::map<TGlyphSpec,ArtPixBuf *,TGlyphSpec_cmp> > _glyphCache;
  LRUCache<FaceSpec, Fresco::DrawingKit::FontMetrics, FaceMetricsFactory> _faceMetricsCache;
  LRUCache<TGlyphSpec, Fresco::DrawingKit::GlyphMetrics, GlyphMetricsFactory,
	   std::map<TGlyphSpec, Fresco::DrawingKit::GlyphMetrics,TGlyphSpec_cmp> > _glyphMetricsCache;
private:
  bool chooseFaceInteractively(const std::map<FamStyle, FT_Face> &, const char *, Babylon::String &, Babylon::String &);
};

} // namespace
} // namespace
} // namespace

#endif
