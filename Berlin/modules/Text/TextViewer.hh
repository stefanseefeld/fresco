/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 2000 Nathaniel Smith <njs@fresco.org>
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
#ifndef _TextKit_TextViewer_hh
#define _TextKit_TextViewer_hh

#include <Fresco/config.hh>
#include <Fresco/View.hh>
#include <Fresco/TextKit.hh>
#include <Berlin/ViewImpl.hh>
#include "Composition.hh"

namespace Berlin
{
  namespace TextKit
  {

    class TextViewer : public virtual ViewImpl,
               public Composition
    {
      public:
    TextViewer(Fresco::TextBuffer_ptr, Fresco::TextKit_ptr,
           Fresco::DrawingKit_ptr, Compositor *);
    virtual ~TextViewer();
    virtual void update(const CORBA::Any &);
      protected:
    virtual void activate_composite();
    Fresco::TextKit_var my_kit;
    Fresco::TextBuffer_var my_buffer;
    };

  } // namespace
} // namespace

#endif
