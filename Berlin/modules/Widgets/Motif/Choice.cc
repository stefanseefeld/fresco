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
#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Thread.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Selection.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/RefCountVar.hh>
#include "Widget/Motif/Choice.hh"
#include <functional>
#include <algorithm>

using namespace Prague;
using namespace Warsaw;

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

Tag ToggleChoice::appendItem(Graphic_ptr g)
{
  Trace trace("ToggleChoice::appendItem");
  RefCount_var<Warsaw::Controller> toggle =
    widgets->toggle(RefCount_var<Warsaw::Graphic>(layout->fixedSize(RefCount_var<Warsaw::Graphic>(Warsaw::Graphic::_nil()),
								    60., 60.)));
  Tag tag = selection->add(toggle);
  appendController(toggle);
  RefCount_var<Warsaw::Graphic> item = layout->hbox();
  item->append(RefCount_var<Warsaw::Graphic>(layout->valign(RefCount_var<Warsaw::Graphic>(layout->margin(toggle, 50.)), 0.5)));
  item->append(RefCount_var<Warsaw::Graphic>(layout->hspace(200.)));
  item->append(RefCount_var<Warsaw::Graphic>(layout->valign(g, 0.5)));
  RefCount_var<Warsaw::Graphic> box = body();
  Warsaw::ToolKit::FrameSpec none, colored;
  Color black = {0., 0., 0., 1.};
  colored.foreground(black);
  box->append(RefCount_var<Warsaw::Graphic>(tools->dynamic(item, 20., Warsaw::Controller::active, colored, none, false, toggle)));
  return tag;
}

Tag ToggleChoice::prependItem(Graphic_ptr g)
{
  Trace trace("ToggleChoice::prependItem");
  RefCount_var<Warsaw::Controller> toggle =
    widgets->toggle(RefCount_var<Warsaw::Graphic>(layout->fixedSize(RefCount_var<Warsaw::Graphic>(Warsaw::Graphic::_nil()),
								    60., 60.)));
  Tag tag = selection->add(toggle);
  appendController(toggle);
  RefCount_var<Warsaw::Graphic> item = layout->hbox();
  item->append(RefCount_var<Warsaw::Graphic>(layout->valign(RefCount_var<Warsaw::Graphic>(layout->margin(toggle, 50.)), 0.5)));
  item->append(RefCount_var<Warsaw::Graphic>(layout->hspace(200.)));
  item->append(RefCount_var<Warsaw::Graphic>(layout->valign(g, 0.5)));
  RefCount_var<Warsaw::Graphic> box = body();
  Warsaw::ToolKit::FrameSpec none, colored;
  Color black = {0., 0., 0., 1.};
  colored.foreground(black);
  box->prepend(RefCount_var<Warsaw::Graphic>(tools->dynamic(item, 20., Warsaw::Controller::active, colored, none, false, toggle)));
  return tag;
}

void ToggleChoice::removeItem(Tag t)
{
  Trace trace("ToggleChoice::remove");
  selection->remove(t);
  RefCount_var<Warsaw::Graphic> box = body();
  box->remove(t);
}

CheckboxChoice::CheckboxChoice(Selection_ptr s, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ::Motif::Choice(s, l, t, w)
{}

Tag CheckboxChoice::appendItem(Graphic_ptr g)
{
  Trace trace("CheckboxChoice::append");
  RefCount_var<Warsaw::Controller> toggle = tools->toggle(RefCount_var<Warsaw::Graphic>(Warsaw::Graphic::_nil()));
  Tag tag = selection->add(toggle);
  appendController(toggle);

  Warsaw::ToolKit::FrameSpec s1, s2;
  s1.brightness(0.5); s1._d(ToolKit::outset);
  s2.brightness(0.5); s2._d(ToolKit::inset);
  RefCount_var<Warsaw::Graphic> frame =
    tools->dynamicDiamond(RefCount_var<Warsaw::Graphic>(layout->fixedSize(RefCount_var<Warsaw::Graphic>(Warsaw::Graphic::_nil()),
									  60., 60.)),
			  20., Warsaw::Controller::toggled, s1, s2, true, toggle);
  toggle->body(frame);

  RefCount_var<Warsaw::Graphic> item = layout->hbox();
  item->append(RefCount_var<Warsaw::Graphic>(layout->valign(RefCount_var<Warsaw::Graphic>(layout->margin(toggle, 50.)), 0.5)));
  item->append(RefCount_var<Warsaw::Graphic>(layout->hspace(200.)));
  item->append(RefCount_var<Warsaw::Graphic>(layout->valign(g, 0.5)));
  RefCount_var<Warsaw::Graphic> box = body();
  Warsaw::ToolKit::FrameSpec none, colored;
  Color black = {0., 0., 0., 1.};
  colored.foreground(black);
  box->append(RefCount_var<Warsaw::Graphic>(tools->dynamic(item, 20., Warsaw::Controller::active, colored, none, false, toggle)));
  return tag;
}

Tag CheckboxChoice::prependItem(Graphic_ptr g)
{
  Trace trace("CheckboxChoice::prepend");
  RefCount_var<Warsaw::Controller> toggle = tools->toggle(RefCount_var<Warsaw::Graphic>(Warsaw::Graphic::_nil()));
  Tag tag = selection->add(toggle);
  appendController(toggle);

  ToolKit::FrameSpec s1, s2;
  s1.brightness(0.5); s1._d(ToolKit::outset);
  s2.brightness(0.5); s2._d(ToolKit::inset);
  RefCount_var<Warsaw::Graphic> frame =
    tools->dynamicDiamond(RefCount_var<Warsaw::Graphic>(layout->fixedSize(RefCount_var<Warsaw::Graphic>(Warsaw::Graphic::_nil()),
									  60., 60.)),
			  20., Warsaw::Controller::toggled, s1, s2, true, toggle);
  toggle->body(frame);
  
  RefCount_var<Warsaw::Graphic> item = layout->hbox();
  item->append(RefCount_var<Warsaw::Graphic>(layout->valign(RefCount_var<Warsaw::Graphic>(layout->margin(toggle, 50.)), 0.5)));
  item->append(RefCount_var<Warsaw::Graphic>(layout->hspace(200.)));
  item->append(RefCount_var<Warsaw::Graphic>(layout->valign(g, 0.5)));
  RefCount_var<Warsaw::Graphic> box = body();
  Warsaw::ToolKit::FrameSpec none, colored;
  Color black = {0., 0., 0., 1.};
  colored.foreground(black);
  box->prepend(RefCount_var<Warsaw::Graphic>(tools->dynamic(item, 20., Warsaw::Controller::active, colored, none, false, toggle)));
  return tag;
}

void CheckboxChoice::removeItem(Tag t)
{
  Trace trace("CheckboxChoice::remove");
  selection->remove(t);
  RefCount_var<Warsaw::Graphic> box = body();
  box->remove(t);
}

};
