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
#ifndef _Unifont_hh
#define _Unifont_hh

#include <Prague/Sys/MMap.hh>
#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/Unicode.hh>
#include "Font.hh"
#include <map>

namespace libArt
{
//. This is a default font, just in case -- a character cell bitmapped unicode
//. font which is generated "on the fly" from the GNU unifont, which we're
//. storing in a packed binary array we mmap() in. this is so that, even if all
//. the font manufactureres in the world turn against us, we can still render
//. multilingual text, albeit not quite as well as certain (ahem) proprietary
//. text systems
class Unifont : public Font
{
public:
  Unifont(double, double) throw(std::runtime_error);
  virtual ~Unifont();
  virtual CORBA::ULong size();
  virtual void size(CORBA::ULong) {}
  virtual CORBA::ULong weight();
  virtual void weight(CORBA::ULong) {}
  virtual Fresco::Unistring *family();
  virtual Fresco::Unistring *subfamily();
  virtual Fresco::Unistring *fullname();
  virtual Fresco::Unistring *style();
  virtual Fresco::DrawingKit::FontMetrics metrics();
  virtual Fresco::DrawingKit::GlyphMetrics metrics(Fresco::Unichar &);
  virtual void allocate_char(const Fresco::Unichar, Fresco::Graphic::Requisition &);
  virtual void buffer(Fresco::Unichar, ArtPixBuf *&);
private:
  void glyph_to_pixels(Fresco::Unichar, unsigned char *);
  double        _xres;
  double        _yres;  
  unsigned char _slab[16*16];
  ArtPixBuf    *_buffer;
//   map<Unichar,ArtPixBuf *> cache;
  Prague::MMap *_glyphmap;
};

}

#endif
