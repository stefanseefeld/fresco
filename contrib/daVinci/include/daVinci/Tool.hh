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
#ifndef _daVinci_Tool_hh
#define _daVinci_Tool_hh

#include <Fresco/config.hh>
#include <Fresco/UnidrawKit.hh>
#include <daVinci/RefCountBase.hh>

namespace daVinci
{

  class Manipulator;
  class Tool : public virtual POA_Unidraw::Tool,
	       public RefCountBase
  {
  public:
    Tool();
    virtual ~Tool();
    virtual CORBA::Boolean grasp(Fresco::Controller_ptr, Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    virtual CORBA::Boolean manipulate(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    virtual Unidraw::Command_ptr effect(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);

    virtual Manipulator         *create_manipulator(Fresco::Controller_ptr, Fresco::PickTraversal_ptr, const Fresco::Input::Event &) = 0;
    virtual Unidraw::Command_ptr interpret_manipulator(Manipulator *) = 0;
  private:
    Manipulator *_manipulator;
  };
  
};

#endif
