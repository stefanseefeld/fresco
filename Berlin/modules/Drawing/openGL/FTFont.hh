/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 2002 Nick Lewycky <nicholas@fresco.org> 
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
#ifndef _openGL_FTFont_hh
#define _openGL_FTFont_hh

#include <Prague/Sys/MMap.hh>
#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/Unicode.hh>
#include <Fresco/Transform.hh>
#include <Berlin/Console/GLContext.hh>
#include "Font.hh"
#include <GL/gl.h>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Berlin
{
  namespace DrawingKit
  {
    namespace openGL
    {

      //. This is a Freetype font.
      class FTFont
      {
	public:
	  FTFont(Console_Extension::GLContext *my_glcontext);
	  virtual ~FTFont();
	  virtual CORBA::ULong size();
	  virtual CORBA::ULong weight();
	  virtual Fresco::Unistring *family();
	  virtual Fresco::Unistring *subfamily();
	  virtual Fresco::Unistring *fullname();
	  virtual Fresco::Unistring *style();
	  virtual Fresco::DrawingKit::FontMetrics metrics();
	  virtual Fresco::DrawingKit::GlyphMetrics
	  metrics(Fresco::Unichar);

	  virtual void set_transform(const Fresco::Transform_var);
	  virtual void size(CORBA::ULong);
	  
	  void draw_char(Fresco::Unichar);
	  void allocate_char(Fresco::Unichar,
			     Fresco::Graphic::Requisition &);
	private:
	  class DrawChar;
	  friend class DrawChar;
	  FT_Face  my_face;
	  Fresco::Transform_var my_tr;
	  CORBA::ULong my_size;
	  FT_Library my_library;
	  Fresco::Unistring my_family;
	  Fresco::Unistring my_subfamily;
	  Fresco::Unistring my_fullname;
	  Fresco::Unistring my_style;

	  Console_Extension::GLContext *my_glcontext;
      };

    } // namespace
  } // namespace
} // namespace

#endif
