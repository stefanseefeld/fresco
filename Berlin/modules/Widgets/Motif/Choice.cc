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
#include "Widget/Motif/Choice.hh"
#include "Berlin/Logger.hh"

namespace Motif
{

Choice::Observer::Observer(Choice *c, Controller_ptr i, Tag tt)
  : choice(c), item(Controller::_duplicate(i)), cached(item->test(Controller::toggled)), t(tt)
{
}

void Choice::Observer::update(const CORBA::Any &any)
{
  bool toggled = item->test(Controller::toggled);
  if (toggled == cached) return; // not for us...
  choice->update(t, toggled);
}

Choice::Choice(Policy p, CommandKit_ptr c, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ControllerImpl(false),
    policy(p),
    command(CommandKit::_duplicate(c)),
    layout(LayoutKit::_duplicate(l)),
    tools(ToolKit::_duplicate(t)),
    widgets(WidgetKit::_duplicate(w))
{
  if (policy == exclusive) constraint = command->exclusive(Controller::toggled);
}
  
Choice::~Choice()
{
  for (olist_t::iterator i = observers.begin(); i != observers.end(); i++)
    (*i)->_dispose();
}

CORBA::Long Choice::selection()
{
  return _selections.size() ? index(_selections.back()) : -1;
}

Choice::SelectionSeq *Choice::selections()
{
  SelectionSeq *sel = new SelectionSeq;
  sel->length(_selections.size());
  for (size_t i = 0; i != sel->length(); i++)
    (*sel)[i] = index(_selections[i]);
  return sel;
}

void Choice::appendController(Controller_ptr c)
{
  ControllerImpl::appendController(c);
  Observer *observer = new Observer(this, c, tag());
  observer->_obj_is_ready(_boa());
  c->attach(Observer_var(observer->_this()));
  observers.push_back(observer);
}

void Choice::prependController(Controller_ptr c)
{
  ControllerImpl::prependController(c);
  Observer *observer = new Observer(this, c, tag());
  observer->_obj_is_ready(_boa());
  c->attach(Observer_var(observer->_this()));
  observers.push_back(observer);
}

void Choice::update(Tag t, bool toggled)
{
  if (toggled) _selections.push_back(t);
  else
    {
      size_t idx = index(t);
      for (slist_t::iterator i = _selections.begin(); i != _selections.end(); i++)
	{
	  if ((*i) == idx) _selections.erase(i);
	  break;
	}
    }
  CORBA::Any sel;
  sel <<= selections();
  notify(sel);
}

Tag Choice::tag()
{
  Tag t = 0;
  do
    {
      olist_t::iterator i;
      for (i = observers.begin(); i != observers.end(); i++)
	if ((*i)->tag() == t) break;
      if (i == observers.end()) return t;
    }
  while (++t);
  return 0;
}

CORBA::Long Choice::index(Tag tag)
{
  size_t i = 0;
  for (; i != observers.size(); i++)
    if (observers[i]->tag() == tag) break;
  return i;
}

ToggleChoice::ToggleChoice(Policy p, CommandKit_ptr c, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : Choice(p, c, l, t, w)
{}

void ToggleChoice::append(Graphic_ptr g)
{
  SectionLog section("ToggleChoice::append");
  Controller_var toggle = widgets->toggle(Graphic_var(layout->fixedSize(Graphic_var(Graphic::_nil()), 50., 50.)));
  if (!CORBA::is_nil(constraint)) constraint->add(toggle);
  appendController(toggle);
  Graphic_var item = layout->hbox();
  item->append(Graphic_var(layout->margin(toggle, 100.)));
  item->append(Graphic_var(layout->hspace(200.)));
  item->append(g);
  Graphic_var box = body();
  box->append(item);
}

void ToggleChoice::prepend(Graphic_ptr g)
{
  SectionLog section("ToggleChoice::prepend");
  Controller_var toggle = widgets->toggle(Graphic_var(layout->fixedSize(Graphic_var(Graphic::_nil()), 50., 50.)));
  if (!CORBA::is_nil(constraint)) constraint->add(toggle);
  appendController(toggle);
  Graphic_var item = layout->hbox();
  item->append(Graphic_var(layout->margin(toggle, 100.)));
  item->append(Graphic_var(layout->hspace(200.)));
  item->append(g);
  Graphic_var box = body();
  box->prepend(item);
}

void ToggleChoice::remove(Tag t)
{
  SectionLog section("ToggleChoice::remove");
  Graphic_var box = body();
  box->remove(t);
}

CheckboxChoice::CheckboxChoice(Policy p, CommandKit_ptr c, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : Choice(p, c, l, t, w)
{}

void CheckboxChoice::append(Graphic_ptr g)
{
  SectionLog section("CheckboxChoice::append");
  Controller_var toggle = tools->toggle(Graphic_var(Graphic::_nil()));
  ToolKit::FrameSpec s1, s2;
  s1.abrightness(0.5);
  s2.bbrightness(0.5);
  Graphic_var frame = tools->dynamicDiamond(g, 20., Controller::toggled, s1, s2, true, toggle);
  toggle->body(frame);

  if (!CORBA::is_nil(constraint)) constraint->add(toggle);
  appendController(toggle);
  Graphic_var item = layout->hbox();
  item->append(Graphic_var(layout->margin(toggle, 100.)));
  item->append(Graphic_var(layout->hspace(200.)));
  item->append(g);
  Graphic_var box = body();
  box->append(item);
}

void CheckboxChoice::prepend(Graphic_ptr g)
{
  SectionLog section("CheckboxChoice::prepend");
  Controller_var toggle = tools->toggle(Graphic_var(Graphic::_nil()));
  ToolKit::FrameSpec s1, s2;
  s1.abrightness(0.5);
  s2.bbrightness(0.5);
  Graphic_var frame = tools->dynamicDiamond(g, 20., Controller::toggled, s1, s2, true, toggle);
  toggle->body(frame);

  if (!CORBA::is_nil(constraint)) constraint->add(toggle);
  appendController(toggle);
  Graphic_var item = layout->hbox();
  item->append(Graphic_var(layout->margin(toggle, 100.)));
  item->append(Graphic_var(layout->hspace(200.)));
  item->append(g);
  Graphic_var box = body();
  box->prepend(item);
}

void CheckboxChoice::remove(Tag t)
{
  SectionLog section("CheckboxChoice::remove");
  Graphic_var box = body();
  box->remove(t);
}

};
