/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Graydon Hoare <graydon@fresco.org> 
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

#include <Prague/Sys/Directory.hh>
#include <Prague/Sys/Path.hh>
#include <Berlin/Logger.hh>
#include <Berlin/RCManager.hh>
#include "FTFont.hh"
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include <freetype/ftglyph.h>

// #define FLOOR(x)  ((x) & -64)
// #define CEIL(x)   (((x)+63) & -64)
// #define TRUNC(x)  ((x) >> 6)
// #define MAX(X,Y) (X>Y?X:Y)
// #define MIN(X,Y) (X<Y?X:Y)

using namespace Prague;
using namespace Fresco;
using namespace Berlin::DrawingKit::libArt;

bool FTFont::chooseFaceInteractively(const std::map<FamStyle,FT_Face> &faces,
                       const char *env, 
                       Babylon::String &fam,
                       Babylon::String &style)
{
  int idx = -1;
  if (env[0] == '\0')
    {
      std::cout << "list of available fonts :\n";
      unsigned int i = 0;
      for (std::map<FamStyle,FT_Face>::const_iterator j = faces.begin(); j != faces.end(); ++i, ++j)
    {
      std::cout << i << ' ' << (*j).second->family_name << ' ' << (*j).second->style_name << std::endl;
    }
      std::cout << "please choose a number :"; std::cin >> idx;
    }
  else idx = atoi(env);
  std::map<FamStyle,FT_Face>::const_iterator j = faces.begin();
  for (int i = 0; i != idx && j != faces.end(); ++i, ++j);
  if (j == faces.end()) return false;
  fam = Babylon::String((*j).second->family_name);
  style = Babylon::String((*j).second->style_name);
  return true;
}

FTFont::FTFont(double xres, double yres)
  : //   xdpi(drawable->dpi(xaxis)),
    //   ydpi(drawable->dpi(yaxis)),
  _xdpi(96.),
  _ydpi(96.),
  _xres(xres),
  _yres(yres),
  _size(14),
  _scale(1),
  _glyphCache(GlyphFactory(this, &_library), 256),
  _faceMetricsCache(FaceMetricsFactory(this, &_library), 64),
  _glyphMetricsCache(GlyphMetricsFactory(this, &_library), 256)
{

  _matrix.xx = 0x10000;
  _matrix.xy = 0x00000;
  _matrix.yx = 0x00000;
  _matrix.yy = 0x10000;

  if (FT_Init_FreeType(&_library))
    {
      std::cerr << "failed to open freetype library" << std::endl;
      exit(-1);    
    }
  Prague::Path path = RCManager::get_path("fontpath");
  for (Prague::Path::iterator i = path.begin(); i != path.end(); ++i)
    {
      Directory directory(*i, Directory::alpha);
      Logger::log(Logger::text) << "libArt::FTFont: scanning font dir " << *i << std::endl;
      for (Directory::iterator j = directory.begin(); j != directory.end(); ++j)
    {
      if ((*j)->name() == "." || (*j)->name() == "..") continue;      
      std::string file = (*j)->long_name();
      if (FT_New_Face(_library, file.c_str(), 0, &_face))
        {
          Logger::log(Logger::text) << "libArt::FTFont: can't open font " << file << std::endl;
          continue;
        }
      _familyStr = Babylon::String(_face->family_name);
      _styleStr = Babylon::String(_face->style_name);
      _family = atomize(_familyStr);
      _style = atomize(_styleStr);
      Logger::log(Logger::text) << "found FT-readable font "
                    << _face->family_name << " (" << _family << ") " << _face->style_name << " (" << _style << ") in "
                    << *i << std::endl;
      _faces[FamStyle(_family, _style)] = _face;
    }
    }
  Logger::log(Logger::text) << "completed scaning font directories" << std::endl;
  Logger::log(Logger::text) << _faces.size() << " fonts found" << std::endl;
  if (!_faces.size())
     throw std::runtime_error("no fonts found. Please check your font path !");
  char *env = getenv("BERLIN_FONT_CHOOSER");
  Babylon::String tmpFam, tmpStyle;
  if (env && chooseFaceInteractively(_faces, env, tmpFam, tmpStyle))
    {
      _familyStr = tmpFam;
      _family = atomize(_familyStr);
      _styleStr = tmpStyle;
      _style = atomize(_styleStr);
    }
}


