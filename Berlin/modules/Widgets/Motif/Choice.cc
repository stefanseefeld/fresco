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
#include <Warsaw/Selection.hh>
#include <Prague/Sys/Thread.hh>
#include <Berlin/SubjectImpl.hh>
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

namespace Motif
{

  class Choice::State : implements(Selection), public SubjectImpl
{
  class Observer;
  friend class Observer;
  class Observer : implements(Observer)
    {
    public:
      Observer(State *, Telltale_ptr, Tag);
      Tag tag() const { return t;}
      bool toggled() { return cached;}
      void update(const CORBA::Any &);
    private:
      State *state;
      Telltale_var item;
      bool cached;
      Tag t;
    };
  typedef vector<Observer *> list_t;
 public:
  State(Policy, CommandKit_ptr);
  ~State();
  virtual Policy type() { return policy;}
  virtual void type(Policy) {}
  Tag add(Telltale_ptr);
  void remove(Tag);
  Items *toggled();
 private:
  void update(Tag, bool);
  Tag tag();
  CORBA::Long index(Tag); 
  Mutex mutex;
  Policy policy;
  TelltaleConstraint_var constraint;
  list_t items;
};

Choice::State::Observer::Observer(State *s, Telltale_ptr i, Tag tt)
  : state(s), item(Telltale::_duplicate(i)), cached(item->test(Controller::toggled)), t(tt)
{
}

void Choice::State::Observer::update(const CORBA::Any &any)
{
  bool toggled = item->test(Controller::toggled);
  if (toggled == cached) return; // not for us...
  cached = toggled;
  state->update(t, toggled);
}

Choice::State::State(Policy p, CommandKit_ptr c)
  : policy(p)
{
  if (policy == exclusive) constraint = c->exclusive(Controller::toggled);
}
Choice::State::~State()
{
  for (list_t::iterator i = items.begin(); i != items.end(); i++)
    (*i)->_dispose();
}

Tag Choice::State::add(Telltale_ptr t)
{
  MutexGuard guard(mutex);
  Observer *observer = new Observer(this, t, tag());
  observer->_obj_is_ready(CORBA::BOA::getBOA());
  t->attach(Observer_var(observer->_this()));
  if (!CORBA::is_nil(constraint)) constraint->add(t);
  items.push_back(observer);
  return observer->tag();
}

void Choice::State::remove(Tag t)
{
  MutexGuard guard(mutex);
  size_t i = index(t);
  if (i < items.size())
    {
//       if (!CORBA::is_nil(constraint)) constraint->remove(t);
      delete items[i];
      items.erase(items.begin() + i);
    }
}

Selection::Items *Choice::State::toggled()
{
  MutexGuard guard(mutex);
  Items *ret = new Items;
  for (list_t::iterator i = items.begin(); i != items.end(); i++)
    if ((*i)->toggled())
      {
	ret->length(ret->length() + 1);
	(*ret)[ret->length() - 1] = (*i)->tag();
      }
  return ret;
}

void Choice::State::update(Tag t, bool toggled)
{
  CORBA::Any any;
  Item item;
  item.id = t;
  item.toggled = toggled;
  any <<= item;
  notify(any);
}

Tag Choice::State::tag()
{
  Tag t = 0;
  do
    {
      list_t::iterator i;
      for (i = items.begin(); i != items.end(); i++)
	if ((*i)->tag() == t) break;
      if (i == items.end()) return t;
    }
  while (++t);
  return 0;
}

CORBA::Long Choice::State::index(Tag tag)
{
  size_t i = 0;
  for (; i != items.size(); i++)
    if (items[i]->tag() == tag) break;
  return i;
}

Choice::Choice(Selection::Policy p, CommandKit_ptr c, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ControllerImpl(false),
    _state(new State(p, c)),
    layout(LayoutKit::_duplicate(l)),
    tools(ToolKit::_duplicate(t)),
    widgets(WidgetKit::_duplicate(w))
{
  _state->_obj_is_ready(CORBA::BOA::getBOA());
}
  
Choice::~Choice()
{
  _state->_dispose();
}

Selection_ptr Choice::state()
{
  return _state->_this();
}

ToggleChoice::ToggleChoice(Selection::Policy p, CommandKit_ptr c, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ::Motif::Choice(p, c, l, t, w)
{}

Tag ToggleChoice::appendItem(Graphic_ptr g)
{
  Trace trace("ToggleChoice::append");
  Controller_var toggle = widgets->toggle(Graphic_var(layout->fixedSize(Graphic_var(Graphic::_nil()), 60., 60.)));
  Tag tag = _state->add(toggle);
  appendController(toggle);
  Graphic_var item = layout->hbox();
  item->append(Graphic_var(layout->valign(Graphic_var(layout->margin(toggle, 50.)), 0.5)));
  item->append(Graphic_var(layout->hspace(200.)));
  item->append(Graphic_var(layout->valign(g, 0.5)));
  Graphic_var box = body();
  ToolKit::FrameSpec none, colored;
  Color black = {0., 0., 0., 1.};
  colored.foreground(black);
  box->append(Graphic_var(tools->dynamic(item, 20., Controller::active, colored, none, false, toggle)));
  return tag;
}

Tag ToggleChoice::prependItem(Graphic_ptr g)
{
  Trace trace("ToggleChoice::prepend");
  Controller_var toggle = widgets->toggle(Graphic_var(layout->fixedSize(Graphic_var(Graphic::_nil()), 60., 60.)));
  Tag tag = _state->add(toggle);
  appendController(toggle);
  Graphic_var item = layout->hbox();
  item->append(Graphic_var(layout->valign(Graphic_var(layout->margin(toggle, 50.)), 0.5)));
  item->append(Graphic_var(layout->hspace(200.)));
  item->append(Graphic_var(layout->valign(g, 0.5)));
  Graphic_var box = body();
  ToolKit::FrameSpec none, colored;
  Color black = {0., 0., 0., 1.};
  colored.foreground(black);
  box->prepend(Graphic_var(tools->dynamic(item, 20., Controller::active, colored, none, false, toggle)));
  return tag;
}

void ToggleChoice::removeItem(Tag t)
{
  Trace trace("ToggleChoice::remove");
  _state->remove(t);
  Graphic_var box = body();
  box->remove(t);
}

CheckboxChoice::CheckboxChoice(Selection::Policy p, CommandKit_ptr c, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ::Motif::Choice(p, c, l, t, w)
{}

Tag CheckboxChoice::appendItem(Graphic_ptr g)
{
  Trace trace("CheckboxChoice::append");
  Controller_var toggle = tools->toggle(Graphic_var(Graphic::_nil()));
  Tag tag = _state->add(toggle);
  appendController(toggle);

  ToolKit::FrameSpec s1, s2;
  s1.abrightness(0.5);
  s2.bbrightness(0.5);
  Graphic_var frame = tools->dynamicDiamond(Graphic_var(layout->fixedSize(Graphic_var(Graphic::_nil()), 60., 60.)),
					    20., Controller::toggled, s1, s2, true, toggle);
  toggle->body(frame);

  Graphic_var item = layout->hbox();
  item->append(Graphic_var(layout->valign(Graphic_var(layout->margin(toggle, 50.)), 0.5)));
  item->append(Graphic_var(layout->hspace(200.)));
  item->append(Graphic_var(layout->valign(g, 0.5)));
  Graphic_var box = body();
  ToolKit::FrameSpec none, colored;
  Color black = {0., 0., 0., 1.};
  colored.foreground(black);
  box->append(Graphic_var(tools->dynamic(item, 20., Controller::active, colored, none, false, toggle)));
  return tag;
}

Tag CheckboxChoice::prependItem(Graphic_ptr g)
{
  Trace trace("CheckboxChoice::prepend");
  Controller_var toggle = tools->toggle(Graphic_var(Graphic::_nil()));
  Tag tag = _state->add(toggle);
  appendController(toggle);

  ToolKit::FrameSpec s1, s2;
  s1.abrightness(0.5);
  s2.bbrightness(0.5);
  Graphic_var frame = tools->dynamicDiamond(Graphic_var(layout->fixedSize(Graphic_var(Graphic::_nil()), 60., 60.)),
					    20., Controller::toggled, s1, s2, true, toggle);
  toggle->body(frame);

  Graphic_var item = layout->hbox();
  item->append(Graphic_var(layout->valign(Graphic_var(layout->margin(toggle, 50.)), 0.5)));
  item->append(Graphic_var(layout->hspace(200.)));
  item->append(Graphic_var(layout->valign(g, 0.5)));
  Graphic_var box = body();
  ToolKit::FrameSpec none, colored;
  Color black = {0., 0., 0., 1.};
  colored.foreground(black);
  box->prepend(Graphic_var(tools->dynamic(item, 20., Controller::active, colored, none, false, toggle)));
  return tag;
}

void CheckboxChoice::removeItem(Tag t)
{
  Trace trace("CheckboxChoice::remove");
  _state->remove(t);
  Graphic_var box = body();
  box->remove(t);
}

};
