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

class Choice::State : public virtual POA_Warsaw::Selection,
	              public SubjectImpl
{
  class Observer : public ObserverImpl
    {
    public:
      Observer(State *, Telltale_ptr, Tag);
      Tag id() const { return t;}
      bool toggled() { return cached;}
      void update(const CORBA::Any &);
    private:
      State *state;
      RefCount_var<Warsaw::Telltale> item;
      bool cached;
      Tag t;
    };
  friend class Observer;
  typedef vector<Observer *> list_t;
 public:
  State(Warsaw::Selection::Policy, CommandKit_ptr);
  ~State();
  virtual Warsaw::Selection::Policy type() { return policy;}
  virtual void type(Warsaw::Selection::Policy) {}
  Tag add(Telltale_ptr);
  void remove(Tag);
  Warsaw::Selection::Items *toggled();
 private:
  void update(Tag, bool);
  Tag uniqueId();
  CORBA::Long idToIndex(Tag); 
  Mutex mutex;
  Warsaw::Selection::Policy policy;
  RefCount_var<Warsaw::TelltaleConstraint> constraint;
  list_t items;
};

Choice::State::Observer::Observer(State *s, Telltale_ptr i, Tag tt)
  : state(s), item(RefCount_var<Warsaw::Telltale>::increment(i)), cached(item->test(Warsaw::Controller::toggled)), t(tt)
{
}

void Choice::State::Observer::update(const CORBA::Any &any)
{
  bool toggled = item->test(Warsaw::Controller::toggled);
  if (toggled == cached) return; // not for us...
  cached = toggled;
  state->update(t, toggled);
}

Choice::State::State(Warsaw::Selection::Policy p, CommandKit_ptr c)
  : policy(p)
{
  Trace trace("Choice::State::State");
  if (policy == Warsaw::Selection::exclusive) constraint = c->exclusive(Warsaw::Controller::toggled);
}

Choice::State::~State()
{
  Trace trace("Choice::State::~State");
  for (list_t::iterator i = items.begin(); i != items.end(); i++)
    (*i)->deactivate();
}

Tag Choice::State::add(Telltale_ptr t)
{
  Trace trace("Choice::State::add");
  MutexGuard guard(mutex);
  Observer *observer = new Observer(this, t, uniqueId());
  activate(observer);
  t->attach(Observer_var(observer->_this()));
  if (!CORBA::is_nil(constraint)) constraint->add(t);
  items.push_back(observer);
  return observer->id();
}

void Choice::State::remove(Tag t)
{
  MutexGuard guard(mutex);
  size_t i = idToIndex(t);
  if (i < items.size())
    {
      //       if (!CORBA::is_nil(constraint)) constraint->remove(t);
      items[i]->deactivate();
      items.erase(items.begin() + i);
    }
}

Selection::Items *Choice::State::toggled()
{
  MutexGuard guard(mutex);
  Warsaw::Selection::Items_var ret = new Warsaw::Selection::Items;
  for (list_t::iterator i = items.begin(); i != items.end(); i++)
    if ((*i)->toggled())
      {
	ret->length(ret->length() + 1);
	ret[ret->length() - 1] = (*i)->id();
      }
  return ret._retn();
}

void Choice::State::update(Tag t, bool toggled)
{
  CORBA::Any any;
  Warsaw::Selection::Item item;
  item.id = t;
  item.toggled = toggled;
  any <<= item;
  notify(any);
}

struct Id_eq : public unary_function<Choice::State::Observer *, bool>
{
  Id_eq(Warsaw::Tag t) : id(t) {}
  bool operator()(const Choice::State::Observer *o) const { return o->id() == id; }
  Warsaw::Tag id;
};

Tag Choice::State::uniqueId()
{
  Tag id = 0;
  do
    if (find_if(items.begin(), items.end(), Id_eq(id)) == items.end())
      return id;
  while(++id);
}

CORBA::Long Choice::State::idToIndex(Tag id)
{
  return find_if(items.begin(), items.end(), Id_eq(id)) - items.begin();
}

Choice::Choice(Selection::Policy p, CommandKit_ptr c, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ControllerImpl(false),
    _state(new State(p, c)),
    layout(LayoutKit::_duplicate(l)),
    tools(ToolKit::_duplicate(t)),
    widgets(WidgetKit::_duplicate(w))
{
  Trace trace("Choice::Choice");
}
  
Choice::~Choice()
{
  Trace trace("Choice::~Choice");
  _state->deactivate();
}

Selection_ptr Choice::state()
{
  Trace trace("Choice::state");
  _state->increment();
  return _state->_this();
}

void Choice::activateComposite()
{
  ControllerImpl::activateComposite();
  activate(_state);
}

ToggleChoice::ToggleChoice(Selection::Policy p, CommandKit_ptr c, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ::Motif::Choice(p, c, l, t, w)
{}

Tag ToggleChoice::appendItem(Graphic_ptr g)
{
  Trace trace("ToggleChoice::appendItem");
  RefCount_var<Warsaw::Controller> toggle =
    widgets->toggle(RefCount_var<Warsaw::Graphic>(layout->fixedSize(RefCount_var<Warsaw::Graphic>(Warsaw::Graphic::_nil()),
								    60., 60.)));
  Tag tag = _state->add(toggle);
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
  Tag tag = _state->add(toggle);
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
  _state->remove(t);
  RefCount_var<Warsaw::Graphic> box = body();
  box->remove(t);
}

CheckboxChoice::CheckboxChoice(Selection::Policy p, CommandKit_ptr c, LayoutKit_ptr l, ToolKit_ptr t, WidgetKit_ptr w)
  : ::Motif::Choice(p, c, l, t, w)
{}

Tag CheckboxChoice::appendItem(Graphic_ptr g)
{
  Trace trace("CheckboxChoice::append");
  RefCount_var<Warsaw::Controller> toggle = tools->toggle(RefCount_var<Warsaw::Graphic>(Warsaw::Graphic::_nil()));
  Tag tag = _state->add(toggle);
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
  Tag tag = _state->add(toggle);
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
  _state->remove(t);
  RefCount_var<Warsaw::Graphic> box = body();
  box->remove(t);
}

};
