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
#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/Selection.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/RefCountVar.hh>
#include "Choice.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::WidgetKit::Motif;

Choice::Choice(Selection_ptr s, LayoutKit_ptr l, ToolKit_ptr t)
  : ControllerImpl(false),
    my_selection(RefCount_var<Selection>::increment(s)),
    my_layout(RefCount_var<LayoutKit>::increment(l)),
    my_tools(RefCount_var<ToolKit>::increment(t))
{ Trace trace("Choice::Choice");}
  
Choice::~Choice() { Trace trace("Choice::~Choice");}

Selection_ptr Choice::state()
{
  Trace trace("Choice::state");
  return RefCount_var<Selection>::increment(my_selection);
}

Graphic_ptr Choice::create_focus_frame(Controller_ptr g)
{
  Fresco::ToolKit::FrameSpec none;
  Graphic_var empty = my_tools->frame(g, 20., none, false);
  Fresco::ToolKit::FrameSpec colored;
  Color c = {0., 0., 0., 1.};
  colored.foreground(c);
  Graphic_var black = my_tools->frame(g, 20., colored, false);

  return my_tools->create_switch(black, empty, Fresco::Controller::active, g);
}

ToggleChoice::ToggleChoice(Selection_ptr s,
			   Graphic_ptr inbox,
			   Graphic_ptr outbox,
			   LayoutKit_ptr l,
			   ToolKit_ptr t)
  : Choice(s, l, t),
    my_in_box(Fresco::Graphic::_duplicate(inbox)),
    my_out_box(Fresco::Graphic::_duplicate(outbox))
{}

