/*$Id$
 *
 * This source file is a part of the Fresci Project.
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
#ifndef _UnidrawKit_Viewer_hh
#define _UnidrawKit_Viewer_hh

#include <Fresco/config.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/UnidrawKit.hh>
#include <Berlin/ControllerImpl.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/ImplVar.hh>

namespace Berlin
{
  namespace UnidrawKit
  {

    class Viewer : public ControllerImpl
    {
      public:
    Viewer();
    virtual ~Viewer();

    void init(Unidraw::Editor_ptr, Unidraw::Model_ptr,
          Fresco::Coord, Fresco::Coord, Fresco::FigureKit_ptr,
          Fresco::ToolKit_ptr);
    virtual void append_graphic(Fresco::Graphic_ptr);
    virtual void prepend_graphic(Fresco::Graphic_ptr);
    virtual Fresco::GraphicIterator_ptr first_child_graphic();
    virtual Fresco::GraphicIterator_ptr last_child_graphic();
      protected:
    virtual void press(Fresco::PickTraversal_ptr,
               const Fresco::Input::Event &);
    virtual void drag(Fresco::PickTraversal_ptr,
              const Fresco::Input::Event &);
    virtual void move(Fresco::PickTraversal_ptr,
              const Fresco::Input::Event &);
    virtual void release(Fresco::PickTraversal_ptr,
                 const Fresco::Input::Event &);
      private:
    void add(Fresco::Coord, Fresco::Coord);
    Unidraw::Editor_var my_editor;
    Unidraw::Tool_var my_active;
    Fresco::Graphic_var my_root;
    };

  } // namespace
} // namespace

#endif
