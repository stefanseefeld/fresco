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
#ifndef _ManipulatorImpl_hh
#define _ManipulatorImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/FigureKit.hh>
#include <Warsaw/ToolKit.hh>
#include <Warsaw/UnidrawKit.hh>
#include <Berlin/ServantBase.hh>

class ManipulatorImpl : public virtual POA_Unidraw::Manipulator,
			public ServantBase
{
public:
  ManipulatorImpl();
  virtual ~ManipulatorImpl();
  CORBA::Boolean grasp(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
  CORBA::Boolean manipulate(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
  Unidraw::Command_ptr effect(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
};

class SelectManipulator : public ManipulatorImpl
{
public:
  SelectManipulator();
  virtual ~SelectManipulator();
  CORBA::Boolean grasp(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
  CORBA::Boolean manipulate(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
  Unidraw::Command_ptr effect(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
};

#endif
