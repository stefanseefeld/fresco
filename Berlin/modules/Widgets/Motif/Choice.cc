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
#include <functional>
#include <algorithm>

using namespace Prague;
using namespace Fresco;

namespace Motif
{

Choice::Choice(Selection_ptr s, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ControllerImpl(false),
    selection(RefCount_var<Selection>::increment(s)),
    layout(RefCount_var<LayoutKit>::increment(l)),
    tools(RefCount_var<ToolKit>::increment(t)),
    widgets(RefCount_var<WidgetKit>::increment(w))
{ Trace trace("Choice::Choice");}
  
Choice::~Choice() { Trace trace("Choice::~Choice");}

Selection_ptr Choice::state()
{
  Trace trace("Choice::state");
  return RefCount_var<Selection>::increment(selection);
}

ToggleChoice::ToggleChoice(Selection_ptr s, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ::Motif::Choice(s, l, t, w)
{}

RefCount_var<Fresco::Graphic> ToggleChoice::create_item(Graphic_ptr g, Tag& t)
{
  Trace trace("ToggleChoice::create_item");

  // Define initial hbox, which is nested inside a toggle-box (no bevel!)
  RefCount_var<Fresco::Graphic> box = layout->hbox();
  RefCount_var<Fresco::Controller> toggle_box = tools->toggle(box);
  t = selection->add(toggle_box);
  append_controller(toggle_box);

  // 'toggle': simply a graphic with bevel dependent upon toggle_box
  RefCount_var<Fresco::Graphic> toggle =
          layout->fixed_size(Fresco::Graphic::_nil(), 60., 60.);
  Fresco::ToolKit::FrameSpec s1, s2;
  s1.brightness(0.5); s1._d(Fresco::ToolKit::inset);
  s2.brightness(0.5); s2._d(Fresco::ToolKit::outset);
  Graphic_var frame = tools->dynamic(toggle, 20., Fresco::Controller::toggled, 
                                     s1, s2, true, toggle_box);

  // now add the toggle button into the button box, along with g
  box->append_graphic(RefCount_var<Fresco::Graphic>(layout->valign(RefCount_var<Fresco::Graphic>(layout->margin(frame, 50.)), 0.5)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(layout->hspace(100.)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(layout->valign(g, 0.5)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(layout->hspace(50.)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(layout->hfill()));

  // Add the 'active item' border
  Fresco::ToolKit::FrameSpec none, colored;
  Color black = {0., 0., 0., 1.};
  colored.foreground(black);
  return RefCount_var<Fresco::Graphic>(tools->dynamic(toggle_box, 20., 
                 Fresco::Controller::active, colored, none, false, toggle_box));
}

Tag ToggleChoice::append_item(Graphic_ptr g)
{
  Trace trace("ToggleChoice::append_item");
  Tag tag;
  body()->append_graphic(create_item(g,tag));
  return tag;
}

Tag ToggleChoice::prepend_item(Graphic_ptr g)
{
  Trace trace("ToggleChoice::prepend_item");
  Tag tag;
  body()->prepend_graphic(create_item(g,tag));
  return tag;
}

void ToggleChoice::remove_item(Tag t)
{
  Trace trace("ToggleChoice::remove_item");
  selection->remove(t);
  Graphic_var box = body();
  box->remove_graphic(t);
}

CheckboxChoice::CheckboxChoice(Selection_ptr s, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ::Motif::Choice(s, l, t, w)
{}

RefCount_var<Fresco::Graphic> CheckboxChoice::create_item(Graphic_ptr g, Tag& t)
{
  Trace trace("CheckboxChoice::create_item");

  // Define initial hbox, which is nested inside a toggle-box (no bevel!)
  RefCount_var<Fresco::Graphic> box = layout->hbox();
  RefCount_var<Fresco::Controller> toggle_box = tools->toggle(box);
  t = selection->add(toggle_box);
  append_controller(toggle_box);

  // 'toggle': simply a graphic with bevel dependent upon toggle_box state
  RefCount_var<Fresco::Graphic> toggle =
          layout->fixed_size(Fresco::Graphic::_nil(), 60., 60.);
  Fresco::ToolKit::FrameSpec s1, s2;
  s1.brightness(0.5); s1._d(Fresco::ToolKit::outset);
  s2.brightness(0.5); s2._d(Fresco::ToolKit::inset);
  RefCount_var<Fresco::Graphic> frame =
    tools->dynamic_diamond(toggle, 20., Fresco::Controller::toggled, 
                           s1, s2, true, toggle_box);
  
  box->append_graphic(RefCount_var<Fresco::Graphic>(layout->valign(RefCount_var<Fresco::Graphic>(layout->margin(frame, 50.)), 0.5)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(layout->hspace(100.)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(layout->valign(g, 0.5)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(layout->hspace(50.)));
  box->append_graphic(RefCount_var<Fresco::Graphic>(layout->hfill()));

  // Add the 'active item' border
  Fresco::ToolKit::FrameSpec none, colored;
  Color black = {0., 0., 0., 1.};
  colored.foreground(black);
  return RefCount_var<Fresco::Graphic>(tools->dynamic(toggle_box, 20., 
                Fresco::Controller::active, colored, none, false, toggle_box));
}

Tag CheckboxChoice::append_item(Graphic_ptr g)
{
  Trace trace("CheckboxChoice::append_item");
  Tag tag;
  body()->append_graphic(create_item(g,tag));
  return tag;
}

Tag CheckboxChoice::prepend_item(Graphic_ptr g)
{
  Trace trace("CheckboxChoice::prepend_item");
  Tag tag;
  body()->prepend_graphic(create_item(g,tag));
  return tag;
}

void CheckboxChoice::remove_item(Tag t)
{
  Trace trace("CheckboxChoice::remove_item");
  selection->remove(t);
  Graphic_var box = body();
  box->remove_graphic(t);
}

ToolChoice::ToolChoice(Selection_ptr s, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ::Motif::Choice(s, l, t, w)
{}

Tag ToolChoice::append_item(Graphic_ptr g)
{
  Trace trace("ToolChoice::append_item");
  RefCount_var<Fresco::Controller> toggle = tools->toggle(Fresco::Graphic::_nil());
  Tag tag = selection->add(toggle);
  append_controller(toggle);

  Fresco::ToolKit::FrameSpec s1, s2;
  s1.brightness(0.5); s1._d(ToolKit::inset);
  s2.brightness(0.5); s2._d(ToolKit::outset);
  RefCount_var<Fresco::Graphic> frame = tools->dynamic(g, 20., Fresco::Controller::toggled, s1, s2, true, toggle);
  toggle->body(frame);
  Graphic_var box = body();
  box->append_graphic(toggle);
  return tag;
}

Tag ToolChoice::prepend_item(Graphic_ptr g)
{
  Trace trace("ToolChoice::prepend_item");
  RefCount_var<Fresco::Controller> toggle = tools->toggle(Fresco::Graphic::_nil());
  Tag tag = selection->add(toggle);
  prepend_controller(toggle);

  Fresco::ToolKit::FrameSpec s1, s2;
  s1.brightness(0.5); s1._d(ToolKit::outset);
  s2.brightness(0.5); s2._d(ToolKit::inset);
  RefCount_var<Fresco::Graphic> frame = tools->dynamic(g, 20., Fresco::Controller::toggled, s1, s2, true, toggle);
  toggle->body(frame);
  Graphic_var box = body();
  box->prepend_graphic(toggle);
  return tag;
}

void ToolChoice::remove_item(Tag t)
{
  Trace trace("ToolChoice::remove_item");
  selection->remove(t);
  Graphic_var box = body();
  box->remove_graphic(t);
}

};
