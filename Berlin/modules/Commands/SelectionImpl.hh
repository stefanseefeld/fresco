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
#ifndef _SelectionImpl_hh
#define _SelectionImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Telltale.hh>
#include <Fresco/Selection.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/RefCountVar.hh>
#include <vector>
#include <algorithm>
#include <functional>

class SelectionImpl : public virtual POA_Fresco::Selection,
	              public SubjectImpl
{
  class Observer;
  friend class Observer;
  typedef std::vector<Observer *> list_t;
  struct Id_eq : public std::unary_function<Observer *, bool>
  {
    Id_eq(Fresco::Tag t) : id(t) {}
    bool operator()(const Observer *) const;
    Fresco::Tag id;
  };
 public:
  SelectionImpl(Fresco::Selection::Policy, Fresco::TelltaleConstraint_ptr);
  virtual ~SelectionImpl();
  virtual Fresco::Selection::Policy type();
  virtual void type(Fresco::Selection::Policy);
  virtual Fresco::Tag add(Fresco::Telltale_ptr);
  virtual void remove(Fresco::Tag);
  virtual Fresco::Selection::Items *toggled();
 private:
  void update(Fresco::Tag, bool);
  void remove_observer(Fresco::Tag);
  Fresco::Tag uniqueId();
  CORBA::Long id_to_index(Fresco::Tag);
  Prague::Mutex mutex;
  Fresco::Selection::Policy policy;
  RefCount_var<Fresco::TelltaleConstraint> constraint;
  list_t items;
};

#endif
