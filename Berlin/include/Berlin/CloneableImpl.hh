#ifndef _CloneableImpl_hh
#define _CloneableImpl_hh

//
// $Id$
//
// This source file is a part of the Berlin Project.
// Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
// http://www.berlin-consortium.org
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public License
// as published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//

#include "Warsaw/Cloneable.hh"

// cloneable is a subclass of LifeCycleObject with some handy methods
// tacked on the side, a "copyStateToOther" pure virtual it forces
// derived classes to implement, an implementation of the
// LifeCycleObject operations in terms of copyStateToOther, and a
// session-management system which is rudimentary and probably will be
// replaced some day in the future when we know more.


class CloneableImpl : implements(Cloneable), public virtual omniLC::_threadControl
{
public: 
  virtual CosLifeCycle::LifeCycleObject_ptr copy ( CosLifeCycle::FactoryFinder_ptr  there, 
						   const CosLifeCycle::Criteria & the_criteria );
  void move ( CosLifeCycle::FactoryFinder_ptr  there, 
	      const CosLifeCycle::Criteria & the_criteria );
  virtual Cloneable_ptr clone(); // override with caution!
  void reload();
  void remove();
  void reference();
  void forget();

  // this is not exposed thru corba, but is called after the object is
  // all hooked up with lifecycle to register it with the appropriate
  // implementation managers.
  virtual void registerWithMyManagers();
};

#endif
