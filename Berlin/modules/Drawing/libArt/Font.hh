/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Font_hh
#define _Font_hh

#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Fresco/DrawingKit.hh>
#include <string>
#include <vector>
#include <libart_lgpl/art_misc.h>
#include <libart_lgpl/art_pixbuf.h>

namespace Berlin {
namespace DrawingKit {
namespace libArt {

class Font
{
public:
  Font() {}
  virtual ~Font() {}
  virtual CORBA::ULong size() = 0;
  virtual void size(CORBA::ULong) = 0;
  virtual CORBA::ULong weight() = 0;
  virtual void weight(CORBA::ULong) = 0;
  virtual Fresco::Unistring *family() = 0;
  virtual Fresco::Unistring *subfamily() = 0;
  virtual Fresco::Unistring *fullname() = 0;
  virtual Fresco::Unistring *style() = 0;
  virtual Fresco::DrawingKit::FontMetrics metrics() = 0;
  virtual Fresco::DrawingKit::GlyphMetrics metrics(Fresco::Unichar &) = 0;
  // this method returns true if the font will handle the trafo internally,
  // false otherwise
  virtual bool transform(double trafo[4]) { return false; };
  virtual void allocate_char(Fresco::Unichar ch, Fresco::Graphic::Requisition &) = 0;
  virtual void buffer(Fresco::Unichar ch, ArtPixBuf *&) = 0;
};

} // namespace
} // namespace
} // namespace

#endif