FTFont::~FTFont() {}
CORBA::ULong FTFont::size() { return _size;}
CORBA::ULong FTFont::weight() { return 100;}
void FTFont::size(CORBA::ULong sz) { _size = sz;}
void FTFont::weight(CORBA::ULong wt) {}

Unistring *FTFont::family()
{ 
  return new Unistring (Unicode::to_CORBA(_familyStr));
}

Unistring *FTFont::subfamily() { return 0;}
void FTFont::subfamily(const Unistring &fname) {}
void FTFont::fullname(const Unistring &fname) {}

void FTFont::family(const Unistring &fname)
{ 
  _familyStr = Unicode::to_internal(fname);
  _family = atomize(_familyStr);
}

void FTFont::style(const Unistring &sname)
{ 
  _styleStr = Unicode::to_internal(sname);
  _style = atomize(_styleStr);
}

Unistring *FTFont::fullname()
{ 
  Babylon::String str = _familyStr;
  str += Babylon::Char(' ');
  str += _styleStr;
  return new Unistring(Unicode::to_CORBA(str));
}

Unistring *FTFont::style() 
{ 
  return new Unistring (Unicode::to_CORBA(Babylon::String(_styleStr)));
}

Fresco::DrawingKit::FontMetrics FTFont::metrics()
{
  Fresco::DrawingKit::FontMetrics fm;
  FaceSpec key(_size, FamStyle(_family, _style));
  _faceMetricsCache.get(key, fm);
  return fm;
}


Fresco::DrawingKit::GlyphMetrics FTFont::metrics(Unichar &uc)
{
  Fresco::DrawingKit::GlyphMetrics gm;
  TGlyphSpec key(_matrix, GlyphSpec(uc, FaceSpec(_size, FamStyle(_family, _style))));
  _glyphMetricsCache.get(key, gm);
  return gm;
}

void FTFont::buffer(Unichar ch, ArtPixBuf *&pb)
{
  TGlyphSpec key(_matrix, GlyphSpec(ch, FaceSpec(((PtSize)(_size * _scale)), FamStyle(_family, _style))));
  _glyphCache.get(key, pb);
}


void FTFont::setup_face(FT_Face &f)
{
  FamStyle spec(_family, _style);
  if (_faces.find(spec) != _faces.end()) f = _faces[spec];
  else f = _face;
}

void FTFont::setup_size(FT_Face &f)
{
  FT_Set_Char_Size
    ( f,                // handle to face object           
      ((PtSize)(_size * _scale * 64)),     // char_width in 1/64th of points  
      ((PtSize)(_size * _scale * 64)),     // char_height in 1/64th of points 
      (unsigned int)0,   // horizontal device resolution    
      (unsigned int)0 ); // vertical device resolution      

//       (unsigned int)xdpi,   // horizontal device resolution    
//       (unsigned int)ydpi ); // vertical device resolution      
}

bool FTFont::load_glyph(Unichar c, FT_Face &f)
{
  FT_CharMap  found = 0;
  FT_CharMap  charmap;  
  for (int n = 0; n < f->num_charmaps; n++)
    {
      charmap = f->charmaps[n];
      if (charmap->encoding == ft_encoding_unicode)
    {    
      found = charmap;
      break;
    }
    }
  if (!found)
    { 
      //     no way of translating!
      return false; 
    }
  /* now, select the charmap for the face object */
  if (FT_Set_Charmap( f, found)) return false;
  int idx = FT_Get_Char_Index(f, (unsigned char)c);
  if (FT_Load_Glyph (f,idx,0))
    return false;
  return true;
}

