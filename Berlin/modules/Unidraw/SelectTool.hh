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
#ifndef _UnidrawKit_SelectTool_hh
#define _UnidrawKit_SelectTool_hh

#include <Fresco/config.hh>
#include <Fresco/Transform.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/UnidrawKit.hh>
#include <Berlin/RefCountBaseImpl.hh>

namespace Berlin
{
  namespace UnidrawKit
  {

    class SelectTool : public virtual POA_Unidraw::Tool,
		       public RefCountBaseImpl
    {
      public:
	SelectTool(Fresco::Graphic_ptr);
	virtual ~SelectTool();
	virtual CORBA::Boolean grasp(Fresco::Controller_ptr,
				     Fresco::PickTraversal_ptr,
				     const Fresco::Input::Event &);
	virtual CORBA::Boolean manipulate(Fresco::PickTraversal_ptr,
					  const Fresco::Input::Event &);
	virtual Unidraw::Command_ptr effect(Fresco::PickTraversal_ptr,
					    const Fresco::Input::Event &);
      private:
	Fresco::Controller_var my_root;
	Fresco::GraphicIterator_var my_iterator;
	Fresco::Transform::Matrix my_matrix;
	Fresco::Graphic_var my_graphic;
	Fresco::Vertex my_begin;
	Fresco::Vertex my_end;
    };
    
  } // namespace
} // namespace

#endif
