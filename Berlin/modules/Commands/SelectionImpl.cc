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
#include <Fresco/Controller.hh>
#include <Berlin/ObserverImpl.hh>
#include "SelectionImpl.hh"

using namespace Prague;
using namespace Fresco;

/*
 * a little glue class to notify the Selection if the 'toggled'
 * flag in the Telltale changed state.
 */
class Berlin::CommandKit::SelectionImpl::Observer : public ObserverImpl
{
  public:
    Observer(SelectionImpl *, Telltale_ptr, Tag);
    ~Observer();
    Tag id() const { return my_t;}
    bool toggled() { return my_cached;}
    void update(const CORBA::Any &);
  private:
    SelectionImpl *my_selection;
    RefCount_var<Fresco::Telltale> my_item;
    bool my_cached;
    Tag my_t;
};

bool Berlin::CommandKit::SelectionImpl::Id_eq::operator()(const SelectionImpl::Observer *o) const
{ return o->id() == id; }

Berlin::CommandKit::SelectionImpl::Observer::Observer(SelectionImpl *s,
						      Telltale_ptr i,
                                                      Tag tt) :
    my_selection(s),
    my_item(RefCount_var<Fresco::Telltale>::increment(i)),
    my_cached(my_item->test(Fresco::Controller::toggled)),
    my_t(tt)
{ }

Berlin::CommandKit::SelectionImpl::Observer::~Observer()
{
    Trace trace("SelectionImpl::Observer::~Observer");
    my_item->detach(Observer_var(_this()));
    my_selection->remove_observer(my_t);
}

void Berlin::CommandKit::SelectionImpl::Observer::update(const CORBA::Any &any)
{
    bool toggled = my_item->test(Fresco::Controller::toggled);
    if (toggled == my_cached) return; // not for us...
    my_cached = toggled;
    my_selection->update(my_t, toggled);
}

Berlin::CommandKit::SelectionImpl::SelectionImpl(Fresco::Selection::Policy p,
                                                 TelltaleConstraint_ptr c) :
  my_policy(p),
  my_constraint(RefCount_var<TelltaleConstraint>::increment(c))
{ Trace trace("SelectionImpl::SelectionImpl"); }

Berlin::CommandKit::SelectionImpl::~SelectionImpl()
{
    Trace trace("SelectionImpl::~SelectionImpl");
    // for (list_t::iterator i = my_items.begin(); i != my_items.end(); i++)
    // try { (*i)->deactivate();}
    // catch (CORBA::OBJECT_NOT_EXIST &) {}
}

Fresco::Selection::Policy Berlin::CommandKit::SelectionImpl::type()
{ return my_policy; }
void Berlin::CommandKit::SelectionImpl::type(Fresco::Selection::Policy p)
{
    Prague::Guard<Mutex> guard(my_mutex);
    my_policy = p;
}

Tag Berlin::CommandKit::SelectionImpl::add(Telltale_ptr t)
{
    Trace trace("SelectionImpl::add");
    Prague::Guard<Mutex> guard(my_mutex);
    Tag id = uniqueId();
    Observer *observer = new Observer(this, t, id);
    // activate(observer);
    t->attach(Observer_var(observer->_this()));
    if (!CORBA::is_nil(my_constraint)) my_constraint->add(t);
    my_items.push_back(observer);
    return id;
}

void Berlin::CommandKit::SelectionImpl::remove(Tag t)
{
    Trace trace("SelectionImpl::remove");
    Prague::Guard<Mutex> guard(my_mutex);
    size_t i = id_to_index(t);
    if (i < my_items.size())
    {
        // if (!CORBA::is_nil(my_constraint)) my_constraint->remove(t);
        my_items[i]->destroy();
        my_items.erase(my_items.begin() + i);
    }
}

Selection::Items * Berlin::CommandKit::SelectionImpl::toggled()
{
    Trace trace("SelectionImpl::toggled");
    Prague::Guard<Mutex> guard(my_mutex);
    Fresco::Selection::Items_var ret = new Fresco::Selection::Items;
    for (list_t::iterator i = my_items.begin(); i != my_items.end(); i++)
        if ((*i)->toggled())
        {
            // FIXME: Use push_back() once we finally switch to gcc 3
            ret->length(ret->length() + 1);
            ret[ret->length() - 1] = (*i)->id();
        }
    return ret._retn();
}

void Berlin::CommandKit::SelectionImpl::update(Tag t, bool toggled)
{
    Trace trace("SelectionImpl::update");
    CORBA::Any any;
    Fresco::Selection::Item item;
    item.id = t;
    item.toggled = toggled;
    any <<= item;
    notify(any);
}

void Berlin::CommandKit::SelectionImpl::remove_observer(Tag t)
{
    Trace trace("SelectionImpl::remove_observer");
    Prague::Guard<Mutex> guard(my_mutex);
    size_t i = id_to_index(t);
    if (i < my_items.size()) my_items.erase(my_items.begin() + i);
}

Tag Berlin::CommandKit::SelectionImpl::uniqueId()
{
    Tag id;
    for (id = 0;
	 std::find_if(my_items.begin(), my_items.end(),
		      Id_eq(id)) != my_items.end();
	 ++id) { }
        return id;
}

CORBA::Long Berlin::CommandKit::SelectionImpl::id_to_index(Tag id)
{
    return std::find_if(my_items.begin(), my_items.end(),
			Id_eq(id)) - my_items.begin();
}