bool FTFont::transform(double trafo[4])
{
  _scale = trafo[0] * trafo[3] - trafo[1] * trafo[2];
  _matrix.xx = (FT_Fixed)(trafo[0] / _scale * 0x10000);
  _matrix.xy = (FT_Fixed)(trafo[1] / _scale * 0x10000);
  _matrix.yx = (FT_Fixed)(trafo[2] / _scale * 0x10000);
  _matrix.yy = (FT_Fixed)(trafo[3] / _scale * 0x10000);
  return true;
}

  
FTFont::atom FTFont::Atomizer::atomize(Babylon::String &u)
{
  std::map<Babylon::String, atom>::iterator i = _atoms.find(u);
  if (i == _atoms.end())
    {
      _atoms[u] = ++_atom;
      return _atom;
    }
  else return i->second;
}

void FTFont::allocate_char(Unichar ch, Graphic::Requisition &r)
{
  Fresco::DrawingKit::GlyphMetrics gm = metrics(ch);
  r.x.natural = r.x.minimum = r.x.maximum = gm.horiAdvance / (_xres * 64.0);
  r.x.defined = true;
  r.x.align = gm.width == 0 ? 0. : ((double)gm.horiBearingX)/((double)gm.horiAdvance);
  r.y.natural = r.y.minimum = r.y.maximum = gm.height / (_yres * 64.0);
  r.y.defined = true;
  r.y.align = gm.height == 0 ? 0. : ((double)gm.horiBearingY)/((double)gm.height); 
}


ArtPixBuf *FTFont::GlyphFactory::produce(const FTFont::TGlyphSpec &gs)
{
  FT_Face face;
  FT_Glyph glyph;
  _font->setup_face(face);
  _font->setup_size(face);  
  Unichar ch = gs.second.first;

  Fresco::DrawingKit::GlyphMetrics gm = _font->metrics(ch);
    
  // loads the TRUNCATED char index! note: only works on indicies < 256
  FT_Load_Char(face, (char)(ch), FT_LOAD_DEFAULT);
  FT_Get_Glyph(face->glyph, &glyph);
  FT_Matrix matrix = gs.first;
  FT_Glyph_Transform(glyph, &matrix, 0);
  FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0,  1);
  
  FT_BitmapGlyph bglyph = (FT_BitmapGlyph)glyph;
  int height = bglyph->bitmap.rows;
  int width = bglyph->bitmap.width;
  int pitch = bglyph->bitmap.pitch;

  art_u8 *pixels = new art_u8[width * height];

  if (width != pitch)
    for (int i = 0; i < height; ++i)
      memcpy(pixels + (width * i), (bglyph->bitmap.buffer) + (pitch * i), width);
  else
    memcpy(pixels, bglyph->bitmap.buffer, (width*height));

  // this is a lie -- we're going to use it as a greymap
  ArtPixBuf *pb = art_pixbuf_new_rgb (pixels, width, height, width);  
  FT_Done_Glyph(glyph);
  return pb;
}


Fresco::DrawingKit::FontMetrics
FTFont::FaceMetricsFactory::produce(const FTFont::FaceSpec &cs) 
{
  Fresco::DrawingKit::FontMetrics fm;
  FT_Face newface;
  _font->setup_face(newface);
  _font->setup_size(newface);
  fm.ascender = newface->size->metrics.ascender;
  fm.descender = newface->size->metrics.descender;
  fm.height = newface->size->metrics.height;
  fm.max_advance = newface->size->metrics.max_advance;
  return fm;
}


Fresco::DrawingKit::GlyphMetrics
FTFont::GlyphMetricsFactory::produce(const FTFont::TGlyphSpec &cs) 
{
  double scale = _font->get_scale();
  Fresco::DrawingKit::GlyphMetrics gm;
  FT_Face face;
  _font->setup_face(face);
  _font->setup_size(face);
  Unichar ch = cs.second.first;
  if (!_font->load_glyph(ch, face)) return gm;
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