RefCount_var<Fresco::Graphic> ToggleChoice::create_item(Graphic_ptr g, Tag& t)
{
  Trace trace("ToggleChoice::create_item");

  // Define initial hbox, which is nested inside a toggle-box (no bevel!)
  RefCount_var<Fresco::Graphic> box = my_layout->hbox();
  RefCount_var<Fresco::Controller> toggle_box = my_tools->toggle(box);
  t = my_selection->add(toggle_box);
  append_controller(toggle_box);

  // 'toggle': simply a graphic with bevel dependent upon toggle_box
  Graphic_var toggle = my_tools->create_switch(my_in_box, my_out_box,
					      Fresco::Controller::toggled, 
					      toggle_box);

  // now add the toggle button into the button box, along with g
  box->append_graphic(RefCount_var<Fresco::Graphic>(my_layout->valign(RefCount_var<Fresco::Graphic>(my_layout->margin(toggle, 50.)), 0.5)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(my_layout->hspace(100.)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(my_layout->valign(g, 0.5)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(my_layout->hspace(50.)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(my_layout->hfill()));

  // Add the 'active item' border
  return create_focus_frame(toggle_box);
}

Tag ToggleChoice::append_item(Graphic_ptr g)
{
  Trace trace("ToggleChoice::append_item");
  Tag tag;
  body()->append_graphic(create_item(g, tag));
  return tag;
}

Tag ToggleChoice::prepend_item(Graphic_ptr g)
{
  Trace trace("ToggleChoice::prepend_item");
  Tag tag;
  body()->prepend_graphic(create_item(g, tag));
  return tag;
}

void ToggleChoice::remove_item(Tag t)
{
  Trace trace("ToggleChoice::remove_item");
  my_selection->remove(t);
  Graphic_var box = body();
  box->remove_graphic(t);
}

CheckboxChoice::CheckboxChoice(Selection_ptr s,
			       Graphic_ptr inbox,
			       Graphic_ptr outbox,
			       LayoutKit_ptr l,
			       ToolKit_ptr t)
  : Choice(s, l, t),
    my_in_box(Fresco::Graphic::_duplicate(inbox)),
    my_out_box(Fresco::Graphic::_duplicate(outbox))
{}

RefCount_var<Fresco::Graphic> CheckboxChoice::create_item(Graphic_ptr g, Tag& t)
{
  Trace trace("CheckboxChoice::create_item");

  // Define initial hbox, which is nested inside a toggle-box (no bevel!)
  RefCount_var<Fresco::Graphic> box = my_layout->hbox();
  RefCount_var<Fresco::Controller> toggle_box = my_tools->toggle(box);
  t = my_selection->add(toggle_box);
  append_controller(toggle_box);

  // 'toggle': simply a graphic with bevel dependent upon toggle_box state

  Graphic_var toggle = my_tools->create_switch(my_in_box, my_out_box,
					       Fresco::Controller::toggled, 
					       toggle_box);

  box->append_graphic(RefCount_var<Fresco::Graphic>(my_layout->valign(RefCount_var<Fresco::Graphic>(my_layout->margin(toggle, 50.)), 0.5)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(my_layout->hspace(100.)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(my_layout->valign(g, 0.5)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(my_layout->hspace(50.)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(my_layout->hfill()));

  // Add the 'active item' border
//   return RefCount_var<Fresco::Graphic>(create_focus_frame(toggle_box));
  return create_focus_frame(toggle_box);
}

Tag CheckboxChoice::append_item(Graphic_ptr g)
{
  Trace trace("CheckboxChoice::append_item");
  Tag tag;
  body()->append_graphic(create_item(g, tag));
  return tag;
}

Tag CheckboxChoice::prepend_item(Graphic_ptr g)
{
  Trace trace("CheckboxChoice::prepend_item");
  Tag tag;
  body()->prepend_graphic(create_item(g, tag));
  return tag;
}

void CheckboxChoice::remove_item(Tag t)
{
  Trace trace("CheckboxChoice::remove_item");
  my_selection->remove(t);
  Graphic_var box = body();
  box->remove_graphic(t);
}

ToolChoice::ToolChoice(Selection_ptr s, LayoutKit_ptr l, ToolKit_ptr t)
  : Choice(s, l, t)
{}

Tag ToolChoice::append_item(Graphic_ptr g)
{
  Trace trace("ToolChoice::append_item");
  RefCount_var<Fresco::Controller> toggle = my_tools->toggle(Fresco::Graphic::_nil());
  Tag tag = my_selection->add(toggle);
  append_controller(toggle);

  Fresco::ToolKit::FrameSpec in, out;
  in.brightness(0.5); in._d(ToolKit::inset);
  Graphic_var inset = my_tools->frame(g, 20., in, true);
  out.brightness(0.5); out._d(ToolKit::outset);
  Graphic_var outset = my_tools->frame(g, 20., out, true);
  Graphic_var frame = my_tools->create_switch(inset, outset,
					      Fresco::Controller::toggled,
					      toggle);
  toggle->body(frame);
  Graphic_var box = body();
  box->append_graphic(toggle);
  return tag;
}

Tag ToolChoice::prepend_item(Graphic_ptr g)
{
  Trace trace("ToolChoice::prepend_item");
  RefCount_var<Fresco::Controller> toggle = my_tools->toggle(Fresco::Graphic::_nil());
  Tag tag = my_selection->add(toggle);
  prepend_controller(toggle);

  Fresco::ToolKit::FrameSpec in, out;
  in.brightness(0.5); in._d(ToolKit::inset);
  Graphic_var inset = my_tools->frame(g, 20., in, true);
  out.brightness(0.5); out._d(ToolKit::outset);
  Graphic_var outset = my_tools->frame(g, 20., out, true);
  Graphic_var frame = my_tools->create_switch(inset, outset,
					      Fresco::Controller::toggled,
					      toggle);
  toggle->body(frame);
  Graphic_var box = body();
  box->prepend_graphic(toggle);
  return tag;
}

void ToolChoice::remove_item(Tag t)
{
  Trace trace("ToolChoice::remove_item");
  my_selection->remove(t);
  Graphic_var box = body();
  box->remove_graphic(t);
}
