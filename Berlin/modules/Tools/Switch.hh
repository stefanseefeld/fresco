/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Switch_hh
#define _Switch_hh

#include <Fresco/config.hh>
#include <Fresco/Telltale.hh>
#include <Fresco/Region.hh>
#include <Berlin/ViewImpl.hh>
#include <Berlin/MonoGraphic.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/RefCountVar.hh>

class Switch : public virtual ViewImpl,
	       public MonoGraphic
{
public:
  Switch(Fresco::Telltale::Mask mask);
  virtual ~Switch();
  void init(Fresco::Graphic_ptr, Fresco::Graphic_ptr);
  virtual void attach(Fresco::Telltale_ptr);
  virtual void update(const CORBA::Any &);
  virtual const char *object_name() { return "Switch";}
private:
  void set(Fresco::Graphic_ptr g1, Fresco::Graphic_ptr g2);
  Fresco::Graphic_var    my_alternate;
  Fresco::Telltale_var   my_telltale;
  bool                   my_on;
  Fresco::Telltale::Mask my_mask;
};

#endif
