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
#ifndef _daVinci_Commands_hh
#define _daVinci_Commands_hh

#include <Fresco/config.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/UnidrawKit.hh>
#include <daVinci/ServantBase.hh>

namespace daVinci
{
  class Command : public virtual POA_Unidraw::Command,
		  public ServantBase
  {
  public:
    Command();
    virtual ~Command();
    virtual void execute();
    virtual void store(Unidraw::Model_ptr, const CORBA::Any &);
    virtual CORBA::Any *recall(Unidraw::Model_ptr);
    virtual void destroy() { deactivate();}
  };

  class CreateCircleCommand : public Command
  {
  public:
    CreateCircleCommand(const Fresco::Vertex &, const Fresco::Vertex &);
    virtual void execute();
  private:
    Fresco::Vertex _begin, _end;
  };
};

#endif
