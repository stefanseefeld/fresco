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
#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/IO.hh>
#include <Fresco/PickTraversal.hh>
#include <Berlin/RefCountVar.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/Requestor.hh>
#include <Berlin/Event.hh>
#include "Viewer.hh"

using namespace Prague;
using namespace Fresco;
using namespace Unidraw;

using namespace Berlin::UnidrawKit;

Viewer::Viewer() : ControllerImpl(false) { }
Viewer::~Viewer() { }

void Viewer::init(Editor_ptr editor, Model_ptr model,
          Coord width, Coord height,
          FigureKit_ptr figures, ToolKit_ptr tools)
{
    my_editor = RefCount_var<Editor>::increment(editor);
    Requestor *requestor = new Requestor(0., 0., width, height);
    activate(requestor);
    my_root = figures->group();
    requestor->body(my_root);
    ToolKit::FrameSpec background;
    Color white = {1., 1., 1., 1.};
    background.foreground(white);
    body(Fresco::Graphic_var(tools->frame(Fresco::Graphic_var(requestor->_this()), 20., background, true)));
    if (!CORBA::is_nil(model))
    {
    Graphic_var view = model->create_view();
    my_root->append_graphic(view);
    }
}

void Viewer::append_graphic(Graphic_ptr c)
{ my_root->append_graphic(c); }

void Viewer::prepend_graphic(Graphic_ptr c)
{ my_root->prepend_graphic(c); }

Fresco::GraphicIterator_ptr Viewer::first_child_graphic()
{ return my_root->first_child_graphic(); }

Fresco::GraphicIterator_ptr Viewer::last_child_graphic()
{ return my_root->last_child_graphic(); }

void Viewer::press(Fresco::PickTraversal_ptr traversal,
           const Fresco::Input::Event &event)
{
    Trace trace("Viewer::press");
    bool ok = false;
    if (CORBA::is_nil(my_active))
    {
    my_active = my_editor->current_tool();
    if (CORBA::is_nil(my_active)) return;
    ok = my_active->grasp(Controller_var(_this()), traversal, event);
    }
    else ok = my_active->manipulate(traversal, event);
    if (!ok && !CORBA::is_nil(my_active))
    {
    Unidraw::Command_var command = my_active->effect(traversal, event);
    command->execute();
    my_active = Unidraw::Tool::_nil();
    }
    ControllerImpl::press(traversal, event);
}

void Viewer::drag(Fresco::PickTraversal_ptr traversal,
          const Fresco::Input::Event &event)
{
    Trace trace("Viewer::drag");
    if (CORBA::is_nil(my_active)) return;
    if (!my_active->manipulate(traversal, event))
    {
    Unidraw::Command_var command = my_active->effect(traversal, event);
    command->execute();
    my_active = Unidraw::Tool::_nil();
    }
}

void Viewer::move(Fresco::PickTraversal_ptr traversal,
          const Fresco::Input::Event &event)
{ Viewer::drag(traversal, event); }

void Viewer::release(Fresco::PickTraversal_ptr traversal,
             const Fresco::Input::Event &event)
{
    Trace trace("Viewer::release");
    if (CORBA::is_nil(my_active))
    {
    ControllerImpl::release(traversal, event);
    return;
    }
    if (!my_active->manipulate(traversal, event))
    {
    Unidraw::Command_var command = my_active->effect(traversal, event);
    command->execute();
    my_active = Unidraw::Tool::_nil();
    }
    ControllerImpl::release(traversal, event);
}
