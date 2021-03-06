/*$Id$
 *
 * This source file is a part of the Fresco Project.
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
#include <Berlin/Console.hh>
#include <Berlin/Console/GLContext.hh>
#include "Drawable.hh"
#include <GL/ggimesa.h>

using namespace Prague;
using namespace Fresco;

namespace GGI
{
  class GLContext : virtual public ::GLContext
  {
    public:
      GLContext() :
        my_drawable(dynamic_cast<GGI::Drawable *>
            (Berlin::Console::instance()->drawable()))
      {
      ggiMesaInit();
      if (ggiMesaAttach(_drawable->visual()) < 0)
          throw std::runtime_error("ggiMesaAttach() failed");
      if (ggiMesaExtendVisual(my_drawable->visual(),
                  GL_FALSE, GL_FALSE,
                  16, 0, 0, 0, 0, 0, 1) < 0)
          throw std::runtime_error("ggiMesaExtendVisual() failed");
      if ((my_context =
           ggiMesaCreateContext(_drawable->visual())) == NULL)
          throw std::runtime_error("ggiMesaCreateContext() failed");
      ggiMesaMakeCurrent(my_context, my_drawable->visual());
      }
      virtual ~GGIGLContext() { ggiMesaDestroyContext(my_context); }
      virtual void flush()
      {
          glFlush();
          my_drawable->flush();
      }
      virtual void add_to_queue(::GLContext::Callback *_cb)
      {
          (*my_cb)();
      }
    private:
      GGI::Drawable *my_drawable;
      ggi_mesa_context_t my_context;
  };

} // namespace

extern "C" Berlin::Console::Extension *load()
{ return new GGI::GLContext(); }
