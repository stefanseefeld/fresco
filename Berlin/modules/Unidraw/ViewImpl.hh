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
#ifndef _UnidrawKit_ViewImpl_hh
#define _UnidrawKit_ViewImpl_hh

#include <Fresco/config.hh>
#include <Fresco/UnidrawKit.hh>
#include <Berlin/ControllerImpl.hh>

namespace Berlin
{
  namespace UnidrawKit
  {

    class UViewImpl : public virtual POA_Unidraw::View,
		      public ControllerImpl
    {
      public:
	UViewImpl(Unidraw::Model_ptr);
	virtual ~UViewImpl();
	virtual Unidraw::Model_ptr subject();
	virtual void traverse(Fresco::Traversal_ptr);
	virtual void draw(Fresco::DrawTraversal_ptr);
	virtual void pick(Fresco::PickTraversal_ptr);
	virtual CORBA::Boolean 
	handle_positional(Fresco::PickTraversal_ptr,
			  const Fresco::Input::Event &);
      private:
	Unidraw::Model_var my_model;
    };

  } // namespace
} // namespace

#endif
