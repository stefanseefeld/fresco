/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include "Console/GLContext.hh"
#include "Console/GGI/GGI.hh"
#include <GL/ggimesa.h>

using namespace Prague;
using namespace Warsaw;

class GGIGLContext : virtual public GLContext
{
public:
  GGIGLContext(Console::Drawable *drawable)
    : _context(GGIMesaCreateContext())
  {
    if (GGIMesaSetVisual(_context, static_cast<GGIDrawable *>(drawable)->visual(), GL_TRUE, GL_FALSE))
      throw std::runtime_error("GGIMesaSetVisual() failed");
    GGIMesaMakeCurrent(_context);
  }
  ~GGIGLContext()
  {
    GGIMesaDestroyContext(_context);
  }
private:
  GGIMesaContext _context;  
};

extern "C" Console::Extension::LoaderT<GGIGLContext> *load() { return new Console::Extension::LoaderT<GGIGLContext>();}
